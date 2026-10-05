import QtQuick

// VesperButton — calm phosphor action. Outlined; fills softly on hover. No siren.
Item {
    id: b
    property var tokens
    property string label: ""
    property color accent: tokens ? tokens.p : "#5fffba"
    property bool ghost: false
    signal clicked()
    implicitWidth: txt.implicitWidth + tokens.fs(28)
    implicitHeight: tokens.fs(38)

    Rectangle {
        anchors.fill: parent; radius: 6
        color: ma.containsMouse && !b.ghost ? Qt.rgba(accent.r, accent.g, accent.b, 0.14) : "transparent"
        border.color: b.ghost ? tokens.pDim : b.accent
        border.width: 1
        Behavior on color { ColorAnimation { duration: 140 } }
    }
    Text {
        id: txt; anchors.centerIn: parent; text: b.label
        color: b.ghost ? tokens.pDim : b.accent
        font.family: tokens.mono; font.pixelSize: tokens.small; font.letterSpacing: 2
    }
    MouseArea { id: ma; anchors.fill: parent; hoverEnabled: true
        cursorShape: Qt.PointingHandCursor; onClicked: b.clicked() }
}
