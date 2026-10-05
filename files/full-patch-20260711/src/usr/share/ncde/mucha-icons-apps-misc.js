// mucha-icons-apps-misc.js — notes, science, security, games, utilities.
.pragma library
.import "mucha-icons-core.js" as C

// JOPLIN — bound notebook with quill
function drawJoplin(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // cover
    ctx.fillStyle = C.PALETTE.indigoDeep;
    C.roundRectPath(ctx, s * 0.20, s * 0.16, s * 0.62, s * 0.68, s * 0.03);
    ctx.fill();
    // spine
    ctx.fillStyle = C.PALETTE.indigo;
    ctx.fillRect(s * 0.20, s * 0.16, s * 0.06, s * 0.68);
    // gilt label
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.32, s * 0.32, s * 0.40, s * 0.10);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.08) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("NOTES", s * 0.52, s * 0.37);
    // ribbon bookmark
    ctx.fillStyle = accent || C.PALETTE.terra;
    ctx.beginPath();
    ctx.moveTo(s * 0.66, s * 0.16);
    ctx.lineTo(s * 0.74, s * 0.16);
    ctx.lineTo(s * 0.74, s * 0.86);
    ctx.lineTo(s * 0.70, s * 0.78);
    ctx.lineTo(s * 0.66, s * 0.86);
    ctx.closePath();
    ctx.fill();
}

// OBSIDIAN — faceted crystal
function drawObsidian(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // crystal facets
    ctx.fillStyle = "#3b3a45";
    ctx.beginPath();
    ctx.moveTo(cx, cy - s * 0.28);
    ctx.lineTo(cx + s * 0.20, cy - s * 0.10);
    ctx.lineTo(cx + s * 0.12, cy + s * 0.26);
    ctx.lineTo(cx - s * 0.12, cy + s * 0.26);
    ctx.lineTo(cx - s * 0.20, cy - s * 0.10);
    ctx.closePath();
    ctx.fill();
    // highlight face
    ctx.fillStyle = "#5c5c70";
    ctx.beginPath();
    ctx.moveTo(cx, cy - s * 0.28);
    ctx.lineTo(cx + s * 0.20, cy - s * 0.10);
    ctx.lineTo(cx, cy + s * 0.04);
    ctx.closePath();
    ctx.fill();
    // gilt outline
    C.setStroke(ctx, accent || C.PALETTE.goldHi, s * 0.014);
    ctx.beginPath();
    ctx.moveTo(cx, cy - s * 0.28);
    ctx.lineTo(cx + s * 0.20, cy - s * 0.10);
    ctx.lineTo(cx + s * 0.12, cy + s * 0.26);
    ctx.lineTo(cx - s * 0.12, cy + s * 0.26);
    ctx.lineTo(cx - s * 0.20, cy - s * 0.10);
    ctx.closePath();
    ctx.moveTo(cx, cy - s * 0.28); ctx.lineTo(cx, cy + s * 0.04);
    ctx.moveTo(cx, cy + s * 0.04); ctx.lineTo(cx + s * 0.12, cy + s * 0.26);
    ctx.moveTo(cx, cy + s * 0.04); ctx.lineTo(cx - s * 0.12, cy + s * 0.26);
    ctx.moveTo(cx, cy + s * 0.04); ctx.lineTo(cx - s * 0.20, cy - s * 0.10);
    ctx.moveTo(cx, cy + s * 0.04); ctx.lineTo(cx + s * 0.20, cy - s * 0.10);
    ctx.stroke();
}

// LOGSEQ — graph nodes & links
function drawLogseq(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var nodes = [[0.30, 0.30], [0.70, 0.32], [0.22, 0.66], [0.50, 0.50], [0.78, 0.72]];
    // links
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.010;
    ctx.lineCap = "round";
    var edges = [[0,3],[1,3],[2,3],[3,4],[1,4]];
    edges.forEach(function(e) {
        ctx.beginPath();
        ctx.moveTo(s * nodes[e[0]][0], s * nodes[e[0]][1]);
        ctx.lineTo(s * nodes[e[1]][0], s * nodes[e[1]][1]);
        ctx.stroke();
    });
    // nodes
    var ncols = [C.PALETTE.terra, C.PALETTE.sageDeep, C.PALETTE.plumDeep, accent || C.PALETTE.gold, C.PALETTE.tealDeep];
    nodes.forEach(function(p, i) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], i === 3 ? s * 0.06 : s * 0.045, 0, Math.PI * 2);
        ctx.fillStyle = ncols[i];
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    });
}

