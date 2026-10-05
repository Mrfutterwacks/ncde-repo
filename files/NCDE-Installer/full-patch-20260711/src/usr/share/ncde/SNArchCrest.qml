// SNArchCrest.qml — Symmetric leaf crest with iris bud at the apex of an arch.
import QtQuick

Canvas {
    property var theme
    antialiasing: true
    layer.enabled: true

    onPaint: {
        var ctx = getContext("2d")
        ctx.reset()
        ctx.scale(width / 110, height / 88)

        var lead = ctx.createLinearGradient(0, 0, 110, 88)
        lead.addColorStop(0, theme.leadDeep)
        lead.addColorStop(0.5, theme.leadBright)
        lead.addColorStop(1, theme.lead)

        ctx.fillStyle = theme.leaf
        ctx.strokeStyle = lead
        ctx.lineWidth = 1.2
        ctx.globalAlpha = 0.92
        ctx.beginPath()
        ctx.moveTo(55, 60)
        ctx.quadraticCurveTo(30, 50, 12, 56)
        ctx.quadraticCurveTo(22, 40, 40, 38)
        ctx.quadraticCurveTo(28, 28, 32, 14)
        ctx.quadraticCurveTo(44, 22, 55, 32)
        ctx.quadraticCurveTo(66, 22, 78, 14)
        ctx.quadraticCurveTo(82, 28, 70, 38)
        ctx.quadraticCurveTo(88, 40, 98, 56)
        ctx.quadraticCurveTo(80, 50, 55, 60)
        ctx.closePath()
        ctx.fill(); ctx.stroke()
        ctx.globalAlpha = 1

        ctx.fillStyle = theme.violet
        ctx.beginPath(); ctx.ellipse(55 - 6, 50 - 14, 12, 28); ctx.fill(); ctx.stroke()
        ctx.fillStyle = theme.violetHi
        ctx.beginPath(); ctx.ellipse(55 - 3, 44 - 8, 6, 16); ctx.fill()

        ctx.strokeStyle = lead
        ctx.lineWidth = 1
        ctx.beginPath(); ctx.moveTo(12, 56); ctx.quadraticCurveTo(4, 72, 16, 82); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(98, 56); ctx.quadraticCurveTo(106, 72, 94, 82); ctx.stroke()
        ctx.fillStyle = theme.amberHi
        ctx.beginPath(); ctx.arc(16, 82, 2.6, 0, Math.PI * 2); ctx.fill(); ctx.stroke()
        ctx.beginPath(); ctx.arc(94, 82, 2.6, 0, Math.PI * 2); ctx.fill(); ctx.stroke()
    }

    function colorA(c, a) { return Qt.rgba(c.r, c.g, c.b, a) }

    Connections {
        target: parent
        function onThemeChanged() { requestPaint() }
    }
}
