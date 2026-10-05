.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA MOON — pearl-and-silver goddess with star halo
//  Drawn at 52×52 (or scaled). Phase index 0..15 where:
//    0  = full moon
//    1..7 = waning gibbous → crescent
//    8  = new moon (mostly dark with faint rim)
//    9..15 = waxing crescent → gibbous
//  Match the QML moonFrame mapping (frame "00" .. "15").
// ═══════════════════════════════════════════════════════════════

function drawMuchaMoon(ctx, W, H, phase) {
  ctx.clearRect(0, 0, W, H);
  if (phase === undefined) phase = 0;
  phase = Math.max(0, Math.min(15, phase | 0));

  var cx = W / 2, cy = H / 2;
  var s  = Math.min(W, H);
  var disc   = s * 0.235;
  var pearlR = s * 0.305;
  var ringR  = s * 0.322;
  var crescR = s * 0.495;   // outer crescent halo radius

  // ── Atmospheric night-glow ────────────────────────────────────
  var atm = ctx.createRadialGradient(cx, cy, disc * 0.6, cx, cy, s * 0.52);
  atm.addColorStop(0.00, "rgba(180,190,228,0.20)");
  atm.addColorStop(0.55, "rgba(120,128,168,0.10)");
  atm.addColorStop(1.00, "rgba(0,0,0,0)");
  ctx.fillStyle = atm;
  ctx.fillRect(0, 0, W, H);

  // ── Outer crescent halo (Mucha "Moon" composition) ────────────
  //   A thin crescent-moon shape that wraps the goddess. This is
  //   her halo regardless of phase — phase shadowing only applies
  //   to the inner disc figure.
  ctx.save();
  // Outer arc (filled crescent)
  var outerCrescG = ctx.createRadialGradient(cx, cy - s * 0.04, disc * 0.85,
                                             cx, cy - s * 0.04, crescR);
  outerCrescG.addColorStop(0.00, "rgba(232,228,238,0.00)");
  outerCrescG.addColorStop(0.50, "rgba(208,212,228,0.42)");
  outerCrescG.addColorStop(0.85, "rgba(232,222,196,0.62)");
  outerCrescG.addColorStop(1.00, "rgba(166,148,108,0.00)");
  ctx.fillStyle = outerCrescG;
  ctx.beginPath();
  ctx.arc(cx, cy - s * 0.04, crescR,      Math.PI * 1.00, Math.PI * 2.00, false);
  ctx.arc(cx, cy - s * 0.04, disc * 0.92, Math.PI * 2.00, Math.PI * 1.00, true);
  ctx.closePath();
  ctx.fill();
  // Engraved outer edge
  ctx.strokeStyle = "rgba(212,200,168,0.78)";
  ctx.lineWidth   = 0.9;
  ctx.beginPath();
  ctx.arc(cx, cy - s * 0.04, crescR, Math.PI * 1.00, Math.PI * 2.00);
  ctx.stroke();
  // Inner crescent edge
  ctx.strokeStyle = "rgba(166,148,108,0.55)";
  ctx.lineWidth   = 0.6;
  ctx.beginPath();
  ctx.arc(cx, cy - s * 0.04, crescR - s * 0.018, Math.PI * 1.02, Math.PI * 1.98);
  ctx.stroke();
  ctx.restore();

  // ── Crescent tips — ornate finials ────────────────────────────
  for (var t = 0; t < 2; t++) {
    var tipA = t === 0 ? Math.PI : 0;
    var tx = cx + Math.cos(tipA) * crescR;
    var ty = cy - s * 0.04 + Math.sin(tipA) * crescR;
    var tg = ctx.createRadialGradient(tx, ty, 0, tx, ty, s * 0.034);
    tg.addColorStop(0.0, "rgba(248,242,222,1.00)");
    tg.addColorStop(0.6, "rgba(212,196,156,0.85)");
    tg.addColorStop(1.0, "rgba(110, 96, 60,0.00)");
    ctx.fillStyle = tg;
    ctx.beginPath();
    ctx.arc(tx, ty, s * 0.030, 0, Math.PI * 2);
    ctx.fill();
    // 6-point star inside finial
    ctx.fillStyle = "rgba(248,232,178,0.95)";
    for (var sp = 0; sp < 6; sp++) {
      var spA = sp * Math.PI / 3;
      var spR = s * 0.014;
      ctx.beginPath();
      ctx.moveTo(tx + Math.cos(spA       ) * spR,       ty + Math.sin(spA       ) * spR);
      ctx.lineTo(tx + Math.cos(spA + 0.52) * spR * 0.4, ty + Math.sin(spA + 0.52) * spR * 0.4);
      ctx.lineTo(tx + Math.cos(spA + 1.04) * spR,       ty + Math.sin(spA + 1.04) * spR);
      ctx.fill();
    }
  }

  // ── Stars scattered around the crescent (8 small 4-point) ────
  var stars = [
    [-0.78,  0.34, 1.0], [-0.62,  0.04, 0.7], [-0.30, -0.18, 1.1],
    [ 0.08, -0.26, 0.8], [ 0.34, -0.16, 1.0], [ 0.62,  0.06, 0.9],
    [ 0.80,  0.36, 1.1], [-0.46, -0.10, 0.6]
  ];
  for (var st = 0; st < stars.length; st++) {
    var sx = cx + stars[st][0] * crescR * 0.86;
    var sy = cy - s * 0.04 + stars[st][1] * crescR * 0.86;
    var sR = s * 0.016 * stars[st][2];
    drawStar4(ctx, sx, sy, sR, "rgba(248,232,178,0.92)");
  }

  // ── Pearl ring around disc ────────────────────────────────────
  for (var p = 0; p < 36; p++) {
    var pa = p * Math.PI / 18;
    var big = (p % 3 === 0);
    var px  = cx + pearlR * Math.cos(pa);
    var py  = cy + pearlR * Math.sin(pa);
    if (big) {
      var pg = ctx.createRadialGradient(px, py, 0, px, py, s * 0.020);
      pg.addColorStop(0.0, "rgba(248,242,222,1.00)");
      pg.addColorStop(0.6, "rgba(196,200,216,0.88)");
      pg.addColorStop(1.0, "rgba( 80, 90,128,0.00)");
      ctx.fillStyle = pg;
      ctx.beginPath();
      ctx.arc(px, py, s * 0.018, 0, Math.PI * 2);
      ctx.fill();
    } else {
      ctx.fillStyle = "rgba(178,184,206,0.78)";
      ctx.beginPath();
      ctx.arc(px, py, s * 0.009, 0, Math.PI * 2);
      ctx.fill();
    }
  }

  // ── Engraved silver bezel ──────────────────────────────────────
  ctx.strokeStyle = "rgba(138,140,168,0.65)";
  ctx.lineWidth   = 0.9;
  ctx.beginPath(); ctx.arc(cx, cy, ringR,             0, Math.PI * 2); ctx.stroke();
  ctx.strokeStyle = "rgba(208,212,228,0.50)";
  ctx.lineWidth   = 0.55;
  ctx.beginPath(); ctx.arc(cx, cy, ringR - s * 0.020, 0, Math.PI * 2); ctx.stroke();

  // ── Disc shadow halo ──────────────────────────────────────────
  var sh = ctx.createRadialGradient(cx, cy, disc * 0.92, cx, cy, disc * 1.18);
  sh.addColorStop(0.0, "rgba(10, 14, 38, 0.34)");
  sh.addColorStop(1.0, "rgba(0,0,0,0)");
  ctx.fillStyle = sh;
  ctx.beginPath(); ctx.arc(cx, cy, disc * 1.18, 0, Math.PI * 2); ctx.fill();

  // ── Moon disc — pearl / silver ────────────────────────────────
  var dg = ctx.createRadialGradient(cx - disc * 0.26, cy - disc * 0.30, 0,
                                    cx, cy, disc);
  dg.addColorStop(0.00, "rgba(252,250,244,1.00)");
  dg.addColorStop(0.32, "rgba(232,228,228,1.00)");
  dg.addColorStop(0.66, "rgba(196,196,212,1.00)");
  dg.addColorStop(0.92, "rgba(150,152,180,1.00)");
  dg.addColorStop(1.00, "rgba(108,110,142,1.00)");
  ctx.fillStyle = dg;
  ctx.beginPath(); ctx.arc(cx, cy, disc, 0, Math.PI * 2); ctx.fill();

  // ── Moon goddess profile (clipped to disc) ────────────────────
  ctx.save();
  ctx.beginPath(); ctx.arc(cx, cy, disc, 0, Math.PI * 2); ctx.clip();
  drawMoonGoddess(ctx, cx, cy, disc);
  ctx.restore();

  // ── Phase shadow (clipped to disc) ────────────────────────────
  //  Phase 0  = full       → no shadow
  //  Phase 8  = new        → whole disc shadowed (with earthshine glow)
  //  Phase 1..7  = waning  → dark on RIGHT side
  //  Phase 9..15 = waxing  → dark on LEFT side
  //  Earthshine: shadow is partially transparent + cool-blue tinted so the
  //  unlit portion glows faintly like the moon's own ashen-light photographs.
  if (phase !== 0) {
    ctx.save();
    ctx.beginPath(); ctx.arc(cx, cy, disc, 0, Math.PI * 2); ctx.clip();

    // Phase angle a: 0..2π over phase 0..16. Full = 0, new = π, full = 2π.
    var a    = (phase / 16) * Math.PI * 2;
    var cosA = Math.cos(a);

    var waning = phase < 8;
    var sign   = waning ?  1 : -1;
    // Terminator x at y=0 (signed):
    //   waning gibbous  (cosA > 0): xTerm0 > 0 → terminator on right (dark side)
    //   waning crescent (cosA < 0): xTerm0 < 0 → terminator on left  (lit side)
    //   waxing mirrors via `sign`
    var xTerm0 = sign * disc * cosA;

    // Build the dark-region path:
    //   • dark-side disc semicircle (top → bottom)
    //   • terminator arc (bottom → top), passing through (xTerm0, 0)
    ctx.beginPath();
    ctx.moveTo(cx, cy - disc);
    if (waning) {
      // Right semicircle (CCW=false through +x)
      ctx.arc(cx, cy, disc, -Math.PI / 2, Math.PI / 2, false);
    } else {
      // Left semicircle  (CCW=true through -x)
      ctx.arc(cx, cy, disc, -Math.PI / 2, Math.PI / 2, true);
    }
    var N = 24;
    for (var i = 1; i <= N; i++) {
      var t = Math.PI / 2 - (i / N) * Math.PI;
      var x = cx + xTerm0 * Math.cos(t);
      var y = cy + disc   * Math.sin(t);
      ctx.lineTo(x, y);
    }
    ctx.closePath();

    // EARTHSHINE — the shadow is cool-blue tinted and not fully opaque, so
    // the disc beneath glows faintly through it. Heavier near disc edge
    // (farther from terminator), lighter near the terminator itself.
    var shadowG = ctx.createRadialGradient(cx + sign * disc * 0.30, cy, 0,
                                            cx + sign * disc * 0.30, cy, disc * 1.15);
    shadowG.addColorStop(0.00, "rgba( 10, 14, 38, 0.72)");
    shadowG.addColorStop(0.60, "rgba( 14, 22, 56, 0.86)");
    shadowG.addColorStop(1.00, "rgba(  6, 10, 28, 0.92)");
    ctx.fillStyle = shadowG;
    ctx.fill();

    // Cool earthshine ambient — adds a faint blue wash inside the shadowed
    // path, suggesting earthlight reflecting onto the dark hemisphere.
    ctx.fillStyle = "rgba( 88,112,168, 0.10)";
    ctx.fill();

    // Soft penumbra along the terminator itself (warm-side glow)
    var penX = cx - sign * Math.abs(xTerm0) * 0.10;
    var penG = ctx.createRadialGradient(penX, cy, 0, penX, cy, disc * 1.20);
    penG.addColorStop(0.0, "rgba(232,200,118,0.06)");
    penG.addColorStop(0.6, "rgba(232,200,118,0.00)");
    penG.addColorStop(1.0, "rgba(  6, 10, 28,0.10)");
    ctx.fillStyle = penG;
    ctx.beginPath(); ctx.arc(cx, cy, disc, 0, Math.PI * 2); ctx.fill();

    // Subtle gold rim along the lit limb (the "horns" of a crescent glow)
    if (cosA !== 0) {
      ctx.strokeStyle = "rgba(248,232,178,0.55)";
      ctx.lineWidth   = 0.7;
      ctx.beginPath();
      var rimStart, rimEnd;
      if (waning) {
        // Lit side = left. Trace the disc's left semicircle.
        rimStart = Math.PI / 2;
        rimEnd   = 3 * Math.PI / 2;
      } else {
        // Lit side = right.
        rimStart = -Math.PI / 2;
        rimEnd   =  Math.PI / 2;
      }
      ctx.arc(cx, cy, disc - 0.3, rimStart, rimEnd, false);
      ctx.stroke();
    }

    ctx.restore();
  }

  // ── Final disc highlight (over phase shadow) ──────────────────
  var hl = ctx.createRadialGradient(cx - disc * 0.32, cy - disc * 0.34, 0,
                                    cx, cy, disc);
  hl.addColorStop(0.00, "rgba(255,254,244,0.42)");
  hl.addColorStop(0.50, "rgba(232,228,228,0.08)");
  hl.addColorStop(1.00, "rgba(0,0,0,0)");
  ctx.fillStyle = hl;
  ctx.beginPath(); ctx.arc(cx, cy, disc, 0, Math.PI * 2); ctx.fill();

  // ── Disc rim engraving (always visible, over shadow) ──────────
  ctx.strokeStyle = "rgba(108,110,142,0.62)";
  ctx.lineWidth   = 0.6;
  ctx.beginPath(); ctx.arc(cx, cy, disc - 0.4, 0, Math.PI * 2); ctx.stroke();
}

