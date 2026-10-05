// mucha-icons-places.js — sidebar "Places" icons (Home, Documents, etc.).
.pragma library
.import "mucha-icons-core.js" as C

var _accentColor = null;
var _glowColor   = null;

function matchPlaceIcon(ctx, s, name, accentColor, glowColor) {
    _accentColor = accentColor || null;
    _glowColor   = glowColor   || null;
    var n = C.normalizeKey(name);

    if (C.hasAny(n, ["home", "user"]))                       return drawHome(ctx, s);
    if (C.hasAny(n, ["desktop"]))                            return drawDesktop(ctx, s);
    if (C.hasAny(n, ["documents", "docs"]))                  return drawDocuments(ctx, s);
    if (C.hasAny(n, ["downloads"]))                          return drawDownloads(ctx, s);
    if (C.hasAny(n, ["music"]))                              return drawMusic(ctx, s);
    if (C.hasAny(n, ["pictures", "photos", "images"]))       return drawPictures(ctx, s);
    if (C.hasAny(n, ["videos", "movies"]))                   return drawVideos(ctx, s);
    if (C.hasAny(n, ["trash", "rubbish", "recycle"]))        return drawTrash(ctx, s);
    if (C.hasAny(n, ["bookmark", "favorit", "starred"]))     return drawBookmark(ctx, s);
    if (C.hasAny(n, ["network", "shared", "smb", "nfs"]))    return drawNetwork(ctx, s);
    if (C.hasAny(n, ["templates"]))                          return drawTemplates(ctx, s);
    if (C.hasAny(n, ["public", "share"]))                    return drawPublic(ctx, s);
    if (C.hasAny(n, ["root", "system"]))                     return drawRoot(ctx, s);
    if (C.hasAny(n, ["search", "find"]))                     return drawSearch(ctx, s);
    if (C.hasAny(n, ["recent", "history"]))                  return drawRecent(ctx, s);

    drawFolder(ctx, s, name);
}

function _accent() { return _accentColor || C.PALETTE.gold; }
function _glow()   { return _glowColor   || C.PALETTE.glow; }

// HOME — gilt house with arched door
function drawHome(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:_accent(), glow:_glow()});
    var cx = s * 0.5;
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.moveTo(cx, s * 0.20);
    ctx.lineTo(s * 0.78, s * 0.48);
    ctx.lineTo(s * 0.78, s * 0.80);
    ctx.lineTo(s * 0.22, s * 0.80);
    ctx.lineTo(s * 0.22, s * 0.48);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // door
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.08, s * 0.80);
    ctx.lineTo(cx - s * 0.08, s * 0.62);
    ctx.arc(cx, s * 0.62, s * 0.08, Math.PI, 0);
    ctx.lineTo(cx + s * 0.08, s * 0.80);
    ctx.closePath();
    ctx.fill();
    // gable
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.46, s * 0.52, s * 0.08, s * 0.06);
}

// DESKTOP — monitor
function drawDesktop(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = "#3b3a30";
    C.roundRectPath(ctx, s * 0.14, s * 0.22, s * 0.72, s * 0.46, s * 0.03);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fillRect(s * 0.17, s * 0.25, s * 0.66, s * 0.40);
    ctx.fillStyle = "#3b3a30";
    ctx.fillRect(s * 0.40, s * 0.68, s * 0.20, s * 0.06);
    ctx.fillRect(s * 0.28, s * 0.74, s * 0.44, s * 0.04);
    // sun on screen
    ctx.beginPath();
    ctx.arc(s * 0.32, s * 0.38, s * 0.06, 0, Math.PI * 2);
    ctx.fillStyle = _accent();
    ctx.fill();
}

// DOCUMENTS — folder with sheet sticking out
function drawDocuments(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    // folder
    ctx.fillStyle = _accent();
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    ctx.beginPath();
    ctx.moveTo(s * 0.14, s * 0.30);
    ctx.lineTo(s * 0.36, s * 0.30);
    ctx.lineTo(s * 0.42, s * 0.22);
    ctx.lineTo(s * 0.66, s * 0.22);
    ctx.lineTo(s * 0.72, s * 0.30);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // peeking sheet
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.30, s * 0.36, s * 0.34, s * 0.32);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.strokeRect(s * 0.30, s * 0.36, s * 0.34, s * 0.32);
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * 0.32, s * (0.40 + i * 0.06), s * 0.30 - (i % 2) * s * 0.08, s * 0.014);
    }
}

