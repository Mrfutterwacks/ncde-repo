// mucha-panels.js — Mucha stained-glass painters for the Weather + Stats
// desktop-widget sections. Pure Canvas 2D, .pragma library, fully transparent.
// leadingColor threads from ncde.gilt4 (fallback: LEADING_BRIGHT module constant).
// accentColor / glowColor pass through from ncde.accent / ncde.glow.
//
// This file is SELF-CONTAINED — it does not depend on mucha-clock.js or
// mucha-salon.js, so the Weather and Stats sections can be installed on their
// own. The weather ICON itself is NOT drawn here — the .qml calls the project's
// existing drawMuchaWeather() from mucha-weather.js into the roundel centre.
//
// Exports (lowercase first letter — Qt forbids capitalised function names):
//   WEATHER
//     paintRoundel       — leaded rose-window roundel (frame only, hollow centre)
//     paintTempReadout   — seven-segment glass temperature + degree ring
//     paintMiniCartouche — small labelled value chip (HI / LO / HUM / WIND …)
//   STATS
//     paintGaugeColumn   — vertical cathedral-window gauge with liquid fill + %
//     paintVFDStrip      — recessed amber readout band (uptime / freq / temp)
//     paintArcDial       — optional circular gauge (alt style)
//   SHARED
//     paintFiligreeRow   — horizontal art-nouveau divider
//     paintSegDigit / paintSegColon — seven-segment glass glyphs (used by temp)
//
.pragma library
.import "ncde-ink.js" as Ink   // wallpaper ink: text + lit digits re-inked (2026-09-24)

var LEADING_BRIGHT = "rgba(240, 210, 122, 1.0)";
var LEADING        = "rgba(184, 138, 50, 1.0)";
var LEADING_DEEP   = "rgba(74, 50, 8, 1.0)";
var VFD_AMBER      = "rgba(248, 184, 80, 1.0)";

// paintTubeGauge's empty-glass-body gradient depends only on position/size/glow
// color, not on the live pct — recompute only when those actually change
// instead of every paint call (Moksha rule: cache, redo only on real change).
// Keyed by gauge label ("CPU"/"RAM"/"DISK" — stable, unique per call site).
// .pragma library makes this module state persist across paint calls.
var _gaugeBgGradCache = {};

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
    // Already rgba() (the LEADING* constants): scale its alpha instead of
    // returning it untouched, or ghost segments render at full strength.
    var m = c.match(/^rgba\(\s*([^,]+),([^,]+),([^,]+),\s*([\d.]+)\s*\)$/);
    if (m) return "rgba(" + m[1] + "," + m[2] + "," + m[3] + "," + (parseFloat(m[4]) * a) + ")";
    return c;
}

function roundRectPath(ctx, x, y, w, h, r) {
    if (r > w/2) r = w/2;
    if (r > h/2) r = h/2;
    ctx.beginPath();
    ctx.moveTo(x+r, y);
    ctx.lineTo(x+w-r, y);
    ctx.quadraticCurveTo(x+w, y, x+w, y+r);
    ctx.lineTo(x+w, y+h-r);
    ctx.quadraticCurveTo(x+w, y+h, x+w-r, y+h);
    ctx.lineTo(x+r, y+h);
    ctx.quadraticCurveTo(x, y+h, x, y+h-r);
    ctx.lineTo(x, y+r);
    ctx.quadraticCurveTo(x, y, x+r, y);
    ctx.closePath();
}

// ═══════════════════════════════════════════════════════════════
// SEVEN-SEGMENT (shared, used by the temperature readout)
// ═══════════════════════════════════════════════════════════════
var SEG_MAP = {
    "0":[1,1,1,1,1,1,0], "1":[0,1,1,0,0,0,0], "2":[1,1,0,1,1,0,1],
    "3":[1,1,1,1,0,0,1], "4":[0,1,1,0,0,1,1], "5":[1,0,1,1,0,1,1],
    "6":[1,0,1,1,1,1,1], "7":[1,1,1,0,0,0,0], "8":[1,1,1,1,1,1,1],
    "9":[1,1,1,1,0,1,1], "-":[0,0,0,0,0,0,1], " ":[0,0,0,0,0,0,0]
};

