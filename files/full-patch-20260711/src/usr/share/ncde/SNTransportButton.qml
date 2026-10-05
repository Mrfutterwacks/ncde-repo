// SNTransportButton.qml — Round leaded-glass jewel button with a glyph.
import QtQuick

Item {
    id: root
    property var theme
    property string glyph: "play"
    property real size: 60
    signal clicked()

    width: size; height: size

    property bool isPressed: false

    Canvas {
        id: cv
        anchors.fill: parent
        antialiasing: true
        renderStrategy: Canvas.Cooperative
        scale: root.isPressed ? 0.94 : 1.0
        Behavior on scale { NumberAnimation { duration: 80 } }

        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var w = width, h = height
            var cx = w / 2, cy = h / 2
            var r = Math.min(w, h) / 2 - 2

            var g = ctx.createRadialGradient(cx - r * 0.25, cy - r * 0.3, r * 0.1, cx, cy, r)
            g.addColorStop(0,   addAlpha(theme.violetHi, 0.55))
            g.addColorStop(0.55, addAlpha(theme.violet, 0.45))
            g.addColorStop(1,   addAlpha(theme.violetLo, 0.6))
            ctx.fillStyle = g
            ctx.beginPath(); ctx.arc(cx, cy, r, 0, Math.PI * 2); ctx.fill()

            var lg = ctx.createLinearGradient(0, 0, 0, h)
            lg.addColorStop(0, theme.leadDeep)
            lg.addColorStop(0.5, theme.leadBright)
            lg.addColorStop(1, theme.lead)
            ctx.strokeStyle = lg
            ctx.lineWidth = 1.6
            ctx.beginPath(); ctx.arc(cx, cy, r, 0, Math.PI * 2); ctx.stroke()

            ctx.strokeStyle = "rgba(255,255,255,0.18)"
            ctx.lineWidth = 0.8
            ctx.beginPath(); ctx.arc(cx, cy, r - 3, 0, Math.PI * 2); ctx.stroke()

            ctx.fillStyle = theme.leadBright
            ctx.strokeStyle = theme.leadDeep
            ctx.lineWidth = 0.6
            var s = r * 0.5
            if (glyph === "play") {
                ctx.beginPath()
                ctx.moveTo(cx - s * 0.5, cy - s * 0.8)
                ctx.lineTo(cx + s * 0.9, cy)
                ctx.lineTo(cx - s * 0.5, cy + s * 0.8)
                ctx.closePath(); ctx.fill(); ctx.stroke()
            } else if (glyph === "pause") {
                var bw = s * 0.4, bh = s * 1.5
                ctx.fillRect(cx - bw - 2, cy - bh / 2, bw, bh)
                ctx.fillRect(cx + 2, cy - bh / 2, bw, bh)
                ctx.strokeRect(cx - bw - 2, cy - bh / 2, bw, bh)
                ctx.strokeRect(cx + 2, cy - bh / 2, bw, bh)
            } else if (glyph === "prev") {
                ctx.fillRect(cx - s, cy - s * 0.7, 2.5, s * 1.4)
                ctx.beginPath()
                ctx.moveTo(cx + s * 0.8, cy - s * 0.8)
                ctx.lineTo(cx - s * 0.4, cy)
                ctx.lineTo(cx + s * 0.8, cy + s * 0.8)
                ctx.closePath(); ctx.fill(); ctx.stroke()
            } else if (glyph === "next") {
                ctx.fillRect(cx + s - 2.5, cy - s * 0.7, 2.5, s * 1.4)
                ctx.beginPath()
                ctx.moveTo(cx - s * 0.8, cy - s * 0.8)
                ctx.lineTo(cx + s * 0.4, cy)
                ctx.lineTo(cx - s * 0.8, cy + s * 0.8)
                ctx.closePath(); ctx.fill(); ctx.stroke()
            }
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

    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: "transparent"
        border.width: 1.5
        border.color: hover.hovered ? root.theme.leadBright : "transparent"
        opacity: hover.hovered ? 1 : 0
        Behavior on opacity { NumberAnimation { duration: 120 } }
    }

    HoverHandler {
        id: hover
        cursorShape: Qt.PointingHandCursor
    }

    TapHandler {
        onPressedChanged: root.isPressed = pressed
        onTapped: root.clicked()
    }

    Connections {
        target: root
        function onThemeChanged() { cv.requestPaint() }
        function onGlyphChanged() { cv.requestPaint() }
    }
}
