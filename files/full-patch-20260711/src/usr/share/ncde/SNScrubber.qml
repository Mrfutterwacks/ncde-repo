// SNScrubber.qml — Horizontal seek bar with a jewel head.
import QtQuick

Item {
    id: root
    property var theme
    property real position: 0
    property real duration: 1
    signal seek(real ms)

    height: 22

    readonly property real pct: duration > 0 ? Math.min(1, Math.max(0, position / duration)) : 0

    Canvas {
        id: cv
        anchors.fill: parent
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var w = width, h = height
            var cy = h / 2

            var trackG = ctx.createLinearGradient(0, cy, w, cy)
            trackG.addColorStop(0, addAlpha(root.theme.leadDeep, 0.6))
            trackG.addColorStop(0.5, addAlpha(root.theme.lead, 0.5))
            trackG.addColorStop(1, addAlpha(root.theme.leadDeep, 0.6))
            ctx.fillStyle = trackG
            roundRect(ctx, 0, cy - 2, w, 4, 2); ctx.fill()

            var fillW = w * root.pct
            var fillG = ctx.createLinearGradient(0, cy, w, cy)
            fillG.addColorStop(0, root.theme.leadDeep)
            fillG.addColorStop(1, root.theme.leadBright)
            ctx.fillStyle = fillG
            roundRect(ctx, 0, cy - 2, fillW, 4, 2); ctx.fill()

            var jx = fillW, jy = cy
            var jg = ctx.createRadialGradient(jx - 3, jy - 3, 1, jx, jy, 8)
            jg.addColorStop(0, root.theme.amberHi)
            jg.addColorStop(0.6, root.theme.amber)
            jg.addColorStop(1, root.theme.leadDeep)
            ctx.fillStyle = jg
            ctx.beginPath(); ctx.arc(jx, jy, 7, 0, Math.PI * 2); ctx.fill()
            ctx.strokeStyle = root.theme.leadBright
            ctx.lineWidth = 1
            ctx.stroke()
        }
        function addAlpha(hex, a) {
            hex = String(hex).replace("#", "")
            var r = parseInt(hex.substring(0, 2), 16)
            var g = parseInt(hex.substring(2, 4), 16)
            var b = parseInt(hex.substring(4, 6), 16)
            return "rgba(" + r + "," + g + "," + b + "," + a + ")"
        }
        function colorA(c, a) { return Qt.rgba(c.r, c.g, c.b, a) }
        function roundRect(ctx, x, y, w, h, r) {
            r = Math.min(r, w / 2, h / 2)
            ctx.beginPath()
            ctx.moveTo(x + r, y)
            ctx.arcTo(x + w, y, x + w, y + h, r)
            ctx.arcTo(x + w, y + h, x, y + h, r)
            ctx.arcTo(x, y + h, x, y, r)
            ctx.arcTo(x, y, x + w, y, r)
            ctx.closePath()
        }
    }

    onPositionChanged: cv.requestPaint()
    onDurationChanged: cv.requestPaint()
    onThemeChanged: cv.requestPaint()
    onWidthChanged: cv.requestPaint()

    function seekAt(x) {
        var p = Math.max(0, Math.min(1, x / width))
        root.seek(p * root.duration)
    }

    TapHandler {
        cursorShape: Qt.PointingHandCursor
        onTapped: (e) => root.seekAt(e.position.x)
    }

    DragHandler {
        target: null
        cursorShape: Qt.PointingHandCursor
        grabPermissions: PointHandler.CanTakeOverFromAnything
        onCentroidChanged: {
            if (active) root.seekAt(centroid.position.x)
        }
    }
}
