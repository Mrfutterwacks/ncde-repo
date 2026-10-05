// NCDEVellum.qml — optional aged-vellum texture wash for LIGHT mode grounds.
// Paints faint foxing blotches + fibre flecks over a parchment base so light
// NCDE looks *painted* (Concordia), not flat cream. No-op in dark mode.
// Seeded RNG → identical every repaint (no flicker). Place behind content:
//   NCDEVellum { anchors.fill: parent }
import QtQuick 2.15

Item {
    id: vel
    NCDEKit { id: k }
    property real intensity: 1.0          // 0..1 strength of the foxing
    property color base: k.panelBg

    // purely decorative texture wash — no content, keep it out of the AT-SPI tree
    Accessible.ignored: true

    Rectangle { anchors.fill: parent; color: vel.base }

    Canvas {
        anchors.fill: parent; antialiasing: true
        renderStrategy: Canvas.Cooperative; layer.enabled: true
        visible: !k.dark                  // texture only in Concordia-day
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var W = width, H = height;
            if (k.dark || W < 2 || H < 2) return;
            // seeded RNG
            var seed = (Math.round(W) ^ (Math.round(H) << 8)) >>> 0;
            function rng(){ seed = (seed * 1664525 + 1013904223) >>> 0; return seed / 4294967296; }
            // warm radial deepening toward the edges
            var g = ctx.createRadialGradient(W*0.45,H*0.4,Math.min(W,H)*0.1,W*0.5,H*0.5,Math.max(W,H)*0.72);
            g.addColorStop(0, "rgba(255,250,232,0)");
            g.addColorStop(1, "rgba(110,72,28," + (0.12*vel.intensity) + ")");
            ctx.fillStyle = g; ctx.fillRect(0,0,W,H);
            // foxing blotches
            ctx.globalCompositeOperation = "multiply";
            var n = Math.round(8 + (W*H)/90000);
            for (var i=0;i<n;i++){
                var cx=rng()*W, cy=rng()*H, r=12+rng()*44, a=(0.03+rng()*0.06)*vel.intensity;
                var b=ctx.createRadialGradient(cx,cy,0,cx,cy,r);
                b.addColorStop(0,"rgba(120,80,32,"+a+")"); b.addColorStop(1,"rgba(120,80,32,0)");
                ctx.fillStyle=b; ctx.beginPath(); ctx.arc(cx,cy,r,0,2*Math.PI); ctx.fill();
            }
            ctx.globalCompositeOperation = "source-over";
            // fibre flecks
            ctx.globalAlpha = 0.4*vel.intensity;
            var f = Math.round((W*H)/9000);
            for (var j=0;j<f;j++){
                var x=rng()*W, y=rng()*H, len=1+rng()*3, ang=rng()*Math.PI;
                ctx.strokeStyle = rng()>0.5 ? "rgba(120,86,40,0.10)" : "rgba(255,248,228,0.14)";
                ctx.lineWidth=0.5; ctx.beginPath();
                ctx.moveTo(x,y); ctx.lineTo(x+Math.cos(ang)*len, y+Math.sin(ang)*len); ctx.stroke();
            }
            ctx.globalAlpha = 1;
        }
    }
}
