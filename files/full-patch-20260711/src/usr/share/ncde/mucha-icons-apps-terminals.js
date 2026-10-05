// mucha-icons-apps-terminals.js — terminal emulators, each visually distinct.
.pragma library
.import "mucha-icons-core.js" as C

// Common: a darkened tablet with prompt content. Each terminal varies the
// frame, the prompt text, the accent, and the surrounding ornament.

function _tablet(ctx, s, fill, frame) {
    ctx.fillStyle = fill;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.16, s * 0.22, s * 0.68, s * 0.56, s * 0.05);
    ctx.fill();
    C.setStroke(ctx, frame, s * 0.018);
    ctx.stroke();
}

// ============================================================================
// KONSOLE — engraved bronze tablet with a calligraphic prompt
// ============================================================================
function drawKonsole(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    _tablet(ctx, s, "#1d1a14", C.PALETTE.gold);
    // engraved fillet
    ctx.strokeStyle = "rgba(230,199,133,0.45)";
    ctx.lineWidth = s * 0.006;
    ctx.strokeRect(s * 0.20, s * 0.26, s * 0.60, s * 0.48);
    // prompt
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.font = "700 " + Math.round(s * 0.18) + "px 'Cinzel',serif";
    ctx.textBaseline = "middle";
    ctx.fillText(">_", s * 0.26, s * 0.46);
    // cursor block blink (filled)
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.54, s * 0.58, s * 0.08, s * 0.10);
    // KDE flourish: small four-petal at bottom
    C.drawRosette(ctx, s * 0.5, s * 0.86, s * 0.04, 4, accent || C.PALETTE.gold, C.PALETTE.bgCreamHi);
}

// ============================================================================
// GNOME TERMINAL — laurel-flanked tablet, sober palette
// ============================================================================
function drawGnomeTerminal(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    _tablet(ctx, s, "#2a2520", C.PALETTE.goldDark);
    // left + right laurel sprig
    for (var i = 0; i < 4; i++) {
        C.leafBead(ctx, s * 0.10, s * 0.34 + i * s * 0.10, s * 0.10, 0, C.PALETTE.sageDeep);
        C.leafBead(ctx, s * 0.90, s * 0.34 + i * s * 0.10, s * 0.10, Math.PI, C.PALETTE.sageDeep);
    }
    ctx.fillStyle = C.PALETTE.sageMist;
    ctx.font = "600 " + Math.round(s * 0.14) + "px monospace";
    ctx.textBaseline = "middle";
    ctx.fillText("$", s * 0.26, s * 0.42);
    // text bars
    ctx.fillStyle = "rgba(184,201,178,0.65)";
    ctx.fillRect(s * 0.34, s * 0.40, s * 0.36, s * 0.030);
    ctx.fillRect(s * 0.22, s * 0.56, s * 0.44, s * 0.024);
    ctx.fillRect(s * 0.22, s * 0.64, s * 0.34, s * 0.024);
}

// ============================================================================
// ALACRITTY — swift; minimal tile with motion-streaks behind a chevron
// ============================================================================
function drawAlacritty(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow, ornament:false});
    // motion streaks
    ctx.save();
    ctx.strokeStyle = C.PALETTE.goldDark;
    ctx.lineCap = "round";
    for (var i = 0; i < 5; i++) {
        ctx.lineWidth = s * (0.020 - i * 0.003);
        ctx.globalAlpha = 1 - i * 0.18;
        ctx.beginPath();
        ctx.moveTo(s * 0.18, s * 0.32 + i * s * 0.07);
        ctx.lineTo(s * 0.62, s * 0.32 + i * s * 0.07);
        ctx.stroke();
    }
    ctx.restore();
    // big chevron / play
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.30);
    ctx.lineTo(s * 0.80, s * 0.50);
    ctx.lineTo(s * 0.50, s * 0.70);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.016);
    ctx.stroke();
    // halo glyph dot
    ctx.beginPath();
    ctx.arc(s * 0.18, s * 0.78, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
}

