// settings_colors.js — Filigree Engine colour math (.pragma library, stateless)
.pragma library

// ── HSL → RGB / Hex ──────────────────────────────────────────────────────────
function hslToRgb(h, s, l) {
    h = ((h % 360) + 360) % 360;
    s = Math.max(0, Math.min(1, s));
    l = Math.max(0, Math.min(1, l));
    var a = s * Math.min(l, 1 - l);
    function f(n) {
        var k = (n + h / 30) % 12;
        return l - a * Math.max(-1, Math.min(k - 3, 9 - k, 1));
    }
    return { r: f(0), g: f(8), b: f(4) };
}

function hslToHex(h, s, l) {
    var c = hslToRgb(h, s, l);
    function h2(v) { return Math.round(v * 255).toString(16).padStart(2, "0"); }
    return ("#" + h2(c.r) + h2(c.g) + h2(c.b)).toUpperCase();
}

// ── Derived palette — 5 slots ─────────────────────────────────────────────────
// calm (0–1): desaturates GROUND/SURFACE/HIGHLIGHT/QUILL while keeping ACCENT vivid.
// Returns [GROUND, SURFACE, ACCENT, HIGHLIGHT, QUILL].
// calm defaults to 0 — backwards-compatible with all existing callers.
var SLOTS = [["GROUND",0.18],["SURFACE",0.32],["ACCENT",0.45],["HIGHLIGHT",0.62],["QUILL",0.82]];
function derivedPalette(hue, sat, calm) {
    calm = calm || 0;
    return SLOTS.map(function(slot) {
        var s = slot[0] === "ACCENT" ? sat : sat * (1 - calm * 0.78);
        return hslToHex(hue, s, slot[1]);
    });
}

// ── WCAG contrast ratio ───────────────────────────────────────────────────────
function _lin(v) { v /= 255; return v <= 0.03928 ? v / 12.92 : Math.pow((v + 0.055) / 1.055, 2.4); }
function _lum(hex) {
    var r = parseInt(hex.substr(1,2),16), g = parseInt(hex.substr(3,2),16), b = parseInt(hex.substr(5,2),16);
    return 0.2126*_lin(r) + 0.7152*_lin(g) + 0.0722*_lin(b);
}
function contrastRatio(a, b) {
    var L1 = _lum(a), L2 = _lum(b), hi = Math.max(L1,L2), lo = Math.min(L1,L2);
    return (hi + 0.05) / (lo + 0.05);
}
function contrastGrade(r) { return r >= 7 ? "AAA" : r >= 4.5 ? "AA" : r >= 3 ? "AA Large" : "Fail"; }

// ── Harmony hue sets ──────────────────────────────────────────────────────────
function harmonyHues(h, mode) {
    if (mode === "comp") return [h, (h + 180) % 360];
    if (mode === "tri")  return [h, (h + 120) % 360, (h + 240) % 360];
    if (mode === "ana")  return [(h + 340) % 360, h, (h + 20) % 360];
    return [h];
}

// ── Poetic palette auto-name ──────────────────────────────────────────────────
var POETIC = { 0:"Garnet", 30:"Amber", 45:"Gilt", 60:"Saffron", 90:"Absinthe",
    120:"Verdigris", 160:"Eau-de-Nil", 180:"Cerulean", 210:"Cyan Salon",
    240:"Lapis", 270:"Iris", 300:"Plum", 330:"Rose" };
var MOODS = ["Nocturne","Salon","Aurore","Crépuscule","Reverie"];
function poeticName(h, l) {
    var best = 0, bd = 999;
    for (var k in POETIC) {
        var d = Math.min(Math.abs(h - k), 360 - Math.abs(h - k));
        if (d < bd) { bd = d; best = k; }
    }
    return POETIC[best] + " " + MOODS[Math.floor((l || 0.45) * MOODS.length) % MOODS.length];
}
