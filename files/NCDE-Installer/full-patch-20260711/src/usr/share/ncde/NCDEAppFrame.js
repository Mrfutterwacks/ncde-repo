// ═══════════════════════════════════════════════════════════════
//  NCDE MUCHA SQUARE APP FRAME
//  Art Nouveau ornate gold-on-ivory square frame for app icons
//  Call: drawAppFrame(ctx, w, h)
//  Designed in 800×800 space; auto-scales to any canvas size.
//  Opening (icon area) is 520/800 = 65% of width at center.
//  Returns { ox, oy, ow, oh } — pixel rect of the icon opening
//  (in canvas pixel coords, not 800×800 space).
// ═══════════════════════════════════════════════════════════════
.pragma library

function drawAppFrame(ctx, w, h) {
    var sx = w / 800, sy = h / 800
    ctx.save()
    ctx.scale(sx, sy)

    // ── PAPER BACKGROUND ─────────────────────────────────────────
    var paper = ctx.createLinearGradient(0,0, 800,800)
    paper.addColorStop(0.00, "#f6efdc")
    paper.addColorStop(0.50, "#ece2c6")
    paper.addColorStop(1.00, "#d8cba8")
    ctx.fillStyle = paper
    ctx.fillRect(0, 0, 800, 800)

    // Subtle dot mesh
    ctx.fillStyle = "rgba(138,90,32,0.12)"
    for (var dx = 11; dx < 800; dx += 22) {
        for (var dy = 11; dy < 800; dy += 22) {
            ctx.beginPath(); ctx.arc(dx, dy, 0.55, 0, Math.PI*2); ctx.fill()
        }
    }

    // ── OUTER GOLD BORDERS ───────────────────────────────────────
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 2.5
    ctx.strokeRect(30, 30, 740, 740)
    ctx.strokeStyle = "rgba(233,201,124,0.8)"; ctx.lineWidth = 0.8
    ctx.strokeRect(34, 34, 732, 732)
    ctx.strokeStyle = "rgba(138,90,32,0.6)"; ctx.lineWidth = 0.8
    ctx.strokeRect(42, 42, 716, 716)

    // Outer bead dots (skip near medallion positions)
    var skipPts = [[95,46],[705,46],[95,754],[705,754],
                   [46,95],[754,95],[46,705],[754,705],
                   [400,46],[400,754],[46,400],[754,400]]
    function nearSkip(x, y) {
        for (var k = 0; k < skipPts.length; k++) {
            var dx2=x-skipPts[k][0], dy2=y-skipPts[k][1]
            if (Math.sqrt(dx2*dx2+dy2*dy2) < 60) return true
        }
        return false
    }
    ctx.fillStyle = "rgba(90,58,20,0.65)"
    for (var bx = 60; bx <= 740; bx += 18) {
        if (!nearSkip(bx,46))  { ctx.beginPath(); ctx.arc(bx,46,1,0,Math.PI*2); ctx.fill() }
        if (!nearSkip(bx,754)) { ctx.beginPath(); ctx.arc(bx,754,1,0,Math.PI*2); ctx.fill() }
    }
    for (var by = 60; by <= 740; by += 18) {
        if (!nearSkip(46,by))  { ctx.beginPath(); ctx.arc(46,by,1,0,Math.PI*2); ctx.fill() }
        if (!nearSkip(754,by)) { ctx.beginPath(); ctx.arc(754,by,1,0,Math.PI*2); ctx.fill() }
    }

    // ── INNER BORDER (around icon opening 140,140 → 660,660) ─────
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 4
    ctx.strokeRect(124, 124, 552, 552)
    ctx.strokeStyle = "#c98a3a"; ctx.lineWidth = 2.5
    ctx.strokeRect(128, 128, 544, 544)
    ctx.strokeStyle = "rgba(233,201,124,0.9)"; ctx.lineWidth = 1
    ctx.strokeRect(132, 132, 536, 536)
    ctx.strokeStyle = "rgba(138,90,32,0.55)"; ctx.lineWidth = 0.6
    ctx.strokeRect(138, 138, 524, 524)

    // Inner bead dots
    ctx.fillStyle = "#e9c97c"
    for (var ibx = 160; ibx <= 640; ibx += 20) {
        ctx.beginPath(); ctx.arc(ibx, 148, 1.8, 0, Math.PI*2); ctx.fill()
        ctx.beginPath(); ctx.arc(ibx, 652, 1.8, 0, Math.PI*2); ctx.fill()
    }
    for (var iby = 160; iby <= 640; iby += 20) {
        ctx.beginPath(); ctx.arc(148, iby, 1.8, 0, Math.PI*2); ctx.fill()
        ctx.beginPath(); ctx.arc(652, iby, 1.8, 0, Math.PI*2); ctx.fill()
    }
    // Corner accent beads
    ctx.fillStyle = "#c98a3a"
    var ibCorners = [[148,148],[652,148],[148,652],[652,652]]
    for (var ibc = 0; ibc < ibCorners.length; ibc++) {
        ctx.beginPath(); ctx.arc(ibCorners[ibc][0], ibCorners[ibc][1], 3, 0, Math.PI*2); ctx.fill()
        ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 0.6; ctx.stroke()
    }

    // ── FOUR CORNER MEDALLIONS ───────────────────────────────────
    var corners = [[95,95,45,1],[705,95,135,1],[95,705,-45,1],[705,705,-135,1]]
    for (var ci = 0; ci < corners.length; ci++) {
        var cx2=corners[ci][0], cy2=corners[ci][1], crot=corners[ci][2]
        // Backing disk
        var cmg = ctx.createRadialGradient(cx2,cy2,0, cx2,cy2,46)
        cmg.addColorStop(0,"#f6e3b0"); cmg.addColorStop(0.6,"#c98a3a"); cmg.addColorStop(1,"#5a3a14")
        ctx.fillStyle = cmg
        ctx.beginPath(); ctx.arc(cx2,cy2,46,0,Math.PI*2); ctx.fill()
        ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1.5; ctx.stroke()
        ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 0.6
        ctx.beginPath(); ctx.arc(cx2,cy2,42,0,Math.PI*2); ctx.stroke()
        _floret8(ctx, cx2, cy2, 32)
        // 45° leaf
        ctx.save(); ctx.translate(cx2,cy2); ctx.rotate(crot*Math.PI/180)
        _leaf(ctx, 0, 60, 0.7)
        ctx.restore()
    }

    // ── MID-EDGE MEDALLIONS ──────────────────────────────────────
    var meds = [
        [400,95,  [[-86,0,0],[86,0,0]]],          // top
        [400,705, [[-86,0,180],[86,0,180]]],        // bottom
        [95,400,  [[0,-86,90],[0,86,-90]]],         // left
        [705,400, [[0,-86,-90],[0,86,90]]]          // right
    ]
    for (var mi = 0; mi < meds.length; mi++) {
        var mx = meds[mi][0], my = meds[mi][1]
        var mmg = ctx.createRadialGradient(mx,my,0, mx,my,36)
        mmg.addColorStop(0,"#f6e3b0"); mmg.addColorStop(0.6,"#c98a3a"); mmg.addColorStop(1,"#5a3a14")
        ctx.fillStyle = mmg
        ctx.beginPath(); ctx.arc(mx,my,36,0,Math.PI*2); ctx.fill()
        ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1.3; ctx.stroke()
        ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 0.6
        ctx.beginPath(); ctx.arc(mx,my,32,0,Math.PI*2); ctx.stroke()
        _floret8(ctx, mx, my, 28)
        // Iris flanks
        var flanks = meds[mi][2]
        for (var fli = 0; fli < flanks.length; fli++) {
            ctx.save()
            ctx.translate(mx+flanks[fli][0], my+flanks[fli][1])
            ctx.rotate(flanks[fli][2]*Math.PI/180); ctx.scale(0.9,0.9)
            _iris(ctx, 0, 0)
            ctx.restore()
        }
    }

    // ── WHIPLASH CONNECTORS ──────────────────────────────────────
    // Top edge: TL→top_center, top_center→TR
    _whiplash(ctx, 145,95, 200,80, 260,110, 360,95)
    _whiplash(ctx, 440,95, 540,110, 600,80, 655,95)
    // Bottom edge
    _whiplash(ctx, 145,705, 200,690, 260,720, 360,705)
    _whiplash(ctx, 440,705, 540,720, 600,690, 655,705)
    // Left side
    _whiplash(ctx, 95,145, 80,200, 110,260, 95,360)
    _whiplash(ctx, 95,440, 110,540, 80,600, 95,655)
    // Right side
    _whiplash(ctx, 705,145, 720,200, 690,260, 705,360)
    _whiplash(ctx, 705,440, 690,540, 720,600, 705,655)

    // Small floret6 accents on whiplash curves
    var wfPos = [
        [195,96],[315,96],[485,96],[605,96],
        [195,706],[315,706],[485,706],[605,706],
        [96,195],[96,315],[96,485],[96,605],
        [704,195],[704,315],[704,485],[704,605],
    ]
    for (var wfi = 0; wfi < wfPos.length; wfi++) {
        _floret6(ctx, wfPos[wfi][0], wfPos[wfi][1], 8)
    }

    // Leaf accents on curves
    ctx.save(); ctx.translate(255,80); ctx.rotate(-15*Math.PI/180); _leaf(ctx,0,0,0.55); ctx.restore()
    ctx.save(); ctx.translate(545,80); ctx.rotate(15*Math.PI/180);  _leaf(ctx,0,0,0.55); ctx.restore()
    ctx.save(); ctx.translate(255,690); ctx.rotate(-15*Math.PI/180);_leaf(ctx,0,0,0.55); ctx.restore()
    ctx.save(); ctx.translate(545,690); ctx.rotate(15*Math.PI/180);  _leaf(ctx,0,0,0.55); ctx.restore()
    ctx.save(); ctx.translate(80,255); ctx.rotate(-105*Math.PI/180);_leaf(ctx,0,0,0.55); ctx.restore()
    ctx.save(); ctx.translate(80,545); ctx.rotate(-75*Math.PI/180); _leaf(ctx,0,0,0.55); ctx.restore()
    ctx.save(); ctx.translate(720,255);ctx.rotate(105*Math.PI/180); _leaf(ctx,0,0,0.55); ctx.restore()
    ctx.save(); ctx.translate(720,545);ctx.rotate(75*Math.PI/180);  _leaf(ctx,0,0,0.55); ctx.restore()

    // ── KEYSTONE PENDANT DROPS ───────────────────────────────────
    _pendant(ctx, 400,130, 0)
    _pendant(ctx, 400,670, 180)
    _pendant(ctx, 130,400, -90)
    _pendant(ctx, 670,400, 90)

    // ── CORNER DIAGONAL PINSTRIPES ───────────────────────────────
    ctx.strokeStyle = "rgba(138,90,32,0.5)"; ctx.lineWidth = 0.6
    var pinLines = [[55,95,75,95],[95,55,95,75],[745,95,725,95],[705,55,705,75],
                    [55,705,75,705],[95,745,95,725],[745,705,725,705],[705,745,705,725]]
    for (var pl = 0; pl < pinLines.length; pl++) {
        ctx.beginPath()
        ctx.moveTo(pinLines[pl][0],pinLines[pl][1])
        ctx.lineTo(pinLines[pl][2],pinLines[pl][3])
        ctx.stroke()
    }

    ctx.restore() // end scale

    // Return icon opening rect in canvas-pixel coords
    return { ox: 140*sx, oy: 140*sy, ow: 520*sx, oh: 520*sy }
}

