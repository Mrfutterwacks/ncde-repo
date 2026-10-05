// ═══════════════════════════════════════════════════════════════
//  NCDE MUCHA PORTRAIT FRAME
//  Tall Art Nouveau frame with arched photo opening + gold halo
//  Call: drawPortraitFrame(ctx, w, h)
//  Designed in 1200×1700 space; auto-scales to any canvas size.
//  Returns { ox, oy, ow, oh } — icon opening rect in canvas px.
//  The opening has an arched top:
//    left=200, right=1000, archTop≈280 (arch peak), bottom=1380
// ═══════════════════════════════════════════════════════════════
.pragma library

function drawPortraitFrame(ctx, w, h) {
    var sx = w / 1200, sy = h / 1700
    ctx.save()
    ctx.scale(sx, sy)

    // ── PAPER BACKGROUND ─────────────────────────────────────────
    var paper = ctx.createLinearGradient(0,0, 0,1700)
    paper.addColorStop(0.00, "#f6efdc")
    paper.addColorStop(0.50, "#ece2c6")
    paper.addColorStop(1.00, "#d8cba8")
    ctx.fillStyle = paper
    ctx.fillRect(0, 0, 1200, 1700)

    // Dot mesh
    ctx.fillStyle = "rgba(138,90,32,0.12)"
    for (var dx = 12; dx < 1200; dx += 24) {
        for (var dy = 12; dy < 1700; dy += 24) {
            ctx.beginPath(); ctx.arc(dx, dy, 0.6, 0, Math.PI*2); ctx.fill()
        }
    }

    // ── HALO DISK (behind image) ──────────────────────────────────
    var haloGlow = ctx.createRadialGradient(600,540,0, 600,540,380)
    haloGlow.addColorStop(0.00,"rgba(246,227,176,0.95)")
    haloGlow.addColorStop(0.50,"rgba(233,201,124,0.75)")
    haloGlow.addColorStop(0.90,"rgba(201,138,58,0.4)")
    haloGlow.addColorStop(1.00,"rgba(201,138,58,0)")
    ctx.fillStyle = haloGlow
    ctx.beginPath(); ctx.arc(600,540,380,0,Math.PI*2); ctx.fill()

    var haloDisk = ctx.createRadialGradient(480,432,0, 600,540,300)
    haloDisk.addColorStop(0.00,"#f6e3b0"); haloDisk.addColorStop(0.70,"#e9c97c"); haloDisk.addColorStop(1.00,"#b07a30")
    ctx.fillStyle = haloDisk
    ctx.beginPath(); ctx.arc(600,540,300,0,Math.PI*2); ctx.fill()

    // Halo rings
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 2
    ctx.beginPath(); ctx.arc(600,540,300,0,Math.PI*2); ctx.stroke()
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 0.8
    ctx.beginPath(); ctx.arc(600,540,294,0,Math.PI*2); ctx.stroke()
    ctx.strokeStyle = "rgba(138,90,32,0.6)"; ctx.lineWidth = 0.8
    ctx.beginPath(); ctx.arc(600,540,280,0,Math.PI*2); ctx.stroke()
    ctx.strokeStyle = "rgba(138,90,32,0.5)"; ctx.lineWidth = 1.2
    ctx.beginPath(); ctx.arc(600,540,260,0,Math.PI*2); ctx.stroke()

    // Halo rays
    ctx.strokeStyle = "rgba(138,90,32,0.45)"; ctx.lineWidth = 0.5
    for (var ri = 0; ri < 48; ri++) {
        var ang = (ri/48)*Math.PI*2
        var ir = 200, or = (ri%2===0)?290:260
        ctx.beginPath()
        ctx.moveTo(600+Math.cos(ang)*ir, 540+Math.sin(ang)*ir)
        ctx.lineTo(600+Math.cos(ang)*or, 540+Math.sin(ang)*or)
        ctx.stroke()
    }

    // Halo 4-point stars
    ctx.fillStyle = "rgba(90,58,20,0.7)"
    for (var si = 0; si < 16; si++) {
        var sang = (si/16)*Math.PI*2 + Math.PI/16
        var hsx = 600 + Math.cos(sang)*240, hsy = 540 + Math.sin(sang)*240
        ctx.save(); ctx.translate(hsx, hsy)
        ctx.beginPath()
        ctx.moveTo(0,-7); ctx.lineTo(2,-2); ctx.lineTo(7,0); ctx.lineTo(2,2)
        ctx.lineTo(0,7); ctx.lineTo(-2,2); ctx.lineTo(-7,0); ctx.lineTo(-2,-2)
        ctx.closePath(); ctx.fill()
        ctx.restore()
    }

    // ── OUTER FRAME BORDERS ──────────────────────────────────────
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 3
    ctx.strokeRect(50, 50, 1100, 1600)
    ctx.strokeStyle = "rgba(233,201,124,0.8)"; ctx.lineWidth = 1
    ctx.strokeRect(54, 54, 1092, 1592)
    ctx.strokeStyle = "rgba(138,90,32,0.6)"; ctx.lineWidth = 1
    ctx.strokeRect(62, 62, 1076, 1576)

    // Outer dots
    ctx.fillStyle = "#5a3a14"
    for (var obx = 80; obx <= 1120; obx += 24) {
        ctx.beginPath(); ctx.arc(obx,58,0.9,0,Math.PI*2); ctx.fill()
        ctx.beginPath(); ctx.arc(obx,1642,0.9,0,Math.PI*2); ctx.fill()
    }
    for (var oby = 80; oby <= 1620; oby += 24) {
        ctx.beginPath(); ctx.arc(58,oby,0.9,0,Math.PI*2); ctx.fill()
        ctx.beginPath(); ctx.arc(1142,oby,0.9,0,Math.PI*2); ctx.fill()
    }

    // ── TOP + BOTTOM BAND PINSTRIPES ─────────────────────────────
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 2
    ctx.beginPath(); ctx.moveTo(80,140); ctx.lineTo(1120,140); ctx.stroke()
    ctx.beginPath(); ctx.moveTo(80,260); ctx.lineTo(1120,260); ctx.stroke()
    ctx.strokeStyle = "rgba(233,201,124,0.7)"; ctx.lineWidth = 0.8
    ctx.beginPath(); ctx.moveTo(80,146); ctx.lineTo(1120,146); ctx.stroke()
    ctx.beginPath(); ctx.moveTo(80,254); ctx.lineTo(1120,254); ctx.stroke()

    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 2
    ctx.beginPath(); ctx.moveTo(80,1400); ctx.lineTo(1120,1400); ctx.stroke()
    ctx.beginPath(); ctx.moveTo(80,1560); ctx.lineTo(1120,1560); ctx.stroke()

    // ── TOP CROWN ORNAMENT ───────────────────────────────────────
    _floret8PF(ctx, 600, 200, 45)
    // Flanking iris
    ctx.save(); ctx.translate(380, 200); _irisPF(ctx); ctx.restore()
    ctx.save(); ctx.translate(820, 200); _irisPF(ctx); ctx.restore()
    // Whiplash curves flanking crown
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 2
    ctx.beginPath(); ctx.moveTo(420,-10+200); ctx.bezierCurveTo(480,-50+200,520,-50+200,550,-20+200); ctx.stroke()
    ctx.beginPath(); ctx.moveTo(780,-10+200); ctx.bezierCurveTo(720,-50+200,680,-50+200,650,-20+200); ctx.stroke()
    _floret6PF(ctx, 485, 162, 10); _floret6PF(ctx, 715, 162, 10)
    // Outer end blocks
    _bandBlock(ctx, 110, 200)
    _bandBlock(ctx, 1090, 200)

    // ── FOUR CORNER MEDALLIONS ───────────────────────────────────
    _floret8PF(ctx, 110, 110, 48)
    _floret8PF(ctx, 1090, 110, 48)
    _floret8PF(ctx, 110, 1590, 48)
    _floret8PF(ctx, 1090, 1590, 48)

    // ── LEFT SIDE ORNAMENT CHAIN ─────────────────────────────────
    _sideOrnament(ctx, 140, false)
    _sideOrnament(ctx, 1060, true)

    // ── ARCH BORDER (over image opening) ─────────────────────────
    // Inner gold arch
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 4
    _archPath(ctx, 200,500,600,280,1000,500,1000,1380,200,1380); ctx.stroke()
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 3
    _archPath(ctx, 196,500,600,276,1004,500,1004,1384,196,1384); ctx.stroke()
    ctx.strokeStyle = "rgba(233,201,124,0.9)"; ctx.lineWidth = 1
    _archPath(ctx, 200,500,600,280,1000,500,1000,1380,200,1380); ctx.stroke()

    // Keystone at top of arch
    ctx.fillStyle = "#c98a3a"; ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 2
    ctx.beginPath()
    ctx.moveTo(564,280); ctx.lineTo(636,280); ctx.lineTo(628,230); ctx.lineTo(572,230)
    ctx.closePath(); ctx.fill(); ctx.stroke()
    ctx.strokeStyle = "#e9c97c"; ctx.lineWidth = 1
    ctx.beginPath(); ctx.moveTo(572,230); ctx.lineTo(628,230); ctx.stroke()
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.arc(600,255,10,0,Math.PI*2); ctx.fill()
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1; ctx.stroke()
    ctx.fillStyle = "#5a3a14"
    ctx.beginPath(); ctx.arc(600,255,3,0,Math.PI*2); ctx.fill()

    // Arch beads (inside edge)
    ctx.fillStyle = "#e9c97c"
    for (var aby = 510; aby <= 1370; aby += 24) {
        ctx.beginPath(); ctx.arc(210,aby,2,0,Math.PI*2); ctx.fill()
        ctx.beginPath(); ctx.arc(990,aby,2,0,Math.PI*2); ctx.fill()
        ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 0.5; ctx.stroke()
    }
    for (var abx = 220; abx <= 980; abx += 24) {
        ctx.beginPath(); ctx.arc(abx,1370,2,0,Math.PI*2); ctx.fill()
    }
    // Arch top beads (bezier samples)
    for (var ai = 0; ai <= 24; ai += 2) {
        var t = ai/24
        var bex = (1-t)*(1-t)*210 + 2*(1-t)*t*600 + t*t*990
        var bey = (1-t)*(1-t)*500 + 2*(1-t)*t*280 + t*t*500
        ctx.beginPath(); ctx.arc(bex,bey,2,0,Math.PI*2); ctx.fill()
    }

    // ── BOTTOM PLINTH ────────────────────────────────────────────
    // Cartouche
    ctx.fillStyle = "#f6efdc"; ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 2.5
    _roundRectPF(ctx, 300,1405, 600,150, 20); ctx.fill(); ctx.stroke()
    ctx.strokeStyle = "#b07a30"; ctx.lineWidth = 0.8
    _roundRectPF(ctx, 308,1412, 584,136, 16); ctx.stroke()
    // Corner dots
    ctx.fillStyle = "#5a3a14"
    [[315,1420],[885,1420],[315,1555],[885,1555]].forEach(function(pt) {
        ctx.beginPath(); ctx.arc(pt[0],pt[1],2,0,Math.PI*2); ctx.fill()
    })
    // Plinth flanking florets
    _floret8PF(ctx, 220, 1480, 29)
    _floret8PF(ctx, 980, 1480, 29)

    ctx.restore() // end scale

    // Return icon opening in canvas-pixel coords
    // Arch opening: x:200→1000, arch peak y≈280, bottom y=1380
    return {
        ox: 200*sx, oy: 280*sy,
        ow: 800*sx, oh: 1100*sy
    }
}

