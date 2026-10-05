// mucha-salon.js — Salon Nocturne Canvas painters for NCDE.
// Pure Canvas 2D, .pragma library. Fully transparent — no fills behind ornament.
// Mucha leading gold + VFD amber hardcoded per CLAUDE.md "Mucha art JS" exemption.
// accentColor / glowColor pass through from ncde.accent / ncde.glow so the
// theme drives all stained-glass mid-tones.
//
// Exports (all lowercase first letter — Qt forbids capitalised function names):
//   paintRoseFrame     — outer rose window (spokes + rings + jewel rim)
//   paintScrubberArc   — circular gold scrubber with progress jewel
//   paintDisc          — spinning leaded-glass medallion (vinyl-style)
//   paintPetals        — audio-reactive blooming petal ring
//   paintJewel         — single transport jewel button (prev/play/pause/next/stop)
//   paintHorn          — small brass gramophone horn flourish
//   paintVFDPanel      — dark glass display with amber recessed text
//   paintEqBars        — stained-glass equaliser bar set
//   paintVolumeVine    — horizontal vine slider with amber jewel
//   paintFiligreeRow   — horizontal art-nouveau divider with side curls
//   paintCartouche     — ornate text frame with side curls + medallions
//   paintIris          — Mucha iris ornament (vertical)
//   paintCrest         — symmetric crown finial
//
.pragma library

// ── Constants ──────────────────────────────────────────────────
var LEADING_BRIGHT = "rgba(240, 210, 122, 1.0)";
var LEADING        = "rgba(184, 138, 50, 1.0)";
var LEADING_DEEP   = "rgba(74, 50, 8, 1.0)";
var VFD_AMBER      = "rgba(248, 184, 80, 1.0)";
var VFD_AMBER_DIM  = "rgba(120, 76, 22, 0.5)";

// ── Color helper — Qt color object | "#rrggbb" → rgba string ──
function toRgba(c, a) {
    if (a === undefined) a = 1;
    if (typeof c !== "string") {
        var r = Math.round(c.r * 255);
        var g = Math.round(c.g * 255);
        var b = Math.round(c.b * 255);
        return "rgba(" + r + "," + g + "," + b + "," + a + ")";
    }
    if (c.charAt(0) === "#" && c.length === 7) {
        return "rgba(" + parseInt(c.substring(1,3), 16) + ","
                       + parseInt(c.substring(3,5), 16) + ","
                       + parseInt(c.substring(5,7), 16) + "," + a + ")";
    }
    return c;
}

