// SNRoseHalo.qml — Static rose-window halo behind the gramophone.
import QtQuick

Canvas {
    property var theme
    antialiasing: true
    layer.enabled: true

    onPaint: {
        var ctx = getContext("2d")
        ctx.reset()
        var w = width, h = height
        var cx = w / 2, cy = h / 2
        var r = Math.min(w, h) / 2 - 4

        var lg = ctx.createLinearGradient(0, 0, 0, h)
        lg.addColorStop(0, theme.leadDeep)
        lg.addColorStop(0.5, theme.leadBright)
        lg.addColorStop(1, theme.lead)

        ctx.strokeStyle = lg
        ctx.globalAlpha = 0.55

        ctx.lineWidth = 1.4
        ctx.beginPath(); ctx.arc(cx, cy, r, 0, Math.PI * 2); ctx.stroke()
        ctx.globalAlpha = 0.45
        ctx.lineWidth = 0.5
        ctx.beginPath(); ctx.arc(cx, cy, r * 0.96, 0, Math.PI * 2); ctx.stroke()

        ctx.globalAlpha = 0.4
        ctx.lineWidth = 0.9
        for (var i = 0; i < 12; i++) {
            var a = (i / 12) * Math.PI * 2 - Math.PI / 2
            var x1 = cx + Math.cos(a) * r * 0.58
            var y1 = cy + Math.sin(a) * r * 0.58
            var x2 = cx + Math.cos(a) * r * 0.95
            var y2 = cy + Math.sin(a) * r * 0.95
            ctx.beginPath(); ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.stroke()
        }

        ctx.lineWidth = 1.1; ctx.globalAlpha = 0.55
        ctx.beginPath(); ctx.arc(cx, cy, r * 0.55, 0, Math.PI * 2); ctx.stroke()
        ctx.lineWidth = 0.7
        ctx.beginPath(); ctx.arc(cx, cy, r * 0.40, 0, Math.PI * 2); ctx.stroke()
        ctx.globalAlpha = 1

        for (var j = 0; j < 24; j++) {
            var ja = (j / 24) * Math.PI * 2
            var jx = cx + Math.cos(ja) * r * 0.96
            var jy = cy + Math.sin(ja) * r * 0.96
            ctx.fillStyle = (j % 3 === 0) ? theme.amberHi : theme.violetHi
            ctx.strokeStyle = theme.lead
            ctx.lineWidth = 0.6
            ctx.beginPath(); ctx.arc(jx, jy, j % 2 === 0 ? 3.2 : 2.2, 0, Math.PI * 2)
            ctx.fill(); ctx.stroke()
        }
    }

    function colorA(c, a) { return Qt.rgba(c.r, c.g, c.b, a) }

    Connections {
        target: parent
        function onThemeChanged() { requestPaint() }
    }
}
