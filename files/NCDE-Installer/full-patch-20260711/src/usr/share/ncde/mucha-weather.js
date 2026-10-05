.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA WEATHER ICONS — pure Canvas replacements for the
//  WeatherIcons/ PNG set. Designed at 64×64 (scale by W/H).
//
//  Usage from QML:
//      Canvas {
//        property int wx: parseInt(widget_data.weatherIcon) || 32
//        onPaint: drawMuchaWeather(getContext("2d"), width, height, wx)
//        onWxChanged: requestPaint()
//      }
//
//  Maps Yahoo weather codes (0..47) → 16 Mucha glyphs.
// ═══════════════════════════════════════════════════════════════

function muchaWeatherType(code) {
  // Normalize Yahoo weather code to a Mucha icon type
  // Clear / sunny
  if (code === 32 || code === 34 || code === 36) return "sun";
  // Clear night
  if (code === 31 || code === 33)                return "moon";
  // Partly cloudy (day)
  if (code === 30 || code === 44)                return "sun-cloud";
  // Partly cloudy (night)
  if (code === 29)                               return "moon-cloud";
  // Mostly cloudy
  if (code === 27 || code === 28 || code === 26) return "cloud";
  // Rain (day/night same — Mucha is timeless)
  if (code === 11 || code === 12 || code === 40 || code === 45 || code === 39)
    return "rain";
  // Drizzle / light rain
  if (code === 9 || code === 8 || code === 10)   return "drizzle";
  // Thunderstorm
  if (code === 3 || code === 4 || code === 37 || code === 38 || code === 47)
    return "thunder";
  // Snow
  if (code === 13 || code === 14 || code === 16 || code === 41 ||
      code === 42 || code === 43 || code === 46)
    return "snow";
  // Sleet / mixed
  if (code === 5 || code === 6 || code === 7 || code === 18) return "sleet";
  // Hail
  if (code === 17 || code === 35) return "hail";
  // Fog / haze / dust
  if (code === 19 || code === 20 || code === 21 || code === 22) return "fog";
  // Wind / blustery
  if (code === 15 || code === 23 || code === 24) return "wind";
  // Tornado / hurricane / tropical storm
  if (code === 0 || code === 1 || code === 2) return "tornado";
  // Cold
  if (code === 25) return "cold";
  return "sun";
}

function drawMuchaWeather(ctx, W, H, code) {
  ctx.clearRect(0, 0, W, H);
  var t = muchaWeatherType(code);

  // Common atmospheric wash behind every icon
  var atm = ctx.createRadialGradient(W / 2, H / 2, 0, W / 2, H / 2, W * 0.55);
  atm.addColorStop(0.0, "rgba(232,212,148,0.10)");
  atm.addColorStop(1.0, "rgba(0,0,0,0)");
  ctx.fillStyle = atm;
  ctx.fillRect(0, 0, W, H);

  switch (t) {
    case "sun":         drawWxSun        (ctx, W, H); break;
    case "moon":        drawWxMoon       (ctx, W, H); break;
    case "sun-cloud":   drawWxSunCloud   (ctx, W, H); break;
    case "moon-cloud":  drawWxMoonCloud  (ctx, W, H); break;
    case "cloud":       drawWxCloud      (ctx, W, H); break;
    case "rain":        drawWxRain       (ctx, W, H); break;
    case "drizzle":     drawWxDrizzle    (ctx, W, H); break;
    case "thunder":     drawWxThunder    (ctx, W, H); break;
    case "snow":        drawWxSnow       (ctx, W, H); break;
    case "sleet":       drawWxSleet      (ctx, W, H); break;
    case "hail":        drawWxHail       (ctx, W, H); break;
    case "fog":         drawWxFog        (ctx, W, H); break;
    case "wind":        drawWxWind       (ctx, W, H); break;
    case "tornado":     drawWxTornado    (ctx, W, H); break;
    case "cold":        drawWxCold       (ctx, W, H); break;
  }

  // Lithograph grain if available
  if (typeof applyMuchaGrain === "function") {
    applyMuchaGrain(ctx, W, H, code * 11 + 7, 0.45);
  }
}

// ═══════════════════════════════════════════════════════════════
//  Atomic Mucha symbols
// ═══════════════════════════════════════════════════════════════

