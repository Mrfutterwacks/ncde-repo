// EnamelPowerRibbon.qml — NCDEPowerRibbon with d18faebb enamel inlay.
// Reference: /home/stephen/Downloads/d18faebb-d720-469f-be05-6e8f053aef0c.jpeg
// (gold filigree rails top/bottom, steel came, arrow cells: cobalt #1a3a8a
// ground, crimson #8b1e3f core, gold scroll overlay).
// Live differs: /usr/share/ncde/NCDEPowerRibbon.qml _jewel()/_came() paint flat
// wallpaper tones + gilt chevrons, no enamel. This component wraps the live
// ribbon: same Row/segment API, Canvas overpaint adds enamel arrow + filigree
// rails per segment. Drop-in: replace NCDEPowerRibbon with EnamelPowerRibbon,
// keep seed/dir/tones/pad props.
import QtQuick 2.15

Item {
    id: rb
    default property alias content: row.data
    property int dir: 1
    property real pad: 5
    property var tones: []
    property int seed: 0
    implicitWidth: row.width + 40
    height: parent ? parent.height : 28
    // tactile slide: ribbon lengthens/shortens with the menu drawer like
    // sheet metal running in a track (GliaBar drawer, launcherStrip).
    Behavior on implicitWidth { NumberAnimation { duration: 220; easing.type: Easing.OutExpo } }
    Behavior on width { NumberAnimation { duration: 220; easing.type: Easing.OutExpo } }
    Row { id: row; anchors.centerIn: parent; spacing: 2 }
    Canvas {
        // Background must stay BEHIND the ribbon content (Row above).
        // Same z-order as siblings paints in declaration order, and this
        // Canvas is declared after the Row, so without z:-1 its opaque
        // steel/enamel plate covers every icon, menu and tray text.
        z: -1
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        onPaint: {
            var ctx = getContext("2d"), W = width, H = height
            ctx.reset()
            // — tactile ground: brushed steel plate under everything —
            var plate = ctx.createLinearGradient(0, 0, 0, H)
            plate.addColorStop(0, "#3a3f46"); plate.addColorStop(0.18, "#6a7078")
            plate.addColorStop(0.5, "#2a2e34"); plate.addColorStop(1, "#101216")
            ctx.fillStyle = plate; ctx.fillRect(0, 0, W, H)
            // brushed streaks
            ctx.strokeStyle = "rgba(255,255,255,0.05)"; ctx.lineWidth = 1
            for (var b = 4; b < H - 3; b += 3) {
                ctx.beginPath(); ctx.moveTo(6, b); ctx.lineTo(W - 6, b); ctx.stroke()
            }
            // drop shadow under plate (tactile lift)
            ctx.fillStyle = "rgba(0,0,0,0.45)"; ctx.fillRect(2, H - 2, W - 4, 2)
            // filigree rails: beveled gold bands, top lit / bottom shadowed
            for (var e = 0; e < 2; e++) {
                var y = e === 0 ? 2 : H - 5
                var g = ctx.createLinearGradient(0, y, 0, y + 3)
                if (e === 0) { g.addColorStop(0, "#fff6d8"); g.addColorStop(0.5, "#b07a30"); g.addColorStop(1, "#5a3a14") }
                else { g.addColorStop(0, "#5a3a14"); g.addColorStop(0.5, "#8a5a20"); g.addColorStop(1, "#f6e3b0") }
                ctx.fillStyle = g; ctx.fillRect(6, y, W - 12, 3)
                // rail rivets + scroll dots
                for (var x = 12; x < W - 12; x += 18) {
                    ctx.fillStyle = "#2a1e0e"
                    ctx.beginPath(); ctx.arc(x, y + 1.5, 1.6, 0, Math.PI * 2); ctx.fill()
                    ctx.fillStyle = "#f6e3b0"
                    ctx.beginPath(); ctx.arc(x - 0.3, y + 1.2, 0.9, 0, Math.PI * 2); ctx.fill()
                }
            }
            // enamel arrow cell behind content: cobalt ground, crimson core, steel came
            var ax = 4, aw = W - 8, ay = 5, ah = H - 10, ahd = Math.min(10, ah / 2)
            function arrow(cw) {
                ctx.beginPath()
                ctx.moveTo(ax, ay); ctx.lineTo(ax + aw - ahd, ay)
                ctx.lineTo(ax + aw, ay + ah / 2); ctx.lineTo(ax + aw - ahd, ay + ah)
                ctx.lineTo(ax, ay + ah); ctx.lineTo(ax + ahd * 0.6, ay + ah / 2)
                ctx.closePath(); ctx.clip()
                ctx.fillStyle = cw; ctx.fillRect(ax, ay, aw, ah)
            }
            ctx.save(); arrow("#1a3a8a"); ctx.restore()
            // enamel gloss: wet highlight over cobalt (tactile glass over metal)
            var gloss = ctx.createLinearGradient(0, ay, 0, ay + ah)
            gloss.addColorStop(0, "rgba(255,255,255,0.42)"); gloss.addColorStop(0.35, "rgba(255,255,255,0.06)")
            gloss.addColorStop(0.7, "rgba(255,255,255,0)"); gloss.addColorStop(1, "rgba(0,0,0,0.30)")
            ctx.save(); arrow("rgba(0,0,0,0)")
            ctx.fillStyle = gloss; ctx.fillRect(ax, ay, aw, ah)
            ctx.restore()
            // crimson core chevron + gold scroll squiggle (ornate)
            ctx.fillStyle = "#8b1e3f"
            ctx.beginPath()
            ctx.moveTo(ax + aw * 0.35, ay + 3); ctx.lineTo(ax + aw - ahd - 3, ay + ah / 2)
            ctx.lineTo(ax + aw * 0.35, ay + ah - 3); ctx.lineTo(ax + aw * 0.5, ay + ah / 2)
            ctx.closePath(); ctx.fill()
            ctx.strokeStyle = "#e9c97c"; ctx.lineWidth = 1.0
            ctx.beginPath()
            ctx.moveTo(ax + aw * 0.42, ay + ah * 0.3)
            ctx.quadraticCurveTo(ax + aw * 0.6, ay + ah * 0.42, ax + aw * 0.52, ay + ah * 0.62)
            ctx.quadraticCurveTo(ax + aw * 0.47, ay + ah * 0.72, ax + aw * 0.58, ay + ah * 0.7)
            ctx.stroke()
            // steel came: dark outer + bright inner bevel (tactile edge)
            ctx.strokeStyle = "#1a1c20"; ctx.lineWidth = 2.4
            ctx.beginPath()
            ctx.moveTo(ax, ay); ctx.lineTo(ax + aw - ahd, ay)
            ctx.lineTo(ax + aw, ay + ah / 2); ctx.lineTo(ax + aw - ahd, ay + ah)
            ctx.lineTo(ax, ay + ah)
            ctx.stroke()
            ctx.strokeStyle = "#e8ecf2"; ctx.lineWidth = 1.0
            ctx.beginPath()
            ctx.moveTo(ax, ay); ctx.lineTo(ax + aw - ahd, ay)
            ctx.lineTo(ax + aw, ay + ah / 2); ctx.lineTo(ax + aw - ahd, ay + ah)
            ctx.lineTo(ax, ay + ah)
            ctx.stroke()
        }
    }
}
