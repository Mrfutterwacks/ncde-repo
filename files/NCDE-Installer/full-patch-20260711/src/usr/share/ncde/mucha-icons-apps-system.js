// mucha-icons-apps-system.js — system monitors, settings, package managers.
.pragma library
.import "mucha-icons-core.js" as C

// HTOP — three colored CPU bars
function drawHtop(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = "#1d1a14";
    C.roundRectPath(ctx, s * 0.14, s * 0.16, s * 0.72, s * 0.68, s * 0.03);
    ctx.fill();
    var cols = [C.PALETTE.terra, C.PALETTE.sageDeep, accent || C.PALETTE.gold, C.PALETTE.tealDeep];
    var levels = [0.62, 0.84, 0.40, 0.74];
    for (var i = 0; i < 4; i++) {
        var x = s * (0.20 + i * 0.16);
        // label
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.font = "700 " + Math.round(s * 0.05) + "px monospace";
        ctx.fillText(String(i + 1), x, s * 0.74);
        // bar bg
        ctx.fillStyle = "#3b3a30";
        ctx.fillRect(x, s * 0.24, s * 0.10, s * 0.44);
        // fill
        var h = s * 0.44 * levels[i];
        ctx.fillStyle = cols[i];
        ctx.fillRect(x, s * 0.24 + (s * 0.44 - h), s * 0.10, h);
        // tick marks
        for (var j = 0; j < 5; j++) {
            ctx.fillStyle = "rgba(255,235,180,0.4)";
            ctx.fillRect(x, s * (0.24 + j * 0.09), s * 0.10, s * 0.004);
        }
    }
}

// BTOP — graph + radial CPU gauge
function drawBtop(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = "#1d1a14";
    C.roundRectPath(ctx, s * 0.14, s * 0.14, s * 0.72, s * 0.72, s * 0.03);
    ctx.fill();
    // graph line
    ctx.strokeStyle = accent || C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    var amps = [0.6, 0.4, 0.7, 0.5, 0.8, 0.3, 0.6, 0.7, 0.5, 0.7];
    for (var i = 0; i < amps.length; i++) {
        var x = s * (0.18 + i * 0.06);
        var y = s * (0.50 - amps[i] * 0.20);
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.stroke();
    // radial gauge bottom-right
    ctx.save();
    var cx = s * 0.70, cy = s * 0.66;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.14, Math.PI * 0.75, Math.PI * 2.25);
    C.setStroke(ctx, "rgba(255,235,180,0.25)", s * 0.020);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.14, Math.PI * 0.75, Math.PI * 1.65);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.020);
    ctx.stroke();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.08) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("78%", cx, cy);
    ctx.restore();
    // memory bar
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.fillRect(s * 0.18, s * 0.66, s * 0.36, s * 0.06);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.18, s * 0.66, s * 0.22, s * 0.06);
}

// GNOME SYSTEM MONITOR — dashboard gauge
function drawSystemMonitor(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.6;
    // gauge dial
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.28, Math.PI, 0);
    ctx.fillStyle = "#1d1a14";
    ctx.fill();
    // arc color bands
    var bands = [["#5d7861", Math.PI, Math.PI * 0.55],
                 [accent || C.PALETTE.gold, Math.PI * 0.55, Math.PI * 0.22],
                 [C.PALETTE.terraDark, Math.PI * 0.22, 0]];
    bands.forEach(function(b) {
        ctx.beginPath();
        ctx.arc(cx, cy, s * 0.28, b[1], b[2], true);
        C.setStroke(ctx, b[0], s * 0.030);
        ctx.stroke();
    });
    // needle
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(Math.PI * 0.6);
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineWidth = s * 0.014;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.lineTo(-s * 0.24, 0);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(0, 0, s * 0.030, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    ctx.restore();
}

// KSYSGUARD — graph + grid
function drawKSysGuard(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = "#1d1a14";
    ctx.fillRect(s * 0.14, s * 0.18, s * 0.72, s * 0.64);
    // grid
    ctx.strokeStyle = "rgba(184,140,74,0.25)";
    ctx.lineWidth = s * 0.005;
    for (var i = 1; i < 6; i++) {
        ctx.beginPath();
        ctx.moveTo(s * 0.14, s * (0.18 + i * 0.11));
        ctx.lineTo(s * 0.86, s * (0.18 + i * 0.11));
        ctx.stroke();
        ctx.beginPath();
        ctx.moveTo(s * (0.14 + i * 0.12), s * 0.18);
        ctx.lineTo(s * (0.14 + i * 0.12), s * 0.82);
        ctx.stroke();
    }
    // two waveforms
    var data1 = [0.4, 0.6, 0.5, 0.7, 0.55, 0.8, 0.6, 0.7];
    var data2 = [0.2, 0.4, 0.3, 0.45, 0.35, 0.5, 0.4, 0.55];
    function draw(line, col) {
        ctx.strokeStyle = col;
        ctx.lineWidth = s * 0.014;
        ctx.beginPath();
        for (var i = 0; i < line.length; i++) {
            var x = s * (0.16 + i * 0.10);
            var y = s * (0.78 - line[i] * 0.50);
            if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
        }
        ctx.stroke();
    }
    draw(data1, accent || C.PALETTE.goldHi);
    draw(data2, C.PALETTE.sageMist);
}

