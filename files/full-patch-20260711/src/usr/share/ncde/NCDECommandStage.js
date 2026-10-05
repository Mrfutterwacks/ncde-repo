// ═══════════════════════════════════════════════════════════════
//  NCDE COMMAND STAGE BACKDROP
//  Theatrical proscenium stage — burgundy/gold Art Nouveau
//  Call: drawCommandStage(ctx, w, h)
//  Designed for 1920×1080; auto-scaled via xMidYMid-slice logic
// ═══════════════════════════════════════════════════════════════
.pragma library

function drawCommandStage(ctx, w, h) {
    // ── slice-scale so stage fills canvas (crops rather than stretches) ──
    var sxy = Math.max(w / 1920, h / 1080)
    var ox  = (w - 1920 * sxy) * 0.5
    var oy  = (h - 1080 * sxy) * 0.5

    ctx.save()
    ctx.translate(ox, oy)
    ctx.scale(sxy, sxy)

    // clip to stage bounds to avoid overdraw outside canvas
    ctx.beginPath()
    ctx.rect(0, 0, 1920, 1080)
    ctx.clip()

    // ── 1. SKY (radial gradient) ─────────────────────────────────
    var sky = ctx.createRadialGradient(960, 453, 0, 960, 453, 810)
    sky.addColorStop(0.00, "#2a3450")
    sky.addColorStop(0.40, "#1a2236")
    sky.addColorStop(0.80, "#0e1322")
    sky.addColorStop(1.00, "#06080f")
    ctx.fillStyle = sky
    ctx.fillRect(0, 0, 1920, 1080)

    // ── 2. STARS (deterministic Mulberry32) ──────────────────────
    var seed = 0x9e3779b9 >>> 0
    function rnd() {
        seed = (seed + 0x6D2B79F5) | 0
        var t = seed
        t = Math.imul(t ^ (t >>> 15), t | 1)
        t ^= t + Math.imul(t ^ (t >>> 7), t | 61)
        return ((t ^ (t >>> 14)) >>> 0) / 4294967296
    }
    function moonHalo(x, y) {
        var dx = x - 960, dy = y - 400
        return Math.sqrt(dx*dx + dy*dy) < 225
    }
    ctx.fillStyle = "#f6e3b0"
    // Bright stars
    for (var i = 0; i < 28; i++) {
        var sx = rnd() * 1920, sy = rnd() * 700 + 50
        if (moonHalo(sx, sy)) { sx = rnd() * 1920; sy = rnd() * 700 + 50 }
        var sr = 1.4 + rnd() * 1.8
        ctx.globalAlpha = 0.75 + rnd() * 0.25
        ctx.beginPath(); ctx.arc(sx, sy, sr, 0, Math.PI*2); ctx.fill()
    }
    // Small stars
    for (var j = 0; j < 160; j++) {
        var sx2 = rnd() * 1920, sy2 = rnd() * 900 + 30
        if (moonHalo(sx2, sy2)) { sx2 = rnd() * 1920; sy2 = rnd() * 900 + 30 }
        var sr2 = 0.4 + rnd() * 0.9
        ctx.globalAlpha = 0.4 + rnd() * 0.5
        ctx.beginPath(); ctx.arc(sx2, sy2, sr2, 0, Math.PI*2); ctx.fill()
    }
    ctx.globalAlpha = 1

    // constellation lines (subtle)
    ctx.strokeStyle = "rgba(233,201,124,0.18)"; ctx.lineWidth = 0.5
    ctx.beginPath()
    ctx.moveTo(340,180); ctx.lineTo(410,230); ctx.lineTo(480,200); ctx.lineTo(530,280); ctx.lineTo(580,250)
    ctx.moveTo(1380,160); ctx.lineTo(1450,220); ctx.lineTo(1520,190); ctx.lineTo(1590,250)
    ctx.stroke()

    // ── 3. MOON HALO + BODY ──────────────────────────────────────
    var mhalo = ctx.createRadialGradient(960,400,0, 960,400,290)
    mhalo.addColorStop(0.00, "rgba(246,227,176,0.45)")
    mhalo.addColorStop(0.30, "rgba(233,201,124,0.22)")
    mhalo.addColorStop(0.60, "rgba(201,138,58,0.08)")
    mhalo.addColorStop(1.00, "rgba(201,138,58,0)")
    ctx.fillStyle = mhalo
    ctx.beginPath(); ctx.arc(960,400,290,0,Math.PI*2); ctx.fill()

    // Moon rays
    ctx.save(); ctx.translate(960,400)
    ctx.strokeStyle = "rgba(201,138,58,0.22)"; ctx.lineWidth = 0.8
    for (var ri = 0; ri < 36; ri++) {
        var ang = (ri/36)*Math.PI*2
        var innerR = 145, outerR = (ri%3===0)?320:(ri%2===0)?260:220
        ctx.beginPath()
        ctx.moveTo(Math.cos(ang)*innerR, Math.sin(ang)*innerR)
        ctx.lineTo(Math.cos(ang)*outerR, Math.sin(ang)*outerR)
        ctx.stroke()
    }
    ctx.strokeStyle = "rgba(201,138,58,0.5)"; ctx.lineWidth = 0.6
    ctx.beginPath(); ctx.arc(0,0,220,0,Math.PI*2); ctx.stroke()
    ctx.strokeStyle = "rgba(201,138,58,0.35)"; ctx.lineWidth = 0.4
    ctx.beginPath(); ctx.arc(0,0,260,0,Math.PI*2); ctx.stroke()
    ctx.restore()

    // Moon body
    var moon = ctx.createRadialGradient(960-51,400-51,0, 960,400,135)
    moon.addColorStop(0.00, "#fbf0d0")
    moon.addColorStop(0.55, "#e9c97c")
    moon.addColorStop(0.90, "#b07a30")
    moon.addColorStop(1.00, "#8a5a20")
    ctx.fillStyle = moon
    ctx.beginPath(); ctx.arc(960,400,135,0,Math.PI*2); ctx.fill()
    // Craters
    ctx.fillStyle = "rgba(176,122,48,0.30)"
    ctx.beginPath(); ctx.ellipse(930,380,14,10,0,0,Math.PI*2); ctx.fill()
    ctx.fillStyle = "rgba(176,122,48,0.22)"
    ctx.beginPath(); ctx.ellipse(980,415,22,16,0,0,Math.PI*2); ctx.fill()
    ctx.strokeStyle = "rgba(138,90,32,0.40)"; ctx.lineWidth = 0.5
    ctx.beginPath(); ctx.arc(960,400,120,0,Math.PI*2); ctx.stroke()

    // ── 4. FOOTLIGHT GLOW WASH ────────────────────────────────────
    var footWash = ctx.createLinearGradient(0,1080, 0,500)
    footWash.addColorStop(0.00, "rgba(255,214,128,0.35)")
    footWash.addColorStop(0.40, "rgba(246,166,72,0.12)")
    footWash.addColorStop(1.00, "rgba(201,96,42,0)")
    ctx.fillStyle = footWash
    ctx.fillRect(240, 500, 1440, 460)

    // Footlight ellipse glows (17 lamps)
    var fCount = 17, fStartX = 290, fEndX = 1630, fY = 940
    for (var fi = 0; fi < fCount; fi++) {
        var ft = fi/(fCount-1), fx = fStartX + ft*(fEndX-fStartX)
        var isCenter = Math.abs(fi - (fCount-1)/2) < 0.6
        var glowR = isCenter ? 220 : 170, glowOp = isCenter ? 0.55 : 0.40
        var fg = ctx.createRadialGradient(fx, fY-10, 0, fx, fY-10, glowR)
        fg.addColorStop(0.00, "rgba(255,214,128,"+glowOp+")")
        fg.addColorStop(0.25, "rgba(246,166,72,"+(glowOp*0.6)+")")
        fg.addColorStop(0.55, "rgba(201,96,42,"+(glowOp*0.25)+")")
        fg.addColorStop(1.00, "rgba(201,96,42,0)")
        ctx.fillStyle = fg
        ctx.beginPath(); ctx.ellipse(fx, fY-10, glowR, glowR*1.4, 0, 0, Math.PI*2)
        ctx.fill()
    }

    // ── 5. LEFT CURTAIN ──────────────────────────────────────────
    var lcGrad = ctx.createLinearGradient(240,0, 660,0)
    lcGrad.addColorStop(0.00, "#2a0612")
    lcGrad.addColorStop(0.20, "#6e1832")
    lcGrad.addColorStop(0.50, "#8b1e3f")
    lcGrad.addColorStop(0.80, "#4a0e22")
    lcGrad.addColorStop(1.00, "#1a0408")
    ctx.fillStyle = lcGrad
    ctx.beginPath()
    ctx.moveTo(240, 200); ctx.lineTo(660, 200)
    ctx.bezierCurveTo(640,280, 610,360, 540,460)
    ctx.bezierCurveTo(480,540, 440,600, 420,660)
    ctx.bezierCurveTo(410,720, 430,780, 480,830)
    ctx.bezierCurveTo(540,880, 600,920, 640,960)
    ctx.lineTo(240, 960); ctx.closePath(); ctx.fill()

    // Pleat shading
    ctx.globalAlpha = 0.6
    var lpleats = [
        ["rgba(42,6,18,0.7)",3, [[280,200],[270,320],[250,480],[280,720],[300,860],[320,940],[320,960]]],
        ["rgba(168,40,74,0.5)",2, [[320,200],[310,320],[290,480],[330,720],[360,860],[380,940],[380,960]]],
        ["rgba(42,6,18,0.6)",2, [[360,200],[360,320],[350,480],[400,720],[440,860],[450,940],[450,960]]],
        ["rgba(168,40,74,0.45)",2,[[410,200],[420,280],[410,420],[460,660],[500,820],[530,920],[540,960]]],
        ["rgba(42,6,18,0.55)",2, [[460,200],[475,260],[465,380],[510,600],[560,800],[600,910],[620,960]]],
    ]
    for (var lp = 0; lp < lpleats.length; lp++) {
        var pleat = lpleats[lp]
        ctx.strokeStyle = pleat[0]; ctx.lineWidth = pleat[1]
        ctx.beginPath()
        var pts = pleat[2]
        ctx.moveTo(pts[0][0], pts[0][1])
        for (var pp = 1; pp < pts.length; pp++) ctx.lineTo(pts[pp][0], pts[pp][1])
        ctx.stroke()
    }
    ctx.globalAlpha = 1

    // Tieback shadow
    ctx.fillStyle = "rgba(26,4,8,0.5)"
    ctx.beginPath(); ctx.ellipse(425,660,60,120,0,0,Math.PI*2); ctx.fill()
    // Tieback rope
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 6; ctx.lineCap = "round"
    ctx.beginPath(); ctx.moveTo(350,620); ctx.bezierCurveTo(410,640,470,660,510,680); ctx.stroke()
    ctx.strokeStyle = "rgba(233,201,124,0.7)"; ctx.lineWidth = 2
    ctx.beginPath(); ctx.moveTo(350,620); ctx.bezierCurveTo(410,640,470,660,510,680); ctx.stroke()
    // Gold inner edge trim
    ctx.strokeStyle = "rgba(201,138,58,0.85)"; ctx.lineWidth = 2.5; ctx.lineCap = "butt"
    ctx.beginPath()
    ctx.moveTo(660,200)
    ctx.bezierCurveTo(640,280,610,360,540,460)
    ctx.bezierCurveTo(480,540,440,600,420,660)
    ctx.bezierCurveTo(410,720,430,780,480,830)
    ctx.bezierCurveTo(540,880,600,920,640,960)
    ctx.stroke()
    // Curtain tassels
    _tassel(ctx, 640, 960, 12, 18, 8, 62)
    _tassel(ctx, 515, 685, 10, 14, 6, 46)

    // ── 6. RIGHT CURTAIN ─────────────────────────────────────────
    var rcGrad = ctx.createLinearGradient(1680,0, 1260,0)
    rcGrad.addColorStop(0.00, "#2a0612")
    rcGrad.addColorStop(0.20, "#6e1832")
    rcGrad.addColorStop(0.50, "#8b1e3f")
    rcGrad.addColorStop(0.80, "#4a0e22")
    rcGrad.addColorStop(1.00, "#1a0408")
    ctx.fillStyle = rcGrad
    ctx.beginPath()
    ctx.moveTo(1680,200); ctx.lineTo(1260,200)
    ctx.bezierCurveTo(1280,280,1310,360,1380,460)
    ctx.bezierCurveTo(1440,540,1480,600,1500,660)
    ctx.bezierCurveTo(1510,720,1490,780,1440,830)
    ctx.bezierCurveTo(1380,880,1320,920,1280,960)
    ctx.lineTo(1680,960); ctx.closePath(); ctx.fill()

    ctx.globalAlpha = 0.6
    var rpleats = [
        ["rgba(42,6,18,0.7)",3, [[1640,200],[1650,320],[1670,480],[1640,720],[1620,860],[1600,960]]],
        ["rgba(168,40,74,0.5)",2,[[1600,200],[1610,320],[1630,480],[1590,720],[1560,860],[1540,960]]],
        ["rgba(42,6,18,0.6)",2, [[1560,200],[1560,320],[1570,480],[1520,720],[1480,860],[1470,960]]],
        ["rgba(168,40,74,0.45)",2,[[1510,200],[1500,280],[1510,420],[1460,660],[1420,820],[1380,960]]],
    ]
    for (var rp = 0; rp < rpleats.length; rp++) {
        var rpleat = rpleats[rp]
        ctx.strokeStyle = rpleat[0]; ctx.lineWidth = rpleat[1]
        ctx.beginPath()
        var rpts = rpleat[2]
        ctx.moveTo(rpts[0][0], rpts[0][1])
        for (var rpp = 1; rpp < rpts.length; rpp++) ctx.lineTo(rpts[rpp][0], rpts[rpp][1])
        ctx.stroke()
    }
    ctx.globalAlpha = 1

    ctx.fillStyle = "rgba(26,4,8,0.5)"
    ctx.beginPath(); ctx.ellipse(1495,660,60,120,0,0,Math.PI*2); ctx.fill()
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 6; ctx.lineCap = "round"
    ctx.beginPath(); ctx.moveTo(1570,620); ctx.bezierCurveTo(1510,640,1450,660,1410,680); ctx.stroke()
    ctx.strokeStyle = "rgba(233,201,124,0.7)"; ctx.lineWidth = 2
    ctx.beginPath(); ctx.moveTo(1570,620); ctx.bezierCurveTo(1510,640,1450,660,1410,680); ctx.stroke()
    ctx.strokeStyle = "rgba(201,138,58,0.85)"; ctx.lineWidth = 2.5; ctx.lineCap = "butt"
    ctx.beginPath()
    ctx.moveTo(1260,200)
    ctx.bezierCurveTo(1280,280,1310,360,1380,460)
    ctx.bezierCurveTo(1440,540,1480,600,1500,660)
    ctx.bezierCurveTo(1510,720,1490,780,1440,830)
    ctx.bezierCurveTo(1380,880,1320,920,1280,960)
    ctx.stroke()
    _tassel(ctx, 1280, 960, 12, 18, 8, 62)
    _tassel(ctx, 1405, 685, 10, 14, 6, 46)

    // ── 7. VALANCE ───────────────────────────────────────────────
    var vGrad = ctx.createLinearGradient(0,200, 0,340)
    vGrad.addColorStop(0.00, "#6e1832")
    vGrad.addColorStop(0.50, "#4a0e22")
    vGrad.addColorStop(1.00, "#2a0612")
    ctx.fillStyle = vGrad
    ctx.beginPath()
    ctx.moveTo(240,200); ctx.lineTo(1680,200); ctx.lineTo(1680,280)
    ctx.bezierCurveTo(1660,320,1620,340,1536,320)
    ctx.bezierCurveTo(1452,300,1412,320,1392,340)
    ctx.bezierCurveTo(1372,320,1332,300,1248,320)
    ctx.bezierCurveTo(1164,340,1124,320,1104,300)
    ctx.bezierCurveTo(1080,320,1040,340,960,340)
    ctx.bezierCurveTo(880,340,840,320,816,300)
    ctx.bezierCurveTo(796,320,756,340,672,320)
    ctx.bezierCurveTo(588,300,548,320,528,340)
    ctx.bezierCurveTo(508,320,468,300,384,320)
    ctx.bezierCurveTo(300,340,260,320,240,280)
    ctx.closePath(); ctx.fill()
    // Valance gold trim
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 2
    ctx.beginPath()
    ctx.moveTo(240,280)
    ctx.bezierCurveTo(260,320,300,340,384,320)
    ctx.bezierCurveTo(468,300,508,320,528,340)
    ctx.bezierCurveTo(548,320,588,300,672,320)
    ctx.bezierCurveTo(756,340,796,320,816,300)
    ctx.bezierCurveTo(840,320,880,340,960,340)
    ctx.bezierCurveTo(1040,340,1080,320,1104,300)
    ctx.bezierCurveTo(1124,320,1164,340,1248,320)
    ctx.bezierCurveTo(1332,300,1372,320,1392,340)
    ctx.bezierCurveTo(1412,320,1452,300,1536,320)
    ctx.bezierCurveTo(1620,340,1660,320,1680,280)
    ctx.stroke()
    // Valance tassels
    var valanceTassels = [[384,320,false],[528,340,true],[672,320,false],
                          [816,300,false],[960,340,true],[1104,300,false],
                          [1248,320,false],[1392,340,true],[1536,320,false]]
    for (var vt = 0; vt < valanceTassels.length; vt++) {
        var vtx=valanceTassels[vt][0], vty=valanceTassels[vt][1], vtl=valanceTassels[vt][2]
        _tassel(ctx, vtx, vty, vtl?7:6, vtl?11:9, vtl?5:4, vtl?48:34)
    }

    // ── 8. PROSCENIUM ARCH (burgundy frame with evenodd cutout) ──
    var frameGrad = ctx.createLinearGradient(0,0, 0,1080)
    frameGrad.addColorStop(0.00, "#4a0e22")
    frameGrad.addColorStop(0.50, "#6e1832")
    frameGrad.addColorStop(1.00, "#2a0612")
    ctx.fillStyle = frameGrad
    ctx.beginPath()
    // Outer frame
    ctx.rect(0, 0, 1920, 1080)
    // Opening cutout (same winding creates evenodd hole)
    ctx.moveTo(240, 960)
    ctx.lineTo(1680, 960)
    ctx.lineTo(1680, 280)
    ctx.bezierCurveTo(1680,220, 1640,200, 1580,200)
    ctx.lineTo(340, 200)
    ctx.bezierCurveTo(280,200, 240,220, 240,280)
    ctx.closePath()
    ctx.fill("evenodd")

    // Frame edge texture
    ctx.strokeStyle = "rgba(42,6,18,0.18)"; ctx.lineWidth = 0.6
    var texLines = [60,100,140,180, 1780,1820,1860]
    for (var tl = 0; tl < texLines.length; tl++) {
        ctx.beginPath(); ctx.moveTo(texLines[tl],0); ctx.lineTo(texLines[tl],1080); ctx.stroke()
    }

    // Inner opening gold trim
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 4
    ctx.beginPath()
    ctx.moveTo(240,960); ctx.lineTo(1680,960); ctx.lineTo(1680,280)
    ctx.bezierCurveTo(1680,220,1640,200,1580,200); ctx.lineTo(340,200)
    ctx.bezierCurveTo(280,200,240,220,240,280); ctx.closePath(); ctx.stroke()
    ctx.strokeStyle = "rgba(233,201,124,0.85)"; ctx.lineWidth = 1.2
    ctx.beginPath()
    ctx.moveTo(244,956); ctx.lineTo(1676,956); ctx.lineTo(1676,280)
    ctx.bezierCurveTo(1676,222,1638,204,1580,204); ctx.lineTo(340,204)
    ctx.bezierCurveTo(282,204,244,222,244,280); ctx.closePath(); ctx.stroke()

    // Outer gold trim
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 2.5
    ctx.strokeRect(10, 10, 1900, 1060)
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 0.8
    ctx.strokeRect(14, 14, 1892, 1052)

    // ── 9. FRAME ORNAMENTS ───────────────────────────────────────
    // Corner medallions
    _floret(ctx, 140, 130, 56)   // TL
    _floret(ctx, 1780, 130, 56)  // TR
    _floret(ctx, 140, 1020, 48)  // BL
    _floret(ctx, 1780, 1020, 48) // BR

    // Side ornament chains
    _sideChain(ctx, 120, false)  // left
    _sideChain(ctx, 1800, true)  // right

    // Top frame horizontal pinstripes (above opening)
    ctx.strokeStyle = "rgba(201,138,58,0.7)"; ctx.lineWidth = 1.2
    ctx.beginPath(); ctx.moveTo(240,180); ctx.lineTo(1680,180); ctx.stroke()
    ctx.strokeStyle = "rgba(138,90,32,0.7)"; ctx.lineWidth = 0.8
    ctx.beginPath(); ctx.moveTo(240,184); ctx.lineTo(1680,184); ctx.stroke()

    // Bottom frieze
    ctx.save(); ctx.translate(0, 1010)
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 1.5
    ctx.beginPath(); ctx.moveTo(240,0); ctx.lineTo(1680,0); ctx.stroke()
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 0.8
    ctx.beginPath(); ctx.moveTo(240,4); ctx.lineTo(1680,4); ctx.stroke()
    for (var bx = 280; bx <= 1640; bx += 60) {
        ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 1.2
        ctx.beginPath()
        ctx.arc(bx, 30, 20, Math.PI, 0)
        ctx.stroke()
        ctx.fillStyle = "#e9c97c"
        ctx.beginPath(); ctx.arc(bx, 30, 2, 0, Math.PI*2); ctx.fill()
        ctx.fillStyle = "#c98a3a"
        ctx.beginPath(); ctx.arc(bx+30, 38, 1.2, 0, Math.PI*2); ctx.fill()
    }
    ctx.restore()

    // ── 10. TITLE CARTOUCHE ─────────────────────────────────────
    ctx.save(); ctx.translate(960, 100)
    var cGrad = ctx.createLinearGradient(0,-75, 0,75)
    cGrad.addColorStop(0, "#6e1832"); cGrad.addColorStop(0.5,"#4a0e22"); cGrad.addColorStop(1,"#2a0612")
    ctx.fillStyle = cGrad
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 3
    _roundRect(ctx, -380,-45, 760,90, 20); ctx.fill(); ctx.stroke()
    ctx.strokeStyle = "rgba(233,201,124,0.8)"; ctx.lineWidth = 1
    _roundRect(ctx, -370,-40, 740,80, 16); ctx.stroke()
    // Cartouche dots
    ctx.fillStyle = "#e9c97c"
    var cdots = [-340,-280,-200,-120,-40,40,120,200,280,340]
    for (var cd = 0; cd < cdots.length; cd++) {
        ctx.beginPath(); ctx.arc(cdots[cd],-68,1.5,0,Math.PI*2); ctx.fill()
        ctx.beginPath(); ctx.arc(cdots[cd],68,1.5,0,Math.PI*2); ctx.fill()
    }
    // Title text
    ctx.fillStyle = "#e9c97c"
    ctx.font = "bold 52px serif"
    ctx.textAlign = "center"; ctx.textBaseline = "middle"
    ctx.shadowColor = "#5a3a14"; ctx.shadowBlur = 2
    ctx.fillText("NCDE COMMAND", 0, 8)
    ctx.shadowBlur = 0
    ctx.restore()

    // ── 11. FOOTLIGHTS (lamp row) ─────────────────────────────────
    for (var li = 0; li < fCount; li++) {
        var lt = li/(fCount-1), lx = fStartX + lt*(fEndX-fStartX)
        var lisc = Math.abs(li-(fCount-1)/2) < 0.6 ? 1.25 : 1
        _lamp(ctx, lx, fY, lisc)
    }

    // Stage floor edge
    ctx.fillStyle = "#0a0710"
    ctx.fillRect(240, 950, 1440, 20)
    ctx.strokeStyle = "#3a2010"; ctx.lineWidth = 1
    ctx.beginPath(); ctx.moveTo(240,950); ctx.lineTo(1680,950); ctx.stroke()

    ctx.restore() // end scale+translate
}

