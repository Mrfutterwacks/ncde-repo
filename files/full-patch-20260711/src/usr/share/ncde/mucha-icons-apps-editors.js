// mucha-icons-apps-editors.js — code editors & IDEs.
// Every icon distinct: each combines a unique metaphor with Mucha framing.

.pragma library
.import "mucha-icons-core.js" as C

// ============================================================================
// VSCODE — chevron-quill embraced by gilded ribbon
// ============================================================================
function drawVSCode(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // ribbon (left-leaning gilt sash)
    ctx.save();
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.26, s * 0.16);
    ctx.lineTo(s * 0.74, s * 0.50);
    ctx.lineTo(s * 0.26, s * 0.84);
    ctx.lineTo(s * 0.18, s * 0.78);
    ctx.lineTo(s * 0.62, s * 0.50);
    ctx.lineTo(s * 0.18, s * 0.22);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    ctx.restore();
    // chevron < > as gilt lines on the ribbon
    ctx.strokeStyle = C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.018;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.48, s * 0.36);
    ctx.lineTo(s * 0.38, s * 0.50);
    ctx.lineTo(s * 0.48, s * 0.64);
    ctx.stroke();
    // central pearl gem
    ctx.beginPath();
    ctx.arc(s * 0.70, s * 0.50, s * 0.035, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.010);
    ctx.stroke();
}

// ============================================================================
// VSCODIUM — same chevron, but in sage with open-loop laurel
// ============================================================================
function drawVSCodium(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // open laurel ring
    for (var i = 0; i < 14; i++) {
        var t = i / 14;
        if (t > 0.35 && t < 0.65) continue;
        var a = t * Math.PI * 2 - Math.PI / 2;
        C.leafBead(ctx, cx + Math.cos(a) * s * 0.34, cy + Math.sin(a) * s * 0.34,
                   s * 0.12, a + Math.PI / 2, C.PALETTE.sageDeep);
    }
    // sage shield body
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.32, s * 0.26);
    ctx.lineTo(s * 0.68, s * 0.50);
    ctx.lineTo(s * 0.32, s * 0.74);
    ctx.lineTo(s * 0.42, s * 0.50);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // gilt chevron
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.018;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.36);
    ctx.lineTo(s * 0.40, s * 0.50);
    ctx.lineTo(s * 0.50, s * 0.64);
    ctx.stroke();
}

// ============================================================================
// CURSOR — arrow cursor with sparkle wand
// ============================================================================
function drawCursor(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // cursor arrow
    ctx.save();
    var g = ctx.createLinearGradient(s * 0.3, s * 0.3, s * 0.7, s * 0.7);
    g.addColorStop(0, C.PALETTE.bgCreamHi);
    g.addColorStop(1, C.PALETTE.goldHi);
    ctx.fillStyle = g;
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.22);
    ctx.lineTo(s * 0.66, s * 0.46);
    ctx.lineTo(s * 0.50, s * 0.50);
    ctx.lineTo(s * 0.58, s * 0.74);
    ctx.lineTo(s * 0.48, s * 0.78);
    ctx.lineTo(s * 0.40, s * 0.54);
    ctx.lineTo(s * 0.30, s * 0.62);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    ctx.restore();
    // sparkle (4-point star + 2 small)
    function spark(x, y, r) {
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.beginPath();
        ctx.moveTo(x, y - r); ctx.lineTo(x + r * 0.3, y - r * 0.3);
        ctx.lineTo(x + r, y); ctx.lineTo(x + r * 0.3, y + r * 0.3);
        ctx.lineTo(x, y + r); ctx.lineTo(x - r * 0.3, y + r * 0.3);
        ctx.lineTo(x - r, y); ctx.lineTo(x - r * 0.3, y - r * 0.3);
        ctx.closePath();
        ctx.fill();
    }
    spark(s * 0.74, s * 0.30, s * 0.08);
    spark(s * 0.20, s * 0.72, s * 0.04);
    spark(s * 0.78, s * 0.68, s * 0.05);
}

