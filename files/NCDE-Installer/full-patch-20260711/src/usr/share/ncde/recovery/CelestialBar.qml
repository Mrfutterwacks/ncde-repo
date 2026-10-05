// ============================================================
//  CelestialBar.qml — animated celestial progress bar (Canvas/paint)
//  A constellation fills toward dawn as the restore proceeds. The
//  onPaint logic is the SAME 2D-context drawing as the HTML concept;
//  only the wrapper is QML. Drive it by setting `progress` (0..100).
// ============================================================
import QtQuick 2.5

Item {
    id: root
    width: 660; height: 120

    // 0..100 — set this from the restore stream (restore-progress)
    property real progress: 0
    property int  nodeCount: 11
    property string phase: ""

    onProgressChanged: cv.requestPaint()

    // gentle idle shimmer so lit stars breathe
    Timer {
        interval: 60; running: root.progress > 0 && root.progress < 100; repeat: true
        onTriggered: cv.requestPaint()
    }

    Canvas {
        id: cv
        anchors.fill: parent
        renderStrategy: Canvas.Threaded
        onPaint: {
            var ctx = getContext("2d");
            var W = width, H = height;
            ctx.clearRect(0, 0, W, H);

            // node positions along the meridian
            var N = root.nodeCount, nodes = [];
            for (var i = 0; i < N; i++)
                nodes.push({ x: 40 + i * (W - 80) / (N - 1), y: H/2 + Math.sin(i * 0.9) * 22 });

            var litX = 40 + (W - 80) * root.progress / 100;

            // baseline meridian
            ctx.strokeStyle = "#6f4f1566"; ctx.lineWidth = 2;
            ctx.beginPath();
            for (i = 0; i < N; i++) i ? ctx.lineTo(nodes[i].x, nodes[i].y) : ctx.moveTo(nodes[i].x, nodes[i].y);
            ctx.stroke();

            // lit (gilt) portion, clipped to progress
            ctx.save();
            ctx.beginPath(); ctx.rect(0, 0, litX, H); ctx.clip();
            var g = ctx.createLinearGradient(40, 0, W - 40, 0);
            g.addColorStop(0, "#6f4f15"); g.addColorStop(0.6, "#b88a2c"); g.addColorStop(1, "#e2c772");
            ctx.strokeStyle = g; ctx.lineWidth = 3; ctx.shadowColor = "#e2c772aa"; ctx.shadowBlur = 10;
            ctx.beginPath();
            for (i = 0; i < N; i++) i ? ctx.lineTo(nodes[i].x, nodes[i].y) : ctx.moveTo(nodes[i].x, nodes[i].y);
            ctx.stroke();
            ctx.restore(); ctx.shadowBlur = 0;

            // star nodes — light up as the fill passes
            for (i = 0; i < N; i++) {
                var lit = nodes[i].x <= litX;
                star(ctx, nodes[i].x, nodes[i].y, lit ? 6.5 : 3.4, lit ? "#fff6d2" : "#6f4f1577", lit);
            }
            // the moon riding the leading edge
            moon(ctx, litX, H/2 - 26, 13);
        }

        function star(ctx, x, y, r, col, glow) {
            ctx.save();
            if (glow) { ctx.shadowColor = "#e2c772"; ctx.shadowBlur = 12; }
            ctx.beginPath();
            for (var i = 0; i < 8; i++) {
                var a = i * Math.PI / 4 - Math.PI / 2;
                var rr = (i % 2 === 0) ? r : r * 0.42;
                var px = x + Math.cos(a) * rr, py = y + Math.sin(a) * rr;
                i ? ctx.lineTo(px, py) : ctx.moveTo(px, py);
            }
            ctx.closePath(); ctx.fillStyle = col; ctx.fill(); ctx.restore();
        }
        function moon(ctx, x, y, r) {
            ctx.save(); ctx.shadowColor = "#e2c772aa"; ctx.shadowBlur = 16;
            ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI * 2); ctx.fillStyle = "#fff6d2"; ctx.fill();
            ctx.restore();
            ctx.beginPath(); ctx.arc(x + r * 0.38, y - r * 0.2, r * 0.92, 0, Math.PI * 2);
            ctx.fillStyle = "#04101a"; ctx.fill();
        }
    }
}
