// mucha-icons-tray.js — system tray icons (indexed by traySubType, 0..15).
.pragma library
.import "mucha-icons-core.js" as C

var _accentColor = null;
var _glowColor   = null;

function setTrayTheme(accent, glow) {
    _accentColor = accent || null;
    _glowColor   = glow   || null;
}

// All tray icons share a small medallion plinth: a circle with halo + rim.
function _plinth(ctx, s, fill) {
    ctx.save();
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.46, 0, Math.PI * 2);
    ctx.fillStyle = fill || "rgba(235,220,180,0.28)";
    ctx.fill();
    C.setStroke(ctx, _accentColor || C.PALETTE.border, Math.max(0.6, s * 0.016));
    ctx.stroke();
    ctx.restore();
}

// --- 0: AUDIO -------------------------------------------------------------
function drawTrayAudio(ctx, s, active) {
    _plinth(ctx, s);
    var cx = s * 0.5, cy = s * 0.5;
    // speaker
    ctx.fillStyle = _accentColor || C.PALETTE.ink;
    ctx.fillRect(cx - s * 0.20, cy - s * 0.06, s * 0.08, s * 0.12);
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.12, cy - s * 0.06);
    ctx.lineTo(cx + s * 0.02, cy - s * 0.18);
    ctx.lineTo(cx + s * 0.02, cy + s * 0.18);
    ctx.lineTo(cx - s * 0.12, cy + s * 0.06);
    ctx.closePath();
    ctx.fill();
    if (active) {
        ctx.strokeStyle = _glowColor || C.PALETTE.goldHi;
        ctx.lineWidth = s * 0.020;
        ctx.lineCap = "round";
        for (var i = 0; i < 3; i++) {
            ctx.beginPath();
            ctx.arc(cx + s * 0.06, cy, s * (0.08 + i * 0.06), -Math.PI * 0.3, Math.PI * 0.3);
            ctx.stroke();
        }
    } else {
        // muted "X"
        ctx.strokeStyle = C.PALETTE.terraDark;
        ctx.lineWidth = s * 0.026;
        ctx.lineCap = "round";
        ctx.beginPath();
        ctx.moveTo(cx + s * 0.10, cy - s * 0.10); ctx.lineTo(cx + s * 0.26, cy + s * 0.10);
        ctx.moveTo(cx + s * 0.26, cy - s * 0.10); ctx.lineTo(cx + s * 0.10, cy + s * 0.10);
        ctx.stroke();
    }
}

// --- 1: MIC ---------------------------------------------------------------
function drawTrayMic(ctx, s, active) {
    _plinth(ctx, s);
    var cx = s * 0.5, cy = s * 0.5;
    ctx.fillStyle = active ? _accentColor || C.PALETTE.terra : "#5d7861";
    C.roundRectPath(ctx, cx - s * 0.10, cy - s * 0.24, s * 0.20, s * 0.30, s * 0.10);
    ctx.fill();
    // arm
    ctx.beginPath();
    ctx.arc(cx, cy + s * 0.04, s * 0.16, 0, Math.PI);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(cx - s * 0.006, cy + s * 0.10, s * 0.012, s * 0.16);
    ctx.fillRect(cx - s * 0.12, cy + s * 0.26, s * 0.24, s * 0.02);
    if (!active) {
        // strike
        ctx.strokeStyle = C.PALETTE.terraDark;
        ctx.lineWidth = s * 0.026;
        ctx.beginPath();
        ctx.moveTo(s * 0.20, s * 0.20); ctx.lineTo(s * 0.80, s * 0.80);
        ctx.stroke();
    }
}

