.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA CITY LIGHTS — 4-point gold stars over earth's night side
//  with halo of pale-gold candle-glow. Renders only on the
//  rotated dark hemisphere; QML rotates this canvas with earth.
// ═══════════════════════════════════════════════════════════════

var MUCHA_CITIES = [
  [-74.0,  40.7, 1.00],  // New York
  [-87.6,  41.8, 0.92],  // Chicago
  [-118.2, 34.1, 0.92],  // Los Angeles
  [-122.4, 37.8, 0.82],  // San Francisco
  [-79.4,  43.7, 0.74],  // Toronto
  [-73.6,  45.5, 0.70],  // Montreal
  [-99.1,  19.4, 0.78],  // Mexico City
  [-43.2, -22.9, 0.82],  // Rio
  [-46.6, -23.5, 0.86],  // São Paulo
  [-58.4, -34.6, 0.70],  // Buenos Aires
  [-0.1,   51.5, 1.00],  // London
  [ 2.3,   48.9, 0.92],  // Paris
  [13.4,   52.5, 0.82],  // Berlin
  [12.5,   41.9, 0.74],  // Rome
  [-3.7,   40.4, 0.72],  // Madrid
  [37.6,   55.7, 0.82],  // Moscow
  [28.9,   41.0, 0.74],  // Istanbul
  [31.2,   30.1, 0.74],  // Cairo
  [55.3,   25.3, 0.68],  // Dubai
  [72.9,   19.1, 0.92],  // Mumbai
  [77.2,   28.6, 0.86],  // Delhi
  [88.4,   22.6, 0.78],  // Kolkata
  [104.0,  30.7, 0.82],  // Chengdu
  [121.5,  31.2, 1.00],  // Shanghai
  [116.4,  39.9, 1.00],  // Beijing
  [113.3,  23.1, 0.92],  // Guangzhou
  [114.2,  22.3, 0.84],  // Hong Kong
  [139.7,  35.7, 1.00],  // Tokyo
  [135.5,  34.7, 0.86],  // Osaka
  [126.9,  37.6, 0.92],  // Seoul
  [103.8,   1.3, 0.82],  // Singapore
  [101.7,   3.1, 0.72],  // Kuala Lumpur
  [151.2, -33.9, 0.78],  // Sydney
  [144.9, -37.8, 0.72]   // Melbourne
];

function drawMuchaCityLights(ctx, W, H) {
  ctx.clearRect(0, 0, W, H);
  var cx = W / 2, cy = H / 2;
  var r  = Math.min(W, H) / 2 - 1;

  // Soft 4-point gold-star helper inline (so this file can be
  // copied alone to a QML Canvas onPaint without depending on
  // mucha-moon.js or mucha-grain.js).
  function star4(x, y, R, alpha) {
    var col = "rgba(252,228,148," + alpha + ")";
    ctx.save();
    ctx.translate(x, y);
    ctx.fillStyle = col;
    ctx.beginPath();
    for (var p = 0; p < 8; p++) {
      var a  = p * Math.PI / 4;
      var rd = (p % 2 === 0) ? R : R * 0.30;
      if (p === 0) ctx.moveTo(Math.cos(a - Math.PI / 4) * rd, Math.sin(a - Math.PI / 4) * rd);
      else         ctx.lineTo(Math.cos(a - Math.PI / 4) * rd, Math.sin(a - Math.PI / 4) * rd);
    }
    ctx.closePath();
    ctx.fill();

    // Soft halo
    var hg = ctx.createRadialGradient(0, 0, 0, 0, 0, R * 2.6);
    hg.addColorStop(0.0, "rgba(252,232,168," + (alpha * 0.55) + ")");
    hg.addColorStop(0.6, "rgba(232,200,118," + (alpha * 0.20) + ")");
    hg.addColorStop(1.0, "rgba(0,0,0,0)");
    ctx.fillStyle = hg;
    ctx.beginPath();
    ctx.arc(0, 0, R * 2.6, 0, Math.PI * 2);
    ctx.fill();

    // Bright core
    ctx.fillStyle = "rgba(255,252,228," + alpha + ")";
    ctx.beginPath();
    ctx.arc(0, 0, R * 0.30, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }

  for (var i = 0; i < MUCHA_CITIES.length; i++) {
    var c = MUCHA_CITIES[i];
    var lonR = c[0] * Math.PI / 180;
    var latR = c[1] * Math.PI / 180;
    var persp = Math.cos(lonR) * Math.cos(latR);
    if (persp < -0.08) continue;
    var px = cx + r * Math.sin(lonR) * Math.cos(latR);
    var py = cy - r * Math.sin(latR);
    if (Math.sqrt((px - cx) * (px - cx) + (py - cy) * (py - cy)) > r * 0.97) continue;
    var alpha = c[2];
    var size  = alpha > 0.88 ? 2.4 : (alpha > 0.74 ? 1.8 : 1.4);
    star4(px, py, size, alpha);
  }
}