// ZIM — gear+pencil
function drawZim(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // gear
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    for (var i = 0; i < 12; i++) {
        var a = i / 12 * Math.PI * 2;
        var r = i % 2 ? s * 0.24 : s * 0.18;
        var x = Math.cos(a) * r, y = Math.sin(a) * r;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.arc(0, 0, s * 0.07, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    ctx.restore();
    // pencil overlay
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-Math.PI / 4);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(-s * 0.020, -s * 0.04, s * 0.040, s * 0.22);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.moveTo(-s * 0.020, s * 0.18); ctx.lineTo(s * 0.020, s * 0.18); ctx.lineTo(0, s * 0.26);
    ctx.closePath(); ctx.fill();
    ctx.restore();
}

// CHERRYTREE — branching tree
function drawCherrytree(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // trunk
    ctx.strokeStyle = "#7a4a26";
    ctx.lineWidth = s * 0.034;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.84);
    ctx.lineTo(s * 0.50, s * 0.50);
    ctx.stroke();
    // branches
    ctx.lineWidth = s * 0.022;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.60); ctx.lineTo(s * 0.28, s * 0.46);
    ctx.moveTo(s * 0.50, s * 0.55); ctx.lineTo(s * 0.72, s * 0.42);
    ctx.moveTo(s * 0.50, s * 0.50); ctx.lineTo(s * 0.50, s * 0.30);
    ctx.stroke();
    // cherries
    var cherries = [[0.28, 0.46], [0.72, 0.42], [0.50, 0.30], [0.40, 0.40], [0.62, 0.34]];
    cherries.forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.05, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.terraDark;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
        // highlight
        ctx.beginPath();
        ctx.arc(s * (p[0] - 0.015), s * (p[1] - 0.015), s * 0.012, 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.goldHi;
        ctx.fill();
    });
}

// ANKI — flashcard
function drawAnki(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // back card
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-0.15);
    ctx.fillStyle = "#dccfa9";
    ctx.fillRect(-s * 0.30, -s * 0.20, s * 0.60, s * 0.40);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(-s * 0.30, -s * 0.20, s * 0.60, s * 0.40);
    ctx.restore();
    // front card
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(0.1);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(-s * 0.30, -s * 0.20, s * 0.60, s * 0.40);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(-s * 0.30, -s * 0.20, s * 0.60, s * 0.40);
    // ? letter
    ctx.fillStyle = accent || C.PALETTE.terraDark;
    ctx.font = "700 " + Math.round(s * 0.30) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("?", 0, 0);
    ctx.restore();
}

// KEEPASS / KEEPASSXC — ornate key
function drawKeePass(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.rotate(-Math.PI / 6);
    // bow (head loop)
    ctx.beginPath();
    ctx.arc(0, -s * 0.20, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // inner ring
    ctx.beginPath();
    ctx.arc(0, -s * 0.20, s * 0.05, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgPaper;
    ctx.fill();
    ctx.stroke();
    // shaft
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(-s * 0.020, -s * 0.10, s * 0.040, s * 0.34);
    // bit (teeth)
    ctx.fillRect(s * 0.020, s * 0.12, s * 0.06, s * 0.030);
    ctx.fillRect(s * 0.020, s * 0.18, s * 0.10, s * 0.030);
    ctx.restore();
}

// BITWARDEN — shield with check
function drawBitwarden(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"shield", accent:accent, glow:glow, ornament:false});
    var cx = s * 0.5, cy = s * 0.55;
    // shield inner fill
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.22);
    ctx.lineTo(s * 0.70, s * 0.22);
    ctx.lineTo(s * 0.70, s * 0.50);
    ctx.bezierCurveTo(s * 0.70, s * 0.72, s * 0.30, s * 0.72, s * 0.30, s * 0.50);
    ctx.closePath();
    ctx.fill();
    // checkmark
    ctx.strokeStyle = accent || C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.030;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.38, cy - s * 0.02);
    ctx.lineTo(s * 0.48, cy + s * 0.08);
    ctx.lineTo(s * 0.62, cy - s * 0.10);
    ctx.stroke();
}

