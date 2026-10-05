import QtQuick 2.15
import QtCore
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Effects 6.5
import Qt.labs.folderlistmodel 2.15

Window {
    id: desktop
    width:   Screen.width
    height:  Screen.height
    visible: true
    flags:   Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnBottomHint | Qt.BypassWindowManagerHint
    color:   ncde.panelBg
    x: 0; y: 0

    property string wallpaperPath: settings.getWallpaper()

    Component.onCompleted: { settings.initWatcher(); foldScriptShift(); loadColorOverrides(); reapplyActivePreset(); irisLiveDebounce.restart() }
    // Script Shift (2026-09-24): one text dial. Older setups spread text size over three
    // values (Text size x UI scale x Accessibility text scale); fold them into
    // fontSizeScale once and retire the other two at 1. A no-op once they're 1.
    function foldScriptShift() {
        var ui  = settings.uiScale > 0 ? settings.uiScale : 1.0
        var acc = settings.accessibilityTextScale > 0 ? settings.accessibilityTextScale : 1.0
        if (Math.abs(ui - 1.0) < 0.001 && Math.abs(acc - 1.0) < 0.001) return
        var f = (settings.fontSizeScale > 0 ? settings.fontSizeScale : 1.0) * ui * acc
        f = Math.max(0.75, Math.min(2.0, Math.round(f * 20) / 20))
        settings.fontSizeScale = f; settings.uiScale = 1.0; settings.accessibilityTextScale = 1.0
        settings.saveFontSettings()
        if (typeof settings.saveAccessibility === "function") settings.saveAccessibility()
        settings.applyFontSettings()
        console.log("NCDE Script Shift: folded text size x" + ui.toFixed(2) + " x" + acc.toFixed(2) + " -> " + f.toFixed(2))
    }

    // ── Iris Chroma preset startup shim (2026-07-15) ───────────────
    // NCDEEngine::loadTheme() restores the active preset's NAME into the
    // "accent" field of active-theme.json (a plain QString field copy — verified
    // in the live binary, offset 0x2d0) but never re-derives the preset's actual
    // colors (m_activePreset, offset 0x300+) that name is supposed to mean.
    // recompute() then runs against whatever m_activePreset the engine was
    // constructed with, so the palette visually reverts on every login/reboot
    // even though the correct preset name round-trips to disk correctly. Only
    // ncde.applyPreset(id) (matched by the preset's id, not its name — verified:
    // applyPreset loops kPresets comparing id, then writes the matched preset's
    // name into this same "accent" field) actually recomputes the real colors.
    // Mirror that one missing step at startup: look up the saved name against
    // the existing 90 presets and reapply the match for real. Never edits
    // kPresets/the presets themselves — read-only lookup, same idiom as
    // loadColorOverrides() above.
    function reapplyActivePreset() {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var j
            try { j = JSON.parse(xhr.responseText) } catch (e) { return }
            if (!j || typeof j.accent !== "string" || j.accent.length === 0) return
            var list = ncde.presets()
            for (var i = 0; i < list.length; i++) {
                if (list[i].name === j.accent) {
                    ncde.applyPreset(list[i].id)
                    reapplyWovenPalette(j.accent)
                    return
                }
            }
        }
        try { xhr.open("GET", "file://" + settings.configBase + "active-theme.json"); xhr.send() }
        catch (e) { /* no config / read-only fs — nothing to restore, stay quiet */ }
    }

    // Woven-from-wallpaper palette (Filigree > Iris Chroma, 2026-09-24): a
    // curated preset re-hued to the wallpaper, stored as the template's name +
    // the rotated engine tokens. Replayed only on top of that same template;
    // accent/border/glow come back through loadColorOverrides() as before.
    function reapplyWovenPalette(templateName) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var w
            try { w = JSON.parse(xhr.responseText) } catch (e) { return }
            if (!w || w.active !== true || w.template !== templateName || !w.palette) return
            ncde.applyPalette(w.palette)
        }
        try { xhr.open("GET", "file://" + settings.configBase + "wallpaper-palette.json"); xhr.send() }
        catch (e) { /* no woven palette — the curated preset stands */ }
    }

    // ── Color-override startup shim (2026-07-12) ──────────────────
    // Settings→Style Manager SAVES manual hex overrides (Accent/Glass/Glow/Border)
    // to ~/.config/ncde/color-overrides.json, but LaPivot has no load path — so the
    // user's custom colors vanished on every relog. Replay them at shell startup:
    // mirror NCDEStyleManager.applyColorOverride's exact engine calls (setOverride*
    // + settings.*Override), minus the save (we are LOADING, not saving). Reads via
    // XMLHttpRequest file:// — the same idiom WeatherLive.qml uses for config. Inert
    // when the file is missing/empty/malformed or a key is blank (the common case).
    function loadColorOverrides() {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var j
            try { j = JSON.parse(xhr.responseText) } catch (e) { return }
            if (!j || typeof j !== "object") return
            function apply(key, fn) {
                var v = j[key]
                if (typeof v === "string" && v.length > 0) fn(v)
            }
            apply("accentOverride",      function(h){ ncde.setOverrideAccent(h);      settings.accentOverride = h })
            apply("accentMutedOverride", function(h){ ncde.setOverrideAccentMuted(h); settings.accentMutedOverride = h })
            apply("glowOverride",        function(h){ ncde.setOverrideGlow(h);        settings.glowOverride = h })
            apply("borderOverride",      function(h){ ncde.setOverrideBorder(h);      settings.borderOverride = h })
        }
        try { xhr.open("GET", "file://" + settings.configBase + "color-overrides.json"); xhr.send() }
        catch (e) { /* no config / read-only fs — nothing to restore, stay quiet */ }
    }

    // ── Kith cursor follows Iris Chroma + one size everywhere (2026-09-24) ──
    // CursorManager's Kith art is a fixed glass-blue baked into LaPivot, and the
    // shell's own window got a size-32 arrow at login while apps used the Input-tab
    // size. ncde-kith-tint (beside this file) re-tints the Kith theme and rebinds
    // every live Kith cursor on the X server to the accent at the Input-tab size.
    // Feed it the accent whenever the palette settles. XHR PUT doesn't truncate,
    // so pad to a fixed width like WallInk (trailing spaces are JSON-safe).
    property color kithAccent: ncde.accent
    onKithAccentChanged: cursorTintDebounce.restart()
    function writeCursorTint() {
        var s = JSON.stringify({ accent: "" + kithAccent, tint: true })
        while (s.length < 96) s += " "
        var x = new XMLHttpRequest()
        try { x.open("PUT", "file://" + settings.configBase + "cursor-tint.json"); x.send(s) } catch (e) { }
    }
    Timer { id: cursorTintDebounce; interval: 400; onTriggered: desktop.writeCursorTint() }
    Timer {
        interval: 2500; running: true; repeat: false    // after the preset/woven replay
        onTriggered: { desktop.writeCursorTint(); launcher.launchExec(settings.assetBase + "ncde-kith-tint") }
    }

    // ── Iris bridge (2026-09-25): the palette reaches GTK apps + notification cards ──
    // The engine only rewrites GTK's _accent.css (with a stale wallpaper accent) and
    // dunst ran its stock grey config. Hand the live tokens to ncde-iris-bridge, which
    // re-hues the GTK palette files and the operator's Mucha notification card from
    // them (and applies Notifications > Position to dunst). Same padded-PUT +
    // launchExec idiom as the Kith tint above. Anything in the signature changing
    // (Iris click, wallpaper ink, fonts, Script Shift, position) re-runs it.
    function _irisHex(c) {
        function h2(v) { var s = Math.round(Math.min(1, Math.max(0, v)) * 255).toString(16); return s.length < 2 ? "0" + s : s }
        return "#" + h2(c.r) + h2(c.g) + h2(c.b)
    }
    readonly property var irisBridgeTokens: ({
        mode: ncde.darkMode ? "dark" : "light",
        accent: _irisHex(ncde.accent), glow: _irisHex(ncde.glow),
        panelBg: _irisHex(ncde.panelBg), surface: _irisHex(ncde.surface),
        surfaceAlt: _irisHex(ncde.surfaceAlt), popupBg: _irisHex(ncde.popupBg),
        border: _irisHex(ncde.border), text: _irisHex(WallInk.inked(ncde.panelText)),
        gilt3: _irisHex(ncde.gilt3), gilt4: _irisHex(ncde.gilt4),
        wine4: _irisHex(ncde.wine4), verd: _irisHex(ncde.verd),
        bodyFont: "" + ncde.bodyFont, titleFont: "" + ncde.titleFont,
        fontPx: theme.fontMedium,            // Script Shift moved: re-run (the bridge reads fonts.json)
        notifPosition: settings.notifPosition !== undefined ? settings.notifPosition : 1,
        dockW: leftDock.width, topH: 28, bottomH: 28
    })
    onIrisBridgeTokensChanged: irisBridgeDebounce.restart()
    function writeIrisBridge() {
        var s = JSON.stringify(irisBridgeTokens)
        while (s.length < 1024) s += " "     // XHR PUT doesn't truncate: fixed width
        var x = new XMLHttpRequest()
        try { x.open("PUT", "file://" + settings.configBase + "iris-bridge.json"); x.send(s) } catch (e) { return }
        launcher.launchExec(settings.assetBase + "ncde-iris-bridge")
    }
    Timer { id: irisBridgeDebounce; interval: 600; onTriggered: desktop.writeIrisBridge() }

    // ── Iris live (2026-09-26): one palette for every NCDE app ──────────────
    // Operator: "Iris Chroma palettes control everything — it is global, same as
    // fonts." Each house app (Verve, Abacus, NCDE Command, Magpie, Hummingbird…)
    // carries its OWN frozen copy of NCDEEngine from its June/July build, with no
    // source to rebuild — so Iris/Filigree clicks never reached them (they sat on
    // the July teal). The shell's engine is the one Iris and Filigree drive: it
    // publishes every token NCDEKit reads to ~/.config/ncde/iris-live.json, and
    // NCDEKit in every app outside the shell follows that file (light + dark).
    readonly property var irisLiveNames: [
        "panelBg", "panelBg2", "surface", "surface2", "surfaceAlt", "surfaceHi", "popupBg",
        "gilt0", "gilt1", "gilt2", "gilt3", "gilt4", "gilt5",
        "wine1", "wine2", "wine3", "wine4",
        "ink", "inkSoft", "inkDim", "panelText", "accent", "glow", "border",
        "verd", "cer", "rose", "lamp", "lineWine", "lineSage", "lineOchre", "lineCer" ]
    readonly property var irisLiveFonts: [ "displayFont", "titleFont", "bodyFont", "fellFont", "garFont", "monoFont" ]
    function _irisHexA(c) {
        var a = c.a === undefined ? 1 : c.a
        var h = _irisHex(c)
        if (a >= 0.999) return h
        var s = Math.round(Math.max(0, a) * 255).toString(16)
        return "#" + (s.length < 2 ? "0" + s : s) + h.substring(1)
    }
    readonly property var irisLiveTokens: {
        var o = { darkMode: !!ncde.darkMode }
        for (var i = 0; i < irisLiveNames.length; i++) {
            var v = ncde[irisLiveNames[i]]
            if (v === undefined || v === null || v === "") continue
            o[irisLiveNames[i]] = _irisHexA(typeof v === "string" ? Qt.color(v) : v)
        }
        for (var j = 0; j < irisLiveFonts.length; j++) {
            var f = ncde[irisLiveFonts[j]]
            if (f !== undefined && f !== null && ("" + f) !== "") o[irisLiveFonts[j]] = "" + f
        }
        return o
    }
    onIrisLiveTokensChanged: irisLiveDebounce.restart()
    function writeIrisLive() {
        var s = JSON.stringify(irisLiveTokens)
        while (s.length < 4096) s += " "     // XHR PUT doesn't truncate: fixed width
        var x = new XMLHttpRequest()
        try { x.open("PUT", "file://" + settings.configBase + "iris-live.json"); x.send(s) } catch (e) { }
    }
    // Super tap from anywhere: the window manager grabs it on the root (W15), so it works while an
    // app has focus too; the Keys handler below only ever saw keys while the desktop had focus
    Connections {
        target: windowMgr
        function onExposeToggleRequested() { exposeOverlay.visible = !exposeOverlay.visible }
    }

    // ── Minimize requests from self-decorated apps ──────────────────────────
    // Steam, games and Electron apps send the ICCCM/EWMH iconify request from
    // their own title bar. The window manager handles it directly (W5), so the
    // old 250 ms file poll + ncde-iconify-bridge helper (2026-09-26) are gone.

    Timer { id: irisLiveDebounce; interval: 150; onTriggered: desktop.writeIrisLive() }
    Connections { target: ncde; function onThemeChanged() { irisLiveDebounce.restart() } }
    // the engine rewrites GTK's _accent.css when it samples a wallpaper: re-assert after it
    Connections {
        target: settings
        function onWallpaperChanged(path) { irisBridgeDebounce.restart() }
    }

    // ── Live config updates from ncde_settings ────────────────────
    Connections {
        target: settings
        function onWallpaperChanged(path) { console.log("[NCDE] main.qml onWallpaperChanged:", path); desktop.wallpaperPath = path }
        function onSlideshowAdvanced(path) { ncde.sampleWallpaper(path) }
    }
    Connections {
        target: animPolicy
        function onPolicyChanged() { settings.setSlideshowPaused(animPolicy.screenIdle) }
    }

    // ── Window manager signals ────────────────────────────────────
    Connections {
        target: windowMgr
        function onWindowAdded(winId, x, y, w, h, title, appId) {}
        function onWindowRemoved(winId) {}
    }

    // ── Autostart ─────────────────────────────────────────────────
    Timer {
        interval: 3000; running: true; repeat: false
        onTriggered: {
            var raw = settings.loadAutostart()
            try {
                var arr = JSON.parse(raw)
                for (var i = 0; i < arr.length; i++)
                    if (arr[i].enabled && arr[i].command)
                        launcher.launchExec(arr[i].command)
            } catch(e) {}
        }
    }

    // ── Keyboard shortcuts ────────────────────────────────────────
    property bool altPressed: false
    property bool altInterrupted: false

    // Keys is an Item-only attached property — on the Window root it never
    // attached ("Could not attach Keys property" once per login) and every
    // shortcut here (Alt+F4, F1 Exposé, Ctrl+Alt+R recovery) was silently
    // dead. A focused child Item is the attachment point; document scope
    // keeps every identifier below resolving exactly as before.
    Item {
        id: shellKeys
        anchors.fill: parent
        focus: true
        Keys.onPressed: (event) => {
            if (event.key === Qt.Key_F4 && (event.modifiers & Qt.AltModifier)) {
                var idx = windowMgr.activeIndex
                if (idx >= 0) {
                    var entry = windowMgr.index(idx, 0)
                    windowMgr.closeWindow(windowMgr.data(entry, 0x101))
                }
                event.accepted = true; return
            }
            if (event.key === Qt.Key_F1) { exposeOverlay.visible = !exposeOverlay.visible; event.accepted = true; return }
            // Ctrl+Alt+R on a LIVE desktop -> launch the System Restore GUI (matches
            // ncde-recovery.desktop: sudo -n /usr/local/bin/ncde-recovery). Was bound to
            // Key_T + "recovery-native" (a command that doesn't exist) -> did nothing.
            // 2026-09-23: switched from pkexec to a scoped sudoers NOPASSWD entry
            // (/etc/sudoers.d/ncde-recovery) — pkexec had no matching polkit rule, so
            // it fell through to the default org.freedesktop.policykit.pkexec.run
            // action and prompted for a password BEFORE the app's own PAM ncde-restore
            // admin-seal prompted again. The .desktop file's header comment always said
            // "the in-app seal is the only password asked" — sudo -n with a NOPASSWD
            // rule scoped to this exact binary is what actually delivers that.
            if (event.key === Qt.Key_R && (event.modifiers & Qt.ControlModifier) && (event.modifiers & Qt.AltModifier)) {
                launcher.launchExec("sudo -n /usr/local/bin/ncde-recovery"); event.accepted = true; return
            }
            if (event.key === Qt.Key_Super_L || event.key === Qt.Key_Super_R || event.key === Qt.Key_Meta) {
                if (!altPressed) { exposeOverlay.visible = !exposeOverlay.visible; event.accepted = true; return }
            }
            if (event.key === Qt.Key_Alt) { altPressed = true; altInterrupted = false; event.accepted = false }
            else if (altPressed) { altInterrupted = true; event.accepted = false }
        }
        Keys.onReleased: (event) => {
            if ((event.key === Qt.Key_Alt || event.key === Qt.Key_Meta) && altPressed && !altInterrupted) {
                altPressed = false; exposeOverlay.visible = true
            } else { altPressed = false; altInterrupted = false }
            event.accepted = false
        }
    }

    // ── Vesper threat-trigger (2026-07-05 audit) ──────────────────
    // "Threat-triggered popup only" (vesper.md) had NO trigger: nothing anywhere
    // launched the green-phosphor UI when the engines found something. While
    // Vesper is armed, the shell polls the brain and pops ncde-vesper once per
    // threat episode (the wrapper is single-instance; re-arms when findings clear).
    Timer {
        id: vesperWatch
        interval: 15000; repeat: true
        running: typeof settings !== "undefined" && settings.kickassArmed === true
        property bool popped: false
        onTriggered: {
            var x = new XMLHttpRequest()
            x.onreadystatechange = function() {
                if (x.readyState !== XMLHttpRequest.DONE) return
                if (x.status !== 200) return          // brain not up — stay quiet
                var n = 0
                try { n = (JSON.parse(x.responseText).findings || []).length } catch (e) {}
                if (n > 0 && !vesperWatch.popped) {
                    vesperWatch.popped = true
                    launcher.launchExec("ncde-vesper")
                } else if (n === 0) {
                    vesperWatch.popped = false
                }
            }
            x.open("GET", "http://127.0.0.1:8077/findings"); x.send()
        }
    }

    // ── Wallpaper ─────────────────────────────────────────────────
    Rectangle { anchors.fill: parent; color: ncde.panelBg; z: 0 }

    Image {
        id: wallpaperImg
        anchors.fill: parent; z: 0
        source: desktop.wallpaperPath !== "" ? "file://" + desktop.wallpaperPath : ""
        fillMode: settings.fitMode === "fit"    ? Image.PreserveAspectFit
                : settings.fitMode === "center" ? Image.Pad
                : settings.fitMode === "tile"   ? Image.Tile
                : Image.PreserveAspectCrop
        visible: desktop.wallpaperPath !== ""

        TapHandler {
            acceptedButtons: Qt.RightButton
            onTapped: (eventPoint) => {
                var pos = eventPoint.position
                desktopMenu.x = Math.min(pos.x, desktop.width  - desktopMenu.width  - 4)
                desktopMenu.y = Math.min(pos.y, desktop.height - desktopMenu.height - 4)
                desktopMenu.visible = true
            }
        }
        TapHandler {
            acceptedButtons: Qt.LeftButton
            onTapped: {
                desktopMenu.visible = false
                appMenu.visible = false
            }
        }
    }

    // ── Widget backdrop ───────────────────────────────────────────
    Rectangle {
        anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: 380; z: 0
        gradient: Gradient { orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: Qt.rgba(0,0,0,0.0)  }
            GradientStop { position: 1.0; color: Qt.rgba(0,0,0,0.42) } }
    }

    // ── Desktop Widget ────────────────────────────────────────────
    DesktopWidget { id: desktopWidget; wallpaperSource: wallpaperImg }

    // ── Left Dock ─────────────────────────────────────────────────
    Dock { id: leftDock; wallpaperSource: wallpaperImg }

    Item {
        id: dockRevealStrip; x: 0; y: 40; width: 4; height: parent.height - 80; z: 601
        HoverHandler { onHoveredChanged: { intellihide.dockHovered = hovered; if (hovered) intellihide.revealAll() } }
    }

    // ── Intellihide Controller ────────────────────────────────────
    Intellihide { id: intellihide }

    Item {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 8
        z: 490
        HoverHandler {
            onHoveredChanged: {
                intellihide.topHovered = hovered
                if (hovered) intellihide.revealAll()
                else intellihide.scheduleHide()
            }
        }
    }

    // ── Top Panel ─────────────────────────────────────────────────
    TopPanel {
        id: topPanel
        wallpaperSource: wallpaperImg
        appMenuTarget: appMenu
        settingsPanelTarget: settingsPanel
        menuLayer: gliaDropMenu
        ledgerTarget: bottomPanelItem.ledger
    }

    // ── App Menu ──────────────────────────────────────────────────
    AppMenu { id: appMenu }

    // ── Settings Panel ────────────────────────────────────────────
    SettingsPanel { id: settingsPanel }

    // ── Desktop right-click menu ──────────────────────────────────
    DesktopMenu { id: desktopMenu; settingsPanelTarget: settingsPanel }

    // ── Notification overlay ──────────────────────────────────────
    Column {
        visible: !settings.dnd
        x: settings.notifPosition === 0 ? 12 : parent.width - width - 12
        y: settings.notifPosition === 2 ? parent.height - height - 40 : 40
        spacing: 6; z: 1100
        Repeater { model: notifications.notifications
            Rectangle { width:320;height:notifCol2.height+20;color:ncde.popupBg;border.color:ncde.border;border.width:1;radius:8
                id:notifCard2;property bool dismissing:false;property int notifId:modelData.id
                NumberAnimation on x{id:si2;from:340;to:0;duration:250;easing.type:Easing.OutCubic}
                NumberAnimation on x{id:so2;to:340;duration:180;easing.type:Easing.InCubic;running:false;onStopped:if(notifCard2.dismissing)notifications.dismiss(notifCard2.notifId)}
                // Honor the sender's expire_timeout (fdo spec): >0 = ms, 0 = never expire.
                Timer{interval:modelData.timeout>0?modelData.timeout:5000;running:modelData.timeout!==0;repeat:false
                    onTriggered:{notifCard2.dismissing=true;so2.start()}}
                Column {
                    id: notifCol2
                    anchors { left: parent.left; right: parent.right; top: parent.top; margins: 10 }
                    spacing: 4
                    // fdo senders pass icon *names* ("mail-unread") — only short glyphs draw
                    Row{width:parent.width;spacing:6
                        Text{text:modelData.icon.length<=2?modelData.icon:"";visible:text!=="";font.pixelSize:Math.round(16 * (theme.fontMedium / 13.0));anchors.verticalCenter:parent.verticalCenter}
                        Text{text:modelData.title;color:ncde.panelText;font.pixelSize:Math.round(12 * (theme.fontMedium / 13.0));font.bold:true;font.family:ncde.titleFont;anchors.verticalCenter:parent.verticalCenter;width:parent.width-60;elide:Text.ElideRight}}
                    Text{text:modelData.body;color:ncde.accent;font.pixelSize:Math.round(11 * (theme.fontMedium / 13.0));font.family:ncde.bodyFont;width:parent.width;wrapMode:Text.WordWrap}}
                Item{width:24;height:24;anchors.top:parent.top;anchors.right:parent.right;anchors.margins:2
                    Text{text:"✕";color:ncde.border;font.pixelSize:Math.round(12 * (theme.fontMedium / 13.0));anchors.centerIn:parent}
                    TapHandler{onTapped:{notifCard2.dismissing=true;so2.start()}}} } }
    }

    // ── HUD / Expose — own top-level Window so it renders above frame windows ──
    Window {
        id: exposeWindow
        flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint | Qt.WindowStaysOnTopHint
        x: 0; y: 0
        width: Screen.width; height: Screen.height
        color: "transparent"

        NCDEExpose {
            id: exposeOverlay
            anchors.fill: parent
            wallpaperUrl: wallpaperImg.visible ? wallpaperImg.source : ""
            wallpaperFill: wallpaperImg.fillMode
            onVisibleChanged: exposeWindow.visible = visible
        }
    }

    // ── Screenshot flash ──────────────────────────────────────────
    Rectangle { id:screenshotFlash;anchors.fill:parent;z:2000;color:"white";opacity:0.0;Behavior on opacity{NumberAnimation{duration:80}} }
    Timer { id:screenshotTimer;interval:80;repeat:false;onTriggered:screenshotFlash.opacity=0.0 }

    // ── Fade Curtain for Compositor Restart ───────────────────────
    Window {
        id: fadeCurtain
        flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.BypassWindowManagerHint
        color: "black"
        opacity: 0.0
        width: Screen.width; height: Screen.height
        visible: opacity > 0
        Behavior on opacity { NumberAnimation { duration: 250 } }
    }

    function triggerFade() { fadeCurtain.opacity = 1.0 }
    function triggerUnfade() { fadeCurtain.opacity = 0.0 }

    // ── Tiling Manager + Snap Preview ─────────────────────────────
    TilingManager { id: tilingManager }

    // ── Window decorations — one QQuickWindow per managed window ──
    Instantiator {
        model: windowMgr
        delegate: Window {
            id: frameWin
            // registerFrameWindowQml() only tracks this overlay's own winId for
            // bookkeeping -- it does NOT reparent the real client into it, and
            // NCDEWindowManager::manage() never reparents either (verified,
            // disassembled both). So hiding MotifFrame's paint alone still left
            // this overlay window sitting over the client's play area with its
            // default full-rect input region, still eating clicks/keys meant
            // for the game underneath -- steam/gamescope run their own window
            // management and this overlay was fighting it. WindowTransparentForInput
            // punches an empty input shape so the overlay never intercepts
            // anything for game windows, regardless of stacking.
            flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint | Qt.WindowDoesNotAcceptFocus
                   | (noFrame ? Qt.WindowTransparentForInput : 0)
            color: "transparent"
            x: model.x - 24
            y: model.y - 44
            width:  model.w + 48
            height: model.h + 82
            visible: registered && !model.minimized
            property bool registered: false
            property bool isSettings: model.appId === "ncde settings"
            // TilingManager.qml's own comments say "keep in sync with main.qml
            // isGame" for exactly this appId check, but it was never actually
            // added here -- Steam/Proton games and gamescope were exempted
            // from grid-tiling but still got a full Motif frame/decoration.
            property bool isGame: (model.appId || "").indexOf("steam_app_") === 0
                                  || model.appId === "gamescope"
            // Steam's OWN client window (appId "steam"/"steamwebhelper" -- NOT a
            // steam_app_*/gamescope game) draws its own titlebar/min/max/close
            // inside its content. Operator, 2026-07-19: "steam should not have a
            // MotifFrame, it has its own window decoration." Previously only
            // isGame was exempted, so Steam's own client still got a MotifFrame
            // overlay sitting on top of it -- eating the drag/button input meant
            // for Steam's own chrome (Steam's controls never did anything, and
            // the overlay's own titlebar had nothing underneath it to move).
            // Folded Steam into the same no-frame/full-input-passthrough
            // treatment as games, edge-to-edge (operator, same session: "edge
            // to edge"). NOTE: deliberately NOT part of TilingManager.qml's
            // isGame grid-exclusion check -- Steam has no MotifFrame Amethyst
            // button to ever call setTiled(true), so it can't reach the grid in
            // practice; no change needed there.
            property bool isSteamClient: model.appId === "steam" || model.appId === "steamwebhelper"
            property bool noFrame: isGame || isSteamClient

            // Some apps (Steam confirmed live, 2026-07-19, operator: "steam is not
            // full screen at all.. it has a gap from the top of the screen") restore
            // their OWN remembered window geometry shortly after mapping, landing
            // back at a windowed size/position instead of the true fullscreen the
            // Component.onCompleted below set once at window creation. noFrame
            // windows have no MotifFrame watching for this drift and correcting it
            // (MotifFrame is invisible/inert for them -- see its `visible` binding
            // below) -- this file has to catch it directly. Same technique as
            // MotifFrame.qml's own 2026-07-17 GIMP fix (snapMaximizedGeometry --
            // originally live-only, clobbered by the 2026-07-21 patch deploy,
            // reconstructed and FOLDED INTO THIS PATCH 2026-07-21; that gap is
            // closed): compare against the enforced geometry and snap back
            // ONLY on an actual mismatch, driven by frameWin's own x/y/width/height
            // bindings (which mirror model.x/y/w/h) -- never a poll/timer, so this
            // cannot cause repeated movement or visible flicker (flashing is a
            // seizure-safety issue on this system, not cosmetic).
            function snapNoFrameFullscreen() {
                if (!noFrame || isSettings) return
                var sw = windowMgr.screenWidth()
                var sh = windowMgr.screenHeight()
                if (model.x !== 0 || model.y !== 0 || model.w !== sw || model.h !== sh) {
                    windowMgr.moveWindow(model.winId, 0, 0)
                    windowMgr.resizeWindow(model.winId, sw, sh)
                }
            }
            onXChanged: snapNoFrameFullscreen()
            onYChanged: snapNoFrameFullscreen()
            onWidthChanged: snapNoFrameFullscreen()
            onHeightChanged: snapNoFrameFullscreen()

            Component.onCompleted: {
                // Stagger frame creation to avoid GLX context thrash
                staggerTimer.interval = Math.min(index * 20, 500)
                staggerTimer.start()
                // CONFIRMED LIVE (operator, 2026-07-15): the steam_app_*/gamescope
                // appId match is correct as-is -- Steam and game windows both
                // frame- and input-fixed. Left as a one-line-per-window-open log
                // (not a flood) in case a future title reports a different appId.
                // 2026-07-19: extended to log isSteamClient/noFrame too, now that
                // the Steam client itself also takes the no-frame path.
                console.log("[NCDE frame] appId='" + (model.appId || "") + "' isGame=" + isGame
                             + " isSteamClient=" + isSteamClient + " noFrame=" + noFrame)

                // "Windows open max" was already the documented design (see
                // MotifFrame's `maximized: true` default and TilingManager's
                // grid-exclusion comment, both operator 2026-06-28/07-06) but
                // nothing ever actually resized a freshly-mapped client to
                // match -- onWindowAdded in this file was an empty stub, and
                // MotifFrame's Component.onCompleted only touched its own
                // local `maximized` flag, never called windowMgr's real
                // move/resize. New windows (and Steam's own client window)
                // were left exactly wherever they placed themselves -- which
                // turned out to be centered, not resized: confirmed live,
                // Steam's window was 1896x1142 at (12,32) on a 1920x1200
                // screen -- (1920-1896)/2=12, (1200-1142)/2=29~32, genuinely
                // centered, just never enlarged to fill the screen. Same
                // mechanism was cutting off Sims 4's game window.
                if (!isSettings) {
                    if (noFrame) {
                        // True fullscreen: exact physical display geometry,
                        // no frame margins at all (games -- and now Steam's
                        // own client, see noFrame above -- already render
                        // with no NCDE decoration -- give them the real
                        // screen, not a screen-minus-chrome inset).
                        windowMgr.setMaximized(model.winId, true)
                        windowMgr.moveWindow(model.winId, 0, 0)
                        windowMgr.resizeWindow(model.winId, windowMgr.screenWidth(), windowMgr.screenHeight())
                    } else {
                        // Same geometry the Green maximize button already
                        // uses (MotifFrame.qml) -- reusing its proven inset
                        // instead of duplicating new numbers.
                        var sw = windowMgr.screenWidth()
                        var sh = windowMgr.screenHeight()
                        var fl = motifDeco.frameLeft, fr = motifDeco.frameRight
                        var th = motifDeco.titleH,    bh = motifDeco.bottomH
                        windowMgr.setMaximized(model.winId, true)
                        windowMgr.moveWindow(model.winId, fl, th)
                        windowMgr.resizeWindow(model.winId, sw - fl - fr, sh - th - bh)
                    }
                }
            }
            Timer {
                id: staggerTimer
                interval: 1; repeat: false
                onTriggered: {
                    registered = true
                    show()
                }
            }

            property bool frameRegistered: false
            onSceneGraphInitialized: {
                if (!frameRegistered) {
                    frameRegistered = true
                    windowMgr.registerFrameWindowQml(model.winId, frameWin)
                }
            }

            Component.onDestruction: {
                windowMgr.destroyFrameWindow(model.winId)
            }

            MotifFrame {
                id: motifDeco
                x: 0; y: 0
                width:  parent.width
                height: parent.height
                winId:       model.winId
                windowTitle: model.title    || "Window"
                windowAppId: model.appId    || ""
                // model.active does not exist (no ActiveRole on windowMgr) — that made isFocused
                // permanently false, killing the Motif glow + stuck a permanent dim overlay on
                // every frame. windowMgr.activeIndex IS live (set on every FOCUS_IN, see
                // NCDEWindowManager.h activateWindow/setActiveIndex) — use it instead.
                isFocused:   index === windowMgr.activeIndex
                isMinimized: model.minimized === true
                isTiled:     model.tiled     === true
                // isMaximized is OWNED LOCALLY by MotifFrame's green/amethyst buttons.
                // The real ncde-wm never sets the `maximized` model role (setMaximized was
                // removed), so binding it here pinned isMaximized to false and re-asserted on
                // every model dataChanged — defeating the amethyst Unmax guard. (s28)
                frameIndex:  index
                windowX:     model.x
                windowY:     model.y
                windowW:     model.w
                windowH:     model.h
                wallpaperRef: wallpaperImg
                visible: !frameWin.isSettings && !frameWin.noFrame
            }
        }
    }

    // ── Glia in-scene menu overlay (above panels, below cursor) ──
    GliaDropMenu {
        id: gliaDropMenu
        anchors.fill: parent
        z: 1500
    }

    // ── Glia click-away dismisser — BELOW panels (z:499 < z:500) ──
    // Panel TapHandlers (z:500) win over this so titles stay clickable
    // while a menu is open. Desktop/wallpaper area clicks dismiss the menu.
    Rectangle {
        anchors.fill: parent
        z: 499
        color: "transparent"
        visible: gliaDropMenu.visible
        TapHandler {
            onTapped: gliaDropMenu.dismissAll()
        }
    }

    // ── Bottom Panel ──────────────────────────────────────────────
    BottomPanel { id: bottomPanelItem; wallpaperSource: wallpaperImg; menuLayer: gliaDropMenu }

    // ── Bottom edge reveal zone — always visible, triggers unified intellihide ──
    Item {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 8; z: 490
        HoverHandler { onHoveredChanged: { if (hovered) intellihide.revealAll() } }
    }

    // ── Dark/Light mode transition fade ──────────────────────────
    NCDEModeTransition { anchors.fill: parent }

    // Kith cursor is now a real X11 hardware cursor (CursorManager, main.cpp) — the
    // QML Canvas overlay + XFixes hide_cursor it depended on are retired.
}
