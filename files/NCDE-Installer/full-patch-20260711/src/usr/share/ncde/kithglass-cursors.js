// kithglass-cursors.js — stained-glass (Tiffany) cursor set for NCDE.
// Qt Canvas drawing library — NO png, NO svg. Same convention as the icon
// theme: a .pragma library of plain draw functions, matched by name.
//
// Every draw fn: (ctx, s, accent, glow [, t])  where t is 0..1 anim phase
// (used by the wait spinner). Hotspots are fractional (x,y) of the canvas.

.pragma library

var PALETTE = {
    came:    "#0b0b14",
    cameLip: "#2a2a40",
    glassHi: "#7fd0f0",
    glass:   "#3a78c8",
    glassDk: "#15306a",
    bevel:   "#bfe6fb",
    gold:    "#e6c785",
    goldHi:  "#fff0c0",
    ruby:    "#d33a52",
    rubyDk:  "#7a1020",
    white:   "#eef4f8"
};
var P = PALETTE;

function lerp(a, b, t) { return a + (b - a) * t; }

function glassFill(ctx, x0, y0, x1, y1, base, hi, dk) {
    var g = ctx.createLinearGradient(x0, y0, x1, y1);
    g.addColorStop(0, hi); g.addColorStop(0.5, base); g.addColorStop(1, dk);
    return g;
}

function came(ctx, w) {
    ctx.lineJoin = "round"; ctx.lineCap = "round";
    ctx.strokeStyle = P.came; ctx.lineWidth = w; ctx.stroke();
}

function sheen(ctx, x, y, w, h) {
    var g = ctx.createLinearGradient(x, y, x, y + h * 0.6);
    g.addColorStop(0, "rgba(255,255,255,0.5)");
    g.addColorStop(1, "rgba(255,255,255,0)");
    ctx.fillStyle = g; ctx.fillRect(x, y, w, h);
}

// ---- ARROW (default / left_ptr) hotspot (0.16,0.06) ---------------------
function drawArrow(ctx, s, accent, glow, t) {
    var p = [[0.16,0.06],[0.16,0.78],[0.34,0.60],[0.46,0.86],[0.58,0.80],[0.46,0.54],[0.70,0.54]];
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(p[0][0]*s, p[0][1]*s);
    for (var i = 1; i < p.length; i++) ctx.lineTo(p[i][0]*s, p[i][1]*s);
    ctx.closePath();
    ctx.fillStyle = glassFill(ctx, 0.16*s, 0.06*s, 0.6*s, 0.86*s, P.glass, P.glassHi, P.glassDk);
    ctx.fill();
    came(ctx, s*0.07);
    ctx.save(); ctx.clip();
    ctx.strokeStyle = "rgba(191,230,251,0.8)"; ctx.lineWidth = s*0.03;
    ctx.beginPath(); ctx.moveTo(0.20*s,0.12*s); ctx.lineTo(0.20*s,0.62*s); ctx.stroke();
    sheen(ctx, 0.10*s, 0.04*s, 0.4*s, 0.5*s);
    ctx.restore();
    ctx.beginPath(); ctx.arc(0.26*s, 0.20*s, s*0.035, 0, Math.PI*2);
    ctx.fillStyle = P.goldHi; ctx.fill();
    ctx.restore();
}

