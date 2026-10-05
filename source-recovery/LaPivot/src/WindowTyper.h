// WindowTyper — classifies QWindow roles for the WM's frame/styling decisions.
// Installs an event filter on QGuiApplication and stamps each top-level window with its
// role (desktop, toppanel, bottompanel, dock, expose, fadecurtain, notification, tooltip,
// menu, toolbar, dialog) as the _NET_WM_WINDOW_TYPE X property on the X11 client window.
//
// Rebuilt from oracle: decomp/WindowTyper.c (13 functions: ctor, eventFilter, internAtoms,
// intern, roleOf, stamp, dtor). Spec: docs/wm-oracle-audit.md, docs/NCDE-WM-REBUILD-PLAN.md.
// The oracle's WindowTyper is a bare QObject with no properties/signals/slots; it only
// reacts to QEvent::WindowChangeInternal (0xCE) for top-level windows.
//
// DEFECTS FIXED vs oracle:
//  W1 atom setup is deferred until the first top-level-window event; the application event
//     filter is installed in the constructor and null X11 connections are handled.
//  W2 roleOf() preserves the oracle's object-name and X11 window-flag fallback classification;
//     only the stays-on-top role uses the screen-size heuristic.
//  W3 stamp() wrote the role property on every eventFilter hit without checking if it
//     changed. Now it writes only when the role atom value differs from the cached one.
//  W4 the oracle used QObject::installEventFilter on the application object. The same event
//     filter is retained; X atoms are initialized lazily after the Qt X11 interface is ready.
#pragma once

#include <QEvent>
#include <QHash>
#include <QObject>
#include <QWindow>
#include <xcb/xcb.h>

class WindowTyper : public QObject
{
    Q_OBJECT

public:
    explicit WindowTyper(QObject *parent = nullptr);
    ~WindowTyper() override;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void ensureAtoms();
    void internAtoms();
    xcb_atom_t intern(const char *name);
    QString roleOf(QWindow *win) const;
    void stamp(QWindow *win);

    xcb_connection_t *m_xcb = nullptr;
    xcb_atom_t m_netWmWindowType = XCB_ATOM_NONE;
    QHash<QString, xcb_atom_t> m_roleAtoms;
    QHash<QWindow *, xcb_atom_t> m_windowRoleCache;
};