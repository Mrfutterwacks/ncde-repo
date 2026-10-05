/*
 * ncde-gtk4-preload.c — NCDE GliaTalk publisher for GTK4 apps (no D-Bus).
 *
 * GTK4 removed loadable modules AND the menu bar AND gdk_window_add_filter — so the
 * mainstream answer is "export the menu over D-Bus." NCDE says no D-Bus, ever. Open
 * source gives us the two seams to do it in-process anyway:
 *   1. LD_PRELOAD interposes gtk_application_set_menubar() -> we grab the GMenuModel.
 *   2. The GdkX11Display "xevent" signal (GDK4's replacement for gdk_window_add_filter)
 *      lets us catch the _NCDE_MENU_INVOKE ClientMessage in-process.
 * We serialize the GMenuModel to `_NCDE_MENUS` (the same X property + JSON shape LaPivot
 * reads) and on invoke fire the item's GAction via g_action_group_activate_action() —
 * in-process, so it just works. No dbusmenu, no org.gtk.Menus.
 *
 * Build:  gcc -shared -fPIC -o ncde-gtk4-preload.so ncde-gtk4-preload.c \
 *              $(pkg-config --cflags --libs gtk4 gtk4-x11) -ldl
 * Load:   GTK4 apps only: export LD_PRELOAD=/usr/lib/ncde/ncde-gtk4-preload.so
 */
#define _GNU_SOURCE
#include <gtk/gtk.h>
#include <gdk/x11/gdkx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static GtkApplication *g_app = NULL;
static GMenuModel     *g_model = NULL;
static gboolean        g_xhooked = FALSE;
static GHashTable     *g_idmap = NULL;   /* int id -> gchar* "app.new" */

static Display *xdpy(void)
{
    GdkDisplay *d = gdk_display_get_default();
    return (d && GDK_IS_X11_DISPLAY(d)) ? gdk_x11_display_get_xdisplay(GDK_X11_DISPLAY(d)) : NULL;
}
static Atom atom(const char *n){ Display*d=xdpy(); return d?XInternAtom(d,n,False):None; }

static void jesc(GString *o, const char *s)
{
    if(!s) return;
    for(; *s; s++){
        switch(*s){
        case '"': g_string_append(o,"\\\""); break; case '\\': g_string_append(o,"\\\\"); break;
        case '\n': g_string_append(o,"\\n"); break; case '\r': g_string_append(o,"\\r"); break;
        case '\t': g_string_append(o,"\\t"); break;
        default: if((unsigned char)*s < 0x20) g_string_append_printf(o,"\\u%04x",*s); else g_string_append_c(o,*s);
        }
    }
}

/* Walk one submenu model's items into the JSON array; flatten sections with separators. */
static void walk_items(GString *j, GMenuModel *m, int *next, gboolean *first)
{
    int n = g_menu_model_get_n_items(m);
    for(int i=0;i<n;i++){
        GMenuModel *sect = g_menu_model_get_item_link(m,i,G_MENU_LINK_SECTION);
        if(sect){
            if(!*first){ g_string_append(j,","); g_string_append(j,"{\"separator\":true}"); }
            *first = TRUE; /* force no leading comma issues handled by separator */
            walk_items(j, sect, next, first);
            g_object_unref(sect);
            continue;
        }
        char *label=NULL, *action=NULL;
        g_menu_model_get_item_attribute(m,i,"label","s",&label);
        g_menu_model_get_item_attribute(m,i,G_MENU_ATTRIBUTE_ACTION,"s",&action);
        GMenuModel *sub = g_menu_model_get_item_link(m,i,G_MENU_LINK_SUBMENU);
        if(label){
            int id = (*next)++;
            g_string_append(j, *first?"":","); *first=FALSE;
            g_string_append(j,"{\"label\":\""); jesc(j,label);
            g_string_append_printf(j,"\",\"id\":%d,\"enabled\":true}",id);
            if(action) g_hash_table_insert(g_idmap, GINT_TO_POINTER(id), g_strdup(action));
        }
        g_free(label); g_free(action);
        if(sub) g_object_unref(sub);
    }
}

