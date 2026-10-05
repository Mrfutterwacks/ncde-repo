// mucha-icons-apps-comm.js — mail, chat, voice/video communication.
.pragma library
.import "mucha-icons-core.js" as C

// THUNDERBIRD — nesting bird with twin-leaf perch
function drawThunderbird(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5;
    // bird body
    ctx.save();
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.20, s * 0.56);
    ctx.bezierCurveTo(cx - s * 0.22, s * 0.36, cx + s * 0.16, s * 0.32, cx + s * 0.22, s * 0.48);
    ctx.bezierCurveTo(cx + s * 0.18, s * 0.62, cx - s * 0.10, s * 0.66, cx - s * 0.20, s * 0.56);
    ctx.closePath();
    ctx.fill();
    // wing
    ctx.fillStyle = C.PALETTE.teal;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.10, s * 0.40);
    ctx.quadraticCurveTo(cx + s * 0.04, s * 0.34, cx + s * 0.10, s * 0.54);
    ctx.quadraticCurveTo(cx, s * 0.50, cx - s * 0.10, s * 0.40);
    ctx.closePath();
    ctx.fill();
    // beak
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.22, s * 0.46);
    ctx.lineTo(cx + s * 0.30, s * 0.48);
    ctx.lineTo(cx + s * 0.22, s * 0.50);
    ctx.closePath();
    ctx.fill();
    // eye
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(cx + s * 0.14, s * 0.44, s * 0.012, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
    // perch branch with leaves
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(s * 0.18, s * 0.70, s * 0.64, s * 0.020);
    C.leafBead(ctx, s * 0.30, s * 0.74, s * 0.10, 0.7, C.PALETTE.sageDeep);
    C.leafBead(ctx, s * 0.70, s * 0.74, s * 0.10, 2.4, C.PALETTE.sageDeep);
}

// EVOLUTION — golden spiral
function drawEvolution(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.024;
    ctx.lineCap = "round";
    ctx.beginPath();
    for (var t = 0; t < Math.PI * 5; t += 0.05) {
        var r = s * 0.005 + t * s * 0.022;
        var x = Math.cos(t) * r, y = Math.sin(t) * r;
        if (t === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.stroke();
    ctx.restore();
    // envelope tab tucked in
    ctx.save();
    ctx.translate(s * 0.68, s * 0.32);
    ctx.rotate(0.3);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(-s * 0.10, -s * 0.06, s * 0.20, s * 0.14);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(-s * 0.10, -s * 0.06, s * 0.20, s * 0.14);
    ctx.beginPath();
    ctx.moveTo(-s * 0.10, -s * 0.06);
    ctx.lineTo(0, s * 0.02);
    ctx.lineTo(s * 0.10, -s * 0.06);
    ctx.stroke();
    ctx.restore();
}

// GEARY — speech ornament with G
function drawGeary(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // speech bubble
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.18, s * 0.22, s * 0.62, s * 0.42, s * 0.10);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // tail
    ctx.beginPath();
    ctx.moveTo(s * 0.32, s * 0.62);
    ctx.lineTo(s * 0.28, s * 0.78);
    ctx.lineTo(s * 0.42, s * 0.62);
    ctx.closePath();
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // G initial
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.22) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("G", s * 0.50, s * 0.42);
}

// KMAIL — wax seal envelope
function drawKMail(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // envelope
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.14, s * 0.30, s * 0.72, s * 0.46);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.strokeRect(s * 0.14, s * 0.30, s * 0.72, s * 0.46);
    // V flap
    ctx.beginPath();
    ctx.moveTo(s * 0.14, s * 0.30);
    ctx.lineTo(s * 0.50, s * 0.58);
    ctx.lineTo(s * 0.86, s * 0.30);
    ctx.stroke();
    // wax seal
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.58, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // seal mark (star)
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("✶", s * 0.50, s * 0.59);
}

