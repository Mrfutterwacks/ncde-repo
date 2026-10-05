// NCDEExpose.qml — NCDE Launchpad / App Grid
// Triggered by F1. Full-screen glass overlay with searchable app grid.
// Aesthetic: same glass + glow as the rest of NCDE.

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

    function refresh() {
        var apps = appMenuModel.getApps("All", expose.searchText)
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
    Timer {
        id: focusTimer; interval: 80; repeat: false
        onTriggered: searchInput.forceActiveFocus()
    }


    // ── Appear / disappear animation ──────────────────────────
    opacity: visible ? 1.0 : 0.0
    scale:   visible ? 1.0 : 0.96
    Behavior on opacity { NumberAnimation { duration: 200; easing.type: Easing.OutExpo } }
    Behavior on scale   { NumberAnimation { duration: 200; easing.type: Easing.OutExpo } }

    // ── Stained-glass background (2026-09-29, operator art "Musa") ──
    // muchaexpose.png carries its own translucency (alpha ≈ 0.56), so the desktop
    // glows through the panes like light through a window. Cropped to fill, centred.
    Image {
        anchors.fill: parent
        source: "muchaexpose.png"
        fillMode: Image.PreserveAspectCrop
        smooth: true; mipmap: true
    }
    // Light scrim so tile labels stay readable over the busy glass.
    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(ncde.panelBg.r, ncde.panelBg.g, ncde.panelBg.b, 0.30)
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
            font.family: theme.fontFamily; font.italic: theme.fontItalic; font.letterSpacing: theme.letterSpacing
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
                color: WallInk.inked(ncde.accentMuted); font.pixelSize: theme.fontMedium; font.family: theme.fontFamily; font.weight: theme.fontWeight; font.italic: theme.fontItalic; font.letterSpacing: theme.letterSpacing
                visible: searchInput.text === ""
            }

            TextInput {
                id: searchInput
                anchors.fill: parent
                anchors.leftMargin: 18; anchors.rightMargin: 18
                anchors.topMargin: 6; anchors.bottomMargin: 6
                color: WallInk.inked(ncde.panelText)
                font.pixelSize: theme.fontMedium; font.family: theme.fontFamily; font.weight: theme.fontWeight; font.italic: theme.fontItalic; font.letterSpacing: theme.letterSpacing
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

                        // Scale spring on hover
                        scale: tile.hovered ? 1.06 : 1.0
                        Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutExpo } }

                        Column {
                            anchors.centerIn: parent
                            spacing: 8

                            // App icon — same stack as a dock slot (Dock.qml): brass
                            // bezel, QML-drawn medallion, glass dome, so Expose icons
                            // look exactly like the dock's.
                            Item {
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: 66; height: 66

                                NCDEIconBezel {
                                    anchors.centerIn: parent
                                    bezelSize: 56
                                    hovered: tile.hovered
                                    pressed: tileTap.pressed
                                }
                                MuchaIcon {
                                    anchors.centerIn: parent
                                    size: 56
                                    // Weight & touch (2026-09-24): sinks 1px while held, same as the dock.
                                    transform: Translate { y: tileTap.pressed ? 1 : 0 }
                                    appName: model.name
                                    appIcon: model.icon || ""
                                    accentColor: ncde.accent
                                    glowColor:   ncde.glow
                                }
                                NCDEGlassCap {
                                    anchors.centerIn: parent
                                    capSize: 56
                                    hovered: tile.hovered
                                    pressed: tileTap.pressed
                                    transform: Translate { y: tileTap.pressed ? 1 : 0 }
                                }
                            }

                            // App name
                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: model.name || ""
                                color: WallInk.inked(tile.hovered ? ncde.accent : ncde.panelText)
                                font.pixelSize: theme.fontSmall; font.family: theme.fontFamily; font.weight: theme.fontWeight; font.italic: theme.fontItalic; font.letterSpacing: theme.letterSpacing
                                elide: Text.ElideRight
                                width: 100
                                horizontalAlignment: Text.AlignHCenter
                                Behavior on color { ColorAnimation { duration: 100 } }

                                // Dark pill behind the name so it reads over the stained glass.
                                Rectangle {
                                    z: -1
                                    anchors.centerIn: parent
                                    width: Math.min(parent.contentWidth, parent.width) + 12
                                    height: parent.contentHeight + 4
                                    radius: height / 2
                                    color: Qt.rgba(ncde.popupBg.r, ncde.popupBg.g, ncde.popupBg.b, 0.72)
                                }
                            }
                        }
                    }

                    HoverHandler { onHoveredChanged: tile.hovered = hovered }
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
