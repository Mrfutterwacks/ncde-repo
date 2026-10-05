import QtQuick

// NCDEWallTones — the current wallpaper's own shades, for the panel ribbons
// (operator 2026-09-25: "what if the ribbons were different shades from the
// wallpaper that is current?"). Reads the wallpaper once per change, shrunk to a
// 64x40 thumbnail, and bins its pixels by hue in Lab exactly the way Filigree's
// "From your wallpaper" picker does (greys carry no hue; each bin is weighted by
// chroma). `tones` is the strongest hues, strongest first, each the bin's own
// Lab mean with its lightness held in a band that reads as tinted glass on the
// dark pill. Empty until sampled (or with no wallpaper) — ribbons then fall back
// to the Iris accent and brass. Static: no timers, nothing animates.
Canvas {
    id: wt
    property url source: ""
    property int count: 4
    property var tones: []

    width: 64; height: 40
    opacity: 0                    // paints, never seen
    enabled: false
    renderStrategy: Canvas.Immediate

    onSourceChanged: { if (source != "") loadImage(source); else tones = [] }
    onImageLoaded: requestPaint()
    Component.onCompleted: if (source != "") loadImage(source)

    function _lab(r, g, b) {
        function lin(c) { c /= 255; return c <= 0.04045 ? c / 12.92 : Math.pow((c + 0.055) / 1.055, 2.4) }
        var R = lin(r), G = lin(g), B = lin(b)
        var x = (R * 0.4124 + G * 0.3576 + B * 0.1805) / 0.95047
        var y =  R * 0.2126 + G * 0.7152 + B * 0.0722
        var z = (R * 0.0193 + G * 0.1192 + B * 0.9505) / 1.08883
        function f(t) { return t > 0.008856 ? Math.cbrt(t) : 7.787 * t + 16 / 116 }
        return [116 * f(y) - 16, 500 * (f(x) - f(y)), 200 * (f(y) - f(z))]
    }
    function _rgb(L, a, b) {
        var fy = (L + 16) / 116, fx = fy + a / 500, fz = fy - b / 200
        function fi(t) { return t * t * t > 0.008856 ? t * t * t : (t - 16 / 116) / 7.787 }
        var x = fi(fx) * 0.95047, y = fi(fy), z = fi(fz) * 1.08883
        var R =  3.2406 * x - 1.5372 * y - 0.4986 * z
        var G = -0.9689 * x + 1.8758 * y + 0.0415 * z
        var B =  0.0557 * x - 0.2040 * y + 1.0570 * z
        function gam(c) { c = c <= 0.0031308 ? 12.92 * c : 1.055 * Math.pow(Math.max(c, 0), 1 / 2.4) - 0.055; return Math.min(1, Math.max(0, c)) }
        return Qt.rgba(gam(R), gam(G), gam(B), 1)
    }

    onPaint: {
        if (source == "" || !isImageLoaded(source)) return
        var ctx = getContext("2d")
        ctx.reset()
        ctx.drawImage(source, 0, 0, width, height)
        var px = ctx.getImageData(0, 0, width, height).data
        var bins = []
        for (var h = 0; h < 12; h++) bins.push({ w: 0, lab: [0, 0, 0] })
        for (var i = 0; i + 3 < px.length; i += 4) {
            if (px[i + 3] < 128) continue
            var L = _lab(px[i], px[i + 1], px[i + 2])
            var C = Math.sqrt(L[1] * L[1] + L[2] * L[2])
            if (C < 12) continue
            var bi = Math.floor(((Math.atan2(L[2], L[1]) + Math.PI) / (2 * Math.PI)) * 12) % 12
            bins[bi].w += C
            bins[bi].lab[0] += L[0] * C; bins[bi].lab[1] += L[1] * C; bins[bi].lab[2] += L[2] * C
        }
        bins.sort(function (a, b) { return b.w - a.w })
        var out = []
        for (var k = 0; k < bins.length && out.length < count; k++) {
            if (bins[k].w <= 0) break
            var w = bins[k].w
            var l = bins[k].lab[0] / w, aa = bins[k].lab[1] / w, bb = bins[k].lab[2] / w
            l = Math.max(42, Math.min(66, l))        // glass on a dark pill: never mud, never chalk
            // a dark, muted wallpaper averages to near-grey; lift the colour (chroma)
            // so neighbouring panes read as different glass, keeping each hue true
            var c = Math.sqrt(aa * aa + bb * bb), c2 = Math.max(22, Math.min(48, c * 1.6))
            if (c > 0) { aa *= c2 / c; bb *= c2 / c }
            out.push(_rgb(l, aa, bb))
        }
        tones = out
    }
}
