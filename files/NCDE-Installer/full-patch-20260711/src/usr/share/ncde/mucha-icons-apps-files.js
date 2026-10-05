// mucha-icons-apps-files.js — file managers, each metaphor distinct.
.pragma library
.import "mucha-icons-core.js" as C

// Helper — folder body with gilded fillet
function _folder(ctx, s, col1, col2) {
    ctx.fillStyle = col1;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    ctx.fillStyle = col2;
    ctx.beginPath();
    ctx.moveTo(s * 0.14, s * 0.30);
    ctx.lineTo(s * 0.40, s * 0.30);
    ctx.lineTo(s * 0.46, s * 0.22);
    ctx.lineTo(s * 0.66, s * 0.22);
    ctx.lineTo(s * 0.72, s * 0.30);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
}

// THUNAR — storm cloud with lightning over a folder
function drawThunar(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _folder(ctx, s, C.PALETTE.indigo, C.PALETTE.indigoDeep);
    // cloud
    ctx.fillStyle = "#e1e3eb";
    ctx.beginPath();
    ctx.arc(s * 0.35, s * 0.46, s * 0.08, 0, Math.PI * 2);
    ctx.arc(s * 0.48, s * 0.40, s * 0.10, 0, Math.PI * 2);
    ctx.arc(s * 0.62, s * 0.46, s * 0.09, 0, Math.PI * 2);
    ctx.arc(s * 0.50, s * 0.52, s * 0.10, 0, Math.PI * 2);
    ctx.fill();
    // bolt
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.48, s * 0.50);
    ctx.lineTo(s * 0.42, s * 0.68);
    ctx.lineTo(s * 0.48, s * 0.68);
    ctx.lineTo(s * 0.44, s * 0.78);
    ctx.lineTo(s * 0.58, s * 0.60);
    ctx.lineTo(s * 0.52, s * 0.60);
    ctx.lineTo(s * 0.56, s * 0.50);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
}

// NAUTILUS — nautilus shell (logarithmic spiral)
function drawNautilus(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.52;
    // outer shell body
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.08, cy - s * 0.10, s * 0.02, s * 0.30,
        [[0, "#f4e3c9"], [1, "#b58a52"]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // chambers (spiral arcs)
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 6; i++) {
        var r = s * (0.24 - i * 0.034);
        ctx.beginPath();
        ctx.arc(0, 0, r, Math.PI * (-0.1 + i * 0.08), Math.PI * (1.1 - i * 0.05));
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    }
    // central spiral
    ctx.beginPath();
    ctx.moveTo(0, 0);
    for (var t = 0; t < Math.PI * 3; t += 0.1) {
        var rr = s * 0.012 * t;
        ctx.lineTo(Math.cos(t) * rr, Math.sin(t) * rr);
    }
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
    ctx.stroke();
    ctx.restore();
}

// DOLPHIN — leaping dolphin curve over wave
function drawDolphin(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    // wave
    ctx.save();
    ctx.fillStyle = C.PALETTE.teal;
    ctx.beginPath();
    ctx.moveTo(s * 0.10, s * 0.78);
    ctx.bezierCurveTo(s * 0.30, s * 0.62, s * 0.70, s * 0.90, s * 0.90, s * 0.74);
    ctx.lineTo(s * 0.90, s * 0.92);
    ctx.lineTo(s * 0.10, s * 0.92);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
    // dolphin body
    ctx.save();
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.66);
    ctx.bezierCurveTo(s * 0.30, s * 0.30, s * 0.66, s * 0.20, s * 0.80, s * 0.46);
    ctx.bezierCurveTo(s * 0.70, s * 0.40, s * 0.62, s * 0.42, s * 0.56, s * 0.50);
    ctx.bezierCurveTo(s * 0.46, s * 0.62, s * 0.32, s * 0.68, s * 0.20, s * 0.66);
    ctx.closePath();
    ctx.fill();
    // fin
    ctx.beginPath();
    ctx.moveTo(s * 0.46, s * 0.34);
    ctx.lineTo(s * 0.54, s * 0.20);
    ctx.lineTo(s * 0.60, s * 0.34);
    ctx.closePath();
    ctx.fill();
    // belly highlight
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.58);
    ctx.bezierCurveTo(s * 0.36, s * 0.50, s * 0.50, s * 0.50, s * 0.56, s * 0.56);
    ctx.bezierCurveTo(s * 0.48, s * 0.60, s * 0.38, s * 0.62, s * 0.30, s * 0.58);
    ctx.closePath();
    ctx.fill();
    // eye
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(s * 0.70, s * 0.40, s * 0.014, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
}

