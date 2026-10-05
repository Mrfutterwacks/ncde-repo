import QtQuick
import "mucha-clock.js" as Clock
import "ncde-color.js" as Col

// NCDEPowerRibbon — a powerline-style ribbon for the panels, in leaded glass
// (operator 2026-09-25: "ribbons strategically placed on top and bottom panel to
// mimic powerline polybars"). Each child laid into it becomes one segment: a pane
// of tinted glass, alternating the Iris accent and brass so neighbours read apart,
// (2026-09-25: each pane now takes one of the current wallpaper's own shades),
// divided by gilt came chevrons that point the way the bar runs (dir 1 = ▸ for a
// ribbon on the left of a panel, dir -1 = ◂ for one on the right). Each pane has an
// opaque body under the glass so its text reads over any wallpaper. The two outer
// ends are the same pointed tails, end jewels and double leading as the clock
// ribbon (Clock.paintGreetingBand), so the whole shell uses one ribbon language.
// Children are laid out in a Row; hidden children take no segment. The ribbon's
// width follows its content. Static: repaints on layout / theme / light changes
// only; no input of its own (the children keep theirs).
Item {
    id: rb
    default property alias content: row.data
    property int dir: 1                 // 1 = chevrons ▸, -1 = chevrons ◂
    property real pad: 5                // glass between a child and its chevron
    // the wallpaper's own shades (NCDEWallTones), one per segment in turn; until
    // the wallpaper has been read, the Iris accent and brass alternate instead
    property var tones: []
    property int seed: 0                // varies the panes between ribbons
    NCDEKit { id: k }
    onTonesChanged: cv.requestPaint()
    readonly property real bandH: height - 4
    readonly property real tail: Math.min(14, bandH * 0.55)
    readonly property real chev: Math.round(bandH * 0.36)   // chevron depth
    readonly property bool _hc: (typeof settings !== "undefined" && settings.highContrast === true)

    implicitWidth: row.width + 2 * (tail + pad) + 2
    width: implicitWidth
    height: parent ? parent.height : 28

    Canvas {
        id: cv
        anchors.fill: parent
        z: -1
        renderStrategy: Canvas.Cooperative
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        Connections { target: ncde; function onThemeChanged() { cv.requestPaint() } }
        Connections { target: ShellLight; function onSignatureChanged() { cv.requestPaint() } }
        Connections { target: row; function onPositioningComplete() { cv.requestPaint() } }

        // seeded per-pane jitter (the frames' Mulberry32): each pane is set at its own
        // tilt and has its own streaks and seed — fixed per pane, never shimmers
        function _jit(i, salt) {
            var t = ((i + 1) * 0x6D2B79F5 + (salt | 0) + rb.seed * 7919) | 0
            t = Math.imul(t ^ (t >>> 15), t | 1)
            t ^= t + Math.imul(t ^ (t >>> 7), t | 61)
            return ((t ^ (t >>> 14)) >>> 0) / 4294967296
        }
        function _css(c, a) { return Col.css(Qt.rgba(c.r, c.g, c.b, a)) }
        function _poly(ctx, pts) { ctx.beginPath(); ctx.moveTo(pts[0][0], pts[0][1]); for (var i = 1; i < pts.length; i++) ctx.lineTo(pts[i][0], pts[i][1]); ctx.closePath() }
        // a piece of jewel glass: deep at the edge away from the light, its own tone
        // in the body, a lit crest toward the light (same read as the frames' jewels)
        function _jewel(ctx, pts, base, x0, y0, x1, y1) {
            _poly(ctx, pts)
            var g = ctx.createLinearGradient(x0 + ShellLight.lx * 6, y0 + ShellLight.ly * 6, x1 - ShellLight.lx * 6, y1 - ShellLight.ly * 6)
            g.addColorStop(0.0, _css(Col.withL(base, 82), 1))
            g.addColorStop(0.4, _css(base, 1))
            g.addColorStop(1.0, _css(Col.withL(base, 18), 1))
            ctx.fillStyle = g; ctx.fill()
        }
        // lead came: dark lead, then a bevel hairline nudged toward the light
        function _came(ctx, pts, closed, w) {
            ctx.beginPath(); ctx.moveTo(pts[0][0], pts[0][1])
            for (var i = 1; i < pts.length; i++) ctx.lineTo(pts[i][0], pts[i][1])
            if (closed) ctx.closePath()
            ctx.lineJoin = "round"; ctx.lineCap = "round"
            ctx.strokeStyle = _css(k.metalCame, 0.95); ctx.lineWidth = w; ctx.stroke()
            ctx.save(); ctx.translate(ShellLight.lx * 0.55, ShellLight.ly * 0.55)
            ctx.strokeStyle = _css(k.metalShine, rb._hc ? 0.92 : 0.68); ctx.lineWidth = Math.max(0.6, w * 0.38); ctx.stroke()
            ctx.restore()
        }
        function _solder(ctx, x, y) {
            ctx.beginPath(); ctx.arc(x, y, 1.5, 0, Math.PI * 2)
            ctx.fillStyle = _css(Qt.tint(k.metalShine, ShellLight.lt(0.45)), 0.95); ctx.fill()
            ctx.strokeStyle = _css(k.metalCame, 0.75); ctx.lineWidth = 0.5; ctx.stroke()
        }

        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var kids = []
            for (var i = 0; i < row.children.length; i++) {
                var kd = row.children[i]
                if (kd.visible && kd.width > 0) kids.push(kd)
            }
            if (!kids.length) return
            var top = (height - rb.bandH) / 2, bot = top + rb.bandH, mid = height / 2
            var a = rb.chev, d = rb.dir
            var x0 = row.x + kids[0].x - rb.pad
            var last = kids[kids.length - 1]
            var x1 = row.x + last.x + last.width + rb.pad
            // boundaries: each is [top point, middle point, bottom point]
            var bounds = [[[x0, top], [x0 - rb.tail, mid], [x0, bot]]]
            for (var j = 1; j < kids.length; j++) {
                var m = row.x + (kids[j - 1].x + kids[j - 1].width + kids[j].x) / 2
                bounds.push([[m - d * a / 2, top], [m + d * a / 2, mid], [m - d * a / 2, bot]])
            }
            bounds.push([[x1, top], [x1 + rb.tail, mid], [x1, bot]])

            var wall = rb.tones && rb.tones.length >= 2
            var tints = wall ? rb.tones : [k.accent, k.gilt2]
            var glow = k.glowOrAccent

            // ── cathedral glass panes ──────────────────────────────────────────
            for (var s = 0; s < kids.length; s++) {
                var L = bounds[s], R = bounds[s + 1]
                var pane = [L[0], R[0], R[1], R[2], L[2], L[1]]
                var t = tints[s % tints.length]
                var j0 = _jit(s, 101), j1 = _jit(s, 202), j2 = _jit(s, 303), j3 = _jit(s, 404)
                // solid body: an opaque pane of the segment's own tone, deepened, so
                // no wallpaper shows through the text (operator 2026-09-25)
                _poly(ctx, pane)
                var bodyR = Math.round(14 + t.r * 74), bodyG = Math.round(8 + t.g * 74), bodyB = Math.round(6 + t.b * 74)
                ctx.fillStyle = "rgba(" + bodyR + "," + bodyG + "," + bodyB + "," + (rb._hc ? 1.0 : 0.97) + ")"
                ctx.fill()
                ctx.save(); _poly(ctx, pane); ctx.clip()
                var pl = Math.min(L[0][0], L[1][0]), pr = Math.max(R[0][0], R[1][0])
                // the glass: lit from the top, its tone full in the middle, shading into the lead
                var g = ctx.createLinearGradient(0, top, 0, bot)
                g.addColorStop(0,    _css(glow, 0.22 + 0.08 * j3))
                g.addColorStop(0.4,  _css(t, wall ? 0.48 : 0.38))
                g.addColorStop(1,    _css(k.shade, 0.42))
                ctx.fillStyle = g; ctx.fillRect(pl - 2, top, pr - pl + 4, bot - top)
                // light through the glass: a soft bloom on the side facing the light
                var cx = pl + (pr - pl) * (0.5 + ShellLight.lx * 0.3), cy = mid + ShellLight.ly * rb.bandH * 0.3
                var rg = ctx.createRadialGradient(cx, cy, 0, cx, cy, Math.max(pr - pl, rb.bandH) * 0.65)
                rg.addColorStop(0, _css(Col.tone(t, 84, 32), 0.16 + 0.06 * j1)); rg.addColorStop(1, _css(t, 0))
                ctx.fillStyle = rg; ctx.fillRect(pl - 2, top, pr - pl + 4, bot - top)
                // thickness drift: darker toward the thicker side of the sheet
                var dg = ctx.createLinearGradient(pl, 0, pr, 0)
                dg.addColorStop(0, _css(k.shade, j0 < 0.5 ? 0.18 : 0)); dg.addColorStop(0.3 + 0.4 * j1, _css(k.shade, 0))
                dg.addColorStop(1, _css(k.shade, j0 < 0.5 ? 0 : 0.18))
                ctx.fillStyle = dg; ctx.fillRect(pl - 2, top, pr - pl + 4, bot - top)
                // rolled streaks: two hairlines at a slight lean, bright mid-pane only
                for (var r = 0; r < 2; r++) {
                    var sj = _jit(s * 5 + r, 505), sx = pl + (pr - pl) * (0.12 + 0.76 * sj), lean = (sj - 0.5) * 0.3 * rb.bandH
                    var sg = ctx.createLinearGradient(0, top, 0, bot)
                    sg.addColorStop(0, ShellLight.css(0)); sg.addColorStop(0.45, ShellLight.css(0.10 + 0.07 * j3)); sg.addColorStop(1, ShellLight.css(0))
                    ctx.strokeStyle = sg; ctx.lineWidth = 1
                    ctx.beginPath(); ctx.moveTo(sx - lean, top); ctx.lineTo(sx + lean, bot); ctx.stroke()
                }
                // seed: a bubble of trapped air near the pane's rim, lit toward the light
                if (j2 > 0.35) {
                    var bx = pl + (pr - pl) * (0.1 + 0.8 * _jit(s, 606)), by = top + rb.bandH * (j3 > 0.5 ? 0.2 : 0.8)
                    ctx.beginPath(); ctx.arc(bx, by, 1.2, 0, Math.PI * 2)
                    ctx.fillStyle = ShellLight.css(0.14); ctx.fill()
                    ctx.fillStyle = ShellLight.css(0.75); ctx.fillRect(bx + ShellLight.lx * 0.5 - 0.5, by + ShellLight.ly * 0.5 - 0.5, 1, 1)
                }
                // wet sheen on the upper half, faded (never a hard line)
                var sh = ctx.createLinearGradient(0, top, 0, mid)
                sh.addColorStop(0, ShellLight.css(rb._hc ? 0.06 : 0.13)); sh.addColorStop(1, ShellLight.css(0))
                ctx.fillStyle = sh; ctx.fillRect(pl - 2, top, pr - pl + 4, mid - top)
                ctx.restore()
            }

            // ── the arrows, enamelled (reference band: silver outer arrowhead,
            // gilt mid layer, enamel core with gold scroll curls) ────────────
            var jw = Math.max(4, a * 0.75)         // width of an arrow inlay
            var amber = k.jewelAmber
            function _inset(pts, f, ccx, ccy) {
                var r = []
                for (var ii = 0; ii < pts.length; ii++)
                    r.push([ccx + (pts[ii][0] - ccx) * f, ccy + (pts[ii][1] - ccy) * f])
                return r
            }
            for (var c = 1; c < bounds.length - 1; c++) {
                var C = bounds[c], h = jw / 2
                var arrow = [[C[0][0] - h, C[0][1]], [C[1][0] - h, C[1][1]], [C[2][0] - h, C[2][1]],
                             [C[2][0] + h, C[2][1]], [C[1][0] + h, C[1][1]], [C[0][0] + h, C[0][1]]]
                var ccx = C[1][0]
                // enamel core: deep blue-to-wine jewel glass
                var core = _inset(arrow, 0.50, ccx, mid)
                _poly(ctx, core)
                var eg = ctx.createLinearGradient(core[0][0], top, core[3][0], bot)
                eg.addColorStop(0.0, _css(Qt.darker(k.accent, 1.35), 1))
                eg.addColorStop(0.55, _css(k.wine3, 1))
                eg.addColorStop(1.0, _css(Qt.darker(k.accent, 1.55), 1))
                ctx.fillStyle = eg; ctx.fill()
                // gilt mid layer: thick gold outline struck around the core
                var midp = _inset(arrow, 0.74, ccx, mid)
                _poly(ctx, midp)
                ctx.lineJoin = "round"; ctx.lineCap = "round"
                ctx.strokeStyle = _css(k.gilt4, 1); ctx.lineWidth = 1.6; ctx.stroke()
                ctx.save(); ctx.translate(ShellLight.lx * 0.5, ShellLight.ly * 0.5)
                ctx.strokeStyle = _css(k.metalShine, 0.85); ctx.lineWidth = 0.6; ctx.stroke()
                ctx.restore()
                // silver outer arrowhead: bright metal rim over lead came
                _poly(ctx, arrow)
                ctx.strokeStyle = _css(Qt.lighter(k.metalShine, 1.6), 1); ctx.lineWidth = 2.0; ctx.stroke()
                ctx.save(); ctx.translate(-ShellLight.lx * 0.4, -ShellLight.ly * 0.4)
                ctx.strokeStyle = _css(k.metalCame, 0.9); ctx.lineWidth = 0.7; ctx.stroke()
                ctx.restore()
                // gold scroll curls inside the enamel, one per flank
                ctx.strokeStyle = _css(k.gilt4, 0.95); ctx.lineWidth = 1.0
                ctx.lineCap = "round"
                ctx.beginPath(); ctx.arc(ccx - h * 0.30, mid, h * 0.30, Math.PI * 0.15, Math.PI * 1.55); ctx.stroke()
                ctx.beginPath(); ctx.arc(ccx + h * 0.30, mid, h * 0.30, -Math.PI * 0.55, Math.PI * 0.85); ctx.stroke()
                // heart jewel: amber cabochon at the centroid catching the light
                ctx.beginPath(); ctx.arc(ccx, mid, 1.6, 0, Math.PI * 2)
                var hg = ctx.createRadialGradient(ccx + ShellLight.lx, mid + ShellLight.ly, 0, ccx, mid, 1.8)
                hg.addColorStop(0, ShellLight.css(0.95)); hg.addColorStop(0.45, _css(amber, 0.95)); hg.addColorStop(1, _css(Col.withL(amber, 25), 1))
                ctx.fillStyle = hg; ctx.fill()
            }
            // the two tails: jewel-glass tips in the accent, a lead line where they meet the panes
            var B0 = bounds[0], BN = bounds[bounds.length - 1]
            var tipL = [B0[0], B0[1], B0[2]], tipR = [BN[0], BN[1], BN[2]]
            _jewel(ctx, tipL, k.jewelRuby, B0[1][0], top, B0[0][0], bot)
            _jewel(ctx, tipR, k.jewelRuby, BN[1][0], top, BN[0][0], bot)
            _came(ctx, [B0[0], B0[2]], false, 1.4)
            _came(ctx, [BN[0], BN[2]], false, 1.4)

            // ── outline: the ribbon's own came, like the clock ribbon's double leading ──
            _came(ctx, [B0[1], B0[0], BN[0], BN[1], BN[2], B0[2]], true, 2.0)
            // solder where the arrows meet the edge leading
            for (var q = 1; q < bounds.length - 1; q++) {
                _solder(ctx, bounds[q][0][0], top); _solder(ctx, bounds[q][2][0], bot)
            }
            _solder(ctx, B0[0][0], top); _solder(ctx, B0[2][0], bot); _solder(ctx, BN[0][0], top); _solder(ctx, BN[2][0], bot);
            // ── end cabochons at the tips ──
            [B0[1], BN[1]].forEach(function (p) {
                ctx.beginPath(); ctx.arc(p[0], p[1], 2.6, 0, Math.PI * 2)
                var cg = ctx.createRadialGradient(p[0] + ShellLight.lx, p[1] + ShellLight.ly, 0, p[0], p[1], 2.8)
                cg.addColorStop(0, ShellLight.css(0.92)); cg.addColorStop(0.4, _css(k.jewelAmber, 0.96)); cg.addColorStop(1, _css(Col.withL(k.jewelAmber, 22), 1))
                ctx.fillStyle = cg; ctx.fill()
                ctx.strokeStyle = _css(k.metalShine, 0.85); ctx.lineWidth = 0.6; ctx.stroke()
            })
        }
    }

    Row {
        id: row
        x: rb.tail + rb.pad + 1
        height: rb.height
        spacing: rb.chev + 2 * rb.pad
    }
}
