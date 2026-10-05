.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA SUN — pale-gold goddess with hair-rays, crown, halo
//  Designed to be drop-in for QML Canvas onPaint at 52×52 (the
//  Item that contains the sun Canvas). All coordinates scale by
//  W and H so the same code looks right at 52, 156, 208, etc.
// ═══════════════════════════════════════════════════════════════

function drawMuchaSun(ctx, W, H) {
  ctx.clearRect(0, 0, W, H);
  var cx = W / 2, cy = H / 2;
  var s  = Math.min(W, H);
  var disc   = s * 0.230;   // solar disc
  var pearlR = s * 0.300;   // dot ring radius
  var ringR  = s * 0.320;   // engraved bezel ring
  var shortR = s * 0.388;   // short ray tip
  var longR  = s * 0.495;   // long ray tip

  // ── Outer atmosphere wash ──────────────────────────────────────
  var atm = ctx.createRadialGradient(cx, cy, disc * 0.6, cx, cy, s * 0.52);
  atm.addColorStop(0.00, "rgba(248,228,160,0.22)");
  atm.addColorStop(0.55, "rgba(212,178,108,0.10)");
  atm.addColorStop(1.00, "rgba(0,0,0,0)");
  ctx.fillStyle = atm;
  ctx.fillRect(0, 0, W, H);

  // ── 12 long whiplash flame rays ────────────────────────────────
  for (var i = 0; i < 12; i++) {
    var ang = i * Math.PI / 6;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(ang);

    // Whiplash flame body — gradient from disc rim to tip
    var rg = ctx.createLinearGradient(0, -disc * 0.84, 0, -longR);
    rg.addColorStop(0.00, "rgba(248,232,178,0.95)");
    rg.addColorStop(0.30, "rgba(232,200,118,0.86)");
    rg.addColorStop(0.65, "rgba(196,156, 78,0.50)");
    rg.addColorStop(1.00, "rgba(140, 96, 30,0.00)");
    ctx.fillStyle = rg;

    var rw = disc * 0.34;                       // ray base half-width
    ctx.beginPath();
    ctx.moveTo(-rw * 0.85, -disc * 0.84);
    // Right edge: gentle S-curve outward then in
    ctx.bezierCurveTo( rw * 0.95, -disc * 0.94,
                       rw * 0.55, -longR * 0.78,
                       0,          -longR);
    // Left edge mirror back to start
    ctx.bezierCurveTo(-rw * 0.55, -longR * 0.78,
                      -rw * 0.95, -disc * 0.94,
                      -rw * 0.85, -disc * 0.84);
    ctx.closePath();
    ctx.fill();

    // Engraved inner spine
    ctx.strokeStyle = "rgba(140, 96, 30,0.55)";
    ctx.lineWidth   = s * 0.008;
    ctx.lineCap     = "round";
    ctx.beginPath();
    ctx.moveTo(0, -disc * 0.86);
    ctx.lineTo(0, -longR * 0.94);
    ctx.stroke();

    // Side veins
    ctx.strokeStyle = "rgba(168,124, 48,0.42)";
    ctx.lineWidth   = s * 0.005;
    for (var v = 0; v < 3; v++) {
      var vt = 0.25 + v * 0.22;
      var vy = -disc * 0.86 - (longR - disc * 0.86) * vt;
      var vw = rw * 0.55 * (1 - vt);
      ctx.beginPath();
      ctx.moveTo(0, vy);
      ctx.bezierCurveTo( vw * 0.7, vy + s * 0.012,
                         vw * 0.9, vy + s * 0.022,
                         vw,        vy + s * 0.030);
      ctx.stroke();
      ctx.beginPath();
      ctx.moveTo(0, vy);
      ctx.bezierCurveTo(-vw * 0.7, vy + s * 0.012,
                        -vw * 0.9, vy + s * 0.022,
                        -vw,        vy + s * 0.030);
      ctx.stroke();
    }

    // Tip jewel
    var tipG = ctx.createRadialGradient(0, -longR + s * 0.012, 0,
                                        0, -longR + s * 0.012, s * 0.024);
    tipG.addColorStop(0.0, "rgba(255,242,200,1.00)");
    tipG.addColorStop(0.6, "rgba(232,188, 88,0.85)");
    tipG.addColorStop(1.0, "rgba(140, 96, 30,0.00)");
    ctx.fillStyle = tipG;
    ctx.beginPath();
    ctx.arc(0, -longR + s * 0.012, s * 0.022, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
  }

  // ── 12 short petal-rays between the long ones ─────────────────
  for (var j = 0; j < 12; j++) {
    var ang2 = j * Math.PI / 6 + Math.PI / 12;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(ang2);

    var sg = ctx.createLinearGradient(0, -disc * 0.86, 0, -shortR);
    sg.addColorStop(0.00, "rgba(244,220,148,0.85)");
    sg.addColorStop(0.55, "rgba(212,170, 82,0.55)");
    sg.addColorStop(1.00, "rgba(160,108, 30,0.00)");
    ctx.fillStyle = sg;

    var sw = disc * 0.18;
    ctx.beginPath();
    ctx.moveTo(0, -disc * 0.86);
    ctx.bezierCurveTo( sw * 0.95, -disc * 0.92,
                       sw * 0.45, -shortR * 0.80,
                       0,           -shortR);
    ctx.bezierCurveTo(-sw * 0.45, -shortR * 0.80,
                      -sw * 0.95, -disc * 0.92,
                       0,          -disc * 0.86);
    ctx.fill();

    // Tiny tip dot
    ctx.fillStyle = "rgba(232,200,118,0.85)";
    ctx.beginPath();
    ctx.arc(0, -shortR + s * 0.008, s * 0.013, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
  }

  // ── Pearl ring — 36 beads, every 3rd a larger jewel ───────────
  for (var p = 0; p < 36; p++) {
    var pa = p * Math.PI / 18;
    var big = (p % 3 === 0);
    var px = cx + pearlR * Math.cos(pa);
    var py = cy + pearlR * Math.sin(pa);
    if (big) {
      var pg = ctx.createRadialGradient(px, py, 0, px, py, s * 0.020);
      pg.addColorStop(0.0, "rgba(255,242,200,1.00)");
      pg.addColorStop(0.6, "rgba(212,178,108,0.90)");
      pg.addColorStop(1.0, "rgba(110, 78, 20,0.00)");
      ctx.fillStyle = pg;
      ctx.beginPath();
      ctx.arc(px, py, s * 0.018, 0, Math.PI * 2);
      ctx.fill();
    } else {
      ctx.fillStyle = "rgba(196,156, 78,0.78)";
      ctx.beginPath();
      ctx.arc(px, py, s * 0.009, 0, Math.PI * 2);
      ctx.fill();
    }
  }

  // ── Engraved double bezel ring ────────────────────────────────
  ctx.strokeStyle = "rgba(166,128, 42,0.65)";
  ctx.lineWidth   = 0.9;
  ctx.beginPath(); ctx.arc(cx, cy, ringR,            0, Math.PI * 2); ctx.stroke();
  ctx.strokeStyle = "rgba(212,178,108,0.50)";
  ctx.lineWidth   = 0.55;
  ctx.beginPath(); ctx.arc(cx, cy, ringR - s * 0.020, 0, Math.PI * 2); ctx.stroke();

  // ── Disc shadow halo (slight) ──────────────────────────────────
  var sh = ctx.createRadialGradient(cx, cy, disc * 0.92,
                                    cx, cy, disc * 1.20);
  sh.addColorStop(0.0, "rgba( 90, 50,  6, 0.28)");
  sh.addColorStop(1.0, "rgba(  0,  0,  0, 0.00)");
  ctx.fillStyle = sh;
  ctx.beginPath(); ctx.arc(cx, cy, disc * 1.20, 0, Math.PI * 2); ctx.fill();

  // ── Solar disc — pale-gold radial ─────────────────────────────
  var dg = ctx.createRadialGradient(cx - disc * 0.24, cy - disc * 0.28, 0,
                                    cx, cy, disc);
  dg.addColorStop(0.00, "rgba(252,246,212,1.00)");
  dg.addColorStop(0.28, "rgba(244,224,150,1.00)");
  dg.addColorStop(0.62, "rgba(220,188, 96,1.00)");
  dg.addColorStop(0.92, "rgba(184,148, 56,1.00)");
  dg.addColorStop(1.00, "rgba(140,100, 24,1.00)");
  ctx.fillStyle = dg;
  ctx.beginPath(); ctx.arc(cx, cy, disc, 0, Math.PI * 2); ctx.fill();

  // ── Sun goddess (face + hair + crown) ─────────────────────────
  drawSunGoddess(ctx, cx, cy, disc);

  // ── Final specular highlight ──────────────────────────────────
  var hl = ctx.createRadialGradient(cx - disc * 0.32, cy - disc * 0.34, 0,
                                    cx, cy, disc);
  hl.addColorStop(0.00, "rgba(255,252,228,0.50)");
  hl.addColorStop(0.45, "rgba(255,248,210,0.10)");
  hl.addColorStop(1.00, "rgba(0,0,0,0)");
  ctx.fillStyle = hl;
  ctx.beginPath(); ctx.arc(cx, cy, disc, 0, Math.PI * 2); ctx.fill();
}

// ═══════════════════════════════════════════════════════════════
//  Sun goddess — bust within the solar disc
//  Drawn relative to (cx, cy) and sized by `disc`
// ═══════════════════════════════════════════════════════════════
function drawSunGoddess(ctx, cx, cy, disc) {
  var fW = disc * 0.50;   // face half-width
  var fH = disc * 0.62;   // face half-height
  var fY = cy - disc * 0.04;

  // ── Halo arc behind the head (engraved double crescent) ──────
  ctx.strokeStyle = "rgba(232,200,118,0.55)";
  ctx.lineWidth   = disc * 0.020;
  ctx.beginPath();
  ctx.arc(cx, fY - disc * 0.06, disc * 0.78, Math.PI * 1.05, Math.PI * 1.95);
  ctx.stroke();
  ctx.strokeStyle = "rgba(166,128, 42,0.42)";
  ctx.lineWidth   = disc * 0.010;
  ctx.beginPath();
  ctx.arc(cx, fY - disc * 0.06, disc * 0.86, Math.PI * 1.08, Math.PI * 1.92);
  ctx.stroke();
  // Small halo beads
  for (var hb = 0; hb < 7; hb++) {
    var hbA = Math.PI * 1.10 + (hb / 6) * Math.PI * 0.80;
    var hbx = cx + Math.cos(hbA) * disc * 0.82;
    var hby = fY - disc * 0.06 + Math.sin(hbA) * disc * 0.82;
    ctx.fillStyle = (hb === 3) ? "rgba(248,232,178,0.92)"
                               : "rgba(212,178,108,0.78)";
    ctx.beginPath();
    ctx.arc(hbx, hby, (hb === 3) ? disc * 0.030 : disc * 0.018, 0, Math.PI * 2);
    ctx.fill();
  }

  // ── Hair — long flowing tresses down the sides ───────────────
  ctx.strokeStyle = "rgba(140, 84, 22,0.78)";
  ctx.lineWidth   = disc * 0.034;
  ctx.lineCap     = "round";
  var sideAngs = [-0.95, -0.72, -0.50, -0.30, 0.30, 0.50, 0.72, 0.95];
  for (var sh2 = 0; sh2 < sideAngs.length; sh2++) {
    var sa  = sideAngs[sh2];
    var dir = sa < 0 ? -1 : 1;
    var sx  = cx + dir * fW * 0.92;
    var sy  = fY - fH * 0.30;
    ctx.beginPath();
    ctx.moveTo(sx, sy);
    ctx.bezierCurveTo(sx + dir * fW * 0.34, fY + fH * 0.20,
                      sx + dir * fW * 0.18, fY + fH * 0.70,
                      sx - dir * fW * 0.10, fY + fH * 1.05);
    ctx.stroke();
  }
  // Finer hair strands
  ctx.strokeStyle = "rgba( 92, 54, 12,0.50)";
  ctx.lineWidth   = disc * 0.012;
  for (var fs = 0; fs < 12; fs++) {
    var fsx = cx - fW * 0.95 + (fs / 11) * fW * 1.9;
    var fsy = fY - fH * 0.78;
    ctx.beginPath();
    ctx.moveTo(fsx, fsy);
    ctx.bezierCurveTo(fsx + (fs - 5.5) * disc * 0.02, fsy - disc * 0.10,
                      fsx + (fs - 5.5) * disc * 0.05, fsy - disc * 0.20,
                      fsx + (fs - 5.5) * disc * 0.08, fsy - disc * 0.30);
    ctx.stroke();
  }

  // ── Face oval ─────────────────────────────────────────────────
  var fg = ctx.createRadialGradient(cx - fW * 0.18, fY - fH * 0.22, 0,
                                    cx, fY, fH * 0.92);
  fg.addColorStop(0.00, "rgba(252,242,210,1.00)");
  fg.addColorStop(0.55, "rgba(240,218,164,1.00)");
  fg.addColorStop(0.88, "rgba(212,176,108,1.00)");
  fg.addColorStop(1.00, "rgba(170,128, 60,1.00)");
  ctx.fillStyle = fg;
  ctx.beginPath();
  ctx.ellipse(cx, fY, fW, fH, 0, 0, Math.PI * 2);
  ctx.fill();

  // ── Hair crown — parted with waves ────────────────────────────
  ctx.fillStyle = "rgba(140, 84, 22,0.88)";
  ctx.beginPath();
  ctx.moveTo(cx - fW * 1.02, fY - fH * 0.35);
  ctx.bezierCurveTo(cx - fW * 0.90, fY - fH * 1.05,
                    cx - fW * 0.30, fY - fH * 1.18,
                    cx,              fY - fH * 0.92);
  ctx.bezierCurveTo(cx + fW * 0.30, fY - fH * 1.18,
                    cx + fW * 0.90, fY - fH * 1.05,
                    cx + fW * 1.02, fY - fH * 0.35);
  ctx.bezierCurveTo(cx + fW * 0.92, fY - fH * 0.55,
                    cx + fW * 0.60, fY - fH * 0.70,
                    cx + fW * 0.18, fY - fH * 0.68);
  ctx.bezierCurveTo(cx,              fY - fH * 0.86,
                    cx,              fY - fH * 0.86,
                    cx - fW * 0.18, fY - fH * 0.68);
  ctx.bezierCurveTo(cx - fW * 0.60, fY - fH * 0.70,
                    cx - fW * 0.92, fY - fH * 0.55,
                    cx - fW * 1.02, fY - fH * 0.35);
  ctx.closePath();
  ctx.fill();
  // Wave lines through hair
  ctx.strokeStyle = "rgba( 70, 40,  8,0.55)";
  ctx.lineWidth   = disc * 0.012;
  for (var wv = 0; wv < 3; wv++) {
    var wY = fY - fH * (0.92 - wv * 0.10);
    ctx.beginPath();
    ctx.moveTo(cx - fW * 0.85, wY);
    ctx.bezierCurveTo(cx - fW * 0.30, wY - disc * 0.035,
                      cx + fW * 0.30, wY - disc * 0.035,
                      cx + fW * 0.85, wY);
    ctx.stroke();
  }
  // Center part / forehead jewel
  ctx.fillStyle = "rgba(196,156, 78,0.82)";
  ctx.beginPath();
  ctx.ellipse(cx, fY - fH * 0.78, disc * 0.020, disc * 0.044, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = "rgba(248,224,148,0.95)";
  ctx.beginPath();
  ctx.arc(cx, fY - fH * 0.78, disc * 0.014, 0, Math.PI * 2);
  ctx.fill();

  // ── Crown of poppies (3 blooms) ───────────────────────────────
  var crownPos = [[-0.46, -0.92], [0.00, -1.02], [0.46, -0.92]];
  for (var cp = 0; cp < crownPos.length; cp++) {
    var ccx = cx + fW * crownPos[cp][0];
    var ccy = fY + fH * crownPos[cp][1];
    var pr  = disc * 0.058;
    // 5 dusty-rose petals
    ctx.fillStyle = "rgba(200,144,144,0.92)";
    for (var pt = 0; pt < 5; pt++) {
      ctx.save();
      ctx.translate(ccx, ccy);
      ctx.rotate(pt * Math.PI * 2 / 5 + cp * 0.4);
      ctx.beginPath();
      ctx.ellipse(0, -pr * 0.70, pr * 0.38, pr * 0.78, 0, 0, Math.PI * 2);
      ctx.fill();
      ctx.restore();
    }
    // Inner shadow
    ctx.fillStyle = "rgba(112, 64, 64,0.55)";
    ctx.beginPath();
    ctx.arc(ccx, ccy, pr * 0.42, 0, Math.PI * 2);
    ctx.fill();
    // Stamen center — gold
    ctx.fillStyle = "rgba(232,200,118,0.95)";
    ctx.beginPath();
    ctx.arc(ccx, ccy, pr * 0.22, 0, Math.PI * 2);
    ctx.fill();
    // Sage leaves to either side
    ctx.fillStyle = "rgba(107,126, 98,0.78)";
    for (var lf = -1; lf <= 1; lf += 2) {
      ctx.save();
      ctx.translate(ccx + lf * pr * 0.55, ccy + pr * 0.10);
      ctx.rotate(lf * 0.5);
      ctx.beginPath();
      ctx.ellipse(0, 0, pr * 0.18, pr * 0.50, 0, 0, Math.PI * 2);
      ctx.fill();
      ctx.restore();
    }
  }

  // ── Eyebrows ──────────────────────────────────────────────────
  ctx.strokeStyle = "rgba( 70, 40, 10,0.78)";
  ctx.lineWidth   = disc * 0.022;
  ctx.lineCap     = "round";
  // Left
  ctx.beginPath();
  ctx.moveTo(cx - fW * 0.46, fY - fH * 0.22);
  ctx.bezierCurveTo(cx - fW * 0.28, fY - fH * 0.34,
                    cx - fW * 0.10, fY - fH * 0.32,
                    cx - fW * 0.04, fY - fH * 0.22);
  ctx.stroke();
  // Right
  ctx.beginPath();
  ctx.moveTo(cx + fW * 0.46, fY - fH * 0.22);
  ctx.bezierCurveTo(cx + fW * 0.28, fY - fH * 0.34,
                    cx + fW * 0.10, fY - fH * 0.32,
                    cx + fW * 0.04, fY - fH * 0.22);
  ctx.stroke();

  // ── Eyes — almond-shaped, lashes, dark pupil ─────────────────
  function drawEye(side) {
    var ex0 = cx + side * fW * 0.46;
    var ex1 = cx + side * fW * 0.06;
    var ey  = fY - fH * 0.08;
    // Eye almond fill (whites)
    ctx.fillStyle = "rgba(248,242,222,0.85)";
    ctx.beginPath();
    ctx.moveTo(ex0, ey);
    ctx.bezierCurveTo(cx + side * fW * 0.34, ey - fH * 0.10,
                      cx + side * fW * 0.12, ey - fH * 0.10,
                      ex1, ey);
    ctx.bezierCurveTo(cx + side * fW * 0.12, ey + fH * 0.06,
                      cx + side * fW * 0.34, ey + fH * 0.06,
                      ex0, ey);
    ctx.fill();
    // Iris
    var ix = cx + side * fW * 0.24;
    var iy = ey - fH * 0.005;
    var ir = disc * 0.038;
    var ig = ctx.createRadialGradient(ix, iy, 0, ix, iy, ir);
    ig.addColorStop(0.0, "rgba(120, 96, 50,1.00)");
    ig.addColorStop(0.7, "rgba( 80, 56, 18,1.00)");
    ig.addColorStop(1.0, "rgba( 40, 26,  4,1.00)");
    ctx.fillStyle = ig;
    ctx.beginPath();
    ctx.arc(ix, iy, ir, 0, Math.PI * 2);
    ctx.fill();
    // Highlight
    ctx.fillStyle = "rgba(255,252,228,0.90)";
    ctx.beginPath();
    ctx.arc(ix - ir * 0.30, iy - ir * 0.35, ir * 0.30, 0, Math.PI * 2);
    ctx.fill();
    // Upper lid line + lashes
    ctx.strokeStyle = "rgba( 38, 22,  4,0.92)";
    ctx.lineWidth   = disc * 0.018;
    ctx.beginPath();
    ctx.moveTo(ex0, ey);
    ctx.bezierCurveTo(cx + side * fW * 0.34, ey - fH * 0.10,
                      cx + side * fW * 0.12, ey - fH * 0.10,
                      ex1, ey);
    ctx.stroke();
    // 4 lashes
    ctx.lineWidth = disc * 0.008;
    for (var L = 0; L < 4; L++) {
      var lt = 0.18 + L * 0.22;
      var lx = ex0 + (ex1 - ex0) * lt;
      var ly = ey - Math.sin(lt * Math.PI) * fH * 0.10;
      ctx.beginPath();
      ctx.moveTo(lx, ly);
      ctx.lineTo(lx + side * disc * 0.006, ly - disc * 0.034);
      ctx.stroke();
    }
  }
  drawEye(-1);
  drawEye( 1);

  // ── Nose — subtle shadow strokes ──────────────────────────────
  ctx.strokeStyle = "rgba(172,108, 44,0.42)";
  ctx.lineWidth   = disc * 0.014;
  ctx.beginPath();
  ctx.moveTo(cx - fW * 0.05, fY + fH * 0.02);
  ctx.bezierCurveTo(cx - fW * 0.08, fY + fH * 0.16,
                    cx - fW * 0.02, fY + fH * 0.18,
                    cx,              fY + fH * 0.16);
  ctx.stroke();
  ctx.beginPath();
  ctx.moveTo(cx + fW * 0.05, fY + fH * 0.02);
  ctx.bezierCurveTo(cx + fW * 0.08, fY + fH * 0.16,
                    cx + fW * 0.02, fY + fH * 0.18,
                    cx,              fY + fH * 0.16);
  ctx.stroke();

  // ── Lips — cupid bow upper, full lower (dusty rose) ──────────
  // Upper lip
  ctx.fillStyle = "rgba(160,104,104,0.92)";
  ctx.beginPath();
  ctx.moveTo(cx - fW * 0.22, fY + fH * 0.34);
  ctx.bezierCurveTo(cx - fW * 0.14, fY + fH * 0.28,
                    cx - fW * 0.06, fY + fH * 0.32,
                    cx,              fY + fH * 0.34);
  ctx.bezierCurveTo(cx + fW * 0.06, fY + fH * 0.32,
                    cx + fW * 0.14, fY + fH * 0.28,
                    cx + fW * 0.22, fY + fH * 0.34);
  ctx.bezierCurveTo(cx + fW * 0.14, fY + fH * 0.36,
                    cx - fW * 0.14, fY + fH * 0.36,
                    cx - fW * 0.22, fY + fH * 0.34);
  ctx.fill();
  // Lower lip
  ctx.fillStyle = "rgba(200,144,144,0.92)";
  ctx.beginPath();
  ctx.moveTo(cx - fW * 0.22, fY + fH * 0.36);
  ctx.bezierCurveTo(cx - fW * 0.12, fY + fH * 0.46,
                    cx + fW * 0.12, fY + fH * 0.46,
                    cx + fW * 0.22, fY + fH * 0.36);
  ctx.bezierCurveTo(cx + fW * 0.10, fY + fH * 0.40,
                    cx - fW * 0.10, fY + fH * 0.40,
                    cx - fW * 0.22, fY + fH * 0.36);
  ctx.fill();
  // Lip-line shadow
  ctx.strokeStyle = "rgba(112, 64, 64,0.78)";
  ctx.lineWidth   = disc * 0.008;
  ctx.beginPath();
  ctx.moveTo(cx - fW * 0.22, fY + fH * 0.355);
  ctx.bezierCurveTo(cx - fW * 0.08, fY + fH * 0.375,
                    cx + fW * 0.08, fY + fH * 0.375,
                    cx + fW * 0.22, fY + fH * 0.355);
  ctx.stroke();
  // Tiny highlight on lower lip
  ctx.fillStyle = "rgba(252,232,210,0.55)";
  ctx.beginPath();
  ctx.ellipse(cx, fY + fH * 0.405, fW * 0.06, fH * 0.012, 0, 0, Math.PI * 2);
  ctx.fill();

  // ── Cheek blush (localized) ──────────────────────────────────
  for (var ch = -1; ch <= 1; ch += 2) {
    var bx = cx + ch * fW * 0.50;
    var by = fY + fH * 0.18;
    var cbg = ctx.createRadialGradient(bx, by, 0, bx, by, fW * 0.30);
    cbg.addColorStop(0.0, "rgba(200,144,144,0.42)");
    cbg.addColorStop(0.6, "rgba(200,144,144,0.18)");
    cbg.addColorStop(1.0, "rgba(200,144,144,0.00)");
    ctx.fillStyle = cbg;
    ctx.beginPath();
    ctx.ellipse(bx, by, fW * 0.30, fH * 0.22, 0, 0, Math.PI * 2);
    ctx.fill();
  }

  // ── Wheat sheaf — held across the chest (Mucha symbolic attribute) ──
  ctx.save();
  ctx.translate(cx, fY + fH * 0.92);
  // Two crossed stalks
  ctx.strokeStyle = "rgba(166,128, 42,0.78)";
  ctx.lineWidth   = disc * 0.014;
  ctx.lineCap     = "round";
  for (var stk = -1; stk <= 1; stk += 2) {
    ctx.save();
    ctx.rotate(stk * 0.18);
    // Stalk
    ctx.beginPath();
    ctx.moveTo(0, disc * 0.34);
    ctx.lineTo(stk * disc * 0.04, -disc * 0.10);
    ctx.stroke();
    // Wheat grains — paired ellipses up the stalk
    ctx.fillStyle = "rgba(232,200,118,0.92)";
    var grains = [-0.05, 0.04, 0.13, 0.22];
    for (var gr = 0; gr < grains.length; gr++) {
      var gy = grains[gr] * disc - disc * 0.06;
      var gx = stk * disc * (0.04 - gr * 0.012);
      ctx.save();
      ctx.translate(gx, gy);
      ctx.rotate(stk * 0.18);
      // Left grain
      ctx.beginPath();
      ctx.ellipse(-disc * 0.025, 0, disc * 0.012, disc * 0.028, 0.4, 0, Math.PI * 2);
      ctx.fill();
      // Right grain
      ctx.beginPath();
      ctx.ellipse( disc * 0.025, 0, disc * 0.012, disc * 0.028, -0.4, 0, Math.PI * 2);
      ctx.fill();
      // Awn — fine bristle line
      ctx.strokeStyle = "rgba(196,156, 78,0.75)";
      ctx.lineWidth   = disc * 0.006;
      ctx.beginPath();
      ctx.moveTo(0, 0);
      ctx.lineTo(stk * disc * 0.005, -disc * 0.060);
      ctx.stroke();
      ctx.restore();
    }
    // Tip awn — long bristles fanning up
    ctx.strokeStyle = "rgba(212,178,108,0.78)";
    ctx.lineWidth   = disc * 0.005;
    var tipY = -disc * 0.10;
    var tipX = stk * disc * 0.04;
    for (var aw = -1; aw <= 1; aw++) {
      ctx.beginPath();
      ctx.moveTo(tipX, tipY);
      ctx.lineTo(tipX + aw * disc * 0.020, tipY - disc * 0.080);
      ctx.stroke();
    }
    ctx.restore();
  }
  // Center ribbon tying the stalks
  ctx.fillStyle = "rgba(200,144,144,0.88)";
  ctx.beginPath();
  ctx.ellipse(0, disc * 0.16, disc * 0.044, disc * 0.020, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = "rgba(112, 64, 64,0.72)";
  ctx.beginPath();
  ctx.arc(0, disc * 0.16, disc * 0.010, 0, Math.PI * 2);
  ctx.fill();
  // Ribbon tails
  ctx.strokeStyle = "rgba(160,104,104,0.78)";
  ctx.lineWidth   = disc * 0.008;
  ctx.beginPath();
  ctx.moveTo(-disc * 0.036, disc * 0.18);
  ctx.bezierCurveTo(-disc * 0.06, disc * 0.22, -disc * 0.07, disc * 0.26, -disc * 0.05, disc * 0.30);
  ctx.moveTo( disc * 0.036, disc * 0.18);
  ctx.bezierCurveTo( disc * 0.06, disc * 0.22,  disc * 0.07, disc * 0.26,  disc * 0.05, disc * 0.30);
  ctx.stroke();
  ctx.restore();
}