static Window active_xid(void)
{
    if(!g_app) return 0;
    GtkWindow *w = gtk_application_get_active_window(g_app);
    if(!w){ GList*ws=gtk_application_get_windows(g_app); if(ws) w=ws->data; }
    if(!w) return 0;
    GdkSurface *s = gtk_native_get_surface(GTK_NATIVE(w));
    if(!s || !GDK_IS_X11_SURFACE(s)) return 0;
    return (Window)gdk_x11_surface_get_xid(GDK_X11_SURFACE(s));
}

static void publish(void)
{
    Display *d = xdpy(); if(!d || !g_model) return;
    Window xid = active_xid(); if(!xid) return;
    if(!g_idmap) g_idmap = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,g_free);
    else g_hash_table_remove_all(g_idmap);
    int next=101; gboolean firstTop=TRUE;
    GString *j = g_string_new("[");
    int n = g_menu_model_get_n_items(g_model);
    for(int i=0;i<n;i++){
        char *label=NULL;
        g_menu_model_get_item_attribute(g_model,i,"label","s",&label);
        GMenuModel *sub = g_menu_model_get_item_link(g_model,i,G_MENU_LINK_SUBMENU);
        if(!sub){ g_free(label); continue; }
        g_string_append(j, firstTop?"":","); firstTop=FALSE;
        g_string_append(j,"{\"title\":\""); jesc(j, label?label:""); g_string_append(j,"\",\"items\":[");
        gboolean firstItem=TRUE;
        walk_items(j, sub, &next, &firstItem);
        g_string_append(j,"]}");
        g_free(label); g_object_unref(sub);
    }
    g_string_append_c(j,']');
    XChangeProperty(d, xid, atom("_NCDE_MENUS"), atom("UTF8_STRING"), 8,
                    PropModeReplace, (unsigned char*)j->str, j->len);
    XFlush(d);
    g_string_free(j, TRUE);
}

static gboolean publish_retry(gpointer tries)
{
    if(active_xid()){ publish(); return G_SOURCE_REMOVE; }
    int t = GPOINTER_TO_INT(tries) - 1;
    return t>0 ? G_SOURCE_CONTINUE : G_SOURCE_REMOVE;   /* give up after ~4s */
}

static void activate_action(const char *full)
{
    if(!full) return;
    const char *dot = strchr(full,'.');
    if(!dot){ if(g_app) g_action_group_activate_action(G_ACTION_GROUP(g_app), full, NULL); return; }
    char scope[8]={0}; int sl = dot-full; if(sl>7) sl=7; memcpy(scope,full,sl);
    const char *name = dot+1;
    if(!strcmp(scope,"app") && g_app)
        g_action_group_activate_action(G_ACTION_GROUP(g_app), name, NULL);
    else if(!strcmp(scope,"win")){
        GtkWindow *w = g_app? gtk_application_get_active_window(g_app):NULL;
        if(w && G_IS_ACTION_GROUP(w)) g_action_group_activate_action(G_ACTION_GROUP(w), name, NULL);
    }
}

static gboolean on_xevent(GdkX11Display *display, XEvent *xe, gpointer u)
{
    (void)display;(void)u;
    if(xe->type != ClientMessage) return FALSE;
    if(xe->xclient.message_type != atom("_NCDE_MENU_INVOKE")) return FALSE;
    int id = (int)xe->xclient.data.l[0];
    if(g_idmap){ const char*a=g_hash_table_lookup(g_idmap,GINT_TO_POINTER(id)); if(a) activate_action(a); }
    return FALSE;   /* let GDK keep processing */
}

/* ---- the interposed symbol ---- */
typedef void (*set_menubar_t)(GtkApplication*, GMenuModel*);
void gtk_application_set_menubar(GtkApplication *app, GMenuModel *model)
{
    static set_menubar_t real = NULL;
    if(!real) real = (set_menubar_t)dlsym(RTLD_NEXT, "gtk_application_set_menubar");
    if(real) real(app, model);
    g_app = app; g_model = model;
    if(!g_xhooked){
        GdkDisplay *d = gdk_display_get_default();
        if(d && GDK_IS_X11_DISPLAY(d)){ g_signal_connect(d,"xevent",G_CALLBACK(on_xevent),NULL); g_xhooked=TRUE; }
    }
    g_timeout_add(200, publish_retry, GINT_TO_POINTER(20));
}
