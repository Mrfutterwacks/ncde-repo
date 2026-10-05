/*
 * ncde-gtk-module.c — NCDE GliaTalk publisher for GTK apps (CDE reborn, no D-Bus).
 *
 * An in-process GTK module (loaded via GTK_MODULES) that turns any GTK app's own
 * GtkMenuBar into an NCDE global menu the ToolTalk way: it walks the menu bar and
 * publishes it as UTF-8 JSON in the `_NCDE_MENUS` X property on the app's own
 * top-level window — exactly the shape LaPivot's reader already understands:
 *   [ { "title":"File", "items":[ {"label":"New","id":101,"shortcut":"Ctrl+N",
 *       "enabled":true}, {"separator":true}, ... ] }, ... ]
 * and listens for the `_NCDE_MENU_INVOKE` ClientMessage (data.l[0] = item id) to
 * activate the matching GtkMenuItem. No D-Bus, no daemon, no dbusmenu — the X
 * display IS the session (GliaTalk spec). Foreign apps that expose no GtkMenuBar
 * simply publish nothing and keep the shell's relay trio; nothing breaks.
 *
 * Build:  gcc -shared -fPIC -o ncde-gtk-module.so ncde-gtk-module.c \
 *              $(pkg-config --cflags --libs gtk+-3.0 x11)
 * Load:   GTK_MODULES=ncde-gtk-module  (per-session; a xinitrc.d drop-in replaces
 *         the old Canonical appmenu-gtk-module.sh).
 */

#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <string.h>

/* Set to 1 to hide the app's in-window menubar so the bar is the only menu
 * (true macOS/CDE global-menu look). 0 = leave it in place (safer default while
 * proving the pipe). Overridable at runtime with NCDE_GLOBALMENU_HIDE=0/1. */
#define NCDE_HIDE_LOCAL_DEFAULT 1

static Atom a_menus   = None;   /* _NCDE_MENUS       (UTF8 property)  */
static Atom a_invoke  = None;   /* _NCDE_MENU_INVOKE (ClientMessage)  */
static Atom a_utf8    = None;

/* ---- JSON helpers -------------------------------------------------------- */

static void json_escape(GString *out, const char *s)
{
    if (!s) return;
    for (; *s; s++) {
        switch (*s) {
        case '"':  g_string_append(out, "\\\""); break;
        case '\\': g_string_append(out, "\\\\"); break;
        case '\n': g_string_append(out, "\\n");  break;
        case '\r': g_string_append(out, "\\r");  break;
        case '\t': g_string_append(out, "\\t");  break;
        default:
            if ((unsigned char)*s < 0x20) g_string_append_printf(out, "\\u%04x", *s);
            else                          g_string_append_c(out, *s);
        }
    }
}

/* GtkMenuItem label with mnemonic underscores stripped ("_File" -> "File"). */
static char *item_label(GtkMenuItem *mi)
{
    const char *raw = gtk_menu_item_get_label(mi);
    if (!raw || !*raw) return NULL;                 /* image-only / separator */
    GString *o = g_string_new(NULL);
    for (const char *p = raw; *p; p++) {
        if (*p == '_') { if (p[1] == '_') { g_string_append_c(o, '_'); p++; } /* "__" -> "_" */ }
        else g_string_append_c(o, *p);
    }
    return g_string_free(o, FALSE);
}

/* Best-effort accelerator text from a child GtkAccelLabel ("Ctrl+N" etc.). */
static char *item_accel(GtkMenuItem *mi)
{
    GtkWidget *child = gtk_bin_get_child(GTK_BIN(mi));
    if (child && GTK_IS_ACCEL_LABEL(child)) {
        /* GtkAccelLabel keeps the accel string internally; fetch via the
         * private-but-stable text the label renders. */
        char *s = NULL;
        g_object_get(child, "label", &s, NULL);   /* the visible text only */
        (void)s;
        if (s) g_free(s);
    }
    return NULL; /* v1: shortcuts omitted (shell shows the label); v2 fills these */
}

