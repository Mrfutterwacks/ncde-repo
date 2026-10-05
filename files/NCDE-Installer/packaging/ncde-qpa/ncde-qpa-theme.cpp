/*
 * ncde-qpa-theme.cpp — NCDE GliaTalk publisher for Qt apps (KDE's mechanism, no D-Bus).
 *
 * A Qt6 QPA platform theme (QT_QPA_PLATFORMTHEME=ncde). Qt hands every app's menu bar to
 * createPlatformMenuBar() IN-PROCESS; we implement the QPlatformMenuBar/Menu/MenuItem
 * interface, serialize the tree to `_NCDE_MENUS` (the same X property + JSON shape LaPivot
 * already reads), and on the `_NCDE_MENU_INVOKE` ClientMessage we emit the item's activated()
 * signal — which triggers the real QAction in-process. Same idea as appmenu-qt5, but the
 * transport is an X property instead of D-Bus. Extends QGenericUnixTheme so non-menu theming
 * (fonts/palette/dialogs) keeps working. Covers Qt apps with a real QMenuBar / Qt.labs.platform
 * menu; QML-custom-menu house apps have no native menu to capture (they publish their own).
 *
 * Build:
 *   moc ncde-qpa-theme.cpp -o moc_ncde.cpp
 *   g++ -shared -fPIC -DQT_NO_KEYWORDS -o libncde-qpa.so ncde-qpa-theme.cpp moc_ncde.cpp \
 *       $(pkg-config --cflags Qt6Gui) -I<QtGui private> -lQt6Gui -lQt6Core -lxcb
 */

#include <qpa/qplatformtheme.h>
#include <qpa/qplatformthemeplugin.h>
#include <qpa/qplatformmenu.h>
#include <private/qgenericunixtheme_p.h>
#include <QGuiApplication>
#include <QAbstractNativeEventFilter>
#include <QWindow>
#include <QHash>
#include <QList>
#include <QByteArray>
#include <xcb/xcb.h>
#include <cstdio>

// ---- shared X helpers -------------------------------------------------------
static xcb_connection_t *xcb_conn()
{
    auto *x11 = qGuiApp->nativeInterface<QNativeInterface::QX11Application>();
    return x11 ? x11->connection() : nullptr;
}
static xcb_atom_t intern(const char *name)
{
    xcb_connection_t *c = xcb_conn(); if (!c) return XCB_NONE;
    xcb_intern_atom_cookie_t ck = xcb_intern_atom(c, 0, (uint16_t)strlen(name), name);
    xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(c, ck, nullptr);
    xcb_atom_t a = r ? r->atom : XCB_NONE; free(r); return a;
}
static xcb_atom_t A_MENUS()  { static xcb_atom_t a = intern("_NCDE_MENUS");        return a; }
static xcb_atom_t A_INVOKE() { static xcb_atom_t a = intern("_NCDE_MENU_INVOKE");   return a; }
static xcb_atom_t A_UTF8()   { static xcb_atom_t a = intern("UTF8_STRING");         return a; }

static void jesc(QByteArray &o, const QString &s)
{
    for (QChar qc : s) {
        ushort c = qc.unicode();
        switch (c) {
        case '"':  o += "\\\""; break;  case '\\': o += "\\\\"; break;
        case '\n': o += "\\n";  break;  case '\r': o += "\\r";  break;
        case '\t': o += "\\t";  break;
        default: if (c < 0x20) o += QByteArray("\\u") + QByteArray::number(c,16).rightJustified(4,'0');
                 else o += QString(qc).toUtf8();
        }
    }
}
// strip Qt mnemonic '&' ("&File" -> "File", "&&" -> "&")
static QString clean(const QString &in)
{
    QString o; for (int i=0;i<in.size();++i){ if(in[i]=='&'){ if(i+1<in.size()&&in[i+1]=='&'){o+='&';++i;} } else o+=in[i]; } return o;
}