// 1PASSWORD — keyhole padlock
function drawOnePassword(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // shackle
    ctx.beginPath();
    ctx.arc(cx, cy - s * 0.10, s * 0.14, Math.PI, 0);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.028);
    ctx.stroke();
    // body
    ctx.fillStyle = C.PALETTE.tealDeep;
    C.roundRectPath(ctx, cx - s * 0.20, cy - s * 0.08, s * 0.40, s * 0.34, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // "1" letter
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.18) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("1", cx, cy + s * 0.09);
}

// STELLARIUM — star with constellation
function drawStellarium(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // sky tile
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.5, s * 0.32, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fill();
    // constellation lines
    var stars = [[0.30,0.30],[0.50,0.34],[0.66,0.46],[0.60,0.62],[0.40,0.70]];
    ctx.strokeStyle = "rgba(230,199,133,0.5)";
    ctx.lineWidth = s * 0.006;
    ctx.beginPath();
    for (var i = 0; i < stars.length; i++) {
        if (i === 0) ctx.moveTo(s * stars[i][0], s * stars[i][1]);
        else ctx.lineTo(s * stars[i][0], s * stars[i][1]);
    }
    ctx.stroke();
    // stars
    stars.forEach(function(p, i) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * (i === 2 ? 0.024 : 0.014), 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.goldHi;
        ctx.fill();
    });
    // halo glints
    [0.5, 0.5].forEach(function(_) {});
    ctx.fillStyle = "rgba(255,235,180,0.4)";
    ctx.beginPath();
    ctx.arc(s * 0.66, s * 0.46, s * 0.05, 0, Math.PI * 2);
    ctx.fill();
}

// KSTARS — star cluster
function drawKStars(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.5, s * 0.32, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.fill();
    // star bursts
    var stars = [[0.4, 0.35, 0.05], [0.6, 0.42, 0.04], [0.42, 0.58, 0.04], [0.62, 0.62, 0.05], [0.5, 0.50, 0.07]];
    stars.forEach(function(p) {
        var x = s * p[0], y = s * p[1], r = s * p[2];
        ctx.fillStyle = accent || C.PALETTE.goldHi;
        ctx.beginPath();
        for (var i = 0; i < 8; i++) {
            var a = i / 8 * Math.PI * 2;
            var rr = i % 2 ? r * 0.4 : r;
            var xx = x + Math.cos(a) * rr, yy = y + Math.sin(a) * rr;
            if (i === 0) ctx.moveTo(xx, yy); else ctx.lineTo(xx, yy);
        }
        ctx.closePath();
        ctx.fill();
    });
}

// CELESTIA — planet with ring
function drawCelestia(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // ring back half
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-0.4);
    ctx.beginPath();
    ctx.ellipse(0, 0, s * 0.34, s * 0.08, 0, Math.PI, Math.PI * 2);
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    ctx.restore();
    // planet
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.20, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.06, cy - s * 0.08, s * 0.02, s * 0.22,
        [[0, "#f6dca0"], [1, C.PALETTE.terraDark]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // ring front half
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-0.4);
    ctx.beginPath();
    ctx.ellipse(0, 0, s * 0.34, s * 0.08, 0, 0, Math.PI);
    C.setStroke(ctx, accent || C.PALETTE.goldHi, s * 0.014);
    ctx.stroke();
    ctx.restore();
}

// GEOGEBRA — protractor arc
function drawGeoGebra(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.60;
    // half disc
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, Math.PI, 0);
    ctx.lineTo(cx + s * 0.30, cy);
    ctx.lineTo(cx - s * 0.30, cy);
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // tick marks
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineWidth = s * 0.006;
    for (var i = 0; i < 19; i++) {
        var a = Math.PI + i / 18 * Math.PI;
        var r1 = s * 0.30, r2 = s * (i % 3 === 0 ? 0.24 : 0.26);
        ctx.beginPath();
        ctx.moveTo(cx + Math.cos(a) * r1, cy + Math.sin(a) * r1);
        ctx.lineTo(cx + Math.cos(a) * r2, cy + Math.sin(a) * r2);
        ctx.stroke();
    }
    // angle line
    ctx.strokeStyle = accent || C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    ctx.moveTo(cx, cy);
    ctx.lineTo(cx + Math.cos(-Math.PI * 0.7) * s * 0.30, cy + Math.sin(-Math.PI * 0.7) * s * 0.30);
    ctx.stroke();
}

