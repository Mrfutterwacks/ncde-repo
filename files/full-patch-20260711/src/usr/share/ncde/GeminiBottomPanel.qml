// GeminiBottomPanel.qml — exact recreation of Gemini bottom filigree band.
// Reference: /home/stephen/Downloads/Gemini_Generated_Image_6t52sg6t52sg6t52.jpeg (bottom edge:
// green vine + gold scrollwork on black, crystal centre jewel).
// Live differs: /usr/share/ncde/BottomPanel.qml:11-16 is a 28px floating pill
// (12px bottom, 6px sides) with NCDEGlassSurface + NCDEPanelBezel + NCDEPowerRibbon.
// Target: full-bleed ~30px band, opaque black-green ground, continuous acanthus
// scroll, centre crystal. Single Canvas, static repaint only.
import QtQuick 2.15

Item {
    id: bot
    height: 30
    Canvas {
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        onPaint: {
            var ctx = getContext("2d"), W = width, H = height
            ctx.reset()
            ctx.fillStyle = "#070503"; ctx.fillRect(0, 0, W, H)
            // top came lip
            ctx.fillStyle = "#8a5a20"; ctx.fillRect(0, 0, W, 1)
            ctx.fillStyle = "#2a1e0e"; ctx.fillRect(0, 1, W, 2)
            // acanthus scroll: repeating leaf arcs, alternating gold/green
            var n = Math.ceil(W / 46)
            for (var i = 0; i <= n; i++) {
                var x = i * 46
                ctx.strokeStyle = (i % 2) ? "#3a7a5e" : "#b07a30"
                ctx.lineWidth = 1.4
                ctx.beginPath(); ctx.arc(x + 12, H / 2, 9, 0.3, 2.8); ctx.stroke()
                ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 1.0
                ctx.beginPath(); ctx.arc(x + 30, H / 2, 7, 3.4, 6.0); ctx.stroke()
                // jewel dot
                ctx.fillStyle = "#e9c97c"
                ctx.beginPath(); ctx.arc(x + 23, H / 2, 1.6, 0, Math.PI * 2); ctx.fill()
            }
            // centre crystal
            var cx = W / 2, cy = H / 2
            var g = ctx.createLinearGradient(cx - 6, cy - 8, cx + 6, cy + 8)
            g.addColorStop(0, "#f6e3b0"); g.addColorStop(0.5, "#8fb8c8"); g.addColorStop(1, "#3a5a6a")
            ctx.fillStyle = g
            ctx.beginPath()
            ctx.moveTo(cx, cy - 8); ctx.lineTo(cx + 5, cy); ctx.lineTo(cx, cy + 8); ctx.lineTo(cx - 5, cy)
            ctx.closePath(); ctx.fill()
            ctx.strokeStyle = "#f6e3b0"; ctx.lineWidth = 1; ctx.stroke()
        }
    }
}
