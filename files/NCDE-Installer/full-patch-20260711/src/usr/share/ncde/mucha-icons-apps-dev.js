// mucha-icons-apps-dev.js — dev tools, VCS, containers, virt, gaming runtimes.
.pragma library
.import "mucha-icons-core.js" as C

// GIT — three-pronged commit graph
function drawGit(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // nodes
    var nodes = [[0.30,0.30],[0.50,0.50],[0.70,0.30],[0.70,0.70]];
    // edges
    ctx.strokeStyle = C.PALETTE.terraDark;
    ctx.lineWidth = s * 0.026;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.30); ctx.lineTo(s * 0.50, s * 0.50);
    ctx.moveTo(s * 0.50, s * 0.50); ctx.lineTo(s * 0.70, s * 0.30);
    ctx.moveTo(s * 0.50, s * 0.50); ctx.lineTo(s * 0.70, s * 0.70);
    ctx.stroke();
    // dots
    nodes.forEach(function(n, i) {
        ctx.beginPath();
        ctx.arc(s * n[0], s * n[1], s * 0.054, 0, Math.PI * 2);
        ctx.fillStyle = i === 0 ? accent || C.PALETTE.gold : C.PALETTE.terraDark;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
        ctx.stroke();
    });
}

// GITHUB DESKTOP — Mona-cat ornament (silhouette, not logo)
function drawGitHubDesktop(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // cat head silhouette with tendril tail
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(cx, cy - s * 0.04, s * 0.20, 0, Math.PI * 2);
    ctx.fill();
    // ears
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.16, cy - s * 0.18);
    ctx.lineTo(cx - s * 0.20, cy - s * 0.30);
    ctx.lineTo(cx - s * 0.08, cy - s * 0.22);
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.16, cy - s * 0.18);
    ctx.lineTo(cx + s * 0.20, cy - s * 0.30);
    ctx.lineTo(cx + s * 0.08, cy - s * 0.22);
    ctx.closePath();
    ctx.fill();
    // eyes
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath(); ctx.arc(cx - s * 0.06, cy - s * 0.04, s * 0.020, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(cx + s * 0.06, cy - s * 0.04, s * 0.020, 0, Math.PI * 2); ctx.fill();
    // tendril tail
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.026;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.18, cy + s * 0.10);
    ctx.bezierCurveTo(cx + s * 0.34, cy + s * 0.06, cx + s * 0.30, cy + s * 0.30, cx + s * 0.18, cy + s * 0.26);
    ctx.stroke();
}

// GITKRAKEN — kraken tentacles
function drawGitKraken(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // central body
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.13, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.fill();
    // 6 tentacles spiralling
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < 6; i++) {
        ctx.save();
        ctx.rotate(i * Math.PI / 3);
        ctx.strokeStyle = i % 2 ? C.PALETTE.plumDeep : accent || C.PALETTE.gold;
        ctx.lineWidth = s * 0.018;
        ctx.lineCap = "round";
        ctx.beginPath();
        ctx.moveTo(s * 0.13, 0);
        ctx.bezierCurveTo(s * 0.20, -s * 0.05, s * 0.28, s * 0.10, s * 0.32, s * 0.06);
        ctx.stroke();
        // sucker dots
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        for (var j = 0; j < 3; j++) {
            ctx.beginPath();
            ctx.arc(s * (0.18 + j * 0.05), j % 2 ? -s * 0.01 : s * 0.03, s * 0.008, 0, Math.PI * 2);
            ctx.fill();
        }
        ctx.restore();
    }
    ctx.restore();
    // eye
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.04, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.020, 0, Math.PI * 2);
    ctx.fill();
}

