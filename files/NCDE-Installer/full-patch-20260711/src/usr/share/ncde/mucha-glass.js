// mucha-glass.js — Mucha ornamental frame painter for NCDEGlass2.
// Pure Canvas 2D, .pragma library. Draws ONLY the leaded frame + corner
// medallions + optional crest ON TOP of the frosted-glass blur pipeline.
// The blur/tint/glow themselves are handled by NCDEGlass2.qml (ported from
// NCDEGlassSurface). Jewels use accentColor / glowColor from ncde.*.
// Leading + leaves follow the Iris Chroma palette when the caller passes
// opts.leading / opts.leaf (NCDEGlass2 passes ncde.gilt4/gilt2/gilt0 + verd),
// so a cold palette gets cold metal instead of fixed warm gold. The constants
// below are only the fallback when no palette is supplied.
//
// Export: paintMuchaFrame(ctx, w, h, radius, accentColor, glowColor, opts)
//   opts = { crest: bool, corners: bool, inset: number,
//            leading: { bright, mid, deep }, leaf: color }
.pragma library

var LEADING_BRIGHT = "rgba(240, 210, 122, 1.0)";
var LEADING        = "rgba(184, 138, 50, 1.0)";
var LEADING_DEEP   = "rgba(74, 50, 8, 1.0)";
var LEAF           = "rgba(42, 74, 58, 1.0)";