// ── helpers ───────────────────────────────────────────────────────

function _medGrad(ctx, x, y, r) {
    var g = ctx.createRadialGradient(x,y,0, x,y,r)
    g.addColorStop(0,"#f6e3b0"); g.addColorStop(0.6,"#c98a3a"); g.addColorStop(1,"#5a3a14")
    return g
}

function _floret8(ctx, x, y, r) {
    ctx.fillStyle = _medGrad(ctx,x,y,r)
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1.2
    ctx.beginPath(); ctx.arc(x,y,r,0,Math.PI*2); ctx.fill(); ctx.stroke()
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 0.6
    ctx.beginPath(); ctx.arc(x,y,r*0.89,0,Math.PI*2); ctx.stroke()
    ctx.fillStyle = "rgba(90,58,20,0.85)"
    for (var pi = 0; pi < 8; pi++) {
        var pa = (pi/8)*Math.PI*2
        ctx.save(); ctx.translate(x,y); ctx.rotate(pa)
        ctx.beginPath(); ctx.ellipse(0,-r*0.57, r*0.11, r*0.30, 0, 0, Math.PI*2); ctx.fill()
        ctx.restore()
    }
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.arc(x,y,r*0.25,0,Math.PI*2); ctx.fill()
    ctx.fillStyle = "#5a3a14"
    ctx.beginPath(); ctx.arc(x,y,r*0.09,0,Math.PI*2); ctx.fill()
}