// DOWNLOADS — down arrow into folder
function drawDownloads(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = C.PALETTE.tealDeep;
    C.roundRectPath(ctx, s * 0.14, s * 0.40, s * 0.72, s * 0.42, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // arrow
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.moveTo(s * 0.40, s * 0.18);
    ctx.lineTo(s * 0.60, s * 0.18);
    ctx.lineTo(s * 0.60, s * 0.40);
    ctx.lineTo(s * 0.70, s * 0.40);
    ctx.lineTo(s * 0.50, s * 0.58);
    ctx.lineTo(s * 0.30, s * 0.40);
    ctx.lineTo(s * 0.40, s * 0.40);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
}

// MUSIC — folder with quaver
function drawMusic(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = C.PALETTE.plumDeep;
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // note
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.ellipse(s * 0.40, s * 0.66, s * 0.07, s * 0.05, -0.3, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillRect(s * 0.46, s * 0.40, s * 0.022, s * 0.26);
    ctx.beginPath();
    ctx.moveTo(s * 0.48, s * 0.40);
    ctx.quadraticCurveTo(s * 0.62, s * 0.46, s * 0.58, s * 0.56);
    ctx.lineTo(s * 0.48, s * 0.50);
    ctx.closePath();
    ctx.fill();
}

// PICTURES — folder with framed image
function drawPictures(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = C.PALETTE.terraDark;
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // photo
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.26, s * 0.40, s * 0.48, s * 0.34);
    // sun + mountains
    ctx.beginPath();
    ctx.arc(s * 0.34, s * 0.48, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = _accent();
    ctx.fill();
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.26, s * 0.74);
    ctx.lineTo(s * 0.40, s * 0.58);
    ctx.lineTo(s * 0.50, s * 0.66);
    ctx.lineTo(s * 0.62, s * 0.52);
    ctx.lineTo(s * 0.74, s * 0.74);
    ctx.closePath();
    ctx.fill();
}

// VIDEOS — folder with play arrow
function drawVideos(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = C.PALETTE.indigoDeep;
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.moveTo(s * 0.40, s * 0.42);
    ctx.lineTo(s * 0.66, s * 0.55);
    ctx.lineTo(s * 0.40, s * 0.68);
    ctx.closePath();
    ctx.fill();
}

// TRASH — urn with lid
function drawTrash(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:_accent(), glow:_glow()});
    var cx = s * 0.5;
    // lid
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillRect(s * 0.20, s * 0.26, s * 0.60, s * 0.10);
    // handle
    ctx.fillRect(s * 0.42, s * 0.20, s * 0.16, s * 0.06);
    // body
    ctx.fillStyle = C.PALETTE.terra;
    ctx.beginPath();
    ctx.moveTo(s * 0.24, s * 0.36);
    ctx.lineTo(s * 0.76, s * 0.36);
    ctx.lineTo(s * 0.72, s * 0.82);
    ctx.lineTo(s * 0.28, s * 0.82);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // vertical strokes
    ctx.strokeStyle = "rgba(58,43,24,0.45)";
    ctx.lineWidth = s * 0.008;
    [0.40, 0.50, 0.60].forEach(function(x) {
        ctx.beginPath();
        ctx.moveTo(s * x, s * 0.40); ctx.lineTo(s * x, s * 0.78);
        ctx.stroke();
    });
}

// BOOKMARK — ribbon
function drawBookmark(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.moveTo(s * 0.32, s * 0.16);
    ctx.lineTo(s * 0.68, s * 0.16);
    ctx.lineTo(s * 0.68, s * 0.82);
    ctx.lineTo(s * 0.50, s * 0.68);
    ctx.lineTo(s * 0.32, s * 0.82);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // star
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.20) + "px serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("✦", s * 0.5, s * 0.40);
}