// SOURCETREE — tree branches
function drawSourcetree(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // trunk
    ctx.strokeStyle = "#7a4a26";
    ctx.lineWidth = s * 0.04;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.moveTo(s * 0.5, s * 0.82);
    ctx.lineTo(s * 0.5, s * 0.40);
    ctx.stroke();
    // branches
    ctx.beginPath();
    ctx.moveTo(s * 0.5, s * 0.50); ctx.lineTo(s * 0.28, s * 0.32);
    ctx.moveTo(s * 0.5, s * 0.50); ctx.lineTo(s * 0.72, s * 0.32);
    ctx.moveTo(s * 0.5, s * 0.40); ctx.lineTo(s * 0.5, s * 0.20);
    ctx.stroke();
    // nodes (commits)
    var ncols = [accent || C.PALETTE.gold, C.PALETTE.sageDeep, C.PALETTE.terra];
    var positions = [[0.28, 0.32], [0.50, 0.20], [0.72, 0.32]];
    positions.forEach(function(p, i) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.05, 0, Math.PI * 2);
        ctx.fillStyle = ncols[i];
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    });
}

// GITG — gitg-flavoured node graph
function drawGitg(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // vertical lines
    ctx.strokeStyle = C.PALETTE.tealDeep;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.20); ctx.lineTo(s * 0.30, s * 0.80);
    ctx.moveTo(s * 0.50, s * 0.20); ctx.lineTo(s * 0.50, s * 0.80);
    ctx.moveTo(s * 0.70, s * 0.40); ctx.lineTo(s * 0.70, s * 0.80);
    ctx.stroke();
    // merge
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.40); ctx.lineTo(s * 0.70, s * 0.50);
    ctx.stroke();
    // nodes
    [[0.30,0.30],[0.50,0.40],[0.30,0.55],[0.70,0.55],[0.50,0.70]].forEach(function(p, i) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.040, 0, Math.PI * 2);
        ctx.fillStyle = i % 2 ? accent || C.PALETTE.gold : C.PALETTE.terra;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    });
}

// MELD — two diff panels with stitched lines
function drawMeld(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // left pane
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.14, s * 0.16, s * 0.32, s * 0.68);
    // right pane
    ctx.fillRect(s * 0.54, s * 0.16, s * 0.32, s * 0.68);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.14, s * 0.16, s * 0.32, s * 0.68);
    ctx.strokeRect(s * 0.54, s * 0.16, s * 0.32, s * 0.68);
    // lines on left (sage) & right (terra) — some shared, some different
    for (var i = 0; i < 6; i++) {
        var same = (i % 2 === 0);
        ctx.fillStyle = same ? "rgba(58,43,24,0.6)" : C.PALETTE.sageDeep;
        ctx.fillRect(s * 0.17, s * (0.22 + i * 0.10), s * (0.22 - (i % 2) * 0.04), s * 0.020);
        ctx.fillStyle = same ? "rgba(58,43,24,0.6)" : C.PALETTE.terraDark;
        ctx.fillRect(s * 0.57, s * (0.22 + i * 0.10), s * (0.22 - (i % 2) * 0.04), s * 0.020);
        if (!same) {
            // bridge stitch
            ctx.strokeStyle = accent || C.PALETTE.gold;
            ctx.lineWidth = s * 0.006;
            ctx.beginPath();
            ctx.moveTo(s * 0.46, s * (0.22 + i * 0.10) + s * 0.01);
            ctx.lineTo(s * 0.54, s * (0.22 + i * 0.10) + s * 0.01);
            ctx.stroke();
        }
    }
}

// POSTMAN — astronaut helmet
function drawPostman(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.54;
    // helmet
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // visor
    ctx.beginPath();
    ctx.arc(cx, cy + s * 0.02, s * 0.18, Math.PI * 0.2, Math.PI * 0.8);
    ctx.fillStyle = "#1d2840";
    ctx.fill();
    // visor highlight
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.beginPath();
    ctx.ellipse(cx - s * 0.06, cy + s * 0.02, s * 0.04, s * 0.008, 0, 0, Math.PI * 2);
    ctx.fill();
}

// INSOMNIA — crescent moon with eye
function drawInsomnia(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx + s * 0.08, cy - s * 0.04, s * 0.22, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCream;
    ctx.fill();
    // sleepless eye (Z)
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.font = "700 " + Math.round(s * 0.14) + "px serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("z", cx - s * 0.12, cy + s * 0.04);
    ctx.font = "700 " + Math.round(s * 0.10) + "px serif";
    ctx.fillText("z", cx - s * 0.20, cy - s * 0.10);
}