// OCTAVE — octagonal mathematical mark
function drawOctave(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // octagon
    ctx.beginPath();
    for (var i = 0; i < 8; i++) {
        var a = i / 8 * Math.PI * 2 + Math.PI / 8;
        var x = cx + Math.cos(a) * s * 0.30;
        var y = cy + Math.sin(a) * s * 0.30;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fillStyle = "#1d80c4";
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
    // sine wave inside
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    for (var x = 0.24; x <= 0.76; x += 0.02) {
        var y = 0.50 + Math.sin((x - 0.5) * 18) * 0.08;
        if (x === 0.24) ctx.moveTo(s * x, s * y); else ctx.lineTo(s * x, s * y);
    }
    ctx.stroke();
}

// RSTUDIO — R letter in a halo
function drawRStudio(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // halo ring
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.022);
    ctx.stroke();
    // R letter
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.font = "700 " + Math.round(s * 0.40) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("R", cx, cy);
    // small caret beneath
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.05, s * 0.74);
    ctx.lineTo(cx + s * 0.05, s * 0.74);
    ctx.lineTo(cx, s * 0.80);
    ctx.closePath();
    ctx.fill();
}

// JUPYTER — orbital with planet
function drawJupyter(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // three orbit dots (the Jupyter triad)
    var pts = [[0,-0.30],[0.26,0.16],[-0.26,0.16]];
    pts.forEach(function(p) {
        ctx.beginPath();
        ctx.arc(cx + s * p[0], cy + s * p[1], s * 0.06, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.terra;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    });
    // central body
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    // orbit ring
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.22, 0, Math.PI * 2);
    C.setStroke(ctx, "rgba(122,90,38,0.5)", s * 0.008);
    ctx.stroke();
}

// CLAMAV / CLAMTK — clam shell with detection mark
function drawClamAV(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.55;
    // top shell
    ctx.fillStyle = "#cfa376";
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.28, Math.PI, 0);
    ctx.lineTo(cx + s * 0.28, cy);
    ctx.lineTo(cx - s * 0.28, cy);
    ctx.closePath();
    ctx.fill();
    // bottom shell
    ctx.fillStyle = "#a8824a";
    ctx.beginPath();
    ctx.arc(cx, cy + s * 0.01, s * 0.28, 0, Math.PI);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.28, Math.PI, 0);
    ctx.stroke();
    // ribs
    for (var i = -3; i <= 3; i++) {
        ctx.beginPath();
        ctx.moveTo(cx + i * s * 0.07, cy);
        ctx.lineTo(cx + i * s * 0.07 * 1.3, cy - s * 0.28);
        C.setStroke(ctx, "rgba(58,43,24,0.4)", s * 0.006);
        ctx.stroke();
    }
    // checkmark
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.022;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.08, cy - s * 0.06);
    ctx.lineTo(cx - s * 0.02, cy);
    ctx.lineTo(cx + s * 0.10, cy - s * 0.14);
    ctx.stroke();
}

// PIKA BACKUP / VORTA / BORG — squirrel with acorn (silhouette)
function drawPikaBackup(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // body
    ctx.fillStyle = "#7a4a26";
    ctx.beginPath();
    ctx.ellipse(s * 0.46, s * 0.62, s * 0.16, s * 0.20, 0, 0, Math.PI * 2);
    ctx.fill();
    // tail (curled)
    ctx.beginPath();
    ctx.moveTo(s * 0.56, s * 0.62);
    ctx.bezierCurveTo(s * 0.80, s * 0.60, s * 0.82, s * 0.20, s * 0.62, s * 0.22);
    ctx.bezierCurveTo(s * 0.70, s * 0.30, s * 0.70, s * 0.50, s * 0.58, s * 0.50);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // head
    ctx.fillStyle = "#7a4a26";
    ctx.beginPath();
    ctx.arc(s * 0.36, s * 0.50, s * 0.10, 0, Math.PI * 2);
    ctx.fill();
    // ear
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.42);
    ctx.lineTo(s * 0.28, s * 0.34);
    ctx.lineTo(s * 0.36, s * 0.42);
    ctx.closePath(); ctx.fill();
    // eye
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(s * 0.34, s * 0.48, s * 0.014, 0, Math.PI * 2);
    ctx.fill();
    // acorn
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.ellipse(s * 0.28, s * 0.58, s * 0.06, s * 0.08, 0, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    ctx.fillStyle = "#7a4a26";
    ctx.beginPath();
    ctx.arc(s * 0.28, s * 0.52, s * 0.07, Math.PI, 0);
    ctx.fill();
}