// CLAWS MAIL — claw + envelope
function drawClaws(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // envelope behind
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.18, s * 0.36, s * 0.64, s * 0.36);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.18, s * 0.36, s * 0.64, s * 0.36);
    // claw (3 talons)
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.fillStyle = "#3b3a30";
    for (var i = -1; i <= 1; i++) {
        ctx.save();
        ctx.rotate(i * 0.35);
        ctx.beginPath();
        ctx.moveTo(-s * 0.02, -s * 0.04);
        ctx.lineTo(s * 0.02, -s * 0.04);
        ctx.lineTo(s * 0.04, s * 0.20);
        ctx.lineTo(0, s * 0.32);
        ctx.lineTo(-s * 0.04, s * 0.20);
        ctx.closePath();
        ctx.fill();
        // gilt tip
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.beginPath();
        ctx.moveTo(-s * 0.020, s * 0.20);
        ctx.lineTo(s * 0.020, s * 0.20);
        ctx.lineTo(0, s * 0.32);
        ctx.closePath();
        ctx.fill();
        ctx.fillStyle = "#3b3a30";
        ctx.restore();
    }
    ctx.restore();
}

// SLACK — quadrant of rounded bars (no logo — ornamental version)
function drawSlack(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    var cols = [C.PALETTE.terra, C.PALETTE.sageDeep, C.PALETTE.indigoDeep, accent || C.PALETTE.gold];
    // 4 grouped bars
    function bar(x, y, w, h, col) {
        ctx.fillStyle = col;
        C.roundRectPath(ctx, x, y, w, h, Math.min(w, h) / 2);
        ctx.fill();
    }
    bar(cx - s * 0.22, cy - s * 0.04, s * 0.20, s * 0.06, cols[0]);
    bar(cx - s * 0.16, cy - s * 0.22, s * 0.06, s * 0.20, cols[1]);
    bar(cx + s * 0.02, cy + s * 0.16, s * 0.20, s * 0.06, cols[2]);
    bar(cx + s * 0.10, cy - s * 0.22, s * 0.06, s * 0.20, cols[3]);
    // hash centre
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.10) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("#", cx, cy);
}

// DISCORD — masked figure (ornament)
function drawDiscord(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.52;
    // hood
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.22, cy - s * 0.04);
    ctx.bezierCurveTo(cx - s * 0.22, cy - s * 0.30, cx + s * 0.22, cy - s * 0.30, cx + s * 0.22, cy - s * 0.04);
    ctx.bezierCurveTo(cx + s * 0.24, cy + s * 0.20, cx - s * 0.24, cy + s * 0.20, cx - s * 0.22, cy - s * 0.04);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // mask plate
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.ellipse(cx, cy - s * 0.02, s * 0.16, s * 0.10, 0, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    // eyeholes
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(cx - s * 0.10, cy - s * 0.04, s * 0.04, s * 0.020);
    ctx.fillRect(cx + s * 0.06, cy - s * 0.04, s * 0.04, s * 0.020);
    // gold mouth bar
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(cx - s * 0.04, cy + s * 0.04, s * 0.08, s * 0.012);
}

// TELEGRAM — paper airplane
function drawTelegram(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // plane body
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.18, s * 0.48);
    ctx.lineTo(s * 0.82, s * 0.20);
    ctx.lineTo(s * 0.68, s * 0.76);
    ctx.lineTo(s * 0.50, s * 0.60);
    ctx.closePath();
    ctx.fill();
    // fold (lighter)
    ctx.fillStyle = "#9bbcbc";
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.60);
    ctx.lineTo(s * 0.82, s * 0.20);
    ctx.lineTo(s * 0.68, s * 0.76);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.beginPath();
    ctx.moveTo(s * 0.18, s * 0.48);
    ctx.lineTo(s * 0.82, s * 0.20);
    ctx.lineTo(s * 0.68, s * 0.76);
    ctx.lineTo(s * 0.50, s * 0.60);
    ctx.lineTo(s * 0.18, s * 0.48);
    ctx.moveTo(s * 0.50, s * 0.60);
    ctx.lineTo(s * 0.82, s * 0.20);
    ctx.stroke();
    // trail dots
    ctx.fillStyle = accent || C.PALETTE.gold;
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(s * (0.10 + i * 0.02), s * (0.62 + i * 0.04), s * 0.018, 0, Math.PI * 2);
        ctx.fill();
    }
}