// BRUNO — coffee bean cluster
function drawBruno(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    function bean(x, y, rot) {
        ctx.save();
        ctx.translate(x, y);
        ctx.rotate(rot);
        ctx.fillStyle = "#5a2f1a";
        ctx.beginPath();
        ctx.ellipse(0, 0, s * 0.10, s * 0.07, 0, 0, Math.PI * 2);
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
        ctx.stroke();
        // crease
        ctx.beginPath();
        ctx.moveTo(-s * 0.08, 0);
        ctx.bezierCurveTo(-s * 0.02, -s * 0.02, s * 0.02, s * 0.02, s * 0.08, 0);
        ctx.stroke();
        ctx.restore();
    }
    bean(s * 0.36, s * 0.42, 0.3);
    bean(s * 0.62, s * 0.42, -0.3);
    bean(s * 0.50, s * 0.66, 0.1);
    // steam dots
    ctx.fillStyle = accent || C.PALETTE.gold;
    [0.36, 0.50, 0.62].forEach(function(x) {
        ctx.beginPath();
        ctx.arc(s * x, s * 0.24, s * 0.018, 0, Math.PI * 2);
        ctx.fill();
    });
}

// DBEAVER — beaver (silhouette) with stripe
function drawDBeaver(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // body
    ctx.fillStyle = "#7a4a26";
    ctx.beginPath();
    ctx.ellipse(cx, cy + s * 0.05, s * 0.22, s * 0.18, 0, 0, Math.PI * 2);
    ctx.fill();
    // tail
    ctx.beginPath();
    ctx.ellipse(cx + s * 0.24, cy + s * 0.14, s * 0.10, s * 0.05, 0.3, 0, Math.PI * 2);
    ctx.fill();
    // cross-hatch on tail
    ctx.strokeStyle = "#3a2a18";
    ctx.lineWidth = s * 0.005;
    for (var i = -2; i <= 2; i++) {
        ctx.beginPath();
        ctx.moveTo(cx + s * 0.16, cy + s * 0.14 + i * s * 0.015);
        ctx.lineTo(cx + s * 0.32, cy + s * 0.14 - i * s * 0.015);
        ctx.stroke();
    }
    // head
    ctx.fillStyle = "#7a4a26";
    ctx.beginPath();
    ctx.arc(cx - s * 0.18, cy - s * 0.04, s * 0.12, 0, Math.PI * 2);
    ctx.fill();
    // teeth
    ctx.fillStyle = "#fff";
    ctx.fillRect(cx - s * 0.18, cy + s * 0.04, s * 0.024, s * 0.04);
    ctx.fillRect(cx - s * 0.15, cy + s * 0.04, s * 0.024, s * 0.04);
    // eye
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(cx - s * 0.20, cy - s * 0.04, s * 0.012, 0, Math.PI * 2);
    ctx.fill();
    // gilt collar
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(cx - s * 0.10, cy + s * 0.04, s * 0.06, s * 0.04);
}

// DOCKER — whale silhouette
function drawDocker(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // waves
    ctx.strokeStyle = C.PALETTE.tealDeep;
    ctx.lineWidth = s * 0.010;
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.moveTo(s * 0.16, s * (0.78 - i * 0.06));
        ctx.bezierCurveTo(s * 0.30, s * (0.72 - i * 0.06), s * 0.70, s * (0.84 - i * 0.06), s * 0.84, s * (0.78 - i * 0.06));
        ctx.stroke();
    }
    // whale body
    ctx.fillStyle = C.PALETTE.teal;
    ctx.beginPath();
    ctx.moveTo(s * 0.18, s * 0.46);
    ctx.bezierCurveTo(s * 0.22, s * 0.30, s * 0.60, s * 0.28, s * 0.66, s * 0.38);
    ctx.lineTo(s * 0.82, s * 0.40);
    ctx.lineTo(s * 0.78, s * 0.50);
    ctx.lineTo(s * 0.66, s * 0.50);
    ctx.bezierCurveTo(s * 0.60, s * 0.60, s * 0.30, s * 0.60, s * 0.18, s * 0.46);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // containers on top
    var ccols = [accent || C.PALETTE.gold, C.PALETTE.terra, C.PALETTE.sageDeep];
    for (var c = 0; c < 3; c++) {
        ctx.fillStyle = ccols[c];
        ctx.fillRect(s * (0.30 + c * 0.10), s * 0.30, s * 0.08, s * 0.08);
        C.setStroke(ctx, C.PALETTE.ink, s * 0.006);
        ctx.strokeRect(s * (0.30 + c * 0.10), s * 0.30, s * 0.08, s * 0.08);
    }
    // eye
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(s * 0.28, s * 0.42, s * 0.012, 0, Math.PI * 2);
    ctx.fill();
    // spout
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineWidth = s * 0.014;
    ctx.beginPath();
    ctx.moveTo(s * 0.34, s * 0.30); ctx.lineTo(s * 0.30, s * 0.18);
    ctx.stroke();
}

