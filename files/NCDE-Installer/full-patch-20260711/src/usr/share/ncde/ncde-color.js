// ncde-color.js — the shell's shared colour math (2026-09-24).
// Operator: the Iris Chroma palette is meant to be UNIVERSAL — every surface,
// control, painter and house app takes its colour from it. This library is how
// a file turns palette tokens into the tones it needs without hardcoding hexes:
// lighter/darker steps, shadow and highlight tones, readable text, and
// "semantic" colours (a category's blue, an alert's red) re-made in the
// palette's own material.
//
// Everything works in CIE Lab / LCh (D65), the same space ncde-ink.js and the
// Woven palette use: equal steps of L look equal, and hue stays put when
// lightness changes. Qt.lighter/darker scale HSV value instead, so on the
// near-black grounds most Iris palettes use they barely move at all.
//
// .pragma library — stateless, one copy per engine. Every function takes a QML
// color, "#rgb"/"#rrggbb"/"#aarrggbb", "rgb()/rgba()", or a colour name, and
// returns a QML color (use css() for Canvas fillStyle/strokeStyle).
.pragma library

function parse(c) {
    if (c === undefined || c === null || c === "") return null
    if (typeof c !== "string") return (c.r !== undefined) ? [c.r, c.g, c.b, c.a === undefined ? 1 : c.a] : null
    var m = c.match(/^rgba?\(\s*([\d.]+)\s*,\s*([\d.]+)\s*,\s*([\d.]+)\s*(?:,\s*([\d.]+)\s*)?\)$/)
    if (m) return [m[1] / 255, m[2] / 255, m[3] / 255, m[4] === undefined ? 1 : parseFloat(m[4])]
    var q = Qt.color(c)
    return q ? [q.r, q.g, q.b, q.a] : null
}

function _lin(c) { return c <= 0.04045 ? c / 12.92 : Math.pow((c + 0.055) / 1.055, 2.4) }
function _gam(c) { return c <= 0.0031308 ? 12.92 * c : 1.055 * Math.pow(Math.max(c, 0), 1 / 2.4) - 0.055 }
function _f(t)   { return t > 0.008856 ? Math.cbrt(t) : 7.787 * t + 16 / 116 }
function _finv(t){ return t > 0.206893 ? t * t * t : (t - 16 / 116) / 7.787 }

// → [L, a, b] or null
function lab(c) {
    var p = parse(c); if (!p) return null
    var r = _lin(p[0]), g = _lin(p[1]), b = _lin(p[2])
    var x = (0.4124 * r + 0.3576 * g + 0.1805 * b) / 0.95047
    var y =  0.2126 * r + 0.7152 * g + 0.0722 * b
    var z = (0.0193 * r + 0.1192 * g + 0.9505 * b) / 1.08883
    var fx = _f(x), fy = _f(y), fz = _f(z)
    return [116 * fy - 16, 500 * (fx - fy), 200 * (fy - fz)]
}
// → [L, C, h(radians)] or null
function lch(c) {
    var q = lab(c); if (!q) return null
    return [q[0], Math.sqrt(q[1] * q[1] + q[2] * q[2]), Math.atan2(q[2], q[1])]
}
function _rgbOfLab(L, a, b) {
    var fy = (L + 16) / 116
    var x = 0.95047 * _finv(fy + a / 500), y = _finv(fy), z = 1.08883 * _finv(fy - b / 200)
    return [_gam( 3.2406 * x - 1.5372 * y - 0.4986 * z),
            _gam(-0.9689 * x + 1.8758 * y + 0.0415 * z),
            _gam( 0.0557 * x - 0.2040 * y + 1.0570 * z)]
}
function _inGamut(o) {
    return o[0] > -0.002 && o[0] < 1.002 && o[1] > -0.002 && o[1] < 1.002 && o[2] > -0.002 && o[2] < 1.002
}
function _clamp01(v) { return Math.min(1, Math.max(0, v)) }
// LCh → QML color; out-of-gamut colours lose chroma (never hue or lightness)
function fromLch(L, C, h, alpha) {
    L = Math.max(0, Math.min(100, L)); C = Math.max(0, C)
    var o = _rgbOfLab(L, C * Math.cos(h), C * Math.sin(h))
    for (var k = 0; k < 40 && !_inGamut(o); k++) {
        C *= 0.9
        o = _rgbOfLab(L, C * Math.cos(h), C * Math.sin(h))
    }
    return Qt.rgba(_clamp01(o[0]), _clamp01(o[1]), _clamp01(o[2]), alpha === undefined ? 1 : alpha)
}
function _alpha(c) { var p = parse(c); return p ? p[3] : 1 }