// ── helper: tassel ───────────────────────────────────────────────
function _tassel(ctx, x, y, rx, ry, rEh, tailLen) {
    ctx.fillStyle = "#c98a3a"
    ctx.strokeStyle = "#8a5a20"
    ctx.lineWidth = 1.5
    ctx.beginPath(); ctx.ellipse(x, y+ry-rEh, rx, ry, 0, 0, Math.PI*2); ctx.fill()
    ctx.fillStyle = "rgba(233,201,124,0.7)"
    ctx.beginPath(); ctx.ellipse(x-rx*0.2, y+ry-rEh-ry*0.3, rx*0.7, ry*0.4, 0, 0, Math.PI*2); ctx.fill()
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 1.3
    var nStrands = 4
    for (var ts = 0; ts < nStrands; ts++) {
        var tdx = (ts - (nStrands-1)/2) * (rx * 0.55)
        ctx.beginPath(); ctx.moveTo(x+tdx, y+ry*2-rEh); ctx.lineTo(x+tdx, y+ry*2-rEh+tailLen); ctx.stroke()
    }
}

// ── helper: lamp ─────────────────────────────────────────────────
function _lamp(ctx, x, y, sc) {
    ctx.save(); ctx.translate(x, y); ctx.scale(sc, sc)
    // Brass dome
    ctx.fillStyle = "#5a3a14"
    ctx.beginPath(); ctx.ellipse(0,0,28,14,0,0,Math.PI*2); ctx.fill()
    ctx.fillStyle = "#8a5a20"
    ctx.beginPath(); ctx.ellipse(0,-2,26,12,0,0,Math.PI*2); ctx.fill()
    // Glass bulb glow
    var lg = ctx.createRadialGradient(-6,-18,0, 0,-12,22)
    lg.addColorStop(0.00,"#fff8d0"); lg.addColorStop(0.40,"#ffd680")
    lg.addColorStop(0.80,"#f6a648"); lg.addColorStop(1.00,"#c9602a")
    ctx.fillStyle = lg
    ctx.beginPath(); ctx.arc(0,-12,22,0,Math.PI*2); ctx.fill()
    // Hotspot
    var lh = ctx.createRadialGradient(-6,-18,0, -6,-18,10)
    lh.addColorStop(0,"rgba(255,255,255,0.95)"); lh.addColorStop(1,"rgba(255,255,255,0)")
    ctx.fillStyle = lh
    ctx.beginPath(); ctx.arc(-6,-18,10,0,Math.PI*2); ctx.fill()
    // Decorative ring
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 1.5
    ctx.beginPath(); ctx.ellipse(0,-2,24,3,0,0,Math.PI*2); ctx.stroke()
    // Finial
    ctx.fillStyle = "#8a5a20"; ctx.fillRect(-4,-38,8,6)
    ctx.fillStyle = "#c98a3a"
    ctx.beginPath(); ctx.arc(0,-42,3,0,Math.PI*2); ctx.fill()
    ctx.restore()
}