// 4-point Mucha star helper
function drawStar4(ctx, x, y, r, fill) {
  ctx.save();
  ctx.translate(x, y);
  ctx.fillStyle = fill;
  ctx.beginPath();
  for (var p = 0; p < 8; p++) {
    var a  = p * Math.PI / 4;
    var rd = (p % 2 === 0) ? r : r * 0.32;
    if (p === 0) ctx.moveTo(Math.cos(a - Math.PI / 4) * rd, Math.sin(a - Math.PI / 4) * rd);
    else         ctx.lineTo(Math.cos(a - Math.PI / 4) * rd, Math.sin(a - Math.PI / 4) * rd);
  }
  ctx.closePath();
  ctx.fill();
  // tiny center sparkle
  ctx.fillStyle = "rgba(255,252,228,0.92)";
  ctx.beginPath();
  ctx.arc(0, 0, r * 0.30, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
//  Moon goddess — left-facing profile in pale silver/lavender
// ═══════════════════════════════════════════════════════════════
function drawMoonGoddess(ctx, cx, cy, disc) {
  // Bust position — face fills upper-right of the disc, hair flows left/down
  var fW = disc * 0.46;
  var fH = disc * 0.60;
  var fX = cx + disc * 0.06;   // face center shifted right
  var fY = cy - disc * 0.04;

  // ── Long flowing hair (behind face) ──────────────────────────
  ctx.strokeStyle = "rgba( 86, 92,128,0.70)";
  ctx.lineWidth   = disc * 0.030;
  ctx.lineCap     = "round";
  var hairCurves = [
    [-0.72,  0.05,  -0.94,  0.62],
    [-0.62, -0.05,  -0.92,  0.42],
    [-0.50, -0.18,  -0.86,  0.20],
    [-0.34, -0.30,  -0.76, -0.05],
    [-0.16, -0.42,  -0.58, -0.28]
  ];
  for (var h = 0; h < hairCurves.length; h++) {
    var hc = hairCurves[h];
    ctx.beginPath();
    ctx.moveTo(fX + fW * 0.10, fY - fH * 0.30);
    ctx.bezierCurveTo(fX + fW * hc[0] * 0.6, fY + fH * hc[1] * 0.4,
                      fX + fW * hc[0],       fY + fH * hc[1],
                      fX + fW * hc[2],       fY + fH * hc[3]);
    ctx.stroke();
  }
  // Fine hair detail strands
  ctx.strokeStyle = "rgba( 60, 68,108,0.50)";
  ctx.lineWidth   = disc * 0.010;
  for (var fs = 0; fs < 8; fs++) {
    var t = fs / 7;
    ctx.beginPath();
    ctx.moveTo(fX - fW * 0.10 - t * fW * 0.5, fY - fH * 0.35 - t * fH * 0.15);
    ctx.bezierCurveTo(fX - fW * (0.40 + t * 0.4), fY + fH * 0.05,
                      fX - fW * (0.70 + t * 0.3), fY + fH * (0.30 - t * 0.5),
                      fX - fW * (0.90 + t * 0.05), fY + fH * (0.50 - t * 0.8));
    ctx.stroke();
  }

  // ── Face profile silhouette (3/4 view, ivory) ────────────────
  var fg = ctx.createRadialGradient(fX - fW * 0.20, fY - fH * 0.28, 0,
                                    fX, fY, fH * 0.92);
  fg.addColorStop(0.00, "rgba(252,248,238,1.00)");
  fg.addColorStop(0.55, "rgba(232,224,212,1.00)");
  fg.addColorStop(0.88, "rgba(196,192,196,1.00)");
  fg.addColorStop(1.00, "rgba(148,148,168,1.00)");
  ctx.fillStyle = fg;
  // Profile-like oval slightly compressed
  ctx.beginPath();
  ctx.ellipse(fX, fY, fW, fH, 0, 0, Math.PI * 2);
  ctx.fill();

  // ── Hair top crown — parted, draping over forehead ───────────
  ctx.fillStyle = "rgba( 70, 78,116,0.92)";
  ctx.beginPath();
  ctx.moveTo(fX - fW * 1.00, fY - fH * 0.32);
  ctx.bezierCurveTo(fX - fW * 0.88, fY - fH * 1.05,
                    fX - fW * 0.30, fY - fH * 1.18,
                    fX,              fY - fH * 0.92);
  ctx.bezierCurveTo(fX + fW * 0.30, fY - fH * 1.18,
                    fX + fW * 0.88, fY - fH * 1.05,
                    fX + fW * 1.00, fY - fH * 0.32);
  ctx.bezierCurveTo(fX + fW * 0.92, fY - fH * 0.52,
                    fX + fW * 0.62, fY - fH * 0.70,
                    fX + fW * 0.18, fY - fH * 0.66);
  ctx.bezierCurveTo(fX,              fY - fH * 0.86,
                    fX,              fY - fH * 0.86,
                    fX - fW * 0.18, fY - fH * 0.66);
  ctx.bezierCurveTo(fX - fW * 0.62, fY - fH * 0.70,
                    fX - fW * 0.92, fY - fH * 0.52,
                    fX - fW * 1.00, fY - fH * 0.32);
  ctx.closePath();
  ctx.fill();
  // Hair wave lines
  ctx.strokeStyle = "rgba( 40, 46, 78,0.60)";
  ctx.lineWidth   = disc * 0.010;
  for (var wv = 0; wv < 3; wv++) {
    var wY = fY - fH * (0.90 - wv * 0.10);
    ctx.beginPath();
    ctx.moveTo(fX - fW * 0.84, wY);
    ctx.bezierCurveTo(fX - fW * 0.30, wY - disc * 0.034,
                      fX + fW * 0.30, wY - disc * 0.034,
                      fX + fW * 0.84, wY);
    ctx.stroke();
  }

  // ── Crescent ornament in hair (Mucha signature) ──────────────
  ctx.save();
  ctx.translate(fX, fY - fH * 0.78);
  ctx.fillStyle = "rgba(232,222,196,0.95)";
  ctx.beginPath();
  ctx.arc(0, 0, disc * 0.050, Math.PI * 1.20, Math.PI * 1.80, false);
  ctx.arc(disc * 0.020, 0, disc * 0.038, Math.PI * 1.80, Math.PI * 1.20, true);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = "rgba(140,116, 64,0.80)";
  ctx.lineWidth   = 0.6;
  ctx.stroke();
  // Tiny star inside crescent
  drawStar4(ctx, disc * 0.005, -disc * 0.002, disc * 0.014,
            "rgba(248,232,178,0.95)");
  ctx.restore();

  // ── Stars in the hair (3 small) ──────────────────────────────
  drawStar4(ctx, fX - fW * 0.66, fY - fH * 0.48, disc * 0.022,
            "rgba(248,232,178,0.85)");
  drawStar4(ctx, fX + fW * 0.42, fY - fH * 0.60, disc * 0.018,
            "rgba(232,222,196,0.78)");
  drawStar4(ctx, fX + fW * 0.78, fY - fH * 0.20, disc * 0.020,
            "rgba(248,232,178,0.82)");

  // ── Eyebrow (subtle, slightly downcast) ──────────────────────
  ctx.strokeStyle = "rgba( 50, 56, 92,0.72)";
  ctx.lineWidth   = disc * 0.022;
  ctx.lineCap     = "round";
  ctx.beginPath();
  ctx.moveTo(fX - fW * 0.46, fY - fH * 0.18);
  ctx.bezierCurveTo(fX - fW * 0.28, fY - fH * 0.32,
                    fX - fW * 0.10, fY - fH * 0.30,
                    fX - fW * 0.02, fY - fH * 0.18);
  ctx.stroke();
  ctx.beginPath();
  ctx.moveTo(fX + fW * 0.46, fY - fH * 0.18);
  ctx.bezierCurveTo(fX + fW * 0.28, fY - fH * 0.32,
                    fX + fW * 0.10, fY - fH * 0.30,
                    fX + fW * 0.02, fY - fH * 0.18);
  ctx.stroke();

  // ── Eyes — downcast / dreaming (mostly closed) ───────────────
  function drawDreamEye(side) {
    var ex0 = fX + side * fW * 0.46;
    var ex1 = fX + side * fW * 0.06;
    var ey  = fY - fH * 0.04;
    // Lash line — gentle downward curve
    ctx.strokeStyle = "rgba( 30, 36, 70,0.92)";
    ctx.lineWidth   = disc * 0.020;
    ctx.beginPath();
    ctx.moveTo(ex0, ey);
    ctx.bezierCurveTo(fX + side * fW * 0.34, ey + fH * 0.04,
                      fX + side * fW * 0.12, ey + fH * 0.04,
                      ex1, ey);
    ctx.stroke();
    // Lashes
    ctx.lineWidth = disc * 0.008;
    for (var L = 0; L < 4; L++) {
      var lt = 0.18 + L * 0.22;
      var lx = ex0 + (ex1 - ex0) * lt;
      var ly = ey + Math.sin(lt * Math.PI) * fH * 0.04;
      ctx.beginPath();
      ctx.moveTo(lx, ly);
      ctx.lineTo(lx + side * disc * 0.004, ly + disc * 0.030);
      ctx.stroke();
    }
    // Tiny iris hint (just visible under lid)
    ctx.fillStyle = "rgba(120,130,168,0.55)";
    ctx.beginPath();
    ctx.ellipse(fX + side * fW * 0.24, ey + fH * 0.01,
                disc * 0.024, disc * 0.010, 0, 0, Math.PI * 2);
    ctx.fill();
  }
  drawDreamEye(-1);
  drawDreamEye( 1);

  // ── Nose shadow ───────────────────────────────────────────────
  ctx.strokeStyle = "rgba(140,128,148,0.45)";
  ctx.lineWidth   = disc * 0.014;
  ctx.beginPath();
  ctx.moveTo(fX - fW * 0.05, fY + fH * 0.04);
  ctx.bezierCurveTo(fX - fW * 0.08, fY + fH * 0.18,
                    fX - fW * 0.02, fY + fH * 0.20,
                    fX,              fY + fH * 0.18);
  ctx.stroke();
  ctx.beginPath();
  ctx.moveTo(fX + fW * 0.05, fY + fH * 0.04);
  ctx.bezierCurveTo(fX + fW * 0.08, fY + fH * 0.18,
                    fX + fW * 0.02, fY + fH * 0.20,
                    fX,              fY + fH * 0.18);
  ctx.stroke();

  // ── Lips — softer dusty rose, small smile ────────────────────
  ctx.fillStyle = "rgba(160,116,128,0.88)";
  ctx.beginPath();
  ctx.moveTo(fX - fW * 0.20, fY + fH * 0.36);
  ctx.bezierCurveTo(fX - fW * 0.12, fY + fH * 0.30,
                    fX - fW * 0.04, fY + fH * 0.34,
                    fX,              fY + fH * 0.36);
  ctx.bezierCurveTo(fX + fW * 0.04, fY + fH * 0.34,
                    fX + fW * 0.12, fY + fH * 0.30,
                    fX + fW * 0.20, fY + fH * 0.36);
  ctx.bezierCurveTo(fX + fW * 0.12, fY + fH * 0.38,
                    fX - fW * 0.12, fY + fH * 0.38,
                    fX - fW * 0.20, fY + fH * 0.36);
  ctx.fill();
  ctx.fillStyle = "rgba(196,150,158,0.88)";
  ctx.beginPath();
  ctx.moveTo(fX - fW * 0.20, fY + fH * 0.38);
  ctx.bezierCurveTo(fX - fW * 0.10, fY + fH * 0.46,
                    fX + fW * 0.10, fY + fH * 0.46,
                    fX + fW * 0.20, fY + fH * 0.38);
  ctx.bezierCurveTo(fX + fW * 0.10, fY + fH * 0.42,
                    fX - fW * 0.10, fY + fH * 0.42,
                    fX - fW * 0.20, fY + fH * 0.38);
  ctx.fill();
  ctx.strokeStyle = "rgba(108, 76, 92,0.72)";
  ctx.lineWidth   = disc * 0.007;
  ctx.beginPath();
  ctx.moveTo(fX - fW * 0.20, fY + fH * 0.375);
  ctx.bezierCurveTo(fX - fW * 0.08, fY + fH * 0.395,
                    fX + fW * 0.08, fY + fH * 0.395,
                    fX + fW * 0.20, fY + fH * 0.375);
  ctx.stroke();

  // ── Cheek tint ────────────────────────────────────────────────
  for (var ch = -1; ch <= 1; ch += 2) {
    var bx = fX + ch * fW * 0.48;
    var by = fY + fH * 0.20;
    var cbg = ctx.createRadialGradient(bx, by, 0, bx, by, fW * 0.28);
    cbg.addColorStop(0.0, "rgba(196,148,150,0.34)");
    cbg.addColorStop(0.6, "rgba(196,148,150,0.14)");
    cbg.addColorStop(1.0, "rgba(196,148,150,0.00)");
    ctx.fillStyle = cbg;
    ctx.beginPath();
    ctx.ellipse(bx, by, fW * 0.30, fH * 0.22, 0, 0, Math.PI * 2);
    ctx.fill();
  }

  // ── Pearl earring ────────────────────────────────────────────
  for (var er = -1; er <= 1; er += 2) {
    var erx = fX + er * fW * 0.96;
    var ery = fY + fH * 0.42;
    var erg = ctx.createRadialGradient(erx, ery, 0, erx, ery, disc * 0.028);
    erg.addColorStop(0.0, "rgba(252,250,244,1.00)");
    erg.addColorStop(0.6, "rgba(208,212,228,0.85)");
    erg.addColorStop(1.0, "rgba( 80, 90,128,0.00)");
    ctx.fillStyle = erg;
    ctx.beginPath();
    ctx.arc(erx, ery, disc * 0.026, 0, Math.PI * 2);
    ctx.fill();
    // Hanging silver pearl
    ctx.fillStyle = "rgba(208,212,228,0.90)";
    ctx.beginPath();
    ctx.arc(erx, ery + disc * 0.060, disc * 0.014, 0, Math.PI * 2);
    ctx.fill();
  }

  // ── Poppy stem — held across chest (sleep / night symbol) ───
  ctx.save();
  ctx.translate(fX, fY + fH * 0.94);
  // Two stems crossing
  ctx.strokeStyle = "rgba( 86,108, 82,0.78)";
  ctx.lineWidth   = disc * 0.014;
  ctx.lineCap     = "round";
  for (var stm = -1; stm <= 1; stm += 2) {
    ctx.save();
    ctx.rotate(stm * 0.22);
    // Stem
    ctx.beginPath();
    ctx.moveTo(0, disc * 0.32);
    ctx.bezierCurveTo(stm * disc * 0.02,  disc * 0.18,
                      stm * disc * 0.06,  disc * 0.02,
                      stm * disc * 0.06, -disc * 0.10);
    ctx.stroke();
    // Sage leaves along stem
    ctx.fillStyle = "rgba(107,126, 98,0.82)";
    var leafPts = [[0.18, 0.05], [0.06, -0.35]];
    for (var lp = 0; lp < leafPts.length; lp++) {
      ctx.save();
      ctx.translate(stm * disc * leafPts[lp][0], disc * leafPts[lp][1]);
      ctx.rotate(stm * 0.55);
      ctx.beginPath();
      ctx.ellipse(0, 0, disc * 0.024, disc * 0.012, 0, 0, Math.PI * 2);
      ctx.fill();
      ctx.restore();
    }
    // Poppy bloom at tip — only on left stem; right stem has a seed pod
    ctx.save();
    ctx.translate(stm * disc * 0.06, -disc * 0.10);
    if (stm === -1) {
      // Open poppy flower — 4 dusty rose petals
      ctx.fillStyle = "rgba(200,144,144,0.95)";
      for (var pt = 0; pt < 4; pt++) {
        ctx.save();
        ctx.rotate(pt * Math.PI / 2 + Math.PI / 8);
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.bezierCurveTo( disc * 0.044, -disc * 0.020,
                            disc * 0.052, -disc * 0.062,
                            disc * 0.028, -disc * 0.080);
        ctx.bezierCurveTo( disc * 0.010, -disc * 0.084,
                           -disc * 0.010, -disc * 0.084,
                           -disc * 0.028, -disc * 0.080);
        ctx.bezierCurveTo(-disc * 0.052, -disc * 0.062,
                           -disc * 0.044, -disc * 0.020,
                            0, 0);
        ctx.fill();
        ctx.restore();
      }
      // Inner dark blot
      ctx.fillStyle = "rgba(112, 64, 64,0.85)";
      ctx.beginPath();
      ctx.arc(0, 0, disc * 0.028, 0, Math.PI * 2);
      ctx.fill();
      // Stamen ring
      ctx.fillStyle = "rgba(232,200,118,0.92)";
      for (var sm = 0; sm < 8; sm++) {
        var sma = sm * Math.PI / 4;
        ctx.beginPath();
        ctx.arc(Math.cos(sma) * disc * 0.020,
                Math.sin(sma) * disc * 0.020,
                disc * 0.005, 0, Math.PI * 2);
        ctx.fill();
      }
      // Center seed
      ctx.fillStyle = "rgba(166,128, 42,0.92)";
      ctx.beginPath();
      ctx.arc(0, 0, disc * 0.010, 0, Math.PI * 2);
      ctx.fill();
    } else {
      // Seed pod — capsule with ribbed engraving and small crown
      var pg = ctx.createRadialGradient(-disc * 0.014, -disc * 0.025, 0,
                                         0, -disc * 0.025, disc * 0.044);
      pg.addColorStop(0.0, "rgba(208,196,168,1.00)");
      pg.addColorStop(0.5, "rgba(168,156,128,1.00)");
      pg.addColorStop(1.0, "rgba(106,100, 80,1.00)");
      ctx.fillStyle = pg;
      ctx.beginPath();
      ctx.ellipse(0, -disc * 0.025, disc * 0.034, disc * 0.052, 0, 0, Math.PI * 2);
      ctx.fill();
      // Ribbed engraving
      ctx.strokeStyle = "rgba( 86, 78, 56,0.78)";
      ctx.lineWidth   = 0.5;
      for (var rb = -2; rb <= 2; rb++) {
        ctx.beginPath();
        ctx.moveTo(rb * disc * 0.012, -disc * 0.060);
        ctx.lineTo(rb * disc * 0.012,  disc * 0.020);
        ctx.stroke();
      }
      // Crown on top — small petals
      ctx.fillStyle = "rgba(140,128,100,0.95)";
      for (var cw = 0; cw < 5; cw++) {
        ctx.save();
        ctx.translate(0, -disc * 0.072);
        ctx.rotate((cw - 2) * 0.35);
        ctx.beginPath();
        ctx.ellipse(0, -disc * 0.012, disc * 0.006, disc * 0.014, 0, 0, Math.PI * 2);
        ctx.fill();
        ctx.restore();
      }
    }
    ctx.restore();
    ctx.restore();
  }
  // Tie ribbon at crossing point — silver
  ctx.fillStyle = "rgba(208,212,228,0.92)";
  ctx.beginPath();
  ctx.ellipse(0, disc * 0.18, disc * 0.044, disc * 0.020, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = "rgba(108,116,148,0.78)";
  ctx.beginPath();
  ctx.arc(0, disc * 0.18, disc * 0.010, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = "rgba(148,156,180,0.78)";
  ctx.lineWidth   = disc * 0.008;
  ctx.beginPath();
  ctx.moveTo(-disc * 0.036, disc * 0.20);
  ctx.bezierCurveTo(-disc * 0.06, disc * 0.24, -disc * 0.08, disc * 0.30, -disc * 0.06, disc * 0.34);
  ctx.moveTo( disc * 0.036, disc * 0.20);
  ctx.bezierCurveTo( disc * 0.06, disc * 0.24,  disc * 0.08, disc * 0.30,  disc * 0.06, disc * 0.34);
  ctx.stroke();
  ctx.restore();

  // ── Owl silhouette perched in the hair (Mucha night attribute) ──
  ctx.save();
  ctx.translate(fX - fW * 0.84, fY - fH * 0.58);
  ctx.rotate(-0.18);
  // Body
  ctx.fillStyle = "rgba( 24, 28, 52,0.92)";
  ctx.beginPath();
  ctx.ellipse(0, 0, disc * 0.044, disc * 0.060, 0, 0, Math.PI * 2);
  ctx.fill();
  // Head
  ctx.beginPath();
  ctx.arc(0, -disc * 0.060, disc * 0.040, 0, Math.PI * 2);
  ctx.fill();
  // Ear tufts
  ctx.beginPath();
  ctx.moveTo(-disc * 0.030, -disc * 0.095);
  ctx.lineTo(-disc * 0.020, -disc * 0.075);
  ctx.lineTo(-disc * 0.005, -disc * 0.090);
  ctx.fill();
  ctx.beginPath();
  ctx.moveTo( disc * 0.030, -disc * 0.095);
  ctx.lineTo( disc * 0.020, -disc * 0.075);
  ctx.lineTo( disc * 0.005, -disc * 0.090);
  ctx.fill();
  // Glowing eyes — pale gold
  ctx.fillStyle = "rgba(252,232,178,0.95)";
  ctx.beginPath(); ctx.arc(-disc * 0.014, -disc * 0.062, disc * 0.008, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc( disc * 0.014, -disc * 0.062, disc * 0.008, 0, Math.PI * 2); ctx.fill();
  ctx.fillStyle = "rgba(110, 78, 20,0.85)";
  ctx.beginPath(); ctx.arc(-disc * 0.014, -disc * 0.062, disc * 0.003, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc( disc * 0.014, -disc * 0.062, disc * 0.003, 0, Math.PI * 2); ctx.fill();
  // Beak
  ctx.fillStyle = "rgba(212,178,108,0.95)";
  ctx.beginPath();
  ctx.moveTo(0, -disc * 0.048);
  ctx.lineTo(-disc * 0.004, -disc * 0.036);
  ctx.lineTo( disc * 0.004, -disc * 0.036);
  ctx.fill();
  // Wing edge — single line down body
  ctx.strokeStyle = "rgba( 60, 70,108,0.85)";
  ctx.lineWidth   = 0.5;
  ctx.beginPath();
  ctx.moveTo(-disc * 0.020, -disc * 0.020);
  ctx.bezierCurveTo(-disc * 0.024, 0,
                    -disc * 0.024, disc * 0.025,
                    -disc * 0.018, disc * 0.040);
  ctx.stroke();
  ctx.beginPath();
  ctx.moveTo( disc * 0.020, -disc * 0.020);
  ctx.bezierCurveTo( disc * 0.024, 0,
                     disc * 0.024, disc * 0.025,
                     disc * 0.018, disc * 0.040);
  ctx.stroke();
  ctx.restore();
}