// ============================================================================
// ZED — bold Z with radiating diagonal rays
// ============================================================================
function drawZed(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // diagonal rays
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-Math.PI / 6);
    for (var i = -3; i <= 3; i++) {
        ctx.strokeStyle = i === 0 ? accent || C.PALETTE.gold : "rgba(122,90,38,0.4)";
        ctx.lineWidth = s * (i === 0 ? 0.012 : 0.008);
        ctx.beginPath();
        ctx.moveTo(-s * 0.30, i * s * 0.05);
        ctx.lineTo(s * 0.30, i * s * 0.05);
        ctx.stroke();
    }
    ctx.restore();
    // Z body
    ctx.save();
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.26, s * 0.28);
    ctx.lineTo(s * 0.74, s * 0.28);
    ctx.lineTo(s * 0.74, s * 0.38);
    ctx.lineTo(s * 0.42, s * 0.62);
    ctx.lineTo(s * 0.74, s * 0.62);
    ctx.lineTo(s * 0.74, s * 0.72);
    ctx.lineTo(s * 0.26, s * 0.72);
    ctx.lineTo(s * 0.26, s * 0.62);
    ctx.lineTo(s * 0.58, s * 0.38);
    ctx.lineTo(s * 0.26, s * 0.38);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
    ctx.stroke();
    ctx.restore();
}

// ============================================================================
// LAPCE — Romanesque arched portal with text rows
// ============================================================================
function drawLapce(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"arch", accent:accent, glow:glow, ornament:false});
    var cx = s * 0.5;
    // double-arch portal
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.86);
    ctx.lineTo(s * 0.22, s * 0.46);
    ctx.arc(cx, s * 0.46, s * 0.28, Math.PI, 0, false);
    ctx.lineTo(s * 0.78, s * 0.86);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.gold, s * 0.016);
    ctx.stroke();
    // inner arch (lighter teal)
    ctx.fillStyle = C.PALETTE.teal;
    ctx.beginPath();
    ctx.moveTo(s * 0.28, s * 0.82);
    ctx.lineTo(s * 0.28, s * 0.48);
    ctx.arc(cx, s * 0.48, s * 0.22, Math.PI, 0, false);
    ctx.lineTo(s * 0.72, s * 0.82);
    ctx.closePath();
    ctx.fill();
    // text lines
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * 0.34, s * 0.52 + i * s * 0.08, s * (0.32 - i * 0.04), s * 0.016);
    }
    // keystone gem
    ctx.beginPath();
    ctx.arc(cx, s * 0.30, s * 0.045, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
}

// ============================================================================
// HELIX — DNA double-helix
// ============================================================================
function drawHelix(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5;
    ctx.save();
    ctx.strokeStyle = C.PALETTE.terraDark;
    ctx.lineWidth = s * 0.024;
    ctx.lineCap = "round";
    // left strand
    ctx.beginPath();
    for (var y = 0.18; y <= 0.82; y += 0.02) {
        var x = cx + Math.sin(y * Math.PI * 4) * s * 0.14;
        if (y === 0.18) ctx.moveTo(x, s * y); else ctx.lineTo(x, s * y);
    }
    ctx.stroke();
    // right strand
    ctx.strokeStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    for (var y2 = 0.18; y2 <= 0.82; y2 += 0.02) {
        var x2 = cx - Math.sin(y2 * Math.PI * 4) * s * 0.14;
        if (y2 === 0.18) ctx.moveTo(x2, s * y2); else ctx.lineTo(x2, s * y2);
    }
    ctx.stroke();
    ctx.restore();
    // rungs (5)
    for (var i = 0; i < 5; i++) {
        var yy = 0.24 + i * 0.13;
        var x1 = cx + Math.sin(yy * Math.PI * 4) * s * 0.14;
        var x2 = cx - Math.sin(yy * Math.PI * 4) * s * 0.14;
        ctx.beginPath();
        ctx.moveTo(x1, s * yy);
        ctx.lineTo(x2, s * yy);
        C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
        ctx.stroke();
        ctx.beginPath();
        ctx.arc(x1, s * yy, s * 0.018, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.goldHi;
        ctx.fill();
        ctx.beginPath();
        ctx.arc(x2, s * yy, s * 0.018, 0, Math.PI * 2);
        ctx.fill();
    }
}

// ============================================================================
// NEOVIM — twin mountain peaks (V) with a rising sun behind
// ============================================================================
function drawNeovim(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // sun
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.46, s * 0.16, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, s * 0.5, s * 0.46, s * 0.02, s * 0.16,
        [[0, "#f6dca0"], [1, accent || C.PALETTE.gold]]);
    ctx.fill();
    // peaks (V)
    ctx.fillStyle = C.PALETTE.sageDark;
    ctx.beginPath();
    ctx.moveTo(s * 0.16, s * 0.78);
    ctx.lineTo(s * 0.36, s * 0.36);
    ctx.lineTo(s * 0.50, s * 0.62);
    ctx.lineTo(s * 0.50, s * 0.78);
    ctx.closePath();
    ctx.fill();
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.78);
    ctx.lineTo(s * 0.50, s * 0.62);
    ctx.lineTo(s * 0.66, s * 0.40);
    ctx.lineTo(s * 0.84, s * 0.78);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.beginPath();
    ctx.moveTo(s * 0.16, s * 0.78);
    ctx.lineTo(s * 0.36, s * 0.36);
    ctx.lineTo(s * 0.50, s * 0.62);
    ctx.lineTo(s * 0.66, s * 0.40);
    ctx.lineTo(s * 0.84, s * 0.78);
    ctx.stroke();
    // snow caps
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.46); ctx.lineTo(s * 0.36, s * 0.36); ctx.lineTo(s * 0.42, s * 0.46);
    ctx.closePath(); ctx.fill();
    ctx.beginPath();
    ctx.moveTo(s * 0.60, s * 0.50); ctx.lineTo(s * 0.66, s * 0.40); ctx.lineTo(s * 0.72, s * 0.50);
    ctx.closePath(); ctx.fill();
}