// STACER — radial CPU/mem gauges side-by-side
function drawStacer(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    function gauge(cx, cy, percent, col) {
        ctx.beginPath();
        ctx.arc(cx, cy, s * 0.12, Math.PI * 0.75, Math.PI * 2.25);
        C.setStroke(ctx, "rgba(58,43,24,0.25)", s * 0.026);
        ctx.stroke();
        ctx.beginPath();
        ctx.arc(cx, cy, s * 0.12, Math.PI * 0.75, Math.PI * 0.75 + Math.PI * 1.5 * percent);
        C.setStroke(ctx, col, s * 0.026);
        ctx.stroke();
        ctx.fillStyle = C.PALETTE.ink;
        ctx.font = "700 " + Math.round(s * 0.08) + "px monospace";
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(Math.round(percent * 100) + "", cx, cy);
    }
    gauge(s * 0.30, s * 0.40, 0.62, accent || C.PALETTE.gold);
    gauge(s * 0.70, s * 0.40, 0.34, C.PALETTE.sageDeep);
    gauge(s * 0.50, s * 0.74, 0.78, C.PALETTE.terra);
}

// PAVUCONTROL — channel slider
function drawPavucontrol(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // 4 sliders
    for (var i = 0; i < 4; i++) {
        var x = s * (0.22 + i * 0.18);
        // track
        ctx.fillStyle = "#3b3a30";
        ctx.fillRect(x - s * 0.006, s * 0.22, s * 0.012, s * 0.56);
        // fill
        var fill = [0.30, 0.60, 0.80, 0.50][i];
        ctx.fillStyle = [C.PALETTE.sageDeep, accent || C.PALETTE.gold, C.PALETTE.terra, C.PALETTE.tealDeep][i];
        ctx.fillRect(x - s * 0.006, s * (0.22 + 0.56 * (1 - fill)), s * 0.012, s * 0.56 * fill);
        // thumb
        ctx.beginPath();
        ctx.arc(x, s * (0.22 + 0.56 * (1 - fill)), s * 0.026, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    }
}

// EASYEFFECTS — equalizer band graph
function drawEasyEffects(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = "#1d1a14";
    ctx.fillRect(s * 0.14, s * 0.20, s * 0.72, s * 0.60);
    // EQ curve
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    var pts = [0.65, 0.50, 0.30, 0.20, 0.30, 0.40, 0.55, 0.60, 0.50];
    for (var i = 0; i < pts.length; i++) {
        var x = s * (0.18 + i * 0.07);
        var y = s * (0.40 + pts[i] * 0.40);
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.stroke();
    // dots
    for (var k = 0; k < pts.length; k++) {
        var x2 = s * (0.18 + k * 0.07);
        var y2 = s * (0.40 + pts[k] * 0.40);
        ctx.beginPath();
        ctx.arc(x2, y2, s * 0.014, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.fill();
    }
    // 0db line
    ctx.strokeStyle = "rgba(184,140,74,0.4)";
    ctx.lineWidth = s * 0.006;
    ctx.beginPath();
    ctx.moveTo(s * 0.14, s * 0.50); ctx.lineTo(s * 0.86, s * 0.50);
    ctx.stroke();
}

// SYNAPTIC — mortar & pestle (package manager)
function drawSynaptic(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // mortar
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.52);
    ctx.lineTo(s * 0.78, s * 0.52);
    ctx.bezierCurveTo(s * 0.74, s * 0.84, s * 0.26, s * 0.84, s * 0.22, s * 0.52);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // rim highlight
    ctx.fillStyle = "rgba(255,235,180,0.25)";
    ctx.fillRect(s * 0.22, s * 0.52, s * 0.56, s * 0.04);
    // pestle
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-0.3);
    ctx.fillStyle = "#9b9bb0";
    ctx.fillRect(-s * 0.020, -s * 0.30, s * 0.040, s * 0.30);
    ctx.beginPath();
    ctx.arc(0, 0, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    ctx.restore();
}

// PAMAC — wrapped parcel
function drawPamac(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // parcel
    ctx.fillStyle = "#a4824a";
    ctx.fillRect(s * 0.18, s * 0.24, s * 0.64, s * 0.56);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.strokeRect(s * 0.18, s * 0.24, s * 0.64, s * 0.56);
    // ribbons
    ctx.fillStyle = accent || C.PALETTE.terra;
    ctx.fillRect(s * 0.45, s * 0.24, s * 0.10, s * 0.56);
    ctx.fillRect(s * 0.18, s * 0.46, s * 0.64, s * 0.10);
    // bow
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.30);
    ctx.bezierCurveTo(s * 0.34, s * 0.16, s * 0.34, s * 0.36, s * 0.50, s * 0.32);
    ctx.bezierCurveTo(s * 0.66, s * 0.36, s * 0.66, s * 0.16, s * 0.50, s * 0.30);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
}

// OCTOPI — octopus tentacle wrapping a box
function drawOctopi(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // box
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(s * 0.28, s * 0.42, s * 0.44, s * 0.38);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.28, s * 0.42, s * 0.44, s * 0.38);
    // tentacle
    ctx.strokeStyle = C.PALETTE.plumDeep;
    ctx.lineWidth = s * 0.024;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.16, s * 0.30);
    ctx.bezierCurveTo(s * 0.34, s * 0.36, s * 0.48, s * 0.20, s * 0.66, s * 0.30);
    ctx.bezierCurveTo(s * 0.84, s * 0.40, s * 0.78, s * 0.60, s * 0.66, s * 0.62);
    ctx.stroke();
    // sucker dots
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    [[0.22,0.28],[0.34,0.30],[0.48,0.22],[0.60,0.24],[0.74,0.34],[0.78,0.50],[0.68,0.58]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.012, 0, Math.PI * 2);
        ctx.fill();
    });
    // eye on top
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.30, s * 0.028, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.30, s * 0.012, 0, Math.PI * 2);
    ctx.fill();
}

