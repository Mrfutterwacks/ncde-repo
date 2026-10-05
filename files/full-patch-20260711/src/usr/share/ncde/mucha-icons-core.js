// mucha-icons-core.js  —  Art Nouveau (Mucha) NCDE icon theme : shared primitives.
//
// Palette, normalisation helpers, geometric primitives, ornamental composers.
// Every drawing function in apps / tray / places / devices / mimes is built
// from the building blocks defined here.
//
// CANVAS PORTABILITY: Functions use only Canvas 2D API common to QML and HTML.
// CSS-color strings everywhere — never QML color objects, never Qt.lighter/darker.

.pragma library

// ============================================================================
// 1. PALETTE — Mucha's Salons, Sarah Bernhardt posters, the Slav Epic.
// ============================================================================

var PALETTE = {
    // Background tile gradient stops (warm aged paper)
    bgCreamHi:  "#f4ead0",
    bgCream:    "#ebdcb4",
    bgPaper:    "#dcc99a",
    bgShade:    "#b89d6b",

    // Inks & outlines  (stained-glass: near-black lead came)
    ink:        "#0b0b14",     // black lead came — primary outline
    inkSoft:    "#1c1c2a",     // softer came
    inkVeil:    "rgba(11,11,20,0.35)",

    // Lead came + stained-glass field (Tiffany medallion frame)
    came:       "#0b0b14",     // heavy black came
    cameLip:    "#23233a",     // came highlight
    glassWhite: "#eef4f8",     // clear/white bezel pane
    glassWhiteHi:"#ffffff",
    glassSky:   "#3a9fd4",     // sky-blue bezel pane
    glassSkyHi: "#7fd0f0",
    glassSkyDk: "#1f6fa6",
    fieldBlue:  "#2a5aa6",     // deep blue inner field (mid)
    fieldBlueHi:"#4d86d8",     // field highlight (streak)
    fieldBlueDk:"#15306a",     // field shade (edge)

    // Gilt accents (medallions, halos, fillets)
    gold:       "#b58c4a",
    goldHi:     "#e6c785",
    goldDark:   "#7a5a26",
    goldShine:  "rgba(255,235,180,0.85)",

    // Mucha greens
    sage:       "#8fa68a",
    sageDeep:   "#5d7861",
    sageDark:   "#3f5a44",
    sageMist:   "#b8c9b2",

    // Roses, terracottas, plums
    rose:       "#c89283",
    roseDeep:   "#a86b58",
    terra:      "#b56340",
    terraDark:  "#7a3e22",
    plum:       "#6e4858",
    plumDeep:   "#43293a",

    // Cools — used sparingly for water/electric metaphors
    teal:       "#6b8e8f",
    tealDeep:   "#3f6263",
    indigo:     "#3d4866",
    indigoDeep: "#23304a",

    // Contract-required generic names (so callers can write PALETTE.bg, .border…)
    bg:         "#ebdcb4",
    border:     "#7a5a26",
    accent:     "#b58c4a",
    glow:       "rgba(230,199,133,0.55)",
    halo:       "rgba(255,235,180,0.45)",

    // Working aliases used by hashColor()
    HASH: [
        "#b58c4a", "#8fa68a", "#c89283", "#6b8e8f", "#6e4858",
        "#a86b58", "#5d7861", "#b56340", "#3d4866", "#7a5a26"
    ]
};

// ============================================================================
// 2. MATCHING HELPERS
// ============================================================================

function normalizeKey(name) {
    // Lowercase, strip non-alphanumeric, pad with spaces so word-boundary
    // matches in hasAny() (which checks " term " inside " name ") work cleanly.
    if (!name) return "  ";
    var s = String(name).toLowerCase();
    var out = " ";
    for (var i = 0; i < s.length; i++) {
        var c = s.charCodeAt(i);
        if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122)) {
            out += s.charAt(i);
        } else {
            if (out.charAt(out.length - 1) !== " ") out += " ";
        }
    }
    if (out.charAt(out.length - 1) !== " ") out += " ";
    return out;
}

function hasAny(n, terms) {
    if (!n || !terms) return false;
    for (var i = 0; i < terms.length; i++) {
        var t = terms[i];
        if (!t) continue;
        if (n.indexOf(" " + t + " ") !== -1) return true;
        // also accept contiguous substring for compound names
        if (n.indexOf(t) !== -1 && t.length >= 4) return true;
    }
    return false;
}

