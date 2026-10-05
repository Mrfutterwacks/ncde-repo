// mucha-clock.js — Mucha stained-glass digital clock painters for NCDE.
// Pure Canvas 2D, .pragma library. Fully transparent — no fills behind ornament.
// Mucha leading gold + VFD amber hardcoded per CLAUDE.md "Mucha art JS" exemption.
// accentColor / glowColor pass through from ncde.accent / ncde.glow.
// leadingColor (optional trailing param) overrides LEADING_BRIGHT per widget.
//
// The concept: a seven-segment digital readout where every LIT segment is a
// glowing stained-glass shard with a gold-leaded outline, and every UNLIT
// segment is a dim leaded ghost. Wrapped in an Art Nouveau cartouche with a
// crest finial and corner filigree.
//
// Exports (lowercase first letter — Qt forbids capitalised function names):
//   paintClockFrame  — cartouche + crest + corner curls (transparent inside)
//   paintDigit       — one seven-segment glyph ('0'-'9' or ' ')
//   paintColon       — two stained-glass dots (blinks via lit flag)
//   paintAmpm        — small AM/PM stacked indicator
//   paintGreetingBand — the greeting's own ribbon above the arch (2026-09-25)
//   measureDigits    — returns total width for a given digit count + sizing
//
.pragma library
.import "ncde-ink.js" as Ink   // wallpaper ink: text + lit digits re-inked (2026-09-24)

var LEADING_BRIGHT = "rgba(240, 210, 122, 1.0)";
var LEADING        = "rgba(184, 138, 50, 1.0)";
var LEADING_DEEP   = "rgba(74, 50, 8, 1.0)";

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
    // Already rgba() (LM/LD are pre-faded leading): scale its alpha instead of
    // returning it untouched, or ghost segments render as bright as lit ones.
    var m = c.match(/^rgba\(\s*([^,]+),([^,]+),([^,]+),\s*([\d.]+)\s*\)$/);
    if (m) return "rgba(" + m[1] + "," + m[2] + "," + m[3] + "," + (parseFloat(m[4]) * a) + ")";
    return c;
}

// ── Seven-segment lookup ───────────────────────────────────────
// Segments: a(top) b(top-right) c(bottom-right) d(bottom)
//           e(bottom-left) f(top-left) g(middle)
var SEG_MAP = {
    "0": [1,1,1,1,1,1,0],
    "1": [0,1,1,0,0,0,0],
    "2": [1,1,0,1,1,0,1],
    "3": [1,1,1,1,0,0,1],
    "4": [0,1,1,0,0,1,1],
    "5": [1,0,1,1,0,1,1],
    "6": [1,0,1,1,1,1,1],
    "7": [1,1,1,0,0,0,0],
    "8": [1,1,1,1,1,1,1],
    "9": [1,1,1,1,0,1,1],
    " ": [0,0,0,0,0,0,0]
};

