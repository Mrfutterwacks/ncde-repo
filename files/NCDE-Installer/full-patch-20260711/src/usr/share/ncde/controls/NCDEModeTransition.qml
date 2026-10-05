// NCDEModeTransition.qml — cinematic dark⇆light fade (the macOS-style moment).
// Drop into the ROOT of main.qml:  NCDEModeTransition { anchors.fill: parent }
// Controls do NOT animate their own colours; this overlay creates the moment:
// fade to black (~140ms), hold (~80ms) while every ncde.* binding re-evaluates,
// then fade out to reveal the new mode already rendered.
import QtQuick 2.15

Item {
    id: trans
    anchors.fill: parent
    z: 9999

    // purely decorative fade overlay — no content, keep it out of the AT-SPI tree
    Accessible.ignored: true

    Rectangle {
        id: overlay
        anchors.fill: parent
        color: "black"
        opacity: 0
        visible: opacity > 0
    }

    SequentialAnimation {
        id: fadeAnim
        PropertyAction  { target: overlay; property: "opacity"; value: 0 }
        NumberAnimation { target: overlay; property: "opacity"; to: 1.0; duration: 140; easing.type: Easing.InOutQuad }
        PauseAnimation  { duration: 80 }
        NumberAnimation { target: overlay; property: "opacity"; to: 0.0; duration: 140; easing.type: Easing.InOutQuad }
    }

    Connections {
        target: (typeof ncde !== "undefined") ? ncde : null
        function onDarkModeChanged() { fadeAnim.restart() }
    }
}
