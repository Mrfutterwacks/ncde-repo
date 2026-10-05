// mucha-wx-icons.js — Mucha stained-glass weather icons for NCDE.
// Pure Canvas 2D, .pragma library. Leaded-gold outlines, accent/glow glass fills.
// Drawn to fill a 0..W / 0..H box (the .qml clips them into the rose roundel).
//
// Dispatcher:  drawMuchaWxIcon(ctx, W, H, code, accentColor, glowColor)
//   code = Yahoo-style weather code (string or int), same codes the project's
//   widget_data.weatherIcon already emits. Unknown codes fall back to "cloudy".
//
// Leaded gold hardcoded per CLAUDE.md "Mucha art JS" exemption.
.pragma library

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
    return c;
}

// ── SUN — leaded-glass disc with 12 tapered gold rays ──────────
function wxSun(ctx, cx, cy, R, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    // Rays
    ctx.translate(cx, cy);
    for (var i = 0; i < 12; i++) {
        ctx.save();
        ctx.rotate((i / 12) * Math.PI * 2);
        var grd = ctx.createLinearGradient(0, -R*1.1, 0, -R*1.55);
        grd.addColorStop(0, LB);
        grd.addColorStop(1, toRgba(accentColor, 0.2));
        ctx.fillStyle = grd;
        ctx.beginPath();
        ctx.moveTo(-R*0.10, -R*1.12);
        ctx.lineTo(0, -R*1.55);
        ctx.lineTo(R*0.10, -R*1.12);
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
    ctx.translate(-cx, -cy);
    // Disc — radial stained glass
    var g = ctx.createRadialGradient(cx - R*0.25, cy - R*0.25, 0, cx, cy, R);
    g.addColorStop(0, "rgba(255, 240, 185, 1)");
    g.addColorStop(0.55, toRgba(accentColor, 0.9));
    g.addColorStop(1, toRgba(glowColor, 0.7));
    ctx.fillStyle = g;
    ctx.shadowColor = toRgba(accentColor, 0.8);
    ctx.shadowBlur = R * 0.5;
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2); ctx.fill();
    ctx.shadowBlur = 0;
    // leaded rim + inner radial leading
    ctx.strokeStyle = LB; ctx.lineWidth = 1.4;
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2); ctx.stroke();
    ctx.strokeStyle = toRgba(LEADING, 0.5); ctx.lineWidth = 0.7;
    for (var k = 0; k < 6; k++) {
        var a = (k / 6) * Math.PI*2;
        ctx.beginPath();
        ctx.moveTo(cx + Math.cos(a)*R*0.3, cy + Math.sin(a)*R*0.3);
        ctx.lineTo(cx + Math.cos(a)*R, cy + Math.sin(a)*R);
        ctx.stroke();
    }
    ctx.strokeStyle = toRgba(LEADING, 0.5); ctx.lineWidth = 0.7;
    ctx.beginPath(); ctx.arc(cx, cy, R*0.45, 0, Math.PI*2); ctx.stroke();
    ctx.restore();
}

// ── MOON — leaded crescent with a couple of stars ──────────────
function wxMoon(ctx, cx, cy, R, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    // Crescent via two arcs
    var g = ctx.createRadialGradient(cx - R*0.3, cy - R*0.3, 0, cx, cy, R);
    g.addColorStop(0, "rgba(248, 240, 210, 1)");
    g.addColorStop(0.6, toRgba(glowColor, 0.85));
    g.addColorStop(1, toRgba(accentColor, 0.6));
    ctx.fillStyle = g;
    ctx.shadowColor = toRgba(glowColor, 0.7);
    ctx.shadowBlur = R * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, R, Math.PI*0.30, Math.PI*1.70, false);
    ctx.arc(cx + R*0.55, cy, R*0.92, Math.PI*1.62, Math.PI*0.38, true);
    ctx.closePath();
    ctx.fill();
    ctx.shadowBlur = 0;
    ctx.strokeStyle = LB; ctx.lineWidth = 1.3; ctx.stroke();
    // leaded craters
    ctx.fillStyle = toRgba(LEADING, 0.35);
    ctx.beginPath(); ctx.arc(cx - R*0.3, cy - R*0.1, R*0.13, 0, Math.PI*2); ctx.fill();
    ctx.beginPath(); ctx.arc(cx - R*0.45, cy + R*0.3, R*0.09, 0, Math.PI*2); ctx.fill();
    // stars
    [[cx + R*0.7, cy - R*0.8, 2.2], [cx + R*1.0, cy - R*0.2, 1.6]].forEach(function (s) {
        wxStar(ctx, s[0], s[1], s[2], LB);
    });
    ctx.restore();
}

