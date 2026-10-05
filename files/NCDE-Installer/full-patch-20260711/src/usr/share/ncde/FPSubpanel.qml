// FPSubpanel.qml — CDE Sub-Panel Drawer
// Slides up from the Front Panel with OutExpo hydraulic easing
// Contains tool groups — the CDE signature feature

import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: panel

    property string label:      ""
    property string groupLabel: ""
    property string iconBase:   ""
    property var    items:      []
    property bool   isOpen:     false

    // ── Size ──────────────────────────────────────────────────────
    width:  Math.max(200, itemsRow.width + 24)
    height: isOpen ? contentCol.implicitHeight + 24 : 0
    clip:   true
    z:      600

    // ── Hydraulic slide — OutExpo ─────────────────────────────────
    Behavior on height {
        NumberAnimation { duration: 250; easing.type: Easing.OutExpo }
    }

    function toggle() { isOpen = !isOpen }
    function close()  { isOpen = false   }

    // ── Panel background ──────────────────────────────────────────
    Rectangle {
        anchors.fill: parent
        color:        ncde.popupBg
        border.color: ncde.border
        border.width: 1
        visible:      panel.isOpen

        // Top glow accent — VFD style
        Rectangle {
            anchors.top:   parent.top
            anchors.left:  parent.left
            anchors.right: parent.right
            height: 2
            color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.75)
        }

        // 3D bevel top highlight
        Rectangle {
            anchors.top:   parent.top; anchors.topMargin: 2
            anchors.left:  parent.left
            anchors.right: parent.right
            height: 1
            color: ncde.topShadow; opacity: 0.6
        }
    }

    // ── Content ───────────────────────────────────────────────────
    Column {
        id: contentCol
        anchors.left:   parent.left;  anchors.leftMargin:  12
        anchors.right:  parent.right; anchors.rightMargin: 12
        anchors.top:    parent.top;   anchors.topMargin:   12
        spacing: 8
        visible: panel.isOpen

        // Subpanel label
        Text {
            text:  panel.groupLabel.toUpperCase()
            color: ncde.glow
            font.pixelSize: SetTheme.sm
            font.bold: true
            font.family: "TerminalVector"
            font.letterSpacing: 1.5
        }

        // Separator
        Rectangle {
            width: parent.width; height: 1
            color: ncde.border; opacity: 0.5
        }

        // Items
        Row {
            id: itemsRow
            spacing: 8

            Repeater {
                model: panel.items

                Column {
                    spacing: 3

                    // Icon button with 1px press depth
                    Item {
                        id: btn
                        width: 44; height: 44
                        anchors.horizontalCenter: parent.horizontalCenter

                        property bool pressed: false
                        property bool hovered: false

                        Rectangle {
                            anchors.fill: parent
                            color: btn.pressed ? Qt.rgba(ncde.activeBg.r,ncde.activeBg.g,ncde.activeBg.b,0.35)
                                 : btn.hovered ? Qt.rgba(ncde.surface.r,ncde.surface.g,ncde.surface.b,0.6)
                                 : "transparent"
                            border.color: btn.hovered ? ncde.border : "transparent"
                            border.width: 1

                            // 3D bevel on hover — Motif tactile
                            Rectangle {
                                visible: btn.hovered && !btn.pressed
                                anchors.top:   parent.top
                                anchors.left:  parent.left
                                anchors.right: parent.right
                                height: 1
                                color: ncde.topShadow
                            }
                            Rectangle {
                                visible: btn.hovered && !btn.pressed
                                anchors.bottom: parent.bottom
                                anchors.left:   parent.left
                                anchors.right:  parent.right
                                height: 1
                                color: ncde.bottomShadow
                            }
                        }

                        Image {
                            anchors.centerIn: parent
                            width: 32; height: 32
                            // 1px press offset
                            anchors.verticalCenterOffset: btn.pressed ? 1 : 0
                            Behavior on anchors.verticalCenterOffset {
                                NumberAnimation { duration: 60; easing.type: Easing.OutExpo }
                            }
                            source: "file://" + panel.iconBase + modelData.icon
                            fillMode: Image.PreserveAspectFit
                            smooth: true
                        }

                        HoverHandler { onHoveredChanged: btn.hovered = hovered }
                        TapHandler {
                            onPressedChanged: btn.pressed = pressed
                            onTapped: {
                                launcher.launchExec(modelData.exec)
                                panel.close()
                            }
                        }
                    }

                    // Label
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text:  modelData.label
                        color: ncde.panelText
                        font.pixelSize: SetTheme.sm; font.family: "TerminalVector"
                        elide: Text.ElideRight; width: 48
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }
}
