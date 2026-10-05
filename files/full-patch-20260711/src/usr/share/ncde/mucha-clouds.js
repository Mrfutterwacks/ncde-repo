.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA CLOUDS — whiplash spiral cloud forms, not blob clouds.
//  Drawn over earth disc (120×120) and rotated independently by
//  QML's cloudRotation animation. Opacity driven by weather code.
// ═══════════════════════════════════════════════════════════════

function drawMuchaClouds(ctx, W, H) {
  ctx.clearRect(0, 0, W, H);
  var cx = W / 2, cy = H / 2;
  var r  = Math.min(W, H) / 2 - 2;

  ctx.save();
  ctx.beginPath(); ctx.arc(cx, cy, r, 0, Math.PI * 2); ctx.clip();

  // Cloud cluster definitions
  //   x, y normalized; size; rotation; whiplash count; opacity
  var clouds = [
    [0.30, 0.22, 0.32, -0.35, 3, 0.90],
    [0.70, 0.36, 0.26,  0.22, 2, 0.78],
    [0.52, 0.66, 0.36, -0.10, 3, 0.86],
    [0.18, 0.54, 0.22,  0.55, 2, 0.66],
    [0.82, 0.18, 0.24, -0.42, 2, 0.74],
    [0.42, 0.82, 0.30,  0.20, 3, 0.68],
    [0.86, 0.62, 0.20, -0.30, 2, 0.58],
    [0.12, 0.78, 0.24,  0.42, 2, 0.62],
    [0.58, 0.10, 0.20, -0.25, 2, 0.60]
  ];

  for (var c = 0; c < clouds.length; c++) {
    var cl   = clouds[c];
    var ccx  = cl[0] * W;
    var ccy  = cl[1] * H;
    var sz   = cl[2] * r * 1.4;
    var rot  = cl[3];
    var swirls = cl[4];
    var op   = cl[5];

    ctx.save();
    ctx.translate(ccx, ccy);
    ctx.rotate(rot);

    // Soft base body — radial ivory wash
    var bg = ctx.createRadialGradient(0, 0, 0, 0, 0, sz);
    bg.addColorStop(0.00, "rgba(252,248,238," + op + ")");
    bg.addColorStop(0.40, "rgba(232,222,196," + (op * 0.65) + ")");
    bg.addColorStop(0.78, "rgba(208,198,168," + (op * 0.28) + ")");
    bg.addColorStop(1.00, "rgba(180,168,138,0.00)");
    ctx.fillStyle = bg;
    ctx.beginPath();
    ctx.ellipse(0, 0, sz, sz * 0.55, 0, 0, Math.PI * 2);
    ctx.fill();

    // Whiplash spiral arms (the Mucha signature)
    ctx.strokeStyle = "rgba(248,242,222," + (op * 0.55) + ")";
    ctx.lineWidth   = sz * 0.060;
    ctx.lineCap     = "round";
    for (var sw = 0; sw < swirls; sw++) {
      var swA0 = sw * (Math.PI * 2 / swirls) + Math.PI * 0.10;
      var spinDir = (sw % 2 === 0) ? 1 : -1;
      ctx.beginPath();
      // Spiral curling inward — 1.5 turns
      var TURNS  = 1.4;
      var STEPS  = 32;
      for (var st = 0; st <= STEPS; st++) {
        var tt    = st / STEPS;
        var radius = sz * (0.92 - tt * 0.74);
        var ang    = swA0 + spinDir * tt * TURNS * Math.PI * 2;
        var sx = Math.cos(ang) * radius * (1.0 + Math.sin(tt * Math.PI) * 0.12);
        var sy = Math.sin(ang) * radius * 0.55;
        if (st === 0) ctx.moveTo(sx, sy);
        else          ctx.lineTo(sx, sy);
      }
      ctx.stroke();

      // Inner thinner highlight stroke
      ctx.save();
      ctx.strokeStyle = "rgba(255,254,244," + (op * 0.42) + ")";
      ctx.lineWidth   = sz * 0.022;
      ctx.beginPath();
      for (var st2 = 0; st2 <= STEPS; st2++) {
        var tt2     = st2 / STEPS;
        var radius2 = sz * (0.88 - tt2 * 0.70);
        var ang2    = swA0 + spinDir * tt2 * TURNS * Math.PI * 2;
        var sx2 = Math.cos(ang2) * radius2 * (1.0 + Math.sin(tt2 * Math.PI) * 0.10);
        var sy2 = Math.sin(ang2) * radius2 * 0.55;
        if (st2 === 0) ctx.moveTo(sx2, sy2);
        else           ctx.lineTo(sx2, sy2);
      }
      ctx.stroke();
      ctx.restore();
    }

    // Sage-tinged shadow underbelly
    ctx.fillStyle = "rgba(107,126, 98," + (op * 0.18) + ")";
    ctx.beginPath();
    ctx.ellipse(0, sz * 0.18, sz * 0.78, sz * 0.22, 0, 0, Math.PI * 2);
    ctx.fill();

    // Tiny condensation dot at swirl center
    ctx.fillStyle = "rgba(252,248,238," + (op * 0.85) + ")";
    ctx.beginPath();
    ctx.arc(0, 0, sz * 0.06, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
  }

  ctx.restore();   // end clip
}