// SIGNAL — semaphore flag
function drawSignal(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // pole
    ctx.fillStyle = "#3b3a30";
    ctx.fillRect(s * 0.34, s * 0.18, s * 0.030, s * 0.64);
    // flag billowing
    ctx.fillStyle = accent || C.PALETTE.terra;
    ctx.beginPath();
    ctx.moveTo(s * 0.37, s * 0.22);
    ctx.lineTo(s * 0.80, s * 0.30);
    ctx.lineTo(s * 0.78, s * 0.50);
    ctx.lineTo(s * 0.37, s * 0.46);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // signal arc
    ctx.save();
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.014;
    ctx.lineCap = "round";
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(s * 0.32, s * 0.74, s * (0.10 + i * 0.06), -Math.PI * 0.3, Math.PI * 0.3);
        ctx.stroke();
    }
    ctx.restore();
}

// WHATSAPP — bubble with phone
function drawWhatsApp(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // bubble
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.fill();
    // tail
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.20, cy + s * 0.22);
    ctx.lineTo(cx - s * 0.32, cy + s * 0.30);
    ctx.lineTo(cx - s * 0.12, cy + s * 0.30);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // phone handset
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-0.4);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(-s * 0.14, -s * 0.10);
    ctx.bezierCurveTo(-s * 0.10, -s * 0.18, s * 0.10, -s * 0.18, s * 0.14, -s * 0.10);
    ctx.lineTo(s * 0.10, -s * 0.04);
    ctx.bezierCurveTo(s * 0.08, -s * 0.06, -s * 0.08, -s * 0.06, -s * 0.10, -s * 0.04);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

// ELEMENT (Matrix) — rune diamond
function drawElement(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // diamond
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(Math.PI / 4);
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fillRect(-s * 0.18, -s * 0.18, s * 0.36, s * 0.36);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.strokeRect(-s * 0.18, -s * 0.18, s * 0.36, s * 0.36);
    ctx.restore();
    // 4 corner dots
    [[-1,-1],[1,-1],[-1,1],[1,1]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(cx + p[0] * s * 0.22, cy + p[1] * s * 0.22, s * 0.026, 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.goldHi;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    });
    // M rune in centre
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.16) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("M", cx, cy);
}

// HEXCHAT / IRSSI / WEECHAT — IRC-style channel banner
function drawHexChat(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // banner
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.14, s * 0.18, s * 0.72, s * 0.10);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.08) + "px monospace";
    ctx.textBaseline = "middle";
    ctx.fillText("#linux", s * 0.20, s * 0.23);
    // chat lines (varied users)
    var ucols = [accent || C.PALETTE.gold, C.PALETTE.terra, C.PALETTE.sageDeep, C.PALETTE.rose];
    for (var i = 0; i < 5; i++) {
        ctx.fillStyle = ucols[i % ucols.length];
        ctx.font = "700 " + Math.round(s * 0.06) + "px monospace";
        ctx.fillText("<usr>", s * 0.16, s * (0.36 + i * 0.10));
        ctx.fillStyle = "rgba(58,43,24,0.75)";
        ctx.fillRect(s * 0.36, s * (0.36 + i * 0.10) - s * 0.006, s * (0.42 - (i % 2) * 0.08), s * 0.012);
    }
}

// PIDGIN — dove
function drawPidgin(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // dove body
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.22, cy + s * 0.05);
    ctx.bezierCurveTo(cx - s * 0.22, cy - s * 0.10, cx + s * 0.10, cy - s * 0.18, cx + s * 0.20, cy - s * 0.06);
    ctx.bezierCurveTo(cx + s * 0.16, cy + s * 0.08, cx, cy + s * 0.14, cx - s * 0.22, cy + s * 0.05);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // wing
    ctx.fillStyle = "#dccfa9";
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.10, cy);
    ctx.quadraticCurveTo(cx + s * 0.02, cy - s * 0.10, cx + s * 0.16, cy - s * 0.02);
    ctx.quadraticCurveTo(cx + s * 0.04, cy + s * 0.06, cx - s * 0.10, cy);
    ctx.closePath();
    ctx.fill();
    // head feather
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.16, cy - s * 0.12);
    ctx.lineTo(cx + s * 0.22, cy - s * 0.18);
    ctx.lineTo(cx + s * 0.20, cy - s * 0.06);
    ctx.closePath();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    // beak & eye
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.20, cy - s * 0.04);
    ctx.lineTo(cx + s * 0.28, cy - s * 0.02);
    ctx.lineTo(cx + s * 0.20, cy);
    ctx.closePath();
    ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(cx + s * 0.14, cy - s * 0.06, s * 0.010, 0, Math.PI * 2);
    ctx.fill();
    // olive branch in beak
    ctx.fillStyle = C.PALETTE.sageDeep;
    C.leafBead(ctx, cx + s * 0.32, cy - s * 0.02, s * 0.08, 0, C.PALETTE.sageDeep);
    C.leafBead(ctx, cx + s * 0.30, cy + s * 0.04, s * 0.06, 0.5, C.PALETTE.sageDeep);
}