function segShard(ctx, x, y, len, t, horizontal, lit, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    ctx.beginPath();
    if (horizontal) {
        ctx.moveTo(x, y+t/2); ctx.lineTo(x+t/2, y); ctx.lineTo(x+len-t/2, y);
        ctx.lineTo(x+len, y+t/2); ctx.lineTo(x+len-t/2, y+t); ctx.lineTo(x+t/2, y+t);
    } else {
        ctx.moveTo(x+t/2, y); ctx.lineTo(x+t, y+t/2); ctx.lineTo(x+t, y+len-t/2);
        ctx.lineTo(x+t/2, y+len); ctx.lineTo(x, y+len-t/2); ctx.lineTo(x, y+t/2);
    }
    ctx.closePath();
    if (lit) {
        var cxg = horizontal ? x+len/2 : x+t/2;
        var cyg = horizontal ? y+t/2 : y+len/2;
        var g = ctx.createRadialGradient(cxg, cyg, 0, cxg, cyg, len*0.6);
        g.addColorStop(0, Ink.css("rgba(255,235,175,0.95)"));
        g.addColorStop(0.4, Ink.css(toRgba(accentColor, 0.85)));
        g.addColorStop(1, Ink.css(toRgba(glowColor, 0.55)));
        ctx.fillStyle = g;
        ctx.shadowColor = Ink.css(toRgba(accentColor, 0.9));
        ctx.shadowBlur = t*1.5;
        ctx.fill(); ctx.shadowBlur = 0;
        ctx.strokeStyle = LB; ctx.lineWidth = 0.9; ctx.stroke();
    } else {
        // unlit: a whisper, so the lit reading comes first (refine 2026-09-25: was 0.20 / 0.28)
        ctx.fillStyle = Ink.css(toRgba(LEADING_DEEP, 0.12)); ctx.fill();
        ctx.strokeStyle = Ink.css(toRgba(LEADING, 0.10)); ctx.lineWidth = 0.5; ctx.stroke();
    }
    ctx.restore();
}

function paintSegDigit(ctx, ch, x, y, w, h, t, accentColor, glowColor, leadingColor) {
    var segs = SEG_MAP[ch] !== undefined ? SEG_MAP[ch] : SEG_MAP[" "];
    var pad = t*0.6;
    var innerW = w - t;
    var halfH = (h - t) / 2;
    segShard(ctx, x+t/2+pad, y, innerW-pad*2, t, true, segs[0], accentColor, glowColor, leadingColor);
    segShard(ctx, x+w-t, y+t/2+pad, halfH-pad*1.5, t, false, segs[1], accentColor, glowColor, leadingColor);
    segShard(ctx, x+w-t, y+h/2+pad*0.5, halfH-pad*1.5, t, false, segs[2], accentColor, glowColor, leadingColor);
    segShard(ctx, x+t/2+pad, y+h-t, innerW-pad*2, t, true, segs[3], accentColor, glowColor, leadingColor);
    segShard(ctx, x, y+h/2+pad*0.5, halfH-pad*1.5, t, false, segs[4], accentColor, glowColor, leadingColor);
    segShard(ctx, x, y+t/2+pad, halfH-pad*1.5, t, false, segs[5], accentColor, glowColor, leadingColor);
    segShard(ctx, x+t/2+pad, y+halfH, innerW-pad*2, t, true, segs[6], accentColor, glowColor, leadingColor);
}