// ============================================================================
// KITTY — silhouette of a sitting cat with whisker rays
// ============================================================================
function drawKitty(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // body
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.beginPath();
    ctx.ellipse(cx, cy + s * 0.05, s * 0.20, s * 0.22, 0, 0, Math.PI * 2);
    ctx.fill();
    // head
    ctx.beginPath();
    ctx.arc(cx, cy - s * 0.16, s * 0.14, 0, Math.PI * 2);
    ctx.fill();
    // ears
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.12, cy - s * 0.20);
    ctx.lineTo(cx - s * 0.06, cy - s * 0.32);
    ctx.lineTo(cx - s * 0.02, cy - s * 0.20);
    ctx.closePath(); ctx.fill();
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.12, cy - s * 0.20);
    ctx.lineTo(cx + s * 0.06, cy - s * 0.32);
    ctx.lineTo(cx + s * 0.02, cy - s * 0.20);
    ctx.closePath(); ctx.fill();
    // eyes
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.beginPath(); ctx.ellipse(cx - s * 0.05, cy - s * 0.17, s * 0.022, s * 0.030, 0, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.ellipse(cx + s * 0.05, cy - s * 0.17, s * 0.022, s * 0.030, 0, 0, Math.PI * 2); ctx.fill();
    // pupils
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath(); ctx.ellipse(cx - s * 0.05, cy - s * 0.17, s * 0.005, s * 0.025, 0, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.ellipse(cx + s * 0.05, cy - s * 0.17, s * 0.005, s * 0.025, 0, 0, Math.PI * 2); ctx.fill();
    // nose
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.015, cy - s * 0.10);
    ctx.lineTo(cx + s * 0.015, cy - s * 0.10);
    ctx.lineTo(cx, cy - s * 0.085);
    ctx.closePath(); ctx.fill();
    // whisker rays
    ctx.strokeStyle = C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.008;
    for (var i = -2; i <= 2; i++) {
        if (i === 0) continue;
        ctx.beginPath();
        ctx.moveTo(cx - s * 0.06, cy - s * 0.08 + i * s * 0.005);
        ctx.lineTo(cx - s * 0.20, cy - s * 0.08 + i * s * 0.015);
        ctx.stroke();
        ctx.beginPath();
        ctx.moveTo(cx + s * 0.06, cy - s * 0.08 + i * s * 0.005);
        ctx.lineTo(cx + s * 0.20, cy - s * 0.08 + i * s * 0.015);
        ctx.stroke();
    }
}

// ============================================================================
// WEZTERM — wind-form W in a domed cartouche
// ============================================================================
function drawWezterm(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"arch", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.55;
    // wind curls
    ctx.save();
    ctx.strokeStyle = C.PALETTE.teal;
    ctx.lineWidth = s * 0.014;
    ctx.lineCap = "round";
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        var y = cy - s * 0.18 + i * s * 0.10;
        ctx.moveTo(s * 0.18, y);
        ctx.bezierCurveTo(s * 0.30, y - s * 0.04, s * 0.60, y - s * 0.04, s * 0.82, y);
        ctx.stroke();
    }
    ctx.restore();
    // big "W" calligraphic
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.22, cy - s * 0.05);
    ctx.lineTo(s * 0.32, cy + s * 0.18);
    ctx.lineTo(s * 0.42, cy - s * 0.04);
    ctx.lineTo(s * 0.50, cy + s * 0.18);
    ctx.lineTo(s * 0.58, cy - s * 0.04);
    ctx.lineTo(s * 0.68, cy + s * 0.18);
    ctx.lineTo(s * 0.78, cy - s * 0.05);
    ctx.lineTo(s * 0.72, cy - s * 0.05);
    ctx.lineTo(s * 0.66, cy + s * 0.08);
    ctx.lineTo(s * 0.58, cy - s * 0.10);
    ctx.lineTo(s * 0.50, cy + s * 0.05);
    ctx.lineTo(s * 0.42, cy - s * 0.10);
    ctx.lineTo(s * 0.34, cy + s * 0.08);
    ctx.lineTo(s * 0.28, cy - s * 0.05);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.010);
    ctx.stroke();
    // tiny gilt droplet over each peak
    ctx.fillStyle = accent || C.PALETTE.gold;
    [0.32, 0.50, 0.68].forEach(function(x) {
        ctx.beginPath();
        ctx.arc(s * x, cy + s * 0.16, s * 0.012, 0, Math.PI * 2);
        ctx.fill();
    });
}

