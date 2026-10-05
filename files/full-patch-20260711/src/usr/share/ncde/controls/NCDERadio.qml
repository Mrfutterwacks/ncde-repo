// NCDERadio.qml — brass radio. Use within a parent that clears siblings,
// or bind `checked` to a group property.
import QtQuick 2.15

Item {
    id: rb
    property string text: ""
    property bool checked: false
    property var group: null          // optional: a list of NCDERadio to clear
    signal picked()
    // 26 (was 22): the TapHandler lives on this root item, so implicitHeight IS the
    // hit-target height — 22px sat under the 24px WCAG 2.5.8 floor. Art unchanged
    // (dot stays 20×20, vertically centered); only the tappable strip grew. Matches
    // the same pass already applied to NCDECheck/NCDESlider.
    implicitHeight: 26
    implicitWidth: rowr.implicitWidth
    activeFocusOnTab: true
    NCDEKit { id: k }

    function _pick() {
        if (rb.group) for (var i = 0; i < rb.group.length; ++i) rb.group[i].checked = false
        rb.checked = true; rb.picked()
    }

    Accessible.role: Accessible.RadioButton
    Accessible.name: rb.text
    Accessible.checkable: true
    Accessible.checked: rb.checked
    Accessible.focusable: true
    Accessible.onToggleAction: rb._pick()

    Row {
        id: rowr; spacing: 9; anchors.verticalCenter: parent.verticalCenter
        Rectangle {
            width: 20; height: 20; radius: 10
            anchors.verticalCenter: parent.verticalCenter
            border.width: 1.5; border.color: rb.checked ? k.gilt0 : (hov.hovered ? k.gilt2 : k.gilt1)
            Behavior on border.color { ColorAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
            gradient: Gradient {
                GradientStop { position: 0; color: rb.checked ? k.gilt5 : k.panelBg2 }
                GradientStop { position: 1; color: rb.checked ? k.gilt3 : k.panelBg2 }
            }
            Rectangle {
                anchors.centerIn: parent; width: 8; height: 8; radius: 4
                color: k.wine1; opacity: rb.checked ? 1 : 0
                Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 110 } }
            }
        }
        Text {
            visible: rb.text !== ""; text: rb.text
            anchors.verticalCenter: parent.verticalCenter
            font.family: k.serif; font.pixelSize: k.fs(15); color: k.ink
        }
    }
    Rectangle {  // keyboard focus ring — same treatment as NCDEField/NCDEButton
        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: -2; width: 24; height: 24; radius: 12
        color: "transparent"; border.color: k.cer; border.width: 2
        opacity: rb.activeFocus ? 0.28 : 0
        Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
    }
    HoverHandler { id: hov }
    TapHandler { onTapped: rb._pick() }
    Keys.onPressed: function(event) {
        if (event.key === Qt.Key_Space || event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
            rb._pick(); event.accepted = true
        }
    }
}