// ---- POINTER / HAND (link) hotspot (0.40,0.06) --------------------------
function drawPointer(ctx, s, accent, glow, t) {
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(0.36*s,0.06*s);
    ctx.lineTo(0.36*s,0.46*s); ctx.lineTo(0.30*s,0.40*s); ctx.lineTo(0.22*s,0.48*s);
    ctx.bezierCurveTo(0.20*s,0.54*s,0.24*s,0.62*s,0.30*s,0.72*s);
    ctx.lineTo(0.34*s,0.90*s); ctx.lineTo(0.72*s,0.90*s); ctx.lineTo(0.78*s,0.56*s);
    ctx.lineTo(0.74*s,0.40*s); ctx.lineTo(0.68*s,0.44*s); ctx.lineTo(0.66*s,0.40*s);
    ctx.lineTo(0.60*s,0.44*s); ctx.lineTo(0.58*s,0.40*s); ctx.lineTo(0.52*s,0.44*s);
    ctx.lineTo(0.50*s,0.30*s); ctx.lineTo(0.44*s,0.30*s); ctx.lineTo(0.44*s,0.06*s);
    ctx.closePath();
    ctx.fillStyle = glassFill(ctx, 0.2*s, 0.06*s, 0.8*s, 0.9*s, P.glass, P.glassHi, P.glassDk);
    ctx.fill();
    came(ctx, s*0.065);
    ctx.save(); ctx.clip(); sheen(ctx, 0.2*s, 0.04*s, 0.6*s, 0.5*s); ctx.restore();
    ctx.strokeStyle = "rgba(11,11,20,0.55)"; ctx.lineWidth = s*0.025;
    var seams = [0.52, 0.60, 0.68];
    for (var i = 0; i < seams.length; i++) {
        ctx.beginPath(); ctx.moveTo(seams[i]*s, 0.5*s); ctx.lineTo(seams[i]*s, 0.78*s); ctx.stroke();
    }
    ctx.beginPath(); ctx.arc(0.40*s, 0.12*s, s*0.03, 0, Math.PI*2); ctx.fillStyle = P.goldHi; ctx.fill();
    ctx.restore();
}

// ---- TEXT / I-BEAM (xterm) hotspot (0.5,0.5) ----------------------------
function drawText(ctx, s, accent, glow, t) {
    ctx.save();
    ctx.beginPath();
    ctx.rect(0.44*s,0.12*s,0.12*s,0.76*s);
    ctx.rect(0.32*s,0.12*s,0.36*s,0.10*s);
    ctx.rect(0.32*s,0.78*s,0.36*s,0.10*s);
    ctx.fillStyle = glassFill(ctx, 0.3*s, 0.1*s, 0.7*s, 0.9*s, P.glass, P.glassHi, P.glassDk);
    ctx.fill();
    came(ctx, s*0.05);
    ctx.beginPath(); ctx.arc(0.5*s,0.22*s,s*0.03,0,Math.PI*2); ctx.fillStyle = P.goldHi; ctx.fill();
    ctx.restore();
}

// ---- WAIT / BUSY (watch) — rotating rose window. t:0..1 -----------------
function drawWait(ctx, s, accent, glow, t) {
    t = t || 0;
    var cx = 0.5*s, cy = 0.5*s, R = 0.42*s;
    ctx.save();
    ctx.beginPath(); ctx.arc(cx, cy, R, 0, Math.PI*2);
    ctx.fillStyle = P.came; ctx.fill();
    ctx.save();
    ctx.translate(cx, cy); ctx.rotate(t*Math.PI*2); ctx.translate(-cx, -cy);
    var segs = 12;
    for (var i = 0; i < segs; i++) {
        var a0 = (i/segs)*Math.PI*2 + 0.06, a1 = ((i+1)/segs)*Math.PI*2 - 0.06;
        ctx.beginPath();
        ctx.arc(cx, cy, R*0.94, a0, a1);
        ctx.arc(cx, cy, R*0.52, a1, a0, true);
        ctx.closePath();
        var phase = ((i/segs) + t) % 1;
        ctx.fillStyle = (i % 2 === 0) ? P.glass : P.white;
        ctx.globalAlpha = 0.4 + 0.6*Math.pow(phase, 1.5);
        ctx.fill();
        ctx.globalAlpha = 1;
    }
    ctx.restore();
    ctx.strokeStyle = P.came; ctx.lineWidth = s*0.05;
    ctx.beginPath(); ctx.arc(cx, cy, R*0.52, 0, Math.PI*2); ctx.stroke();
    ctx.lineWidth = s*0.035;
    ctx.beginPath(); ctx.arc(cx, cy, R*0.96, 0, Math.PI*2); ctx.stroke();
    ctx.beginPath(); ctx.arc(cx, cy, R*0.30, 0, Math.PI*2);
    var g = ctx.createRadialGradient(cx-R*0.1, cy-R*0.1, 1, cx, cy, R*0.3);
    g.addColorStop(0, P.goldHi); g.addColorStop(1, P.gold);
    ctx.fillStyle = g; ctx.fill();
    ctx.strokeStyle = P.came; ctx.lineWidth = s*0.03; ctx.stroke();
    ctx.restore();
}

