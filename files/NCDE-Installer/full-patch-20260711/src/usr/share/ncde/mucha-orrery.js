.pragma library
// ═══════════════════════════════════════════════════════════════
//  MUCHA ORRERY — brass arc with Roman-numeral hour marks and
//  zodiac glyphs, armatures connecting sun & moon to center.
//  Draws the orbital track + armatures + zodiac. Sun/moon discs
//  are rendered separately on top (mucha-sun.js, mucha-moon.js).
//
//  opts = {
//    sunArcAngle:  0..180 or <0 hidden
//    moonArcAngle: 0..180 or <0 hidden
//    sunVisible:   bool
//    moonVisible:  bool
//    monthIndex:   0..11      // current month, for highlighting zodiac
//  }
// ═══════════════════════════════════════════════════════════════

// Zodiac glyphs in approximate solar-month order (Aries = March)
//   Each entry: glyph (unicode astrological), short ascii fallback
var MUCHA_ZODIAC = [
  { g: "\u2648", n: "Ari" },  // Aries        Mar 21 – Apr 19
  { g: "\u2649", n: "Tau" },  // Taurus       Apr 20 – May 20
  { g: "\u264A", n: "Gem" },  // Gemini       May 21 – Jun 20
  { g: "\u264B", n: "Cnc" },  // Cancer       Jun 21 – Jul 22
  { g: "\u264C", n: "Leo" },  // Leo          Jul 23 – Aug 22
  { g: "\u264D", n: "Vir" },  // Virgo        Aug 23 – Sep 22
  { g: "\u264E", n: "Lib" },  // Libra        Sep 23 – Oct 22
  { g: "\u264F", n: "Sco" },  // Scorpio      Oct 23 – Nov 21
  { g: "\u2650", n: "Sgr" },  // Sagittarius  Nov 22 – Dec 21
  { g: "\u2651", n: "Cap" },  // Capricorn    Dec 22 – Jan 19
  { g: "\u2652", n: "Aqr" },  // Aquarius     Jan 20 – Feb 18
  { g: "\u2653", n: "Psc" }   // Pisces       Feb 19 – Mar 20
];

