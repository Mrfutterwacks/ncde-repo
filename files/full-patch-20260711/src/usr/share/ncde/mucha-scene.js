.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA SPACE SCENE — sky, starfield, nebulae, elaborate
//  figurative Art Nouveau border with corner cartouches (sun,
//  moon, iris, poppy), top banner with location, bottom garland,
//  side lily sprays, warm/cool temperature wash following the
//  sun and moon arc positions, optional meteor + bird silhouette.
//
//  Renders at the scene size used in QML (e.g. 316×230). All
//  ornament scales with W and H so it works at any size.
//
//  Pass-through state used for warm/cool zones & meteor:
//    opts = {
//      sunArcAngle:  0..180,   // 0=east, 90=zenith, 180=west
//      moonArcAngle: 0..180,
//      sunVisible:   bool,
//      moonVisible:  bool,
//      meteorPhase:  0..1,     // animate by changing this
//      birdPhase:    0..1,     // 0..1 across earth disc
//      locationText: "ILL · 40°N",
//      dateText:     "MMVI · V · XXI"
//    }
// ═══════════════════════════════════════════════════════════════

function drawMuchaScene(ctx, W, H, opts) {
  opts = opts || {};
  ctx.clearRect(0, 0, W, H);

  // ── Sky base — deep midnight with violet haze ───────────────
  var sky = ctx.createRadialGradient(W * 0.5, H * 0.38, 0,
                                     W * 0.5, H * 0.50, W * 0.78);
  sky.addColorStop(0.00, "rgba( 26, 22, 52,1.00)");
  sky.addColorStop(0.34, "rgba( 18, 14, 40,1.00)");
  sky.addColorStop(0.68, "rgba( 10,  8, 24,1.00)");
  sky.addColorStop(1.00, "rgba(  4,  2, 12,1.00)");
  ctx.fillStyle = sky;
  ctx.fillRect(0, 0, W, H);

  // ── Nebula wash — dusty rose & violet ──────────────────────
  var neb1 = ctx.createRadialGradient(W * 0.66, H * 0.24, 0,
                                       W * 0.66, H * 0.24, W * 0.36);
  neb1.addColorStop(0.0, "rgba( 88, 38,108,0.18)");
  neb1.addColorStop(1.0, "rgba(0,0,0,0)");
  ctx.fillStyle = neb1; ctx.fillRect(0, 0, W, H);
  var neb2 = ctx.createRadialGradient(W * 0.22, H * 0.18, 0,
                                       W * 0.22, H * 0.18, W * 0.30);
  neb2.addColorStop(0.0, "rgba(160,108,108,0.10)");
  neb2.addColorStop(1.0, "rgba(0,0,0,0)");
  ctx.fillStyle = neb2; ctx.fillRect(0, 0, W, H);
  // Sage galactic dust along horizon
  var neb3 = ctx.createLinearGradient(0, H * 0.62, 0, H);
  neb3.addColorStop(0.0, "rgba(0,0,0,0)");
  neb3.addColorStop(0.6, "rgba( 88, 96, 78,0.10)");
  neb3.addColorStop(1.0, "rgba( 72, 60, 12,0.20)");
  ctx.fillStyle = neb3; ctx.fillRect(0, 0, W, H);

  // ── Temperature-zone wash: warm cone from sun, cool from moon ──
  function arcXY(ang) {
    var cx = W / 2;
    var cy = H / 2 + 10;
    var radius = Math.min(W, H) * 0.39;
    return {
      x: cx + radius * Math.cos((ang + 180) * Math.PI / 180),
      y: cy - Math.abs(radius * Math.sin(ang * Math.PI / 180)) * 1.1
    };
  }
  if (opts.sunVisible && typeof opts.sunArcAngle === "number") {
    var sp = arcXY(opts.sunArcAngle);
    var warmG = ctx.createRadialGradient(sp.x, sp.y, 0,
                                          sp.x, sp.y, W * 0.55);
    warmG.addColorStop(0.0, "rgba(232,178, 88,0.22)");
    warmG.addColorStop(0.4, "rgba(200,140, 60,0.10)");
    warmG.addColorStop(1.0, "rgba(0,0,0,0)");
    ctx.fillStyle = warmG;
    ctx.fillRect(0, 0, W, H);
  }
  if (opts.moonVisible && typeof opts.moonArcAngle === "number") {
    var mp = arcXY(opts.moonArcAngle);
    var coolG = ctx.createRadialGradient(mp.x, mp.y, 0,
                                          mp.x, mp.y, W * 0.45);
    coolG.addColorStop(0.0, "rgba(140,148,200,0.18)");
    coolG.addColorStop(0.4, "rgba(108,116,168,0.08)");
    coolG.addColorStop(1.0, "rgba(0,0,0,0)");
    ctx.fillStyle = coolG;
    ctx.fillRect(0, 0, W, H);
  }

  // ── Starfield — 4-point Mucha stars + dust ──────────────────
  function localStar4(x, y, R, alpha) {
    ctx.save();
    ctx.translate(x, y);
    ctx.fillStyle = "rgba(252,242,200," + alpha + ")";
    ctx.beginPath();
    for (var p = 0; p < 8; p++) {
      var a  = p * Math.PI / 4;
      var rd = (p % 2 === 0) ? R : R * 0.32;
      if (p === 0) ctx.moveTo(Math.cos(a - Math.PI / 4) * rd, Math.sin(a - Math.PI / 4) * rd);
      else         ctx.lineTo(Math.cos(a - Math.PI / 4) * rd, Math.sin(a - Math.PI / 4) * rd);
    }
    ctx.closePath();
    ctx.fill();
    ctx.fillStyle = "rgba(255,252,232,0.85)";
    ctx.beginPath();
    ctx.arc(0, 0, R * 0.28, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  var bigStars = [
    [0.07, 0.08, 5.0], [0.93, 0.07, 4.2], [0.50, 0.05, 5.6], [0.20, 0.13, 3.4],
    [0.80, 0.16, 3.8], [0.35, 0.22, 3.0], [0.65, 0.12, 3.4], [0.10, 0.30, 2.8],
    [0.90, 0.30, 2.8], [0.45, 0.32, 2.4], [0.55, 0.26, 2.4], [0.04, 0.46, 3.2],
    [0.96, 0.48, 3.2], [0.16, 0.58, 2.6], [0.84, 0.60, 2.6], [0.50, 0.60, 2.6]
  ];
  for (var bs = 0; bs < bigStars.length; bs++) {
    localStar4(bigStars[bs][0] * W, bigStars[bs][1] * H, bigStars[bs][2], 0.86);
  }
  // Fine dust
  ctx.fillStyle = "rgba(238,230,210,0.42)";
  for (var dd = 0; dd < 90; dd++) {
    var dx = ((dd * 73) % 100) / 100 * W;
    var dy = ((dd * 137) % 100) / 100 * H;
    var dr = ((dd * 23) % 100) > 70 ? 0.8 : 0.5;
    ctx.beginPath(); ctx.arc(dx, dy, dr, 0, Math.PI * 2); ctx.fill();
  }

  // ── Optional meteor streak ──────────────────────────────────
  if (typeof opts.meteorPhase === "number" && opts.meteorPhase > 0 && opts.meteorPhase < 1) {
    var mph = opts.meteorPhase;
    var sx0 = W * 0.10, sy0 = H * 0.06;
    var ex0 = W * 0.92, ey0 = H * 0.42;
    var mx = sx0 + (ex0 - sx0) * mph;
    var my = sy0 + (ey0 - sy0) * mph;
    var tg = ctx.createLinearGradient(mx - (ex0 - sx0) * 0.10, my - (ey0 - sy0) * 0.10,
                                       mx, my);
    tg.addColorStop(0.0, "rgba(252,232,178,0.00)");
    tg.addColorStop(0.7, "rgba(252,232,178,0.55)");
    tg.addColorStop(1.0, "rgba(252,248,220,0.95)");
    ctx.strokeStyle = tg;
    ctx.lineWidth   = 1.2;
    ctx.lineCap     = "round";
    ctx.beginPath();
    ctx.moveTo(mx - (ex0 - sx0) * 0.10, my - (ey0 - sy0) * 0.10);
    ctx.lineTo(mx, my);
    ctx.stroke();
    // Head star
    localStar4(mx, my, 2.4, 0.95);
  }

  // ── Horizon line ────────────────────────────────────────────
  ctx.strokeStyle = "rgba(212,178,108,0.18)";
  ctx.lineWidth   = 0.6;
  ctx.beginPath();
  ctx.moveTo(W * 0.08, H * 0.50 + 10);
  ctx.lineTo(W * 0.92, H * 0.50 + 10);
  ctx.stroke();

  // ═══ Mucha border ═══════════════════════════════════════════
  drawMuchaBorder(ctx, W, H, opts);
}

// ═══════════════════════════════════════════════════════════════
//  Border — figurative Mucha frame
// ═══════════════════════════════════════════════════════════════
function drawMuchaBorder(ctx, W, H, opts) {
  opts = opts || {};
  var gMain = "rgba(212,178,108,0.78)";
  var gDim  = "rgba(166,128, 42,0.55)";
  var gHi   = "rgba(248,232,178,0.92)";

  // ── Outer & inner gold lines ────────────────────────────────
  ctx.strokeStyle = gMain;
  ctx.lineWidth   = 1.4;
  ctx.strokeRect(3.5, 3.5, W - 7, H - 7);
  ctx.strokeStyle = gDim;
  ctx.lineWidth   = 0.85;
  ctx.strokeRect(9, 9, W - 18, H - 18);

  // ── Dot bands (top + bottom) ────────────────────────────────
  ctx.fillStyle = gMain;
  for (var td = 14; td < W - 12; td += 7) {
    var big = (Math.round(td / 7) % 3 === 0);
    ctx.beginPath(); ctx.arc(td, 6.5,     big ? 1.4 : 0.8, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(td, H - 6.5, big ? 1.4 : 0.8, 0, Math.PI * 2); ctx.fill();
  }
  for (var vd = 14; vd < H - 12; vd += 7) {
    var big2 = (Math.round(vd / 7) % 3 === 0);
    ctx.beginPath(); ctx.arc(6.5,     vd, big2 ? 1.4 : 0.8, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(W - 6.5, vd, big2 ? 1.4 : 0.8, 0, Math.PI * 2); ctx.fill();
  }

  // ── 4 corner cartouches — figurative ────────────────────────
  drawCornerSunGlyph (ctx,        16,        16);
  drawCornerMoonGlyph(ctx, W - 16,        16);
  drawCornerIris     (ctx,        16, H - 16);
  drawCornerPoppy    (ctx, W - 16, H - 16);

  // ── Top center cartouche — banner with location/date ───────
  drawTopCartouche(ctx, W / 2, 4.5, W,
                   opts.locationText || "ILL · 40° N",
                   opts.dateText     || romanDate(new Date()));

  // ── Bottom center garland ───────────────────────────────────
  drawBottomGarland(ctx, W / 2, H - 4.5, W);

  // ── Side lily sprays (mid-height) ───────────────────────────
  drawSideLilySpray(ctx,         4.5, H * 0.50,  1);
  drawSideLilySpray(ctx, W -     4.5, H * 0.50, -1);

  // ── #10 Border tangle — a poppy tendril from bottom-right
  //    corner reaches inward and curls around a star ──────────
  ctx.save();
  ctx.translate(W - 18, H - 18);
  ctx.strokeStyle = "rgba(166,128, 42,0.62)";
  ctx.lineWidth   = 0.85;
  ctx.lineCap     = "round";
  ctx.beginPath();
  ctx.moveTo(0, 0);
  ctx.bezierCurveTo(-W * 0.06, -H * 0.10, -W * 0.10, -H * 0.18, -W * 0.18, -H * 0.20);
  ctx.bezierCurveTo(-W * 0.24, -H * 0.21, -W * 0.28, -H * 0.18, -W * 0.30, -H * 0.14);
  ctx.stroke();
  // Tiny leaves along the tendril
  ctx.fillStyle = "rgba(107,126, 98,0.78)";
  var ldotsX = [-W * 0.08, -W * 0.16, -W * 0.24];
  var ldotsY = [-H * 0.13, -H * 0.19, -H * 0.18];
  for (var lt = 0; lt < 3; lt++) {
    ctx.save();
    ctx.translate(ldotsX[lt], ldotsY[lt]);
    ctx.rotate(-0.4 - lt * 0.2);
    ctx.beginPath();
    ctx.ellipse(0, 0, 2.6, 1.0, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  // Poppy bud at tip
  ctx.fillStyle = "rgba(200,144,144,0.92)";
  ctx.beginPath();
  ctx.arc(-W * 0.30, -H * 0.14, 2.6, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = "rgba(112, 64, 64,0.85)";
  ctx.beginPath();
  ctx.arc(-W * 0.30, -H * 0.14, 1.3, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
//  Corner cartouches
// ═══════════════════════════════════════════════════════════════
function drawCornerSunGlyph(ctx, x, y) {
  ctx.save();
  ctx.translate(x, y);
  ctx.fillStyle = "rgba(232,200,118,0.85)";
  for (var rp = 0; rp < 8; rp++) {
    ctx.save();
    ctx.rotate(rp * Math.PI / 4);
    ctx.beginPath();
    ctx.ellipse(0, -7, 1.2, 3.6, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  ctx.fillStyle = "rgba(248,232,178,0.95)";
  ctx.beginPath(); ctx.arc(0, 0, 2.6, 0, Math.PI * 2); ctx.fill();
  // Tiny face dot eyes
  ctx.fillStyle = "rgba(110, 78, 20,0.80)";
  ctx.beginPath(); ctx.arc(-0.9, -0.4, 0.4, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc( 0.9, -0.4, 0.4, 0, Math.PI * 2); ctx.fill();
  // Smile
  ctx.strokeStyle = "rgba(160, 84, 44,0.78)";
  ctx.lineWidth   = 0.5;
  ctx.beginPath();
  ctx.arc(0, 0.2, 1.0, 0.2, Math.PI - 0.2);
  ctx.stroke();
  ctx.restore();
}

function drawCornerMoonGlyph(ctx, x, y) {
  ctx.save();
  ctx.translate(x, y);
  // Crescent
  ctx.fillStyle = "rgba(232,222,196,0.90)";
  ctx.beginPath();
  ctx.arc(0, 0, 6.0, Math.PI * 0.30, Math.PI * 1.70, false);
  ctx.arc(2.4, 0, 4.6, Math.PI * 1.70, Math.PI * 0.30, true);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = "rgba(140,116, 64,0.78)";
  ctx.lineWidth   = 0.5;
  ctx.stroke();
  // Tiny stars around
  ctx.fillStyle = "rgba(252,242,200,0.92)";
  ctx.beginPath(); ctx.arc(-6, -4, 0.7, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(-4,  6, 0.6, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc( 6, -6, 0.5, 0, Math.PI * 2); ctx.fill();
  ctx.restore();
}

function drawCornerIris(ctx, x, y) {
  ctx.save();
  ctx.translate(x, y);
  // Iris flower — 3 upright + 3 falling petals
  // Lavender-violet falls
  ctx.fillStyle = "rgba(148,128,168,0.85)";
  for (var fp = 0; fp < 3; fp++) {
    ctx.save();
    ctx.rotate(fp * Math.PI * 2 / 3 + Math.PI / 6);
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.bezierCurveTo( 3, 2,  4, 5,  2.5, 7);
    ctx.bezierCurveTo( 1, 8, -1, 8, -2.5, 7);
    ctx.bezierCurveTo(-4, 5, -3, 2,  0,    0);
    ctx.fill();
    ctx.restore();
  }
  // Pale gold standards (upright petals)
  ctx.fillStyle = "rgba(232,200,118,0.78)";
  for (var sp = 0; sp < 3; sp++) {
    ctx.save();
    ctx.rotate(sp * Math.PI * 2 / 3);
    ctx.beginPath();
    ctx.ellipse(0, -3.4, 1.4, 3.2, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  // Center pistil
  ctx.fillStyle = "rgba(248,232,178,0.95)";
  ctx.beginPath(); ctx.arc(0, 0, 1.2, 0, Math.PI * 2); ctx.fill();
  // Stem hint
  ctx.strokeStyle = "rgba(107,126, 98,0.85)";
  ctx.lineWidth   = 0.7;
  ctx.beginPath();
  ctx.moveTo(0, 7);
  ctx.bezierCurveTo(-2, 12, -4, 16, -8, 16);
  ctx.stroke();
  ctx.restore();
}

function drawCornerPoppy(ctx, x, y) {
  ctx.save();
  ctx.translate(x, y);
  // Petals — 4 dusty rose
  ctx.fillStyle = "rgba(200,144,144,0.92)";
  for (var pp = 0; pp < 4; pp++) {
    ctx.save();
    ctx.rotate(pp * Math.PI / 2 + Math.PI / 8);
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.bezierCurveTo( 4, -1,  5, -4,  3, -6);
    ctx.bezierCurveTo( 1, -7, -1, -7, -3, -6);
    ctx.bezierCurveTo(-5, -4, -4, -1,  0,  0);
    ctx.fill();
    ctx.restore();
  }
  // Inner shadow
  ctx.fillStyle = "rgba(112, 64, 64,0.78)";
  ctx.beginPath(); ctx.arc(0, 0, 2.2, 0, Math.PI * 2); ctx.fill();
  // Stamen gold ring
  ctx.fillStyle = "rgba(232,200,118,0.88)";
  for (var st = 0; st < 12; st++) {
    var sa = st * Math.PI / 6;
    ctx.beginPath();
    ctx.arc(Math.cos(sa) * 1.4, Math.sin(sa) * 1.4, 0.4, 0, Math.PI * 2);
    ctx.fill();
  }
  // Seed pod center
  ctx.fillStyle = "rgba(166,128, 42,0.88)";
  ctx.beginPath(); ctx.arc(0, 0, 0.9, 0, Math.PI * 2); ctx.fill();
  // Stem
  ctx.strokeStyle = "rgba(107,126, 98,0.85)";
  ctx.lineWidth   = 0.7;
  ctx.beginPath();
  ctx.moveTo(0, 7);
  ctx.bezierCurveTo(2, 12, 4, 16, 8, 16);
  ctx.stroke();
  ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
//  Top cartouche — banner with location and Roman-numeral date
// ═══════════════════════════════════════════════════════════════
function drawTopCartouche(ctx, cx, y, W, locationText, dateText) {
  ctx.save();
  ctx.translate(cx, y);

  // Banner ribbon
  var bw = Math.min(W * 0.42, 130);
  var bh = 16;
  // Center plate
  var bg = ctx.createLinearGradient(0, 0, 0, bh);
  bg.addColorStop(0.0, "rgba(196,164, 92,0.92)");
  bg.addColorStop(0.5, "rgba(232,200,118,0.92)");
  bg.addColorStop(1.0, "rgba(160,128, 42,0.92)");
  ctx.fillStyle = bg;
  ctx.beginPath();
  ctx.moveTo(-bw / 2 + 6, 0);
  ctx.lineTo( bw / 2 - 6, 0);
  ctx.bezierCurveTo(bw / 2 + 2, 0, bw / 2 + 2, bh, bw / 2 - 6, bh);
  ctx.lineTo(-bw / 2 + 6, bh);
  ctx.bezierCurveTo(-bw / 2 - 2, bh, -bw / 2 - 2, 0, -bw / 2 + 6, 0);
  ctx.closePath();
  ctx.fill();
  // Side tails (forked ends)
  ctx.fillStyle = "rgba(166,128, 42,0.85)";
  for (var sd = -1; sd <= 1; sd += 2) {
    ctx.save();
    ctx.translate(sd * (bw / 2 + 6), bh / 2);
    ctx.beginPath();
    ctx.moveTo(0, -bh / 2);
    ctx.lineTo(sd * 16, -bh * 0.2);
    ctx.lineTo(sd * 10, 0);
    ctx.lineTo(sd * 16, bh * 0.2);
    ctx.lineTo(0, bh / 2);
    ctx.bezierCurveTo(sd * -3, bh / 2 - 2, sd * -3, -bh / 2 + 2, 0, -bh / 2);
    ctx.fill();
    ctx.restore();
  }
  // Edge engraving
  ctx.strokeStyle = "rgba(110, 78, 20,0.72)";
  ctx.lineWidth   = 0.6;
  ctx.beginPath();
  ctx.moveTo(-bw / 2 + 6, 0); ctx.lineTo(bw / 2 - 6, 0);
  ctx.moveTo(-bw / 2 + 6, bh); ctx.lineTo(bw / 2 - 6, bh);
  ctx.stroke();
  // Text — location centered, date below
  ctx.fillStyle    = "rgba( 60, 36,  8,0.95)";
  ctx.textAlign    = "center";
  ctx.textBaseline = "middle";
  ctx.font         = "600 8px serif";
  ctx.fillText(locationText, 0, bh * 0.30);
  ctx.font         = "italic 7px serif";
  ctx.fillText(dateText,     0, bh * 0.72);
  ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
//  Bottom garland — hanging beads on a curving line
// ═══════════════════════════════════════════════════════════════
function drawBottomGarland(ctx, cx, y, W) {
  ctx.save();
  ctx.translate(cx, y);
  ctx.strokeStyle = "rgba(166,128, 42,0.62)";
  ctx.lineWidth   = 0.9;
  ctx.beginPath();
  ctx.moveTo(-46, 0);
  ctx.bezierCurveTo(-28,  0, -10,  4, 0, 4);
  ctx.bezierCurveTo( 10,  4,  28,  0, 46, 0);
  ctx.stroke();
  // Beads
  ctx.fillStyle = "rgba(232,200,118,0.78)";
  var gx = [-34, -22, -12, -4, 0, 4, 12, 22, 34];
  var gy = [ -1,   1,   2,  3, 3, 3,  2,  1, -1];
  for (var gb = 0; gb < gx.length; gb++) {
    var big = (gb === 4);
    ctx.beginPath();
    ctx.arc(gx[gb], gy[gb], big ? 2.0 : 1.4, 0, Math.PI * 2);
    ctx.fill();
  }
  // Center hanging jewel
  ctx.fillStyle = "rgba(200,144,144,0.92)";
  ctx.beginPath();
  ctx.moveTo(0, 5);
  ctx.lineTo(-3, 9);
  ctx.lineTo(0, 13);
  ctx.lineTo(3, 9);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = "rgba(112, 64, 64,0.85)";
  ctx.lineWidth   = 0.5;
  ctx.stroke();
  ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
//  Side lily spray
// ═══════════════════════════════════════════════════════════════
function drawSideLilySpray(ctx, x, y, dir) {
  ctx.save();
  ctx.translate(x, y);
  ctx.strokeStyle = "rgba(166,128, 42,0.58)";
  ctx.lineWidth   = 0.95;
  ctx.lineCap     = "round";
  // Main stem
  ctx.beginPath();
  ctx.moveTo(0, -32);
  ctx.bezierCurveTo(dir * 6, -16, dir * 4, -4, 0, 0);
  ctx.bezierCurveTo(dir * 4, 4, dir * 6, 16, 0, 32);
  ctx.stroke();
  // Leaves
  ctx.fillStyle = "rgba(107,126, 98,0.75)";
  var ly = [-22, -10, 0, 10, 22];
  for (var l = 0; l < ly.length; l++) {
    ctx.save();
    ctx.translate(dir * 3, ly[l]);
    ctx.rotate(dir > 0 ? -0.45 : 0.45);
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.bezierCurveTo(dir * 6, -2, dir * 9, -0.5, dir * 7, 3);
    ctx.bezierCurveTo(dir * 6, 4.5, dir * 2, 3, 0, 0);
    ctx.fill();
    ctx.restore();
  }
  // Three lily flowers
  var fy = [-20, 0, 20];
  for (var f = 0; f < fy.length; f++) {
    ctx.save();
    ctx.translate(dir * 8, fy[f]);
    ctx.fillStyle = "rgba(232,222,196,0.92)";
    for (var pp = 0; pp < 6; pp++) {
      ctx.save();
      ctx.rotate(pp * Math.PI / 3);
      ctx.beginPath();
      ctx.ellipse(0, -3.6, 1.4, 3.2, 0, 0, Math.PI * 2);
      ctx.fill();
      ctx.restore();
    }
    ctx.fillStyle = "rgba(232,200,118,0.95)";
    ctx.beginPath();
    ctx.arc(0, 0, 1.4, 0, Math.PI * 2);
    ctx.fill();
    // Stamen dots
    ctx.fillStyle = "rgba(166,128, 42,0.85)";
    for (var sd = 0; sd < 5; sd++) {
      var sa = sd * Math.PI * 2 / 5;
      ctx.beginPath();
      ctx.arc(Math.cos(sa) * 1.0, Math.sin(sa) * 1.0, 0.4, 0, Math.PI * 2);
      ctx.fill();
    }
    ctx.restore();
  }
  ctx.restore();
}

// ═══════════════════════════════════════════════════════════════
//  Roman-numeral date helper — "MMVI · V · XXI"
// ═══════════════════════════════════════════════════════════════
function romanDate(d) {
  function R(n) {
    var v = [[1000,"M"],[900,"CM"],[500,"D"],[400,"CD"],[100,"C"],[90,"XC"],
             [50,"L"],[40,"XL"],[10,"X"],[9,"IX"],[5,"V"],[4,"IV"],[1,"I"]];
    var out = "";
    for (var i = 0; i < v.length; i++) {
      while (n >= v[i][0]) { out += v[i][1]; n -= v[i][0]; }
    }
    return out;
  }
  return R(d.getFullYear()) + " · " + R(d.getMonth() + 1) + " · " + R(d.getDate());
}