// Same hue and chroma, lightness set to L (0..100).
function withL(c, L) {
    var q = lch(c); if (!q) return c
    return fromLch(L, q[1], q[2], _alpha(c))
}
// Perceptual lightness step (+ lighter, - darker), in L units.
function shade(c, dL) {
    var q = lch(c); if (!q) return c
    return fromLch(q[0] + dL, q[1], q[2], _alpha(c))
}
// Same colour, chroma capped at maxC — for tones that should carry a hint of
// the palette without becoming a second competing colour.
function tone(c, L, maxC) {
    var q = lch(c); if (!q) return c
    return fromLch(L, Math.min(q[1], maxC === undefined ? q[1] : maxC), q[2], _alpha(c))
}
// Mix in Lab (t = 0 → a, 1 → b).
function mix(a, b, t) {
    var p = lab(a), q = lab(b); if (!p || !q) return a
    var L = p[0] + (q[0] - p[0]) * t, A = p[1] + (q[1] - p[1]) * t, B = p[2] + (q[2] - p[2]) * t
    var o = _rgbOfLab(L, A, B)
    var al = _alpha(a) + (_alpha(b) - _alpha(a)) * t
    return Qt.rgba(_clamp01(o[0]), _clamp01(o[1]), _clamp01(o[2]), al)
}
function withAlpha(c, a) { var p = parse(c); return p ? Qt.rgba(p[0], p[1], p[2], a) : c }

// ── contrast (WCAG 2.x) ──────────────────────────────────────────────────
function luminance(c) {
    var p = parse(c); if (!p) return 0
    return 0.2126 * _lin(p[0]) + 0.7152 * _lin(p[1]) + 0.0722 * _lin(p[2])
}
function contrast(a, b) {
    var x = luminance(a), y = luminance(b)
    return (Math.max(x, y) + 0.05) / (Math.min(x, y) + 0.05)
}
// true when light text reads better than dark text on this ground
function isDark(bg) { return contrast(bg, "#ffffff") >= contrast(bg, "#000000") }
// fg moved away from bg in lightness (hue kept) until the ratio is >= min.
// Returns fg untouched when it already passes, so a palette's own tuned ink
// is never changed unless it would actually be hard to read.
function readable(fg, bg, min) {
    min = min || 4.5
    if (contrast(fg, bg) >= min) return fg
    var q = lch(fg); if (!q) return fg
    var up = isDark(bg), L = q[0], out = fg
    for (var k = 0; k < 50; k++) {
        L += up ? 2 : -2
        if (L > 100 || L < 0) break
        out = fromLch(L, q[1], q[2], _alpha(fg))
        if (contrast(out, bg) >= min) return out
    }
    return up ? Qt.rgba(1, 1, 1, _alpha(fg)) : Qt.rgba(0, 0, 0, _alpha(fg))
}

// ── semantic colours in the palette's material ───────────────────────────
// A category's blue or an alert's red must stay recognisably blue or red, but
// a stock web-UI blue sits on a Belle-Époque palette like a sticker. harmonize
// keeps the colour's own hue identity, pulls the hue `pull` (0..1) of the way
// toward the anchor (the palette accent), and re-makes it at lightness L and
// chroma C, so every semantic colour shares the palette's weight.
function _hueToward(h, target, t) {
    var d = target - h
    while (d >  Math.PI) d -= 2 * Math.PI
    while (d < -Math.PI) d += 2 * Math.PI
    return h + d * t
}
function harmonize(c, anchor, L, C, pull) {
    var q = lch(c); if (!q) return c
    var a = lch(anchor)
    var h = (a && a[1] > 6) ? _hueToward(q[2], a[2], pull === undefined ? 0.15 : pull) : q[2]
    return fromLch(L === undefined ? q[0] : L, C === undefined ? q[1] : C, h, _alpha(c))
}

// ── Canvas helpers ───────────────────────────────────────────────────────
function css(c, alpha) {
    var p = parse(c); if (!p) return c
    var a = alpha === undefined ? p[3] : alpha
    return "rgba(" + Math.round(p[0] * 255) + "," + Math.round(p[1] * 255) + "," + Math.round(p[2] * 255) + "," + a + ")"
}
function hex(c) {
    var p = parse(c); if (!p) return c
    function h2(v) { var s = Math.round(v * 255).toString(16); return s.length < 2 ? "0" + s : s }
    return "#" + h2(p[0]) + h2(p[1]) + h2(p[2])
}
