// mucha-icons-apps-media.js — audio and video apps. Every metaphor unique.
.pragma library
.import "mucha-icons-core.js" as C

// ============================================================================
// VLC — traffic-cone reimagined as a fluted gilt cone
// ============================================================================
function drawVLC(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5;
    // cone body (4-band)
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.06, s * 0.20);
    ctx.lineTo(cx + s * 0.06, s * 0.20);
    ctx.lineTo(cx + s * 0.24, s * 0.74);
    ctx.lineTo(cx - s * 0.24, s * 0.74);
    ctx.closePath();
    var g = ctx.createLinearGradient(0, s * 0.20, 0, s * 0.74);
    g.addColorStop(0, accent || C.PALETTE.goldHi);
    g.addColorStop(1, C.PALETTE.terraDark);
    ctx.fillStyle = g;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // fluting stripes
    ctx.fillStyle = "rgba(58,43,24,0.4)";
    for (var i = 0; i < 5; i++) {
        var y = s * (0.30 + i * 0.10);
        var w = (y - s * 0.20) / (s * 0.54) * s * 0.48;
        ctx.fillRect(cx - w / 2, y, w, s * 0.012);
    }
    // tip cap
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    C.roundRectPath(ctx, cx - s * 0.08, s * 0.18, s * 0.16, s * 0.05, s * 0.018);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // base
    ctx.fillStyle = C.PALETTE.ink;
    C.roundRectPath(ctx, cx - s * 0.30, s * 0.74, s * 0.60, s * 0.04, s * 0.012);
    ctx.fill();
}

// MPV — triangular play with mosaic halo
function drawMPV(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // mosaic ring
    for (var i = 0; i < 24; i++) {
        var a = i / 24 * Math.PI * 2 - Math.PI / 2;
        ctx.save();
        ctx.translate(cx + Math.cos(a) * s * 0.34, cy + Math.sin(a) * s * 0.34);
        ctx.rotate(a + Math.PI / 2);
        ctx.fillStyle = i % 3 === 0 ? accent || C.PALETTE.gold
                       : i % 3 === 1 ? C.PALETTE.plum : C.PALETTE.sageDeep;
        ctx.fillRect(-s * 0.025, -s * 0.012, s * 0.05, s * 0.024);
        ctx.restore();
    }
    // play triangle
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.10, cy - s * 0.16);
    ctx.lineTo(cx + s * 0.16, cy);
    ctx.lineTo(cx - s * 0.10, cy + s * 0.16);
    ctx.closePath();
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
}

// SMPLAYER — trapezoid film frame
function drawSMPlayer(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // trapezoid (perspective film)
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.26);
    ctx.lineTo(s * 0.80, s * 0.26);
    ctx.lineTo(s * 0.86, s * 0.74);
    ctx.lineTo(s * 0.14, s * 0.74);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    // play
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.42, s * 0.36);
    ctx.lineTo(s * 0.66, s * 0.50);
    ctx.lineTo(s * 0.42, s * 0.64);
    ctx.closePath();
    ctx.fill();
    // film holes
    for (var i = 0; i < 4; i++) {
        ctx.fillStyle = C.PALETTE.bgCream;
        ctx.fillRect(s * (0.22 + i * 0.16), s * 0.20, s * 0.04, s * 0.03);
        ctx.fillRect(s * (0.22 + i * 0.16), s * 0.77, s * 0.04, s * 0.03);
    }
}

// CELLULOID — film reel
function drawCelluloid(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.32, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    // 6 reel holes
    for (var i = 0; i < 6; i++) {
        var a = i / 6 * Math.PI * 2;
        ctx.beginPath();
        ctx.arc(cx + Math.cos(a) * s * 0.18, cy + Math.sin(a) * s * 0.18, s * 0.05, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.bgCream;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.goldDark, s * 0.008);
        ctx.stroke();
    }
    // hub
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.06, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
}

