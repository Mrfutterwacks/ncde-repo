// GliaTalkProto — see GliaTalk.h for the spec and the defect list.
// Rebuilt from oracle: decomp/GliaTalkProto.c (internAtom 0x176f9e, readMenus 0x17703d, sendInvoke 0x1771e7).
#include "GliaTalk.h"

#include <QByteArray>
#include <QHash>
#include <cstdlib>
#include <cstring>

namespace {
struct Atoms { xcb_atom_t menus = 0, invoke = 0; };
// G1: per-connection cache (LaPivot has one connection; tests may open several)
Atoms &atomsFor(xcb_connection_t *c)
{
    static QHash<xcb_connection_t *, Atoms> cache;
    Atoms &a = cache[c];
    if (!a.menus || !a.invoke) {
        // pipelined: both requests out before the first reply is awaited
        const xcb_intern_atom_cookie_t m = xcb_intern_atom(c, 0, 11, "_NCDE_MENUS");
        const xcb_intern_atom_cookie_t i = xcb_intern_atom(c, 0, 17, "_NCDE_MENU_INVOKE");
        if (xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(c, m, nullptr)) { a.menus = r->atom; free(r); }
        if (xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(c, i, nullptr)) { a.invoke = r->atom; free(r); }
    }
    return a;
}
}

xcb_atom_t GliaTalkProto::internAtom(xcb_connection_t *c, const char *name)
{
    const xcb_intern_atom_cookie_t ck = xcb_intern_atom(c, 0, uint16_t(strlen(name)), name);
    xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(c, ck, nullptr);
    const xcb_atom_t a = r ? r->atom : static_cast<xcb_atom_t>(XCB_ATOM_NONE);
    free(r);
    return a;
}

QString GliaTalkProto::readMenus(xcb_connection_t *c, xcb_window_t w)
{
    if (!c || !w)
        return QString();
    const xcb_atom_t atom = atomsFor(c).menus;
    if (!atom)
        return QString();
    QByteArray buf;
    quint32 offsetBytes = 0;
    for (;;) {
        // oracle: long_offset = bytes/4, long_length 0x10000 (256 KiB per chunk), any type
        const xcb_get_property_cookie_t ck =
            xcb_get_property(c, 0, w, atom, XCB_GET_PROPERTY_TYPE_ANY, offsetBytes >> 2, 0x10000);
        xcb_get_property_reply_t *r = xcb_get_property_reply(c, ck, nullptr);
        if (!r)
            return QString();
        if (r->type == XCB_ATOM_NONE) {                // property absent: publishes nothing
            free(r);
            return QString();
        }
        if (r->format != 8) {                          // format-8 only
            free(r);
            return QString();
        }
        const int len = xcb_get_property_value_length(r);
        if (len > 0)
            buf.append(static_cast<const char *>(xcb_get_property_value(r)), len);
        const quint32 after = r->bytes_after;
        free(r);
        if (after == 0)
            return QString::fromUtf8(buf);
        if (len <= 0)                                  // no progress
            return QString();
        offsetBytes += quint32(len);
    }
}

void GliaTalkProto::sendInvoke(xcb_connection_t *c, xcb_window_t w, quint32 id)
{
    if (!c || !w)
        return;
    const xcb_atom_t atom = atomsFor(c).invoke;
    if (!atom)
        return;
    xcb_client_message_event_t ev;
    memset(&ev, 0, sizeof ev);
    ev.response_type = XCB_CLIENT_MESSAGE;
    ev.format = 32;
    ev.window = w;
    ev.type = atom;
    ev.data.data32[0] = id;
    xcb_send_event(c, 0, w, XCB_EVENT_MASK_NO_EVENT, reinterpret_cast<const char *>(&ev));
    xcb_flush(c);
}