// ── One leaded-glass segment shard (hexagonal capsule) ─────────
// orientation: "h" horizontal | "v" vertical. (x,y) = top-left of seg box.
function paintSegment(ctx, x, y, len, thick, horizontal, lit, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    var t = thick;
    ctx.save();
    ctx.beginPath();
    if (horizontal) {
        // pointed-end horizontal bar
        ctx.moveTo(x,           y + t/2);
        ctx.lineTo(x + t/2,     y);
        ctx.lineTo(x + len - t/2, y);
        ctx.lineTo(x + len,     y + t/2);
        ctx.lineTo(x + len - t/2, y + t);
        ctx.lineTo(x + t/2,     y + t);
    } else {
        // pointed-end vertical bar
        ctx.moveTo(x + t/2,     y);
        ctx.lineTo(x + t,       y + t/2);
        ctx.lineTo(x + t,       y + len - t/2);
        ctx.lineTo(x + t/2,     y + len);
        ctx.lineTo(x,           y + len - t/2);
        ctx.lineTo(x,           y + t/2);
    }
    ctx.closePath();

    if (lit) {
        // Glowing stained-glass fill
        var cxg = horizontal ? x + len/2 : x + t/2;
        var cyg = horizontal ? y + t/2   : y + len/2;
        var g = ctx.createRadialGradient(cxg, cyg, 0, cxg, cyg, (horizontal ? len : len) * 0.6);
        g.addColorStop(0,   Ink.css("rgba(255, 235, 175, 0.95)"));
        g.addColorStop(0.4, Ink.css(toRgba(accentColor, 0.85)));
        g.addColorStop(1,   Ink.css(toRgba(glowColor, 0.55)));
        ctx.fillStyle = g;
        ctx.shadowColor = Ink.css(toRgba(accentColor, 0.9));
        ctx.shadowBlur = thick * 1.6;
        ctx.fill();
        ctx.shadowBlur = 0;
        // gold leading
        ctx.strokeStyle = LB;
        ctx.lineWidth = 1;
        ctx.stroke();
    } else {
        // Dim leaded ghost — a whisper, so the lit time reads first, not "88:88"
        // (refine 2026-09-25: was 0.22 / 0.30, still legible as a second readout)
        ctx.fillStyle = Ink.css(toRgba(LD, 0.13));
        ctx.fill();
        ctx.strokeStyle = Ink.css(toRgba(LM, 0.12));
        ctx.lineWidth = 0.6;
        ctx.stroke();
    }
    ctx.restore();
}

// ── One seven-segment digit ────────────────────────────────────
// (x, y) = top-left. w/h = digit cell size. thick = segment thickness.
function paintDigit(ctx, ch, x, y, w, h, thick, accentColor, glowColor, leadingColor) {
    var segs = SEG_MAP[ch] !== undefined ? SEG_MAP[ch] : SEG_MAP[" "];
    var t = thick;
    var pad = t * 0.6;
    var innerW = w - t;
    var halfH = (h - t) / 2;

    // a top
    paintSegment(ctx, x + t/2 + pad, y, innerW - pad*2, t, true,  segs[0], accentColor, glowColor, leadingColor);
    // b top-right
    paintSegment(ctx, x + w - t, y + t/2 + pad, halfH - pad*1.5, t, false, segs[1], accentColor, glowColor, leadingColor);
    // c bottom-right
    paintSegment(ctx, x + w - t, y + h/2 + pad*0.5, halfH - pad*1.5, t, false, segs[2], accentColor, glowColor, leadingColor);
    // d bottom
    paintSegment(ctx, x + t/2 + pad, y + h - t, innerW - pad*2, t, true,  segs[3], accentColor, glowColor, leadingColor);
    // e bottom-left
    paintSegment(ctx, x, y + h/2 + pad*0.5, halfH - pad*1.5, t, false, segs[4], accentColor, glowColor, leadingColor);
    // f top-left
    paintSegment(ctx, x, y + t/2 + pad, halfH - pad*1.5, t, false, segs[5], accentColor, glowColor, leadingColor);
    // g middle
    paintSegment(ctx, x + t/2 + pad, y + halfH, innerW - pad*2, t, true,  segs[6], accentColor, glowColor, leadingColor);
}

// ── Colon (two stained-glass dots) ─────────────────────────────
function paintColon(ctx, cx, topY, h, dotR, lit, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    var y1 = topY + h * 0.34;
    var y2 = topY + h * 0.66;
    [y1, y2].forEach(function (cy) {
        ctx.beginPath();
        ctx.arc(cx, cy, dotR, 0, Math.PI * 2);
        if (lit) {
            var g = ctx.createRadialGradient(cx, cy, 0, cx, cy, dotR);
            g.addColorStop(0,   Ink.css("rgba(255, 235, 175, 0.95)"));
            g.addColorStop(0.5, Ink.css(toRgba(accentColor, 0.85)));
            g.addColorStop(1,   Ink.css(toRgba(glowColor, 0.5)));
            ctx.fillStyle = g;
            ctx.shadowColor = Ink.css(toRgba(accentColor, 0.9));
            ctx.shadowBlur = dotR * 1.8;
            ctx.fill();
            ctx.shadowBlur = 0;
            ctx.strokeStyle = LB;
            ctx.lineWidth = 0.8;
            ctx.stroke();
        } else {
            ctx.fillStyle = Ink.css(toRgba(LD, 0.13));
            ctx.fill();
            ctx.strokeStyle = Ink.css(toRgba(LM, 0.12));
            ctx.lineWidth = 0.5;
            ctx.stroke();
        }
    });
}

