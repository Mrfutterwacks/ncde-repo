// SNFiligreeDivider.qml — Horizontal gold filigree with center medallion.
import QtQuick

Canvas {
    property var theme
    height: 24
    antialiasing: true

    onPaint: {
        var ctx = getContext("2d")
        ctx.reset()
        var w = width, h = height
        var cy = h / 2
        var cx = w / 2

        var lead = ctx.createLinearGradient(0, cy, w, cy)
        lead.addColorStop(0, theme.leadDeep)
        lead.addColorStop(0.5, theme.leadBright)
        lead.addColorStop(1, theme.leadDeep)

        ctx.strokeStyle = lead
        ctx.globalAlpha = 0.6
        ctx.lineWidth = 1
        ctx.beginPath()
        ctx.moveTo(0, cy); ctx.lineTo(w, cy)
        ctx.stroke()
        ctx.globalAlpha = 1

        ctx.lineWidth = 0.9
        ctx.beginPath()
        ctx.moveTo(cx - 8, cy)
        ctx.quadraticCurveTo(cx - 24, cy - 8, cx - 38, cy)
        ctx.quadraticCurveTo(cx - 52, cy + 8, cx - 60, cy)
        ctx.stroke()
        ctx.beginPath()
        ctx.moveTo(cx + 8, cy)
        ctx.quadraticCurveTo(cx + 24, cy - 8, cx + 38, cy)
        ctx.quadraticCurveTo(cx + 52, cy + 8, cx + 60, cy)
        ctx.stroke()

        ctx.fillStyle = theme.amberHi
        ctx.beginPath(); ctx.arc(cx - 72, cy, 1.6, 0, Math.PI * 2); ctx.fill()
        ctx.beginPath(); ctx.arc(cx + 72, cy, 1.6, 0, Math.PI * 2); ctx.fill()

        ctx.fillStyle = theme.violetHi
        ctx.strokeStyle = lead
        ctx.lineWidth = 0.8
        ctx.beginPath(); ctx.arc(cx, cy, 6, 0, Math.PI * 2); ctx.fill(); ctx.stroke()
        ctx.fillStyle = theme.amberHi
        ctx.beginPath(); ctx.arc(cx, cy, 2.2, 0, Math.PI * 2); ctx.fill()
    }

    function colorA(c, a) { return Qt.rgba(c.r, c.g, c.b, a) }

    Connections {
        target: parent
        function onThemeChanged() { requestPaint() }
    }
}