// ── helpers ───────────────────────────────────────────────────────

function _medGradPF(ctx, x, y, r) {
    var g = ctx.createRadialGradient(x,y,0, x,y,r)
    g.addColorStop(0,"#f6e3b0"); g.addColorStop(0.6,"#c98a3a"); g.addColorStop(1,"#5a3a14")
    return g
}

function _floret8PF(ctx, x, y, r) {
    ctx.fillStyle = _medGradPF(ctx,x,y,r)
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1.2
    ctx.beginPath(); ctx.arc(x,y,r,0,Math.PI*2); ctx.fill(); ctx.stroke()
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 0.6
    ctx.beginPath(); ctx.arc(x,y,r*0.875,0,Math.PI*2); ctx.stroke()
    ctx.fillStyle = "rgba(90,58,20,0.8)"
    for (var pi = 0; pi < 8; pi++) {
        var pa = (pi/8)*Math.PI*2
        ctx.save(); ctx.translate(x,y); ctx.rotate(pa)
        ctx.beginPath(); ctx.ellipse(0,-r*0.5625, r*0.11, r*0.28, 0, 0, Math.PI*2); ctx.fill()
        ctx.restore()
    }
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.arc(x,y,r*0.25,0,Math.PI*2); ctx.fill()
    ctx.fillStyle = "#5a3a14"
    ctx.beginPath(); ctx.arc(x,y,r*0.09,0,Math.PI*2); ctx.fill()
}

