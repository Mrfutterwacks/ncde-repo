// mucha-weather-window.js — the Space card's orrery seen through a window,
// with the real weather outside (2026-09-24, operator: "the scene would have
// rain or whatever like a window one is looking out"; new animation approved
// for this feature only).
//
// paintWeather(ctx, W, H, t, sky, day, accent, glow)
//   sky  = WeatherLive.sky: { kind, level 1..3, windDir (deg FROM, -1 var),
//          windKt, hail, pellets }  — kinds: clear cloudy fog rain storm
//          sleet snow hail tornado. "clear" paints nothing (the orrery as-is).
//   day  = 0 (night) .. 1 (noon) — the sky brightness SpacePanel already has.
//   t    = seconds; every particle is a pure function of (index, t), so there
//          is no particle state to leak, drift or reset.
// Everything of one kind is batched into ONE path + ONE stroke/fill: a canvas
// call per particle is what makes QML Canvas expensive.
.pragma library
.import "ncde-color.js" as Col   // autumn leaves take the Iris palette (2026-09-26)

function hash(n) {                       // deterministic 0..1 per index
    var s = Math.sin(n * 127.1 + 311.7) * 43758.5453;
    return s - Math.floor(s);
}

function rgba(c, a) {
    return "rgba(" + Math.round(c.r * 255) + "," + Math.round(c.g * 255) + "," + Math.round(c.b * 255) + "," + a + ")";
}

// East-west push of the wind across the window, -1..1 (+ = to the right).
// Wind FROM 270 (west) blows east -> particles lean right.
function slantOf(sky) {
    if (!sky || sky.windDir < 0 || !sky.windKt) return 0;
    var vx = -Math.sin(sky.windDir * Math.PI / 180);
    return Math.max(-0.9, Math.min(0.9, vx * sky.windKt / 28));
}

// ── sky veils ──────────────────────────────────────────────────
function veil(ctx, W, H, top, bottom) {
    var g = ctx.createLinearGradient(0, 0, 0, H);
    g.addColorStop(0, top); g.addColorStop(1, bottom);
    ctx.fillStyle = g; ctx.fillRect(0, 0, W, H);
}

// Soft drifting cloud bank across the top of the window.
// moonlit (2026-10-01): night cloud cover is lit from below/by the moon — drawn in the old dark slate it was
// invisible against the night sky (operator: the orrery showed no weather while the card said cloudy).
function clouds(ctx, W, H, t, n, alpha, dark, ceiling, moonlit) {
    var col = moonlit ? "110,118,140" : dark ? "46,50,62" : "196,202,214";
    for (var i = 0; i < n; i++) {
        var speed = 3 + hash(i + 7) * 5;
        var span = W + 160;
        var x = ((hash(i) * span + t * speed) % span) - 80;
        var y = H * ceiling * (0.25 + hash(i + 3) * 0.9);
        var r = 28 + hash(i + 11) * 34;
        for (var k = 0; k < 4; k++) {
            var px = x + (k - 1.5) * r * 0.55, py = y + Math.sin(k * 1.7 + i) * r * 0.18;
            var rr = r * (0.6 + 0.4 * hash(i * 4 + k));
            var g = ctx.createRadialGradient(px, py, 0, px, py, rr);
            g.addColorStop(0, "rgba(" + col + "," + alpha + ")");
            g.addColorStop(1, "rgba(" + col + ",0)");
            ctx.fillStyle = g;
            ctx.fillRect(px - rr, py - rr, rr * 2, rr * 2);
        }
    }
}

// ── precipitation ──────────────────────────────────────────────
function rain(ctx, W, H, t, n, slant, alpha, seed) {
    var fall = H * 1.25;
    ctx.beginPath();
    for (var i = 0; i < n; i++) {
        var sp = 430 + hash(i + seed) * 220;
        var len = 13 + hash(i + seed + 2) * 14;
        var y = ((hash(i + seed + 1) * fall + t * sp) % fall) - H * 0.12;
        var x0 = hash(i + seed + 3) * (W + H) - H * 0.5;
        var x = x0 + slant * y;
        if (x < -20 || x > W + 20) continue;
        ctx.moveTo(x, y); ctx.lineTo(x - slant * len, y - len);
    }
    ctx.strokeStyle = "rgba(170,196,235," + (alpha * 0.45) + ")";
    ctx.lineWidth = 2.6; ctx.stroke();
    ctx.strokeStyle = "rgba(225,236,252," + alpha + ")";
    ctx.lineWidth = 1.1; ctx.stroke();
}

