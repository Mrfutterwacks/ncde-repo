// BottomPanel.qml — NCDE Bottom Panel
// CDE Front Panel DNA: icon launcher buttons, clock, workspace switcher
// Height: 28px to match the top panel; icon-only launchers (labels dropped to fit)

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import "ncde-color.js" as Col

Item {
    id: bottomPanel
    anchors.left: parent.left; anchors.leftMargin: 47
    anchors.right: parent.right; anchors.rightMargin: 47
    height: 30
    z: 500

    // Wallpaper reference: the glass shows it through, the ribbons take its tones
    property Item wallpaperSource: null
    property Item menuLayer: null
    property alias ledger: ledger

    // panel-frame.png rows 0-5 and 66-71 are transparent (measured 2026-10-01): the panel may sit
    // so the frame's INK meets the screen edge, never clipped; the rail still floats 7-8 px in.
    readonly property int frameInkPad: 6
    property real panelY: parent.height - 52 + frameInkPad
    property real _dragStartY: panelY
    function clampPanelY(value) {
        var minY = -bottomPanelFrame.y - frameInkPad
        var maxY = Math.max(minY, parent.height - (bottomPanelFrame.y + bottomPanelFrame.height) + frameInkPad)
        return Math.max(minY, Math.min(value, maxY))
    }

    // Dummy bezel id kept so older references do not break; ring is 0.
    Item { id: bottomBezel; property int ring: 0 }

    // ── Intellihide ───────────────────────────────────────
    y: panelY
    property real targetY: intellihide.btmRevealed ? 0 : parent.height + 20 - panelY
    Behavior on targetY {
        NumberAnimation { duration: 400; easing.type: Easing.OutExpo }
    }
    transform: Translate { y: bottomPanel.targetY }

    DragHandler {
        id: bottomPanelDrag
        enabled: intellihide.btmRevealed
        target: null
        acceptedButtons: Qt.LeftButton
        xAxis.enabled: false
        yAxis.enabled: true
        onActiveChanged: if (active) bottomPanel._dragStartY = bottomPanel.panelY
        onTranslationChanged: {
            if (active) bottomPanel.panelY = bottomPanel.clampPanelY(bottomPanel._dragStartY + translation.y)
        }
    }

    BorderImage {
        id: bottomPanelFrame
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

    HoverHandler {
        onHoveredChanged: {
            intellihide.btmHovered = hovered
            if (hovered) intellihide.revealAll()
            else intellihide.scheduleHide()
        }
    }

    // Iris/Filigree glass settings for this surface (restored with the glass)
    property var _surfaceGlass: typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("bottomPanel") : null
    Connections {
        target: ncde
        function onThemeChanged() {
            bottomPanel._surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("bottomPanel") : null
        }
    }

    // ── Aero glass pill (restored 2026-09-29, operator: "you removed all my
    // glass") — the 2026-09-28 build had swapped it for an opaque painted
    // ground; this is the July glass block, unchanged.
    NCDEGlassSurface {
        anchors.fill: parent
        backgroundSource: bottomPanel.wallpaperSource
        specularInset: 0.0
        revealPulse: intellihide.btmRevealed
        glintPulse: intellihide.glintPulse
        tint: {
            if (!ncde.presetActive) {
                var g = bottomPanel._surfaceGlass
                if (g && g["tint"] !== undefined) { var c = Qt.color(g["tint"]); return Qt.rgba(c.r, c.g, c.b, g["shine"] !== undefined ? g["shine"] * 0.36 : 0.18) }
            }
            return Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18)
        }
        glowA: bottomPanel._surfaceGlass && bottomPanel._surfaceGlass["glow"] !== undefined ? bottomPanel._surfaceGlass["glow"] : 0.70
        edge: {
            if (!ncde.presetActive) {
                var g = bottomPanel._surfaceGlass
                if (g && g["border"] !== undefined) { var c = Qt.color(g["border"]); return Qt.rgba(c.r, c.g, c.b, 0.85) }
            }
            return Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.85)
        }
        glowRim:  !ncde.presetActive && bottomPanel._surfaceGlass && bottomPanel._surfaceGlass["glowColor"] !== undefined ? Qt.color(bottomPanel._surfaceGlass["glowColor"]) : ncde.glow
        glowHalo: !ncde.presetActive && bottomPanel._surfaceGlass && bottomPanel._surfaceGlass["glowColor"] !== undefined ? Qt.color(bottomPanel._surfaceGlass["glowColor"]) : ncde.glow
    }
    // the current wallpaper's shades, for the ribbon panes (read once per wallpaper)
    NCDEWallTones { id: wallTones; source: bottomPanel.wallpaperSource ? bottomPanel.wallpaperSource.source : "" }

    // ── Leap Frog Ledger window ────────────────────────────────
    Window {
        id: ledgerWindow
        // Real bug fixed 2026-07-04: missing Qt.WindowStaysOnTopHint. This window
        // bypasses LaPivot's own WM (BypassWindowManagerHint), so nothing else raises
        // it above other windows; every managed app opens maximized by design, so
        // without this hint the Ledger opened (visible=true) but sat behind whatever
        // else was full-screen. Matches the proven working pattern already used by
        // main.qml's exposeWindow for the same bypass-WM situation.
        flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint | Qt.WindowStaysOnTopHint
        width: 860; height: 620
        x: (Screen.width  - width)  / 2
        y: (Screen.height - height) / 2
        color: "transparent"
        visible: false

        LeapFrogLedger { id: ledger; anchors.fill: parent; onCloseRequested: ledgerWindow.visible = false }
        // 2026-09-26: typing did nothing in the Ledger. A window that bypasses the
        // WM never gets X keyboard focus unless it asks (Qt's requestActivate()
        // sets it directly for such windows): ask when it opens, and whenever a
        // field inside takes focus while the window itself isn't active.
        onVisibleChanged: if (visible) Qt.callLater(ledgerWindow.requestActivate)
        onActiveFocusItemChanged: if (activeFocusItem && !active) requestActivate()
    }


    Row {
        anchors.fill: parent
        anchors.leftMargin: 6; anchors.rightMargin: 6
        spacing: 0
        z: 2

        // ── LEFT: CDE Front Panel launchers, on an ornament ribbon ──
        OrnamentRibbon {
            id: launcherStrip
            seed: 3
            dir: 1
            tones: wallTones.tones
            pad: 2
            anchors.verticalCenter: parent.verticalCenter

            Repeater {
                model: [
                    { exec: "/usr/local/bin/orchidee", name: "Orchidée",     tip: "Orchidée"    },
                    { exec: "magpie-talker",           name: "Magpie",       tip: "Magpie"      },
                    { exec: "verve-text",              name: "Verve",        tip: "Verve"       },
                    { exec: "abacus",                  name: "Abacus",       tip: "Abacus"      },
                    { exec: "verdantfolio",            name: "Writer",       tip: "Verdant"     },
                ]

                // CDE-style launcher button — beveled circle (NCDEIconBezel,
                // same brass-bezel treatment as the dock) instead of the old
                // flat 30x24 square, 2026-09-23.
                Item {
                    id: fpBtn
                    width: 30; height: 30
                    anchors.verticalCenter: parent.verticalCenter
                    property bool pressed: false
                    property bool hovered: false

                    NCDEIconBezel {
                        anchors.centerIn: parent
                        bezelSize: 20
                        hovered: fpBtn.hovered
                        pressed: fpBtn.pressed
                    }

                    // Icon-only launcher (CDE FP label dropped to fit the 28px panel)
                    MuchaIcon {
                        anchors.horizontalCenter: parent.horizontalCenter
                        size: 18
                        appName: modelData.name
                        accentColor: ncde.accent
                        glowColor:   ncde.glow
                        y: parent.height / 2 - size / 2 + (fpBtn.pressed ? 1 : 0)
                        Behavior on y { NumberAnimation { duration: 60; easing.type: Easing.OutExpo } }
                    }

                    // Glass dome over the launcher medallion (same bezel as the dock).
                    NCDEGlassCap {
                        anchors.centerIn: parent
                        capSize: 20
                        hovered: fpBtn.hovered
                        pressed: fpBtn.pressed
                        transform: Translate { y: fpBtn.pressed ? 1 : 0 }
                    }

                    HoverHandler {
                        onHoveredChanged: {
                            fpBtn.hovered = hovered
                            if (hovered) fpTipDelay.restart()
                            else fpTipDelay.stop()
                        }
                    }
                    TapHandler {
                        onPressedChanged: fpBtn.pressed = pressed
                        onTapped: launcher.launchExec(modelData.exec)
                    }

                    // Tooltip cartouche (2026-07-09) — surfaces the launcher model's
                    // tip field, which shipped in the model but was never rendered.
                    Timer { id: fpTipDelay; interval: 450 }
                    Rectangle {
                        visible: fpBtn.hovered && !fpBtn.pressed && !fpTipDelay.running
                        y: -(height + 8)
                        x: Math.max((fpBtn.width - width) / 2, -(fpBtn.x + 4))
                        width: fpTipText.implicitWidth + 16
                        height: fpTipText.implicitHeight + 8
                        radius: 6
                        z: 10
                        color: Qt.rgba(ncde.panelBg.r, ncde.panelBg.g, ncde.panelBg.b, 0.94)
                        border.width: 1
                        border.color: Qt.rgba(ncde.gilt3.r, ncde.gilt3.g, ncde.gilt3.b, 0.9)
                        Text {
                            id: fpTipText
                            anchors.centerIn: parent
                            text: modelData.tip
                            color: WallInk.inked(ncde.panelText)
                            font.family: ncde.titleFont
                            font.pixelSize: SetTheme.sm
                        }
                    }
                }
            }

        }

        // ── CENTER: Window task list ───────────────────────────
        Item {
            id: taskArea
            height: parent.height
            width: bottomPanel.width
                   - launcherStrip.width
                   - minimizedStrip.width
                   - wsRibbon.width
                   - 20

            Row {
                anchors.fill: parent
                anchors.leftMargin: 6; anchors.rightMargin: 6
                spacing: 2

                Repeater {
                    id: taskRepeater
                    model: windowMgr

                    Rectangle {
                        visible: model.minimized !== true && width > 20
                        width: {
                            var active = windowMgr.count
                            var avail = taskArea.width - 8
                            return active > 0 ? Math.min(180, avail / active - 3) : 0
                        }
                        height: 20
                        radius: 3
                        anchors.verticalCenter: parent.verticalCenter

                        color: windowMgr.activeIndex === index
                            ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18)
                            : Qt.rgba(1,1,1,0.04)
                        border.color: windowMgr.activeIndex === index
                            ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.7)
                            : Qt.rgba(1,1,1,0.10)
                        border.width: 1

                        Behavior on color { ColorAnimation { duration: 120 } }

                        // Active top line — inset by the button's corner radius so it never
                        // pokes square past the rounded corners (2026-09-25)
                        Rectangle {
                            visible: windowMgr.activeIndex === index
                            anchors.top: parent.top; anchors.topMargin: 1
                            anchors.left: parent.left; anchors.right: parent.right
                            anchors.leftMargin: parent.radius; anchors.rightMargin: parent.radius
                            height: 2; color: ncde.accent; radius: 1
                        }

                        Text {
                            anchors.left: parent.left; anchors.leftMargin: 8
                            anchors.right: parent.right; anchors.rightMargin: 6
                            anchors.verticalCenter: parent.verticalCenter
                            text: model.title || "Window"
                            // 2026-09-25: the active title was the mid accent on the dark
                            // panel, hard to read — lifted to 4.5:1 against the panel ground
                            // (hue kept; a palette that already passes is left untouched)
                            color: Col.readable(WallInk.inked(windowMgr.activeIndex === index ? ncde.accent : ncde.gilt4),
                                                ncde.panelBg, 4.5)
                            font.pixelSize: theme.fontSmall; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                            elide: Text.ElideRight
                        }

                        TapHandler {
                            onTapped: {
                                if (windowMgr.activeIndex === index) {
                                    windowMgr.minimizeWindow(model.winId)
                                } else {
                                    if (model.minimized) windowMgr.unminimizeWindow(model.winId)
                                    else windowMgr.activateWindow(model.winId)
                                }
                            }
                        }
                    }
                }
            }
        }

        // ── MINIMIZED PILLS ────────────────────────────────────
        Row {
            id: minimizedStrip
            spacing: 3
            anchors.verticalCenter: parent.verticalCenter

            visible: windowMgr.count > 0

            Rectangle {
                visible: minimizedStrip.visible
                width: 1; height: 16
                anchors.verticalCenter: parent.verticalCenter
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "transparent" }
                    GradientStop { position: 0.5; color: Qt.rgba(ncde.glow.r,ncde.glow.g,ncde.glow.b,0.35) }
                    GradientStop { position: 1.0; color: "transparent" }
                }
            }

            Repeater {
                model: windowMgr
                Rectangle {
                    visible: model.minimized === true
                    width: visible ? 30 : 0; height: 22
                    radius: 11
                    anchors.verticalCenter: parent.verticalCenter
                    color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.1)
                    border.color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, minP.val)
                    border.width: 1

                    Item { id: minP; property real val: 0.3
                        SequentialAnimation on val {
                            running: model.minimized === true && !animPolicy.screenIdle; loops: Animation.Infinite
                            NumberAnimation { to: 0.8; duration: 1200; easing.type: Easing.InOutSine }
                            NumberAnimation { to: 0.2; duration: 1200; easing.type: Easing.InOutSine }
                        }
                    }

                    MuchaIcon {
                        anchors.centerIn: parent
                        size: 14
                        appName: model.appId || model.title.split(" ")[0] || "?"
                        accentColor: ncde.accent
                        glowColor:   ncde.glow
                    }

                    TapHandler {
                        onTapped: {
                            windowMgr.unminimizeWindow(model.winId)
                        }
                    }
                    HoverHandler { id: mh }
                }
            }

            Rectangle {
                visible: minimizedStrip.visible
                width: 1; height: 16
                anchors.verticalCenter: parent.verticalCenter
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "transparent" }
                    GradientStop { position: 0.5; color: Qt.rgba(ncde.glow.r,ncde.glow.g,ncde.glow.b,0.35) }
                    GradientStop { position: 1.0; color: "transparent" }
                }
            }
        }

        // ── Leap Frog menu + workspaces, on an ornament ribbon ──
        OrnamentRibbon {
            id: wsRibbon
            followsDrawer: true     // menus slide via the GliaBar drawer; don't chase it
            seed: 4
            dir: -1
            tones: wallTones.tones
            pad: 4
            anchors.verticalCenter: parent.verticalCenter

        // ── LEAP FROG LEDGER menu strip ────────────────────────
        GliaLeapFrogBar {
            id: menuStrip
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height
            app: ledger
            pond: pond
            menuLayer: bottomPanel.menuLayer
        }

        // ── WORKSPACE SWITCHER — CDE FP centerpiece ───────────
        Row {
            id: wsRow
            spacing: 3
            anchors.verticalCenter: parent.verticalCenter

            Repeater {
                model: ncdeWorkspace.names

                // Beveled circle, same brass-bezel treatment as the dock icons
                // (NCDEIconBezel, extracted from Dock.qml 2026-09-23) instead of
                // the old 28x22 square. The old cell crammed a number line AND
                // a "One/Two/Three/Four" caption line into a 22px-tall box —
                // that's what was clipping the numbers. Single bold number now,
                // same "icon, no caption" language the dock itself uses.
                // 2026-09-25 (operator): same size as the launcher icons on the left
                // of this panel — the 30px slot and 20px bezel of fpBtn. They were a
                // 26px bezel in a 32px ring (36px across), bigger than the icons and
                // taller than the 28px panel.
                Item {
                    id: wsCell
                    width: 30; height: 30
                    anchors.verticalCenter: parent.verticalCenter

                    readonly property bool active: ncdeWorkspace.current === index
                    // Weight & touch (2026-09-24): the current workspace's button stays
                    // latched down in its socket, like a radio-set push button; the
                    // others sink only while held. Instant — no new animation.
                    readonly property bool sunk: active || wsTap.pressed

                    NCDEIconBezel {
                        anchors.centerIn: parent
                        bezelSize: 20
                        hovered: wsCell.active
                        pressed: wsCell.sunk
                    }

                    Text {
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: wsCell.sunk ? 1 : 0
                        z: 2    // the numeral sits on the dome, crisp (2026-09-26)
                        text: index + 1
                        color: WallInk.inked(wsCell.active ? ncde.accent : ncde.gilt4)
                        font.pixelSize: theme.fontSmall + 1; font.bold: wsCell.active
                        font.family: "TerminalVector"
                    }

                    // Glass dome over the number (2026-09-26, operator: "add glass domes
                    // to the 1234"): the same lens the dock and the launchers wear, so
                    // every button on the shell is one family. The current workspace's
                    // dome takes the accent; it sinks with the latched button.
                    NCDEGlassCap {
                        anchors.centerIn: parent
                        capSize: 20
                        hovered: wsHover.hovered
                        pressed: wsCell.sunk
                        tintColor: wsCell.active ? ncde.accent : ncde.gilt2
                        transform: Translate { y: wsCell.sunk ? 1 : 0 }
                    }
                    HoverHandler { id: wsHover }

                    // Active-state accent ring, laid ON the bezel's outer edge (not a
                    // bigger circle around it); inactive buttons have no ring at all,
                    // so no stray hairline circles
                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.width - 1; height: width
                        radius: width / 2
                        color: "transparent"
                        border.color: wsCell.active
                            ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.85)
                            : "transparent"
                        border.width: 1.5
                        Behavior on border.color { ColorAnimation { duration: 120 } }
                    }

                    // ncdeWorkspace.activate() now sends a real _NET_CURRENT_DESKTOP EWMH
                    // ClientMessage (NCDEWorkspace.h), which NCDEWindowManager's own
                    // switchDesktop()/XCB_CLIENT_MESSAGE handler acts on directly — no more
                    // external wmctrl shell-out. index is 0-based, matching EWMH's own convention.
                    TapHandler { id: wsTap; onTapped: ncdeWorkspace.activate(index) }
                }
            }
        }
        }
    }
}
