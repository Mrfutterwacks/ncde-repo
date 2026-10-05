.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA EARTH — sage continents, dusty rose deserts, ivory poles,
//  teal-violet ocean, fine gold meridians. Scalloped Mucha
//  coastlines. Accurate-ish geography (8-14 vertices per continent
//  with sine-perturbed coastlines).
//  Render at 120×120 (matches QML globeClip size).
// ═══════════════════════════════════════════════════════════════

// Continent shapes — normalized [-1..1] coordinates, [-y = north].
// Each continent is a flat polygon ring with optional sub-polygons.
var MUCHA_EARTH_CONTINENTS = {
  northAmerica: {
    fill:     "rgba(148,167,138,1.00)",   // sage
    interior: "rgba(168,160,124,0.55)",   // warm tint
    poly: [
      [-0.82, -0.50], [-0.86, -0.62], [-0.78, -0.74], [-0.60, -0.78],
      [-0.42, -0.80], [-0.26, -0.78], [-0.18, -0.62], [-0.06, -0.56],
      [-0.04, -0.40], [-0.06, -0.24], [-0.14, -0.16], [-0.22, -0.04],
      [-0.32,  0.06], [-0.42,  0.04], [-0.50, -0.06], [-0.60, -0.10],
      [-0.70, -0.20], [-0.78, -0.32], [-0.80, -0.42]
    ]
  },
  greenland: {
    fill:     "rgba(220,224,224,0.85)",   // ivory cool
    interior: "rgba(196,200,212,0.40)",
    poly: [
      [-0.20, -0.80], [-0.06, -0.82], [ 0.02, -0.74], [-0.04, -0.62],
      [-0.14, -0.62], [-0.20, -0.70]
    ]
  },
  southAmerica: {
    fill:     "rgba(148,167,138,1.00)",
    interior: "rgba(184,148,108,0.55)",   // warm earth
    poly: [
      [-0.36,  0.08], [-0.28,  0.10], [-0.20,  0.18], [-0.14,  0.28],
      [-0.12,  0.42], [-0.16,  0.58], [-0.22,  0.70], [-0.30,  0.74],
      [-0.36,  0.66], [-0.42,  0.50], [-0.46,  0.34], [-0.46,  0.18]
    ]
  },
  europe: {
    fill:     "rgba(148,167,138,1.00)",
    interior: "rgba(168,160,124,0.55)",
    poly: [
      [ 0.02, -0.66], [ 0.14, -0.72], [ 0.30, -0.74], [ 0.42, -0.68],
      [ 0.42, -0.54], [ 0.32, -0.46], [ 0.20, -0.40], [ 0.10, -0.38],
      [ 0.02, -0.44], [-0.02, -0.56]
    ]
  },
  africa: {
    fill:     "rgba(148,167,138,1.00)",
    interior: "rgba(200,144,144,0.42)",   // sahara dusty rose
    poly: [
      [ 0.04, -0.34], [ 0.18, -0.32], [ 0.30, -0.28], [ 0.38, -0.18],
      [ 0.42, -0.04], [ 0.40,  0.10], [ 0.36,  0.26], [ 0.28,  0.42],
      [ 0.20,  0.54], [ 0.10,  0.58], [ 0.02,  0.46], [-0.02,  0.30],
      [-0.04,  0.14], [-0.02, -0.02], [ 0.00, -0.18]
    ]
  },
  asia: {
    fill:     "rgba(148,167,138,1.00)",
    interior: "rgba(168,160,124,0.55)",
    poly: [
      [ 0.30, -0.72], [ 0.50, -0.74], [ 0.68, -0.72], [ 0.82, -0.66],
      [ 0.90, -0.54], [ 0.92, -0.40], [ 0.88, -0.26], [ 0.78, -0.14],
      [ 0.66, -0.06], [ 0.54,  0.04], [ 0.46,  0.02], [ 0.40, -0.10],
      [ 0.36, -0.24], [ 0.34, -0.40], [ 0.32, -0.56]
    ]
  },
  india: {
    fill:     "rgba(148,167,138,1.00)",
    interior: "rgba(200,144,144,0.45)",
    poly: [
      [ 0.42, -0.10], [ 0.52, -0.06], [ 0.56,  0.04], [ 0.52,  0.14],
      [ 0.46,  0.16], [ 0.42,  0.08]
    ]
  },
  southeastAsia: {
    fill:     "rgba(148,167,138,1.00)",
    interior: "rgba(168,160,124,0.50)",
    poly: [
      [ 0.62,  0.04], [ 0.74,  0.10], [ 0.80,  0.20], [ 0.74,  0.28],
      [ 0.64,  0.26], [ 0.58,  0.16]
    ]
  },
  australia: {
    fill:     "rgba(148,167,138,1.00)",
    interior: "rgba(200,144,144,0.50)",   // central desert
    poly: [
      [ 0.62,  0.34], [ 0.76,  0.32], [ 0.86,  0.40], [ 0.84,  0.50],
      [ 0.72,  0.56], [ 0.60,  0.52], [ 0.56,  0.42]
    ]
  },
  antarctica: {
    fill:     "rgba(232,228,228,0.92)",   // ivory cool
    interior: "rgba(196,200,212,0.45)",
    poly: [
      [-0.96,  0.80], [-0.70,  0.84], [-0.40,  0.86], [-0.10,  0.88],
      [ 0.20,  0.88], [ 0.50,  0.86], [ 0.80,  0.84], [ 0.96,  0.80],
      [ 0.96,  1.00], [-0.96,  1.00]
    ]
  }
};