// ---- HELP (arrow + ? jewel) hotspot (0.16,0.06) -------------------------
function drawHelp(ctx, s, accent, glow, t) {
    drawArrow(ctx, s*0.78, accent, glow, t);
    ctx.save();
    ctx.translate(s*0.52, s*0.52);
    ctx.beginPath(); ctx.arc(0, 0, s*0.26, 0, Math.PI*2);
    ctx.fillStyle = glassFill(ctx, -s*0.2, -s*0.2, s*0.2, s*0.2, P.ruby, "#f08098", P.rubyDk);
    ctx.fill(); ctx.strokeStyle = P.came; ctx.lineWidth = s*0.045; ctx.stroke();
    ctx.fillStyle = P.goldHi; ctx.font = "bold " + Math.round(s*0.34) + "px serif";
    ctx.textAlign = "center"; ctx.textBaseline = "middle"; ctx.fillText("?", 0, s*0.02);
    ctx.restore();
}

// ---- MOVE / FLEUR (4-way) hotspot (0.5,0.5) -----------------------------
function drawMove(ctx, s, accent, glow, t) {
    ctx.save(); ctx.translate(s*0.5, s*0.5);
    ctx.beginPath();
    var arm = 0.40*s, w = 0.10*s, head = 0.18*s;
    for (var k = 0; k < 4; k++) {
        ctx.save(); ctx.rotate(k*Math.PI/2);
        ctx.moveTo(-w,-w); ctx.lineTo(-w,-arm+head); ctx.lineTo(-head,-arm+head);
        ctx.lineTo(0,-arm); ctx.lineTo(head,-arm+head); ctx.lineTo(w,-arm+head); ctx.lineTo(w,-w);
        ctx.restore();
    }
    ctx.closePath();
    ctx.fillStyle = glassFill(ctx, -s*0.4, -s*0.4, s*0.4, s*0.4, P.glass, P.glassHi, P.glassDk);
    ctx.fill(); came(ctx, s*0.055);
    ctx.beginPath(); ctx.arc(0, 0, s*0.05, 0, Math.PI*2); ctx.fillStyle = P.goldHi; ctx.fill();
    ctx.restore();
}

function _dblArrow(ctx, s, ang) {
    ctx.save(); ctx.translate(s*0.5, s*0.5); ctx.rotate(ang);
    ctx.beginPath();
    var arm = 0.40*s, w = 0.085*s, head = 0.18*s;
    ctx.moveTo(-w,-w); ctx.lineTo(-w,-arm+head); ctx.lineTo(-head,-arm+head);
    ctx.lineTo(0,-arm); ctx.lineTo(head,-arm+head); ctx.lineTo(w,-arm+head); ctx.lineTo(w,-w);
    ctx.lineTo(w,w); ctx.lineTo(w,arm-head); ctx.lineTo(head,arm-head);
    ctx.lineTo(0,arm); ctx.lineTo(-head,arm-head); ctx.lineTo(-w,arm-head); ctx.lineTo(-w,w);
    ctx.closePath();
    ctx.fillStyle = glassFill(ctx, 0, -arm, 0, arm, P.glass, P.glassHi, P.glassDk);
    ctx.fill(); came(ctx, s*0.055);
    ctx.beginPath(); ctx.arc(0, 0, s*0.045, 0, Math.PI*2); ctx.fillStyle = P.goldHi; ctx.fill();
    ctx.restore();
}
function drawResizeV(ctx, s, a, g, t)  { _dblArrow(ctx, s, 0); }
function drawResizeH(ctx, s, a, g, t)  { _dblArrow(ctx, s, Math.PI/2); }
function drawResizeD1(ctx, s, a, g, t) { _dblArrow(ctx, s, -Math.PI/4); }
function drawResizeD2(ctx, s, a, g, t) { _dblArrow(ctx, s, Math.PI/4); }

// ---- CROSSHAIR hotspot (0.5,0.5) ----------------------------------------
function drawCrosshair(ctx, s, accent, glow, t) {
    ctx.save(); ctx.translate(s*0.5, s*0.5);
    ctx.beginPath();
    var L = 0.42*s, w = 0.05*s;
    ctx.rect(-w,-L,2*w,2*L); ctx.rect(-L,-w,2*L,2*w);
    ctx.fillStyle = glassFill(ctx, -L, -L, L, L, P.glass, P.glassHi, P.glassDk);
    ctx.fill(); came(ctx, s*0.04);
    ctx.beginPath(); ctx.arc(0, 0, s*0.05, 0, Math.PI*2);
    ctx.fillStyle = P.ruby; ctx.fill(); ctx.strokeStyle = P.came; ctx.lineWidth = s*0.02; ctx.stroke();
    ctx.restore();
}