function _floret6(ctx, x, y, r) {
    ctx.fillStyle = _medGrad(ctx,x,y,r)
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 0.9
    ctx.beginPath(); ctx.arc(x,y,r,0,Math.PI*2); ctx.fill(); ctx.stroke()
    ctx.fillStyle = "rgba(90,58,20,0.8)"
    for (var pi = 0; pi < 6; pi++) {
        var pa = (pi/6)*Math.PI*2
        ctx.save(); ctx.translate(x,y); ctx.rotate(pa)
        ctx.beginPath(); ctx.ellipse(0,-r*0.57, r*0.13, r*0.32, 0, 0, Math.PI*2); ctx.fill()
        ctx.restore()
    }
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.arc(x,y,r*0.20,0,Math.PI*2); ctx.fill()
}

function _leaf(ctx, x, y, sc) {
    ctx.fillStyle = "#b07a30"; ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 0.7*sc
    ctx.save(); ctx.translate(x,y); ctx.scale(sc,sc)
    ctx.beginPath()
    ctx.moveTo(0,0); ctx.bezierCurveTo(-7,-6,-7,-22,0,-30)
    ctx.bezierCurveTo(7,-22,7,-6,0,0); ctx.closePath()
    ctx.fill(); ctx.stroke()
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 0.4
    ctx.beginPath(); ctx.moveTo(0,-2); ctx.lineTo(0,-26); ctx.stroke()
    ctx.restore()
}