// TOTEM — vertical filmstrip with gilt frame
function drawTotem(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(s * 0.30, s * 0.14, s * 0.40, s * 0.72);
    for (var i = 0; i < 4; i++) {
        // frame windows
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.fillRect(s * 0.36, s * 0.20 + i * s * 0.16, s * 0.28, s * 0.10);
        // sprocket holes
        ctx.fillStyle = C.PALETTE.bgCream;
        ctx.fillRect(s * 0.32, s * 0.21 + i * s * 0.16, s * 0.03, s * 0.04);
        ctx.fillRect(s * 0.65, s * 0.21 + i * s * 0.16, s * 0.03, s * 0.04);
    }
    // play overlay
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.44, s * 0.40);
    ctx.lineTo(s * 0.58, s * 0.50);
    ctx.lineTo(s * 0.44, s * 0.60);
    ctx.closePath();
    ctx.fill();
}

// KAFFEINE — coffee cup with audio waves
function drawKaffeine(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    // cup
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.moveTo(s * 0.28, s * 0.46);
    ctx.lineTo(s * 0.68, s * 0.46);
    ctx.bezierCurveTo(s * 0.66, s * 0.78, s * 0.30, s * 0.78, s * 0.28, s * 0.46);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // handle
    ctx.beginPath();
    ctx.arc(s * 0.74, s * 0.58, s * 0.08, -Math.PI * 0.6, Math.PI * 0.6);
    C.setStroke(ctx, C.PALETTE.terraDark, s * 0.030);
    ctx.stroke();
    // steam waves
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.012;
    ctx.lineCap = "round";
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        var x = s * (0.36 + i * 0.12);
        ctx.moveTo(x, s * 0.38);
        ctx.bezierCurveTo(x - s * 0.03, s * 0.30, x + s * 0.03, s * 0.26, x, s * 0.18);
        ctx.stroke();
    }
}

// AUDACIOUS — speaker cone with sound rays
function drawAudacious(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // speaker rectangle
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(s * 0.18, s * 0.36, s * 0.16, s * 0.28);
    // cone
    ctx.beginPath();
    ctx.moveTo(s * 0.34, s * 0.36);
    ctx.lineTo(s * 0.50, s * 0.24);
    ctx.lineTo(s * 0.50, s * 0.76);
    ctx.lineTo(s * 0.34, s * 0.64);
    ctx.closePath();
    ctx.fill();
    // sound rays
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.018;
    ctx.lineCap = "round";
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(cx, cy, s * (0.12 + i * 0.08), -Math.PI * 0.3, Math.PI * 0.3);
        ctx.stroke();
    }
}

// RHYTHMBOX — frame drum with crossed sticks
function drawRhythmbox(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.52;
    // drum head
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.06, cy - s * 0.08, s * 0.02, s * 0.26,
        [[0, C.PALETTE.bgCreamHi], [1, C.PALETTE.bgPaper]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.terraDark, s * 0.014);
    ctx.stroke();
    // rim
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    C.setStroke(ctx, C.PALETTE.terraDark, s * 0.020);
    ctx.stroke();
    // tension lugs
    for (var i = 0; i < 8; i++) {
        var a = i / 8 * Math.PI * 2;
        ctx.beginPath();
        ctx.arc(cx + Math.cos(a) * s * 0.30, cy + Math.sin(a) * s * 0.30, s * 0.022, 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fill();
    }
    // sticks crossed
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = "#a87742";
    ctx.save(); ctx.rotate(0.5);
    ctx.fillRect(-s * 0.02, -s * 0.22, s * 0.04, s * 0.44);
    ctx.beginPath(); ctx.arc(0, -s * 0.22, s * 0.034, 0, Math.PI * 2); ctx.fill();
    ctx.restore();
    ctx.save(); ctx.rotate(-0.5);
    ctx.fillRect(-s * 0.02, -s * 0.22, s * 0.04, s * 0.44);
    ctx.beginPath(); ctx.arc(0, -s * 0.22, s * 0.034, 0, Math.PI * 2); ctx.fill();
    ctx.restore();
    ctx.restore();
}

// CLEMENTINE — citrus fruit (clementine)
function drawClementine(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.54;
    // fruit
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.06, cy - s * 0.10, s * 0.02, s * 0.30,
        [[0, "#f5b870"], [1, "#b56340"]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.terraDark, s * 0.014);
    ctx.stroke();
    // dimple top
    ctx.beginPath();
    ctx.arc(cx, cy - s * 0.24, s * 0.05, 0, Math.PI * 2);
    ctx.fillStyle = "#7a3e22";
    ctx.fill();
    // leaf
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(cx, cy - s * 0.28);
    ctx.quadraticCurveTo(cx + s * 0.18, cy - s * 0.38, cx + s * 0.20, cy - s * 0.22);
    ctx.quadraticCurveTo(cx + s * 0.10, cy - s * 0.22, cx, cy - s * 0.28);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    // segments lines
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 8; i++) {
        ctx.beginPath();
        ctx.moveTo(0, 0);
        var a = i / 8 * Math.PI * 2;
        ctx.lineTo(Math.cos(a) * s * 0.24, Math.sin(a) * s * 0.24);
        C.setStroke(ctx, "rgba(255,235,180,0.5)", s * 0.010);
        ctx.stroke();
    }
    ctx.restore();
}

