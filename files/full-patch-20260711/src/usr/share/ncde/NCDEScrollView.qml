// NCDEScrollView.qml — parchment-dark ground + brass scrollbar in one wrapper.
// Use:  NCDEScrollView { Column { ... } }   (single content child)
import QtQuick 2.15
import QtQuick.Controls 2.15

Flickable {
    id: view
    default property alias content: holder.data
    contentWidth: width
    contentHeight: holder.childrenRect.height + 2 * holder.padding
    boundsBehavior: Flickable.StopAtBounds
    clip: true
    NCDEKit { id: k }

    Accessible.role: Accessible.Pane

    // warm-dark content ground
    Rectangle {
        parent: view
        anchors.fill: parent
        z: -1
        color: k.surface
        border.color: k.gilt1; border.width: 1; radius: 8
    }

    Item {
        id: holder
        property int padding: 2
        x: padding; y: padding
        width: view.width - 2 * padding
    }

    ScrollBar.vertical: NCDEScrollBar {}
}