function _floret6PF(ctx, x, y, r) {
    ctx.fillStyle = _medGradPF(ctx,x,y,r)
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1
    ctx.beginPath(); ctx.arc(x,y,r,0,Math.PI*2); ctx.fill(); ctx.stroke()
    ctx.fillStyle = "rgba(90,58,20,0.75)"
    for (var pi = 0; pi < 6; pi++) {
        var pa = (pi/6)*Math.PI*2
        ctx.save(); ctx.translate(x,y); ctx.rotate(pa)
        ctx.beginPath(); ctx.ellipse(0,-r*0.56, r*0.13, r*0.31, 0, 0, Math.PI*2); ctx.fill()
        ctx.restore()
    }
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.arc(x,y,r*0.19,0,Math.PI*2); ctx.fill()
}

function _irisPF(ctx) {
    var ig = ctx.createRadialGradient(0,0,0, 0,-18,22)
    ig.addColorStop(0,"#f6e3b0"); ig.addColorStop(0.6,"#c98a3a"); ig.addColorStop(1,"#5a3a14")
    ctx.fillStyle = ig; ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1
    ctx.beginPath(); ctx.moveTo(0,0); ctx.bezierCurveTo(-20,-10,-28,-30,-18,-50)
    ctx.bezierCurveTo(-8,-42,-2,-28,0,-10); ctx.closePath(); ctx.fill(); ctx.stroke()
    ctx.beginPath(); ctx.moveTo(0,0); ctx.bezierCurveTo(20,-10,28,-30,18,-50)
    ctx.bezierCurveTo(8,-42,2,-28,0,-10); ctx.closePath(); ctx.fill(); ctx.stroke()
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.moveTo(0,0); ctx.bezierCurveTo(-8,-18,-4,-42,0,-56)
    ctx.bezierCurveTo(4,-42,8,-18,0,0); ctx.closePath(); ctx.fill(); ctx.stroke()
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1.5
    ctx.beginPath(); ctx.moveTo(0,0); ctx.lineTo(0,60); ctx.stroke()
}

