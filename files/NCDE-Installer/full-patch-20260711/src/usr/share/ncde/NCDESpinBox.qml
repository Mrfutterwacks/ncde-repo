// NCDESpinBox.qml — number entry with brass ± steppers.
import QtQuick 2.15

Item {
    id: sp
    property real value: 0
    property real from: 0
    property real to: 100
    property real step: 1
    property int  decimals: 0
    property string suffix: ""
    property string accessibleName: ""
    signal moved(real value)
    implicitWidth: 150; implicitHeight: 34
    NCDEKit { id: k }

    function _clamp(v){ return Math.max(from, Math.min(to, v)) }
    function _set(v){ var n = _clamp(v); if (n !== value) { value = n; moved(n) } }
    readonly property string display: value.toFixed(decimals) + suffix

    Accessible.role: Accessible.SpinBox
    Accessible.name: sp.accessibleName
    Accessible.description: sp.display
    Accessible.focusable: true
    Accessible.onIncreaseAction: sp._set(sp.value + sp.step)
    Accessible.onDecreaseAction: sp._set(sp.value - sp.step)

    Rectangle {
        anchors.fill: parent; radius: 8
        color: k.panelBg2; border.color: input.activeFocus ? k.cer : k.gilt1; border.width: 1.5
        Rectangle { anchors { left: parent.left; right: parent.right; top: parent.top; margins: 1 }
                    height: 3; radius: 2; color: Qt.rgba(0,0,0,0.4) }
    }

    // − stepper
    Rectangle {
        id: minus; width: 30; height: parent.height; radius: 8
        anchors.left: parent.left
        color: mHov.hovered ? k.surfaceHi : "transparent"
        Text { anchors.centerIn: parent; text: "\u2212"; color: k.gilt3; font.family: k.titles; font.pixelSize: k.fs(16) }
        HoverHandler { id: mHov }
        TapHandler { onTapped: sp._set(sp.value - sp.step) }
    }
    TextInput {
        id: input
        anchors.centerIn: parent; width: parent.width - 64
        horizontalAlignment: TextInput.AlignHCenter
        text: sp.display; color: k.ink
        font.family: k.serif; font.pixelSize: k.fs(15)
        selectByMouse: true; clip: true
        inputMethodHints: Qt.ImhFormattedNumbersOnly
        onEditingFinished: { var v = parseFloat(text); if (!isNaN(v)) sp._set(v); else text = sp.display }
    }
    // + stepper
    Rectangle {
        id: plus; width: 30; height: parent.height; radius: 8
        anchors.right: parent.right
        color: pHov.hovered ? k.surfaceHi : "transparent"
        Text { anchors.centerIn: parent; text: "+"; color: k.gilt3; font.family: k.titles; font.pixelSize: k.fs(16) }
        HoverHandler { id: pHov }
        TapHandler { onTapped: sp._set(sp.value + sp.step) }
    }
}
