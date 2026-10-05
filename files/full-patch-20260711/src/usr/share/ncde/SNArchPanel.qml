// ArchPanel.qml — Reusable stained-glass arched panel.
import QtQuick

Item {
    id: panel
    property real archRise: 0.28
    property string accent: "jewel"
    property var theme
    property real density: 1.0

    default property alias children: contentItem.data

    Canvas {
        id: arch
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var w = width, h = height
            var archH = h * panel.archRise

            ctx.beginPath()
            ctx.moveTo(0, archH)
            ctx.quadraticCurveTo(0, 0, w * 0.18, 0)
            ctx.quadraticCurveTo(w / 2, -archH * 0.55, w * 0.82, 0)
            ctx.quadraticCurveTo(w, 0, w, archH)
            ctx.lineTo(w, h)
            ctx.lineTo(0, h)
            ctx.closePath()

            var gradTop = panel.accent === "violet" ? panel.theme.violet
                       : panel.accent === "amber"  ? panel.theme.amber
                       : panel.theme.jewel
            var gradHi  = panel.accent === "violet" ? panel.theme.violetHi
                       : panel.accent === "amber"  ? panel.theme.amberHi
                       : panel.theme.jewelHi
            var gradLo  = panel.accent === "violet" ? panel.theme.violetLo
                       : panel.accent === "amber"  ? panel.theme.amberLo
                       : panel.theme.jewelLo

            var g = ctx.createRadialGradient(w * 0.4, h * 0.35, w * 0.05, w * 0.5, h * 0.6, h * 0.9)
            g.addColorStop(0,    addAlpha(gradHi, 0.55))
            g.addColorStop(0.55, addAlpha(gradTop, 0.45))
            g.addColorStop(1,    addAlpha(gradLo, 0.65))
            ctx.fillStyle = g
            ctx.fill()

            var sheen = ctx.createLinearGradient(0, 0, 0, h)
            sheen.addColorStop(0, "rgba(255,255,255,0.08)")
            sheen.addColorStop(0.5, "rgba(255,255,255,0)")
            sheen.addColorStop(1, "rgba(0,0,0,0.20)")
            ctx.fillStyle = sheen
            ctx.fill()

            ctx.save()
            ctx.clip()
            ctx.strokeStyle = goldStroke(ctx, 0, 0, 0, h)
            ctx.lineWidth = 1.2
            ctx.globalAlpha = 0.55
            ctx.beginPath()
            ctx.moveTo(w * 0.5, 8); ctx.lineTo(w * 0.5, h - 6)
            ctx.moveTo(8, archH * 1.05); ctx.lineTo(w - 8, archH * 1.05)
            ctx.stroke()

            ctx.globalAlpha = 0.30
            ctx.lineWidth = 0.8
            for (var i = 1; i < 4; i++) {
                var y = archH + (h - archH) * (i / 4)
                ctx.beginPath()
                ctx.moveTo(8, y); ctx.lineTo(w - 8, y)
                ctx.stroke()
            }
            ctx.restore()

            ctx.lineWidth = 3
            ctx.strokeStyle = goldStroke(ctx, 0, 0, 0, h)
            ctx.beginPath()
            ctx.moveTo(0, archH)
            ctx.quadraticCurveTo(0, 0, w * 0.18, 0)
            ctx.quadraticCurveTo(w / 2, -archH * 0.55, w * 0.82, 0)
            ctx.quadraticCurveTo(w, 0, w, archH)
            ctx.lineTo(w, h)
            ctx.lineTo(0, h)
            ctx.closePath()
            ctx.stroke()

            ctx.lineWidth = 0.7
            ctx.strokeStyle = addAlpha(panel.theme.leadDeep, 0.85)
            ctx.stroke()

            ctx.fillStyle = "rgba(255,255,255,0.20)"
            var rng = new seededRng(panel.width * 37 + panel.height)
            for (var s = 0; s < 14; s++) {
                var sx = rng.next() * w
                var sy = archH + rng.next() * (h - archH)
                var sr = 0.4 + rng.next() * 0.5
                ctx.beginPath()
                ctx.arc(sx, sy, sr, 0, Math.PI * 2)
                ctx.fill()
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
        function goldStroke(ctx, x0, y0, x1, y1) {
            var g = ctx.createLinearGradient(x0, y0, x1, y1)
            g.addColorStop(0,    panel.theme.leadDeep)
            g.addColorStop(0.35, panel.theme.lead)
            g.addColorStop(0.65, panel.theme.leadBright)
            g.addColorStop(1,    panel.theme.lead)
            return g
        }
        function seededRng(seed) {
            this.s = seed % 2147483647
            if (this.s <= 0) this.s += 2147483646
            this.next = function() { this.s = this.s * 16807 % 2147483647; return (this.s - 1) / 2147483646 }
        }

        Connections {
            target: panel
            function onThemeChanged() { arch.requestPaint() }
        }
    }

    SNArchCrest {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: -28
        width: parent.width * 0.32
        height: width * 0.7
        theme: panel.theme
        visible: panel.density > 0.05
    }

    SNIrisOrnament {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 14
        width: Math.min(panel.width * 0.18, 64)
        height: width
        theme: panel.theme
        visible: panel.density > 0.5
    }

    SNCornerFiligree {
        width: Math.min(panel.width * 0.28, 90); height: width
        anchors.left: parent.left; anchors.leftMargin: -4
        anchors.top: parent.top; anchors.topMargin: parent.archRise * panel.height - 4
        theme: panel.theme
        visible: panel.density > 0.3
    }
    SNCornerFiligree {
        width: Math.min(panel.width * 0.28, 90); height: width
        anchors.right: parent.right; anchors.rightMargin: -4
        anchors.top: parent.top; anchors.topMargin: parent.archRise * panel.height - 4
        theme: panel.theme
        flipX: true
        visible: panel.density > 0.3
    }
    SNCornerFiligree {
        width: Math.min(panel.width * 0.26, 80); height: width
        anchors.left: parent.left; anchors.leftMargin: -4
        anchors.bottom: parent.bottom; anchors.bottomMargin: -4
        theme: panel.theme
        flipY: true
        visible: panel.density > 0.55
    }
    SNCornerFiligree {
        width: Math.min(panel.width * 0.26, 80); height: width
        anchors.right: parent.right; anchors.rightMargin: -4
        anchors.bottom: parent.bottom; anchors.bottomMargin: -4
        theme: panel.theme
        flipX: true; flipY: true
        visible: panel.density > 0.55
    }

    Item {
        id: contentItem
        anchors.fill: parent
    }
}