function wxStar(ctx, x, y, r, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    ctx.fillStyle = LB;
    ctx.shadowColor = LB; ctx.shadowBlur = 5;
    ctx.beginPath();
    for (var i = 0; i < 4; i++) {
        var a = (i / 4) * Math.PI * 2;
        ctx.lineTo(x + Math.cos(a) * r, y + Math.sin(a) * r);
        var a2 = a + Math.PI / 4;
        ctx.lineTo(x + Math.cos(a2) * r * 0.4, y + Math.sin(a2) * r * 0.4);
    }
    ctx.closePath(); ctx.fill();
    ctx.shadowBlur = 0;
    ctx.restore();
}

// ── CLOUD — leaded stained-glass cloud (returns its bbox) ──────
function wxCloud(ctx, cx, cy, R, accentColor, glowColor, tint, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    var col = tint || glowColor;
    var g = ctx.createLinearGradient(cx, cy - R*0.6, cx, cy + R*0.6);
    g.addColorStop(0, toRgba(col, 0.85));
    g.addColorStop(1, toRgba(col, 0.5));
    ctx.fillStyle = g;
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.3;
    ctx.beginPath();
    // puffy outline
    ctx.moveTo(cx - R*0.95, cy + R*0.35);
    ctx.bezierCurveTo(cx - R*1.3, cy + R*0.35, cx - R*1.3, cy - R*0.25, cx - R*0.85, cy - R*0.30);
    ctx.bezierCurveTo(cx - R*0.78, cy - R*0.75, cx - R*0.15, cy - R*0.95, cx + R*0.05, cy - R*0.55);
    ctx.bezierCurveTo(cx + R*0.30, cy - R*0.95, cx + R*0.85, cy - R*0.75, cx + R*0.80, cy - R*0.28);
    ctx.bezierCurveTo(cx + R*1.25, cy - R*0.30, cx + R*1.25, cy + R*0.35, cx + R*0.90, cy + R*0.35);
    ctx.closePath();
    ctx.fill();
    ctx.stroke();
    // a couple of internal leadings
    ctx.strokeStyle = toRgba(LEADING, 0.4); ctx.lineWidth = 0.6;
    ctx.beginPath(); ctx.moveTo(cx - R*0.4, cy - R*0.1); ctx.lineTo(cx - R*0.4, cy + R*0.3); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(cx + R*0.3, cy - R*0.3); ctx.lineTo(cx + R*0.3, cy + R*0.3); ctx.stroke();
    ctx.restore();
}

// ── RAINDROPS / SNOW / BOLT accents under a cloud ──────────────
function wxRain(ctx, cx, baseY, R, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    for (var i = -1; i <= 1; i++) {
        var x = cx + i * R * 0.55;
        var g = ctx.createLinearGradient(x, baseY, x, baseY + R*0.7);
        g.addColorStop(0, toRgba(glowColor, 0.9));
        g.addColorStop(1, toRgba(accentColor, 0.5));
        ctx.fillStyle = g;
        ctx.strokeStyle = LB; ctx.lineWidth = 0.8;
        ctx.beginPath();
        ctx.moveTo(x, baseY);
        ctx.bezierCurveTo(x - R*0.18, baseY + R*0.4, x - R*0.18, baseY + R*0.7, x, baseY + R*0.7);
        ctx.bezierCurveTo(x + R*0.18, baseY + R*0.7, x + R*0.18, baseY + R*0.4, x, baseY);
        ctx.closePath(); ctx.fill(); ctx.stroke();
    }
    ctx.restore();
}