// Small Mucha sun — disc, 8 long + 8 short rays, pearl ring
function muchaIconSun(ctx, cx, cy, R) {
  // Long rays
  ctx.save();
  ctx.translate(cx, cy);
  for (var i = 0; i < 8; i++) {
    ctx.save();
    ctx.rotate(i * Math.PI / 4);
    var rg = ctx.createLinearGradient(0, -R * 0.86, 0, -R * 1.55);
    rg.addColorStop(0.0, "rgba(248,232,178,0.95)");
    rg.addColorStop(0.5, "rgba(220,176, 78,0.78)");
    rg.addColorStop(1.0, "rgba(160,108, 30,0.00)");
    ctx.fillStyle = rg;
    ctx.beginPath();
    ctx.moveTo(-R * 0.18, -R * 0.86);
    ctx.bezierCurveTo( R * 0.18, -R * 1.00, R * 0.06, -R * 1.40, 0, -R * 1.55);
    ctx.bezierCurveTo(-R * 0.06, -R * 1.40, -R * 0.18, -R * 1.00, -R * 0.18, -R * 0.86);
    ctx.fill();
    // Tip jewel
    ctx.fillStyle = "rgba(252,232,178,0.92)";
    ctx.beginPath(); ctx.arc(0, -R * 1.48, R * 0.07, 0, Math.PI * 2); ctx.fill();
    ctx.restore();
  }
  // Short petal rays
  for (var j = 0; j < 8; j++) {
    ctx.save();
    ctx.rotate(j * Math.PI / 4 + Math.PI / 8);
    var sg = ctx.createLinearGradient(0, -R * 0.86, 0, -R * 1.20);
    sg.addColorStop(0.0, "rgba(244,212,140,0.85)");
    sg.addColorStop(1.0, "rgba(160,108, 30,0.00)");
    ctx.fillStyle = sg;
    ctx.beginPath();
    ctx.moveTo(0, -R * 0.86);
    ctx.bezierCurveTo( R * 0.10, -R * 0.94, R * 0.05, -R * 1.10, 0, -R * 1.20);
    ctx.bezierCurveTo(-R * 0.05, -R * 1.10, -R * 0.10, -R * 0.94, 0, -R * 0.86);
    ctx.fill();
    ctx.restore();
  }
  ctx.restore();

  // Pearl ring
  for (var p = 0; p < 16; p++) {
    var pa = p * Math.PI / 8;
    var px = cx + R * 1.08 * Math.cos(pa);
    var py = cy + R * 1.08 * Math.sin(pa);
    ctx.fillStyle = (p % 4 === 0) ? "rgba(248,232,178,0.95)" : "rgba(200,160, 78,0.78)";
    ctx.beginPath();
    ctx.arc(px, py, (p % 4 === 0) ? R * 0.07 : R * 0.038, 0, Math.PI * 2);
    ctx.fill();
  }
  // Disc
  var dg = ctx.createRadialGradient(cx - R * 0.24, cy - R * 0.28, 0, cx, cy, R);
  dg.addColorStop(0.0,  "rgba(252,246,212,1.00)");
  dg.addColorStop(0.5,  "rgba(232,200,118,1.00)");
  dg.addColorStop(0.95, "rgba(184,148, 56,1.00)");
  dg.addColorStop(1.0,  "rgba(140,100, 24,1.00)");
  ctx.fillStyle = dg;
  ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI * 2); ctx.fill();
  // Engraved bezel
  ctx.strokeStyle = "rgba(166,128, 42,0.65)";
  ctx.lineWidth   = 0.7;
  ctx.beginPath(); ctx.arc(cx, cy, R - 1, 0, Math.PI * 2); ctx.stroke();
  // Center 3-petal blossom (no face at this scale)
  ctx.save();
  ctx.translate(cx, cy);
  ctx.fillStyle = "rgba(200,144,144,0.75)";
  for (var bp = 0; bp < 3; bp++) {
    ctx.save();
    ctx.rotate(bp * Math.PI * 2 / 3);
    ctx.beginPath();
    ctx.ellipse(0, -R * 0.30, R * 0.10, R * 0.22, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  ctx.fillStyle = "rgba(110, 78, 20,0.85)";
  ctx.beginPath(); ctx.arc(0, 0, R * 0.10, 0, Math.PI * 2); ctx.fill();
  ctx.fillStyle = "rgba(232,200,118,0.95)";
  ctx.beginPath(); ctx.arc(0, 0, R * 0.05, 0, Math.PI * 2); ctx.fill();
  ctx.restore();
  // Final highlight
  var hl = ctx.createRadialGradient(cx - R * 0.30, cy - R * 0.32, 0, cx, cy, R);
  hl.addColorStop(0.0, "rgba(255,252,228,0.40)");
  hl.addColorStop(1.0, "rgba(0,0,0,0)");
  ctx.fillStyle = hl;
  ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI * 2); ctx.fill();
}

