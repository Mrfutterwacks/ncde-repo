// ChromeBar.qml — 58px chrome: jewel-glass menubar (top 30) + tab strip (28).
// Input is TapHandler/HoverHandler/DragHandler only — never MouseArea.
// All intents go through the C++ `bridge`.

import QtQuick

Item {
    id: bar

    readonly property var panes: [
        { mid: "file",     label: "File",     top: "#ffe6ad", bot: "#d99a3f" },
        { mid: "edit",     label: "Edit",     top: "#ffd6c2", bot: "#d4794f" },
        { mid: "view",     label: "View",     top: "#ffd2e2", bot: "#cf6592" },
        { mid: "terminal", label: "Terminal", top: "#ecd6ff", bot: "#9560c2" },
        { mid: "tabs",     label: "Tabs",     top: "#d6dcff", bot: "#6670b8" },
        { mid: "help",     label: "Help",     top: "#c8f1ea", bot: "#3f9488" }
    ]

    // ── Row 1 — jewel-glass menubar (top 30px) ──────────────────────────────
    Item {
        id: menubar
        x: 0; y: 0
        width: parent.width; height: 30

        Row {
            id: paneRow
            height: 30
            Repeater {
                model: bar.panes
                delegate: Item {
                    id: pane
                    required property var modelData
                    height: 30
                    width: lbl.implicitWidth + 30

                    Rectangle {
                        anchors.fill: parent
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: pane.modelData.top }
                            GradientStop { position: 1.0; color: pane.modelData.bot }
                        }
                    }
                    // top highlight over the top 48%
                    Rectangle {
                        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
                        height: parent.height * 0.48
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: Qt.rgba(1,1,1,0.45) }
                            GradientStop { position: 1.0; color: Qt.rgba(1,1,1,0.0) }
                        }
                    }
                    // hover fill
                    Rectangle {
                        anchors.fill: parent
                        color: Qt.rgba(1,1,1, ph.hovered ? 0.10 : 0.0)
                    }
                    // lead came on the right edge
                    Rectangle { anchors.right: parent.right; width: 1; height: parent.height; color: "#6e757b" }

                    Text {
                        id: lbl
                        anchors.centerIn: parent
                        text: pane.modelData.label
                        color: "#3a1d08"
                        font.family: "Georgia"
                        font.pixelSize: 14
                        font.weight: Font.DemiBold
                        style: Text.Raised
                        styleColor: Qt.rgba(1,1,1,0.25)
                    }
                    HoverHandler { id: ph }
                    TapHandler { onTapped: bridge.activateMenu(pane.modelData.mid) }
                }
            }
        }
        // lead came on the very left of the first pane
        Rectangle { x: 0; y: 0; width: 1; height: 30; color: "#6e757b" }
        // right spacer (teal cathedral glass) — also a window-drag zone
        Rectangle {
            anchors.left: paneRow.right
            anchors.right: parent.right
            height: 30
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(200/255, 241/255, 234/255, 0.20) }
                GradientStop { position: 1.0; color: Qt.rgba(63/255, 148/255, 136/255, 0.13) }
            }
            DragHandler { target: null; onActiveChanged: if (active) bridge.startMove() }
        }
    }

    // ── Row 2 — tab strip (bottom 28px) ─────────────────────────────────────
    Item {
        id: tabstrip
        x: 0; y: 30
        width: parent.width; height: 28

        Rectangle {
            anchors.fill: parent
            color: Qt.rgba(42/255, 26/255, 10/255, 217/255)
            DragHandler { target: null; onActiveChanged: if (active) bridge.startMove() }
        }
        Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: "#0a0604" }

        Row {
            id: tabRow
            x: 6; height: 28

            Repeater {
                // bridge lands after the first binding pass — guard the startup frame
                model: bridge ? bridge.tabTitles : []
                delegate: Item {
                    id: tab
                    required property int index
                    required property string modelData
                    height: 28
                    width: Math.min(220, tm.advanceWidth + 46)
                    readonly property bool active: bridge ? index === bridge.activeIndex : false

                    TextMetrics { id: tm; font.pixelSize: 12; text: tab.modelData }

                    // active jewel
                    Rectangle {
                        anchors.fill: parent
                        visible: tab.active
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#c8801e" }
                            GradientStop { position: 1.0; color: "#5e3308" }
                        }
                    }
                    // hover (inactive)
                    Rectangle {
                        anchors.fill: parent
                        visible: !tab.active && th.hovered
                        color: Qt.rgba(93/255, 58/255, 28/255, 242/255)
                    }
                    // active top highlight
                    Rectangle {
                        visible: tab.active
                        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
                        height: 1; color: Qt.rgba(1,1,1,0.30)
                    }
                    // came divider before each tab past the first
                    Rectangle { visible: tab.index > 0; anchors.left: parent.left; width: 1; height: parent.height; color: "#0a0604" }

                    Text {
                        id: tlbl
                        anchors.left: parent.left; anchors.leftMargin: 13
                        anchors.right: closeBtn.left; anchors.rightMargin: 4
                        anchors.verticalCenter: parent.verticalCenter
                        text: tab.modelData
                        color: ncde.glow
                        font.pixelSize: 12
                        elide: Text.ElideRight
                    }
                    Text {
                        id: closeBtn
                        anchors.right: parent.right; anchors.rightMargin: 9
                        anchors.verticalCenter: parent.verticalCenter
                        text: "\u00d7"
                        font.pixelSize: 14
                        color: ch.hovered ? "#fb5050" : Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.55)
                        visible: tab.active || th.hovered
                        HoverHandler { id: ch }
                        TapHandler { onTapped: bridge.closeTab(tab.index) }
                    }
                    HoverHandler { id: th }
                    TapHandler { onTapped: bridge.selectTab(tab.index) }
                }
            }

            // new-tab "+"
            Item {
                height: 28; width: 36
                Rectangle { anchors.left: parent.left; width: 1; height: parent.height; color: "#0a0604" }
                Text {
                    anchors.centerIn: parent
                    text: "+"
                    font.pixelSize: 18; font.weight: Font.Light
                    color: nh.hovered ? ncde.glow : Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.55)
                }
                HoverHandler { id: nh }
                TapHandler { onTapped: bridge.newTab() }
            }
        }
    }
}
