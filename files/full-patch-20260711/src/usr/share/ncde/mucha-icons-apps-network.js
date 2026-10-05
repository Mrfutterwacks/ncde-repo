// mucha-icons-apps-network.js — torrent, transfer, remote, cloud, VPN.
.pragma library
.import "mucha-icons-core.js" as C

// QBITTORRENT — cascading arrows torrent
function drawQbittorrent(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // pool at bottom
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath();
    ctx.ellipse(s * 0.5, s * 0.78, s * 0.30, s * 0.06, 0, 0, Math.PI * 2);
    ctx.fill();
    // 3 stream arrows
    var cols = [accent || C.PALETTE.gold, C.PALETTE.sageDeep, C.PALETTE.terra];
    for (var i = 0; i < 3; i++) {
        var x = s * (0.30 + i * 0.20);
        ctx.fillStyle = cols[i];
        ctx.beginPath();
        ctx.moveTo(x - s * 0.04, s * 0.20);
        ctx.lineTo(x + s * 0.04, s * 0.20);
        ctx.lineTo(x + s * 0.04, s * 0.56);
        ctx.lineTo(x + s * 0.10, s * 0.56);
        ctx.lineTo(x, s * 0.72);
        ctx.lineTo(x - s * 0.10, s * 0.56);
        ctx.lineTo(x - s * 0.04, s * 0.56);
        ctx.closePath();
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    }
}

// TRANSMISSION — gear with arrow streams
function drawTransmission(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // 4 directional arrows
    var aspects = [[0,-1],[1,0],[0,1],[-1,0]];
    var cols = [accent || C.PALETTE.gold, C.PALETTE.terra, C.PALETTE.sageDeep, C.PALETTE.indigoDeep];
    aspects.forEach(function(d, i) {
        ctx.save();
        ctx.translate(cx, cy);
        ctx.rotate(Math.atan2(d[1], d[0]));
        ctx.fillStyle = cols[i];
        ctx.beginPath();
        ctx.moveTo(s * 0.12, -s * 0.04);
        ctx.lineTo(s * 0.24, -s * 0.04);
        ctx.lineTo(s * 0.24, -s * 0.08);
        ctx.lineTo(s * 0.34, 0);
        ctx.lineTo(s * 0.24, s * 0.08);
        ctx.lineTo(s * 0.24, s * 0.04);
        ctx.lineTo(s * 0.12, s * 0.04);
        ctx.closePath();
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
        ctx.restore();
    });
    // hub
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.08, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.014);
    ctx.stroke();
}

// DELUGE — rain droplets
function drawDeluge(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // cloud
    ctx.fillStyle = "#cdd2da";
    ctx.beginPath();
    ctx.arc(s * 0.36, s * 0.34, s * 0.10, 0, Math.PI * 2);
    ctx.arc(s * 0.50, s * 0.28, s * 0.13, 0, Math.PI * 2);
    ctx.arc(s * 0.64, s * 0.34, s * 0.10, 0, Math.PI * 2);
    ctx.arc(s * 0.50, s * 0.40, s * 0.12, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // drops (purple/gold)
    var drops = [[0.32, 0.58, C.PALETTE.plum],
                 [0.46, 0.62, accent || C.PALETTE.gold],
                 [0.60, 0.58, C.PALETTE.plumDeep],
                 [0.40, 0.74, C.PALETTE.tealDeep],
                 [0.56, 0.74, C.PALETTE.terra]];
    drops.forEach(function(d) {
        ctx.fillStyle = d[2];
        ctx.beginPath();
        ctx.moveTo(s * d[0], s * (d[1] - 0.06));
        ctx.bezierCurveTo(s * (d[0] + 0.04), s * (d[1] - 0.02), s * (d[0] + 0.04), s * (d[1] + 0.04), s * d[0], s * (d[1] + 0.06));
        ctx.bezierCurveTo(s * (d[0] - 0.04), s * (d[1] + 0.04), s * (d[0] - 0.04), s * (d[1] - 0.02), s * d[0], s * (d[1] - 0.06));
        ctx.closePath();
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.006);
        ctx.stroke();
    });
}

// WIRESHARK — shark fin
function drawWireshark(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    // water
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.10, s * 0.62);
    ctx.bezierCurveTo(s * 0.30, s * 0.56, s * 0.70, s * 0.66, s * 0.90, s * 0.60);
    ctx.lineTo(s * 0.90, s * 0.88);
    ctx.lineTo(s * 0.10, s * 0.88);
    ctx.closePath();
    ctx.fill();
    // fin
    ctx.fillStyle = "#3b3a30";
    ctx.beginPath();
    ctx.moveTo(s * 0.36, s * 0.66);
    ctx.bezierCurveTo(s * 0.46, s * 0.40, s * 0.62, s * 0.38, s * 0.66, s * 0.62);
    ctx.bezierCurveTo(s * 0.58, s * 0.58, s * 0.46, s * 0.60, s * 0.36, s * 0.66);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.012);
    ctx.stroke();
    // wave ripples
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineWidth = s * 0.008;
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.66, s * 0.20, 0, Math.PI);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.66, s * 0.28, 0, Math.PI);
    ctx.stroke();
}

