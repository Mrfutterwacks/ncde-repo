// SettingsPanel.qml — NCDE Settings, left-rail shell (compositor-embedded Rectangle).
// Replaces the old 5-tab horizontal cartouche panel.
// All colors and fonts from SetTheme singleton (property var k: SetTheme).
// Signal wallpaperApplyRequested(string) relayed from WallpapersTab for main.qml compat.
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Rectangle {
    id: settingsPanel
    visible: false
    width: normalWidth; height: normalHeight
    z: 900
    radius: 12
    border.color: k.gilt0; border.width: 2
    clip: true

    // Backward-compat signal and property for main.qml
    signal wallpaperApplyRequested(string path)
    property string wallpaperPath: ""

    property var k: SetTheme
    property bool collapsed: false
    property bool expanded: false

    // A11y fix 2026-07-09: panel + rail geometry follow SetTheme.acc so scaled
    // text never clips (capped to the screen like the expanded state).
    readonly property int normalHeight: Math.min(Math.round(660 * k.acc), Screen.height - 40)
    readonly property int normalWidth:  Math.min(Math.round(940 * k.acc), Screen.width - 40)

    NumberAnimation { id: spHeightAnim; target: settingsPanel; property: "height"; duration: 200; easing.type: Easing.OutCubic }
    NumberAnimation { id: spWidthAnim;  target: settingsPanel; property: "width";  duration: 200; easing.type: Easing.OutCubic }

    onCollapsedChanged: {
        if (collapsed) {
            spHeightAnim.to = Math.round(56 * k.acc); spHeightAnim.start()
        } else {
            spHeightAnim.to = expanded ? Screen.height - 40 : normalHeight; spHeightAnim.start()
        }
    }
    onExpandedChanged: {
        if (expanded) {
            spWidthAnim.to  = Screen.width  - 40; spWidthAnim.start()
            spHeightAnim.to = Screen.height - 40; spHeightAnim.start()
            settingsPanel.x = 20; settingsPanel.y = 20
        } else {
            spWidthAnim.to  = normalWidth;  spWidthAnim.start()
            spHeightAnim.to = collapsed ? Math.round(56 * k.acc) : normalHeight; spHeightAnim.start()
            settingsPanel.x = (Screen.width  - normalWidth)  / 2
            settingsPanel.y = (Screen.height - (collapsed ? Math.round(56 * k.acc) : normalHeight)) / 2
        }
    }

    // Parchment ground
    gradient: Gradient {
        GradientStop { position: 0.0; color: settingsPanel.k.paper0 }
        GradientStop { position: 0.5; color: settingsPanel.k.paper1 }
        GradientStop { position: 1.0; color: settingsPanel.k.paper2 }
    }

    onVisibleChanged: {
        if (visible) {
            settingsPanel.x = (Screen.width  - settingsPanel.width)  / 2
            settingsPanel.y = (Screen.height - settingsPanel.height) / 2
        }
    }

    // ── Tab registry ─────────────────────────────────────────────────
    // Groups: Appearance · Devices · Users · System · Apps · GTK Apps
    // Missing tab files degrade gracefully to "Coming soon" placeholder.
    readonly property var tabs: [
        // ── Appearance ───────────────────────────────────────────────
        { label: "Wallpapers",       group: "Appearance", file: "WallpapersTab.qml"      },
        { label: "Filigree",         group: "Appearance", file: "FiligreeTab.qml"         },
        // "Fonts" retired 2026-07-02 — FontsTab.qml was a near-exact duplicate of Filigree's own
        // "Fonts" tab (same properties, same controls), just with a bespoke color-picker instead of
        // the shared fil.openColorPopup() every other Filigree section uses. Filigree's version is
        // the canonical one now; FontsTab.qml is left in place (never-delete) but unreferenced.
        { label: "Widget Spacing",   group: "Appearance", file: "WidgetSpacingTab.qml"    },
        { label: "Screensaver",      group: "Appearance", file: "ScreensaverTab.qml"      },
        // ── Devices ──────────────────────────────────────────────────
        { label: "Display",          group: "Devices",    file: "DisplayTab.qml"          },
        { label: "Input",            group: "Devices",    file: "InputTab.qml"            },
        { label: "Sound",            group: "Devices",    file: "SoundTab.qml"            },
        { label: "Power",            group: "Devices",    file: "PowerTab.qml"            },
        { label: "Storage",          group: "Devices",    file: "StorageTab.qml"          },
        { label: "Network",          group: "Devices",    file: "NetworkTab.qml"          },
        { label: "Bluetooth",        group: "Devices",    file: "BluetoothTab.qml"        },
        { label: "Printers",         group: "Devices",    file: "PrintersTab.qml"         },
        // ── Users ────────────────────────────────────────────────────
        { label: "Users & Groups",   group: "Users",      file: "UsersTab.qml"            },
        { label: "Security",         group: "Users",      file: "SecurityTab.qml"         },
        { label: "Privacy",          group: "Users",      file: "PrivacyTab.qml"          },
        // ── System ───────────────────────────────────────────────────
        { label: "Dock",             group: "System",     file: "DockTab.qml"             },
        { label: "Date & Time",      group: "System",     file: "DateTimeTab.qml"         },
        { label: "Language & Region",group: "System",     file: "LanguageTab.qml"         },
        { label: "Notifications",    group: "System",     file: "NotificationsTab.qml"    },
        { label: "Session",          group: "System",     file: "SessionTab.qml"          },
        { label: "Accessibility",    group: "System",     file: "AccessibilityTab.qml"    },
        { label: "About",            group: "System",     file: "AboutTab.qml"            },
        // ── Apps ─────────────────────────────────────────────────────
        { label: "Dock Apps",        group: "Apps",       file: "DockAppsTab.qml"         }
    ]
    property int currentTab: 0

    // Open the panel directly at a named tab (Glia System menu → Preferences/
    // Administration route here; label must match tabs[].label, falls back to
    // just opening the panel if the label is unknown).
    function openSection(label) {
        for (var i = 0; i < tabs.length; i++)
            if (tabs[i].label === label) { currentTab = i; break }
        visible = true
    }

    // ── Vellum texture (Concordia light mode only) ───────────────────
    NCDEVellum { anchors.fill: parent; base: "transparent"; intensity: 0.85 }

    // ── Gilt inner hairlines ─────────────────────────────────────────
    Rectangle { anchors.fill: parent; anchors.margins: 3;  radius: 10; color: "transparent"; border.color: settingsPanel.k.gilt4; border.width: 1; opacity: 0.7; z: 1 }
    Rectangle { anchors.fill: parent; anchors.margins: 7;  radius:  7; color: "transparent"; border.color: settingsPanel.k.gilt1; border.width: 1; opacity: 0.45; z: 1 }

    // ── Title bar ────────────────────────────────────────────────────
    Rectangle {
        id: titleBar
        x: 12; y: 10
        width: parent.width - 24; height: Math.round(36 * k.acc)
        radius: 18
        border.color: settingsPanel.k.gilt3; border.width: 2
        gradient: Gradient {
            GradientStop { position: 0; color: settingsPanel.k.wine3 }
            GradientStop { position: 1; color: settingsPanel.k.wine1 }
        }

        // Inner gilt hairline
        Rectangle { anchors.fill: parent; anchors.margins: 4; radius: 14; color: "transparent"; border.color: settingsPanel.k.gilt4; border.width: 1; opacity: 0.7 }

        Text {
            anchors.centerIn: parent
            text: "NCDE SETTINGS"
            color: settingsPanel.k.gilt5
            font.family: settingsPanel.k.display; font.bold: true; font.pixelSize: k.lg; font.letterSpacing: 5
        }

        // Window jewels — gold=collapse, cerulean=expand, rose=close
        Row {
            anchors.right: parent.right; anchors.rightMargin: 14; anchors.verticalCenter: parent.verticalCenter
            spacing: 9
            Rectangle {
                width: 14; height: 14; radius: 7
                color: colHov.hovered ? Qt.lighter(settingsPanel.k.gilt4, 1.15) : settingsPanel.k.gilt4
                border.color: Qt.rgba(0,0,0,.35); border.width: 1.5
                HoverHandler { id: colHov }
                TapHandler { onTapped: { settingsPanel.expanded = false; settingsPanel.collapsed = !settingsPanel.collapsed } }
            }
            Rectangle {
                width: 14; height: 14; radius: 7
                color: expHov.hovered ? Qt.lighter(settingsPanel.k.cer, 1.15) : settingsPanel.k.cer
                border.color: Qt.rgba(0,0,0,.35); border.width: 1.5
                HoverHandler { id: expHov }
                TapHandler { onTapped: { settingsPanel.collapsed = false; settingsPanel.expanded = !settingsPanel.expanded } }
            }
            Rectangle {
                width: 14; height: 14; radius: 7
                color: clsHov.hovered ? Qt.lighter(settingsPanel.k.rose, 1.12) : settingsPanel.k.rose
                border.color: Qt.rgba(0,0,0,.35); border.width: 1.5
                HoverHandler { id: clsHov }
                TapHandler { onTapped: { settingsPanel.collapsed = false; settingsPanel.expanded = false; settingsPanel.visible = false } }
            }
        }

        DragHandler {
            target: settingsPanel
            onActiveChanged: {
                if (!active) {
                    settingsPanel.x = Math.max(0, Math.min(Screen.width  - settingsPanel.width,  settingsPanel.x))
                    settingsPanel.y = Math.max(32, Math.min(Screen.height - settingsPanel.height, settingsPanel.y))
                }
            }
        }
    }

    // ── Left rail ─────────────────────────────────────────────────────
    Rectangle {
        id: rail
        anchors.left: parent.left; anchors.leftMargin: 10
        anchors.top: titleBar.bottom; anchors.topMargin: 10
        anchors.bottom: parent.bottom; anchors.bottomMargin: 10
        width: Math.round(158 * k.acc)
        radius: 8
        color: Qt.rgba(settingsPanel.k.wine1.r, settingsPanel.k.wine1.g, settingsPanel.k.wine1.b, 0.05)
        border.color: settingsPanel.k.gilt1; border.width: 1

        Flickable {
            anchors.fill: parent; anchors.margins: 6
            contentHeight: railCol.height; interactive: contentHeight > height
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: railCol; width: parent.width; spacing: 2

                Repeater {
                    model: ["Appearance", "Devices", "Users", "System", "Apps"]
                    Column {
                        width: parent.width; spacing: 1

                        // Group header
                        Text {
                            text: modelData.toUpperCase()
                            color: settingsPanel.k.gilt1
                            font.family: settingsPanel.k.display; font.bold: true; font.pixelSize: k.md; font.letterSpacing: 2
                            topPadding: index > 0 ? 10 : 4; bottomPadding: 4; leftPadding: 8
                        }
                        Rectangle { width: parent.width - 10; height: 1; x: 5; color: settingsPanel.k.gilt1; opacity: 0.35 }

                        // Tabs in this group
                        Repeater {
                            model: {
                                var group = modelData
                                var arr = []
                                for (var i = 0; i < settingsPanel.tabs.length; i++)
                                    if (settingsPanel.tabs[i].group === group) arr.push(i)
                                return arr
                            }
                            Rectangle {
                                property int tabIndex: modelData
                                property bool sel: settingsPanel.currentTab === tabIndex
                                width: parent.width - 8; x: 4; height: Math.round(28 * k.acc); radius: 6
                                color: sel ? settingsPanel.k.gilt4 : (rHov.hovered ? Qt.rgba(settingsPanel.k.gilt4.r, settingsPanel.k.gilt4.g, settingsPanel.k.gilt4.b, 0.25) : "transparent")
                                border.color: sel ? settingsPanel.k.gilt2 : "transparent"; border.width: 1
                                Text {
                                    anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter
                                    text: settingsPanel.tabs[tabIndex].label
                                    color: sel ? settingsPanel.k.wine1 : settingsPanel.k.ink
                                    font.family: sel ? settingsPanel.k.titles : settingsPanel.k.serif
                                    font.bold: sel; font.pixelSize: k.md
                                }
                                HoverHandler { id: rHov }
                                TapHandler { onTapped: settingsPanel.currentTab = tabIndex }
                            }
                        }
                        Item { width: 1; height: 4 }
                    }
                }
            }
        }
    }

    // ── Content area ─────────────────────────────────────────────────
    Item {
        id: contentArea
        anchors.left: rail.right; anchors.leftMargin: 10
        anchors.right: parent.right; anchors.rightMargin: 14
        anchors.top: titleBar.bottom; anchors.topMargin: 10
        anchors.bottom: parent.bottom; anchors.bottomMargin: 10
        clip: true

        Loader {
            id: tabLoader
            anchors.fill: parent
            source: settingsPanel.tabs[settingsPanel.currentTab].file
        }

        // Graceful placeholder when tab file is missing
        Rectangle {
            anchors.centerIn: parent
            visible: tabLoader.status === Loader.Error
            width: 300; height: 110; radius: 12
            color: settingsPanel.k.paper0; border.color: settingsPanel.k.gilt1; border.width: 1
            Column {
                anchors.centerIn: parent; spacing: 10
                Text { anchors.horizontalCenter: parent.horizontalCenter; text: "Coming soon"
                       color: settingsPanel.k.gilt1; font.family: settingsPanel.k.display; font.bold: true; font.pixelSize: k.lg }
                Text { anchors.horizontalCenter: parent.horizontalCenter
                       text: settingsPanel.tabs[settingsPanel.currentTab].label
                       color: settingsPanel.k.inkSoft; font.family: settingsPanel.k.fell; font.italic: true; font.pixelSize: k.md }
            }
        }

        // Relay WallpapersTab signal to main.qml callers
        Connections {
            target: tabLoader.item
            ignoreUnknownSignals: true
            function onWallpaperApplyRequested(path) {
                settingsPanel.wallpaperApplyRequested(path)
                settingsPanel.wallpaperPath = path
            }
        }
    }
}
