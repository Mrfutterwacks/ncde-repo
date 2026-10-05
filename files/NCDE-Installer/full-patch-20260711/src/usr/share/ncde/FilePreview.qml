// FilePreview.qml — Orchidée's leaf pane: shows the chosen file's details (and a
// thumbnail for images). Pure primitives.
import QtQuick 2.15

Item {
    id: pv
    property string path: ""
    width: 240

    property var info: ({})
    onPathChanged: {
        var rows = orchidee.entries(orchidee.parentOf(path), true)
        info = {}
        for (var i = 0; i < rows.length; i++) if (rows[i].path === path) { info = rows[i]; break }
    }

    NCDEKit { id: k }
    readonly property color goldDeep: k.gilt1
    readonly property color ink: k.ink
    readonly property color burg4: k.wine4
    readonly property color gold1: k.gilt0

    Rectangle { anchors.right: parent.right; width: 1; height: parent.height; color: pv.goldDeep; opacity: 0.4 }

    Column {
        anchors.fill: parent
        anchors.margins: 18
        spacing: 12

        // thumb / icon plate
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 150; height: 150; radius: 10
            color: Qt.rgba(246/255,239/255,220/255,0.7)
            border.width: 1.5; border.color: pv.goldDeep
            Image {
                anchors.fill: parent; anchors.margins: 6
                visible: (pv.info.kind === "img")
                source: visible ? ("file://" + pv.path) : ""
                fillMode: Image.PreserveAspectFit; asynchronous: true; cache: true
            }
            Text {
                anchors.centerIn: parent
                visible: pv.info.kind !== "img"
                text: glyph(pv.info.kind)
                font.pixelSize: theme.scale(56); color: pv.gold1
            }
        }

        Text {
            width: parent.width; horizontalAlignment: Text.AlignHCenter; wrapMode: Text.WordWrap
            text: pv.info.name || ""
            font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing; lineHeight: theme.lineHeight; font.pixelSize: theme.fontMedium + theme.scale(2); color: pv.ink
        }
        Rectangle { width: parent.width; height: 1; color: Qt.rgba(138/255,90/255,32/255,0.4) }
        Column {
            width: parent.width; spacing: 4
            DetailRow { k: "Kind"; v: pv.info.type || "" }
            DetailRow { k: "Size"; v: pv.info.size || "\u2014" }
            DetailRow { k: "Where"; v: orchidee.parentOf(pv.path) }
        }
    }

    function glyph(kind) {
        if (kind === "music") return "\u266a"
        if (kind === "video") return "\u25b6"
        if (kind === "dir")   return "\u25b8"
        return "\u25a4"
    }

    component DetailRow: Row {
        property string k: ""
        property string v: ""
        width: parent.width; spacing: 8
        Text { width: 48; text: k; color: pv.gold1
               font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; font.italic: true; font.pixelSize: theme.fontSmall }
        Text { width: parent.width - 56; elide: Text.ElideMiddle; text: v; color: pv.ink
               font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing; font.pixelSize: theme.fontSmall }
    }
}