/* ---- id map: per-toplevel {id -> GtkMenuItem*} --------------------------- */

static GHashTable *toplevel_map(GtkWidget *top, gboolean create)
{
    GHashTable *m = g_object_get_data(G_OBJECT(top), "ncde-menu-map");
    if (!m && create) {
        m = g_hash_table_new(g_direct_hash, g_direct_equal);
        g_object_set_data_full(G_OBJECT(top), "ncde-menu-map",
                               m, (GDestroyNotify)g_hash_table_destroy);
    }
    return m;
}

/* Serialize one submenu's items into the JSON array, registering ids. */
static void append_items(GString *json, GtkMenuShell *sub,
                         GHashTable *map, int *next_id)
{
    GList *kids = gtk_container_get_children(GTK_CONTAINER(sub)), *l;
    gboolean first = TRUE;
    for (l = kids; l; l = l->next) {
        GtkWidget *w = l->data;
        if (GTK_IS_SEPARATOR_MENU_ITEM(w)) {
            g_string_append(json, first ? "" : ",");
            g_string_append(json, "{\"separator\":true}");
            first = FALSE;
            continue;
        }
        if (!GTK_IS_MENU_ITEM(w)) continue;
        char *lbl = item_label(GTK_MENU_ITEM(w));
        if (!lbl) continue;                         /* skip unlabeled */
        int id = (*next_id)++;
        g_hash_table_insert(map, GINT_TO_POINTER(id), w);
        char *acc = item_accel(GTK_MENU_ITEM(w));
        gboolean en = gtk_widget_get_sensitive(w);
        g_string_append(json, first ? "" : ",");
        g_string_append(json, "{\"label\":\"");
        json_escape(json, lbl);
        g_string_append_printf(json, "\",\"id\":%d,\"enabled\":%s",
                               id, en ? "true" : "false");
        if (acc && *acc) { g_string_append(json, ",\"shortcut\":\""); json_escape(json, acc); g_string_append_c(json, '"'); }
        g_string_append_c(json, '}');
        first = FALSE;
        g_free(lbl); g_free(acc);
    }
    g_list_free(kids);
}

/* ---- publish ------------------------------------------------------------- */

static void publish_menubar(GtkMenuBar *bar)
{
    GtkWidget *top = gtk_widget_get_toplevel(GTK_WIDGET(bar));
    if (!GTK_IS_WINDOW(top)) return;
    GdkWindow *gw = gtk_widget_get_window(top);
    if (!gw) return;                                /* not realized yet */

    GHashTable *map = toplevel_map(top, TRUE);
    g_hash_table_remove_all(map);
    int next_id = 101;

    GString *json = g_string_new("[");
    GList *tops = gtk_container_get_children(GTK_CONTAINER(bar)), *l;
    gboolean first = TRUE;
    for (l = tops; l; l = l->next) {
        if (!GTK_IS_MENU_ITEM(l->data)) continue;
        GtkMenuItem *mi = l->data;
        GtkWidget *sub = gtk_menu_item_get_submenu(mi);
        char *title = item_label(mi);
        if (!title || !GTK_IS_MENU_SHELL(sub)) { g_free(title); continue; }
        g_string_append(json, first ? "" : ",");
        g_string_append(json, "{\"title\":\"");
        json_escape(json, title);
        g_string_append(json, "\",\"items\":[");
        append_items(json, GTK_MENU_SHELL(sub), map, &next_id);
        g_string_append(json, "]}");
        first = FALSE;
        g_free(title);
    }
    g_list_free(tops);
    g_string_append_c(json, ']');

    Display *dpy = GDK_WINDOW_XDISPLAY(gw);
    Window   xid = GDK_WINDOW_XID(gw);
    XChangeProperty(dpy, xid, a_menus, a_utf8, 8, PropModeReplace,
                    (unsigned char *)json->str, json->len);
    g_string_free(json, TRUE);

    const char *hide = g_getenv("NCDE_GLOBALMENU_HIDE");
    gboolean do_hide = hide ? (atoi(hide) != 0) : NCDE_HIDE_LOCAL_DEFAULT;
    if (do_hide) gtk_widget_hide(GTK_WIDGET(bar));
}