function wxSnow(ctx, cx, baseY, R, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 1.2;
    ctx.shadowColor = toRgba(glowColor, 0.8);
    ctx.shadowBlur = 4;
    for (var i = -1; i <= 1; i++) {
        var x = cx + i * R * 0.55;
        var y = baseY + R * 0.35;
        for (var k = 0; k < 3; k++) {
            var a = (k / 3) * Math.PI;
            ctx.beginPath();
            ctx.moveTo(x - Math.cos(a)*R*0.22, y - Math.sin(a)*R*0.22);
            ctx.lineTo(x + Math.cos(a)*R*0.22, y + Math.sin(a)*R*0.22);
            ctx.stroke();
        }
    }
    ctx.shadowBlur = 0;
    ctx.restore();
}

function wxBolt(ctx, cx, baseY, R, accentColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    var g = ctx.createLinearGradient(cx, baseY, cx, baseY + R*0.9);
    g.addColorStop(0, "rgba(255, 240, 185, 1)");
    g.addColorStop(1, toRgba(accentColor, 0.7));
    ctx.fillStyle = g;
    ctx.strokeStyle = LB; ctx.lineWidth = 0.9;
    ctx.shadowColor = LB; ctx.shadowBlur = 6;
    ctx.beginPath();
    ctx.moveTo(cx + R*0.15, baseY);
    ctx.lineTo(cx - R*0.25, baseY + R*0.5);
    ctx.lineTo(cx + R*0.02, baseY + R*0.5);
    ctx.lineTo(cx - R*0.18, baseY + R*0.95);
    ctx.lineTo(cx + R*0.35, baseY + R*0.38);
    ctx.lineTo(cx + R*0.05, baseY + R*0.38);
    ctx.closePath();
    ctx.fill(); ctx.stroke();
    ctx.shadowBlur = 0;
    ctx.restore();
}

// ── FOG — stacked leaded bars ──────────────────────────────────
function wxFog(ctx, cx, cy, R, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    ctx.strokeStyle = LB;
    ctx.lineCap = "round";
    for (var i = 0; i < 5; i++) {
        var y = cy - R*0.6 + i * R*0.35;
        var w = R * (1.3 - (i % 2) * 0.25);
        ctx.lineWidth = 3;
        ctx.strokeStyle = toRgba(i % 2 === 0 ? glowColor : accentColor, 0.8);
        ctx.shadowColor = toRgba(glowColor, 0.6); ctx.shadowBlur = 3;
        ctx.beginPath();
        ctx.moveTo(cx - w/2, y);
        ctx.lineTo(cx + w/2, y);
        ctx.stroke();
    }
    ctx.shadowBlur = 0;
    ctx.restore();
}

// ── WIND — leaded gust swirls ──────────────────────────────────
function wxWind(ctx, cx, cy, R, accentColor, glowColor, leadingColor) {
    var LB = leadingColor || LEADING_BRIGHT;
    ctx.save();
    ctx.strokeStyle = LB;
    ctx.lineWidth = 2.4;
    ctx.lineCap = "round";
    ctx.shadowColor = toRgba(accentColor, 0.6); ctx.shadowBlur = 4;
    // three gust lines with curled ends
    var lines = [[-0.5, 1.1], [0.0, 1.4], [0.3, 0.9]];
    for (var i = 0; i < lines.length; i++) {
        var y = cy + lines[i][0] * R;
        var w = lines[i][1] * R;
        ctx.beginPath();
        ctx.moveTo(cx - w*0.5, y);
        ctx.lineTo(cx + w*0.3, y);
        ctx.arc(cx + w*0.3, y - R*0.18, R*0.18, Math.PI*0.5, Math.PI*2.2, false);
        ctx.stroke();
    }
    ctx.shadowBlur = 0;
    ctx.restore();
}

