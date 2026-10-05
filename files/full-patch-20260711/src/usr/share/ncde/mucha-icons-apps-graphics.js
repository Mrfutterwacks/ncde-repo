// mucha-icons-apps-graphics.js — graphics, photo, CAD, 3D.
.pragma library
.import "mucha-icons-core.js" as C

// GIMP — paint brush with bristle splay
function drawGimp(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-Math.PI / 6);
    // handle
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(-s * 0.04, -s * 0.30, s * 0.08, s * 0.34);
    // ferrule
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(-s * 0.06, s * 0.04, s * 0.12, s * 0.08);
    // bristles fanning
    ctx.fillStyle = C.PALETTE.terra;
    ctx.beginPath();
    ctx.moveTo(-s * 0.06, s * 0.12);
    ctx.lineTo(s * 0.06, s * 0.12);
    ctx.lineTo(s * 0.18, s * 0.34);
    ctx.lineTo(-s * 0.18, s * 0.34);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // splay strands
    for (var i = -3; i <= 3; i++) {
        ctx.beginPath();
        ctx.moveTo(i * s * 0.020, s * 0.12);
        ctx.lineTo(i * s * 0.040, s * 0.34);
        C.setStroke(ctx, C.PALETTE.terraDark, s * 0.006);
        ctx.stroke();
    }
    ctx.restore();
    // paint splat on tile
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.arc(s * 0.74, s * 0.78, s * 0.05, 0, Math.PI * 2);
    ctx.fill();
    ctx.beginPath();
    ctx.arc(s * 0.80, s * 0.72, s * 0.025, 0, Math.PI * 2);
    ctx.fill();
}

// KRITA — paint palette with brush
function drawKrita(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // palette shape
    ctx.fillStyle = "#cfa376";
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.36);
    ctx.bezierCurveTo(s * 0.10, s * 0.60, s * 0.30, s * 0.84, s * 0.56, s * 0.80);
    ctx.bezierCurveTo(s * 0.78, s * 0.76, s * 0.88, s * 0.56, s * 0.78, s * 0.36);
    ctx.bezierCurveTo(s * 0.66, s * 0.20, s * 0.32, s * 0.20, s * 0.20, s * 0.36);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // thumb hole
    ctx.beginPath();
    ctx.arc(s * 0.70, s * 0.50, s * 0.06, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCream;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    // paint dabs
    [[0.32, 0.36, C.PALETTE.terra],
     [0.42, 0.34, accent || C.PALETTE.gold],
     [0.52, 0.36, C.PALETTE.sageDeep],
     [0.34, 0.50, C.PALETTE.indigoDeep],
     [0.44, 0.52, C.PALETTE.roseDeep]].forEach(function(d) {
        ctx.beginPath();
        ctx.arc(s * d[0], s * d[1], s * 0.04, 0, Math.PI * 2);
        ctx.fillStyle = d[2];
        ctx.fill();
    });
    // small stylus
    ctx.save();
    ctx.translate(s * 0.62, s * 0.62);
    ctx.rotate(-0.6);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(-s * 0.012, -s * 0.20, s * 0.024, s * 0.20);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(-s * 0.012, 0);
    ctx.lineTo(s * 0.012, 0);
    ctx.lineTo(0, s * 0.04);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

// INKSCAPE — calligraphic nib
function drawInkscape(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-Math.PI / 8);
    // nib body
    var g = ctx.createLinearGradient(0, -s * 0.30, 0, s * 0.30);
    g.addColorStop(0, "#e6e8ec"); g.addColorStop(1, accent || C.PALETTE.gold);
    ctx.fillStyle = g;
    ctx.beginPath();
    ctx.moveTo(-s * 0.10, -s * 0.30);
    ctx.lineTo(s * 0.10, -s * 0.30);
    ctx.lineTo(s * 0.06, s * 0.20);
    ctx.lineTo(0, s * 0.32);
    ctx.lineTo(-s * 0.06, s * 0.20);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // slit & vent hole
    ctx.beginPath();
    ctx.arc(0, -s * 0.04, s * 0.025, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    ctx.fillRect(-s * 0.006, -s * 0.04, s * 0.012, s * 0.34);
    ctx.restore();
    // ink drop
    ctx.beginPath();
    ctx.moveTo(s * 0.66, s * 0.76);
    ctx.bezierCurveTo(s * 0.76, s * 0.84, s * 0.58, s * 0.86, s * 0.62, s * 0.78);
    ctx.closePath();
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fill();
}

// PINTA — small palette dab
function drawPinta(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // colour wheel ring
    var cols = [C.PALETTE.terra, accent || C.PALETTE.gold, C.PALETTE.sageDeep,
                C.PALETTE.tealDeep, C.PALETTE.indigoDeep, C.PALETTE.plumDeep];
    for (var i = 0; i < 6; i++) {
        ctx.beginPath();
        ctx.moveTo(cx, cy);
        ctx.arc(cx, cy, s * 0.28, (i / 6) * Math.PI * 2, ((i + 1) / 6) * Math.PI * 2);
        ctx.closePath();
        ctx.fillStyle = cols[i];
        ctx.fill();
    }
    // dividers
    ctx.strokeStyle = C.PALETTE.bgCream;
    ctx.lineWidth = s * 0.010;
    for (var k = 0; k < 6; k++) {
        var a = k / 6 * Math.PI * 2;
        ctx.beginPath();
        ctx.moveTo(cx, cy);
        ctx.lineTo(cx + Math.cos(a) * s * 0.28, cy + Math.sin(a) * s * 0.28);
        ctx.stroke();
    }
    // centre droplet
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.08, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
}

// DARKTABLE — crescent moon over a darkroom tray
function drawDarktable(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // dark tile
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.014);
    ctx.stroke();
    // moon
    ctx.beginPath();
    ctx.arc(cx + s * 0.04, cy - s * 0.04, s * 0.18, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx + s * 0.10, cy - s * 0.04, s * 0.18, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fill();
    // stars
    [[0.30, 0.30], [0.72, 0.32], [0.30, 0.66], [0.70, 0.66]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.012, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.fill();
    });
}

