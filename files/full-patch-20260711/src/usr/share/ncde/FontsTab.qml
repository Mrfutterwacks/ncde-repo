// FontsTab.qml — font family, weight, italic, scale, spacing, leading, rendering, preview.
// Chip strip replaces OrnDropdown — never uses font.family:modelData on list items.
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: ft
    property var k: SetTheme
    clip: true

    Flickable {
        anchors.fill: parent
        contentHeight: col.height
        interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}

        Column {
            id: col; width: parent.width; spacing: 14

            Text { text: "Fonts"; color: ft.k.wine2; font.family: ft.k.display; font.bold: true; font.pixelSize: k.lg }
            Text { text: "The typeface and its measure."; color: ft.k.inkSoft; font.family: ft.k.fell; font.italic: true; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing }

            Text { text: "FONT FAMILY"; color: ft.k.inkLabel; font.family: ft.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2; topPadding: 4 }

            Text { text: "SANS"; color: ft.k.inkLabel; font.family: ft.k.titles; font.pixelSize: k.sm }
            Flow {
                width: parent.width; spacing: 4
                Repeater {
                    model: ["Noto Sans","Liberation Sans","Ubuntu","Cantarell","Roboto","Open Sans","Fira Sans","Lato"]
                    Rectangle {
                        property bool on: settings.fontFamily === modelData
                        height: 24; radius: 5; width: fc1.implicitWidth + 14
                        border.color: on ? ft.k.gilt0 : ft.k.gilt1; border.width: 1
                        color: on ? ft.k.gilt4 : ft.k.paper0
                        Text { id: fc1; anchors.centerIn: parent; text: modelData; font.family: ft.k.titles; font.pixelSize: k.sm; color: ft.k.ink }
                        TapHandler {
                            onTapped: {
                                settings.fontFamily = modelData
                                settings.saveFontSettings()
                                settings.applyFontSettings()
                            }
                        }
                    }
                }
            }

            Text { text: "SERIF"; color: ft.k.inkLabel; font.family: ft.k.titles; font.pixelSize: k.sm }
            Flow {
                width: parent.width; spacing: 4
                Repeater {
                    model: ["Noto Serif","Liberation Serif","DejaVu Serif","FreeSerif","EB Garamond"]
                    Rectangle {
                        property bool on: settings.fontFamily === modelData
                        height: 24; radius: 5; width: fc2.implicitWidth + 14
                        border.color: on ? ft.k.gilt0 : ft.k.gilt1; border.width: 1
                        color: on ? ft.k.gilt4 : ft.k.paper0
                        Text { id: fc2; anchors.centerIn: parent; text: modelData; font.family: ft.k.titles; font.pixelSize: k.sm; color: ft.k.ink }
                        TapHandler {
                            onTapped: {
                                settings.fontFamily = modelData
                                settings.saveFontSettings()
                                settings.applyFontSettings()
                            }
                        }
                    }
                }
            }

            Text { text: "MONO"; color: ft.k.inkLabel; font.family: ft.k.titles; font.pixelSize: k.sm }
            Flow {
                width: parent.width; spacing: 4
                Repeater {
                    model: ["Noto Sans Mono","Liberation Mono","Ubuntu Mono","Fira Mono","DejaVu Sans Mono"]
                    Rectangle {
                        property bool on: settings.fontFamily === modelData
                        height: 24; radius: 5; width: fc3.implicitWidth + 14
                        border.color: on ? ft.k.gilt0 : ft.k.gilt1; border.width: 1
                        color: on ? ft.k.gilt4 : ft.k.paper0
                        Text { id: fc3; anchors.centerIn: parent; text: modelData; font.family: ft.k.titles; font.pixelSize: k.sm; color: ft.k.ink }
                        TapHandler {
                            onTapped: {
                                settings.fontFamily = modelData
                                settings.saveFontSettings()
                                settings.applyFontSettings()
                            }
                        }
                    }
                }
            }

            Row {
                width: parent.width; spacing: 10
                Text { text: "Custom"; width: 50; color: ft.k.inkLabel; font.family: ft.k.titles; font.pixelSize: k.sm; anchors.verticalCenter: parent.verticalCenter }
                Rectangle {
                    width: parent.width - 60; height: 26; radius: 5
                    color: Qt.rgba(ft.k.paper0.r, ft.k.paper0.g, ft.k.paper0.b, 0.08); border.color: ft.k.gilt1; border.width: 1
                    TextInput {
                        anchors.fill: parent; anchors.margins: 6; verticalAlignment: TextInput.AlignVCenter
                        text: settings.fontFamily; color: ft.k.ink; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing
                        onEditingFinished: {
                            settings.fontFamily = text
                            settings.saveFontSettings()
                            settings.applyFontSettings()
                        }
                    }
                }
            }

            Row {
                width: parent.width; spacing: 10
                Text { text: "Weight"; width: 78; color: ft.k.ink; font.family: ft.k.titles; font.pixelSize: k.sm; anchors.verticalCenter: parent.verticalCenter }
                Row {
                    spacing: 4; anchors.verticalCenter: parent.verticalCenter
                    Repeater {
                        model: [{n:"Light",v:300},{n:"Regular",v:400},{n:"Bold",v:700}]
                        Rectangle {
                            height: 24; radius: 5; width: wtxt.implicitWidth + 14
                            property bool on: settings.fontWeight === modelData.v
                            border.color: on ? ft.k.gilt0 : ft.k.gilt1; border.width: 1
                            color: on ? ft.k.gilt4 : ft.k.paper0
                            Text { id: wtxt; anchors.centerIn: parent; text: modelData.n; font.family: ft.k.titles; font.pixelSize: k.sm; color: ft.k.ink }
                            TapHandler { onTapped: { settings.fontWeight = modelData.v; settings.saveFontSettings(); settings.applyFontSettings() } }
                        }
                    }
                }
            }

            Row {
                width: parent.width; spacing: 10
                Text { text: "Italic"; width: 78; color: ft.k.ink; font.family: ft.k.titles; font.pixelSize: k.sm; anchors.verticalCenter: parent.verticalCenter }
                Rectangle {
                    height: 24; width: 60; radius: 5
                    property bool on: settings.fontItalic
                    border.color: on ? ft.k.gilt0 : ft.k.gilt1; border.width: 1
                    color: on ? ft.k.gilt4 : ft.k.paper0
                    Text { anchors.centerIn: parent; text: parent.on ? "On" : "Off"; font.family: ft.k.titles; font.pixelSize: k.sm; color: ft.k.ink }
                    TapHandler { onTapped: { settings.fontItalic = !settings.fontItalic; settings.saveFontSettings(); settings.applyFontSettings() } }
                }
            }

            Rectangle { width: parent.width; height: 1; color: ft.k.gilt1; opacity: 0.4 }

            Text { text: "SCALE"; color: ft.k.inkLabel; font.family: ft.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

            Row { spacing: 12; width: parent.width
                Text { text: "Font size scale"; width: 140; anchors.verticalCenter: parent.verticalCenter
                       color: ft.k.inkLabel; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing }
                NCDESlider {
                    minValue: 6; maxValue: 18
                    value: Math.round(settings.fontSizeScale * 10)
                    onMoved: function(v) { settings.fontSizeScale = v / 10.0; settings.saveFontSettings(); settings.applyFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text { text: settings.fontSizeScale.toFixed(2) + "x"; color: ft.k.ink
                       font.family: ft.k.mono; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; width: 54
                       anchors.verticalCenter: parent.verticalCenter }
            }

            Row { spacing: 12; width: parent.width
                Text { text: "UI scale"; width: 140; anchors.verticalCenter: parent.verticalCenter
                       color: ft.k.inkLabel; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing }
                NCDESlider {
                    minValue: 6; maxValue: 20
                    value: Math.round(settings.uiScale * 10)
                    onMoved: function(v) { settings.uiScale = v / 10.0; settings.saveFontSettings(); settings.applyFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text { text: settings.uiScale.toFixed(1) + "x"; color: ft.k.ink
                       font.family: ft.k.mono; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; width: 54
                       anchors.verticalCenter: parent.verticalCenter }
            }

            Row { spacing: 12; width: parent.width
                Text { text: "Spacing"; width: 140; anchors.verticalCenter: parent.verticalCenter
                       color: ft.k.inkLabel; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing }
                NCDESlider {
                    minValue: 0; maxValue: 19
                    value: Math.round((settings.letterSpacing + 1.5) * 2)
                    onMoved: function(v) { settings.letterSpacing = v * 0.5 - 1.5; settings.saveFontSettings(); settings.applyFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text { text: settings.letterSpacing.toFixed(1) + "px"; color: ft.k.ink
                       font.family: ft.k.mono; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; width: 54
                       anchors.verticalCenter: parent.verticalCenter }
            }

            Row { spacing: 12; width: parent.width
                Text { text: "Leading"; width: 140; anchors.verticalCenter: parent.verticalCenter
                       color: ft.k.inkLabel; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing }
                NCDESlider {
                    minValue: 8; maxValue: 25
                    value: Math.round(settings.lineHeight * 10)
                    onMoved: function(v) { settings.lineHeight = v / 10.0; settings.saveFontSettings(); settings.applyFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text { text: settings.lineHeight.toFixed(1) + "x"; color: ft.k.ink
                       font.family: ft.k.mono; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; width: 54
                       anchors.verticalCenter: parent.verticalCenter }
            }

            Rectangle { width: parent.width; height: 1; color: ft.k.gilt1; opacity: 0.4 }

            Text { text: "TEXT COLOUR"; color: ft.k.inkLabel; font.family: ft.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

            Row { spacing: 12; width: parent.width
                Text { text: "Fill"; width: 78; color: ft.k.ink; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
                Rectangle {
                    width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                    border.color: ft.k.gilt0; border.width: 1.5
                    color: settings.textColor !== "" ? settings.textColor : ft.k.gilt3
                    TapHandler { onTapped: { colorPickerTarget = "fill"; colorPopup.visible = true } }
                }
            }

            Row { spacing: 12; width: parent.width
                Text { text: "Outline"; width: 78; color: ft.k.ink; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
                Row { spacing: 6; anchors.verticalCenter: parent.verticalCenter
                    Rectangle {
                        width: 24; height: 24; radius: 5
                        border.color: !settings.textOutlineEnabled ? ft.k.gilt3 : ft.k.gilt1; border.width: !settings.textOutlineEnabled ? 2 : 1
                        color: ft.k.paper0
                        Text { anchors.centerIn: parent; text: "Off"; font.family: ft.k.titles; font.pixelSize: k.sm; color: ft.k.ink }
                        TapHandler { onTapped: { settings.textOutlineColor = ""; settings.textOutlineEnabled = false; settings.saveFontSettings() } }
                    }
                    Rectangle {
                        width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                        border.color: settings.textOutlineEnabled ? ft.k.gilt3 : ft.k.gilt0; border.width: settings.textOutlineEnabled ? 2 : 1.5
                        color: settings.textOutlineColor !== "" ? settings.textOutlineColor : ft.k.gilt0
                        TapHandler { onTapped: { colorPickerTarget = "outline"; colorPopup.visible = true } }
                    }
                }
            }

            Row { spacing: 12; width: parent.width
                Text { text: "Outline width"; width: 78; color: ft.k.ink; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue: 0; maxValue: 8; value: Math.round(settings.textOutlineWidth * 2)
                    onMoved: function(v){ settings.textOutlineWidth = v / 2.0; settings.saveFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: settings.textOutlineWidth.toFixed(1) + "px"; color: ft.k.ink; font.family: ft.k.mono; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
            }

            Text { text: "SHADOW"; color: ft.k.inkLabel; font.family: ft.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

            Row { spacing: 12; width: parent.width
                Text { text: "Shadow"; width: 78; color: ft.k.ink; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
                Row { spacing: 6; anchors.verticalCenter: parent.verticalCenter
                    Rectangle {
                        width: 24; height: 24; radius: 5
                        border.color: !settings.textShadowEnabled ? ft.k.gilt3 : ft.k.gilt1; border.width: !settings.textShadowEnabled ? 2 : 1
                        color: ft.k.paper0
                        Text { anchors.centerIn: parent; text: "Off"; font.family: ft.k.titles; font.pixelSize: k.sm; color: ft.k.ink }
                        TapHandler { onTapped: { settings.textShadowEnabled = false; settings.saveFontSettings() } }
                    }
                    Rectangle {
                        width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                        border.color: settings.textShadowEnabled ? ft.k.gilt3 : ft.k.gilt0; border.width: settings.textShadowEnabled ? 2 : 1.5
                        color: settings.textShadowColor !== "" ? settings.textShadowColor : "#000000"
                        TapHandler { onTapped: { colorPickerTarget = "shadow"; colorPopup.visible = true } }
                    }
                }
            }

            Row { spacing: 12; width: parent.width
                Text { text: "Blur"; width: 78; color: ft.k.ink; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue: 0; maxValue: 20; value: Math.round(settings.textShadowRadius)
                    onMoved: function(v){ settings.textShadowRadius = v; settings.saveFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: settings.textShadowRadius.toFixed(0) + "px"; color: ft.k.ink; font.family: ft.k.mono; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
            }

            Row { spacing: 12; width: parent.width
                Text { text: "Offset X"; width: 78; color: ft.k.ink; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue: 0; maxValue: 10; value: Math.round(settings.textShadowOffsetX + 5)
                    onMoved: function(v){ settings.textShadowOffsetX = v - 5; settings.saveFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: settings.textShadowOffsetX.toFixed(1) + "px"; color: ft.k.ink; font.family: ft.k.mono; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
            }

            Row { spacing: 12; width: parent.width
                Text { text: "Offset Y"; width: 78; color: ft.k.ink; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue: 0; maxValue: 10; value: Math.round(settings.textShadowOffsetY + 5)
                    onMoved: function(v){ settings.textShadowOffsetY = v - 5; settings.saveFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: settings.textShadowOffsetY.toFixed(1) + "px"; color: ft.k.ink; font.family: ft.k.mono; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing; anchors.verticalCenter: parent.verticalCenter }
            }

            Rectangle { width: parent.width; height: 30; radius: 6
                border.color: ft.k.gilt0; border.width: 2
                gradient: Gradient { GradientStop { position: 0; color: ft.k.gilt4 } GradientStop { position: 1; color: ft.k.gilt3 } }
                Text { anchors.centerIn: parent; text: "Apply Fonts"; color: ft.k.wine1; font.family: ft.k.display; font.bold: true; font.pixelSize: k.sm }
                TapHandler { onTapped: { settings.saveTextColor(); settings.saveFontSettings(); settings.applyFontSettings() } }
            }

            Rectangle { width: parent.width; height: 1; color: ft.k.gilt1; opacity: 0.4 }

            Text { text: "PREVIEW"; color: ft.k.inkLabel; font.family: ft.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }
            Rectangle {
                width: parent.width; height: 80; radius: 8; clip: true
                border.color: ft.k.gilt1; border.width: 1
                gradient: Gradient { GradientStop { position: 0; color: ft.k.paper2 } GradientStop { position: 1; color: ft.k.paper3 } }
                Column {
                    anchors.centerIn: parent; spacing: 2
                    Text { text: "The quick brown fox jumps — 1234"
                           color: settings.textColor !== "" ? settings.textColor : ft.k.gilt3
                           font.family: settings.fontFamily; font.pixelSize: k.lg
                           font.weight: settings.fontWeight; font.italic: settings.fontItalic
                           style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                           styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : ft.k.gilt0
                           anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: "The quick brown fox jumps — 1234567890"
                           color: settings.textColor !== "" ? settings.textColor : ft.k.gilt3
                           font.family: settings.fontFamily; font.pixelSize: k.md
                           font.weight: settings.fontWeight; font.italic: settings.fontItalic
                           anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: "The quick brown fox jumps — 1234567890"
                           color: settings.textColor !== "" ? settings.textColor : ft.k.gilt3
                           font.family: settings.fontFamily; font.pixelSize: k.sm
                           font.weight: settings.fontWeight; font.italic: settings.fontItalic
                           anchors.horizontalCenter: parent.horizontalCenter }
                }
            }

            Item { width: 1; height: 8 }
        }
    }

    // ── colour picker state ────────────────────────────────────────────────
    property string colorPickerTarget: ""

    Rectangle {
        id: colorPopup
        z: 20; anchors.fill: parent; visible: false
        color: Qt.rgba(0,0,0,0.55)
        TapHandler {}

        Rectangle {
            anchors.centerIn: parent; width: 280
            height: cpCol.height + 28; radius: 12
            color: ft.k.paper0; border.color: ft.k.gilt2; border.width: 2

            Column {
                id: cpCol
                anchors.top: parent.top; anchors.topMargin: 14
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: ft.colorPickerTarget === "fill"    ? "Font — Fill"    :
                          ft.colorPickerTarget === "outline" ? "Font — Outline" : "Font — Shadow"
                    color: ft.k.wine2; font.family: ft.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2
                }

                SettingsColorWheel {
                    id: cpWheel; width: 220; height: 220
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter; spacing: 8
                    Rectangle {
                        width: 88; height: 28; radius: 6
                        border.color: ft.k.gilt0; border.width: 2
                        gradient: Gradient { GradientStop { position: 0; color: ft.k.gilt4 } GradientStop { position: 1; color: ft.k.gilt3 } }
                        Text { anchors.centerIn: parent; text: "Set Colour"; color: ft.k.wine1; font.family: ft.k.display; font.bold: true; font.pixelSize: k.sm }
                        TapHandler { onTapped: {
                            var h = cpWheel.currentHex
                            if      (ft.colorPickerTarget === "fill")    { settings.textColor = h }
                            else if (ft.colorPickerTarget === "outline") { settings.textOutlineColor = h; settings.textOutlineEnabled = true }
                            else                                         { settings.textShadowColor = h; settings.textShadowEnabled = true }
                            colorPopup.visible = false
                        } }
                    }
                    Rectangle {
                        width: 78; height: 28; radius: 6; color: "transparent"
                        border.color: ft.k.inkSoft; border.width: 1
                        Text { anchors.centerIn: parent; text: "Cancel"; color: ft.k.inkSoft; font.family: ft.k.serif; font.pixelSize: k.md; font.letterSpacing: ncde.letterSpacing }
                        TapHandler { onTapped: colorPopup.visible = false }
                    }
                }
            }
        }
    }
}