// PCMANFM — tablet with rows of file glyphs
function drawPCManFM(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _folder(ctx, s, C.PALETTE.sageDeep, C.PALETTE.sageDark);
    // tab strip
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.20, s * 0.38, s * 0.60, s * 0.10);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.22, s * 0.40, s * 0.10, s * 0.06);
    ctx.fillStyle = "rgba(58,43,24,0.5)";
    ctx.fillRect(s * 0.34, s * 0.40, s * 0.10, s * 0.06);
    ctx.fillRect(s * 0.46, s * 0.40, s * 0.10, s * 0.06);
    // file list rows
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    for (var i = 0; i < 3; i++) {
        ctx.fillRect(s * 0.20, s * 0.52 + i * s * 0.09, s * 0.60, s * 0.06);
    }
    ctx.fillStyle = C.PALETTE.ink;
    for (var j = 0; j < 3; j++) {
        ctx.fillRect(s * 0.30, s * 0.555 + j * s * 0.09, s * 0.20, s * 0.012);
    }
}

// NEMO — Trident over a folder
function drawNemo(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    _folder(ctx, s, C.PALETTE.tealDeep, "#234748");
    // trident
    ctx.save();
    ctx.fillStyle = accent || C.PALETTE.gold;
    var cx = s * 0.5;
    // shaft
    ctx.fillRect(cx - s * 0.012, s * 0.36, s * 0.024, s * 0.40);
    // prongs
    ctx.fillRect(cx - s * 0.20, s * 0.36, s * 0.026, s * 0.16);
    ctx.fillRect(cx + s * 0.18, s * 0.36, s * 0.026, s * 0.16);
    // crossbar
    ctx.fillRect(cx - s * 0.20, s * 0.36, s * 0.40, s * 0.024);
    // tips (3 spear tips)
    [-1, 0, 1].forEach(function(dx) {
        ctx.beginPath();
        ctx.moveTo(cx + dx * s * 0.19 - s * 0.020, s * 0.36);
        ctx.lineTo(cx + dx * s * 0.19 + s * 0.020, s * 0.36);
        ctx.lineTo(cx + dx * s * 0.19, s * 0.28);
        ctx.closePath();
        ctx.fill();
    });
    ctx.restore();
}

// CAJA — ornamental wooden chest
function drawCaja(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // chest body
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(s * 0.18, s * 0.40, s * 0.64, s * 0.40);
    // lid
    ctx.beginPath();
    ctx.moveTo(s * 0.18, s * 0.40);
    ctx.quadraticCurveTo(s * 0.50, s * 0.20, s * 0.82, s * 0.40);
    ctx.lineTo(s * 0.82, s * 0.46);
    ctx.lineTo(s * 0.18, s * 0.46);
    ctx.closePath();
    ctx.fillStyle = "#6a3d18";
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    ctx.strokeRect(s * 0.18, s * 0.40, s * 0.64, s * 0.40);
    // iron bands
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.16, s * 0.52, s * 0.68, s * 0.04);
    ctx.fillRect(s * 0.16, s * 0.70, s * 0.68, s * 0.04);
    // lock
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.fillRect(s * 0.46, s * 0.42, s * 0.08, s * 0.12);
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.50, s * 0.016, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    // corner studs
    [[0.20,0.42],[0.78,0.42],[0.20,0.76],[0.78,0.76]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.020, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.goldHi;
        ctx.fill();
    });
}