// --- 2: BATTERY -----------------------------------------------------------
function drawTrayBattery(ctx, s, percent, charging) {
    _plinth(ctx, s);
    var p = Math.max(0, Math.min(100, percent || 0));
    // case
    ctx.fillStyle = C.PALETTE.ink;
    C.roundRectPath(ctx, s * 0.18, s * 0.34, s * 0.56, s * 0.32, s * 0.04);
    ctx.fill();
    // terminal
    ctx.fillRect(s * 0.74, s * 0.42, s * 0.06, s * 0.16);
    // fill
    var fillW = s * 0.50 * (p / 100);
    var col = p < 20 ? C.PALETTE.terraDark : (p < 40 ? C.PALETTE.terra : (_accentColor || C.PALETTE.gold));
    ctx.fillStyle = col;
    C.roundRectPath(ctx, s * 0.21, s * 0.37, fillW, s * 0.26, s * 0.02);
    ctx.fill();
    if (charging) {
        ctx.fillStyle = _glowColor || C.PALETTE.goldHi;
        ctx.beginPath();
        ctx.moveTo(s * 0.50, s * 0.36);
        ctx.lineTo(s * 0.42, s * 0.50);
        ctx.lineTo(s * 0.50, s * 0.50);
        ctx.lineTo(s * 0.46, s * 0.64);
        ctx.lineTo(s * 0.56, s * 0.48);
        ctx.lineTo(s * 0.48, s * 0.48);
        ctx.lineTo(s * 0.54, s * 0.36);
        ctx.closePath();
        ctx.fill();
    }
}

// --- 3: WIFI --------------------------------------------------------------
function drawTrayWifi(ctx, s, bars) {
    _plinth(ctx, s);
    var cx = s * 0.5, cy = s * 0.66;
    var rs = [0.12, 0.20, 0.28];
    for (var i = 0; i < 3; i++) {
        var col = (i < (bars || 0)) ? _accentColor || C.PALETTE.gold : "rgba(58,43,24,0.25)";
        ctx.beginPath();
        ctx.arc(cx, cy, s * rs[i], -Math.PI * 0.75, -Math.PI * 0.25);
        C.setStroke(ctx, col, s * 0.026);
        ctx.stroke();
    }
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.022, 0, Math.PI * 2);
    ctx.fillStyle = _accentColor || C.PALETTE.gold;
    ctx.fill();
}

// --- 4: ETHERNET ---------------------------------------------------------
function drawTrayEthernet(ctx, s, active) {
    _plinth(ctx, s);
    // plug body
    ctx.fillStyle = active ? _accentColor || C.PALETTE.gold : C.PALETTE.ink;
    C.roundRectPath(ctx, s * 0.30, s * 0.20, s * 0.40, s * 0.36, s * 0.04);
    ctx.fill();
    // pins
    for (var i = 0; i < 4; i++) {
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.fillRect(s * (0.34 + i * 0.08), s * 0.26, s * 0.04, s * 0.10);
    }
    // cable
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(s * 0.46, s * 0.56, s * 0.08, s * 0.10);
    ctx.fillRect(s * 0.46, s * 0.66, s * 0.08, s * 0.18);
}

// --- 5: BLUETOOTH --------------------------------------------------------
function drawTrayBluetooth(ctx, s, active) {
    _plinth(ctx, s);
    var col = active ? _accentColor || C.PALETTE.tealDeep : "rgba(58,43,24,0.4)";
    ctx.save();
    ctx.translate(s * 0.5, s * 0.5);
    ctx.strokeStyle = col;
    ctx.lineWidth = s * 0.030;
    ctx.lineCap = "round";
    ctx.lineJoin = "round";
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.28);
    ctx.lineTo(s * 0.12, -s * 0.14);
    ctx.lineTo(-s * 0.12, s * 0.10);
    ctx.lineTo(0, s * 0.24);
    ctx.lineTo(0, -s * 0.04);
    ctx.lineTo(s * 0.12, s * 0.10);
    ctx.lineTo(-s * 0.12, -s * 0.14);
    ctx.lineTo(0, -s * 0.04);
    ctx.stroke();
    ctx.restore();
}