function hashCode(s) {
    var h = 0;
    s = String(s || "");
    for (var i = 0; i < s.length; i++) {
        h = ((h << 5) - h) + s.charCodeAt(i);
        h |= 0;
    }
    return Math.abs(h);
}

function hashColor(name, palette) {
    var arr = palette || PALETTE.HASH;
    return arr[hashCode(name) % arr.length];
}

function hashPick(name, arr) { return arr[hashCode(name) % arr.length]; }

// ============================================================================
// 3. LOW-LEVEL GEOMETRY HELPERS
// ============================================================================

function withScale(ctx, s, fn) {
    // Many draw routines below are written for a 48px canvas; scale up/down.
    ctx.save();
    ctx.scale(s / 48, s / 48);
    fn(ctx);
    ctx.restore();
}

function setStroke(ctx, color, w) {
    ctx.strokeStyle = color;
    ctx.lineWidth = w;
    ctx.lineCap = "round";
    ctx.lineJoin = "round";
}

function fillPath(ctx, color) {
    ctx.fillStyle = color;
    ctx.fill();
}

function ringDots(ctx, cx, cy, r, count, dotR, color) {
    ctx.fillStyle = color;
    for (var i = 0; i < count; i++) {
        var a = (i / count) * Math.PI * 2 - Math.PI / 2;
        var x = cx + Math.cos(a) * r;
        var y = cy + Math.sin(a) * r;
        ctx.beginPath();
        ctx.arc(x, y, dotR, 0, Math.PI * 2);
        ctx.fill();
    }
}

function arcRing(ctx, cx, cy, r, a0, a1, color, w) {
    setStroke(ctx, color, w);
    ctx.beginPath();
    ctx.arc(cx, cy, r, a0, a1);
    ctx.stroke();
}