// ---- menu item --------------------------------------------------------------
class NcdeMenuBar; class NcdeMenu;
class NcdeMenuItem : public QPlatformMenuItem {
public:
    quintptr m_tag=0; QString m_text; bool m_sep=false,m_enabled=true,m_visible=true,m_checkable=false,m_checked=false;
    QPlatformMenu *m_sub=nullptr; int m_id=0;
    void setTag(quintptr t) override { m_tag=t; } quintptr tag() const override { return m_tag; }
    void setText(const QString &t) override { m_text=t; }
    void setIcon(const QIcon &) override {}
    void setMenu(QPlatformMenu *m) override { m_sub=m; }
    void setVisible(bool v) override { m_visible=v; }
    void setIsSeparator(bool s) override { m_sep=s; }
    void setFont(const QFont &) override {}
    void setRole(MenuRole) override {}
    void setCheckable(bool c) override { m_checkable=c; }
    void setChecked(bool c) override { m_checked=c; }
    void setShortcut(const QKeySequence&) override {}
    void setEnabled(bool e) override { m_enabled=e; }
    void setIconSize(int) override {}
    void fire() { Q_EMIT activated(); }
};

// ---- menu -------------------------------------------------------------------
class NcdeMenu : public QPlatformMenu {
public:
    quintptr m_tag=0; QString m_text; bool m_enabled=true,m_visible=true; QList<NcdeMenuItem*> m_items;
    NcdeMenuBar *m_bar=nullptr;
    void reserialize();
    void insertMenuItem(QPlatformMenuItem *mi, QPlatformMenuItem *before) override {
        int idx = before ? m_items.indexOf(static_cast<NcdeMenuItem*>(before)) : -1;
        if (idx<0) m_items.append(static_cast<NcdeMenuItem*>(mi));
        else m_items.insert(idx, static_cast<NcdeMenuItem*>(mi));
        reserialize();
    }
    void removeMenuItem(QPlatformMenuItem *mi) override { m_items.removeAll(static_cast<NcdeMenuItem*>(mi)); reserialize(); }
    void syncMenuItem(QPlatformMenuItem *) override { reserialize(); }
    void syncSeparatorsCollapsible(bool) override {}
    void setTag(quintptr t) override { m_tag=t; } quintptr tag() const override { return m_tag; }
    void setText(const QString &t) override { m_text=t; reserialize(); }
    void setIcon(const QIcon &) override {}
    void setEnabled(bool e) override { m_enabled=e; }
    bool isEnabled() const override { return m_enabled; }
    void setVisible(bool v) override { m_visible=v; }
    void setMinimumWidth(int) override {}
    void setFont(const QFont &) override {}
    void setMenuType(MenuType) override {}
    void showPopup(const QWindow*, const QRect&, const QPlatformMenuItem*) override {}
    void dismiss() override {}
    QPlatformMenuItem *menuItemAt(int p) const override { return (p>=0&&p<m_items.size())?m_items[p]:nullptr; }
    QPlatformMenuItem *menuItemForTag(quintptr t) const override { for(auto*i:m_items) if(i->tag()==t) return i; return nullptr; }
    QPlatformMenuItem *createMenuItem() const override { return new NcdeMenuItem; }
    QPlatformMenu *createSubMenu() const override { return new NcdeMenu; }
};

static void ncde_install_filter_once();
// ---- menu bar ---------------------------------------------------------------
class NcdeMenuBar : public QPlatformMenuBar {
public:
    QWindow *m_win=nullptr; QList<NcdeMenu*> m_menus; QHash<int,NcdeMenuItem*> m_idmap;
    void insertMenu(QPlatformMenu *m, QPlatformMenu *before) override {
        auto *nm=static_cast<NcdeMenu*>(m); nm->m_bar=this;
        int idx = before ? m_menus.indexOf(static_cast<NcdeMenu*>(before)) : -1;
        if (idx<0) m_menus.append(nm); else m_menus.insert(idx,nm);
        serialize();
    }
    void removeMenu(QPlatformMenu *m) override { m_menus.removeAll(static_cast<NcdeMenu*>(m)); serialize(); }
    void syncMenu(QPlatformMenu *) override { serialize(); }
    void handleReparent(QWindow *w) override { m_win=w; serialize(); }
    QWindow *parentWindow() const override { return m_win; }
    QPlatformMenu *menuForTag(quintptr t) const override { for(auto*m:m_menus) if(m->tag()==t) return m; return nullptr; }
    QPlatformMenu *createMenu() const override { return new NcdeMenu; }