// --- 6: NOTIFICATIONS ----------------------------------------------------
function drawTrayNotifications(ctx, s, badge) {
    _plinth(ctx, s);
    var cx = s * 0.5;
    // bell
    ctx.fillStyle = _accentColor || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.20, s * 0.62);
    ctx.lineTo(cx - s * 0.14, s * 0.34);
    ctx.bezierCurveTo(cx - s * 0.14, s * 0.22, cx + s * 0.14, s * 0.22, cx + s * 0.14, s * 0.34);
    ctx.lineTo(cx + s * 0.20, s * 0.62);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // clapper
    ctx.beginPath();
    ctx.arc(cx, s * 0.72, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    // top knob
    ctx.beginPath();
    ctx.arc(cx, s * 0.20, s * 0.030, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fill();
    if (badge && badge > 0) {
        ctx.beginPath();
        ctx.arc(s * 0.74, s * 0.30, s * 0.10, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.terraDark;
        ctx.fill();
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.font = "700 " + Math.round(s * 0.10) + "px sans-serif";
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(badge > 9 ? "9+" : "" + badge, s * 0.74, s * 0.30);
    }
}

// --- 7: CLIPBOARD --------------------------------------------------------
function drawTrayClipboard(ctx, s) {
    _plinth(ctx, s);
    // board
    ctx.fillStyle = "#7a4a26";
    C.roundRectPath(ctx, s * 0.22, s * 0.20, s * 0.56, s * 0.66, s * 0.03);
    ctx.fill();
    // paper
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.26, s * 0.30, s * 0.48, s * 0.50);
    // clip
    ctx.fillStyle = _accentColor || C.PALETTE.gold;
    C.roundRectPath(ctx, s * 0.36, s * 0.14, s * 0.28, s * 0.12, s * 0.02);
    ctx.fill();
    // lines
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * 0.30, s * (0.38 + i * 0.10), s * 0.36 - (i % 2) * s * 0.10, s * 0.014);
    }
}

// --- 8: BRIGHTNESS -------------------------------------------------------
function drawTrayBrightness(ctx, s, percent) {
    _plinth(ctx, s);
    var cx = s * 0.5, cy = s * 0.5;
    // sun center
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = _accentColor || C.PALETTE.goldHi;
    ctx.fill();
    // rays — count proportional to brightness
    var nrays = 8;
    var lit = Math.round((percent || 100) / 100 * nrays);
    ctx.save();
    ctx.translate(cx, cy);
    for (var i = 0; i < nrays; i++) {
        ctx.save();
        ctx.rotate(i / nrays * Math.PI * 2);
        ctx.fillStyle = i < lit ? _accentColor || C.PALETTE.gold : "rgba(58,43,24,0.3)";
        ctx.fillRect(s * 0.16, -s * 0.014, s * 0.10, s * 0.028);
        ctx.restore();
    }
    ctx.restore();
}

// --- 9: KEYBOARD ---------------------------------------------------------
function drawTrayKeyboard(ctx, s) {
    _plinth(ctx, s);
    ctx.fillStyle = C.PALETTE.ink;
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.40, s * 0.04);
    ctx.fill();
    // keys
    ctx.fillStyle = _accentColor || C.PALETTE.goldHi;
    for (var r = 0; r < 2; r++) {
        for (var c = 0; c < 5; c++) {
            ctx.fillRect(s * (0.20 + c * 0.12), s * (0.36 + r * 0.10), s * 0.08, s * 0.06);
        }
    }
    // spacebar
    ctx.fillRect(s * 0.24, s * 0.58, s * 0.52, s * 0.05);
}

// --- 10: POWER ------------------------------------------------------------
function drawTrayPower(ctx, s) {
    _plinth(ctx, s);
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy + s * 0.04, s * 0.20, Math.PI * 0.25, Math.PI * 0.75, true);
    C.setStroke(ctx, _accentColor || C.PALETTE.gold, s * 0.034);
    ctx.stroke();
    ctx.fillStyle = _accentColor || C.PALETTE.gold;
    ctx.fillRect(cx - s * 0.020, cy - s * 0.22, s * 0.040, s * 0.22);
}

// --- 11: UPDATES ----------------------------------------------------------
function drawTrayUpdates(ctx, s, badge) {
    _plinth(ctx, s);
    var cx = s * 0.5, cy = s * 0.5;
    // circular arrow
    ctx.strokeStyle = _accentColor || C.PALETTE.gold;
    ctx.lineWidth = s * 0.030;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.20, -Math.PI * 0.85, Math.PI * 0.65);
    ctx.stroke();
    // arrow head
    var ax = cx + Math.cos(Math.PI * 0.65) * s * 0.20;
    var ay = cy + Math.sin(Math.PI * 0.65) * s * 0.20;
    ctx.fillStyle = _accentColor || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(ax, ay);
    ctx.lineTo(ax - s * 0.04, ay - s * 0.08);
    ctx.lineTo(ax + s * 0.08, ay - s * 0.04);
    ctx.closePath();
    ctx.fill();
    if (badge && badge > 0) {
        ctx.beginPath();
        ctx.arc(s * 0.74, s * 0.30, s * 0.10, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.terraDark;
        ctx.fill();
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.font = "700 " + Math.round(s * 0.10) + "px sans-serif";
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(badge > 9 ? "9+" : "" + badge, s * 0.74, s * 0.30);
    }
}

