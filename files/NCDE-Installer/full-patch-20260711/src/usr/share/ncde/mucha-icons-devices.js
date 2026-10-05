// mucha-icons-devices.js — drives, removable media, hardware devices.
.pragma library
.import "mucha-icons-core.js" as C

var _accentColor = null;
var _glowColor   = null;

function matchDeviceIcon(ctx, s, name, accentColor, glowColor) {
    _accentColor = accentColor || null;
    _glowColor   = glowColor   || null;
    var n = C.normalizeKey(name);

    if (C.hasAny(n, ["nvme", "ssd"]))                              return drawSSD(ctx, s);
    if (C.hasAny(n, ["harddisk", "hdd", "drive", "disk"]))         return drawHDD(ctx, s);
    if (C.hasAny(n, ["usb", "thumbdrive", "pendrive", "flash"]))   return drawUSB(ctx, s);
    if (C.hasAny(n, ["sdcard", "sd"]))                             return drawSDCard(ctx, s);
    if (C.hasAny(n, ["dvd", "cdrom", "bluray", "optical"]))        return drawDisc(ctx, s);
    if (C.hasAny(n, ["printer"]))                                  return drawPrinter(ctx, s);
    if (C.hasAny(n, ["scanner"]))                                  return drawScanner(ctx, s);
    if (C.hasAny(n, ["camera", "webcam"]))                         return drawCamera(ctx, s);
    if (C.hasAny(n, ["phone", "mobile", "android"]))               return drawPhone(ctx, s);
    if (C.hasAny(n, ["tablet", "ipad"]))                           return drawTablet(ctx, s);
    if (C.hasAny(n, ["display", "monitor", "screen"]))             return drawDisplay(ctx, s);
    if (C.hasAny(n, ["keyboard"]))                                 return drawKeyboard(ctx, s);
    if (C.hasAny(n, ["mouse"]))                                    return drawMouse(ctx, s);
    if (C.hasAny(n, ["audio", "headphone", "headset"]))            return drawHeadphones(ctx, s);
    if (C.hasAny(n, ["controller", "gamepad", "joystick"]))        return drawGamepad(ctx, s);

    drawGenericDevice(ctx, s, name);
}

function _accent() { return _accentColor || C.PALETTE.gold; }
function _glow()   { return _glowColor   || C.PALETTE.glow; }

// HDD — drive platter exposed
function drawHDD(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#9b9bb0";
    C.roundRectPath(ctx, s * 0.14, s * 0.22, s * 0.72, s * 0.56, s * 0.03);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // platter
    ctx.beginPath();
    ctx.arc(s * 0.42, s * 0.50, s * 0.22, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(s * 0.42, s * 0.50, s * 0.05, 0, Math.PI * 2);
    ctx.fillStyle = _accent();
    ctx.fill();
    // arm
    ctx.save();
    ctx.translate(s * 0.42, s * 0.50);
    ctx.rotate(-0.4);
    ctx.fillStyle = "#5c5c70";
    ctx.fillRect(-s * 0.024, 0, s * 0.048, s * 0.22);
    ctx.beginPath();
    ctx.moveTo(-s * 0.04, 0); ctx.lineTo(s * 0.04, 0); ctx.lineTo(0, -s * 0.06);
    ctx.closePath(); ctx.fill();
    ctx.restore();
    // screws
    [[0.18,0.26],[0.82,0.26],[0.18,0.74],[0.82,0.74]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.016, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.ink;
        ctx.fill();
    });
}

// SSD — smooth flat brick
function drawSSD(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.40, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, _accent(), s * 0.012);
    ctx.stroke();
    // gold pad
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.14, s * 0.46, s * 0.10, s * 0.10);
    // text
    ctx.fillStyle = "rgba(230,199,133,0.7)";
    ctx.font = "700 " + Math.round(s * 0.07) + "px monospace";
    ctx.textBaseline = "middle";
    ctx.fillText("SSD", s * 0.30, s * 0.42);
    ctx.fillText("1TB", s * 0.30, s * 0.58);
    // led
    ctx.beginPath();
    ctx.arc(s * 0.76, s * 0.40, s * 0.018, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.sageMist;
    ctx.fill();
}

// USB — usb stick
function drawUSB(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    // body
    ctx.fillStyle = C.PALETTE.indigoDeep;
    C.roundRectPath(ctx, s * 0.30, s * 0.16, s * 0.40, s * 0.50, s * 0.03);
    ctx.fill();
    // tip
    ctx.fillStyle = "#9b9bb0";
    ctx.fillRect(s * 0.36, s * 0.66, s * 0.28, s * 0.18);
    // contacts
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.40, s * 0.74, s * 0.20, s * 0.06);
    // cap detail
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.34, s * 0.24, s * 0.32, s * 0.06);
    // logo
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.12) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("USB", s * 0.5, s * 0.44);
}

