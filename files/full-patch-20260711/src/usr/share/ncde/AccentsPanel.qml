import QtQuick 2.15
import QtQuick.Layouts 2.15
import "colors.js" as Colors

Item {
    id: panel

    property real currentHue: 36
    property real currentSat: 0.75
    property real currentLightness: 0.45
    readonly property string accentHex: Colors.hslToHex(currentHue, currentSat, currentLightness)
    readonly property var derived: Colors.derivedPalette(currentHue, currentSat)

    RowLayout {
        anchors.fill: parent
        anchors.margins: 30
        spacing: 40

        // ── LEFT: ColorWheel ──
        ColumnLayout {
            Layout.preferredWidth: 380
            Layout.fillHeight: true
            spacing: 16

            Item { Layout.fillHeight: true }

            ColorWheel {
                id: wheel
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 340
                Layout.preferredHeight: 340
                hue: panel.currentHue
                saturation: panel.currentSat
                onPicked: function(h, s) {
                    panel.currentHue = h;
                    panel.currentSat = s;
                }
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: "CHOIX DU TON"
                font.family: ncde.titleFont; font.weight: Font.Bold
                font.pixelSize: theme.fontSmall; font.letterSpacing: 3; color: ncde.gilt0
            }

            Item { Layout.fillHeight: true }
        }

        // ── RIGHT: swatch + derived + controls ──
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 14

            Item { Layout.fillHeight: true; Layout.preferredHeight: 1 }

            // Main swatch + hex
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 82
                color: "transparent"
                border.color: ncde.gilt0; border.width: 3
                Rectangle {
                    anchors.fill: parent; anchors.margins: 5
                    color: "transparent"; border.color: ncde.gilt3; border.width: 1
                }
                RowLayout {
                    anchors.fill: parent; spacing: 0
                    Rectangle {
                        Layout.fillWidth: true; Layout.fillHeight: true
                        color: panel.accentHex
                        Behavior on color { ColorAnimation { duration: 120 } }
                    }
                    Rectangle {
                        Layout.preferredWidth: 200; Layout.fillHeight: true
                        gradient: Gradient {
                            orientation: Gradient.Vertical
                            GradientStop { position: 0; color: ncde.surface }
                            GradientStop { position: 1; color: ncde.surfaceAlt }
                        }
                        Rectangle {
                            anchors.left: parent.left; width: 2
                            anchors.top: parent.top; anchors.bottom: parent.bottom
                            color: ncde.gilt0
                        }
                        ColumnLayout {
                            anchors.centerIn: parent; spacing: 2
                            Text {
                                text: "PRIMARY ACCENT"
                                font.family: ncde.titleFont; font.weight: Font.Bold
                                font.pixelSize: theme.fontSmall; font.letterSpacing: 3; color: ncde.gilt0
                            }
                            Text {
                                text: panel.accentHex
                                font.family: ncde.bodyFont; font.italic: true; font.pixelSize: theme.fontLarge; color: ncde.wine2
                            }
                        }
                    }
                }
            }

            // Lightness slider
            Item {
                Layout.fillWidth: true; Layout.preferredHeight: 36
                Text {
                    anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                    text: "LIGHTNESS"; font.family: ncde.titleFont; font.weight: Font.Bold
                    font.pixelSize: theme.fontSmall; font.letterSpacing: 2; color: ncde.gilt0
                }

                Rectangle {
                    id: lightTrack
                    anchors.left: parent.left; anchors.leftMargin: 110
                    anchors.right: parent.right; anchors.rightMargin: 16
                    anchors.verticalCenter: parent.verticalCenter
                    height: 14; radius: 7
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0; color: "black" }
                        GradientStop { position: 0.5; color: panel.accentHex }
                        GradientStop { position: 1; color: "white" }
                    }
                    border.color: ncde.gilt0; border.width: 1

                    Rectangle {
                        x: panel.currentLightness * (parent.width - 14)
                        y: 0; width: 14; height: 14; radius: 7
                        color: ncde.surface; border.color: ncde.gilt3; border.width: 2
                        Behavior on x { NumberAnimation { duration: 60 } }
                    }

                    TapHandler {
                        onTapped: function(eventPoint) {
                            panel.currentLightness = Math.max(0, Math.min(1, (eventPoint.position.x - 7) / (lightTrack.width - 14)));
                        }
                    }
                    DragHandler {
                        onActiveChanged: if (!active) panel.currentLightness = Math.max(0, Math.min(1, (centroid.position.x - 7) / (lightTrack.width - 14)));
                        onCentroidChanged: panel.currentLightness = Math.max(0, Math.min(1, (centroid.position.x - 7) / (lightTrack.width - 14)));
                    }
                }
            }

            // Derived palette label
            Item {
                Layout.fillWidth: true; Layout.preferredHeight: 18
                Text {
                    anchors.centerIn: parent
                    text: "\u2014 DERIVED PALETTE \u2014"
                    font.family: ncde.titleFont; font.weight: Font.Bold
                    font.pixelSize: theme.fontSmall; font.letterSpacing: 3.5; color: ncde.gilt0
                }
            }

            // 5 derived chips
            RowLayout {
                Layout.fillWidth: true; spacing: 10
                Repeater {
                    model: ["deep", "shade", "base", "light", "veil"]
                    delegate: ColumnLayout {
                        Layout.fillWidth: true; spacing: 4
                        Rectangle {
                            Layout.fillWidth: true; Layout.preferredHeight: 52
                            color: panel.derived[index]
                            border.color: ncde.gilt0; border.width: 2
                            Behavior on color { ColorAnimation { duration: 120 } }
                            Rectangle {
                                anchors.fill: parent; anchors.margins: 4
                                color: "transparent"; border.color: ncde.gilt3; border.width: 1
                            }
                        }
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            text: modelData.toUpperCase()
                            font.family: ncde.bodyFont; font.italic: true; font.pixelSize: theme.fontSmall; font.letterSpacing: 1.5; color: ncde.gilt0
                        }
                    }
                }
            }

            // Action buttons
            Item {
                Layout.fillWidth: true; Layout.preferredHeight: 40; Layout.topMargin: 12
                Row {
                    anchors.centerIn: parent; spacing: 16
                    Rectangle {
                        width: 120; height: 32; radius: 3
                        color: ncde.wine2; border.color: ncde.gilt3; border.width: 1
                        Text { anchors.centerIn: parent; text: "Apply Accent"; color: ncde.gilt5; font.pixelSize: theme.fontSmall; font.bold: true }
                        TapHandler {
                            onTapped: {
                                ncde.setBaseColor(ncde.panelBg, panel.accentHex, ncde.panelText);
                                ncde.saveTheme(settings.configBase + "active-theme.json");
                            }
                        }
                    }
                    Rectangle {
                        width: 100; height: 32; radius: 3
                        color: "transparent"; border.color: ncde.gilt0; border.width: 1
                        Text { anchors.centerIn: parent; text: "Reset"; color: ncde.gilt0; font.pixelSize: theme.fontSmall; font.family: ncde.bodyFont }
                        TapHandler {
                            onTapped: {
                                ncde.clearCustomBase();
                                ncde.saveTheme(settings.configBase + "active-theme.json");
                            }
                        }
                    }
                }
            }

            Item { Layout.fillHeight: true; Layout.preferredHeight: 1 }
        }
    }

    onCurrentHueChanged: { /* derived palette auto-updates */ }
    onCurrentSatChanged: { /* derived palette auto-updates */ }
}