// ---- NOT-ALLOWED (ruby) hotspot (0.5,0.5) -------------------------------
function drawNotAllowed(ctx, s, accent, glow, t) {
    ctx.save(); ctx.translate(s*0.5, s*0.5);
    ctx.beginPath(); ctx.arc(0, 0, s*0.40, 0, Math.PI*2);
    ctx.lineWidth = s*0.14; ctx.strokeStyle = P.came; ctx.stroke();
    ctx.beginPath(); ctx.arc(0, 0, s*0.40, 0, Math.PI*2);
    ctx.lineWidth = s*0.10;
    ctx.strokeStyle = glassFill(ctx, -s*0.4, -s*0.4, s*0.4, s*0.4, P.ruby, "#f08098", P.rubyDk);
    ctx.stroke();
    ctx.save(); ctx.rotate(-Math.PI/4);
    ctx.beginPath(); ctx.rect(-s*0.40, -s*0.07, s*0.80, s*0.14);
    ctx.fillStyle = P.came; ctx.fill();
    ctx.beginPath(); ctx.rect(-s*0.40, -s*0.05, s*0.80, s*0.10);
    ctx.fillStyle = glassFill(ctx, -s*0.4, 0, s*0.4, 0, P.ruby, "#f08098", P.rubyDk); ctx.fill();
    ctx.restore();
    ctx.restore();
}

// ---- GRAB / GRABBING hotspot (0.5,0.5) ----------------------------------
function _hand(ctx, s, closed) {
    ctx.save();
    var top = closed ? 0.42 : 0.30;
    ctx.beginPath();
    ctx.moveTo(0.24*s,0.62*s);
    ctx.lineTo(0.24*s,(top+0.08)*s);
    ctx.bezierCurveTo(0.24*s,top*s,0.34*s,top*s,0.34*s,(top+0.04)*s);
    ctx.lineTo(0.34*s,top*s);
    ctx.bezierCurveTo(0.34*s,(top-0.06)*s,0.46*s,(top-0.06)*s,0.46*s,top*s);
    ctx.bezierCurveTo(0.46*s,(top-0.08)*s,0.58*s,(top-0.08)*s,0.58*s,top*s);
    ctx.bezierCurveTo(0.58*s,(top-0.06)*s,0.70*s,(top-0.06)*s,0.70*s,(top+0.02)*s);
    ctx.lineTo(0.74*s,0.50*s);
    ctx.bezierCurveTo(0.78*s,0.66*s,0.70*s,0.86*s,0.54*s,0.88*s);
    ctx.lineTo(0.40*s,0.88*s);
    ctx.bezierCurveTo(0.30*s,0.86*s,0.24*s,0.74*s,0.24*s,0.62*s);
    ctx.closePath();
    ctx.fillStyle = glassFill(ctx, 0.2*s, top*s, 0.78*s, 0.9*s, P.glass, P.glassHi, P.glassDk);
    ctx.fill(); came(ctx, s*0.055);
    ctx.save(); ctx.clip(); sheen(ctx, 0.2*s, top*s, 0.6*s, 0.4*s); ctx.restore();
    ctx.strokeStyle = "rgba(11,11,20,0.5)"; ctx.lineWidth = s*0.022;
    var kn = [0.34, 0.46, 0.58];
    for (var i = 0; i < kn.length; i++) {
        ctx.beginPath(); ctx.moveTo(kn[i]*s,(top+0.02)*s); ctx.lineTo(kn[i]*s,(top+0.16)*s); ctx.stroke();
    }
    ctx.restore();
}
function drawGrab(ctx, s, a, g, t)     { _hand(ctx, s, false); }
function drawGrabbing(ctx, s, a, g, t) { _hand(ctx, s, true); }

