import QtQuick

// ConsentBar — "he asks first." A calm bottom prompt for the consent gates
// (go online? / update knowledge?). Never auto-acts; waits for the user.
Item {
    id: bar
    property var tokens
    property string prompt: ""
    property string yesLabel: "Allow"
    property string noLabel: "No"
    signal yes()
    signal no()
    implicitHeight: tokens.fs(60)

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0.02,0.10,0.07,0.92)
        border.color: tokens.pDim; border.width: 1
    }
    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left; anchors.leftMargin: tokens.pad
        anchors.right: parent.right; anchors.rightMargin: tokens.pad
        spacing: tokens.fs(16)
        Text {
            width: parent.width - tokens.fs(220)
            anchors.verticalCenter: parent.verticalCenter
            text: bar.prompt; color: tokens.pHi
            font.family: tokens.mono; font.pixelSize: tokens.fs(15); wrapMode: Text.WordWrap
        }
        VesperButton { tokens: bar.tokens; label: bar.yesLabel; accent: tokens.p
            anchors.verticalCenter: parent.verticalCenter; onClicked: bar.yes() }
        VesperButton { tokens: bar.tokens; label: bar.noLabel; ghost: true
            anchors.verticalCenter: parent.verticalCenter; onClicked: bar.no() }
    }
}
