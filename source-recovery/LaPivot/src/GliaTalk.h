// GliaTalkProto — the WM side of GliaTalk, NCDE's no-D-Bus global-menu protocol (CDE ToolTalk, modern).
//
// Rebuilt from oracle: LaPivot.oracle decomp/GliaTalkProto.c (3 functions: internAtom, readMenus, sendInvoke).
// Spec: docs/gliatalk.md, NCDE-ARCHITECTURE-DIGEST.md §1/§3.1 — an app publishes its real menus as UTF-8 JSON on
// the `_NCDE_MENUS` property of its own top-level window; the WM reads it at manage time and on PropertyNotify;
// invoking an item is a `_NCDE_MENU_INVOKE` ClientMessage (format 32, data32[0] = item id) sent to that window.
// "No dbus, ever." Empty string = the window publishes nothing (the shell keeps its relay trio).
//
// DEFECTS FIXED vs oracle:
//  G1 readMenus/sendInvoke interned their atom with a blocking round trip on EVERY call (each PropertyNotify of
//     every window and every menu click). The atoms never change for the life of the X connection: interned
//     once per connection and cached (internAtom keeps the oracle's uncached behaviour for other callers).
// Hardening (not observed failures): a chunk that makes no progress while bytes_after > 0 ends the read instead
// of re-requesting the same offset forever; a value that is not format 8 (gliatalk.md: "UTF-8 JSON") is ignored
// instead of being decoded as UTF-8 and handed to the menu bar's JSON.parse.
#pragma once

#include <QString>
#include <xcb/xcb.h>

namespace GliaTalkProto {
// one blocking intern (as the oracle); 0 on failure
xcb_atom_t internAtom(xcb_connection_t *c, const char *name);
// the window's `_NCDE_MENUS` JSON, "" when it publishes nothing
QString readMenus(xcb_connection_t *c, xcb_window_t w);
// send `_NCDE_MENU_INVOKE` with the item id to the window
void sendInvoke(xcb_connection_t *c, xcb_window_t w, quint32 id);
}