// MINECRAFT — pixel cube
function drawMinecraft(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // dirt cube with grass top
    var cx = s * 0.5, cy = s * 0.5;
    // top face (grass)
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(cx, cy - s * 0.26);
    ctx.lineTo(cx + s * 0.24, cy - s * 0.14);
    ctx.lineTo(cx, cy - s * 0.02);
    ctx.lineTo(cx - s * 0.24, cy - s * 0.14);
    ctx.closePath();
    ctx.fill();
    // left face (dirt)
    ctx.fillStyle = "#7a4a26";
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.24, cy - s * 0.14);
    ctx.lineTo(cx, cy - s * 0.02);
    ctx.lineTo(cx, cy + s * 0.24);
    ctx.lineTo(cx - s * 0.24, cy + s * 0.12);
    ctx.closePath();
    ctx.fill();
    // right face (lighter dirt)
    ctx.fillStyle = "#a4824a";
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.24, cy - s * 0.14);
    ctx.lineTo(cx, cy - s * 0.02);
    ctx.lineTo(cx, cy + s * 0.24);
    ctx.lineTo(cx + s * 0.24, cy + s * 0.12);
    ctx.closePath();
    ctx.fill();
    // pixel grid
    ctx.strokeStyle = "rgba(58,43,24,0.35)";
    ctx.lineWidth = s * 0.006;
    [-1, 0, 1].forEach(function(i) {
        // top
        ctx.beginPath();
        ctx.moveTo(cx + i * s * 0.06, cy - s * 0.26 + Math.abs(i) * s * 0.06);
        ctx.lineTo(cx + i * s * 0.06, cy - s * 0.02 + Math.abs(i) * s * 0.06);
        ctx.stroke();
    });
}

