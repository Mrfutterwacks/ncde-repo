// mucha-icons-apps-browsers.js
// Web browsers — every icon a distinct Mucha-style composition.
// All draw functions take (ctx, s, accent, glow). No PNG/SVG. No Qt.lighter().

.pragma library
.import "mucha-icons-core.js" as C

// ============================================================================
// FIREFOX — flame-curled fox medallion inside a sage shield
// ============================================================================
function drawFirefox(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    C.drawHalo(ctx, s, glow || C.PALETTE.goldShine);

    var cx = s * 0.5, cy = s * 0.5, r = s * 0.30;

    // flame swirl (3-armed whiplash around the disc)
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 3; i++) {
        ctx.save();
        ctx.rotate(i * Math.PI * 2 / 3);
        var g = ctx.createLinearGradient(0, -r * 1.25, 0, r * 0.6);
        g.addColorStop(0, C.PALETTE.terra);
        g.addColorStop(1, C.PALETTE.gold);
        ctx.fillStyle = g;
        ctx.beginPath();
        ctx.moveTo(0, -r * 1.25);
        ctx.bezierCurveTo(r * 0.6, -r * 1.1, r * 0.85, -r * 0.2, r * 0.05, r * 0.18);
        ctx.bezierCurveTo(-r * 0.05, -r * 0.55, -r * 0.05, -r * 0.95, 0, -r * 1.25);
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
    ctx.restore();

    // inner disc & stylised fox face (geometric — no logo)
    C.drawInnerDisc(ctx, s, C.PALETTE.plumDeep, 0.22);
    C.stipple(ctx, cx - s * 0.22, cy - s * 0.22, s * 0.44, s * 0.44, 0.10, "rgba(255,235,180,0.18)");
    ctx.save();
    ctx.fillStyle = C.PALETTE.goldHi;
    // ears (twin triangles)
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.13, cy - s * 0.05);
    ctx.lineTo(cx - s * 0.18, cy - s * 0.16);
    ctx.lineTo(cx - s * 0.07, cy - s * 0.10);
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.13, cy - s * 0.05);
    ctx.lineTo(cx + s * 0.18, cy - s * 0.16);
    ctx.lineTo(cx + s * 0.07, cy - s * 0.10);
    ctx.closePath();
    ctx.fill();
    // muzzle (almond)
    C.leafBead(ctx, cx, cy + s * 0.05, s * 0.18, 0, C.PALETTE.bgCreamHi);
    // eye gem
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.arc(cx, cy - s * 0.005, s * 0.025, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();

    // accent rim
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.22, 0, Math.PI * 2);
    C.setStroke(ctx, accent || C.PALETTE.border, s * 0.018);
    ctx.stroke();
}

// ============================================================================
// LIBREWOLF — silvered wolf-flame variant; cool moon palette
// ============================================================================
function drawLibreWolf(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // moon halo (full disc, cool pewter)
    ctx.beginPath();
    ctx.arc(cx, cy * 0.92, s * 0.34, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx, cy * 0.92, s * 0.04, s * 0.34,
        [[0,"#e8e9ee"],[0.7,"#b9bdc8"],[1,"#7e8597"]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.indigoDeep, s * 0.014);
    ctx.stroke();
    // wolf-flame curl (single sinuous tail)
    ctx.save();
    ctx.strokeStyle = C.PALETTE.indigoDeep;
    ctx.lineWidth = s * 0.07;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.22, cy - s * 0.18);
    ctx.bezierCurveTo(cx + s * 0.32, cy + s * 0.05, cx, cy + s * 0.30, cx - s * 0.18, cy + s * 0.05);
    ctx.bezierCurveTo(cx - s * 0.05, cy - s * 0.10, cx + s * 0.05, cy - s * 0.05, cx + s * 0.08, cy - s * 0.18);
    ctx.stroke();
    ctx.restore();
    // wolf ears triangles
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.10, cy - s * 0.18);
    ctx.lineTo(cx - s * 0.18, cy - s * 0.30);
    ctx.lineTo(cx - s * 0.04, cy - s * 0.22);
    ctx.closePath(); ctx.fill();
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.10, cy - s * 0.18);
    ctx.lineTo(cx + s * 0.18, cy - s * 0.30);
    ctx.lineTo(cx + s * 0.04, cy - s * 0.22);
    ctx.closePath(); ctx.fill();
    // crescent shadow over moon
    ctx.save();
    ctx.globalCompositeOperation = "multiply";
    ctx.fillStyle = "rgba(60,70,95,0.35)";
    ctx.beginPath();
    ctx.arc(cx + s * 0.08, cy * 0.92, s * 0.30, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
}

