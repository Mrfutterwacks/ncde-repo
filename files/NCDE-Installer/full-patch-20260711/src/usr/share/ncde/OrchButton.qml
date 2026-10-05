// OrchButton.qml — toolbar pill button for Orchidée. Primitives only.
import QtQuick 2.15

Item {
    id: btn
    property string label: ""
    property bool danger: false
    property bool enabled: true
    signal clicked()

    readonly property color gold: Qt.rgba(240/255,210/255,122/255,1)
    readonly property color goldDeep: ncde.gilt1
    readonly property color burg2: ncde.wine2
    readonly property color burg4: ncde.wine4
    readonly property color cream: ncde.surface

    implicitWidth: txt.implicitWidth + 30
    implicitHeight: 34
    opacity: enabled ? 1 : 0.4

    Rectangle {
        anchors.fill: parent
        radius: height / 2
        border.width: 1.5
        border.color: btn.danger ? btn.goldDeep : btn.goldDeep
        color: btn.danger ? (hov.hovered && btn.enabled ? btn.burg4 : Qt.rgba(139/255,30/255,63/255,0.12))
                          : (hov.hovered && btn.enabled ? btn.gold : Qt.rgba(240/255,210/255,122/255,0.2))
        scale: (hov.hovered && btn.enabled) ? 1.03 : 1
        Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
    }
    Text {
        id: txt; anchors.centerIn: parent; text: btn.label
        font.family: theme.titleFont; font.letterSpacing: 1.5; font.pixelSize: theme.fontSmall
        color: btn.danger ? (hov.hovered && btn.enabled ? btn.cream : btn.burg4) : ncde.panelText
    }
    HoverHandler { id: hov; enabled: btn.enabled }
    TapHandler { enabled: btn.enabled; onTapped: btn.clicked() }
}