// SD CARD — corner-clipped card with contact strip
function drawSDCard(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.20);
    ctx.lineTo(s * 0.62, s * 0.20);
    ctx.lineTo(s * 0.78, s * 0.36);
    ctx.lineTo(s * 0.78, s * 0.80);
    ctx.lineTo(s * 0.20, s * 0.80);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // contact lines
    ctx.fillStyle = _accent();
    for (var i = 0; i < 6; i++) {
        ctx.fillRect(s * 0.26, s * (0.34 + i * 0.05), s * 0.06, s * 0.030);
    }
    // SD letter
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.14) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("SD", s * 0.56, s * 0.62);
}

// OPTICAL DISC
function drawDisc(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:_accent(), glow:_glow()});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.32, 0, Math.PI * 2);
    ctx.fillStyle = C.radial(ctx, cx - s * 0.08, cy - s * 0.10, s * 0.02, s * 0.32,
        [[0, "#e6e6ec"], [0.5, "#a9b1c5"], [1, "#5d6477"]]);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // rainbow sheen (3 arcs)
    [C.PALETTE.rose, _accent(), C.PALETTE.sageDeep].forEach(function(col, i) {
        ctx.beginPath();
        ctx.arc(cx, cy, s * (0.18 + i * 0.05), Math.PI * 0.2, Math.PI * 0.6);
        C.setStroke(ctx, col, s * 0.012);
        ctx.stroke();
    });
    // hub
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.07, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
}

// PRINTER — top tray + body + output
function drawPrinter(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    // top paper feed
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.26, s * 0.18, s * 0.48, s * 0.18);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.26, s * 0.18, s * 0.48, s * 0.18);
    // body
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.14, s * 0.36, s * 0.72, s * 0.32, s * 0.03);
    ctx.fill();
    // led
    ctx.beginPath();
    ctx.arc(s * 0.76, s * 0.46, s * 0.018, 0, Math.PI * 2);
    ctx.fillStyle = _accent();
    ctx.fill();
    // output paper
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.30, s * 0.62, s * 0.40, s * 0.20);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.30, s * 0.62, s * 0.40, s * 0.20);
    // text lines on paper
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 3; i++) {
        ctx.fillRect(s * 0.34, s * (0.68 + i * 0.06), s * 0.32 - (i % 2) * s * 0.06, s * 0.010);
    }
}

// SCANNER — flat lid with bar
function drawScanner(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.46, s * 0.03);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.18, s * 0.34, s * 0.64, s * 0.30);
    // scan bar
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.18, s * 0.44, s * 0.64, s * 0.04);
    // light beam
    ctx.fillStyle = "rgba(230,199,133,0.5)";
    ctx.fillRect(s * 0.18, s * 0.44, s * 0.64, s * 0.20);
}

// CAMERA — DSLR-ish
function drawCamera(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    // body
    ctx.fillStyle = "#23211a";
    C.roundRectPath(ctx, s * 0.14, s * 0.32, s * 0.72, s * 0.48, s * 0.04);
    ctx.fill();
    // viewfinder hump
    ctx.fillRect(s * 0.38, s * 0.22, s * 0.24, s * 0.12);
    // lens
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.56, s * 0.18, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    C.setStroke(ctx, _accent(), s * 0.014);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.56, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = "#1d2840";
    ctx.fill();
    // flash
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.18, s * 0.36, s * 0.08, s * 0.06);
}

// PHONE — smartphone outline
function drawPhone(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#1d1a14";
    C.roundRectPath(ctx, s * 0.30, s * 0.14, s * 0.40, s * 0.72, s * 0.06);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fillRect(s * 0.34, s * 0.22, s * 0.32, s * 0.52);
    // speaker
    ctx.fillStyle = "#3b3a30";
    ctx.fillRect(s * 0.44, s * 0.18, s * 0.12, s * 0.020);
    // home dot
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.80, s * 0.018, 0, Math.PI * 2);
    ctx.fillStyle = _accent();
    ctx.fill();
    // app squares
    ctx.fillStyle = _accent();
    for (var r = 0; r < 3; r++) {
        for (var c = 0; c < 3; c++) {
            ctx.fillRect(s * (0.36 + c * 0.10), s * (0.26 + r * 0.14), s * 0.08, s * 0.08);
        }
    }
}

// TABLET — landscape device
function drawTablet(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#1d1a14";
    C.roundRectPath(ctx, s * 0.14, s * 0.22, s * 0.72, s * 0.56, s * 0.05);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.18, s * 0.28, s * 0.64, s * 0.44);
    // grid
    ctx.fillStyle = _accent();
    for (var r = 0; r < 2; r++) {
        for (var c = 0; c < 4; c++) {
            ctx.fillRect(s * (0.22 + c * 0.14), s * (0.32 + r * 0.18), s * 0.10, s * 0.10);
        }
    }
}

