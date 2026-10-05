// NCDEScrollBar.qml — brass thumb, dark recessed channel, no end arrows,
// slim by default → widens on hover, auto-hides when content fits.
// Use:  ScrollBar.vertical: NCDEScrollBar {}
import QtQuick 2.15
import QtQuick.Controls 2.15

ScrollBar {
    id: sb
    policy: size < 1.0 ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff
    minimumSize: 0.08
    padding: 3
    NCDEKit { id: k }

    property int slim: 8
    property int wide: 12
    property bool hot: sb.pressed || sb.hovered

    contentItem: Rectangle {
        implicitWidth: sb.hot ? sb.wide : sb.slim
        implicitHeight: sb.hot ? sb.wide : sb.slim
        radius: width / 2
        border.color: k.gilt0; border.width: 1
        opacity: sb.active ? 1 : 0
        gradient: Gradient {
            orientation: sb.horizontal ? Gradient.Vertical : Gradient.Horizontal
            GradientStop { position: 0; color: sb.hot ? k.gilt5 : k.gilt4 }
            GradientStop { position: 1; color: sb.hot ? k.gilt3 : k.gilt2 }
        }
        Behavior on implicitWidth  { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
        Behavior on implicitHeight { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
        Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 160 } }
    }

    background: Rectangle {
        implicitWidth: sb.slim + 2; implicitHeight: sb.slim + 2
        radius: width / 2
        color: Qt.rgba(0, 0, 0, k.dark ? 0.45 : 0.12)
        border.color: Qt.rgba(0, 0, 0, k.dark ? 0.60 : 0.20); border.width: 1
        opacity: sb.active ? 1 : 0
        Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 160 } }
    }
}