// STRAWBERRY — berry with stem of leaves
function drawStrawberry(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.58;
    // berry body
    ctx.fillStyle = C.PALETTE.terra;
    ctx.beginPath();
    ctx.moveTo(cx, cy - s * 0.06);
    ctx.bezierCurveTo(cx + s * 0.26, cy - s * 0.06, cx + s * 0.20, cy + s * 0.28, cx, cy + s * 0.30);
    ctx.bezierCurveTo(cx - s * 0.20, cy + s * 0.28, cx - s * 0.26, cy - s * 0.06, cx, cy - s * 0.06);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.terraDark, s * 0.012);
    ctx.stroke();
    // seeds
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    var seeds = [[-0.10,0.02],[0.04,0.04],[0.14,0.02],[-0.14,0.10],[0.00,0.10],[0.12,0.12],
                 [-0.08,0.18],[0.06,0.18],[-0.02,0.24]];
    for (var i = 0; i < seeds.length; i++) {
        ctx.beginPath();
        ctx.ellipse(cx + s * seeds[i][0], cy + s * seeds[i][1], s * 0.012, s * 0.018, 0.4, 0, Math.PI * 2);
        ctx.fill();
    }
    // calyx (leaves)
    ctx.fillStyle = C.PALETTE.sageDeep;
    for (var k = -2; k <= 2; k++) {
        ctx.beginPath();
        ctx.moveTo(cx, cy - s * 0.10);
        ctx.lineTo(cx + k * s * 0.05 - s * 0.04, cy - s * 0.22);
        ctx.lineTo(cx + k * s * 0.05 + s * 0.04, cy - s * 0.22);
        ctx.closePath();
        ctx.fill();
    }
}

// SPOTIFY — pulse arcs (no logo) inside cream tile
function drawSpotify(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // three concentric arcs
    ctx.save();
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineCap = "round";
    [[0.10, 0.030], [0.16, 0.024], [0.22, 0.018]].forEach(function(arc) {
        ctx.lineWidth = s * arc[1];
        ctx.beginPath();
        ctx.arc(cx - s * 0.04, cy - s * 0.02, s * arc[0], Math.PI * 0.12, Math.PI * 0.88);
        ctx.stroke();
    });
    ctx.restore();
}

// DEADBEEF — minimal coffin-shape with audio bars
function drawDeadbeef(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // coffin shape
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.18);
    ctx.lineTo(s * 0.70, s * 0.18);
    ctx.lineTo(s * 0.80, s * 0.34);
    ctx.lineTo(s * 0.70, s * 0.82);
    ctx.lineTo(s * 0.30, s * 0.82);
    ctx.lineTo(s * 0.20, s * 0.34);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    // bars
    ctx.fillStyle = accent || C.PALETTE.gold;
    var heights = [0.10, 0.18, 0.26, 0.16, 0.22];
    for (var i = 0; i < heights.length; i++) {
        ctx.fillRect(s * (0.32 + i * 0.075), s * 0.62 - s * heights[i], s * 0.06, s * heights[i]);
    }
    // cross inscription
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.475, s * 0.26, s * 0.05, s * 0.16);
    ctx.fillRect(s * 0.43, s * 0.30, s * 0.14, s * 0.04);
}

