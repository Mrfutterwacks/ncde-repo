// NCDEToggle.qml — verdigris-fill switch with a brass knob.
import QtQuick 2.15

Item {
    id: tg
    property bool checked: false
    property string accessibleName: ""
    signal toggled(bool value)
    implicitWidth: 46; implicitHeight: 24
    activeFocusOnTab: true
    NCDEKit { id: k }

    function _toggle() { tg.checked = !tg.checked; tg.toggled(tg.checked) }

    Accessible.role: Accessible.Switch
    Accessible.name: tg.accessibleName
    Accessible.checkable: true
    Accessible.checked: tg.checked
    Accessible.focusable: true
    Accessible.onToggleAction: tg._toggle()

    Rectangle {
        anchors.fill: parent; radius: height/2
        border.color: hov.hovered ? Qt.lighter(k.gilt0, 1.25) : k.gilt0; border.width: 1.5
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0; color: tg.checked ? k.verd : k.surface2 }
            GradientStop { position: 1; color: tg.checked ? Qt.darker(k.verd, 1.6) : k.surface2 }
        }
        Behavior on color { ColorAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 160 } }
        Behavior on border.color { ColorAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
    }
    Rectangle {  // keyboard focus ring — same treatment as NCDEField/NCDEButton
        anchors.fill: parent; anchors.margins: -2; radius: height/2 + 2
        color: "transparent"; border.color: k.cer; border.width: 2
        opacity: tg.activeFocus ? 0.28 : 0
        Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
    }
    Rectangle {
        width: 18; height: 18; radius: 9
        anchors.verticalCenter: parent.verticalCenter
        x: tg.checked ? parent.width - width - 3 : 3
        border.color: k.gilt0; border.width: 1
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0;   color: k.gilt5 }
            GradientStop { position: 0.6; color: k.gilt3 }
            GradientStop { position: 1;   color: k.gilt0 }
        }
        Behavior on x { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 160; easing.type: Easing.OutCubic } }
    }
    HoverHandler { id: hov }
    TapHandler { onTapped: tg._toggle() }
    Keys.onPressed: function(event) {
        if (event.key === Qt.Key_Space || event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
            tg._toggle(); event.accepted = true
        }
    }
}
