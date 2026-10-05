import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Effects 6.5
import Qt5Compat.GraphicalEffects
import "mucha-space.js" as Space
import "ncde-color.js" as Col

Item {
    id: topPanel

    property Item wallpaperSource: null
    property Item appMenuTarget: null
    property Item settingsPanelTarget: null
    property Item menuLayer: null
    property Item ledgerTarget: null

    property var _surfaceGlass: null
    Component.onCompleted: {
        _surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("topPanel") : null
    }
    Connections {
        target: ncde
        function onThemeChanged() {
            topPanel._surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("topPanel") : null
        }
    }

    // ── Intellihide reveal strip ───────────────────────────────
    Item {
        id: topPanelRevealStrip; x: 0; y: 0; width: parent.width; height: 4; z: 601
        HoverHandler { onHoveredChanged: { intellihide.topHovered = hovered; if (hovered) intellihide.revealAll() } }
    }

    // GliaDropMenu is top-level (z:1500 in main.qml) and positioned once at
    // open-time. NO-OBSCURE: never auto-hide the panel while any dropdown or
    // tray popup is open — otherwise the button slides out from under its menu.
    // When the panel does hide, dismiss everything so nothing is left orphaned.
    Connections {
        target: intellihide
        function onTopRevealedChanged() {
            if (!intellihide.topRevealed) {
                topGliaBar.close()
                powerMenu.visible = false
                volumePopup.visible = false
                clockCalPopup.visible = false
            }
        }
    }
    // While the slide-out Glia menu is open, pin the panel open.
    Connections {
        target: topPanel.menuLayer
        function onVisibleChanged() {
            if (topPanel.menuLayer && topPanel.menuLayer.visible) {
                intellihide.revealAll(); intellihide.cancelHide()
            }
        }
    }

    // panel-frame.png rows 0-5 and 66-71 are transparent (measured 2026-10-01): the panel may sit
    // so the frame's INK meets the screen edge, never clipped; the rail still floats 7-8 px in.
    readonly property int frameInkPad: 6
    property real panelY: 20 - frameInkPad
    property real _dragStartY: panelY
    function clampPanelY(value) {
        var minY = -topPanelFrame.y - frameInkPad
        var maxY = Math.max(minY, parent.height - (topPanelFrame.y + topPanelFrame.height) + frameInkPad)
        return Math.max(minY, Math.min(value, maxY))
    }

    // Gemini exact full-bleed opaque bar (2026-09-28): replaces floating
    // 28px aero-glass pill (6px margins) with 32px edge-to-edge ground.
    // Canvas painter is byte-identical to GeminiTopPanel.qml bg.
    // Functional children (GliaBar, clockRibbon, trayRibbon, popups) unchanged.
    Item { id: topBezel; property int ring: 0 }

    y: intellihide.topRevealed ? panelY : -(height + 20)
    anchors.left: parent.left; anchors.leftMargin: 47
    anchors.right: parent.right; anchors.rightMargin: 47
    height: 32; z: 500
    Behavior on y {
        enabled: !topPanelDrag.active
        NumberAnimation { duration: 220; easing.type: Easing.OutExpo }
    }
    HoverHandler {
        onHoveredChanged: {
            intellihide.topHovered = hovered
            if (hovered) intellihide.revealAll()
            else intellihide.scheduleHide()
        }
    }
    DragHandler {
        id: topPanelDrag
        enabled: intellihide.topRevealed
        target: null
        acceptedButtons: Qt.LeftButton
        xAxis.enabled: false
        yAxis.enabled: true
        onActiveChanged: if (active) topPanel._dragStartY = topPanel.panelY
        onTranslationChanged: {
            if (active) topPanel.panelY = topPanel.clampPanelY(topPanel._dragStartY + translation.y)
        }
    }

    BorderImage {
        id: topPanelFrame
        x: -47      // glass pill end clears the cap C-curve ink on every row (measured 2026-10-01)
        y: -20
        width: parent.width + 94
        height: 72
        source: "panel-frame.png"
        border { left: 60; right: 60; top: 19; bottom: 19 }
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch
        smooth: true
        z: -1
    }

    // ── Pennant under the N logo (operator 2026-10-01): hangs from the frame's
    // bottom rail directly under the circular N, cords tucked behind the rail
    // (z below the frame). pennant.png = operator art, 111x143. Fades away while
    // the Glia menu drawer is slid out or one of its menus is open, and comes
    // back when the menu furls. Iris: purple art rotated toward the accent.
    Image {
        id: topPennant
        x: { menuRibbon.x; menuRibbon.width; topPanel.width
             return nLogo.mapToItem(topPanel, nLogo.width / 2, 0).x - width / 2 }
        y: topPanelFrame.y + 53 - 6        // frame bottom rail starts at row 53; cords tuck 6 px behind it
        width: 30
        height: Math.round(30 * 143 / 111)
        source: "pennant.png"
        fillMode: Image.PreserveAspectFit
        smooth: true
        mipmap: true
        z: -2
        opacity: (topGliaBar.expanded || topGliaBar.open) ? 0 : 0.95
        Behavior on opacity { NumberAnimation { duration: 180; easing.type: Easing.OutExpo } }
        layer.enabled: true
        layer.effect: HueSaturation {
            hue: { var h = ncde.accent.hslHue - 0.80; return h < -0.5 ? h + 1 : (h > 0.5 ? h - 1 : h) }
        }
    }

    // ── Aero glass pill (restored 2026-09-29, operator: "you removed all my
    // glass") — the 2026-09-28 build had swapped it for an opaque painted
    // ground; this is the July glass block, unchanged.
    NCDEGlassSurface {
        anchors.fill: parent
        backgroundSource: topPanel.wallpaperSource
        specularInset: 0.0
        revealPulse: intellihide.topRevealed
        glintPulse: intellihide.glintPulse
        tint: {
            if (!ncde.presetActive) {
                var g = topPanel._surfaceGlass
                if (g && g["tint"] !== undefined) { var c = Qt.color(g["tint"]); return Qt.rgba(c.r, c.g, c.b, g["shine"] !== undefined ? g["shine"] * 0.36 : 0.18) }
            }
            return Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18)
        }
        glowA: topPanel._surfaceGlass && topPanel._surfaceGlass["glow"] !== undefined ? topPanel._surfaceGlass["glow"] : 0.70
        edge: {
            if (!ncde.presetActive) {
                var g = topPanel._surfaceGlass
                if (g && g["border"] !== undefined) { var c = Qt.color(g["border"]); return Qt.rgba(c.r, c.g, c.b, 0.85) }
            }
            return Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.85)
        }
        glowRim:  !ncde.presetActive && topPanel._surfaceGlass && topPanel._surfaceGlass["glowColor"] !== undefined ? Qt.color(topPanel._surfaceGlass["glowColor"]) : ncde.glow
        glowHalo: !ncde.presetActive && topPanel._surfaceGlass && topPanel._surfaceGlass["glowColor"] !== undefined ? Qt.color(topPanel._surfaceGlass["glowColor"]) : ncde.glow
    }
    // the current wallpaper's shades, for the ribbon panes (read once per wallpaper)
    NCDEWallTones { id: wallTones; source: topPanel.wallpaperSource ? topPanel.wallpaperSource.source : "" }

    // ── Glia global menus + model ─────────────────────────────
    GliaGlobalMenus {
        id: gliaGlobals
        onSettings:   if (topPanel.settingsPanelTarget) topPanel.settingsPanelTarget.visible = !topPanel.settingsPanelTarget.visible
        onSettingsSection: function(label) {
            var p = topPanel.settingsPanelTarget
            if (!p) return
            if (typeof p.openSection === "function") p.openSection(label)
            else p.visible = true
        }
        onHelp:       handbook.show()
        onRunCommand: if (topPanel.appMenuTarget) topPanel.appMenuTarget.visible = !topPanel.appMenuTarget.visible
    }

    GliaMenuModel {
        id: topMenuModel
        mode: "static"
        staticMenus: gliaGlobals.menus
    }

    // GliaTalk v1: feed the focused app's published menus into Glia's bar.
    Connections {
        target: (typeof windowMgr !== "undefined" && windowMgr) ? windowMgr : null
        function onActiveAppMenusChanged() { gliaGlobals.setAppMenusJson(windowMgr.activeAppMenus) }
        function onActiveIndexChanged()    { gliaGlobals.setAppMenusJson(windowMgr.activeAppMenus) }
    }

    Connections {
        target: topMenuModel
        function onActionInvoked(actionId) { gliaGlobals.route(actionId) }
    }

    GliaDocPopup  { id: gliaDoc }
    NCDEHandbook  { id: handbook }
    Connections {
        target: topGliaBar
        function onDocRequested(doc) {
            if (doc === "handbook") handbook.show()
            else gliaDoc.show(doc)
        }
    }
    Connections { target: gliaGlobals; function onAbout() { gliaDoc.show("about-ncde") } }

    // Left: NCDE logo + global menu bar, on a powerline ribbon (2026-09-25).
    // The ribbon's width follows the menu drawer, so when the menus furl it rolls
    // up to the logo with them and unrolls as they slide back out -- riding the
    // drawer's own existing slide, no animation of its own.
    OrnamentRibbon {
        id: menuRibbon
        followsDrawer: true     // menus slide via the GliaBar drawer; don't chase it
        seed: 1
        dir: 1
        tones: wallTones.tones
        anchors.left: parent.left; anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        z: 2

        // Logo + menus share ONE glass segment (2026-09-25), the way the bottom
        // "Leap Frog" + its menus do: as a separate segment the furled menu drawer
        // was 0 px wide, so the moment it began to slide out a second chevron
        // appeared hard against the tail point -- a "double point". In one segment
        // the ribbon simply lengthens with the drawer.
        Row {
            spacing: 0          // a gap here would pop in as the drawer starts to open
            anchors.verticalCenter: parent.verticalCenter

            MuchaIcon {
                id: nLogo
                width: 24; height: 24
                anchors.verticalCenter: parent.verticalCenter
                size: 24
                appName: "bfbpanel"
                accentColor: ncde.accent
                glowColor:   ncde.glow
                TapHandler { onTapped: topGliaBar.toggle() }
            }

            GliaBar {
                id: topGliaBar
                anchors.verticalCenter: parent.verticalCenter
                menuModel: topMenuModel
                collapsible: true
                openUpward: false
                menuLayer: topPanel.menuLayer
                // the drawer slides out from the logo toward the centered clock:
                // cap it so a long menu row can never reach under the clock face
                maxDrawerWidth: Math.max(0, clockRibbon.x - 40)
            }
        }

    }

    // ── Clock cartouche (frame asset, 2026-09-28) ──────────────────────────
    // clock-frame-bar.png (composed from "clock center.png"): gilt corner
    // scrolls, rails and crystal jewels with a transparent middle carrying the
    // time, tonight's moon and the date — the moon sits between them as the
    // centre jewel. Fixed 280x44 (slight overflow above/below the 32px bar,
    // like the Gemini reference) so the frame is always 1:1, never cropped or
    // stretched however the text width varies. Same moon maths and painter as
    // the orrery. Tapping anywhere on it opens the Ledger pop-out; hovering
    // the moon names the phase.
    Item {
        id: clockRibbon
        z: 2
        readonly property color ink: WallInk.inked(settings.topPanelTextColor !== "" ? settings.topPanelTextColor : ncde.gilt4)
        // re-read once a minute, riding the clock's own tick
        readonly property var _now: { var t = widget_data.timeMinute; return new Date() }
        readonly property real moonPhase: {
            var jd = _now.getTime() / 86400000 + 2440587.5
            var d = (jd - 2451549.5) % 29.53058867
            if (d < 0) d += 29.53058867
            return d / 29.53058867
        }
        readonly property string phaseName: {
            var p = moonPhase
            return p < 0.03 || p > 0.97 ? "New moon" : p < 0.22 ? "Waxing crescent" : p < 0.28 ? "First quarter"
                 : p < 0.47 ? "Waxing gibbous" : p < 0.53 ? "Full moon" : p < 0.72 ? "Waning gibbous"
                 : p < 0.78 ? "Last quarter" : "Waning crescent"
        }
        anchors.centerIn: parent
        // hugs its contents: time + moon + date, plus the two carved caps
        width: ribbonRow.width + 2 * 30
        height: parent.height

        // ── Clock cartouche (operator art 2026-09-29, clock-frame-open.png) ──
        // Source plaque ~/Downloads/1790727309287.png (kept in my-project/
        // files as clock-frame-SOURCE-*); its centre filigree lifted out so it
        // is an open frame (clock-frame-open-MASTER.png), then scaled to the
        // bar's own 32px so it sits INSIDE the bar — nothing overlaps the band
        // below (the old 44px frame hung 6px over its medallion). 9-slice: the
        // carved caps (31px) never stretch, only the straight rails do.
        // Iris tint: partial hue rotation toward the accent (gold 0.12 base).
        // Behind text (z:1).
        BorderImage {
            id: clockFrame
            anchors.fill: parent
            source: "clock-frame-open.png"
            border { left: 31; right: 31; top: 0; bottom: 0 }
            horizontalTileMode: BorderImage.Stretch
            verticalTileMode: BorderImage.Stretch
            smooth: true
            opacity: 0.95
            z: 1
            layer.enabled: true
            layer.effect: HueSaturation {
                hue: (ncde.accent.hslHue - 0.12) * 0.6
                saturation: -0.1
            }
        }

        Row {
            id: ribbonRow
            anchors.centerIn: parent; spacing: 9
            z: 2
            // 2026-09-25: lining, tabular figures ("11" and "31" sat at different
            // heights/widths in old-style numerals) and no letter-spacing on the pair,
            // so HH : MM reads evenly spaced
            Row {
                id: panelClock
                spacing: 2; anchors.verticalCenter: parent.verticalCenter
                Text { text: widget_data.timeHour; color: clockRibbon.ink; font.pixelSize: theme.fontLarge; font.bold: true; font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: 0; font.features: { "lnum": 1, "tnum": 1 }; anchors.verticalCenter: parent.verticalCenter }
                Text { text: ":"; color: clockRibbon.ink; font.pixelSize: theme.fontLarge; font.bold: true; font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: 0; anchors.verticalCenter: parent.verticalCenter; anchors.verticalCenterOffset: -1
                       opacity: widget_data.colonOn ? 1.0 : 0.2; Behavior on opacity { NumberAnimation { duration: 100 } } }
                Text { text: widget_data.timeMinute; color: clockRibbon.ink; font.pixelSize: theme.fontLarge; font.bold: true; font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: 0; font.features: { "lnum": 1, "tnum": 1 }; anchors.verticalCenter: parent.verticalCenter }
                Text { text: widget_data.timeAMPM; color: clockRibbon.ink; font.pixelSize: theme.fontSmall; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing; anchors.verticalCenter: parent.verticalCenter; leftPadding: 3 }
            }
            Canvas {
                id: moonDisc
                width: 14; height: 14
                anchors.verticalCenter: parent.verticalCenter
                renderStrategy: Canvas.Cooperative
                property real phase: clockRibbon.moonPhase
                onPhaseChanged: requestPaint()
                Connections { target: ncde; function onThemeChanged() { moonDisc.requestPaint() } }
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.reset()
                    Space.paintMoon(ctx, width / 2, height / 2, 5.5, phase, ncde.glow, Col.css(ncde.gilt4))
                }
                HoverHandler { id: moonHover }
                ToolTip.visible: moonHover.hovered
                ToolTip.delay: 600
                ToolTip.text: clockRibbon.phaseName
            }
            Text {
                text: Qt.formatDate(clockRibbon._now, "ddd d MMM")
                color: clockRibbon.ink
                font.pixelSize: 12; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic
                font.letterSpacing: 0; font.features: { "lnum": 1, "tnum": 1 }
                anchors.verticalCenter: parent.verticalCenter
                style: theme.textStyle; styleColor: theme.textStyleColor
            }
        }
        TapHandler { onTapped: clockCalPopup.visible = !clockCalPopup.visible }
    }

    // Leap Frog Ledger clock drop-down (Ledger's own month+agenda pop-out)
    // NO-OBSCURE: raised to z:1400 (above dock 600/AppMenu), pins panel open while visible.
    ClockCalendarPopup {
        id: clockCalPopup
        visible: false
        anchors.horizontalCenter: clockRibbon.horizontalCenter
        anchors.top: parent.bottom; anchors.topMargin: 2 + topBezel.ring
        z: 1400
        onVisibleChanged: { if (visible) { intellihide.revealAll(); intellihide.cancelHide() } else if (!volumePopup.visible && !powerMenu.visible) intellihide.scheduleHide() }
        onCloseRequested: visible = false
        onOpenFull: { visible = false; if (topPanel.ledgerTarget) topPanel.ledgerTarget.openFull() }
        // 2026-07-21: Quick add opens the editor on the selected day; tapping an
        // agenda entry opens THAT appointment (was: both just opened the window).
        onQuickAdd: function(d) { visible = false; if (topPanel.ledgerTarget) { topPanel.ledgerTarget.openFull(); topPanel.ledgerTarget.editorDlg.openNew(d, 9*60) } }
        onOpenAppt: function(apptId) { visible = false; if (topPanel.ledgerTarget) { topPanel.ledgerTarget.openFull(); topPanel.ledgerTarget.editAppt(apptId) } }
    }

    // Right: tray, on a powerline ribbon (2026-09-25): network, volume, settings,
    // battery and power each get their own glass segment; the gilt came chevrons
    // between them replace the old 1px divider lines
    OrnamentRibbon {
        id: trayRibbon
        seed: 2
        dir: -1
        tones: wallTones.tones
        anchors.right: parent.right; anchors.rightMargin: 4; anchors.verticalCenter: parent.verticalCenter
        z: 2
        NCDEIcon { size: 16; type: widget_data.networkUp ? "network-up" : "network-down"; accentColor: ncde.accent; glowColor: ncde.glow; bgColor: ncde.panelBg; textColor: ncde.gilt4; anchors.verticalCenter: parent.verticalCenter }
        Row {
            spacing: 3; anchors.verticalCenter: parent.verticalCenter
            NCDEIcon { size: 14; type: widget_data.muted ? "volume-muted" : widget_data.volume > 50 ? "volume-high" : "volume-low"
                accentColor: ncde.accent; glowColor: ncde.glow; bgColor: ncde.panelBg; textColor: ncde.gilt4; anchors.verticalCenter: parent.verticalCenter
                TapHandler { onTapped: widget_data.toggleMute() } }
            Text {
                text: widget_data.muted ? "—" : widget_data.volume+"%"
                color: WallInk.inked(settings.topPanelTextColor !== "" ? settings.topPanelTextColor : ncde.gilt4)
                // Fixed size (operator, 2026-07-15): the top-panel tray is a status
                // strip, not document text -- Fonts tab scale must never resize it,
                // same as the NCDEIcon glyphs it sits next to (16/14px, always fixed).
                font.pixelSize: 12; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: 0; font.features: { "lnum": 1, "tnum": 1 }; anchors.verticalCenter: parent.verticalCenter   // 2026-09-25: size stays fixed; no letter-spacing, lining figures, so "100%" reads as one number
                style: theme.textStyle; styleColor: theme.textStyleColor
                layer.enabled: theme.textShadowEnabled
                layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                    shadowBlur: theme.textShadowRadius / 32.0
                    shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
                TapHandler { onTapped: volumePopup.visible = !volumePopup.visible }
            }
        }
        Text {
            // Fixed size (operator, 2026-07-15): tray status icon, not document text --
            // see the volume-% note above, same reasoning applies to gear/power.
            text: "⚙"; color: WallInk.inked(settings.topPanelTextColor !== "" ? settings.topPanelTextColor : ncde.gilt4); font.pixelSize: 16; anchors.verticalCenter: parent.verticalCenter
            style: theme.textStyle; styleColor: theme.textStyleColor
            layer.enabled: theme.textShadowEnabled
            layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                shadowBlur: theme.textShadowRadius / 32.0
                shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
            TapHandler { onTapped: if (topPanel.settingsPanelTarget) topPanel.settingsPanelTarget.visible = !topPanel.settingsPanelTarget.visible }
        }
        Row {
            visible: widget_data.hasBattery
            spacing: 3; anchors.verticalCenter: parent.verticalCenter
            NCDEIcon {
                size: 14
                type: widget_data.batteryCharging ? "battery-charging"
                    : widget_data.batteryLevel >= 80 ? "battery-full"
                    : widget_data.batteryLevel >= 50 ? "battery-high"
                    : widget_data.batteryLevel >= 20 ? "battery-mid"
                    : "battery-low"
                accentColor: ncde.accent; glowColor: ncde.glow; bgColor: ncde.panelBg; textColor: ncde.gilt4
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                visible: settings.showBatteryPct
                text: widget_data.batteryLevel + "%"
                color: WallInk.inked(settings.topPanelTextColor !== "" ? settings.topPanelTextColor : ncde.gilt4)
                // Fixed size (operator, 2026-07-15): see the volume-% note above.
                font.pixelSize: 12; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: 0; font.features: { "lnum": 1, "tnum": 1 }; anchors.verticalCenter: parent.verticalCenter   // 2026-09-25: size stays fixed; no letter-spacing, lining figures, so "100%" reads as one number
                style: theme.textStyle; styleColor: theme.textStyleColor
                layer.enabled: theme.textShadowEnabled
                layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                    shadowBlur: theme.textShadowRadius / 32.0
                    shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
            }
        }
        Item { id: pwrBtn; width: 22; height: 22; anchors.verticalCenter: parent.verticalCenter
            property bool hov: false
            Rectangle { anchors.fill: parent; radius: 3
                color: pwrBtn.hov ? Qt.rgba(ncde.accent.r,ncde.accent.g,ncde.accent.b,0.15) : "transparent" }
            Text {
                // Fixed size (operator, 2026-07-15): see the volume-% note above.
                text: "⏻"; color: WallInk.inked(pwrBtn.hov ? ncde.accent : (settings.topPanelTextColor !== "" ? settings.topPanelTextColor : ncde.gilt4)); font.pixelSize: 16; anchors.centerIn: parent
                style: theme.textStyle; styleColor: theme.textStyleColor
                layer.enabled: theme.textShadowEnabled
                layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                    shadowBlur: theme.textShadowRadius / 32.0
                    shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
            }
            HoverHandler { onHoveredChanged: pwrBtn.hov = hovered }
            TapHandler { onTapped: powerMenu.visible = !powerMenu.visible }
        }
    }

    // Volume popup — NO-OBSCURE: z:1400 above dock, pins panel open while visible.
    Rectangle {
        id: volumePopup; visible: false
        onVisibleChanged: { if (visible) { intellihide.revealAll(); intellihide.cancelHide() } else if (!visible && !powerMenu.visible && !clockCalPopup.visible) intellihide.scheduleHide() }
        anchors.right: parent.right; anchors.rightMargin: 8; anchors.top: parent.bottom; anchors.topMargin: 2 + topBezel.ring
        width: 220; height: 86; z: 1400; radius: 8; color: ncde.popupBg; border.color: ncde.border; border.width: 1
        // popup-header.png (645x62 enamel band): header trim, 200x19.
        Image {
            anchors.top: parent.top; anchors.topMargin: 4
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200; height: 19
            source: "popup-header.png"
            fillMode: Image.PreserveAspectFit
            smooth: true
            mipmap: true
            opacity: 0.95
            layer.enabled: true
            layer.effect: HueSaturation {
                hue: (ncde.accent.hslHue - 0.12) * 0.6
                saturation: -0.1
            }
        }
        Column { anchors { fill: parent; margins: 10; topMargin: 27 }
        spacing: 6
            Row { width: parent.width
                Text { text: "VOL"; color: WallInk.inked(ncde.accent); font.pixelSize: theme.fontSmall; font.family: "TerminalVector"; width: 30 }
                Slider { id: volSlider; width: parent.width-60; height: 20; from: 0; to: 150
                    Component.onCompleted: value = widget_data.volume
                    Connections { target: widget_data
                        // REVERTED 2026-07-13: an earlier pass here claimed widget_data
                        // has no changed() signal and rewrote this to onTrayChanged —
                        // WRONG on inspection of the live binary's own moc signal list
                        // (WidgetData: changed, clockChanged, statsChanged, weatherChanged,
                        // moonPositionChanged, mediaChanged, mediaPositionChanged — NO
                        // trayChanged at all; that belongs to a different class). changed()
                        // is real; restored to the original, verified-correct handler.
                        function onChanged() { if (!volSlider.pressed) volSlider.value = widget_data.volume }
                    }
                    onMoved: widget_data.setVolume(Math.round(value))
                    background: Rectangle { height:3;radius:2;color:Qt.rgba(ncde.border.r,ncde.border.g,ncde.border.b,0.5); Rectangle{width:parent.width*parent.parent.visualPosition;height:parent.height;radius:parent.radius;color:ncde.accent} }
                    handle: Rectangle { x:parent.leftPadding+parent.visualPosition*(parent.availableWidth-width); y:parent.topPadding+parent.availableHeight/2-height/2; width:10;height:10;radius:5;color:ncde.accent } }
                Text { text: widget_data.volume+"%"; color: WallInk.inked(ncde.border); font.pixelSize:theme.fontSmall; font.family:"TerminalVector"; width:30; horizontalAlignment:Text.AlignRight } } }
    }

    // Power menu — NO-OBSCURE: z:1400 above dock, pins panel open while visible.
    Rectangle {
        id: powerMenu; visible: false
        onVisibleChanged: {
            if (visible) { intellihide.revealAll(); intellihide.cancelHide() }
            else if (!visible && !volumePopup.visible && !clockCalPopup.visible) intellihide.scheduleHide()
        }
        anchors.right: parent.right; anchors.rightMargin: 8; anchors.top: parent.bottom; anchors.topMargin: 2 + topBezel.ring
        width: 160; z: 1400; height: powerMenuCol.implicitHeight+30; color: ncde.popupBg; border.color: ncde.border; border.width:1; radius:8
        // popup-header.png: header trim, 148x14 to fit the 160-wide menu.
        Image {
            anchors.top: parent.top; anchors.topMargin: 4
            anchors.horizontalCenter: parent.horizontalCenter
            width: 148; height: 14
            source: "popup-header.png"
            fillMode: Image.PreserveAspectFit
            smooth: true
            mipmap: true
            opacity: 0.95
            layer.enabled: true
            layer.effect: HueSaturation {
                hue: (ncde.accent.hslHue - 0.12) * 0.6
                saturation: -0.1
            }
        }
        Column { id: powerMenuCol; anchors { top:parent.top;left:parent.left;right:parent.right;margins:6; topMargin: 24 }
        spacing:2
            Repeater { model: [{label:"Lock Screen",action:"lock"},{label:"Log Out",action:"logout"},{label:"Reboot",action:"reboot"},{label:"Power Off",action:"poweroff"}]
                Rectangle { width:parent.width;height:28;radius:4
                    color:pmH.hovered?Qt.rgba(ncde.accent.r,ncde.accent.g,ncde.accent.b,0.12):"transparent"
                    Behavior on color{ColorAnimation{duration:80}}
                    HoverHandler{id:pmH}
                    Text {
                        anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter
                        text: modelData.label; color: WallInk.inked(pmH.hovered ? ncde.accent : theme.textColor)
                        font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Noto Sans"
                        style: theme.textStyle; styleColor: theme.textStyleColor
                        layer.enabled: theme.textShadowEnabled
                        layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                            shadowBlur: theme.textShadowRadius / 32.0
                            shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
                        Behavior on color { ColorAnimation { duration: 80 } }
                    }
                    TapHandler{onTapped:{powerMenu.visible=false;var a=modelData.action;if(a==="logout"){launcher.logout()}else if(a==="lock")launcher.systemCommand("ncde-portal --lock");else if(a==="reboot")launcher.systemCommand("systemctl reboot");else if(a==="poweroff")launcher.systemCommand("systemctl poweroff")}} } } }
    }
}