// RAWTHERAPEE — apothecary flask
function drawRawTherapee(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5;
    // flask body
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.06, s * 0.22);
    ctx.lineTo(cx + s * 0.06, s * 0.22);
    ctx.lineTo(cx + s * 0.06, s * 0.40);
    ctx.lineTo(cx + s * 0.22, s * 0.74);
    ctx.bezierCurveTo(cx + s * 0.24, s * 0.84, cx - s * 0.24, s * 0.84, cx - s * 0.22, s * 0.74);
    ctx.lineTo(cx - s * 0.06, s * 0.40);
    ctx.closePath();
    ctx.fillStyle = "rgba(143,166,138,0.35)";
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // liquid
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.18, s * 0.62);
    ctx.lineTo(cx + s * 0.18, s * 0.62);
    ctx.lineTo(cx + s * 0.22, s * 0.74);
    ctx.bezierCurveTo(cx + s * 0.24, s * 0.84, cx - s * 0.24, s * 0.84, cx - s * 0.22, s * 0.74);
    ctx.closePath();
    ctx.clip();
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.22, s * 0.62, s * 0.56, s * 0.22);
    ctx.restore();
    // bubbles
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    [[0.46, 0.70], [0.52, 0.74], [0.50, 0.78]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.018, 0, Math.PI * 2);
        ctx.fill();
    });
    // stopper
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(cx - s * 0.08, s * 0.16, s * 0.16, s * 0.08);
}

// DIGIKAM — camera shutter
function drawDigikam(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // camera body
    ctx.fillStyle = "#23211a";
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    // lens
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.56, s * 0.18, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.018);
    ctx.stroke();
    // aperture
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.56, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fill();
    // flash
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.18, s * 0.22, s * 0.10, s * 0.10);
    // viewfinder hump
    ctx.fillStyle = "#23211a";
    ctx.fillRect(s * 0.38, s * 0.22, s * 0.24, s * 0.10);
}

// SHOTWELL — photo frame with sprig
function drawShotwell(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // frame
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.14, s * 0.20, s * 0.72, s * 0.60);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.20, s * 0.26, s * 0.60, s * 0.48);
    // landscape photo
    // sky
    ctx.fillStyle = "#a5b9c8";
    ctx.fillRect(s * 0.20, s * 0.26, s * 0.60, s * 0.30);
    // sun
    ctx.beginPath();
    ctx.arc(s * 0.32, s * 0.36, s * 0.06, 0, Math.PI * 2);
    ctx.fillStyle = "#f6c463";
    ctx.fill();
    // hills
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.56);
    ctx.bezierCurveTo(s * 0.34, s * 0.42, s * 0.50, s * 0.50, s * 0.62, s * 0.46);
    ctx.bezierCurveTo(s * 0.72, s * 0.44, s * 0.80, s * 0.48, s * 0.80, s * 0.56);
    ctx.lineTo(s * 0.80, s * 0.74);
    ctx.lineTo(s * 0.20, s * 0.74);
    ctx.closePath();
    ctx.fill();
}