// ============================================================================
// TILIX — split-pane tablet (two windows in a tiled arrangement)
// ============================================================================
function drawTilix(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // left pane
    ctx.fillStyle = "#1f1a14";
    ctx.fillRect(s * 0.16, s * 0.20, s * 0.30, s * 0.60);
    // right top & bottom
    ctx.fillStyle = "#2a221a";
    ctx.fillRect(s * 0.50, s * 0.20, s * 0.34, s * 0.28);
    ctx.fillStyle = "#1f1a14";
    ctx.fillRect(s * 0.50, s * 0.52, s * 0.34, s * 0.28);
    // dividers (gold)
    C.setStroke(ctx, C.PALETTE.gold, s * 0.012);
    ctx.beginPath(); ctx.moveTo(s * 0.48, s * 0.20); ctx.lineTo(s * 0.48, s * 0.80); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(s * 0.50, s * 0.50); ctx.lineTo(s * 0.84, s * 0.50); ctx.stroke();
    // glyphs in each pane
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px monospace";
    ctx.textBaseline = "middle";
    ctx.fillText("$", s * 0.22, s * 0.34);
    ctx.fillText(">", s * 0.55, s * 0.34);
    ctx.fillText("#", s * 0.55, s * 0.66);
    // bars
    ctx.fillStyle = "rgba(230,199,133,0.55)";
    ctx.fillRect(s * 0.22, s * 0.46, s * 0.20, s * 0.018);
    ctx.fillRect(s * 0.22, s * 0.54, s * 0.16, s * 0.018);
    ctx.fillRect(s * 0.62, s * 0.40, s * 0.16, s * 0.018);
    ctx.fillRect(s * 0.62, s * 0.72, s * 0.16, s * 0.018);
}

// ============================================================================
// TERMINATOR — crossed sabres over a tablet
// ============================================================================
function drawTerminator(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    _tablet(ctx, s, "#1c170f", C.PALETTE.gold);
    // crossed sabres
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    function sabre(rot) {
        ctx.save();
        ctx.rotate(rot);
        // blade
        var g = ctx.createLinearGradient(0, -s * 0.30, 0, s * 0.30);
        g.addColorStop(0, "#e6e6ec");
        g.addColorStop(1, "#9b9bb0");
        ctx.fillStyle = g;
        ctx.beginPath();
        ctx.moveTo(-s * 0.012, -s * 0.30);
        ctx.lineTo(s * 0.012, -s * 0.30);
        ctx.lineTo(s * 0.016, s * 0.10);
        ctx.lineTo(0, s * 0.18);
        ctx.lineTo(-s * 0.016, s * 0.10);
        ctx.closePath();
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.006);
        ctx.stroke();
        // guard
        ctx.beginPath();
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fillRect(-s * 0.05, s * 0.10, s * 0.10, s * 0.022);
        // grip
        ctx.fillStyle = C.PALETTE.terraDark;
        ctx.fillRect(-s * 0.010, s * 0.12, s * 0.020, s * 0.14);
        // pommel
        ctx.beginPath();
        ctx.arc(0, s * 0.27, s * 0.025, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.goldHi;
        ctx.fill();
        ctx.restore();
    }
    sabre(-0.55);
    sabre(0.55);
    ctx.restore();
}

// ============================================================================
// YAKUAKE — drop-down ribbon descending from the top
// ============================================================================
function drawYakuake(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // pulled-down ribbon
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.16, s * 0.10);
    ctx.lineTo(s * 0.84, s * 0.10);
    ctx.lineTo(s * 0.84, s * 0.60);
    ctx.quadraticCurveTo(s * 0.50, s * 0.78, s * 0.16, s * 0.60);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.014);
    ctx.stroke();
    // top mount
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.10, s * 0.04, s * 0.80, s * 0.08);
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.010);
    ctx.strokeRect(s * 0.10, s * 0.04, s * 0.80, s * 0.08);
    // text content
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.font = "600 " + Math.round(s * 0.10) + "px monospace";
    ctx.textBaseline = "middle";
    ctx.fillText("$ _", s * 0.24, s * 0.34);
    ctx.fillStyle = "rgba(230,199,133,0.5)";
    ctx.fillRect(s * 0.24, s * 0.46, s * 0.30, s * 0.018);
    // hanging tassel
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.45, s * 0.74);
    ctx.lineTo(s * 0.55, s * 0.74);
    ctx.lineTo(s * 0.50, s * 0.86);
    ctx.closePath();
    ctx.fill();
}