// ── AM/PM stacked indicator (small) ────────────────────────────
// ts = Script Shift text factor (optional, default 1): AM/PM is text, so it follows it.
function paintAmpm(ctx, x, topY, h, ampm, fontFamily, leadingColor, ts) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    ctx.save();
    ctx.font = "600 " + Math.round(h * 0.16 * (ts || 1)) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
    ctx.textBaseline = "middle";
    var isAM = (ampm === "AM");
    // AM
    ctx.fillStyle = Ink.css(isAM ? LB : toRgba(LM, 0.30));
    if (isAM) { ctx.shadowColor = LB; ctx.shadowBlur = 4; }
    ctx.fillText("AM", x, topY + h * 0.34);
    ctx.shadowBlur = 0;
    // PM
    ctx.fillStyle = Ink.css(!isAM ? LB : toRgba(LM, 0.30));
    if (!isAM) { ctx.shadowColor = LB; ctx.shadowBlur = 4; }
    ctx.fillText("PM", x, topY + h * 0.64);
    ctx.shadowBlur = 0;
    ctx.restore();
}

// ── Clock cartouche frame (transparent interior) ───────────────
// Ornate stained-glass surround: arched top, gold leading, corner curls,
// crest finial, side jewels. No interior fill.
// opts (optional): { noCrest: true } — the ClockPanel's greeting band takes the
// crest's place above the arch (2026-09-25); MuchaClock keeps the crest.
function paintClockFrame(ctx, x, y, w, h, accentColor, glowColor, leadingColor, opts) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    ctx.save();
    var r = 10;

    // Outer leaded arch-top rectangle
    var archH = h * 0.30;
    ctx.beginPath();
    ctx.moveTo(x, y + archH);
    ctx.quadraticCurveTo(x, y, x + w * 0.16, y + archH * 0.35);
    ctx.quadraticCurveTo(x + w / 2, y - archH * 0.35, x + w * 0.84, y + archH * 0.35);
    ctx.quadraticCurveTo(x + w, y, x + w, y + archH);
    ctx.lineTo(x + w, y + h - r);
    ctx.quadraticCurveTo(x + w, y + h, x + w - r, y + h);
    ctx.lineTo(x + r, y + h);
    ctx.quadraticCurveTo(x, y + h, x, y + h - r);
    ctx.closePath();

    // faint inner tint so the glass reads (very subtle, accent-derived, no black)
    var tint = ctx.createLinearGradient(x, y, x, y + h);
    tint.addColorStop(0, toRgba(glowColor, 0.10));
    tint.addColorStop(1, toRgba(accentColor, 0.05));
    ctx.fillStyle = tint;
    ctx.fill();

    // double gold leading
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.6;
    ctx.stroke();
    ctx.strokeStyle = toRgba(LD, 0.7);
    ctx.lineWidth = 0.5;
    ctx.stroke();

    // Corner curls (bottom L / R)
    paintCornerCurl(ctx, x + 3, y + h - 3, 1, 1, leadingColor);
    paintCornerCurl(ctx, x + w - 3, y + h - 3, -1, 1, leadingColor);

    // Crest finial at apex
    if (!(opts && opts.noCrest))
        paintCrestSmall(ctx, x + w / 2, y - archH * 0.30, w * 0.34, accentColor, leadingColor);

    // Side jewels at the arch shoulders
    [[x + w * 0.10, y + archH * 0.9], [x + w * 0.90, y + archH * 0.9]].forEach(function (p) {
        ctx.fillStyle = toRgba(accentColor, 0.85);
        ctx.strokeStyle = LB;
        ctx.lineWidth = 0.6;
        ctx.beginPath();
        ctx.arc(p[0], p[1], 3, 0, Math.PI * 2);
        ctx.fill(); ctx.stroke();
        ctx.fillStyle = "rgba(255, 230, 170, 1)";
        ctx.beginPath(); ctx.arc(p[0], p[1], 1, 0, Math.PI * 2); ctx.fill();
    });

    ctx.restore();
}

