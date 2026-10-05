// NCDEExpose.qml — NCDE Launchpad / App Grid
// Triggered by F1. Full-screen glass overlay with searchable app grid.
// Aesthetic: same glass + glow as the rest of NCDE.
//
// Animations (2026-10-03):
//   • Ink-bloom entrance — after a per-tile delay (index * 18 ms, max 300 ms) the
//     tile fades in, springs 0.3 → 1.0 (OutBack) and a glow flash blooms behind it.
//   • Wobble-tilt on hover — copy of Dock.qml's wobbleAnim: quick cheeky
//     jiggle (7° → -5° → 3° → 0°) using only NumberAnimation.
//   • Magnetic drift — hovered tile floats up 4 px; its neighbours lift 1.5 px.
//   • Breathing aura — ncde.glow halo pulses behind the bezel while hovered.
//   • Glass shimmer — a highlight glints across the dome on hover-enter.
//   • Particle motes — five glow sparks drift upward while hovered.
//   • Hover ripple — the tiles either side of the hovered one swell slightly.
//   Every hover effect fades out through a 'fade' property, so nothing is left
//   frozen half-visible when the pointer leaves mid-cycle.
//   • 1-px press sink already present via Translate on MuchaIcon / NCDEGlassCap.

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Effects 6.5

Item {
    id: expose
    anchors.fill: parent
    visible: false
    z: 1500

    // ── App model ─────────────────────────────────────────────
    ListModel { id: exposeModel }

    property string searchText: ""

    // The desktop wallpaper, painted here under the translucent art (operator 2026-10-01: Expose is
    // translucent with the WALLPAPER under it, never black). Expose is its own top-level window, so
    // without this it showed whatever lay behind it: app windows, or black when nothing composites.
    property url wallpaperUrl: ""
    property int wallpaperFill: Image.PreserveAspectCrop

    function refresh() {
        var apps = appMenuModel.getApps("All", expose.searchText)
        exposeGrid.hoveredIndex = -1
        exposeModel.clear()
        for (var i = 0; i < apps.length; i++) exposeModel.append(apps[i])
    }

    onVisibleChanged: {
        if (visible) {
            searchText = ""
            searchInput.text = ""
            // Rescan the .desktop dirs on every open so apps installed since login
            // (pacman, flatpak, AppImages via ncde-appimage-gen) show up without
            // a manual desktop-menu "Refresh". Search keystrokes don't rescan.
            appMenuModel.reload()
            refresh()
            focusTimer.restart()
        }
    }
    // reload() only queues a rescan; when it finds new or removed apps, show them in the open grid
    Connections {
        target: appMenuModel
        function onChanged() { if (expose.visible) expose.refresh() }
    }
    Timer {
        id: focusTimer; interval: 80; repeat: false
        onTriggered: searchInput.forceActiveFocus()
    }


    // ── Appear / disappear animation ──────────────────────────
    opacity: visible ? 1.0 : 0.0
    scale:   visible ? 1.0 : 0.96
    Behavior on opacity { NumberAnimation { duration: 200; easing.type: Easing.OutExpo } }
    Behavior on scale   { NumberAnimation { duration: 200; easing.type: Easing.OutExpo } }

    Rectangle { anchors.fill: parent; color: ncde.panelBg }   // only seen when there is no wallpaper
    Image {
        anchors.fill: parent
        source: expose.wallpaperUrl
        fillMode: expose.wallpaperFill
        visible: source != ""
        asynchronous: true
        smooth: true
    }
    ExposeBackdrop {
        anchors.fill: parent
    }

    // Glow vignette border
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.20)
        border.width: 2
    }

    // ── Close on background click ──────────────────────────────
    TapHandler { onTapped: expose.visible = false }

    // ── Header ────────────────────────────────────────────────
    Item {
        id: exposeHeader
        anchors.top: parent.top; anchors.topMargin: 48
        anchors.left: parent.left; anchors.right: parent.right
        height: 80

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            text: "NCDE EXPOSE"
            color: WallInk.inked(ncde.glow)
            font.pixelSize: theme.fontMedium; font.bold: true
            font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
        }

        // ── Search bar ────────────────────────────────────────
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            width: 420; height: 36; radius: 18
            color: Qt.rgba(ncde.popupBg.r, ncde.popupBg.g, ncde.popupBg.b, 0.90)
            border.color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.50)
            border.width: 1

            // Left glow line
            Rectangle {
                anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
                width: 2; radius: 18
                color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.60)
            }

            Text {
                anchors.left: parent.left; anchors.leftMargin: 18
                anchors.verticalCenter: parent.verticalCenter
                text: "Search apps..."
                color: WallInk.inked(ncde.accentMuted); font.pixelSize: theme.fontMedium; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                visible: searchInput.text === ""
            }

            TextInput {
                id: searchInput
                anchors.fill: parent
                anchors.leftMargin: 18; anchors.rightMargin: 18
                anchors.topMargin: 6; anchors.bottomMargin: 6
                color: WallInk.inked(ncde.panelText)
                font.pixelSize: theme.fontMedium; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                selectByMouse: true
                onTextChanged: {
                    expose.searchText = text
                    expose.refresh()
                }
                Keys.onEscapePressed: expose.visible = false
            }
        }
    }

    // ── App grid ──────────────────────────────────────────────
    ScrollView {
        id: exposeGrid
        anchors.top: exposeHeader.bottom; anchors.topMargin: 24
        anchors.bottom: parent.bottom; anchors.bottomMargin: 48
        anchors.left: parent.left; anchors.leftMargin: 48
        anchors.right: parent.right; anchors.rightMargin: 48
        clip: true

        // Index of the tile under the pointer (-1 = none) — drives the hover ripple.
        property int hoveredIndex: -1

        ScrollBar.vertical: NCDEScrollBar {}

        Flow {
            width: exposeGrid.width
            spacing: 20
            padding: 8

            Repeater {
                model: exposeModel

                // ── App tile ──────────────────────────────────
                Item {
                    id: tile
                    width: 110; height: 120
                    property bool hovered: false
                    // Distance from the hovered tile (-1 = nothing hovered)
                    readonly property int hoverDist: exposeGrid.hoveredIndex < 0
                        ? -1 : Math.abs(exposeGrid.hoveredIndex - index)

                    // ── Magnetic drift ────────────────────────
                    property real driftY: hovered ? -4 : (hoverDist === 1 ? -1.5 : 0)
                    Behavior on driftY { NumberAnimation { duration: 260; easing.type: Easing.OutBack; easing.overshoot: 1.4 } }
                    transform: Translate { y: tile.driftY }

                    // ── Ink-bloom entrance ────────────────────
                    // Everything waits for the per-tile delay, then fade + spring + bloom
                    // run together, so the cascade stays a wave. Plain NumberAnimation only.
                    opacity: 0
                    scale: 0.3
                    Component.onCompleted: entranceAnim.start()
                    SequentialAnimation {
                        id: entranceAnim
                        PauseAnimation { duration: Math.max(0, Math.min(index * 18, 300)) }   // index is -1 for a moment at creation
                        ParallelAnimation {
                            NumberAnimation { target: tile; property: "opacity"; to: 1.0; duration: 250; easing.type: Easing.OutCubic }
                            NumberAnimation { target: tile; property: "scale"; to: 1.0; duration: 380; easing.type: Easing.OutBack; easing.overshoot: 1.3 }
                            NumberAnimation { target: bloomFlash; property: "scale"; from: 0.4; to: 1.25; duration: 410; easing.type: Easing.OutQuad }
                            SequentialAnimation {
                                NumberAnimation { target: bloomFlash; property: "opacity"; from: 0; to: 0.4; duration: 90 }
                                NumberAnimation { target: bloomFlash; property: "opacity"; to: 0; duration: 320; easing.type: Easing.InQuad }
                            }
                        }
                    }

                    Rectangle {
                        id: bloomFlash
                        anchors.centerIn: parent
                        width: parent.width; height: parent.height
                        radius: 12
                        color: ncde.glow
                        opacity: 0
                        scale: 0.4
                        visible: opacity > 0
                    }

                    Rectangle {
                        anchors.fill: parent; radius: 12
                        color: tile.hovered
                            ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18)
                            : Qt.rgba(ncde.surface.r, ncde.surface.g, ncde.surface.b, 0.30)
                        border.color: tile.hovered
                            ? Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.60)
                            : Qt.rgba(ncde.border.r, ncde.border.g, ncde.border.b, 0.30)
                        border.width: 1
                        Behavior on color { ColorAnimation { duration: 100 } }

                        // Scale spring on hover; neighbours swell slightly (hover ripple)
                        scale: tile.hovered ? 1.06 : (tile.hoverDist === 1 ? 1.02 : 1.0)
                        Behavior on scale { NumberAnimation { duration: 160; easing.type: Easing.OutExpo } }

                        Column {
                            anchors.centerIn: parent
                            spacing: 8

                            // App icon — same stack as a dock slot (Dock.qml): brass
                            // bezel, QML-drawn medallion, glass dome, so Expose icons
                            // look exactly like the dock's.
                            Item {
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: 66; height: 66

                                // ── Breathing aura ────────────────
                                // fade (Behavior) handles in/out; breath (loop) handles the pulse.
                                // On unhover fade → 0, so a stopped mid-cycle breath is never seen.
                                Rectangle {
                                    id: glowAura
                                    anchors.centerIn: parent
                                    width: 70; height: 70; radius: 35
                                    color: ncde.glow
                                    property real fade: tile.hovered ? 1 : 0
                                    Behavior on fade { NumberAnimation { duration: 220; easing.type: Easing.OutQuad } }
                                    property real breath: 0
                                    opacity: fade * (0.12 + breath)
                                    visible: fade > 0
                                    SequentialAnimation {
                                        running: tile.hovered
                                        loops: Animation.Infinite
                                        NumberAnimation { target: glowAura; property: "breath"; to: 0.22; duration: 900; easing.type: Easing.InOutSine }
                                        NumberAnimation { target: glowAura; property: "breath"; to: 0;    duration: 900; easing.type: Easing.InOutSine }
                                    }
                                }

                                NCDEIconBezel {
                                    anchors.centerIn: parent
                                    bezelSize: 56
                                    hovered: tile.hovered
                                    pressed: tileTap.pressed
                                }
                                MuchaIcon {
                                    id: tileIcon
                                    anchors.centerIn: parent
                                    size: 56
                                    // Weight & touch (2026-09-24): sinks 1px while held, same as the dock.
                                    transform: Translate { y: tileTap.pressed ? 1 : 0 }
                                    appName: model.name
                                    appIcon: model.icon || ""
                                    accentColor: ncde.accent
                                    glowColor:   ncde.glow

                                    // ── Wobble-tilt on hover (2026-10-03) ─────────────────
                                    // Copied verbatim from Dock.qml:404-412.
                                    // A quick cheeky jiggle (7° → -5° → 3° → 0°) fires
                                    // when the pointer enters the tile.
                                    property real wobble: 0
                                    rotation: wobble
                                    SequentialAnimation {
                                        id: wobbleAnim
                                        NumberAnimation { target: tileIcon; property: "wobble"; to:  7; duration: 90;  easing.type: Easing.OutQuad }
                                        NumberAnimation { target: tileIcon; property: "wobble"; to: -5; duration: 110; easing.type: Easing.InOutSine }
                                        NumberAnimation { target: tileIcon; property: "wobble"; to:  3; duration: 90;  easing.type: Easing.InOutSine }
                                        NumberAnimation { target: tileIcon; property: "wobble"; to:  0; duration: 160; easing.type: Easing.OutBack }
                                    }
                                }
                                NCDEGlassCap {
                                    anchors.centerIn: parent
                                    capSize: 56
                                    hovered: tile.hovered
                                    pressed: tileTap.pressed
                                    transform: Translate { y: tileTap.pressed ? 1 : 0 }
                                }

                                // ── Glass shimmer ─────────────────
                                // A glint near the top of the dome widens and fades once per hover-enter.
                                Item {
                                    anchors.centerIn: parent
                                    width: 56; height: 56
                                    clip: true
                                    Rectangle {
                                        id: shimmerDot
                                        width: 16; height: 4; radius: 2
                                        color: "white"
                                        opacity: 0
                                        visible: opacity > 0
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        y: 8
                                        SequentialAnimation {
                                            id: shimmerAnim
                                            PropertyAction  { target: shimmerDot; property: "width"; value: 16 }
                                            NumberAnimation { target: shimmerDot; property: "opacity"; to: 0.6; duration: 150 }
                                            NumberAnimation { target: shimmerDot; property: "width"; to: 36; duration: 200; easing.type: Easing.OutQuad }
                                            NumberAnimation { target: shimmerDot; property: "width"; to: 16; duration: 200; easing.type: Easing.InQuad }
                                            NumberAnimation { target: shimmerDot; property: "opacity"; to: 0; duration: 150 }
                                        }
                                    }
                                }
                            }

                            // App name on a black label that hugs the text (operator 2026-10-01)
                            Rectangle {
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: appLabel.paintedWidth + 12
                                height: appLabel.paintedHeight + 4
                                radius: 4
                                color: "black"
                                visible: appLabel.text !== ""
                            Text {
                                id: appLabel
                                anchors.centerIn: parent
                                text: model.name || ""
                                color: WallInk.inked(tile.hovered ? ncde.accent : ncde.panelText)
                                font.pixelSize: theme.fontSmall; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                                elide: Text.ElideRight
                                width: Math.min(implicitWidth, 94)
                                horizontalAlignment: Text.AlignHCenter
                                Behavior on color { ColorAnimation { duration: 100 } }
                            }
                            }
                        }

                        // ── Particle motes ────────────────────────
                        // Five glow sparks rise over the icon while hovered. The whole field
                        // fades out on unhover, so no spark is left frozen mid-flight.
                        Item {
                            id: moteField
                            anchors.fill: parent
                            property real fade: tile.hovered ? 1 : 0
                            Behavior on fade { NumberAnimation { duration: 250 } }
                            opacity: fade
                            visible: fade > 0
                            Repeater {
                                model: 5
                                Rectangle {
                                    id: mote
                                    property int mi: index          // mote index, not tile index
                                    width: 2; height: 2; radius: 1
                                    color: ncde.glow
                                    x: 30 + mi * 12 + (mi % 2 ? 3 : -3)
                                    y: 80
                                    opacity: 0
                                    SequentialAnimation {
                                        running: moteField.visible
                                        loops: Animation.Infinite
                                        PauseAnimation { duration: mote.mi * 230 }
                                        ParallelAnimation {
                                            NumberAnimation { target: mote; property: "y"; from: 80; to: 10; duration: 1300 + mote.mi * 90 }
                                            SequentialAnimation {
                                                NumberAnimation { target: mote; property: "opacity"; from: 0; to: 0.8; duration: 250 }
                                                PauseAnimation  { duration: 450 }
                                                NumberAnimation { target: mote; property: "opacity"; to: 0; duration: 600 + mote.mi * 90 }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    HoverHandler {
                        onHoveredChanged: {
                            tile.hovered = hovered
                            if (hovered) {
                                // Animations first, so nothing below can ever stop them.
                                wobbleAnim.restart()
                                shimmerAnim.restart()
                                exposeGrid.hoveredIndex = index
                            } else if (exposeGrid.hoveredIndex === index) {
                                exposeGrid.hoveredIndex = -1
                            }
                        }
                    }
                    TapHandler {
                        id: tileTap
                        onTapped: {
                            // Launch via the .desktop (gtk-launch <appId>) so field codes / flatpak
                            // forwarding / D-Bus-activation are handled — same as the dock. Falls back
                            // to the raw exec if appId is absent (no regression).
                            launcher.launchExec(model.appId ? "gtk-launch " + model.appId : model.exec)
                            expose.visible = false
                        }
                    }
                }
            }
        }
    }

    // ── Keyboard: Esc closes ──────────────────────────────────
    Keys.onEscapePressed: expose.visible = false
    Keys.onPressed: (event) => {
        if (event.key === Qt.Key_F1) { expose.visible = false; event.accepted = true }
    }
}
