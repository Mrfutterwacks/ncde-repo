// NCDETimePicker.qml — a real, working time-of-day picker ("h:mm AP" strings, e.g. "10:00 PM").
// Built 2026-07-01 to replace a static, non-interactive display box in NotificationsTab.qml's
// Quiet Hours row. Same button+dropdown pattern already proven in DisplayTab.qml's resolution picker.
import QtQuick 2.15

Item {
    id: tp
    property string value: "12:00 AM"
    signal picked(string v)
    implicitWidth: 100; implicitHeight: 30
    NCDEKit { id: k }

    readonly property var _times: {
        var out = []
        for (var h = 0; h < 24; h++)
            for (var m = 0; m < 60; m += 30) {
                var hh = h % 12; if (hh === 0) hh = 12
                out.push(hh + ":" + (m < 10 ? "0" : "") + m + " " + (h < 12 ? "AM" : "PM"))
            }
        return out
    }

    Rectangle {
        id: btn; anchors.fill: parent; radius: 8
        color: k.surface; border.color: k.gilt1; border.width: 1.5
        Text { anchors.centerIn: parent; text: tp.value + "  ▾"
               font.family: k.serif; font.pixelSize: Math.round(13 * (theme.fontMedium / 13.0)); color: k.ink }
        TapHandler { onTapped: drop.visible = !drop.visible }
    }
    Rectangle {
        id: drop; visible: false; z: 30
        anchors.top: btn.bottom; anchors.topMargin: 4
        anchors.left: btn.left; width: Math.max(btn.width, 90)
        height: Math.min(tp._times.length * 26, 200)
        radius: 8; color: k.surface; border.color: k.gilt1; border.width: 1; clip: true
        ListView {
            anchors.fill: parent
            model: tp._times
            currentIndex: tp._times.indexOf(tp.value)
            highlightMoveDuration: 0
            Component.onCompleted: if (currentIndex >= 0) positionViewAtIndex(currentIndex, ListView.Center)
            delegate: Rectangle {
                width: drop.width; height: 26
                color: rHov.hovered ? k.gilt4 : "transparent"
                Text { anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter
                       text: modelData; font.family: k.serif; font.pixelSize: Math.round(13 * (theme.fontMedium / 13.0)); color: k.ink }
                HoverHandler { id: rHov }
                TapHandler { onTapped: { tp.picked(modelData); drop.visible = false } }
            }
        }
    }
}