// AUDACITY — sound waveform on cream
function drawAudacity(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // headphone arc
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.52, s * 0.26, Math.PI, 0);
    C.setStroke(ctx, C.PALETTE.terraDark, s * 0.040);
    ctx.stroke();
    // ear cups
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillRect(s * 0.20, s * 0.50, s * 0.10, s * 0.18);
    ctx.fillRect(s * 0.70, s * 0.50, s * 0.10, s * 0.18);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.20, s * 0.50, s * 0.10, s * 0.18);
    ctx.strokeRect(s * 0.70, s * 0.50, s * 0.10, s * 0.18);
    // waveform between
    ctx.save();
    ctx.translate(s * 0.34, s * 0.62);
    ctx.fillStyle = accent || C.PALETTE.gold;
    var amps = [0.06, 0.10, 0.04, 0.12, 0.07, 0.14, 0.05, 0.10, 0.06];
    for (var i = 0; i < amps.length; i++) {
        ctx.fillRect(i * s * 0.035, -s * amps[i] / 2, s * 0.020, s * amps[i]);
    }
    ctx.restore();
}

// ARDOUR — channel-strip console with bowed strings ornament
function drawArdour(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // dark console body
    ctx.fillStyle = "#23211a";
    C.roundRectPath(ctx, s * 0.16, s * 0.20, s * 0.68, s * 0.60, s * 0.03);
    ctx.fill();
    // 5 channel strips (faders)
    for (var i = 0; i < 5; i++) {
        var x = s * (0.22 + i * 0.13);
        ctx.fillStyle = "#3b3a30";
        ctx.fillRect(x, s * 0.30, s * 0.06, s * 0.40);
        // knob at top
        ctx.beginPath();
        ctx.arc(x + s * 0.03, s * 0.26, s * 0.022, 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fill();
        // fader cap
        var v = 0.40 + 0.30 * (i % 3) / 2;
        ctx.fillStyle = C.PALETTE.terra;
        ctx.fillRect(x - s * 0.006, s * (0.30 + v * 0.36), s * 0.072, s * 0.04);
    }
    // VU meter line
    ctx.fillStyle = "rgba(230,199,133,0.6)";
    ctx.fillRect(s * 0.20, s * 0.74, s * 0.60, s * 0.04);
}

// LMMS — piano keys vertical with wave overlay
function drawLMMS(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // keyboard frame
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.18, s * 0.20, s * 0.64, s * 0.60);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.strokeRect(s * 0.18, s * 0.20, s * 0.64, s * 0.60);
    // black keys
    ctx.fillStyle = C.PALETTE.ink;
    var blackPositions = [0.10, 0.22, 0.42, 0.54, 0.66];  // c#, d#, f#, g#, a#
    for (var i = 0; i < blackPositions.length; i++) {
        ctx.fillRect(s * (0.18 + blackPositions[i] * 0.64), s * 0.20, s * 0.08, s * 0.36);
    }
    // white-key dividers
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    for (var j = 1; j < 7; j++) {
        ctx.beginPath();
        ctx.moveTo(s * (0.18 + j * 0.64 / 7), s * 0.56);
        ctx.lineTo(s * (0.18 + j * 0.64 / 7), s * 0.80);
        ctx.stroke();
    }
    // gold waveform overlay
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    for (var x = 0.18; x <= 0.82; x += 0.02) {
        var y = 0.50 + Math.sin(x * 30) * 0.05;
        if (x === 0.18) ctx.moveTo(s * x, s * y);
        else ctx.lineTo(s * x, s * y);
    }
    ctx.stroke();
}

