import QtQuick 2.15
import "mucha-scene.js"   as MuchaScene
import "mucha-orrery.js"  as MuchaOrrery
import "mucha-earth.js"   as MuchaEarth
import "mucha-clouds.js"  as MuchaClouds
import "mucha-cities.js"  as MuchaCities
import "mucha-sun.js"     as MuchaSun
import "mucha-moon.js"    as MuchaMoon

Item {
    id: root
    property QtObject desktopWidget: null

    width:  parent.width
    height: 230
    layer.enabled: true

    readonly property real cx:     width / 2
    readonly property real cy:     height / 2 + 10
    readonly property real radius: 88

    function arcX(angleDeg) {
        return cx + radius * Math.cos((angleDeg + 180) * Math.PI / 180)
    }
    function arcY(angleDeg) {
        return cy - Math.abs(radius * Math.sin(angleDeg * Math.PI / 180)) * 1.1
    }

    function arcXm(angleDeg) {
        return cx + radius * Math.cos((angleDeg + 180) * Math.PI / 180)
    }
    function arcYm(angleDeg) {
        return cy - Math.abs(radius * Math.sin(angleDeg * Math.PI / 180)) * 1.1
    }

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0.05, 0.02, 0.15, desktopWidget ? desktopWidget.skyBrightness * 0.25 : 0)
        Behavior on color {
            ColorAnimation { duration: 120000; easing.type: Easing.InOutSine }
        }
    }

    Canvas {
        id: spaceCanvas
        anchors.fill: parent
        opacity: starTwinkle.val * (desktopWidget ? desktopWidget.starOpacity : 0)
        Behavior on opacity {
            NumberAnimation { duration: 120000; easing.type: Easing.InOutSine }
        }
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d")
            if (!desktopWidget) return
            MuchaScene.drawMuchaScene(ctx, width, height, {
                sunArcAngle:  desktopWidget.sunArcAngle,
                moonArcAngle: desktopWidget.moonArcAngle,
                sunVisible:   desktopWidget.sunVisible,
                moonVisible:  desktopWidget.moonVisible,
                meteorPhase:  0,
                birdPhase:    0,
                locationText: "ILL · 41° N",
                dateText:     ""
            })
        }
        Connections {
            target: desktopWidget
            function onSunArcAngleChanged()  { spaceCanvas.requestPaint() }
            function onMoonArcAngleChanged() { spaceCanvas.requestPaint() }
            function onSunVisibleChanged()   { spaceCanvas.requestPaint() }
            function onMoonVisibleChanged()  { spaceCanvas.requestPaint() }
        }
    }

    Item {
        id: starTwinkle
        property real val: 0.6
        SequentialAnimation on val {
            loops: Animation.Infinite
            running: root.visible && animPolicy.decorative && animPolicy.idleLoops && !animPolicy.screenIdle
            NumberAnimation { to: 0.8;  duration: 4000; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.5;  duration: 3500; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.7;  duration: 5000; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.55; duration: 3000; easing.type: Easing.InOutSine }
        }
    }

    Rectangle {
        width:   parent.width - 20
        height:  1
        x:       10
        y:       cy
        color:   Qt.rgba(desktopWidget ? desktopWidget.c5.r : 0.5, desktopWidget ? desktopWidget.c5.g : 0.5, desktopWidget ? desktopWidget.c5.b : 0.5, 0.08)
    }

    Canvas {
        id: orreryRingCanvas
        anchors.fill: parent
        Component.onCompleted: requestPaint()
        Connections {
            target: desktopWidget
            function onSunArcAngleChanged()  { orreryRingCanvas.requestPaint() }
            function onMoonArcAngleChanged() { orreryRingCanvas.requestPaint() }
            function onSunVisibleChanged()   { orreryRingCanvas.requestPaint() }
            function onMoonVisibleChanged()  { orreryRingCanvas.requestPaint() }
        }
        onPaint: {
            var ctx = getContext("2d")
            if (!desktopWidget) return
            MuchaOrrery.drawMuchaOrrery(ctx, width, height, {
                sunArcAngle:  desktopWidget.sunArcAngle,
                moonArcAngle: desktopWidget.moonArcAngle,
                sunVisible:   desktopWidget.sunVisible,
                moonVisible:  desktopWidget.moonVisible,
                monthIndex:   new Date().getMonth()
            })
        }
    }

    Item {
        width:   52
        height:  52
        visible: desktopWidget ? desktopWidget.sunVisible : false
        x: arcX(desktopWidget ? desktopWidget.sunArcAngle : 0) - 26
        y: arcY(desktopWidget ? desktopWidget.sunArcAngle : 0) - 26
        Behavior on x { NumberAnimation { duration: 60000; easing.type: Easing.Linear } }
        Behavior on y { NumberAnimation { duration: 60000; easing.type: Easing.Linear } }
        Rectangle {
            anchors.centerIn: parent
            width: sunGlow.sz; height: sunGlow.sz; radius: sunGlow.sz / 2
            color: Qt.rgba(0.95, 0.78, 0.22, 0.12)
        }
        Item {
            id: sunGlow
            property real sz: 60
            SequentialAnimation on sz {
                loops: Animation.Infinite
                running: root.visible && animPolicy.decorative && animPolicy.idleLoops && !animPolicy.screenIdle
                NumberAnimation { to: 76; duration: 2400; easing.type: Easing.InOutSine }
                NumberAnimation { to: 60; duration: 2400; easing.type: Easing.InOutSine }
            }
        }
        Canvas {
            anchors.fill: parent
            Component.onCompleted: requestPaint()
            onPaint: {
                var ctx = getContext("2d")
                MuchaSun.drawMuchaSun(ctx, width, height)
            }
        }
    }

    Item {
        id: earthItem
        width: 164; height: 164
        anchors.centerIn: parent

        Rectangle {
            width: 164; height: 164; radius: 82; color: "transparent"
            anchors.centerIn: parent
            border.color: Qt.rgba(desktopWidget ? desktopWidget.glowCol.r : 0.5, desktopWidget ? desktopWidget.glowCol.g : 0.5, desktopWidget ? desktopWidget.glowCol.b : 0.5, earthRing.op)
            border.width: 2
            Item {
                id: earthRing
                property real op: 0.3
                SequentialAnimation on op {
                    loops: Animation.Infinite
                    running: root.visible && animPolicy.decorative && animPolicy.idleLoops && !animPolicy.screenIdle
                    NumberAnimation { to: 0.7; duration: 2500; easing.type: Easing.InOutSine }
                    NumberAnimation { to: 0.3; duration: 2500; easing.type: Easing.InOutSine }
                }
            }
        }

        Rectangle {
            id: globeClip
            width: 120; height: 120; radius: 60; color: "#050510"; clip: true
            anchors.centerIn: parent

            Canvas {
                id: earthCanvas
                width: 120; height: 120
                anchors.centerIn: parent
                rotation: desktopWidget ? desktopWidget.earthRotation : 0
                Component.onCompleted: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    MuchaEarth.drawMuchaEarth(ctx, width, height)
                }
            }

            Canvas {
                id: cloudCanvas
                width: 120; height: 120
                anchors.centerIn: parent
                rotation: desktopWidget ? desktopWidget.cloudRotation : 0
                opacity: desktopWidget ? desktopWidget.cloudOpacity : 0
                Behavior on opacity { NumberAnimation { duration: 30000; easing.type: Easing.InOutSine } }
                Component.onCompleted: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    MuchaClouds.drawMuchaClouds(ctx, width, height)
                }
            }

            Canvas {
                id: cityLightsCanvas
                width: 120; height: 120
                anchors.centerIn: parent
                rotation: desktopWidget ? desktopWidget.earthRotation : 0
                opacity: desktopWidget ? (desktopWidget.sunVisible ? 0.20 : 0.92) : 0.20
                Behavior on opacity { NumberAnimation { duration: 30000; easing.type: Easing.InOutSine } }
                Component.onCompleted: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    MuchaCities.drawMuchaCityLights(ctx, width, height)
                }
            }
        }

        Rectangle {
            width: 132; height: 132; radius: 66; color: "transparent"
            anchors.centerIn: parent
            border.color: Qt.rgba(0.38, 0.68, 0.98, 0.34)
            border.width: 5
        }

        Rectangle {
            width: 164; height: 164; radius: 82; color: "transparent"
            anchors.centerIn: parent
            border.color: Qt.rgba(desktopWidget ? desktopWidget.glowCol.r : 0.5, desktopWidget ? desktopWidget.glowCol.g : 0.5, desktopWidget ? desktopWidget.glowCol.b : 0.5, earthRing.op)
            border.width: 2
        }
    }

    Item {
        width:   44
        height:  44
        visible: desktopWidget ? desktopWidget.moonVisible : false
        x: arcX(desktopWidget ? desktopWidget.moonArcAngle : 0) - 22
        y: arcY(desktopWidget ? desktopWidget.moonArcAngle : 0) - 22
        Behavior on x { NumberAnimation { duration: 60000; easing.type: Easing.Linear } }
        Behavior on y { NumberAnimation { duration: 60000; easing.type: Easing.Linear } }

        Rectangle {
            anchors.centerIn: parent
            width: moonGlow.sz; height: moonGlow.sz; radius: moonGlow.sz / 2
            color: Qt.rgba(0.72, 0.85, 1.0, 0.11)
        }
        Item {
            id: moonGlow
            property real sz: 52
            SequentialAnimation on sz {
                loops: Animation.Infinite
                running: root.visible && animPolicy.decorative && animPolicy.idleLoops && !animPolicy.screenIdle
                NumberAnimation { to: 66; duration: 2800; easing.type: Easing.InOutSine }
                NumberAnimation { to: 52; duration: 2800; easing.type: Easing.InOutSine }
            }
        }
        Canvas {
            id: moonCanvas
            anchors.fill: parent
            Component.onCompleted: requestPaint()
            Connections {
                target: desktopWidget
                function onMoonPhaseRatioChanged() { moonCanvas.requestPaint() }
                function onMoonWaxingChanged()     { moonCanvas.requestPaint() }
            }
            onPaint: {
                var ctx = getContext("2d")
                var phase = Math.round((desktopWidget ? desktopWidget.moonPhaseRatio : 0.5) * 15)
                MuchaMoon.drawMuchaMoon(ctx, width, height, phase)
            }
        }
    }

    Rectangle {
        anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
        height: 130
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 1.0; color: Qt.rgba(ncde.panelBg.r,ncde.panelBg.g,ncde.panelBg.b,0.50) }
        }
    }
    Rectangle {
        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
        height: 40
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color: Qt.rgba(ncde.panelBg.r,ncde.panelBg.g,ncde.panelBg.b,0.32) }
            GradientStop { position: 1.0; color: "transparent" }
        }
    }
    Rectangle {
        anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: 24
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: Qt.rgba(ncde.panelBg.r,ncde.panelBg.g,ncde.panelBg.b,0.28) }
            GradientStop { position: 1.0; color: "transparent" }
        }
    }
    Rectangle {
        anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: 24
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 1.0; color: Qt.rgba(ncde.panelBg.r,ncde.panelBg.g,ncde.panelBg.b,0.28) }
        }
    }
}