// GTHUMB — film grid 4-up
function drawGthumb(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    var cols = [C.PALETTE.teal, accent || C.PALETTE.gold, C.PALETTE.sageDeep, C.PALETTE.terra];
    for (var i = 0; i < 4; i++) {
        var x = s * (0.18 + (i % 2) * 0.34);
        var y = s * (0.18 + (i >> 1) * 0.34);
        ctx.fillStyle = cols[i];
        ctx.fillRect(x, y, s * 0.30, s * 0.30);
        C.setStroke(ctx, C.PALETTE.bgCreamHi, s * 0.014);
        ctx.strokeRect(x, y, s * 0.30, s * 0.30);
    }
}

// GWENVIEW — magnifier over a photo
function drawGwenview(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // photo
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.fillRect(s * 0.14, s * 0.24, s * 0.50, s * 0.40);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.14, s * 0.24, s * 0.50, s * 0.40);
    // sun on photo
    ctx.beginPath();
    ctx.arc(s * 0.28, s * 0.38, s * 0.05, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    // magnifier
    ctx.save();
    ctx.beginPath();
    ctx.arc(s * 0.62, s * 0.58, s * 0.16, 0, Math.PI * 2);
    ctx.fillStyle = "rgba(255,255,255,0.4)";
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.022);
    ctx.stroke();
    // handle
    ctx.beginPath();
    ctx.moveTo(s * 0.74, s * 0.70);
    ctx.lineTo(s * 0.86, s * 0.86);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.030);
    ctx.stroke();
    ctx.restore();
}

// NOMACS — folio paper photo viewer
function drawNomacs(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // 3 stacked photos
    [[0.26, 0.20, -0.10], [0.30, 0.26, 0.06], [0.34, 0.32, -0.04]].forEach(function(p, i) {
        ctx.save();
        ctx.translate(s * 0.5, s * 0.5);
        ctx.rotate(p[2]);
        ctx.fillStyle = i === 2 ? C.PALETTE.bgCreamHi : (i === 1 ? "#dccfa9" : "#b89e6d");
        ctx.fillRect(-s * p[0], -s * p[1], s * p[0] * 2, s * p[1] * 2);
        C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
        ctx.strokeRect(-s * p[0], -s * p[1], s * p[0] * 2, s * p[1] * 2);
        ctx.restore();
    });
    // moon over top image
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-0.04);
    ctx.beginPath();
    ctx.arc(s * 0.10, -s * 0.18, s * 0.06, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    ctx.restore();
}

// EOG — eye in a halo (Eye Of Gnome)
function drawEOG(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // eye almond
    ctx.beginPath();
    ctx.moveTo(s * 0.18, cy);
    ctx.bezierCurveTo(s * 0.30, s * 0.22, s * 0.70, s * 0.22, s * 0.82, cy);
    ctx.bezierCurveTo(s * 0.70, s * 0.78, s * 0.30, s * 0.78, s * 0.18, cy);
    ctx.closePath();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // iris
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.13, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    // pupil
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.05, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    // glint
    ctx.beginPath();
    ctx.arc(cx - s * 0.03, cy - s * 0.03, s * 0.020, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
}

// FEH — tiny stylised eye
function drawFeh(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // monospace "feh" command-style
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.18) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("feh", cx, cy - s * 0.08);
    // small image preview rectangle
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.30, s * 0.56, s * 0.40, s * 0.20);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.76);
    ctx.lineTo(s * 0.42, s * 0.62);
    ctx.lineTo(s * 0.54, s * 0.70);
    ctx.lineTo(s * 0.62, s * 0.64);
    ctx.lineTo(s * 0.70, s * 0.76);
    ctx.closePath();
    ctx.fill();
}

