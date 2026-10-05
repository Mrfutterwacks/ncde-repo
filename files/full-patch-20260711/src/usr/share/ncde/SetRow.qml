// SetRow.qml — label | control | hint. Put the control as the default child.
import QtQuick 2.15
Row {
    id: r
    property string label: ""
    property string hint: ""
    property int labelWidth: 160
    width: parent ? parent.width : 480
    spacing: 12
    Text {
        text: r.label; width: r.labelWidth
        anchors.verticalCenter: parent.verticalCenter
        font.family: (typeof ncde !== "undefined" && ncde.titleFont) ? ncde.titleFont : "Cinzel"; font.pixelSize: theme.fontMedium; color: ncde.foreground
    }
    Text {
        text: r.hint; visible: r.hint !== ""
        anchors.verticalCenter: parent.verticalCenter
        font.family: (typeof ncde !== "undefined" && ncde.fellFont) ? ncde.fellFont : "IM Fell English"; font.italic: true; font.pixelSize: theme.fontSmall; color: ncde.foreground
    }
}