// DISCOVER — magnifier over store grid
function drawDiscover(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // 2x2 mini app tiles
    var cols = [C.PALETTE.terra, accent || C.PALETTE.gold, C.PALETTE.sageDeep, C.PALETTE.tealDeep];
    for (var i = 0; i < 4; i++) {
        var x = s * (0.16 + (i % 2) * 0.22);
        var y = s * (0.16 + (i >> 1) * 0.22);
        ctx.fillStyle = cols[i];
        C.roundRectPath(ctx, x, y, s * 0.18, s * 0.18, s * 0.03);
        ctx.fill();
    }
    // magnifier
    ctx.beginPath();
    ctx.arc(s * 0.66, s * 0.62, s * 0.14, 0, Math.PI * 2);
    ctx.fillStyle = "rgba(255,255,255,0.55)";
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.018);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(s * 0.76, s * 0.72);
    ctx.lineTo(s * 0.88, s * 0.86);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.028);
    ctx.stroke();
}

// GNOME SOFTWARE — shopping bag (parcel + handles)
function drawGnomeSoftware(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // bag
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.20, s * 0.34, s * 0.60, s * 0.50);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.strokeRect(s * 0.20, s * 0.34, s * 0.60, s * 0.50);
    // handles
    ctx.beginPath();
    ctx.arc(s * 0.34, s * 0.34, s * 0.06, Math.PI, 0);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(s * 0.66, s * 0.34, s * 0.06, Math.PI, 0);
    ctx.stroke();
    // star
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.font = "700 " + Math.round(s * 0.20) + "px serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("✦", s * 0.50, s * 0.60);
}

