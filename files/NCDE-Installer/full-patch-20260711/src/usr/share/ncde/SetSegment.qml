// SetSegment.qml — segmented choice (TapHandler only).
import QtQuick 2.15
Row {
    id: seg
    property var model: []
    property int currentIndex: 0
    signal chose(int index)
    spacing: 0
    Repeater {
        model: seg.model
        Rectangle {
            height: 30
            width: lab.implicitWidth + 26
            property bool on: seg.currentIndex === index
            color: on ? ncde.gilt3 : ncde.surface
            border.color: ncde.gilt1; border.width: 1
            radius: 0
            Rectangle { visible: index===0; width: 8; height: parent.height; anchors.left: parent.left
                        color: parent.color; }
            Text {
                id: lab; anchors.centerIn: parent; text: modelData
                font.family: (typeof ncde !== "undefined" && ncde.titleFont) ? ncde.titleFont : "Cinzel"; font.pixelSize: theme.fontSmall
                color: parent.on ? (ncde.darkMode ? ncde.gilt4 : ncde.gilt1) : ncde.panelText
            }
            TapHandler { onTapped: { seg.currentIndex = index; seg.chose(index) } }
        }
    }
}
