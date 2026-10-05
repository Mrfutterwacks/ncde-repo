// SNVolumeKnob.qml — Circular knob with gold arc and amber indicator.
import QtQuick

Item {
    id: root
    property var theme
    property real value: 0.7
    width: 96; height: 96

    onValueChanged: cv.requestPaint()
    onThemeChanged: cv.requestPaint()

    Canvas {
        id: cv
        anchors.fill: parent
        antialiasing: true
        renderStrategy: Canvas.Cooperative
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var w = width, h = height
            var cx = w / 2, cy = h / 2
            var r = Math.min(w, h) / 2 - 6

            ctx.strokeStyle = root.theme.leadDeep
            ctx.lineWidth = 3
            ctx.globalAlpha = 0.6
            ctx.beginPath(); ctx.arc(cx, cy, r, 0, Math.PI * 2); ctx.stroke()
            ctx.globalAlpha = 1

            var startA = (-135) * Math.PI / 180
            var endA   = (-135 + root.value * 270) * Math.PI / 180
            var lg = ctx.createLinearGradient(0, 0, 0, h)
            lg.addColorStop(0, root.theme.leadBright)
            lg.addColorStop(1, root.theme.lead)
            ctx.strokeStyle = lg
            ctx.lineWidth = 3.5
            ctx.lineCap = "round"
            ctx.beginPath(); ctx.arc(cx, cy, r, startA, endA); ctx.stroke()

            ctx.strokeStyle = root.theme.lead
            ctx.lineWidth = 1
            for (var i = 0; i < 11; i++) {
                var a = (-135 + i * 27) * Math.PI / 180
                var x1 = cx + Math.cos(a) * (r + 4)
                var y1 = cy + Math.sin(a) * (r + 4)
                var x2 = cx + Math.cos(a) * (r + 9)
                var y2 = cy + Math.sin(a) * (r + 9)
                ctx.globalAlpha = 0.4 + (i / 10) * 0.4
                ctx.beginPath(); ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.stroke()
            }
            ctx.globalAlpha = 1

            var g = ctx.createRadialGradient(cx - 4, cy - 4, 2, cx, cy, 22)
            g.addColorStop(0, addAlpha(root.theme.violetHi, 0.7))
            g.addColorStop(1, addAlpha(root.theme.violetLo, 0.7))
            ctx.fillStyle = g
            ctx.beginPath(); ctx.arc(cx, cy, 22, 0, Math.PI * 2); ctx.fill()
            ctx.strokeStyle = lg
            ctx.lineWidth = 1.5
            ctx.stroke()

            ctx.fillStyle = root.theme.amberHi
            ctx.strokeStyle = root.theme.lead
            ctx.lineWidth = 0.6
            ctx.beginPath()
            ctx.arc(cx + Math.cos(endA) * 14, cy + Math.sin(endA) * 14, 3, 0, Math.PI * 2)
            ctx.fill(); ctx.stroke()
        }

        function addAlpha(hex, a) {
            hex = String(hex).replace("#", "")
            var r = parseInt(hex.substring(0, 2), 16)
            var g = parseInt(hex.substring(2, 4), 16)
            var b = parseInt(hex.substring(4, 6), 16)
            return "rgba(" + r + "," + g + "," + b + "," + a + ")"
        }
        function colorA(c, a) { return Qt.rgba(c.r, c.g, c.b, a) }
    }

    Text {
        anchors.centerIn: parent
        text: "VOL"
        color: root.theme.leadBright
        font.family: ncde.titleFont
        font.pixelSize: theme.fontSmall
        font.letterSpacing: 2
        opacity: 0.85
    }

    property real _startY: 0
    property real _startVal: 0

    DragHandler {
        id: volDrag
        target: null
        cursorShape: Qt.SizeVerCursor
        onActiveChanged: {
            if (active) {
                root._startY   = centroid.position.y
                root._startVal = root.value
            }
        }
        onCentroidChanged: {
            if (active) {
                root.value = Math.max(0, Math.min(1, root._startVal + (root._startY - centroid.position.y) / 120))
                root.valueChanged()
            }
        }
    }

    WheelHandler {
        onWheel: (e) => {
            root.value = Math.max(0, Math.min(1, root.value + e.angleDelta.y / 1200))
            root.valueChanged()
        }
    }
}