// ═══════════════════════════════════════════════════════════════
// WEATHER — rose-window roundel (frame only; icon hosted by .qml)
// ═══════════════════════════════════════════════════════════════
function paintRoundel(ctx, cx, cy, outerR, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();

    // Faint glass disc so the hosted icon sits on a leaded pane (no black)
    var bg = ctx.createRadialGradient(cx, cy, outerR*0.2, cx, cy, outerR);
    bg.addColorStop(0, toRgba(glowColor, 0.12));
    bg.addColorStop(0.7, toRgba(accentColor, 0.07));
    bg.addColorStop(1, toRgba(glowColor, 0.02));
    ctx.fillStyle = bg;
    ctx.beginPath(); ctx.arc(cx, cy, outerR, 0, Math.PI*2); ctx.fill();

    // Double gold rim
    ctx.strokeStyle = LB; ctx.lineWidth = 1.6;
    ctx.beginPath(); ctx.arc(cx, cy, outerR, 0, Math.PI*2); ctx.stroke();
    ctx.strokeStyle = toRgba(LEADING_DEEP, 0.7); ctx.lineWidth = 0.5;
    ctx.beginPath(); ctx.arc(cx, cy, outerR-2, 0, Math.PI*2); ctx.stroke();

    // 16 petal-arc scallops on the rim (rose-window tracery)
    var petals = 16;
    ctx.strokeStyle = toRgba(LB, 0.55);
    ctx.lineWidth = 0.8;
    for (var i = 0; i < petals; i++) {
        var a = (i / petals) * Math.PI*2;
        var px = cx + Math.cos(a) * outerR;
        var py = cy + Math.sin(a) * outerR;
        ctx.beginPath();
        ctx.arc(px, py, outerR * 0.12, a + Math.PI*0.5, a + Math.PI*1.5);
        ctx.stroke();
    }

    // Inner halo ring that frames the icon
    ctx.strokeStyle = toRgba(LB, 0.5);
    ctx.lineWidth = 0.9;
    ctx.beginPath(); ctx.arc(cx, cy, outerR*0.74, 0, Math.PI*2); ctx.stroke();

    // Jewels at the cardinal points
    for (var j = 0; j < 8; j++) {
        var ja = (j / 8) * Math.PI*2 - Math.PI/2;
        var jx = cx + Math.cos(ja) * outerR * 0.74;
        var jy = cy + Math.sin(ja) * outerR * 0.74;
        ctx.fillStyle = (j % 2 === 0) ? toRgba(accentColor, 0.85) : toRgba(glowColor, 0.7);
        ctx.strokeStyle = toRgba(LB, 0.5); ctx.lineWidth = 0.4;
        ctx.beginPath(); ctx.arc(jx, jy, j % 2 === 0 ? 2 : 1.4, 0, Math.PI*2);
        ctx.fill(); ctx.stroke();
    }

    ctx.restore();
}

// Temperature readout: seven-segment glass digits + degree ring + unit.
// tempStr like "72" or "-4". (x,y) = top-left of the digit run.
function paintTempReadout(ctx, x, y, tempStr, digitW, digitH, segT, unit, fontFamily, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    var gap = digitW * 0.22;
    var cur = x;
    for (var i = 0; i < tempStr.length; i++) {
        paintSegDigit(ctx, tempStr.charAt(i), cur, y, digitW, digitH, segT, accentColor, glowColor, leadingColor);
        cur += digitW + gap;
    }
    // Degree ring
    var degR = digitW * 0.16;
    var degX = cur + degR + 2;
    var degY = y + segT;
    ctx.strokeStyle = LB;
    ctx.lineWidth = segT * 0.45;
    ctx.shadowColor = toRgba(accentColor, 0.8);
    ctx.shadowBlur = 4;
    ctx.beginPath(); ctx.arc(degX, degY, degR, 0, Math.PI*2); ctx.stroke();
    ctx.shadowBlur = 0;
    // Unit letter (F / C) below the degree
    if (unit) {
        ctx.font = "600 " + Math.round(digitH*0.28) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        ctx.fillStyle = Ink.css(LB);
        ctx.textAlign = "center"; ctx.textBaseline = "middle";
        ctx.fillText(unit, degX, degY + digitH*0.42);
        ctx.textAlign = "left"; ctx.textBaseline = "alphabetic";
    }
    return cur + degR*2 + 4; // right edge
}

