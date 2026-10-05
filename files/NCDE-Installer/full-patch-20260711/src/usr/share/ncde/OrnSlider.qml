// OrnSlider.qml — Art Nouveau ornate horizontal slider
// Gold-rim track, burgundy fill, jeweled bronze thumb.
// API: from, to, value, stepSize, tickCount
//      onMoved (while dragging), onReleased (on release — wire saves here)
import QtQuick 2.15

Item {
    id: orn
    height: 32

    readonly property color anGold1: ncde.gilt0
    readonly property color anGold2: ncde.gilt1
    readonly property color anGold3: ncde.gilt2
    readonly property color anGold4: ncde.gilt3
    readonly property color anGold5: ncde.gilt4
    readonly property color anGold6: ncde.gilt5
    readonly property color anBurg1: ncde.wine2
    readonly property color anBurg2: ncde.wine4

    property real from: 0
    property real to: 100
    property real value: 0
    property real stepSize: 0
    property bool pressed: dragHandler.active
    property int  tickCount: 0
    signal moved()
    signal released()

    function _clamp(v) { return Math.max(from, Math.min(to, v)) }
    function _quantize(v) {
        if (stepSize <= 0) return _clamp(v)
        var n = Math.round((v - from) / stepSize)
        return _clamp(from + n * stepSize)
    }
    function _setFromX(x) {
        var t = Math.max(0, Math.min(1, x / width))
        var q = _quantize(from + t * (to - from))
        if (q !== value) { value = q; orn.moved() }
    }

    readonly property real _pos: width * Math.max(0, Math.min(1, (value - from) / (to - from)))

    Canvas {
        id: trackCv
        anchors.fill: parent
        Connections { target: orn; function on_PosChanged()  { trackCv.requestPaint() } }
        Connections { target: orn; function onValueChanged() { trackCv.requestPaint() } }
        onPaint: {
            var ctx = getContext("2d"); ctx.reset()
            var cy = height / 2
            var g = ctx.createLinearGradient(0, cy - 3, 0, cy + 3)
            g.addColorStop(0, orn.anGold3); g.addColorStop(1, orn.anGold2)
            ctx.fillStyle = g; ctx.strokeStyle = orn.anGold1; ctx.lineWidth = 1
            roundRect(ctx, 0, cy - 4, width, 8, 3); ctx.fill(); ctx.stroke()
            ctx.strokeStyle = "rgba(255,255,255,0.25)"
            ctx.beginPath(); ctx.moveTo(2, cy - 3); ctx.lineTo(width - 2, cy - 3); ctx.stroke()
            ctx.strokeStyle = "rgba(0,0,0,0.4)"
            ctx.beginPath(); ctx.moveTo(2, cy + 3); ctx.lineTo(width - 2, cy + 3); ctx.stroke()
            if (orn._pos > 2) {
                var gg = ctx.createLinearGradient(0, cy - 3, 0, cy + 3)
                gg.addColorStop(0, orn.anBurg2); gg.addColorStop(1, orn.anBurg1)
                ctx.fillStyle = gg; ctx.strokeStyle = orn.anGold1; ctx.lineWidth = 1
                roundRect(ctx, 0, cy - 4, orn._pos, 8, 3); ctx.fill(); ctx.stroke()
            }
            if (orn.tickCount > 1) {
                ctx.fillStyle = orn.anGold1; ctx.globalAlpha = 0.5
                for (var i = 0; i < orn.tickCount; i++) {
                    var x = (i / (orn.tickCount - 1)) * width
                    ctx.fillRect(x - 0.5, cy - 7, 1, 14)
                }
                ctx.globalAlpha = 1
            }
        }
        function roundRect(ctx, x, y, w, h, r) {
            r = Math.min(r, h/2, w/2)
            ctx.beginPath()
            ctx.moveTo(x + r, y); ctx.lineTo(x + w - r, y)
            ctx.quadraticCurveTo(x + w, y, x + w, y + r)
            ctx.lineTo(x + w, y + h - r)
            ctx.quadraticCurveTo(x + w, y + h, x + w - r, y + h)
            ctx.lineTo(x + r, y + h)
            ctx.quadraticCurveTo(x, y + h, x, y + h - r)
            ctx.lineTo(x, y + r)
            ctx.quadraticCurveTo(x, y, x + r, y)
            ctx.closePath()
        }
    }

    Canvas {
        id: thumbCv
        width: 26; height: 26
        x: Math.max(-1, Math.min(orn.width - width + 1, orn._pos - width/2))
        anchors.verticalCenter: parent.verticalCenter
        Connections { target: orn; function onValueChanged() { thumbCv.requestPaint() } }
        onPaint: {
            var ctx = getContext("2d"); ctx.reset()
            var cx = width/2, cy = height/2
            var g = ctx.createRadialGradient(cx - 4, cy - 4, 1, cx, cy, 12)
            g.addColorStop(0.00, ncde.gilt5); g.addColorStop(0.55, ncde.gilt3); g.addColorStop(1.00, ncde.gilt0)
            ctx.fillStyle = g
            ctx.beginPath(); ctx.arc(cx, cy, 12, 0, Math.PI*2); ctx.fill()
            ctx.strokeStyle = ncde.gilt0; ctx.lineWidth = 1.5; ctx.stroke()
            ctx.strokeStyle = ncde.gilt4; ctx.lineWidth = 1
            ctx.beginPath(); ctx.arc(cx, cy, 13, 0, Math.PI*2); ctx.stroke()
            ctx.fillStyle = ncde.gilt0
            ctx.beginPath(); ctx.arc(cx, cy, 3, 0, Math.PI*2); ctx.fill()
            ctx.strokeStyle = ncde.gilt4; ctx.lineWidth = 0.8
            ctx.beginPath(); ctx.arc(cx, cy, 4, 0, Math.PI*2); ctx.stroke()
        }
    }

    TapHandler {
        onTapped: function(eventPoint) { orn._setFromX(eventPoint.position.x); orn.released() }
    }
    DragHandler {
        id: dragHandler
        target: null
        xAxis.enabled: true; yAxis.enabled: false
        onCentroidChanged: { if (active) orn._setFromX(centroid.position.x) }
        onActiveChanged:   { if (!active) orn.released() }
    }
    WheelHandler {
        onWheel: function(ev) {
            var step = (orn.stepSize > 0) ? orn.stepSize : (orn.to - orn.from) / 50
            var q = orn._quantize(orn.value + (ev.angleDelta.y > 0 ? 1 : -1) * step)
            if (q !== orn.value) { orn.value = q; orn.moved(); orn.released() }
        }
    }
}
