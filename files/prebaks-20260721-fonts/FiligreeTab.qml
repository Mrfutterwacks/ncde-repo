// qmllint disable unqualified
// ╔══════════════════════════════════════════════════════════════════════╗
// ║  FiligreeTab.qml — NCDE Filigree (visual design authority) tab body.    ║
// ║                                                                        ║
// ║  Self-contained Item. Drop into SettingsPanel.qml as the Filigree tab, ║
// ║  or load standalone (Phase 2). Uses the existing reusable components:   ║
// ║     SettingsColorWheel · NCDESlider · settings_colors.js         ║
// ║                                                                        ║
// ║  Context objects: ncde · settings · theme · notifications.             ║
// ║                                                                        ║
// ║  Every engine/settings hook used here is live C++ (verified against    ║
// ║  the running engine, 2026-07-20; old typeof guards kept as harmless    ║
// ║  belt-and-braces). INSTANT-APPLY (operator, 2026-07-20): every         ║
// ║  control applies AND persists the moment it changes — no Apply         ║
// ║  buttons; sliders preview live while dragging, persist on release.     ║
// ║                                                                        ║
// ║  Lélan: TapHandler only (no MouseArea); no Timers; persistence via     ║
// ║  config-writing methods that fire QFileSystemWatcher → themeChanged.   ║
// ╚══════════════════════════════════════════════════════════════════════╝

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Effects
import "settings_colors.js" as Colors