// SUPERTUX / SUPERTUXKART — penguin head
function drawSuperTux(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // head
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.ellipse(cx, cy, s * 0.22, s * 0.26, 0, 0, Math.PI * 2);
    ctx.fill();
    // belly
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.ellipse(cx, cy + s * 0.05, s * 0.14, s * 0.18, 0, 0, Math.PI * 2);
    ctx.fill();
    // eyes
    ctx.fillStyle = "#fff";
    ctx.beginPath(); ctx.arc(cx - s * 0.07, cy - s * 0.10, s * 0.030, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(cx + s * 0.07, cy - s * 0.10, s * 0.030, 0, Math.PI * 2); ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath(); ctx.arc(cx - s * 0.07, cy - s * 0.10, s * 0.012, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(cx + s * 0.07, cy - s * 0.10, s * 0.012, 0, Math.PI * 2); ctx.fill();
    // beak
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.05, cy - s * 0.02);
    ctx.lineTo(cx + s * 0.05, cy - s * 0.02);
    ctx.lineTo(cx, cy + s * 0.04);
    ctx.closePath();
    ctx.fill();
}

// CONKY — c-glyph in a bird tail
function drawConky(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // background tablet
    ctx.fillStyle = "#1d1a14";
    ctx.fillRect(s * 0.14, s * 0.16, s * 0.72, s * 0.68);
    // ascii widget content
    ctx.fillStyle = "rgba(230,199,133,0.85)";
    ctx.font = "700 " + Math.round(s * 0.08) + "px monospace";
    ctx.textBaseline = "top";
    ctx.fillText("CPU [|||  ]", s * 0.18, s * 0.22);
    ctx.fillText("MEM [||||]", s * 0.18, s * 0.32);
    ctx.fillText("UP  03:14", s * 0.18, s * 0.42);
    // graph
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.010;
    ctx.beginPath();
    for (var i = 0; i < 10; i++) {
        var x = s * (0.18 + i * 0.06);
        var y = s * (0.66 + Math.sin(i * 0.9) * 0.06);
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.stroke();
}

// REDSHIFT / GAMMASTEP / NIGHT-LIGHT — moon + sun
function drawRedshift(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // gradient day-night background
    ctx.save();
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.32, 0, Math.PI * 2);
    ctx.clip();
    var g = ctx.createLinearGradient(0, 0, s, 0);
    g.addColorStop(0, "#f6c463");
    g.addColorStop(1, "#23304a");
    ctx.fillStyle = g;
    ctx.fillRect(0, 0, s, s);
    ctx.restore();
    // sun (left)
    ctx.beginPath();
    ctx.arc(cx - s * 0.15, cy, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fill();
    // moon (right) — crescent
    ctx.beginPath();
    ctx.arc(cx + s * 0.15, cy, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx + s * 0.20, cy - s * 0.02, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = "#23304a";
    ctx.fill();
    // ring
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.32, 0, Math.PI * 2);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
}

// FLAMESHOT / SPECTACLE / SCREENSHOT — capture frame
function drawScreenshot(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // crop brackets
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.022;
    ctx.lineCap = "round";
    var ps = [[0.18,0.22,0.32,0.22],[0.18,0.22,0.18,0.36],
              [0.82,0.22,0.68,0.22],[0.82,0.22,0.82,0.36],
              [0.18,0.78,0.32,0.78],[0.18,0.78,0.18,0.64],
              [0.82,0.78,0.68,0.78],[0.82,0.78,0.82,0.64]];
    ps.forEach(function(p) {
        ctx.beginPath();
        ctx.moveTo(s * p[0], s * p[1]);
        ctx.lineTo(s * p[2], s * p[3]);
        ctx.stroke();
    });
    // sample landscape inside
    ctx.fillStyle = "rgba(143,166,138,0.5)";
    ctx.fillRect(s * 0.22, s * 0.26, s * 0.56, s * 0.48);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.22, s * 0.60);
    ctx.lineTo(s * 0.34, s * 0.40);
    ctx.lineTo(s * 0.48, s * 0.54);
    ctx.lineTo(s * 0.60, s * 0.40);
    ctx.lineTo(s * 0.78, s * 0.60);
    ctx.lineTo(s * 0.78, s * 0.74);
    ctx.lineTo(s * 0.22, s * 0.74);
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.arc(s * 0.32, s * 0.36, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fill();
}

// CALCULATOR — calculator face
function drawCalculator(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // body
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.18, s * 0.14, s * 0.64, s * 0.72, s * 0.04);
    ctx.fill();
    // screen
    ctx.fillStyle = "#dcefa9";
    ctx.fillRect(s * 0.24, s * 0.20, s * 0.52, s * 0.16);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.10) + "px monospace";
    ctx.textAlign = "right";
    ctx.textBaseline = "middle";
    ctx.fillText("42", s * 0.74, s * 0.28);
    // buttons grid
    for (var r = 0; r < 4; r++) {
        for (var c = 0; c < 4; c++) {
            var x = s * (0.24 + c * 0.13);
            var y = s * (0.42 + r * 0.11);
            ctx.fillStyle = c === 3 ? accent || C.PALETTE.gold : C.PALETTE.bgCreamHi;
            C.roundRectPath(ctx, x, y, s * 0.10, s * 0.08, s * 0.02);
            ctx.fill();
        }
    }
}

// CLOCK — clock face
function drawClock(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // hour ticks
    for (var i = 0; i < 12; i++) {
        var a = i / 12 * Math.PI * 2;
        ctx.beginPath();
        ctx.moveTo(cx + Math.cos(a) * s * 0.30, cy + Math.sin(a) * s * 0.30);
        ctx.lineTo(cx + Math.cos(a) * s * (i % 3 === 0 ? 0.24 : 0.27),
                   cy + Math.sin(a) * s * (i % 3 === 0 ? 0.24 : 0.27));
        C.setStroke(ctx, C.PALETTE.ink, s * (i % 3 === 0 ? 0.014 : 0.008));
        ctx.stroke();
    }
    // hands at 10:10
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.020;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(cx, cy);
    ctx.lineTo(cx + Math.cos(-Math.PI * 0.83) * s * 0.16, cy + Math.sin(-Math.PI * 0.83) * s * 0.16);
    ctx.stroke();
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    ctx.moveTo(cx, cy);
    ctx.lineTo(cx + Math.cos(-Math.PI * 0.33) * s * 0.22, cy + Math.sin(-Math.PI * 0.33) * s * 0.22);
    ctx.stroke();
    // pivot
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.020, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
}

