// mucha-space.js — consolidated Mucha space-scene painter library for NCDE.
// Replaces the old family (mucha-scene/orrery/earth/clouds/cities/sun/moon/
// grain/palette). Pure Canvas 2D, .pragma library, transparent background.
// Leaded gold + zodiac gems hardcoded per CLAUDE.md "Mucha art JS" exemption;
// sky/aurora/jewels follow accentColor / glowColor from ncde.*.
//
// The QML (SpaceWidget2.qml) computes astronomy + animation phase and passes a
// single `st` state object into drawMuchaSpace(). All sub-painters are exported
// too in case you want to compose differently.
//
// drawMuchaSpace(ctx, W, H, st, accentColor, glowColor)
//   st = {
//     t,            // elapsed seconds (animation clock)
//     brightness,   // 0..1 sky brightness (day) — drives sky + star fade
//     starOpacity,  // 0..1
//     earthRot,     // degrees — Earth surface rotation
//     cloudRot,     // degrees — cloud layer rotation
//     zodiacRot,    // degrees — slow zodiac ring rotation
//     sunAngle,     // degrees on the ring (-90 = top/noon); null if below horizon
//     moonAngle,    // degrees on the ring; null if below horizon
//     moonPhase,    // 0..1 (0=new, 0.5=full)
//     activeSign,   // 0..11 zodiac index to highlight (or -1)
//     location,     // string for banner
//     dateText,     // string for banner
//     showBorder,   // bool — Mucha arch border
//     showBanner    // bool
//   }
.pragma library
.import "ncde-ink.js" as Ink   // wallpaper ink: text + lit digits re-inked (2026-09-24)
.import "ncde-color.js" as Col // Earth glass takes the Iris palette (2026-09-25)
.import "mucha-earth-land.js" as Land   // true coastlines (2026-09-25)

var LEADING_BRIGHT = "rgba(240, 210, 122, 1.0)";
var LEADING        = "rgba(184, 138, 50, 1.0)";
var LEADING_DEEP   = "rgba(74, 50, 8, 1.0)";

// Traditional zodiac birthstone gem colours (Aries…Pisces)
var ZODIAC_GEM = [
    "#c0392b", "#2ecc71", "#f5f5f5", "#e74c3c", "#b7e778", "#3498db",
    "#e8d5b0", "#f1c40f", "#1abc9c", "#8e2f2f", "#9b59b6", "#7fd8d8"
];
// Astrological glyphs (Noto Sans Symbols renders these)
var ZODIAC_GLYPH = ["♈","♉","♊","♋","♌","♍","♎","♏","♐","♑","♒","♓"];

function toRgba(c, a) {
    if (a === undefined) a = 1;
    if (typeof c !== "string") {
        return "rgba(" + Math.round(c.r*255) + "," + Math.round(c.g*255) + ","
                       + Math.round(c.b*255) + "," + a + ")";
    }
    if (c.charAt(0) === "#" && c.length === 7) {
        return "rgba(" + parseInt(c.substring(1,3),16) + ","
                       + parseInt(c.substring(3,5),16) + ","
                       + parseInt(c.substring(5,7),16) + "," + a + ")";
    }
    return c;
}

// ── Deterministic PRNG so the star field is stable frame-to-frame ──
function seededRng(seed) {
    var s = seed % 2147483647;
    if (s <= 0) s += 2147483646;
    return function () { s = (s * 16807) % 2147483647; return (s - 1) / 2147483646; };
}

// QML-safe ellipse — Qt's Canvas 2D has no ellipsePath(ctx, ). Bake the ellipse
// into the current path via translate/scale/arc so fills AND strokes work
// (stroke width stays uniform because stroke happens after restore).
// Call exactly like ellipsePath(ctx, ): caller does beginPath() before, fill/stroke after.
function ellipsePath(ctx, cx, cy, rx, ry, rot, a0, a1, ccw) {
    ctx.save();
    ctx.translate(cx, cy);
    if (rot) ctx.rotate(rot);
    ctx.scale(rx, ry);
    ctx.arc(0, 0, 1, (a0 === undefined ? 0 : a0),
                     (a1 === undefined ? Math.PI*2 : a1), ccw || false);
    ctx.restore();
}

// Shared arch path — same shape as the gold Mucha border.
// Call before clip() or stroke(); caller owns save/restore.
var FOOT_R = 12;   // bottom-corner radius of the arch frame

function archPath(ctx, w, h) {
    var inset = 4;
    var archH = h * 0.18;
    ctx.beginPath();
    ctx.moveTo(inset, archH);
    ctx.quadraticCurveTo(inset, inset, w*0.16, inset + archH*0.4);
    ctx.quadraticCurveTo(w/2, inset - archH*0.25, w*0.84, inset + archH*0.4);
    ctx.quadraticCurveTo(w - inset, inset, w - inset, archH);
    // rounded foot, matching the glass frame's corners (2026-09-24)
    ctx.lineTo(w - inset, h - inset - FOOT_R);
    ctx.quadraticCurveTo(w - inset, h - inset, w - inset - FOOT_R, h - inset);
    ctx.lineTo(inset + FOOT_R, h - inset);
    ctx.quadraticCurveTo(inset, h - inset, inset, h - inset - FOOT_R);
    ctx.closePath();
}

