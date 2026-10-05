// TrashRow.qml — one row in Binnie's trash list: icon · name/path · 24h rewind
// ring · REWIND · delete-forever. Reads a binnieTrash item record.
import QtQuick 2.15

Item {
    id: row
    property var entry: ({})
    // 2026-07-14, journal-caught live: BinnieApp.qml's ListView delegate
    // onRewind/onForever handler bodies threw "ReferenceError: app is not
    // defined" even though `app` (the root Window id) resolves fine in
    // ordinary property bindings just outside this same delegate (e.g.
    // `app.goldDeep` a few lines up). Researched: ListView delegate signal-
    // handler bodies run in a context that doesn't reliably see the
    // enclosing file's outer ids, only explicit property bindings do — the
    // established QML fix is to pass the reference down as a real property
    // (matching this file's own existing `pal` pattern) instead of relying
    // on implicit outer-scope id lookup.
    property var win: null
    signal rewind()
    signal forever()

    height: 58

    NCDEKit { id: k }
    property var pal: null
    readonly property color gold:     pal ? pal.gold     : Qt.rgba(240/255,210/255,122/255,1)
    readonly property color goldSoft: pal ? pal.goldSoft : Qt.rgba(138/255,90/255,32/255,0.25)
    readonly property color goldDeep: pal ? pal.goldDeep : ncde.gilt1
    readonly property color gold1:    pal ? pal.gold1    : ncde.gilt0
    readonly property color gold2:    pal ? pal.gold2    : ncde.gilt1
    readonly property color burg4:    pal ? pal.burg4    : ncde.wine4
    readonly property color ink:      pal ? pal.ink      : k.ink
    readonly property color cream:    pal ? pal.cream    : ncde.surface

    readonly property real frac: entry.fraction !== undefined ? entry.fraction : 1
    readonly property color ringColor: frac < 0.04 ? ncde.wine4 : (frac < 0.25 ? ncde.gilt2 : ncde.verd)

    Rectangle {
        anchors.fill: parent; anchors.margins: 1
        radius: 12
        color: hov.hovered ? Qt.rgba(139/255,30/255,63/255,0.07) : "transparent"
    }
    Rectangle { anchors.top: parent.top; width: parent.width; height: 1
        color: row.goldSoft; visible: row.y > 0 }
    HoverHandler { id: hov }

    Row {
        anchors.fill: parent
        anchors.leftMargin: 12; anchors.rightMargin: 10
        spacing: 12

        // icon
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: 40; height: 40; radius: 6
            color: row.entry.isDir ? Qt.rgba(201/255,138/255,58/255,0.3) : Qt.rgba(row.cream.r, row.cream.g, row.cream.b, 0.85)
            border.width: 1.4; border.color: row.gold2
            Text { anchors.centerIn: parent; text: row.entry.isDir ? "\u25b8" : "\u25a4"
                   color: row.gold1; font.pixelSize: theme.fontMedium }
        }

        // name + path
        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - 40 - 46 - 96 - 48
            spacing: 1
            Text { width: parent.width; elide: Text.ElideRight
                   text: row.entry.name || ""
                   font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing; font.pixelSize: theme.fontMedium + theme.scale(1); color: row.ink }
            Text { width: parent.width; elide: Text.ElideRight
                   text: (row.entry.path || "") + "  \u00b7  " + hoursText()
                   font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; font.italic: true
                   font.pixelSize: theme.fontSmall; color: row.gold1 }
        }

        // rewind ring
        Item {
            anchors.verticalCenter: parent.verticalCenter
            width: 46; height: 46
            Canvas {
                anchors.fill: parent; renderStrategy: Canvas.Cooperative
                Component.onCompleted: requestPaint()
                onPaint: {
                    var ctx = getContext("2d"); ctx.reset()
                    var cx = width/2, cy = height/2, r = width/2 - 4
                    ctx.lineWidth = 4; ctx.strokeStyle = "rgba(138,90,32,0.25)"
                    ctx.beginPath(); ctx.arc(cx,cy,r,0,Math.PI*2); ctx.stroke()
                    ctx.strokeStyle = row.ringColor; ctx.lineCap = "round"
                    ctx.beginPath(); ctx.arc(cx,cy,r,-Math.PI/2,-Math.PI/2 + Math.PI*2*row.frac); ctx.stroke()
                }
                Connections { target: row; function onFracChanged(){ parent.requestPaint() } }
            }
            Column {
                anchors.centerIn: parent; spacing: -2
                Text { anchors.horizontalCenter: parent.horizontalCenter; text: ringNum()
                       font.family: theme.titleFont; font.bold: true; font.pixelSize: theme.fontSmall + theme.scale(1)
                       color: row.ringColor }
                Text { anchors.horizontalCenter: parent.horizontalCenter; text: ringUnit()
                       font.pixelSize: theme.scale(8); font.letterSpacing: 1; color: row.gold2 }
            }
        }

        // actions
        Row {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8
            PillButton { pal: row.pal; label: "REWIND"; primary: false; onClicked: row.rewind() }
            Item {
                anchors.verticalCenter: parent.verticalCenter
                width: 30; height: 30
                Rectangle { anchors.fill: parent; radius: width/2
                    color: fhov.hovered ? row.burg4 : "transparent"
                    border.width: 1.5; border.color: fhov.hovered ? row.goldDeep : "transparent" }
                Text { anchors.centerIn: parent; text: "\u2717"
                       color: fhov.hovered ? row.cream : row.gold1; font.pixelSize: theme.fontMedium }
                HoverHandler { id: fhov }
                TapHandler { onTapped: row.forever() }
            }
        }
    }

    function hoursText() {
        var h = row.entry.hoursLeft
        if (h === undefined) return ""
        return h >= 1 ? ("deleted \u00b7 " + Math.round(h) + "h to rewind")
                      : ("deleted \u00b7 " + Math.round(h*60) + "m to rewind")
    }
    function ringNum() {
        var h = row.entry.hoursLeft || 0
        return h >= 1 ? Math.round(h) : Math.round(h*60)
    }
    function ringUnit() {
        return (row.entry.hoursLeft || 0) >= 1 ? "H LEFT" : "M LEFT"
    }
}
