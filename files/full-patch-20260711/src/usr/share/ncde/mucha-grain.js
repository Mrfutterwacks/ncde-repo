.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA LITHOGRAPH GRAIN — shared noise overlay
//  Call as the LAST step of each onPaint. Density auto-scales by
//  canvas area so a small icon gets less grain than a large scene.
//  `seed` keeps the pattern stable across repaints (use a constant
//  per-element so it doesn't shimmer between frames).
// ═══════════════════════════════════════════════════════════════
function applyMuchaGrain(ctx, W, H, seed, density) {
  if (density === undefined) density = 1.0;
  // Mulberry32 — small deterministic PRNG safe inside QML JS engine
  var a = (seed || 1) >>> 0;
  function rnd() {
    a = (a + 0x6D2B79F5) | 0;
    var t = a;
    t = Math.imul(t ^ (t >>> 15), t | 1);
    t ^= t + Math.imul(t ^ (t >>> 7), t | 61);
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  }
  var count = Math.round(W * H * 0.012 * density);
  for (var i = 0; i < count; i++) {
    var x = rnd() * W;
    var y = rnd() * H;
    var r = rnd();
    // mostly cool ink, occasional warm fleck — lithograph plate offset
    var warm = r > 0.88;
    var dark = r > 0.55;
    var rad  = (rnd() < 0.92) ? 0.4 : 0.9;
    if (warm) {
      ctx.fillStyle = "rgba(160,108,32,0.10)";
    } else if (dark) {
      ctx.fillStyle = "rgba(8,6,18,0.14)";
    } else {
      ctx.fillStyle = "rgba(240,232,212,0.06)";
    }
    ctx.beginPath();
    ctx.arc(x, y, rad, 0, Math.PI * 2);
    ctx.fill();
  }
  // Subtle vignette to unify
  var vg = ctx.createRadialGradient(W / 2, H / 2, Math.min(W, H) * 0.32,
                                    W / 2, H / 2, Math.max(W, H) * 0.72);
  vg.addColorStop(0.0, "rgba(0,0,0,0)");
  vg.addColorStop(1.0, "rgba(8,4,16,0.16)");
  ctx.fillStyle = vg;
  ctx.fillRect(0, 0, W, H);
}

// 4-point Mucha star — shared helper (if you don't already have it
// from mucha-moon.js, paste this once at the top of each onPaint that needs it).
function muchaStar4(ctx, x, y, r, fill) {
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
  ctx.fillStyle = "rgba(255,252,228,0.85)";
  ctx.beginPath();
  ctx.arc(0, 0, r * 0.28, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}