// Major-city ornament marks (lat/lon as decimal degrees, name initial)
// Drawn as small Mucha trefoils — *separate from* the city-lights canvas
// which animates by time-of-day.
var MUCHA_EARTH_LANDMARKS = [
  { lon: -74.0, lat:  40.7 },  // NYC
  { lon:   2.3, lat:  48.9 },  // Paris
  { lon:  37.6, lat:  55.7 },  // Moscow
  { lon: 116.4, lat:  39.9 },  // Beijing
  { lon: 139.7, lat:  35.7 },  // Tokyo
  { lon: -43.2, lat: -22.9 },  // Rio
  { lon:  31.2, lat:  30.1 },  // Cairo
  { lon: 151.2, lat: -33.9 }   // Sydney
];

// ── Scalloped path — replaces straight polygon edges with gentle
//    sine ripples for Art Nouveau coastline rhythm. ───────────
function muchaScallopedPath(ctx, pts, amp, period) {
  if (pts.length < 2) return;
  ctx.beginPath();
  for (var i = 0; i < pts.length; i++) {
    var p1 = pts[i];
    var p2 = pts[(i + 1) % pts.length];
    var dx = p2[0] - p1[0];
    var dy = p2[1] - p1[1];
    var len = Math.sqrt(dx * dx + dy * dy);
    if (len < 0.001) continue;
    var nx = -dy / len, ny = dx / len;
    var steps = Math.max(6, Math.round(len / period * 4));
    if (i === 0) ctx.moveTo(p1[0], p1[1]);
    for (var s = 1; s <= steps; s++) {
      var t  = s / steps;
      var ph = (i * 1.7);                          // phase varies per edge
      var bumps = Math.max(1, len / period);
      var off = Math.sin(t * bumps * Math.PI * 2 + ph) * amp;
      ctx.lineTo(p1[0] + dx * t + nx * off,
                 p1[1] + dy * t + ny * off);
    }
  }
  ctx.closePath();
}