function paintCornerCurl(ctx, x, y, sx, sy, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    ctx.translate(x, y);
    ctx.scale(sx, sy);
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.1;
    ctx.beginPath();
    ctx.moveTo(0, -2);
    ctx.quadraticCurveTo(-16, -2, -16, -16);
    ctx.quadraticCurveTo(-16, -8, -22, -7);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(-2, 0);
    ctx.quadraticCurveTo(-2, -14, -14, -16);
    ctx.stroke();
    // leaf
    ctx.fillStyle = "rgba(42, 74, 58, 0.85)";
    ctx.beginPath();
    ctx.ellipse(-20, -7, 3.5, 1.6, -0.5, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();
    ctx.restore();
}

function paintCrestSmall(ctx, cx, baseY, width, accentColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    ctx.translate(cx, baseY);
    var s = width / 90;
    ctx.scale(s, s);
    ctx.fillStyle = "rgba(42, 74, 58, 0.92)";
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.quadraticCurveTo(-20, -8, -35, -3);
    ctx.quadraticCurveTo(-26, -16, -12, -18);
    ctx.quadraticCurveTo(-22, -26, -18, -38);
    ctx.quadraticCurveTo(-9, -31, 0, -22);
    ctx.quadraticCurveTo(9, -31, 18, -38);
    ctx.quadraticCurveTo(22, -26, 12, -18);
    ctx.quadraticCurveTo(26, -16, 35, -3);
    ctx.quadraticCurveTo(20, -8, 0, 0);
    ctx.closePath();
    ctx.fill(); ctx.stroke();
    // central bud
    ctx.fillStyle = toRgba(accentColor, 0.95);
    ctx.beginPath();
    ctx.ellipse(0, -9, 4, 10, 0, 0, Math.PI * 2);
    ctx.fill(); ctx.stroke();
    ctx.restore();
}

// ── Date ribbon-cartouche (drawn into the glass below the digits) ──
// A slim stained-glass banner with curled ends holding the date text.
// ts = Script Shift text factor (optional, default 1). The ribbon grows with its
// text (height 18*ts) and widens to hold it; callers make room for 18*ts.
function paintDateBanner(ctx, cx, y, w, dateText, fontFamily, accentColor, glowColor, leadingColor, ts) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    var h = 18 * (ts || 1);
    if (dateText) {
        ctx.font = "600 " + Math.round(h * 0.56) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        w = Math.max(w, ctx.measureText(dateText).width + 16);
    }
    var x = cx - w / 2;

    // Ribbon body — flattened hexagon (pointed ends)
    var pt = 9;
    ctx.beginPath();
    ctx.moveTo(x - pt, y + h / 2);
    ctx.lineTo(x, y);
    ctx.lineTo(x + w, y);
    ctx.lineTo(x + w + pt, y + h / 2);
    ctx.lineTo(x + w, y + h);
    ctx.lineTo(x, y + h);
    ctx.closePath();

    var bg = ctx.createLinearGradient(x, y, x, y + h);
    bg.addColorStop(0, toRgba(glowColor, 0.16));
    bg.addColorStop(1, toRgba(accentColor, 0.08));
    ctx.fillStyle = bg;
    ctx.fill();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 0.9;
    ctx.stroke();

    // End jewels
    [x - pt, x + w + pt].forEach(function (jx) {
        ctx.fillStyle = toRgba(accentColor, 0.9);
        ctx.beginPath();
        ctx.arc(jx, y + h / 2, 2, 0, Math.PI * 2);
        ctx.fill();
        ctx.strokeStyle = LB;
        ctx.lineWidth = 0.5;
        ctx.stroke();
    });

    // Date text — VFD-style amber, centred
    if (dateText) {
        ctx.font = "600 " + Math.round(h * 0.56) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillStyle = "rgba(0, 0, 0, 0.45)";
        ctx.fillText(dateText, cx + 0.5, y + h / 2 + 1.5);
        ctx.fillStyle = Ink.css(LB);
        ctx.shadowColor = toRgba(accentColor, 0.7);
        ctx.shadowBlur = 3;
        ctx.fillText(dateText, cx, y + h / 2 + 1);
        ctx.shadowBlur = 0;
        ctx.textAlign = "left";
        ctx.textBaseline = "alphabetic";
    }

    ctx.restore();
}

