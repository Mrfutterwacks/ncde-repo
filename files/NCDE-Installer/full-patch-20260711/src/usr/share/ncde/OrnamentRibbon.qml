import QtQuick
import Qt5Compat.GraphicalEffects
import "mucha-clock.js" as Clock
import "ncde-color.js" as Col

// OrnamentRibbon — NCDEPowerRibbon with its natural chevrons/tails replaced by
// the hand-drawn art, glass panes kept.
// WHAT STAYS: the per-child cathedral glass panes (opaque body, lit glass,
// bloom, streaks, bubbles, sheen — byte-identical to NCDEPowerRibbon), the
// Row layout, tones/seed/ShellLight/highContrast behavior. No glass removed.
// WHAT CHANGES:
//  - divider chevrons  → arrow art, drawn in-Canvas (dir 1 = arrow-right.png,
//    dir -1 = arrow-left.png: trimmed versions of Downloads arrowl.png /
//    arrow.png — identical art, padding removed so they fit), sized chev wide
//    x bandH tall so they always fit the band by construction.
//  - pointed tails     → end-cap Images (arrow-left.png / arrow-right.png),
//    PreserveAspectFit, bandH tall, always fully visible even furled.
//  - outline came      → menu-expand-ribbon.png (trimmed Downloads
//    menuexpandribbon.png) as the slide track behind the panes
//    (PreserveAspectCrop: rails never distort; ends crop away under the caps).
// Drop-in API: same default content alias (Row), dir / pad / tones / seed
// props, implicitWidth, width, height, tactile slide Behaviors.
Item {
    id: rb
    default property alias content: row.data
    property int dir: 1                 // 1 = dividers ▸, -1 = dividers ◂
    property real pad: 5                // glass between a child and its arrow
    // the wallpaper's own shades (NCDEWallTones), one per segment in turn; until
    // the wallpaper has been read, the Iris accent and brass alternate instead
    property var tones: []
    property int seed: 0                // varies the panes between ribbons
    NCDEKit { id: k }
    onTonesChanged: cv.requestPaint()
    readonly property real bandH: height - 4
    // divider/end-cap widths follow the art aspect at band height, so the
    // images fit the band exactly: H=30 → bandH=26 → ~20px; H=32 → ~21px.
    // 2026-09-29 (operator: "arrows are cut off"): arrow-left/right.png were
    // the two HALVES of one symmetric ornament, sliced through its scrolls, so
    // every cap and divider showed a flat cut. arrow-ornament.png is the whole
    // piece (left half + its mirror, seamless, 165x110). Dividers and both end
    // caps use it whole; widths follow its aspect at band height.
    readonly property real chev: Math.round(bandH * 165 / 110)
    readonly property real tail: chev
    readonly property bool _hc: (typeof settings !== "undefined" && settings.highContrast === true)

    implicitWidth: row.width + 2 * (tail + pad) + 2
    width: implicitWidth
    height: parent ? parent.height : 28
    // tactile slide: ribbon lengthens/shortens like sheet metal in a track.
    // followsDrawer (2026-09-29, operator: "the background moves after the menus
    // slide out"): a ribbon holding a GliaBar drawer must NOT animate on its own —
    // the drawer already animates its width, and these Behaviors restarted every
    // frame chasing it, so the ribbon lagged and kept moving after the menus
    // stopped. With followsDrawer the ribbon tracks the drawer frame-for-frame.
    property bool followsDrawer: false
    Behavior on implicitWidth { enabled: !rb.followsDrawer; NumberAnimation { duration: 220; easing.type: Easing.OutExpo } }
    Behavior on width { enabled: !rb.followsDrawer; NumberAnimation { duration: 220; easing.type: Easing.OutExpo } }

    // ── Slide track (menu-expand-ribbon.png, behind the glass) ──
    Image {
        id: track
        z: -2
        anchors.fill: parent
        source: "menu-expand-ribbon.png"
        fillMode: Image.PreserveAspectCrop
        smooth: true
        mipmap: true
        layer.enabled: true
        layer.effect: HueSaturation {
            hue: (ncde.accent.hslHue - 0.12) * 0.6
            saturation: -0.1
        }
    }

    // ── End caps (arrow art, always fully visible) ──
    Image {
        id: leftCap
        z: 0
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: rb.chev
        height: rb.bandH
        source: "arrow-ornament.png"
        fillMode: Image.PreserveAspectFit
        smooth: true
        mipmap: true
        // no tint (2026-09-29): caps match the dividers exactly — same art, same colour
    }
    Image {
        id: rightCap
        z: 0
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: rb.chev
        height: rb.bandH
        source: "arrow-ornament.png"
        fillMode: Image.PreserveAspectFit
        smooth: true
        mipmap: true
        // no tint (2026-09-29): caps match the dividers exactly — same art, same colour
    }

    // Divider source (hidden): the Canvas draws it at every pane boundary.
    Image {
        id: divImg
        visible: false
        source: "arrow-ornament.png"
        smooth: true
        mipmap: true
        onStatusChanged: if (status === Image.Ready) cv.requestPaint()
    }

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
        Connections { target: divImg; function onStatusChanged() { if (divImg.status === Image.Ready) cv.requestPaint() } }

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

            // ── cathedral glass panes (kept from NCDEPowerRibbon) ────
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

            // ── divider arrows (arrow art, replaces the enamel chevrons) ──
            // chev wide x bandH tall, centered on each pane seam: fits the band
            // by construction, never cropped, points the way the bar runs.
            if (divImg.status === Image.Ready) {
                for (var c = 1; c < bounds.length - 1; c++) {
                    var dx = bounds[c][1][0] - rb.dir * rb.chev / 2 - rb.chev / 2   // seam centre m
                    ctx.drawImage(divImg, dx, top, rb.chev, rb.bandH)
                }
                // (2026-09-29) the Iris wash rectangle is gone: the whole ornament has
                // open corners, so a clipped rect showed as a tinted box behind it
            }
        }
    }

    Row {
        id: row
        x: rb.tail + rb.pad + 1
        height: rb.height
        spacing: rb.chev + 2 * rb.pad
    }
}
