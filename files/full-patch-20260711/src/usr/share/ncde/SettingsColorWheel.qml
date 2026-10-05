// SettingsColorWheel.qml — HSV color wheel, GPU-rendered via ShaderEffect.
// Hue = angle (red at east), Saturation = radius, Value = brightness strip below.

import QtQuick

Item {
    id: wheel
    implicitWidth:  340
    implicitHeight: 390   // 340 wheel + 50 for brightness strip

    property real hue:        36    // 0..360
    property real saturation: 0.75  // 0..1
    property real value:      1.0   // 0..1  (brightness)

    readonly property color  current:    Qt.hsva(hue / 360.0, saturation, value, 1.0)
    readonly property string currentHex: {
        var c = Qt.hsva(hue / 360.0, saturation, value, 1.0)
        function h2(v) { return Math.round(v * 255).toString(16).padStart(2, "0") }
        return ("#" + h2(c.r) + h2(c.g) + h2(c.b)).toUpperCase()
    }
    signal picked(real hue, real saturation)

    // ── Wheel disc ────────────────────────────────────────────────────────
    Item {
        id: discArea
        width: Math.min(parent.width, parent.height - 50)
        height: width
        anchors.horizontalCenter: parent.horizontalCenter

        // Canvas base — always renders the HSV wheel; visible if shader fails
        Canvas {
            id: wheelCanvas
            anchors.fill: parent
            renderStrategy: Canvas.Cooperative
            layer.enabled: true
            onVisibleChanged: if (visible) requestPaint()
            Component.onCompleted: requestPaint()

            onPaint: {
                var ctx = getContext("2d")
                if (!ctx) { Qt.callLater(requestPaint); return }
                var cx = width / 2, cy = height / 2
                var r  = Math.min(cx, cy) - 6
                ctx.clearRect(0, 0, width, height)

                function h2(v) { return Math.round(v * 255).toString(16).padStart(2, "0") }

                var hueGrad = ctx.createConicalGradient(cx, cy, 0)
                for (var h = 0; h <= 360; h += 2) {
                    var c = Qt.hsva(h / 360, 1.0, 1.0, 1.0)
                    hueGrad.addColorStop(h / 360, "#" + h2(c.r) + h2(c.g) + h2(c.b))
                }
                ctx.beginPath()
                ctx.arc(cx, cy, r, 0, Math.PI * 2, false)
                ctx.fillStyle = hueGrad
                ctx.fill()

                var satGrad = ctx.createRadialGradient(cx, cy, 0, cx, cy, r)
                satGrad.addColorStop(0, 'rgba(255,255,255,1)')
                satGrad.addColorStop(1, 'rgba(255,255,255,0)')
                ctx.beginPath()
                ctx.arc(cx, cy, r, 0, Math.PI * 2, false)
                ctx.fillStyle = satGrad
                ctx.fill()
            }
        }

        // ShaderEffect overlay — GPU quality when the .qsb loads; transparent on failure, Canvas shows through
        ShaderEffect {
            id: shaderDisc
            anchors.fill: parent
            fragmentShader: "qrc:/shaders/qml/compositor/colorwheel.frag.qsb"
        }

        // triple gold frame rings
        Rectangle {
            anchors.fill: parent; radius: width / 2
            color: "transparent"; border.color: ncde.gilt0; border.width: 3
        }
        Rectangle {
            anchors.fill: parent; anchors.margins: 3; radius: width / 2
            color: "transparent"; border.color: ncde.gilt3; border.width: 2
        }
        Rectangle {
            anchors.fill: parent; anchors.margins: 5; radius: width / 2
            color: "transparent"; border.color: ncde.gilt4; border.width: 2
        }

        // indicator dot
        Rectangle {
            id: ind
            width: 22; height: 22; radius: 11
            color: Qt.hsva(wheel.hue / 360.0, wheel.saturation, 1.0, 1.0)
            border.color: ncde.surface; border.width: 3
            z: 5
            x: {
                var cx = discArea.width / 2
                var r  = (Math.min(discArea.width, discArea.height) / 2 - 6) * wheel.saturation
                return cx + r * Math.cos(wheel.hue * Math.PI / 180) - width / 2
            }
            y: {
                var cy = discArea.height / 2
                var r  = (Math.min(discArea.width, discArea.height) / 2 - 6) * wheel.saturation
                return cy + r * Math.sin(wheel.hue * Math.PI / 180) - height / 2
            }
            Rectangle {
                anchors.fill: parent; anchors.margins: -3; radius: width / 2
                color: "transparent"; border.color: ncde.gilt0; border.width: 2; z: -1
            }
        }

        function _pickAt(px, py) {
            var cx = width / 2, cy = height / 2
            var dx = px - cx, dy = py - cy
            var dist = Math.sqrt(dx*dx + dy*dy)
            var r  = Math.min(cx, cy) - 6
            var ang = Math.atan2(dy, dx) * 180 / Math.PI
            if (ang < 0) ang += 360
            wheel.hue        = ang
            // no minimum clamp (was 0.15) — the wheel centre must reach true
            // neutrals, else pure white/grey text colours are unpickable
            wheel.saturation = Math.min(1, dist / r)
            wheel.picked(wheel.hue, wheel.saturation)
        }

        TapHandler {
            onTapped: discArea._pickAt(point.position.x, point.position.y)
        }
        DragHandler {
            target: null
            onCentroidChanged: if (active) discArea._pickAt(centroid.position.x, centroid.position.y)
        }
    }

    // ── Brightness strip ─────────────────────────────────────────────────
    Item {
        id: brightStrip
        anchors.top: discArea.bottom
        anchors.topMargin: 12
        anchors.left: discArea.left
        anchors.right: discArea.right
        height: 22

        Rectangle {
            anchors.fill: parent
            radius: height / 2
            border.color: ncde.gilt1; border.width: 1.5

            // gradient: left = black, right = full-brightness hue at current sat
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: "#000000" }
                GradientStop { position: 1.0; color: Qt.hsva(wheel.hue / 360.0, wheel.saturation, 1.0, 1.0) }
            }
        }

        // brightness indicator
        Rectangle {
            id: brightInd
            width: 18; height: 18; radius: 9
            border.color: ncde.surface; border.width: 2
            color: wheel.current
            x: wheel.value * (brightStrip.width - width)
            anchors.verticalCenter: parent.verticalCenter
            Rectangle {
                anchors.fill: parent; anchors.margins: -2; radius: width / 2
                color: "transparent"; border.color: ncde.gilt0; border.width: 1.5; z: -1
            }
        }

        TapHandler {
            onTapped: wheel.value = Math.max(0, Math.min(1, point.position.x / brightStrip.width))
        }
        DragHandler {
            target: null
            onCentroidChanged: {
                if (active)
                    wheel.value = Math.max(0, Math.min(1, centroid.position.x / brightStrip.width))
            }
        }
    }
}