// ============================================================================
// VIM — single mountain V with feather quill across
// ============================================================================
function drawVim(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // V triangle
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.18, s * 0.22);
    ctx.lineTo(s * 0.82, s * 0.22);
    ctx.lineTo(s * 0.50, s * 0.82);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // inner V outline
    ctx.beginPath();
    ctx.moveTo(s * 0.28, s * 0.30);
    ctx.lineTo(s * 0.72, s * 0.30);
    ctx.lineTo(s * 0.50, s * 0.70);
    ctx.closePath();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
    ctx.stroke();
    // feather quill diagonally
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-Math.PI / 4);
    ctx.strokeStyle = C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.012;
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.34); ctx.lineTo(0, s * 0.20);
    ctx.stroke();
    // barbs
    for (var i = 0; i < 6; i++) {
        var t = i / 5;
        ctx.beginPath();
        ctx.moveTo(0, -s * 0.34 + t * s * 0.40);
        ctx.lineTo(-s * 0.08 * (1 - t * 0.3), -s * 0.34 + t * s * 0.40 + s * 0.04);
        ctx.stroke();
    }
    ctx.restore();
}

// ============================================================================
// EMACS — coiled infinity (meta-key) in a brassy disc
// ============================================================================
function drawEmacs(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // brassy inner disc
    C.drawInnerDisc(ctx, s, C.PALETTE.plumDeep, 0.34);
    // infinity / lemniscate
    ctx.save();
    ctx.strokeStyle = C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.040;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(cx, cy);
    ctx.bezierCurveTo(cx - s * 0.20, cy - s * 0.20, cx - s * 0.22, cy + s * 0.16, cx, cy);
    ctx.bezierCurveTo(cx + s * 0.22, cy - s * 0.16, cx + s * 0.20, cy + s * 0.20, cx, cy);
    ctx.stroke();
    // gilt inner stroke
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    ctx.moveTo(cx, cy);
    ctx.bezierCurveTo(cx - s * 0.20, cy - s * 0.20, cx - s * 0.22, cy + s * 0.16, cx, cy);
    ctx.bezierCurveTo(cx + s * 0.22, cy - s * 0.16, cx + s * 0.20, cy + s * 0.20, cx, cy);
    ctx.stroke();
    ctx.restore();
    // tiny key-cap M at top
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(cx - s * 0.06, cy - s * 0.30, s * 0.12, s * 0.06);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.06) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("M", cx, cy - s * 0.27);
}

// ============================================================================
// SUBLIME — calligraphic S in a square frame
// ============================================================================
function drawSublime(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // S calligraphic
    ctx.save();
    ctx.strokeStyle = C.PALETTE.terraDark;
    ctx.lineWidth = s * 0.06;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.68, s * 0.28);
    ctx.bezierCurveTo(s * 0.30, s * 0.20, s * 0.30, s * 0.46, s * 0.52, s * 0.50);
    ctx.bezierCurveTo(s * 0.74, s * 0.54, s * 0.74, s * 0.80, s * 0.32, s * 0.74);
    ctx.stroke();
    // gilt highlight
    ctx.strokeStyle = accent || C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.016;
    ctx.beginPath();
    ctx.moveTo(s * 0.68, s * 0.28);
    ctx.bezierCurveTo(s * 0.30, s * 0.20, s * 0.30, s * 0.46, s * 0.52, s * 0.50);
    ctx.bezierCurveTo(s * 0.74, s * 0.54, s * 0.74, s * 0.80, s * 0.32, s * 0.74);
    ctx.stroke();
    ctx.restore();
    // tiny terminal dots
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath(); ctx.arc(s * 0.68, s * 0.28, s * 0.025, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.32, s * 0.74, s * 0.025, 0, Math.PI * 2); ctx.fill();
}