// Beads on the glass: sit still, now and then one lets go and runs down.
function beads(ctx, W, H, t, n) {
    ctx.beginPath();
    for (var i = 0; i < n; i++) {
        var bx = hash(i + 50) * W, by = hash(i + 51) * H * 0.9;
        var cycle = 7 + hash(i + 52) * 9, ph = (t / cycle + hash(i + 53)) % 1;
        var run = ph > 0.8 ? (ph - 0.8) / 0.2 : 0;          // last 20% of its cycle: runs
        var y = by + run * run * H * 0.5;
        var r = 1.2 + hash(i + 54) * 1.6;
        ctx.moveTo(bx + r, y); ctx.arc(bx, y, r, 0, Math.PI * 2);
    }
    ctx.fillStyle = "rgba(220,235,255,0.20)"; ctx.fill();
    ctx.strokeStyle = "rgba(255,255,255,0.35)"; ctx.lineWidth = 0.6; ctx.stroke();
}

function flakes(ctx, W, H, t, n, slant, seed) {
    var fall = H * 1.15;
    ctx.beginPath();
    for (var i = 0; i < n; i++) {
        var sp = 22 + hash(i + seed) * 38;
        var y = ((hash(i + seed + 1) * fall + t * sp) % fall) - H * 0.08;
        var x = hash(i + seed + 2) * (W + 60) - 30 + slant * y * 0.7
                + Math.sin(t * (0.8 + hash(i + seed + 4)) + i) * 6;
        var r = 0.8 + hash(i + seed + 3) * 1.9;
        ctx.moveTo(x + r, y); ctx.arc(x, y, r, 0, Math.PI * 2);
    }
    ctx.fillStyle = "rgba(250,252,255,0.85)"; ctx.fill();
}

function pellets(ctx, W, H, t, n, slant, seed, r, sp0, alpha) {
    var fall = H * 1.2;
    var trails = [];
    ctx.beginPath();
    for (var i = 0; i < n; i++) {
        var sp = sp0 + hash(i + seed) * 160;
        var y = ((hash(i + seed + 1) * fall + t * sp) % fall) - H * 0.1;
        var x = hash(i + seed + 2) * (W + H) - H * 0.5 + slant * y;
        if (x < -10 || x > W + 10) continue;
        var rr = r * (0.7 + hash(i + seed + 3) * 0.6);
        ctx.moveTo(x + rr, y); ctx.arc(x, y, rr, 0, Math.PI * 2);
        if (r >= 1.5) trails.push([x, y, rr]);
    }
    ctx.fillStyle = "rgba(240,246,255," + alpha + ")"; ctx.fill();
    ctx.strokeStyle = "rgba(120,140,170,0.6)"; ctx.lineWidth = 0.7; ctx.stroke();
    if (trails.length) {
        ctx.beginPath();
        trails.forEach(function (p) { ctx.moveTo(p[0], p[1] - p[2]); ctx.lineTo(p[0] - slant * 9, p[1] - p[2] - 9); });
        ctx.strokeStyle = "rgba(235,242,255,0.35)"; ctx.lineWidth = p0w(r); ctx.stroke();
    }
}
function p0w(r) { return Math.max(1, r * 0.9); }

// Frost / glaze creeping in from the window's edges.
function frost(ctx, W, H, amt) {
    var e = Math.min(W, H) * 0.32 * amt;
    [[0, 0], [W, 0], [0, H], [W, H]].forEach(function (c) {
        var g = ctx.createRadialGradient(c[0], c[1], 0, c[0], c[1], e);
        g.addColorStop(0, "rgba(232,242,255," + (0.42 * amt) + ")");
        g.addColorStop(1, "rgba(232,242,255,0)");
        ctx.fillStyle = g; ctx.fillRect(c[0] - e, c[1] - e, e * 2, e * 2);
    });
}

