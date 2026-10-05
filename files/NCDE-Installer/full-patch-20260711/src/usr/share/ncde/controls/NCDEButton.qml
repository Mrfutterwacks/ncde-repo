// NCDEButton.qml — variants: "primary" (wine), "gilt", "ghost".
import QtQuick 2.15

Item {
    id: btn
    property string text: "Button"
    property string variant: "primary"   // primary | gilt | ghost
    property string glyph: ""
    signal clicked()
    implicitWidth: row.implicitWidth + 36
    implicitHeight: 34
    activeFocusOnTab: true
    NCDEKit { id: k }

    readonly property bool prim:  variant === "primary"
    readonly property bool gilt:  variant === "gilt"
    readonly property bool ghost: variant === "ghost"

    // AT-SPI: this shared kit had zero Accessible.* markup anywhere (2026-07-15 audit) — every
    // consumer inherits real screen-reader exposure from here. name falls back to the glyph when
    // text is empty (icon-only buttons) so a screen reader never announces a blank button.
    Accessible.role: Accessible.Button
    Accessible.name: btn.text !== "" ? btn.text : btn.glyph
    Accessible.focusable: true
    Accessible.pressed: tap.pressed
    Accessible.onPressAction: btn.clicked()

    Rectangle {
        anchors.fill: parent; radius: 8
        border.width: 1.5
        border.color: btn.prim ? k.wine1 : (btn.gilt ? k.gilt0 : k.gilt1)
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0; color: btn.prim ? (hov.hovered ? k.wine4 : k.wine3)
                                                : btn.gilt ? (hov.hovered ? k.gilt5 : k.gilt4)
                                                : (hov.hovered ? k.surfaceHi : k.surface) }
            GradientStop { position: 1; color: btn.prim ? (hov.hovered ? k.wine2 : k.wine1)
                                                : btn.gilt ? (hov.hovered ? k.gilt4 : k.gilt3)
                                                : k.surface }
        }
        scale: tap.pressed ? 0.97 : 1.0
        Behavior on scale { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 90; easing.type: Easing.OutCubic } }
    }
    Rectangle {  // keyboard focus ring — same treatment as NCDEField
        anchors.fill: parent; anchors.margins: -2; radius: 10
        color: "transparent"; border.color: k.cer; border.width: 2
        opacity: btn.activeFocus ? 0.28 : 0
        Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
    }
    Row {
        id: row; anchors.centerIn: parent; spacing: 7
        Text { visible: btn.glyph !== ""; text: btn.glyph
               color: btn.prim ? k.gilt5 : (btn.gilt ? k.wine1 : k.gilt3)
               font.family: k.titles; font.pixelSize: k.fs(13); anchors.verticalCenter: parent.verticalCenter }
        Text { text: btn.text; font.family: k.titles; font.weight: Font.DemiBold
               font.pixelSize: k.fs(13); font.letterSpacing: 0.5
               color: btn.prim ? k.gilt5 : (btn.gilt ? k.wine1 : k.gilt3)
               anchors.verticalCenter: parent.verticalCenter }
    }
    HoverHandler { id: hov }
    TapHandler { id: tap; onTapped: btn.clicked() }
    Keys.onPressed: function(event) {
        if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter || event.key === Qt.Key_Space) {
            btn.clicked(); event.accepted = true
        }
    }
}