// Small Mucha moon — crescent with star + filigree
function muchaIconMoon(ctx, cx, cy, R) {
  // Halo of small stars
  var stars = [[-1.5, -1.0, 0.10], [-1.7,  0.4, 0.07], [ 1.5, -1.4, 0.12],
               [ 1.7,  0.2, 0.08], [-0.4, -1.8, 0.09], [ 0.6,  1.6, 0.08]];
  for (var s = 0; s < stars.length; s++) {
    var sx = cx + stars[s][0] * R;
    var sy = cy + stars[s][1] * R;
    var sr = stars[s][2] * R;
    ctx.save();
    ctx.translate(sx, sy);
    ctx.fillStyle = "rgba(252,242,200,0.92)";
    ctx.beginPath();
    for (var p = 0; p < 8; p++) {
      var a  = p * Math.PI / 4;
      var rd = (p % 2 === 0) ? sr : sr * 0.32;
      if (p === 0) ctx.moveTo(Math.cos(a - Math.PI / 4) * rd, Math.sin(a - Math.PI / 4) * rd);
      else         ctx.lineTo(Math.cos(a - Math.PI / 4) * rd, Math.sin(a - Math.PI / 4) * rd);
    }
    ctx.closePath();
    ctx.fill();
    ctx.restore();
  }
  // Crescent body
  ctx.save();
  ctx.translate(cx, cy);
  // Outer glow
  var og = ctx.createRadialGradient(0, 0, R * 0.4, 0, 0, R * 1.6);
  og.addColorStop(0.0, "rgba(208,212,228,0.18)");
  og.addColorStop(1.0, "rgba(0,0,0,0)");
  ctx.fillStyle = og;
  ctx.beginPath(); ctx.arc(0, 0, R * 1.6, 0, Math.PI * 2); ctx.fill();
  // Crescent shape
  var cg = ctx.createLinearGradient(-R, 0, R, 0);
  cg.addColorStop(0.0, "rgba(248,242,222,1.00)");
  cg.addColorStop(0.5, "rgba(220,222,232,1.00)");
  cg.addColorStop(1.0, "rgba(168,172,200,1.00)");
  ctx.fillStyle = cg;
  ctx.beginPath();
  ctx.arc(0, 0, R, Math.PI * 0.30, Math.PI * 1.70, false);
  ctx.arc(R * 0.42, 0, R * 0.78, Math.PI * 1.70, Math.PI * 0.30, true);
  ctx.closePath();
  ctx.fill();
  // Bezel
  ctx.strokeStyle = "rgba(140,116, 64,0.72)";
  ctx.lineWidth   = 0.7;
  ctx.stroke();
  // Tiny face — just an eye + smile
  ctx.fillStyle = "rgba( 50, 36, 16,0.72)";
  ctx.beginPath(); ctx.arc(-R * 0.30, -R * 0.10, R * 0.05, 0, Math.PI * 2); ctx.fill();
  ctx.strokeStyle = "rgba( 50, 36, 16,0.65)";
  ctx.lineWidth = 0.6;
  ctx.beginPath();
  ctx.arc(-R * 0.20, R * 0.10, R * 0.16, 0.4, Math.PI - 0.4);
  ctx.stroke();
  ctx.restore();
}

