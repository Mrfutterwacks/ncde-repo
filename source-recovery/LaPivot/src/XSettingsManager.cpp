// XSettingsManager — see XSettingsManager.h for the spec and the defect list.
// Rebuilt from oracle: decomp/XSettingsManager.c (start 0x1fe226, started 0x1fead8,
// setCursorSize 0x1feb06, atom 0x1fec4c, put32 0x1fed53, put16 0x1fedc1, pad4 0x1fee21,
// appendString 0x1fee5e, appendInt 0x1fefea, publish 0x1ff11c).
#include "XSettingsManager.h"

#include <cstdlib>
#include <cstdint>
#include <xcb/xcb.h>

XSettingsManager::~XSettingsManager()
{
    if (m_xcb) {
        xcb_disconnect(m_xcb);
        m_xcb = nullptr;
    }
}

bool XSettingsManager::start(const QString &cursorTheme, int cursorSize)
{
    if (started())
        return true;

    m_cursorTheme = cursorTheme;
    m_cursorSize = cursorSize;

    int screenNum = 0;
    m_xcb = xcb_connect(nullptr, &screenNum);
    if (!m_xcb)
        return false;
    if (xcb_connection_has_error(m_xcb)) {
        xcb_disconnect(m_xcb);
        m_xcb = nullptr;
        return false;
    }

    const auto fail = [this]() {
        if (m_xcb)
            xcb_disconnect(m_xcb);
        m_xcb = nullptr;
        m_managerWindow = XCB_WINDOW_NONE;
        return false;
    };

    const xcb_setup_t *setup = xcb_get_setup(m_xcb);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    for (int i = 0; i < screenNum && iter.data; ++i) {
        xcb_screen_next(&iter);
    }
    if (!iter.data)
        return fail();

    xcb_screen_t *screen = iter.data;
    m_managerWindow = xcb_generate_id(m_xcb);

    // Intern required atoms
    m_xsettingsAtom = internAtom("_XSETTINGS_S" + QString::number(screenNum));
    m_settingsAtom = internAtom("_XSETTINGS_SETTINGS");
    m_managerAtom = internAtom("MANAGER");

    if (m_xsettingsAtom == XCB_ATOM_NONE || m_settingsAtom == XCB_ATOM_NONE || m_managerAtom == XCB_ATOM_NONE) {
        return fail();
    }

    // Create the manager window (1x1, InputOnly)
    uint32_t mask = XCB_CW_EVENT_MASK;
    uint32_t values[] = { XCB_EVENT_MASK_PROPERTY_CHANGE };
    xcb_create_window(m_xcb, XCB_COPY_FROM_PARENT, m_managerWindow, screen->root,
                      static_cast<int16_t>(-1), static_cast<int16_t>(-1), 1, 1, 0,
                      XCB_WINDOW_CLASS_INPUT_ONLY, XCB_COPY_FROM_PARENT,
                      mask, values);
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_managerWindow, m_settingsAtom,
                        m_settingsAtom, 8, 0, nullptr);
    xcb_flush(m_xcb);

    // CreateNotify has no timestamp field. CurrentTime is valid for selection
    // ownership and avoids waiting for an unrelated event on the GUI thread.
    xcb_set_selection_owner(m_xcb, m_managerWindow, m_xsettingsAtom, XCB_CURRENT_TIME);
    xcb_flush(m_xcb);

    // Verify ownership
    xcb_get_selection_owner_cookie_t ck = xcb_get_selection_owner(m_xcb, m_xsettingsAtom);
    xcb_get_selection_owner_reply_t *r = xcb_get_selection_owner_reply(m_xcb, ck, nullptr);
    bool owns = r && r->owner == m_managerWindow;
    free(r);

    if (!owns)
        return fail();

    xcb_client_message_event_t managerEvent{};
    managerEvent.response_type = XCB_CLIENT_MESSAGE;
    managerEvent.format = 32;
    managerEvent.window = screen->root;
    managerEvent.type = m_managerAtom;
    managerEvent.data.data32[0] = XCB_CURRENT_TIME;
    managerEvent.data.data32[1] = m_xsettingsAtom;
    managerEvent.data.data32[2] = m_managerWindow;
    xcb_send_event(m_xcb, 0, screen->root, XCB_EVENT_MASK_STRUCTURE_NOTIFY,
                   reinterpret_cast<const char *>(&managerEvent));
    xcb_flush(m_xcb);

    // Initialize setting atoms cache
    m_settingAtoms["Gtk/CursorThemeName"] = 0;
    m_settingAtoms["Gtk/CursorThemeSize"] = 0;

    // Initial publish
    m_serial = 0;
    publish();

    return true;
}

