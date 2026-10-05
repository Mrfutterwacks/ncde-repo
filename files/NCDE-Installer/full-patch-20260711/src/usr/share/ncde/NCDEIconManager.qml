// NCDEIconManager.qml — NCDE Icon Manager
// CandyBar-style: browse icons by category, drop a PNG to replace,
// manage icon packs. Every save triggers live reload via ?v= versioning.
import QtQuick
import QtQuick.Controls

Item {
    id: iconMgr

    property string selectedCategory: ""
    property string selectedIcon:     ""
    property string selectedPath:     ""
    property bool   selectedReplaced: false
    property string pendingSource:    ""

    ListModel { id: catModel  }
    ListModel { id: iconModel }
    ListModel { id: packModel }

    function loadCategories() {
        catModel.clear()
        var cats = iconManager.categories()
        for (var i = 0; i < cats.length; i++)
            catModel.append({ name: cats[i], count: iconManager.listIcons(cats[i]).length })
        if (catModel.count > 0 && selectedCategory === "")
            selectCategory(catModel.get(0).name)
    }

    function selectCategory(cat) {
        selectedCategory = cat
        selectedIcon = ""; selectedPath = ""; pendingSource = ""; sourceInput.text = ""
        iconSearch.text = ""
        iconModel.clear()
        var icons = iconManager.listIcons(cat)
        for (var i = 0; i < icons.length; i++) iconModel.append(icons[i])
    }

    function selectIcon(name, path, replaced) {
        selectedIcon    = name
        selectedPath    = path
        selectedReplaced = replaced
        pendingSource   = ""
        sourceInput.text = ""
    }

    function refreshIconModel() {
        var scroll = iconGrid.contentY
        var icons  = iconManager.listIcons(selectedCategory)
        var q      = iconSearch.text.toLowerCase()
        iconModel.clear()
        for (var i = 0; i < icons.length; i++)
            if (q === "" || icons[i].name.toLowerCase().indexOf(q) >= 0)
                iconModel.append(icons[i])
        iconGrid.contentY = scroll
        // Re-select to refresh replaced state
        if (selectedIcon !== "") {
            selectedReplaced = iconManager.isReplaced(selectedCategory, selectedIcon)
            selectedPath     = iconManager.iconFilePath(selectedCategory, selectedIcon)
        }
    }

    function loadPacks() {
        packModel.clear()
        var packs = iconManager.listPacks()
        for (var i = 0; i < packs.length; i++) packModel.append(packs[i])
    }

    Component.onCompleted: { loadCategories(); loadPacks() }

    Connections {
        target: iconManager
        function onCatalogChanged() { loadCategories(); loadPacks() }
    }

    // ── Two-column layout ─────────────────────────────────────────
    Row {
        anchors.fill: parent; spacing: 8

        // ── LEFT: Category list + Pack list ──────────────────────
        Rectangle {
            width: 158; height: parent.height; radius: 4
            color: Qt.rgba(ncde.panelBg.r, ncde.panelBg.g, ncde.panelBg.b, 0.8)
            border.color: ncde.border; border.width: 1
            clip: true

            Column {
                anchors.fill: parent; anchors.margins: 6; spacing: 0

                // ICON SETS header
                Text {
                    text: "ICON SETS"
                    color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.bold: true
                    font.family: "TerminalVector"; font.letterSpacing: 1.5
                    topPadding: 4; bottomPadding: 6
                }

                Repeater {
                    model: catModel
                    Rectangle {
                        width: parent.width; height: 26; radius: 3
                        color: iconMgr.selectedCategory === model.name
                            ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18)
                            : cH.hovered ? Qt.rgba(ncde.surface.r, ncde.surface.g, ncde.surface.b, 0.6)
                            : "transparent"
                        Behavior on color { ColorAnimation { duration: 80 } }

                        Rectangle {
                            anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
                            width: 2; color: ncde.accent
                            visible: iconMgr.selectedCategory === model.name
                        }
                        Row {
                            anchors.left: parent.left; anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter; spacing: 6
                            Text {
                                text: model.name.charAt(0).toUpperCase() + model.name.slice(1)
                                color: iconMgr.selectedCategory === model.name ? ncde.accent : ncde.panelText
                                font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa"
                                font.bold: iconMgr.selectedCategory === model.name
                            }
                            Rectangle {
                                width: cntTxt.width + 6; height: 14; radius: 7
                                color: Qt.rgba(ncde.border.r, ncde.border.g, ncde.border.b, 0.4)
                                anchors.verticalCenter: parent.verticalCenter
                                Text { id: cntTxt; anchors.centerIn: parent; text: model.count
                                       color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.family: "TerminalVector" }
                            }
                        }
                        HoverHandler { id: cH }
                        TapHandler { onTapped: iconMgr.selectCategory(model.name) }
                    }
                }

                // Divider
                Item { width: 1; height: 8 }
                Rectangle { width: parent.width - 8; height: 1; anchors.horizontalCenter: parent.horizontalCenter; color: ncde.border; opacity: 0.4 }
                Item { width: 1; height: 6 }

                // PACKS header
                Text {
                    text: "ICON PACKS"
                    color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.bold: true
                    font.family: "TerminalVector"; font.letterSpacing: 1.5; bottomPadding: 4
                }

                Repeater {
                    model: packModel
                    Rectangle {
                        width: parent.width; height: 30; radius: 3
                        color: pH.hovered ? Qt.rgba(ncde.surface.r, ncde.surface.g, ncde.surface.b, 0.6) : "transparent"
                        Column {
                            anchors.left: parent.left; anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter; spacing: 1
                            Text { text: model.name; color: ncde.panelText; font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa"; elide: Text.ElideRight; width: 130 }
                            Text { text: model.author; color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.family: "TerminalVector"; visible: model.author !== "" }
                        }
                        HoverHandler { id: pH }
                        TapHandler { onTapped: {
                            iconManager.applyPack(model.folder)
                            iconMgr.refreshIconModel()
                        }}
                    }
                }

                Item { width: 1; height: 8 }

                Rectangle {
                    width: parent.width - 8; height: 24; radius: 3
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.12)
                    border.color: ncde.accent; border.width: 1
                    Text { anchors.centerIn: parent; text: "+ Import Pack"; color: ncde.accent; font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa" }
                    TapHandler { onTapped: importDialog.visible = true }
                }

                Item { width: 1; height: 4 }

                Rectangle {
                    width: parent.width - 8; height: 24; radius: 3
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "transparent"
                    border.color: Qt.rgba(ncde.accentMuted.r, ncde.accentMuted.g, ncde.accentMuted.b, 0.45)
                    border.width: 1
                    Text { anchors.centerIn: parent; text: "Restore All"; color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa" }
                    TapHandler { onTapped: {
                        iconManager.restoreAll()
                        iconMgr.refreshIconModel()
                    }}
                }
            }
        }

        // ── RIGHT: Search bar + Icon grid + Action strip ──────────
        Item {
            width: parent.width - 158 - 8; height: parent.height

            // Search bar
            Rectangle {
                id: iconSearchBar
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                height: 28; radius: 4
                color: Qt.rgba(ncde.panelBg.r, ncde.panelBg.g, ncde.panelBg.b, 0.8)
                border.color: ncde.border; border.width: 1
                Row {
                    anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 6
                    Text { text: "🔍"; font.pixelSize: theme.fontSmall; color: ncde.accentMuted; anchors.verticalCenter: parent.verticalCenter }
                    TextInput {
                        id: iconSearch; width: parent.width - 28
                        color: ncde.panelText; font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa"
                        anchors.verticalCenter: parent.verticalCenter
                        onTextChanged: iconMgr.refreshIconModel()
                    }
                }
            }

            // Action strip (slides up from bottom when icon selected)
            Rectangle {
                id: actionStrip
                anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
                height: iconMgr.selectedIcon !== "" ? 94 : 0
                clip: true
                Behavior on height { NumberAnimation { duration: 180; easing.type: Easing.OutExpo } }

                color: Qt.rgba(ncde.panelBg.r, ncde.panelBg.g, ncde.panelBg.b, 0.95)
                border.color: ncde.accent; border.width: 1; radius: 4

                Rectangle {
                    anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                    height: 1; color: ncde.glow
                }

                Row {
                    anchors.fill: parent; anchors.margins: 8; spacing: 10

                    // Current icon preview
                    Rectangle {
                        width: 64; height: 64; radius: 8
                        anchors.verticalCenter: parent.verticalCenter
                        color: Qt.rgba(ncde.surface.r, ncde.surface.g, ncde.surface.b, 0.7)
                        border.color: ncde.border; border.width: 1
                        Image {
                            anchors.centerIn: parent; width: 48; height: 48
                            source: iconMgr.selectedPath !== ""
                                ? "file://" + iconMgr.selectedPath + "?v=" + iconManager.version
                                : ""
                            fillMode: Image.PreserveAspectFit; smooth: true
                        }
                        Text {
                            anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottomMargin: 2
                            text: iconMgr.selectedReplaced ? "CUSTOM" : "ORIGINAL"
                            color: iconMgr.selectedReplaced ? ncde.accent : ncde.accentMuted
                            font.pixelSize: theme.fontSmall; font.family: "TerminalVector"
                        }
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 64 - 10; spacing: 5

                        Text {
                            text: iconMgr.selectedIcon
                            color: ncde.panelText; font.pixelSize: theme.fontSmall; font.family: "TerminalVector"; font.bold: true
                        }

                        // Drop zone / path input
                        Rectangle {
                            width: parent.width; height: 26; radius: 3
                            color: dropZone.containsDrag
                                ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.22)
                                : Qt.rgba(ncde.popupBg.r, ncde.popupBg.g, ncde.popupBg.b, 0.9)
                            border.color: dropZone.containsDrag ? ncde.accent : ncde.border
                            border.width: 1
                            Behavior on color { ColorAnimation { duration: 80 } }

                            TextInput {
                                id: sourceInput
                                anchors.fill: parent; anchors.margins: 6
                                color: ncde.panelText; font.pixelSize: theme.fontSmall; font.family: "TerminalVector"
                                onTextChanged: iconMgr.pendingSource = text
                            }
                            Text {
                                anchors.fill: parent; anchors.margins: 6
                                text: "Drop PNG here or type path..."
                                color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.family: "TerminalVector"
                                visible: sourceInput.text === ""
                            }

                            DropArea {
                                id: dropZone; anchors.fill: parent
                                onDropped: (drop) => {
                                    if (drop.hasUrls) {
                                        var p = drop.urls[0].toString().replace("file://", "")
                                        sourceInput.text = p
                                        drop.acceptProposedAction()
                                    }
                                }
                            }
                        }

                        Row {
                            spacing: 6
                            // Apply
                            Rectangle {
                                width: 72; height: 22; radius: 3
                                color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.20)
                                border.color: ncde.accent; border.width: 1
                                opacity: iconMgr.pendingSource !== "" ? 1.0 : 0.4
                                Text { anchors.centerIn: parent; text: "Apply"; color: ncde.accent; font.pixelSize: theme.fontSmall; font.bold: true; font.family: settings.fontFamily || "Comfortaa" }
                                TapHandler {
                                    enabled: iconMgr.pendingSource !== ""
                                    onTapped: {
                                        if (iconManager.replaceIcon(iconMgr.selectedCategory,
                                                                    iconMgr.selectedIcon,
                                                                    iconMgr.pendingSource)) {
                                            iconMgr.refreshIconModel()
                                            iconMgr.selectIcon(iconMgr.selectedIcon,
                                                iconManager.iconFilePath(iconMgr.selectedCategory, iconMgr.selectedIcon),
                                                true)
                                        }
                                    }
                                }
                            }
                            // Restore
                            Rectangle {
                                width: 72; height: 22; radius: 3
                                color: "transparent"
                                border.color: Qt.rgba(ncde.accentMuted.r, ncde.accentMuted.g, ncde.accentMuted.b, 0.6)
                                border.width: 1
                                opacity: iconMgr.selectedReplaced ? 1.0 : 0.3
                                Text { anchors.centerIn: parent; text: "Restore"; color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa" }
                                TapHandler {
                                    enabled: iconMgr.selectedReplaced
                                    onTapped: {
                                        iconManager.restoreIcon(iconMgr.selectedCategory, iconMgr.selectedIcon)
                                        iconMgr.refreshIconModel()
                                        iconMgr.selectIcon(iconMgr.selectedIcon,
                                            iconManager.iconFilePath(iconMgr.selectedCategory, iconMgr.selectedIcon),
                                            false)
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Icon grid — fills space between search bar and action strip
            GridView {
                id: iconGrid
                anchors.top: iconSearchBar.bottom; anchors.topMargin: 4
                anchors.bottom: actionStrip.top; anchors.bottomMargin: 4
                anchors.left: parent.left; anchors.right: parent.right
                cellWidth: 88; cellHeight: 82
                clip: true; model: iconModel

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AsNeeded
                    background: Rectangle { color: Qt.rgba(ncde.border.r,ncde.border.g,ncde.border.b,0.2); radius:3 }
                    contentItem: Rectangle { implicitWidth:4; radius:3; color: Qt.rgba(ncde.accent.r,ncde.accent.g,ncde.accent.b,0.55) }
                }

                delegate: Item {
                    width: 88; height: 82
                    property bool sel: iconMgr.selectedIcon === model.name

                    Rectangle {
                        anchors.fill: parent; anchors.margins: 3; radius: 6
                        color: sel
                            ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18)
                            : iH.hovered ? Qt.rgba(ncde.surface.r, ncde.surface.g, ncde.surface.b, 0.6)
                            : "transparent"
                        border.color: sel ? ncde.accent : (iH.hovered ? Qt.rgba(ncde.border.r,ncde.border.g,ncde.border.b,0.5) : "transparent")
                        border.width: sel ? 2 : 1
                        Behavior on color { ColorAnimation { duration: 80 } }

                        Column {
                            anchors.centerIn: parent; spacing: 4
                            Image {
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: 40; height: 40
                                source: "file://" + model.path + "?v=" + iconManager.version
                                fillMode: Image.PreserveAspectFit; smooth: true
                                onStatusChanged: if (status === Image.Error) visible = false
                            }
                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: model.name; color: sel ? ncde.accent : ncde.panelText
                                font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa"
                                elide: Text.ElideRight; width: 80
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        // Replaced dot
                        Rectangle {
                            visible: model.replaced
                            anchors.top: parent.top; anchors.right: parent.right
                            anchors.margins: 4
                            width: 7; height: 7; radius: 4; color: ncde.accent
                        }

                        HoverHandler { id: iH }
                        TapHandler { onTapped: iconMgr.selectIcon(model.name, model.path, model.replaced) }
                    }
                }
            }
        }
    }

    // ── Import pack dialog ────────────────────────────────────────
    Rectangle {
        id: importDialog
        visible: false; z: 100
        anchors.centerIn: parent
        width: 420; height: 110; radius: 8
        color: ncde.popupBg; border.color: ncde.border; border.width: 1

        Column {
            anchors.fill: parent; anchors.margins: 14; spacing: 8
            Text { text: "Path to icon pack folder:"; color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.family: "TerminalVector" }
            Rectangle {
                width: parent.width; height: 28; radius: 3
                color: ncde.panelBg; border.color: ncde.border; border.width: 1
                TextInput {
                    id: packPathInput; anchors.fill: parent; anchors.margins: 6
                    color: ncde.panelText; font.pixelSize: theme.fontSmall; font.family: "TerminalVector"
                }
                Text {
                    anchors.fill: parent; anchors.margins: 6
                    text: "~/Downloads/MyIconPack"
                    color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.family: "TerminalVector"
                    visible: packPathInput.text === ""
                }
            }
            Row {
                spacing: 8
                Rectangle {
                    width: 80; height: 26; radius: 3
                    color: Qt.rgba(ncde.accent.r,ncde.accent.g,ncde.accent.b,0.18); border.color: ncde.accent; border.width: 1
                    Text { anchors.centerIn: parent; text: "Import"; color: ncde.accent; font.pixelSize: theme.fontSmall; font.bold: true; font.family: settings.fontFamily || "Comfortaa" }
                    TapHandler { onTapped: {
                        iconManager.importPack(packPathInput.text.replace("~", launcher.homePath()))
                        importDialog.visible = false; packPathInput.text = ""
                    }}
                }
                Rectangle {
                    width: 70; height: 26; radius: 3
                    color: "transparent"; border.color: ncde.border; border.width: 1
                    Text { anchors.centerIn: parent; text: "Cancel"; color: ncde.accentMuted; font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa" }
                    TapHandler { onTapped: { importDialog.visible = false; packPathInput.text = "" } }
                }
            }
        }
    }
}