// ── lightning ──────────────────────────────────────────────────
// A strike every ~4-9 s: sheet flash over the pane + a forked bolt, flickered.
function lightning(ctx, W, H, t, rate) {
    var period = 6.5 / rate;
    var cyc = Math.floor(t / period);
    if (hash(cyc * 3 + 1) > 0.75) return;                 // some cycles stay dark
    var dt = t - (cyc * period + hash(cyc * 3 + 2) * period * 0.6);
    if (dt < 0 || dt > 0.5) return;
    var f = dt < 0.08 ? 1 : dt < 0.14 ? 0.25 : dt < 0.2 ? 0.85 : Math.max(0, 1 - (dt - 0.2) / 0.3);
    ctx.fillStyle = "rgba(225,228,255," + (0.30 * f) + ")";
    ctx.fillRect(0, 0, W, H);
    var x = W * (0.15 + hash(cyc * 3 + 3) * 0.7), y = 0;
    ctx.beginPath(); ctx.moveTo(x, y);
    var k = 0, forks = [];
    while (y < H * 0.62) {
        x += (hash(cyc * 31 + k) - 0.5) * 22; y += 8 + hash(cyc * 17 + k) * 12;
        ctx.lineTo(x, y);
        if (hash(cyc * 7 + k) > 0.8) forks.push([x, y, k]);
        k++;
    }
    forks.forEach(function (p) {
        var fx = p[0], fy = p[1];
        ctx.moveTo(fx, fy);
        for (var j = 0; j < 4; j++) {
            fx += (hash(p[2] * 13 + j) - 0.3) * 18; fy += 7 + hash(p[2] * 5 + j) * 8;
            ctx.lineTo(fx, fy);
        }
    });
    ctx.strokeStyle = "rgba(200,190,255," + (0.35 * f) + ")"; ctx.lineWidth = 4; ctx.stroke();
    ctx.strokeStyle = "rgba(255,255,255," + (0.95 * f) + ")"; ctx.lineWidth = 1.3; ctx.stroke();
}

// ── tornado ────────────────────────────────────────────────────
function funnel(ctx, W, H, t) {
    var baseX = W * 0.66 + Math.sin(t * 0.35) * W * 0.06;
    var top = H * 0.10, bot = H * 0.80, rings = 26;
    ctx.beginPath();
    for (var s = 0; s <= 20; s++) {                       // left edge down
        var u0 = s / 20, w0 = 64 * Math.pow(1 - u0, 1.6) + 5;
        var x0 = baseX + Math.sin(t * 1.3 + u0 * 3.2) * 10 * u0 - w0;
        if (s === 0) ctx.moveTo(x0, top + (bot - top) * u0); else ctx.lineTo(x0, top + (bot - top) * u0);
    }
    for (s = 20; s >= 0; s--) {                           // right edge back up
        var u1 = s / 20, w1 = 64 * Math.pow(1 - u1, 1.6) + 5;
        ctx.lineTo(baseX + Math.sin(t * 1.3 + u1 * 3.2) * 10 * u1 + w1, top + (bot - top) * u1);
    }
    ctx.closePath();
    var fg = ctx.createLinearGradient(baseX - 60, 0, baseX + 60, 0);
    fg.addColorStop(0, "rgba(52,56,54,0.55)"); fg.addColorStop(0.45, "rgba(92,98,92,0.78)"); fg.addColorStop(1, "rgba(36,40,38,0.6)");
    ctx.fillStyle = fg; ctx.fill();
    for (var k = 0; k < rings; k++) {
        var u = k / (rings - 1);
        var y = top + (bot - top) * u;
        var w = 64 * Math.pow(1 - u, 1.6) + 5;
        var sway = Math.sin(t * 1.3 + u * 3.2) * 10 * u;
        var spin = t * 7 + k * 0.9;
        ctx.beginPath();
        ctx.ellipse(baseX + sway - w, y - w * 0.14, w * 2, w * 0.28);
        ctx.strokeStyle = "rgba(150,156,146," + (0.45 - 0.3 * Math.abs(Math.sin(spin))) + ")";
        ctx.lineWidth = 1.6; ctx.stroke();
    }
    // debris orbiting the touchdown
    ctx.beginPath();
    for (var i = 0; i < 26; i++) {
        var a = t * (2.5 + hash(i) * 2) + i;
        var rr = 10 + hash(i + 9) * 26;
        var dx = baseX + Math.sin(t * 1.3 + 3.2) * 10 + Math.cos(a) * rr;
        var dy = bot - 4 - Math.abs(Math.sin(a * 0.5)) * 16 * hash(i + 4);
        ctx.moveTo(dx + 1.4, dy); ctx.arc(dx, dy, 1.4, 0, Math.PI * 2);
    }
    ctx.fillStyle = "rgba(40,36,30,0.75)"; ctx.fill();
}