// ============================================================================
// CHROMIUM — three-petal triadic rosette (open-source, sage-led)
// ============================================================================
function drawChromium(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5, R = s * 0.32;
    // three petal sections (RYB-ish translated to Mucha)
    var cols = [C.PALETTE.terra, C.PALETTE.sageDeep, C.PALETTE.goldDark];
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 3; i++) {
        ctx.save();
        ctx.rotate(i * Math.PI * 2 / 3 - Math.PI / 2);
        ctx.fillStyle = cols[i];
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.arc(0, 0, R, -Math.PI * 0.5 - 0.04, -Math.PI * 0.5 + Math.PI * 2 / 3 + 0.04, false);
        ctx.closePath();
        ctx.fill();
        // veining
        C.setStroke(ctx, "rgba(255,235,180,0.45)", s * 0.014);
        ctx.beginPath();
        ctx.moveTo(0, -R * 0.15);
        ctx.lineTo(R * 0.6 * Math.cos(Math.PI / 3), R * 0.6 * Math.sin(Math.PI / 3) - R * 0.15);
        ctx.stroke();
        ctx.restore();
    }
    ctx.restore();
    // central beaded ring
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.14, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.ringDots(ctx, cx, cy, s * 0.18, 18, s * 0.012, C.PALETTE.goldDark);
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.07, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    // accent border
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.14, 0, Math.PI * 2);
    C.setStroke(ctx, accent || C.PALETTE.border, s * 0.014);
    ctx.stroke();
}

