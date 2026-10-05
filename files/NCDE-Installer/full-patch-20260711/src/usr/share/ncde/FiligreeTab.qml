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
import "glass-modes.js" as GlassModes

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
    // Tokens come from NCDEKit (Iris Chroma → engine → kit), not a private copy:
    // the old local block hardcoded every font (ignoring the engine's font
    // choices) and skipped the kit's high-contrast ink. Names kept (paper0,
    // gilt*, ink…) so the ~1400 lines below are untouched.
    NCDEKit { id: kit }
    QtObject {
        id: fp
        readonly property color paper0:ncde.surface; readonly property color paper1:ncde.surface
        readonly property color paper2:ncde.surfaceAlt; readonly property color paper3:ncde.surfaceAlt
        readonly property color gilt0:kit.gilt0; readonly property color gilt1:kit.gilt1
        readonly property color gilt2:kit.gilt2; readonly property color gilt3:kit.gilt3
        readonly property color gilt4:kit.gilt4; readonly property color gilt5:kit.gilt5
        readonly property color wine1:kit.wine1; readonly property color wine2:kit.wine2
        readonly property color wine3:kit.wine3; readonly property color wine4:kit.wine4
        // ncde.foreground stays the ink (same as before) unless high contrast is on,
        // where the kit's WCAG-extreme ink wins.
        readonly property color ink: kit._hc ? kit.ink : ncde.foreground
        // soft captions for real (was === ink): SetTheme.inkSoft pattern, 0.65 alpha
        readonly property color inkSoft: kit._hc ? kit.inkSoft : Qt.rgba(ncde.foreground.r, ncde.foreground.g, ncde.foreground.b, 0.65)
        // Headings on paper: gilt4 on a LIGHT (Solaris) palette was pale-gold-on-vellum.
        // kit.inkLabel = gilt4 on dark grounds, gilt1 on light — readable on both.
        readonly property color label: kit.inkLabel
        readonly property string display: kit.display; readonly property string titles: kit.titles
        readonly property string serif: kit.serif;     readonly property string fell: kit.fell
        readonly property string gar: kit.gar
        readonly property string mono: "TerminalVector"   // Filigree's own readout face, deliberately not the kit mono
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
        // Full HSV decomposition — hue AND saturation AND brightness, so the wheel
        // always opens showing the colour the swatch shows (greys seed sat 0, not
        // 0.75; dark colours no longer open bright; brightness no longer sticks
        // at wherever the strip was last dragged).
        var h = 0, sv = 0
        if (d > 0) {
            if (mx===r2) h = ((g2-b2)/d)%6
            else if (mx===g2) h = (b2-r2)/d+2
            else h = (r2-g2)/d+4
            h *= 60; if (h<0) h += 360; sv = d/mx
        }
        colorWheel.hue = h; colorWheel.saturation = sv; colorWheel.value = mx
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
            // "Follow Iris palette" surfaces show the palette values NCDEGlassSurface actually
            // renders (accent tint, glow edge + glow) — not stale custom entries or the old gilt4
            // placeholder border, which never matched the real edge colour.
            var c = GlassModes.isCustom(k)
            s[k] = {
                tint:      (c && g && g["tint"])      ? g["tint"]      : ncde.accent,
                shine:     (c && g && g["shine"]      !== undefined) ? g["shine"]  : 0.5,
                glow:      (g && g["glow"]            !== undefined) ? g["glow"]   : 0.7,
                border:    (c && g && g["border"])    ? g["border"]    : ncde.glow,
                glowColor: (c && g && g["glowColor"]) ? g["glowColor"] : ncde.glow,
                custom:    c
            }
        }
        surf = s
    }
    // Stale-state fix: surf/widg used to load once, so after picking an Iris palette the
    // Glass/Widgets swatches kept showing the previous palette. Iris → engine → here.
    Connections {
        target: ncde
        function onThemeChanged() { fil._loadSurfFromEngine(); fil._loadWidgFromEngine() }
    }
    // Follow Iris palette (on) vs Custom glass (off) for one surface. Saving the theme fires
    // themeChanged, which is what makes every panel re-read its glass.
    function setFollowPalette(key, follow) {
        GlassModes.setCustom(key, !follow)
        if (follow) saveTheme()
        else pushSurface(key)
        _loadSurfFromEngine()
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
        var entry = { tint: old.tint, shine: old.shine, glow: old.glow, border: old.border, glowColor: old.glowColor, custom: old.custom }
        entry[field] = val
        // Touching a colour or Shine means "customise this surface"; Intensity works in both modes.
        if (field !== "glow") entry.custom = true
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
    // Installed families, read once (Qt.fontFamilies walks fontconfig — do not re-bind)
    readonly property var _installedFonts: Qt.fontFamilies()

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
    // Human display names for surface/widget keys — internal keys (topPanel,
    // laombre) must never leak into headings or popup titles. La’Ombre popups
    // stay "Ghost" (operator precedent, widgetMeta.pop).
    function _dispName(key) {
        return ({ topPanel:"Top Panel", bottomPanel:"Bottom Panel", dock:"Dock",
                  clock:"Clock", space:"Space", weather:"Weather", stats:"Stats",
                  salon:"Salon", laombre:"Ghost" })[key] || key
    }

    // ── persistence helpers (confirmed + guarded) ─────────────────────────
    function saveTheme() { ncde.saveTheme(settings.configBase + "active-theme.json") }
    function pushSurface(key) {
        var o = surf[key]
        if (o.custom) GlassModes.setCustom(key, true)
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

    // Follow Iris palette / Custom — one per glass control block (Glass tab + Widgets tab).
    component GlassModeRow: Column {
        id: gmRow
        property string key: ""
        readonly property bool isCustom: fil.surf[key] ? fil.surf[key].custom === true : false
        width: parent ? parent.width : 0; spacing: 4
        Row {
            spacing: 6
            Repeater {
                model: [ {follow:true, n:"Follow Iris palette"}, {follow:false, n:"Custom glass"} ]
                Rectangle {
                    property bool sel: modelData.follow ? !gmRow.isCustom : gmRow.isCustom
                    height: 24; radius: 12; width: gmLbl.implicitWidth + 20
                    border.color: sel ? fp.gilt0 : fp.gilt1; border.width: sel ? 2 : 1
                    color: sel ? fp.gilt4 : fp.paper0
                    Text { id: gmLbl; anchors.centerIn: parent; text: modelData.n; font.family: fp.titles; font.pixelSize: SetTheme.sm
                           color: parent.sel ? fp.wine1 : fp.inkSoft }
                    TapHandler { onTapped: if (!parent.sel) fil.setFollowPalette(gmRow.key, modelData.follow) }
                }
            }
        }
        Text {
            width: parent.width; wrapMode: Text.WordWrap
            text: gmRow.isCustom
                  ? "Your colours sit on top of the Iris palette. Switch back to follow it again."
                  : "Colours come from the active Iris Chroma palette. Change any swatch or Shine to customise."
            color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm
        }
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
                            height: 26; radius: 5; width: bfs1.implicitWidth + 16
                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                            color: on ? fp.gilt4 : fp.paper0
                            Row {
                                id: bfs1; anchors.centerIn: parent; spacing: 6
                                Text { text: "Aa"; font.family: modelData; font.pixelSize: SetTheme.md; color: fp.gilt3; anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink; anchors.verticalCenter: parent.verticalCenter }
                            }
                            TapHandler { onTapped: { settings.fontFamily = modelData; settings.saveFontSettings(); settings.applyFontSettings() } }
                        }
                    }
                }
                Text { text: "SERIF"; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; topPadding: 2 }
                Flow {
                    width: parent.width; spacing: 4
                    Repeater {
                        model: ["Cormorant Garamond","Noto Serif","Liberation Serif","DejaVu Serif","FreeSerif","EB Garamond"]
                        Rectangle {
                            property bool on: settings.fontFamily === modelData
                            height: 26; radius: 5; width: bfs2.implicitWidth + 16
                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                            color: on ? fp.gilt4 : fp.paper0
                            Row {
                                id: bfs2; anchors.centerIn: parent; spacing: 6
                                Text { text: "Aa"; font.family: modelData; font.pixelSize: SetTheme.md; color: fp.gilt3; anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink; anchors.verticalCenter: parent.verticalCenter }
                            }
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
                            height: 26; radius: 5; width: bfs3.implicitWidth + 16
                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                            color: on ? fp.gilt4 : fp.paper0
                            Row {
                                id: bfs3; anchors.centerIn: parent; spacing: 6
                                Text { text: "Aa"; font.family: modelData; font.pixelSize: SetTheme.md; color: fp.gilt3; anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink; anchors.verticalCenter: parent.verticalCenter }
                            }
                            TapHandler { onTapped: { settings.fontFamily = modelData; settings.saveFontSettings(); settings.applyFontSettings() } }
                        }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Custom"; width: 78; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        width: parent.width - 88; height: 26; radius: 5
                        color: Qt.rgba(0,0,0,0.08); border.color: fp.gilt1; border.width: 1
                        TextInput {
                            anchors.fill: parent; anchors.margins: 6; verticalAlignment: TextInput.AlignVCenter
                            text: settings.fontFamily; color: fp.ink; font.family: fp.serif; font.pixelSize: SetTheme.sm
                            onEditingFinished: {
                                var t = text.trim()
                                if (t === "") { text = settings.fontFamily; return }
                                settings.fontFamily = t; settings.saveFontSettings(); settings.applyFontSettings()
                            }
                        }
                    }
                }
                Text {
                    visible: fil._installedFonts.indexOf(settings.fontFamily) === -1
                    text: "\u201C" + settings.fontFamily + "\u201D isn\u2019t installed \u2014 the closest installed face is shown instead."
                    color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm
                    wrapMode: Text.WordWrap; width: parent.width
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
                Row {
                    width: parent.width; spacing: 10
                    Item { width: 78; height: 1 }
                    Rectangle {
                        property bool atDefault: settings.fontFamily === "Noto Sans" && settings.fontWeight === 400
                                                 && !settings.fontItalic && Math.abs(settings.letterSpacing) < 0.05
                                                 && Math.abs((settings.lineHeight > 0 ? settings.lineHeight : 1.0) - 1.0) < 0.05
                        height: 26; radius: 13; width: rstTypo.implicitWidth + 22
                        color: fp.paper0; border.color: fp.gilt1; border.width: 1.5
                        opacity: atDefault ? 0.45 : 1.0
                        Text { id: rstTypo; anchors.centerIn: parent; text: "Reset Typography"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.inkSoft }
                        TapHandler { onTapped: {
                            settings.fontFamily = "Noto Sans"; settings.fontWeight = 400; settings.fontItalic = false
                            settings.letterSpacing = 0.0; settings.lineHeight = 1.0
                            settings.saveFontSettings(); settings.applyFontSettings()
                            // sliders hold their own value once dragged — resync the knobs
                            spacingSlider.value = 3; leadingSlider.value = 10
                        } }
                    }
                    Text { text: "Family, weight, italic, spacing, leading \u2014 back to NCDE defaults."; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }

                // ── MEASURE ───────────────────────────────────────────────
                Rule { text: "MEASURE" }

                // Live sample — both sliders below apply immediately (no separate
                // Apply step), so this resizes in real time as you drag.
                Rectangle {
                    width: parent.width; height: 72; radius: 6; clip: true
                    color: Qt.rgba(0,0,0,0.03); border.color: fp.gilt1; border.width: 1
                    Text {
                        anchors.centerIn: parent; horizontalAlignment: Text.AlignHCenter
                        text: "The quick brown fox jumps over the lazy dog\n1234567890 \u2014 AaBbCcDdEe"
                        color: fp.ink; font.family: settings.fontFamily; font.weight: settings.fontWeight
                        font.italic: settings.fontItalic; font.pixelSize: SetTheme.md
                        font.letterSpacing: settings.letterSpacing
                        lineHeight: settings.lineHeight > 0 ? settings.lineHeight : 1.0
                    }
                }

                Text { text: "Script Shift"; width: 110; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; topPadding: 6 }
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
                Text { text: "One dial for every word in NCDE — shell, desktop widgets, Settings and the house apps. Widgets grow to fit; nothing else resizes."; wrapMode: Text.WordWrap; width: parent.width; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }

                // Script Shift (2026-09-24, operator): ONE dial for all text. "Interface Scale"
                // (uiScale) and its Accessibility-multiplier note were removed here: uiScale is
                // retired at 1 (main.qml folds any old value into Script Shift once) and the
                // Accessibility tab's text slider now drives this same fontSizeScale value.
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Spacing"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { id: spacingSlider; minValue: 0; maxValue: 19; value: Math.round((settings.letterSpacing + 1.5) * 2)
                        onMoved: function(v) { settings.letterSpacing = v * 0.5 - 1.5 }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.letterSpacing.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 36; anchors.verticalCenter: parent.verticalCenter }
                }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Leading"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { id: leadingSlider; minValue: 8; maxValue: 25; value: Math.round(settings.lineHeight * 10)
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
                        // the shadow the controls below configure must be visible HERE,
                        // else Shadow/Blur/Offset appear to do nothing (shell blur is /32)
                        layer.enabled: settings.textShadowEnabled
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: settings.textShadowColor !== "" ? settings.textShadowColor : "#000000"
                            shadowBlur: Math.max(0.0, Math.min(1.0, settings.textShadowRadius / 32.0))
                            shadowHorizontalOffset: settings.textShadowOffsetX
                            shadowVerticalOffset: settings.textShadowOffsetY
                        }
                        Text { text: "The quick brown fox jumps — 1234"; font.family: settings.fontFamily; font.pixelSize: SetTheme.lg; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: settings.letterSpacing; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; style: settings.textOutlineEnabled ? Text.Outline : Text.Normal; styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : fp.gilt0; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: "The quick brown fox jumps — 1234567890"; font.family: settings.fontFamily; font.pixelSize: SetTheme.md; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: settings.letterSpacing; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; style: settings.textOutlineEnabled ? Text.Outline : Text.Normal; styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : fp.gilt0; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: "The quick brown fox jumps — 1234567890"; font.family: settings.fontFamily; font.pixelSize: SetTheme.sm; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: settings.letterSpacing; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; style: settings.textOutlineEnabled ? Text.Outline : Text.Normal; styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : fp.gilt0; anchors.horizontalCenter: parent.horizontalCenter }
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
                    // inert until an outline colour is set — dimmed so the dependency reads
                    opacity: settings.textOutlineEnabled ? 1.0 : 0.45
                    enabled: settings.textOutlineEnabled
                    Text { text: "Thickness"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
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
                    opacity: settings.textShadowEnabled ? 1.0 : 0.45
                    enabled: settings.textShadowEnabled
                    Text { text: "Blur"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 0; maxValue: 20; value: Math.round(settings.textShadowRadius)
                        onMoved: function(v){ settings.textShadowRadius = v }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.textShadowRadius.toFixed(0) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }
                Row {
                    width: parent.width; spacing: 10
                    opacity: settings.textShadowEnabled ? 1.0 : 0.45
                    enabled: settings.textShadowEnabled
                    Text { text: "Offset X"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 0; maxValue: 10; value: Math.round(settings.textShadowOffsetX + 5)
                        onMoved: function(v){ settings.textShadowOffsetX = v - 5 }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.textShadowOffsetX.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }
                Row {
                    width: parent.width; spacing: 10
                    opacity: settings.textShadowEnabled ? 1.0 : 0.45
                    enabled: settings.textShadowEnabled
                    Text { text: "Offset Y"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    NCDESlider { minValue: 0; maxValue: 10; value: Math.round(settings.textShadowOffsetY + 5)
                        onMoved: function(v){ settings.textShadowOffsetY = v - 5 }
                        onReleased: { settings.saveFontSettings() }
                        anchors.verticalCenter: parent.verticalCenter }
                    Text { text: settings.textShadowOffsetY.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }

                // ── TERMINAL ──────────────────────────────────────────────
                // Relocated from the Glass tab 2026-07-21 so every font on the
                // system is controlled from this one tab. The glass-tint slider
                // stays in Glass (it is a material control, not a font one).
                Rule { text: "TERMINAL" }
                Text { text: "ncde-terminal\u2019s own face \u2014 separate from the shell body font above."
                       color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }
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
                            onEditingFinished: {
                                var t = text.trim()
                                if (t === "") { text = termRow.cfg.fontFamily !== undefined ? termRow.cfg.fontFamily : "monospace"; return }
                                ncde.setTerminalFont(t)
                            }
                        }
                    }
                    Text { text: "e.g. JetBrains Mono"; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
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
                                    sectionColorRow.cur !== "" ? sectionColorRow.cur : fil.fPalette[4],
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
                onVisibleChanged: if (visible) termRow.refresh()
                width: parent.width; spacing: 14

                // Moved from DisplayTab.qml (2026-07-02) — light/dark theme belongs alongside every
                // other appearance control (Iris Chroma for color, this for light/dark), not under
                // Devices → Display. Same ncde.darkModeLock/saveTheme() backend, unchanged.
                Rule { text: "SOLEI-LUNE" }
                Text { text: "Appearance mode — light or dark, for every app on NCDE."
                       color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }
                Row {
                    spacing: 6
                    Repeater {
                        model: [
                            {k:"auto",  n:"Auto",  i:0},
                            {k:"light", n:"Light", i:1},
                            {k:"dark",  n:"Dark",  i:2}
                        ]
                        Rectangle {
                            property bool sel: (ncde.darkModeLock || "auto") === modelData.k
                            height: 32; width: slLbl.implicitWidth + 24
                            radius: 16
                            border.color: sel ? fp.gilt0 : fp.gilt1; border.width: sel ? 2 : 1
                            color: sel ? fp.gilt4 : fp.paper0
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
                                color: "black"
                                // Live preview = the REAL NCDEGlassSurface pipeline over a crop of the
                                // actual wallpaper (the old preview was flat rectangles that looked nothing
                                // like the glass). Fed from the tab's local state, so it tracks slider drags
                                // before they're saved. Sampling a sibling Image is valid in any Window.
                                Image {
                                    id: prevWp
                                    anchors.fill: parent
                                    fillMode: Image.PreserveAspectCrop
                                    asynchronous: true
                                    sourceSize.width: 240
                                    source: { var p = settings.getWallpaper() || ""; return p === "" ? "" : (p.indexOf("://") > 0 ? p : "file://" + p) }
                                }
                                NCDEGlassSurface {
                                    anchors.centerIn: parent
                                    width: parent.width * 0.72; height: parent.height * 0.52
                                    cornerRadius: modelData.k === "dock" ? height / 2 : 6
                                    backgroundSource: prevWp
                                    blurPx: 14
                                    tint:     { var c = Qt.color(glassCard.o.tint); return Qt.rgba(c.r, c.g, c.b, 0.18) }
                                    edge:     { var c = Qt.color(glassCard.o.border); return Qt.rgba(c.r, c.g, c.b, 0.85) }
                                    glowRim:  Qt.color(glassCard.o.glowColor)
                                    glowHalo: Qt.color(glassCard.o.glowColor)
                                    glowA:    glassCard.o.glow
                                    shine:    glassCard.o.shine
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
                        Text { text: fil._dispName(fil.selSurface).toUpperCase() + " — GLASS"; color: fp.ink; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm; font.letterSpacing: 2 }
                        GlassModeRow { key: fil.selSurface }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Surface"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5; color: gctrlCol.o.tint
                                TapHandler { onTapped: fil.openColorPopup(
                                    fil._dispName(fil.selSurface) + " — Surface",
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
                                    fil._dispName(fil.selSurface) + " — Outline",
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
                                    fil._dispName(fil.selSurface) + " — Glow",
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
                            Text { text: "Intensity"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
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
                Text { text: "ncde-terminal is its own material — tintable, but never light/dark-adaptive. This brightness override is a manual accessibility control; its font moved to the Fonts tab."
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
                            // (a gradient overrides `color` in QML — the old fully-transparent
                            // two-stop gradient meant this tint never painted)
                            color: Qt.lighter(widgPreview.o.accent, 1.9)
                            Column { anchors.centerIn: parent; spacing: 2
                                Text { text: widgPreview.sample[0]; color: widgPreview.o.fill !== "" ? widgPreview.o.fill : ncde.gilt4; font.family: widgPreview.o.font; font.pixelSize: SetTheme.lg; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                                Text { text: widgPreview.sample[1]; color: widgPreview.o.fill !== "" ? widgPreview.o.fill : ncde.gilt4; font.family: widgPreview.o.font; font.pixelSize: SetTheme.sm; anchors.horizontalCenter: parent.horizontalCenter } }
                        }
                        Column {
                            width: parent.width - 162; spacing: 7
                            Row { spacing: 10; width: parent.width
                                Text { text: "Accent"; width: 54; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                Rectangle {
                                    width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                    border.color: fp.gilt0; border.width: 1.5; color: fil.widg[fil.selWidget].accent
                                    TapHandler { onTapped: fil.openColorPopup(
                                        fil._dispName(fil.selWidget) + " — Accent",
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
                                        fil._dispName(fil.selWidget) + " — Text",
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
                        Text { text: fil._dispName(fil.selWidget).toUpperCase() + " — GLASS"; color: fp.ink; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm; font.letterSpacing: 2 }
                        GlassModeRow { key: fil.selWidget }
                        Row { spacing: 10; width: parent.width
                            Text { text: "Surface"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                            Rectangle {
                                width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                border.color: fp.gilt0; border.width: 1.5; color: wgCol.o.tint
                                TapHandler { onTapped: fil.openColorPopup(
                                    fil._dispName(fil.selWidget) + " — Surface",
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
                                    fil._dispName(fil.selWidget) + " — Outline",
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
                                    fil._dispName(fil.selWidget) + " — Glow",
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
                            Text { text: "Intensity"; width: 60; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
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

                // presets() is static data — read once instead of 18× per rebuild.
                readonly property var allPresets: ncde.presets()
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

                // Light/dark axis, 2026-09-23 (operator: "Solaris" / "Midnight Mass"),
                // layered on TOP of the faction categories above — each section still
                // groups by faction, just filtered to that section's light/dark subset.
                // ncde.presets() already carries a real per-preset `dark` bool (raw.dark
                // in NCDEEngine::presets(), verified against the reconstructed source),
                // no new data plumbing needed.
                property var sections: [
                    {label: "Solaris",       dark: false},
                    {label: "Midnight Mass", dark: true}
                ]
                // Returns [{label, items}] for one section's dark value — categories
                // with zero matching presets are skipped entirely (never instantiated),
                // not just hidden, so no empty section headers show up.
                function catsForSection(wantDark) {
                    var out = [], all = irisCol.allPresets, last = 0
                    for (var i = 0; i < irisCol.cats.length; i++) {
                        var cat = irisCol.cats[i]
                        last = Math.max(last, cat.to)
                        var items = all.slice(cat.from, cat.to).filter(function(p) { return p.dark === wantDark })
                        if (items.length > 0) out.push({label: cat.label, items: items})
                    }
                    // The ranges above are hand-kept index spans; any preset added past them
                    // still shows up instead of silently vanishing from the picker.
                    var extra = all.slice(last).filter(function(p) { return p.dark === wantDark })
                    if (extra.length > 0) out.push({label: "Further Palettes", items: extra})
                    return out
                }

                Item { width: 1; height: 10 }

                Text {
                    leftPadding: 10
                    text: "IRIS CHROMA — " + irisCol.allPresets.length + " Curated Palettes"
                    color: fp.label; font.family: fp.display; font.bold: true
                    font.pixelSize: SetTheme.sm; font.letterSpacing: 1
                }
                Item { width: 1; height: 6 }

                // ── From your wallpaper (2026-09-24) ─────────────────────────────
                // Suggests the three curated presets that best suit the current
                // wallpaper. Curated-paint model intact: it only RANKS the 90 presets,
                // never mixes a colour. Sampled on a tiny hidden Canvas (64x40): the
                // two strongest hue clusters (weighted by chroma) are matched against
                // each preset's accent + border in CIELAB, the wallpaper's overall
                // lightness picks Solaris vs Midnight Mass, and the ground colour is a
                // tie-breaker. Re-ranks whenever the Iris tab is opened.
                Item {
                    width: 1; height: 0
                    Canvas {
                        id: wallSampler
                        width: 64; height: 40
                        opacity: 0
                        property string src: {
                            var p = (typeof settings.getWallpaper === "function") ? settings.getWallpaper() : ""
                            return p ? "file://" + p : ""
                        }
                        property string _pending: ""
                        function sample() {
                            if (src === "") return
                            if (isImageLoaded(src)) requestPaint()
                            else { _pending = src; loadImage(src) }
                        }
                        onImageLoaded: requestPaint()
                        onPaint: {
                            if (src === "" || !isImageLoaded(src)) return
                            var ctx = getContext("2d")
                            ctx.clearRect(0, 0, width, height)
                            ctx.drawImage(src, 0, 0, width, height)
                            irisCol.rankForWallpaper(ctx.getImageData(0, 0, width, height).data)
                        }
                    }
                }
                Connections {
                    target: irisCol
                    function onVisibleChanged() { if (irisCol.visible) wallSampler.sample() }
                }

                property var wallPicks: []
                property var wallClusters: []
                property bool wallIsDark: true

                // ── Woven from the wallpaper (operator, 2026-09-24: "drawn from the
                // wallpaper's colours with motif math") ─────────────────────────────
                // The motif math is the same rule the 2026-07-21 Iris redesign used to
                // make the 90 palettes: rotate hue in LCh, keep lightness. The best-
                // ranked curated palette is the template; its accent family turns to the
                // wallpaper's strongest hue, its gilt family to the second. L (and so
                // every contrast relationship) is kept; text, shadows and the semantic
                // status colours (verd/cer/rose/amber, wine) stay exactly as curated.
                readonly property var _famAccent: ["accentMuted","background","surface","surfaceAlt","surfaceHi",
                    "panelBg","popupBg","clockColor","lamp","widgetC0","widgetC1","widgetC2","widgetC3",
                    "widgetC4","widgetC5","selectColor","activeBg","inactiveBg","activeTs","activeBs",
                    "inactiveTs","inactiveBs"]
                readonly property var _famGilt: ["gilt0","gilt1","gilt2","gilt3","gilt4","gilt5"]
                readonly property string _wovenPath: settings.configBase + "wallpaper-palette.json"
                property bool wovenActive: false

                function _lch(lab) { return [lab[0], Math.sqrt(lab[1]*lab[1] + lab[2]*lab[2]), Math.atan2(lab[2], lab[1])] }
                function _labToHex(L, a, b) {
                    function finv(t) { return t > 0.206893 ? t * t * t : (t - 16 / 116) / 7.787 }
                    var fy = (L + 16) / 116, x = 0.95047 * finv(fy + a / 500), y = finv(fy), z = 1.08883 * finv(fy - b / 200)
                    var rgb = [ 3.2406 * x - 1.5372 * y - 0.4986 * z,
                               -0.9689 * x + 1.8758 * y + 0.0415 * z,
                                0.0557 * x - 0.2040 * y + 1.0570 * z]
                    var ok = true, out = "#"
                    for (var i = 0; i < 3; i++) {
                        var c = rgb[i] <= 0.0031308 ? 12.92 * rgb[i] : 1.055 * Math.pow(Math.max(rgb[i], 0), 1 / 2.4) - 0.055
                        if (c < -0.002 || c > 1.002) ok = false
                        var v = Math.round(Math.min(1, Math.max(0, c)) * 255)
                        out += (v < 16 ? "0" : "") + v.toString(16)
                    }
                    return { hex: out, inGamut: ok }
                }
                // hue-rotate one colour by d radians; L kept, C trimmed only if out of gamut
                function _rotate(c, d, chromaTo, chromaMix) {
                    var q = _lch(_labOf(c)), C = q[1]
                    if (chromaTo !== undefined) C = C + (chromaTo - C) * chromaMix
                    if (C < 4) return Qt.color(c).toString()   // near-grey: no hue to turn
                    var h = q[2] + d, r
                    for (var k = 0; k < 24; k++) {
                        r = _labToHex(q[0], C * Math.cos(h), C * Math.sin(h))
                        if (r.inGamut) break
                        C *= 0.92
                    }
                    return r.hex
                }
                function _hueDelta(from, toLab) {
                    var d = _lch(toLab)[2] - _lch(_labOf(from))[2]
                    while (d > Math.PI) d -= 2 * Math.PI
                    while (d < -Math.PI) d += 2 * Math.PI
                    return d
                }
                // preview pigments (panelBg, surface, accent, border, ink) — no engine calls
                function wovenPreview(p) {
                    if (!p || wallClusters.length < 2) return []
                    var d1 = _hueDelta(p.accent, wallClusters[0]), d2 = _hueDelta(p.border || p.accent, wallClusters[1])
                    var c1 = _lch(wallClusters[0])[1]
                    return [_rotate(p.panelBg || p.accent, d1), _rotate(p.surface || p.accent, d1),
                            _rotate(p.accent, d1, c1, 0.5), _rotate(p.border || p.accent, d2), p.ink || "#000000"]
                }
                function applyWoven() {
                    var t = wallPicks[0]
                    if (!t || wallClusters.length < 2) return
                    ncde.applyPreset(t.id)                    // template tokens into the engine
                    var d1 = _hueDelta(ncde.accent, wallClusters[0]), d2 = _hueDelta(ncde.border, wallClusters[1])
                    var c1 = _lch(wallClusters[0])[1], pal = {}
                    for (var i = 0; i < _famAccent.length; i++) {
                        var k = _famAccent[i]
                        if (ncde[k] !== undefined) pal[k] = _rotate(ncde[k], d1)
                    }
                    for (var j = 0; j < _famGilt.length; j++) {
                        var g = _famGilt[j]
                        if (ncde[g] !== undefined) pal[g] = _rotate(ncde[g], d2)
                    }
                    var acc = _rotate(ncde.accent, d1, c1, 0.5), brd = _rotate(ncde.border, d2), glw = _rotate(ncde.glow, d1)
                    ncde.applyPalette(pal)
                    // accent/border/glow ride the Style Manager override path, which
                    // main.qml already replays at login (loadColorOverrides)
                    ncde.setOverrideAccent(acc); settings.accentOverride = acc
                    ncde.setOverrideBorder(brd); settings.borderOverride = brd
                    ncde.setOverrideGlow(glw);   settings.glowOverride = glw
                    settings.saveColorOverrides()
                    saveTheme()
                    _writeWoven({ active: true, template: t.name, palette: pal,
                                  accent: acc, border: brd, glow: glw })
                    wovenActive = true
                    inkFromWallpaper()
                    irisCol.activeName = ""
                    notifications.notify("Filigree", "Palette woven from your wallpaper (" + t.name + " pattern)", "", 2500)
                }
                // Wallpaper ink (2026-09-24): a palette picked from this section also
                // re-inks all shell text in the wallpaper's strongest hue (ncde-ink.js);
                // a card from the main grid turns it off.
                function inkFromWallpaper() {
                    if (wallClusters.length > 0) WallInk.setInk(true, _lch(wallClusters[0])[2])
                }
                // any curated card: the woven layer steps aside
                function clearWoven() {
                    if (!wovenActive) return
                    wovenActive = false
                    ncde.setOverrideAccent(""); settings.accentOverride = ""
                    ncde.setOverrideBorder(""); settings.borderOverride = ""
                    ncde.setOverrideGlow("");   settings.glowOverride = ""
                    settings.saveColorOverrides()
                    _writeWoven({ active: false })
                }
                function _writeWoven(obj) {
                    var x = new XMLHttpRequest()
                    try { x.open("PUT", "file://" + _wovenPath); x.send(JSON.stringify(obj, null, 2)) } catch (e) { }
                }
                Component.onCompleted: {
                    if (irisCol.visible) wallSampler.sample()
                    var x = new XMLHttpRequest()
                    x.onreadystatechange = function() {
                        if (x.readyState !== XMLHttpRequest.DONE) return
                        try { irisCol.wovenActive = JSON.parse(x.responseText).active === true } catch (e) { }
                    }
                    try { x.open("GET", "file://" + _wovenPath); x.send() } catch (e) { }
                }
                function _lab(r, g, b) {
                    function lin(c) { c /= 255; return c <= 0.04045 ? c / 12.92 : Math.pow((c + 0.055) / 1.055, 2.4) }
                    var R = lin(r), G = lin(g), B = lin(b)
                    var x = (R * 0.4124 + G * 0.3576 + B * 0.1805) / 0.95047
                    var y =  R * 0.2126 + G * 0.7152 + B * 0.0722
                    var z = (R * 0.0193 + G * 0.1192 + B * 0.9505) / 1.08883
                    function f(t) { return t > 0.008856 ? Math.cbrt(t) : 7.787 * t + 16 / 116 }
                    return [116 * f(y) - 16, 500 * (f(x) - f(y)), 200 * (f(y) - f(z))]
                }
                function _labOf(c) { var q = Qt.color(c); return _lab(q.r * 255, q.g * 255, q.b * 255) }
                function _dE(a, b) { return Math.sqrt((a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) + (a[2]-b[2])*(a[2]-b[2])) }
                function rankForWallpaper(px) {
                    var n = 0, mean = [0, 0, 0], bins = []
                    for (var h = 0; h < 12; h++) bins.push({ w: 0, lab: [0, 0, 0] })
                    for (var i = 0; i + 3 < px.length; i += 4) {
                        if (px[i + 3] < 128) continue
                        var L = _lab(px[i], px[i + 1], px[i + 2])
                        mean[0] += L[0]; mean[1] += L[1]; mean[2] += L[2]; n++
                        var C = Math.sqrt(L[1] * L[1] + L[2] * L[2])
                        if (C < 12) continue                  // greys carry no hue
                        var bi = Math.floor(((Math.atan2(L[2], L[1]) + Math.PI) / (2 * Math.PI)) * 12) % 12
                        bins[bi].w += C
                        bins[bi].lab[0] += L[0] * C; bins[bi].lab[1] += L[1] * C; bins[bi].lab[2] += L[2] * C
                    }
                    if (n === 0) { wallPicks = []; return }
                    mean = [mean[0] / n, mean[1] / n, mean[2] / n]
                    bins.sort(function (a, b) { return b.w - a.w })
                    var cl = bins.filter(function (b) { return b.w > 0 }).slice(0, 2).map(function (b) {
                        return [b.lab[0] / b.w, b.lab[1] / b.w, b.lab[2] / b.w]
                    })
                    if (cl.length === 0) cl = [mean]
                    if (cl.length === 1) cl.push(cl[0])
                    var wallDark = mean[0] < 45
                    wallClusters = cl; wallIsDark = wallDark
                    var scored = allPresets.map(function (p) {
                        var A = _labOf(p.accent), B = _labOf(p.border || p.accent)
                        var fit = Math.min(_dE(A, cl[0]) + 0.5 * _dE(B, cl[1]),
                                           _dE(A, cl[1]) + 0.5 * _dE(B, cl[0]))
                        var ground = p.panelBg ? 0.3 * _dE(_labOf(p.panelBg), mean) : 0
                        return { p: p, score: fit + ground + (p.dark !== wallDark ? 35 : 0) }
                    })
                    scored.sort(function (a, b) { return a.score - b.score })
                    wallPicks = scored.slice(0, 3).map(function (x) { return x.p })
                }

                Column {
                    visible: irisCol.wallPicks.length > 0
                    width: irisCol.width; spacing: 0
                    Rectangle {
                        width: parent.width; height: 32
                        color: Qt.rgba(fp.gilt2.r, fp.gilt2.g, fp.gilt2.b, 0.30)
                        border.color: fp.gilt4; border.width: 1
                        Text {
                            anchors.verticalCenter: parent.verticalCenter; leftPadding: 10
                            text: "FROM YOUR WALLPAPER"
                            color: fp.label; font.family: fp.display; font.bold: true
                            font.pixelSize: SetTheme.sm; font.letterSpacing: 1.5
                        }
                    }
                    Flow {
                        width: parent.width; spacing: 6
                        topPadding: 6; bottomPadding: 10; leftPadding: 6; rightPadding: 6
                        Repeater {
                            model: irisCol.wallPicks
                            delegate: Rectangle {
                                id: wallCard
                                property var pd: modelData
                                width: 148; height: 56; radius: 6
                                readonly property bool isActive: irisCol.activeName === pd.name
                                color: wallCardTap.pressed ? fp.gilt3 : fp.paper1
                                border.color: isActive ? fp.gilt4 : (wallCardHover.hovered ? fp.gilt3 : fp.gilt1)
                                border.width: isActive ? 2 : 1
                                Column {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left; anchors.right: parent.right
                                    anchors.margins: 8; spacing: 5
                                    Text {
                                        text: wallCard.pd.name
                                        font.pixelSize: SetTheme.sm
                                        font.family: fp.titles; color: fp.ink
                                        elide: Text.ElideRight; width: parent.width
                                    }
                                    Row {
                                        spacing: 3
                                        Repeater {
                                            model: 5
                                            Rectangle {
                                                id: wSwatch
                                                width: 14; height: 14; radius: 7
                                                color: {
                                                    var p = wallCard.pd, c = Qt.color(p.accent)
                                                    var real = [p.panelBg, p.surface, p.accent, p.border, p.ink][index]
                                                    return (real !== undefined && real !== null && real !== "") ? real : c
                                                }
                                                border.width: 1
                                                border.color: Qt.rgba(0, 0, 0, 0.25)
                                                Rectangle {
                                                    x: wSwatch.width * 0.20; y: wSwatch.height * 0.16
                                                    width: wSwatch.width * 0.34; height: wSwatch.height * 0.24
                                                    radius: height / 2
                                                    color: Qt.rgba(1, 1, 1, 0.55)
                                                }
                                            }
                                        }
                                    }
                                }
                                Rectangle {
                                    visible: wallCard.isActive
                                    width: 16; height: 16; radius: 8
                                    anchors.top: parent.top; anchors.right: parent.right
                                    anchors.topMargin: 4; anchors.rightMargin: 4
                                    color: fp.gilt4; border.color: fp.wine2; border.width: 1
                                    Text { anchors.centerIn: parent; text: "\u2713"; color: fp.wine1; font.bold: true; font.pixelSize: SetTheme.sm - 1 }
                                }
                                TapHandler { id: wallCardTap; onTapped: { irisCol.clearWoven(); ncde.applyPreset(wallCard.pd.id); irisCol.inkFromWallpaper(); saveTheme(); irisCol.activeName = wallCard.pd.name; notifications.notify("Filigree", "Theme changed: " + wallCard.pd.name, "", 2000) } }
                                HoverHandler { id: wallCardHover }
                            }
                        }
                        // Woven card: the top pick's pattern, re-hued to the wallpaper
                        Rectangle {
                            id: wovenCard
                            visible: irisCol.wallClusters.length >= 2
                            property var pv: irisCol.wovenPreview(irisCol.wallPicks[0])
                            width: 148; height: 56; radius: 6
                            color: wovenTap.pressed ? fp.gilt3 : fp.paper1
                            border.color: irisCol.wovenActive ? fp.gilt4 : (wovenHover.hovered ? fp.gilt3 : fp.gilt2)
                            border.width: irisCol.wovenActive ? 2 : 1
                            Column {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left; anchors.right: parent.right
                                anchors.margins: 8; spacing: 5
                                Text {
                                    text: "\u2726 Woven"
                                    font.pixelSize: SetTheme.sm; font.italic: true
                                    font.family: fp.titles; color: fp.ink
                                    elide: Text.ElideRight; width: parent.width
                                }
                                Row {
                                    spacing: 3
                                    Repeater {
                                        model: wovenCard.pv
                                        Rectangle {
                                            id: vSwatch
                                            width: 14; height: 14; radius: 7
                                            color: modelData
                                            border.width: 1
                                            border.color: Qt.rgba(0, 0, 0, 0.25)
                                            Rectangle {
                                                x: vSwatch.width * 0.20; y: vSwatch.height * 0.16
                                                width: vSwatch.width * 0.34; height: vSwatch.height * 0.24
                                                radius: height / 2
                                                color: Qt.rgba(1, 1, 1, 0.55)
                                            }
                                        }
                                    }
                                }
                            }
                            Rectangle {
                                visible: irisCol.wovenActive
                                width: 16; height: 16; radius: 8
                                anchors.top: parent.top; anchors.right: parent.right
                                anchors.topMargin: 4; anchors.rightMargin: 4
                                color: fp.gilt4; border.color: fp.wine2; border.width: 1
                                Text { anchors.centerIn: parent; text: "\u2713"; color: fp.wine1; font.bold: true; font.pixelSize: SetTheme.sm - 1 }
                            }
                            TapHandler { id: wovenTap; onTapped: irisCol.applyWoven() }
                            HoverHandler { id: wovenHover }
                        }
                    }
                    Text {
                        visible: wovenCard.visible
                        leftPadding: 10; bottomPadding: 8
                        width: parent.width - 20; wrapMode: Text.WordWrap
                        text: "\u2726 Woven: " + (irisCol.wallPicks.length ? irisCol.wallPicks[0].name : "the first palette") + "'s pattern re-hued to your wallpaper's own colours, lightness kept so every contrast holds. Tap any curated card to return to it. Any palette picked here also inks all shell text in your wallpaper's colour."
                        color: fp.inkSoft; font.family: fp.serif; font.italic: true
                        font.pixelSize: SetTheme.sm - 1
                    }
                }

                Repeater {
                    model: irisCol.sections
                    delegate: Column {
                        id: sectionCol
                        property var sec: modelData
                        width: irisCol.width; spacing: 0

                        Rectangle {
                            width: parent.width; height: 32
                            color: Qt.rgba(fp.gilt2.r, fp.gilt2.g, fp.gilt2.b, 0.30)
                            border.color: fp.gilt4; border.width: 1
                            Text {
                                anchors.verticalCenter: parent.verticalCenter; leftPadding: 10
                                text: sectionCol.sec.label.toUpperCase()
                                color: fp.label; font.family: fp.display; font.bold: true
                                font.pixelSize: SetTheme.sm; font.letterSpacing: 1.5
                            }
                        }

                        Repeater {
                            model: irisCol.catsForSection(sectionCol.sec.dark)
                            delegate: Column {
                                id: catCol
                                property var cat: modelData
                                width: sectionCol.width; spacing: 0

                                Rectangle {
                                    width: parent.width; height: 26
                                    color: Qt.rgba(fp.gilt1.r, fp.gilt1.g, fp.gilt1.b, 0.18)
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter; leftPadding: 10
                                        text: catCol.cat.label.toUpperCase()
                                        color: fp.label; font.family: fp.titles
                                        font.pixelSize: SetTheme.sm - 1; font.letterSpacing: 1.2
                                    }
                                }

                                Flow {
                                    width: parent.width; spacing: 6
                                    topPadding: 6; bottomPadding: 6; leftPadding: 6; rightPadding: 6
                                    Repeater {
                                        model: catCol.cat.items
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
                                                // Small glass-glint dot added 2026-09-23: these swatches
                                                // were flat Qt.lighter/darker fills with zero highlight —
                                                // exactly the "no 3D shading" flatness issue, at card-
                                                // preview scale. A tiny upper-left specular catch-light
                                                // (same corner-glint idea NCDEGlassSurface/KithGlass both
                                                // use) is enough to read as a bead of glass, not a sticker.
                                                Rectangle {
                                                    id: swatch
                                                    width: 14; height: 14; radius: 7
                                                    // The palette's REAL colours where the preset carries them
                                                    // (ground, surface, accent, border, ink) — the old dots were
                                                    // five lighter/darker shades of the accent, so every palette
                                                    // with a similar accent looked identical. Falls back per-dot
                                                    // to the old shade if a field isn't present.
                                                    color: {
                                                        var p = irisCard.pd, c = Qt.color(p.accent)
                                                        var real = [p.panelBg, p.surface, p.accent, p.border, p.ink][index]
                                                        if (real !== undefined && real !== null && real !== "") return real
                                                        if (index === 0) return Qt.lighter(c, 3.0)
                                                        if (index === 1) return Qt.lighter(c, 1.7)
                                                        if (index === 2) return c
                                                        if (index === 3) return Qt.darker(c, 1.8)
                                                        return Qt.darker(c, 3.2)
                                                    }
                                                    border.width: 1
                                                    border.color: Qt.rgba(0, 0, 0, 0.25)
                                                    Rectangle {
                                                        x: swatch.width * 0.20; y: swatch.height * 0.16
                                                        width: swatch.width * 0.34; height: swatch.height * 0.24
                                                        radius: height / 2
                                                        color: Qt.rgba(1, 1, 1, 0.55)
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
                                    TapHandler { id: irisCardTap; onTapped: { irisCol.clearWoven(); if (WallInk.inkOn) WallInk.setInk(false); ncde.applyPreset(irisCard.pd.id); saveTheme(); irisCol.activeName = irisCard.pd.name; notifications.notify("Filigree", "Theme changed: " + irisCard.pd.name, "", 2000) } }
                                    HoverHandler { id: irisCardHover }
                                }
                            }
                        }

                        Item { width: 1; height: 4 }
                            }
                        }
                    }
                }

                Item { width: 1; height: 16 }
            }
        }
    }



    // ── Unified colour picker popup (Glass / Widgets / Type / Sections) ────
    Rectangle {
        id: popScrim
        z: 20
        anchors.fill: parent
        visible: fil._colorPopupOpen
        color: Qt.rgba(0, 0, 0, 0.55)
        // still swallows every tap (nothing reaches the tab beneath); a tap that
        // lands outside the dialog card dismisses — same as Cancel
        TapHandler { onTapped: function(ep) {
            var p = popDialog.mapFromItem(popScrim, ep.position.x, ep.position.y)
            if (p.x < 0 || p.y < 0 || p.x > popDialog.width || p.y > popDialog.height)
                fil._colorPopupOpen = false
        } }

        Rectangle {
            id: popDialog
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
