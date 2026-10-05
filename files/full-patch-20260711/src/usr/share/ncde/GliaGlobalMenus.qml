// GliaGlobalMenus.qml — NCDE's always-present top-panel menus, self-executing.
//
// OPERATOR SPEC (2026-07-07, verbatim intent): "glia is an in house global menu
// but does not use dbus — it reads the system like CDE used to." Do NOT rebuild
// this as a dbus appmenu bridge. The menus read the system directly (gliaSystem
// C++ helper for apps/places/recents) and act by running real commands or by
// relaying the standard keystroke to the focused window. Menu identities:
// File fronts Orchidée, Edit fronts Verve, Places open in Orchidée.
//
// The set that never leaves the top bar (independent of the focused app):
// the NCDE house menu, then the GNOME-2 trio Applications / Places / System.
//
// DROP-IN: feed `menus` into a dbus GliaMenuModel's `prependMenus`, and call
// `route(id)` from the model's `onActionInvoked`. That's the whole wiring —
// route() runs every action itself:
//   • launch:*  → systemCommand (auto-detected on windowMgr / launcher / runner)
//   • place:*   → xdg-open of the XDG user dir (bash-expanded)
//   • system:lock/house:lock → ncde-portal --lock; logout/shutdown → loginctl / systemctl
// The ONLY optional hooks are NCDE's own panels, which are not shell commands:
//   onSettings / onAbout / onRunCommand  → open your Settings / About / Run UI.
import QtQuick