/* Re-publish shortly after map so late-populated menus are captured. */
static gboolean idle_publish(gpointer bar) { if (GTK_IS_MENU_BAR(bar)) publish_menubar(bar); return G_SOURCE_REMOVE; }

/* Emission hook on GtkWidget::map — fires for every widget mapped anywhere. */
static gboolean on_map(GSignalInvocationHint *ih, guint n, const GValue *pv, gpointer d)
{
    GtkWidget *w = g_value_get_object(&pv[0]);
    if (GTK_IS_MENU_BAR(w)) {
        publish_menubar(GTK_MENU_BAR(w));
        g_idle_add(idle_publish, w);               /* catch dynamic items */
    }
    return TRUE;                                    /* keep the hook installed */
}

/* ---- invoke -------------------------------------------------------------- */

static GdkFilterReturn on_xevent(GdkXEvent *xe, GdkEvent *ev, gpointer d)
{
    XEvent *x = (XEvent *)xe;
    if (x->type != ClientMessage) return GDK_FILTER_CONTINUE;
    if (x->xclient.message_type != a_invoke) return GDK_FILTER_CONTINUE;
    long id = x->xclient.data.l[0];
#if GTK_MAJOR_VERSION >= 3
    GdkWindow *gw = gdk_x11_window_lookup_for_display(gdk_display_get_default(),
                                                      x->xclient.window);
#else
    GdkWindow *gw = gdk_window_lookup_for_display(gdk_display_get_default(),
                                                  x->xclient.window);
#endif
    if (!gw) return GDK_FILTER_REMOVE;
    gpointer ud = NULL;
    gdk_window_get_user_data(gw, &ud);
    if (!GTK_IS_WIDGET(ud)) return GDK_FILTER_REMOVE;
    GtkWidget *top = gtk_widget_get_toplevel(GTK_WIDGET(ud));
    GHashTable *map = toplevel_map(top, FALSE);
    if (map) {
        GtkWidget *item = g_hash_table_lookup(map, GINT_TO_POINTER((int)id));
        if (item && GTK_IS_MENU_ITEM(item) && gtk_widget_get_sensitive(item))
            gtk_menu_item_activate(GTK_MENU_ITEM(item));
    }
    return GDK_FILTER_REMOVE;
}

/* ---- module entry -------------------------------------------------------- */

G_MODULE_EXPORT void gtk_module_init(gint *argc, gchar ***argv)
{
    GdkDisplay *disp = gdk_display_get_default();
#if GTK_MAJOR_VERSION >= 3
    if (!disp || !GDK_IS_X11_DISPLAY(disp)) return;   /* X11 only, by design */
#else
    if (!disp) return;                                /* GDK2 is X11-only */
#endif
    Display *dpy = GDK_DISPLAY_XDISPLAY(disp);
    a_menus  = XInternAtom(dpy, "_NCDE_MENUS", False);
    a_invoke = XInternAtom(dpy, "_NCDE_MENU_INVOKE", False);
    a_utf8   = XInternAtom(dpy, "UTF8_STRING", False);

    g_signal_add_emission_hook(g_signal_lookup("map", GTK_TYPE_WIDGET),
                               0, on_map, NULL, NULL);
    gdk_window_add_filter(NULL, on_xevent, NULL);
}

G_MODULE_EXPORT void gtk_module_display_init(GdkDisplay *display) { }

/* GTK checks this to allow loading into setuid apps; we are safe (no privilege). */
G_MODULE_EXPORT gchar *g_module_check_init(GModule *module) { return NULL; }