Item {
    id: fil
    clip: true

    // Shared snap points for the two global scale sliders below — percentages,
    // not raw multipliers, matching the OS accessibility text-size convention.
    readonly property var scalePresets: [75, 90, 100, 110, 125, 150, 175, 200]
    function _nearestPreset(pct) {
        var arr = fil.scalePresets, best = arr[0], bestD = Math.abs(pct - best)
        for (var i = 1; i < arr.length; i++) {
            var d = Math.abs(pct - arr[i])
            if (d < bestD) { bestD = d; best = arr[i] }
        }
        return best
    }

    // ── palette / fonts (local so the tab is self-contained) ─────────────
    QtObject {
        id: fp
        readonly property color paper0:ncde.surface; readonly property color paper1:ncde.surface
        readonly property color paper2:ncde.surfaceAlt; readonly property color paper3:ncde.surfaceAlt
        readonly property color gilt0:ncde.gilt0; readonly property color gilt1:ncde.gilt1
        readonly property color gilt2:ncde.gilt2; readonly property color gilt3:ncde.gilt3
        readonly property color gilt4:ncde.gilt4; readonly property color gilt5:ncde.gilt5
        readonly property color wine1:ncde.wine1; readonly property color wine2:ncde.wine2
        readonly property color wine3:ncde.wine3; readonly property color wine4:ncde.wine4
        readonly property color ink:ncde.foreground
        // soft captions for real (was === ink): SetTheme.inkSoft pattern, 0.65 alpha
        readonly property color inkSoft:Qt.rgba(ncde.foreground.r, ncde.foreground.g, ncde.foreground.b, 0.65)
        readonly property string display:"Cinzel Decorative"; readonly property string titles:"Cinzel"
        readonly property string serif:"Cormorant Garamond"; readonly property string fell:"IM Fell English"
        readonly property string gar:"EB Garamond"; readonly property string mono:"TerminalVector"
    }

    // ── studio state ─────────────────────────────────────────────────────
    property real   fHue: 36
    property real   fSat: 0.75
    property real   fCalm: 0.0
    // fPalette/fHue/fSat/fCalm/recompute() are kept (Color Studio's UI is gone) — Sections tab
    // still uses fPalette[4] as a live-theme-derived fallback color; Component.onCompleted below
    // seeds it from the current engine accent so it's never just the hardcoded 36/0.75/0 default.
    property var    fPalette: Colors.derivedPalette(36, 0.75, 0.0)
    property bool   _colorPopupOpen: false
    property string _colorPopupTitle: ""
    property var    _colorCallback: null
    property var    _colorResetCallback: null   // non-null → popup shows a Reset button (Sections rows)
    property string _activeTab: "iris"   // Color Studio removed (redundant since Iris Chroma) — Iris is the new default
    function recompute() {
        fPalette = Colors.derivedPalette(fHue, fSat, fCalm)
    }
    // Same QColor->hex pattern already used in openColorPopup() below, factored out
    // so the new live contrast readout can reuse it instead of duplicating it again.
    function _panelBgHex() {
        function h2(v) { return Math.round(v * 255).toString(16).padStart(2,"0") }
        var c = ncde.panelBg
        return "#" + h2(c.r) + h2(c.g) + h2(c.b)
    }
    function openColorPopup(title, currentHex, callback, resetCallback) {
        _colorPopupTitle = title
        _colorCallback = callback
        _colorResetCallback = resetCallback || null
        function chHex(v) { return Math.round(v * 255).toString(16).padStart(2,"0") }
        var hex = (currentHex && currentHex.length === 7) ? currentHex : ("#" + chHex(ncde.gilt3.r) + chHex(ncde.gilt3.g) + chHex(ncde.gilt3.b))
        var r2 = parseInt(hex.slice(1,3),16)/255, g2 = parseInt(hex.slice(3,5),16)/255, b2 = parseInt(hex.slice(5,7),16)/255
        var mx = Math.max(r2,g2,b2), mn = Math.min(r2,g2,b2), d = mx-mn
        var h = 0, sv = 0.75
        if (d > 0) {
            if (mx===r2) h = ((g2-b2)/d)%6
            else if (mx===g2) h = (b2-r2)/d+2
            else h = (r2-g2)/d+4
            h *= 60; if (h<0) h += 360; sv = d/mx
        }
        colorWheel.hue = h; colorWheel.saturation = sv
        _colorPopupOpen = true
    }

    function _loadSurfFromEngine() {
        if (typeof ncde.surfaceGlass !== "function") return
        // "menus" dropped (2026-07-02, operator): menus render via NCDEKit's parchment/ink system
        // (driven by Iris Chroma), not glass — no consumer ever read the "menus" glass entry, it
        // was dead UI. "panels" split into topPanel/bottomPanel (operator: they're independent
        // surfaces). Shared "widgets" bucket replaced by one key per widget (clock/space/weather/
        // stats/salon) so each widget's glass now lives combined with its own style section in the
        // Widgets tab, instead of one setting applying uniformly to every widget at once.
        var keys = ["topPanel","bottomPanel","dock","clock","space","weather","stats","salon","laombre"]
        var s = {}
        for (var i = 0; i < keys.length; i++) {
            var k = keys[i]
            var g = ncde.surfaceGlass(k)
            s[k] = {
                tint:      (g && g["tint"])      ? g["tint"]      : ncde.accent,
                shine:     (g && g["shine"]      !== undefined) ? g["shine"]  : 0.5,
                glow:      (g && g["glow"]       !== undefined) ? g["glow"]   : 0.4,
                border:    (g && g["border"])    ? g["border"]    : ncde.gilt4,
                glowColor: (g && g["glowColor"]) ? g["glowColor"] : ncde.glow
            }
        }
        surf = s
    }
    Component.onCompleted: {
        // Lift the current engine accent so the wheel starts at the live palette.
        var c = ncde.accent
        var mx = Math.max(c.r,c.g,c.b), mn = Math.min(c.r,c.g,c.b), d = mx-mn
        var h = 0
        if (d > 0) {
            if (mx === c.r) h = ((c.g-c.b)/d) % 6
            else if (mx === c.g) h = (c.b-c.r)/d + 2
            else h = (c.r-c.g)/d + 4
            h *= 60; if (h < 0) h += 360
        }
        fHue = h; fSat = mx === 0 ? 0.5 : d/mx; recompute()
        _loadSurfFromEngine()
        _loadWidgFromEngine()
    }
    // glass-by-surface state (Top Panel/Bottom Panel/Dock) — per-widget glass (Clock/Space/Weather/
    // Stats/Salon) lives here too but its controls surface in the Widgets tab, combined with each
    // widget's own style section (operator, 2026-07-02). "Menus" removed — dead UI, nothing ever
    // consumed it (menus follow NCDEKit's parchment/ink system, driven by Iris Chroma, not glass).
    property string selSurface: "topPanel"
    property var    surf: ({
        topPanel:    { tint:ncde.accent, shine:0.5,  glow:0.4, border:ncde.gilt4, glowColor:ncde.glow },
        bottomPanel: { tint:ncde.accent, shine:0.5,  glow:0.4, border:ncde.gilt4, glowColor:ncde.glow },
        dock:        { tint:ncde.accent, shine:0.5,  glow:0.4, border:ncde.gilt4, glowColor:ncde.glow },
        clock:       { tint:ncde.accent, shine:0.5,  glow:0.4, border:ncde.gilt4, glowColor:ncde.glow },
        space:       { tint:ncde.accent, shine:0.5,  glow:0.4, border:ncde.gilt4, glowColor:ncde.glow },
        weather:     { tint:ncde.accent, shine:0.5,  glow:0.4, border:ncde.gilt4, glowColor:ncde.glow },
        stats:       { tint:ncde.accent, shine:0.5,  glow:0.4, border:ncde.gilt4, glowColor:ncde.glow },
        salon:       { tint:ncde.wine1, shine:0.35, glow:0.5, border:ncde.gilt4, glowColor:ncde.wine1 },
        laombre:     { tint:ncde.wine1, shine:0.35, glow:0.5, border:ncde.gilt4, glowColor:ncde.wine1 }
    })
    function _updateSurf(key, field, val) {
        var old = surf[key]
        var entry = { tint: old.tint, shine: old.shine, glow: old.glow, border: old.border, glowColor: old.glowColor }
        entry[field] = val
        var s = { topPanel: surf.topPanel, bottomPanel: surf.bottomPanel, dock: surf.dock,
                   clock: surf.clock, space: surf.space, weather: surf.weather, stats: surf.stats,
                   salon: surf.salon, laombre: surf.laombre }
        s[key] = entry
        surf = s
    }

    // per-widget state (Clock/Space/Weather/Stats/Salon Nocturne)
    property string selWidget: "clock"
    property var    widg: ({
        clock:   { accent:ncde.gilt3, glow:"", leading:"", fill:"", font:"Cinzel" },
        space:   { accent:ncde.cer, glow:"", leading:"", fill:"", font:"Cinzel" },
        weather: { accent:ncde.verd, glow:"", leading:"", fill:"", font:"Cinzel" },
        stats:   { accent:ncde.wine4, glow:"", leading:"", fill:"", font:"Cinzel" },
        salon:   { accent:ncde.wine1, glow:"", leading:"", fill:"", font:"Cormorant Garamond" },
        laombre: { accent:ncde.wine1, glow:"", leading:"", fill:"", font:"Cinzel" }
    })
    function _updateWidg(key, field, val) {
        var old = widg[key]
        var entry = { accent: old.accent, glow: old.glow, leading: old.leading, fill: old.fill, font: old.font }
        entry[field] = val
        var w = { clock: widg.clock, space: widg.space, weather: widg.weather, stats: widg.stats, salon: widg.salon, laombre: widg.laombre }
        w[key] = entry
        widg = w
    }
    function _loadWidgFromEngine() {
        if (typeof ncde.widgetStyle !== "function") return
        var keys = ["clock","space","weather","stats","salon","laombre"]
        var w = {}
        for (var i = 0; i < keys.length; i++) {
            var k = keys[i]
            var s = ncde.widgetStyle(k)
            w[k] = {
                accent:  (s && s["accent"])  ? s["accent"]  : widg[k].accent,
                glow:    (s && s["glow"]     !== undefined) ? s["glow"]    : "",
                leading: (s && s["leading"]  !== undefined) ? s["leading"] : "",
                fill:    (s && s["fill"])    ? s["fill"]    : widg[k].fill,
                font:    (s && s["font"])    ? s["font"]    : widg[k].font
            }
        }
        widg = w
    }

    readonly property var widgetFonts:  ["Cinzel","Cormorant Garamond","EB Garamond","IM Fell English"]

    // Phase 3 dedupe (2026-07-21): one metadata row per widget drives the 12 Glow/Frame
    // rows, the 6 Reset buttons, and their popup titles — previously unrolled copies.
    // pop = popup display name (La’Ombre’s popups were titled "Ghost", preserved).
    readonly property var widgetMeta: [
        { k:"clock",   pop:"Clock",   fontDef:"Cinzel",             reset:"Reset Clock" },
        { k:"space",   pop:"Space",   fontDef:"Cinzel",             reset:"Reset Space" },
        { k:"weather", pop:"Weather", fontDef:"Cinzel",             reset:"Reset Weather" },
        { k:"stats",   pop:"Stats",   fontDef:"Cinzel",             reset:"Reset Stats" },
        { k:"salon",   pop:"Salon",   fontDef:"Cormorant Garamond", reset:"Reset Salon" },
        { k:"laombre", pop:"Ghost",   fontDef:"Cinzel",             reset:"Reset La’Ombre d’Opale" }
    ]
    // per-widget default accent/glow colour — the same fallbacks the unrolled blocks used
    function _widgDefault(key) {
        return ({ clock: ncde.gilt3, space: ncde.cer, weather: ncde.verd,
                  stats: ncde.wine4, salon: "#6a4a8b", laombre: "#6a4a8b" })[key]
    }

    // ── persistence helpers (confirmed + guarded) ─────────────────────────
    function saveTheme() { ncde.saveTheme(settings.configBase + "active-theme.json") }
    function pushSurface(key) {
        var o = surf[key]
        if (typeof ncde.setSurfaceGlass === "function")
            ncde.setSurfaceGlass(key, Qt.color(o.tint), o.shine, o.glow, Qt.color(o.border), Qt.color(o.glowColor))
        if (typeof settings.saveSurfaceGlass === "function")
            settings.saveSurfaceGlass(key, Qt.color(o.tint), o.shine, o.glow, Qt.color(o.border), Qt.color(o.glowColor))
        saveTheme()
    }
    function pushWidget(key) {
        var o = widg[key]
        var map = { accent: o.accent || "", glow: o.glow || "", leading: o.leading || "", fill: o.fill || "", font: o.font || "" }
        if (typeof ncde.setWidgetStyleMap === "function")
            ncde.setWidgetStyleMap(key, map)
        if (typeof settings.saveWidgetStyleMap === "function")
            settings.saveWidgetStyleMap(key, map)
        saveTheme()
    }
    function pushSectionColor(prop, val) {
        // Use explicit dot notation — bracket notation does not reliably invoke C++ setters
        if      (prop === "topPanelTextColor")  settings.topPanelTextColor  = val
        else if (prop === "gliaTextColor")      settings.gliaTextColor      = val
        else if (prop === "dockHoverTextColor") settings.dockHoverTextColor = val
        else if (prop === "leapFrogTextColor")  settings.leapFrogTextColor  = val
        settings.saveSectionColors()   // instant persist — no Apply step
    }

    // ── reusable inline pieces ─────────────────────────────────────────────
    component Rule: Row {
        property string text: ""
        anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined
        spacing: 8
        Rectangle { anchors.verticalCenter: parent.verticalCenter; width: 40; height: 1; color: fp.gilt1; opacity: 0.5 }
        Text { text: parent.text; color: fp.gilt1; font.family: fp.display; font.bold: true
               font.pixelSize: SetTheme.sm; font.letterSpacing: 3 }
        Rectangle { anchors.verticalCenter: parent.verticalCenter; width: 40; height: 1; color: fp.gilt1; opacity: 0.5 }
    }
    component Swatch: Rectangle {
        property string hexv: "#000000"
        property bool   on: false
        signal picked()
        width: 22; height: 22; radius: 11
        color: hexv === "" ? "transparent" : hexv
        border.width: on ? 3 : 1
        border.color: on ? fp.gilt3 : fp.gilt0
        Text { text: "↺"; visible: parent.hexv === ""; anchors.centerIn: parent; color: fp.gilt1; font.pixelSize: SetTheme.md }
        HoverHandler { id: swh }
        Rectangle { anchors.fill: parent; radius: width/2; color: fp.gilt5; opacity: swh.hovered && !parent.on ? 0.15 : 0 }
        TapHandler { onTapped: parent.picked() }
    }

    // ── Tab bar ──────────────────────────────────────────────────────────
    Flow {
        id: tabBar
        anchors.top: parent.top; anchors.topMargin: 6
        anchors.left: parent.left; anchors.right: parent.right
        spacing: 6
        Repeater {
            model: [
                {k:"type",     n:"Fonts"},
                {k:"sections", n:"Sections"},
                {k:"glass",    n:"Glass"},
                {k:"widgets",  n:"Widgets"},
                {k:"iris",     n:"Iris Chroma"}
            ]
            Rectangle {
                height: 26; radius: 13; width: tlbl.implicitWidth + 22
                property bool sel: fil._activeTab === modelData.k
                border.color: sel ? fp.gilt0 : fp.gilt1; border.width: sel ? 2 : 1.5
                color: sel ? fp.gilt4 : fp.paper0
                Text {
                    id: tlbl; anchors.centerIn: parent
                    text: modelData.n; font.family: fp.titles; font.pixelSize: SetTheme.sm
                    color: parent.sel ? fp.wine1 : fp.inkSoft
                }
                TapHandler { onTapped: { fil._activeTab = modelData.k; flick.contentY = 0 } }
            }
        }
    }

    // ── Content ───────────────────────────────────────────────────────────
    Flickable {
        id: flick

        anchors.top: tabBar.bottom; anchors.topMargin: 8
        anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
        contentHeight: col.height
        interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}

        Column {
            id: col
            width: parent.width
            spacing: 0
            topPadding: 8

            // ═══ TYPE TAB ══════════════════════════════════════════════════
            Column {
                visible: fil._activeTab === "type"
                onVisibleChanged: if (visible) termRow.refresh()
                width: parent.width; spacing: 14

                // ── BODY FONT ─────────────────────────────────────────────
                // Chips use fp.titles (Cinzel, always loaded) — never font.family:modelData.
                // Live preview below shows the active font.
                Rule { text: "BODY FONT" }
                Text { text: "SANS"; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; topPadding: 2 }
                Flow {
                    width: parent.width; spacing: 4
                    Repeater {
                        model: ["Noto Sans","Liberation Sans","Ubuntu","Cantarell","Roboto","Open Sans","Fira Sans","Lato"]
                        Rectangle {
                            property bool on: settings.fontFamily === modelData
                            height: 24; radius: 5; width: bfs1.implicitWidth + 14
                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                            color: on ? fp.gilt4 : fp.paper0
                            Text { id: bfs1; anchors.centerIn: parent; text: modelData; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink }
                            TapHandler { onTapped: { settings.fontFamily = modelData; settings.saveFontSettings(); settings.applyFontSettings() } }
                        }
                    }
                }
                Text { text: "SERIF"; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; topPadding: 2 }
                Flow {
                    width: parent.width; spacing: 4
                    Repeater {
                        model: ["Noto Serif","Liberation Serif","DejaVu Serif","FreeSerif","EB Garamond"]
                        Rectangle {
                            property bool on: settings.fontFamily === modelData
                            height: 24; radius: 5; width: bfs2.implicitWidth + 14
                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                            color: on ? fp.gilt4 : fp.paper0
                            Text { id: bfs2; anchors.centerIn: parent; text: modelData; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink }
                            TapHandler { onTapped: { settings.fontFamily = modelData; settings.saveFontSettings(); settings.applyFontSettings() } }
                        }
                    }
                }
                Text { text: "MONO"; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; topPadding: 2 }
                Flow {
                    width: parent.width; spacing: 4
                    Repeater {
                        model: ["Noto Sans Mono","Liberation Mono","Ubuntu Mono","Fira Mono","JetBrains Mono","DejaVu Sans Mono"]
                        Rectangle {
                            property bool on: settings.fontFamily === modelData
                            height: 24; radius: 5; width: bfs3.implicitWidth + 14
                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                            color: on ? fp.gilt4 : fp.paper0
                            Text { id: bfs3; anchors.centerIn: parent; text: modelData; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink }
                            TapHandler { onTapped: { settings.fontFamily = modelData; settings.saveFontSettings(); settings.applyFontSettings() } }
                        }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Custom"; width: 50; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        width: parent.width - 60; height: 26; radius: 5
                        color: Qt.rgba(0,0,0,0.08); border.color: fp.gilt1; border.width: 1
                        TextInput {
                            anchors.fill: parent; anchors.margins: 6; verticalAlignment: TextInput.AlignVCenter
                            text: settings.fontFamily; color: fp.ink; font.family: fp.serif; font.pixelSize: SetTheme.sm
                            onEditingFinished: { settings.fontFamily = text; settings.saveFontSettings(); settings.applyFontSettings() }
                        }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Weight"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Row {
                        spacing: 4; anchors.verticalCenter: parent.verticalCenter
                        Repeater {
                            model: [{n:"Light",v:300},{n:"Regular",v:400},{n:"Bold",v:700}]
                            Rectangle {
                                height: 24; radius: 5; width: wtxt.implicitWidth + 14
                                property bool on: settings.fontWeight === modelData.v
                                border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                                color: on ? fp.gilt4 : fp.paper0
                                Text { id: wtxt; anchors.centerIn: parent; text: modelData.n; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink }
                                TapHandler { onTapped: { settings.fontWeight = modelData.v; settings.saveFontSettings(); settings.applyFontSettings() } }
                            }
                        }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Italic"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        height: 24; width: 60; radius: 5
                        property bool on: settings.fontItalic
                        border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                        color: on ? fp.gilt4 : fp.paper0
                        Text { anchors.centerIn: parent; text: parent.on ? "On" : "Off"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink }
                        TapHandler { onTapped: { settings.fontItalic = !settings.fontItalic; settings.saveFontSettings(); settings.applyFontSettings() } }
                    }
                }

                // ── NCDE SIGNATURE FONTS ──────────────────────────────────
                Rule { text: "NCDE SIGNATURE FONTS" }
                Rectangle {
                    width: parent.width; radius: 7; border.color: fp.gilt1; border.width: 1
                    color: Qt.rgba(0,0,0,0.03)
                    height: sigCol.height + 18
                    Column {
                        id: sigCol
                        anchors.left: parent.left; anchors.right: parent.right
                        anchors.top: parent.top; anchors.margins: 10; spacing: 6
                        Text { text: "NCDE's visual identity — not user-configurable."; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }
                        Repeater {
                            model: [
                                {role:"Display",    f:"Cinzel Decorative"},
                                {role:"Titles",     f:"Cinzel"},
                                {role:"Serif",      f:"Cormorant Garamond"},
                                {role:"Body Serif", f:"EB Garamond"},
                                {role:"Accent",     f:"IM Fell English"},
                                {role:"Mono",       f:"TerminalVector"}
                            ]
                            Row {
                                spacing: 10
                                Text { text: modelData.role; width: 80; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData.f; color: fp.ink; font.family: modelData.f; font.pixelSize: SetTheme.md }
                            }
                        }
                    }
                }

                // ── MEASURE ───────────────────────────────────────────────
                Rule { text: "MEASURE" }

                // Live sample — both sliders below apply immediately (no separate
                // Apply step), so this resizes in real time as you drag.
                Rectangle {
                    width: parent.width; height: 44; radius: 6; clip: true
                    color: Qt.rgba(0,0,0,0.03); border.color: fp.gilt1; border.width: 1
                    Text {
                        anchors.centerIn: parent
                        text: "The quick brown fox jumps — 1234"
                        color: fp.ink; font.family: settings.fontFamily; font.weight: settings.fontWeight
                        font.italic: settings.fontItalic; font.pixelSize: SetTheme.md
                    }
                }

                Text { text: "Text Size"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; topPadding: 6 }
                Row {
                    width: parent.width; spacing: 10
                    NCDESlider {
                        id: textSizeSlider
                        minValue: 75; maxValue: 200; snapValues: fil.scalePresets
                        value: fil._nearestPreset(Math.round(settings.fontSizeScale * 100))
                        onMoved: function(v) {
                            settings.fontSizeScale = v / 100.0
                            settings.saveFontSettings(); settings.applyFontSettings()
                        }
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text { text: Math.round(settings.fontSizeScale * 100) + "%"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 44; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        height: 26; radius: 13; width: rstText.implicitWidth + 22
                        anchors.verticalCenter: parent.verticalCenter
                        color: fp.paper0; border.color: fp.gilt1; border.width: 1.5
                        opacity: Math.round(settings.fontSizeScale * 100) === 100 ? 0.45 : 1.0
                        Text { id: rstText; anchors.centerIn: parent; text: "Reset to 100%"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.inkSoft }
                        TapHandler { onTapped: { settings.fontSizeScale = 1.0; settings.saveFontSettings(); settings.applyFontSettings(); textSizeSlider.value = 100 } }
                    }
                }
                Text { text: "Grows or shrinks all text, on its own."; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }

                Text { text: "Interface Scale"; width: 100; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; topPadding: 6 }
                Row {
                    width: parent.width; spacing: 10
                    NCDESlider {
                        id: uiScaleSlider
                        minValue: 75; maxValue: 200; snapValues: fil.scalePresets
                        value: fil._nearestPreset(Math.round(settings.uiScale * 100))
                        onMoved: function(v) {
                            settings.uiScale = v / 100.0
                            settings.saveFontSettings(); settings.applyFontSettings()
                        }
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text { text: Math.round(settings.uiScale * 100) + "%"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 44; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        height: 26; radius: 13; width: rstUi.implicitWidth + 22
                        anchors.verticalCenter: parent.verticalCenter
                        color: fp.paper0; border.color: fp.gilt1; border.width: 1.5
                        opacity: Math.round(settings.uiScale * 100) === 100 ? 0.45 : 1.0
                        Text { id: rstUi; anchors.centerIn: parent; text: "Reset to 100%"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.inkSoft }
                        TapHandler { onTapped: { settings.uiScale = 1.0; settings.saveFontSettings(); settings.applyFontSettings(); uiScaleSlider.value = 100 } }
                    }
                }
                Text { text: "Resizes the whole interface, including text — layers on top of Text Size above."; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; wrapMode: Text.WordWrap; width: parent.width
                }
                Text {
                    visible: settings.accessibilityTextScale > 0 && Math.abs(settings.accessibilityTextScale - 1.0) > 0.001
                    text: "Note: an Accessibility text scale of " + Math.round(settings.accessibilityTextScale * 100) + "% is also active (Settings \u2192 Accessibility). It multiplies on top of both sliders here."
                    color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm
                    wrapMode: Text.WordWrap; width: parent.width
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Spacing"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 0; maxValue: 19; value: Math.round((settings.letterSpacing + 1.5) * 2)
                        onMoved: function(v) { settings.letterSpacing = v * 0.5 - 1.5 }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.letterSpacing.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 36; anchors.verticalCenter: parent.verticalCenter }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Leading"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 8; maxValue: 25; value: Math.round(settings.lineHeight * 10)
                        onMoved: function(v) { settings.lineHeight = v / 10.0 }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.lineHeight.toFixed(1) + "×"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 36; anchors.verticalCenter: parent.verticalCenter }
                }

                // ── TEXT RENDERING ────────────────────────────────────────
                Rule { text: "TEXT RENDERING" }
                Rectangle {
                    width: parent.width; height: 76; radius: 8; clip: true
                    border.color: fp.gilt1; border.width: 1
                    gradient: Gradient { GradientStop { position: 0; color: fp.paper2 } GradientStop { position: 1; color: fp.paper3 } }
                    Column {
                        anchors.centerIn: parent; spacing: 2
                        Text { text: "The quick brown fox jumps — 1234"; font.family: settings.fontFamily; font.pixelSize: theme.fontLarge; font.weight: settings.fontWeight; font.italic: settings.fontItalic; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; style: settings.textOutlineEnabled ? Text.Outline : Text.Normal; styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : fp.gilt0; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: "The quick brown fox jumps — 1234567890"; font.family: settings.fontFamily; font.pixelSize: theme.fontMedium; font.weight: settings.fontWeight; font.italic: settings.fontItalic; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: "The quick brown fox jumps — 1234567890"; font.family: settings.fontFamily; font.pixelSize: theme.fontSmall; font.weight: settings.fontWeight; font.italic: settings.fontItalic; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; anchors.horizontalCenter: parent.horizontalCenter }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Fill"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                        border.color: fp.gilt0; border.width: 1.5
                        color: settings.textColor !== "" ? settings.textColor : ncde.gilt3
                        TapHandler { onTapped: fil.openColorPopup("Font — Fill", settings.textColor !== "" ? settings.textColor : ncde.gilt3, function(c) { settings.textColor = c; settings.saveTextColor() }) }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Outline"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Row { spacing: 6; anchors.verticalCenter: parent.verticalCenter
                        Swatch { hexv: ""; on: !settings.textOutlineEnabled
                                 onPicked: { settings.textOutlineColor = ""; settings.textOutlineEnabled = false; settings.saveFontSettings() } }
                        Rectangle {
                            width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                            border.color: settings.textOutlineEnabled ? fp.gilt3 : fp.gilt0
                            border.width: settings.textOutlineEnabled ? 3 : 1.5
                            color: settings.textOutlineColor !== "" ? settings.textOutlineColor : ncde.gilt0
                            TapHandler { onTapped: fil.openColorPopup("Font — Outline", settings.textOutlineColor !== "" ? settings.textOutlineColor : ncde.gilt0, function(c) { settings.textOutlineColor = c; settings.textOutlineEnabled = true; settings.saveFontSettings() }) }
                        }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Outline width"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 0; maxValue: 8; value: Math.round(settings.textOutlineWidth * 2)
                        onMoved: function(v){ settings.textOutlineWidth = v / 2.0 }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.textOutlineWidth.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Shadow"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Row { spacing: 6; anchors.verticalCenter: parent.verticalCenter
                        Swatch { hexv: ""; on: !settings.textShadowEnabled
                                 onPicked: { settings.textShadowEnabled = false; settings.saveFontSettings() } }
                        Rectangle {
                            width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                            border.color: settings.textShadowEnabled ? fp.gilt3 : fp.gilt0
                            border.width: settings.textShadowEnabled ? 3 : 1.5
                            color: settings.textShadowColor !== "" ? settings.textShadowColor : "#000000"
                            TapHandler { onTapped: fil.openColorPopup("Font — Shadow", settings.textShadowColor !== "" ? settings.textShadowColor : "#000000", function(c) { settings.textShadowColor = c; settings.textShadowEnabled = true; settings.saveFontSettings() }) }
                        }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Blur"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 0; maxValue: 20; value: Math.round(settings.textShadowRadius)
                        onMoved: function(v){ settings.textShadowRadius = v }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.textShadowRadius.toFixed(0) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Offset X"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 0; maxValue: 10; value: Math.round(settings.textShadowOffsetX + 5)
                        onMoved: function(v){ settings.textShadowOffsetX = v - 5 }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.textShadowOffsetX.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Offset Y"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 0; maxValue: 10; value: Math.round(settings.textShadowOffsetY + 5)
                        onMoved: function(v){ settings.textShadowOffsetY = v - 5 }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.textShadowOffsetY.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }

                Item { width: 1; height: 8 }
            }

            // ═══ SECTIONS TAB ══════════════════════════════════════════════
            Column {
                visible: fil._activeTab === "sections"
                width: parent.width; spacing: 14

                Rule { text: "SECTION COLOURS" }
                Column {
                    width: parent.width; spacing: 7
                    Repeater {
                        model: [ {p:"topPanelTextColor", n:"Top Panel"}, {p:"gliaTextColor", n:"Glia Menus"},
                                 {p:"dockHoverTextColor", n:"Dock Hover"}, {p:"leapFrogTextColor", n:"Leap Frog"} ]
                        Row {
                            id: sectionColorRow
                            width: parent.width; spacing: 12
                            property string cur: (typeof settings[modelData.p] === "string") ? settings[modelData.p] : ""
                            Text { text: modelData.n; width: 120; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5
                                color: parent.cur !== "" ? parent.cur : fil.fPalette[4]
                                TapHandler { onTapped: fil.openColorPopup(
                                    modelData.n + " — Colour",
                                    sectionColorRow.cur,
                                    function(c) { fil.pushSectionColor(modelData.p, c) },
                                    function()  { fil.pushSectionColor(modelData.p, "") }
                                ) }
                            }
                            Text { text: "↺"; color: fp.gilt1; font.family: fp.serif; font.pixelSize: SetTheme.lg; anchors.verticalCenter: parent.verticalCenter
                                   TapHandler { onTapped: fil.pushSectionColor(modelData.p, "") } }
                        }
                    }
                }

                Text { text: "Changes apply and save instantly. ↺ clears a colour back to QUILL — the engine's own ink."
                       color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm
                       wrapMode: Text.WordWrap; width: parent.width }

                Item { width: 1; height: 8 }
            }

            // ═══ GLASS TAB ═════════════════════════════════════════════════
            Column {
                visible: fil._activeTab === "glass"
                width: parent.width; spacing: 14

                // Moved from DisplayTab.qml (2026-07-02) — light/dark theme belongs alongside every
                // other appearance control (Iris Chroma for color, this for light/dark), not under
                // Devices → Display. Same ncde.darkModeLock/saveTheme() backend, unchanged.
                Rule { text: "SOLEI-LUNE" }
                Text { text: "Appearance mode — light or dark, for every app on NCDE."
                       color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }
                Row {
                    spacing: 0
                    Repeater {
                        model: [
                            {k:"auto",  n:"Auto",  i:0},
                            {k:"light", n:"Light", i:1},
                            {k:"dark",  n:"Dark",  i:2}
                        ]
                        Rectangle {
                            property bool sel: (ncde.darkModeLock || "auto") === modelData.k
                            height: 32; width: slLbl.implicitWidth + 24
                            radius: (modelData.i === 0 || modelData.i === 2) ? 10 : 0
                            border.color: sel ? fp.gilt0 : fp.gilt1; border.width: sel ? 2 : 1
                            color: sel ? fp.gilt4 : "transparent"
                            Text {
                                id: slLbl; anchors.centerIn: parent
                                text: modelData.n
                                font.family: fp.titles; font.pixelSize: SetTheme.sm
                                color: parent.sel ? fp.wine1 : fp.inkSoft
                            }
                            TapHandler { onTapped: { ncde.darkModeLock = modelData.k; ncde.saveTheme(settings.configBase + "active-theme.json") } }
                        }
                    }
                }
                Text {
                    text: {
                        var l = ncde.darkModeLock || "auto"
                        if (l === "light") return "Concordia day — warm parchment and sepia ink."
                        if (l === "dark")  return "Belle Epoque night — near-black grounds, ivory ink."
                        return "Auto — follows your wallpaper brightness."
                    }
                    color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm
                }

                Rule { text: "GLASS BY SURFACE" }
                Row {
                    width: parent.width; spacing: 8
                    Repeater {
                        model: [ {k:"topPanel",n:"Top Panel"}, {k:"bottomPanel",n:"Bottom Panel"}, {k:"dock",n:"Dock"} ]
                        Rectangle {
                            id: glassCard
                            width: (parent.width - 16) / 3; height: 74; radius: 8; clip: true
                            property var o: fil.surf[modelData.k]
                            property bool sel: fil.selSurface === modelData.k
                            border.color: sel ? fp.gilt3 : fp.gilt1; border.width: sel ? 2 : 1.5
                            color: fp.paper0
                            Rectangle {
                                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                                height: 46; clip: true
                                color: {
                                    var c = Qt.color(parent.o.tint)
                                    return Qt.rgba(c.r, c.g, c.b, 0.55)
                                }
                                Behavior on color { ColorAnimation { duration: 200 } }
                                Rectangle {
                                    anchors.centerIn: parent; width: parent.width * 0.6; height: parent.height * 0.52; radius: 7
                                    color: Qt.rgba(0,0,0,0); border.width: 1 + glassCard.o.glow * 2; border.color: glassCard.o.border
                                    Rectangle { anchors.fill: parent; radius: 7; color: glassCard.o.tint; opacity: 0.45 }
                                    Rectangle { anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                                                height: parent.height * 0.46; radius: 7; opacity: glassCard.o.shine
                                                gradient: Gradient { GradientStop { position: 0; color: Qt.rgba(1,1,1,0.7) } GradientStop { position: 1; color: Qt.rgba(1,1,1,0) } } }
                                }
                            }
                            Row {
                                anchors.bottom: parent.bottom; height: 28; anchors.horizontalCenter: parent.horizontalCenter; spacing: 6
                                Rectangle { width: 11; height: 11; radius: 6; color: glassCard.o.tint; border.color: fp.gilt0; border.width: 1; anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData.n; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink; anchors.verticalCenter: parent.verticalCenter }
                            }
                            TapHandler { onTapped: fil.selSurface = modelData.k }
                        }
                    }
                }
                Rectangle {
                    width: parent.width; radius: 8; color: Qt.rgba(0,0,0,0.04); border.color: fp.gilt1; border.width: 1
                    height: gctrlCol.height + 20
                    Column {
                        id: gctrlCol
                        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
                        anchors.margins: 11; spacing: 7
                        property var o: fil.surf[fil.selSurface]
                        Text { text: fil.selSurface.toUpperCase() + " — GLASS"; color: fp.ink; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm; font.letterSpacing: 2 }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Surface"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5; color: gctrlCol.o.tint
                                TapHandler { onTapped: fil.openColorPopup(
                                    fil.selSurface.charAt(0).toUpperCase() + fil.selSurface.slice(1) + " — Surface",
                                    gctrlCol.o.tint,
                                    function(c) { fil._updateSurf(fil.selSurface, "tint", c); fil.pushSurface(fil.selSurface) }
                                ) }
                            } }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Outline"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5; color: gctrlCol.o.border
                                TapHandler { onTapped: fil.openColorPopup(
                                    fil.selSurface.charAt(0).toUpperCase() + fil.selSurface.slice(1) + " — Outline",
                                    gctrlCol.o.border,
                                    function(c) { fil._updateSurf(fil.selSurface, "border", c); fil.pushSurface(fil.selSurface) }
                                ) }
                            } }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Glow"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5; color: gctrlCol.o.glowColor
                                TapHandler { onTapped: fil.openColorPopup(
                                    fil.selSurface.charAt(0).toUpperCase() + fil.selSurface.slice(1) + " — Glow",
                                    gctrlCol.o.glowColor,
                                    function(c) { fil._updateSurf(fil.selSurface, "glowColor", c); fil.pushSurface(fil.selSurface) }
                                ) }
                            } }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Shine"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            NCDESlider { minValue: 0; maxValue: 100; value: Math.round(gctrlCol.o.shine * 100)
                                onMoved: function(v){ fil._updateSurf(fil.selSurface, "shine", v/100) }
                                onReleased: { fil.pushSurface(fil.selSurface) }
                        anchors.verticalCenter: parent.verticalCenter } }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Glow Int."; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            NCDESlider { minValue: 0; maxValue: 100; value: Math.round(gctrlCol.o.glow * 100)
                                onMoved: function(v){ fil._updateSurf(fil.selSurface, "glow", v/100) }
                                onReleased: { fil.pushSurface(fil.selSurface) }
                        anchors.verticalCenter: parent.verticalCenter } }
                    }
                }

                // ── TERMINAL (METAL) ────────────────────────────────────────
                // ncde-terminal is a separate process/material class (Metal — tintable, but never
                // light/dark-adaptive, unlike Glass/Parchment). Only these two are exposed here:
                // a manual glass-brightness slider (NCDEGlassSurface's own baseDarkness — an
                // accessibility control, not automatic inversion) and a font override. Both are
                // written into ncde-terminal's own config.json (ncde.setTerminalFont/GlassTint) and
                // picked up live by that process's own file watcher — this app's config never
                // touches active-theme.json.
                Rule { text: "TERMINAL (METAL)" }
                Text { text: "ncde-terminal is its own material — tintable, but never light/dark-adaptive. These two are manual accessibility overrides."
                       color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }
                Row {
                    id: termRow
                    width: parent.width; spacing: 10
                    property var cfg: ncde.terminalConfig()
                    // one-shot binding goes stale if ncde-terminal's config changes while
                    // another tab is up — re-read every time the Type tab becomes visible
                    function refresh() {
                        cfg = ncde.terminalConfig()
                        termTintSlider.value = (cfg.glassTint !== undefined ? cfg.glassTint : 0) * 100
                        termFontInput.text = cfg.fontFamily !== undefined ? cfg.fontFamily : "monospace"
                    }
                    Text { text: "Glass tint"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider {
                        id: termTintSlider
                        minValue: 0; maxValue: 100
                        value: (termRow.cfg.glassTint !== undefined ? termRow.cfg.glassTint : 0) * 100
                        onMoved: function(v) { ncde.setTerminalGlassTint(v / 100.0) }
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text { text: "dark ↔ light"; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Font"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        width: 220; height: 30; radius: 6; color: fp.paper0; border.color: fp.gilt1; border.width: 1
                        anchors.verticalCenter: parent.verticalCenter
                        TextInput {
                            id: termFontInput
                            anchors.fill: parent; anchors.margins: 6; verticalAlignment: TextInput.AlignVCenter
                            color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm
                            text: termRow.cfg.fontFamily !== undefined ? termRow.cfg.fontFamily : "monospace"
                            onEditingFinished: ncde.setTerminalFont(text)
                        }
                    }
                    Text { text: "e.g. JetBrains Mono"; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }

                Item { width: 1; height: 8 }
            }

            // ═══ WIDGETS TAB ═══════════════════════════════════════════════
            Column {
                visible: fil._activeTab === "widgets"
                width: parent.width; spacing: 14

                Rule { text: "WIDGETS — COLOUR & TYPE" }
                Flow {
                    width: parent.width; spacing: 6
                    Repeater {
                        model: [ {k:"clock",n:"Clock"}, {k:"space",n:"Space"}, {k:"weather",n:"Weather"}, {k:"stats",n:"Stats"}, {k:"salon",n:"Salon Nocturne"}, {k:"laombre",n:"La’Ombre d’Opale"} ]
                        Rectangle {
                            id: widgetChip
                            height: 28; radius: 14; width: wlab.implicitWidth + 34
                            property bool sel: fil.selWidget === modelData.k
                            border.color: sel ? fp.gilt0 : fp.gilt1; border.width: sel ? 2 : 1.5
                            color: sel ? fp.gilt4 : fp.paper0
                            Row { anchors.centerIn: parent; spacing: 7
                                Rectangle { width: 11; height: 11; radius: 6; color: fil.widg[modelData.k].accent; border.color: fp.gilt0; border.width: 1; anchors.verticalCenter: parent.verticalCenter }
                                Text { id: wlab; text: modelData.n; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: widgetChip.sel ? fp.wine1 : fp.ink; anchors.verticalCenter: parent.verticalCenter } }
                            TapHandler { onTapped: fil.selWidget = modelData.k }
                        }
                    }
                }
                Rectangle {
                    id: widgPreview
                    width: parent.width; radius: 8; color: Qt.rgba(0,0,0,0.04); border.color: fp.gilt1; border.width: 1
                    height: wctrlCol.height + 22
                    property var o: fil.widg[fil.selWidget]
                    property var sample: ({ clock:["10:24","Tuesday"], space:["Desk 2","3 windows"], weather:["18°","Clear skies"], stats:["42%","CPU · 6.1 GB"], salon:["Nocturne","Op. 9 No. 2"], laombre:["♪","SALON NOCTURNE"] })[fil.selWidget]
                    Row {
                        id: wctrlCol
                        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.margins: 11
                        spacing: 12
                        Rectangle {
                            width: 150; height: 96; radius: 8; border.color: widgPreview.o.accent; border.width: 1
                            gradient: Gradient { GradientStop { position: 0; color: Qt.rgba(0,0,0,0) } GradientStop { position: 1; color: Qt.rgba(0,0,0,0) } }
                            color: Qt.lighter(widgPreview.o.accent, 1.9)
                            Column { anchors.centerIn: parent; spacing: 2
                                Text { text: widgPreview.sample[0]; color: widgPreview.o.fill; font.family: widgPreview.o.font; font.pixelSize: SetTheme.lg; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                                Text { text: widgPreview.sample[1]; color: widgPreview.o.fill; font.family: widgPreview.o.font; font.pixelSize: SetTheme.sm; anchors.horizontalCenter: parent.horizontalCenter } }
                        }
                        Column {
                            width: parent.width - 162; spacing: 7
                            Row { spacing: 10; width: parent.width
                                Text { text: "Accent"; width: 54; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                Rectangle {
                                    width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                    border.color: fp.gilt0; border.width: 1.5; color: fil.widg[fil.selWidget].accent
                                    TapHandler { onTapped: fil.openColorPopup(
                                        fil.selWidget.charAt(0).toUpperCase() + fil.selWidget.slice(1) + " — Accent",
                                        fil.widg[fil.selWidget].accent,
                                        function(c) { fil._updateWidg(fil.selWidget, "accent", c); fil.pushWidget(fil.selWidget) }
                                    ) }
                                } }
                            // Glow + Frame rows for every widget — data-driven (Phase 3).
                            // Same swatch/↺/caption/× behavior as the unrolled originals;
                            // popup default = per-widget accent for Glow, engine amber for Frame.
                            Repeater {
                                model: {
                                    var rows = []
                                    for (var i = 0; i < fil.widgetMeta.length; i++) {
                                        var m = fil.widgetMeta[i]
                                        rows.push({ wk: m.k, pop: m.pop, field: "glow",    label: "Glow",  cap: "engine default" })
                                        rows.push({ wk: m.k, pop: m.pop, field: "leading", label: "Frame", cap: "amber default" })
                                    }
                                    return rows
                                }
                                Row {
                                    visible: fil.selWidget === modelData.wk
                                    spacing: 10; width: parent.width
                                    Text { text: modelData.label; width: 54; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                    Rectangle {
                                        width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                        border.color: fp.gilt0; border.width: 1.5
                                        color: fil.widg[modelData.wk][modelData.field] !== "" ? fil.widg[modelData.wk][modelData.field] : "transparent"
                                        Text { text: "↺"; visible: fil.widg[modelData.wk][modelData.field] === ""; anchors.centerIn: parent; color: fp.gilt1; font.pixelSize: SetTheme.md }
                                        TapHandler { onTapped: fil.openColorPopup(
                                            modelData.pop + " — " + modelData.label,
                                            fil.widg[modelData.wk][modelData.field] !== "" ? fil.widg[modelData.wk][modelData.field]
                                                                                           : (modelData.field === "glow" ? fil._widgDefault(modelData.wk) : ncde.gilt3),
                                            function(c) { fil._updateWidg(modelData.wk, modelData.field, c); fil.pushWidget(modelData.wk) }
                                        ) }
                                    }
                                    Text { text: "·"; color: fp.inkSoft; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                    Text { text: modelData.cap; visible: fil.widg[modelData.wk][modelData.field] === ""; color: fp.inkSoft; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                    Text {
                                        visible: fil.widg[modelData.wk][modelData.field] !== ""
                                        text: "×"; color: fp.gilt1; font.pixelSize: SetTheme.md; anchors.verticalCenter: parent.verticalCenter
                                        TapHandler { onTapped: { fil._updateWidg(modelData.wk, modelData.field, ""); fil.pushWidget(modelData.wk) } }
                                    }
                                }
                            }
                            Row { spacing: 10; width: parent.width
                                Text { text: "Text"; width: 54; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                Rectangle {
                                    width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                    border.color: fp.gilt0; border.width: 1.5
                                    color: fil.widg[fil.selWidget].fill !== "" ? fil.widg[fil.selWidget].fill : "transparent"
                                    Text { text: "↺"; visible: fil.widg[fil.selWidget].fill === ""; anchors.centerIn: parent; color: fp.gilt1; font.pixelSize: SetTheme.md }
                                    TapHandler { onTapped: fil.openColorPopup(
                                        fil.selWidget.charAt(0).toUpperCase() + fil.selWidget.slice(1) + " — Text",
                                        fil.widg[fil.selWidget].fill !== "" ? fil.widg[fil.selWidget].fill : ncde.gilt3,
                                        function(c) { fil._updateWidg(fil.selWidget, "fill", c); fil.pushWidget(fil.selWidget) }
                                    ) }
                                }
                                Text {
                                    visible: fil.widg[fil.selWidget].fill !== ""
                                    text: "×"; color: fp.gilt1; font.pixelSize: SetTheme.md; anchors.verticalCenter: parent.verticalCenter
                                    TapHandler { onTapped: { fil._updateWidg(fil.selWidget, "fill", ""); fil.pushWidget(fil.selWidget) } }
                                }
                            }
                            Row { spacing: 10; width: parent.width
                                Text { text: "Font"; width: 54; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                Row { spacing: 5
                                    Repeater { model: fil.widgetFonts
                                        Rectangle { height: 22; radius: 5; width: ftxt.implicitWidth + 14
                                            property bool on: fil.widg[fil.selWidget].font === modelData
                                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1; color: on ? fp.gilt4 : fp.paper0
                                            Text { id: ftxt; anchors.centerIn: parent; text: modelData; font.family: modelData; font.pixelSize: SetTheme.sm; color: fp.ink }
                                            TapHandler { onTapped: { fil._updateWidg(fil.selWidget, "font", modelData); fil.pushWidget(fil.selWidget) } } } } } }
                        }
                    }
                }

                // Reset buttons — one per widget, data-driven (Phase 3). Same engine+settings
                // reset calls and per-widget accent/font fallbacks as the unrolled originals.
                Repeater {
                    model: fil.widgetMeta
                    Rectangle {
                        visible: fil.selWidget === modelData.k
                        width: parent.width; height: 28; radius: 6
                        border.color: fp.gilt1; border.width: 1.5
                        color: fp.paper1
                        Text { anchors.centerIn: parent; text: modelData.reset; color: fp.ink; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm }
                        TapHandler { onTapped: {
                            settings.resetWidgetStyle(modelData.k)
                            ncde.resetWidgetStyle(modelData.k)
                            var ws = ncde.widgetStyle(modelData.k)
                            var w = { clock: widg.clock, space: widg.space, weather: widg.weather, stats: widg.stats, salon: widg.salon, laombre: widg.laombre }
                            w[modelData.k] = {
                                accent:  (ws && ws["accent"])  ? ws["accent"]  : fil._widgDefault(modelData.k),
                                glow:    (ws && ws["glow"]     !== undefined) ? ws["glow"]    : "",
                                leading: (ws && ws["leading"]  !== undefined) ? ws["leading"] : "",
                                fill:    (ws && ws["fill"])    ? ws["fill"]    : "",
                                font:    (ws && ws["font"])    ? ws["font"]    : modelData.fontDef
                            }
                            widg = w
                        } }
                    }
                }

                // Each widget's own glass, combined here rather than a single shared setting for
                // every widget at once (operator, 2026-07-02) — generic over fil.selWidget the same
                // way the Glass tab's own control block is generic over fil.selSurface.
                Rule { text: "GLASS" }
                Rectangle {
                    id: widgGlassCtrl
                    width: parent.width; radius: 8; color: Qt.rgba(0,0,0,0.04); border.color: fp.gilt1; border.width: 1
                    height: wgCol.height + 20
                    Column {
                        id: wgCol
                        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
                        anchors.margins: 11; spacing: 7
                        property var o: fil.surf[fil.selWidget]
                        Row { spacing: 10; width: parent.width
                            Text { text: "Surface"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5; color: wgCol.o.tint
                                TapHandler { onTapped: fil.openColorPopup(
                                    fil.selWidget.charAt(0).toUpperCase() + fil.selWidget.slice(1) + " — Surface",
                                    wgCol.o.tint,
                                    function(c) { fil._updateSurf(fil.selWidget, "tint", c); fil.pushSurface(fil.selWidget) }
                                ) }
                            } }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Outline"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5; color: wgCol.o.border
                                TapHandler { onTapped: fil.openColorPopup(
                                    fil.selWidget.charAt(0).toUpperCase() + fil.selWidget.slice(1) + " — Outline",
                                    wgCol.o.border,
                                    function(c) { fil._updateSurf(fil.selWidget, "border", c); fil.pushSurface(fil.selWidget) }
                                ) }
                            } }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Glow"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5; color: wgCol.o.glowColor
                                TapHandler { onTapped: fil.openColorPopup(
                                    fil.selWidget.charAt(0).toUpperCase() + fil.selWidget.slice(1) + " — Glow",
                                    wgCol.o.glowColor,
                                    function(c) { fil._updateSurf(fil.selWidget, "glowColor", c); fil.pushSurface(fil.selWidget) }
                                ) }
                            } }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Shine"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            NCDESlider { minValue: 0; maxValue: 100; value: Math.round(wgCol.o.shine * 100)
                                onMoved: function(v){ fil._updateSurf(fil.selWidget, "shine", v/100) }
                                onReleased: { fil.pushSurface(fil.selWidget) }
                        anchors.verticalCenter: parent.verticalCenter } }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Glow Int."; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            NCDESlider { minValue: 0; maxValue: 100; value: Math.round(wgCol.o.glow * 100)
                                onMoved: function(v){ fil._updateSurf(fil.selWidget, "glow", v/100) }
                                onReleased: { fil.pushSurface(fil.selWidget) }
                        anchors.verticalCenter: parent.verticalCenter } }
                    }
                }

                Item { width: 1; height: 8 }
            }

            // ── Iris Chroma — 90 curated palettes across 9 themes ─────────────────
            Column {
                id: irisCol
                visible: fil._activeTab === "iris"
                width: parent.width
                spacing: 0

                // active palette = engine accentName (same identity Style Manager and
                // main.qml's reapplyActivePreset use); kept fresh via themeChanged so
                // changes made elsewhere (Style Manager) reflect here too.
                property string activeName: ncde.accentName
                Connections { target: ncde; function onThemeChanged() { irisCol.activeName = ncde.accentName } }

                property var cats: [
                    {label: "Crimson Masquerade",   from: 0,  to: 23},
                    {label: "The Garou Nation",      from: 23, to: 37},
                    {label: "The Nine Traditions",   from: 37, to: 46},
                    {label: "The Convention",        from: 46, to: 51},
                    {label: "The Underworld Guilds", from: 51, to: 61},
                    {label: "The Dreaming Courts",   from: 61, to: 73},
                    {label: "The Hunter's Road",     from: 73, to: 80},
                    {label: "Mythic Realms",         from: 80, to: 87},
                    {label: "The Brass Age",         from: 87, to: 90}
                ]

                Item { width: 1; height: 10 }

                Text {
                    leftPadding: 10
                    text: "IRIS CHROMA — 90 Curated Palettes"
                    color: fp.gilt4; font.family: fp.display; font.bold: true
                    font.pixelSize: SetTheme.sm; font.letterSpacing: 1
                }
                Item { width: 1; height: 6 }

                Repeater {
                    model: irisCol.cats
                    delegate: Column {
                        id: catCol
                        property var cat: modelData
                        width: irisCol.width; spacing: 0

                        Rectangle {
                            width: parent.width; height: 26
                            color: Qt.rgba(fp.gilt1.r, fp.gilt1.g, fp.gilt1.b, 0.18)
                            Text {
                                anchors.verticalCenter: parent.verticalCenter; leftPadding: 10
                                text: catCol.cat.label.toUpperCase()
                                color: fp.gilt4; font.family: fp.titles
                                font.pixelSize: SetTheme.sm - 1; font.letterSpacing: 1.2
                            }
                        }

                        Flow {
                            width: parent.width; spacing: 6
                            topPadding: 6; bottomPadding: 6; leftPadding: 6; rightPadding: 6
                            Repeater {
                                model: ncde.presets().slice(catCol.cat.from, catCol.cat.to)
                                delegate: Rectangle {
                                    id: irisCard
                                    property var pd: modelData
                                    width: 148; height: 56; radius: 6
                                    readonly property bool isActive: irisCol.activeName === pd.name
                                    color: irisCardTap.pressed ? fp.gilt3 : fp.paper1
                                    border.color: isActive ? fp.gilt4 : (irisCardHover.hovered ? fp.gilt3 : fp.gilt1)
                                    border.width: isActive ? 2 : 1
                                    Column {
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.left: parent.left; anchors.right: parent.right
                                        anchors.margins: 8; spacing: 5
                                        Text {
                                            text: irisCard.pd.name
                                            font.pixelSize: SetTheme.sm
                                            font.family: fp.titles; color: fp.ink
                                            elide: Text.ElideRight; width: parent.width
                                        }
                                        Row {
                                            spacing: 3
                                            Repeater {
                                                model: 5
                                                Rectangle {
                                                    width: 14; height: 14; radius: 7
                                                    color: {
                                                        var c = Qt.color(irisCard.pd.accent)
                                                        if (index === 0) return Qt.lighter(c, 3.0)
                                                        if (index === 1) return Qt.lighter(c, 1.7)
                                                        if (index === 2) return c
                                                        if (index === 3) return Qt.darker(c, 1.8)
                                                        return Qt.darker(c, 3.2)
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Rectangle {
                                        visible: irisCard.isActive
                                        width: 16; height: 16; radius: 8
                                        anchors.top: parent.top; anchors.right: parent.right
                                        anchors.topMargin: 4; anchors.rightMargin: 4
                                        color: fp.gilt4; border.color: fp.wine2; border.width: 1
                                        Text { anchors.centerIn: parent; text: "\u2713"; color: fp.wine1; font.bold: true; font.pixelSize: SetTheme.sm - 1 }
                                    }
                                    TapHandler { id: irisCardTap; onTapped: { ncde.applyPreset(irisCard.pd.id); saveTheme(); irisCol.activeName = irisCard.pd.name; notifications.notify("Filigree", "Theme changed: " + irisCard.pd.name, "", 2000) } }
                                    HoverHandler { id: irisCardHover }
                                }
                            }
                        }

                        Item { width: 1; height: 4 }
                    }
                }

                Item { width: 1; height: 16 }
            }
        }
    }



    // ── Unified colour picker popup (Glass / Widgets / Type / Sections) ────
    Rectangle {
        z: 20
        anchors.fill: parent
        visible: fil._colorPopupOpen
        color: Qt.rgba(0, 0, 0, 0.55)
        TapHandler {}

        Rectangle {
            anchors.centerIn: parent
            width: 280; height: colorPopupCol.height + 28
            radius: 12
            color: fp.paper0
            border.color: fp.gilt2; border.width: 2

            Column {
                id: colorPopupCol
                anchors.top: parent.top; anchors.topMargin: 14
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: fil._colorPopupTitle
                    color: fp.ink; font.family: fp.display; font.bold: true
                    font.pixelSize: SetTheme.sm; font.letterSpacing: 2
                }

                SettingsColorWheel {
                    id: colorWheel
                    width: 220; height: 220
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                // Live WCAG contrast readout — real Colors.contrastRatio()/contrastGrade()
                // (already correct, already in this file's own imports, previously never
                // called from anywhere). Only shown for font-color popups, where "contrast
                // against what" is unambiguous (text on ncde.panelBg) — glass tints/widget
                // accents don't have a single well-defined comparison, so no readout there.
                Text {
                    visible: fil._colorPopupTitle.indexOf("Font") === 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    property real _ratio: Colors.contrastRatio(colorWheel.currentHex, fil._panelBgHex())
                    property string _grade: Colors.contrastGrade(_ratio)
                    text: "Contrast on background: " + _ratio.toFixed(1) + ":1 (" + _grade + ")"
                    color: _grade === "Fail" ? "#e05252" : (_grade === "AA Large" ? fp.gilt2 : fp.ink)
                    font.family: fp.serif; font.italic: _grade === "Fail"
                    font.bold: _grade === "Fail"
                    font.pixelSize: SetTheme.sm
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 8

                    Rectangle {
                        width: 88; height: 28; radius: 6
                        border.color: fp.gilt0; border.width: 2
                        gradient: Gradient {
                            GradientStop { position: 0; color: fp.gilt4 }
                            GradientStop { position: 1; color: fp.gilt3 }
                        }
                        Text { anchors.centerIn: parent; text: "Set Colour"
                               color: fp.wine1; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm }
                        TapHandler { onTapped: {
                            if (fil._colorCallback) fil._colorCallback(colorWheel.currentHex)
                            fil._colorPopupOpen = false
                        } }
                    }

                    Rectangle {
                        visible: fil._colorResetCallback !== null
                        width: 78; height: 28; radius: 6; color: "transparent"
                        border.color: fp.gilt1; border.width: 1
                        Text {
                            anchors.centerIn: parent; text: "Reset"
                            color: fp.gilt1; font.family: fp.serif; font.pixelSize: SetTheme.sm
                            layer.enabled: settings.textShadowEnabled
                            layer.effect: MultiEffect {
                                autoPaddingEnabled: true; shadowEnabled: true
                                shadowColor: settings.textShadowColor !== "" ? settings.textShadowColor : "#000000"
                                shadowBlur: Math.max(0.0, Math.min(1.0, settings.textShadowRadius / 20.0))
                                shadowHorizontalOffset: settings.textShadowOffsetX
                                shadowVerticalOffset: settings.textShadowOffsetY
                            }
                        }
                        TapHandler { onTapped: {
                            if (fil._colorResetCallback) fil._colorResetCallback()
                            fil._colorPopupOpen = false
                        } }
                    }

                    Rectangle {
                        width: 78; height: 28; radius: 6; color: "transparent"
                        border.color: fp.inkSoft; border.width: 1
                        Text {
                            anchors.centerIn: parent; text: "Cancel"
                            color: fp.inkSoft; font.family: fp.serif; font.pixelSize: SetTheme.sm
                            layer.enabled: settings.textShadowEnabled
                            layer.effect: MultiEffect {
                                autoPaddingEnabled: true; shadowEnabled: true
                                shadowColor: settings.textShadowColor !== "" ? settings.textShadowColor : "#000000"
                                shadowBlur: Math.max(0.0, Math.min(1.0, settings.textShadowRadius / 20.0))
                                shadowHorizontalOffset: settings.textShadowOffsetX
                                shadowVerticalOffset: settings.textShadowOffsetY
                            }
                        }
                        TapHandler { onTapped: fil._colorPopupOpen = false }
                    }
                }
            }
        }
    }
}