// ── autumn leaves (2026-09-26, operator: "maybe falling leaves for autumn?
// seasonal") ──────────────────────────────────────────────────────────────
// One leaf, painted ONCE into an s×s canvas, stem down, pointing up; SpacePanel
// moves the painted leaf (anim-policy.md: paint once, move the image). Stained
// glass like the Earth: an amber / rust / gold / crimson pane (pulled a touch
// toward the Iris accent), set in dark lead with a thin gilt midrib and veins.
var LEAF_HUES = ["#c9812a", "#a8472a", "#caa13c", "#8e2a33"];
function paintLeaf(ctx, s, variant, accent, leading) {
    ctx.clearRect(0, 0, s, s);
    var base = Col.harmonize(LEAF_HUES[variant % LEAF_HUES.length], accent, undefined, undefined, 0.12);
    var cx = s / 2, top = s * 0.08, bot = s * 0.80, half = s * 0.30;
    ctx.save();
    ctx.beginPath();                               // an ovate leaf with a drawn-out tip
    ctx.moveTo(cx, top);
    ctx.bezierCurveTo(cx + half * 1.25, s * 0.30, cx + half * 0.95, s * 0.68, cx, bot);
    ctx.bezierCurveTo(cx - half * 0.95, s * 0.68, cx - half * 1.25, s * 0.30, cx, top);
    ctx.closePath();
    var g = ctx.createRadialGradient(cx - s * 0.08, s * 0.38, 0, cx, s * 0.45, s * 0.46);
    g.addColorStop(0, Col.css(Col.shade(base, 14), 0.95));
    g.addColorStop(1, Col.css(Col.shade(base, -8), 0.92));
    ctx.fillStyle = g; ctx.fill();
    ctx.lineJoin = "round";
    ctx.strokeStyle = "rgba(30,24,20,0.85)"; ctx.lineWidth = Math.max(1, s * 0.07); ctx.stroke();
    var gilt = Col.css(leading || "#c9a24a", 0.9);
    ctx.beginPath();                               // midrib + stem
    ctx.moveTo(cx, top + s * 0.06); ctx.lineTo(cx, s * 0.96);
    for (var k = 1; k <= 3; k++) {                 // veins
        var vy = top + (bot - top) * (0.22 + 0.2 * k);
        ctx.moveTo(cx, vy); ctx.lineTo(cx + half * (0.75 - 0.12 * k), vy - s * 0.10);
        ctx.moveTo(cx, vy); ctx.lineTo(cx - half * (0.75 - 0.12 * k), vy - s * 0.10);
    }
    ctx.strokeStyle = gilt; ctx.lineWidth = Math.max(0.6, s * 0.035); ctx.stroke();
    ctx.restore();
}

// Spring: one blossom petal, pale pink glass with the notched tip of a cherry
// petal, a fine gilt rim — painted once, stem end down.
function paintPetal(ctx, s, variant, accent, leading) {
    ctx.clearRect(0, 0, s, s);
    var base = Col.harmonize(["#f2c4cf", "#f7dbe2", "#eab3c3"][variant % 3], accent, undefined, undefined, 0.10);
    var cx = s / 2, top = s * 0.14, bot = s * 0.86, half = s * 0.26;
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(cx, bot);
    ctx.bezierCurveTo(cx + half * 1.5, s * 0.66, cx + half * 1.2, top, cx + half * 0.28, top + s * 0.03);
    ctx.lineTo(cx, top + s * 0.12);                                  // the notch
    ctx.lineTo(cx - half * 0.28, top + s * 0.03);
    ctx.bezierCurveTo(cx - half * 1.2, top, cx - half * 1.5, s * 0.66, cx, bot);
    ctx.closePath();
    var g = ctx.createRadialGradient(cx, s * 0.72, 0, cx, s * 0.5, s * 0.46);
    g.addColorStop(0, Col.css(Col.shade(base, -10), 0.95));
    g.addColorStop(1, Col.css(Col.shade(base, 8), 0.9));
    ctx.fillStyle = g; ctx.fill();
    ctx.strokeStyle = Col.css(leading || "#c9a24a", 0.7); ctx.lineWidth = Math.max(0.6, s * 0.04); ctx.stroke();
    ctx.restore();
}