function leafBead(ctx, cx, cy, len, ang, color) {
    // small almond / leaf bead — used for laurels & beaded rings
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(ang);
    ctx.fillStyle = color;
    ctx.beginPath();
    ctx.moveTo(-len * 0.5, 0);
    ctx.quadraticCurveTo(0, -len * 0.35, len * 0.5, 0);
    ctx.quadraticCurveTo(0,  len * 0.35, -len * 0.5, 0);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

function laurelRing(ctx, cx, cy, r, count, leafLen, color) {
    for (var i = 0; i < count; i++) {
        var a = (i / count) * Math.PI * 2 - Math.PI / 2;
        var x = cx + Math.cos(a) * r;
        var y = cy + Math.sin(a) * r;
        leafBead(ctx, x, y, leafLen, a + Math.PI / 2, color);
    }
}

function gradient(ctx, x0, y0, x1, y1, stops) {
    var g = ctx.createLinearGradient(x0, y0, x1, y1);
    for (var i = 0; i < stops.length; i++) g.addColorStop(stops[i][0], stops[i][1]);
    return g;
}

function radial(ctx, cx, cy, r0, r1, stops) {
    var g = ctx.createRadialGradient(cx, cy, r0, cx, cy, r1);
    for (var i = 0; i < stops.length; i++) g.addColorStop(stops[i][0], stops[i][1]);
    return g;
}

// ============================================================================
// 4. THE TILE — leaded stained-glass medallion (Tiffany style).
//    Every icon, whatever `shape` it asks for, now renders this frame:
//      • heavy black lead-came outer ring
//      • segmented bezel band of alternating sky-blue / clear glass panes,
//        divided by radial came lines
//      • a deep-blue opalescent inner field with diagonal light streaks
//    The motif then draws on top of the blue field.
// ============================================================================

// "#rrggbb" / "#aarrggbb" -> [r,g,b], or null for anything else (rgba(), names).
function _hexRgb(c) {
    c = "" + c;
    if (c.charAt(0) !== "#") return null;
    if (c.length === 9) c = "#" + c.substring(3);
    if (c.length !== 7) return null;
    return [parseInt(c.substring(1,3),16), parseInt(c.substring(3,5),16), parseInt(c.substring(5,7),16)];
}
// Blend two hex colours (t = 0 -> a, 1 -> b); "" when either is unparseable.
function _mixHex(a, b, t) {
    var A = _hexRgb(a), B = _hexRgb(b);
    if (!A || !B) return "";
    function h(i) { var v = Math.round(A[i] + (B[i] - A[i]) * t); return (v < 16 ? "0" : "") + v.toString(16); }
    return "#" + h(0) + h(1) + h(2);
}

function drawTile(ctx, s, baseColor, opts) {
    // Signature preserved for compatibility. `shape`/`ornament`/`halo`/`rim`
    // are accepted but the medallion frame is always drawn (the reference
    // sheet is uniformly circular). `accent` tints the innermost came fillet.
    opts = opts || {};
    var accent = opts.accent || PALETTE.gold;

    // Bezel panes + field follow Iris Chroma (2026-09-24): the tinted panes were a fixed
    // Tiffany sky-blue that clashed with every non-blue palette. Every caller
    // already passes the Iris accent; derive the pane gradient from it and warm
    // the clear panes a touch toward it. Unparseable accent -> original sky-blue.
    var paneHi  = _mixHex(accent, "#ffffff", 0.45) || PALETTE.glassSkyHi;
    var paneMid = _mixHex(accent, "#ffffff", 0.08) || PALETTE.glassSky;
    var paneDk  = _mixHex(accent, "#000000", 0.35) || PALETTE.glassSkyDk;
    var clearHi = PALETTE.glassWhiteHi;
    var clear   = _mixHex(PALETTE.glassWhite, accent, 0.40) || PALETTE.glassWhite;
    // Inner field: the same deep glass, hued from the accent but kept dark so the
    // light motifs drawn on it keep their contrast (was fixed deep blue).
    var fieldHi = _mixHex(accent, "#000000", 0.40) || PALETTE.fieldBlueHi;
    var fieldMd = _mixHex(accent, "#000000", 0.62) || PALETTE.fieldBlue;
    var fieldDk = _mixHex(accent, "#000000", 0.80) || PALETTE.fieldBlueDk;

    var cx = s * 0.5, cy = s * 0.5;
    var R  = s * 0.485;            // outer radius (small bleed margin)

    var rBezelOut = R;             // outer edge of segmented band
    var rBezelIn  = R * 0.82;      // inner edge of segmented band (thin bezel)
    var rField    = R * 0.78;      // inner glass field radius (dominant)

    ctx.save();

    // ---- 1. OUTER BLACK CAME DISC ----------------------------------------
    ctx.beginPath();
    ctx.arc(cx, cy, R, 0, Math.PI * 2);
    ctx.fillStyle = PALETTE.came;
    ctx.fill();

    // ---- 2. SEGMENTED BEZEL BAND -----------------------------------------
    // 16 wedges alternating sky-blue and clear, leaving thin came gaps.
    var segs = 16;
    var gap  = 0.045;              // radians of came between segments
    for (var i = 0; i < segs; i++) {
        var a0 = (i / segs) * Math.PI * 2 - Math.PI / 2 + gap / 2;
        var a1 = ((i + 1) / segs) * Math.PI * 2 - Math.PI / 2 - gap / 2;
        var sky = (i % 2 === 0);

        ctx.beginPath();
        ctx.arc(cx, cy, rBezelOut - s * 0.012, a0, a1, false);
        ctx.arc(cx, cy, rBezelIn  + s * 0.006, a1, a0, true);
        ctx.closePath();

        var mid = (a0 + a1) / 2;
        var gx = cx + Math.cos(mid) * (rBezelIn + rBezelOut) / 2;
        var gy = cy + Math.sin(mid) * (rBezelIn + rBezelOut) / 2;
        if (sky) {
            ctx.fillStyle = radial(ctx, gx, gy, 0, s * 0.12, [
                [0, paneHi], [0.6, paneMid], [1, paneDk]
            ]);
        } else {
            ctx.fillStyle = radial(ctx, gx, gy, 0, s * 0.12, [
                [0, clearHi], [1, clear]
            ]);
        }
        ctx.fill();
        // little inner sheen on each pane
        ctx.fillStyle = "rgba(255,255,255,0.18)";
        ctx.beginPath();
        ctx.arc(cx, cy, rBezelOut - s * 0.012, a0, (a0 + a1) / 2, false);
        ctx.arc(cx, cy, rBezelIn  + s * 0.006, (a0 + a1) / 2, a0, true);
        ctx.closePath();
        ctx.fill();
    }

    // ---- 3. CAME RINGS bounding the bezel --------------------------------
    setStroke(ctx, PALETTE.came, s * 0.018);
    ctx.beginPath(); ctx.arc(cx, cy, rBezelOut - s * 0.006, 0, Math.PI * 2); ctx.stroke();
    setStroke(ctx, PALETTE.came, s * 0.030);
    ctx.beginPath(); ctx.arc(cx, cy, rBezelIn, 0, Math.PI * 2); ctx.stroke();

    // ---- 4. INNER GLASS FIELD (deep blue, opalescent) --------------------
    ctx.beginPath();
    ctx.arc(cx, cy, rField, 0, Math.PI * 2);
    ctx.fillStyle = radial(ctx, cx - rField * 0.3, cy - rField * 0.35, rField * 0.05, rField * 1.15, [
        [0, fieldHi],
        [0.5, fieldMd],
        [1, fieldDk]
    ]);
    ctx.fill();

    // diagonal opalescent streaks
    ctx.save();
    ctx.beginPath();
    ctx.arc(cx, cy, rField, 0, Math.PI * 2);
    ctx.clip();
    ctx.strokeStyle = "rgba(255,255,255,0.10)";
    ctx.lineWidth = s * 0.05;
    for (var k = -3; k <= 3; k++) {
        ctx.beginPath();
        ctx.moveTo(cx - rField + k * s * 0.16, cy - rField);
        ctx.lineTo(cx + rField + k * s * 0.16, cy + rField);
        ctx.stroke();
    }
    ctx.restore();

    // ---- 5. ACCENT FILLET + FIELD CAME -----------------------------------
    setStroke(ctx, accent, s * 0.012);
    ctx.globalAlpha = 0.9;
    ctx.beginPath(); ctx.arc(cx, cy, rField + s * 0.012, 0, Math.PI * 2); ctx.stroke();
    ctx.globalAlpha = 1;
    setStroke(ctx, PALETTE.came, s * 0.022);
    ctx.beginPath(); ctx.arc(cx, cy, rField, 0, Math.PI * 2); ctx.stroke();

    ctx.restore();
}

// Legacy helper retained for any caller that referenced shapes directly.
function _legacyBodyShape() { /* no-op: medallion frame is now universal */ }

// ============================================================================
// 4b. GLASS SURFACE — glossy specular overlay, drawn AFTER the motif so the
//     sheen sweeps across glass and lead came alike (like a real window).
//     Call once at the very end of every icon.
// ============================================================================
function drawGlassSurface(ctx, s) {
    var cx = s * 0.5, cy = s * 0.5;
    var R  = s * 0.485;

    ctx.save();
    // clip to the medallion so the gloss never spills past the rim
    ctx.beginPath();
    ctx.arc(cx, cy, R, 0, Math.PI * 2);
    ctx.clip();

    // 1. broad upper-left reflection (soft curved sweep)
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(-0.5);
    var g = ctx.createLinearGradient(0, -R, 0, R * 0.25);
    g.addColorStop(0,   "rgba(255,255,255,0.34)");
    g.addColorStop(0.4, "rgba(255,255,255,0.12)");
    g.addColorStop(1,   "rgba(255,255,255,0.0)");
    ctx.fillStyle = g;
    ctx.beginPath();
    ctx.ellipse(0, -R * 0.34, R * 1.05, R * 0.78, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();

    // 2. bright crescent gloss hugging the top rim
    ctx.beginPath();
    ctx.arc(cx, cy, R * 0.93, Math.PI * 1.12, Math.PI * 1.88, false);
    ctx.arc(cx, cy, R * 0.62, Math.PI * 1.88, Math.PI * 1.12, true);
    ctx.closePath();
    var g2 = ctx.createLinearGradient(0, cy - R, 0, cy);
    g2.addColorStop(0, "rgba(255,255,255,0.40)");
    g2.addColorStop(1, "rgba(255,255,255,0.0)");
    ctx.fillStyle = g2;
    ctx.fill();

    // 3. small hard glint near the top-left
    ctx.beginPath();
    ctx.ellipse(cx - R * 0.34, cy - R * 0.42, R * 0.16, R * 0.07, -0.7, 0, Math.PI * 2);
    ctx.fillStyle = "rgba(255,255,255,0.55)";
    ctx.fill();

    // 4. faint lower inner shadow (glass depth)
    var g3 = radial(ctx, cx, cy + R * 0.5, R * 0.2, R, [
        [0, "rgba(0,0,0,0)"],
        [1, "rgba(8,10,30,0.30)"]
    ]);
    ctx.fillStyle = g3;
    ctx.beginPath();
    ctx.arc(cx, cy, R, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
}

// KithGlass — public name for the glass-surface overlay applied to icons.
function KithGlass(ctx, s) { drawGlassSurface(ctx, s); }


function roundRectPath(ctx, x, y, w, h, r) {
    ctx.moveTo(x + r, y);
    ctx.lineTo(x + w - r, y);
    ctx.quadraticCurveTo(x + w, y, x + w, y + r);
    ctx.lineTo(x + w, y + h - r);
    ctx.quadraticCurveTo(x + w, y + h, x + w - r, y + h);
    ctx.lineTo(x + r, y + h);
    ctx.quadraticCurveTo(x, y + h, x, y + h - r);
    ctx.lineTo(x, y + r);
    ctx.quadraticCurveTo(x, y, x + r, y);
    ctx.closePath();
}

function shieldPath(ctx, w) {
    ctx.moveTo(w * 0.5, 0);
    ctx.lineTo(w, w * 0.18);
    ctx.lineTo(w, w * 0.55);
    ctx.quadraticCurveTo(w, w * 0.92, w * 0.5, w);
    ctx.quadraticCurveTo(0, w * 0.92, 0, w * 0.55);
    ctx.lineTo(0, w * 0.18);
    ctx.closePath();
}

function archPath(ctx, w) {
    var r = w * 0.5;
    ctx.moveTo(0, w);
    ctx.lineTo(0, r);
    ctx.arc(r, r, r, Math.PI, 0, false);
    ctx.lineTo(w, w);
    ctx.closePath();
}

function medallionPath(ctx, w) {
    // 8-lobed cusped circle ("gothic foil" — a Mucha favourite for frames)
    var cx = w / 2, cy = w / 2, R = w * 0.5;
    var lobes = 16;
    for (var i = 0; i <= lobes * 8; i++) {
        var t = i / (lobes * 8);
        var a = t * Math.PI * 2;
        var k = 1 + 0.022 * Math.cos(a * lobes);
        var x = cx + Math.cos(a) * R * k;
        var y = cy + Math.sin(a) * R * k;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
}

// ============================================================================
// 5. COMPOSITORS — common emblem scaffolds reused across many app icons.
// ============================================================================

// Halo arc behind central glyph (Mucha's signature feature)
function drawHalo(ctx, s, color) {
    color = color || PALETTE.goldShine;
    ctx.save();
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy * 0.92, s * 0.30, Math.PI * 1.05, Math.PI * 1.95);
    setStroke(ctx, color, s * 0.06);
    ctx.globalAlpha = 0.6;
    ctx.stroke();
    ctx.globalAlpha = 1;
    ctx.beginPath();
    ctx.arc(cx, cy * 0.92, s * 0.30, Math.PI * 1.05, Math.PI * 1.95);
    setStroke(ctx, color, s * 0.014);
    ctx.stroke();
    ctx.restore();
}

// Whiplash S-curve (decorative side ornament)
function drawWhiplash(ctx, x0, y0, x1, y1, color, w) {
    ctx.save();
    setStroke(ctx, color, w);
    ctx.beginPath();
    var dx = x1 - x0, dy = y1 - y0;
    var mx = x0 + dx * 0.5, my = y0 + dy * 0.5;
    ctx.moveTo(x0, y0);
    ctx.bezierCurveTo(x0 + dy * 0.4, y0 - dx * 0.4, mx + dy * 0.2, my, mx, my);
    ctx.bezierCurveTo(mx - dy * 0.2, my, x1 - dy * 0.4, y1 + dx * 0.4, x1, y1);
    ctx.stroke();
    ctx.restore();
}

// Mucha "stem with three petals" floral ornament — used as a corner flourish
function drawFloralStem(ctx, x, y, scale, color, accent) {
    ctx.save();
    ctx.translate(x, y);
    ctx.scale(scale, scale);
    setStroke(ctx, color, 0.06);
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.quadraticCurveTo(0.4, -0.3, 0.2, -0.8);
    ctx.stroke();
    // leaves
    ctx.beginPath();
    ctx.moveTo(0.1, -0.2);
    ctx.quadraticCurveTo(0.45, -0.25, 0.25, -0.45);
    ctx.quadraticCurveTo(0.0, -0.35, 0.1, -0.2);
    ctx.closePath();
    fillPath(ctx, accent);
    // little flower head
    ctx.beginPath();
    ctx.arc(0.2, -0.85, 0.12, 0, Math.PI * 2);
    fillPath(ctx, accent);
    ctx.beginPath();
    ctx.arc(0.2, -0.85, 0.05, 0, Math.PI * 2);
    fillPath(ctx, color);
    ctx.restore();
}

// Central emblem disc — a smaller filled medallion behind the figural element
function drawInnerDisc(ctx, s, color, rRatio) {
    rRatio = rRatio || 0.32;
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * rRatio, 0, Math.PI * 2);
    ctx.fillStyle = color;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx, cy, s * rRatio, 0, Math.PI * 2);
    setStroke(ctx, PALETTE.goldDark, Math.max(0.5, s * 0.012));
    ctx.stroke();
}

// Inscription label inside a ribbon banner
function drawBanner(ctx, s, text, color) {
    ctx.save();
    var w = s * 0.62, h = s * 0.18;
    var x = (s - w) / 2, y = s * 0.74;
    ctx.fillStyle = color || PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(x, y + h / 2);
    ctx.lineTo(x + h * 0.5, y);
    ctx.lineTo(x + w - h * 0.5, y);
    ctx.lineTo(x + w, y + h / 2);
    ctx.lineTo(x + w - h * 0.5, y + h);
    ctx.lineTo(x + h * 0.5, y + h);
    ctx.closePath();
    ctx.fill();
    setStroke(ctx, PALETTE.goldDark, Math.max(0.5, s * 0.012));
    ctx.stroke();
    if (text) {
        ctx.fillStyle = PALETTE.ink;
        ctx.font = "600 " + Math.round(s * 0.10) + "px 'Cinzel','Trajan Pro','Times New Roman',serif";
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(text, s * 0.5, y + h * 0.55);
    }
    ctx.restore();
}

// Monogram letter centred in the tile — used by drawDefault().
function drawMonogram(ctx, s, ch, fg, bg) {
    if (bg) drawInnerDisc(ctx, s, bg, 0.34);
    ctx.save();
    ctx.fillStyle = fg || PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.42) + "px 'Cinzel','Trajan Pro','Times New Roman',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText(String(ch).toUpperCase().charAt(0), s * 0.5, s * 0.52);
    ctx.restore();
}