// ── helper: floret medallion ─────────────────────────────────────
function _floret(ctx, x, y, r) {
    var mg = ctx.createRadialGradient(x,y,0, x,y,r)
    mg.addColorStop(0,"#f6e3b0"); mg.addColorStop(0.6,"#c98a3a"); mg.addColorStop(1,"#5a3a14")
    ctx.fillStyle = mg
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1.5
    ctx.beginPath(); ctx.arc(x,y,r,0,Math.PI*2); ctx.fill(); ctx.stroke()
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 0.8
    ctx.beginPath(); ctx.arc(x,y,r*0.9,0,Math.PI*2); ctx.stroke()
    // 8 petals
    ctx.fillStyle = "rgba(90,58,20,0.85)"
    for (var pi = 0; pi < 8; pi++) {
        var pa = (pi/8)*Math.PI*2, pr = r*0.55
        ctx.save(); ctx.translate(x,y); ctx.rotate(pa)
        ctx.beginPath(); ctx.ellipse(0,-pr, r*0.12, r*0.30, 0, 0, Math.PI*2); ctx.fill()
        ctx.restore()
    }
    // Center disc
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.arc(x,y,r*0.25,0,Math.PI*2); ctx.fill()
    ctx.fillStyle = "#5a3a14"
    ctx.beginPath(); ctx.arc(x,y,r*0.10,0,Math.PI*2); ctx.fill()
}