QtObject {
    id: g

    // If systemCommand lives on neither windowMgr nor a `launcher` context
    // property, point this at the object that exposes systemCommand(string).
    property var runner: null

    // ── GliaTalk v1 (2026-07-07): the focused app's published menus ────────────
    // TopPanel feeds windowMgr.activeAppMenus (JSON) through setAppMenusJson();
    // items invoke back over X11 (windowMgr.invokeAppMenu → _NCDE_MENU_INVOKE).
    property var appMenus: []
    function setAppMenusJson(j) {
        if (!j || j === "") { if (appMenus.length) appMenus = []; return }
        var out = []
        try {
            var src = JSON.parse(j)
            for (var m = 0; m < src.length; m++) {
                var items = []
                var srcItems = src[m].items || []
                for (var i = 0; i < srcItems.length; i++) {
                    var it = srcItems[i]
                    if (it.separator) { items.push({ separator: true }); continue }
                    items.push({ label: it.label || "", shortcut: it.shortcut || "",
                                 actionId: "gliatalk:" + (it.id || 0) })
                }
                out.push({ title: src[m].title || "", items: items })
            }
        } catch (e) { out = [] }
        appMenus = out
    }

    // optional — NCDE's own panels (no shell command equivalent)
    signal settings()
    signal settingsSection(string label)   // open Settings at a specific tab (label from SettingsPanel.tabs)
    signal help()                          // open the NCDE Handbook
    signal about()
    signal runCommand()
    signal unhandled(string id)

    // ── run a shell command via whatever the shell exposes ────────────────
    function sh(cmd) {
        if (!cmd) return false
        if (runner && runner.systemCommand) { runner.systemCommand(cmd); return true }
        if (typeof windowMgr !== "undefined" && windowMgr && windowMgr.systemCommand) { windowMgr.systemCommand(cmd); return true }
        if (typeof launcher  !== "undefined" && launcher  && launcher.systemCommand)  { launcher.systemCommand(cmd);  return true }
        console.warn("GliaGlobalMenus: no systemCommand runner found for:", cmd)
        return false
    }

    // ── built-in default action per id (bash, so $HOME / chains expand) ───
    readonly property var _cmd: ({
        // Static-fallback launchers point at NCDE's REAL house apps (2026-07-07 —
        // were agent-guessed Debianisms/foreign apps, several nonexistent on this base).
        "launch:files":       "/usr/local/bin/orchidee",
        "launch:term":        "/usr/local/bin/ncde-terminal",
        "launch:text":        "/usr/local/bin/verve-text",
        "launch:calc":        "/usr/local/bin/abacus",
        "launch:imageviewer": "/usr/local/bin/orchidee \"$(xdg-user-dir PICTURES 2>/dev/null || echo $HOME/Pictures)\"",
        "launch:screenshot":  "mkdir -p \"$(xdg-user-dir PICTURES 2>/dev/null || echo $HOME/Pictures)\" && maim \"$(xdg-user-dir PICTURES 2>/dev/null || echo $HOME/Pictures)/Screenshot-$(date +%Y%m%d-%H%M%S).png\"",
        "launch:web":         "/usr/local/bin/ncde-chromium || firefox",
        "launch:mail":        "/usr/local/bin/hummingbird-courier",
        "launch:binnie":      "/usr/local/bin/binnie",
        "launch:notes":       "/usr/local/bin/verve-text",

        // Places open in Orchidée (operator 2026-07-07: "places orchidee") — she
        // takes the start dir as argv[1]. place:network routes to Settings→Network
        // in route() (no network-share browser ships yet — flagged).
        "place:home":      "/usr/local/bin/orchidee \"$HOME\"",
        "place:documents": "/usr/local/bin/orchidee \"$(xdg-user-dir DOCUMENTS 2>/dev/null || echo $HOME/Documents)\"",
        "place:downloads": "/usr/local/bin/orchidee \"$(xdg-user-dir DOWNLOAD  2>/dev/null || echo $HOME/Downloads)\"",
        "place:pictures":  "/usr/local/bin/orchidee \"$(xdg-user-dir PICTURES  2>/dev/null || echo $HOME/Pictures)\"",
        "place:music":     "/usr/local/bin/orchidee \"$(xdg-user-dir MUSIC     2>/dev/null || echo $HOME/Music)\"",
        "place:trash":     "/usr/local/bin/binnie",

        // system:appearance/display/keyboard/mouse/users/network/time route to the
        // shell Settings panel (settingsSection) in route() — no shell command.
        // system:help routes to the NCDE Handbook (help()). (2026-07-07: these were
        // literal no-ops/`xrandr --auto`/foreign nm-connection-editor — operator:
        // "no dead functions.. the functions should work so we can decide.")
        "system:lock":       "ncde-portal --lock",
        "system:logout":     "loginctl terminate-session \"$XDG_SESSION_ID\" || pkill -KILL -u \"$USER\"",
        "system:shutdown":   "systemctl poweroff || loginctl poweroff",

        "house:lock":        "ncde-portal --lock",
        "house:logout":      "loginctl terminate-session \"$XDG_SESSION_ID\" || pkill -KILL -u \"$USER\"",

        // File/Edit/View — no per-app menu bridge exists (in-house CDE-style menu, not a
        // dbus appmenu integration), so these relay the standard shortcut to whatever
        // window currently has focus via xdotool. Works uniformly for Orchidee, GTK apps,
        // or anything else honoring normal shortcuts — no per-app code needed.
        // File fronts Orchidée (operator 2026-07-07: "File is for Orchidee") —
        // New/Open open her; Save/Save As/Close relay to the focused window.
        "file:new":        "/usr/local/bin/orchidee \"$HOME\"",
        "file:open":       "/usr/local/bin/orchidee \"$HOME\"",
        "file:save":       "xdotool key ctrl+s",
        "file:saveas":     "xdotool key ctrl+shift+s",
        "file:close":      "xdotool key ctrl+w",
        // Edit fronts Verve (operator 2026-07-07) — the standard editing keys,
        // relayed to the focused window (Verve and every well-behaved app honor them).
        "edit:undo":       "xdotool key ctrl+z",
        "edit:redo":       "xdotool key ctrl+shift+z",
        "edit:cut":        "xdotool key ctrl+x",
        "edit:copy":       "xdotool key ctrl+c",
        "edit:paste":      "xdotool key ctrl+v",
        "edit:selectall":  "xdotool key ctrl+a",
        // View zoom: ctrl+equal is the Zoom-In chord Chromium/Firefox/Verve/GTK
        // document apps all honor unshifted — browser text and document text
        // genuinely grow (operator 2026-07-07). plus needs Shift on most layouts.
        "view:zoomin":     "xdotool key ctrl+equal",
        "view:zoomout":    "xdotool key ctrl+minus",
        "view:reset":      "xdotool key ctrl+0"
    })

    // ── single entry point — connect GliaMenuModel.onActionInvoked here ───
    function route(id) {
        if (!id) return
        // live entries from the C++ helper:
        if (id.indexOf("exec:") === 0) {                       // a real .desktop app
            if (typeof gliaSystem !== "undefined" && gliaSystem) { gliaSystem.launch(id.substring(5)); return }
        }
        if (id.indexOf("open:") === 0) {                       // a real place path
            if (typeof gliaSystem !== "undefined" && gliaSystem) { gliaSystem.openPath(id.substring(5)); return }
        }
        // GliaTalk: a published app item — send the request to the focused window.
        if (id.indexOf("gliatalk:") === 0) {
            if (typeof windowMgr !== "undefined" && windowMgr)
                windowMgr.invokeAppMenu(parseInt(id.substring(9)))
            return
        }
        // NCDE's own panels have no shell command — hand them to the shell.
        if (id === "house:settings") { settings(); return }
        if (id === "house:about")  { about();      return }
        if (id === "run")          { runCommand(); return }
        // System → Preferences/Administration open the shell Settings at the right
        // tab (labels = SettingsPanel.tabs). Previously no-ops — 2026-07-07.
        const sections = {
            "system:appearance": "Filigree",
            "system:display":    "Display",
            "system:keyboard":   "Input",
            "system:mouse":      "Input",
            "system:users":      "Users & Groups",
            "system:network":    "Network",
            "system:time":       "Date & Time"
        }
        if (sections[id])          { settingsSection(sections[id]); return }
        if (id === "place:network"){ settingsSection("Network");    return }
        if (id === "system:help")  { help();        return }
        // Full Screen — real WM-level toggle on the active window (same activeIndex→client
        // lookup main.qml's Alt+F4 handler uses), not a synthetic F11 that some apps ignore.
        if (id === "view:fullscreen") {
            if (typeof windowMgr !== "undefined" && windowMgr) {
                var idx = windowMgr.activeIndex
                if (idx >= 0) {
                    var entry = windowMgr.index(idx, 0)
                    var client = windowMgr.data(entry, 0x101)
                    windowMgr.setMaximized(client, !windowMgr.isMaximized(client))
                }
            }
            return
        }
        var cmd = _cmd[id]
        if (cmd) { sh(cmd); return }
        unhandled(id)
    }

    // ── recent files — live from gliaSystem when available ───────────────
    readonly property var _recentItems: {
        if (hasSystem && gliaSystem.recentFiles && gliaSystem.recentFiles.length > 0)
            return gliaSystem.recentFiles
        return [{ label: "No recent files", enabled: false, actionId: "" }]
    }

    // ── live system data (C++ helper), with graceful fallback ─────────────
    readonly property bool hasSystem: (typeof gliaSystem !== "undefined") && gliaSystem !== null

    // Applications menu items: real grouped apps when available, else the
    // static starter list below.
    readonly property var _appItems: {
        if (hasSystem && gliaSystem.applications && gliaSystem.applications.length > 0) {
            // gliaSystem.applications gives {name, icon, exec, id} — map to the
            // {label, actionId} shape GliaDropMenu/route() expect.
            var live = gliaSystem.applications.map(function(a) {
                return { label: a.name, actionId: "exec:" + a.id }
            })
            live.push({ separator: true })
            live.push({ label: "Run Command…", shortcut: "Alt+F2", actionId: "run" })
            return live
        }
        return _appItemsStatic
    }
    readonly property var _placeItems: {
        if (hasSystem && gliaSystem.places && gliaSystem.places.length > 0) {
            // gliaSystem.places gives {name, path} — map to {label, actionId}.
            return gliaSystem.places.map(function(p) {
                return { label: p.name, actionId: "open:" + p.path }
            })
        }
        return _placeItemsStatic
    }

    // ── the menus (same shape GliaMenuModel / GliaBar expect) ─────────────
    // Applications + Places are LIVE (from gliaSystem); NCDE + System static.
    // `menus` rebuilds whenever the helper rescans (changed → _appItems re-eval).
    readonly property var menus: [
        { title: "NCDE", items: [
            { label: "Meet Glia",    actionId: "house:about" },
            { label: "Settings…",    shortcut: "Ctrl+,", actionId: "house:settings" },
            { separator: true },
            { label: "Lock Screen",  shortcut: "Super+L", actionId: "house:lock" },
            { label: "Log Out…",     actionId: "house:logout" },
        ]},
        { title: "Applications", items: g._appItems },
        { title: "Places",       items: g._placeItems },
        { title: "System", items: [
            { label: "Preferences", submenu: [
                { label: "Appearance",       actionId: "system:appearance" },
                { label: "Display",          actionId: "system:display" },
                { label: "Keyboard",         actionId: "system:keyboard" },
                { label: "Mouse & Touchpad", actionId: "system:mouse" },
            ]},
            { label: "Administration", submenu: [
                { label: "Users & Groups", actionId: "system:users" },
                { label: "Network",        actionId: "system:network" },
                { label: "Time & Date",    actionId: "system:time" },
            ]},
            { separator: true },
            { label: "Help",        shortcut: "F1", actionId: "system:help" },
            { label: "Lock Screen", actionId: "system:lock" },
            { label: "Log Out…",    actionId: "system:logout" },
            { label: "Shut Down…",  actionId: "system:shutdown" },
        ]},
        { spacer: true },
    ].concat(
        // GliaTalk v1 (2026-07-07): when the FOCUSED app publishes its real menus
        // (_NCDE_MENUS via GliaTalkPublisher), they REPLACE the static File/Edit/
        // View relay trio — true global-menu parity, CDE but modern. Apps that
        // publish nothing (all foreign apps) keep the relay trio; nothing is lost.
        (g.appMenus && g.appMenus.length > 0) ? g.appMenus : [
        { title: "File", items: [
            { label: "New…",          shortcut: "Ctrl+N",       actionId: "file:new" },
            { label: "Open…",         shortcut: "Ctrl+O",       actionId: "file:open" },
            { label: "Open Recent",   submenu: g._recentItems },
            { separator: true },
            { label: "Save",          shortcut: "Ctrl+S",       actionId: "file:save" },
            { label: "Save As…",      shortcut: "Ctrl+Shift+S", actionId: "file:saveas" },
            { separator: true },
            { label: "Close Window",  shortcut: "Ctrl+W",       actionId: "file:close" },
        ]},
        { title: "Edit", items: [
            { label: "Undo",          shortcut: "Ctrl+Z",       actionId: "edit:undo" },
            { label: "Redo",          shortcut: "Ctrl+Shift+Z", actionId: "edit:redo" },
            { separator: true },
            { label: "Cut",           shortcut: "Ctrl+X",       actionId: "edit:cut" },
            { label: "Copy",          shortcut: "Ctrl+C",       actionId: "edit:copy" },
            { label: "Paste",         shortcut: "Ctrl+V",       actionId: "edit:paste" },
            { label: "Select All",    shortcut: "Ctrl+A",       actionId: "edit:selectall" },
        ]},
        { title: "View", items: [
            { label: "Zoom In",       shortcut: "Ctrl++",       actionId: "view:zoomin" },
            { label: "Zoom Out",      shortcut: "Ctrl+-",       actionId: "view:zoomout" },
            { label: "Reset Zoom",    shortcut: "Ctrl+0",       actionId: "view:reset" },
            { separator: true },
            { label: "Full Screen",   shortcut: "F11",          actionId: "view:fullscreen" },
        ]}
    ]).concat([
        { title: "NCDE Handbook", doc: "handbook" },
    ])

    // ── static fallbacks (used only if the gliaSystem helper is absent) ───
    readonly property var _appItemsStatic: [
        { label: "Accessories", submenu: [
            { label: "Orchidée",    actionId: "launch:files" },
            { label: "Terminal",    actionId: "launch:term" },
            { label: "Text Editor", actionId: "launch:text" },
            { label: "Calculator",  actionId: "launch:calc" },
        ]},
        { label: "Graphics", submenu: [
            { label: "Image Viewer", actionId: "launch:imageviewer" },
            { label: "Screenshot",   actionId: "launch:screenshot" },
        ]},
        { label: "Internet", submenu: [
            { label: "Web Browser", actionId: "launch:web" },
            { label: "Hummingbird (Mail)", actionId: "launch:mail" },
        ]},
        { label: "Office", submenu: [
            // (Leap Frog Ledger removed 2026-07-07 — it is the shell's own pond at
            // the foot of the screen, not a launchable binary; entry was dead.)
            { label: "Notes",     actionId: "launch:notes" },
        ]},
        { label: "System Tools", submenu: [
            { label: "Binnie (Trash)", actionId: "launch:binnie" },
            { label: "Orchidée",      actionId: "launch:files" },
        ]},
        { separator: true },
        { label: "Run Command…", shortcut: "Alt+F2", actionId: "run" },
    ]
    readonly property var _placeItemsStatic: [
        { label: "Home",      actionId: "place:home" },
        { label: "Documents", actionId: "place:documents" },
        { label: "Downloads", actionId: "place:downloads" },
        { label: "Pictures",  actionId: "place:pictures" },
        { label: "Music",     actionId: "place:music" },
        { separator: true },
        { label: "Network",   actionId: "place:network" },
        { label: "Binnie (Trash)", actionId: "place:trash" },
    ]
}