// ---- METADATA (label, hotspot, X11 names, animation) --------------------
var CURSORS = {
    arrow:      { fn: drawArrow,      hot:[0.16,0.06], label:"Default",      xnames:["left_ptr","default","arrow","top_left_arrow"] },
    pointer:    { fn: drawPointer,    hot:[0.40,0.06], label:"Pointer/Link", xnames:["pointer","hand","hand1","hand2","pointing_hand"] },
    text:       { fn: drawText,       hot:[0.50,0.50], label:"Text",         xnames:["xterm","text","ibeam"] },
    wait:       { fn: drawWait,       hot:[0.50,0.50], label:"Busy/Wait",    animated:true, frames:12, delay:60, xnames:["watch","wait","progress"] },
    help:       { fn: drawHelp,       hot:[0.16,0.06], label:"Help",         xnames:["help","question_arrow","whats_this"] },
    move:       { fn: drawMove,       hot:[0.50,0.50], label:"Move",         xnames:["move","fleur","all-scroll","size_all"] },
    resizeV:    { fn: drawResizeV,    hot:[0.50,0.50], label:"Resize NS",    xnames:["sb_v_double_arrow","ns-resize","size_ver","v_double_arrow"] },
    resizeH:    { fn: drawResizeH,    hot:[0.50,0.50], label:"Resize EW",    xnames:["sb_h_double_arrow","ew-resize","size_hor","h_double_arrow"] },
    resizeD1:   { fn: drawResizeD1,   hot:[0.50,0.50], label:"Resize NESW",  xnames:["nesw-resize","size_bdiag","fd_double_arrow"] },
    resizeD2:   { fn: drawResizeD2,   hot:[0.50,0.50], label:"Resize NWSE",  xnames:["nwse-resize","size_fdiag","bd_double_arrow"] },
    crosshair:  { fn: drawCrosshair,  hot:[0.50,0.50], label:"Crosshair",    xnames:["crosshair","cross","tcross"] },
    notAllowed: { fn: drawNotAllowed, hot:[0.50,0.50], label:"Not Allowed",  xnames:["not-allowed","forbidden","no-drop","circle"] },
    grab:       { fn: drawGrab,       hot:[0.50,0.50], label:"Grab",         xnames:["grab","openhand"] },
    grabbing:   { fn: drawGrabbing,   hot:[0.50,0.50], label:"Grabbing",     xnames:["grabbing","closedhand","dnd-move"] }
};

// Route a Qt.*Cursor shape name (or X11 name) to a draw function.
function matchCursor(ctx, s, name, accent, glow, t) {
    var key = normalizeCursor(name);
    var c = CURSORS[key] || CURSORS.arrow;
    c.fn(ctx, s, accent, glow, t);
}

function normalizeCursor(name) {
    var n = String(name || "").toLowerCase();
    if (n.indexOf("point") !== -1 || n.indexOf("hand") !== -1 || n.indexOf("link") !== -1) return "pointer";
    if (n.indexOf("text") !== -1 || n.indexOf("ibeam") !== -1 || n.indexOf("xterm") !== -1) return "text";
    if (n.indexOf("wait") !== -1 || n.indexOf("busy") !== -1 || n.indexOf("watch") !== -1 || n.indexOf("progress") !== -1) return "wait";
    if (n.indexOf("help") !== -1 || n.indexOf("question") !== -1 || n.indexOf("whats") !== -1) return "help";
    if (n.indexOf("all") !== -1 || n.indexOf("fleur") !== -1 || n === "move" || n.indexOf("sizeall") !== -1) return "move";
    if (n.indexOf("nesw") !== -1 || n.indexOf("bdiag") !== -1) return "resizeD1";
    if (n.indexOf("nwse") !== -1 || n.indexOf("fdiag") !== -1) return "resizeD2";
    if (n.indexOf("ns") !== -1 || n.indexOf("ver") !== -1 || n.indexOf("sizev") !== -1 || (n.indexOf("v_") !== -1)) return "resizeV";
    if (n.indexOf("ew") !== -1 || n.indexOf("hor") !== -1 || n.indexOf("sizeh") !== -1 || (n.indexOf("h_") !== -1)) return "resizeH";
    if (n.indexOf("cross") !== -1) return "crosshair";
    if (n.indexOf("forbidden") !== -1 || n.indexOf("notallowed") !== -1 || n.indexOf("not-allowed") !== -1 || n.indexOf("nodrop") !== -1) return "notAllowed";
    if (n.indexOf("grabbing") !== -1 || n.indexOf("closed") !== -1 || n.indexOf("dndmove") !== -1) return "grabbing";
    if (n.indexOf("grab") !== -1 || n.indexOf("open") !== -1) return "grab";
    return "arrow";
}