// KRUSADER — crusader cross over twin folders
function drawKrusader(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"shield", accent:accent, glow:glow, ornament:false});
    // two folders side by side
    ctx.fillStyle = C.PALETTE.terraDark;
    C.roundRectPath(ctx, s * 0.10, s * 0.48, s * 0.36, s * 0.36, s * 0.03);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.terra;
    C.roundRectPath(ctx, s * 0.54, s * 0.48, s * 0.36, s * 0.36, s * 0.03);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    C.roundRectPath(ctx, s * 0.10, s * 0.48, s * 0.36, s * 0.36, s * 0.03);
    ctx.stroke();
    C.roundRectPath(ctx, s * 0.54, s * 0.48, s * 0.36, s * 0.36, s * 0.03);
    ctx.stroke();
    // cross
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fillRect(s * 0.45, s * 0.12, s * 0.10, s * 0.36);
    ctx.fillRect(s * 0.32, s * 0.22, s * 0.36, s * 0.10);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.45, s * 0.12, s * 0.10, s * 0.36);
    ctx.strokeRect(s * 0.32, s * 0.22, s * 0.36, s * 0.10);
    // chevron arrows between the folders
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.58);
    ctx.lineTo(s * 0.46, s * 0.66);
    ctx.lineTo(s * 0.54, s * 0.66);
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.78);
    ctx.lineTo(s * 0.46, s * 0.70);
    ctx.lineTo(s * 0.54, s * 0.70);
    ctx.closePath();
    ctx.fill();
}

// RANGER — antler-crowned badge
function drawRanger(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.56;
    // badge disc
    C.drawInnerDisc(ctx, s, C.PALETTE.sageDark, 0.26);
    // antlers
    ctx.save();
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineWidth = s * 0.014;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.06, cy - s * 0.22);
    ctx.lineTo(cx - s * 0.14, cy - s * 0.36);
    ctx.lineTo(cx - s * 0.10, cy - s * 0.34);
    ctx.lineTo(cx - s * 0.20, cy - s * 0.42);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.06, cy - s * 0.22);
    ctx.lineTo(cx + s * 0.14, cy - s * 0.36);
    ctx.lineTo(cx + s * 0.10, cy - s * 0.34);
    ctx.lineTo(cx + s * 0.20, cy - s * 0.42);
    ctx.stroke();
    ctx.restore();
    // monogram R
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.22) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("R", cx, cy);
}

// DOUBLE COMMANDER — two side panes
function drawDoubleCmd(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = "#1f1a14";
    ctx.fillRect(s * 0.14, s * 0.22, s * 0.34, s * 0.56);
    ctx.fillStyle = "#2a221a";
    ctx.fillRect(s * 0.52, s * 0.22, s * 0.34, s * 0.56);
    // file rows
    ctx.fillStyle = "rgba(230,199,133,0.6)";
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.17, s * 0.28 + i * s * 0.08, s * 0.18 - (i % 2) * s * 0.04, s * 0.018);
        ctx.fillRect(s * 0.55, s * 0.28 + i * s * 0.08, s * 0.18 - (i % 2) * s * 0.04, s * 0.018);
    }
    // current row highlight
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.14, s * 0.36, s * 0.34, s * 0.06);
    // gap
    C.setStroke(ctx, C.PALETTE.gold, s * 0.012);
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.22); ctx.lineTo(s * 0.50, s * 0.78);
    ctx.stroke();
}

// MIDNIGHT COMMANDER — classic blue ASCII panes
function drawMidnightCmd(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.14, s * 0.22, s * 0.72, s * 0.56);
    // borders ascii-style
    ctx.strokeStyle = "#c0c8e8";
    ctx.lineWidth = s * 0.010;
    ctx.strokeRect(s * 0.16, s * 0.24, s * 0.68, s * 0.52);
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.24); ctx.lineTo(s * 0.50, s * 0.76);
    ctx.stroke();
    // file glyphs
    ctx.fillStyle = "#dde4f4";
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * 0.20, s * 0.30 + i * s * 0.09, s * 0.22, s * 0.014);
        ctx.fillRect(s * 0.54, s * 0.30 + i * s * 0.09, s * 0.22, s * 0.014);
    }
    // selected row
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fillRect(s * 0.18, s * 0.30, s * 0.30, s * 0.018);
}

// GENERIC FILES — simple labelled folder
function drawGenericFiles(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    _folder(ctx, s, C.PALETTE.goldDark, accent || C.PALETTE.gold);
    // shadow inside
    ctx.fillStyle = "rgba(58,43,24,0.25)";
    ctx.fillRect(s * 0.14, s * 0.34, s * 0.72, s * 0.06);
    // tiny file glyphs on folder face
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    for (var i = 0; i < 3; i++) {
        C.roundRectPath(ctx, s * (0.26 + i * 0.16), s * 0.50, s * 0.10, s * 0.16, s * 0.012);
        ctx.fill();
    }
}