// SYSTEM SETTINGS / KDE settings — gear & screwdriver crossed
function drawSystemSettings(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // gear
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    for (var i = 0; i < 16; i++) {
        var a = i / 16 * Math.PI * 2;
        var r = i % 2 ? s * 0.28 : s * 0.22;
        var x = Math.cos(a) * r, y = Math.sin(a) * r;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // hub
    ctx.beginPath();
    ctx.arc(0, 0, s * 0.08, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
    ctx.stroke();
    ctx.restore();
    // screwdriver
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(0.7);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(-s * 0.020, -s * 0.30, s * 0.040, s * 0.16);
    ctx.fillStyle = "#9b9bb0";
    ctx.fillRect(-s * 0.014, -s * 0.14, s * 0.028, s * 0.30);
    ctx.beginPath();
    ctx.moveTo(-s * 0.014, s * 0.16); ctx.lineTo(s * 0.014, s * 0.16); ctx.lineTo(0, s * 0.22);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

// GNOME CONTROL CENTER / Settings — gear
function drawSettings(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = "#3b3a30";
    ctx.beginPath();
    for (var i = 0; i < 16; i++) {
        var a = i / 16 * Math.PI * 2;
        var r = i % 2 ? s * 0.30 : s * 0.24;
        var x = Math.cos(a) * r, y = Math.sin(a) * r;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.arc(0, 0, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(0, 0, s * 0.10, 0, Math.PI * 2);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    ctx.restore();
}

// GPARTED — disk with partition slices
function drawGparted(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    // partitions (pie)
    var parts = [[0.40, C.PALETTE.terra], [0.30, C.PALETTE.sageDeep],
                 [0.20, accent || C.PALETTE.gold], [0.10, C.PALETTE.tealDeep]];
    var a0 = -Math.PI / 2;
    for (var i = 0; i < parts.length; i++) {
        var a1 = a0 + parts[i][0] * Math.PI * 2;
        ctx.beginPath();
        ctx.moveTo(cx, cy);
        ctx.arc(cx, cy, s * 0.28, a0, a1);
        ctx.closePath();
        ctx.fillStyle = parts[i][1];
        ctx.fill();
        a0 = a1;
    }
    // hub
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.06, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
}

// TIMESHIFT — hourglass
function drawTimeshift(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // top & bottom plates
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(cx - s * 0.20, s * 0.18, s * 0.40, s * 0.040);
    ctx.fillRect(cx - s * 0.20, s * 0.78 - s * 0.040, s * 0.40, s * 0.040);
    // glass
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.18, s * 0.22);
    ctx.lineTo(cx + s * 0.18, s * 0.22);
    ctx.lineTo(cx, cy);
    ctx.lineTo(cx + s * 0.18, s * 0.78);
    ctx.lineTo(cx - s * 0.18, s * 0.78);
    ctx.lineTo(cx, cy);
    ctx.closePath();
    ctx.fillStyle = "rgba(184,140,74,0.25)";
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // sand top (partial)
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.14, s * 0.30);
    ctx.lineTo(cx + s * 0.14, s * 0.30);
    ctx.lineTo(cx, cy - s * 0.02);
    ctx.closePath();
    ctx.fill();
    // sand bottom (pile)
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.14, s * 0.74);
    ctx.lineTo(cx + s * 0.14, s * 0.74);
    ctx.quadraticCurveTo(cx, s * 0.60, cx - s * 0.14, s * 0.74);
    ctx.closePath();
    ctx.fill();
    // falling grain
    ctx.fillRect(cx - s * 0.006, s * 0.48, s * 0.012, s * 0.10);
}

// DEJA DUP — mirror (looking-glass)
function drawDejaDup(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // mirror oval
    ctx.beginPath();
    ctx.ellipse(cx, cy - s * 0.04, s * 0.20, s * 0.26, 0, 0, Math.PI * 2);
    ctx.fillStyle = "rgba(160,180,200,0.4)";
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.020);
    ctx.stroke();
    // handle
    ctx.fillStyle = accent || C.PALETTE.goldDark;
    ctx.fillRect(cx - s * 0.020, s * 0.62 - s * 0.020, s * 0.040, s * 0.16);
    ctx.beginPath();
    ctx.arc(cx, s * 0.80, s * 0.030, 0, Math.PI * 2);
    ctx.fill();
    // reflection (sheen lines)
    ctx.strokeStyle = "rgba(255,255,255,0.55)";
    ctx.lineWidth = s * 0.010;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.06, cy - s * 0.18); ctx.lineTo(cx - s * 0.12, cy + s * 0.04);
    ctx.moveTo(cx - s * 0.02, cy - s * 0.20); ctx.lineTo(cx - s * 0.06, cy - s * 0.06);
    ctx.stroke();
}

// BLEACHBIT — broom on disc
function drawBleachbit(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(0.5);
    // handle
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(-s * 0.014, -s * 0.30, s * 0.028, s * 0.36);
    // bristles
    ctx.fillStyle = "#dccfa9";
    ctx.beginPath();
    ctx.moveTo(-s * 0.10, s * 0.06);
    ctx.lineTo(s * 0.10, s * 0.06);
    ctx.lineTo(s * 0.18, s * 0.28);
    ctx.lineTo(-s * 0.18, s * 0.28);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // bristle hatch
    for (var i = -3; i <= 3; i++) {
        ctx.beginPath();
        ctx.moveTo(i * s * 0.025, s * 0.06);
        ctx.lineTo(i * s * 0.045, s * 0.28);
        ctx.stroke();
    }
    ctx.restore();
    // sparkle
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.font = "700 " + Math.round(s * 0.10) + "px serif";
    ctx.fillText("✦", s * 0.30, s * 0.30);
    ctx.fillText("·", s * 0.74, s * 0.36);
}