// Mini labelled value chip (HI 81° · HUM 47% · WIND 6mph …)
function paintMiniCartouche(ctx, x, y, w, h, label, value, fontFamily, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    roundRectPath(ctx, x, y, w, h, h*0.32);
    var bg = ctx.createLinearGradient(x, y, x, y+h);
    bg.addColorStop(0, toRgba(glowColor, 0.13));
    bg.addColorStop(1, toRgba(accentColor, 0.06));
    ctx.fillStyle = bg; ctx.fill();
    ctx.strokeStyle = toRgba(LB, 0.8); ctx.lineWidth = 0.8; ctx.stroke();

    // label (small caps, dim gold) on top
    ctx.font = "600 " + Math.round(h*0.26) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
    ctx.fillStyle = Ink.css(toRgba(LB, 0.7));
    ctx.textAlign = "center"; ctx.textBaseline = "middle";
    ctx.fillText(label, x + w/2, y + h*0.30);

    // value (bright leading) below
    // Text size tracks h (Script Shift callers pass a taller chip); a value too
    // wide for a narrow chip steps down to fit rather than spill over the border.
    var vpx = Math.round(h*0.34);
    ctx.font = "600 " + vpx + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
    while (vpx > 8 && ctx.measureText(value).width > w - 6) {
        vpx -= 0.5;
        ctx.font = "600 " + vpx + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
    }
    ctx.fillStyle = Ink.css(toRgba(leadingColor || LEADING_BRIGHT, 1.0));
    ctx.shadowColor = toRgba(accentColor, 0.6); ctx.shadowBlur = 2;
    ctx.fillText(value, x + w/2, y + h*0.68);
    ctx.shadowBlur = 0;
    ctx.textAlign = "left"; ctx.textBaseline = "alphabetic";
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// STATS — vertical cathedral-window gauge column with liquid fill
// pct 0..100. (x,y) = top-left of the column. label below, % inside.
// ═══════════════════════════════════════════════════════════════
function paintGaugeColumn(ctx, x, y, w, h, pct, label, valueText, fontFamily, accentColor, glowColor) {
    ctx.save();
    pct = Math.max(0, Math.min(100, pct));

    // Pointed-arch cathedral window outline
    var archH = w * 0.55;
    function windowPath() {
        ctx.beginPath();
        ctx.moveTo(x, y + archH);
        ctx.quadraticCurveTo(x, y, x + w/2, y);
        ctx.quadraticCurveTo(x + w, y, x + w, y + archH);
        ctx.lineTo(x + w, y + h);
        ctx.lineTo(x, y + h);
        ctx.closePath();
    }

    // Empty glass ground (very faint)
    windowPath();
    ctx.fillStyle = toRgba(glowColor, 0.05);
    ctx.fill();

    // Liquid fill — rises from the bottom to pct
    var fillTop = y + h - (h - 4) * (pct / 100);
    ctx.save();
    windowPath();
    ctx.clip();
    var liq = ctx.createLinearGradient(0, y + h, 0, fillTop);
    liq.addColorStop(0, toRgba(accentColor, 0.85));
    liq.addColorStop(0.6, toRgba(accentColor, 0.55));
    liq.addColorStop(1, toRgba(glowColor, 0.75));
    ctx.fillStyle = liq;
    ctx.fillRect(x, fillTop, w, (y + h) - fillTop);
    // Meniscus highlight
    ctx.strokeStyle = "rgba(255,235,175,0.7)";
    ctx.lineWidth = 1;
    ctx.beginPath();
    ctx.moveTo(x, fillTop); ctx.lineTo(x + w, fillTop);
    ctx.stroke();
    // Horizontal leaded mullions across the glass
    ctx.strokeStyle = toRgba(LEADING_DEEP, 0.4);
    ctx.lineWidth = 0.6;
    for (var my = y + archH; my < y + h; my += (h - archH) / 4) {
        ctx.beginPath(); ctx.moveTo(x, my); ctx.lineTo(x + w, my); ctx.stroke();
    }
    ctx.restore();

    // Gold leaded frame
    windowPath();
    ctx.strokeStyle = LEADING_BRIGHT; ctx.lineWidth = 1.4; ctx.stroke();
    // Central mullion
    ctx.strokeStyle = toRgba(LEADING_BRIGHT, 0.45); ctx.lineWidth = 0.7;
    ctx.beginPath(); ctx.moveTo(x + w/2, y + archH*0.4); ctx.lineTo(x + w/2, y + h); ctx.stroke();

    // Apex jewel
    ctx.fillStyle = toRgba(accentColor, 0.9);
    ctx.strokeStyle = LEADING_BRIGHT; ctx.lineWidth = 0.5;
    ctx.beginPath(); ctx.arc(x + w/2, y + 4, 2.2, 0, Math.PI*2); ctx.fill(); ctx.stroke();

    // Value text (% or used) centred in the glass
    if (valueText) {
        ctx.font = "600 " + Math.round(w*0.26) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        ctx.fillStyle = "rgba(0,0,0,0.45)";
        ctx.textAlign = "center"; ctx.textBaseline = "middle";
        ctx.fillText(valueText, x + w/2 + 0.5, y + h*0.5 + 1.5);
        ctx.fillStyle = Ink.css("rgba(255,238,200,0.96)");
        ctx.shadowColor = "rgba(0,0,0,0.6)"; ctx.shadowBlur = 3;
        ctx.fillText(valueText, x + w/2, y + h*0.5);
        ctx.shadowBlur = 0;
        ctx.textAlign = "left"; ctx.textBaseline = "alphabetic";
    }

    // Label below the column
    if (label) {
        ctx.font = "600 " + Math.round(w*0.22) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        ctx.fillStyle = Ink.css(toRgba(LEADING_BRIGHT, 0.85));
        ctx.textAlign = "center";
        ctx.fillText(label, x + w/2, y + h + Math.round(w*0.30));
        ctx.textAlign = "left";
    }

    ctx.restore();
}

// Recessed VFD readout band (uptime / freq / temp etc.)
// lines = array of {label, value}. Drawn as right-justified value rows.
// ts = Script Shift text factor (optional, default 1); callers pass h grown to match.
function paintVFDStrip(ctx, x, y, w, h, lines, fontFixed, leadingColor, ts) {
    ts = ts || 1;
    var LB = leadingColor || LEADING_BRIGHT;
    var LM = leadingColor ? toRgba(leadingColor, 0.75) : LEADING;
    ctx.save();
    // recessed glass body
    var body = ctx.createLinearGradient(x, y, x, y+h);
    body.addColorStop(0, "rgba(12,10,24,0.80)");
    body.addColorStop(0.5, "rgba(20,16,38,0.72)");
    body.addColorStop(1, "rgba(8,6,18,0.80)");
    ctx.fillStyle = body;
    roundRectPath(ctx, x, y, w, h, 4); ctx.fill();
    ctx.strokeStyle = LM; ctx.lineWidth = 1;
    roundRectPath(ctx, x+0.5, y+0.5, w-1, h-1, 4); ctx.stroke();
    ctx.strokeStyle = LB; ctx.lineWidth = 0.5;
    roundRectPath(ctx, x+1.5, y+1.5, w-3, h-3, 3); ctx.stroke();

    var n = lines.length;
    var rowH = (h - 8) / n;
    for (var i = 0; i < n; i++) {
        var ry = y + 4 + rowH * i + rowH/2;
        // label (dim leading, left)
        ctx.font = "500 " + Math.round(10 * ts) + "px " + (fontFixed || "monospace");
        ctx.textBaseline = "middle";
        ctx.fillStyle = Ink.css(toRgba(LB, 0.55));
        ctx.textAlign = "left";
        ctx.fillText(lines[i].label, x + 8, ry);
        // value (bright leading, right)
        ctx.font = "600 " + Math.round(11 * ts) + "px " + (fontFixed || "monospace");
        ctx.fillStyle = Ink.css(toRgba(LB, 1.0));
        ctx.shadowColor = LB; ctx.shadowBlur = 3;
        ctx.textAlign = "right";
        ctx.fillText(lines[i].value, x + w - 8, ry);
        ctx.shadowBlur = 0;
    }
    ctx.textAlign = "left"; ctx.textBaseline = "alphabetic";
    ctx.restore();
}

// ── TUBE GAUGE — mad-scientist test-tube with bubbling liquid ──
// pct 0..100. t = time seconds (animates rising bubbles). (x,y)=top-left of
// the tube's bounding box; tube is a rounded-bottom glass cylinder with a
// brass collar near the top. Label sits below; value floats in the liquid.
// ts = Script Shift text factor (optional, default 1): value + label text follow it.
function paintTubeGauge(ctx, x, y, w, h, pct, label, valueText, t, fontFamily, accentColor, glowColor, leadingColor, fillColor, ts) {
    ts = ts || 1;
    ctx.save();
    pct = Math.max(0, Math.min(100, pct));
    var LB = leadingColor || LEADING_BRIGHT;

    var cx = x + w / 2;
    var rad = w / 2;                  // cylinder radius
    var collarY = y + h * 0.10;       // brass collar sits here
    var tubeTop = y + h * 0.06;       // glass opening
    var tubeBottomCy = y + h - rad;   // centre of the rounded bottom

    // Tube glass path (rounded bottom, open top)
    function tubePath() {
        ctx.beginPath();
        ctx.moveTo(x, tubeTop);
        ctx.lineTo(x, tubeBottomCy);
        ctx.arc(cx, tubeBottomCy, rad, Math.PI, 0, false);
        ctx.lineTo(x + w, tubeTop);
    }

    // Empty glass body (very faint) — gradient cached, doesn't depend on pct
    tubePath();
    ctx.lineTo(x, tubeTop);
    ctx.closePath();
    var bgKey = x + "|" + y + "|" + w + "|" + glowColor;
    var bgCache = _gaugeBgGradCache[label];
    var gbg;
    if (bgCache && bgCache.key === bgKey) {
        gbg = bgCache.grad;
    } else {
        gbg = ctx.createLinearGradient(x, y, x + w, y);
        gbg.addColorStop(0, toRgba(glowColor, 0.06));
        gbg.addColorStop(0.5, toRgba(glowColor, 0.02));
        gbg.addColorStop(1, toRgba(glowColor, 0.08));
        _gaugeBgGradCache[label] = { key: bgKey, grad: gbg };
    }
    ctx.fillStyle = gbg;
    ctx.fill();

    // Liquid region — clip to tube, fill from bottom to pct
    var liqTopY = collarY + (tubeBottomCy + rad - collarY) * (1 - pct / 100);
    ctx.save();
    tubePath();
    ctx.lineTo(x, tubeTop);
    ctx.closePath();
    ctx.clip();

    // Liquid body
    var liq = ctx.createLinearGradient(0, tubeBottomCy + rad, 0, liqTopY);
    liq.addColorStop(0, toRgba(accentColor, 0.9));
    liq.addColorStop(0.6, toRgba(accentColor, 0.6));
    liq.addColorStop(1, toRgba(glowColor, 0.78));
    ctx.fillStyle = liq;
    ctx.fillRect(x, liqTopY, w, (tubeBottomCy + rad) - liqTopY);

    // Rising bubbles (deterministic from t + column phase)
    var liqH = (tubeBottomCy + rad) - liqTopY;
    if (liqH > 6) {
        ctx.fillStyle = "rgba(255, 245, 210, 0.55)";
        var n = 7;
        for (var b = 0; b < n; b++) {
            var phase = (b * 0.137 + (b % 3) * 0.21);
            var speed = 0.18 + (b % 4) * 0.05;
            var prog = ((t * speed + phase) % 1);          // 0..1 rising
            var by = (tubeBottomCy + rad - 3) - prog * (liqH - 4);
            var bx = cx + Math.sin((t * 1.3 + b * 2.1)) * rad * 0.5;
            var br = 0.8 + (b % 3) * 0.7;
            var fade = Math.min(1, prog * 2) * (1 - prog * 0.4);
            ctx.globalAlpha = 0.5 * fade;
            ctx.beginPath();
            ctx.arc(bx, by, br, 0, Math.PI * 2);
            ctx.fill();
        }
        ctx.globalAlpha = 1;
    }

    // Meniscus highlight at the liquid surface
    ctx.strokeStyle = "rgba(255, 240, 200, 0.8)";
    ctx.lineWidth = 1.2;
    ctx.beginPath();
    ctx.ellipse(cx, liqTopY, rad * 0.92, 2.6, 0, 0, Math.PI * 2);
    ctx.stroke();
    // a little glow bloom on the surface
    ctx.fillStyle = toRgba(glowColor, 0.25);
    ctx.beginPath();
    ctx.ellipse(cx, liqTopY, rad * 0.92, 2.6, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();

    // Glass vertical highlight streak
    ctx.strokeStyle = "rgba(255, 255, 255, 0.22)";
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(x + rad * 0.5, collarY + 4);
    ctx.lineTo(x + rad * 0.5, tubeBottomCy);
    ctx.stroke();

    // Tube glass outline (gold leading)
    tubePath();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.5;
    ctx.stroke();

    // Brass collar near the top
    var collarH = h * 0.07;
    var brass = ctx.createLinearGradient(x, collarY, x, collarY + collarH);
    brass.addColorStop(0, "rgba(253, 233, 179, 1)");
    brass.addColorStop(0.5, LB);
    brass.addColorStop(1, LEADING_DEEP);
    ctx.fillStyle = brass;
    ctx.strokeStyle = LEADING_DEEP;
    ctx.lineWidth = 0.6;
    roundRectPath(ctx, x - 2, collarY, w + 4, collarH, 2);
    ctx.fill();
    ctx.stroke();
    // collar rivets
    ctx.fillStyle = LEADING_DEEP;
    ctx.beginPath(); ctx.arc(x + 3, collarY + collarH/2, 1, 0, Math.PI*2); ctx.fill();
    ctx.beginPath(); ctx.arc(x + w - 3, collarY + collarH/2, 1, 0, Math.PI*2); ctx.fill();

    // Lip ring at the very top
    ctx.strokeStyle = LB;
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.ellipse(cx, tubeTop, rad, 2.4, 0, 0, Math.PI * 2);
    ctx.stroke();

    // Value text floating in the liquid
    if (valueText) {
        var valuePx = Math.max(8, Math.round(w * 0.30 * ts));
        ctx.font = "600 " + valuePx + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        var valueMaxWidth = Math.max(8, w * 0.66);
        while (valuePx > 8 && ctx.measureText(valueText).width > valueMaxWidth) {
            valuePx -= 1;
            ctx.font = "600 " + valuePx + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        }
        ctx.textAlign = "center"; ctx.textBaseline = "middle";
        var tubeBottom = tubeBottomCy + rad;
        var vY = Math.max(liqTopY + 12, (liqTopY + tubeBottom) / 2);
        vY = Math.min(vY, tubeBottom - 10);  // never overflow below the tube
        ctx.fillStyle = "rgba(0,0,0,0.45)";
        ctx.fillText(valueText, cx + 0.5, vY + 1.5);
        ctx.fillStyle = Ink.css(fillColor || "rgba(255,238,200,0.96)");
        ctx.shadowColor = "rgba(0,0,0,0.6)"; ctx.shadowBlur = 3;
        ctx.fillText(valueText, cx, vY);
        ctx.shadowBlur = 0;
        ctx.textAlign = "left"; ctx.textBaseline = "alphabetic";
    }

    // Label below the tube
    if (label) {
        ctx.font = "600 " + Math.round(w * 0.26 * ts) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
        ctx.fillStyle = Ink.css(toRgba(LB, 0.85));
        ctx.textAlign = "center";
        ctx.fillText(label, cx, y + h + Math.round(w * 0.34 * ts));
        ctx.textAlign = "left";
    }

    ctx.restore();
}

// Optional circular gauge dial (alt stats style)
function paintArcDial(ctx, cx, cy, r, pct, label, valueText, fontFamily, accentColor, glowColor) {
    ctx.save();
    pct = Math.max(0, Math.min(100, pct));
    var start = Math.PI * 0.75;
    var sweep = Math.PI * 1.5;
    // track
    ctx.strokeStyle = toRgba(LEADING_DEEP, 0.6);
    ctx.lineWidth = 5; ctx.lineCap = "round";
    ctx.beginPath(); ctx.arc(cx, cy, r, start, start + sweep); ctx.stroke();
    // fill
    var fg = ctx.createLinearGradient(cx - r, cy, cx + r, cy);
    fg.addColorStop(0, toRgba(glowColor, 0.8));
    fg.addColorStop(1, LEADING_BRIGHT);
    ctx.strokeStyle = fg; ctx.lineWidth = 5;
    ctx.shadowColor = toRgba(accentColor, 0.7); ctx.shadowBlur = 5;
    ctx.beginPath(); ctx.arc(cx, cy, r, start, start + sweep * (pct/100)); ctx.stroke();
    ctx.shadowBlur = 0;
    // value
    ctx.font = "600 " + Math.round(r*0.5) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
    ctx.fillStyle = Ink.css(VFD_AMBER);
    ctx.textAlign = "center"; ctx.textBaseline = "middle";
    ctx.fillText(valueText, cx, cy - r*0.05);
    ctx.font = "600 " + Math.round(r*0.26) + "px " + (fontFamily ? "'" + fontFamily + "', serif" : "serif");
    ctx.fillStyle = Ink.css(toRgba(LEADING_BRIGHT, 0.8));
    ctx.fillText(label, cx, cy + r*0.45);
    ctx.textAlign = "left"; ctx.textBaseline = "alphabetic";
    ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
// SHARED — horizontal filigree divider
// ═══════════════════════════════════════════════════════════════
function paintFiligreeRow(ctx, x, y, w, accentColor) {
    ctx.save();
    var cx = x + w/2;
    var g = ctx.createLinearGradient(x, y, x+w, y);
    g.addColorStop(0, "rgba(74,50,8,0)");
    g.addColorStop(0.5, LEADING_BRIGHT);
    g.addColorStop(1, "rgba(74,50,8,0)");
    ctx.strokeStyle = g; ctx.lineWidth = 0.9;
    ctx.beginPath(); ctx.moveTo(x, y); ctx.lineTo(x+w, y); ctx.stroke();
    ctx.strokeStyle = toRgba(LEADING_BRIGHT, 0.7); ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.moveTo(cx-8, y); ctx.quadraticCurveTo(cx-22, y-6, cx-36, y);
    ctx.quadraticCurveTo(cx-50, y+6, cx-58, y); ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(cx+8, y); ctx.quadraticCurveTo(cx+22, y-6, cx+36, y);
    ctx.quadraticCurveTo(cx+50, y+6, cx+58, y); ctx.stroke();
    ctx.fillStyle = toRgba(accentColor, 0.9);
    ctx.strokeStyle = LEADING_BRIGHT; ctx.lineWidth = 0.7;
    ctx.beginPath(); ctx.arc(cx, y, 5, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.fillStyle = "rgba(255,230,170,1)";
    ctx.beginPath(); ctx.arc(cx, y, 1.6, 0, Math.PI*2); ctx.fill();
    ctx.restore();
}