// PODMAN — seal balancing a container
function drawPodman(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // seal body
    ctx.fillStyle = "#3b3a30";
    ctx.beginPath();
    ctx.ellipse(s * 0.5, s * 0.66, s * 0.22, s * 0.14, 0, 0, Math.PI * 2);
    ctx.fill();
    // head
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.50, s * 0.10, 0, Math.PI * 2);
    ctx.fill();
    // eyes
    ctx.fillStyle = "#fff";
    ctx.beginPath(); ctx.arc(s * 0.46, s * 0.48, s * 0.018, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.54, s * 0.48, s * 0.018, 0, Math.PI * 2); ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath(); ctx.arc(s * 0.46, s * 0.49, s * 0.008, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.54, s * 0.49, s * 0.008, 0, Math.PI * 2); ctx.fill();
    // container balanced on nose
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.40, s * 0.28, s * 0.20, s * 0.10);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.strokeRect(s * 0.40, s * 0.28, s * 0.20, s * 0.10);
    // line on container
    ctx.beginPath();
    ctx.moveTo(s * 0.40, s * 0.33); ctx.lineTo(s * 0.60, s * 0.33);
    ctx.stroke();
}

// VIRT-MANAGER — multi-pane window
function drawVirtManager(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // outer window
    ctx.fillStyle = "#3b3a30";
    ctx.fillRect(s * 0.14, s * 0.20, s * 0.72, s * 0.60);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.16, s * 0.28, s * 0.68, s * 0.50);
    // 4 mini VMs
    var vcols = [C.PALETTE.terra, accent || C.PALETTE.gold, C.PALETTE.sageDeep, C.PALETTE.tealDeep];
    for (var i = 0; i < 4; i++) {
        var x = s * (0.20 + (i % 2) * 0.32);
        var y = s * (0.32 + (i >> 1) * 0.22);
        ctx.fillStyle = vcols[i];
        ctx.fillRect(x, y, s * 0.28, s * 0.18);
        // small play
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.beginPath();
        ctx.moveTo(x + s * 0.10, y + s * 0.06);
        ctx.lineTo(x + s * 0.18, y + s * 0.09);
        ctx.lineTo(x + s * 0.10, y + s * 0.12);
        ctx.closePath();
        ctx.fill();
    }
}