// ── Code classification (Yahoo-style) ──────────────────────────
function wxType(code) {
    var c = parseInt(code);
    if (isNaN(c)) return "cloudy";
    // night clear / partly
    if (c === 31 || c === 33) return "moon";
    if (c === 29 || c === 27) return "cloudy-night";
    // sunny / clear day
    if (c === 32 || c === 34 || c === 36) return "sun";
    // partly cloudy day
    if (c === 30 || c === 28 || c === 44) return "cloudy-day";
    // overcast
    if (c === 26 || c === 25) return "cloudy";
    // fog / haze
    if (c === 19 || c === 20 || c === 21 || c === 22 || c === 23 || c === 24) return "fog";
    // wind
    if (c === 15 || c === 16 || c === 17 || c === 18) return "wind";
    // thunder
    if (c === 0 || c === 1 || c === 2 || c === 3 || c === 4 || c === 37 || c === 38 || c === 39 || c === 47) return "thunder";
    // snow / sleet
    if (c === 5 || c === 6 || c === 7 || c === 8 || c === 10 || c === 13 || c === 14 || c === 16 || c === 41 || c === 42 || c === 43 || c === 46) return "snow";
    // rain / showers / drizzle
    if (c === 9 || c === 11 || c === 12 || c === 40 || c === 45) return "rain";
    return "cloudy";
}

// ── Master dispatcher ──────────────────────────────────────────
function drawMuchaWxIcon(ctx, W, H, code, accentColor, glowColor, leadingColor) {
    var cx = W / 2, cy = H / 2;
    var R = Math.min(W, H) * 0.26;
    var type = wxType(code);

    switch (type) {
    case "sun":
        wxSun(ctx, cx, cy, R, accentColor, glowColor, leadingColor);
        break;
    case "moon":
        wxMoon(ctx, cx, cy, R, accentColor, glowColor, leadingColor);
        break;
    case "cloudy-day":
        wxSun(ctx, cx - R*0.45, cy - R*0.45, R*0.62, accentColor, glowColor, leadingColor);
        wxCloud(ctx, cx + R*0.15, cy + R*0.30, R*0.85, accentColor, glowColor, undefined, leadingColor);
        break;
    case "cloudy-night":
        wxMoon(ctx, cx - R*0.45, cy - R*0.50, R*0.6, accentColor, glowColor, leadingColor);
        wxCloud(ctx, cx + R*0.15, cy + R*0.30, R*0.85, accentColor, glowColor, undefined, leadingColor);
        break;
    case "cloudy":
        wxCloud(ctx, cx - R*0.25, cy - R*0.2, R*0.75, accentColor, glowColor, accentColor, leadingColor);
        wxCloud(ctx, cx + R*0.30, cy + R*0.15, R*0.95, accentColor, glowColor, undefined, leadingColor);
        break;
    case "rain":
        wxCloud(ctx, cx, cy - R*0.35, R*0.95, accentColor, glowColor, undefined, leadingColor);
        wxRain(ctx, cx, cy + R*0.55, R, accentColor, glowColor, leadingColor);
        break;
    case "snow":
        wxCloud(ctx, cx, cy - R*0.35, R*0.95, accentColor, glowColor, undefined, leadingColor);
        wxSnow(ctx, cx, cy + R*0.55, R, accentColor, glowColor, leadingColor);
        break;
    case "thunder":
        wxCloud(ctx, cx, cy - R*0.4, R*0.95, accentColor, glowColor, undefined, leadingColor);
        wxBolt(ctx, cx, cy + R*0.5, R, accentColor, leadingColor);
        break;
    case "fog":
        wxFog(ctx, cx, cy, R, accentColor, glowColor, leadingColor);
        break;
    case "wind":
        wxWind(ctx, cx, cy, R, accentColor, glowColor, leadingColor);
        break;
    default:
        wxCloud(ctx, cx, cy, R, accentColor, glowColor, undefined, leadingColor);
    }
}