// A simple petal/flower head used as a stand-in figure
function drawRosette(ctx, cx, cy, r, petals, color, eye) {
    ctx.save();
    for (var i = 0; i < petals; i++) {
        var a = (i / petals) * Math.PI * 2;
        ctx.save();
        ctx.translate(cx, cy);
        ctx.rotate(a);
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.quadraticCurveTo(r * 0.35, -r * 0.55, 0, -r);
        ctx.quadraticCurveTo(-r * 0.35, -r * 0.55, 0, 0);
        ctx.closePath();
        ctx.fillStyle = color;
        ctx.fill();
        ctx.restore();
    }
    ctx.beginPath();
    ctx.arc(cx, cy, r * 0.22, 0, Math.PI * 2);
    ctx.fillStyle = eye || PALETTE.gold;
    ctx.fill();
    ctx.restore();
}

// Stippled / hatched shadow texture used inside discs for a print feel
function stipple(ctx, x, y, w, h, density, color) {
    ctx.save();
    ctx.fillStyle = color;
    var n = Math.floor(w * h * density);
    // deterministic dot pattern using hash
    var seed = 1337;
    function rnd() { seed = (seed * 9301 + 49297) % 233280; return seed / 233280; }
    for (var i = 0; i < n; i++) {
        var px = x + rnd() * w;
        var py = y + rnd() * h;
        ctx.fillRect(px, py, 0.6, 0.6);
    }
    ctx.restore();
}
