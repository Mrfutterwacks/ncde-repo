// NCDEMenu.qml — parchment-dark popup menu; hover = gilt; mono shortcuts.
// Use NCDEMenu + NCDEMenuItem like the Qt Menu/MenuItem pair.
import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: menu
    NCDEKit { id: k }
    padding: 4
    background: Rectangle {
        implicitWidth: 200
        radius: 8; color: k.surface; border.color: k.gilt1; border.width: 1.5
    }
    delegate: MenuItem {
        id: mi
        implicitHeight: 34
        contentItem: Item {
            Text {
                anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter
                text: mi.text; font.family: k.serif; font.pixelSize: k.fs(15)
                color: mi.highlighted ? k.wine1 : k.ink
            }
            Text {
                // shortcut may be undefined (Action with no shortcut) —
                // && would propagate undefined into bool/QString and throw
                visible: !!(mi.action && mi.action.shortcut)
                anchors.right: parent.right; anchors.rightMargin: 14; anchors.verticalCenter: parent.verticalCenter
                text: (mi.action && mi.action.shortcut) ? mi.action.shortcut : ""
                font.family: k.mono; font.pixelSize: k.fs(11)
                color: mi.highlighted ? k.wine2 : k.inkDim
            }
        }
        background: Rectangle {
            radius: 6
            gradient: mi.highlighted ? giltGrad : null
            color: mi.highlighted ? "transparent" : "transparent"
            Gradient { id: giltGrad; orientation: Gradient.Vertical
                GradientStop { position: 0; color: k.gilt4 } GradientStop { position: 1; color: k.gilt3 } }
        }
    }
}