// ═══════════════════════════════════════════════════════════════
// ROSE WINDOW FRAME
// 12 spokes from inner ring to outer rim. 24 jewels on outer rim.
// No background fill — fully transparent.
// ═══════════════════════════════════════════════════════════════
function paintRoseFrame(ctx, cx, cy, outerR, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    ctx.save();

    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.4;
    ctx.beginPath();
    ctx.arc(cx, cy, outerR, 0, Math.PI * 2);
    ctx.stroke();
    ctx.strokeStyle = LD;
    ctx.lineWidth = 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, outerR - 1.5, 0, Math.PI * 2);
    ctx.stroke();

    var spokes = 12;
    var innerR = outerR * 0.32;
    ctx.strokeStyle = toRgba(LB, 0.4);
    ctx.lineWidth = 0.7;
    for (var i = 0; i < spokes; i++) {
        var a = (i / spokes) * Math.PI * 2 - Math.PI / 2;
        ctx.beginPath();
        ctx.moveTo(cx + Math.cos(a) * innerR, cy + Math.sin(a) * innerR);
        ctx.lineTo(cx + Math.cos(a) * (outerR - 2), cy + Math.sin(a) * (outerR - 2));
        ctx.stroke();
    }

    ctx.strokeStyle = toRgba(LB, 0.6);
    ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.arc(cx, cy, innerR, 0, Math.PI * 2);
    ctx.stroke();

    var jewels = 24;
    for (var j = 0; j < jewels; j++) {
        var ja = (j / jewels) * Math.PI * 2;
        var jx = cx + Math.cos(ja) * outerR;
        var jy = cy + Math.sin(ja) * outerR;
        ctx.fillStyle = (j % 3 === 0) ? toRgba(accentColor, 0.85) : toRgba(glowColor, 0.75);
        ctx.strokeStyle = toRgba(LB, 0.5);
        ctx.lineWidth = 0.4;
        ctx.beginPath();
        ctx.arc(jx, jy, j % 2 === 0 ? 1.6 : 1.1, 0, Math.PI * 2);
        ctx.fill();
        ctx.stroke();
    }

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// CIRCULAR SCRUBBER ARC
// Gold fills from 12 o'clock clockwise as frac goes 0..1.
// ═══════════════════════════════════════════════════════════════
function paintScrubberArc(ctx, cx, cy, radius, frac, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    if (frac < 0) frac = 0;
    if (frac > 1) frac = 1;
    ctx.save();

    ctx.strokeStyle = toRgba(LD, 0.7);
    ctx.lineWidth = 3.5;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.arc(cx, cy, radius, -Math.PI / 2, Math.PI * 1.5);
    ctx.stroke();

    if (frac > 0.001) {
        var startA = -Math.PI / 2;
        var endA = startA + frac * Math.PI * 2;
        var fg = ctx.createLinearGradient(cx, cy - radius, cx + radius, cy);
        fg.addColorStop(0, LM);
        fg.addColorStop(1, LB);
        ctx.strokeStyle = fg;
        ctx.lineWidth = 3.5;
        ctx.beginPath();
        ctx.arc(cx, cy, radius, startA, endA);
        ctx.stroke();
    }

    var ja = -Math.PI / 2 + frac * Math.PI * 2;
    var jx = cx + Math.cos(ja) * radius;
    var jy = cy + Math.sin(ja) * radius;
    var jg = ctx.createRadialGradient(jx - 1.5, jy - 1.5, 0, jx, jy, 6);
    jg.addColorStop(0, "rgba(255, 230, 170, 1)");
    jg.addColorStop(0.5, LM);
    jg.addColorStop(1, LD);
    ctx.fillStyle = jg;
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.6;
    ctx.beginPath();
    ctx.arc(jx, jy, 4, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// RECORD RING (spinning leaded-glass platter BEHIND the petals)
// A translucent accent-glass annulus with record grooves, radial
// leading panels, inlaid orbiting jewels, and two reflecting shine
// wedges — all rotating with rotationDeg. NOT vinyl-black: it is
// tinted glass so wallpaper still glows through, and it gives the
// petals a surface to bloom against. Drawn before paintPetals.
//   innerR  ~ disc radius (platter hugs the centre medallion)
//   outerR  ~ just inside the rose frame
// ═══════════════════════════════════════════════════════════════
function paintRecordRing(ctx, cx, cy, innerR, outerR, rotationDeg, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    ctx.save();
    ctx.translate(cx, cy);

    var inFrac = innerR / outerR;

    // ── Glass platter — full disc whose centre is transparent so the
    //    spinning medallion shows through; glass only from innerR out. ──
    var plat = ctx.createRadialGradient(0, 0, 0, 0, 0, outerR);
    plat.addColorStop(0,                       "rgba(0,0,0,0)");
    plat.addColorStop(Math.max(0, inFrac-0.02),"rgba(0,0,0,0)");
    plat.addColorStop(inFrac,                  toRgba(accentColor, 0.34));
    plat.addColorStop(0.72,                    toRgba(accentColor, 0.20));
    plat.addColorStop(0.90,                    toRgba(glowColor,   0.17));
    plat.addColorStop(1,                       toRgba(accentColor, 0.32));
    ctx.fillStyle = plat;
    ctx.beginPath();
    ctx.arc(0, 0, outerR, 0, Math.PI * 2);
    ctx.fill();

    // clip to the platter disc for grooves + spinning features
    ctx.save();
    ctx.beginPath();
    ctx.arc(0, 0, outerR, 0, Math.PI * 2);
    ctx.clip();

    // ── Record grooves — concentric rings (static; circles look same spun) ──
    var grooveCount = Math.floor((outerR - innerR) / 2.2);
    for (var g = 0; g < grooveCount; g++) {
        var gr = innerR + 2 + g * 2.2;
        ctx.strokeStyle = (g % 2 === 0) ? toRgba(LD, 0.22)
                                        : toRgba(LB, 0.10);
        ctx.lineWidth = 0.7;
        ctx.beginPath();
        ctx.arc(0, 0, gr, 0, Math.PI * 2);
        ctx.stroke();
    }

    // ── Rotating features ──
    ctx.rotate(rotationDeg * Math.PI / 180);

    // radial leading panels (stained-glass division of the platter)
    var panels = 12;
    ctx.strokeStyle = toRgba(LB, 0.28);
    ctx.lineWidth = 0.7;
    for (var i = 0; i < panels; i++) {
        var a = (i / panels) * Math.PI * 2;
        ctx.beginPath();
        ctx.moveTo(Math.cos(a) * innerR, Math.sin(a) * innerR);
        ctx.lineTo(Math.cos(a) * outerR, Math.sin(a) * outerR);
        ctx.stroke();
    }

    // inlaid orbiting jewels at a mid radius
    var midR = (innerR + outerR) / 2;
    for (var k = 0; k < 6; k++) {
        var ka = (k / 6) * Math.PI * 2;
        var jx = Math.cos(ka) * midR;
        var jy = Math.sin(ka) * midR;
        var jg = ctx.createRadialGradient(jx, jy, 0, jx, jy, 3);
        jg.addColorStop(0, toRgba(glowColor, 0.95));
        jg.addColorStop(1, toRgba(accentColor, 0.10));
        ctx.fillStyle = jg;
        ctx.beginPath();
        ctx.arc(jx, jy, 2.1, 0, Math.PI * 2);
        ctx.fill();
    }

    // two reflecting shine wedges (light catching the spinning glass)
    for (var w = 0; w < 2; w++) {
        var c0 = w * Math.PI;          // 0 and 180 degrees
        ctx.beginPath();
        ctx.arc(0, 0, outerR, c0 - 0.22, c0 + 0.22, false);
        ctx.arc(0, 0, innerR, c0 + 0.22, c0 - 0.22, true);
        ctx.closePath();
        ctx.fillStyle = toRgba(glowColor, 0.14);
        ctx.fill();
        // bright centre streak
        ctx.strokeStyle = "rgba(255,245,215,0.30)";
        ctx.lineWidth = 1.2;
        ctx.beginPath();
        ctx.moveTo(Math.cos(c0) * innerR, Math.sin(c0) * innerR);
        ctx.lineTo(Math.cos(c0) * outerR, Math.sin(c0) * outerR);
        ctx.stroke();
    }

    ctx.restore(); // drop clip + rotation

    // ── Leaded rims ──
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.1;
    ctx.beginPath();
    ctx.arc(0, 0, outerR, 0, Math.PI * 2);
    ctx.stroke();
    ctx.strokeStyle = toRgba(LM, 0.8);
    ctx.lineWidth = 0.8;
    ctx.beginPath();
    ctx.arc(0, 0, innerR, 0, Math.PI * 2);
    ctx.stroke();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// TONEARM — Art Nouveau record arm whose headshell is a night-blooming
// flower bud; the needle is the point where the bud kisses the groove.
// The arm tracks playback: it sweeps slowly inward as frac goes 0→1,
// exactly like a turntable arm riding toward the label. A soft moonlit
// glow blooms at the needle (brighter while playing).
//   platInnerR / platOuterR — the record platter band (from paintRecordRing)
//   frac     — playback fraction 0..1 (drives the arm's inward sweep)
//   playing  — bool (needle glow + bud bloom intensify)
// ═══════════════════════════════════════════════════════════════
function paintTonearm(ctx, cx, cy, platInnerR, platOuterR, frac, playing, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    if (frac < 0) frac = 0; if (frac > 1) frac = 1;
    ctx.save();

    // pivot mount — upper-right, just outside the rose frame
    var pa = -0.50;
    var pr = platOuterR + 16;
    var pivotX = cx + Math.cos(pa) * pr;
    var pivotY = cy + Math.sin(pa) * pr;

    // needle contact point — sweeps inward with playback
    var ca = -1.15;
    var contactR = (platOuterR - 6) - ((platOuterR - 6) - (platInnerR + 6)) * frac;
    var contactX = cx + Math.cos(ca) * contactR;
    var contactY = cy + Math.sin(ca) * contactR;

    // bud sits a little back up the arm from the contact point
    var dx = contactX - pivotX, dy = contactY - pivotY;
    var dlen = Math.sqrt(dx*dx + dy*dy) || 1;
    var ux = dx / dlen, uy = dy / dlen;
    var budLen = 17;
    var budX = contactX - ux * budLen;
    var budY = contactY - uy * budLen;
    var aimAngle = Math.atan2(contactY - budY, contactX - budX);

    // ── the arm: whiplash stem from pivot to bud (dark under, gold over) ──
    var mx = (pivotX + budX) / 2 + uy * 14;   // bow the stem to one side
    var my = (pivotY + budY) / 2 - ux * 14;
    ctx.lineCap = "round";
    ctx.strokeStyle = LD;
    ctx.lineWidth = 4.4;
    ctx.beginPath();
    ctx.moveTo(pivotX, pivotY);
    ctx.quadraticCurveTo(mx, my, budX, budY);
    ctx.stroke();
    ctx.strokeStyle = LM;
    ctx.lineWidth = 3.0;
    ctx.beginPath();
    ctx.moveTo(pivotX, pivotY);
    ctx.quadraticCurveTo(mx, my, budX, budY);
    ctx.stroke();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.0;
    ctx.beginPath();
    ctx.moveTo(pivotX, pivotY);
    ctx.quadraticCurveTo(mx, my, budX, budY);
    ctx.stroke();

    // a small leaf midway along the stem
    var lfx = (pivotX + mx) / 2, lfy = (pivotY + my) / 2;
    ctx.save();
    ctx.translate(lfx, lfy);
    ctx.rotate(aimAngle + 0.7);
    ctx.fillStyle = "rgba(42, 74, 58, 0.9)";
    ctx.strokeStyle = toRgba(LB, 0.7);
    ctx.lineWidth = 0.6;
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.quadraticCurveTo(7, -3, 12, 0);
    ctx.quadraticCurveTo(7, 3, 0, 0);
    ctx.closePath();
    ctx.fill(); ctx.stroke();
    ctx.restore();

    // ── pivot mount — ornate calyx + jewel ──
    var pmg = ctx.createRadialGradient(pivotX - 2, pivotY - 2, 0, pivotX, pivotY, 9);
    pmg.addColorStop(0, "rgba(253, 233, 179, 1)");
    pmg.addColorStop(0.5, LM);
    pmg.addColorStop(1, LD);
    ctx.fillStyle = pmg;
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.8;
    ctx.beginPath();
    ctx.arc(pivotX, pivotY, 7, 0, Math.PI * 2);
    ctx.fill(); ctx.stroke();
    // little sepals around the pivot
    ctx.strokeStyle = toRgba(LB, 0.8);
    ctx.lineWidth = 0.8;
    for (var p = 0; p < 6; p++) {
        var sa = (p / 6) * Math.PI * 2;
        ctx.beginPath();
        ctx.moveTo(pivotX + Math.cos(sa) * 7, pivotY + Math.sin(sa) * 7);
        ctx.lineTo(pivotX + Math.cos(sa) * 11, pivotY + Math.sin(sa) * 11);
        ctx.stroke();
    }
    ctx.fillStyle = toRgba(accentColor, 0.95);
    ctx.beginPath();
    ctx.arc(pivotX, pivotY, 2.4, 0, Math.PI * 2);
    ctx.fill();

    // ── needle contact glow (the music point) ──
    var ng = ctx.createRadialGradient(contactX, contactY, 0, contactX, contactY, playing ? 9 : 5);
    ng.addColorStop(0, "rgba(255, 244, 210, " + (playing ? 0.95 : 0.6) + ")");
    ng.addColorStop(0.5, toRgba(glowColor, playing ? 0.55 : 0.3));
    ng.addColorStop(1, toRgba(glowColor, 0));
    ctx.fillStyle = ng;
    ctx.beginPath();
    ctx.arc(contactX, contactY, playing ? 9 : 5, 0, Math.PI * 2);
    ctx.fill();

    // ── the lily-trumpet headshell ──
    drawLilyTrumpet(ctx, budX, budY, aimAngle, 13, playing, accentColor, glowColor, leadingColor);

    // fine gold needle from bud tip to the groove
    var tipX = budX + ux * budLen * 0.7;
    var tipY = budY + uy * budLen * 0.7;
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.1;
    ctx.beginPath();
    ctx.moveTo(tipX, tipY);
    ctx.lineTo(contactX, contactY);
    ctx.stroke();
    ctx.fillStyle = "rgba(255, 246, 220, 1)";
    ctx.beginPath();
    ctx.arc(contactX, contactY, 1.5, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
}

// Night-blooming flower bud — layered luminous teardrop petals around a
// spiralled core, pointing along `angle` (tip toward the needle/groove).
// Reads as a closed rosebud AND a moonflower: pale glass petals, gold
// leading, soft moonlit bloom that intensifies while playing.
function drawNightBud(ctx, x, y, angle, size, playing, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    ctx.save();
    ctx.translate(x, y);
    ctx.rotate(angle);          // local +X points toward the contact/needle

    // moonlit halo
    var halo = ctx.createRadialGradient(0, 0, 0, 0, 0, size * 1.9);
    halo.addColorStop(0, toRgba(glowColor, playing ? 0.45 : 0.26));
    halo.addColorStop(1, toRgba(glowColor, 0));
    ctx.fillStyle = halo;
    ctx.beginPath();
    ctx.arc(0, 0, size * 1.9, 0, Math.PI * 2);
    ctx.fill();

    // calyx (sepals) at the back of the bud, where it meets the stem
    ctx.fillStyle = "rgba(42, 74, 58, 0.95)";
    ctx.strokeStyle = toRgba(LB, 0.7);
    ctx.lineWidth = 0.6;
    for (var sgn = -1; sgn <= 1; sgn += 2) {
        ctx.beginPath();
        ctx.moveTo(-size * 0.9, 0);
        ctx.quadraticCurveTo(-size * 0.4, sgn * size * 0.7, size * 0.1, sgn * size * 0.35);
        ctx.quadraticCurveTo(-size * 0.4, sgn * size * 0.2, -size * 0.9, 0);
        ctx.closePath();
        ctx.fill(); ctx.stroke();
    }

    // outer petals (two side wraps) — pale luminous glass
    for (var s2 = -1; s2 <= 1; s2 += 2) {
        var pg = ctx.createLinearGradient(-size * 0.6, 0, size, 0);
        pg.addColorStop(0, toRgba(accentColor, 0.55));
        pg.addColorStop(0.6, toRgba(glowColor, 0.55));
        pg.addColorStop(1, "rgba(255, 248, 228, 0.9)");
        ctx.fillStyle = pg;
        ctx.strokeStyle = toRgba(LB, 0.8);
        ctx.lineWidth = 0.7;
        ctx.beginPath();
        ctx.moveTo(-size * 0.7, 0);
        ctx.quadraticCurveTo(-size * 0.1, s2 * size * 0.72, size * 1.0, s2 * size * 0.16);
        ctx.quadraticCurveTo(size * 1.18, 0, size * 1.0, s2 * size * 0.16);
        ctx.quadraticCurveTo(-size * 0.1, s2 * size * 0.30, -size * 0.7, 0);
        ctx.closePath();
        ctx.fill(); ctx.stroke();
    }

    // central petal — the closed spire, brightest (catching moonlight)
    var cg = ctx.createLinearGradient(-size * 0.6, 0, size * 1.15, 0);
    cg.addColorStop(0, toRgba(accentColor, 0.6));
    cg.addColorStop(0.55, toRgba(glowColor, 0.7));
    cg.addColorStop(1, "rgba(255, 250, 235, 1)");
    ctx.fillStyle = cg;
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.8;
    ctx.beginPath();
    ctx.moveTo(-size * 0.6, 0);
    ctx.quadraticCurveTo(0, size * 0.42, size * 1.15, 0);
    ctx.quadraticCurveTo(0, -size * 0.42, -size * 0.6, 0);
    ctx.closePath();
    ctx.fill(); ctx.stroke();

    // central seam + a tiny dewdrop jewel at the heart
    ctx.strokeStyle = toRgba(LB, 0.6);
    ctx.lineWidth = 0.5;
    ctx.beginPath();
    ctx.moveTo(-size * 0.4, 0);
    ctx.lineTo(size * 0.9, 0);
    ctx.stroke();
    ctx.fillStyle = "rgba(255, 246, 220, 1)";
    ctx.beginPath();
    ctx.arc(size * 0.1, 0, 1.4, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
}

// Lily-trumpet headshell — a flared trumpet-lily flower whose throat
// narrows to the needle point (local +X). The bell mouth opens back
// toward the arm; the throat glows like a little gramophone horn (music
// pours from the bloom), brighter while playing. Reads as calla/trumpet
// lily: flared scalloped rim, gold veins, a stamen with a jewel anther.
function drawLilyTrumpet(ctx, x, y, angle, size, playing, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    ctx.save();
    ctx.translate(x, y);
    ctx.rotate(angle);                 // +X -> needle/throat; -X -> bell mouth

    var bx = -size * 0.75;             // bell back-rim centre
    var rimH = size * 0.95;            // bell half-height
    var tipX = size * 1.15;            // throat / needle point

    // moonlit/music halo
    var halo = ctx.createRadialGradient(bx * 0.3, 0, 0, bx * 0.3, 0, size * 2.0);
    halo.addColorStop(0, toRgba(glowColor, playing ? 0.42 : 0.22));
    halo.addColorStop(1, toRgba(glowColor, 0));
    ctx.fillStyle = halo;
    ctx.beginPath();
    ctx.arc(bx * 0.3, 0, size * 2.0, 0, Math.PI * 2);
    ctx.fill();

    // trumpet body — funnel from wide back rim to the front point
    ctx.beginPath();
    ctx.moveTo(bx, -rimH);
    ctx.quadraticCurveTo(size * 0.25, -size * 0.52, tipX, 0);
    ctx.quadraticCurveTo(size * 0.25, size * 0.52, bx, rimH);
    ctx.quadraticCurveTo(bx - size * 0.16, 0, bx, -rimH);
    ctx.closePath();
    var body = ctx.createLinearGradient(bx, 0, tipX, 0);
    body.addColorStop(0, toRgba(accentColor, 0.5));
    body.addColorStop(0.55, toRgba(glowColor, 0.55));
    body.addColorStop(1, "rgba(255, 250, 236, 0.96)");
    ctx.fillStyle = body;
    ctx.fill();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.8;
    ctx.stroke();

    // trumpet veins
    ctx.strokeStyle = toRgba(LB, 0.45);
    ctx.lineWidth = 0.5;
    var veins = [-0.55, -0.2, 0.2, 0.55];
    for (var v = 0; v < veins.length; v++) {
        ctx.beginPath();
        ctx.moveTo(bx, rimH * veins[v]);
        ctx.quadraticCurveTo(size * 0.3, size * 0.36 * veins[v], tipX * 0.94, 0);
        ctx.stroke();
    }

    // lily frill — 3 recurved tepal tips at the bell rim
    ctx.fillStyle = toRgba(glowColor, 0.55);
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.6;
    var tips = [-1, 0, 1];
    for (var tp = 0; tp < tips.length; tp++) {
        var ty = rimH * 0.84 * tips[tp];
        var txx = bx + (tips[tp] === 0 ? -size * 0.05 : size * 0.02);
        ctx.beginPath();
        ctx.moveTo(txx, ty);
        ctx.quadraticCurveTo(bx - size * 0.42, ty + tips[tp] * size * 0.22, bx - size * 0.55, ty + tips[tp] * size * 0.02);
        ctx.quadraticCurveTo(bx - size * 0.28, ty, txx, ty);
        ctx.closePath();
        ctx.fill(); ctx.stroke();
    }

    // throat opening (the glowing mouth) — ellipse at the back rim
    ctx.save();
    ctx.translate(bx, 0);
    ctx.save();
    ctx.scale(size * 0.20, rimH * 0.92);
    ctx.beginPath();
    ctx.arc(0, 0, 1, 0, Math.PI * 2);
    ctx.restore();
    var tg = ctx.createRadialGradient(0, 0, 0, 0, 0, rimH * 0.92);
    tg.addColorStop(0, "rgba(255, 248, 226, " + (playing ? 0.95 : 0.7) + ")");
    tg.addColorStop(0.5, toRgba(glowColor, 0.5));
    tg.addColorStop(1, toRgba(LD, 0.65));
    ctx.fillStyle = tg;
    ctx.fill();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.7;
    ctx.stroke();
    ctx.restore();

    // stamen — gold filament with a jewel anther rising from the throat
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.moveTo(bx + size * 0.1, 0);
    ctx.quadraticCurveTo(size * 0.25, -size * 0.16, size * 0.55, -size * 0.08);
    ctx.stroke();
    var ag = ctx.createRadialGradient(size * 0.55, -size * 0.08, 0, size * 0.55, -size * 0.08, 3);
    ag.addColorStop(0, "rgba(255, 232, 170, 1)");
    ag.addColorStop(1, toRgba(accentColor, 0.2));
    ctx.fillStyle = ag;
    ctx.beginPath();
    ctx.arc(size * 0.55, -size * 0.08, 2, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// DISC (spinning leaded-glass medallion — accent-tinted, NOT black)
// ═══════════════════════════════════════════════════════════════
function paintDisc(ctx, cx, cy, radius, rotationDeg, accentColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(rotationDeg * Math.PI / 180);

    var rim = ctx.createRadialGradient(0, 0, radius * 0.3, 0, 0, radius);
    rim.addColorStop(0,    toRgba(accentColor, 0.55));
    rim.addColorStop(0.55, toRgba(accentColor, 0.30));
    rim.addColorStop(1,    toRgba(accentColor, 0.12));
    ctx.fillStyle = rim;
    ctx.beginPath();
    ctx.arc(0, 0, radius - 1, 0, Math.PI * 2);
    ctx.fill();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1;
    ctx.stroke();

    ctx.strokeStyle = toRgba(LB, 0.18);
    ctx.lineWidth = 0.3;
    for (var i = 0; i < 8; i++) {
        var r = radius - 5 - i * (radius * 0.06);
        if (r > 0) {
            ctx.beginPath();
            ctx.arc(0, 0, r, 0, Math.PI * 2);
            ctx.stroke();
        }
    }

    // Sheen
    ctx.save();
    ctx.rotate(-Math.PI / 8);
    var sh = ctx.createLinearGradient(-radius * 0.6, 0, radius * 0.6, 0);
    sh.addColorStop(0,   "rgba(255, 255, 255, 0)");
    sh.addColorStop(0.5, "rgba(255, 255, 255, 0.15)");
    sh.addColorStop(1,   "rgba(255, 255, 255, 0)");
    ctx.fillStyle = sh;
    ctx.beginPath();
    ctx.ellipse(0, 0, radius * 0.7, radius * 0.15, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();

    // Medallion centre
    var medR = radius * 0.45;
    var med = ctx.createRadialGradient(-medR * 0.2, -medR * 0.2, 0, 0, 0, medR);
    med.addColorStop(0,   toRgba(accentColor, 0.90));
    med.addColorStop(0.7, toRgba(accentColor, 0.55));
    med.addColorStop(1,   toRgba(accentColor, 0.30));
    ctx.fillStyle = med;
    ctx.beginPath();
    ctx.arc(0, 0, medR, 0, Math.PI * 2);
    ctx.fill();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.8;
    ctx.stroke();

    ctx.strokeStyle = toRgba(LB, 0.5);
    ctx.lineWidth = 0.5;
    ctx.beginPath();
    ctx.moveTo(-medR, 0); ctx.lineTo(medR, 0);
    ctx.moveTo(0, -medR); ctx.lineTo(0, medR);
    ctx.stroke();

    ctx.fillStyle = LB;
    ctx.strokeStyle = LD;
    ctx.lineWidth = 0.4;
    ctx.beginPath();
    ctx.arc(0, 0, 2.5, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// PETAL RING (audio-reactive bloom)
// bloom 0..1 — synth envelope from track-position tick + slow breath.
// t = elapsed time seconds (slow rotation of the whole ring).
// ═══════════════════════════════════════════════════════════════
function paintPetals(ctx, cx, cy, innerR, outerR, t, bloom, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    var count = 18;
    var baseAngle = t * 0.08;
    ctx.save();

    for (var i = 0; i < count; i++) {
        var a = baseAngle + (i / count) * Math.PI * 2;
        var phase = Math.sin(t * 1.4 + i * 0.7);
        var reactive = bloom * 0.7 + (phase * 0.5 + 0.5) * bloom * 0.4;
        var len = (outerR - innerR) * (0.60 + reactive * 0.50);
        var hw  = ((outerR - innerR) * 0.18) * (0.85 + reactive * 0.40);
        var r0  = innerR + (outerR - innerR) * 0.04;

        var ux = Math.cos(a), uy = Math.sin(a);
        var px = Math.cos(a + Math.PI / 2), py = Math.sin(a + Math.PI / 2);
        // point at radius rr, lateral offset ww
        function PX(rr, ww) { return cx + ux * rr + px * ww; }
        function PY(rr, ww) { return cy + uy * rr + py * ww; }

        var bX = PX(r0, 0),           bY = PY(r0, 0);            // base
        var tX = PX(r0 + len, 0),     tY = PY(r0 + len, 0);      // pointed tip
        // lotus shoulders: wide around 22%..80%, pinched base, sharp tip
        var Lc1X = PX(r0 + len * 0.22, hw),      Lc1Y = PY(r0 + len * 0.22, hw);
        var Lc2X = PX(r0 + len * 0.80, hw * 0.9),Lc2Y = PY(r0 + len * 0.80, hw * 0.9);
        var Rc2X = PX(r0 + len * 0.80, -hw * 0.9),Rc2Y = PY(r0 + len * 0.80, -hw * 0.9);
        var Rc1X = PX(r0 + len * 0.22, -hw),     Rc1Y = PY(r0 + len * 0.22, -hw);

        ctx.beginPath();
        ctx.moveTo(bX, bY);
        ctx.bezierCurveTo(Lc1X, Lc1Y, Lc2X, Lc2Y, tX, tY);   // left shoulder → tip
        ctx.bezierCurveTo(Rc2X, Rc2Y, Rc1X, Rc1Y, bX, bY);   // tip → right shoulder → base
        ctx.closePath();

        // lotus colouring: deeper at the base, luminous toward the tip
        var grad = ctx.createLinearGradient(bX, bY, tX, tY);
        grad.addColorStop(0,    toRgba(accentColor, 0.55 + reactive * 0.25));
        grad.addColorStop(0.55, toRgba(glowColor,   0.42 + reactive * 0.22));
        grad.addColorStop(1,    "rgba(255, 248, 230, " + (0.5 + reactive * 0.4) + ")");
        ctx.fillStyle = grad;
        ctx.fill();

        ctx.strokeStyle = toRgba(LB, 0.4 + reactive * 0.4);
        ctx.lineWidth = 0.6;
        ctx.stroke();

        // central vein (lotus ridge)
        ctx.strokeStyle = toRgba(LB, 0.3 + reactive * 0.3);
        ctx.lineWidth = 0.5;
        ctx.beginPath();
        ctx.moveTo(bX, bY);
        ctx.lineTo(PX(r0 + len * 0.62, 0), PY(r0 + len * 0.62, 0));
        ctx.stroke();

        // dew jewel at the tip on bloom
        if (reactive > 0.3) {
            ctx.fillStyle = toRgba(LB, 0.5 + reactive * 0.5);
            ctx.beginPath();
            ctx.arc(tX, tY, 0.8 + reactive * 1.3, 0, Math.PI * 2);
            ctx.fill();
        }
    }

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// TRANSPORT JEWEL  (kind: "prev"|"play"|"pause"|"next"|"stop"|"shuffle"|"repeat")
// ═══════════════════════════════════════════════════════════════
function paintJewel(ctx, cx, cy, r, kind, hover, accentColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    ctx.save();

    if (hover) {
        var hg = ctx.createRadialGradient(cx, cy, r * 0.6, cx, cy, r * 1.8);
        hg.addColorStop(0, toRgba(LB, 0.45));
        hg.addColorStop(1, toRgba(LB, 0));
        ctx.fillStyle = hg;
        ctx.beginPath();
        ctx.arc(cx, cy, r * 1.8, 0, Math.PI * 2);
        ctx.fill();
    }

    var bg = ctx.createRadialGradient(cx - r * 0.3, cy - r * 0.3, 0, cx, cy, r);
    bg.addColorStop(0,   hover ? toRgba(LB, 0.6) : toRgba(accentColor, 0.65));
    bg.addColorStop(0.6, toRgba(accentColor, 0.40));
    bg.addColorStop(1,   toRgba(accentColor, 0.20));
    ctx.fillStyle = bg;
    ctx.beginPath();
    ctx.arc(cx, cy, r, 0, Math.PI * 2);
    ctx.fill();

    ctx.strokeStyle = hover ? LB : LM;
    ctx.lineWidth = 0.8;
    ctx.stroke();

    ctx.fillStyle = LB;
    var s = r * 0.42;
    if (kind === "play") {
        ctx.beginPath();
        ctx.moveTo(cx - s * 0.45, cy - s);
        ctx.lineTo(cx + s * 0.85, cy);
        ctx.lineTo(cx - s * 0.45, cy + s);
        ctx.closePath();
        ctx.fill();
    } else if (kind === "pause") {
        ctx.fillRect(cx - s * 0.55, cy - s, s * 0.35, s * 2);
        ctx.fillRect(cx + s * 0.20, cy - s, s * 0.35, s * 2);
    } else if (kind === "prev") {
        ctx.fillRect(cx - s, cy - s, s * 0.30, s * 2);
        ctx.beginPath();
        ctx.moveTo(cx + s, cy - s);
        ctx.lineTo(cx - s * 0.4, cy);
        ctx.lineTo(cx + s, cy + s);
        ctx.closePath();
        ctx.fill();
    } else if (kind === "next") {
        ctx.fillRect(cx + s * 0.70, cy - s, s * 0.30, s * 2);
        ctx.beginPath();
        ctx.moveTo(cx - s, cy - s);
        ctx.lineTo(cx + s * 0.4, cy);
        ctx.lineTo(cx - s, cy + s);
        ctx.closePath();
        ctx.fill();
    } else if (kind === "stop") {
        ctx.fillRect(cx - s * 0.7, cy - s * 0.7, s * 1.4, s * 1.4);
    } else if (kind === "shuffle") {
        ctx.strokeStyle = LB;
        ctx.lineWidth = 1.1;
        ctx.beginPath();
        ctx.moveTo(cx - s, cy - s * 0.5);
        ctx.bezierCurveTo(cx - s * 0.2, cy - s * 0.5, cx + s * 0.2, cy + s * 0.5, cx + s, cy + s * 0.5);
        ctx.moveTo(cx - s, cy + s * 0.5);
        ctx.bezierCurveTo(cx - s * 0.2, cy + s * 0.5, cx + s * 0.2, cy - s * 0.5, cx + s, cy - s * 0.5);
        ctx.stroke();
    } else if (kind === "repeat") {
        ctx.strokeStyle = LB;
        ctx.lineWidth = 1.1;
        ctx.beginPath();
        ctx.arc(cx, cy, s * 0.85, Math.PI * 0.2, Math.PI * 1.8);
        ctx.stroke();
        ctx.beginPath();
        ctx.moveTo(cx + s * 0.7, cy - s * 0.6);
        ctx.lineTo(cx + s * 0.95, cy - s * 0.15);
        ctx.lineTo(cx + s * 0.45, cy - s * 0.15);
        ctx.closePath();
        ctx.fill();
    }

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// BRASS HORN — small gramophone horn flourish (top-right ornament)
// ═══════════════════════════════════════════════════════════════
function paintHorn(ctx, cx, cy, scale, accentColor) {
    ctx.save();
    ctx.translate(cx, cy);
    ctx.scale(scale, scale);

    // Bell shadow
    ctx.fillStyle = LEADING_DEEP;
    ctx.beginPath();
    ctx.ellipse(-2, -2, 26, 26, 0, 0, Math.PI * 2);
    ctx.fill();

    // Bell brass
    var brass = ctx.createRadialGradient(-10, -14, 0, 0, 0, 36);
    brass.addColorStop(0,   "rgba(253, 233, 179, 1)");
    brass.addColorStop(0.4, LEADING_BRIGHT);
    brass.addColorStop(0.85, LEADING_DEEP);
    brass.addColorStop(1,   "rgba(58, 40, 6, 1)");
    ctx.fillStyle = brass;
    ctx.strokeStyle = LEADING_DEEP;
    ctx.lineWidth = 0.8;
    ctx.beginPath();
    ctx.arc(0, 0, 25, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();

    // Stained-glass insert
    var ins = ctx.createRadialGradient(0, 0, 0, 0, 0, 20);
    ins.addColorStop(0,   toRgba(accentColor, 0.7));
    ins.addColorStop(0.7, toRgba(accentColor, 0.45));
    ins.addColorStop(1,   toRgba(accentColor, 0.20));
    ctx.fillStyle = ins;
    ctx.beginPath();
    ctx.arc(0, 0, 19, 0, Math.PI * 2);
    ctx.fill();

    // Radial leading
    ctx.strokeStyle = toRgba(LEADING_BRIGHT, 0.7);
    ctx.lineWidth = 0.7;
    for (var i = 0; i < 8; i++) {
        var a = (i / 8) * Math.PI * 2;
        ctx.beginPath();
        ctx.moveTo(Math.cos(a) * 4, Math.sin(a) * 4);
        ctx.lineTo(Math.cos(a) * 19, Math.sin(a) * 19);
        ctx.stroke();
    }
    ctx.strokeStyle = LEADING_BRIGHT;
    ctx.lineWidth = 1;
    ctx.beginPath();
    ctx.arc(0, 0, 19, 0, Math.PI * 2);
    ctx.stroke();

    // Neck — narrowing tube going down-right
    ctx.fillStyle = brass;
    ctx.strokeStyle = LEADING_DEEP;
    ctx.lineWidth = 0.6;
    ctx.beginPath();
    ctx.moveTo(18, 12);
    ctx.quadTo(26, 22, 24, 32);
    ctx.lineTo(16, 36);
    ctx.quadTo(14, 24, 12, 16);
    ctx.closePath();
    ctx.fill();
    ctx.stroke();

    // Sparkle
    ctx.fillStyle = "rgba(255, 240, 200, 0.55)";
    ctx.beginPath();
    ctx.arc(-8, -10, 3, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// VFD DISPLAY PANEL (dark recessed glass with amber readout)
// Lines are pre-formatted strings; this function just paints them.
// font(s) come from theme via the .qml file passing fontSpec strings.
// ═══════════════════════════════════════════════════════════════
function paintVFDPanel(ctx, x, y, w, h, line1, line2, sub, fontFixed) {
    ctx.save();

    // Recessed glass body
    var body = ctx.createLinearGradient(x, y, x, y + h);
    body.addColorStop(0,   "rgba(12, 10, 24, 0.85)");
    body.addColorStop(0.5, "rgba(20, 16, 38, 0.78)");
    body.addColorStop(1,   "rgba(8, 6, 18, 0.85)");
    ctx.fillStyle = body;
    roundRectPath(ctx, x, y, w, h, 4);
    ctx.fill();

    // Gold leaded frame
    ctx.strokeStyle = LEADING;
    ctx.lineWidth = 1;
    roundRectPath(ctx, x + 0.5, y + 0.5, w - 1, h - 1, 4);
    ctx.stroke();
    ctx.strokeStyle = LEADING_BRIGHT;
    ctx.lineWidth = 0.5;
    roundRectPath(ctx, x + 1.5, y + 1.5, w - 3, h - 3, 3);
    ctx.stroke();

    // Ghost VFD grid (faint amber dots — segment display feel)
    ctx.fillStyle = VFD_AMBER_DIM;
    var dot = 1;
    for (var dy = y + 4; dy < y + h - 3; dy += 4) {
        for (var dx = x + 4; dx < x + w - 3; dx += 4) {
            ctx.fillRect(dx, dy, dot, dot);
        }
    }

    // Amber recessed text — main line
    if (line1) {
        ctx.font = "600 13px " + (fontFixed || "monospace");
        ctx.textBaseline = "top";
        ctx.fillStyle = "rgba(0, 0, 0, 0.6)";
        ctx.fillText(line1, x + 9, y + 7);  // shadow
        ctx.fillStyle = VFD_AMBER;
        ctx.shadowColor = VFD_AMBER;
        ctx.shadowBlur = 4;
        ctx.fillText(line1, x + 8, y + 6);
        ctx.shadowBlur = 0;
    }

    // Smaller secondary
    if (line2) {
        ctx.font = "500 10px " + (fontFixed || "monospace");
        ctx.fillStyle = "rgba(0, 0, 0, 0.5)";
        ctx.fillText(line2, x + 9, y + 25);
        ctx.fillStyle = "rgba(248, 184, 80, 0.85)";
        ctx.shadowColor = VFD_AMBER;
        ctx.shadowBlur = 3;
        ctx.fillText(line2, x + 8, y + 24);
        ctx.shadowBlur = 0;
    }

    // Right-aligned sub (time, bitrate)
    if (sub) {
        ctx.font = "600 10px " + (fontFixed || "monospace");
        ctx.textAlign = "right";
        ctx.fillStyle = "rgba(0, 0, 0, 0.5)";
        ctx.fillText(sub, x + w - 7, y + 25);
        ctx.fillStyle = VFD_AMBER;
        ctx.shadowColor = VFD_AMBER;
        ctx.shadowBlur = 3;
        ctx.fillText(sub, x + w - 8, y + 24);
        ctx.shadowBlur = 0;
        ctx.textAlign = "left";
    }

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// EQUALISER BARS — 10 stained-glass bars, synth-animated by bloom + phase
// ═══════════════════════════════════════════════════════════════
function paintEqBars(ctx, x, y, w, h, t, bloom, accentColor, glowColor) {
    var bars = 10;
    var pad = 2;
    var bw = (w - pad * (bars + 1)) / bars;
    ctx.save();

    for (var i = 0; i < bars; i++) {
        // Each bar phase
        var ph = Math.sin(t * 3.0 + i * 0.9) * 0.5 + 0.5;
        var ph2 = Math.sin(t * 1.7 + i * 1.3) * 0.5 + 0.5;
        var hgt = h * (0.15 + (ph * 0.6 + ph2 * 0.3) * (0.35 + bloom * 0.8));
        if (hgt > h - 2) hgt = h - 2;
        if (hgt < 2) hgt = 2;
        var bx = x + pad + i * (bw + pad);
        var by = y + h - hgt;

        // Bar — stained-glass gradient
        var g = ctx.createLinearGradient(bx, by, bx, by + hgt);
        g.addColorStop(0,   toRgba(LEADING_BRIGHT, 0.95));
        g.addColorStop(0.4, toRgba(accentColor, 0.75));
        g.addColorStop(1,   toRgba(glowColor, 0.45));
        ctx.fillStyle = g;
        ctx.fillRect(bx, by, bw, hgt);

        // Leaded edges
        ctx.strokeStyle = toRgba(LEADING, 0.7);
        ctx.lineWidth = 0.5;
        ctx.strokeRect(bx + 0.25, by + 0.25, bw - 0.5, hgt - 0.5);

        // Peak cap
        ctx.fillStyle = LEADING_BRIGHT;
        ctx.fillRect(bx, by - 1, bw, 1);
    }

    // Baseline shelf
    ctx.strokeStyle = toRgba(LEADING_DEEP, 0.6);
    ctx.lineWidth = 0.5;
    ctx.beginPath();
    ctx.moveTo(x, y + h);
    ctx.lineTo(x + w, y + h);
    ctx.stroke();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// VOLUME VINE — horizontal slider with amber jewel head, fancier than scrubber
// ═══════════════════════════════════════════════════════════════
function paintVolumeVine(ctx, x, y, w, frac, accentColor) {
    if (frac < 0) frac = 0;
    if (frac > 1) frac = 1;
    ctx.save();

    // Vine baseline (subtle curve)
    ctx.strokeStyle = toRgba(LEADING_DEEP, 0.65);
    ctx.lineWidth = 2;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(x, y);
    ctx.bezierCurveTo(x + w * 0.3, y - 2, x + w * 0.7, y + 2, x + w, y);
    ctx.stroke();

    // Filled portion in gold
    var fillX = x + w * frac;
    var fg = ctx.createLinearGradient(x, y, fillX, y);
    fg.addColorStop(0, LEADING_DEEP);
    fg.addColorStop(1, LEADING_BRIGHT);
    ctx.strokeStyle = fg;
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(x, y);
    ctx.bezierCurveTo(
        x + (fillX - x) * 0.3, y - 2,
        x + (fillX - x) * 0.7, y + 2,
        fillX, y
    );
    ctx.stroke();

    // Tick marks (musical staff feel)
    var ticks = 10;
    for (var i = 0; i < ticks; i++) {
        var tx = x + (i / (ticks - 1)) * w;
        ctx.strokeStyle = toRgba(LEADING, 0.4);
        ctx.lineWidth = 0.5;
        ctx.beginPath();
        ctx.moveTo(tx, y - 4);
        ctx.lineTo(tx, y - 6);
        ctx.stroke();
    }

    // Tiny leaves at endpoints
    ctx.fillStyle = toRgba(LEADING, 0.7);
    ctx.beginPath();
    ctx.ellipse(x - 4, y, 3, 1.5, -0.6, 0, Math.PI * 2);
    ctx.fill();
    ctx.beginPath();
    ctx.ellipse(x + w + 4, y, 3, 1.5, 0.6, 0, Math.PI * 2);
    ctx.fill();

    // Amber jewel at frac position
    var jg = ctx.createRadialGradient(fillX - 1, y - 1, 0, fillX, y, 5);
    jg.addColorStop(0, "rgba(255, 230, 170, 1)");
    jg.addColorStop(0.5, LEADING);
    jg.addColorStop(1, LEADING_DEEP);
    ctx.fillStyle = jg;
    ctx.strokeStyle = LEADING_BRIGHT;
    ctx.lineWidth = 0.5;
    ctx.beginPath();
    ctx.arc(fillX, y, 4, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// FILIGREE DIVIDER — horizontal art-nouveau divider with side curls
// ═══════════════════════════════════════════════════════════════
function paintFiligreeRow(ctx, x, y, w, accentColor) {
    ctx.save();
    var cx = x + w / 2;

    // Hairline
    var g = ctx.createLinearGradient(x, y, x + w, y);
    g.addColorStop(0,   "rgba(74, 50, 8, 0)");
    g.addColorStop(0.5, LEADING_BRIGHT);
    g.addColorStop(1,   "rgba(74, 50, 8, 0)");
    ctx.strokeStyle = g;
    ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.moveTo(x, y); ctx.lineTo(x + w, y);
    ctx.stroke();

    // Side curls
    ctx.strokeStyle = toRgba(LEADING_BRIGHT, 0.7);
    ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.moveTo(cx - 8, y);
    ctx.quadTo(cx - 22, y - 6, cx - 36, y);
    ctx.quadTo(cx - 50, y + 6, cx - 58, y);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(cx + 8, y);
    ctx.quadTo(cx + 22, y - 6, cx + 36, y);
    ctx.quadTo(cx + 50, y + 6, cx + 58, y);
    ctx.stroke();

    // Center medallion
    ctx.fillStyle = toRgba(accentColor, 0.9);
    ctx.strokeStyle = LEADING_BRIGHT;
    ctx.lineWidth = 0.7;
    ctx.beginPath();
    ctx.arc(cx, y, 5, 0, Math.PI * 2);
    ctx.fill(); ctx.stroke();
    ctx.fillStyle = "rgba(255, 230, 170, 1)";
    ctx.beginPath();
    ctx.arc(cx, y, 1.6, 0, Math.PI * 2);
    ctx.fill();

    // Outer dots
    ctx.fillStyle = "rgba(255, 230, 170, 0.85)";
    ctx.beginPath();
    ctx.arc(cx - 70, y, 1.2, 0, Math.PI * 2);
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx + 70, y, 1.2, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// CARTOUCHE — ornate text frame for titles
// ═══════════════════════════════════════════════════════════════
function paintCartouche(ctx, x, y, w, h, text, fontFamily) {
    ctx.save();

    // Frame — flattened ellipse-ish rounded
    roundRectPath(ctx, x, y, w, h, h * 0.45);
    var bg = ctx.createLinearGradient(x, y, x, y + h);
    bg.addColorStop(0,   "rgba(20, 16, 44, 0.65)");
    bg.addColorStop(1,   "rgba(10, 8, 24, 0.55)");
    ctx.fillStyle = bg;
    ctx.fill();
    ctx.strokeStyle = LEADING_BRIGHT;
    ctx.lineWidth = 0.9;
    ctx.stroke();

    // Inner dark line
    roundRectPath(ctx, x + 2, y + 2, w - 4, h - 4, (h - 4) * 0.45);
    ctx.strokeStyle = toRgba(LEADING_DEEP, 0.7);
    ctx.lineWidth = 0.5;
    ctx.stroke();

    // Side end-jewels
    ctx.fillStyle = LEADING_BRIGHT;
    ctx.beginPath();
    ctx.arc(x + 6, y + h / 2, 2, 0, Math.PI * 2);
    ctx.fill();
    ctx.beginPath();
    ctx.arc(x + w - 6, y + h / 2, 2, 0, Math.PI * 2);
    ctx.fill();

    // Text
    if (text) {
        ctx.font = "600 " + Math.round(h * 0.5) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        ctx.fillStyle = LEADING_BRIGHT;
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.shadowColor = LEADING_DEEP;
        ctx.shadowBlur = 2;
        ctx.fillText(text, x + w / 2, y + h / 2 + 1);
        ctx.shadowBlur = 0;
        ctx.textAlign = "left";
        ctx.textBaseline = "alphabetic";
    }

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// IRIS  — vertical Mucha iris ornament (stem + 3 petals)
// ═══════════════════════════════════════════════════════════════
function paintIris(ctx, cx, baseY, size, accentColor) {
    ctx.save();
    ctx.translate(cx, baseY);
    var s = size / 60;
    ctx.scale(s, s);

    // Stem
    ctx.strokeStyle = "rgba(42, 74, 58, 1)";
    ctx.lineWidth = 1.6;
    ctx.beginPath();
    ctx.moveTo(0, 0); ctx.quadTo(-2, -20, 0, -45);
    ctx.stroke();

    // Falls (drooping)
    ctx.fillStyle = toRgba(accentColor, 0.85);
    ctx.strokeStyle = LEADING_BRIGHT;
    ctx.lineWidth = 0.7;
    ctx.beginPath();
    ctx.moveTo(0, -45);
    ctx.quadTo(-22, -38, -22, -22);
    ctx.quadTo(-10, -28, 0, -32);
    ctx.closePath();
    ctx.fill(); ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(0, -45);
    ctx.quadTo(22, -38, 22, -22);
    ctx.quadTo(10, -28, 0, -32);
    ctx.closePath();
    ctx.fill(); ctx.stroke();

    // Standards (upright)
    ctx.fillStyle = toRgba(accentColor, 0.95);
    ctx.beginPath();
    ctx.moveTo(0, -45);
    ctx.quadTo(-14, -60, -16, -78);
    ctx.quadTo(-6, -72, 0, -60);
    ctx.closePath();
    ctx.fill(); ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(0, -45);
    ctx.quadTo(14, -60, 16, -78);
    ctx.quadTo(6, -72, 0, -60);
    ctx.closePath();
    ctx.fill(); ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(0, -45);
    ctx.quadTo(-4, -68, 0, -88);
    ctx.quadTo(4, -68, 0, -45);
    ctx.closePath();
    ctx.fill(); ctx.stroke();

    // Center beard
    ctx.fillStyle = "rgba(244, 204, 107, 1)";
    ctx.beginPath();
    ctx.arc(0, -47, 2, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// CREST — symmetric crown finial (sits above arches / cartouches)
// ═══════════════════════════════════════════════════════════════
function paintCrest(ctx, cx, baseY, width, accentColor) {
    ctx.save();
    ctx.translate(cx, baseY);
    var s = width / 110;
    ctx.scale(s, s);

    // Leafy crown
    ctx.fillStyle = "rgba(42, 74, 58, 0.92)";
    ctx.strokeStyle = LEADING_BRIGHT;
    ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.quadTo(-25, -10, -43, -4);
    ctx.quadTo(-33, -20, -15, -22);
    ctx.quadTo(-27, -32, -23, -46);
    ctx.quadTo(-11, -38, 0, -28);
    ctx.quadTo(11, -38, 23, -46);
    ctx.quadTo(27, -32, 15, -22);
    ctx.quadTo(33, -20, 43, -4);
    ctx.quadTo(25, -10, 0, 0);
    ctx.closePath();
    ctx.fill(); ctx.stroke();

    // Central bud
    ctx.fillStyle = toRgba(accentColor, 0.95);
    ctx.beginPath();
    ctx.ellipse(0, -10, 5, 12, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();

    // Descending tendrils
    ctx.strokeStyle = LEADING_BRIGHT;
    ctx.lineWidth = 0.7;
    ctx.beginPath();
    ctx.moveTo(-43, -4); ctx.quadTo(-50, 8, -38, 14);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(43, -4); ctx.quadTo(50, 8, 38, 14);
    ctx.stroke();

    // End jewels
    ctx.fillStyle = "rgba(244, 204, 107, 1)";
    ctx.beginPath(); ctx.arc(-38, 14, 1.8, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc( 38, 14, 1.8, 0, Math.PI * 2); ctx.fill();

    ctx.restore();
}

// ── Rounded-rect path helper ───────────────────────────────────
function roundRectPath(ctx, x, y, w, h, r) {
    if (r > w / 2) r = w / 2;
    if (r > h / 2) r = h / 2;
    ctx.beginPath();
    ctx.moveTo(x + r, y);
    ctx.lineTo(x + w - r, y);
    ctx.quadraticCurveTo(x + w, y, x + w, y + r);
    ctx.lineTo(x + w, y + h - r);
    ctx.quadraticCurveTo(x + w, y + h, x + w - r, y + h);
    ctx.lineTo(x + r, y + h);
    ctx.quadraticCurveTo(x, y + h, x, y + h - r);
    ctx.lineTo(x, y + r);
    ctx.quadraticCurveTo(x, y, x + r, y);
    ctx.closePath();
}
