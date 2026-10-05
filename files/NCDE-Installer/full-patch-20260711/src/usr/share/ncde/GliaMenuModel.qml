// GliaMenuModel.qml — normalizes a menu source into a uniform tree for GliaBar.
//
// Two sources, one shape:
//   • mode "dbus"   → the focused window's exported appmenu (NCDEMenuBridge),
//                     OPTIONALLY with `prependMenus` shown first — the always-
//                     present global set (NCDE house + Applications/Places/
//                     System). The TOP panel uses this.
//   • mode "static" → a hand-authored tree (`staticMenus`). The BOTTOM panel
//                     uses this for Leap Frog's Ledger / View / Pond / Help.
//
// Exposes:
//   appName  : string  — focused app name (bridge); rarely shown now
//   menus    : array   — [ { title, items:[ …itemDescriptor… ] }, … ]
//
// itemDescriptor:
//   { label, shortcut, separator, enabled, checkable, checked,
//     submenu:[…], actionId }
//
// ACTION ID CONTRACT (dbus mode): the bridge hands out INTEGER ids for the
// focused app's actions; prepended global menus use STRING ids. invoke()
// routes by type — ints → bridge.trigger(); strings → actionInvoked() so the
// shell can run them (launch app, open place, system action, house menu).
import QtQuick

QtObject {
    id: model

    property string mode: "static"          // "dbus" | "static"

    // ── DBus source (top panel) ───────────────────────────────────────────
    // Assign the NCDEMenuBridge context object/instance here.
    property var bridge: null
    // Always-present global menus shown BEFORE the app menus (dbus mode).
    // Same shape as `menus`; leaf items carry STRING actionIds. Feed this
    // GliaGlobalMenus.menus.
    property var prependMenus: []

    // ── Static source (bottom panel) ──────────────────────────────────────
    property string staticAppName: ""
    property var    staticMenus: []          // same shape as `menus`

    // ── Output ────────────────────────────────────────────────────────────
    readonly property string appName: mode === "dbus"
        ? (bridge ? bridge.appName : "")
        : staticAppName

    readonly property var menus: mode === "dbus"
        ? prependMenus.concat(bridge ? bridge.menuModel : [])
        : staticMenus

    readonly property bool empty: !menus || menus.length === 0

    signal actionInvoked(string actionId)    // string-id consumers connect here

    // Called by GliaBar when a leaf row is chosen.
    function invoke(actionId) {
        if (actionId === undefined || actionId === null) return
        if (mode === "dbus") {
            // app actions are integer ids from the bridge; global (prepended)
            // actions are strings → bubble up for the shell to run.
            if (typeof actionId === "number") {
                if (bridge) bridge.trigger(actionId)
            } else {
                actionInvoked(String(actionId))
            }
        } else {
            actionInvoked(String(actionId))
        }
    }

    // Called by GliaBar just before showing a top-level menu, so the bridge
    // can lazily populate that branch (dbusmenu is lazy). Only the APP menus
    // are lazy; the prepended globals are static, so offset the index.
    function aboutToShow(menuIndex) {
        if (mode !== "dbus" || !bridge || !bridge.aboutToShow) return
        var n = prependMenus.length
        if (menuIndex >= n) bridge.aboutToShow(menuIndex - n)
    }
}
