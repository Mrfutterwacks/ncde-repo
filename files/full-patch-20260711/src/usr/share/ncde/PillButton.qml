// PillButton.qml — a small parchment-style pill button for Binnie's app.
// Pure primitives: HoverHandler + TapHandler only.
import QtQuick 2.15

Item {
    id: btn
    property string label: ""
    property bool primary: false
    signal clicked()

    property var pal: null
    readonly property color gold:     pal ? pal.gold     : Qt.rgba(240/255,210/255,122/255,1)
    readonly property color goldDeep: pal ? pal.goldDeep : ncde.gilt1
    readonly property color burg2:    pal ? pal.burg2    : ncde.wine2
    readonly property color burg4:    pal ? pal.burg4    : ncde.wine4
    readonly property color cream:    pal ? pal.cream    : ncde.surface

    implicitWidth: txt.implicitWidth + 32
    implicitHeight: 34

    Rectangle {
        anchors.fill: parent
        radius: height / 2
        border.width: 1.5
        border.color: btn.goldDeep
        gradient: btn.primary ? gradPrimary : null
        color: btn.primary ? "transparent" : (hov.hovered ? btn.gold : Qt.rgba(240/255,210/255,122/255,0.2))
        scale: hov.hovered ? 1.03 : 1
        Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
        Gradient { id: gradPrimary
            GradientStop { position: 0; color: btn.burg4 }
            GradientStop { position: 1; color: btn.burg2 } }
    }
    Text {
        id: txt
        anchors.centerIn: parent
        text: btn.label
        font.family: theme.titleFont; font.letterSpacing: 1.5
        font.pixelSize: theme.fontSmall
        color: btn.primary ? btn.cream : ncde.panelText
    }
    HoverHandler { id: hov }
    TapHandler { onTapped: btn.clicked() }
}