// ============================================================================
// ATOM — orbital nucleus
// ============================================================================
function drawAtom(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // 3 orbital ellipses
    var rots = [0, Math.PI / 3, -Math.PI / 3];
    for (var i = 0; i < 3; i++) {
        ctx.save();
        ctx.translate(cx, cy);
        ctx.rotate(rots[i]);
        ctx.strokeStyle = [C.PALETTE.teal, C.PALETTE.terra, C.PALETTE.sageDeep][i];
        ctx.lineWidth = s * 0.018;
        ctx.beginPath();
        ctx.ellipse(0, 0, s * 0.30, s * 0.12, 0, 0, Math.PI * 2);
        ctx.stroke();
        // electron
        ctx.fillStyle = [C.PALETTE.tealDeep, C.PALETTE.terraDark, C.PALETTE.sageDark][i];
        ctx.beginPath();
        ctx.arc(s * 0.30, 0, s * 0.030, 0, Math.PI * 2);
        ctx.fill();
        ctx.restore();
    }
    // nucleus
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.07, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
}

// ============================================================================
// KATE — KDE feather plume on parchment
// ============================================================================
function drawKate(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // parchment
    ctx.save();
    ctx.translate(s * 0.36, s * 0.20);
    ctx.rotate(-0.08);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    C.roundRectPath(ctx, 0, 0, s * 0.44, s * 0.58, s * 0.02);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.010);
    ctx.stroke();
    // text lines
    ctx.fillStyle = "rgba(58,43,24,0.6)";
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.04, s * 0.08 + i * s * 0.08, s * (0.36 - i * 0.04), s * 0.014);
    }
    ctx.restore();
    // feather diagonally
    ctx.save();
    ctx.translate(s * 0.30, s * 0.78);
    ctx.rotate(-Math.PI / 3);
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.bezierCurveTo(s * 0.05, -s * 0.20, s * 0.06, -s * 0.40, 0, -s * 0.50);
    ctx.bezierCurveTo(-s * 0.06, -s * 0.40, -s * 0.05, -s * 0.20, 0, 0);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // central vein
    ctx.beginPath();
    ctx.moveTo(0, 0); ctx.lineTo(0, -s * 0.46);
    ctx.stroke();
    // tip
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(0, 0); ctx.lineTo(-s * 0.015, s * 0.04); ctx.lineTo(s * 0.015, s * 0.04);
    ctx.closePath(); ctx.fill();
    ctx.restore();
}

// ============================================================================
// GEDIT — gilt-tipped pen on flat tablet (simplest of the editors)
// ============================================================================
function drawGedit(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // tablet
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.18, s * 0.24, s * 0.64, s * 0.52);
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.strokeRect(s * 0.18, s * 0.24, s * 0.64, s * 0.52);
    // text
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * 0.24, s * 0.32 + i * s * 0.08, s * (0.5 - i * 0.05), s * 0.016);
    }
    // pen across
    ctx.save();
    ctx.translate(s * 0.74, s * 0.78);
    ctx.rotate(-Math.PI / 5);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillRect(-s * 0.30, -s * 0.014, s * 0.46, s * 0.028);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.16, -s * 0.014);
    ctx.lineTo(s * 0.24, 0);
    ctx.lineTo(s * 0.16, s * 0.014);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

// ============================================================================
// GEANY — lantern emblem (G monogram lit)
// ============================================================================
function drawGeany(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.52;
    // lantern body
    ctx.fillStyle = C.PALETTE.indigoDeep;
    C.roundRectPath(ctx, cx - s * 0.18, cy - s * 0.22, s * 0.36, s * 0.44, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    // glass panel
    ctx.fillStyle = C.PALETTE.goldHi;
    C.roundRectPath(ctx, cx - s * 0.13, cy - s * 0.16, s * 0.26, s * 0.32, s * 0.02);
    ctx.fill();
    // G letter
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.font = "700 " + Math.round(s * 0.24) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("G", cx, cy);
    // top cap & ring
    ctx.fillStyle = C.PALETTE.gold;
    ctx.fillRect(cx - s * 0.10, cy - s * 0.28, s * 0.20, s * 0.04);
    ctx.beginPath();
    ctx.arc(cx, cy - s * 0.34, s * 0.04, 0, Math.PI * 2);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
    ctx.stroke();
}

// ============================================================================
// NANO — small leaf with ascii lines
// ============================================================================
function drawNano(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // leaf
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-Math.PI / 8);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.28);
    ctx.bezierCurveTo(s * 0.20, -s * 0.20, s * 0.20, s * 0.10, 0, s * 0.22);
    ctx.bezierCurveTo(-s * 0.20, s * 0.10, -s * 0.20, -s * 0.20, 0, -s * 0.28);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // vein
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.28); ctx.lineTo(0, s * 0.22);
    C.setStroke(ctx, C.PALETTE.sageMist, s * 0.010);
    ctx.stroke();
    // side veins
    for (var i = -3; i <= 3; i++) {
        if (i === 0) continue;
        ctx.beginPath();
        ctx.moveTo(0, i * s * 0.05);
        ctx.lineTo(s * 0.10 * (i > 0 ? -1 : 1), i * s * 0.05 - s * 0.04);
        ctx.stroke();
    }
    ctx.restore();
    // tiny ascii ^G ^O hints in corners
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.font = "600 " + Math.round(s * 0.08) + "px monospace";
    ctx.fillText("^G", s * 0.16, s * 0.84);
    ctx.fillText("^O", s * 0.72, s * 0.84);
}