// WEATHER — cloud + sun
function drawWeather(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // sun rays
    var cx = s * 0.5, cy = s * 0.5;
    ctx.save();
    ctx.translate(s * 0.38, s * 0.40);
    for (var i = 0; i < 8; i++) {
        ctx.save();
        ctx.rotate(i / 8 * Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fillRect(s * 0.08, -s * 0.008, s * 0.04, s * 0.016);
        ctx.restore();
    }
    ctx.beginPath();
    ctx.arc(0, 0, s * 0.08, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fill();
    ctx.restore();
    // cloud
    ctx.fillStyle = "#cdd2da";
    ctx.beginPath();
    ctx.arc(s * 0.46, s * 0.62, s * 0.10, 0, Math.PI * 2);
    ctx.arc(s * 0.60, s * 0.56, s * 0.13, 0, Math.PI * 2);
    ctx.arc(s * 0.74, s * 0.62, s * 0.10, 0, Math.PI * 2);
    ctx.arc(s * 0.60, s * 0.68, s * 0.12, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
}

// MAPS — compass over folded paper
function drawMaps(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // folded paper
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.16, s * 0.28);
    ctx.lineTo(s * 0.36, s * 0.22);
    ctx.lineTo(s * 0.56, s * 0.28);
    ctx.lineTo(s * 0.76, s * 0.22);
    ctx.lineTo(s * 0.84, s * 0.76);
    ctx.lineTo(s * 0.64, s * 0.82);
    ctx.lineTo(s * 0.44, s * 0.76);
    ctx.lineTo(s * 0.24, s * 0.82);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    // road
    ctx.strokeStyle = C.PALETTE.terra;
    ctx.lineWidth = s * 0.018;
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.74);
    ctx.bezierCurveTo(s * 0.36, s * 0.50, s * 0.60, s * 0.66, s * 0.82, s * 0.40);
    ctx.stroke();
    // pin
    ctx.beginPath();
    ctx.arc(s * 0.58, s * 0.56, s * 0.06, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fill();
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.arc(s * 0.58, s * 0.56, s * 0.024, 0, Math.PI * 2);
    ctx.fill();
}

// GENERIC GAME — d20 die
function drawGenericGame(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // d20 silhouette
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.beginPath();
    for (var i = 0; i < 6; i++) {
        var a = i / 6 * Math.PI * 2 - Math.PI / 2;
        var x = cx + Math.cos(a) * s * 0.26;
        var y = cy + Math.sin(a) * s * 0.26;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    // inner triangle
    ctx.strokeStyle = accent || C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.012;
    ctx.beginPath();
    for (var j = 0; j < 3; j++) {
        var aa = j / 3 * Math.PI * 2 - Math.PI / 2;
        var xx = cx + Math.cos(aa) * s * 0.18;
        var yy = cy + Math.sin(aa) * s * 0.18;
        if (j === 0) ctx.moveTo(xx, yy); else ctx.lineTo(xx, yy);
    }
    ctx.closePath();
    ctx.stroke();
    // 20
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.16) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("20", cx, cy);
}

// GENERIC VAULT
function drawGenericVault(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"shield", accent:accent, glow:glow, ornament:false});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.arc(cx, cy + s * 0.04, s * 0.16, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.arc(cx, cy + s * 0.04, s * 0.08, 0, Math.PI * 2);
    ctx.fill();
    // tick on edge
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 8; i++) {
        var a = i / 8 * Math.PI * 2;
        ctx.beginPath();
        ctx.arc(cx + Math.cos(a) * s * 0.22, cy + s * 0.04 + Math.sin(a) * s * 0.22, s * 0.012, 0, Math.PI * 2);
        ctx.fill();
    }
}

// GENERIC NOTE
function drawGenericNote(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.18, s * 0.16);
    ctx.lineTo(s * 0.68, s * 0.16);
    ctx.lineTo(s * 0.82, s * 0.32);
    ctx.lineTo(s * 0.82, s * 0.84);
    ctx.lineTo(s * 0.18, s * 0.84);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.22, s * 0.30, s * 0.40, s * 0.020);
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * 0.22, s * (0.42 + i * 0.08), s * (0.50 - (i % 2) * 0.08), s * 0.014);
    }
}