function drawMuchaEarth(ctx, W, H) {
  ctx.clearRect(0, 0, W, H);
  var cx = W / 2, cy = H / 2;
  var r  = Math.min(W, H) / 2 - 1;

  // ── Clip to globe disc ──────────────────────────────────────
  ctx.save();
  ctx.beginPath(); ctx.arc(cx, cy, r, 0, Math.PI * 2); ctx.clip();

  // ── Ocean — deep teal-violet with painted brushwork ────────
  var oc = ctx.createRadialGradient(cx - r * 0.22, cy - r * 0.24, 0,
                                    cx, cy, r);
  oc.addColorStop(0.00, "rgba( 48, 90,140,1.00)");
  oc.addColorStop(0.32, "rgba( 28, 64,116,1.00)");
  oc.addColorStop(0.68, "rgba( 16, 38, 84,1.00)");
  oc.addColorStop(1.00, "rgba(  8, 18, 52,1.00)");
  ctx.fillStyle = oc;
  ctx.fillRect(0, 0, W, H);

  // ── Painted ocean current ribbons (whiplash arcs) ──────────
  ctx.strokeStyle = "rgba(120,168,210,0.16)";
  ctx.lineWidth   = 0.7;
  for (var oc2 = 0; oc2 < 5; oc2++) {
    var oy = cy - r * 0.7 + (oc2 / 4) * r * 1.4;
    var amp = r * 0.06;
    var freq = (oc2 % 2 === 0) ? 3 : 4;
    ctx.beginPath();
    for (var x = -r; x <= r; x += 1.5) {
      var y = oy + Math.sin((x / r) * freq * Math.PI + oc2 * 0.9) * amp;
      if (x === -r) ctx.moveTo(cx + x, y);
      else          ctx.lineTo(cx + x, y);
    }
    ctx.stroke();
  }

  // ── Engraved gold meridians + parallels ─────────────────────
  ctx.strokeStyle = "rgba(212,178,108,0.34)";
  ctx.lineWidth   = 0.55;
  // Equator
  ctx.beginPath(); ctx.moveTo(cx - r, cy); ctx.lineTo(cx + r, cy); ctx.stroke();
  // Tropics + arctic circles (curved as ellipses for "globe" feel)
  var parR = [0.30, 0.55, 0.78];
  for (var pr = 0; pr < parR.length; pr++) {
    ctx.beginPath();
    ctx.ellipse(cx, cy, r, r * (1 - parR[pr] * 0.7), 0, 0, Math.PI * 2);
    ctx.stroke();
  }
  // Meridians — 8 long lines from pole to pole
  for (var mm = 0; mm < 8; mm++) {
    var ma = mm * Math.PI / 8;
    ctx.beginPath();
    ctx.moveTo(cx + r * Math.cos(ma), cy + r * Math.sin(ma));
    ctx.lineTo(cx - r * Math.cos(ma), cy - r * Math.sin(ma));
    ctx.stroke();
  }
  // Prime meridian — thicker gold
  ctx.strokeStyle = "rgba(232,200,118,0.55)";
  ctx.lineWidth   = 0.8;
  ctx.beginPath();
  ctx.moveTo(cx, cy - r);
  ctx.lineTo(cx, cy + r);
  ctx.stroke();

  // ── Continents — scalloped sage with interior gradients ────
  function drawContinent(c, ampMul) {
    // Convert normalized -1..1 to canvas coords
    var pts = [];
    for (var i = 0; i < c.poly.length; i++) {
      pts.push([cx + c.poly[i][0] * r, cy + c.poly[i][1] * r]);
    }
    var scallopAmp = r * 0.014 * (ampMul || 1);

    // Soft drop-shadow under continent (faux atmosphere on land)
    ctx.save();
    ctx.shadowColor   = "rgba(8,12,28,0.45)";
    ctx.shadowBlur    = r * 0.040;
    ctx.shadowOffsetX = r * 0.008;
    ctx.shadowOffsetY = r * 0.014;
    muchaScallopedPath(ctx, pts, scallopAmp, r * 0.20);
    ctx.fillStyle = c.fill;
    ctx.fill();
    ctx.restore();

    // Interior tint (deserts / forests / etc)
    muchaScallopedPath(ctx, pts, scallopAmp, r * 0.20);
    ctx.save();
    ctx.clip();
    // Find bbox
    var bx = 999, by = 999, ex = -999, ey = -999;
    for (var p2 = 0; p2 < pts.length; p2++) {
      bx = Math.min(bx, pts[p2][0]); by = Math.min(by, pts[p2][1]);
      ex = Math.max(ex, pts[p2][0]); ey = Math.max(ey, pts[p2][1]);
    }
    var ig = ctx.createRadialGradient((bx + ex) / 2, (by + ey) / 2, 0,
                                       (bx + ex) / 2, (by + ey) / 2,
                                       Math.max(ex - bx, ey - by) * 0.6);
    ig.addColorStop(0.0, c.interior);
    ig.addColorStop(1.0, "rgba(0,0,0,0)");
    ctx.fillStyle = ig;
    ctx.fillRect(bx - 4, by - 4, (ex - bx) + 8, (ey - by) + 8);

    // Subtle topographic hatching — fine sage lines
    ctx.strokeStyle = "rgba( 68, 82, 64,0.32)";
    ctx.lineWidth   = 0.4;
    var step = r * 0.05;
    for (var ty = by; ty < ey; ty += step) {
      ctx.beginPath();
      var first = true;
      for (var tx = bx; tx <= ex; tx += step * 0.4) {
        var jy = ty + Math.sin(tx * 0.4) * step * 0.18;
        if (first) { ctx.moveTo(tx, jy); first = false; }
        else        ctx.lineTo(tx, jy);
      }
      ctx.stroke();
    }
    ctx.restore();

    // Coastline gold edge — thin engraved line
    muchaScallopedPath(ctx, pts, scallopAmp, r * 0.20);
    ctx.strokeStyle = "rgba(232,200,118,0.42)";
    ctx.lineWidth   = 0.6;
    ctx.stroke();
  }

  // Order matters — back to front
  drawContinent(MUCHA_EARTH_CONTINENTS.northAmerica, 1.0);
  drawContinent(MUCHA_EARTH_CONTINENTS.southAmerica, 1.0);
  drawContinent(MUCHA_EARTH_CONTINENTS.greenland,    0.6);
  drawContinent(MUCHA_EARTH_CONTINENTS.europe,       0.8);
  drawContinent(MUCHA_EARTH_CONTINENTS.africa,       1.0);
  drawContinent(MUCHA_EARTH_CONTINENTS.asia,         1.0);
  drawContinent(MUCHA_EARTH_CONTINENTS.india,        0.7);
  drawContinent(MUCHA_EARTH_CONTINENTS.southeastAsia, 0.7);
  drawContinent(MUCHA_EARTH_CONTINENTS.australia,    0.9);
  drawContinent(MUCHA_EARTH_CONTINENTS.antarctica,   1.2);

  // ── Polar compass rose — gold ornament at N pole ────────────
  ctx.save();
  ctx.translate(cx, cy - r * 0.92);
  ctx.strokeStyle = "rgba(232,200,118,0.85)";
  ctx.lineWidth   = 0.7;
  for (var rp = 0; rp < 8; rp++) {
    ctx.save();
    ctx.rotate(rp * Math.PI / 4);
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.lineTo(0, -r * 0.06);
    ctx.stroke();
    if (rp % 2 === 0) {
      ctx.beginPath();
      ctx.moveTo(-r * 0.012, -r * 0.045);
      ctx.lineTo( 0,          -r * 0.06);
      ctx.lineTo( r * 0.012, -r * 0.045);
      ctx.fillStyle = "rgba(232,200,118,0.85)";
      ctx.fill();
    }
    ctx.restore();
  }
  ctx.fillStyle = "rgba(166,128,42,0.85)";
  ctx.beginPath(); ctx.arc(0, 0, r * 0.014, 0, Math.PI * 2); ctx.fill();
  ctx.restore();

  // ── Landmark trefoils (Mucha city-marks, not animated) ─────
  for (var lm = 0; lm < MUCHA_EARTH_LANDMARKS.length; lm++) {
    var L = MUCHA_EARTH_LANDMARKS[lm];
    var lonR = L.lon * Math.PI / 180;
    var latR = L.lat * Math.PI / 180;
    var persp = Math.cos(lonR) * Math.cos(latR);
    if (persp < -0.05) continue;
    var lx = cx + r * Math.sin(lonR) * Math.cos(latR);
    var ly = cy - r * Math.sin(latR);
    if (Math.sqrt((lx - cx) * (lx - cx) + (ly - cy) * (ly - cy)) > r * 0.97) continue;
    ctx.save();
    ctx.translate(lx, ly);
    ctx.fillStyle = "rgba(166,128,42,0.70)";
    for (var tr = 0; tr < 3; tr++) {
      ctx.save();
      ctx.rotate(tr * Math.PI * 2 / 3);
      ctx.beginPath();
      ctx.ellipse(0, -r * 0.014, r * 0.006, r * 0.012, 0, 0, Math.PI * 2);
      ctx.fill();
      ctx.restore();
    }
    ctx.fillStyle = "rgba(232,200,118,0.92)";
    ctx.beginPath(); ctx.arc(0, 0, r * 0.005, 0, Math.PI * 2); ctx.fill();
    ctx.restore();
  }

  // ── Ocean specular sheen (top-left) ─────────────────────────
  var sp = ctx.createRadialGradient(cx - r * 0.34, cy - r * 0.36, 0,
                                    cx, cy, r);
  sp.addColorStop(0.0, "rgba(240,232,212,0.22)");
  sp.addColorStop(0.5, "rgba(220,200,160,0.04)");
  sp.addColorStop(1.0, "rgba(0,0,0,0)");
  ctx.fillStyle = sp;
  ctx.fillRect(0, 0, W, H);

  ctx.restore();   // end disc clip

  // ── Atmospheric limb halo (outside clip) ────────────────────
  ctx.strokeStyle = "rgba(120,168,210,0.45)";
  ctx.lineWidth   = 4;
  ctx.beginPath(); ctx.arc(cx, cy, r + 2, 0, Math.PI * 2); ctx.stroke();
  ctx.strokeStyle = "rgba(232,200,118,0.34)";
  ctx.lineWidth   = 1;
  ctx.beginPath(); ctx.arc(cx, cy, r + 0.5, 0, Math.PI * 2); ctx.stroke();

  // Grain — small density since canvas is small
  if (typeof applyMuchaGrain === "function") {
    applyMuchaGrain(ctx, W, H, 71, 0.55);
  }
}