// FILEZILLA — fish
function drawFilezilla(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // body
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.18, cy);
    ctx.bezierCurveTo(s * 0.20, cy - s * 0.20, s * 0.66, cy - s * 0.20, s * 0.72, cy);
    ctx.bezierCurveTo(s * 0.66, cy + s * 0.20, s * 0.20, cy + s * 0.20, s * 0.18, cy);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // tail
    ctx.beginPath();
    ctx.moveTo(s * 0.72, cy);
    ctx.lineTo(s * 0.86, cy - s * 0.12);
    ctx.lineTo(s * 0.86, cy + s * 0.12);
    ctx.closePath();
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // scales
    ctx.strokeStyle = "rgba(58,43,24,0.45)";
    ctx.lineWidth = s * 0.005;
    for (var i = 0; i < 3; i++) {
        for (var j = 0; j < 4; j++) {
            ctx.beginPath();
            ctx.arc(s * (0.32 + j * 0.10), cy - s * 0.08 + i * s * 0.08, s * 0.04, Math.PI * 0.2, Math.PI * 0.8);
            ctx.stroke();
        }
    }
    // eye
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.arc(s * 0.26, cy - s * 0.04, s * 0.020, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.arc(s * 0.26, cy - s * 0.04, s * 0.010, 0, Math.PI * 2);
    ctx.fill();
}

// REMMINA — remote monitor
function drawRemmina(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // monitor
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.14, s * 0.22, s * 0.72, s * 0.42, s * 0.03);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.17, s * 0.25, s * 0.66, s * 0.36);
    // stand
    ctx.fillStyle = "#3b3a30";
    ctx.fillRect(s * 0.44, s * 0.64, s * 0.12, s * 0.10);
    ctx.fillRect(s * 0.30, s * 0.74, s * 0.40, s * 0.04);
    // signal arc
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.012;
    ctx.lineCap = "round";
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(s * 0.5, s * 0.40, s * (0.05 + i * 0.06), -Math.PI * 0.4, Math.PI * 0.4);
        ctx.stroke();
    }
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.40, s * 0.020, 0, Math.PI * 2);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fill();
}

// KRDC — KDE remote desktop
function drawKRDC(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // two monitors connecting
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.10, s * 0.26, s * 0.32, s * 0.30, s * 0.02);
    ctx.fill();
    C.roundRectPath(ctx, s * 0.58, s * 0.26, s * 0.32, s * 0.30, s * 0.02);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fillRect(s * 0.12, s * 0.28, s * 0.28, s * 0.24);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillRect(s * 0.60, s * 0.28, s * 0.28, s * 0.24);
    // arrow connection
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.42, s * 0.38);
    ctx.lineTo(s * 0.54, s * 0.38);
    ctx.lineTo(s * 0.54, s * 0.34);
    ctx.lineTo(s * 0.60, s * 0.41);
    ctx.lineTo(s * 0.54, s * 0.48);
    ctx.lineTo(s * 0.54, s * 0.44);
    ctx.lineTo(s * 0.42, s * 0.44);
    ctx.closePath();
    ctx.fill();
    // stands
    ctx.fillStyle = "#3b3a30";
    ctx.fillRect(s * 0.20, s * 0.56, s * 0.12, s * 0.06);
    ctx.fillRect(s * 0.68, s * 0.56, s * 0.12, s * 0.06);
    ctx.fillRect(s * 0.16, s * 0.62, s * 0.20, s * 0.03);
    ctx.fillRect(s * 0.64, s * 0.62, s * 0.20, s * 0.03);
}

// OPENVPN / WIREGUARD — keyhole shield
function drawVPN(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"shield", accent:accent, glow:glow, ornament:false});
    var cx = s * 0.5, cy = s * 0.5;
    // keyhole
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.beginPath();
    ctx.arc(cx, cy - s * 0.04, s * 0.08, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillRect(cx - s * 0.03, cy - s * 0.04, s * 0.06, s * 0.20);
    // shield outline accent
    ctx.save();
    ctx.translate(2.5, 2.5);
    C.shieldPath(ctx, s - 5);
    C.setStroke(ctx, accent || C.PALETTE.gold, s * 0.018);
    ctx.stroke();
    ctx.restore();
    // lock fastener at top
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.12, s * 0.30);
    ctx.lineTo(cx + s * 0.12, s * 0.30);
    ctx.lineTo(cx + s * 0.10, s * 0.36);
    ctx.lineTo(cx - s * 0.10, s * 0.36);
    ctx.closePath();
    ctx.fill();
}