// VIRTUALBOX — engraved cube
function drawVirtualBox(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    // top
    ctx.fillStyle = "#8c5fae";
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.24);
    ctx.lineTo(s * 0.20, -s * 0.12);
    ctx.lineTo(0, 0);
    ctx.lineTo(-s * 0.20, -s * 0.12);
    ctx.closePath();
    ctx.fill();
    // left
    ctx.fillStyle = "#6e4090";
    ctx.beginPath();
    ctx.moveTo(-s * 0.20, -s * 0.12);
    ctx.lineTo(0, 0);
    ctx.lineTo(0, s * 0.24);
    ctx.lineTo(-s * 0.20, s * 0.12);
    ctx.closePath();
    ctx.fill();
    // right
    ctx.fillStyle = "#5a2f72";
    ctx.beginPath();
    ctx.moveTo(s * 0.20, -s * 0.12);
    ctx.lineTo(0, 0);
    ctx.lineTo(0, s * 0.24);
    ctx.lineTo(s * 0.20, s * 0.12);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.24);
    ctx.lineTo(s * 0.20, -s * 0.12);
    ctx.lineTo(s * 0.20, s * 0.12);
    ctx.lineTo(0, s * 0.24);
    ctx.lineTo(-s * 0.20, s * 0.12);
    ctx.lineTo(-s * 0.20, -s * 0.12);
    ctx.closePath();
    ctx.moveTo(0, 0); ctx.lineTo(0, s * 0.24);
    ctx.moveTo(-s * 0.20, -s * 0.12); ctx.lineTo(0, 0);
    ctx.moveTo(s * 0.20, -s * 0.12); ctx.lineTo(0, 0);
    ctx.stroke();
    ctx.restore();
}

// VMWARE — ringed cylinder
function drawVMware(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5;
    // stacked rings
    for (var i = 0; i < 4; i++) {
        var y = s * (0.30 + i * 0.10);
        ctx.fillStyle = i % 2 ? C.PALETTE.sageDeep : C.PALETTE.tealDeep;
        ctx.fillRect(cx - s * 0.22, y, s * 0.44, s * 0.08);
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.strokeRect(cx - s * 0.22, y, s * 0.44, s * 0.08);
    }
    // top dome
    ctx.beginPath();
    ctx.ellipse(cx, s * 0.30, s * 0.22, s * 0.06, 0, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
}

// GNOME BOXES — abstract box stack
function drawBoxes(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    var cx = s * 0.5;
    // 3 boxes overlapping
    ctx.fillStyle = C.PALETTE.terra;
    ctx.fillRect(s * 0.16, s * 0.48, s * 0.40, s * 0.30);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.fillRect(s * 0.32, s * 0.34, s * 0.40, s * 0.30);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.48, s * 0.20, s * 0.40, s * 0.30);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.16, s * 0.48, s * 0.40, s * 0.30);
    ctx.strokeRect(s * 0.32, s * 0.34, s * 0.40, s * 0.30);
    ctx.strokeRect(s * 0.48, s * 0.20, s * 0.40, s * 0.30);
    // play
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.62, s * 0.30);
    ctx.lineTo(s * 0.76, s * 0.35);
    ctx.lineTo(s * 0.62, s * 0.40);
    ctx.closePath();
    ctx.fill();
}

// WINE — goblet
function drawWine(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5;
    // bowl
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.18, s * 0.22);
    ctx.lineTo(cx + s * 0.18, s * 0.22);
    ctx.bezierCurveTo(cx + s * 0.20, s * 0.46, cx - s * 0.20, s * 0.46, cx - s * 0.18, s * 0.22);
    ctx.closePath();
    ctx.fill();
    // glass outline
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.20, s * 0.20);
    ctx.lineTo(cx + s * 0.20, s * 0.20);
    ctx.bezierCurveTo(cx + s * 0.22, s * 0.50, cx + s * 0.04, s * 0.56, cx + s * 0.02, s * 0.62);
    ctx.lineTo(cx + s * 0.02, s * 0.76);
    ctx.lineTo(cx + s * 0.16, s * 0.78);
    ctx.lineTo(cx - s * 0.16, s * 0.78);
    ctx.lineTo(cx - s * 0.02, s * 0.76);
    ctx.lineTo(cx - s * 0.02, s * 0.62);
    ctx.bezierCurveTo(cx - s * 0.04, s * 0.56, cx - s * 0.22, s * 0.50, cx - s * 0.20, s * 0.20);
    ctx.closePath();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // highlight
    ctx.fillStyle = "rgba(255,235,180,0.4)";
    ctx.fillRect(cx - s * 0.14, s * 0.24, s * 0.04, s * 0.16);
    // gilt rim
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fillRect(cx - s * 0.20, s * 0.20, s * 0.40, s * 0.012);
}