function _iris(ctx, x, y) {
    ctx.save(); ctx.translate(x, y)
    var ig = ctx.createRadialGradient(0,0,0,0,-16,20)
    ig.addColorStop(0,"#f6e3b0"); ig.addColorStop(0.6,"#c98a3a"); ig.addColorStop(1,"#5a3a14")
    ctx.fillStyle = ig; ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 0.9
    // Left petal
    ctx.beginPath(); ctx.moveTo(0,0); ctx.bezierCurveTo(-12,-6,-18,-20,-12,-32)
    ctx.bezierCurveTo(-6,-26,-2,-18,0,-8); ctx.closePath(); ctx.fill(); ctx.stroke()
    // Right petal
    ctx.beginPath(); ctx.moveTo(0,0); ctx.bezierCurveTo(12,-6,18,-20,12,-32)
    ctx.bezierCurveTo(6,-26,2,-18,0,-8); ctx.closePath(); ctx.fill(); ctx.stroke()
    // Center
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.moveTo(0,0); ctx.bezierCurveTo(-5,-12,-3,-28,0,-36)
    ctx.bezierCurveTo(3,-28,5,-12,0,0); ctx.closePath(); ctx.fill(); ctx.stroke()
    // Stem
    ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1
    ctx.beginPath(); ctx.moveTo(0,0); ctx.lineTo(0,14); ctx.stroke()
    ctx.restore()
}

function _whiplash(ctx, x1,y1, cx1,cy1, cx2,cy2, x2,y2) {
    ctx.strokeStyle = "#8a5a20"; ctx.lineWidth = 2
    ctx.beginPath(); ctx.moveTo(x1,y1); ctx.bezierCurveTo(cx1,cy1,cx2,cy2,x2,y2); ctx.stroke()
    ctx.strokeStyle = "rgba(233,201,124,0.7)"; ctx.lineWidth = 0.8
    ctx.beginPath(); ctx.moveTo(x1,y1); ctx.bezierCurveTo(cx1,cy1,cx2,cy2,x2,y2); ctx.stroke()
}

function _pendant(ctx, x, y, rotDeg) {
    ctx.save(); ctx.translate(x, y); ctx.rotate(rotDeg*Math.PI/180)
    ctx.fillStyle = "#c98a3a"; ctx.strokeStyle = "#5a3a14"; ctx.lineWidth = 1
    ctx.beginPath()
    ctx.moveTo(0,0); ctx.bezierCurveTo(-6,8,-6,18,0,24)
    ctx.bezierCurveTo(6,18,6,8,0,0); ctx.closePath()
    ctx.fill(); ctx.stroke()
    ctx.fillStyle = "#e9c97c"
    ctx.beginPath(); ctx.arc(0, 14, 2, 0, Math.PI*2); ctx.fill()
    ctx.restore()
}
