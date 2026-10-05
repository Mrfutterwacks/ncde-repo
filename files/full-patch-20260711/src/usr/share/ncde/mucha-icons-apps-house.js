// mucha-icons-apps-house.js — NCDE's own house apps, as kith emblems.
//
// 2026-09-24 (operator): the house apps fell through to drawDefault()'s letter
// monograms. Inspiration is Changeling: The Dreaming — each app wears the kith
// whose nature matches its job (original emblems in the spirit of each kith,
// drawn Mucha-style on the shared Iris-tinted medallion):
//   NCDE Command  — Sidhe   (rule; the court's crown)
//   Orchidée      — Boggan  (keepers of the household; hearth-door + orchid)
//   Hummingbird   — Eshu    (wandering messengers; bird, sealed letter, road-star)
//   Magpie Talker — Pooka   (talkative shapeshifters; magpie with hare's ears)
//   Binnie        — Redcap  (devours anything; a bin with a red cap and a grin)
.pragma library
.import "mucha-icons-core.js" as C

function _gold(accent) { return accent || C.PALETTE.gold; }

// Rotated ellipse path. Qt's Context2D ellipse() takes a bounding box, not the
// browser's (cx, cy, rx, ry, rotation) form, so build it from arc + transform.
function _ell(ctx, cx, cy, rx, ry, rot) {
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(rot);
    ctx.scale(rx, ry);
    ctx.arc(0, 0, 1, 0, Math.PI * 2);
    ctx.restore();
}

// four-point glamour sparkle
function _glint(ctx, x, y, r, color) {
    ctx.save();
    ctx.fillStyle = color;
    ctx.beginPath();
    ctx.moveTo(x, y - r);
    ctx.quadraticCurveTo(x, y, x + r, y);
    ctx.quadraticCurveTo(x, y, x, y + r);
    ctx.quadraticCurveTo(x, y, x - r, y);
    ctx.quadraticCurveTo(x, y, x, y - r);
    ctx.fill();
    ctx.restore();
}