// ── helper: side ornament chain ───────────────────────────────────
function _sideChain(ctx, x, mirrorX) {
    var flip = mirrorX ? -1 : 1
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 1.5
    ctx.beginPath(); ctx.moveTo(x,240); ctx.lineTo(x,920); ctx.stroke()
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 0.8
    ctx.beginPath(); ctx.moveTo(x-3*flip,240); ctx.lineTo(x-3*flip,920); ctx.stroke()
    ctx.beginPath(); ctx.moveTo(x+3*flip,240); ctx.lineTo(x+3*flip,920); ctx.stroke()
    var chainY = [300,460,580,720,860]
    var chainSc = [0.85, 0.70, 0.90, 0.70, 0.85]
    for (var ci = 0; ci < chainY.length; ci++) {
        _floret(ctx, x, chainY[ci], 32*chainSc[ci])
    }
    var wlY = [[340,460],[480,580],[620,720],[740,860]]
    for (var wi = 0; wi < wlY.length; wi++) {
        var wy0 = wlY[wi][0], wy1 = wlY[wi][1]
        ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 1.2
        ctx.beginPath()
        ctx.moveTo(x, wy0)
        ctx.bezierCurveTo(x - 20*flip, (wy0+wy1)/2-20, x + 20*flip, (wy0+wy1)/2+20, x, wy1)
        ctx.stroke()
    }
}

// ── helper: rounded rect path ─────────────────────────────────────
function _roundRect(ctx, x, y, w, h, r) {
    ctx.beginPath()
    ctx.moveTo(x+r, y)
    ctx.lineTo(x+w-r, y); ctx.arcTo(x+w, y, x+w, y+r, r)
    ctx.lineTo(x+w, y+h-r); ctx.arcTo(x+w, y+h, x+w-r, y+h, r)
    ctx.lineTo(x+r, y+h); ctx.arcTo(x, y+h, x, y+h-r, r)
    ctx.lineTo(x, y+r); ctx.arcTo(x, y, x+r, y, r)
    ctx.closePath()
}