// ============================================================================
// GUAKE — flame above the tablet
// ============================================================================
function drawGuake(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _tablet(ctx, s, "#1a1610", C.PALETTE.gold);
    // flame above
    ctx.save();
    var g = ctx.createLinearGradient(0, s * 0.04, 0, s * 0.30);
    g.addColorStop(0, "#f6c463");
    g.addColorStop(0.5, C.PALETTE.terra);
    g.addColorStop(1, C.PALETTE.terraDark);
    ctx.fillStyle = g;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.04);
    ctx.bezierCurveTo(s * 0.40, s * 0.10, s * 0.32, s * 0.18, s * 0.40, s * 0.24);
    ctx.bezierCurveTo(s * 0.34, s * 0.18, s * 0.42, s * 0.10, s * 0.50, s * 0.16);
    ctx.bezierCurveTo(s * 0.58, s * 0.10, s * 0.66, s * 0.18, s * 0.60, s * 0.24);
    ctx.bezierCurveTo(s * 0.68, s * 0.18, s * 0.60, s * 0.10, s * 0.50, s * 0.04);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
    // text
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.font = "600 " + Math.round(s * 0.12) + "px monospace";
    ctx.textBaseline = "middle";
    ctx.fillText(">_", s * 0.26, s * 0.50);
    ctx.fillStyle = "rgba(230,199,133,0.5)";
    ctx.fillRect(s * 0.26, s * 0.64, s * 0.42, s * 0.020);
}

// ============================================================================
// FOOT — footprint in a wax seal
// ============================================================================
function drawFoot(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // wax disc
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.08, cy - s * 0.10, s * 0.02, s * 0.32,
        [[0, "#d28465"], [1, C.PALETTE.terraDark]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // footprint (sole + 5 toe-dots)
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.ellipse(cx, cy + s * 0.05, s * 0.08, s * 0.14, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx,           cy - s * 0.13, s * 0.030, 0, Math.PI * 2);
    ctx.arc(cx - s * 0.06, cy - s * 0.10, s * 0.022, 0, Math.PI * 2);
    ctx.arc(cx + s * 0.06, cy - s * 0.10, s * 0.022, 0, Math.PI * 2);
    ctx.arc(cx - s * 0.10, cy - s * 0.06, s * 0.018, 0, Math.PI * 2);
    ctx.arc(cx + s * 0.10, cy - s * 0.06, s * 0.018, 0, Math.PI * 2);
    ctx.fill();
}

// ============================================================================
// HYPER — H monogram in starburst rays
// ============================================================================
function drawHyper(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // rays
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 16; i++) {
        ctx.save();
        ctx.rotate(i / 16 * Math.PI * 2);
        ctx.fillStyle = i % 2 ? C.PALETTE.gold : C.PALETTE.goldHi;
        ctx.beginPath();
        ctx.moveTo(0, -s * 0.16);
        ctx.lineTo(s * 0.014, -s * 0.34);
        ctx.lineTo(-s * 0.014, -s * 0.34);
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
    ctx.restore();
    // central disc
    C.drawInnerDisc(ctx, s, C.PALETTE.indigoDeep, 0.18);
    // H
    ctx.save();
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.fillRect(cx - s * 0.08, cy - s * 0.10, s * 0.030, s * 0.20);
    ctx.fillRect(cx + s * 0.05, cy - s * 0.10, s * 0.030, s * 0.20);
    ctx.fillRect(cx - s * 0.06, cy - s * 0.014, s * 0.12, s * 0.028);
    ctx.restore();
}

// ============================================================================
// XTERM / URXVT / RXVT / ST — vellum scroll with classical X
// ============================================================================
function drawXterm(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // parchment
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.16, s * 0.20, s * 0.68, s * 0.60, s * 0.02);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    // engraved X
    ctx.save();
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.060;
    ctx.lineCap = "square";
    ctx.beginPath();
    ctx.moveTo(s * 0.26, s * 0.30);
    ctx.lineTo(s * 0.74, s * 0.70);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(s * 0.74, s * 0.30);
    ctx.lineTo(s * 0.26, s * 0.70);
    ctx.stroke();
    // gilt inner
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.020;
    ctx.beginPath();
    ctx.moveTo(s * 0.26, s * 0.30);
    ctx.lineTo(s * 0.74, s * 0.70);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(s * 0.74, s * 0.30);
    ctx.lineTo(s * 0.26, s * 0.70);
    ctx.stroke();
    ctx.restore();
    // corner bosses
    [[0.16,0.20],[0.84,0.20],[0.16,0.80],[0.84,0.80]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.025, 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fill();
    });
}

// ============================================================================
// GENERIC TERMINAL — tablet with prompt
// ============================================================================
function drawGenericTerminal(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    _tablet(ctx, s, "#231d15", C.PALETTE.gold);
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.font = "700 " + Math.round(s * 0.16) + "px monospace";
    ctx.textBaseline = "middle";
    ctx.fillText(">", s * 0.26, s * 0.46);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.42, s * 0.40, s * 0.10, s * 0.12);
}