// LUTRIS — laurel wreath with controller
function drawLutris(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // laurel left
    for (var i = 0; i < 5; i++) {
        var a1 = Math.PI * 0.85 + i * 0.10;
        var a2 = Math.PI * 0.15 - i * 0.10;
        C.leafBead(ctx, cx + Math.cos(a1) * s * 0.34, cy + Math.sin(a1) * s * 0.34,
                   s * 0.14, a1 + Math.PI / 2, C.PALETTE.sageDeep);
        C.leafBead(ctx, cx + Math.cos(a2) * s * 0.34, cy + Math.sin(a2) * s * 0.34,
                   s * 0.14, a2 + Math.PI / 2, C.PALETTE.sageDeep);
    }
    // controller silhouette
    ctx.fillStyle = C.PALETTE.indigoDeep;
    C.roundRectPath(ctx, s * 0.26, s * 0.40, s * 0.48, s * 0.22, s * 0.08);
    ctx.fill();
    // d-pad
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    ctx.fillRect(s * 0.32, s * 0.48, s * 0.06, s * 0.020);
    ctx.fillRect(s * 0.34, s * 0.46, s * 0.020, s * 0.06);
    // buttons
    ctx.beginPath(); ctx.arc(s * 0.62, s * 0.48, s * 0.018, 0, Math.PI * 2); ctx.fill();
    ctx.beginPath(); ctx.arc(s * 0.68, s * 0.52, s * 0.018, 0, Math.PI * 2); ctx.fill();
}

// HEROIC — laurel cross
function drawHeroic(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"shield", accent:accent, glow:glow, ornament:false});
    // cross
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.46, s * 0.16, s * 0.08, s * 0.66);
    ctx.fillRect(s * 0.22, s * 0.40, s * 0.56, s * 0.08);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.46, s * 0.16, s * 0.08, s * 0.66);
    ctx.strokeRect(s * 0.22, s * 0.40, s * 0.56, s * 0.08);
    // laurel at base
    C.leafBead(ctx, s * 0.34, s * 0.80, s * 0.14, -0.3, C.PALETTE.sageDeep);
    C.leafBead(ctx, s * 0.66, s * 0.80, s * 0.14, 0.3 + Math.PI, C.PALETTE.sageDeep);
}

// BOTTLES — ornate bottle
function drawBottles(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5;
    // bottle silhouette
    ctx.fillStyle = "rgba(143,166,138,0.4)";
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.05, s * 0.18);
    ctx.lineTo(cx + s * 0.05, s * 0.18);
    ctx.lineTo(cx + s * 0.05, s * 0.36);
    ctx.lineTo(cx + s * 0.20, s * 0.46);
    ctx.lineTo(cx + s * 0.20, s * 0.80);
    ctx.lineTo(cx - s * 0.20, s * 0.80);
    ctx.lineTo(cx - s * 0.20, s * 0.46);
    ctx.lineTo(cx - s * 0.05, s * 0.36);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // label
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(cx - s * 0.18, s * 0.56, s * 0.36, s * 0.16);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.strokeRect(cx - s * 0.18, s * 0.56, s * 0.36, s * 0.16);
    // ornamental star on label
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.10) + "px serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("✦", cx, s * 0.64);
    // cork
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(cx - s * 0.05, s * 0.12, s * 0.10, s * 0.08);
}

// STEAM — cog with steam wisps
function drawSteam(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.56;
    // steam wisps top
    ctx.strokeStyle = C.PALETTE.bgCream;
    ctx.lineWidth = s * 0.014;
    ctx.lineCap = "round";
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        var x = s * (0.34 + i * 0.16);
        ctx.moveTo(x, s * 0.30);
        ctx.bezierCurveTo(x - s * 0.04, s * 0.20, x + s * 0.04, s * 0.16, x, s * 0.10);
        ctx.stroke();
    }
    // cog
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    for (var k = 0; k < 24; k++) {
        var a = k / 24 * Math.PI * 2;
        var r = k % 2 ? s * 0.26 : s * 0.22;
        var x = cx + Math.cos(a) * r;
        var y = cy + Math.sin(a) * r;
        if (k === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
    ctx.stroke();
    // hub
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
}