// EMPATHY — cluster of speech bubbles
function drawEmpathy(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // bubble 1
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.12, s * 0.22, s * 0.46, s * 0.30, s * 0.08);
    ctx.fill();
    // bubble 2
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.40, s * 0.48, s * 0.46, s * 0.30, s * 0.08);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    C.roundRectPath(ctx, s * 0.12, s * 0.22, s * 0.46, s * 0.30, s * 0.08);
    ctx.stroke();
    C.roundRectPath(ctx, s * 0.40, s * 0.48, s * 0.46, s * 0.30, s * 0.08);
    ctx.stroke();
    // text dots inside each
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    for (var i = 0; i < 3; i++) {
        ctx.beginPath(); ctx.arc(s * (0.22 + i * 0.08), s * 0.36, s * 0.016, 0, Math.PI * 2); ctx.fill();
        ctx.beginPath(); ctx.arc(s * (0.50 + i * 0.08), s * 0.62, s * 0.016, 0, Math.PI * 2); ctx.fill();
    }
}

// ZOOM — camera lens
function drawZoom(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // video tile
    ctx.fillStyle = C.PALETTE.indigoDeep;
    C.roundRectPath(ctx, s * 0.20, s * 0.32, s * 0.50, s * 0.36, s * 0.04);
    ctx.fill();
    // camera triangle to the right
    ctx.beginPath();
    ctx.moveTo(s * 0.70, s * 0.40);
    ctx.lineTo(s * 0.82, s * 0.34);
    ctx.lineTo(s * 0.82, s * 0.66);
    ctx.lineTo(s * 0.70, s * 0.60);
    ctx.closePath();
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
    ctx.stroke();
    // play / camera face
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.36, s * 0.42);
    ctx.lineTo(s * 0.58, s * 0.50);
    ctx.lineTo(s * 0.36, s * 0.58);
    ctx.closePath();
    ctx.fill();
}

// TEAMS — connected nodes ornament
function drawTeams(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // 3 connected silhouettes
    var nodes = [[0.28, 0.40], [0.72, 0.40], [0.50, 0.74]];
    // connections
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    ctx.moveTo(s * nodes[0][0], s * nodes[0][1]);
    ctx.lineTo(s * nodes[1][0], s * nodes[1][1]);
    ctx.lineTo(s * nodes[2][0], s * nodes[2][1]);
    ctx.lineTo(s * nodes[0][0], s * nodes[0][1]);
    ctx.stroke();
    // person silhouettes
    for (var i = 0; i < 3; i++) {
        var x = s * nodes[i][0], y = s * nodes[i][1];
        ctx.fillStyle = [C.PALETTE.indigoDeep, C.PALETTE.terra, C.PALETTE.sageDeep][i];
        ctx.beginPath();
        ctx.arc(x, y - s * 0.04, s * 0.05, 0, Math.PI * 2);
        ctx.fill();
        ctx.beginPath();
        ctx.moveTo(x - s * 0.08, y + s * 0.10);
        ctx.bezierCurveTo(x - s * 0.06, y + s * 0.02, x + s * 0.06, y + s * 0.02, x + s * 0.08, y + s * 0.10);
        ctx.closePath();
        ctx.fill();
    }
}