// ============================================================================
// CHROME — same triadic geometry but with gilt frame & polychrome panels
// ============================================================================
function drawChrome(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5, R = s * 0.34;
    var cols = [C.PALETTE.terra, C.PALETTE.sageDeep, C.PALETTE.goldHi];
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 3; i++) {
        ctx.save();
        ctx.rotate(i * Math.PI * 2 / 3 - Math.PI / 2);
        var grd = ctx.createLinearGradient(0, -R, 0, R * 0.4);
        grd.addColorStop(0, cols[i]);
        grd.addColorStop(1, "#3a2b18");
        ctx.fillStyle = grd;
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.arc(0, 0, R, -Math.PI * 0.5 - 0.04, -Math.PI * 0.5 + Math.PI * 2 / 3 + 0.04, false);
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
    ctx.restore();
    // panel separators in gold
    for (var j = 0; j < 3; j++) {
        var a = j * Math.PI * 2 / 3 - Math.PI / 2;
        ctx.beginPath();
        ctx.moveTo(cx, cy);
        ctx.lineTo(cx + Math.cos(a) * R, cy + Math.sin(a) * R);
        C.setStroke(ctx, C.PALETTE.gold, s * 0.026);
        ctx.stroke();
    }
    // sapphire bezel core
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.13, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.04, cy - s * 0.04, s * 0.005, s * 0.13,
        [[0,"#a9c3e8"],[1,C.PALETTE.indigoDeep]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.gold, s * 0.022);
    ctx.stroke();
    // bezel claws (4 prongs)
    for (var k = 0; k < 4; k++) {
        var aa = k * Math.PI / 2 + Math.PI / 4;
        ctx.beginPath();
        ctx.arc(cx + Math.cos(aa) * s * 0.13, cy + Math.sin(aa) * s * 0.13, s * 0.018, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.goldHi;
        ctx.fill();
    }
}

// ============================================================================
// BRAVE — heater shield with lion-rampant heraldic ornament
// ============================================================================
function drawBrave(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"shield", accent:accent, glow:glow, ornament:false});
    var cx = s * 0.5;
    // central pale
    var paleW = s * 0.13;
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillRect(cx - paleW / 2, s * 0.10, paleW, s * 0.78);
    // crossing chevron
    ctx.save();
    ctx.fillStyle = C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.12, s * 0.62);
    ctx.lineTo(cx, s * 0.32);
    ctx.lineTo(s * 0.88, s * 0.62);
    ctx.lineTo(s * 0.88, s * 0.72);
    ctx.lineTo(cx, s * 0.42);
    ctx.lineTo(s * 0.12, s * 0.72);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
    // crowned lion-head ornament (stylised — gold quatrefoil with mane rays)
    var lx = cx, ly = s * 0.58;
    for (var i = 0; i < 12; i++) {
        var a = i / 12 * Math.PI * 2;
        ctx.beginPath();
        ctx.moveTo(lx + Math.cos(a) * s * 0.08, ly + Math.sin(a) * s * 0.08);
        ctx.lineTo(lx + Math.cos(a) * s * 0.18, ly + Math.sin(a) * s * 0.18);
        C.setStroke(ctx, C.PALETTE.goldHi, s * 0.022);
        ctx.stroke();
    }
    ctx.beginPath();
    ctx.arc(lx, ly, s * 0.085, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // eyes & muzzle
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath(); ctx.arc(lx - s * 0.025, ly - s * 0.01, s * 0.011, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(lx + s * 0.025, ly - s * 0.01, s * 0.011, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath();
    ctx.moveTo(lx - s * 0.015, ly + s * 0.018);
    ctx.lineTo(lx + s * 0.015, ly + s * 0.018);
    ctx.lineTo(lx, ly + s * 0.035);
    ctx.closePath(); ctx.fill();
    // shield outline (theme accent)
    ctx.save();
    ctx.translate(2.5, 2.5);
    C.shieldPath(ctx, s - 5);
    C.setStroke(ctx, accent || C.PALETTE.border, s * 0.020);
    ctx.stroke();
    ctx.restore();
}

// ============================================================================
// VIVALDI — musical staff curled into a rose; sangue-di-bue palette
// ============================================================================
function drawVivaldi(ctx, s, accent, glow) {
    C.drawTile(ctx, s, "#e8d6c4", {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // spiralling staff lines
    ctx.save();
    ctx.strokeStyle = C.PALETTE.terraDark;
    ctx.lineWidth = s * 0.013;
    ctx.lineCap = "round";
    for (var i = 0; i < 5; i++) {
        ctx.beginPath();
        var r0 = s * (0.12 + i * 0.035);
        for (var t = 0; t <= 270; t += 6) {
            var ang = (t / 180) * Math.PI;
            var rr = r0 + t * 0.025;
            var x = cx + Math.cos(ang) * rr * 0.04;
            var y = cy + Math.sin(ang) * rr * 0.04;
            if (t === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
        }
        ctx.stroke();
    }
    ctx.restore();
    // rose head at centre
    C.drawRosette(ctx, cx, cy, s * 0.18, 6, C.PALETTE.roseDeep, C.PALETTE.goldHi);
    // treble-clef-like ornament — abstract S
    ctx.save();
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.026;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.02, cy - s * 0.27);
    ctx.bezierCurveTo(cx + s * 0.20, cy - s * 0.20, cx + s * 0.18, cy + s * 0.05, cx, cy + s * 0.05);
    ctx.bezierCurveTo(cx - s * 0.18, cy + s * 0.05, cx - s * 0.20, cy + s * 0.27, cx + s * 0.02, cy + s * 0.33);
    ctx.stroke();
    ctx.restore();
}

// ============================================================================
// OPERA — operatic mask in a domed proscenium arch
// ============================================================================
function drawOpera(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"arch", accent:accent, glow:glow, ornament:false});
    var cx = s * 0.5;
    // proscenium drapes
    ctx.save();
    ctx.fillStyle = C.PALETTE.plumDeep;
    for (var i = 0; i < 4; i++) {
        ctx.beginPath();
        var x0 = s * 0.09 + i * s * 0.08;
        ctx.moveTo(x0, s * 0.05);
        ctx.quadraticCurveTo(x0 + s * 0.03, s * 0.32, x0 + s * 0.02, s * 0.55);
        ctx.lineTo(x0 + s * 0.07, s * 0.55);
        ctx.quadraticCurveTo(x0 + s * 0.10, s * 0.32, x0 + s * 0.075, s * 0.05);
        ctx.closePath();
        ctx.fill();
    }
    for (var j = 0; j < 4; j++) {
        ctx.beginPath();
        var xr = s * 0.91 - j * s * 0.08;
        ctx.moveTo(xr, s * 0.05);
        ctx.quadraticCurveTo(xr - s * 0.03, s * 0.32, xr - s * 0.02, s * 0.55);
        ctx.lineTo(xr - s * 0.07, s * 0.55);
        ctx.quadraticCurveTo(xr - s * 0.10, s * 0.32, xr - s * 0.075, s * 0.05);
        ctx.closePath();
        ctx.fill();
    }
    ctx.restore();
    // mask
    ctx.save();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.ellipse(cx, s * 0.58, s * 0.22, s * 0.14, 0, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // eyeholes
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.ellipse(cx - s * 0.08, s * 0.55, s * 0.035, s * 0.025, -0.2, 0, Math.PI * 2);
    ctx.fill();
    ctx.beginPath();
    ctx.ellipse(cx + s * 0.08, s * 0.55, s * 0.035, s * 0.025, 0.2, 0, Math.PI * 2);
    ctx.fill();
    // tear (operatic)
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.08, s * 0.61);
    ctx.quadraticCurveTo(cx - s * 0.095, s * 0.68, cx - s * 0.08, s * 0.71);
    ctx.quadraticCurveTo(cx - s * 0.065, s * 0.68, cx - s * 0.08, s * 0.61);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
    // gilded "O" cartouche over the arch
    ctx.beginPath();
    ctx.arc(cx, s * 0.20, s * 0.075, 0, Math.PI * 2);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.025);
    ctx.stroke();
}

// ============================================================================
// EDGE — swept whiplash crest with gilded swash
// ============================================================================
function drawEdge(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // wave body
    ctx.save();
    var grd = ctx.createLinearGradient(0, cy - s * 0.2, 0, cy + s * 0.2);
    grd.addColorStop(0, C.PALETTE.teal);
    grd.addColorStop(1, C.PALETTE.tealDeep);
    ctx.fillStyle = grd;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.30, cy + s * 0.10);
    ctx.bezierCurveTo(cx - s * 0.10, cy - s * 0.30, cx + s * 0.20, cy - s * 0.20, cx + s * 0.28, cy + s * 0.05);
    ctx.bezierCurveTo(cx + s * 0.10, cy - s * 0.05, cx - s * 0.05, cy + s * 0.10, cx - s * 0.30, cy + s * 0.10);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    ctx.restore();
    // gilt swash overlay
    ctx.save();
    ctx.strokeStyle = C.PALETTE.gold;
    ctx.lineWidth = s * 0.012;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.24, cy + s * 0.05);
    ctx.bezierCurveTo(cx - s * 0.05, cy - s * 0.22, cx + s * 0.18, cy - s * 0.15, cx + s * 0.24, cy + s * 0.02);
    ctx.stroke();
    ctx.restore();
    // pearl beads along crest
    for (var i = 0; i < 7; i++) {
        var t = i / 6;
        var x = cx - s * 0.24 + t * s * 0.48;
        var y = cy + s * 0.08 + Math.sin(t * Math.PI) * -s * 0.22;
        ctx.beginPath();
        ctx.arc(x, y, s * 0.013, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.goldHi;
        ctx.fill();
    }
    // base ornament — laurel sprig
    C.drawFloralStem(ctx, cx - s * 0.20, cy + s * 0.30, s * 0.20, C.PALETTE.sageDeep, accent || C.PALETTE.gold);
    C.drawFloralStem(ctx, cx + s * 0.20, cy + s * 0.30, -s * 0.20, C.PALETTE.sageDeep, accent || C.PALETTE.gold);
}