// SIDHE — NCDE Command. A five-tined court crown, jewelled, thorn-wreathed.
function drawKithSidhe(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var g = _gold(accent);
    // soft court radiance behind the crown
    ctx.fillStyle = C.radial(ctx, s * 0.5, s * 0.42, 0, s * 0.30,
        [[0, "rgba(255,235,180,0.35)"], [1, "rgba(255,235,180,0)"]]);
    ctx.fillRect(0, 0, s, s);
    ctx.save();
    // crown body: tines rising from the circlet
    var base = s * 0.62, left = s * 0.27, right = s * 0.73;
    var tips = [[0.27, 0.40], [0.385, 0.33], [0.5, 0.25], [0.615, 0.33], [0.73, 0.40]];
    ctx.beginPath();
    ctx.moveTo(left, base);
    ctx.lineTo(left, s * tips[0][1]);
    for (var i = 1; i < tips.length; i++) {
        var px = s * tips[i - 1][0], nx = s * tips[i][0];
        ctx.quadraticCurveTo((px + nx) / 2, s * 0.50, nx, s * tips[i][1]);
    }
    ctx.lineTo(right, base);
    ctx.closePath();
    ctx.fillStyle = C.radial(ctx, s * 0.45, s * 0.36, 0, s * 0.36,
        [[0, C.PALETTE.goldHi], [0.6, g], [1, C.PALETTE.goldDark]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // circlet band
    ctx.fillStyle = C.PALETTE.goldDark;
    ctx.fillRect(left - s * 0.01, base - s * 0.02, right - left + s * 0.02, s * 0.07);
    ctx.strokeRect(left - s * 0.01, base - s * 0.02, right - left + s * 0.02, s * 0.07);
    // band gems
    var gems = [C.PALETTE.roseDeep, C.PALETTE.teal, C.PALETTE.roseDeep];
    for (var j = 0; j < 3; j++) {
        ctx.fillStyle = gems[j];
        ctx.beginPath(); ctx.arc(s * (0.36 + j * 0.14), base + s * 0.015, s * 0.018, 0, Math.PI * 2); ctx.fill();
    }
    // tine pearls, a star on the tallest
    for (var k = 0; k < tips.length; k++) {
        if (k === 2) continue;
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.beginPath(); ctx.arc(s * tips[k][0], s * tips[k][1] - s * 0.012, s * 0.016, 0, Math.PI * 2); ctx.fill();
    }
    _glint(ctx, s * 0.5, s * 0.21, s * 0.055, C.PALETTE.bgCreamHi);
    ctx.restore();
    // thorned briar beneath the crown
    C.setStroke(ctx, C.PALETTE.sageDeep, s * 0.014);
    ctx.beginPath();
    ctx.moveTo(s * 0.24, s * 0.74);
    ctx.bezierCurveTo(s * 0.38, s * 0.68, s * 0.62, s * 0.80, s * 0.76, s * 0.72);
    ctx.stroke();
    ctx.fillStyle = C.PALETTE.sageDeep;
    [[0.33, 0.71, -1], [0.47, 0.74, 1], [0.60, 0.75, -1], [0.70, 0.73, 1]].forEach(function (t) {
        ctx.beginPath();
        ctx.moveTo(s * t[0] - s * 0.012, s * t[1]);
        ctx.lineTo(s * t[0], s * (t[1] + t[2] * 0.035));
        ctx.lineTo(s * t[0] + s * 0.012, s * t[1]);
        ctx.fill();
    });
    C.drawRosette(ctx, s * 0.24, s * 0.74, s * 0.035, 5, C.PALETTE.rose, g);
}

// BOGGAN — Orchidée. The household's arched hearth-door, an orchid over the lintel.
function drawKithBoggan(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var g = _gold(accent);
    ctx.save();
    // arched door
    var dl = s * 0.34, dr = s * 0.66, top = s * 0.40, bot = s * 0.76;
    ctx.beginPath();
    ctx.moveTo(dl, bot);
    ctx.lineTo(dl, top + s * 0.06);
    ctx.arc(s * 0.5, top + s * 0.06, (dr - dl) / 2, Math.PI, 0);
    ctx.lineTo(dr, bot);
    ctx.closePath();
    ctx.fillStyle = C.gradient(ctx, 0, top, 0, bot, [[0, "#9a6a3a"], [1, "#5e3a1c"]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // planks
    C.setStroke(ctx, "rgba(20,10,4,0.55)", s * 0.008);
    for (var i = 1; i < 3; i++) {
        var x = dl + (dr - dl) * i / 3;
        ctx.beginPath(); ctx.moveTo(x, top + s * 0.02); ctx.lineTo(x, bot); ctx.stroke();
    }
    // iron strap + ring pull in gilt
    C.setStroke(ctx, g, s * 0.016);
    ctx.beginPath(); ctx.moveTo(dl, s * 0.64); ctx.lineTo(dr, s * 0.64); ctx.stroke();
    ctx.beginPath(); ctx.arc(s * 0.59, s * 0.57, s * 0.025, 0, Math.PI * 2); ctx.stroke();
    // warm hearth glow under the door
    ctx.fillStyle = "rgba(255,196,110,0.75)";
    ctx.fillRect(dl + s * 0.01, bot - s * 0.018, dr - dl - s * 0.02, s * 0.014);
    // doorstep
    ctx.fillStyle = C.PALETTE.bgPaper;
    ctx.fillRect(s * 0.30, bot, s * 0.40, s * 0.035);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.30, bot, s * 0.40, s * 0.035);
    ctx.restore();
    // orchid over the lintel: five petals + lip
    var ox = s * 0.5, oy = s * 0.30;
    ctx.save();
    ctx.translate(ox, oy);
    var petal = C.PALETTE.rose, petalDk = C.PALETTE.plum;
    for (var p = 0; p < 5; p++) {
        ctx.save();
        ctx.rotate(-Math.PI / 2 + p * (Math.PI * 2 / 5));
        ctx.beginPath();
        _ell(ctx, s * 0.07, 0, s * 0.07, s * 0.032, 0);
        ctx.fillStyle = C.radial(ctx, s * 0.03, 0, 0, s * 0.12, [[0, C.PALETTE.bgCreamHi], [0.5, petal], [1, petalDk]]);
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.plumDeep, s * 0.006);
        ctx.stroke();
        ctx.restore();
    }
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.beginPath(); ctx.arc(0, s * 0.012, s * 0.028, 0, Math.PI * 2); ctx.fill();
    ctx.fillStyle = g;
    ctx.beginPath(); ctx.arc(0, 0, s * 0.012, 0, Math.PI * 2); ctx.fill();
    ctx.restore();
    // trailing leaves down the jambs
    C.leafBead(ctx, s * 0.30, s * 0.46, s * 0.09, 1.9, C.PALETTE.sageDeep);
    C.leafBead(ctx, s * 0.70, s * 0.46, s * 0.09, 1.2, C.PALETTE.sageDeep);
    _glint(ctx, s * 0.66, s * 0.22, s * 0.028, C.PALETTE.bgCreamHi);
}

// ESHU — Hummingbird Courier. Road-star behind, hummingbird bearing a sealed letter.
function drawKithEshu(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var g = _gold(accent);
    // eight-point road-star (the wanderer's compass)
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.fillStyle = "rgba(255,235,180,0.20)";
    ctx.beginPath();
    for (var i = 0; i < 16; i++) {
        var r = (i % 2 === 0) ? (i % 4 === 0 ? s * 0.33 : s * 0.22) : s * 0.07;
        var a = i * Math.PI / 8 - Math.PI / 2;
        if (i === 0) ctx.moveTo(Math.cos(a) * r, Math.sin(a) * r); else ctx.lineTo(Math.cos(a) * r, Math.sin(a) * r);
    }
    ctx.closePath();
    ctx.fill();
    ctx.restore();
    // letter
    ctx.save();
    ctx.translate(s * 0.40, s * 0.64);
    ctx.rotate(-0.18);
    var lw = s * 0.28, lh = s * 0.18;
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(-lw / 2, -lh / 2, lw, lh);
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.010);
    ctx.strokeRect(-lw / 2, -lh / 2, lw, lh);
    ctx.beginPath(); ctx.moveTo(-lw / 2, -lh / 2); ctx.lineTo(0, s * 0.015); ctx.lineTo(lw / 2, -lh / 2); ctx.stroke();
    // rose wax seal
    ctx.fillStyle = C.PALETTE.roseDeep;
    ctx.beginPath(); ctx.arc(0, s * 0.015, s * 0.032, 0, Math.PI * 2); ctx.fill();
    C.drawRosette(ctx, 0, s * 0.015, s * 0.018, 5, C.PALETTE.terraDark, null);
    ctx.restore();
    // hummingbird, diving toward the letter
    ctx.save();
    // larger, and facing down-left so the beak meets the seal
    ctx.translate(s * 0.62, s * 0.34);
    ctx.scale(-1.45, 1.45);
    ctx.rotate(0.5);
    // tail
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath(); ctx.moveTo(-s * 0.10, s * 0.0); ctx.lineTo(-s * 0.19, -s * 0.03); ctx.lineTo(-s * 0.17, s * 0.04); ctx.closePath(); ctx.fill();
    // body
    ctx.fillStyle = C.radial(ctx, 0, -s * 0.01, 0, s * 0.12, [[0, "#9fd3b8"], [0.6, C.PALETTE.teal], [1, C.PALETTE.tealDeep]]);
    ctx.beginPath();
    ctx.moveTo(-s * 0.11, 0);
    ctx.bezierCurveTo(-s * 0.06, -s * 0.07, s * 0.06, -s * 0.06, s * 0.08, -s * 0.01);
    ctx.bezierCurveTo(s * 0.05, s * 0.05, -s * 0.06, s * 0.05, -s * 0.11, 0);
    ctx.fill();
    // ruby throat (glamour)
    ctx.fillStyle = C.PALETTE.roseDeep;
    ctx.beginPath(); ctx.arc(s * 0.05, s * 0.01, s * 0.022, 0, Math.PI * 2); ctx.fill();
    // needle beak toward the seal
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.beginPath(); ctx.moveTo(s * 0.08, -s * 0.01); ctx.lineTo(s * 0.20, s * 0.03); ctx.stroke();
    // eye
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath(); ctx.arc(s * 0.055, -s * 0.025, s * 0.010, 0, Math.PI * 2); ctx.fill();
    // blurred wings
    ctx.fillStyle = "rgba(238,244,248,0.70)";
    ctx.beginPath(); _ell(ctx, -s * 0.02, -s * 0.08, s * 0.09, s * 0.03, -0.9); ctx.fill();
    ctx.fillStyle = "rgba(238,244,248,0.40)";
    ctx.beginPath(); _ell(ctx, -s * 0.05, -s * 0.07, s * 0.09, s * 0.03, -0.5); ctx.fill();
    ctx.restore();
    _glint(ctx, s * 0.30, s * 0.30, s * 0.030, g);
    _glint(ctx, s * 0.74, s * 0.66, s * 0.024, C.PALETTE.bgCreamHi);
}

// POOKA — Magpie Talker. A magpie with the pooka's hare ears, a speech banderole, crescent moon.
function drawKithPooka(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var g = _gold(accent);
    // crescent moon
    ctx.save();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath(); ctx.arc(s * 0.66, s * 0.30, s * 0.075, 0, Math.PI * 2); ctx.fill();
    ctx.globalCompositeOperation = "destination-out";
    ctx.beginPath(); ctx.arc(s * 0.695, s * 0.285, s * 0.065, 0, Math.PI * 2); ctx.fill();
    ctx.restore();
    // speech banderole (curling ribbon) along the bottom
    ctx.save();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.70);
    ctx.bezierCurveTo(s * 0.38, s * 0.64, s * 0.58, s * 0.76, s * 0.78, s * 0.68);
    ctx.lineTo(s * 0.78, s * 0.76);
    ctx.bezierCurveTo(s * 0.58, s * 0.84, s * 0.38, s * 0.72, s * 0.22, s * 0.78);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.010);
    ctx.stroke();
    // "words" on the ribbon
    ctx.fillStyle = g;
    for (var i = 0; i < 4; i++) ctx.fillRect(s * (0.30 + i * 0.11), s * (0.725 + (i % 2) * 0.006), s * 0.07, s * 0.012);
    ctx.restore();
    // magpie
    ctx.save();
    ctx.translate(s * 0.44, s * 0.46);
    // long tail sweeping down-left (iridescent)
    ctx.fillStyle = C.gradient(ctx, -s * 0.24, s * 0.16, 0, 0, [[0, "#2f5f7a"], [1, C.PALETTE.indigoDeep]]);
    ctx.beginPath(); ctx.moveTo(-s * 0.06, s * 0.06); ctx.lineTo(-s * 0.25, s * 0.19); ctx.lineTo(-s * 0.21, s * 0.21); ctx.lineTo(-s * 0.02, s * 0.10); ctx.closePath(); ctx.fill();
    // hare ears (the pooka's other shape), behind the head
    ctx.fillStyle = C.PALETTE.inkSoft;
    ctx.beginPath(); _ell(ctx, s * 0.06, -s * 0.17, s * 0.022, s * 0.07, -0.25); ctx.fill();
    ctx.beginPath(); _ell(ctx, s * 0.11, -s * 0.16, s * 0.020, s * 0.065, 0.25); ctx.fill();
    ctx.fillStyle = C.PALETTE.rose;
    ctx.beginPath(); _ell(ctx, s * 0.06, -s * 0.17, s * 0.009, s * 0.045, -0.25); ctx.fill();
    // black body + head
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.moveTo(-s * 0.08, s * 0.08);
    ctx.bezierCurveTo(-s * 0.10, -s * 0.04, s * 0.02, -s * 0.12, s * 0.10, -s * 0.10);
    ctx.bezierCurveTo(s * 0.16, -s * 0.08, s * 0.14, s * 0.02, s * 0.06, s * 0.08);
    ctx.closePath();
    ctx.fill();
    // white belly + shoulder patch
    ctx.fillStyle = C.PALETTE.glassWhite;
    ctx.beginPath(); _ell(ctx, s * 0.03, s * 0.035, s * 0.06, s * 0.035, -0.4); ctx.fill();
    ctx.beginPath(); _ell(ctx, -s * 0.03, -s * 0.02, s * 0.04, s * 0.018, -0.6); ctx.fill();
    // teal wing sheen
    C.setStroke(ctx, "#4fa3b8", s * 0.012);
    ctx.beginPath(); ctx.moveTo(-s * 0.07, s * 0.03); ctx.quadraticCurveTo(-s * 0.02, -s * 0.05, s * 0.04, -s * 0.05); ctx.stroke();
    // beak, open mid-chatter
    ctx.fillStyle = C.PALETTE.inkSoft;
    ctx.beginPath(); ctx.moveTo(s * 0.14, -s * 0.10); ctx.lineTo(s * 0.21, -s * 0.11); ctx.lineTo(s * 0.145, -s * 0.085); ctx.closePath(); ctx.fill();
    ctx.beginPath(); ctx.moveTo(s * 0.14, -s * 0.08); ctx.lineTo(s * 0.20, -s * 0.065); ctx.lineTo(s * 0.14, -s * 0.07); ctx.closePath(); ctx.fill();
    // bright eye
    ctx.fillStyle = g;
    ctx.beginPath(); ctx.arc(s * 0.105, -s * 0.095, s * 0.013, 0, Math.PI * 2); ctx.fill();
    ctx.restore();
    _glint(ctx, s * 0.30, s * 0.28, s * 0.028, C.PALETTE.bgCreamHi);
}

