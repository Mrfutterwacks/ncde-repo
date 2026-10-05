// SNPlaylist.qml — Scrollable queue with a leaded-glass jewel per row.
import QtQuick
import QtQuick.Controls.Basic

ListView {
    id: list
    property var theme
    property var tracks: []
    property int currentTrack: 0
    property bool playing: false
    signal trackSelected(int index)

    clip: true
    model: tracks
    spacing: 2
    boundsBehavior: Flickable.StopAtBounds

    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AsNeeded
        contentItem: Rectangle {
            implicitWidth: 3
            radius: 2
            color: list.theme ? list.theme.lead : "#b88a32"
            opacity: 0.5
        }
    }

    delegate: Item {
        id: row
        width: list.width
        height: 56
        property bool active: index === list.currentTrack
        property var item: modelData

        HoverHandler { id: rowHover }

        Rectangle {
            anchors.fill: parent
            color: row.active ? Qt.rgba(0.6, 0.4, 1.0, 0.16)
                              : (rowHover.hovered ? Qt.rgba(0.6, 0.4, 1.0, 0.07) : "transparent")
            radius: 4
        }

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: list.theme.lead
            opacity: 0.18
        }

        Rectangle {
            visible: row.active
            anchors.left: parent.left
            anchors.leftMargin: -10
            anchors.verticalCenter: parent.verticalCenter
            width: 7; height: 7; radius: 3.5
            color: list.theme.amberHi
            border.color: list.theme.lead
            border.width: 0.5
        }

        Canvas {
            id: jewel
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            width: 22; height: 22
            antialiasing: true
            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()
                ctx.scale(width / 24, height / 24)
                var t = list.theme
                var lead = ctx.createLinearGradient(0, 0, 0, 24)
                lead.addColorStop(0, t.leadDeep)
                lead.addColorStop(0.5, t.leadBright)
                lead.addColorStop(1, t.lead)
                ctx.strokeStyle = lead
                ctx.lineWidth = 1
                var shape = index % 4
                if (shape === 0) {
                    ctx.fillStyle = t.violetHi
                    ctx.beginPath(); ctx.moveTo(12, 2); ctx.quadraticCurveTo(4, 12, 12, 22)
                    ctx.quadraticCurveTo(20, 12, 12, 2); ctx.closePath()
                    ctx.fill(); ctx.stroke()
                } else if (shape === 1) {
                    ctx.fillStyle = t.amber
                    ctx.beginPath(); ctx.moveTo(12, 3); ctx.lineTo(21, 8); ctx.lineTo(21, 16)
                    ctx.lineTo(12, 21); ctx.lineTo(3, 16); ctx.lineTo(3, 8); ctx.closePath()
                    ctx.fill(); ctx.stroke()
                } else if (shape === 2) {
                    ctx.fillStyle = t.jewel
                    ctx.beginPath(); ctx.moveTo(12, 2); ctx.lineTo(22, 12); ctx.lineTo(12, 22)
                    ctx.lineTo(2, 12); ctx.closePath()
                    ctx.fill(); ctx.stroke()
                } else {
                    ctx.fillStyle = t.violet
                    ctx.beginPath(); ctx.arc(12, 12, 9, 0, Math.PI * 2); ctx.fill(); ctx.stroke()
                    ctx.strokeStyle = t.leadBright
                    ctx.globalAlpha = 0.7
                    ctx.lineWidth = 0.6
                    ctx.beginPath()
                    ctx.moveTo(12, 5); ctx.lineTo(12, 19)
                    ctx.moveTo(5, 12); ctx.lineTo(19, 12)
                    ctx.moveTo(7, 7); ctx.lineTo(17, 17)
                    ctx.moveTo(7, 17); ctx.lineTo(17, 7)
                    ctx.stroke()
                    ctx.globalAlpha = 1
                }
                if (row.active) {
                    ctx.fillStyle = t.amberHi
                    ctx.beginPath(); ctx.arc(12, 12, 1.8, 0, Math.PI * 2); ctx.fill()
                }
            }
            Connections {
                target: list
                function onCurrentTrackChanged() { jewel.requestPaint() }
                function onThemeChanged() { jewel.requestPaint() }
            }
        }

        Column {
            anchors.left: jewel.right
            anchors.leftMargin: 12
            anchors.right: durLabel.left
            anchors.rightMargin: 8
            anchors.verticalCenter: parent.verticalCenter
            spacing: 2

            Row {
                spacing: 6
                Text {
                    text: row.item ? row.item.title : ""
                    color: row.active ? ncde.surface : list.theme.text
                    font.family: ncde.bodyFont
                    font.italic: true
                    font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg)
                    elide: Text.ElideRight
                    width: Math.min(implicitWidth, row.width - 100)
                }
                Row {
                    visible: row.active && list.playing
                    spacing: 2
                    anchors.verticalCenter: parent.verticalCenter
                    Repeater {
                        model: 3
                        Rectangle {
                            width: 2; radius: 1
                            color: list.theme.amberHi
                            height: 5
                            Timer { interval: 80; repeat: true; running: row.active && list.playing
                                onTriggered: parent.height = 4 + Math.random() * 8 }
                        }
                    }
                }
            }
            Text {
                text: row.item ? row.item.artist.toUpperCase() : ""
                color: list.theme.textDim
                font.family: ncde.titleFont
                font.pixelSize: (theme ? theme.fontSmall : ncde.fontSize_sm)
                font.letterSpacing: 2.5
                opacity: 0.7
                elide: Text.ElideRight
                width: parent.width
            }
        }

        Text {
            id: durLabel
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            text: {
                if (!row.item) return ""
                var s = row.item.duration || 0
                var m = Math.floor(s / 60)
                var ss = Math.floor(s % 60)
                return m + ":" + (ss < 10 ? "0" + ss : ss)
            }
            color: list.theme.leadBright
            font.family: ncde.bodyFont
            font.italic: true
            font.pixelSize: (theme ? theme.fontMedium : ncde.fontSize_md)
            opacity: row.active ? 1 : 0.7
        }

        TapHandler {
            cursorShape: Qt.PointingHandCursor
            onTapped: list.trackSelected(index)
        }
    }
}
