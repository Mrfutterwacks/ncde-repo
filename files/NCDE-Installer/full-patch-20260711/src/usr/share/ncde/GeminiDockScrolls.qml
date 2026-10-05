// GeminiDockScrolls.qml — left-dock top/bottom volutes from Gemini image.
// Reference: Gemini_Generated_Image (left vertical dock: gold scroll caps,
// ~40px tall each, acanthus volute + ball terminal).
// Live differs: /usr/share/ncde/Dock.qml:126-141 is a plain glass pill
// (cornerRadius = dockWidth/2), no caps. This Canvas draws the two caps;
// place above/below the dock glass, same width (64px), static.
import QtQuick 2.15

Item {
    id: caps
    width: 64; height: 84
    property bool isTop: true
    Canvas {
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        onPaint: {
            var ctx = getContext("2d"), W = width, H = height
            var flip = caps.isTop ? 1 : -1, cy = caps.isTop ? H - 8 : 8
            ctx.reset()
            ctx.save(); ctx.translate(0, cy); ctx.scale(1, flip)
            // outer volute
            ctx.strokeStyle = "#b07a30"; ctx.lineWidth = 2.2
            ctx.beginPath(); ctx.arc(W / 2, 22, 20, Math.PI * 1.05, Math.PI * 1.95); ctx.stroke()
            ctx.strokeStyle = "#e9c97c"; ctx.lineWidth = 1.0
            ctx.beginPath(); ctx.arc(W / 2, 22, 16, Math.PI * 1.1, Math.PI * 1.9); ctx.stroke()
            // inner spiral
            ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 1.4
            ctx.beginPath(); ctx.arc(W / 2 - 8, 30, 7, 0, Math.PI * 1.7); ctx.stroke()
            // ball terminal
            var g = ctx.createRadialGradient(W / 2 + 10, 12, 0, W / 2 + 10, 12, 6)
            g.addColorStop(0, "#f6e3b0"); g.addColorStop(1, "#5a3a14")
            ctx.fillStyle = g
            ctx.beginPath(); ctx.arc(W / 2 + 10, 12, 5, 0, Math.PI * 2); ctx.fill()
            ctx.restore()
        }
    }
}
