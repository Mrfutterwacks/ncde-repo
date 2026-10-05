// NCDEPasswordField.qml — NCDEField with a brass key glyph and an
// echo-toggle eye. Reveals/hides the secret without losing focus.
import QtQuick 2.15

NCDEField {
    id: pw
    iconText: "\u26bf"          // key-ish glyph; swap for an icon font if preferred
    echoMode: revealed ? TextInput.Normal : TextInput.Password
    property bool revealed: false
    NCDEKit { id: pk }

    // input.Accessible.* is inherited from NCDEField, but passwordEdit is specific to this
    // subtype — attached properties can't be re-declared on an id from outside its own
    // definition block, so set it imperatively once.
    Component.onCompleted: input.Accessible.passwordEdit = true

    // eye toggle, right-aligned (drawn over the field's right padding)
    Text {
        text: pw.revealed ? "\u25c9" : "\u25cb"   // open/closed eye stand-in
        color: eyeHover.hovered ? pk.gilt4 : pk.gilt2
        font.family: pk.titles; font.pixelSize: pk.fs(15)
        anchors.right: parent.right; anchors.rightMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        HoverHandler { id: eyeHover }
        TapHandler { onTapped: pw.revealed = !pw.revealed }
    }
    // keep text clear of the eye
    input.rightPadding: 22
}