bool XSettingsManager::started() const
{
    return m_xcb != nullptr && m_managerWindow != XCB_WINDOW_NONE;
}

void XSettingsManager::setCursorSize(int size)
{
    if (!started() || size == m_cursorSize)
        return;

    m_cursorSize = size;
    ++m_serial;
    m_settingAtoms[QStringLiteral("Gtk/CursorThemeSize")] = m_serial;   // last-change serial (oracle)
    publish();
}

xcb_atom_t XSettingsManager::internAtom(const QString &name)
{
    if (!m_xcb)
        return XCB_ATOM_NONE;

    QByteArray latin1 = name.toLatin1();
    xcb_intern_atom_cookie_t ck = xcb_intern_atom(m_xcb, 0, latin1.size(), latin1.constData());
    xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(m_xcb, ck, nullptr);
    xcb_atom_t atom = r ? r->atom : static_cast<xcb_atom_t>(XCB_ATOM_NONE);
    free(r);
    return atom;
}

void XSettingsManager::put32(QByteArray &buf, uint32_t val)
{
    buf.append(static_cast<char>(val & 0xFF));
    buf.append(static_cast<char>((val >> 8) & 0xFF));
    buf.append(static_cast<char>((val >> 16) & 0xFF));
    buf.append(static_cast<char>((val >> 24) & 0xFF));
}

void XSettingsManager::put16(QByteArray &buf, uint16_t val)
{
    buf.append(static_cast<char>(val & 0xFF));
    buf.append(static_cast<char>((val >> 8) & 0xFF));
}

void XSettingsManager::pad4(QByteArray &buf)
{
    while (buf.size() % 4 != 0) {
        buf.append('\0');
    }
}

void XSettingsManager::appendString(QByteArray &buf, const QString &name, const QString &value)
{
    QByteArray nameBytes = name.toLatin1();
    QByteArray valueBytes = value.toUtf8();

    buf.append(static_cast<char>(1)); // type: string (XSETTINGS: 0 int, 1 string, 2 colour; oracle)
    buf.append(static_cast<char>(0)); // padding

    put16(buf, static_cast<uint16_t>(nameBytes.size()));
    buf.append(nameBytes);
    pad4(buf);

    auto it = m_settingAtoms.find(name);
    uint32_t atom = (it != m_settingAtoms.end()) ? *it : 0;
    put32(buf, atom);

    put32(buf, static_cast<uint32_t>(valueBytes.size()));
    buf.append(valueBytes);
    pad4(buf);
}

void XSettingsManager::appendInt(QByteArray &buf, const QString &name, int value)
{
    QByteArray nameBytes = name.toLatin1();

    buf.append(static_cast<char>(0)); // type: int (X1: the first rebuild had 0/1 swapped)
    buf.append(static_cast<char>(0)); // padding

    put16(buf, static_cast<uint16_t>(nameBytes.size()));
    buf.append(nameBytes);
    pad4(buf);

    auto it = m_settingAtoms.find(name);
    uint32_t atom = (it != m_settingAtoms.end()) ? *it : 0;
    put32(buf, atom);

    put32(buf, static_cast<uint32_t>(value));
}

void XSettingsManager::publish()
{
    if (!started())
        return;

    QByteArray data;
    data.reserve(256);

    // XSETTINGS header (oracle): byte-order CARD8 (0 = LSBFirst), 3 pad, serial, n_settings.
    // X1 2026-10-01: the first rebuild left out the byte-order + pad bytes, so every GTK client
    // misparsed the property ("Invalid XSETTINGS property ... Expected 12140 bytes, only 60 left").
    data.append('\0');
    data.append(3, '\0');
    put32(data, m_serial);
    put32(data, 2); // two settings: Gtk/CursorThemeName, Gtk/CursorThemeSize

    appendString(data, "Gtk/CursorThemeName", m_cursorTheme);
    appendInt(data, "Gtk/CursorThemeSize", m_cursorSize);

    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_managerWindow, m_settingsAtom,
                        m_settingsAtom, 8, data.size(),
                        reinterpret_cast<const uint8_t *>(data.constData()));
    xcb_flush(m_xcb);
}