// ============================================================================
// NOTEPAD / NOTEPADQQ — spiral-bound notepad
// ============================================================================
function drawNotepad(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // pad
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    C.roundRectPath(ctx, s * 0.22, s * 0.18, s * 0.60, s * 0.68, s * 0.02);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    // red header band
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillRect(s * 0.22, s * 0.18, s * 0.60, s * 0.10);
    // spiral binding (rings on left)
    for (var i = 0; i < 6; i++) {
        ctx.beginPath();
        ctx.arc(s * 0.22, s * 0.28 + i * s * 0.10, s * 0.022, 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.006);
        ctx.stroke();
    }
    // ruling lines
    ctx.fillStyle = "rgba(58,43,24,0.5)";
    for (var j = 0; j < 5; j++) {
        ctx.fillRect(s * 0.32, s * 0.40 + j * s * 0.08, s * 0.44, s * 0.012);
    }
}

// ============================================================================
// JetBrains family — shared "bracket frame" with unique central motifs
// ============================================================================
function _jbFrame(ctx, s, cornerCol) {
    // black square with corner brackets
    ctx.fillStyle = C.PALETTE.ink;
    C.roundRectPath(ctx, s * 0.14, s * 0.14, s * 0.72, s * 0.72, s * 0.05);
    ctx.fill();
    // corner triangles
    var tri = function(cx, cy, sx, sy, col) {
        ctx.fillStyle = col;
        ctx.beginPath();
        ctx.moveTo(cx, cy);
        ctx.lineTo(cx + sx * s * 0.22, cy);
        ctx.lineTo(cx, cy + sy * s * 0.22);
        ctx.closePath();
        ctx.fill();
    };
    tri(s * 0.14, s * 0.14,  1,  1, cornerCol[0]);
    tri(s * 0.86, s * 0.14, -1,  1, cornerCol[1]);
    tri(s * 0.14, s * 0.86,  1, -1, cornerCol[2]);
    tri(s * 0.86, s * 0.86, -1, -1, cornerCol[3]);
}

function drawIntelliJ(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.terra, C.PALETTE.gold, C.PALETTE.plum, C.PALETTE.terra]);
    // IJ glyph
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.36, s * 0.30, s * 0.06, s * 0.40);
    ctx.fillRect(s * 0.30, s * 0.30, s * 0.18, s * 0.06);
    ctx.beginPath();
    ctx.moveTo(s * 0.54, s * 0.30);
    ctx.lineTo(s * 0.66, s * 0.30);
    ctx.lineTo(s * 0.66, s * 0.66);
    ctx.bezierCurveTo(s * 0.66, s * 0.78, s * 0.54, s * 0.78, s * 0.48, s * 0.70);
    ctx.lineTo(s * 0.54, s * 0.62);
    ctx.bezierCurveTo(s * 0.58, s * 0.66, s * 0.60, s * 0.62, s * 0.60, s * 0.62);
    ctx.lineTo(s * 0.60, s * 0.36);
    ctx.lineTo(s * 0.54, s * 0.36);
    ctx.closePath();
    ctx.fill();
}

function drawPyCharm(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.sageDeep, C.PALETTE.goldDark, C.PALETTE.sageDark, C.PALETTE.gold]);
    // coiled serpent (python) — two-tone
    ctx.fillStyle = C.PALETTE.sageMist;
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.42, s * 0.16, Math.PI, 0, false);
    ctx.lineTo(s * 0.66, s * 0.42);
    ctx.bezierCurveTo(s * 0.66, s * 0.62, s * 0.34, s * 0.62, s * 0.34, s * 0.42);
    ctx.closePath();
    ctx.fill();
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.58, s * 0.16, 0, Math.PI, false);
    ctx.lineTo(s * 0.34, s * 0.58);
    ctx.bezierCurveTo(s * 0.34, s * 0.38, s * 0.66, s * 0.38, s * 0.66, s * 0.58);
    ctx.closePath();
    ctx.fill();
    // eye dots
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath(); ctx.arc(s * 0.42, s * 0.42, s * 0.014, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.58, s * 0.58, s * 0.014, 0, Math.PI * 2); ctx.fill();
}