// Whiplash spiral cloud
function muchaIconCloud(ctx, cx, cy, R, color, opacity) {
  color   = color   || "rgba(252,248,238,";
  opacity = opacity || 0.92;
  ctx.save();
  ctx.translate(cx, cy);
  // Body
  var bg = ctx.createRadialGradient(0, 0, 0, 0, 0, R);
  bg.addColorStop(0.0, color + opacity + ")");
  bg.addColorStop(0.55, color + (opacity * 0.55) + ")");
  bg.addColorStop(1.0,  color + "0)");
  ctx.fillStyle = bg;
  ctx.beginPath();
  ctx.ellipse(0, 0, R, R * 0.55, 0, 0, Math.PI * 2);
  ctx.fill();
  // Whorl arms
  ctx.strokeStyle = color + (opacity * 0.60) + ")";
  ctx.lineWidth   = R * 0.10;
  ctx.lineCap     = "round";
  for (var sw = 0; sw < 2; sw++) {
    var spin = (sw === 0) ? 1 : -1;
    var off  = sw * Math.PI;
    ctx.beginPath();
    for (var st = 0; st <= 28; st++) {
      var tt = st / 28;
      var rad = R * (0.92 - tt * 0.72);
      var ang = off + spin * tt * 1.3 * Math.PI * 2;
      var sx  = Math.cos(ang) * rad * 1.0;
      var sy  = Math.sin(ang) * rad * 0.55;
      if (st === 0) ctx.moveTo(sx, sy);
      else          ctx.lineTo(sx, sy);
    }
    ctx.stroke();
  }
  // Inner highlight stroke
  ctx.strokeStyle = "rgba(255,254,244," + (opacity * 0.50) + ")";
  ctx.lineWidth   = R * 0.04;
  ctx.beginPath();
  ctx.ellipse(-R * 0.10, -R * 0.06, R * 0.50, R * 0.20, 0, 0, Math.PI * 2);
  ctx.stroke();
  // Sage shadow belly
  ctx.fillStyle = "rgba(107,126, 98," + (opacity * 0.20) + ")";
  ctx.beginPath();
  ctx.ellipse(0, R * 0.18, R * 0.78, R * 0.22, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}

// Mucha raindrop — teardrop with curving inner highlight
function muchaIconRaindrop(ctx, x, y, len, color) {
  color = color || "rgba(120,168,210,";
  ctx.save();
  ctx.translate(x, y);
  // Body
  ctx.fillStyle = color + "0.92)";
  ctx.beginPath();
  ctx.moveTo(0, -len);
  ctx.bezierCurveTo(len * 0.30, -len * 0.45, len * 0.30, len * 0.20, 0, len * 0.50);
  ctx.bezierCurveTo(-len * 0.30, len * 0.20, -len * 0.30, -len * 0.45, 0, -len);
  ctx.fill();
  // Highlight
  ctx.strokeStyle = "rgba(232,242,250,0.78)";
  ctx.lineWidth   = Math.max(0.5, len * 0.06);
  ctx.beginPath();
  ctx.moveTo(-len * 0.10, -len * 0.30);
  ctx.bezierCurveTo(-len * 0.20, -len * 0.05, -len * 0.18, len * 0.10, -len * 0.05, len * 0.20);
  ctx.stroke();
  // Tip gold accent
  ctx.fillStyle = "rgba(232,200,118,0.45)";
  ctx.beginPath(); ctx.arc(0, -len * 0.85, len * 0.10, 0, Math.PI * 2); ctx.fill();
  ctx.restore();
}

// Mucha snowflake — 6 arms with botanical detail
function muchaIconSnowflake(ctx, cx, cy, R) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.strokeStyle = "rgba(232,238,248,0.92)";
  ctx.fillStyle   = "rgba(248,250,254,0.92)";
  ctx.lineWidth   = R * 0.08;
  ctx.lineCap     = "round";
  for (var a = 0; a < 6; a++) {
    ctx.save();
    ctx.rotate(a * Math.PI / 3);
    // Main arm
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.lineTo(0, -R);
    ctx.stroke();
    // Side branches
    for (var br = 1; br <= 2; br++) {
      var by = -R * (0.30 + br * 0.30);
      var bl = R * 0.20 * (3 - br) / 2;
      ctx.beginPath();
      ctx.moveTo(0, by);
      ctx.lineTo(-bl, by - bl);
      ctx.moveTo(0, by);
      ctx.lineTo( bl, by - bl);
      ctx.stroke();
    }
    // Tip droplet
    ctx.beginPath();
    ctx.arc(0, -R, R * 0.08, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  // Center rosette
  ctx.fillStyle = "rgba(232,200,118,0.85)";
  for (var pp = 0; pp < 6; pp++) {
    ctx.save();
    ctx.rotate(pp * Math.PI / 3);
    ctx.beginPath();
    ctx.ellipse(0, -R * 0.16, R * 0.05, R * 0.10, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  ctx.fillStyle = "rgba(248,232,178,0.95)";
  ctx.beginPath(); ctx.arc(0, 0, R * 0.07, 0, Math.PI * 2); ctx.fill();
  ctx.restore();
}

// Mucha lightning — crystalline forked bolt with gold filigree edge
function muchaIconBolt(ctx, x, y, len) {
  ctx.save();
  ctx.translate(x, y);
  var bolt = [
    [0,         0],
    [len * 0.30, -len * 0.10],
    [len * 0.10, -len * 0.40],
    [len * 0.42, -len * 0.55],
    [len * 0.20, -len * 0.90],
    [len * 0.55, -len * 1.05]
  ];
  // Body fill — pale gold gradient
  var bg = ctx.createLinearGradient(0, 0, 0, -len);
  bg.addColorStop(0.0, "rgba(232,178, 88,0.95)");
  bg.addColorStop(0.5, "rgba(252,232,178,0.95)");
  bg.addColorStop(1.0, "rgba(255,252,228,1.00)");
  ctx.fillStyle = bg;
  ctx.strokeStyle = "rgba(140, 96, 30,0.85)";
  ctx.lineWidth   = 0.7;
  ctx.beginPath();
  for (var b = 0; b < bolt.length; b++) {
    if (b === 0) ctx.moveTo(bolt[b][0], bolt[b][1]);
    else         ctx.lineTo(bolt[b][0], bolt[b][1]);
  }
  // Mirror back with offset to create thickness
  for (var b2 = bolt.length - 1; b2 >= 0; b2--) {
    ctx.lineTo(bolt[b2][0] - len * 0.10, bolt[b2][1] + len * 0.03);
  }
  ctx.closePath();
  ctx.fill();
  ctx.stroke();
  // Inner highlight
  ctx.strokeStyle = "rgba(255,255,240,0.85)";
  ctx.lineWidth   = 0.5;
  ctx.beginPath();
  for (var b3 = 0; b3 < bolt.length; b3++) {
    var px = bolt[b3][0] - len * 0.04;
    var py = bolt[b3][1] + len * 0.01;
    if (b3 === 0) ctx.moveTo(px, py);
    else          ctx.lineTo(px, py);
  }
  ctx.stroke();
  ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
//  Weather icon compositions
// ═══════════════════════════════════════════════════════════════

function drawWxSun(ctx, W, H) {
  muchaIconSun(ctx, W / 2, H / 2, W * 0.28);
}

function drawWxMoon(ctx, W, H) {
  muchaIconMoon(ctx, W / 2, H / 2, W * 0.28);
}

function drawWxSunCloud(ctx, W, H) {
  muchaIconSun(ctx, W * 0.36, H * 0.36, W * 0.22);
  muchaIconCloud(ctx, W * 0.62, H * 0.62, W * 0.32);
}

function drawWxMoonCloud(ctx, W, H) {
  muchaIconMoon(ctx, W * 0.36, H * 0.36, W * 0.22);
  muchaIconCloud(ctx, W * 0.62, H * 0.62, W * 0.32);
}

function drawWxCloud(ctx, W, H) {
  muchaIconCloud(ctx, W * 0.58, H * 0.38, W * 0.26, "rgba(208,212,228,", 0.78);
  muchaIconCloud(ctx, W * 0.42, H * 0.56, W * 0.34, "rgba(252,248,238,", 0.92);
}

function drawWxRain(ctx, W, H) {
  muchaIconCloud(ctx, W / 2, H * 0.36, W * 0.32, "rgba(168,180,210,", 0.92);
  // 4 raindrops
  var drops = [
    [W * 0.32, H * 0.66, W * 0.07],
    [W * 0.46, H * 0.74, W * 0.07],
    [W * 0.60, H * 0.66, W * 0.07],
    [W * 0.72, H * 0.78, W * 0.06]
  ];
  for (var d = 0; d < drops.length; d++) {
    muchaIconRaindrop(ctx, drops[d][0], drops[d][1], drops[d][2]);
  }
}

function drawWxDrizzle(ctx, W, H) {
  muchaIconCloud(ctx, W / 2, H * 0.38, W * 0.30, "rgba(208,212,228,", 0.78);
  // tiny droplets, more of them
  var dots = [
    [W * 0.28, H * 0.66], [W * 0.40, H * 0.74], [W * 0.52, H * 0.66],
    [W * 0.64, H * 0.74], [W * 0.76, H * 0.66],
    [W * 0.34, H * 0.84], [W * 0.58, H * 0.84]
  ];
  for (var d2 = 0; d2 < dots.length; d2++) {
    muchaIconRaindrop(ctx, dots[d2][0], dots[d2][1], W * 0.04);
  }
}

function drawWxThunder(ctx, W, H) {
  muchaIconCloud(ctx, W / 2, H * 0.32, W * 0.34, "rgba(108,108,138,", 0.95);
  // Bolt down middle
  muchaIconBolt(ctx, W * 0.42, H * 0.55, W * 0.40);
  // Two flanking raindrops
  muchaIconRaindrop(ctx, W * 0.22, H * 0.74, W * 0.06);
  muchaIconRaindrop(ctx, W * 0.78, H * 0.74, W * 0.06);
}

function drawWxSnow(ctx, W, H) {
  muchaIconCloud(ctx, W / 2, H * 0.34, W * 0.30, "rgba(232,238,248,", 0.92);
  muchaIconSnowflake(ctx, W * 0.32, H * 0.72, W * 0.12);
  muchaIconSnowflake(ctx, W * 0.54, H * 0.82, W * 0.10);
  muchaIconSnowflake(ctx, W * 0.74, H * 0.66, W * 0.11);
}

function drawWxSleet(ctx, W, H) {
  muchaIconCloud(ctx, W / 2, H * 0.32, W * 0.30, "rgba(196,202,218,", 0.88);
  // Mix drop + snowflake
  muchaIconRaindrop(ctx, W * 0.30, H * 0.68, W * 0.07);
  muchaIconSnowflake(ctx, W * 0.50, H * 0.74, W * 0.10);
  muchaIconRaindrop(ctx, W * 0.72, H * 0.70, W * 0.07);
}

function drawWxHail(ctx, W, H) {
  muchaIconCloud(ctx, W / 2, H * 0.32, W * 0.30, "rgba(168,176,200,", 0.92);
  // Hailstones — small pearl beads with engraved facets
  var hails = [[W * 0.32, H * 0.66], [W * 0.46, H * 0.78],
               [W * 0.60, H * 0.66], [W * 0.74, H * 0.78]];
  for (var h = 0; h < hails.length; h++) {
    var hx = hails[h][0], hy = hails[h][1], hr = W * 0.055;
    var hg = ctx.createRadialGradient(hx - hr * 0.3, hy - hr * 0.3, 0, hx, hy, hr);
    hg.addColorStop(0.0, "rgba(248,250,254,1.00)");
    hg.addColorStop(0.6, "rgba(196,210,222,1.00)");
    hg.addColorStop(1.0, "rgba(108,128,150,1.00)");
    ctx.fillStyle = hg;
    ctx.beginPath(); ctx.arc(hx, hy, hr, 0, Math.PI * 2); ctx.fill();
    ctx.strokeStyle = "rgba(108,128,150,0.85)";
    ctx.lineWidth   = 0.6;
    ctx.stroke();
    // Facet line
    ctx.strokeStyle = "rgba(248,250,254,0.85)";
    ctx.beginPath();
    ctx.arc(hx, hy, hr * 0.6, Math.PI, Math.PI * 1.5);
    ctx.stroke();
  }
}

function drawWxFog(ctx, W, H) {
  // 5 horizontal whiplash bands fading in and out
  ctx.lineCap = "round";
  for (var b = 0; b < 5; b++) {
    var y = H * 0.30 + b * H * 0.10;
    var amp = W * 0.020;
    var grad = ctx.createLinearGradient(0, y, W, y);
    grad.addColorStop(0.0, "rgba(232,228,212,0.00)");
    grad.addColorStop(0.5, "rgba(232,228,212,0.85)");
    grad.addColorStop(1.0, "rgba(232,228,212,0.00)");
    ctx.strokeStyle = grad;
    ctx.lineWidth   = H * 0.05;
    ctx.beginPath();
    for (var x = 0; x <= W; x += 2) {
      var fy = y + Math.sin((x / W) * Math.PI * 3 + b * 0.7) * amp;
      if (x === 0) ctx.moveTo(x, fy);
      else         ctx.lineTo(x, fy);
    }
    ctx.stroke();
  }
  // Faded sun behind for haze
  ctx.globalAlpha = 0.32;
  muchaIconSun(ctx, W * 0.30, H * 0.30, W * 0.16);
  ctx.globalAlpha = 1.0;
}

function drawWxWind(ctx, W, H) {
  // Three flowing whiplash curves — like Mucha hair caught in wind
  ctx.strokeStyle = "rgba(212,200,168,0.85)";
  ctx.lineWidth   = W * 0.04;
  ctx.lineCap     = "round";
  var paths = [
    [[ W * 0.10, H * 0.36 ], [ W * 0.40, H * 0.28 ], [ W * 0.62, H * 0.42 ], [ W * 0.92, H * 0.34 ]],
    [[ W * 0.06, H * 0.56 ], [ W * 0.32, H * 0.50 ], [ W * 0.66, H * 0.62 ], [ W * 0.94, H * 0.52 ]],
    [[ W * 0.10, H * 0.74 ], [ W * 0.42, H * 0.68 ], [ W * 0.60, H * 0.78 ], [ W * 0.86, H * 0.70 ]]
  ];
  for (var i = 0; i < paths.length; i++) {
    var pa = paths[i];
    ctx.beginPath();
    ctx.moveTo(pa[0][0], pa[0][1]);
    ctx.bezierCurveTo(pa[1][0], pa[1][1], pa[2][0], pa[2][1], pa[3][0], pa[3][1]);
    ctx.stroke();
    // Tail curl
    ctx.save();
    ctx.translate(pa[3][0], pa[3][1]);
    ctx.strokeStyle = "rgba(232,200,118,0.78)";
    ctx.lineWidth   = W * 0.025;
    ctx.beginPath();
    ctx.arc(-W * 0.04, 0, W * 0.04, 0.2, Math.PI * 1.6);
    ctx.stroke();
    ctx.restore();
    // Leaf at tail
    ctx.fillStyle = "rgba(107,126, 98,0.78)";
    ctx.save();
    ctx.translate(pa[3][0] - W * 0.06, pa[3][1] + H * 0.02);
    ctx.rotate(-0.2);
    ctx.beginPath();
    ctx.ellipse(0, 0, W * 0.04, H * 0.012, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
}

function drawWxTornado(ctx, W, H) {
  // Coiled funnel — wider top, narrow base; thick wisps spiral around it
  var cx = W / 2;
  var topY = H * 0.16;
  var botY = H * 0.84;
  var topR = W * 0.36;
  var botR = W * 0.06;
  // Funnel cone fill (subtle violet wash)
  var coneG = ctx.createLinearGradient(0, topY, 0, botY);
  coneG.addColorStop(0.0, "rgba(168,168,196,0.55)");
  coneG.addColorStop(0.6, "rgba(108,110,148,0.45)");
  coneG.addColorStop(1.0, "rgba( 64, 60, 96,0.50)");
  ctx.fillStyle = coneG;
  ctx.beginPath();
  // Outline cone
  for (var c = 0; c <= 20; c++) {
    var tt = c / 20;
    var y = topY + (botY - topY) * tt;
    var rx = topR + (botR - topR) * tt;
    var w = rx * (1.0 + Math.sin(tt * Math.PI * 4) * 0.06);
    if (c === 0) ctx.moveTo(cx - w, y);
    else         ctx.lineTo(cx - w, y);
  }
  for (var c2 = 20; c2 >= 0; c2--) {
    var tt2 = c2 / 20;
    var y2 = topY + (botY - topY) * tt2;
    var rx2 = topR + (botR - topR) * tt2;
    var w2 = rx2 * (1.0 + Math.sin(tt2 * Math.PI * 4 + Math.PI) * 0.06);
    ctx.lineTo(cx + w2, y2);
  }
  ctx.closePath();
  ctx.fill();

  // Whorl bands — concentric ellipses with varying opacity
  for (var k = 0; k < 14; k++) {
    var tt3 = k / 13;
    var y3 = topY + (botY - topY) * tt3;
    var rx3 = (topR + (botR - topR) * tt3) * (1.0 + Math.sin(tt3 * Math.PI * 6) * 0.08);
    var ry3 = rx3 * 0.20;
    // Alternating thick/thin
    var thick = (k % 2 === 0);
    ctx.strokeStyle = thick ? "rgba(232,228,212,0.85)"
                            : "rgba(168,168,196,0.45)";
    ctx.lineWidth   = thick ? W * 0.018 : W * 0.010;
    ctx.lineCap     = "round";
    ctx.beginPath();
    ctx.ellipse(cx, y3, rx3, ry3, 0, 0, Math.PI * 2);
    ctx.stroke();
  }

  // Whiplash spiraling line — Mucha hair-like flowing curve down the side
  ctx.strokeStyle = "rgba(232,200,118,0.88)";
  ctx.lineWidth   = W * 0.025;
  ctx.lineCap     = "round";
  ctx.beginPath();
  for (var s = 0; s <= 80; s++) {
    var tt4 = s / 80;
    var y4 = topY + (botY - topY) * tt4;
    var rx4 = topR + (botR - topR) * tt4;
    var ang = tt4 * Math.PI * 6;
    var x = cx + Math.cos(ang) * rx4 * 1.05;
    if (s === 0) ctx.moveTo(x, y4);
    else         ctx.lineTo(x, y4);
  }
  ctx.stroke();
  // Highlight tracer
  ctx.strokeStyle = "rgba(252,242,200,0.50)";
  ctx.lineWidth   = W * 0.010;
  ctx.beginPath();
  for (var s2 = 0; s2 <= 80; s2++) {
    var tt5 = s2 / 80;
    var y5 = topY + (botY - topY) * tt5;
    var rx5 = topR + (botR - topR) * tt5;
    var ang2 = tt5 * Math.PI * 6 + Math.PI;
    var x2 = cx + Math.cos(ang2) * rx5 * 1.05;
    if (s2 === 0) ctx.moveTo(x2, y5);
    else          ctx.lineTo(x2, y5);
  }
  ctx.stroke();

  // Cap cloud above the funnel — small whorl
  muchaIconCloud(ctx, cx, topY * 0.78, W * 0.28, "rgba(168,168,196,", 0.85);

  // Debris kicked up at the base — small dark dashes
  ctx.fillStyle = "rgba(112, 84, 36,0.85)";
  for (var d = 0; d < 5; d++) {
    var dx = cx + (d - 2) * W * 0.09 + (d % 2 === 0 ? 4 : -4);
    var dy = botY + W * 0.02 + (d % 2) * W * 0.04;
    ctx.save();
    ctx.translate(dx, dy);
    ctx.rotate((d - 2) * 0.3);
    ctx.beginPath();
    ctx.ellipse(0, 0, W * 0.025, W * 0.008, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  // Ground dust streak
  var dustG = ctx.createRadialGradient(cx, botY + W * 0.05, 0,
                                       cx, botY + W * 0.05, W * 0.40);
  dustG.addColorStop(0.0, "rgba(168,148,108,0.42)");
  dustG.addColorStop(1.0, "rgba(0,0,0,0)");
  ctx.fillStyle = dustG;
  ctx.beginPath();
  ctx.ellipse(cx, botY + W * 0.05, W * 0.42, W * 0.08, 0, 0, Math.PI * 2);
  ctx.fill();
}

function drawWxCold(ctx, W, H) {
  // Single large snowflake centered
  muchaIconSnowflake(ctx, W / 2, H / 2, W * 0.34);
  // Wisps of pale-blue mist
  ctx.strokeStyle = "rgba(168,196,220,0.42)";
  ctx.lineWidth   = W * 0.03;
  ctx.lineCap     = "round";
  for (var w = 0; w < 3; w++) {
    var y = H * 0.20 + w * H * 0.30;
    ctx.beginPath();
    ctx.moveTo(W * 0.10, y);
    ctx.bezierCurveTo(W * 0.30, y - H * 0.06, W * 0.70, y + H * 0.06, W * 0.90, y);
    ctx.stroke();
  }
}
