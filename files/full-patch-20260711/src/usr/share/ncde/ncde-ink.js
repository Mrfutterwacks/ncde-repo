// ncde-ink.js — "wallpaper ink" (operator, 2026-09-24: "all fonts on the shell
// will turn that color when this theme is picked").
// When a palette is picked from Filigree → Iris → "From your wallpaper", every
// piece of shell text is re-inked in the wallpaper's own hue. Motif math, same
// rule as Woven: keep each colour's lightness, turn its hue (LCh) to the
// wallpaper's strongest hue, give it enough chroma to read as that colour.
// Lightness is kept, so light text on dark glass becomes lavender and dark text
// on gold becomes deep purple — every contrast relationship holds.
// State lives here (.pragma library = one copy per engine) so the Canvas
// painter libraries (mucha-clock/panels/space.js) and ThemeTokens share it.
// ThemeTokens.qml owns persistence (wallpaper-ink.json) and calls set().
.pragma library

var on = false
var hue = 0          // LCh hue, radians (Filigree's _lch(wallClusters[0])[2])
var chroma = 38

function set(isOn, h, c) {
    on = isOn === true
    if (typeof h === "number" && isFinite(h)) hue = h
    if (typeof c === "number" && c > 0) chroma = c
}

// accept a QML color, "#rgb" / "#rrggbb" / "#aarrggbb", "rgb()/rgba()", or a name
function _parse(c) {
    if (c === undefined || c === null || c === "") return null
    if (typeof c !== "string") return (c.r !== undefined) ? [c.r, c.g, c.b, c.a] : null
    var m = c.match(/^rgba?\(\s*([\d.]+)\s*,\s*([\d.]+)\s*,\s*([\d.]+)\s*(?:,\s*([\d.]+)\s*)?\)$/)
    if (m) return [m[1] / 255, m[2] / 255, m[3] / 255, m[4] === undefined ? 1 : parseFloat(m[4])]
    var q = Qt.color(c)
    return q ? [q.r, q.g, q.b, q.a] : null
}
function _lin(c) { return c <= 0.04045 ? c / 12.92 : Math.pow((c + 0.055) / 1.055, 2.4) }
function _gam(c) { return c <= 0.0031308 ? 12.92 * c : 1.055 * Math.pow(Math.max(c, 0), 1 / 2.4) - 0.055 }
function _L(r, g, b) {
    var y = 0.2126 * _lin(r) + 0.7152 * _lin(g) + 0.0722 * _lin(b)
    return y > 0.008856 ? 116 * Math.cbrt(y) - 16 : 903.3 * y
}
function _rgb(L, a, b) {
    function finv(t) { return t > 0.206893 ? t * t * t : (t - 16 / 116) / 7.787 }
    var fy = (L + 16) / 116, x = 0.95047 * finv(fy + a / 500), y = finv(fy), z = 1.08883 * finv(fy - b / 200)
    return [_gam( 3.2406 * x - 1.5372 * y - 0.4986 * z),
            _gam(-0.9689 * x + 1.8758 * y + 0.0415 * z),
            _gam( 0.0557 * x - 0.2040 * y + 1.0570 * z)]
}
// → [r, g, b, a] in 0..1, or the parsed input unchanged when ink is off
function _ink(c) {
    var p = _parse(c)
    if (!p || !on) return p
    // keep lightness, but pull the extremes in far enough to carry colour
    var L = Math.max(18, Math.min(84, _L(p[0], p[1], p[2])))
    var C = chroma * Math.min(1, Math.min(L, 100 - L) / 16), out
    for (var k = 0; k < 24; k++) {
        out = _rgb(L, C * Math.cos(hue), C * Math.sin(hue))
        if (out[0] > -0.002 && out[0] < 1.002 && out[1] > -0.002 && out[1] < 1.002 && out[2] > -0.002 && out[2] < 1.002) break
        C *= 0.9
    }
    return [Math.min(1, Math.max(0, out[0])), Math.min(1, Math.max(0, out[1])), Math.min(1, Math.max(0, out[2])), p[3]]
}
// for QML color properties
function color(c) {
    if (!on) return c
    var q = _ink(c)
    return q ? Qt.rgba(q[0], q[1], q[2], q[3]) : c
}
// for Canvas fillStyle / strokeStyle (keeps the input when ink is off)
function css(c) {
    if (!on) return c
    var q = _ink(c)
    return q ? "rgba(" + Math.round(q[0] * 255) + "," + Math.round(q[1] * 255) + "," + Math.round(q[2] * 255) + "," + q[3] + ")" : c
}