// JAMI — sound wave hub
function drawJami(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // central J
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.font = "700 " + Math.round(s * 0.36) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("J", cx, cy);
    // signal arcs
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.014;
    ctx.lineCap = "round";
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(cx, cy, s * (0.20 + i * 0.06), -Math.PI * 0.7, -Math.PI * 0.3);
        ctx.stroke();
        ctx.beginPath();
        ctx.arc(cx, cy, s * (0.20 + i * 0.06), Math.PI * 0.3, Math.PI * 0.7);
        ctx.stroke();
    }
}

// MUMBLE — microphone
function drawMumble(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // mic head
    ctx.fillStyle = C.PALETTE.ink;
    C.roundRectPath(ctx, cx - s * 0.10, cy - s * 0.26, s * 0.20, s * 0.30, s * 0.10);
    ctx.fill();
    // grille lines
    ctx.strokeStyle = "rgba(230,199,133,0.55)";
    ctx.lineWidth = s * 0.005;
    for (var i = 0; i < 4; i++) {
        ctx.beginPath();
        ctx.moveTo(cx - s * 0.08, cy - s * 0.20 + i * s * 0.06);
        ctx.lineTo(cx + s * 0.08, cy - s * 0.20 + i * s * 0.06);
        ctx.stroke();
    }
    // arch holder
    ctx.beginPath();
    ctx.arc(cx, cy + s * 0.06, s * 0.16, 0, Math.PI);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    // stand
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(cx - s * 0.006, cy + s * 0.10, s * 0.012, s * 0.16);
    ctx.fillRect(cx - s * 0.12, cy + s * 0.26, s * 0.24, s * 0.02);
}

// TEAMSPEAK — headset
function drawTeamSpeak(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // headband
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, Math.PI, 0);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.030);
    ctx.stroke();
    // cups
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(cx - s * 0.32, cy - s * 0.04, s * 0.10, s * 0.20);
    ctx.fillRect(cx + s * 0.22, cy - s * 0.04, s * 0.10, s * 0.20);
    // boom mic
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.22, cy + s * 0.10);
    ctx.bezierCurveTo(cx - s * 0.10, cy + s * 0.26, cx + s * 0.06, cy + s * 0.26, cx + s * 0.10, cy + s * 0.16);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(cx + s * 0.10, cy + s * 0.16, s * 0.030, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
}

// SKYPE — cloud with phone receiver
function drawSkype(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // bubble
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    // S handset
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-Math.PI / 6);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(-s * 0.16, -s * 0.04);
    ctx.bezierCurveTo(-s * 0.16, -s * 0.20, s * 0.16, -s * 0.20, s * 0.16, -s * 0.04);
    ctx.bezierCurveTo(s * 0.16, s * 0.04, s * 0.08, s * 0.04, s * 0.04, s * 0.04);
    ctx.bezierCurveTo(s * 0.06, s * 0.12, -s * 0.02, s * 0.12, -s * 0.06, s * 0.04);
    ctx.bezierCurveTo(-s * 0.10, s * 0.04, -s * 0.16, s * 0.04, -s * 0.16, -s * 0.04);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

// GENERIC MAIL — envelope
function drawGenericMail(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.14, s * 0.30, s * 0.72, s * 0.46);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.strokeRect(s * 0.14, s * 0.30, s * 0.72, s * 0.46);
    ctx.beginPath();
    ctx.moveTo(s * 0.14, s * 0.30);
    ctx.lineTo(s * 0.50, s * 0.58);
    ctx.lineTo(s * 0.86, s * 0.30);
    ctx.stroke();
    // gilt rim
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.14, s * 0.74, s * 0.72, s * 0.02);
}

// GENERIC CHAT — bubble with dots
function drawGenericChat(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.16, s * 0.26, s * 0.66, s * 0.34, s * 0.10);
    ctx.fill();
    ctx.beginPath();
    ctx.moveTo(s * 0.32, s * 0.60);
    ctx.lineTo(s * 0.26, s * 0.76);
    ctx.lineTo(s * 0.42, s * 0.60);
    ctx.closePath();
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(s * (0.34 + i * 0.10), s * 0.43, s * 0.020, 0, Math.PI * 2);
        ctx.fill();
    }
}