// REDCAP — Binnie. A wicker bin in a tall red cap, grinning with too many teeth.
function drawKithRedcap(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var g = _gold(accent);
    ctx.save();
    // bin body (tapered wicker)
    var tl = s * 0.30, tr = s * 0.70, bl = s * 0.35, br = s * 0.65, top = s * 0.46, bot = s * 0.78;
    ctx.beginPath();
    ctx.moveTo(tl, top); ctx.lineTo(tr, top); ctx.lineTo(br, bot); ctx.lineTo(bl, bot); ctx.closePath();
    ctx.fillStyle = C.gradient(ctx, tl, 0, tr, 0, [[0, "#8a6232"], [0.5, "#c19050"], [1, "#7a5228"]]);
    ctx.fill();
    ctx.save();
    ctx.clip();
    C.setStroke(ctx, "rgba(60,36,14,0.55)", s * 0.008);
    for (var r = 0; r < 5; r++) {           // weave rows
        var y = top + (bot - top) * (r + 0.5) / 5;
        ctx.beginPath(); ctx.moveTo(tl - s * 0.02, y); ctx.lineTo(tr + s * 0.02, y); ctx.stroke();
    }
    for (var c = 0; c < 7; c++) {           // weave uprights
        var t = (c + 0.5) / 7;
        ctx.beginPath(); ctx.moveTo(tl + (tr - tl) * t, top); ctx.lineTo(bl + (br - bl) * t, bot); ctx.stroke();
    }
    ctx.restore();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // rim
    ctx.fillStyle = "#6a4420";
    ctx.fillRect(tl - s * 0.02, top - s * 0.025, tr - tl + s * 0.04, s * 0.04);
    ctx.strokeRect(tl - s * 0.02, top - s * 0.025, tr - tl + s * 0.04, s * 0.04);
    // grin: dark mouth with a row of sharp teeth
    ctx.fillStyle = "#1a0a06";
    ctx.beginPath();
    ctx.moveTo(s * 0.38, s * 0.60);
    ctx.quadraticCurveTo(s * 0.50, s * 0.71, s * 0.62, s * 0.60);
    ctx.quadraticCurveTo(s * 0.50, s * 0.64, s * 0.38, s * 0.60);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    for (var k = 0; k < 6; k++) {
        var tx = s * (0.405 + k * 0.038);
        ctx.beginPath(); ctx.moveTo(tx, s * 0.612); ctx.lineTo(tx + s * 0.019, s * 0.612); ctx.lineTo(tx + s * 0.0095, s * 0.640); ctx.closePath(); ctx.fill();
    }
    // glinting eyes
    ctx.fillStyle = g;
    ctx.beginPath(); ctx.arc(s * 0.43, s * 0.53, s * 0.018, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.57, s * 0.53, s * 0.018, 0, Math.PI * 2); ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(s * 0.427, s * 0.515, s * 0.006, s * 0.03);
    ctx.fillRect(s * 0.567, s * 0.515, s * 0.006, s * 0.03);
    // the red cap, flopping to one side
    ctx.beginPath();
    ctx.moveTo(s * 0.32, top - s * 0.02);
    ctx.bezierCurveTo(s * 0.36, s * 0.26, s * 0.58, s * 0.18, s * 0.72, s * 0.26);
    ctx.bezierCurveTo(s * 0.64, s * 0.30, s * 0.66, s * 0.38, s * 0.68, top - s * 0.02);
    ctx.closePath();
    ctx.fillStyle = C.radial(ctx, s * 0.46, s * 0.32, 0, s * 0.22, [[0, "#d8483a"], [0.7, "#a82020"], [1, "#6a1010"]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // cap tassel bell
    ctx.fillStyle = g;
    ctx.beginPath(); ctx.arc(s * 0.735, s * 0.265, s * 0.022, 0, Math.PI * 2); ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.006);
    ctx.stroke();
    ctx.restore();
}

function drawKithNocker(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var g = _gold(accent), cx = s * 0.5, cy = s * 0.51;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = C.gradient(ctx, -s * 0.28, -s * 0.28, s * 0.28, s * 0.28,
        [[0, C.PALETTE.goldHi], [0.55, g], [1, C.PALETTE.goldDark]]);
    ctx.beginPath();
    for (var i = 0; i < 24; i++) {
        var a = i * Math.PI / 12 - Math.PI / 2;
        var r = i % 2 === 0 ? s * 0.30 : s * 0.245;
        var px = Math.cos(a) * r, py = Math.sin(a) * r;
        if (i === 0) ctx.moveTo(px, py); else ctx.lineTo(px, py);
    }
    ctx.closePath(); ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014); ctx.stroke();
    ctx.fillStyle = C.PALETTE.bgCream;
    ctx.beginPath(); ctx.arc(0, 0, s * 0.22, 0, Math.PI * 2); ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.beginPath(); ctx.arc(0, 0, s * 0.20, 0, Math.PI * 2); ctx.stroke();
    ctx.restore();

    var left = s * 0.29, right = s * 0.71, top = s * 0.34, bottom = s * 0.64;
    ctx.fillStyle = C.gradient(ctx, left, top, right, bottom,
        [[0, C.PALETTE.indigoDeep], [0.55, C.PALETTE.tealDeep], [1, C.PALETTE.indigoDeep]]);
    ctx.beginPath();
    ctx.moveTo(left, bottom); ctx.lineTo(left, top + s * 0.04);
    ctx.quadraticCurveTo(cx, top - s * 0.01, right, top + s * 0.04);
    ctx.lineTo(right, bottom); ctx.closePath(); ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012); ctx.stroke();
    ctx.fillStyle = g; ctx.fillRect(left, top + s * 0.08, right - left, s * 0.035);
    C.setStroke(ctx, C.PALETTE.bgCreamHi, s * 0.022);
    ctx.beginPath(); ctx.moveTo(s * 0.37, s * 0.49); ctx.lineTo(s * 0.45, s * 0.55);
    ctx.lineTo(s * 0.37, s * 0.60); ctx.moveTo(s * 0.49, s * 0.60); ctx.lineTo(s * 0.61, s * 0.60); ctx.stroke();
    C.setStroke(ctx, C.PALETTE.terraDark, s * 0.026);
    ctx.beginPath(); ctx.moveTo(s * 0.24, s * 0.72); ctx.lineTo(s * 0.39, s * 0.66);
    ctx.lineTo(s * 0.45, s * 0.70); ctx.moveTo(s * 0.76, s * 0.72); ctx.lineTo(s * 0.61, s * 0.66);
    ctx.lineTo(s * 0.55, s * 0.70); ctx.stroke();
    _glint(ctx, s * 0.68, s * 0.28, s * 0.028, C.PALETTE.bgCreamHi);
}

