// NCDESeparator.qml — gilt hairline divider (horizontal or vertical).
import QtQuick 2.15
Rectangle {
    id: sep
    property bool vertical: false
    NCDEKit { id: k }
    implicitWidth:  vertical ? 1 : 80
    implicitHeight: vertical ? 80 : 1
    color: k.gilt1
    opacity: 0.4

    Accessible.role: Accessible.Separator
}