// MIXXX — DJ turntable
function drawMixxx(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // platter
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.32, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    // grooves
    ctx.save();
    for (var i = 0; i < 6; i++) {
        ctx.beginPath();
        ctx.arc(cx, cy, s * (0.10 + i * 0.038), 0, Math.PI * 2);
        C.setStroke(ctx, "rgba(230,199,133,0.3)", s * 0.005);
        ctx.stroke();
    }
    ctx.restore();
    // label
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    // spindle
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.018, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    // tonearm
    ctx.save();
    ctx.strokeStyle = C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.020;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.84, s * 0.20);
    ctx.lineTo(s * 0.58, s * 0.46);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(s * 0.86, s * 0.18, s * 0.030, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.fill();
    ctx.restore();
}

// HYDROGEN — drum hex pad grid
function drawHydrogen(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // 4x4 pad grid
    for (var r = 0; r < 4; r++) {
        for (var c = 0; c < 4; c++) {
            ctx.fillStyle = (r + c) % 2 ? C.PALETTE.plumDeep : C.PALETTE.plum;
            ctx.fillRect(s * (0.16 + c * 0.17), s * (0.16 + r * 0.17), s * 0.14, s * 0.14);
            C.setStroke(ctx, C.PALETTE.gold, s * 0.006);
            ctx.strokeRect(s * (0.16 + c * 0.17), s * (0.16 + r * 0.17), s * 0.14, s * 0.14);
        }
    }
    // active pads (lit)
    var lit = [[0,0],[1,2],[2,1],[3,3]];
    for (var i = 0; i < lit.length; i++) {
        var lc = lit[i];
        ctx.fillStyle = accent || C.PALETTE.goldHi;
        ctx.fillRect(s * (0.16 + lc[1] * 0.17), s * (0.16 + lc[0] * 0.17), s * 0.14, s * 0.14);
    }
}

// ROSEGARDEN — rose motif on a music staff
function drawRosegarden(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // staff lines
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.006;
    for (var i = 0; i < 5; i++) {
        ctx.beginPath();
        ctx.moveTo(s * 0.16, s * (0.32 + i * 0.06));
        ctx.lineTo(s * 0.84, s * (0.32 + i * 0.06));
        ctx.stroke();
    }
    // rose centred
    C.drawRosette(ctx, s * 0.5, s * 0.5, s * 0.16, 6, C.PALETTE.roseDeep, C.PALETTE.goldHi);
    // tiny leaves
    C.leafBead(ctx, s * 0.32, s * 0.66, s * 0.10, -0.5, C.PALETTE.sageDeep);
    C.leafBead(ctx, s * 0.68, s * 0.66, s * 0.10, 0.5 + Math.PI, C.PALETTE.sageDeep);
}

// MUSESCORE — treble clef on staff
function drawMuseScore(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // staff lines
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.005;
    for (var i = 0; i < 5; i++) {
        ctx.beginPath();
        ctx.moveTo(s * 0.14, s * (0.32 + i * 0.06));
        ctx.lineTo(s * 0.86, s * (0.32 + i * 0.06));
        ctx.stroke();
    }
    // treble clef stylised
    ctx.save();
    ctx.translate(s * 0.42, s * 0.50);
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.028;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.28);
    ctx.bezierCurveTo(s * 0.10, -s * 0.20, s * 0.10, s * 0.10, 0, s * 0.10);
    ctx.bezierCurveTo(-s * 0.12, s * 0.10, -s * 0.12, -s * 0.04, 0, -s * 0.04);
    ctx.bezierCurveTo(s * 0.08, -s * 0.04, s * 0.06, s * 0.18, 0, s * 0.20);
    ctx.bezierCurveTo(-s * 0.08, s * 0.22, -s * 0.10, s * 0.30, 0, s * 0.34);
    ctx.stroke();
    ctx.restore();
    // a couple of notes
    [0.62, 0.74].forEach(function(x, i) {
        ctx.beginPath();
        ctx.ellipse(s * x, s * (0.50 + i * 0.06), s * 0.022, s * 0.018, -0.3, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.ink;
        ctx.fill();
        ctx.fillRect(s * (x + 0.018), s * (0.30 + i * 0.06), s * 0.004, s * 0.20);
    });
}