// ── Greeting band (2026-09-25) ─────────────────────────────────
// The greeting's own leaded ribbon above the clock's arch — same pointed-end
// ribbon and end jewels as the date banner, so the card reads top-to-bottom as
// greeting / time / date. A short came drop hangs the arch from the ribbon,
// with a small jewel where it meets the apex. The text itself is a QML Text
// laid over the ribbon (it follows the widget font + Script Shift).
// (cx, y) = top centre; w/h = ribbon body; apexY = arch apex below it.
function paintGreetingBand(ctx, cx, y, w, h, apexY, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var LD = leadingColor ? toRgba(leadingColor, 0.30) : LEADING_DEEP;
    ctx.save();
    var x = cx - w / 2, pt = Math.min(12, h * 0.5);

    ctx.beginPath();
    ctx.moveTo(x - pt, y + h / 2);
    ctx.lineTo(x, y);
    ctx.lineTo(x + w, y);
    ctx.lineTo(x + w + pt, y + h / 2);
    ctx.lineTo(x + w, y + h);
    ctx.lineTo(x, y + h);
    ctx.closePath();
    var bg = ctx.createLinearGradient(x, y, x, y + h);
    bg.addColorStop(0, toRgba(glowColor, 0.18));
    bg.addColorStop(1, toRgba(accentColor, 0.08));
    ctx.fillStyle = bg;
    ctx.fill();
    // double leading, like the arch
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.2;
    ctx.stroke();
    ctx.strokeStyle = toRgba(LD, 0.7);
    ctx.lineWidth = 0.5;
    ctx.stroke();

    // End jewels
    [x - pt, x + w + pt].forEach(function (jx) {
        ctx.fillStyle = toRgba(accentColor, 0.9);
        ctx.beginPath();
        ctx.arc(jx, y + h / 2, 2.4, 0, Math.PI * 2);
        ctx.fill();
        ctx.strokeStyle = LB;
        ctx.lineWidth = 0.6;
        ctx.stroke();
    });

    // Came drop to the arch apex + a jewel at the join
    if (apexY > y + h + 2) {
        ctx.strokeStyle = LB;
        ctx.lineWidth = 1.1;
        ctx.beginPath();
        ctx.moveTo(cx, y + h);
        ctx.lineTo(cx, apexY);
        ctx.stroke();
        var jy = (y + h + apexY) / 2;
        ctx.fillStyle = toRgba(accentColor, 0.9);
        ctx.beginPath();
        ctx.moveTo(cx, jy - 3.2); ctx.lineTo(cx + 2.4, jy); ctx.lineTo(cx, jy + 3.2); ctx.lineTo(cx - 2.4, jy);
        ctx.closePath();
        ctx.fill();
        ctx.lineWidth = 0.6;
        ctx.stroke();
    }
    ctx.restore();
}

// ── Layout helper — total readout width for "HH:MM" style ──────
// digitW, gap, colonW are returned so the .qml can centre everything.
function measureDigits(digitCount, hasColon, digitW, gap, colonW) {
    var w = digitCount * digitW + (digitCount - 1) * gap;
    if (hasColon) w += colonW + gap;
    return w;
}
