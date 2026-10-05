// SNGramophone.qml — Brass horn with stained-glass insert + spinning disc.
import QtQuick

Item {
    id: root
    property var theme
    property bool spinning: false
    property string albumLabel: ""
    readonly property real motionDurationScale: animPolicy.thermalPressure || animPolicy.lowPower ? 2.0 : 1.0

    Item {
        id: discContainer
        anchors.fill: parent

        RotationAnimator on rotation {
            running: root.visible && root.spinning && animPolicy.decorative
                     && !animPolicy.screenIdle && !animPolicy.desktopObscured
            from: 0; to: 360
            duration: 6000 * root.motionDurationScale
            loops: Animation.Infinite
        }

        Canvas {
            id: disc
            anchors.centerIn: parent
            width: parent.width * 0.48
            height: width
            antialiasing: true
            renderStrategy: Canvas.Cooperative
            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()
                var w = width, h = height
                var cx = w / 2, cy = h / 2
                var r = Math.min(w, h) / 2 - 2

                var g = ctx.createRadialGradient(cx, cy, 1, cx, cy, r)
                g.addColorStop(0, root.theme.violetHi)
                g.addColorStop(0.4, "#0c0918")
                g.addColorStop(1, "#000000")
                ctx.fillStyle = g
                ctx.beginPath(); ctx.arc(cx, cy, r, 0, Math.PI * 2); ctx.fill()

                var lg = ctx.createLinearGradient(0, 0, 0, h)
                lg.addColorStop(0, root.theme.leadBright)
                lg.addColorStop(1, root.theme.lead)
                ctx.strokeStyle = lg
                ctx.lineWidth = 2
                ctx.stroke()

                ctx.strokeStyle = "rgba(255,255,255,0.04)"
                ctx.lineWidth = 0.5
                for (var i = 0; i < 14; i++) {
                    ctx.beginPath(); ctx.arc(cx, cy, r - 6 - i * 4, 0, Math.PI * 2); ctx.stroke()
                }

                ctx.save()
                ctx.translate(cx, cy)
                ctx.rotate(-25 * Math.PI / 180)
                ctx.fillStyle = "rgba(255,255,255,0.06)"
                ctx.beginPath(); ctx.ellipse(-r * 0.3, -r * 0.15, r * 0.5, r * 0.18); ctx.fill()
                ctx.restore()

                ctx.fillStyle = addAlpha(root.theme.violet, 0.6)
                ctx.beginPath(); ctx.arc(cx, cy, r * 0.36, 0, Math.PI * 2); ctx.fill()
                ctx.strokeStyle = lg
                ctx.lineWidth = 1.5
                ctx.stroke()

                ctx.strokeStyle = root.theme.lead
                ctx.lineWidth = 0.7; ctx.globalAlpha = 0.6
                ctx.beginPath()
                ctx.moveTo(cx - r * 0.36, cy); ctx.lineTo(cx + r * 0.36, cy)
                ctx.moveTo(cx, cy - r * 0.36); ctx.lineTo(cx, cy + r * 0.36)
                ctx.stroke()
                ctx.globalAlpha = 1

                if (root.albumLabel) {
                    ctx.fillStyle = root.theme.leadBright
                    ctx.font = "italic 10px 'Cormorant Garamond'"
                    ctx.textAlign = "center"
                    ctx.globalAlpha = 0.85
                    ctx.fillText(root.albumLabel.toUpperCase(), cx, cy - r * 0.18)
                    ctx.globalAlpha = 1
                }

                ctx.fillStyle = root.theme.leadBright
                ctx.beginPath(); ctx.arc(cx, cy, 5, 0, Math.PI * 2); ctx.fill()
                ctx.strokeStyle = root.theme.leadDeep
                ctx.lineWidth = 0.8; ctx.stroke()
                ctx.fillStyle = root.theme.leadDeep
                ctx.beginPath(); ctx.arc(cx, cy, 1.5, 0, Math.PI * 2); ctx.fill()
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
    }

    Canvas {
        id: horn
        anchors.fill: parent
        antialiasing: true
        renderStrategy: Canvas.Cooperative
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var w = width, h = height
            var cx = w / 2, cy = h / 2
            ctx.translate(cx, cy)

            ctx.fillStyle = addAlpha(root.theme.leadDeep, 0.7)
            ctx.beginPath(); ctx.arc(-w * 0.05, -h * 0.25, w * 0.32, 0, Math.PI * 2); ctx.fill()

            var brass = ctx.createRadialGradient(-w * 0.12, -h * 0.32, w * 0.05, -w * 0.05, -h * 0.25, w * 0.32)
            brass.addColorStop(0, "#fde9b3")
            brass.addColorStop(0.4, root.theme.leadBright)
            brass.addColorStop(0.85, root.theme.leadDeep)
            brass.addColorStop(1, "#3a2806")
            ctx.fillStyle = brass
            ctx.beginPath(); ctx.arc(-w * 0.05, -h * 0.25, w * 0.30, 0, Math.PI * 2); ctx.fill()

            var glass = ctx.createRadialGradient(-w * 0.08, -h * 0.30, w * 0.02, -w * 0.05, -h * 0.25, w * 0.25)
            glass.addColorStop(0, addAlpha(root.theme.jewelHi, 0.85))
            glass.addColorStop(0.7, addAlpha(root.theme.jewel, 0.55))
            glass.addColorStop(1, addAlpha(root.theme.jewelLo, 0.3))
            ctx.fillStyle = glass
            ctx.beginPath(); ctx.arc(-w * 0.05, -h * 0.25, w * 0.25, 0, Math.PI * 2); ctx.fill()

            ctx.strokeStyle = root.theme.leadBright
            ctx.lineWidth = 1.4
            ctx.globalAlpha = 0.85
            for (var i = 0; i < 8; i++) {
                var a = (i / 8) * Math.PI * 2
                var r1 = w * 0.04, r2 = w * 0.25
                var cxx = -w * 0.05, cyy = -h * 0.25
                ctx.beginPath()
                ctx.moveTo(cxx + Math.cos(a) * r1, cyy + Math.sin(a) * r1)
                ctx.lineTo(cxx + Math.cos(a) * r2, cyy + Math.sin(a) * r2)
                ctx.stroke()
            }
            ctx.globalAlpha = 1

            ctx.lineWidth = 2.5
            var ringG = ctx.createLinearGradient(0, -h * 0.5, 0, 0)
            ringG.addColorStop(0, root.theme.leadBright)
            ringG.addColorStop(1, root.theme.lead)
            ctx.strokeStyle = ringG
            ctx.beginPath(); ctx.arc(-w * 0.05, -h * 0.25, w * 0.25, 0, Math.PI * 2); ctx.stroke()

            ctx.fillStyle = root.theme.amberHi
            ctx.globalAlpha = 0.5
            ctx.beginPath(); ctx.arc(-w * 0.16, -h * 0.34, w * 0.025, 0, Math.PI * 2); ctx.fill()
            ctx.globalAlpha = 1

            ctx.fillStyle = brass
            ctx.beginPath()
            ctx.moveTo(w * 0.14, -h * 0.14)
            ctx.quadraticCurveTo(w * 0.20, -h * 0.08, w * 0.20, 0)
            ctx.lineTo(w * 0.14, h * 0.035)
            ctx.quadraticCurveTo(w * 0.11, -h * 0.045, w * 0.11, -h * 0.105)
            ctx.closePath()
            ctx.fill(); ctx.strokeStyle = root.theme.leadDeep; ctx.lineWidth = 1.4; ctx.stroke()

            ctx.strokeStyle = ringG
            ctx.lineWidth = 8
            ctx.lineCap = "round"
            ctx.beginPath()
            ctx.moveTo(w * 0.14, h * 0.035)
            ctx.quadraticCurveTo(w * 0.14, h * 0.14, 0, h * 0.22)
            ctx.stroke()
            ctx.strokeStyle = addAlpha(root.theme.leadDeep, 0.6)
            ctx.lineWidth = 1; ctx.stroke()

            ctx.fillStyle = brass
            ctx.beginPath(); ctx.arc(w * 0.14, h * 0.035, 7, 0, Math.PI * 2); ctx.fill()
            ctx.strokeStyle = root.theme.leadDeep
            ctx.lineWidth = 1; ctx.stroke()
            ctx.fillStyle = root.theme.leadDeep
            ctx.beginPath(); ctx.arc(w * 0.14, h * 0.035, 2, 0, Math.PI * 2); ctx.fill()

            ctx.fillStyle = brass
            ctx.beginPath(); ctx.ellipse(0, h * 0.22, 10, 6); ctx.fill()
            ctx.strokeStyle = root.theme.leadDeep
            ctx.lineWidth = 1; ctx.stroke()
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

    Connections {
        target: root
        function onThemeChanged() { disc.requestPaint(); horn.requestPaint() }
        function onAlbumLabelChanged() { disc.requestPaint() }
    }
}