function drawMuchaOrrery(ctx, W, H, opts) {
  opts = opts || {};
  ctx.clearRect(0, 0, W, H);

  var cx     = W / 2;
  var cy     = H / 2 + 10;
  var orbitR = Math.min(W, H) * 0.382;

  function arcX(a)         { return cx + orbitR * Math.cos((a + 180) * Math.PI / 180); }
  function arcY(a)         { return cy - Math.abs(orbitR * Math.sin(a * Math.PI / 180)) * 1.1; }
  function arcXr(a, dr)    { return cx + (orbitR - dr) * Math.cos((a + 180) * Math.PI / 180); }
  function arcYr(a, dr)    { return cy - Math.abs((orbitR - dr) * Math.sin(a * Math.PI / 180)) * 1.1; }

  var gMain  = "rgba(212,178,108,0.82)";
  var gDim   = "rgba(166,128, 42,0.50)";
  var gLight = "rgba(248,232,178,0.92)";
  var gGlow  = "rgba(232,200,118,0.20)";

  // ── Outer glow halo ──────────────────────────────────────────
  ctx.strokeStyle = gGlow;
  ctx.lineWidth   = 6;
  ctx.lineCap     = "round";
  ctx.beginPath();
  for (var ga = 0; ga <= 180; ga += 3) {
    if (ga === 0) ctx.moveTo(arcX(ga), arcY(ga));
    else          ctx.lineTo(arcX(ga), arcY(ga));
  }
  ctx.stroke();

  // ── Main track ───────────────────────────────────────────────
  ctx.strokeStyle = gMain;
  ctx.lineWidth   = 1.3;
  ctx.beginPath();
  for (var a = 0; a <= 180; a += 2) {
    if (a === 0) ctx.moveTo(arcX(a), arcY(a));
    else         ctx.lineTo(arcX(a), arcY(a));
  }
  ctx.stroke();

  // ── Parallel inner & outer tracks (engraved) ─────────────────
  ctx.strokeStyle = gDim;
  ctx.lineWidth   = 0.55;
  for (var k = 0; k < 2; k++) {
    var dr = k === 0 ? 5 : -5;
    ctx.beginPath();
    for (var ai = 0; ai <= 180; ai += 2) {
      if (ai === 0) ctx.moveTo(arcXr(ai, dr), arcYr(ai, dr));
      else          ctx.lineTo(arcXr(ai, dr), arcYr(ai, dr));
    }
    ctx.stroke();
  }

  // ── Tick marks every 15° ─────────────────────────────────────
  for (var t = 0; t <= 180; t += 15) {
    var tx = arcX(t), ty = arcY(t);
    var dt = 2;
    var tx2 = arcX(Math.min(t + dt, 180)), ty2 = arcY(Math.min(t + dt, 180));
    var tdx = tx2 - tx, tdy = ty2 - ty;
    var tlen = Math.sqrt(tdx * tdx + tdy * tdy) || 1;
    var nx = -tdy / tlen, ny = tdx / tlen;
    var major = (t % 45 === 0);
    var len = major ? 11 : 6;
    ctx.strokeStyle = major ? gLight : gMain;
    ctx.lineWidth   = major ? 1.4 : 0.9;
    ctx.beginPath();
    ctx.moveTo(tx + nx * len * 0.5, ty + ny * len * 0.5);
    ctx.lineTo(tx - nx * len * 0.5, ty - ny * len * 0.5);
    ctx.stroke();
    if (major) {
      ctx.fillStyle = gLight;
      ctx.beginPath();
      ctx.arc(tx, ty, 2.2, 0, Math.PI * 2);
      ctx.fill();
    }
  }

  // ── Roman-numeral hour labels at cardinal points ─────────────
  ctx.fillStyle    = "rgba(232,200,118,0.92)";
  ctx.font         = "italic 600 9px serif";
  ctx.textAlign    = "center";
  ctx.textBaseline = "middle";
  var labels = [
    [0,   "VI"],   // east horizon ≈ 6 (sunrise)
    [45,  "IX"],   // morning
    [90,  "XII"],  // noon zenith
    [135, "III"],  // afternoon
    [180, "VI"]    // west horizon ≈ 6 (sunset)
  ];
  for (var l = 0; l < labels.length; l++) {
    var la = labels[l][0], txt = labels[l][1];
    var lx = arcX(la), ly = arcY(la);
    var ldx = lx - cx, ldy = ly - cy;
    var llen = Math.sqrt(ldx * ldx + ldy * ldy) || 1;
    ctx.fillText(txt, lx + ldx / llen * 14, ly + ldy / llen * 14);
  }

  // ── Zodiac glyphs along the inner track ──────────────────────
  //  12 evenly-spaced positions across the visible arc (0..180).
  //  Highlight the current month's glyph in pale gold; others in dim.
  var monthIdx = (typeof opts.monthIndex === "number") ? opts.monthIndex
                                                       : (new Date().getMonth());
  // Map calendar month to zodiac index — zodiac begins at Aries (Mar)
  // Mar=2 → Aries(0), Apr=3 → Taurus(1), … so zodiacIdx = (month + 10) % 12
  var currentZ = (monthIdx + 10) % 12;
  ctx.textBaseline = "middle";
  ctx.textAlign    = "center";
  for (var z = 0; z < 12; z++) {
    var za = (z / 11) * 180;
    var zx = arcXr(za, -16);          // outside the orbit
    var zy = arcYr(za, -16);
    var active = (z === currentZ);
    ctx.fillStyle = active ? "rgba(248,232,178,0.95)"
                           : "rgba(166,128, 42,0.55)";
    ctx.font = active ? "600 11px serif" : "11px serif";
    ctx.fillText(MUCHA_ZODIAC[z].g, zx, zy);
    // Tiny brass cup beneath each glyph
    ctx.strokeStyle = active ? "rgba(248,232,178,0.65)"
                             : "rgba(166,128, 42,0.40)";
    ctx.lineWidth   = 0.5;
    ctx.beginPath();
    ctx.arc(zx, zy, 6.5, 0, Math.PI * 2);
    ctx.stroke();
  }

  // ── Horizon base line (dashed) ───────────────────────────────
  ctx.strokeStyle = "rgba(166,128, 42,0.40)";
  ctx.lineWidth   = 0.85;
  ctx.setLineDash([4, 3]);
  ctx.beginPath();
  ctx.moveTo(arcX(0)   - 8, arcY(0));
  ctx.lineTo(arcX(180) + 8, arcY(180));
  ctx.stroke();
  ctx.setLineDash([]);
  // End caps
  ctx.fillStyle = gMain;
  ctx.beginPath(); ctx.arc(arcX(0),   arcY(0),   3.5, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(arcX(180), arcY(180), 3.5, 0, Math.PI * 2); ctx.fill();
  ctx.strokeStyle = gLight; ctx.lineWidth = 0.8;
  ctx.beginPath(); ctx.arc(arcX(0),   arcY(0),   5.5, 0, Math.PI * 2); ctx.stroke();
  ctx.beginPath(); ctx.arc(arcX(180), arcY(180), 5.5, 0, Math.PI * 2); ctx.stroke();

  // ── Zenith marker ────────────────────────────────────────────
  ctx.fillStyle = gLight;
  ctx.beginPath(); ctx.arc(arcX(90), arcY(90) - 9, 2.6, 0, Math.PI * 2); ctx.fill();
  ctx.strokeStyle = gDim; ctx.lineWidth = 0.7;
  ctx.beginPath();
  ctx.moveTo(arcX(90), arcY(90));
  ctx.lineTo(arcX(90), arcY(90) - 16);
  ctx.stroke();

  // ── Sun armature ─────────────────────────────────────────────
  if (opts.sunVisible && typeof opts.sunArcAngle === "number" && opts.sunArcAngle >= 0) {
    var sx = arcX(opts.sunArcAngle), sy = arcY(opts.sunArcAngle);
    var ag = ctx.createLinearGradient(cx, cy, sx, sy);
    ag.addColorStop(0.0, "rgba(212,178,108,0.18)");
    ag.addColorStop(0.6, "rgba(212,178,108,0.55)");
    ag.addColorStop(1.0, "rgba(248,232,178,0.82)");
    ctx.strokeStyle = ag;
    ctx.lineWidth   = 1.5;
    ctx.setLineDash([3, 2]);
    ctx.beginPath(); ctx.moveTo(cx, cy); ctx.lineTo(sx, sy); ctx.stroke();
    ctx.setLineDash([]);
    ctx.strokeStyle = gLight; ctx.lineWidth = 1.2;
    ctx.beginPath(); ctx.arc(sx, sy, 5, 0, Math.PI * 2); ctx.stroke();
  }

  // ── Moon armature ────────────────────────────────────────────
  if (opts.moonVisible && typeof opts.moonArcAngle === "number" &&
      opts.moonArcAngle >= 0 && opts.moonArcAngle <= 180) {
    var mx = arcX(opts.moonArcAngle), my = arcY(opts.moonArcAngle);
    var mg = ctx.createLinearGradient(cx, cy, mx, my);
    mg.addColorStop(0.0, "rgba(148,168,215,0.10)");
    mg.addColorStop(0.6, "rgba(148,168,215,0.40)");
    mg.addColorStop(1.0, "rgba(185,205,245,0.78)");
    ctx.strokeStyle = mg;
    ctx.lineWidth   = 1.2;
    ctx.setLineDash([2, 3]);
    ctx.beginPath(); ctx.moveTo(cx, cy); ctx.lineTo(mx, my); ctx.stroke();
    ctx.setLineDash([]);
    ctx.strokeStyle = "rgba(208,212,228,0.78)"; ctx.lineWidth = 1.0;
    ctx.beginPath(); ctx.arc(mx, my, 4, 0, Math.PI * 2); ctx.stroke();
  }

  // ── Center gimbal joint ──────────────────────────────────────
  ctx.strokeStyle = gLight; ctx.lineWidth = 1.2;
  ctx.beginPath(); ctx.arc(cx, cy, 7, 0, Math.PI * 2); ctx.stroke();
  ctx.fillStyle = "rgba(166,128, 42,0.50)";
  ctx.beginPath(); ctx.arc(cx, cy, 4.4, 0, Math.PI * 2); ctx.fill();
  ctx.strokeStyle = gLight; ctx.lineWidth = 0.7;
  ctx.beginPath();
  ctx.moveTo(cx - 9, cy); ctx.lineTo(cx + 9, cy);
  ctx.moveTo(cx, cy - 9); ctx.lineTo(cx, cy + 9);
  ctx.stroke();
}
