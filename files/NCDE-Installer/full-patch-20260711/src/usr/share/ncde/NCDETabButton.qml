// NCDETabButton.qml — a tab in NCDETabBar; gilt when current.
import QtQuick 2.15
import QtQuick.Controls 2.15

TabButton {
    id: tab
    NCDEKit { id: k }
    implicitHeight: 34
    implicitWidth: lbl.implicitWidth + 32
    contentItem: Text {
        id: lbl; text: tab.text
        font.family: k.titles; font.pixelSize: k.fs(13)
        color: tab.checked ? k.wine1 : k.gilt2
        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        radius: 8
        // square the bottom so the tab merges with the panel below
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop { position: 0; color: tab.checked ? k.gilt4 : k.surface }
            GradientStop { position: 1; color: tab.checked ? k.gilt3 : k.panelBg2 } }
        border.color: k.gilt1; border.width: 1
        Rectangle {  // cover bottom radius
            anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
            height: 8; color: tab.checked ? k.gilt3 : k.panelBg2
        }
    }
}