// ═══════════════════════════════════════════════════════════════
// SKY — deep gradient + twin nebulae. Brightness lifts it toward dusk.
// ═══════════════════════════════════════════════════════════════
function paintSky(ctx, w, h, brightness, accentColor, glowColor) {
    ctx.save();
    archPath(ctx, w, h);
    ctx.clip();
    var b = brightness || 0;
    var g = ctx.createLinearGradient(0, 0, 0, h);
    // night base → dusk lift
    g.addColorStop(0,   "rgba(" + Math.round(6 + b*30) + "," + Math.round(8 + b*20) + "," + Math.round(26 + b*40) + ",0.82)");
    g.addColorStop(0.5, "rgba(" + Math.round(10 + b*40) + "," + Math.round(10 + b*30) + "," + Math.round(40 + b*40) + ",0.82)");
    g.addColorStop(1,   "rgba(" + Math.round(8 + b*50) + "," + Math.round(16 + b*40) + "," + Math.round(34 + b*30) + ",0.82)");
    ctx.fillStyle = g;
    ctx.fillRect(0, 0, w, h);
    // nebulae
    var n1 = ctx.createRadialGradient(w*0.72, h*0.20, 0, w*0.72, h*0.20, w*0.4);
    n1.addColorStop(0, toRgba(accentColor, 0.16));
    n1.addColorStop(1, "rgba(0,0,0,0)");
    ctx.fillStyle = n1; ctx.fillRect(0, 0, w, h);
    var n2 = ctx.createRadialGradient(w*0.20, h*0.62, 0, w*0.20, h*0.62, w*0.34);
    n2.addColorStop(0, toRgba(glowColor, 0.13));
    n2.addColorStop(1, "rgba(0,0,0,0)");
    ctx.fillStyle = n2; ctx.fillRect(0, 0, w, h);
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// STARS — stable twinkling field + diffraction spikes on a few + a
// periodic shooting star that streaks across.
// ═══════════════════════════════════════════════════════════════
function paintStars(ctx, w, h, t, starOpacity) {
    ctx.save();
    var op = starOpacity === undefined ? 1 : starOpacity;
    var rng = seededRng(1337);
    var count = 90;
    for (var i = 0; i < count; i++) {
        var x = rng() * w;
        var y = rng() * h * 0.8;
        var base = 0.3 + rng() * 0.7;
        var tw = 0.5 + 0.5 * Math.sin(t * (0.6 + rng()*1.6) + i);
        var r = 0.4 + rng() * 1.3;
        ctx.globalAlpha = base * tw * op;
        ctx.fillStyle = "rgba(220, 228, 255, 1)";
        ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.fill();
        // diffraction spike on the brightest
        if (r > 1.4) {
            ctx.strokeStyle = "rgba(230, 236, 255, " + (base*tw*op*0.5) + ")";
            ctx.lineWidth = 0.4;
            ctx.beginPath();
            ctx.moveTo(x - 3, y); ctx.lineTo(x + 3, y);
            ctx.moveTo(x, y - 3); ctx.lineTo(x, y + 3);
            ctx.stroke();
        }
    }
    ctx.globalAlpha = 1;

    // Shooting star — one every ~9s, streaks over ~0.8s
    var period = 9.0;
    var local = t % period;
    if (local < 0.8) {
        var p = local / 0.8;
        var seed = Math.floor(t / period);
        var sr = seededRng(seed * 97 + 3);
        var sx = sr() * w * 0.6;
        var sy = sr() * h * 0.4;
        var len = 40 + sr() * 30;
        var ang = Math.PI * (0.15 + sr() * 0.15);
        var hx = sx + Math.cos(ang) * p * (w * 0.5);
        var hy = sy + Math.sin(ang) * p * (w * 0.5);
        var tailX = hx - Math.cos(ang) * len;
        var tailY = hy - Math.sin(ang) * len;
        var grad = ctx.createLinearGradient(tailX, tailY, hx, hy);
        grad.addColorStop(0, "rgba(255,240,200,0)");
        grad.addColorStop(1, "rgba(255,245,215," + (1 - p) + ")");
        ctx.strokeStyle = grad;
        ctx.lineWidth = 1.4;
        ctx.beginPath(); ctx.moveTo(tailX, tailY); ctx.lineTo(hx, hy); ctx.stroke();
        ctx.fillStyle = "rgba(255,248,220," + (1 - p) + ")";
        ctx.beginPath(); ctx.arc(hx, hy, 1.6, 0, Math.PI*2); ctx.fill();
    }
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// AURORA — slow shimmering ribbons across the upper sky.
// ═══════════════════════════════════════════════════════════════
function paintAurora(ctx, w, h, t, accentColor, glowColor) {
    ctx.save();
    ctx.globalCompositeOperation = "lighter";
    for (var band = 0; band < 3; band++) {
        var yBase = h * (0.14 + band * 0.08);
        var amp = 10 + band * 6;
        var col = band % 2 === 0 ? glowColor : accentColor;
        var grad = ctx.createLinearGradient(0, yBase - 26, 0, yBase + 26);
        grad.addColorStop(0, "rgba(0,0,0,0)");
        grad.addColorStop(0.5, toRgba(col, 0.10 + 0.04*Math.sin(t*0.5 + band)));
        grad.addColorStop(1, "rgba(0,0,0,0)");
        ctx.fillStyle = grad;
        ctx.beginPath();
        ctx.moveTo(0, yBase);
        for (var x = 0; x <= w; x += 12) {
            var y = yBase + Math.sin(x*0.02 + t*(0.4 + band*0.15) + band) * amp
                          + Math.sin(x*0.05 - t*0.3) * (amp*0.4);
            ctx.lineTo(x, y);
        }
        ctx.lineTo(w, yBase + 30);
        ctx.lineTo(0, yBase + 30);
        ctx.closePath();
        ctx.fill();
    }
    ctx.restore();
}

// ── Hand-drawn Canvas zodiac glyphs (no font dependency) ───────
// drawZodiacGlyph(ctx, i, x, y, s, color) — i = 0..11 (Aries..Pisces).
// s ≈ half-height in px. Pure stroke paths so they inherit gold leading.
function drawZodiacGlyph(ctx, i, x, y, s, color) {
    ctx.save();
    ctx.translate(x, y);
    ctx.strokeStyle = color;
    ctx.lineWidth = 1.2;
    ctx.lineCap = "round";
    ctx.lineJoin = "round";
    ctx.fillStyle = color;
    switch (i) {
    case 0: // Aries — two outward curling horns
        ctx.beginPath();
        ctx.moveTo(0, s);
        ctx.bezierCurveTo(0, -s*0.2, -s, -s*0.2, -s, -s*0.7);
        ctx.bezierCurveTo(-s, -s*1.1, -s*0.4, -s*1.1, -s*0.4, -s*0.6);
        ctx.moveTo(0, s);
        ctx.bezierCurveTo(0, -s*0.2, s, -s*0.2, s, -s*0.7);
        ctx.bezierCurveTo(s, -s*1.1, s*0.4, -s*1.1, s*0.4, -s*0.6);
        ctx.stroke();
        break;
    case 1: // Taurus — circle with crescent on top
        ctx.beginPath(); ctx.arc(0, s*0.35, s*0.6, 0, Math.PI*2); ctx.stroke();
        ctx.beginPath(); ctx.arc(0, -s*0.5, s*0.7, Math.PI*1.05, Math.PI*1.95, false); ctx.stroke();
        break;
    case 2: // Gemini — two bars with top & bottom connectors
        ctx.beginPath();
        ctx.moveTo(-s*0.5, -s); ctx.lineTo(-s*0.5, s);
        ctx.moveTo(s*0.5, -s);  ctx.lineTo(s*0.5, s);
        ctx.moveTo(-s*0.8, -s); ctx.lineTo(s*0.8, -s);
        ctx.moveTo(-s*0.8, s);  ctx.lineTo(s*0.8, s);
        ctx.stroke();
        break;
    case 3: // Cancer — two linked circles+tails (69)
        ctx.beginPath(); ctx.arc(-s*0.3, -s*0.3, s*0.28, 0, Math.PI*2); ctx.stroke();
        ctx.beginPath(); ctx.arc(s*0.3, s*0.3, s*0.28, 0, Math.PI*2); ctx.stroke();
        ctx.beginPath();
        ctx.moveTo(-s*0.55, -s*0.3); ctx.bezierCurveTo(-s, -s*0.3, -s, s*0.6, s*0.05, s*0.55);
        ctx.moveTo(s*0.55, s*0.3);   ctx.bezierCurveTo(s, s*0.3, s, -s*0.6, -s*0.05, -s*0.55);
        ctx.stroke();
        break;
    case 4: // Leo — small circle with looping mane tail
        ctx.beginPath(); ctx.arc(-s*0.35, s*0.35, s*0.32, 0, Math.PI*2); ctx.stroke();
        ctx.beginPath();
        ctx.moveTo(-s*0.05, s*0.5);
        ctx.bezierCurveTo(s*0.4, s*0.5, s*0.4, -s*0.6, 0, -s*0.6);
        ctx.bezierCurveTo(-s*0.5, -s*0.6, -s*0.3, s*0.1, s*0.1, -s*0.05);
        ctx.bezierCurveTo(s*0.5, -s*0.2, s*0.7, s*0.3, s*0.6, s*0.7);
        ctx.stroke();
        break;
    case 5: // Virgo — M with an inward loop
        ctx.beginPath();
        ctx.moveTo(-s*0.8, s); ctx.lineTo(-s*0.8, -s*0.6);
        ctx.bezierCurveTo(-s*0.8, -s, -s*0.3, -s, -s*0.3, -s*0.6);
        ctx.lineTo(-s*0.3, s*0.4);
        ctx.moveTo(-s*0.3, -s*0.6);
        ctx.bezierCurveTo(-s*0.3, -s, s*0.2, -s, s*0.2, -s*0.6);
        ctx.lineTo(s*0.2, s*0.4);
        ctx.moveTo(s*0.2, -s*0.6);
        ctx.bezierCurveTo(s*0.2, -s, s*0.7, -s, s*0.7, -s*0.5);
        ctx.bezierCurveTo(s*0.7, s*0.2, s*0.2, s*0.3, s*0.55, s);
        ctx.stroke();
        break;
    case 6: // Libra — half-sun over a line
        ctx.beginPath(); ctx.moveTo(-s, s*0.55); ctx.lineTo(s, s*0.55); ctx.stroke();
        ctx.beginPath(); ctx.moveTo(-s, s*0.1); ctx.lineTo(-s*0.4, s*0.1); ctx.stroke();
        ctx.beginPath(); ctx.arc(0, s*0.1, s*0.42, Math.PI, 0, true); ctx.stroke();
        ctx.beginPath(); ctx.moveTo(s*0.4, s*0.1); ctx.lineTo(s, s*0.1); ctx.stroke();
        break;
    case 7: // Scorpio — M with an arrow tail
        ctx.beginPath();
        ctx.moveTo(-s*0.85, s); ctx.lineTo(-s*0.85, -s*0.6);
        ctx.bezierCurveTo(-s*0.85, -s, -s*0.4, -s, -s*0.4, -s*0.6);
        ctx.lineTo(-s*0.4, s*0.4);
        ctx.moveTo(-s*0.4, -s*0.6);
        ctx.bezierCurveTo(-s*0.4, -s, s*0.05, -s, s*0.05, -s*0.6);
        ctx.lineTo(s*0.05, s*0.4);
        ctx.moveTo(s*0.05, -s*0.6);
        ctx.bezierCurveTo(s*0.05, -s, s*0.5, -s, s*0.5, -s*0.6);
        ctx.lineTo(s*0.5, s*0.6);
        ctx.lineTo(s, s);                      // arrow shaft
        ctx.moveTo(s, s); ctx.lineTo(s*0.6, s);
        ctx.moveTo(s, s); ctx.lineTo(s, s*0.55);
        ctx.stroke();
        break;
    case 8: // Sagittarius — arrow with crossbar
        ctx.beginPath();
        ctx.moveTo(-s*0.8, s*0.8); ctx.lineTo(s*0.7, -s*0.7);
        ctx.moveTo(s*0.7, -s*0.7); ctx.lineTo(s*0.15, -s*0.7);
        ctx.moveTo(s*0.7, -s*0.7); ctx.lineTo(s*0.7, -s*0.15);
        ctx.moveTo(-s*0.15, s*0.05); ctx.lineTo(s*0.2, s*0.45);
        ctx.stroke();
        break;
    case 9: // Capricorn — V joining a looped circle (sea-goat)
        ctx.beginPath();
        ctx.moveTo(-s*0.8, -s*0.6);
        ctx.lineTo(-s*0.2, s*0.5);
        ctx.lineTo(s*0.1, -s*0.5);
        ctx.bezierCurveTo(s*0.3, -s, s*0.7, -s*0.8, s*0.7, -s*0.2);
        ctx.bezierCurveTo(s*0.7, s*0.4, s*0.1, s*0.4, s*0.2, -s*0.1);
        ctx.stroke();
        break;
    case 10: // Aquarius — two zigzag waves
        for (var wv = 0; wv < 2; wv++) {
            var yy = -s*0.25 + wv * s*0.55;
            ctx.beginPath();
            ctx.moveTo(-s, yy);
            ctx.lineTo(-s*0.5, yy - s*0.3);
            ctx.lineTo(0, yy);
            ctx.lineTo(s*0.5, yy - s*0.3);
            ctx.lineTo(s, yy);
            ctx.stroke();
        }
        break;
    case 11: // Pisces — two arcs joined by a bar
        ctx.beginPath(); ctx.arc(-s*0.7, 0, s*0.7, Math.PI*1.5, Math.PI*0.5, true); ctx.stroke();
        ctx.beginPath(); ctx.arc(s*0.7, 0, s*0.7, Math.PI*0.5, Math.PI*1.5, true); ctx.stroke();
        ctx.beginPath(); ctx.moveTo(-s*0.55, 0); ctx.lineTo(s*0.55, 0); ctx.stroke();
        break;
    }
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// ZODIAC ORRERY RING — outer leaded ring, 12 gem stations + glyphs,
// slow rotation. activeSign glows.
// ═══════════════════════════════════════════════════════════════
function paintOrreryRing(ctx, cx, cy, R, rotationDeg, activeSign, accentColor, glowColor, leadingColor) {
    ctx.save();
    var rot = rotationDeg * Math.PI / 180;
    var LB = leadingColor || LEADING_BRIGHT;

    // Outer + inner leaded rings
    ctx.strokeStyle = LB; ctx.lineWidth = 1.5;
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2); ctx.stroke();
    ctx.strokeStyle = toRgba(leadingColor || LEADING_DEEP, 0.7); ctx.lineWidth = 0.5;
    ctx.beginPath(); ctx.arc(cx, cy, R - 2, 0, Math.PI*2); ctx.stroke();
    ctx.strokeStyle = toRgba(LB, 0.55); ctx.lineWidth = 1;
    ctx.beginPath(); ctx.arc(cx, cy, R - 22, 0, Math.PI*2); ctx.stroke();

    // Tick spokes between stations
    ctx.strokeStyle = toRgba(LB, 0.35); ctx.lineWidth = 0.6;
    for (var s = 0; s < 24; s++) {
        var ta = rot + (s / 24) * Math.PI*2;
        ctx.beginPath();
        ctx.moveTo(cx + Math.cos(ta)*(R-22), cy + Math.sin(ta)*(R-22));
        ctx.lineTo(cx + Math.cos(ta)*(R-2),  cy + Math.sin(ta)*(R-2));
        ctx.stroke();
    }

    // 12 gem stations + hand-drawn glyphs
    for (var i = 0; i < 12; i++) {
        var a = rot + (i / 12) * Math.PI*2 - Math.PI/2;
        var gx = cx + Math.cos(a) * (R - 12);
        var gy = cy + Math.sin(a) * (R - 12);
        var active = (i === activeSign);
        var gemR = active ? 5.5 : 3.2;
        if (active) {
            var halo = ctx.createRadialGradient(gx, gy, 0, gx, gy, 14);
            halo.addColorStop(0, toRgba(ZODIAC_GEM[i], 0.8));
            halo.addColorStop(1, "rgba(0,0,0,0)");
            ctx.fillStyle = halo;
            ctx.beginPath(); ctx.arc(gx, gy, 14, 0, Math.PI*2); ctx.fill();
        }
        var gg = ctx.createRadialGradient(gx-1, gy-1, 0, gx, gy, gemR);
        gg.addColorStop(0, active ? "rgba(255,255,255,1)" : toRgba(ZODIAC_GEM[i], 0.9));
        gg.addColorStop(1, toRgba(ZODIAC_GEM[i], active ? 0.85 : 0.5));
        ctx.fillStyle = gg;
        ctx.strokeStyle = LB; ctx.lineWidth = 0.6;
        ctx.beginPath(); ctx.arc(gx, gy, gemR, 0, Math.PI*2); ctx.fill(); ctx.stroke();

        // hand-drawn glyph just inside the gem
        var lx = cx + Math.cos(a) * (R - 32);
        var ly = cy + Math.sin(a) * (R - 32);
        var glyphCol = active ? LB : toRgba(LB, 0.55);
        if (active) { ctx.save(); ctx.shadowColor = toRgba(ZODIAC_GEM[i], 0.9); ctx.shadowBlur = 5; }
        drawZodiacGlyph(ctx, i, lx, ly, 5, glyphCol);
        if (active) ctx.restore();
    }
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// EARTH — globe with continents, rotating surface, drifting clouds,
// night-side city lights and a day/night terminator.
// ═══════════════════════════════════════════════════════════════
// ── Earth as leaded glass (2026-09-25) ──────────────────────────────────
// The continents used to be eight rotating ellipses. They are now the real
// coastlines (mucha-earth-land.js, Natural Earth 1:110m) on an orthographic
// globe that turns with the same earthRot as before — no motion added or
// retuned. Land, desert and ice are separate glass pieces set in lead came
// (dark lead + a thin gilt centre line, like MotifFrame's came); the ocean
// carries a leaded graticule. Every colour comes from the Iris palette:
// land from verd, desert from gilt3, ocean + air pulled toward the accent,
// ice toward the glow (operator: Iris is universal).
var EARTH_TILT = 12 * Math.PI / 180;   // view latitude: a little of the north, where most land is
var _rad = Math.PI / 1800;              // tenths of a degree -> radians
var _land = null;                       // per-ring point tables, built once
var _desert = null;
var _water = null;

// City lights at real cities (lon, lat), not scattered over the sea.
var CITIES = [
    -74,40.7, -118.2,34, -87.6,41.9, -89.6,40.7, -79.4,43.7, -99.1,19.4, -46.6,-23.5, -58.4,-34.6,
    -77,-12, -74,4.7, -0.1,51.5, 2.35,48.9, -3.7,40.4, 13.4,52.5, 12.5,41.9, 37.6,55.8, 29,41,
    31.2,30, 3.4,6.5, 15.3,-4.3, 28,-26.2, 36.8,-1.3, 51.4,35.7, 46.7,24.7, 67,24.9, 77.2,28.6,
    72.9,19, 88.4,22.6, 90.4,23.8, 100.5,13.8, 106.8,-6.2, 121,14.6, 116.4,39.9, 121.5,31.2,
    114.2,22.3, 127,37.6, 139.7,35.7, 135.5,34.7, 151.2,-33.9, 145,-37.8, -43.2,-22.9, 30.5,50.5
];

function _table(flat, scale) {
    var n = flat.length / 2, t = { n: n, lam: [], sp: [], cp: [], seam: [], x: [], y: [], z: [] };
    for (var i = 0; i < n; i++) {
        var lo = flat[2*i] * scale, la = flat[2*i+1] * scale;
        t.lam.push(lo); t.sp.push(Math.sin(la)); t.cp.push(Math.cos(la));
        t.seam.push(Math.abs(flat[2*i]) * scale >= Math.PI * 0.9997);   // the ±180° cut Natural Earth makes
        t.x.push(0); t.y.push(0); t.z.push(0);
    }
    return t;
}
function _earthPrep() {
    if (_land) return;
    _land = [];
    for (var r = 0; r < Land.RINGS.length; r++) {
        var t = _table(Land.RINGS[r], _rad); t.ice = Land.ICE[r]; _land.push(t);
    }
    _desert = [];
    for (var d = 0; d < Land.DESERT.length; d++) _desert.push(_table(Land.DESERT[d], _rad));
    _water = [];
    for (var w = 0; w < Land.WATER.length; w++) _water.push(_table(Land.WATER[w], _rad));
}
// Orthographic projection; points on the far side are laid on the limb so a
// piece that turns over the edge stays a closed shape.
function _project(t, lam0, cx, cy, R) {
    var s0 = Math.sin(EARTH_TILT), c0 = Math.cos(EARTH_TILT), any = false;
    for (var i = 0; i < t.n; i++) {
        var dl = t.lam[i] - lam0, cd = Math.cos(dl);
        var x = t.cp[i] * Math.sin(dl);
        var y = c0 * t.sp[i] - s0 * t.cp[i] * cd;
        var z = s0 * t.sp[i] + c0 * t.cp[i] * cd;
        if (z < 0) { var m = Math.sqrt(x*x + y*y) || 1; x /= m; y /= m; } else any = true;
        t.x[i] = cx + R * x; t.y[i] = cy - R * y; t.z[i] = z;
    }
    return any;
}
// Canvas calls are the cost here, not the maths: a point within PX_STEP of the
// last one drawn is skipped (sub-pixel at orrery size), which also thins the
// crowded points near the limb and on the far side.
var PX_STEP2 = 0.9 * 0.9;
function _fillPath(ctx, t) {
    var lx = t.x[0], ly = t.y[0];
    ctx.moveTo(lx, ly);
    for (var i = 1; i < t.n; i++) {
        var dx = t.x[i] - lx, dy = t.y[i] - ly;
        if (dx*dx + dy*dy < PX_STEP2) continue;
        lx = t.x[i]; ly = t.y[i]; ctx.lineTo(lx, ly);
    }
    ctx.closePath();
}
// Coastline only: no came along the ±180° cut or along the limb.
function _coastPath(ctx, t) {
    var pen = false, lx = 0, ly = 0;
    for (var k = 1; k <= t.n; k++) {
        var i = k - 1, j = k % t.n;
        var skip = (t.z[i] < 0 && t.z[j] < 0) || (t.seam[i] && t.seam[j]);
        if (skip) { if (pen && (lx !== t.x[i] || ly !== t.y[i])) ctx.lineTo(t.x[i], t.y[i]); pen = false; continue; }
        if (!pen) { lx = t.x[i]; ly = t.y[i]; ctx.moveTo(lx, ly); pen = true; }
        var dx = t.x[j] - lx, dy = t.y[j] - ly;
        if (dx*dx + dy*dy < PX_STEP2 && k < t.n) continue;
        lx = t.x[j]; ly = t.y[j]; ctx.lineTo(lx, ly);
    }
}
var _earthCol = { key: "" };
function _earthColors(accent, glow, lead, pal) {
    var verd = (pal && pal.verd) ? pal.verd : "#4f8a50";
    var gilt = (pal && pal.gilt3) ? pal.gilt3 : "#c8a45c";
    var key = [Col.hex(accent), Col.hex(glow), String(lead), Col.hex(verd), Col.hex(gilt)].join("|");
    if (_earthCol.key === key) return _earthCol;
    var sea = "#2f6aa8";
    _earthCol = {
        key: key,
        sea0: Col.css(Col.harmonize(sea, accent, 56, 30, 0.1)),
        sea1: Col.css(Col.harmonize(sea, accent, 32, 34, 0.1)),
        sea2: Col.css(Col.harmonize(sea, accent, 12, 22, 0.1)),
        land0: Col.css(Col.harmonize("#4f8a50", verd, 64, 36, 0.7)),
        land1: Col.css(Col.harmonize("#4f8a50", verd, 48, 34, 0.7)),
        land2: Col.css(Col.harmonize("#4f8a50", verd, 30, 26, 0.7)),
        sand0: Col.css(Col.harmonize("#c8a45c", gilt, 76, 40, 0.6)),
        sand1: Col.css(Col.harmonize("#c8a45c", gilt, 60, 38, 0.6)),
        ice0: Col.css(Col.harmonize("#e8f0fa", glow, 96, 5, 0.5)),
        ice1: Col.css(Col.harmonize("#e8f0fa", glow, 82, 8, 0.5)),
        leadDark: Col.css(Col.tone(lead, 16, 18), 0.95),
        came: Col.css(lead, 0.8),
        grat: Col.css(lead, 0.22),
        air: Col.harmonize("#78befe", accent, 76, 34, 0.1),
        city: Col.css(Col.harmonize("#ffdc96", gilt, 90, 40, 0.4))
    };
    return _earthCol;
}
function _glassFill(ctx, cx, cy, R, c0, c1, c2) {
    var g = ctx.createRadialGradient(cx - R*0.35, cy - R*0.4, R*0.05, cx, cy, R*1.05);
    g.addColorStop(0, c0); g.addColorStop(0.55, c1); g.addColorStop(1, c2 || c1);
    return g;
}
function _graticule(ctx, lam0, cx, cy, R) {
    var s0 = Math.sin(EARTH_TILT), c0 = Math.cos(EARTH_TILT);
    function seg(pts) {
        var pen = false;
        for (var i = 0; i < pts.length; i += 2) {
            var dl = pts[i] - lam0, sp = Math.sin(pts[i+1]), cp = Math.cos(pts[i+1]), cd = Math.cos(dl);
            var z = s0 * sp + c0 * cp * cd;
            if (z < 0) { pen = false; continue; }
            var x = cx + R * cp * Math.sin(dl), y = cy - R * (c0 * sp - s0 * cp * cd);
            if (pen) ctx.lineTo(x, y); else { ctx.moveTo(x, y); pen = true; }
        }
    }
    var d = Math.PI / 180, lo, la, p;
    ctx.beginPath();
    for (lo = -180; lo < 180; lo += 30) { p = []; for (la = -80; la <= 80; la += 5) p.push(lo*d, la*d); seg(p); }
    for (la = -60; la <= 60; la += 30) { p = []; for (lo = -180; lo <= 180; lo += 5) p.push(lo*d, la*d); seg(p); }
    ctx.stroke();
}

function paintEarth(ctx, cx, cy, R, earthRot, cloudRot, sunAngleDeg, accentColor, glowColor, leadingColor, pal) {
    ctx.save();
    var LB = leadingColor || LEADING_BRIGHT;

    _earthPrep();
    var EC = _earthColors(accentColor, glowColor, LB, pal);
    var lam0 = -(earthRot % 360) * Math.PI / 180;   // surface turns west -> east, as before
    var lw = Math.max(1, R * 0.03);

    // Ocean: one glass sphere, lit from the upper left
    ctx.fillStyle = _glassFill(ctx, cx, cy, R, EC.sea0, EC.sea1, EC.sea2);
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2); ctx.fill();

    // Clip to globe for surface features
    ctx.save();
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2); ctx.clip();

    // Leaded graticule across the sea (under the land)
    ctx.strokeStyle = EC.grat; ctx.lineWidth = 0.6;
    _graticule(ctx, lam0, cx, cy, R);

    // Land glass: every visible landmass in one path, green glass then sand
    ctx.beginPath();
    var shown = [];
    for (var r = 0; r < _land.length; r++) {
        if (!_project(_land[r], lam0, cx, cy, R) || _land[r].ice) continue;
        _fillPath(ctx, _land[r]); shown.push(_land[r]);
    }
    ctx.fillStyle = _glassFill(ctx, cx, cy, R, EC.land0, EC.land1, EC.land2);
    ctx.fill();
    // Sand glass: desert pieces (cut to the coast in the data), fine came inland
    ctx.beginPath();
    for (var d = 0; d < _desert.length; d++)
        if (_project(_desert[d], lam0, cx, cy, R)) _fillPath(ctx, _desert[d]);
    ctx.fillStyle = _glassFill(ctx, cx, cy, R, EC.sand0, EC.sand1);
    ctx.fill();
    ctx.strokeStyle = EC.came; ctx.lineWidth = lw * 0.45; ctx.stroke();
    // Water set into the land: the Caspian + the great lakes, in sea glass
    ctx.beginPath();
    var wet = [];
    for (var w = 0; w < _water.length; w++)
        if (_project(_water[w], lam0, cx, cy, R)) { _fillPath(ctx, _water[w]); wet.push(_water[w]); }
    ctx.fillStyle = _glassFill(ctx, cx, cy, R, EC.sea0, EC.sea1, EC.sea2);
    ctx.fill();
    // Ice glass: Greenland + Antarctica
    ctx.beginPath();
    var iced = [];
    for (var q = 0; q < _land.length; q++)
        if (_land[q].ice && _project(_land[q], lam0, cx, cy, R)) { _fillPath(ctx, _land[q]); iced.push(_land[q]); }
    ctx.fillStyle = _glassFill(ctx, cx, cy, R, EC.ice0, EC.ice1);
    ctx.fill();

    // Lead came on every coast: dark lead, then a thin gilt centre line
    ctx.beginPath();
    for (var s = 0; s < shown.length; s++) _coastPath(ctx, shown[s]);
    for (var t2 = 0; t2 < iced.length; t2++) _coastPath(ctx, iced[t2]);
    for (var t3 = 0; t3 < wet.length; t3++) _coastPath(ctx, wet[t3]);
    ctx.lineJoin = "round"; ctx.lineCap = "round";
    ctx.strokeStyle = EC.leadDark; ctx.lineWidth = lw; ctx.stroke();
    ctx.strokeStyle = EC.came; ctx.lineWidth = lw * 0.4; ctx.stroke();

    // Night side + city lights (terminator opposite the sun angle)
    var sunA = (sunAngleDeg === null || sunAngleDeg === undefined) ? 90 : sunAngleDeg;
    var nightDir = (sunA + 180) * Math.PI / 180;
    var term = ctx.createLinearGradient(
        cx + Math.cos(nightDir + Math.PI) * R, cy + Math.sin(nightDir + Math.PI) * R,
        cx + Math.cos(nightDir) * R,            cy + Math.sin(nightDir) * R);
    term.addColorStop(0, "rgba(4, 8, 22, 0)");
    term.addColorStop(0.55, "rgba(4, 8, 22, 0.35)");
    term.addColorStop(1, "rgba(2, 4, 14, 0.85)");
    ctx.fillStyle = term;
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2); ctx.fill();

    // City lights on the night side, at real cities
    var s0 = Math.sin(EARTH_TILT), c0 = Math.cos(EARTH_TILT), dg = Math.PI / 180;
    var ndx = Math.cos(nightDir), ndy = Math.sin(nightDir);
    ctx.fillStyle = EC.city;
    for (var c = 0; c < CITIES.length; c += 2) {
        var dl = CITIES[c] * dg - lam0, la = CITIES[c+1] * dg;
        var sp = Math.sin(la), cp = Math.cos(la), cd = Math.cos(dl);
        if (s0 * sp + c0 * cp * cd < 0.05) continue;          // far side
        var ux = cp * Math.sin(dl), uy = -(c0 * sp - s0 * cp * cd);
        var dot = ux * ndx + uy * ndy;
        if (dot <= 0.1) continue;
        ctx.globalAlpha = Math.min(0.9, dot) * (0.55 + 0.45 * ((c * 37) % 10) / 10);
        ctx.beginPath(); ctx.arc(cx + ux * R, cy + uy * R, Math.max(0.7, R * 0.016), 0, Math.PI*2); ctx.fill();
    }
    ctx.globalAlpha = 1;

    // Clouds — drifting translucent swirls
    var clng = seededRng(555);
    var clon = (cloudRot % 360) / 360;
    ctx.fillStyle = "rgba(245, 248, 255, 0.5)";
    for (var m = 0; m < 7; m++) {
        var cu = ((clng() + clon) % 1);
        var cpx = cx + (cu * 2 - 1) * R;
        var cdepth = 1 - Math.abs(cu * 2 - 1);
        if (cdepth <= 0.1) continue;
        var cpy = cy + (clng() * 2 - 1) * R * 0.8;
        ctx.globalAlpha = cdepth * 0.45;
        ctx.beginPath();
        ellipsePath(ctx, cpx, cpy, R*0.22*cdepth, R*0.10*cdepth, clng(), 0, Math.PI*2);
        ctx.fill();
    }
    ctx.globalAlpha = 1;
    ctx.restore(); // unclip

    // Atmospheric rim — cyan scattering glow hugging the limb
    var atmo = ctx.createRadialGradient(cx, cy, R*0.82, cx, cy, R*1.12);
    atmo.addColorStop(0, Col.css(EC.air, 0));
    atmo.addColorStop(0.7, Col.css(EC.air, 0.18));
    atmo.addColorStop(0.9, Col.css(Col.shade(EC.air, 6), 0.30));
    atmo.addColorStop(1, Col.css(EC.air, 0));
    ctx.fillStyle = atmo;
    ctx.beginPath(); ctx.arc(cx, cy, R*1.12, 0, Math.PI*2); ctx.fill();

    // Specular sheen + leaded rim
    var sheen = ctx.createRadialGradient(cx - R*0.4, cy - R*0.4, 0, cx - R*0.4, cy - R*0.4, R*0.7);
    sheen.addColorStop(0, "rgba(255,255,255,0.22)");
    sheen.addColorStop(1, "rgba(255,255,255,0)");
    ctx.fillStyle = sheen;
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2); ctx.fill();
    ctx.strokeStyle = LB; ctx.lineWidth = 1.2;
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2); ctx.stroke();
    // glow
    ctx.strokeStyle = toRgba(glowColor, 0.4); ctx.lineWidth = 3;
    ctx.beginPath(); ctx.arc(cx, cy, R + 1.5, 0, Math.PI*2); ctx.stroke();

    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// ARMATURE + SUN / MOON riding the ring
