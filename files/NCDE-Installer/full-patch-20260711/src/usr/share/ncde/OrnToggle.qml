// OrnToggle.qml — Art Nouveau on/off toggle
// Gold-knob on ivory track when off, on burgundy track when on.
import QtQuick 2.15

Item {
    id: orn
    width: 60
    height: 26

    readonly property color anGold1:  ncde.gilt0
    readonly property color anGold5:  ncde.gilt4
    readonly property color anBurg1:  ncde.wine2
    readonly property color anBurg2:  ncde.wine4
    readonly property color anIvory3: ncde.surfaceAlt

    property bool checked: false
    signal toggled()

    HoverHandler { id: hov }
    TapHandler {
        onTapped: { orn.checked = !orn.checked; orn.toggled() }
    }

    Canvas {
        id: track
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        Connections { target: orn; function onCheckedChanged() { track.requestPaint() } }
        onPaint: {
            var ctx = getContext("2d"); ctx.reset()
            ctx.beginPath()
            var r = height/2
            ctx.moveTo(r, 0); ctx.lineTo(width - r, 0)
            ctx.quadraticCurveTo(width, 0, width, r)
            ctx.lineTo(width, height - r)
            ctx.quadraticCurveTo(width, height, width - r, height)
            ctx.lineTo(r, height)
            ctx.quadraticCurveTo(0, height, 0, height - r)
            ctx.lineTo(0, r)
            ctx.quadraticCurveTo(0, 0, r, 0)
            ctx.closePath()
            if (orn.checked) {
                var g = ctx.createLinearGradient(0, 0, 0, height)
                g.addColorStop(0, orn.anBurg2); g.addColorStop(1, orn.anBurg1)
                ctx.fillStyle = g
            } else {
                ctx.fillStyle = orn.anIvory3
            }
            ctx.fill()
            ctx.strokeStyle = orn.anGold1; ctx.lineWidth = 2; ctx.stroke()
            ctx.strokeStyle = "rgba(0,0,0,0.25)"; ctx.lineWidth = 1
            ctx.beginPath(); ctx.moveTo(4, 2); ctx.lineTo(width - 4, 2); ctx.stroke()
        }
    }

    Canvas {
        id: knob
        renderStrategy: Canvas.Cooperative
        width: parent.height - 4
        height: parent.height - 4
        anchors.verticalCenter: parent.verticalCenter
        x: orn.checked ? (orn.width - width - 2) : 2
        Behavior on x { NumberAnimation { duration: 180; easing.type: Easing.OutCubic } }
        onPaint: {
            var ctx = getContext("2d"); ctx.reset()
            var cx = width/2, cy = height/2
            var g = ctx.createRadialGradient(cx - 3, cy - 3, 0.5, cx, cy, cx)
            g.addColorStop(0.00, ncde.gilt5); g.addColorStop(0.55, ncde.gilt3); g.addColorStop(1.00, ncde.gilt0)
            ctx.fillStyle = g
            ctx.beginPath(); ctx.arc(cx, cy, cx - 1, 0, Math.PI*2); ctx.fill()
            ctx.strokeStyle = orn.anGold1; ctx.lineWidth = 1.4; ctx.stroke()
            ctx.fillStyle = "rgba(246,227,176,0.5)"
            ctx.beginPath(); ctx.arc(cx - 2, cy - 2, 2, 0, Math.PI*2); ctx.fill()
        }
    }
}