function _bandBlock(ctx, x, y) {
    ctx.save(); ctx.translate(x, y)
    ctx.fillStyle = "url(#checkered)"; // plain fill fallback
    ctx.fillStyle = "#8a5a20"
    ctx.fillRect(-30,-50,60,100)
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1.5
    ctx.strokeRect(-30,-50,60,100)
    _floret6PF(ctx, 0, 0, 16)
    ctx.restore()
}

function _archPath(ctx, lx,ly, topX,topY, rx,ry, rbx,rby, lbx,lby) {
    // Draws arch path: left side up → bezier arch top → right side down → bottom
    ctx.beginPath()
    ctx.moveTo(lx, ly)
    ctx.quadraticCurveTo(topX, topY, rx, ry)
    ctx.lineTo(rbx, rby)
    ctx.lineTo(lbx, lby)
    ctx.closePath()
}

function _sideOrnament(ctx, x, flipX) {
    var flip = flipX ? -1 : 1
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 1.5
    ctx.beginPath(); ctx.moveTo(x,280); ctx.lineTo(x,1380); ctx.stroke()
    ctx.strokeStyle = "#b07a30"; ctx.lineWidth = 0.6
    ctx.beginPath(); ctx.moveTo(x-3,280); ctx.lineTo(x-3,1380); ctx.stroke()
    ctx.beginPath(); ctx.moveTo(x+3,280); ctx.lineTo(x+3,1380); ctx.stroke()

    var ornY = [360,480,620,760,900,1040,1180,1320]
    var useFloret = [true,false,true,false,true,false,true,false]
    for (var oi = 0; oi < ornY.length; oi++) {
        if (useFloret[oi]) {
            _floret8PF(ctx, x, ornY[oi], 30)
        } else {
            // iris
            ctx.save(); ctx.translate(x, ornY[oi])
            ctx.rotate(flip < 0 ? 0 : Math.PI)
            ctx.scale(0.85,0.85); _irisPF(ctx)
            ctx.restore()
        }
    }
    // Whiplash connectors
    var wlPairs = [[400,480],[540,620],[660,760],[800,900],[940,1040],[1080,1180],[1220,1320]]
    for (var wi = 0; wi < wlPairs.length; wi++) {
        var wy0 = wlPairs[wi][0], wy1 = wlPairs[wi][1]
        ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 1.2
        ctx.beginPath(); ctx.moveTo(x, wy0)
        ctx.bezierCurveTo(x-22*flip,(wy0+wy1)/2-20, x+22*flip,(wy0+wy1)/2+20, x, wy1)
        ctx.stroke()
    }
    // Hash marks
    ctx.strokeStyle = "rgba(138,90,32,0.6)"; ctx.lineWidth = 0.8
    var hashY = [320,440,560,680,800,920,1040,1160,1280]
    for (var hi = 0; hi < hashY.length; hi++) {
        var hx0 = flip < 0 ? x-50 : x+30
        var hx1 = flip < 0 ? x-30 : x+50
        ctx.beginPath(); ctx.moveTo(hx0, hashY[hi]); ctx.lineTo(hx1, hashY[hi]); ctx.stroke()
    }
}

function _roundRectPF(ctx, x, y, w, h, r) {
    ctx.beginPath()
    ctx.moveTo(x+r,y); ctx.lineTo(x+w-r,y); ctx.arcTo(x+w,y,x+w,y+r,r)
    ctx.lineTo(x+w,y+h-r); ctx.arcTo(x+w,y+h,x+w-r,y+h,r)
    ctx.lineTo(x+r,y+h); ctx.arcTo(x,y+h,x,y+h-r,r)
    ctx.lineTo(x,y+r); ctx.arcTo(x,y,x+r,y,r); ctx.closePath()
}