// Summer day: a dandelion seed — a dark seed, a fine stalk and a white parasol
// of filaments, painted once.
function paintSeed(ctx, s, variant, accent, leading) {
    ctx.clearRect(0, 0, s, s);
    var cx = s / 2, top = s * 0.30, bot = s * 0.90;
    ctx.save();
    ctx.strokeStyle = "rgba(245,242,230,0.85)"; ctx.lineWidth = Math.max(0.5, s * 0.025);
    ctx.beginPath();
    ctx.moveTo(cx, bot); ctx.lineTo(cx, top);                        // stalk
    for (var k = 0; k < 11; k++) {                                   // the parasol
        var a = Math.PI * (1.08 + 0.84 * k / 10);
        ctx.moveTo(cx, top); ctx.lineTo(cx + Math.cos(a) * s * 0.34, top + Math.sin(a) * s * 0.26);
    }
    ctx.stroke();
    ctx.fillStyle = Col.css(leading || "#c9a24a", 0.8);
    ctx.beginPath(); ctx.ellipse(cx - s * 0.03, bot - s * 0.08, s * 0.06, s * 0.1); ctx.fill();
    ctx.restore();
}

// Summer night: a firefly — a warm yellow-green glow with a bright heart.
function paintFirefly(ctx, s, variant, accent, leading) {
    ctx.clearRect(0, 0, s, s);
    var c = s / 2;
    var g = ctx.createRadialGradient(c, c, 0, c, c, s * 0.48);
    g.addColorStop(0, "rgba(250,255,190,1)");
    g.addColorStop(0.18, "rgba(220,240,120,0.85)");
    g.addColorStop(0.5, "rgba(170,210,80,0.25)");
    g.addColorStop(1, "rgba(150,200,60,0)");
    ctx.fillStyle = g; ctx.fillRect(0, 0, s, s);
}

// Winter (dry days): diamond dust — a tiny six-armed ice crystal that catches
// the light. Real on cold clear days; snow itself shows only when it snows.
function paintCrystal(ctx, s, variant, accent, leading) {
    ctx.clearRect(0, 0, s, s);
    var c = s / 2, r = s * (0.22 + 0.05 * (variant % 3));
    var g = ctx.createRadialGradient(c, c, 0, c, c, s * 0.42);
    g.addColorStop(0, "rgba(235,245,255,0.55)");
    g.addColorStop(1, "rgba(200,225,255,0)");
    ctx.fillStyle = g; ctx.fillRect(0, 0, s, s);
    ctx.save();
    ctx.strokeStyle = "rgba(240,248,255,0.95)"; ctx.lineWidth = Math.max(0.6, s * 0.04); ctx.lineCap = "round";
    ctx.beginPath();
    for (var k = 0; k < 6; k++) {
        var a = k * Math.PI / 3, ex = c + Math.cos(a) * r, ey = c + Math.sin(a) * r;
        ctx.moveTo(c, c); ctx.lineTo(ex, ey);
        var bx = c + Math.cos(a) * r * 0.6, by = c + Math.sin(a) * r * 0.6;   // side barbs
        ctx.moveTo(bx, by); ctx.lineTo(bx + Math.cos(a + 0.8) * r * 0.25, by + Math.sin(a + 0.8) * r * 0.25);
        ctx.moveTo(bx, by); ctx.lineTo(bx + Math.cos(a - 0.8) * r * 0.25, by + Math.sin(a - 0.8) * r * 0.25);
    }
    ctx.stroke();
    ctx.restore();
}

function paintDrift(ctx, s, kind, variant, accent, leading) {
    if (kind === "petal") paintPetal(ctx, s, variant, accent, leading);
    else if (kind === "seed") paintSeed(ctx, s, variant, accent, leading);
    else if (kind === "firefly") paintFirefly(ctx, s, variant, accent, leading);
    else if (kind === "crystal") paintCrystal(ctx, s, variant, accent, leading);
    else paintLeaf(ctx, s, variant, accent, leading);
}