// REAPER — scythe blade
function drawReaper(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // shaft
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-0.3);
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(-s * 0.014, -s * 0.32, s * 0.028, s * 0.62);
    // blade
    ctx.fillStyle = "#dadde5";
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.32);
    ctx.quadraticCurveTo(s * 0.28, -s * 0.30, s * 0.30, -s * 0.06);
    ctx.quadraticCurveTo(s * 0.20, -s * 0.14, 0, -s * 0.18);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // edge highlight
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.010;
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.30);
    ctx.quadraticCurveTo(s * 0.20, -s * 0.20, s * 0.30, -s * 0.06);
    ctx.stroke();
    ctx.restore();
    // sound wave at base
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.010;
    ctx.beginPath();
    for (var x = 0.20; x <= 0.80; x += 0.03) {
        var y = 0.80 + Math.sin(x * 30) * 0.04;
        if (x === 0.20) ctx.moveTo(s * x, s * y); else ctx.lineTo(s * x, s * y);
    }
    ctx.stroke();
}

// BITWIG — colour-grid synth
function drawBitwig(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    var cols = [C.PALETTE.terra, accent || C.PALETTE.gold, C.PALETTE.sageDeep, C.PALETTE.tealDeep];
    for (var r = 0; r < 3; r++) {
        for (var c = 0; c < 3; c++) {
            var col = cols[(r * 3 + c) % cols.length];
            ctx.fillStyle = col;
            ctx.fillRect(s * (0.20 + c * 0.21), s * (0.20 + r * 0.21), s * 0.18, s * 0.18);
        }
    }
    // central play
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.moveTo(s * 0.44, s * 0.42);
    ctx.lineTo(s * 0.60, s * 0.50);
    ctx.lineTo(s * 0.44, s * 0.58);
    ctx.closePath();
    ctx.fill();
}

// KDENLIVE — film strip with K
function drawKdenlive(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.14, s * 0.26, s * 0.72, s * 0.48);
    // sprocket
    ctx.fillStyle = C.PALETTE.bgCream;
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * (0.18 + i * 0.18), s * 0.20, s * 0.10, s * 0.06);
        ctx.fillRect(s * (0.18 + i * 0.18), s * 0.74, s * 0.10, s * 0.06);
    }
    // K monogram inside frame
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fillRect(s * 0.34, s * 0.34, s * 0.07, s * 0.32);
    ctx.beginPath();
    ctx.moveTo(s * 0.41, s * 0.50);
    ctx.lineTo(s * 0.62, s * 0.34);
    ctx.lineTo(s * 0.66, s * 0.34);
    ctx.lineTo(s * 0.45, s * 0.52);
    ctx.lineTo(s * 0.66, s * 0.66);
    ctx.lineTo(s * 0.62, s * 0.66);
    ctx.closePath();
    ctx.fill();
}

// OPENSHOT — camera lens
function drawOpenShot(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // lens body
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.32, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    // aperture blades
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 6; i++) {
        ctx.save();
        ctx.rotate(i * Math.PI / 3);
        ctx.fillStyle = i % 2 ? C.PALETTE.gold : C.PALETTE.goldDark;
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(s * 0.22, -s * 0.08);
        ctx.lineTo(s * 0.22, s * 0.08);
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
    ctx.restore();
    // central iris
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.06, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx - s * 0.02, cy - s * 0.02, s * 0.022, 0, Math.PI * 2);
    ctx.fillStyle = "#fff";
    ctx.fill();
}

// SHOTCUT — clapperboard slate
function drawShotcut(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // bottom slate
    ctx.fillStyle = "#2a221a";
    ctx.fillRect(s * 0.16, s * 0.36, s * 0.68, s * 0.44);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.strokeRect(s * 0.16, s * 0.36, s * 0.68, s * 0.44);
    // clapper top
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.moveTo(s * 0.14, s * 0.34);
    ctx.lineTo(s * 0.86, s * 0.16);
    ctx.lineTo(s * 0.90, s * 0.26);
    ctx.lineTo(s * 0.18, s * 0.44);
    ctx.closePath();
    ctx.fill();
    // stripes on clapper
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    for (var i = 0; i < 5; i++) {
        ctx.save();
        ctx.translate(s * (0.20 + i * 0.14), s * (0.32 - i * 0.04));
        ctx.rotate(-0.25);
        ctx.fillRect(0, 0, s * 0.07, s * 0.08);
        ctx.restore();
    }
    // scene text
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.font = "700 " + Math.round(s * 0.10) + "px monospace";
    ctx.fillText("SCN 1", s * 0.22, s * 0.58);
}