function drawWebStorm(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.teal, C.PALETTE.gold, C.PALETTE.tealDeep, C.PALETTE.terra]);
    // globe with ribbon
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.5, s * 0.20, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fill();
    ctx.strokeStyle = C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.010;
    for (var i = -2; i <= 2; i++) {
        ctx.beginPath();
        ctx.ellipse(s * 0.5, s * 0.5, s * 0.20 * Math.cos(i * 0.4), s * 0.20, 0, 0, Math.PI * 2);
        ctx.stroke();
    }
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.5);
    ctx.lineTo(s * 0.70, s * 0.5);
    ctx.stroke();
}

function drawCLion(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.terra, C.PALETTE.indigo, C.PALETTE.gold, C.PALETTE.plum]);
    // C bracket + ray
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineWidth = s * 0.08;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.arc(s * 0.52, s * 0.50, s * 0.18, Math.PI * 0.25, Math.PI * 1.75);
    ctx.stroke();
    // ray going out the opening
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.020;
    ctx.beginPath();
    ctx.moveTo(s * 0.66, s * 0.40);
    ctx.lineTo(s * 0.82, s * 0.34);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(s * 0.66, s * 0.60);
    ctx.lineTo(s * 0.82, s * 0.66);
    ctx.stroke();
}

function drawGoLand(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.teal, C.PALETTE.rose, C.PALETTE.terra, C.PALETTE.gold]);
    // gopher silhouette: oval head with whisker triangle
    ctx.fillStyle = "#9bcde3";
    ctx.beginPath();
    ctx.ellipse(s * 0.50, s * 0.52, s * 0.16, s * 0.18, 0, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // ears
    ctx.beginPath();
    ctx.ellipse(s * 0.36, s * 0.40, s * 0.04, s * 0.06, -0.5, 0, Math.PI * 2);
    ctx.fillStyle = "#9bcde3";
    ctx.fill();
    ctx.beginPath();
    ctx.ellipse(s * 0.64, s * 0.40, s * 0.04, s * 0.06, 0.5, 0, Math.PI * 2);
    ctx.fill();
    // eyes (large)
    ctx.fillStyle = "#fff";
    ctx.beginPath(); ctx.arc(s * 0.43, s * 0.50, s * 0.034, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.57, s * 0.50, s * 0.034, 0, Math.PI * 2); ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath(); ctx.arc(s * 0.43, s * 0.50, s * 0.014, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.57, s * 0.50, s * 0.014, 0, Math.PI * 2); ctx.fill();
    // teeth
    ctx.fillStyle = "#fff";
    ctx.fillRect(s * 0.48, s * 0.56, s * 0.018, s * 0.04);
    ctx.fillRect(s * 0.504, s * 0.56, s * 0.018, s * 0.04);
}

function drawAndroidStudio(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.sage, C.PALETTE.terra, C.PALETTE.sage, C.PALETTE.indigo]);
    // robot dome
    ctx.fillStyle = C.PALETTE.sageMist;
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.56, s * 0.18, Math.PI, 0, false);
    ctx.lineTo(s * 0.32, s * 0.56);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // antennas
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.012;
    ctx.beginPath();
    ctx.moveTo(s * 0.38, s * 0.32); ctx.lineTo(s * 0.42, s * 0.40);
    ctx.moveTo(s * 0.62, s * 0.32); ctx.lineTo(s * 0.58, s * 0.40);
    ctx.stroke();
    // eyes
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath(); ctx.arc(s * 0.44, s * 0.48, s * 0.018, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.56, s * 0.48, s * 0.018, 0, Math.PI * 2); ctx.fill();
}

function drawRider(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.terra, C.PALETTE.plum, C.PALETTE.gold, C.PALETTE.indigoDeep]);
    // rider silhouette: horse + figure (abstract)
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.28, s * 0.66);
    ctx.lineTo(s * 0.34, s * 0.46);
    ctx.lineTo(s * 0.46, s * 0.44);
    ctx.lineTo(s * 0.48, s * 0.32);
    ctx.lineTo(s * 0.58, s * 0.32);
    ctx.lineTo(s * 0.62, s * 0.44);
    ctx.lineTo(s * 0.72, s * 0.50);
    ctx.lineTo(s * 0.74, s * 0.66);
    ctx.lineTo(s * 0.66, s * 0.66);
    ctx.lineTo(s * 0.62, s * 0.56);
    ctx.lineTo(s * 0.40, s * 0.56);
    ctx.lineTo(s * 0.36, s * 0.66);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
}

