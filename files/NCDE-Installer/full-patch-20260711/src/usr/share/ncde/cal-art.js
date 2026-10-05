// cal-art.js — Canvas ornaments for the NCDE Calendar.
// Illuminated-manuscript page texture, seasonal botanical header art,
// moon-phase glyphs, today-gem, hand-drawn zodiac glyphs. Pure Canvas 2D,
// QML-safe (no Path2D, no ctx.ellipse, no ctx.filter).
//
// Palette (2026-09-24, operator: the Iris palette is universal): the gold
// leaf, the seal red and the page's age-stain come from the live palette
// (ncde.gilt4/gilt2/gilt0/wine4) instead of fixed hexes. This file is imported
// WITHOUT .pragma library, so it runs in its importer's context and can read
// `ncde` itself — every painter re-reads it on entry, so every caller
// (Ledger, ClockCalendarPopup, Season card, Manual) follows the palette with
// no change of its own. The fixed values stay as the fallback. Seasonal
// flowers, the frog and the moon keep their own illustration colours.
.import "ncde-color.js" as Col

const CalArt = (() => {
  let GOLD_B = "#e2c772", GOLD = "#b8862c", GOLD_D = "#6e4f17";
  let SEAL = "#8a2230";
  function _sync() {
    try {
      if (typeof ncde === "undefined" || !ncde || ncde.gilt2 === undefined) return;
      GOLD_B = Col.hex(ncde.gilt4); GOLD = Col.hex(ncde.gilt2); GOLD_D = Col.hex(ncde.gilt0);
      if (ncde.wine4 !== undefined) SEAL = Col.hex(ncde.wine4);
    } catch (e) { /* no engine (standalone preview): keep the fixed golds */ }
  }

  // QML-safe ellipse via translate/scale/arc
  function ellipse(ctx, cx, cy, rx, ry, rot) {
    ctx.save(); ctx.translate(cx, cy); if (rot) ctx.rotate(rot); ctx.scale(rx, ry);
    ctx.arc(0, 0, 1, 0, Math.PI*2); ctx.restore();
  }

  function rng(seed) { let s = seed % 2147483647; if (s<=0) s+=2147483646;
    return () => { s = (s*16807) % 2147483647; return (s-1)/2147483646; }; }

  // ── Parchment page texture ──────────────────────────────────
  // dark/surfaceColor/surfaceAltColor let the caller pass NCDEKit's live k.dark/k.surface/
  // k.surface2 so the page itself goes dark-adaptive like every other parchment surface —
  // otherwise adaptive ink text (k.ink) goes light-on-light against this permanently-light page.
  function paintPage(ctx, w, h, dark, surfaceColor, surfaceAltColor) {
    const g = ctx.createLinearGradient(0, 0, 0, h);
    if (dark || surfaceColor) {
      // palette grounds whenever the caller passes them (light palettes too);
      // the cream stops below are only the no-palette fallback
      const s = surfaceColor || "#171009", sa = surfaceAltColor || "#1e1409";
      g.addColorStop(0, sa); g.addColorStop(0.5, s); g.addColorStop(1, sa);
    } else {
      g.addColorStop(0, "#f4ead0"); g.addColorStop(0.5, "#efe2c2"); g.addColorStop(1, "#e8d8b2");
    }
    ctx.fillStyle = g; ctx.fillRect(0, 0, w, h);
    // vignette
    const v = ctx.createRadialGradient(w/2, h/2, Math.min(w,h)*0.3, w/2, h/2, Math.max(w,h)*0.7);
    v.addColorStop(0, "rgba(0,0,0,0)"); v.addColorStop(1, Col.css(GOLD_D, 0.16));
    ctx.fillStyle = v; ctx.fillRect(0, 0, w, h);
    // foxing speckle
    const r = rng(7);
    for (let i = 0; i < (w*h)/2600; i++) {
      const x = r()*w, y = r()*h, rad = 0.4 + r()*1.4;
      ctx.fillStyle = Col.css(GOLD_D, 0.02 + r()*0.05);
      ctx.beginPath(); ctx.arc(x, y, rad, 0, Math.PI*2); ctx.fill();
    }
  }

  // ── Double gold rule border with corner medallions ──────────
  function paintBorder(ctx, w, h, inset) {
    inset = inset || 10;
    ctx.strokeStyle = GOLD; ctx.lineWidth = 2;
    ctx.strokeRect(inset, inset, w-inset*2, h-inset*2);
    ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.6;
    ctx.strokeRect(inset+3, inset+3, w-inset*2-6, h-inset*2-6);
    [[inset,inset],[w-inset,inset],[inset,h-inset],[w-inset,h-inset]].forEach(([x,y]) => {
      ctx.fillStyle = GOLD_B; ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.8;
      ctx.beginPath(); ctx.arc(x, y, 4.5, 0, Math.PI*2); ctx.fill(); ctx.stroke();
      ctx.fillStyle = SEAL; ctx.beginPath(); ctx.arc(x, y, 1.8, 0, Math.PI*2); ctx.fill();
    });
  }

  // ── Seasonal illuminated header — a distinct little scene per season ──
  // season: 'winter'|'spring'|'summer'|'autumn'. Draws into an (x,y,w,h) band.
  function paintSeasonHeader(ctx, x, y, w, h, season, accent) {
    ctx.save();
    ctx.translate(x, y);
    const cx = w/2;
    const P = ({
      winter: { wash:"rgba(180,214,230,0.20)", stem:"#8fb0bd", stemDk:"#5f818f",
                leaf:"#7f9aa6", petal:"#e6f2f8", petal2:"#c2ddea", core:"#dff0f8", glyph:"flake" },
      spring: { wash:"rgba(228,164,196,0.20)", stem:"#79a85c", stemDk:"#4f7a3a",
                leaf:"#6fae54", petal:"#f2aecb", petal2:"#f8d6e5", core:"#f6d879", glyph:"blossom" },
      summer: { wash:"rgba(232,184,74,0.18)",  stem:"#4f8a3c", stemDk:"#356226",
                leaf:"#4a7a3a", petal:"#f0cd5a", petal2:"#f7e4a0", core:"#e08a2a", glyph:"firefly" },
      autumn: { wash:"rgba(196,106,42,0.20)",  stem:"#9a6a34", stemDk:"#6e4a20",
                leaf:"#b5652a", petal:"#d98a3a", petal2:"#e8b46a", core:"#c0532a", glyph:"leaf" },
    })[season] || { wash:"rgba(228,164,196,0.20)", stem:"#79a85c", stemDk:"#4f7a3a",
                    leaf:"#6fae54", petal:"#f2aecb", petal2:"#f8d6e5", core:"#f6d879", glyph:"blossom" };

    // 1) soft seasonal wash behind the art
    const wash = ctx.createRadialGradient(cx, h*0.5, 2, cx, h*0.5, w*0.5);
    wash.addColorStop(0, P.wash); wash.addColorStop(1, "rgba(0,0,0,0)");
    ctx.fillStyle = wash;
    ctx.beginPath(); ellipse(ctx, cx, h*0.5, w*0.5, h*0.62, 0); ctx.fill();

    // 2) symmetric whiplash stems with tendril curls, leaves and tip motifs
    for (const dir of [-1, 1]) {
      // stem — dark underlay then gold overlay (leaded look)
      for (const [col, lw] of [[P.stemDk, 2.2], [GOLD, 1.0]]) {
        ctx.strokeStyle = col; ctx.lineWidth = lw; ctx.lineCap = "round";
        ctx.beginPath();
        ctx.moveTo(cx, h*0.60);
        ctx.bezierCurveTo(cx + dir*w*0.10, h*0.28, cx + dir*w*0.26, h*0.86, cx + dir*w*0.45, h*0.40);
        ctx.stroke();
      }
      // curl tendril at the tip
      ctx.strokeStyle = GOLD; ctx.lineWidth = 0.9;
      ctx.beginPath(); ctx.arc(cx + dir*w*0.47, h*0.36, h*0.11, 0, Math.PI*1.5, dir < 0);
      ctx.stroke();
      // leaves stepping up the stem
      for (let k = 1; k <= 3; k++) {
        drawSeasonLeaf(ctx, cx + dir*w*0.11*k, h*(0.56 - k*0.10), w*0.032, dir*0.7 - 0.4, P.leaf);
      }
      // tip motif
      seasonMotif(ctx, cx + dir*w*0.43, h*0.40, w*0.044, P, season, false);
    }

    // 3) central crown motif
    seasonMotif(ctx, cx, h*0.44, w*0.058, P, season, true);

    // 4) a hovering creature to the side (butterfly in spring, dragonfly in summer)
    if (season === "spring") drawButterfly(ctx, cx + w*0.34, h*0.26, w*0.028, P.petal);
    else if (season === "summer") paintDragonfly(ctx, cx + w*0.36, h*0.24, w*0.03, 0.4);
    else if (season === "winter") drawStar(ctx, cx + w*0.34, h*0.24, w*0.02);
    else drawAcorn(ctx, cx + w*0.35, h*0.26, w*0.022, P);

    // 5) pond band along the base (subtle)
    paintLilypad(ctx, cx - w*0.31, h*0.90, w*0.032, false);
    paintLilypad(ctx, cx + w*0.29, h*0.92, w*0.026, season === "spring" || season === "summer");

    // 6) drifting seasonal particles (deterministic — no per-frame flicker)
    seasonParticles(ctx, w, h, P, season);

    ctx.restore();
  }

  // pointed leaf with a centre vein
  function drawSeasonLeaf(ctx, x, y, r, rot, col) {
    ctx.save(); ctx.translate(x, y); ctx.rotate(rot);
    ctx.fillStyle = col; ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.5;
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.quadraticCurveTo(r*0.7, -r*0.8, r*2, 0);
    ctx.quadraticCurveTo(r*0.7, r*0.8, 0, 0);
    ctx.closePath(); ctx.fill(); ctx.stroke();
    ctx.strokeStyle = "rgba(255,255,255,0.25)"; ctx.lineWidth = 0.4;
    ctx.beginPath(); ctx.moveTo(r*0.15, 0); ctx.lineTo(r*1.7, 0); ctx.stroke();
    ctx.restore();
  }

  // dispatcher — the right bloom/emblem for the season
  function seasonMotif(ctx, x, y, r, P, season, crown) {
    if (season === "winter") drawSnowflake(ctx, x, y, r*(crown?1.15:0.95), P);
    else if (season === "summer") drawLilySun(ctx, x, y, r*(crown?1.1:0.9), P);
    else if (season === "autumn") drawMapleLeaf(ctx, x, y, r*(crown?1.25:1.0), crown?0:0.35, P);
    else drawBlossom5(ctx, x, y, r*(crown?1.1:0.9), P);
  }

  function drawBlossom5(ctx, x, y, r, P) {
    ctx.save(); ctx.translate(x, y);
    ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.5;
    for (let p = 0; p < 5; p++) {
      ctx.save(); ctx.rotate((p/5)*Math.PI*2);
      const g = ctx.createRadialGradient(0, -r*0.7, 0, 0, -r*0.7, r*0.72);
      g.addColorStop(0, P.petal2); g.addColorStop(1, P.petal);
      ctx.fillStyle = g;
      ctx.beginPath(); ellipse(ctx, 0, -r*0.62, r*0.36, r*0.60, 0); ctx.fill(); ctx.stroke();
      ctx.strokeStyle = "rgba(180,80,120,0.4)"; ctx.lineWidth = 0.4;
      ctx.beginPath(); ctx.moveTo(0, -r*1.18); ctx.lineTo(0, -r*0.95); ctx.stroke();
      ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.5;
      ctx.restore();
    }
    ctx.fillStyle = P.core; ctx.beginPath(); ctx.arc(0, 0, r*0.32, 0, Math.PI*2); ctx.fill();
    ctx.fillStyle = GOLD;
    for (let s = 0; s < 6; s++) { const a = (s/6)*Math.PI*2;
      ctx.beginPath(); ctx.arc(Math.cos(a)*r*0.17, Math.sin(a)*r*0.17, r*0.05, 0, Math.PI*2); ctx.fill(); }
    ctx.restore();
  }

  function drawLilySun(ctx, x, y, r, P) {
    ctx.save(); ctx.translate(x, y);
    ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.5;
    for (let p = 0; p < 12; p++) {
      ctx.save(); ctx.rotate((p/12)*Math.PI*2);
      const g = ctx.createLinearGradient(0, 0, 0, -r*1.15);
      g.addColorStop(0, P.core); g.addColorStop(0.5, P.petal); g.addColorStop(1, P.petal2);
      ctx.fillStyle = g;
      ctx.beginPath(); ellipse(ctx, 0, -r*0.8, r*0.14, r*0.5, 0); ctx.fill(); ctx.stroke();
      ctx.restore();
    }
    const g = ctx.createRadialGradient(-r*0.2, -r*0.2, r*0.05, 0, 0, r*0.6);
    g.addColorStop(0, P.petal2); g.addColorStop(1, P.core);
    ctx.fillStyle = g; ctx.strokeStyle = GOLD; ctx.lineWidth = 0.8;
    ctx.beginPath(); ctx.arc(0, 0, r*0.5, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.fillStyle = "#8a5a1a";
    for (let s = 0; s < 7; s++) { const a = (s/7)*Math.PI*2;
      ctx.beginPath(); ctx.arc(Math.cos(a)*r*0.24, Math.sin(a)*r*0.24, r*0.05, 0, Math.PI*2); ctx.fill(); }
    ctx.restore();
  }

  function drawSnowflake(ctx, x, y, r, P) {
    ctx.save(); ctx.translate(x, y);
    const halo = ctx.createRadialGradient(0, 0, 0, 0, 0, r*1.5);
    halo.addColorStop(0, "rgba(223,240,248,0.65)"); halo.addColorStop(1, "rgba(223,240,248,0)");
    ctx.fillStyle = halo; ctx.beginPath(); ctx.arc(0, 0, r*1.5, 0, Math.PI*2); ctx.fill();
    ctx.strokeStyle = "#eaf6fb"; ctx.lineWidth = 1.1; ctx.lineCap = "round";
    for (let p = 0; p < 6; p++) {
      ctx.save(); ctx.rotate((p/6)*Math.PI*2);
      ctx.beginPath();
      ctx.moveTo(0, 0); ctx.lineTo(0, -r);
      ctx.moveTo(0, -r*0.5); ctx.lineTo(-r*0.26, -r*0.72); ctx.moveTo(0, -r*0.5); ctx.lineTo(r*0.26, -r*0.72);
      ctx.moveTo(0, -r*0.8); ctx.lineTo(-r*0.18, -r*0.95); ctx.moveTo(0, -r*0.8); ctx.lineTo(r*0.18, -r*0.95);
      ctx.stroke(); ctx.restore();
    }
    ctx.fillStyle = "#dff0f8"; ctx.strokeStyle = GOLD; ctx.lineWidth = 0.6;
    ctx.beginPath(); ctx.arc(0, 0, r*0.15, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.restore();
  }

  function drawMapleLeaf(ctx, x, y, r, rot, P) {
    ctx.save(); ctx.translate(x, y); if (rot) ctx.rotate(rot);
    const g = ctx.createLinearGradient(0, -r, 0, r);
    g.addColorStop(0, P.petal2); g.addColorStop(1, P.core);
    ctx.fillStyle = g; ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.5;
    const pts = [[0,-r],[r*0.26,-r*0.34],[r*0.72,-r*0.5],[r*0.42,-r*0.02],[r*0.66,r*0.42],
                 [r*0.2,r*0.24],[0,r*0.82],[-r*0.2,r*0.24],[-r*0.66,r*0.42],[-r*0.42,-r*0.02],
                 [-r*0.72,-r*0.5],[-r*0.26,-r*0.34]];
    ctx.beginPath(); ctx.moveTo(pts[0][0], pts[0][1]);
    for (let i = 1; i < pts.length; i++) ctx.lineTo(pts[i][0], pts[i][1]);
    ctx.closePath(); ctx.fill(); ctx.stroke();
    ctx.strokeStyle = "rgba(110,74,32,0.5)"; ctx.lineWidth = 0.4;
    ctx.beginPath(); ctx.moveTo(0, r*0.8); ctx.lineTo(0, -r*0.6);
    ctx.moveTo(0, -r*0.1); ctx.lineTo(r*0.4, -r*0.32); ctx.moveTo(0, -r*0.1); ctx.lineTo(-r*0.4, -r*0.32);
    ctx.stroke();
    ctx.restore();
  }

  function drawButterfly(ctx, x, y, s, col) {
    ctx.save(); ctx.translate(x, y);
    ctx.fillStyle = col; ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.4;
    for (const sx of [-1, 1]) {
      ctx.beginPath(); ellipse(ctx, sx*s*0.5, -s*0.3, s*0.5, s*0.36, sx*0.5); ctx.fill(); ctx.stroke();
      ctx.beginPath(); ellipse(ctx, sx*s*0.42, s*0.4, s*0.34, s*0.26, -sx*0.5); ctx.fill(); ctx.stroke();
    }
    ctx.strokeStyle = "#5a3e18"; ctx.lineWidth = s*0.12; ctx.lineCap = "round";
    ctx.beginPath(); ctx.moveTo(0, -s*0.55); ctx.lineTo(0, s*0.65); ctx.stroke();
    ctx.lineWidth = 0.5;
    ctx.beginPath();
    ctx.moveTo(0, -s*0.55); ctx.quadraticCurveTo(-s*0.2, -s*0.95, -s*0.36, -s*0.9);
    ctx.moveTo(0, -s*0.55); ctx.quadraticCurveTo(s*0.2, -s*0.95, s*0.36, -s*0.9);
    ctx.stroke();
    ctx.restore();
  }

  function drawStar(ctx, x, y, r) {
    ctx.save(); ctx.translate(x, y);
    const halo = ctx.createRadialGradient(0, 0, 0, 0, 0, r*2);
    halo.addColorStop(0, "rgba(230,244,250,0.6)"); halo.addColorStop(1, "rgba(230,244,250,0)");
    ctx.fillStyle = halo; ctx.beginPath(); ctx.arc(0, 0, r*2, 0, Math.PI*2); ctx.fill();
    ctx.fillStyle = "#eaf6fb"; ctx.strokeStyle = GOLD; ctx.lineWidth = 0.5;
    ctx.beginPath();
    for (let i = 0; i < 8; i++) { const a = (i/8)*Math.PI*2, rr = i%2 ? r*0.4 : r;
      const px = Math.cos(a)*rr, py = Math.sin(a)*rr; i ? ctx.lineTo(px, py) : ctx.moveTo(px, py); }
    ctx.closePath(); ctx.fill(); ctx.stroke();
    ctx.restore();
  }

  function drawAcorn(ctx, x, y, r, P) {
    ctx.save(); ctx.translate(x, y);
    const g = ctx.createLinearGradient(0, -r, 0, r);
    g.addColorStop(0, "#c88a4a"); g.addColorStop(1, "#8a5a24");
    ctx.fillStyle = g; ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.5;
    ctx.beginPath();
    ctx.moveTo(-r*0.7, -r*0.1); ctx.quadraticCurveTo(-r*0.7, r*0.9, 0, r*1.1);
    ctx.quadraticCurveTo(r*0.7, r*0.9, r*0.7, -r*0.1); ctx.closePath(); ctx.fill(); ctx.stroke();
    ctx.fillStyle = "#6e4a20";
    ctx.beginPath();
    ctx.moveTo(-r*0.85, -r*0.1); ctx.quadraticCurveTo(0, -r*0.7, r*0.85, -r*0.1);
    ctx.quadraticCurveTo(0, r*0.15, -r*0.85, -r*0.1); ctx.closePath(); ctx.fill(); ctx.stroke();
    ctx.strokeStyle = "#4a3014"; ctx.lineWidth = 0.9; ctx.lineCap = "round";
    ctx.beginPath(); ctx.moveTo(0, -r*0.5); ctx.lineTo(0, -r*0.95); ctx.stroke();
    ctx.restore();
  }

  // deterministic drifting particles per season
  function seasonParticles(ctx, w, h, P, season) {
    const pts = [[0.12,0.30],[0.30,0.16],[0.60,0.20],[0.80,0.32],[0.90,0.18],
                 [0.20,0.48],[0.72,0.50],[0.48,0.12],[0.38,0.40],[0.66,0.36]];
    ctx.save();
    for (let i = 0; i < pts.length; i++) {
      const px = pts[i][0]*w, py = pts[i][1]*h;
      if (season === "winter") {
        ctx.fillStyle = "rgba(232,246,251,0.85)";
        ctx.beginPath(); ctx.arc(px, py, 1.1, 0, Math.PI*2); ctx.fill();
      } else if (season === "autumn") {
        drawMapleLeaf(ctx, px, py, 2.6, i*0.9, P);
      } else if (season === "spring") {
        ctx.fillStyle = P.petal;
        ctx.beginPath(); ellipse(ctx, px, py, 2.4, 1.2, i*0.7); ctx.fill();
      } else {
        const g = ctx.createRadialGradient(px, py, 0, px, py, 3.2);
        g.addColorStop(0, "rgba(246,227,154,0.9)"); g.addColorStop(1, "rgba(246,227,154,0)");
        ctx.fillStyle = g; ctx.beginPath(); ctx.arc(px, py, 3.2, 0, Math.PI*2); ctx.fill();
        ctx.fillStyle = "#f6e39a"; ctx.beginPath(); ctx.arc(px, py, 0.9, 0, Math.PI*2); ctx.fill();
      }
    }
    ctx.restore();
  }

  function paintBloom(ctx, x, y, r, pal) {
    ctx.save(); ctx.translate(x, y);
    ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.6;
    for (let p = 0; p < 6; p++) {
      ctx.save(); ctx.rotate((p/6)*Math.PI*2);
      ctx.fillStyle = pal.bloom;
      ctx.beginPath(); ellipse(ctx, 0, -r*0.7, r*0.32, r*0.62, 0); ctx.fill(); ctx.stroke();
      ctx.restore();
    }
    ctx.fillStyle = pal.bloom2; ctx.beginPath(); ctx.arc(0, 0, r*0.42, 0, Math.PI*2); ctx.fill();
    ctx.fillStyle = GOLD; ctx.beginPath(); ctx.arc(0, 0, r*0.18, 0, Math.PI*2); ctx.fill();
    ctx.restore();
  }

  // ── Moon-phase glyph (small, for day cells) ─────────────────
  // phase 0..1. Draws a silver disc with the lit fraction.
  function paintMoon(ctx, x, y, r, phase) {
    ctx.save();
    // disc
    ctx.fillStyle = "#cfc8b0"; ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.fill();
    // illuminated part
    let ph = phase % 1; if (ph < 0) ph += 1;
    const illum = (1 - Math.cos(ph*Math.PI*2)) / 2;
    const waxing = ph < 0.5;
    ctx.save();
    ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.clip();
    ctx.fillStyle = "#f6f0dc";
    if (illum > 0.02) {
      const off = (1 - illum) * 2 * r * (waxing ? 1 : -1);
      ctx.beginPath(); ctx.arc(x + off, y, r, 0, Math.PI*2); ctx.fill();
    }
    ctx.restore();
    ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.6; ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.stroke();
    ctx.restore();
  }

  // ── Today gem — glowing faceted jewel ───────────────────────
  function paintGem(ctx, x, y, r, color) {
    ctx.save();
    const halo = ctx.createRadialGradient(x, y, 0, x, y, r*2.4);
    halo.addColorStop(0, color); halo.addColorStop(1, "rgba(0,0,0,0)");
    ctx.globalAlpha = 0.5; ctx.fillStyle = halo;
    ctx.beginPath(); ctx.arc(x, y, r*2.4, 0, Math.PI*2); ctx.fill();
    ctx.globalAlpha = 1;
    // facets
    ctx.fillStyle = color; ctx.strokeStyle = GOLD_B; ctx.lineWidth = 0.8;
    ctx.beginPath();
    ctx.moveTo(x, y-r); ctx.lineTo(x+r, y); ctx.lineTo(x, y+r); ctx.lineTo(x-r, y);
    ctx.closePath(); ctx.fill(); ctx.stroke();
    ctx.fillStyle = "rgba(255,255,255,0.6)";
    ctx.beginPath(); ctx.moveTo(x, y-r); ctx.lineTo(x+r*0.4, y-r*0.1); ctx.lineTo(x, y); ctx.lineTo(x-r*0.4, y-r*0.1);
    ctx.closePath(); ctx.fill();
    ctx.restore();
  }

  // ── Holiday almanac seal — 12-petal gold rosette with a burgundy star center.
  // Ported from the original browser prototype's drawHolidaySeal() (cal-app.js) for the
  // "On this day" card — that card had regressed to the generic paintGem() during the QML
  // port (2026-07-04 fix). Colors are passed in (not hardcoded) so it stays theme-adaptive.
  function paintHolidaySeal(ctx, cx, cy, r, petalColor, petalStroke, centerColor, starColor) {
    r = r || 18;
    ctx.save(); ctx.translate(cx, cy);
    const petalR = r * 0.61; const petalW = r * 0.19; const petalH = r * 0.33;
    ctx.fillStyle = petalColor; ctx.strokeStyle = petalStroke; ctx.lineWidth = 1;
    for (let p = 0; p < 12; p++) {
      ctx.save(); ctx.rotate(p / 12 * Math.PI * 2);
      ctx.beginPath(); ctx.ellipse(0, -petalR, petalW, petalH, 0, 0, Math.PI * 2);
      ctx.fill(); ctx.stroke(); ctx.restore();
    }
    ctx.fillStyle = centerColor;
    ctx.beginPath(); ctx.arc(0, 0, r * 0.39, 0, Math.PI * 2); ctx.fill(); ctx.stroke();
    ctx.fillStyle = starColor; ctx.font = "bold " + Math.round(r * 0.56) + "px 'Cinzel', serif";
    ctx.textAlign = "center"; ctx.textBaseline = "middle";
    ctx.fillText("✦", 0, 0);
    ctx.restore();
  }

  // ── Hand-drawn zodiac glyph (vector, no font) ───────────────
  function paintZodiac(ctx, i, x, y, s, color) {
    ctx.save(); ctx.translate(x, y);
    ctx.strokeStyle = color; ctx.lineWidth = 1.1; ctx.lineCap = "round"; ctx.lineJoin = "round";
    switch (i) {
      case 0: ctx.beginPath(); ctx.moveTo(0,s); ctx.bezierCurveTo(0,-s*0.2,-s,-s*0.2,-s,-s*0.7); ctx.bezierCurveTo(-s,-s*1.1,-s*0.4,-s*1.1,-s*0.4,-s*0.6);
              ctx.moveTo(0,s); ctx.bezierCurveTo(0,-s*0.2,s,-s*0.2,s,-s*0.7); ctx.bezierCurveTo(s,-s*1.1,s*0.4,-s*1.1,s*0.4,-s*0.6); ctx.stroke(); break;
      case 1: ctx.beginPath(); ctx.arc(0,s*0.35,s*0.6,0,Math.PI*2); ctx.stroke(); ctx.beginPath(); ctx.arc(0,-s*0.5,s*0.7,Math.PI*1.05,Math.PI*1.95,false); ctx.stroke(); break;
      case 2: ctx.beginPath(); ctx.moveTo(-s*0.5,-s); ctx.lineTo(-s*0.5,s); ctx.moveTo(s*0.5,-s); ctx.lineTo(s*0.5,s);
              ctx.moveTo(-s*0.8,-s); ctx.lineTo(s*0.8,-s); ctx.moveTo(-s*0.8,s); ctx.lineTo(s*0.8,s); ctx.stroke(); break;
      case 3: ctx.beginPath(); ctx.arc(-s*0.3,-s*0.3,s*0.28,0,Math.PI*2); ctx.stroke(); ctx.beginPath(); ctx.arc(s*0.3,s*0.3,s*0.28,0,Math.PI*2); ctx.stroke();
              ctx.beginPath(); ctx.moveTo(-s*0.55,-s*0.3); ctx.bezierCurveTo(-s,-s*0.3,-s,s*0.6,s*0.05,s*0.55);
              ctx.moveTo(s*0.55,s*0.3); ctx.bezierCurveTo(s,s*0.3,s,-s*0.6,-s*0.05,-s*0.55); ctx.stroke(); break;
      case 4: ctx.beginPath(); ctx.arc(-s*0.35,s*0.35,s*0.32,0,Math.PI*2); ctx.stroke(); ctx.beginPath(); ctx.moveTo(-s*0.05,s*0.5);
              ctx.bezierCurveTo(s*0.4,s*0.5,s*0.4,-s*0.6,0,-s*0.6); ctx.bezierCurveTo(-s*0.5,-s*0.6,-s*0.3,s*0.1,s*0.1,-s*0.05);
              ctx.bezierCurveTo(s*0.5,-s*0.2,s*0.7,s*0.3,s*0.6,s*0.7); ctx.stroke(); break;
      case 5: ctx.beginPath(); ctx.moveTo(-s*0.8,s); ctx.lineTo(-s*0.8,-s*0.6); ctx.bezierCurveTo(-s*0.8,-s,-s*0.3,-s,-s*0.3,-s*0.6); ctx.lineTo(-s*0.3,s*0.4);
              ctx.moveTo(-s*0.3,-s*0.6); ctx.bezierCurveTo(-s*0.3,-s,s*0.2,-s,s*0.2,-s*0.6); ctx.lineTo(s*0.2,s*0.4);
              ctx.moveTo(s*0.2,-s*0.6); ctx.bezierCurveTo(s*0.2,-s,s*0.7,-s,s*0.7,-s*0.5); ctx.bezierCurveTo(s*0.7,s*0.2,s*0.2,s*0.3,s*0.55,s); ctx.stroke(); break;
      case 6: ctx.beginPath(); ctx.moveTo(-s,s*0.55); ctx.lineTo(s,s*0.55); ctx.stroke(); ctx.beginPath(); ctx.moveTo(-s,s*0.1); ctx.lineTo(-s*0.4,s*0.1); ctx.stroke();
              ctx.beginPath(); ctx.arc(0,s*0.1,s*0.42,Math.PI,0,true); ctx.stroke(); ctx.beginPath(); ctx.moveTo(s*0.4,s*0.1); ctx.lineTo(s,s*0.1); ctx.stroke(); break;
      case 7: ctx.beginPath(); ctx.moveTo(-s*0.85,s); ctx.lineTo(-s*0.85,-s*0.6); ctx.bezierCurveTo(-s*0.85,-s,-s*0.4,-s,-s*0.4,-s*0.6); ctx.lineTo(-s*0.4,s*0.4);
              ctx.moveTo(-s*0.4,-s*0.6); ctx.bezierCurveTo(-s*0.4,-s,s*0.05,-s,s*0.05,-s*0.6); ctx.lineTo(s*0.05,s*0.4);
              ctx.moveTo(s*0.05,-s*0.6); ctx.bezierCurveTo(s*0.05,-s,s*0.5,-s,s*0.5,-s*0.6); ctx.lineTo(s*0.5,s*0.6); ctx.lineTo(s,s);
              ctx.moveTo(s,s); ctx.lineTo(s*0.6,s); ctx.moveTo(s,s); ctx.lineTo(s,s*0.55); ctx.stroke(); break;
      case 8: ctx.beginPath(); ctx.moveTo(-s*0.8,s*0.8); ctx.lineTo(s*0.7,-s*0.7); ctx.moveTo(s*0.7,-s*0.7); ctx.lineTo(s*0.15,-s*0.7);
              ctx.moveTo(s*0.7,-s*0.7); ctx.lineTo(s*0.7,-s*0.15); ctx.moveTo(-s*0.15,s*0.05); ctx.lineTo(s*0.2,s*0.45); ctx.stroke(); break;
      case 9: ctx.beginPath(); ctx.moveTo(-s*0.8,-s*0.6); ctx.lineTo(-s*0.2,s*0.5); ctx.lineTo(s*0.1,-s*0.5);
              ctx.bezierCurveTo(s*0.3,-s,s*0.7,-s*0.8,s*0.7,-s*0.2); ctx.bezierCurveTo(s*0.7,s*0.4,s*0.1,s*0.4,s*0.2,-s*0.1); ctx.stroke(); break;
      case 10: for (let wv=0; wv<2; wv++){ const yy=-s*0.25+wv*s*0.55; ctx.beginPath(); ctx.moveTo(-s,yy); ctx.lineTo(-s*0.5,yy-s*0.3); ctx.lineTo(0,yy); ctx.lineTo(s*0.5,yy-s*0.3); ctx.lineTo(s,yy); ctx.stroke(); } break;
      case 11: ctx.beginPath(); ctx.arc(-s*0.7,0,s*0.7,Math.PI*1.5,Math.PI*0.5,true); ctx.stroke(); ctx.beginPath(); ctx.arc(s*0.7,0,s*0.7,Math.PI*0.5,Math.PI*1.5,true); ctx.stroke();
              ctx.beginPath(); ctx.moveTo(-s*0.55,0); ctx.lineTo(s*0.55,0); ctx.stroke(); break;
    }
    ctx.restore();
  }

  // ── Lilypad (with optional bloom + dewdrop) ─────────────────
  function paintLilypad(ctx, x, y, r, withBloom) {
    ctx.save(); ctx.translate(x, y);
    // pad — disc with a wedge notch
    const g = ctx.createRadialGradient(-r*0.3, -r*0.3, r*0.1, 0, 0, r);
    g.addColorStop(0, "#6fae54"); g.addColorStop(0.7, "#4a7a3a"); g.addColorStop(1, "#33561f");
    ctx.fillStyle = g; ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.7;
    ctx.beginPath();
    ctx.arc(0, 0, r, Math.PI*0.28, Math.PI*1.72, false); // notch gap toward upper-right
    ctx.lineTo(0, 0); ctx.closePath(); ctx.fill(); ctx.stroke();
    // radial veins
    ctx.strokeStyle = "rgba(40,70,30,0.5)"; ctx.lineWidth = 0.5;
    for (let i = 0; i < 7; i++) {
      const a = Math.PI*0.3 + (i/7)*Math.PI*1.4;
      ctx.beginPath(); ctx.moveTo(0,0); ctx.lineTo(Math.cos(a)*r*0.92, Math.sin(a)*r*0.92); ctx.stroke();
    }
    // dewdrop
    ctx.fillStyle = "rgba(220,240,255,0.7)";
    ctx.beginPath(); ctx.arc(-r*0.25, r*0.15, r*0.12, 0, Math.PI*2); ctx.fill();
    if (withBloom) {
      ctx.translate(r*0.3, -r*0.35);
      ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.5;
      for (let p = 0; p < 8; p++) { ctx.save(); ctx.rotate((p/8)*Math.PI*2);
        ctx.fillStyle = "#f0c8dc"; ctx.beginPath(); ellipse(ctx, 0, -r*0.28, r*0.10, r*0.26, 0); ctx.fill(); ctx.stroke(); ctx.restore(); }
      ctx.fillStyle = "#f0d27a"; ctx.beginPath(); ctx.arc(0,0,r*0.14,0,Math.PI*2); ctx.fill();
    }
    ctx.restore();
  }

  // ── Frog (sitting, front view) ──────────────────────────────
  function paintFrog(ctx, x, y, s) {
    ctx.save(); ctx.translate(x, y);
    const body = ctx.createRadialGradient(-s*0.2, -s*0.3, s*0.1, 0, 0, s);
    body.addColorStop(0, "#7cc05a"); body.addColorStop(0.7, "#4f8a3c"); body.addColorStop(1, "#356226");
    ctx.strokeStyle = "#2a4a1c"; ctx.lineWidth = 0.8;
    // hind legs
    ctx.fillStyle = "#4f8a3c";
    ctx.beginPath(); ellipse(ctx, -s*0.78, s*0.5, s*0.34, s*0.22, -0.5); ctx.fill(); ctx.stroke();
    ctx.beginPath(); ellipse(ctx,  s*0.78, s*0.5, s*0.34, s*0.22,  0.5); ctx.fill(); ctx.stroke();
    // feet
    ctx.lineWidth = 1.4; ctx.lineCap = "round"; ctx.strokeStyle = "#356226";
    for (const sx of [-1,1]) for (const t of [-0.2,0,0.2]) {
      ctx.beginPath(); ctx.moveTo(sx*s*1.0, s*0.62); ctx.lineTo(sx*s*1.0 + sx*s*0.18, s*0.62 + t*s*0.5 + s*0.18); ctx.stroke();
    }
    // body
    ctx.fillStyle = body; ctx.lineWidth = 0.8; ctx.strokeStyle = "#2a4a1c";
    ctx.beginPath(); ellipse(ctx, 0, s*0.1, s*0.66, s*0.7, 0); ctx.fill(); ctx.stroke();
    // belly
    ctx.fillStyle = "rgba(220,230,170,0.6)"; ctx.beginPath(); ellipse(ctx, 0, s*0.32, s*0.4, s*0.4, 0); ctx.fill();
    // eyes
    for (const sx of [-1,1]) {
      ctx.fillStyle = body; ctx.strokeStyle = "#2a4a1c"; ctx.lineWidth = 0.8;
      ctx.beginPath(); ctx.arc(sx*s*0.42, -s*0.62, s*0.32, 0, Math.PI*2); ctx.fill(); ctx.stroke();
      ctx.fillStyle = "#f0d27a"; ctx.beginPath(); ctx.arc(sx*s*0.42, -s*0.6, s*0.2, 0, Math.PI*2); ctx.fill();
      ctx.fillStyle = "#1a2a10"; ctx.beginPath(); ctx.arc(sx*s*0.42, -s*0.56, s*0.09, 0, Math.PI*2); ctx.fill();
      ctx.fillStyle = "rgba(255,255,255,0.8)"; ctx.beginPath(); ctx.arc(sx*s*0.42-s*0.04, -s*0.62, s*0.03, 0, Math.PI*2); ctx.fill();
    }
    // smile
    ctx.strokeStyle = "#2a4a1c"; ctx.lineWidth = 1; ctx.lineCap = "round";
    ctx.beginPath(); ctx.arc(0, s*0.02, s*0.42, Math.PI*0.12, Math.PI*0.88); ctx.stroke();
    // nostrils
    ctx.fillStyle = "#2a4a1c"; ctx.beginPath(); ctx.arc(-s*0.12,-s*0.18,s*0.04,0,6.3); ctx.arc(s*0.12,-s*0.18,s*0.04,0,6.3); ctx.fill();
    ctx.restore();
  }

  // ── Dragonfly ───────────────────────────────────────────────
  function paintDragonfly(ctx, x, y, s, rot) {
    ctx.save(); ctx.translate(x, y); if (rot) ctx.rotate(rot);
    // wings
    ctx.fillStyle = "rgba(180,210,230,0.45)"; ctx.strokeStyle = "rgba(110,79,23,0.5)"; ctx.lineWidth = 0.4;
    for (const sx of [-1,1]) for (const sy of [-1,1]) {
      ctx.beginPath(); ellipse(ctx, sx*s*0.5, sy*s*0.22, s*0.5, s*0.16, sx*sy*0.5); ctx.fill(); ctx.stroke();
    }
    // body
    ctx.strokeStyle = "#3a6a8a"; ctx.lineWidth = s*0.16; ctx.lineCap = "round";
    ctx.beginPath(); ctx.moveTo(0,-s*0.1); ctx.lineTo(0, s*0.9); ctx.stroke();
    ctx.fillStyle = "#5b9bd5"; ctx.beginPath(); ctx.arc(0, -s*0.18, s*0.14, 0, Math.PI*2); ctx.fill();
    ctx.restore();
  }

  // ── Cattail (reed) ──────────────────────────────────────────
  function paintCattail(ctx, x, y, h) {
    ctx.save(); ctx.translate(x, y);
    ctx.strokeStyle = "#5a7a3a"; ctx.lineWidth = 1.4; ctx.lineCap = "round";
    ctx.beginPath(); ctx.moveTo(0, 0); ctx.lineTo(0, -h); ctx.stroke();
    // blade leaf
    ctx.strokeStyle = "#4a6a3a"; ctx.lineWidth = 1;
    ctx.beginPath(); ctx.moveTo(0, -h*0.3); ctx.quadraticCurveTo(-h*0.3, -h*0.7, -h*0.1, -h*1.05); ctx.stroke();
    // cattail head
    const g = ctx.createLinearGradient(0,-h,0,-h*0.55); g.addColorStop(0,"#7a5a2a"); g.addColorStop(1,"#5a3e18");
    ctx.fillStyle = g; ctx.strokeStyle = GOLD_D; ctx.lineWidth = 0.5;
    ctx.beginPath(); ellipse(ctx, 0, -h*0.78, h*0.09, h*0.22, 0); ctx.fill(); ctx.stroke();
    ctx.restore();
  }

  // ── Frog-on-lilypad masthead emblem ─────────────────────────
  // Bakes its own soft drop-shadow (CSS: filter:drop-shadow(0 2px 3px rgba(40,60,20,.3)))
  // so no MultiEffect/layer.effect is needed on the Canvas that calls this (2026-07-04 fidelity).
  function paintEmblem(ctx, cx, cy, s) {
    ctx.save();
    ctx.fillStyle = "rgba(40,60,20,0.3)";
    ctx.beginPath(); ellipse(ctx, cx, cy + s*0.9, s*1.1, s*0.32, 0); ctx.fill();
    ctx.restore();
    // pond ripple
    ctx.strokeStyle = "rgba(90,140,170,0.4)"; ctx.lineWidth = 0.8;
    ctx.beginPath(); ellipse(ctx, cx, cy+s*0.7, s*1.25, s*0.4, 0); ctx.stroke();
    paintLilypad(ctx, cx, cy+s*0.55, s*0.95, true);
    paintFrog(ctx, cx, cy-s*0.15, s*0.5);
  }

  // ── Glow dot — solid center + soft radial halo, replaces CSS `box-shadow: 0 0 Npx color`
  // glow on small dots (rail .tg, agenda .cal-ag-gem, cmd .cmd-gem, now-line dot). One helper
  // for all of them (2026-07-04 fidelity doc §"What must move INTO cal-art.js").
  function paintGlowDot(ctx, x, y, r, color, haloR) {
    haloR = haloR || r * 2.6;
    ctx.save();
    const halo = ctx.createRadialGradient(x, y, 0, x, y, haloR);
    halo.addColorStop(0, color); halo.addColorStop(1, "rgba(0,0,0,0)");
    ctx.globalAlpha = 0.55; ctx.fillStyle = halo;
    ctx.beginPath(); ctx.arc(x, y, haloR, 0, Math.PI*2); ctx.fill();
    ctx.globalAlpha = 1; ctx.fillStyle = color;
    ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.fill();
    ctx.restore();
  }

  // ── Dashed frame — CSS `.cal-time-block.ghost{border:1.5px dashed var(--gold)}`. QML
  // Rectangle can't dash a border, so draw it here (2026-07-04 fidelity doc).
  function paintDashedFrame(ctx, w, h, color, dash, gap, lw) {
    dash = dash || 5; gap = gap || 4; lw = lw || 1.5;
    ctx.save();
    ctx.strokeStyle = color; ctx.lineWidth = lw;
    if (ctx.setLineDash) ctx.setLineDash([dash, gap]);
    ctx.strokeRect(lw/2, lw/2, w-lw, h-lw);
    if (ctx.setLineDash) ctx.setLineDash([]);
    ctx.restore();
  }

  // ── Inset panel — CSS `box-shadow: inset 0 0 0 1px color` (the active-tab inset ring /
  // modal double-frame). Optional Canvas alternative to the double-Rectangle trick, for
  // callers that would rather paint it once than nest a second Rectangle.
  function paintInsetPanel(ctx, w, h, radius, color, lw) {
    lw = lw || 1;
    ctx.save();
    ctx.strokeStyle = color; ctx.lineWidth = lw;
    var r = radius || 0, x = lw/2, y = lw/2, ww = w-lw, hh = h-lw;
    ctx.beginPath();
    ctx.moveTo(x+r, y);
    ctx.lineTo(x+ww-r, y); ctx.arcTo(x+ww, y, x+ww, y+r, r);
    ctx.lineTo(x+ww, y+hh-r); ctx.arcTo(x+ww, y+hh, x+ww-r, y+hh, r);
    ctx.lineTo(x+r, y+hh); ctx.arcTo(x, y+hh, x, y+hh-r, r);
    ctx.lineTo(x, y+r); ctx.arcTo(x, y, x+r, y, r);
    ctx.closePath(); ctx.stroke();
    ctx.restore();
  }

  const api = { paintPage, paintBorder, paintSeasonHeader, paintMoon, paintGem, paintHolidaySeal, paintZodiac, ellipse,
           paintLilypad, paintFrog, paintDragonfly, paintCattail, paintEmblem, paintGlowDot, paintDashedFrame,
           paintInsetPanel };
  // every public painter reads the live palette first
  Object.keys(api).forEach(n => {
    if (n === "ellipse") return;
    const f = api[n];
    api[n] = function() { _sync(); return f.apply(null, arguments); };
  });
  return api;
})();
