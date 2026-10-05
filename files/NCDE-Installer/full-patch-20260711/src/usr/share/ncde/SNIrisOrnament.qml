// SNIrisOrnament.qml — Stylized Mucha iris flower.
import QtQuick

Canvas {
    property var theme
    antialiasing: true
    layer.enabled: true

    onPaint: {
        var ctx = getContext("2d")
        ctx.reset()
        ctx.scale(width / 100, height / 100)

        var leadGrad = ctx.createLinearGradient(0, 0, 0, 100)
        leadGrad.addColorStop(0, theme.leadDeep)
        leadGrad.addColorStop(0.5, theme.leadBright)
        leadGrad.addColorStop(1, theme.lead)

        ctx.strokeStyle = theme.leaf
        ctx.lineWidth = 1.8
        ctx.beginPath(); ctx.moveTo(50, 70); ctx.quadraticCurveTo(48, 85, 50, 98); ctx.stroke()

        ctx.lineWidth = 1.4
        ctx.beginPath(); ctx.moveTo(50, 70); ctx.quadraticCurveTo(38, 78, 30, 92); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(50, 70); ctx.quadraticCurveTo(62, 78, 70, 92); ctx.stroke()

        ctx.strokeStyle = leadGrad
        ctx.lineWidth = 0.9
        ctx.fillStyle = theme.violetHi
        ctx.globalAlpha = 0.92
        ctx.beginPath()
        ctx.moveTo(50, 55); ctx.quadraticCurveTo(30, 60, 28, 78)
        ctx.quadraticCurveTo(38, 72, 50, 70); ctx.closePath()
        ctx.fill(); ctx.stroke()
        ctx.beginPath()
        ctx.moveTo(50, 55); ctx.quadraticCurveTo(70, 60, 72, 78)
        ctx.quadraticCurveTo(62, 72, 50, 70); ctx.closePath()
        ctx.fill(); ctx.stroke()
        ctx.fillStyle = theme.violet
        ctx.beginPath()
        ctx.moveTo(50, 58); ctx.quadraticCurveTo(44, 75, 50, 80)
        ctx.quadraticCurveTo(56, 75, 50, 58); ctx.closePath()
        ctx.fill(); ctx.stroke()

        ctx.fillStyle = theme.violetHi
        ctx.beginPath()
        ctx.moveTo(50, 50); ctx.quadraticCurveTo(36, 35, 34, 18)
        ctx.quadraticCurveTo(44, 22, 50, 36); ctx.closePath()
        ctx.fill(); ctx.stroke()
        ctx.beginPath()
        ctx.moveTo(50, 50); ctx.quadraticCurveTo(64, 35, 66, 18)
        ctx.quadraticCurveTo(56, 22, 50, 36); ctx.closePath()
        ctx.fill(); ctx.stroke()
        ctx.fillStyle = theme.glowHi
        ctx.beginPath()
        ctx.moveTo(50, 48); ctx.quadraticCurveTo(46, 28, 50, 12)
        ctx.quadraticCurveTo(54, 28, 50, 48); ctx.closePath()
        ctx.fill(); ctx.stroke()

        ctx.fillStyle = theme.amberHi
        ctx.beginPath(); ctx.arc(50, 52, 2.4, 0, Math.PI * 2); ctx.fill(); ctx.stroke()
    }

    function colorA(c, a) { return Qt.rgba(c.r, c.g, c.b, a) }

    Connections {
        target: parent
        function onThemeChanged() { requestPaint() }
    }
}