// ═══════════════════════════════════════════════════════════════
function paintArmature(ctx, cx, cy, angleDeg, innerR, outerR, accentColor, leadingColor) {
    var a = angleDeg * Math.PI / 180;
    ctx.save();
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.strokeStyle = toRgba(LB, 0.75);
    ctx.lineWidth = 1.4;
    ctx.beginPath();
    ctx.moveTo(cx + Math.cos(a)*innerR, cy + Math.sin(a)*innerR);
    ctx.lineTo(cx + Math.cos(a)*outerR, cy + Math.sin(a)*outerR);
    ctx.stroke();
    // pivot collar
    ctx.fillStyle = LB;
    ctx.beginPath(); ctx.arc(cx + Math.cos(a)*innerR, cy + Math.sin(a)*innerR, 2, 0, Math.PI*2); ctx.fill();
    ctx.restore();
}

function paintSun(ctx, x, y, r, accentColor, glowColor, leadingColor) {
    ctx.save();
    var LB = leadingColor || LEADING_BRIGHT;
    // rays
    ctx.translate(x, y);
    for (var i = 0; i < 12; i++) {
        ctx.save(); ctx.rotate((i/12)*Math.PI*2);
        var grd = ctx.createLinearGradient(0, -r*1.1, 0, -r*1.7);
        grd.addColorStop(0, LB);
        grd.addColorStop(1, toRgba(accentColor, 0.15));
        ctx.fillStyle = grd;
        ctx.beginPath(); ctx.moveTo(-r*0.12, -r*1.12); ctx.lineTo(0, -r*1.7); ctx.lineTo(r*0.12, -r*1.12); ctx.closePath(); ctx.fill();
        ctx.restore();
    }
    ctx.translate(-x, -y);
    var g = ctx.createRadialGradient(x - r*0.3, y - r*0.3, 0, x, y, r);
    g.addColorStop(0, "rgba(255, 244, 200, 1)");
    g.addColorStop(0.55, "rgba(244, 196, 90, 1)");
    g.addColorStop(1, toRgba(accentColor, 0.7));
    ctx.fillStyle = g;
    ctx.shadowColor = "rgba(244, 200, 110, 0.9)"; ctx.shadowBlur = r;
    ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.fill();
    ctx.shadowBlur = 0;
    ctx.strokeStyle = LB; ctx.lineWidth = 1.2;
    ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.stroke();
    ctx.restore();
}