function drawKithSatyr(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var g = _gold(accent), cx = s * 0.5;
    ctx.save();
    C.setStroke(ctx, C.PALETTE.sageDeep, s * 0.035);
    ctx.beginPath(); ctx.moveTo(s * 0.33, s * 0.43);
    ctx.bezierCurveTo(s * 0.20, s * 0.30, s * 0.25, s * 0.19, s * 0.38, s * 0.27);
    ctx.moveTo(s * 0.67, s * 0.43);
    ctx.bezierCurveTo(s * 0.80, s * 0.30, s * 0.75, s * 0.19, s * 0.62, s * 0.27);
    ctx.stroke();
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath(); ctx.arc(cx, s * 0.34, s * 0.11, Math.PI, 0); ctx.lineTo(s * 0.60, s * 0.48);
    ctx.quadraticCurveTo(cx, s * 0.53, s * 0.40, s * 0.48); ctx.closePath(); ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012); ctx.stroke();

    C.setStroke(ctx, g, s * 0.035);
    ctx.beginPath();
    ctx.moveTo(s * 0.36, s * 0.43);
    ctx.bezierCurveTo(s * 0.27, s * 0.55, s * 0.34, s * 0.72, s * 0.50, s * 0.76);
    ctx.bezierCurveTo(s * 0.66, s * 0.72, s * 0.73, s * 0.55, s * 0.64, s * 0.43);
    ctx.moveTo(s * 0.36, s * 0.43); ctx.lineTo(s * 0.64, s * 0.43); ctx.stroke();
    C.setStroke(ctx, C.PALETTE.plumDeep, s * 0.010);
    for (var i = 0; i < 5; i++) {
        var x = s * (0.39 + i * 0.055);
        ctx.beginPath(); ctx.moveTo(x, s * 0.46); ctx.lineTo(x, s * 0.72); ctx.stroke();
    }
    C.setStroke(ctx, C.PALETTE.roseDeep, s * 0.018);
    ctx.beginPath(); ctx.moveTo(s * 0.33, s * 0.62); ctx.quadraticCurveTo(s * 0.5, s * 0.56, s * 0.67, s * 0.62); ctx.stroke();
    [0.30, 0.70].forEach(function(x, i) {
        C.leafBead(ctx, s * x, s * 0.57, s * 0.10, i ? -0.8 : 0.8, C.PALETTE.sageDeep);
        C.drawRosette(ctx, s * x, s * 0.57, s * 0.026, 5, C.PALETTE.rose, g);
    });
    ctx.restore();
    _glint(ctx, s * 0.50, s * 0.80, s * 0.03, C.PALETTE.bgCreamHi);
}

