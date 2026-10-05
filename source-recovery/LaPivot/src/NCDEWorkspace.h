// NCDEWorkspace — manages X11 virtual desktops (_NET_CURRENT_DESKTOP, _NET_NUMBER_OF_DESKTOPS,
// _NET_DESKTOP_NAMES). Exposes the desktop names and current index to QML (ncdeWorkspace).
// Reads from X11 on a 1 s timer and emits changed() when anything differs.
//
// Rebuilt from oracle: decomp/NCDEWorkspace.c (14 functions: ctor, names, current, activate,
// intern, readCard, refresh, dtor). Spec: docs/wm-oracle-audit.md, NCDE-ARCHITECTURE-DIGEST.md §2.
// The oracle interface (interfaces/LaPivot-metaobjects.h) has:
//   - properties: names (QStringList), current (int)
//   - signal: changed()
//   - invokable: activate(int)
//
// DEFECTS FIXED vs oracle:
//  WK1 refresh() still runs at the oracle's 1 s cadence and uses synchronous X property replies.
//     It now emits only on changed values. This remaining GUI-thread round-trip is not yet fixed.
//  WK2 the oracle's names() reports numbered names when _NET_DESKTOP_NAMES is absent; the same
//     fallback is rebuilt in refresh(), while the cached model emits only when values differ.
//  WK3 activate(int) now checks the X connection, atom and root before sending the EWMH message.
#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <xcb/xcb.h>

class NCDEWorkspace : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList names READ names NOTIFY changed)
    Q_PROPERTY(int current READ current NOTIFY changed)

public:
    explicit NCDEWorkspace(QObject *parent = nullptr);
    ~NCDEWorkspace() override;

    QStringList names() const;
    int current() const;

    Q_INVOKABLE void activate(int i);

signals:
    void changed();

private:
    void refresh();
    xcb_atom_t intern(const char *name);
    uint32_t readCard(xcb_atom_t atom) const;

    xcb_connection_t *m_xcb = nullptr;
    xcb_window_t m_root = XCB_WINDOW_NONE;
    xcb_atom_t m_netCurrentDesktop = XCB_ATOM_NONE;
    xcb_atom_t m_netNumberOfDesktops = XCB_ATOM_NONE;
    xcb_atom_t m_netDesktopNames = XCB_ATOM_NONE;
    int m_current = 0;
    QStringList m_names;
    QTimer *m_timer = nullptr;
};