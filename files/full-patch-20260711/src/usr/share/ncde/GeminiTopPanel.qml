// GeminiTopPanel.qml — exact recreation of Gemini_Generated_Image_6t52sg6t52sg6t52.jpeg top bar.
// Reference: /home/stephen/Downloads/Gemini_Generated_Image_6t52sg6t52sg6t52.jpeg
// Live differs: /usr/share/ncde/TopPanel.qml:64-67 is a 28px floating pill
// (6px side/top margins, intellihide slide) with NCDEGlassSurface aero blur +
// NCDEPanelBezel 3px brass ring + NCDEPowerRibbon chevrons.
// Gemini target: full-bleed dark bar (~32px), near-black ground, serif ivory
// menus left (Applications/File/Edit/Windows/Help), center swallowtail clock
// cartouche with filigree wings, gilt tray right. No glass blur, no pill gap.
// Single Canvas painter: ground + top gilt hairline + bottom came + wing volutes.
import QtQuick 2.15

Item {
    id: top
    height: 32
    property string clockText: "2:56"
    property string dateText: "Sep 29"

    Canvas {
        id: bg
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        onPaint: {
            var ctx = getContext("2d"), W = width, H = height
            ctx.reset()
            // ground: Belle Époque night, subtle vertical falloff
            var g = ctx.createLinearGradient(0, 0, 0, H)
            g.addColorStop(0, "#1a120a"); g.addColorStop(0.5, "#0c0907"); g.addColorStop(1, "#060403")
            ctx.fillStyle = g; ctx.fillRect(0, 0, W, H)
            // top gilt hairline
            ctx.fillStyle = "#e9c97c"; ctx.fillRect(0, 0, W, 1)
            ctx.fillStyle = "rgba(233,201,124,0.25)"; ctx.fillRect(0, 1, W, 1)
            // bottom came (dark lead + brass lip)
            ctx.fillStyle = "#2a1e0e"; ctx.fillRect(0, H - 3, W, 3)
            ctx.fillStyle = "#8a5a20"; ctx.fillRect(0, H - 4, W, 1)
            // center cartouche plate
            var cw = 210, cx = (W - cw) / 2
            ctx.fillStyle = "#14100a"
            ctx.beginPath()
            ctx.moveTo(cx + 12, 4); ctx.lineTo(cx + cw - 12, 4)
            ctx.quadraticCurveTo(cx + cw, 4, cx + cw, H / 2)
            ctx.quadraticCurveTo(cx + cw, H - 4, cx + cw - 12, H - 4)
            ctx.lineTo(cx + 12, H - 4)
            ctx.quadraticCurveTo(cx, H - 4, cx, H / 2)
            ctx.quadraticCurveTo(cx, 4, cx + 12, 4)
            ctx.fill()
            ctx.strokeStyle = "#b07a30"; ctx.lineWidth = 1; ctx.stroke()
            // filigree wings: mirrored volute spirals (approximation of Gemini scroll)
            ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 1.2
            for (var s = -1; s <= 1; s += 2) {
                for (var i = 0; i < 3; i++) {
                    var bx = W / 2 + s * (cw / 2 + 14 + i * 16)
                    ctx.beginPath()
                    ctx.arc(bx, H / 2, 7 - i, 0, Math.PI * 1.7)
                    ctx.stroke()
                }
            }
        }
    }
    Row {
        anchors.left: parent.left; anchors.leftMargin: 12
        anchors.verticalCenter: parent.verticalCenter; spacing: 14
        Repeater {
            model: ["Applications", "File", "Edit", "Windows", "Help"]
            Text { text: modelData; color: "#e8dcc8"; font.family: "Georgia"; font.pixelSize: 13 }
        }
    }
    Row {
        anchors.centerIn: parent; spacing: 8
        Text { text: top.clockText; color: "#f6e3b0"; font.family: "Georgia"; font.bold: true; font.pixelSize: 15 }
        Rectangle { width: 7; height: 7; radius: 3.5; color: "#e8dcc8"; anchors.verticalCenter: parent.verticalCenter }
        Text { text: top.dateText; color: "#a89a7c"; font.family: "Georgia"; font.pixelSize: 12 }
    }
}