function toRgba(c, a) {
    if (a === undefined) a = 1;
    if (typeof c !== "string") {
        return "rgba(" + Math.round(c.r*255) + "," + Math.round(c.g*255) + ","
                       + Math.round(c.b*255) + "," + a + ")";
    }
    if (c.charAt(0) === "#" && c.length === 7) {
        return "rgba(" + parseInt(c.substring(1,3),16) + ","
                       + parseInt(c.substring(3,5),16) + ","
                       + parseInt(c.substring(5,7),16) + "," + a + ")";
    }
    // rgb()/rgba() strings: re-emit with the requested alpha. Previously these fell
    // through unchanged, so toRgba(LEADING_BRIGHT, 0.45) drew the "faint" inner
    // line at full opacity.
    var m = /^rgba?\(\s*([\d.]+)\s*,\s*([\d.]+)\s*,\s*([\d.]+)/.exec(c);
    if (m) return "rgba(" + m[1] + "," + m[2] + "," + m[3] + "," + a + ")";
    return c;
}

function roundRectPath(ctx, x, y, w, h, r) {
    if (r > w/2) r = w/2;
    if (r > h/2) r = h/2;
    ctx.beginPath();
    ctx.moveTo(x+r, y);
    ctx.lineTo(x+w-r, y);
    ctx.quadraticCurveTo(x+w, y, x+w, y+r);
    ctx.lineTo(x+w, y+h-r);
    ctx.quadraticCurveTo(x+w, y+h, x+w-r, y+h);
    ctx.lineTo(x+r, y+h);
    ctx.quadraticCurveTo(x, y+h, x, y+h-r);
    ctx.lineTo(x, y+r);
    ctx.quadraticCurveTo(x, y, x+r, y);
    ctx.closePath();
}

// One corner ornament: whiplash curls running a short way down each edge from
// the corner, plus a jewel sitting on the corner. Drawn for the top-left
// corner in local space; the dispatcher flips it for the other three.
function cornerOrnament(ctx, r, accentColor, glowColor, pal) {
    // curls along the two edges meeting at this corner
    ctx.strokeStyle = pal.bright;
    ctx.lineWidth = 1.2;
    // horizontal curl (running right along the top edge)
    ctx.beginPath();
    ctx.moveTo(r + 2, 3);
    ctx.quadraticCurveTo(r + 18, 3, r + 22, 11);
    ctx.quadraticCurveTo(r + 24, 4, r + 30, 4);
    ctx.stroke();
    // vertical curl (running down the left edge)
    ctx.beginPath();
    ctx.moveTo(3, r + 2);
    ctx.quadraticCurveTo(3, r + 18, 11, r + 22);
    ctx.quadraticCurveTo(4, r + 24, 4, r + 30);
    ctx.stroke();
    // little leaf on each curl
    ctx.fillStyle = toRgba(pal.leaf, 0.85);
    ctx.beginPath(); ctx.ellipse(r + 30, 4, 3.2, 1.5, -0.5, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.beginPath(); ctx.ellipse(4, r + 30, 1.5, 3.2, -0.5, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    // corner jewel medallion
    var jx = r * 0.62 + 2, jy = r * 0.62 + 2;
    var g = ctx.createRadialGradient(jx - 1.5, jy - 1.5, 0, jx, jy, 5.5);
    g.addColorStop(0, "rgba(255, 235, 175, 1)");
    g.addColorStop(0.55, toRgba(accentColor, 0.9));
    g.addColorStop(1, toRgba(glowColor, 0.6));
    ctx.fillStyle = g;
    ctx.strokeStyle = pal.bright;
    ctx.lineWidth = 0.9;
    ctx.beginPath(); ctx.arc(jx, jy, 4.5, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.fillStyle = "rgba(255, 240, 200, 1)";
    ctx.beginPath(); ctx.arc(jx, jy, 1.4, 0, Math.PI*2); ctx.fill();
}

// Verdigris (2026-09-25, BEAUTIFY-NEXT #32): bronze patina gathers where the curls
// root into the corner and in the recess behind the corner jewel. Soft radial
// spots in the palette's own verd, lifted toward the pale blue-green of copper
// carbonate. Drawn in the TL corner's local space, flipped like the ornament.
function patinaOf(leaf) {
    var m = /^rgba?\(\s*([\d.]+)\s*,\s*([\d.]+)\s*,\s*([\d.]+)/.exec(toRgba(leaf, 1));
    var r = m ? +m[1] : 42, g = m ? +m[2] : 74, b = m ? +m[3] : 58;
    // halfway to verdigris' pale blue-green, keeping the palette's own cast
    return [Math.round(r + (150 - r) * 0.55), Math.round(g + (205 - g) * 0.55), Math.round(b + (188 - b) * 0.55)];
}
function patinaSpot(ctx, x, y, rad, p, a) {
    var g = ctx.createRadialGradient(x, y, 0, x, y, rad);
    g.addColorStop(0.0, "rgba(" + p[0] + "," + p[1] + "," + p[2] + "," + a + ")");
    g.addColorStop(1.0, "rgba(" + p[0] + "," + p[1] + "," + p[2] + ",0)");
    ctx.fillStyle = g;
    ctx.beginPath(); ctx.arc(x, y, rad, 0, Math.PI * 2); ctx.fill();
}
function cornerPatina(ctx, r, p) {
    var jx = r * 0.62 + 2, jy = r * 0.62 + 2;
    patinaSpot(ctx, jx + 1.5, jy + 1.5, 8.5, p, 0.40);   // behind the corner jewel
    patinaSpot(ctx, r + 4, 4, 6, p, 0.36);           // root of the top curl
    patinaSpot(ctx, 4, r + 4, 6, p, 0.36);           // root of the side curl
}

// Small leafy crest finial straddling the top-centre of the frame.
function topCrest(ctx, cx, baseY, width, accentColor, pal) {
    ctx.save();
    ctx.translate(cx, baseY);
    var s = width / 90;
    ctx.scale(s, s);
    ctx.fillStyle = toRgba(pal.leaf, 0.92);
    ctx.strokeStyle = pal.bright;
    ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.quadraticCurveTo(-20, -7, -33, -2);
    ctx.quadraticCurveTo(-25, -15, -11, -17);
    ctx.quadraticCurveTo(-20, -24, -16, -35);
    ctx.quadraticCurveTo(-8, -28, 0, -20);
    ctx.quadraticCurveTo(8, -28, 16, -35);
    ctx.quadraticCurveTo(20, -24, 11, -17);
    ctx.quadraticCurveTo(25, -15, 33, -2);
    ctx.quadraticCurveTo(20, -7, 0, 0);
    ctx.closePath();
    ctx.fill(); ctx.stroke();
    ctx.fillStyle = toRgba(accentColor, 0.95);
    ctx.beginPath(); ctx.ellipse(0, -8, 3.5, 9, 0, 0, Math.PI*2); ctx.fill(); ctx.stroke();
    ctx.restore();
}

// ── Master frame painter ───────────────────────────────────────
function paintMuchaFrame(ctx, w, h, radius, accentColor, glowColor, opts) {
    opts = opts || {};
    var crest   = opts.crest   !== undefined ? opts.crest   : true;
    var corners = opts.corners !== undefined ? opts.corners : true;
    var inset   = opts.inset   !== undefined ? opts.inset   : 3;
    var ld      = opts.leading || {};
    var pal = {
        bright: ld.bright !== undefined ? toRgba(ld.bright, 1) : LEADING_BRIGHT,
        mid:    ld.mid    !== undefined ? toRgba(ld.mid,    1) : LEADING,
        deep:   ld.deep   !== undefined ? toRgba(ld.deep,   1) : LEADING_DEEP,
        leaf:   opts.leaf !== undefined ? opts.leaf : LEAF
    };

    ctx.clearRect(0, 0, w, h);
    ctx.save();

    // Outer double gold leading
    var og = ctx.createLinearGradient(0, 0, 0, h);
    og.addColorStop(0, pal.bright);
    og.addColorStop(0.5, pal.mid);
    og.addColorStop(1, pal.deep);
    ctx.strokeStyle = og;
    ctx.lineWidth = 2;
    roundRectPath(ctx, inset, inset, w - inset*2, h - inset*2, radius);
    ctx.stroke();

    // Came crown (2026-09-25, BEAUTIFY-NEXT #31): real lead came is rounded on
    // top, so a thin highlight runs along the middle of the line — brightest on
    // the side facing the shell's one light (opts.light, from ShellLight), fading
    // round to nothing on the far side. Same path, so it follows every curve.
    var L = opts.light;
    if (L && L.css) {
        var ex = Math.abs(L.lx) * w / 2 + Math.abs(L.ly) * h / 2;
        var cg = ctx.createLinearGradient(w / 2 + L.lx * ex, h / 2 + L.ly * ex,
                                          w / 2 - L.lx * ex, h / 2 - L.ly * ex);
        cg.addColorStop(0.0, L.css(0.55));
        cg.addColorStop(0.5, L.css(0.14));
        cg.addColorStop(1.0, L.css(0.0));
        ctx.strokeStyle = cg;
        ctx.lineWidth = 0.6;
        roundRectPath(ctx, inset, inset, w - inset*2, h - inset*2, radius);
        ctx.stroke();
    }

    // Inner thin line
    ctx.strokeStyle = toRgba(pal.bright, 0.45);
    ctx.lineWidth = 0.7;
    var i2 = inset + 3;
    roundRectPath(ctx, i2, i2, w - i2*2, h - i2*2,
                  Math.max(0, radius - 3));
    ctx.stroke();

    // Top inner sheen (subtle bevel — reads as thick glass). 2026-09-25: fades
    // out at both ends instead of stopping square (operator: no harsh lines)
    var sx0 = radius + 4, sx1 = w - radius - 4;
    var sg = ctx.createLinearGradient(sx0, 0, sx1, 0);
    var sc = (L && L.css) ? L.css : function (a) { return "rgba(255, 255, 255, " + a + ")"; };
    sg.addColorStop(0.0, sc(0)); sg.addColorStop(0.2, sc(0.18)); sg.addColorStop(0.8, sc(0.18)); sg.addColorStop(1.0, sc(0));
    ctx.strokeStyle = sg;
    ctx.lineWidth = 0.8;
    ctx.beginPath();
    ctx.moveTo(radius + 4, inset + 4.5);
    ctx.lineTo(w - radius - 4, inset + 4.5);
    ctx.stroke();

    // Corner medallions (flip the TL ornament into each corner)
    if (corners) {
        var r = radius;
        // verdigris first, under the curls — clipped to the frame's rounded outline
        // so no patina reaches past it (operator: no harsh lines)
        var pat = patinaOf(pal.leaf);
        ctx.save();
        roundRectPath(ctx, inset, inset, w - inset*2, h - inset*2, radius);
        ctx.clip();
        ctx.save(); ctx.translate(inset, inset); cornerPatina(ctx, r, pat); ctx.restore();
        ctx.save(); ctx.translate(w - inset, inset); ctx.scale(-1, 1); cornerPatina(ctx, r, pat); ctx.restore();
        ctx.save(); ctx.translate(inset, h - inset); ctx.scale(1, -1); cornerPatina(ctx, r, pat); ctx.restore();
        ctx.save(); ctx.translate(w - inset, h - inset); ctx.scale(-1, -1); cornerPatina(ctx, r, pat); ctx.restore();
        ctx.restore();
        // TL
        ctx.save(); ctx.translate(inset, inset); cornerOrnament(ctx, r, accentColor, glowColor, pal); ctx.restore();
        // TR
        ctx.save(); ctx.translate(w - inset, inset); ctx.scale(-1, 1); cornerOrnament(ctx, r, accentColor, glowColor, pal); ctx.restore();
        // BL
        ctx.save(); ctx.translate(inset, h - inset); ctx.scale(1, -1); cornerOrnament(ctx, r, accentColor, glowColor, pal); ctx.restore();
        // BR
        ctx.save(); ctx.translate(w - inset, h - inset); ctx.scale(-1, -1); cornerOrnament(ctx, r, accentColor, glowColor, pal); ctx.restore();
    }

    // Crest at the top centre
    if (crest) {
        topCrest(ctx, w / 2, inset + 1, Math.min(w * 0.28, 64), accentColor, pal);
    }

    ctx.restore();
}