// DISPLAY
function drawDisplay(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.12, s * 0.20, s * 0.76, s * 0.46, s * 0.03);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fillRect(s * 0.16, s * 0.24, s * 0.68, s * 0.38);
    // stand
    ctx.fillStyle = "#3b3a30";
    ctx.fillRect(s * 0.42, s * 0.66, s * 0.16, s * 0.10);
    ctx.fillRect(s * 0.30, s * 0.76, s * 0.40, s * 0.04);
    // glint
    ctx.fillStyle = "rgba(230,199,133,0.4)";
    ctx.beginPath();
    ctx.moveTo(s * 0.18, s * 0.32);
    ctx.lineTo(s * 0.28, s * 0.24);
    ctx.lineTo(s * 0.30, s * 0.24);
    ctx.lineTo(s * 0.20, s * 0.32);
    ctx.closePath();
    ctx.fill();
}

// KEYBOARD
function drawKeyboard(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.10, s * 0.30, s * 0.80, s * 0.40, s * 0.04);
    ctx.fill();
    ctx.fillStyle = _accent();
    for (var r = 0; r < 3; r++) {
        for (var c = 0; c < 8; c++) {
            ctx.fillRect(s * (0.13 + c * 0.094), s * (0.36 + r * 0.09), s * 0.07, s * 0.06);
        }
    }
    // space
    ctx.fillRect(s * 0.30, s * 0.62, s * 0.40, s * 0.05);
}

// MOUSE
function drawMouse(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:_accent(), glow:_glow()});
    var cx = s * 0.5;
    ctx.fillStyle = "#3b3a30";
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.16, s * 0.30);
    ctx.bezierCurveTo(cx - s * 0.16, s * 0.20, cx + s * 0.16, s * 0.20, cx + s * 0.16, s * 0.30);
    ctx.lineTo(cx + s * 0.16, s * 0.74);
    ctx.bezierCurveTo(cx + s * 0.16, s * 0.82, cx - s * 0.16, s * 0.82, cx - s * 0.16, s * 0.74);
    ctx.closePath();
    ctx.fill();
    // split top
    ctx.strokeStyle = "rgba(230,199,133,0.4)";
    ctx.lineWidth = s * 0.008;
    ctx.beginPath();
    ctx.moveTo(cx, s * 0.22); ctx.lineTo(cx, s * 0.40);
    ctx.stroke();
    // wheel
    ctx.fillStyle = _accent();
    ctx.fillRect(cx - s * 0.014, s * 0.30, s * 0.028, s * 0.06);
}

// HEADPHONES
function drawHeadphones(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:_accent(), glow:_glow()});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, Math.PI, 0);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.030);
    ctx.stroke();
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, cx - s * 0.32, cy - s * 0.04, s * 0.10, s * 0.20, s * 0.02);
    ctx.fill();
    C.roundRectPath(ctx, cx + s * 0.22, cy - s * 0.04, s * 0.10, s * 0.20, s * 0.02);
    ctx.fill();
    // gold cushion
    ctx.fillStyle = _accent();
    ctx.fillRect(cx - s * 0.30, cy + s * 0.04, s * 0.06, s * 0.10);
    ctx.fillRect(cx + s * 0.24, cy + s * 0.04, s * 0.06, s * 0.10);
}

// GAMEPAD
function drawGamepad(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = C.PALETTE.indigoDeep;
    C.roundRectPath(ctx, s * 0.12, s * 0.34, s * 0.76, s * 0.32, s * 0.16);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // d-pad
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.22, s * 0.46, s * 0.10, s * 0.04);
    ctx.fillRect(s * 0.25, s * 0.43, s * 0.04, s * 0.10);
    // buttons
    [[0.70,0.42, C.PALETTE.terraDark],[0.76,0.50, _accent()],[0.70,0.58, C.PALETTE.sageDeep],[0.64,0.50, C.PALETTE.tealDeep]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.022, 0, Math.PI * 2);
        ctx.fillStyle = p[2];
        ctx.fill();
    });
    // sticks
    [[0.40,0.58],[0.58,0.58]].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(s * p[0], s * p[1], s * 0.024, 0, Math.PI * 2);
        ctx.fillStyle = "#1d1a14";
        ctx.fill();
        C.setStroke(ctx, _accent(), s * 0.006);
        ctx.stroke();
    });
}

// GENERIC DEVICE — beige box with initial
function drawGenericDevice(ctx, s, name) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.18, s * 0.22, s * 0.64, s * 0.56, s * 0.04);
    ctx.fill();
    ctx.fillStyle = _accent();
    var initial = (name && String(name).replace(/[^A-Za-z]/g, '').charAt(0)) || '?';
    ctx.font = "700 " + Math.round(s * 0.24) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText(initial.toUpperCase(), s * 0.5, s * 0.50);
    // led
    ctx.beginPath();
    ctx.arc(s * 0.72, s * 0.30, s * 0.018, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.sageMist;
    ctx.fill();
}