function paintMoon(ctx, x, y, r, phase, glowColor, leadingColor) {
    ctx.save();
    var LB = leadingColor || LEADING_BRIGHT;
    // full disc
    var g = ctx.createRadialGradient(x - r*0.3, y - r*0.3, 0, x, y, r);
    g.addColorStop(0, "rgba(248, 244, 224, 1)");
    g.addColorStop(0.7, "rgba(214, 206, 178, 1)");
    g.addColorStop(1, "rgba(150, 142, 120, 1)");
    ctx.fillStyle = g;
    ctx.shadowColor = toRgba(glowColor, 0.7); ctx.shadowBlur = r*0.8;
    ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.fill();
    ctx.shadowBlur = 0;
    // craters
    ctx.fillStyle = "rgba(150, 144, 120, 0.5)";
    ctx.beginPath(); ctx.arc(x - r*0.3, y - r*0.1, r*0.16, 0, Math.PI*2); ctx.fill();
    ctx.beginPath(); ctx.arc(x + r*0.2, y + r*0.3, r*0.12, 0, Math.PI*2); ctx.fill();
    ctx.beginPath(); ctx.arc(x + r*0.35, y - r*0.3, r*0.09, 0, Math.PI*2); ctx.fill();
    // phase shadow — accurate new→full illumination
    // ph: 0 new, 0.25 first quarter, 0.5 full, 0.75 last quarter, 1 new
    var ph = (phase === undefined) ? 0.5 : (phase % 1);
    if (ph < 0) ph += 1;
    var illum = (1 - Math.cos(ph * Math.PI * 2)) / 2;   // 0 new → 1 full
    var offset = illum * 2 * r;                          // shadow disc travel
    var waxing = ph < 0.5;                               // lit grows from the right
    var shadowCx = x + (waxing ? -offset : offset);
    ctx.save();
    ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.clip();
    ctx.fillStyle = "rgba(6, 8, 22, 0.9)";
    ctx.beginPath(); ctx.arc(shadowCx, y, r, 0, Math.PI*2); ctx.fill();
    ctx.restore();
    // leaded rim
    ctx.strokeStyle = LB; ctx.lineWidth = 1.1;
    ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.stroke();
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// MUCHA ARCH BORDER — botanical flourishes framing the scene
// ═══════════════════════════════════════════════════════════════
function paintArchBorder(ctx, w, h, accentColor, glowColor, leadingColor) {
    ctx.save();
    var LB = leadingColor || LEADING_BRIGHT;
    var inset = 4;
    // arched-top frame
    var archH = h * 0.18;
    ctx.beginPath();
    ctx.moveTo(inset, archH);
    ctx.quadraticCurveTo(inset, inset, w*0.16, inset + archH*0.4);
    ctx.quadraticCurveTo(w/2, inset - archH*0.25, w*0.84, inset + archH*0.4);
    ctx.quadraticCurveTo(w - inset, inset, w - inset, archH);
    // rounded foot, matching the glass frame's corners (2026-09-24)
    ctx.lineTo(w - inset, h - inset - FOOT_R);
    ctx.quadraticCurveTo(w - inset, h - inset, w - inset - FOOT_R, h - inset);
    ctx.lineTo(inset + FOOT_R, h - inset);
    ctx.quadraticCurveTo(inset, h - inset, inset, h - inset - FOOT_R);
    ctx.closePath();
    ctx.strokeStyle = LB; ctx.lineWidth = 2; ctx.stroke();
    ctx.strokeStyle = toRgba(leadingColor || LEADING_DEEP, 0.7); ctx.lineWidth = 0.6; ctx.stroke();

    // corner botanical curls (bottom corners)
    drawVine(ctx, inset + 2, h - inset - 2, 1, 1, accentColor, leadingColor);
    drawVine(ctx, w - inset - 2, h - inset - 2, -1, 1, accentColor, leadingColor);
    // apex bud
    ctx.fillStyle = toRgba(accentColor, 0.9);
    ctx.strokeStyle = LB; ctx.lineWidth = 0.8;
    ctx.beginPath(); ellipsePath(ctx, w/2, inset + archH*0.05, 4, 9, 0, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.restore();
}

function drawVine(ctx, x, y, sx, sy, accentColor, leadingColor) {
    ctx.save();
    ctx.translate(x, y);
    ctx.scale(sx, sy);
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.strokeStyle = LB; ctx.lineWidth = 1.2;
    ctx.beginPath();
    ctx.moveTo(0, -4);
    ctx.quadraticCurveTo(0, -26, 22, -30);
    ctx.quadraticCurveTo(10, -34, 12, -44);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(4, 0);
    ctx.quadraticCurveTo(26, 0, 30, -22);
    ctx.stroke();
    ctx.fillStyle = "rgba(42, 74, 58, 0.85)";
    ctx.beginPath(); ellipsePath(ctx, 12, -44, 3.5, 1.6, -0.5, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.beginPath(); ellipsePath(ctx, 30, -22, 1.6, 3.5, -0.5, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.fillStyle = toRgba(accentColor, 0.9);
    ctx.beginPath(); ctx.arc(2, -2, 2.4, 0, Math.PI*2); ctx.fill();
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// BANNER — single branding ribbon at the bottom (e.g. "Athelian Engine")
// ═══════════════════════════════════════════════════════════════
// ts = Script Shift text factor (optional, default 1): ribbon height 22*ts, text
// 11*ts, widened to hold the label.
function paintBanner(ctx, cx, y, w, bannerText, fontFamily, accentColor, glowColor, leadingColor, ts) {
    ctx.save();
    var LB = leadingColor || LEADING_BRIGHT;
    ts = ts || 1;
    var fpx = Math.round(11 * ts);
    ctx.font = "600 " + fpx + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
    w = Math.max(w, ctx.measureText((bannerText || "").toUpperCase()).width + 20);
    var h = 22 * ts, x = cx - w/2, pt = 11;
    ctx.beginPath();
    ctx.moveTo(x - pt, y + h/2); ctx.lineTo(x, y); ctx.lineTo(x + w, y);
    ctx.lineTo(x + w + pt, y + h/2); ctx.lineTo(x + w, y + h); ctx.lineTo(x, y + h);
    ctx.closePath();
    var bg = ctx.createLinearGradient(x, y, x, y + h);
    bg.addColorStop(0, toRgba(glowColor, 0.18));
    bg.addColorStop(1, toRgba(accentColor, 0.10));
    ctx.fillStyle = bg; ctx.fill();
    ctx.strokeStyle = LB; ctx.lineWidth = 1; ctx.stroke();
    [x - pt, x + w + pt].forEach(function (jx) {
        ctx.fillStyle = toRgba(accentColor, 0.9);
        ctx.beginPath(); ctx.arc(jx, y + h/2, 2.2, 0, Math.PI*2); ctx.fill();
        ctx.strokeStyle = LB; ctx.lineWidth = 0.5; ctx.stroke();
    });
    // text — small-caps branding, letter-spaced
    ctx.textAlign = "center"; ctx.textBaseline = "middle";
    var label = (bannerText || "").toUpperCase();
    ctx.font = "600 " + fpx + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
    ctx.fillStyle = "rgba(0,0,0,0.45)";
    ctx.fillText(label, cx + 0.5, y + h/2 + 1.5);
    ctx.fillStyle = Ink.css(LB);
    ctx.shadowColor = toRgba(accentColor, 0.6); ctx.shadowBlur = 3;
    ctx.fillText(label, cx, y + h/2 + 1);
    ctx.shadowBlur = 0;
    ctx.textAlign = "left"; ctx.textBaseline = "alphabetic";
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// MASTER COMPOSITOR
// ═══════════════════════════════════════════════════════════════
// 2026-07-14 perf split: paintSky and paintArchBorder take no time parameter —
// sky only actually changes when `brightness` does (once/minute via updateAstro,
// not per-frame), and the border never changes at all. Both used to be redrawn
// unconditionally on every ~30fps animated frame for zero visual benefit (real
// cost: LaPivot sustained ~55% CPU, confirmed live). They're now painted on
// their own separate, rarely-repainted Canvas layers by the caller (SpacePanel.qml/
// SpaceWidget2.qml) instead of inside this per-frame compositor — see
// drawMuchaSpaceStatic() below. Everything genuinely time-varying (stars/
// shooting-star, aurora, orrery rotation, earth+clouds, sun/moon armatures)
// stays exactly as it was, every frame, full animation intact.
function drawMuchaSpace(ctx, W, H, st, accentColor, glowColor, leadingColor, layer) {
    ctx.clearRect(0, 0, W, H);
    // layer (2026-09-26, Evas-style split): undefined = the whole scene, as before;
    // "ring" = ring + armatures + sun + moon + banner; "earth" = the globe alone.
    // Stars and aurora are painted once (paintStarGroup / paintAuroraBand) and
    // moved by render-thread animators in SpacePanel.qml.
    var all = !layer, earth = layer === "earth";

    if (all) {
        paintStars(ctx, W, H, st.t, st.starOpacity);
        paintAurora(ctx, W, H, st.t, accentColor, glowColor);
    }

    var cx = W / 2;
    // Script Shift grows only the banner: size the orrery from the height it had
    // before the banner's extra (22*(ts-1)) so the artwork itself never scales with text.
    var ts = st.textScale || 1;
    var Hs = H - (st.showBanner ? 22 * (ts - 1) : 0);
    var cy = Hs * 0.48;
    var ringR = Math.min(W, Hs) * 0.42;
    var earthR = ringR * 0.34;

    if (earth) {
        paintEarth(ctx, cx, cy, earthR, st.earthRot, st.cloudRot, st.sunAngle, accentColor, glowColor, leadingColor,
                   { verd: st.verd, gilt3: st.gilt3 });
        return;
    }

    paintOrreryRing(ctx, cx, cy, ringR, st.zodiacRot, st.activeSign, accentColor, glowColor, leadingColor);

    // armatures + bodies on the ring (drawn under/over earth as appropriate)
    var bodyOrbit = ringR - 26;
    if (st.sunAngle !== null && st.sunAngle !== undefined) {
        paintArmature(ctx, cx, cy, st.sunAngle, earthR, bodyOrbit, accentColor, leadingColor);
    }
    if (st.moonAngle !== null && st.moonAngle !== undefined) {
        paintArmature(ctx, cx, cy, st.moonAngle, earthR, bodyOrbit, accentColor, leadingColor);
    }

    if (all) paintEarth(ctx, cx, cy, earthR, st.earthRot, st.cloudRot, st.sunAngle, accentColor, glowColor, leadingColor,
               { verd: st.verd, gilt3: st.gilt3 });

    if (st.sunAngle !== null && st.sunAngle !== undefined) {
        var sa = st.sunAngle * Math.PI / 180;
        paintSun(ctx, cx + Math.cos(sa)*bodyOrbit, cy + Math.sin(sa)*bodyOrbit, 9, accentColor, glowColor, leadingColor);
    }
    if (st.moonAngle !== null && st.moonAngle !== undefined) {
        var ma = st.moonAngle * Math.PI / 180;
        paintMoon(ctx, cx + Math.cos(ma)*bodyOrbit, cy + Math.sin(ma)*bodyOrbit, 7, st.moonPhase, glowColor, leadingColor);
    }

    if (st.showBanner) paintBanner(ctx, cx, H - 6 - 22 * ts, Math.min(W*0.7, 220),
                                   st.bannerText || "Athelian Engine", st.fontFamily, accentColor, glowColor, leadingColor, ts);
}

// ═══════════════════════════════════════════════════════════════
// PAINT-ONCE LAYERS (2026-09-26) — the Evas/Moksha way: the artwork is
// painted once and the motion is done by moving/fading the painted image on
// Qt's render thread (anim-policy.md §1), instead of re-rasterising the sky
// thirty times a second. Same stars, same places, same colours.
// ═══════════════════════════════════════════════════════════════

// One of `groups` twinkle groups of the same 90 stars paintStars draws (same
// seeded positions/sizes), at their peak brightness; the group's opacity is
// what twinkles.
function paintStarGroup(ctx, w, h, starOpacity, group, groups) {
    ctx.clearRect(0, 0, w, h);
    ctx.save();
    var op = starOpacity === undefined ? 1 : starOpacity;
    var rng = seededRng(1337);
    for (var i = 0; i < 90; i++) {
        var x = rng() * w;
        var y = rng() * h * 0.8;
        var base = 0.3 + rng() * 0.7;
        rng();                                   // twinkle speed (the group carries it now)
        var r = 0.4 + rng() * 1.3;
        if (i % groups !== group) continue;
        ctx.globalAlpha = base * op;
        ctx.fillStyle = "rgba(220, 228, 255, 1)";
        ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.fill();
        if (r > 1.4) {
            ctx.strokeStyle = "rgba(230, 236, 255, " + (base*op*0.5) + ")";
            ctx.lineWidth = 0.4;
            ctx.beginPath();
            ctx.moveTo(x - 3, y); ctx.lineTo(x + 3, y);
            ctx.moveTo(x, y - 3); ctx.lineTo(x, y + 3);
            ctx.stroke();
        }
    }
    ctx.restore();
}

// One aurora ribbon as a seamless strip two scene-widths wide (the wave repeats
// every W, so sliding it left by W and starting over never shows a seam). Drawn
// at the ribbon's brightest; its opacity breathes and its x slides.
function paintAuroraBand(ctx, W, h, band, accentColor, glowColor) {
    ctx.clearRect(0, 0, W * 2, h);
    ctx.save();
    ctx.globalCompositeOperation = "lighter";
    var k1 = 2 * Math.PI * Math.max(1, Math.round(0.02 * W / (2 * Math.PI))) / W;
    var k2 = 2 * Math.PI * Math.max(1, Math.round(0.05 * W / (2 * Math.PI))) / W;
    var yBase = h * (0.14 + band * 0.08);
    var amp = 10 + band * 6;
    var col = band % 2 === 0 ? glowColor : accentColor;
    var grad = ctx.createLinearGradient(0, yBase - 26, 0, yBase + 26);
    grad.addColorStop(0, "rgba(0,0,0,0)");
    grad.addColorStop(0.5, toRgba(col, 0.14));
    grad.addColorStop(1, "rgba(0,0,0,0)");
    ctx.fillStyle = grad;
    ctx.beginPath();
    ctx.moveTo(0, yBase);
    for (var x = 0; x <= W * 2 + 12; x += 6) {
        var y = yBase + Math.sin(x * k1 + band) * amp + Math.sin(x * k2) * (amp * 0.4);
        ctx.lineTo(x, y);
    }
    ctx.lineTo(W * 2 + 12, yBase + 30);
    ctx.lineTo(0, yBase + 30);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

// The shooting star, head at the right edge, pointing right (the item is
// rotated to its heading): the same gradient tail + bright head as paintStars.
function paintMeteor(ctx, len, h) {
    ctx.clearRect(0, 0, len + 4, h);
    var cy = h / 2, hx = len;
    var grad = ctx.createLinearGradient(0, cy, hx, cy);
    grad.addColorStop(0, "rgba(255,240,200,0)");
    grad.addColorStop(1, "rgba(255,245,215,1)");
    ctx.strokeStyle = grad;
    ctx.lineWidth = 1.4;
    ctx.beginPath(); ctx.moveTo(0, cy); ctx.lineTo(hx, cy); ctx.stroke();
    ctx.fillStyle = "rgba(255,248,220,1)";
    ctx.beginPath(); ctx.arc(hx, cy, 1.6, 0, Math.PI*2); ctx.fill();
}

// Sky and border are called directly by name (paintSky / paintArchBorder,
// both already exported above) from two SEPARATE Canvas layers in the QML —
// sky behind the animated canvas, border in front of it, matching the exact
// original draw order (sky first, border last, over everything). They must
// stay on separate layers: combining them into one call/canvas would put the
// border behind the animation or the sky in front of it, both wrong.
