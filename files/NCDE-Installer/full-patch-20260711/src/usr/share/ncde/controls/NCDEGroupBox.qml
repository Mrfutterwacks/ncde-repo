// NCDEGroupBox.qml — titled section frame. Put content as default children.
import QtQuick 2.15

Item {
    id: gb
    property string title: ""
    default property alias content: holder.data
    implicitWidth: 280
    implicitHeight: holder.childrenRect.height + 38
    NCDEKit { id: k }

    Accessible.role: Accessible.Grouping
    Accessible.name: gb.title

    Rectangle {
        anchors.fill: parent; anchors.topMargin: 8; radius: 9
        color: k.surface; border.color: k.gilt1; border.width: 1
    }
    // title cartouche notched into the top border
    Rectangle {
        visible: gb.title !== ""
        x: 14; y: 0; height: 18; radius: 9
        width: tl.implicitWidth + 20
        color: k.panelBg; border.color: k.gilt1; border.width: 1
        Text { id: tl; anchors.centerIn: parent; text: gb.title
               font.family: k.display; font.bold: true; font.pixelSize: k.fs(10)
               font.letterSpacing: 1.5; color: k.gilt3 }
    }
    Item {
        id: holder
        anchors.fill: parent
        anchors.topMargin: 26; anchors.margins: 14; anchors.bottomMargin: 12
    }
}