function drawDataGrip(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.gold, C.PALETTE.terra, C.PALETTE.plum, C.PALETTE.sageDeep]);
    // database cylinders (stacked)
    for (var i = 0; i < 3; i++) {
        var y = s * 0.36 + i * s * 0.10;
        ctx.fillStyle = i % 2 ? C.PALETTE.goldHi : C.PALETTE.goldDark;
        ctx.beginPath();
        ctx.ellipse(s * 0.5, y, s * 0.18, s * 0.05, 0, 0, Math.PI * 2);
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    }
    // side walls
    ctx.fillStyle = C.PALETTE.goldDark;
    ctx.fillRect(s * 0.32, s * 0.36, s * 0.04, s * 0.20);
    ctx.fillRect(s * 0.64, s * 0.36, s * 0.04, s * 0.20);
}

function drawRubyMine(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.terra, C.PALETTE.terraDark, C.PALETTE.gold, C.PALETTE.rose]);
    // ruby gem facets
    ctx.save();
    ctx.translate(s * 0.5, s * 0.52);
    var g = ctx.createLinearGradient(0, -s * 0.18, 0, s * 0.18);
    g.addColorStop(0, "#e8a48f"); g.addColorStop(1, C.PALETTE.terraDark);
    ctx.fillStyle = g;
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.18);
    ctx.lineTo(s * 0.16, -s * 0.06);
    ctx.lineTo(s * 0.10, s * 0.18);
    ctx.lineTo(-s * 0.10, s * 0.18);
    ctx.lineTo(-s * 0.16, -s * 0.06);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // facet lines
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.18); ctx.lineTo(0, s * 0.18);
    ctx.moveTo(-s * 0.16, -s * 0.06); ctx.lineTo(s * 0.16, -s * 0.06);
    ctx.moveTo(-s * 0.10, s * 0.18); ctx.lineTo(0, -s * 0.18);
    ctx.moveTo(s * 0.10, s * 0.18); ctx.lineTo(0, -s * 0.18);
    ctx.stroke();
    ctx.restore();
}

function drawPhpStorm(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.plum, C.PALETTE.terra, C.PALETTE.indigo, C.PALETTE.gold]);
    // stylised elephant head
    ctx.fillStyle = "#c0a5c4";
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.46, s * 0.16, 0, Math.PI * 2);
    ctx.fill();
    // trunk
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.54);
    ctx.bezierCurveTo(s * 0.42, s * 0.66, s * 0.60, s * 0.72, s * 0.58, s * 0.62);
    ctx.bezierCurveTo(s * 0.56, s * 0.58, s * 0.52, s * 0.56, s * 0.50, s * 0.54);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // ears
    ctx.beginPath();
    ctx.ellipse(s * 0.34, s * 0.44, s * 0.08, s * 0.12, -0.3, 0, Math.PI * 2);
    ctx.fillStyle = "#c0a5c4"; ctx.fill();
    ctx.beginPath();
    ctx.ellipse(s * 0.66, s * 0.44, s * 0.08, s * 0.12, 0.3, 0, Math.PI * 2);
    ctx.fill();
    // eye
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(s * 0.46, s * 0.44, s * 0.014, 0, Math.PI * 2); ctx.fill();
}

function drawFleet(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _jbFrame(ctx, s, [C.PALETTE.teal, C.PALETTE.indigo, C.PALETTE.gold, C.PALETTE.terra]);
    // sail/anchor abstract
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.28);
    ctx.lineTo(s * 0.66, s * 0.62);
    ctx.lineTo(s * 0.34, s * 0.62);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.49, s * 0.28, s * 0.02, s * 0.42);
    // crossbar
    ctx.fillRect(s * 0.40, s * 0.68, s * 0.20, s * 0.020);
}

// ============================================================================
// ECLIPSE — solar eclipse with corona
// ============================================================================
function drawEclipse(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // corona rays
    for (var i = 0; i < 24; i++) {
        var a = i / 24 * Math.PI * 2;
        ctx.beginPath();
        ctx.moveTo(cx + Math.cos(a) * s * 0.18, cy + Math.sin(a) * s * 0.18);
        ctx.lineTo(cx + Math.cos(a) * s * 0.34, cy + Math.sin(a) * s * 0.34);
        C.setStroke(ctx, accent || C.PALETTE.goldHi, s * (i % 2 ? 0.014 : 0.008));
        ctx.stroke();
    }
    // eclipsed sun
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.18, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.gold;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx - s * 0.03, cy - s * 0.02, s * 0.16, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    // bright crescent
    ctx.beginPath();
    ctx.arc(cx + s * 0.02, cy + s * 0.02, s * 0.18, -Math.PI * 0.2, Math.PI * 0.2);
    C.setStroke(ctx, C.PALETTE.goldHi, s * 0.010);
    ctx.stroke();
}