// DAVINCI RESOLVE — colour-grade palette
function drawResolve(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // three overlapping color circles
    ctx.globalAlpha = 0.85;
    ctx.beginPath();
    ctx.arc(cx - s * 0.10, cy - s * 0.06, s * 0.16, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx + s * 0.10, cy - s * 0.06, s * 0.16, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx, cy + s * 0.10, s * 0.16, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.gold;
    ctx.fill();
    ctx.globalAlpha = 1;
    // hub
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
}

// PITIVI — playhead caret
function drawPitivi(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // timeline tracks
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.14, s * 0.32, s * 0.72, s * 0.12);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.fillRect(s * 0.14, s * 0.48, s * 0.72, s * 0.12);
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.fillRect(s * 0.14, s * 0.64, s * 0.72, s * 0.12);
    // playhead
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.20);
    ctx.lineTo(s * 0.56, s * 0.30);
    ctx.lineTo(s * 0.44, s * 0.30);
    ctx.closePath();
    ctx.fill();
    ctx.fillRect(s * 0.49, s * 0.30, s * 0.02, s * 0.50);
}

// FLOWBLADE — flowing horizontal blade
function drawFlowblade(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // 3 horizontal streams
    var cols = [C.PALETTE.teal, C.PALETTE.terra, C.PALETTE.sageDeep];
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.moveTo(s * 0.12, s * (0.32 + i * 0.12));
        ctx.bezierCurveTo(s * 0.30, s * (0.42 + i * 0.10), s * 0.70, s * (0.22 + i * 0.10), s * 0.88, s * (0.32 + i * 0.12));
        ctx.lineTo(s * 0.88, s * (0.40 + i * 0.12));
        ctx.bezierCurveTo(s * 0.70, s * (0.30 + i * 0.10), s * 0.30, s * (0.50 + i * 0.10), s * 0.12, s * (0.40 + i * 0.12));
        ctx.closePath();
        ctx.fillStyle = cols[i];
        ctx.fill();
    }
    // blade across
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(0.2);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fillRect(-s * 0.34, -s * 0.020, s * 0.68, s * 0.040);
    ctx.restore();
}

// OBS — camera/cam aperture with REC badge
function drawOBS(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // ring
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.020);
    ctx.stroke();
    // 3 dots around (rotation)
    for (var i = 0; i < 3; i++) {
        var a = i / 3 * Math.PI * 2 - Math.PI / 2;
        ctx.beginPath();
        ctx.arc(cx + Math.cos(a) * s * 0.30, cy + Math.sin(a) * s * 0.30, s * 0.026, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.ink;
        ctx.fill();
    }
    // REC dot
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.12, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fill();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.08) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("REC", cx, cy);
}

// OLIVE — olive branch
function drawOlive(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // branch
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-Math.PI / 4);
    ctx.strokeStyle = C.PALETTE.sageDark;
    ctx.lineWidth = s * 0.012;
    ctx.beginPath();
    ctx.moveTo(-s * 0.26, 0);
    ctx.lineTo(s * 0.26, 0);
    ctx.stroke();
    // leaves
    for (var i = -3; i <= 3; i++) {
        if (i === 0) continue;
        C.leafBead(ctx, i * s * 0.08, i % 2 ? -s * 0.04 : s * 0.04, s * 0.12,
                   i % 2 ? -0.5 : 0.5, C.PALETTE.sageDeep);
    }
    // olives
    [-0.16, 0.06, 0.20].forEach(function(x, idx) {
        ctx.beginPath();
        ctx.arc(x, idx % 2 ? -s * 0.02 : s * 0.02, s * 0.018, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.plumDeep;
        ctx.fill();
    });
    ctx.restore();
}