// ============================================================================
// TOR — concentric onion layers with a watching eye
// ============================================================================
function drawTor(ctx, s, accent, glow) {
    C.drawTile(ctx, s, "#e0d2b2", {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // onion layers
    var layers = [{r: 0.36, c: C.PALETTE.plumDeep},
                  {r: 0.30, c: C.PALETTE.plum},
                  {r: 0.24, c: C.PALETTE.roseDeep},
                  {r: 0.18, c: C.PALETTE.terra},
                  {r: 0.12, c: C.PALETTE.gold}];
    for (var i = 0; i < layers.length; i++) {
        ctx.beginPath();
        ctx.arc(cx, cy, s * layers[i].r, 0, Math.PI * 2);
        ctx.fillStyle = layers[i].c;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    }
    // watchful eye in centre
    ctx.beginPath();
    ctx.ellipse(cx, cy, s * 0.08, s * 0.05, 0, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.025, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    // lashes
    ctx.save();
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.008;
    for (var k = 0; k < 5; k++) {
        var a = -Math.PI * 0.65 + k * Math.PI * 0.075;
        ctx.beginPath();
        ctx.moveTo(cx + Math.cos(a) * s * 0.085, cy + Math.sin(a) * s * 0.05);
        ctx.lineTo(cx + Math.cos(a) * s * 0.115, cy + Math.sin(a) * s * 0.075);
        ctx.stroke();
    }
    ctx.restore();
}

// ============================================================================
// FALKON — feather plume with a falcon-claw clasp
// ============================================================================
function drawFalkon(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // feather shaft
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-Math.PI / 8);
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.018;
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.32);
    ctx.lineTo(0, s * 0.28);
    ctx.stroke();
    // barbs (left + right pairs, fanning)
    ctx.strokeStyle = C.PALETTE.sageDeep;
    ctx.lineWidth = s * 0.010;
    for (var i = 0; i < 18; i++) {
        var t = i / 17;
        var y = -s * 0.30 + t * s * 0.55;
        var len = s * 0.16 * (1 - Math.abs(t - 0.4));
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.quadraticCurveTo(-len * 0.6, y - s * 0.02, -len, y - s * 0.04);
        ctx.stroke();
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.quadraticCurveTo(len * 0.6, y - s * 0.02, len, y - s * 0.04);
        ctx.stroke();
    }
    ctx.restore();
    // claw clasp
    ctx.save();
    ctx.translate(cx, cy + s * 0.22);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(-s * 0.10, 0);
    ctx.bezierCurveTo(-s * 0.08, s * 0.08, s * 0.08, s * 0.08, s * 0.10, 0);
    ctx.lineTo(s * 0.07, -s * 0.02);
    ctx.bezierCurveTo(s * 0.05, s * 0.04, -s * 0.05, s * 0.04, -s * 0.07, -s * 0.02);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    ctx.restore();
}

// ============================================================================
// KONQUEROR — laurel crown of conquest around a Q-style cartouche
// ============================================================================
function drawKonqueror(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // laurel wreath
    var lr = s * 0.34;
    for (var i = 0; i < 12; i++) {
        var a = -Math.PI * 0.85 + i / 11 * Math.PI * 0.7 * -1;
        C.leafBead(ctx, cx + Math.cos(a) * lr, cy + Math.sin(a) * lr, s * 0.16, a + Math.PI / 2, C.PALETTE.sageDeep);
    }
    for (var j = 0; j < 12; j++) {
        var a2 = Math.PI * 0.15 + j / 11 * Math.PI * 0.7;
        C.leafBead(ctx, cx + Math.cos(a2) * lr, cy + Math.sin(a2) * lr, s * 0.16, a2 + Math.PI / 2, C.PALETTE.sageDeep);
    }
    // tie ribbon at bottom
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.10, cy + s * 0.32);
    ctx.lineTo(cx - s * 0.05, cy + s * 0.42);
    ctx.lineTo(cx + s * 0.05, cy + s * 0.42);
    ctx.lineTo(cx + s * 0.10, cy + s * 0.32);
    ctx.closePath();
    ctx.fill();
    // central cartouche
    C.drawInnerDisc(ctx, s, C.PALETTE.bgCreamHi, 0.20);
    // Q-like glyph
    ctx.save();
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.022;
    ctx.beginPath();
    ctx.arc(cx, cy - s * 0.02, s * 0.13, 0, Math.PI * 2);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.07, cy + s * 0.05);
    ctx.lineTo(cx + s * 0.16, cy + s * 0.14);
    ctx.stroke();
    ctx.restore();
}

