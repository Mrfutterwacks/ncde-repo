// NCDECheck.qml — gilt-fill checkbox with a wine tick.
import QtQuick 2.15

Item {
    id: cb
    property string text: ""
    property bool checked: false
    signal toggled(bool value)
    // 26 (was 22): the TapHandler lives on this root item, so implicitHeight IS the
    // hit-target height — 22px sat under the 24px WCAG 2.5.8 floor. Art unchanged
    // (box stays 20×20, vertically centered); only the tappable strip grew.
    implicitHeight: 26
    implicitWidth: rowc.implicitWidth
    activeFocusOnTab: true
    NCDEKit { id: k }

    function _toggle() { cb.checked = !cb.checked; cb.toggled(cb.checked) }

    Accessible.role: Accessible.CheckBox
    Accessible.name: cb.text
    Accessible.checkable: true
    Accessible.checked: cb.checked
    Accessible.focusable: true
    Accessible.onToggleAction: cb._toggle()

    Row {
        id: rowc; spacing: 9; anchors.verticalCenter: parent.verticalCenter
        Rectangle {
            id: box; width: 20; height: 20; radius: 5
            anchors.verticalCenter: parent.verticalCenter
            border.width: 1.5; border.color: cb.checked ? k.gilt0 : (hov.hovered ? k.gilt2 : k.gilt1)
            Behavior on border.color { ColorAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0; color: cb.checked ? k.gilt4 : k.panelBg2 }
                GradientStop { position: 1; color: cb.checked ? k.gilt3 : k.panelBg2 }
            }
            Canvas {
                id: tick; anchors.fill: parent; antialiasing: true
                renderStrategy: Canvas.Cooperative; layer.enabled: true
                opacity: cb.checked ? 1 : 0
                Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 110 } }
                Component.onCompleted: requestPaint()
                onPaint: {
                    var ctx = getContext("2d"); ctx.reset();
                    ctx.strokeStyle = k.wine1; ctx.lineWidth = 2.6; ctx.lineCap = "round"; ctx.lineJoin = "round";
                    ctx.beginPath(); ctx.moveTo(width*0.24, height*0.52);
                    ctx.lineTo(width*0.43, height*0.70); ctx.lineTo(width*0.78, height*0.30); ctx.stroke();
                }
            }
        }
        Text {
            visible: cb.text !== ""; text: cb.text
            anchors.verticalCenter: parent.verticalCenter
            font.family: k.serif; font.pixelSize: k.fs(15); color: k.ink
        }
    }
    Rectangle {  // keyboard focus ring — same treatment as NCDEField/NCDEButton
        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: -2; width: 24; height: 24; radius: 7
        color: "transparent"; border.color: k.cer; border.width: 2
        opacity: cb.activeFocus ? 0.28 : 0
        Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
    }
    HoverHandler { id: hov }
    TapHandler { onTapped: cb._toggle() }
    Keys.onPressed: function(event) {
        if (event.key === Qt.Key_Space || event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
            cb._toggle(); event.accepted = true
        }
    }
}