// PROTONVPN / MULLVAD — atom / orbit shield
function drawProtonVPN(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // 3 orbits
    var rots = [0, Math.PI / 3, -Math.PI / 3];
    for (var i = 0; i < 3; i++) {
        ctx.save();
        ctx.translate(cx, cy);
        ctx.rotate(rots[i]);
        ctx.strokeStyle = accent || C.PALETTE.gold;
        ctx.lineWidth = s * 0.012;
        ctx.beginPath();
        ctx.ellipse(0, 0, s * 0.30, s * 0.12, 0, 0, Math.PI * 2);
        ctx.stroke();
        ctx.restore();
    }
    // shield-lock at centre
    ctx.fillStyle = C.PALETTE.plumDeep;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.10, cy - s * 0.10);
    ctx.lineTo(cx + s * 0.10, cy - s * 0.10);
    ctx.lineTo(cx + s * 0.10, cy + s * 0.04);
    ctx.bezierCurveTo(cx + s * 0.10, cy + s * 0.14, cx - s * 0.10, cy + s * 0.14, cx - s * 0.10, cy + s * 0.04);
    ctx.closePath();
    ctx.fill();
    ctx.fillStyle = C.PALETTE.goldHi;
    ctx.fillRect(cx - s * 0.014, cy - s * 0.02, s * 0.028, s * 0.06);
}

// DROPBOX — folded box (paper)
function drawDropbox(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // 4 paper diamonds
    function dia(x, y, col) {
        ctx.fillStyle = col;
        ctx.beginPath();
        ctx.moveTo(x, y - s * 0.10);
        ctx.lineTo(x + s * 0.14, y);
        ctx.lineTo(x, y + s * 0.10);
        ctx.lineTo(x - s * 0.14, y);
        ctx.closePath();
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    }
    dia(cx - s * 0.14, cy - s * 0.10, accent || C.PALETTE.gold);
    dia(cx + s * 0.14, cy - s * 0.10, C.PALETTE.terra);
    dia(cx - s * 0.14, cy + s * 0.10, C.PALETTE.sageDeep);
    dia(cx + s * 0.14, cy + s * 0.10, C.PALETTE.tealDeep);
}

// NEXTCLOUD / OWNCLOUD — cloud with arches
function drawNextcloud(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"round", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.55;
    // cloud body
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.beginPath();
    ctx.arc(cx - s * 0.16, cy, s * 0.10, 0, Math.PI * 2);
    ctx.arc(cx, cy - s * 0.08, s * 0.14, 0, Math.PI * 2);
    ctx.arc(cx + s * 0.16, cy, s * 0.10, 0, Math.PI * 2);
    ctx.arc(cx, cy + s * 0.04, s * 0.14, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // 3 dots inside (the next… motif)
    ctx.fillStyle = accent || C.PALETTE.goldHi;
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(cx - s * 0.08 + i * s * 0.08, cy, s * 0.020, 0, Math.PI * 2);
        ctx.fill();
    }
}

// SYNCTHING — two arrows curling
function drawSyncthing(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.strokeStyle = accent || C.PALETTE.gold;
    ctx.lineWidth = s * 0.030;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.20, -Math.PI * 0.4, Math.PI * 0.9);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.20, Math.PI * 0.6, Math.PI * 1.9);
    ctx.stroke();
    // arrowheads
    ctx.fillStyle = accent || C.PALETTE.gold;
    var a1x = cx + Math.cos(Math.PI * 0.9) * s * 0.20;
    var a1y = cy + Math.sin(Math.PI * 0.9) * s * 0.20;
    ctx.beginPath();
    ctx.arc(a1x, a1y, s * 0.04, 0, Math.PI * 2);
    ctx.fill();
    var a2x = cx + Math.cos(Math.PI * 1.9) * s * 0.20;
    var a2y = cy + Math.sin(Math.PI * 1.9) * s * 0.20;
    ctx.beginPath();
    ctx.arc(a2x, a2y, s * 0.04, 0, Math.PI * 2);
    ctx.fill();
    // 3 device dots
    var devs = [[0.30,0.30],[0.70,0.30],[0.50,0.78]];
    devs.forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.04, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.sageDeep;
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
    });
}

// MEGA — bigger cloud with M
function drawMega(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.arc(cx - s * 0.20, cy + s * 0.06, s * 0.12, 0, Math.PI * 2);
    ctx.arc(cx, cy - s * 0.08, s * 0.16, 0, Math.PI * 2);
    ctx.arc(cx + s * 0.20, cy + s * 0.06, s * 0.12, 0, Math.PI * 2);
    ctx.arc(cx, cy + s * 0.10, s * 0.18, 0, Math.PI * 2);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // M letter
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.20) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("M", cx, cy);
}
