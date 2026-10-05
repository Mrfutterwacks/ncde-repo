// SNCornerFiligree.qml — Mucha curling vine for panel corners.
import QtQuick

Canvas {
    property var theme
    property bool flipX: false
    property bool flipY: false
    antialiasing: true

    onPaint: {
        var ctx = getContext("2d")
        ctx.reset()
        ctx.save()
        if (flipX) { ctx.translate(width, 0); ctx.scale(-1, 1) }
        if (flipY) { ctx.translate(0, height); ctx.scale(1, -1) }
        ctx.scale(width / 100, height / 100)

        var g = ctx.createLinearGradient(0, 0, 100, 100)
        g.addColorStop(0,    theme.leadDeep)
        g.addColorStop(0.35, theme.lead)
        g.addColorStop(0.65, theme.leadBright)
        g.addColorStop(1,    theme.lead)
        ctx.strokeStyle = g
        ctx.lineCap = "round"

        ctx.lineWidth = 2.2
        ctx.beginPath()
        ctx.moveTo(4, 4)
        ctx.quadraticCurveTo(4, 38, 22, 50)
        ctx.quadraticCurveTo(44, 60, 50, 80)
        ctx.quadraticCurveTo(56, 96, 70, 96)
        ctx.stroke()

        ctx.lineWidth = 1.6; ctx.globalAlpha = 0.85
        ctx.beginPath()
        ctx.moveTo(18, 4)
        ctx.quadraticCurveTo(18, 24, 32, 32)
        ctx.quadraticCurveTo(46, 38, 50, 56)
        ctx.stroke()

        ctx.lineWidth = 1.3; ctx.globalAlpha = 0.7
        ctx.beginPath()
        ctx.moveTo(22, 50)
        ctx.quadraticCurveTo(12, 58, 14, 72)
        ctx.quadraticCurveTo(17, 82, 28, 80)
        ctx.stroke()
        ctx.globalAlpha = 1

        ctx.fillStyle = theme.leaf
        ctx.strokeStyle = g
        ctx.lineWidth = 0.8
        ctx.beginPath(); ctx.moveTo(32, 32); ctx.quadraticCurveTo(38, 24, 46, 28)
        ctx.quadraticCurveTo(40, 36, 32, 32); ctx.fill(); ctx.stroke()
        ctx.globalAlpha = 0.75
        ctx.beginPath(); ctx.moveTo(14, 72); ctx.quadraticCurveTo(6, 70, 4, 60)
        ctx.quadraticCurveTo(12, 62, 14, 72); ctx.fill(); ctx.stroke()
        ctx.globalAlpha = 0.7
        ctx.beginPath(); ctx.moveTo(6, 22); ctx.quadraticCurveTo(14, 20, 14, 14)
        ctx.quadraticCurveTo(10, 8, 4, 12); ctx.quadraticCurveTo(2, 18, 6, 22); ctx.fill(); ctx.stroke()
        ctx.globalAlpha = 1

        ctx.fillStyle = theme.jewelHi
        ctx.beginPath(); ctx.arc(50, 80, 3.2, 0, Math.PI * 2); ctx.fill()
        ctx.lineWidth = 0.7; ctx.stroke()
        ctx.fillStyle = theme.amberHi
        ctx.beginPath(); ctx.arc(50, 80, 1.3, 0, Math.PI * 2); ctx.fill()

        ctx.restore()
    }

    function colorA(c, a) { return Qt.rgba(c.r, c.g, c.b, a) }

    Connections {
        target: parent
        function onThemeChanged() { requestPaint() }
    }
}