// HANDBRAKE — pineapple handle (Mucha rendition of the cocktail)
function drawHandBrake(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5;
    // pineapple body
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.18, s * 0.36);
    ctx.lineTo(cx + s * 0.18, s * 0.36);
    ctx.lineTo(cx + s * 0.22, s * 0.74);
    ctx.bezierCurveTo(cx + s * 0.18, s * 0.86, cx - s * 0.18, s * 0.86, cx - s * 0.22, s * 0.74);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // diamond cross-hatch
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.18, s * 0.36);
    ctx.lineTo(cx + s * 0.18, s * 0.36);
    ctx.lineTo(cx + s * 0.22, s * 0.74);
    ctx.bezierCurveTo(cx + s * 0.18, s * 0.86, cx - s * 0.18, s * 0.86, cx - s * 0.22, s * 0.74);
    ctx.closePath();
    ctx.clip();
    ctx.strokeStyle = C.PALETTE.terraDark;
    ctx.lineWidth = s * 0.006;
    for (var i = -8; i < 8; i++) {
        ctx.beginPath();
        ctx.moveTo(cx + i * s * 0.06 - s * 0.20, s * 0.30);
        ctx.lineTo(cx + i * s * 0.06 + s * 0.20, s * 0.90);
        ctx.stroke();
        ctx.beginPath();
        ctx.moveTo(cx + i * s * 0.06 + s * 0.20, s * 0.30);
        ctx.lineTo(cx + i * s * 0.06 - s * 0.20, s * 0.90);
        ctx.stroke();
    }
    ctx.restore();
    // leaves on top
    ctx.fillStyle = C.PALETTE.sageDark;
    for (var k = -2; k <= 2; k++) {
        ctx.beginPath();
        ctx.moveTo(cx, s * 0.36);
        ctx.lineTo(cx + k * s * 0.06 - s * 0.03, s * 0.20);
        ctx.lineTo(cx + k * s * 0.06 + s * 0.03, s * 0.20);
        ctx.closePath();
        ctx.fill();
    }
}

// AVIDEMUX — split film frame
function drawAvidemux(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(s * 0.14, s * 0.26, s * 0.36, s * 0.48);
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.50, s * 0.26, s * 0.36, s * 0.48);
    // play
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.38);
    ctx.lineTo(s * 0.40, s * 0.50);
    ctx.lineTo(s * 0.22, s * 0.62);
    ctx.closePath();
    ctx.fill();
    // pause bars
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fillRect(s * 0.59, s * 0.38, s * 0.05, s * 0.24);
    ctx.fillRect(s * 0.69, s * 0.38, s * 0.05, s * 0.24);
    // scissors cut symbol between
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.012;
    ctx.setLineDash([s * 0.020, s * 0.020]);
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.20);
    ctx.lineTo(s * 0.50, s * 0.80);
    ctx.stroke();
    ctx.setLineDash([]);
}

// GENERIC MUSIC — eighth note on a halo
function drawGenericMusic(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    C.drawHalo(ctx, s);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.ellipse(s * 0.42, s * 0.66, s * 0.10, s * 0.07, -0.3, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillRect(s * 0.50, s * 0.30, s * 0.04, s * 0.36);
    ctx.beginPath();
    ctx.moveTo(s * 0.54, s * 0.30);
    ctx.quadraticCurveTo(s * 0.72, s * 0.36, s * 0.66, s * 0.50);
    ctx.lineTo(s * 0.54, s * 0.46);
    ctx.closePath();
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
}

// GENERIC VIDEO — film strip
function drawGenericVideo(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(s * 0.14, s * 0.22, s * 0.72, s * 0.56);
    for (var i = 0; i < 4; i++) {
        ctx.fillStyle = C.PALETTE.bgCream;
        ctx.fillRect(s * (0.20 + i * 0.16), s * 0.26, s * 0.10, s * 0.06);
        ctx.fillRect(s * (0.20 + i * 0.16), s * 0.68, s * 0.10, s * 0.06);
    }
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.40, s * 0.36);
    ctx.lineTo(s * 0.64, s * 0.50);
    ctx.lineTo(s * 0.40, s * 0.64);
    ctx.closePath();
    ctx.fill();
}
