import QtQuick
import "ncde-color.js" as Col

// NCDEPanelBezel — a thin brass bezel around a panel's glass pill, so the top and
// bottom panels read as set into brass like the dock icons (NCDEIconBezel) and the
// widget cards (NCDEWidgetPane). Operator 2026-09-25: "what if the top and bottom
// panel had bezels too? like the dock and the widgets" — thinner than the widget
// ring (the panels are one text line tall), same metal, same light.
//
// It sits OUTSIDE the pill: anchors.fill the panel with anchors.margins: -ring, so
// the panel keeps every pixel of its own height (the launcher bezels are already
// 30px in a 28px pill). Being a child of the panel it rides intellihide with it.
//   ring    — brass: lit edge (whichever side faces ShellLight) in gilt4, falling
//             through gilt2 to gilt0 on the far edge; the end cap facing the light
//             catches a soft extra sheen that fades before the straight run
//   came    — dark leading on the ring's outer and inner edge
//   bevel   — bright hairline on the ring's lit crest, fading around the pill
//   inset   — soft shadow on the glass under the lit lip, painted as a stroke
//             along the pill's own outline so it never ends square (no harsh lines)
//   glint   — one point of light on the cap facing the light
// Static: one Canvas, repainted on resize / theme change / when the light moves.
// No input (a Canvas has no handlers). Place it right after the panel's
// NCDEGlassSurface so the panel's content draws over it.
Canvas {
    id: bz
    property real ring: 3
    readonly property bool _hc: (typeof settings !== "undefined" && settings.highContrast === true)

    renderStrategy: Canvas.Cooperative
    onWidthChanged: requestPaint()
    onHeightChanged: requestPaint()
    on_HcChanged: requestPaint()
    Connections { target: ncde; function onThemeChanged() { bz.requestPaint() } }
    Connections { target: ShellLight; function onSignatureChanged() { bz.requestPaint() } }
    // The standard (2026-09-26): one metal, one shade — NCDEKit's palette metal
    // (same lightness as before, so the default palette looks unchanged) and the
    // palette's own shade for cavities and lead, never black or a fixed brown.
    NCDEKit { id: k }
    function _kc(c, a) { return Col.css(Qt.rgba(c.r, c.g, c.b, a)) }

    function _pill(ctx, x, y, w, h) {
        var r = Math.max(0, Math.min(h / 2, w / 2))
        ctx.moveTo(x + r, y)
        ctx.lineTo(x + w - r, y); ctx.arc(x + w - r, y + r, r, -Math.PI / 2, Math.PI / 2, false)
        ctx.lineTo(x + r, y + h); ctx.arc(x + r, y + r, r, Math.PI / 2, 3 * Math.PI / 2, false)
        ctx.closePath()
    }
    // top-to-bottom line whose first stop sits on the edge facing the light
    function _vLine(ctx, H) {
        return ShellLight.ly <= 0 ? ctx.createLinearGradient(0, 0, 0, H)
                                  : ctx.createLinearGradient(0, H, 0, 0)
    }

    onPaint: {
        var ctx = getContext("2d")
        var W = width, H = height, b = ring
        ctx.reset()
        if (W < 4 * b + 8 || H < 2 * b + 6) return
        var ix = b, iy = b, iw = W - 2 * b, ih = H - 2 * b
        var R = H / 2, ir = ih / 2

        // ── inset shadow on the glass under the lit lip ──
        ctx.save()
        ctx.beginPath(); _pill(ctx, ix, iy, iw, ih); ctx.clip()
        var sh = _vLine(ctx, H)
        var sa = (_hc ? 0.22 : 0.34) * Math.max(ShellLight.facing(0, -1), ShellLight.facing(0, 1))
        sh.addColorStop(0.0, _kc(k.shade, sa))
        sh.addColorStop(0.35, _kc(k.shade, (sa * 0.25)))
        sh.addColorStop(0.6, _kc(k.shade, 0))
        sh.addColorStop(1.0, _kc(k.shade, 0))
        ctx.beginPath(); _pill(ctx, ix, iy, iw, ih)
        ctx.strokeStyle = sh; ctx.lineWidth = 6; ctx.stroke()
        ctx.restore()

        // ── brass ring (outer pill minus inner pill) ──
        var br = _vLine(ctx, H)
        br.addColorStop(0.00, k.metalShine)
        br.addColorStop(0.50, k.metalWarm)
        br.addColorStop(1.00, k.metal)
        ctx.beginPath()
        _pill(ctx, 0.5, 0.5, W - 1, H - 1)
        _pill(ctx, ix, iy, iw, ih)
        ctx.fillStyle = br
        ctx.fillRule = Qt.OddEvenFill
        ctx.fill()
        // the cap facing the light takes an extra sheen that fades out along the run
        var capL = ShellLight.lx <= 0
        var cs = capL ? ctx.createLinearGradient(0, 0, R * 2.2, 0)
                      : ctx.createLinearGradient(W, 0, W - R * 2.2, 0)
        var ca = 0.30 * Math.abs(ShellLight.lx)
        cs.addColorStop(0.0, ShellLight.css(ca)); cs.addColorStop(1.0, ShellLight.css(0))
        ctx.fillStyle = cs
        ctx.fill()
        ctx.fillRule = Qt.WindingFill

        // ── came lines ──
        ctx.beginPath(); _pill(ctx, 0.5, 0.5, W - 1, H - 1)
        ctx.strokeStyle = _kc(k.metalCame, 0.80); ctx.lineWidth = 1; ctx.stroke()
        ctx.beginPath(); _pill(ctx, ix - 0.5, iy - 0.5, iw + 1, ih + 1)
        ctx.strokeStyle = _kc(k.metalCame, 0.70); ctx.lineWidth = 1; ctx.stroke()

        // ── bevel: bright hairline on the lit crest, gone by the far edge ──
        ctx.beginPath(); _pill(ctx, 1.5, 1.5, W - 3, H - 3)
        var bv = _vLine(ctx, H)
        bv.addColorStop(0.0, ShellLight.css(_hc ? 0.60 : 0.42))
        bv.addColorStop(0.30, ShellLight.css(0.06))
        bv.addColorStop(0.55, ShellLight.css(0))
        bv.addColorStop(1.0, ShellLight.css(0))
        ctx.strokeStyle = bv; ctx.lineWidth = 1; ctx.stroke()

        // ── glint on the cap facing the light ──
        var cx = capL ? R : W - R
        var gx = cx + ShellLight.lx * (R - b / 2), gy = R + ShellLight.ly * (R - b / 2)
        var gl = ctx.createRadialGradient(gx, gy, 0, gx, gy, 6)
        gl.addColorStop(0, ShellLight.css(0.70)); gl.addColorStop(1, ShellLight.css(0))
        ctx.fillStyle = gl; ctx.fillRect(gx - 7, gy - 7, 14, 14)
    }
}