// --- 12: CALENDAR ---------------------------------------------------------
function drawTrayCalendar(ctx, s) {
    _plinth(ctx, s);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    C.roundRectPath(ctx, s * 0.18, s * 0.22, s * 0.64, s * 0.60, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // header
    ctx.fillStyle = _accentColor || C.PALETTE.terraDark;
    ctx.fillRect(s * 0.18, s * 0.22, s * 0.64, s * 0.14);
    // rings
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(s * 0.28, s * 0.16, s * 0.04, s * 0.14);
    ctx.fillRect(s * 0.68, s * 0.16, s * 0.04, s * 0.14);
    // date
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.22) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("12", s * 0.50, s * 0.58);
}

// --- 13: MAIL -------------------------------------------------------------
function drawTrayMail(ctx, s, badge) {
    _plinth(ctx, s);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.16, s * 0.30, s * 0.68, s * 0.40);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.16, s * 0.30, s * 0.68, s * 0.40);
    ctx.beginPath();
    ctx.moveTo(s * 0.16, s * 0.30); ctx.lineTo(s * 0.50, s * 0.56); ctx.lineTo(s * 0.84, s * 0.30);
    ctx.stroke();
    if (badge && badge > 0) {
        ctx.beginPath();
        ctx.arc(s * 0.74, s * 0.30, s * 0.10, 0, Math.PI * 2);
        ctx.fillStyle = C.PALETTE.terraDark;
        ctx.fill();
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.font = "700 " + Math.round(s * 0.10) + "px sans-serif";
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(badge > 9 ? "9+" : "" + badge, s * 0.74, s * 0.30);
    }
    ctx.fillStyle = _accentColor || C.PALETTE.gold;
    ctx.fillRect(s * 0.16, s * 0.68, s * 0.68, s * 0.024);
}

// --- 14: VPN --------------------------------------------------------------
function drawTrayVPN(ctx, s, active) {
    _plinth(ctx, s);
    var col = active ? _accentColor || C.PALETTE.sageDeep : "rgba(58,43,24,0.4)";
    ctx.fillStyle = col;
    ctx.beginPath();
    ctx.moveTo(s * 0.30, s * 0.22);
    ctx.lineTo(s * 0.70, s * 0.22);
    ctx.lineTo(s * 0.70, s * 0.54);
    ctx.bezierCurveTo(s * 0.70, s * 0.74, s * 0.30, s * 0.74, s * 0.30, s * 0.54);
    ctx.closePath();
    ctx.fill();
    // key
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.44, s * 0.06, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillRect(s * 0.484, s * 0.44, s * 0.030, s * 0.16);
}

// --- 15: NIGHT LIGHT ------------------------------------------------------
function drawTrayNightLight(ctx, s, active) {
    _plinth(ctx, s);
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx + s * 0.02, cy - s * 0.04, s * 0.22, 0, Math.PI * 2);
    ctx.fillStyle = active ? _accentColor || C.PALETTE.goldHi : "rgba(58,43,24,0.35)";
    ctx.fill();
    ctx.beginPath();
    ctx.arc(cx + s * 0.10, cy - s * 0.10, s * 0.22, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCream;
    ctx.fill();
    // stars
    if (active) {
        ctx.fillStyle = _glowColor || C.PALETTE.goldHi;
        ctx.font = "700 " + Math.round(s * 0.08) + "px serif";
        ctx.fillText("✦", s * 0.22, s * 0.72);
        ctx.fillText("·", s * 0.30, s * 0.62);
    }
}

// --- DEFAULT --------------------------------------------------------------
function drawTrayDefault(ctx, s) {
    _plinth(ctx, s);
    ctx.fillStyle = _accentColor || C.PALETTE.gold;
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.5, s * 0.10, 0, Math.PI * 2);
    ctx.fill();
}
