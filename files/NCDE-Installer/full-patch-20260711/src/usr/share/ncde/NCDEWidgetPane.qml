import QtQuick
import "ncde-color.js" as Col

// NCDEWidgetPane — a brass bezel + glass pane laid OVER a desktop widget card,
// so each card reads as a window set into brass, the way NCDEIconBezel +
// NCDEGlassCap make the dock icons read as glass jewels set into sockets
// (operator 2026-09-24: "put a glass layer over the widgets like the icons
// have ... with bezels"). Same layer vocabulary, re-derived for a flat pane:
//   bezel  — brass ring around the card edge: palette gilt shine upper-left
//            falling to deep bronze lower-right, dark came line on both edges,
//            inset shadow where the glass sits IN the socket, glint at the
//            upper-left like the icon bezel's
//   pane   1. lens tint      — barely-there palette tint, thicker toward the bottom
//          2. top sheen      — broad soft reflection across the upper third
//          3. catch-light    — one diagonal specular streak, upper-left
//          4. bottom caustic — faint glow pooled along the lower edge
//          5. rim            — bright Fresnel hairline just inside the bezel
// Iris Chroma drives it (gilt ramp for the brass, accent tint, glow caustic);
// high-contrast mode halves the sheen so text never washes out. Static: one
// Canvas, repainted only on resize / theme change — no animation, no clicks
// taken (a Canvas has no input handlers).
// Place it LAST in the card (on top), anchors.fill the card's root.
// One light (2026-09-25): brass ramp, bevel, streak, glint and inset shadow all
// take their direction and colour from ShellLight, like the icon bezels and domes.
Canvas {
    id: pane
    property real radius: 18        // card corner (glass cornerRadius 14 + its 4px inset)
    property real ring: 5           // bezel width
    readonly property bool _hc: (typeof settings !== "undefined" && settings.highContrast === true)

    renderStrategy: Canvas.Cooperative
    onWidthChanged: requestPaint()
    onHeightChanged: requestPaint()
    on_HcChanged: requestPaint()
    Connections { target: ncde; function onThemeChanged() { pane.requestPaint() } }
    // the light follows the sun (2026-09-25): repaint when it moves or warms
    Connections { target: ShellLight; function onSignatureChanged() { pane.requestPaint() } }
    // The standard (2026-09-26): one metal, one shade — NCDEKit's palette metal
    // (same lightness as before, so the default palette looks unchanged) and the
    // palette's own shade for cavities and lead, never black or a fixed brown.
    NCDEKit { id: k }
    function _kc(c, a) { return Col.css(Qt.rgba(c.r, c.g, c.b, a)) }

    function _rr(ctx, x, y, w, h, r) {
        r = Math.max(0, Math.min(r, w / 2, h / 2))
        ctx.moveTo(x + r, y)
        ctx.lineTo(x + w - r, y); ctx.arcTo(x + w, y, x + w, y + r, r)
        ctx.lineTo(x + w, y + h - r); ctx.arcTo(x + w, y + h, x + w - r, y + h, r)
        ctx.lineTo(x + r, y + h); ctx.arcTo(x, y + h, x, y + h - r, r)
        ctx.lineTo(x, y + r); ctx.arcTo(x, y, x + r, y, r)
        ctx.closePath()
    }
    function _c(c, a) { return Qt.rgba(c.r, c.g, c.b, a) }
    // a gradient line across the card running from the lit edge to the far one
    function _lightLine(ctx, W, H) {
        var ex = Math.abs(ShellLight.lx) * W / 2 + Math.abs(ShellLight.ly) * H / 2
        return ctx.createLinearGradient(W / 2 + ShellLight.lx * ex, H / 2 + ShellLight.ly * ex,
                                        W / 2 - ShellLight.lx * ex, H / 2 - ShellLight.ly * ex)
    }

    onPaint: {
        var ctx = getContext("2d")
        var W = width, H = height, R = radius, b = ring
        ctx.reset()
        if (W < 2 * b + 4 || H < 2 * b + 4) return
        var ix = b, iy = b, iw = W - 2 * b, ih = H - 2 * b, ir = Math.max(2, R - b)
        var sheen = _hc ? 0.5 : 1.0

        // ── pane (under the bezel so the bezel overlaps its edge) ──
        ctx.save()
        ctx.beginPath(); _rr(ctx, ix, iy, iw, ih, ir); ctx.clip()
        // 1. lens tint
        var lt = ctx.createLinearGradient(0, iy, 0, iy + ih)
        lt.addColorStop(0.0, _c(ncde.accent, 0.03))
        lt.addColorStop(0.6, _c(ncde.accent, 0.05))
        lt.addColorStop(1.0, k.shadeA(0.12))
        ctx.fillStyle = lt; ctx.fillRect(ix, iy, iw, ih)
        // 2. top sheen
        var sh = ctx.createLinearGradient(0, iy, 0, iy + ih * 0.34)
        // wet shine (2026-09-25): a liquid meniscus — the sheen holds, then ends on
        // a crisp lip instead of fading (kept faint: text sits under it)
        sh.addColorStop(0.00, ShellLight.css(0.13 * sheen))
        sh.addColorStop(0.55, ShellLight.css(0.08 * sheen))
        sh.addColorStop(0.80, ShellLight.css(0.06 * sheen))
        sh.addColorStop(0.86, ShellLight.css(0.01 * sheen))
        sh.addColorStop(1.00, ShellLight.css(0))
        ctx.fillStyle = sh; ctx.fillRect(ix, iy, iw, ih * 0.34)
        // wet refraction line: light bent through the pane leaves as a thin bright
        // line just inside the far (bottom) edge. It fades out along its length —
        // no ends, no corners (operator: no harsh lines)
        var rl = ctx.createLinearGradient(ix + iw * 0.06, 0, ix + iw * 0.94, 0)
        rl.addColorStop(0.0, ShellLight.css(0))
        rl.addColorStop(0.3, ShellLight.css(0.12 * sheen))
        rl.addColorStop(0.7, ShellLight.css(0.12 * sheen))
        rl.addColorStop(1.0, ShellLight.css(0))
        ctx.beginPath(); _rr(ctx, ix + iw * 0.06, iy + ih - 5, iw * 0.88, 2.5, 1.25)
        ctx.fillStyle = rl; ctx.fill()
        // 3. catch-light: one diagonal streak, square to the light
        ctx.save()
        ctx.translate(ix + iw * 0.16, iy)
        ctx.rotate(ShellLight.gradientTurn * Math.PI / 180)
        var cl = ctx.createLinearGradient(0, 0, 26, 0)
        cl.addColorStop(0.0, ShellLight.css(0))
        cl.addColorStop(0.5, ShellLight.css(0.10 * sheen))
        cl.addColorStop(1.0, ShellLight.css(0))
        ctx.fillStyle = cl; ctx.fillRect(0, -ih, 26, ih * 1.2)
        ctx.restore()
        // 4. bottom caustic
        var cx = ix + iw / 2, cy = iy + ih
        var ca = ctx.createRadialGradient(cx, cy, 0, cx, cy, iw * 0.45)
        ca.addColorStop(0.0, _c(ncde.glow, 0.10))
        ca.addColorStop(1.0, _c(ncde.glow, 0))
        ctx.fillStyle = ca; ctx.fillRect(ix, iy + ih * 0.5, iw, ih * 0.5)
        // inset shadow: the pane sits IN the socket; the lip on the lit side
        // shades the glass just under it (top + left at the shell's light)
        var s1 = ctx.createLinearGradient(0, iy, 0, iy + 7)
        s1.addColorStop(0, _kc(k.shade, (0.37 * ShellLight.facing(0, -1)))); s1.addColorStop(1, _kc(k.shade, 0))
        ctx.fillStyle = s1; ctx.fillRect(ix, iy, iw, 7)
        var s2 = ctx.createLinearGradient(ix, 0, ix + 6, 0)
        s2.addColorStop(0, _kc(k.shade, (0.44 * ShellLight.facing(-1, 0)))); s2.addColorStop(1, _kc(k.shade, 0))
        ctx.fillStyle = s2; ctx.fillRect(ix, iy, 6, ih)
        ctx.restore()
        // 5. rim: Fresnel hairline just inside the bezel
        ctx.beginPath(); _rr(ctx, ix + 1.5, iy + 1.5, iw - 3, ih - 3, ir - 1)
        ctx.strokeStyle = ShellLight.css(_hc ? 0.55 : 0.26); ctx.lineWidth = _hc ? 1.5 : 1; ctx.stroke()

        // ── brass bezel ring ──
        ctx.beginPath()
        _rr(ctx, 0.5, 0.5, W - 1, H - 1, R)
        _rr(ctx, ix, iy, iw, ih, ir)
        var br = _lightLine(ctx, W, H)
        br.addColorStop(0.00, k.metalShine)
        br.addColorStop(0.45, k.metalWarm)
        br.addColorStop(1.00, k.metal)
        ctx.fillStyle = br
        ctx.fillRule = Qt.OddEvenFill   // outer minus inner = the ring
        ctx.fill()
        ctx.fillRule = Qt.WindingFill
        // came lines: dark leading on the outer and inner edge of the brass
        ctx.beginPath(); _rr(ctx, 0.5, 0.5, W - 1, H - 1, R)
        ctx.strokeStyle = _kc(k.metalCame, 0.85); ctx.lineWidth = 1; ctx.stroke()
        ctx.beginPath(); _rr(ctx, ix - 0.5, iy - 0.5, iw + 1, ih + 1, ir + 0.5)
        ctx.strokeStyle = _kc(k.metalCame, 0.75); ctx.lineWidth = 1; ctx.stroke()
        // bevel: a bright hairline along the ring's lit crest
        ctx.beginPath(); _rr(ctx, 2, 2, W - 4, H - 4, R - 1.5)
        var bv = _lightLine(ctx, W, H)
        bv.addColorStop(0.0, ShellLight.css(0.45)); bv.addColorStop(0.35, ShellLight.css(0.08)); bv.addColorStop(1.0, ShellLight.css(0))
        ctx.strokeStyle = bv; ctx.lineWidth = 1; ctx.stroke()
        // glint on the brass where the light strikes the corner (as the icon bezel's)
        var gx = R + ShellLight.lx * (R - b / 2), gy = R + ShellLight.ly * (R - b / 2)
        var gl = ctx.createRadialGradient(gx, gy, 0, gx, gy, 9)
        gl.addColorStop(0, ShellLight.css(0.75)); gl.addColorStop(1, ShellLight.css(0))
        ctx.fillStyle = gl; ctx.fillRect(gx - 10, gy - 10, 20, 20)
    }

    // ── Picture frame (operator art 2026-09-29, widget-frame.png) ──
    // Thin bronze moulding with small carved corners, laid on the card's own
    // edge — INSIDE the card's bounds, so it adds no size and can never touch
    // a neighbouring widget. Source ~/Downloads/.../widget frame.png (kept in
    // my-project/files as widget-frame-SOURCE.png): bbox (344,168)-(1704,1880),
    // 80px moulding scaled to 7px so it covers the 5px brass ring and the
    // card's rounded corners (their curve stays within 3.75px of the edge).
    // 9-slice: the 13px corners never stretch, only the straight moulding.
    BorderImage {
        anchors.fill: parent
        source: "widget-frame.png"
        border { left: 13; right: 13; top: 13; bottom: 13 }
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch
        smooth: true
    }
}