// NETWORK — globe nodes
function drawNetwork(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:_accent(), glow:_glow()});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fill();
    C.setStroke(ctx, _accent(), s * 0.014);
    ctx.stroke();
    // longitude bands
    ctx.strokeStyle = C.PALETTE.bgCreamHi;
    ctx.lineWidth = s * 0.010;
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.ellipse(cx, cy, s * 0.26 * Math.cos(i * 0.5), s * 0.26, 0, 0, Math.PI * 2);
        ctx.stroke();
    }
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.26, cy); ctx.lineTo(cx + s * 0.26, cy);
    ctx.stroke();
}

// TEMPLATES — folder with grid
function drawTemplates(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = C.PALETTE.sageDeep;
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // grid sheets
    var cols = [C.PALETTE.bgCreamHi, _accent(), C.PALETTE.terra];
    for (var i = 0; i < 3; i++) {
        ctx.fillStyle = cols[i];
        ctx.fillRect(s * (0.22 + i * 0.20), s * 0.42, s * 0.14, s * 0.30);
        C.setStroke(ctx, C.PALETTE.ink, s * 0.006);
        ctx.strokeRect(s * (0.22 + i * 0.20), s * 0.42, s * 0.14, s * 0.30);
    }
}

// PUBLIC — folder with people
function drawPublic(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = C.PALETTE.terra;
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // 3 people heads
    var col = C.PALETTE.bgCreamHi;
    [0.32, 0.50, 0.68].forEach(function(x) {
        ctx.fillStyle = col;
        ctx.beginPath();
        ctx.arc(s * x, s * 0.48, s * 0.05, 0, Math.PI * 2);
        ctx.fill();
        ctx.beginPath();
        ctx.moveTo(s * (x - 0.07), s * 0.74);
        ctx.bezierCurveTo(s * (x - 0.06), s * 0.58, s * (x + 0.06), s * 0.58, s * (x + 0.07), s * 0.74);
        ctx.closePath();
        ctx.fill();
    });
}

// ROOT — shield with gilt
function drawRoot(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"shield", accent:_accent(), glow:_glow(), ornament:false});
    ctx.fillStyle = _accent();
    ctx.font = "700 " + Math.round(s * 0.34) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("/", s * 0.5, s * 0.52);
}

// SEARCH — magnifier
function drawSearch(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"medallion", accent:_accent(), glow:_glow()});
    ctx.beginPath();
    ctx.arc(s * 0.42, s * 0.42, s * 0.20, 0, Math.PI * 2);
    ctx.fillStyle = "rgba(255,255,255,0.55)";
    ctx.fill();
    C.setStroke(ctx, _accent(), s * 0.022);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(s * 0.56, s * 0.56); ctx.lineTo(s * 0.80, s * 0.80);
    C.setStroke(ctx, _accent(), s * 0.030);
    ctx.stroke();
}

// RECENT — clock with arrow back
function drawRecent(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:_accent(), glow:_glow()});
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.26, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fill();
    C.setStroke(ctx, _accent(), s * 0.014);
    ctx.stroke();
    // hand
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.016;
    ctx.beginPath();
    ctx.moveTo(cx, cy); ctx.lineTo(cx + s * 0.14, cy - s * 0.10);
    ctx.moveTo(cx, cy); ctx.lineTo(cx, cy - s * 0.18);
    ctx.stroke();
    // arrow back curl
    ctx.strokeStyle = _accent();
    ctx.lineWidth = s * 0.018;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, -Math.PI * 0.8, -Math.PI * 0.2);
    ctx.stroke();
}

// FALLBACK — labelled folder
function drawFolder(ctx, s, name) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    ctx.fillStyle = _accent();
    C.roundRectPath(ctx, s * 0.14, s * 0.30, s * 0.72, s * 0.50, s * 0.04);
    ctx.fill();
    ctx.beginPath();
    ctx.moveTo(s * 0.14, s * 0.30);
    ctx.lineTo(s * 0.36, s * 0.30);
    ctx.lineTo(s * 0.42, s * 0.22);
    ctx.lineTo(s * 0.66, s * 0.22);
    ctx.lineTo(s * 0.72, s * 0.30);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    var initial = (name && String(name).replace(/[^A-Za-z]/g, '').charAt(0)) || '·';
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.22) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText(initial.toUpperCase(), s * 0.5, s * 0.58);
}
