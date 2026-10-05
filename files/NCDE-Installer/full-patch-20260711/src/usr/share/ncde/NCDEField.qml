// NCDEField.qml — single-line text field. Parchment-dark, gilt border,
// inset shadow, cerulean/accent focus ring. Optional leading icon glyph.
import QtQuick 2.15

Item {
    id: field
    property alias text: input.text
    property string placeholder: ""
    property string iconText: ""          // optional glyph drawn left
    property bool   error: false
    property alias echoMode: input.echoMode
    property alias input: input
    signal accepted()
    implicitWidth: 240
    implicitHeight: 36
    NCDEKit { id: k }

    Rectangle {
        id: box
        anchors.fill: parent; radius: k.rControl
        color: k.panelBg2
        border.width: 1.5
        border.color: field.error ? k.rose : (input.activeFocus ? k.cer : k.gilt1)
        Rectangle {  // inset shadow (top)
            anchors { left: parent.left; right: parent.right; top: parent.top; margins: 1 }
            height: 3; radius: 2; color: Qt.rgba(0,0,0,0.4)
        }
        Rectangle {  // focus glow ring
            anchors.fill: parent; anchors.margins: -2; radius: k.rControl + 2
            color: "transparent"; border.color: k.cer; border.width: 2
            opacity: input.activeFocus ? 0.28 : 0; z: -1
            Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
        }
    }

    Row {
        anchors.fill: parent
        anchors.leftMargin: 12; anchors.rightMargin: 12
        spacing: 8
        Text {
            visible: field.iconText !== ""
            text: field.iconText; color: k.gilt2
            font.family: k.titles; font.pixelSize: k.fs(15)
            anchors.verticalCenter: parent.verticalCenter
        }
        TextInput {
            id: input
            width: parent.width - (field.iconText !== "" ? 24 : 0)
            anchors.verticalCenter: parent.verticalCenter
            font.family: k.serif; font.pixelSize: k.fs(16)
            color: k.ink; selectionColor: k.gilt3; selectedTextColor: k.wine1
            clip: true; selectByMouse: true
            onAccepted: field.accepted()
            Accessible.role: Accessible.EditableText
            Accessible.name: field.placeholder !== "" ? field.placeholder : field.iconText
            Accessible.editable: true
            Accessible.focusable: true
            Text {
                anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                text: field.placeholder; color: k.inkDim
                font.family: k.serif; font.italic: true; font.pixelSize: k.fs(16)
                visible: input.text.length === 0 && !input.activeFocus
            }
        }
    }
}
