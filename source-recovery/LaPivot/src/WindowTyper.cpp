// WindowTyper — see WindowTyper.h for the spec and the defect list.
// Rebuilt from oracle: decomp/WindowTyper.c (ctor 0x1a30ea, eventFilter 0x1a31fc,
// internAtoms 0x1a3358, intern 0x1a34ee, roleOf 0x1a3630, stamp 0x1a3920).
#include "WindowTyper.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QWindow>
#include <QtLogging>

#include <cstdlib>
#include <cstring>
#include <xcb/xcb.h>
#include <xcb/xcb_icccm.h>

WindowTyper::WindowTyper(QObject *parent) : QObject(parent)
{
    // W1: X connection might not be ready yet; install event filter but defer internAtoms
    QCoreApplication *app = QCoreApplication::instance();
    if (app) {
        app->installEventFilter(this);
    }
}

WindowTyper::~WindowTyper()
{
    QCoreApplication *app = QCoreApplication::instance();
    if (app) {
        app->removeEventFilter(this);
    }
}

void WindowTyper::ensureAtoms()
{
    if (m_xcb && m_netWmWindowType == XCB_ATOM_NONE) {
        internAtoms();
    }
}

void WindowTyper::internAtoms()
{
    QGuiApplication *guiApp = qobject_cast<QGuiApplication *>(QCoreApplication::instance());
    if (!guiApp)
        return;

    auto *x11 = guiApp->nativeInterface<QNativeInterface::QX11Application>();
    if (!x11)
        return;

    m_xcb = x11->connection();
    if (!m_xcb)
        return;

    m_netWmWindowType = intern("_NET_WM_WINDOW_TYPE");
    if (m_netWmWindowType == XCB_ATOM_NONE)
        return;

    // Role -> atom mapping (same as oracle)
    struct RoleAtom { const char *role; const char *atomName; };
    constexpr RoleAtom kRoles[] = {
        { "desktop",       "_NET_WM_WINDOW_TYPE_DESKTOP" },
        { "toppanel",      "_NET_WM_WINDOW_TYPE_DOCK" },
        { "bottompanel",   "_NET_WM_WINDOW_TYPE_DOCK" },
        { "dock",          "_NET_WM_WINDOW_TYPE_DOCK" },
        { "expose",        "_NET_WM_WINDOW_TYPE_UTILITY" },
        { "fadecurtain",   "_NET_WM_WINDOW_TYPE_SPLASH" },
        { "notification",  "_NET_WM_WINDOW_TYPE_NOTIFICATION" },
        { "tooltip",       "_NET_WM_WINDOW_TYPE_TOOLTIP" },
        { "menu",          "_NET_WM_WINDOW_TYPE_POPUP_MENU" },
        { "toolbar",       "_NET_WM_WINDOW_TYPE_TOOLBAR" },
        { "dialog",        "_NET_WM_WINDOW_TYPE_DIALOG" },
    };

    for (const auto &ra : kRoles) {
        m_roleAtoms[ra.role] = intern(ra.atomName);
    }
}

xcb_atom_t WindowTyper::intern(const char *name)
{
    if (!m_xcb)
        return XCB_ATOM_NONE;

    xcb_intern_atom_cookie_t ck = xcb_intern_atom(m_xcb, 0, strlen(name), name);
    xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(m_xcb, ck, nullptr);
    xcb_atom_t atom = r ? r->atom : static_cast<xcb_atom_t>(XCB_ATOM_NONE);
    free(r);
    return atom;
}

QString WindowTyper::roleOf(QWindow *win) const
{
    if (!win)
        return QString();

    // 1. Check objectName() for explicit roles
    QString name = win->objectName().toLower();
    if (!name.isEmpty() && m_roleAtoms.contains(name))
        return name;

    // 2. Fall back to Qt window flags
    Qt::WindowFlags flags = win->flags();

    const uint32_t rawFlags = static_cast<uint32_t>(flags.toInt());
    if (rawFlags & 0x04000000U)
        return "desktop";

    if (rawFlags & 0x00080000U)
        return "expose";

    if (rawFlags & 0x00040000U) {
        QScreen *screen = win->screen();
        if (!screen)
            return "dock";
        const QSize screenSize = screen->size();
        const QSize windowSize = win->size();
        if (windowSize.width() < screenSize.width() / 3
            || windowSize.height() < screenSize.height() / 3)
            return "dock";
        return "fadecurtain";
    }

    // 3. Default
    return QString();
}

void WindowTyper::stamp(QWindow *win)
{
    if (!win || !win->isTopLevel())
        return;

    ensureAtoms();
    if (!m_xcb || m_netWmWindowType == XCB_ATOM_NONE)
        return;

    QString role = roleOf(win);
    if (role.isEmpty())
        return;

    auto it = m_roleAtoms.constFind(role);
    if (it == m_roleAtoms.cend())
        return;

    xcb_atom_t roleAtom = *it;
    WId winId = win->winId();
    if (!winId)
        return;

    // W3: only write if the role changed
    xcb_atom_t cached = m_windowRoleCache.value(win, XCB_ATOM_NONE);
    if (cached == roleAtom)
        return;

    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, winId, m_netWmWindowType,
                        XCB_ATOM_ATOM, 32, 1, &roleAtom);
    xcb_flush(m_xcb);

    m_windowRoleCache[win] = roleAtom;
}

bool WindowTyper::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::WindowChangeInternal) { // 0xCE
        QWindow *win = qobject_cast<QWindow *>(watched);
        if (win && win->isTopLevel()) {
            stamp(win);
        }
    }
    return QObject::eventFilter(watched, event);
}