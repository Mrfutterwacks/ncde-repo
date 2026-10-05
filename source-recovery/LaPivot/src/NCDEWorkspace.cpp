// NCDEWorkspace — see NCDEWorkspace.h for the spec and the defect list.
// Rebuilt from oracle: decomp/NCDEWorkspace.c (ctor 0x17dc0c, names 0x17dea4, current 0x17e088,
// activate 0x17e09a, intern 0x17e172, readCard 0x17e21c, refresh 0x17e308).
#include "NCDEWorkspace.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include <QTimer>
#include <QtLogging>

#include <xcb/xcb.h>

NCDEWorkspace::NCDEWorkspace(QObject *parent) : QObject(parent)
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

    // Get the root window of the default screen
    const xcb_setup_t *setup = xcb_get_setup(m_xcb);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    if (iter.data) {
        m_root = iter.data->root;
    }

    if (m_root == XCB_WINDOW_NONE)
        return;

    // Intern EWMH atoms
    m_netCurrentDesktop = intern("_NET_CURRENT_DESKTOP");
    m_netNumberOfDesktops = intern("_NET_NUMBER_OF_DESKTOPS");
    m_netDesktopNames = intern("_NET_DESKTOP_NAMES");

    // Initial read
    refresh();

    // Timer for periodic refresh (oracle: 1000 ms)
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &NCDEWorkspace::refresh);
    m_timer->start(1000);
}

NCDEWorkspace::~NCDEWorkspace() = default;

QStringList NCDEWorkspace::names() const
{
    return m_names;
}

int NCDEWorkspace::current() const
{
    return m_current;
}

void NCDEWorkspace::activate(int index)
{
    if (!m_xcb || m_netCurrentDesktop == XCB_ATOM_NONE || m_root == XCB_WINDOW_NONE)
        return;

    xcb_client_message_event_t ev{};
    ev.response_type = XCB_CLIENT_MESSAGE;
    ev.format = 32;
    ev.window = m_root;
    ev.type = m_netCurrentDesktop;
    ev.data.data32[0] = static_cast<uint32_t>(index);
    ev.data.data32[1] = XCB_CURRENT_TIME;

    xcb_send_event(m_xcb, 0, m_root, XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT, reinterpret_cast<const char *>(&ev));
    xcb_flush(m_xcb);

    // Optimistically update local state; refresh() will confirm
    if (index != m_current) {
        m_current = index;
        emit changed();
    }
}

void NCDEWorkspace::refresh()
{
    if (!m_xcb || m_root == XCB_WINDOW_NONE)
        return;

    uint32_t current = readCard(m_netCurrentDesktop);
    uint32_t count = readCard(m_netNumberOfDesktops);
    if (count < 1)
        count = 4; // oracle default

    QStringList newNames;
    newNames.reserve(count);

    // Read _NET_DESKTOP_NAMES (UTF-8 string list)
    if (m_netDesktopNames != XCB_ATOM_NONE) {
        xcb_get_property_cookie_t ck = xcb_get_property(m_xcb, 0, m_root, m_netDesktopNames,
                                                        XCB_GET_PROPERTY_TYPE_ANY, 0, 0x10000);
        xcb_get_property_reply_t *r = xcb_get_property_reply(m_xcb, ck, nullptr);
        if (r && r->type != XCB_ATOM_NONE && r->format == 8) {
            const char *data = static_cast<const char *>(xcb_get_property_value(r));
            int len = xcb_get_property_value_length(r);
            if (len > 0) {
                QString utf8 = QString::fromUtf8(data, len);
                // Split by null terminator
                newNames = utf8.split('\0', Qt::SkipEmptyParts);
            }
        }
        free(r);
    }

    // Fallback to numbered names if empty
    if (newNames.isEmpty()) {
        for (uint32_t i = 0; i < count; ++i) {
            newNames << QString::number(i + 1);
        }
    }

    // Check if anything changed. The local flag cannot be called "changed": that name is the
    // signal (void changed()), so inside a member function the bare name resolves to the signal and
    // hides the local. Use m_changedWas / anyChanged instead.
    bool anyChanged = false;
    if (current != static_cast<uint32_t>(m_current)) {
        m_current = static_cast<int>(current);
        anyChanged = true;
    }
    if (newNames != m_names) {
        m_names = std::move(newNames);
        anyChanged = true;
    }

    if (anyChanged)
        emit changed();
}

xcb_atom_t NCDEWorkspace::intern(const char *name)
{
    if (!m_xcb)
        return XCB_ATOM_NONE;

    xcb_intern_atom_cookie_t ck = xcb_intern_atom(m_xcb, 0, strlen(name), name);
    xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(m_xcb, ck, nullptr);
    xcb_atom_t atom = r ? r->atom : static_cast<xcb_atom_t>(XCB_ATOM_NONE);
    free(r);
    return atom;
}

uint32_t NCDEWorkspace::readCard(xcb_atom_t atom) const
{
    if (!m_xcb || m_root == XCB_WINDOW_NONE || atom == XCB_ATOM_NONE)
        return 0;

    xcb_get_property_cookie_t ck = xcb_get_property(m_xcb, 0, m_root, atom, XCB_ATOM_CARDINAL, 0, 1);
    xcb_get_property_reply_t *r = xcb_get_property_reply(m_xcb, ck, nullptr);
    if (!r)
        return 0;

    int len = xcb_get_property_value_length(r);
    uint32_t val = 0;
    if (len >= 4) {
        const uint32_t *data = static_cast<const uint32_t *>(xcb_get_property_value(r));
        val = *data;
    }
    free(r);
    return val;
}