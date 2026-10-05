// SNPetalVisualizer.qml — Stained-glass petals with procedural spectrum animation.
import QtQuick
import Qt.labs.animation

Item {
    id: root
    property var theme
    property bool playing: false

    property real phase: 0
    property real paintElapsed: 0

    FrameAnimation {
        id: petalPump
        running: root.visible && animPolicy.decorative && !animPolicy.screenIdle
                 && !animPolicy.desktopObscured && (root.playing || animPolicy.idleLoops)
        onRunningChanged: if (!running) root.paintElapsed = 0
        onTriggered: {
            root.paintElapsed += frameTime
            var paintInterval = (animPolicy.thermalPressure || animPolicy.lowPower) ? 0.066 : 0.033
            if (root.paintElapsed < paintInterval) return
            root.phase += root.paintElapsed
            root.paintElapsed = 0
            cv.requestPaint()
        }
    }

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
            var size = Math.min(w, h)

            // Procedural spectrum — 32 bands driven by phase + noise
            var spec = []
            var bands = 32
            for (var k = 0; k < bands; k++) {
                var base = root.playing ? (Math.sin(root.phase * 1.4 + k * 0.42) * 0.5 + 0.5) : 0
                spec.push(base * (0.25 + Math.abs(Math.sin(root.phase * 0.7 + k * 0.3)) * 0.55))
            }

            var energy = 0
            for (var ek = 0; ek < bands; ek++) energy += spec[ek]
            energy = energy / bands
            var breath = (Math.sin(root.phase * 0.5) + 1) / 2 * 0.18
            var bloom = Math.max(breath, energy)

            var layers = [
                { count: 12, rOff: 0.30, len: 0.20, width: 0.10, color: "back",  baseAlpha: 0.45 },
                { count: 18, rOff: 0.28, len: 0.16, width: 0.07, color: "mid",   baseAlpha: 0.55 },
                { count: 24, rOff: 0.27, len: 0.11, width: 0.045, color: "front", baseAlpha: 0.70 },
            ]

            for (var li = 0; li < layers.length; li++) {
                var layer = layers[li]
                var baseAngle = root.phase * (0.04 + li * 0.02) * (li % 2 === 0 ? 1 : -1)

                for (var i = 0; i < layer.count; i++) {
                    var a = baseAngle + (i / layer.count) * Math.PI * 2
                    var binIdx = (Math.floor((i / layer.count) * 18) + li * 4) % bands
                    var band = spec[binIdx]
                    var reactive = band * 0.7 + bloom * 0.5

                    var len = size * layer.len * (0.6 + reactive * 0.9)
                    var pwidth = size * layer.width * (0.8 + reactive * 0.5)
                    var r0 = size * layer.rOff

                    var bx = cx + Math.cos(a) * r0
                    var by = cy + Math.sin(a) * r0
                    var tx = cx + Math.cos(a) * (r0 + len)
                    var ty = cy + Math.sin(a) * (r0 + len)
                    var pa = a + Math.PI / 2
                    var wx = Math.cos(pa) * pwidth
                    var wy = Math.sin(pa) * pwidth

                    ctx.beginPath()
                    ctx.moveTo(bx, by)
                    ctx.bezierCurveTo(bx + wx, by + wy, tx + wx * 0.4, ty + wy * 0.4, tx, ty)
                    ctx.bezierCurveTo(tx - wx * 0.4, ty - wy * 0.4, bx - wx, by - wy, bx, by)
                    ctx.closePath()

                    var midX = (bx + tx) / 2, midY = (by + ty) / 2
                    var g = ctx.createRadialGradient(midX, midY, 1, midX, midY, len * 1.1)
                    var hi, mid, lo
                    if (layer.color === "back")  { hi = root.theme.jewelHi;  mid = root.theme.jewel;     lo = root.theme.jewelLo }
                    else if (layer.color === "mid"){ hi = root.theme.amber;   mid = root.theme.amberLo;   lo = root.theme.leadDeep }
                    else                            { hi = root.theme.leadBright; mid = root.theme.lead; lo = root.theme.leadDeep }
                    g.addColorStop(0,   addAlpha(hi,  0.85 * layer.baseAlpha + reactive * 0.3))
                    g.addColorStop(0.6, addAlpha(mid, 0.55 * layer.baseAlpha + reactive * 0.25))
                    g.addColorStop(1,   addAlpha(lo,  0.15))
                    ctx.fillStyle = g
                    ctx.fill()

                    ctx.strokeStyle = "rgba(212,178,100," + (0.5 + reactive * 0.4) + ")"
                    ctx.lineWidth = 1.0
                    ctx.stroke()

                    ctx.beginPath()
                    ctx.moveTo(bx, by); ctx.lineTo(tx, ty)
                    ctx.strokeStyle = "rgba(255,230,170," + (0.18 + reactive * 0.4) + ")"
                    ctx.lineWidth = 0.6
                    ctx.stroke()

                    if (li === 2 && reactive > 0.35) {
                        ctx.beginPath()
                        ctx.arc(tx, ty, 1.8 + reactive * 2.5, 0, Math.PI * 2)
                        ctx.fillStyle = addAlpha(hi, 0.6 + reactive * 0.4)
                        ctx.fill()
                    }
                }
            }

            var bass = 0
            for (var b = 1; b < 6; b++) bass += (spec[b] || 0)
            bass = bass / 5
            var innerR = size * 0.30
            var halo = ctx.createRadialGradient(cx, cy, innerR * 0.6, cx, cy, innerR * (1.6 + bass * 0.8))
            halo.addColorStop(0, addAlpha(root.theme.glowHi, 0.30 + bass * 0.4))
            halo.addColorStop(0.6, addAlpha(root.theme.glowMid, 0.10 + bass * 0.2))
            halo.addColorStop(1, "rgba(0,0,0,0)")
            ctx.fillStyle = halo
            ctx.beginPath(); ctx.arc(cx, cy, innerR * (1.7 + bass), 0, Math.PI * 2); ctx.fill()
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
