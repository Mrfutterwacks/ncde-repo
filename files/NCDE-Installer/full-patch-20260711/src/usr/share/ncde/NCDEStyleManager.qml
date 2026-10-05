// NCDEStyleManager.qml — NCDE Style Manager · Mucha skin
// Drop-in replacement. All bindings unchanged (ncde.accentName/darkMode/accent,
// ncde.setAccentName, ncde.saveTheme, ncde.activeBg…panelText, ncde.accentMuted/
// glow/border, setOverride*, settings.*Override, settings.saveColorOverrides,
// ncde.themeName). Only the visual skin changed: parchment ground, gilt borders,
// Cinzel/Cormorant type. TerminalVector kept for hex readouts.
// Live engine colors and named accent swatches are DATA — left intact.

import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: styleManager
    width: 480
    height: col.implicitHeight + 24
    radius: 6
    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop { position: 0; color: ncde.surface }
        GradientStop { position: 1; color: ncde.surfaceAlt }
    }
    border.color: m.gilt1; border.width: 1

    // ── palette ──────────────────────────────────────────────────
    QtObject {
        id: m
        readonly property color paper1: ncde.surface
        readonly property color paper2: ncde.surfaceAlt
        readonly property color paper3: ncde.surfaceAlt
        readonly property color gilt0:  ncde.gilt0
        readonly property color gilt1:  ncde.gilt1
        readonly property color gilt2:  ncde.gilt2
        readonly property color gilt3:  ncde.gilt3
        readonly property color gilt4:  ncde.gilt4
        readonly property color gilt5:  ncde.gilt5
        readonly property color wine1:  ncde.wine1
        readonly property color wine2:  ncde.wine2
        readonly property color wine3:  ncde.wine3
        readonly property color wine4:  ncde.wine4
        readonly property color ink:    ncde.foreground
        readonly property string display: (typeof ncde !== "undefined" && ncde.displayFont) ? ncde.displayFont : "Cinzel Decorative, Cinzel, serif"
        readonly property string serif:   (typeof ncde !== "undefined" && ncde.bodyFont)    ? ncde.bodyFont    : "Cormorant Garamond, serif"
        readonly property string mono:    "TerminalVector"
    }

    // gilt top line (replaces VFD glow line)
    Rectangle {
        anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
        anchors.topMargin: 2; anchors.leftMargin: 2; anchors.rightMargin: 2
        height: 2; color: m.gilt3; opacity: 0.8
    }

    Column {
        id: col
        anchors.left: parent.left;   anchors.leftMargin:  16
        anchors.right: parent.right; anchors.rightMargin: 16
        anchors.top: parent.top;     anchors.topMargin:   14
        spacing: 12

        // ── Header ────────────────────────────────────────────
        Row {
            width: parent.width
            spacing: 10
            Text {
                text: "NCDE STYLE MANAGER"
                color: m.gilt0
                font.pixelSize: theme.fontMedium; font.bold: true; font.family: m.display
                font.letterSpacing: 2
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: ncde.themeName
                color: m.gilt1
                font.pixelSize: theme.fontSmall; font.italic: true; font.family: m.serif
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle { width: parent.width; height: 1; color: m.gilt1; opacity: 0.5 }

        // ── Section: Accent ───────────────────────────────────
        SectionLabel { text: "ACCENT COLOR" }

        Flow {
            width: parent.width; spacing: 5

            Repeater {
                model: [
                    { name: "cyan",   dark: ncde.verd, light: "#C97A2B", label: "Teal"   },
                    { name: "blue",   dark: "#5E81AC", light: "#729FCF", label: "Blue"   },
                    { name: "green",  dark: "#A3BE8C", light: "#8FBC8F", label: "Green"  },
                    { name: "yellow", dark: "#EBCB8B", light: "#EBCB8B", label: "Yellow" },
                    { name: "orange", dark: "#D08770", light: "#E08A36", label: "Orange" },
                    { name: "red",    dark: "#BF616A", light: "#E06C75", label: "Red"    },
                    { name: "purple", dark: "#B48EAD", light: "#B48EAD", label: "Purple" },
                    { name: "pink",   dark: "#C77E9E", light: "#F4A7B9", label: "Pink"   },
                ]

                Item {
                    id: swatch
                    width: 52; height: 48
                    readonly property string accentName: modelData.name
                    readonly property bool   isActive:   ncde.accentName === accentName
                    readonly property color  swatchColor: ncde.darkMode ? modelData.dark : modelData.light

                    Rectangle {
                        anchors.fill: parent; radius: 4
                        color: swatch.isActive
                            ? Qt.rgba(m.gilt3.r, m.gilt3.g, m.gilt3.b, 0.18)
                            : "transparent"
                        border.color: swatch.isActive ? m.gilt3 : Qt.rgba(m.gilt0.r, m.gilt0.g, m.gilt0.b, 0.25)
                        border.width: swatch.isActive ? 2 : 1

                        Column {
                            anchors.centerIn: parent; spacing: 3

                            Rectangle {
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: 28; height: 22; radius: 3
                                color: swatch.swatchColor
                                border.color: m.gilt0; border.width: 1

                                Rectangle { anchors.top:parent.top; anchors.left:parent.left; anchors.right:parent.right
                                    height:1; color:Qt.lighter(swatch.swatchColor,1.5); radius:3 }
                                Rectangle { anchors.bottom:parent.bottom; anchors.left:parent.left; anchors.right:parent.right
                                    height:1; color:Qt.darker(swatch.swatchColor,1.4) }

                                Rectangle {
                                    visible: swatch.isActive
                                    anchors.centerIn: parent
                                    width: 6; height: 6; radius: 3
                                    color: Qt.rgba(1,1,1,0.95)
                                    border.color: m.gilt0; border.width: 0.5
                                }
                            }

                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: modelData.label
                                color: swatch.isActive ? m.gilt0 : m.gilt1
                                font.pixelSize: theme.fontSmall; font.family: m.serif
                                font.bold: swatch.isActive
                            }
                        }
                    }

                    property bool pressed: false
                    scale: pressed ? 0.95 : 1.0
                    Behavior on scale { NumberAnimation { duration: 60; easing.type: Easing.OutExpo } }

                    HoverHandler {}
                    TapHandler {
                        onPressedChanged: swatch.pressed = pressed
                        onTapped: {
                            ncde.setAccentName(swatch.accentName)
                            ncde.saveTheme(settings.configBase + "active-theme.json")
                        }
                    }
                }
            }
        }

        Rectangle { width: parent.width; height: 1; color: m.gilt1; opacity: 0.4 }

        // ── Section: Glass & Surface ──────────────────────────
        SectionLabel { text: "GLASS & SURFACE" }

        Column {
            width: parent.width; spacing: 4

            // ── Tappable override tiles ───────────────────────
            Item {
                width: parent.width; height: 36
                Text {
                    anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                    text: "OVERRIDE"
                    color: m.gilt1; font.pixelSize: theme.fontSmall; font.family: m.serif; font.bold: true
                    font.letterSpacing: 1; width: 110
                }
                Row {
                    anchors.left: parent.left; anchors.leftMargin: 116
                    anchors.verticalCenter: parent.verticalCenter; spacing: 4
                    Repeater {
                        model: [
                            { color: ncde.accent,      label: "Accent", key: "accent"      },
                            { color: ncde.accentMuted, label: "Glass",  key: "accentMuted" },
                            { color: ncde.glow,        label: "Glow",   key: "glow"        },
                            { color: ncde.border,      label: "Border", key: "border"      },
                        ]
                        Column { spacing: 2; anchors.verticalCenter: parent.verticalCenter
                            Rectangle {
                                width: 64; height: 20; radius: 2
                                color: modelData.color
                                border.color: m.gilt0; border.width: 1
                                Rectangle { anchors.top:parent.top; anchors.left:parent.left; anchors.right:parent.right; height:1; color:Qt.lighter(modelData.color,1.5); opacity:0.6 }
                                Rectangle { anchors.bottom:parent.bottom; anchors.left:parent.left; anchors.right:parent.right; height:1; color:Qt.darker(modelData.color,1.5); opacity:0.6 }
                                Text { anchors.centerIn:parent; text:modelData.color.toString().toUpperCase().substring(1,7); color:Qt.rgba(1,1,1,0.8); font.pixelSize: Math.round(8 * (theme.fontMedium / 13.0)); font.family:m.mono }
                                TapHandler { onTapped: colorPopup.openFor(modelData.key, modelData.label) }
                            }
                            Text { anchors.horizontalCenter:parent.horizontalCenter; text:modelData.label; color:m.gilt1; font.pixelSize: theme.fontSmall; font.family:m.serif }
                        }
                    }
                }
            }

            // ── Live reference rows ───────────────────────────
            Text {
                text: "LIVE REFERENCE"
                color: m.gilt1; opacity: 0.7
                font.pixelSize: theme.fontSmall; font.bold: true; font.family: m.display
                font.letterSpacing: 2
            }

            MotifRow {
                label: "ACTIVE WINDOW"
                c1: ncde.activeBg;  l1: "Bg"
                c2: ncde.activeTs;  l2: "TS"
                c3: ncde.activeBs;  l3: "BS"
                c4: ncde.activeFg;  l4: "Fg"
            }
            MotifRow {
                label: "INACTIVE WINDOW"
                c1: ncde.inactiveBg; l1: "Bg"
                c2: ncde.inactiveTs; l2: "TS"
                c3: ncde.inactiveBs; l3: "BS"
                c4: ncde.inactiveFg; l4: "Fg"
            }
            MotifRow {
                label: "PANEL / SHELL"
                c1: ncde.panelBg;      l1: "Bg"
                c2: ncde.topShadow;    l2: "TS"
                c3: ncde.bottomShadow; l3: "BS"
                c4: ncde.panelText;    l4: "Fg"
            }
        }

        Item { height: 4 }
    }

    // ── Apply a hex color override to the target key ──────────────
    function applyColorOverride(key, hex) {
        if (key === "accent")       { ncde.setOverrideAccent(hex);       settings.accentOverride = hex; }
        else if (key === "accentMuted") { ncde.setOverrideAccentMuted(hex);  settings.accentMutedOverride = hex; }
        else if (key === "glow")    { ncde.setOverrideGlow(hex);         settings.glowOverride = hex; }
        else if (key === "border")  { ncde.setOverrideBorder(hex);       settings.borderOverride = hex; }
        settings.saveColorOverrides()
    }

    // ── Color picker popup (tapped from Accent/Glow row) ─────────
    Popup {
        id: colorPopup
        modal: true; closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 240; height: 210
        background: Rectangle {
            radius: 8; border.color: m.gilt0; border.width: 2
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0; color: m.paper1 }
                GradientStop { position: 1; color: m.paper2 }
            }
        }

        property string targetKey: ""
        property string targetLabel: ""
        function openFor(key, label) { targetKey = key; targetLabel = label; hexInput.text = ""; open() }

        Column { spacing: 8; anchors.centerIn: parent; width: parent.width - 24
            Text { text: "Pick " + colorPopup.targetLabel; color: m.gilt0; font.pixelSize: theme.fontMedium; font.bold: true; font.family: m.display }

            Flow { spacing: 4; width: parent.width
                Repeater {
                    model: ["", "#FFFFFF",ncde.verd,"#5E81AC","#A3BE8C","#D08770","#BF616A","#B48EAD","#EBCB8B"]
                    Rectangle {
                        width: 24; height: 24; radius: 12
                        border.width: 1; border.color: m.gilt0
                        color: modelData || "transparent"
                        Text { text:"↺"; visible:parent.color==="transparent"; color:m.gilt1; font.pixelSize: theme.fontMedium; anchors.centerIn:parent }
                        TapHandler { onTapped: { applyColorOverride(colorPopup.targetKey, modelData); colorPopup.close() } }
                    }
                }
            }

            Row { spacing: 6; width: parent.width
                Text { text:"#"; color:m.gilt1; font.pixelSize: theme.fontMedium; font.family:m.mono; anchors.verticalCenter:parent.verticalCenter }
                Rectangle { width:80; height:22; radius:3; color:Qt.rgba(0,0,0,0.12); border.color:m.gilt1; border.width:1
                    TextInput {
                        id: hexInput; anchors.fill:parent; anchors.margins:3
                        verticalAlignment: TextInput.AlignVCenter
                        color:m.ink; font.pixelSize: theme.fontSmall; font.family:m.mono
                        onEditingFinished: {
                            var t = text.trim()
                            if (t.length===6) t="#"+t
                            if (/^#[0-9A-Fa-f]{6}$/.test(t)) { applyColorOverride(colorPopup.targetKey, t); colorPopup.close() }
                        }
                    }
                }
                Rectangle { width:50; height:22; radius:4; border.color:m.gilt0; border.width:1
                    gradient: Gradient {
                        orientation: Gradient.Vertical
                        GradientStop { position: 0; color: m.gilt4 }
                        GradientStop { position: 1; color: m.gilt3 }
                    }
                    Text { anchors.centerIn:parent; text:"Set"; color:m.wine1; font.pixelSize: theme.fontSmall; font.family:m.display; font.bold:true }
                    TapHandler { onTapped: {
                        var t = hexInput.text.trim()
                        if (t.length===6) t="#"+t
                        if (/^#[0-9A-Fa-f]{6}$/.test(t)) { applyColorOverride(colorPopup.targetKey, t); colorPopup.close() }
                    }}
                }
            }

            Rectangle { width:parent.width; height:22; radius:3; color:Qt.rgba(0,0,0,0.10); border.color:m.gilt1; border.width:1
                Text { anchors.centerIn:parent; text:"Reset to auto (use theme)"; color:m.gilt1; font.pixelSize: theme.fontSmall; font.family:m.serif; font.italic:true }
                TapHandler { onTapped: { applyColorOverride(colorPopup.targetKey, ""); colorPopup.close() } }
            }
        }
    }

    // ── Section label component ───────────────────────────────
    component SectionLabel: Text {
        color: m.gilt0
        font.pixelSize: theme.fontSmall; font.bold: true; font.family: m.display
        font.letterSpacing: 2
    }

    // ── Motif color row — shows 4 swatches with labels ────────
    component MotifRow: Item {
        width: parent.width; height: 36
        property string label: ""
        property color c1; property string l1: ""
        property color c2; property string l2: ""
        property color c3; property string l3: ""
        property color c4; property string l4: ""

        Text {
            anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
            text: label
            color: m.gilt1; font.pixelSize: theme.fontSmall
            font.family: m.serif; font.bold: true; font.letterSpacing: 1
            width: 110
        }

        Row {
            anchors.left: parent.left; anchors.leftMargin: 116
            anchors.verticalCenter: parent.verticalCenter
            spacing: 4

            Repeater {
                model: [
                    { color: c1, label: l1 },
                    { color: c2, label: l2 },
                    { color: c3, label: l3 },
                    { color: c4, label: l4 },
                ]

                Column {
                    spacing: 2
                    anchors.verticalCenter: parent.verticalCenter

                    Rectangle {
                        width: 64; height: 20; radius: 2
                        color: modelData.color
                        border.color: m.gilt0; border.width: 1

                        Rectangle {
                            anchors.top:parent.top; anchors.left:parent.left; anchors.right:parent.right
                            height:1; color:Qt.lighter(modelData.color,1.5); opacity:0.6 }
                        Rectangle {
                            anchors.bottom:parent.bottom; anchors.left:parent.left; anchors.right:parent.right
                            height:1; color:Qt.darker(modelData.color,1.5); opacity:0.6 }

                        Text {
                            anchors.centerIn: parent
                            text: modelData.color.toString().toUpperCase().substring(1,7)
                            color: Qt.rgba(1,1,1,0.8)
                            font.pixelSize: theme.fontSmall; font.family: m.mono
                        }
                    }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: modelData.label
                        color: m.gilt1; font.pixelSize: theme.fontSmall; font.family: m.serif
                    }
                }
            }
        }
    }
}