// ============================================================================
// QUTEBROWSER — keyboard-driven; minimalist column of glyphs with a stylus
// ============================================================================
function drawQutebrowser(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    var cx = s * 0.5;
    // engraved command column
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.18, s * 0.16, s * 0.64, s * 0.18);
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.font = "700 " + Math.round(s * 0.13) + "px monospace";
    ctx.textBaseline = "middle";
    ctx.textAlign = "left";
    ctx.fillText(":open", s * 0.22, s * 0.25);
    // command rows
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "600 " + Math.round(s * 0.09) + "px monospace";
    ctx.fillText("gg / G", s * 0.20, s * 0.46);
    ctx.fillText("h j k l", s * 0.20, s * 0.60);
    ctx.fillText(":quit", s * 0.20, s * 0.74);
    // stylus (a quill) on right
    ctx.save();
    ctx.translate(s * 0.78, s * 0.78);
    ctx.rotate(-Math.PI / 4);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.18);
    ctx.lineTo(s * 0.02, -s * 0.18);
    ctx.lineTo(s * 0.05, s * 0.10);
    ctx.lineTo(-s * 0.03, s * 0.12);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    ctx.restore();
}

// ============================================================================
// EPIPHANY (GNOME Web) — globe in a bay-leaf wreath
// ============================================================================
function drawEpiphany(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // globe
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.06, cy - s * 0.06, s * 0.02, s * 0.26,
        [[0,"#cbe2dd"],[1,C.PALETTE.tealDeep]]);
    ctx.fill();
    // longitude/latitude
    ctx.save();
    ctx.strokeStyle = C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.010;
    for (var i = 0; i < 5; i++) {
        ctx.beginPath();
        ctx.ellipse(cx, cy, s * 0.26 * (1 - i * 0.18), s * 0.26, 0, 0, Math.PI * 2);
        ctx.stroke();
    }
    for (var j = 1; j < 4; j++) {
        ctx.beginPath();
        ctx.moveTo(cx - s * 0.26, cy - s * 0.26 + j * s * 0.13);
        ctx.bezierCurveTo(cx - s * 0.10, cy - s * 0.26 + j * s * 0.13 - 2,
                          cx + s * 0.10, cy - s * 0.26 + j * s * 0.13 - 2,
                          cx + s * 0.26, cy - s * 0.26 + j * s * 0.13);
        ctx.stroke();
    }
    ctx.restore();
    // tiny bay wreath beneath
    for (var k = 0; k < 5; k++) {
        var a1 = Math.PI * 0.78 + k * 0.05;
        var a2 = Math.PI * 0.22 - k * 0.05;
        C.leafBead(ctx, cx + Math.cos(a1) * s * 0.34, cy + Math.sin(a1) * s * 0.34, s * 0.10, a1, C.PALETTE.sageDeep);
        C.leafBead(ctx, cx + Math.cos(a2) * s * 0.34, cy + Math.sin(a2) * s * 0.34, s * 0.10, a2, C.PALETTE.sageDeep);
    }
}

