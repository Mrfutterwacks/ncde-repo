// DockPrefs.qml — Dock preferences panel · Mucha skin
// Drop-in replacement. All bindings unchanged (settings.dock*, saveDockPrefs,
// dockApps/setDockApps, MuchaIcon, themeManager, settings.assetBase).
// Only the visual skin changed: parchment ground, gilt borders, brass sliders,
// Cinzel/Cormorant type. TerminalVector kept for numeric/exec readouts.
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: dockPrefs

    // ── palette (matches SettingsPanel mucha tokens) ─────────────
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
        readonly property string display: ncde.displayFont
        readonly property string serif:   ncde.bodyFont
        readonly property string mono:    ncde.monoFont
    }

    // ── Functions at Item level so they're accessible everywhere ─
    function reloadApps() {
        dockAppsModel.clear()
        var apps = settings.dockApps
        for (var i = 0; i < apps.length; i++)
            dockAppsModel.append(apps[i])
    }

    function saveApps() {
        var apps = []
        for (var i = 0; i < dockAppsModel.count; i++)
            apps.push({
                name: dockAppsModel.get(i).name,
                icon: dockAppsModel.get(i).icon,
                exec: dockAppsModel.get(i).exec
            })
        settings.setDockApps(apps)
        settings.saveDockPrefs()
    }

    Component.onCompleted: reloadApps()

    Connections {
        target: settings
        function onDockPrefsChanged() { reloadApps() }
    }

    ListModel { id: dockAppsModel }

    // ── Reusable styled components ────────────────────────────────
    component PrefLabel: Text {
        color: m.gilt1; font.pixelSize: theme.fontMedium; font.family: m.serif
        font.bold: true; width: 110
        anchors.verticalCenter: parent ? parent.verticalCenter : undefined
    }

    component ValueLabel: Text {
        color: m.ink; font.pixelSize: theme.fontSmall; font.family: m.mono
        width: 56; horizontalAlignment: Text.AlignRight
        anchors.verticalCenter: parent ? parent.verticalCenter : undefined
    }

    // Mucha section header — gilt rule + Cinzel caps
    component SectionHead: Row {
        property string text: ""
        width: parent ? parent.width : 0
        spacing: 12
        Text {
            text: parent.text
            color: m.gilt0; font.family: m.display; font.bold: true
            font.pixelSize: theme.fontSmall; font.letterSpacing: 3
            anchors.verticalCenter: parent.verticalCenter
        }
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - 220; height: 1; color: m.gilt1; opacity: 0.55
        }
    }

    // Brass-knob slider on a gold track (matches SettingsOrnSlider look)
    component PrefSlider: Slider {
        height: 24
        background: Rectangle {
            height: 6; radius: 3
            anchors.verticalCenter: parent.verticalCenter
            border.color: m.gilt0; border.width: 1
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0; color: m.gilt2 }
                GradientStop { position: 1; color: m.gilt1 }
            }
            Rectangle {
                width: parent.width * parent.parent.visualPosition
                height: parent.height; radius: parent.radius
                border.color: m.gilt0; border.width: 1
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0; color: m.wine4 }
                    GradientStop { position: 1; color: m.wine2 }
                }
                Behavior on width { NumberAnimation { duration: 60 } }
            }
        }
        handle: Rectangle {
            x: parent.leftPadding + parent.visualPosition * (parent.availableWidth - width)
            y: parent.topPadding + parent.availableHeight / 2 - height / 2
            width: 20; height: 20; radius: 10
            border.color: m.gilt0; border.width: 2
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0;    color: m.gilt5 }
                GradientStop { position: 0.55; color: m.gilt3 }
                GradientStop { position: 1;    color: m.gilt0 }
            }
            Rectangle {
                anchors.centerIn: parent; width: 5; height: 5; radius: 2.5
                color: m.gilt0; border.color: m.gilt4; border.width: 1
            }
        }
    }

    ScrollView {
        anchors.fill: parent
        contentWidth: parent.width
        clip: true

        Column {
            id: prefColumn
            width: dockPrefs.width - 12
            x: 4
            spacing: 0

            // ── SETTINGS SECTION ─────────────────────────────────
            Item { width: parent.width; height: 10 }
            SectionHead { text: "DOCK SETTINGS" }
            Item { width: parent.width; height: 10 }

            // Icon Size
            Row {
                width: parent.width; height: 38; spacing: 8
                PrefLabel { text: "Icon Size" }
                Row {
                    spacing: 4; anchors.verticalCenter: parent.verticalCenter
                    Rectangle {
                        width: 26; height: 26; radius: 4
                        border.color: m.gilt0; border.width: 1.5
                        gradient: Gradient {
                            orientation: Gradient.Vertical
                            GradientStop { position: 0; color: m.gilt4 }
                            GradientStop { position: 1; color: m.gilt3 }
                        }
                        Text { anchors.centerIn: parent; text: "−"
                               color: m.wine1; font.pixelSize: theme.fontLarge; font.bold: true }
                        TapHandler {
                            onTapped: { settings.dockIconSize = Math.max(24, settings.dockIconSize - 4); settings.saveDockPrefs() }
                        }
                    }
                    Rectangle {
                        width: 50; height: 26; radius: 4
                        color: Qt.rgba(0,0,0,0.10)
                        border.color: m.gilt1; border.width: 1
                        TextInput {
                            anchors.centerIn: parent
                            width: parent.width - 8
                            text: settings.dockIconSize
                            color: m.ink; font.pixelSize: theme.fontSmall
                            font.family: m.mono
                            horizontalAlignment: TextInput.AlignHCenter
                            validator: IntValidator { bottom: 24; top: 96 }
                            onEditingFinished: settings.dockIconSize = parseInt(text) || 48
                        }
                    }
                    Rectangle {
                        width: 26; height: 26; radius: 4
                        border.color: m.gilt0; border.width: 1.5
                        gradient: Gradient {
                            orientation: Gradient.Vertical
                            GradientStop { position: 0; color: m.gilt4 }
                            GradientStop { position: 1; color: m.gilt3 }
                        }
                        Text { anchors.centerIn: parent; text: "+"
                               color: m.wine1; font.pixelSize: theme.fontLarge; font.bold: true }
                        TapHandler {
                            onTapped: { settings.dockIconSize = Math.min(96, settings.dockIconSize + 4); settings.saveDockPrefs() }
                        }
                    }
                    Text { text: "px"; color: m.gilt1; font.pixelSize: theme.fontSmall; font.family: m.mono
                           anchors.verticalCenter: parent.verticalCenter }
                }
            }

            // Spacing
            Row {
                width: parent.width; height: 38; spacing: 8
                PrefLabel { text: "Icon Spacing" }
                PrefSlider {
                    id: spacingSlider
                    width: parent.width - 180; from: 0; to: 20
                    value: settings.dockSpacing
                    onMoved: settings.dockSpacing = Math.round(value)
                    onPressedChanged: if (!pressed) settings.saveDockPrefs()
                }
                ValueLabel { text: settings.dockSpacing + " px" }
            }

            // Zoom Level
            Row {
                width: parent.width; height: 38; spacing: 8
                PrefLabel { text: "Zoom Level" }
                PrefSlider {
                    width: parent.width - 180; from: 1.0; to: 2.5
                    value: settings.dockZoomPercent
                    onMoved: settings.dockZoomPercent = Math.round(value * 100) / 100
                    onPressedChanged: if (!pressed) settings.saveDockPrefs()
                }
                ValueLabel { text: settings.dockZoomPercent.toFixed(2) + "×" }
            }

            // Zoom Radius
            Row {
                width: parent.width; height: 38; spacing: 8
                PrefLabel { text: "Zoom Radius" }
                PrefSlider {
                    width: parent.width - 180; from: 48; to: 200
                    value: settings.dockZoomRange
                    onMoved: settings.dockZoomRange = Math.round(value)
                    onPressedChanged: if (!pressed) settings.saveDockPrefs()
                }
                ValueLabel {
                    text: settings.dockZoomRange <= 64 ? "Tight" :
                          settings.dockZoomRange >= 170 ? "Wide" : "Medium"
                }
            }

            // Animation Speed
            Row {
                width: parent.width; height: 38; spacing: 8
                PrefLabel { text: "Anim Speed" }
                PrefSlider {
                    width: parent.width - 180; from: 20; to: 400
                    value: settings.dockAnimSpeed
                    onMoved: settings.dockAnimSpeed = Math.round(value)
                    onPressedChanged: if (!pressed) settings.saveDockPrefs()
                }
                ValueLabel {
                    text: settings.dockAnimSpeed <= 60 ? "Instant" :
                          settings.dockAnimSpeed >= 300 ? "Slow" : "Normal"
                }
            }

            Item { width: parent.width; height: 10 }
            SectionHead { text: "SPRING FEEL" }
            Item { width: parent.width; height: 6 }

            // Presets
            Row {
                width: parent.width; height: 32; spacing: 6
                Repeater {
                    model: [
                        { n: "Jelly",   spring: 1.8,  damping: 0.08, mass: 0.5 },
                        { n: "Tiffany", spring: 4.6,  damping: 0.16, mass: 0.9 },
                        { n: "Precise", spring: 9.0,  damping: 0.65, mass: 0.4 }
                    ]
                    Rectangle {
                        width: (parent.width - 12) / 3; height: 30; radius: 6
                        property bool active: Math.abs(settings.dockMagSpring  - modelData.spring)  < 0.01 &&
                                              Math.abs(settings.dockMagDamping - modelData.damping) < 0.01 &&
                                              Math.abs(settings.dockMagMass    - modelData.mass)    < 0.01
                        border.color: active ? m.gilt0 : m.gilt1; border.width: active ? 2 : 1
                        gradient: Gradient {
                            orientation: Gradient.Vertical
                            GradientStop { position: 0; color: active ? m.gilt4 : m.paper1 }
                            GradientStop { position: 1; color: active ? m.gilt3 : m.paper2 }
                        }
                        Text {
                            anchors.centerIn: parent; text: modelData.n
                            color: parent.active ? m.wine1 : m.gilt1
                            font.pixelSize: theme.fontSmall; font.family: m.display; font.bold: true
                        }
                        TapHandler { onTapped: {
                            settings.dockMagSpring  = modelData.spring
                            settings.dockMagDamping = modelData.damping
                            settings.dockMagMass    = modelData.mass
                            settings.saveDockPrefs()
                        } }
                    }
                }
            }

            Item { width: parent.width; height: 4 }

            // Spring (snap speed)
            Row {
                width: parent.width; height: 38; spacing: 8
                PrefLabel { text: "Snap" }
                PrefSlider {
                    width: parent.width - 180; from: 1.0; to: 12.0
                    value: settings.dockMagSpring
                    onMoved: settings.dockMagSpring = Math.round(value * 10) / 10
                    onPressedChanged: if (!pressed) settings.saveDockPrefs()
                }
                ValueLabel {
                    text: settings.dockMagSpring <= 2.0  ? "Drift" :
                          settings.dockMagSpring >= 9.0  ? "Snap"  : "Glass"
                }
            }

            // Damping (bounce)
            Row {
                width: parent.width; height: 38; spacing: 8
                PrefLabel { text: "Bounce" }
                PrefSlider {
                    width: parent.width - 180; from: 0.05; to: 0.80
                    value: settings.dockMagDamping
                    onMoved: settings.dockMagDamping = Math.round(value * 100) / 100
                    onPressedChanged: if (!pressed) settings.saveDockPrefs()
                }
                ValueLabel {
                    text: settings.dockMagDamping <= 0.10 ? "Jelly" :
                          settings.dockMagDamping >= 0.55 ? "Silk"  : "Bead"
                }
            }

            // Mass (inertia / weight)
            Row {
                width: parent.width; height: 38; spacing: 8
                PrefLabel { text: "Weight" }
                PrefSlider {
                    width: parent.width - 180; from: 0.3; to: 2.0
                    value: settings.dockMagMass
                    onMoved: settings.dockMagMass = Math.round(value * 10) / 10
                    onPressedChanged: if (!pressed) settings.saveDockPrefs()
                }
                ValueLabel {
                    text: settings.dockMagMass <= 0.45 ? "Feather" :
                          settings.dockMagMass >= 1.5  ? "Amber"   : "Glass"
                }
            }

            Item { width: parent.width; height: 6 }

            // Save button
            Rectangle {
                width: 130; height: 30; radius: 6
                border.color: m.gilt0; border.width: 2
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0; color: m.gilt4 }
                    GradientStop { position: 1; color: m.gilt3 }
                }
                Text { anchors.centerIn: parent; text: "Save Settings"
                       color: m.wine1; font.pixelSize: theme.fontSmall; font.family: m.display; font.bold: true }
                TapHandler { onTapped: settings.saveDockPrefs() }
            }

            // ── APPS SECTION ──────────────────────────────────────
            Item { width: parent.width; height: 14 }
            Rectangle { width: parent.width; height: 1; color: m.gilt1; opacity: 0.5 }
            Item { width: parent.width; height: 10 }

            SectionHead { text: "DOCK APPS" }
            Item { width: parent.width; height: 8 }

            // Column headers
            Row {
                width: parent.width; height: 20; spacing: 0
                Text { width: 36;  text: "Icon"; color: m.gilt1; font.pixelSize: theme.fontSmall
                       font.family: m.serif; font.bold: true }
                Text { width: 130; text: "Name"; color: m.gilt1; font.pixelSize: theme.fontSmall
                       font.family: m.serif; font.bold: true }
                Text { width: parent.width - 36 - 130 - 32
                       text: "Exec Command"; color: m.gilt1; font.pixelSize: theme.fontSmall
                       font.family: m.serif; font.bold: true }
            }

            Item { width: parent.width; height: 4 }

            // Apps list
            Column {
                width: parent.width
                spacing: 4

                Repeater {
                    model: dockAppsModel

                    Rectangle {
                        width: prefColumn.width; height: 36; radius: 4
                        color: Qt.rgba(m.paper1.r, m.paper1.g, m.paper1.b, 0.55)
                        border.color: m.gilt1; border.width: 1

                        Row {
                            anchors.fill: parent; anchors.margins: 4; spacing: 4

                            // Icon preview — pure QML
                            MuchaIcon {
                                width: 26; height: 26; size: 26
                                appName: model.name
                                accentColor: ncde.accent
                                glowColor:   ncde.glow
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            // Name field
                            Rectangle {
                                width: 126; height: parent.height - 6
                                anchors.verticalCenter: parent.verticalCenter
                                color: Qt.rgba(0,0,0,0.10); border.color: m.gilt1; border.width: 1; radius: 3
                                TextInput {
                                    anchors.fill: parent; anchors.margins: 5
                                    verticalAlignment: TextInput.AlignVCenter
                                    text: model.name; color: m.ink; font.pixelSize: theme.fontSmall
                                    font.family: m.serif; selectByMouse: true
                                    onEditingFinished: {
                                        dockAppsModel.setProperty(index, "name", text)
                                        dockPrefs.saveApps()
                                    }
                                }
                            }

                            // Exec field
                            Rectangle {
                                width: parent.width - 26 - 126 - 28 - 20
                                height: parent.height - 6
                                anchors.verticalCenter: parent.verticalCenter
                                color: Qt.rgba(0,0,0,0.10); border.color: m.gilt1; border.width: 1; radius: 3
                                TextInput {
                                    anchors.fill: parent; anchors.margins: 5
                                    verticalAlignment: TextInput.AlignVCenter
                                    text: model.exec; color: m.ink; font.pixelSize: theme.fontSmall
                                    font.family: m.mono; selectByMouse: true
                                    onEditingFinished: {
                                        dockAppsModel.setProperty(index, "exec", text)
                                        dockPrefs.saveApps()
                                    }
                                }
                            }

                            // Delete button
                            Rectangle {
                                width: 26; height: parent.height - 6
                                anchors.verticalCenter: parent.verticalCenter
                                radius: 3; border.color: m.gilt0; border.width: 1
                                gradient: Gradient {
                                    orientation: Gradient.Vertical
                                    GradientStop { position: 0; color: m.wine3 }
                                    GradientStop { position: 1; color: m.wine1 }
                                }
                                Text { anchors.centerIn: parent; text: "✕"
                                       color: m.gilt4; font.pixelSize: theme.fontSmall }
                                TapHandler {
                                    onTapped: {
                                        dockAppsModel.remove(index)
                                        dockPrefs.saveApps()
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Item { width: parent.width; height: 8 }

            // Add App button
            Rectangle {
                width: 110; height: 30; radius: 6
                border.color: m.gilt0; border.width: 2
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0; color: m.paper1 }
                    GradientStop { position: 1; color: m.paper2 }
                }
                Text { anchors.centerIn: parent; text: "+ Add App"
                       color: m.gilt0; font.pixelSize: theme.fontSmall; font.family: m.display; font.bold: true }
                TapHandler {
                    onTapped: {
                        dockAppsModel.append({ name: "New App", icon: "", exec: "" })
                        dockPrefs.saveApps()
                    }
                }
            }

            Item { width: parent.width; height: 16 }
        }
    }
}