// BLENDER — geometric primitive triad (cube + sphere + cone abstract)
function drawBlender(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // cube
    ctx.save();
    ctx.translate(s * 0.34, s * 0.60);
    ctx.fillStyle = C.PALETTE.terra;
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.10);
    ctx.lineTo(s * 0.10, -s * 0.05);
    ctx.lineTo(s * 0.10, s * 0.10);
    ctx.lineTo(0, s * 0.15);
    ctx.lineTo(-s * 0.10, s * 0.10);
    ctx.lineTo(-s * 0.10, -s * 0.05);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    // face highlight
    ctx.fillStyle = "rgba(255,235,180,0.4)";
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.10);
    ctx.lineTo(s * 0.10, -s * 0.05);
    ctx.lineTo(s * 0.10, s * 0.10);
    ctx.lineTo(0, s * 0.05);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
    // sphere
    ctx.beginPath();
    ctx.arc(s * 0.66, s * 0.40, s * 0.12, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, s * 0.62, s * 0.36, s * 0.02, s * 0.12,
        [[0, "#f6e4b6"], [1, accent || C.PALETTE.gold]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // cone
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.32, s * 0.40);
    ctx.lineTo(s * 0.20, s * 0.20);
    ctx.lineTo(s * 0.44, s * 0.20);
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.ellipse(s * 0.32, s * 0.40, s * 0.12, s * 0.04, 0, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
}

// FREECAD — calipers crossed
function drawFreeCAD(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // base bar
    ctx.fillStyle = "#9b9bb0";
    ctx.fillRect(s * 0.14, s * 0.42, s * 0.72, s * 0.10);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.14, s * 0.42, s * 0.72, s * 0.10);
    // jaws
    ctx.fillStyle = "#7a7e90";
    ctx.fillRect(s * 0.14, s * 0.30, s * 0.10, s * 0.20);
    ctx.fillRect(s * 0.46, s * 0.30, s * 0.10, s * 0.20);
    // tick marks
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 10; i++) {
        ctx.fillRect(s * (0.18 + i * 0.06), s * 0.52, s * 0.005, s * (i % 5 === 0 ? 0.08 : 0.05));
    }
    // measurement readout
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fillRect(s * 0.60, s * 0.66, s * 0.24, s * 0.10);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.07) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("42.0", s * 0.72, s * 0.71);
}

// OPENSCAD — wireframe cube
function drawOpenSCAD(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.strokeStyle = accent || C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.014;
    ctx.lineCap = "round";
    // 3D wireframe
    var p = [
        [-0.20, -0.10], [0.20, -0.10], [0.30, 0.00], [-0.10, 0.00], // back face
        [-0.20, 0.10], [0.20, 0.10], [0.30, 0.20], [-0.10, 0.20]    // front face
    ];
    function l(a, b) {
        ctx.beginPath();
        ctx.moveTo(p[a][0] * s, p[a][1] * s);
        ctx.lineTo(p[b][0] * s, p[b][1] * s);
        ctx.stroke();
    }
    l(0,1); l(1,2); l(2,3); l(3,0);
    l(4,5); l(5,6); l(6,7); l(7,4);
    l(0,4); l(1,5); l(2,6); l(3,7);
    ctx.restore();
    // code line below
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "600 " + Math.round(s * 0.08) + "px monospace";
    ctx.textAlign = "center";
    ctx.fillText("cube();", s * 0.5, s * 0.82);
}

// LIBRECAD — drafting set-square
function drawLibreCAD(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // big triangle (45-45-90)
    ctx.fillStyle = "rgba(184,140,74,0.35)";
    ctx.beginPath();
    ctx.moveTo(s * 0.14, s * 0.80);
    ctx.lineTo(s * 0.86, s * 0.80);
    ctx.lineTo(s * 0.14, s * 0.20);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // inner cut-out
    ctx.fillStyle = C.PALETTE.bgCream;
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.72);
    ctx.lineTo(s * 0.74, s * 0.72);
    ctx.lineTo(s * 0.22, s * 0.30);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    // tick marks on hypotenuse
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.008;
    for (var i = 0; i < 6; i++) {
        var t = i / 5;
        var x = s * (0.14 + t * 0.72);
        var y = s * (0.80 - t * 0.60);
        ctx.beginPath();
        ctx.moveTo(x, y);
        ctx.lineTo(x + s * 0.02, y + s * 0.025);
        ctx.stroke();
    }
}

// KICAD — circuit board with traces
function drawKiCad(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // PCB
    ctx.fillStyle = C.PALETTE.sageDark;
    ctx.fillRect(s * 0.14, s * 0.18, s * 0.72, s * 0.64);
    // traces
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.014;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.30); ctx.lineTo(s * 0.50, s * 0.30); ctx.lineTo(s * 0.50, s * 0.50);
    ctx.lineTo(s * 0.78, s * 0.50);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.66); ctx.lineTo(s * 0.40, s * 0.66); ctx.lineTo(s * 0.40, s * 0.74);
    ctx.lineTo(s * 0.78, s * 0.74);
    ctx.stroke();
    // pads
    [[0.22,0.30],[0.50,0.30],[0.78,0.50],[0.22,0.66],[0.78,0.74]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.024, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    });
}

