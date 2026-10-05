// OrchideeSidebar.qml — Orchidée collapsible sidebar.
// Two sections: Places (quick-access fixed rows) and a lazy folder tree rooted
// at /. Collapse/expand is controlled by width from OrchideeApp (no Behavior).
//
// Thunar model (2026-07-06): a Bin place sits under Places — tap it to browse
// Binnie's bin inside Orchidée; DROP a dragged file on it to toss it (the
// shared freedesktop trash, 24h rewind — Binnie is Glia's father). Every place
// and tree folder also accepts drops → orchidee.moveTo().
import QtQuick 2.15

Item {
    id: sidebar
    clip: true

    signal navigate(string path)
    signal binRequested()                 // open the Bin view in the content pane
    signal tossed(string name)            // a drag landed on the Bin → trashed
    signal moved(string name)             // a drag landed on a place/tree folder
    signal refused()                      // a protected path was refused (Glia explains)

    property bool showHidden: false       // bound from OrchideeApp (Ctrl+H)
    property string currentPath: ""       // bound from OrchideeApp: highlights the open place (Thunar)
    property bool   binActive:   false    // bound from OrchideeApp: the Bin view is open
    onShowHiddenChanged: treeNodes = [{ path: "/", name: "/", depth: 0, expanded: false }]

    function dropOk(src, destDir) {
        if (!src || !src.dragPath || src.dragPath === destDir) return false
        if (orchidee.parentOf(src.dragPath) === destDir) return false
        if (src.dragIsDir && (destDir + "/").indexOf(src.dragPath + "/") === 0) return false
        return true
    }

    NCDEKit { id: k }
    readonly property color goldDeep: k.gilt1
    readonly property color gold1:    k.gilt0
    readonly property color burg4:    k.wine4
    readonly property color ink:      k.ink
    readonly property color cream:    k.surfaceHi

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(k.panelBg2.r, k.panelBg2.g, k.panelBg2.b, 0.7)
    }
    Rectangle {
        anchors.right: parent.right; width: 1; height: parent.height
        color: sidebar.goldDeep; opacity: 0.4
    }

    readonly property var placeDefs: [
        { glyph: "⌂", label: "Home",      path: orchidee.home },
        { glyph: "↓", label: "Downloads", path: orchidee.home + "/Downloads" },
        { glyph: "▤", label: "Documents", path: orchidee.home + "/Documents" },
        { glyph: "▣", label: "Pictures",  path: orchidee.home + "/Pictures" },
        { glyph: "♪", label: "Music",     path: orchidee.home + "/Music" },
        { glyph: "▶", label: "Videos",    path: orchidee.home + "/Videos" },
        { glyph: "⊞", label: "Desktop",   path: orchidee.home + "/Desktop" },
    ]

    // Flat tree model: each node is {path, name, depth, expanded}
    property var treeNodes: [{ path: "/", name: "/", depth: 0, expanded: false }]

    function expandNode(idx) {
        var node = Object.assign({}, treeNodes[idx])
        if (node.expanded) return
        var raw = orchidee.entries(node.path, sidebar.showHidden)
        var children = []
        for (var i = 0; i < raw.length; i++)
            if (raw[i].isDir)
                children.push({ path: raw[i].path, name: raw[i].name,
                                 depth: node.depth + 1, expanded: false })
        node.expanded = true
        treeNodes = treeNodes.slice(0, idx).concat([node])
                             .concat(children).concat(treeNodes.slice(idx + 1))
    }

    function collapseNode(idx) {
        var node = Object.assign({}, treeNodes[idx])
        if (!node.expanded) return
        node.expanded = false
        var end = idx + 1
        while (end < treeNodes.length && treeNodes[end].depth > node.depth) end++
        treeNodes = treeNodes.slice(0, idx).concat([node]).concat(treeNodes.slice(end))
    }

    Flickable {
        anchors.fill: parent
        contentHeight: col.implicitHeight
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        Column {
            id: col
            width: parent.width

            // ── PLACES header ─────────────────────────────────────
            Item {
                width: col.width; height: 24
                Text {
                    anchors.fill: parent; leftPadding: 10
                    verticalAlignment: Text.AlignVCenter
                    text: "PLACES"
                    font.family: theme.titleFont
                    font.pixelSize: theme.fontSmall - theme.scale(1)
                    font.letterSpacing: 1.5; color: sidebar.burg4
                }
            }

            // Place rows
            Repeater {
                model: sidebar.placeDefs
                delegate: Item {
                    width: col.width; height: 28
                    visible: orchidee.pathExists(modelData.path)
                    Rectangle {
                        anchors.fill: parent; anchors.margins: 3; radius: 5
                        color: modelData.path === sidebar.currentPath && !sidebar.binActive
                               ? Qt.rgba(k.wine4.r, k.wine4.g, k.wine4.b, 0.22)
                               : plHov.hovered ? Qt.rgba(139/255,30/255,63/255,0.10) : "transparent"
                        border.width: plDrop.containsDrag ? 2 : 0
                        border.color: sidebar.goldDeep
                    }
                    Row {
                        anchors.fill: parent; anchors.leftMargin: 10; spacing: 8
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            width: 18; horizontalAlignment: Text.AlignHCenter   // one glyph column → labels line up
                            text: modelData.glyph; font.pixelSize: theme.fontSmall; color: sidebar.gold1
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData.label
                            font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing; font.pixelSize: theme.fontSmall
                            color: sidebar.ink
                        }
                    }
                    HoverHandler { id: plHov }
                    TapHandler { onTapped: sidebar.navigate(modelData.path) }
                    DropArea {
                        id: plDrop
                        anchors.fill: parent
                        onDropped: {
                            // a bin item dragged out → restore it INTO this place
                            if (drag.source && drag.source.dragBinName) {
                                if (binnieTrash.restoreTo(drag.source.dragBinName, modelData.path))
                                    sidebar.moved(drag.source.dragBinName)
                                return
                            }
                            if (!sidebar.dropOk(drag.source, modelData.path)) return
                            var nm = orchidee.baseName(drag.source.dragPath)
                            if (orchidee.moveTo(drag.source.dragPath, modelData.path))
                                sidebar.moved(nm)
                        }
                    }
                }
            }

            // ── the BIN — Binnie's shared trash, browsable in place (Thunar) ──
            Item {
                width: col.width; height: 28
                Rectangle {
                    anchors.fill: parent; anchors.margins: 3; radius: 5
                    color: sidebar.binActive ? Qt.rgba(k.wine4.r, k.wine4.g, k.wine4.b, 0.22)
                           : binHov.hovered ? Qt.rgba(139/255,30/255,63/255,0.10) : "transparent"
                    border.width: binDrop.containsDrag ? 2 : 0
                    border.color: sidebar.goldDeep
                }
                Row {
                    anchors.fill: parent; anchors.leftMargin: 10; spacing: 8
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 18; horizontalAlignment: Text.AlignHCenter
                        text: "♻"; font.pixelSize: theme.fontSmall; color: sidebar.gold1
                    }
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: binnieTrash.items.length > 0
                              ? "Bin (" + binnieTrash.items.length + ")"
                              : "Bin"
                        font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing; font.pixelSize: theme.fontSmall
                        color: sidebar.ink
                    }
                }
                HoverHandler { id: binHov }
                TapHandler { onTapped: sidebar.binRequested() }
                DropArea {
                    id: binDrop
                    anchors.fill: parent
                    onDropped: {
                        var src = drag.source
                        if (!src || src.dragBinName) return   // already in the bin
                        if (!src.dragPath) return
                        if (orchidee.isProtected(src.dragPath)) { sidebar.refused(); return }
                        var nm = orchidee.baseName(src.dragPath)
                        if (orchidee.trash(src.dragPath)) sidebar.tossed(nm)
                    }
                }
            }

            // Divider
            Rectangle {
                width: col.width; height: 1
                color: sidebar.goldDeep; opacity: 0.3
            }

            // ── TREE header ───────────────────────────────────────
            Item {
                width: col.width; height: 24
                Text {
                    anchors.fill: parent; leftPadding: 10
                    verticalAlignment: Text.AlignVCenter
                    text: "TREE"
                    font.family: theme.titleFont
                    font.pixelSize: theme.fontSmall - theme.scale(1)
                    font.letterSpacing: 1.5; color: sidebar.burg4
                }
            }

            // Tree nodes
            Repeater {
                model: sidebar.treeNodes
                delegate: Item {
                    id: treeRow
                    width: col.width; height: 26
                    Rectangle {
                        anchors.fill: parent; anchors.margins: 2; radius: 4
                        color: treeHov.hovered ? Qt.rgba(139/255,30/255,63/255,0.08) : "transparent"
                        border.width: treeDrop.containsDrag ? 2 : 0
                        border.color: sidebar.goldDeep
                    }
                    DropArea {
                        id: treeDrop
                        anchors.fill: parent
                        onDropped: {
                            // a bin item dragged out → restore it INTO this folder
                            if (drag.source && drag.source.dragBinName) {
                                if (binnieTrash.restoreTo(drag.source.dragBinName, modelData.path))
                                    sidebar.moved(drag.source.dragBinName)
                                return
                            }
                            if (!sidebar.dropOk(drag.source, modelData.path)) return
                            var nm = orchidee.baseName(drag.source.dragPath)
                            if (orchidee.moveTo(drag.source.dragPath, modelData.path))
                                sidebar.moved(nm)
                        }
                    }
                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: 8 + modelData.depth * 14
                        spacing: 4

                        // Expand/collapse toggle
                        Item {
                            width: 14; height: parent.height
                            Text {
                                anchors.centerIn: parent
                                text: modelData.expanded ? "▾" : "▸"
                                font.pixelSize: theme.fontSmall; color: sidebar.goldDeep
                            }
                            TapHandler {
                                onTapped: {
                                    if (modelData.expanded) sidebar.collapseNode(index)
                                    else                    sidebar.expandNode(index)
                                }
                            }
                        }

                        // Folder name — navigate on tap
                        Item {
                            width: parent.width - 18; height: parent.height
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                width: parent.width
                                elide: Text.ElideRight
                                text: modelData.name
                                font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing; font.pixelSize: theme.fontSmall
                                color: sidebar.ink
                            }
                            TapHandler { onTapped: sidebar.navigate(modelData.path) }
                        }
                    }
                    HoverHandler { id: treeHov }
                }
            }
        }
    }
}