// ============================================================================
// NETBEANS — mariner's compass
// ============================================================================
function drawNetBeans(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // compass rose star (8-point)
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 8; i++) {
        ctx.save();
        ctx.rotate(i * Math.PI / 4);
        ctx.fillStyle = i % 2 ? C.PALETTE.indigoDeep : C.PALETTE.gold;
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(s * 0.05, -s * 0.10);
        ctx.lineTo(0, -s * (i % 2 ? 0.22 : 0.30));
        ctx.lineTo(-s * 0.05, -s * 0.10);
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
    ctx.restore();
    // central pivot
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    // cardinal letters
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.08) + "px serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("N", cx, cy - s * 0.36);
}

// ============================================================================
// QT CREATOR — triple-spiral Qt mark
// ============================================================================
function drawQtCreator(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // green ring
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.32, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.fill();
    // inner cream
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.22, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    // Q tail (stylised)
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.14, cy + s * 0.10);
    ctx.lineTo(cx + s * 0.30, cy + s * 0.30);
    C.setStroke(ctx, C.PALETTE.sageDeep, s * 0.044);
    ctx.stroke();
    // Q letter
    ctx.fillStyle = C.PALETTE.sageDark;
    ctx.font = "700 " + Math.round(s * 0.28) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("Q", cx, cy);
}

// ============================================================================
// KDEVELOP — developer's compass with angled rule
// ============================================================================
function drawKDevelop(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.52;
    // compass legs
    ctx.save();
    ctx.translate(cx, cy);
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.026;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.22);
    ctx.lineTo(-s * 0.18, s * 0.20);
    ctx.moveTo(0, -s * 0.22);
    ctx.lineTo(s * 0.18, s * 0.20);
    ctx.stroke();
    // hinge
    ctx.beginPath();
    ctx.arc(0, -s * 0.22, s * 0.030, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    ctx.stroke();
    // arc swept
    ctx.beginPath();
    ctx.arc(0, -s * 0.22, s * 0.26, Math.PI * 0.4, Math.PI * 0.6);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    ctx.restore();
}

// ============================================================================
// CODE::BLOCKS — stacked engraved cubes
// ============================================================================
function drawCodeBlocks(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    function cube(cx, cy, sz, col1, col2) {
        ctx.fillStyle = col1;
        ctx.fillRect(cx - sz / 2, cy - sz / 2, sz, sz);
        // diagonal highlight
        ctx.fillStyle = col2;
        ctx.beginPath();
        ctx.moveTo(cx - sz / 2, cy - sz / 2);
        ctx.lineTo(cx + sz / 2, cy - sz / 2);
        ctx.lineTo(cx, cy);
        ctx.closePath();
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.strokeRect(cx - sz / 2, cy - sz / 2, sz, sz);
    }
    cube(s * 0.35, s * 0.62, s * 0.22, C.PALETTE.terra, C.PALETTE.goldHi);
    cube(s * 0.65, s * 0.62, s * 0.22, C.PALETTE.sageDeep, C.PALETTE.sageMist);
    cube(s * 0.50, s * 0.36, s * 0.22, C.PALETTE.indigoDeep, C.PALETTE.gold);
    // braces engraved
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("{ }", s * 0.5, s * 0.36);
}

// ============================================================================
// GENERIC EDITOR — fallback for unknown editors
// ============================================================================
function drawGenericEditor(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // paper
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    C.roundRectPath(ctx, s * 0.20, s * 0.16, s * 0.60, s * 0.68, s * 0.02);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    // dog-ear
    ctx.fillStyle = C.PALETTE.bgPaper;
    ctx.beginPath();
    ctx.moveTo(s * 0.80, s * 0.16);
    ctx.lineTo(s * 0.80, s * 0.28);
    ctx.lineTo(s * 0.68, s * 0.16);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.010);
    ctx.stroke();
    // text lines
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.26, s * 0.32 + i * s * 0.08, s * (0.46 - i * 0.04), s * 0.014);
    }
    // pen tip
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.74, s * 0.74);
    ctx.lineTo(s * 0.86, s * 0.86);
    ctx.lineTo(s * 0.80, s * 0.86);
    ctx.lineTo(s * 0.72, s * 0.80);
    ctx.closePath();
    ctx.fill();
}
