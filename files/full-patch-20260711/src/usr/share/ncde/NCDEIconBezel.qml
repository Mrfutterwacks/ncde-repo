import QtQuick
import QtQuick.Effects 6.5
import "ncde-color.js" as Col

// NCDEIconBezel — brass bezel + socket shadow, set behind a medallion so it reads
// as a jewel set INTO the glass — same technique as MotifFrame's TiffanyButton
// bezel/socket-shadow/glint. Originally private to Dock.qml (dock icon size only);
// extracted 2026-09-23 as a shared component so BottomPanel's workspace switcher
// can use the exact same beveled-circle treatment as the dock icons.
// Weight & touch (2026-09-24): `pressed` sinks the jewel into this socket, the
// same press MotifFrame's title-bar jewels already had — the socket shadow
// tightens (less gap under the jewel), the inner ring darkens and the glint
// dims and drops 1px. Callers move their own icon/cap down 1px to match.
// One light (2026-09-25): the ring's shine, the socket shadow and the glint all
// follow ShellLight — bright side toward the light, shadow falling away from it.
// Verdigris (2026-09-25): patina from the palette's verd sits in the socket on the
// side the light never polishes — same tone as MotifFrame's recesses. Static.
Item {
    id: bezel
    property real bezelSize: 48
    property bool  hovered: false
    property bool  pressed: false
    width:  bezelSize + 10
    height: bezelSize + 10

    // The standard (2026-09-26): one metal for every socket, bezel and frame —
    // NCDEKit's palette metal (the old bronze's exact lightness/chroma, the
    // palette's gold hue), so a cold palette no longer gets a brown ring with a
    // palette-coloured shine.
    NCDEKit { id: k }
    readonly property color bBronzeDark:  k.metalDark
    readonly property color bBronzeMid:   k.metalMid
    readonly property color bBronzeShine: k.metalShine
    readonly property color bCame:        k.metalCame
    readonly property color bPatina:      k.patina

    // brass bezel ring (a circle, so turning it points its shine at the light)
    Rectangle {
        anchors.fill: parent
        radius: width / 2
        rotation: ShellLight.gradientTurn
        gradient: Gradient {
            GradientStop { position: 0.00; color: bezel.bBronzeShine }
            GradientStop { position: 0.45; color: bezel.bBronzeMid }
            GradientStop { position: 1.00; color: bezel.bBronzeDark }
        }
        border.color: bezel.bCame
        border.width: 1
    }
    // inset ring shadow — gives the bezel depth
    Rectangle {
        anchors.centerIn: parent
        width: parent.width - 4; height: parent.height - 4
        radius: width / 2
        color: "transparent"
        border.color: bezel.bBronzeDark
        border.width: 1
        opacity: bezel.pressed ? 1.0 : 0.7
    }
    // verdigris in the socket, away from the light (the medallion covers the middle,
    // so only the rim of it shows between the ring and the jewel)
    Rectangle {
        anchors.centerIn: parent
        width: parent.width - 4; height: parent.height - 4
        radius: width / 2
        rotation: ShellLight.gradientTurn
        gradient: Gradient {
            GradientStop { position: 0.00; color: Qt.rgba(bezel.bPatina.r, bezel.bPatina.g, bezel.bPatina.b, 0.0) }
            GradientStop { position: 0.55; color: Qt.rgba(bezel.bPatina.r, bezel.bPatina.g, bezel.bPatina.b, 0.0) }
            GradientStop { position: 1.00; color: Qt.rgba(bezel.bPatina.r, bezel.bPatina.g, bezel.bPatina.b, 0.50) }
        }
    }
    // socket shadow — the medallion sits IN this bezel, not on top of it;
    // it falls away from the light (2px out, 1px when pressed in)
    Rectangle {
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -ShellLight.lx * (bezel.pressed ? 1 : 2)
        anchors.verticalCenterOffset: -ShellLight.ly * (bezel.pressed ? 1 : 2)
        width: bezel.bezelSize + 1; height: bezel.bezelSize + 1
        radius: width / 2
        color: k.shadeA(bezel.pressed ? 0.66 : 0.54)
        layer.enabled: true
        layer.effect: MultiEffect { blurEnabled: true; blur: 0.4; blurMax: 10 }
    }
    // glint where the light strikes the ring — brightens on hover, matching TiffanyButton;
    // laid along the rim (turned with the light)
    Rectangle {
        width: Math.max(3, bezel.bezelSize * 0.09)
        height: width * 0.7
        x: parent.width * ShellLight.hx(0.34) - width / 2
        y: parent.height * ShellLight.hy(0.34) - height / 2 + (bezel.pressed ? 1 : 0)
        radius: height / 2
        rotation: ShellLight.gradientTurn
        color: ShellLight.lt(bezel.pressed ? 0.40 : (bezel.hovered ? 0.85 : 0.62))
        Behavior on color { ColorAnimation { duration: 110 } }
    }
}