function drawKithTroll(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var g = _gold(accent);
    ctx.save();
    ctx.fillStyle = C.radial(ctx, s * 0.50, s * 0.52, 0, s * 0.38,
        [[0, C.PALETTE.sageMist], [0.65, C.PALETTE.sageDeep], [1, C.PALETTE.indigoDeep]]);
    ctx.beginPath(); ctx.ellipse(s * 0.5, s * 0.55, s * 0.29, s * 0.31, 0, 0, Math.PI * 2); ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014); ctx.stroke();
    ctx.fillStyle = C.gradient(ctx, s * 0.22, s * 0.48, s * 0.78, s * 0.66,
        [[0, C.PALETTE.indigoDeep], [0.5, C.PALETTE.tealDeep], [1, C.PALETTE.indigoDeep]]);
    ctx.beginPath(); ctx.moveTo(s * 0.24, s * 0.55);
    ctx.lineTo(s * 0.36, s * 0.43); ctx.lineTo(s * 0.45, s * 0.50);
    ctx.lineTo(s * 0.55, s * 0.40); ctx.lineTo(s * 0.66, s * 0.50);
    ctx.lineTo(s * 0.76, s * 0.55); ctx.lineTo(s * 0.69, s * 0.68);
    ctx.quadraticCurveTo(s * 0.50, s * 0.77, s * 0.31, s * 0.68); ctx.closePath(); ctx.fill();
    C.setStroke(ctx, g, s * 0.018); ctx.stroke();
    C.setStroke(ctx, C.PALETTE.bgCreamHi, s * 0.012);
    [[0.36,0.56],[0.50,0.51],[0.64,0.56]].forEach(function(p) {
        ctx.beginPath(); ctx.moveTo(s * p[0], s * p[1]); ctx.lineTo(s * p[0], s * 0.66); ctx.stroke();
    });
    ctx.fillStyle = C.PALETTE.goldHi;
    [[0.36,0.56],[0.50,0.51],[0.64,0.56]].forEach(function(p) {
        ctx.beginPath(); ctx.arc(s * p[0], s * p[1], s * 0.025, 0, Math.PI * 2); ctx.fill();
    });
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.025);
    ctx.beginPath(); ctx.moveTo(s * 0.27, s * 0.78); ctx.lineTo(s * 0.73, s * 0.78);
    ctx.moveTo(s * 0.34, s * 0.75); ctx.lineTo(s * 0.30, s * 0.82);
    ctx.moveTo(s * 0.66, s * 0.75); ctx.lineTo(s * 0.70, s * 0.82); ctx.stroke();
    ctx.restore();
    _glint(ctx, s * 0.50, s * 0.25, s * 0.035, C.PALETTE.bgCreamHi);
}

