// XSettingsManager — manages the XSETTINGS selection for GTK/Qt theme propagation (cursor theme,
// cursor size). Implements the XSETTINGS specification (freedesktop.org). Not a QObject; plain
// C++ class used by main.cpp.
//
// Rebuilt from oracle: decomp/XSettingsManager.c (11 functions: ctor, dtor, start, started,
// setCursorSize, atom, put32, put16, pad4, appendString, appendInt, publish). Spec: XSETTINGS
// spec, docs/wm-oracle-audit.md. The oracle class is a non-QObject with these public methods:
//   XSettingsManager()
//   ~XSettingsManager()
//   bool start(const QString &cursorTheme, int cursorSize) — claims the XSETTINGS manager selection
//   bool started() const — true if we own the selection
//   void setCursorSize(int size) — updates Gtk/CursorThemeSize and republishes
//
// The oracle stores: xcb_connection_t*, xcb_window_t managerWindow, xcb_atom_t xsettingsAtom,
// xcb_atom_t settingsAtom, xcb_atom_t managerAtom, int serial, QHash<QString, uint> settingAtoms,
// QString cursorTheme, int cursorSize.
//
// DEFECTS FIXED vs oracle:
//  XM1 the oracle waited indefinitely for CreateNotify. That event has no timestamp member, and
//     the prior attempted `cn->time` fix did not compile. Use CurrentTime, verify selection
//     ownership, then send the ICCCM MANAGER announcement without polling any event queue.
//  XM2 repeated start() calls now retain an already-running manager rather than opening another
//     connection and replacing its owned selection.
//  XM3 the manager window is created as a valid InputOnly window (COPY_FROM_PARENT visual).
//  XM4 setCursorSize() is a no-op unless the selection is owned and the size actually changes.
//  XM5 The setting records are rebuilt on each actual publish; per-setting protocol atoms are
//     not required because XSETTINGS uses a last-change serial, so no fictitious atom cache.
#pragma once

#include <QChar>
#include <QByteArray>
#include <QHash>
#include <QString>
#include <xcb/xcb.h>

class XSettingsManager
{
public:
    XSettingsManager() = default;
    ~XSettingsManager();

    // Starts the XSETTINGS manager. Returns true if this process owns the selection.
    bool start(const QString &cursorTheme, int cursorSize);

    // True if we successfully claimed the manager selection.
    bool started() const;

    // Updates the cursor size setting and republishes (only if we own the selection).
    void setCursorSize(int size);

private:
    xcb_atom_t internAtom(const QString &name);
    void put32(QByteArray &buf, uint32_t val);
    void put16(QByteArray &buf, uint16_t val);
    void pad4(QByteArray &buf);
    void appendString(QByteArray &buf, const QString &name, const QString &value);
    void appendInt(QByteArray &buf, const QString &name, int value);
    void publish();

    xcb_connection_t *m_xcb = nullptr;
    xcb_window_t m_managerWindow = XCB_WINDOW_NONE;
    xcb_atom_t m_xsettingsAtom = XCB_ATOM_NONE;
    xcb_atom_t m_settingsAtom = XCB_ATOM_NONE;
    xcb_atom_t m_managerAtom = XCB_ATOM_NONE;
    uint32_t m_serial = 0;
    QHash<QString, uint32_t> m_settingAtoms;
    QString m_cursorTheme;
    int m_cursorSize = 24;
};