// SCRIBUS — typographic block
function drawScribus(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // page
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.18, s * 0.16, s * 0.64, s * 0.68);
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.strokeRect(s * 0.18, s * 0.16, s * 0.64, s * 0.68);
    // big drop cap "S"
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.font = "700 " + Math.round(s * 0.40) + "px 'Cinzel',serif";
    ctx.textBaseline = "top";
    ctx.fillText("S", s * 0.22, s * 0.20);
    // body text
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * 0.46, s * (0.24 + i * 0.05), s * 0.32, s * 0.014);
    }
    for (var j = 0; j < 4; j++) {
        ctx.fillRect(s * 0.22, s * (0.52 + j * 0.06), s * 0.56, s * 0.014);
    }
    // accent line
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.22, s * 0.74, s * 0.56, s * 0.020);
}

// MYPAINT — single brush stroke
function drawMyPaint(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    // bold curving brushstroke
    ctx.save();
    ctx.lineCap = "round";
    var g = ctx.createLinearGradient(s * 0.2, s * 0.2, s * 0.8, s * 0.8);
    g.addColorStop(0, C.PALETTE.terra);
    g.addColorStop(0.5, accent || C.PALETTE.gold);
    g.addColorStop(1, C.PALETTE.sageDeep);
    ctx.strokeStyle = g;
    ctx.lineWidth = s * 0.10;
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.30);
    ctx.bezierCurveTo(s * 0.40, s * 0.20, s * 0.66, s * 0.58, s * 0.78, s * 0.78);
    ctx.stroke();
    // bristle texture
    ctx.strokeStyle = "rgba(58,43,24,0.3)";
    ctx.lineWidth = s * 0.008;
    for (var i = 0; i < 5; i++) {
        ctx.beginPath();
        ctx.moveTo(s * 0.22, s * (0.28 + i * 0.01));
        ctx.bezierCurveTo(s * 0.40, s * 0.20, s * 0.66, s * 0.58, s * 0.78, s * (0.76 + i * 0.008));
        ctx.stroke();
    }
    ctx.restore();
}

// SYNFIG — animation curve
function drawSynfig(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // animation curve (bezier)
    ctx.strokeStyle = C.PALETTE.terraDark;
    ctx.lineWidth = s * 0.022;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.72);
    ctx.bezierCurveTo(s * 0.32, s * 0.18, s * 0.68, s * 0.82, s * 0.80, s * 0.28);
    ctx.stroke();
    // keyframe diamonds
    [[0.20, 0.72], [0.50, 0.50], [0.80, 0.28]].forEach(function(p) {
        ctx.save();
        ctx.translate(s * p[0], s * p[1]);
        ctx.rotate(Math.PI / 4);
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fillRect(-s * 0.030, -s * 0.030, s * 0.060, s * 0.060);
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.strokeRect(-s * 0.030, -s * 0.030, s * 0.060, s * 0.060);
        ctx.restore();
    });
    // control handles
    ctx.strokeStyle = C.PALETTE.sageDeep;
    ctx.lineWidth = s * 0.008;
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.72); ctx.lineTo(s * 0.32, s * 0.30);
    ctx.moveTo(s * 0.80, s * 0.28); ctx.lineTo(s * 0.68, s * 0.70);
    ctx.stroke();
}

// PENCIL2D — pencil
function drawPencil2D(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-Math.PI / 4);
    // body
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(-s * 0.05, -s * 0.26, s * 0.10, s * 0.40);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(-s * 0.05, -s * 0.26, s * 0.10, s * 0.40);
    // ferrule
    ctx.fillStyle = "#9b9bb0";
    ctx.fillRect(-s * 0.05, s * 0.10, s * 0.10, s * 0.05);
    // eraser
    ctx.fillStyle = "#d97a7a";
    ctx.fillRect(-s * 0.05, s * 0.15, s * 0.10, s * 0.08);
    // tip wood
    ctx.fillStyle = "#cfa376";
    ctx.beginPath();
    ctx.moveTo(-s * 0.05, -s * 0.26);
    ctx.lineTo(s * 0.05, -s * 0.26);
    ctx.lineTo(0, -s * 0.36);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // lead tip
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.moveTo(-s * 0.015, -s * 0.32);
    ctx.lineTo(s * 0.015, -s * 0.32);
    ctx.lineTo(0, -s * 0.36);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

// IMAGEMAGICK — wand
function drawImageMagick(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // wand
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-Math.PI / 5);
    ctx.fillStyle = "#23211a";
    ctx.fillRect(-s * 0.014, -s * 0.04, s * 0.028, s * 0.34);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(-s * 0.020, -s * 0.10, s * 0.040, s * 0.06);
    // star
    ctx.translate(0, -s * 0.20);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath();
    for (var i = 0; i < 10; i++) {
        var r = i % 2 ? s * 0.06 : s * 0.14;
        var a = i / 10 * Math.PI * 2 - Math.PI / 2;
        var x = Math.cos(a) * r, y = Math.sin(a) * r;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    ctx.restore();
}