function drawKithSluagh(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    ctx.save();
    ctx.fillStyle = C.radial(ctx, s * 0.5, s * 0.5, 0, s * 0.36,
        [[0, "rgba(107,142,143,0.18)"], [0.7, "rgba(61,72,102,0.30)"], [1, "rgba(35,48,74,0.08)"]]);
    ctx.beginPath(); ctx.arc(s * 0.5, s * 0.5, s * 0.34, 0, Math.PI * 2); ctx.fill();
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.23);
    ctx.bezierCurveTo(s * 0.30, s * 0.32, s * 0.25, s * 0.56, s * 0.37, s * 0.74);
    ctx.quadraticCurveTo(s * 0.50, s * 0.67, s * 0.63, s * 0.74);
    ctx.bezierCurveTo(s * 0.75, s * 0.56, s * 0.70, s * 0.32, s * 0.50, s * 0.23);
    ctx.closePath(); ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012); ctx.stroke();
    ctx.fillStyle = C.PALETTE.teal;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.35);
    ctx.bezierCurveTo(s * 0.40, s * 0.43, s * 0.40, s * 0.56, s * 0.50, s * 0.65);
    ctx.bezierCurveTo(s * 0.60, s * 0.56, s * 0.60, s * 0.43, s * 0.50, s * 0.35);
    ctx.closePath(); ctx.fill();
    C.setStroke(ctx, C.PALETTE.bgCreamHi, s * 0.015);
    ctx.beginPath(); ctx.moveTo(s * 0.50, s * 0.39);
    ctx.quadraticCurveTo(s * 0.40, s * 0.47, s * 0.50, s * 0.55);
    ctx.quadraticCurveTo(s * 0.60, s * 0.47, s * 0.50, s * 0.39); ctx.stroke();
    C.setStroke(ctx, C.PALETTE.roseDeep, s * 0.020);
    ctx.beginPath();
    ctx.moveTo(s * 0.31, s * 0.43); ctx.quadraticCurveTo(s * 0.16, s * 0.28, s * 0.29, s * 0.22);
    ctx.moveTo(s * 0.69, s * 0.43); ctx.quadraticCurveTo(s * 0.84, s * 0.28, s * 0.71, s * 0.22);
    ctx.stroke();
    C.setStroke(ctx, _gold(accent), s * 0.012);
    ctx.beginPath(); ctx.arc(s * 0.50, s * 0.50, s * 0.31, Math.PI * 0.18, Math.PI * 0.82); ctx.stroke();
    ctx.restore();
    C.drawRosette(ctx, s * 0.50, s * 0.78, s * 0.04, 5, C.PALETTE.plum, _gold(accent));
    _glint(ctx, s * 0.72, s * 0.31, s * 0.028, C.PALETTE.bgCreamHi);
}