// ── compositor ─────────────────────────────────────────────────
function paintWeather(ctx, W, H, t, sky, day, accent, glow) {
    ctx.clearRect(0, 0, W, H);
    if (!sky || !sky.kind || sky.kind === "clear") return false;
    var lv = Math.max(1, Math.min(3, sky.level || 2));
    var sl = slantOf(sky);
    var night = day < 0.35;
    ctx.save();
    switch (sky.kind) {
    case "cloudy":
        veil(ctx, W, H, "rgba(40,46,60," + (0.18 * lv) + ")", "rgba(40,46,60," + (0.06 * lv) + ")");
        clouds(ctx, W, H, t, 3 + lv * 2, night ? 0.30 : 0.42, false, 0.45, night);
        break;
    case "fog":
        veil(ctx, W, H, "rgba(170,178,190," + (0.20 + 0.12 * lv) + ")", "rgba(190,196,206," + (0.30 + 0.14 * lv) + ")");
        clouds(ctx, W, H, t * 0.6, 7, 0.28, false, 1.0, night);
        break;
    case "rain":
        veil(ctx, W, H, "rgba(26,32,46," + (0.14 + 0.08 * lv) + ")", "rgba(26,32,46,0.06)");
        clouds(ctx, W, H, t, 4 + lv, 0.35, true, 0.3);
        rain(ctx, W, H, t, [45, 90, 140][lv - 1], sl, 0.34 + 0.1 * lv, 0);
        beads(ctx, W, H, t, 10 + lv * 6);
        break;
    case "storm":
        veil(ctx, W, H, "rgba(12,14,26," + (0.42 + 0.08 * lv) + ")", "rgba(12,14,26,0.22)");
        clouds(ctx, W, H, t * 1.6, 7, 0.45, true, 0.35);
        rain(ctx, W, H, t, [90, 125, 150][lv - 1], sl + (sl >= 0 ? 0.15 : -0.15), 0.62, 0);
        if (sky.hail) pellets(ctx, W, H, t, 26, sl, 400, 1.8, 480, 0.9);
        beads(ctx, W, H, t, 22);
        lightning(ctx, W, H, t, lv >= 3 ? 1.4 : 1);
        break;
    case "sleet":
        veil(ctx, W, H, "rgba(40,46,58," + (0.18 + 0.06 * lv) + ")", "rgba(60,68,80,0.10)");
        clouds(ctx, W, H, t, 5, 0.35, true, 0.3);
        rain(ctx, W, H, t, [25, 45, 70][lv - 1], sl, 0.22, 200);
        pellets(ctx, W, H, t, [40, 70, 105][lv - 1], sl, 300, 1.5, 340, 0.85);
        frost(ctx, W, H, 0.55 + 0.15 * lv);
        break;
    case "snow":
        veil(ctx, W, H, "rgba(70,78,96," + (0.14 + 0.06 * lv) + ")", "rgba(200,208,222," + (0.04 * lv) + ")");
        clouds(ctx, W, H, t, 5, 0.30, night, 0.3);
        flakes(ctx, W, H, t, [45, 85, 140][lv - 1], sl, 0);
        if (sky.pellets) pellets(ctx, W, H, t, 30, sl, 300, 1.0, 340, 0.7);
        frost(ctx, W, H, 0.6 + 0.2 * lv);
        break;
    case "hail":
        veil(ctx, W, H, "rgba(30,36,50,0.32)", "rgba(30,36,50,0.12)");
        clouds(ctx, W, H, t, 6, 0.40, true, 0.3);
        rain(ctx, W, H, t, 50, sl, 0.25, 0);
        pellets(ctx, W, H, t, [30, 50, 80][lv - 1], sl, 400, 2.4, 460, 0.95);
        beads(ctx, W, H, t, 16);
        break;
    case "tornado":
        veil(ctx, W, H, "rgba(38,52,40,0.55)", "rgba(30,34,28,0.35)");   // the green-grey tornado sky
        clouds(ctx, W, H, t * 2.2, 9, 0.55, true, 0.22);
        funnel(ctx, W, H, t);
        rain(ctx, W, H, t, 110, sl + 0.35, 0.35, 0);
        beads(ctx, W, H, t, 20);
        lightning(ctx, W, H, t, 1.2);
        break;
    }
    ctx.restore();
    return true;
}