// ============================================================================
// MIDORI — green hexagonal cell with citrus segments
// ============================================================================
function drawMidori(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // hexagon
    ctx.beginPath();
    for (var i = 0; i < 6; i++) {
        var a = i / 6 * Math.PI * 2 - Math.PI / 2;
        var x = cx + Math.cos(a) * s * 0.30;
        var y = cy + Math.sin(a) * s * 0.30;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // citrus segments
    for (var k = 0; k < 6; k++) {
        var aa = k / 6 * Math.PI * 2 - Math.PI / 2;
        ctx.save();
        ctx.translate(cx, cy);
        ctx.rotate(aa);
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.quadraticCurveTo(s * 0.07, -s * 0.05, 0, -s * 0.22);
        ctx.quadraticCurveTo(-s * 0.07, -s * 0.05, 0, 0);
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
    // central pip
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
}

// ============================================================================
// TEXT BROWSER (lynx/links/w3m/netsurf/dillo) — scroll & monospace prompt
// ============================================================================
function drawTextBrowser(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // unfurled scroll
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.13, s * 0.22, s * 0.74, s * 0.56, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.014);
    ctx.stroke();
    // scroll rolls top & bottom
    for (var i = 0; i < 2; i++) {
        var y = i ? s * 0.78 : s * 0.22;
        ctx.beginPath();
        ctx.ellipse(s * 0.5, y, s * 0.40, s * 0.045, 0, 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
        ctx.stroke();
    }
    // text lines
    ctx.fillStyle = C.PALETTE.ink;
    var w = s * 0.55;
    for (var k = 0; k < 5; k++) {
        ctx.fillRect(s * 0.22, s * 0.32 + k * s * 0.08, w * (0.6 + 0.08 * k), s * 0.018);
    }
    // hyperlink (gold underline)
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.22, s * 0.66, s * 0.20, s * 0.014);
}

// ============================================================================
// GENERIC BROWSER — globe with longitude bands (used for unknown browsers)
// ============================================================================
function drawGenericBrowser(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.08, cy - s * 0.08, s * 0.02, s * 0.30,
        [[0,"#d8e6df"],[1,C.PALETTE.sageDeep]]);
    ctx.fill();
    ctx.save();
    ctx.strokeStyle = C.PALETTE.gold;
    ctx.lineWidth = s * 0.011;
    for (var i = 0; i < 4; i++) {
        ctx.beginPath();
        ctx.ellipse(cx, cy, s * 0.30 * (1 - i * 0.22), s * 0.30, 0, 0, Math.PI * 2);
        ctx.stroke();
    }
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.30, cy);
    ctx.lineTo(cx + s * 0.30, cy);
    ctx.stroke();
    ctx.restore();
    C.setStroke(ctx, accent || C.PALETTE.border, s * 0.018);
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.stroke();
}
