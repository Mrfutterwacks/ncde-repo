import QtQuick 2.15

Item {
    id: dropZone
    property string exec: ""
    property bool   active: area.containsDrag
    property Item   iconTarget: null
    signal fileDropped(var paths)
    signal fileHovered(var paths)
    readonly property bool motionAllowed: typeof animPolicy === "undefined" || animPolicy === null
        || (animPolicy.decorative && !animPolicy.screenIdle)
    readonly property real motionDurationScale: typeof animPolicy !== "undefined" && animPolicy !== null
        && (animPolicy.thermalPressure || animPolicy.lowPower) ? 1.5 : 1.0

    Rectangle {
        anchors.fill: parent; color: "transparent"; radius: 2
        border.color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, glowAnim.val)
        border.width: dropZone.active ? 2 : 0
        Behavior on border.width {
            NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 80 * dropZone.motionDurationScale; easing.type: Easing.OutExpo }
        }
    }
    Rectangle {
        anchors.fill: parent; radius: 2
        color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b,
                       dropZone.active ? 0.15 : 0.0)
        Behavior on color {
            ColorAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 120 * dropZone.motionDurationScale; easing.type: Easing.OutExpo }
        }
    }
    Item {
        id: glowAnim; property real val: 0.0
        SequentialAnimation on val {
            running: dropZone.visible && dropZone.active && dropZone.motionAllowed; loops: Animation.Infinite
            NumberAnimation { to: 0.9; duration: 350 * dropZone.motionDurationScale; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.3; duration: 350 * dropZone.motionDurationScale; easing.type: Easing.InOutSine }
            onStopped: glowAnim.val = 0.6
        }
    }
    onActiveChanged: {
        if (!iconTarget) return
        if (active) { iconScaleIn.restart() } else { iconScaleOut.restart() }
    }
    SequentialAnimation {
        id: iconScaleIn
        NumberAnimation { target: dropZone.iconTarget; property: "scale"
                          to: 1.18; duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 120 * dropZone.motionDurationScale; easing.type: Easing.OutExpo }
        NumberAnimation { target: dropZone.iconTarget; property: "scale"
                          to: 1.10; duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 80 * dropZone.motionDurationScale; easing.type: Easing.OutExpo }
    }
    SequentialAnimation {
        id: iconScaleOut
        NumberAnimation { target: dropZone.iconTarget; property: "scale"
                          to: 0.95; duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 60 * dropZone.motionDurationScale;  easing.type: Easing.OutExpo }
        NumberAnimation { target: dropZone.iconTarget; property: "scale"
                          to: 1.0;  duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 100 * dropZone.motionDurationScale; easing.type: Easing.OutExpo }
    }
    SequentialAnimation {
        id: acceptFlash
        NumberAnimation { target: dropZone; property: "opacity"
                          to: 0.4; duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 60 * dropZone.motionDurationScale;  easing.type: Easing.OutExpo }
        NumberAnimation { target: dropZone; property: "opacity"
                          to: 1.0; duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 180 * dropZone.motionDurationScale; easing.type: Easing.OutExpo }
    }
    DropArea {
        id: area; anchors.fill: parent
        onEntered: (drag) => {
            if (drag.hasUrls) { drag.accepted = true; dropZone.fileHovered(drag.urls) }
            else drag.accepted = false
        }
        onDropped: (drop) => {
            if (drop.hasUrls) {
                acceptFlash.restart()
                dropZone.fileDropped(drop.urls)
                if (dropZone.exec !== "") launcher.launchWithFiles(dropZone.exec, drop.urls)
                drop.acceptProposedAction()
            }
        }
    }
}