    void invoke(int id){ if(auto*it=m_idmap.value(id,nullptr)) if(it->m_enabled) it->fire(); }

    void serialize(){
        if(!m_win) return;
        xcb_connection_t *c=xcb_conn(); if(!c) return;
        m_idmap.clear(); int next=101;
        QByteArray j="[";
        bool firstMenu=true;
        for(NcdeMenu *m:m_menus){
            if(!m->m_visible) continue;
            j += firstMenu?"":","; firstMenu=false;
            j += "{\"title\":\""; jesc(j, clean(m->m_text)); j += "\",\"items\":[";
            bool firstItem=true;
            for(NcdeMenuItem *it:m->m_items){
                if(!it->m_visible) continue;
                j += firstItem?"":","; firstItem=false;
                if(it->m_sep){ j += "{\"separator\":true}"; continue; }
                int id=next++; it->m_id=id; m_idmap.insert(id,it);
                j += "{\"label\":\""; jesc(j, clean(it->m_text));
                j += "\",\"id\":"; j += QByteArray::number(id);
                j += ",\"enabled\":"; j += it->m_enabled?"true":"false";
                if(it->m_checkable){ j += ",\"checked\":"; j += it->m_checked?"true":"false"; }
                j += "}";
            }
            j += "]}";
        }
        j += "]";
        xcb_change_property(c, XCB_PROP_MODE_REPLACE, (xcb_window_t)m_win->winId(),
                            A_MENUS(), A_UTF8(), 8, j.size(), j.constData());
        xcb_flush(c);
        registry().insert((xcb_window_t)m_win->winId(), this);
        ncde_install_filter_once();
    }
    static QHash<xcb_window_t,NcdeMenuBar*>& registry(){ static QHash<xcb_window_t,NcdeMenuBar*> r; return r; }
    ~NcdeMenuBar(){ if(m_win) registry().remove((xcb_window_t)m_win->winId()); }
};
void NcdeMenu::reserialize(){ if(m_bar) m_bar->serialize(); }

// ---- invoke event filter ----------------------------------------------------
class NcdeInvokeFilter : public QAbstractNativeEventFilter {
public:
    bool nativeEventFilter(const QByteArray &t, void *msg, qintptr *) override {
        if(t!="xcb_generic_event_t") return false;
        auto *ev=static_cast<xcb_generic_event_t*>(msg);
        if((ev->response_type & ~0x80)!=XCB_CLIENT_MESSAGE) return false;
        auto *cm=reinterpret_cast<xcb_client_message_event_t*>(ev);
        if(cm->type!=A_INVOKE()) return false;
        if(auto*bar=NcdeMenuBar::registry().value(cm->window,nullptr))
            bar->invoke((int)cm->data.data32[0]);
        return false;
    }
};

static void ncde_install_filter_once(){ static bool done=false; if(!done && qGuiApp){ static NcdeInvokeFilter f; qGuiApp->installNativeEventFilter(&f); done=true; } }

// ---- theme + plugin ---------------------------------------------------------
class NcdeTheme : public QGenericUnixTheme {
public:
    NcdeTheme(){}
    QPlatformMenuItem *createPlatformMenuItem() const override { return new NcdeMenuItem; }
    QPlatformMenu     *createPlatformMenu()     const override { return new NcdeMenu; }
    QPlatformMenuBar  *createPlatformMenuBar()  const override { return new NcdeMenuBar; }
};

class NcdeThemePlugin : public QPlatformThemePlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QPA.QPlatformThemeFactoryInterface.5.1" FILE "ncde.json")
public:
    QPlatformTheme *create(const QString &key, const QStringList &) override {
        return key.compare(QLatin1String("ncde"), Qt::CaseInsensitive)==0 ? new NcdeTheme : nullptr;
    }
};

#include "moc_ncde-qpa-theme.cpp"
