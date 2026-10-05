// mucha-icons-mimetypes.js — file type icons, matched by MIME + extension.
.pragma library
.import "mucha-icons-core.js" as C

var _accentColor = null;
var _glowColor   = null;

function matchMimeIcon(ctx, s, mimeType, extension, accentColor, glowColor) {
    _accentColor = accentColor || null;
    _glowColor   = glowColor   || null;

    var m = " " + String(mimeType || "").toLowerCase() + " ";
    var e = " " + String(extension || "").toLowerCase() + " ";
    var n = m + e;

    if (C.hasAny(n, ["image", "png", "jpg", "jpeg", "gif", "webp", "svg", "bmp", "tiff", "heic"]))
        return drawMimeImage(ctx, s, extension);
    if (C.hasAny(n, ["audio", "sound", "mp3", "wav", "ogg", "flac", "opus", "m4a", "aac"]))
        return drawMimeAudio(ctx, s, extension);
    if (C.hasAny(n, ["video", "mp4", "mkv", "webm", "avi", "mov", "wmv"]))
        return drawMimeVideo(ctx, s, extension);
    if (C.hasAny(n, ["pdf"]))                                  return drawMimePDF(ctx, s);
    if (C.hasAny(n, ["epub", "mobi", "azw", "kfx"]))           return drawMimeBook(ctx, s);
    if (C.hasAny(n, ["text", "plain", "txt", "md", "markdown", "rst"])) return drawMimeText(ctx, s, extension);
    if (C.hasAny(n, ["html", "xml", "json", "yaml", "toml", "ini", "css", "scss"])) return drawMimeMarkup(ctx, s, extension);
    if (C.hasAny(n, ["script", "shell", "sh", "bash", "zsh", "fish", "py", "rb", "pl", "js", "ts", "go", "rs", "java", "kt", "c", "cpp", "h", "hpp", "lua", "swift", "php"])) return drawMimeCode(ctx, s, extension);
    if (C.hasAny(n, ["zip", "tar", "gz", "bz2", "xz", "7z", "rar", "archive"])) return drawMimeArchive(ctx, s, extension);
    if (C.hasAny(n, ["msword", "doc", "docx", "odt", "rtf"]))  return drawMimeDoc(ctx, s, extension);
    if (C.hasAny(n, ["spreadsheet", "xls", "xlsx", "ods", "csv"])) return drawMimeSheet(ctx, s, extension);
    if (C.hasAny(n, ["presentation", "ppt", "pptx", "odp"]))   return drawMimeSlides(ctx, s, extension);
    if (C.hasAny(n, ["font", "ttf", "otf", "woff"]))           return drawMimeFont(ctx, s);
    if (C.hasAny(n, ["executable", "binary", "exe", "appimage", "elf"])) return drawMimeExecutable(ctx, s);
    if (C.hasAny(n, ["iso", "img", "disk"]))                   return drawMimeISO(ctx, s);
    if (C.hasAny(n, ["torrent"]))                              return drawMimeTorrent(ctx, s);
    if (C.hasAny(n, ["deb", "rpm", "pkg", "apk", "flatpak", "snap"])) return drawMimePackage(ctx, s, extension);
    if (C.hasAny(n, ["3d", "obj", "stl", "fbx", "blend", "gltf", "glb"])) return drawMime3D(ctx, s, extension);

    drawMimeGeneric(ctx, s, extension);
}

function _accent() { return _accentColor || C.PALETTE.gold; }
function _glow()   { return _glowColor   || C.PALETTE.glow; }

// Common page chassis: aged paper with folded corner, colored tag area below.
function _page(ctx, s, tagCol) {
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.18, s * 0.10);
    ctx.lineTo(s * 0.68, s * 0.10);
    ctx.lineTo(s * 0.82, s * 0.24);
    ctx.lineTo(s * 0.82, s * 0.90);
    ctx.lineTo(s * 0.18, s * 0.90);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    // dog-ear
    ctx.fillStyle = "#dccfa9";
    ctx.beginPath();
    ctx.moveTo(s * 0.68, s * 0.10);
    ctx.lineTo(s * 0.68, s * 0.24);
    ctx.lineTo(s * 0.82, s * 0.24);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.010);
    ctx.stroke();
    // bottom tag area
    if (tagCol) {
        ctx.fillStyle = tagCol;
        ctx.fillRect(s * 0.18, s * 0.66, s * 0.64, s * 0.24);
    }
}

// IMAGE — landscape thumbnail
function drawMimeImage(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.sageDeep);
    // sun + mountains
    ctx.beginPath();
    ctx.arc(s * 0.32, s * 0.74, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = _accent();
    ctx.fill();
    ctx.fillStyle = C.PALETTE.sageDark;
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.86);
    ctx.lineTo(s * 0.36, s * 0.72);
    ctx.lineTo(s * 0.48, s * 0.80);
    ctx.lineTo(s * 0.60, s * 0.68);
    ctx.lineTo(s * 0.80, s * 0.86);
    ctx.closePath();
    ctx.fill();
    _ext(ctx, s, ext || "IMG");
}

// AUDIO — note + waveform
function drawMimeAudio(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.plumDeep);
    // waveform
    ctx.strokeStyle = _accent();
    ctx.lineWidth = s * 0.012;
    ctx.beginPath();
    for (var x = 0.22; x <= 0.78; x += 0.03) {
        var y = 0.78 + Math.sin((x - 0.22) * 30) * 0.04;
        if (x === 0.22) ctx.moveTo(s * x, s * y); else ctx.lineTo(s * x, s * y);
    }
    ctx.stroke();
    // note
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.ellipse(s * 0.30, s * 0.72, s * 0.04, s * 0.030, -0.3, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillRect(s * 0.34, s * 0.66, s * 0.014, s * 0.06);
    _ext(ctx, s, ext || "AUD");
}

// VIDEO — film strip motif
function drawMimeVideo(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.indigoDeep);
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.moveTo(s * 0.40, s * 0.72);
    ctx.lineTo(s * 0.58, s * 0.78);
    ctx.lineTo(s * 0.40, s * 0.84);
    ctx.closePath();
    ctx.fill();
    // sprocket holes
    ctx.fillStyle = C.PALETTE.bgCream;
    for (var i = 0; i < 3; i++) {
        ctx.fillRect(s * (0.22 + i * 0.20), s * 0.70, s * 0.06, s * 0.02);
        ctx.fillRect(s * (0.22 + i * 0.20), s * 0.86, s * 0.06, s * 0.02);
    }
    _ext(ctx, s, ext || "VID");
}

// PDF
function drawMimePDF(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.terraDark);
    // PDF letters
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.16) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("PDF", s * 0.50, s * 0.78);
    // text lines above
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 4; i++) {
        ctx.fillRect(s * 0.24, s * (0.30 + i * 0.07), s * (0.50 - (i % 2) * 0.10), s * 0.012);
    }
}

// BOOK
function drawMimeBook(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    // open book
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.20);
    ctx.lineTo(s * 0.20, s * 0.28);
    ctx.lineTo(s * 0.20, s * 0.80);
    ctx.lineTo(s * 0.50, s * 0.76);
    ctx.lineTo(s * 0.80, s * 0.80);
    ctx.lineTo(s * 0.80, s * 0.28);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // spine fold
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.20); ctx.lineTo(s * 0.50, s * 0.76);
    ctx.stroke();
    // text
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.24, s * (0.34 + i * 0.08), s * 0.22, s * 0.012);
        ctx.fillRect(s * 0.54, s * (0.34 + i * 0.08), s * 0.22, s * 0.012);
    }
    // ribbon
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.moveTo(s * 0.66, s * 0.22);
    ctx.lineTo(s * 0.70, s * 0.22);
    ctx.lineTo(s * 0.70, s * 0.40);
    ctx.lineTo(s * 0.68, s * 0.36);
    ctx.lineTo(s * 0.66, s * 0.40);
    ctx.closePath();
    ctx.fill();
}

// TEXT
function drawMimeText(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s);
    // text lines
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 8; i++) {
        ctx.fillRect(s * 0.24, s * (0.20 + i * 0.08), s * (0.50 - (i % 3) * 0.08), s * 0.012);
    }
    _ext(ctx, s, ext || "TXT", _accent());
}

// MARKUP (HTML/XML/JSON)
function drawMimeMarkup(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.sageDeep);
    // chevrons
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.16) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("<>", s * 0.50, s * 0.78);
    // colored text
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.font = "700 " + Math.round(s * 0.08) + "px monospace";
    ctx.textAlign = "left";
    ctx.fillText("<tag>", s * 0.24, s * 0.28);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillText("  ...", s * 0.24, s * 0.38);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillText("</tag>", s * 0.24, s * 0.48);
    _ext(ctx, s, ext || "");
}

// CODE
function drawMimeCode(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.tealDeep);
    // syntax-highlighted lines
    ctx.font = "700 " + Math.round(s * 0.06) + "px monospace";
    ctx.textBaseline = "middle";
    var rows = [
        [C.PALETTE.terraDark, "fn"],
        [C.PALETTE.ink, " main()"],
        [C.PALETTE.sageDark, " {"],
        [C.PALETTE.ink, "  print"],
        [C.PALETTE.goldDark, "(...)"],
        [C.PALETTE.ink, "}"]
    ];
    for (var i = 0; i < 4; i++) {
        var x = s * 0.24;
        for (var k = 0; k < 3; k++) {
            var seg = rows[(i + k) % rows.length];
            ctx.fillStyle = seg[0];
            ctx.fillText(seg[1], x, s * (0.24 + i * 0.08));
            x += ctx.measureText(seg[1]).width;
        }
    }
    _ext(ctx, s, ext || "");
}

// ARCHIVE
function drawMimeArchive(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.terra);
    // zipper
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.48, s * 0.16, s * 0.04, s * 0.50);
    for (var i = 0; i < 6; i++) {
        ctx.fillRect(s * 0.42, s * (0.20 + i * 0.08), s * 0.06, s * 0.020);
        ctx.fillRect(s * 0.52, s * (0.24 + i * 0.08), s * 0.06, s * 0.020);
    }
    // pull
    ctx.fillStyle = _accent();
    C.roundRectPath(ctx, s * 0.42, s * 0.66, s * 0.16, s * 0.10, s * 0.02);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    _ext(ctx, s, ext || "ZIP");
}

// DOC
function drawMimeDoc(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.indigoDeep);
    ctx.fillStyle = C.PALETTE.ink;
    // title bar
    ctx.fillRect(s * 0.24, s * 0.22, s * 0.40, s * 0.030);
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.24, s * (0.32 + i * 0.06), s * (0.50 - (i % 2) * 0.10), s * 0.012);
    }
    _ext(ctx, s, ext || "DOC");
}

// SHEET (Excel-like)
function drawMimeSheet(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.sageDeep);
    // grid
    ctx.strokeStyle = C.PALETTE.ink;
    ctx.lineWidth = s * 0.006;
    for (var r = 0; r < 5; r++) {
        ctx.beginPath();
        ctx.moveTo(s * 0.22, s * (0.22 + r * 0.10));
        ctx.lineTo(s * 0.78, s * (0.22 + r * 0.10));
        ctx.stroke();
    }
    for (var c = 0; c < 4; c++) {
        ctx.beginPath();
        ctx.moveTo(s * (0.22 + c * 0.19), s * 0.22);
        ctx.lineTo(s * (0.22 + c * 0.19), s * 0.62);
        ctx.stroke();
    }
    _ext(ctx, s, ext || "CSV");
}

// SLIDES
function drawMimeSlides(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.terra);
    // slide thumb
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.24, s * 0.24, s * 0.50, s * 0.30);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.strokeRect(s * 0.24, s * 0.24, s * 0.50, s * 0.30);
    // title + bullets
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillRect(s * 0.27, s * 0.27, s * 0.32, s * 0.020);
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 3; i++) {
        ctx.fillRect(s * 0.30, s * (0.36 + i * 0.05), s * 0.20, s * 0.012);
    }
    _ext(ctx, s, ext || "PPT");
}

// FONT
function drawMimeFont(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.48) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("Aa", s * 0.50, s * 0.50);
    // baseline
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.22, s * 0.68, s * 0.56, s * 0.014);
}

// EXECUTABLE
function drawMimeExecutable(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, "#1d1a14");
    // gear
    ctx.save();
    ctx.translate(s * 0.5, s * 0.78);
    ctx.fillStyle = _accent();
    ctx.beginPath();
    for (var i = 0; i < 12; i++) {
        var a = i / 12 * Math.PI * 2;
        var r = i % 2 ? s * 0.11 : s * 0.08;
        var x = Math.cos(a) * r, y = Math.sin(a) * r;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.arc(0, 0, s * 0.04, 0, Math.PI * 2);
    ctx.fillStyle = "#1d1a14";
    ctx.fill();
    ctx.restore();
    // bin content
    ctx.fillStyle = "#dccfa9";
    ctx.font = "600 " + Math.round(s * 0.05) + "px monospace";
    ctx.textAlign = "left";
    ctx.fillText("0x4c", s * 0.24, s * 0.30);
    ctx.fillText("0x7f", s * 0.24, s * 0.40);
}

// ISO — disc image
function drawMimeISO(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.indigoDeep);
    // disc on page
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.78, s * 0.10, 0, Math.PI * 2);
    ctx.fillStyle = "#dadde5";
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(s * 0.50, s * 0.78, s * 0.030, 0, Math.PI * 2);
    ctx.fillStyle = C.PALETTE.bgCream;
    ctx.fill();
    // ISO text
    ctx.fillStyle = _accent();
    ctx.font = "700 " + Math.round(s * 0.10) + "px monospace";
    ctx.textAlign = "center";
    ctx.fillText("ISO", s * 0.50, s * 0.42);
}

// TORRENT
function drawMimeTorrent(ctx, s) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.tealDeep);
    ctx.fillStyle = _accent();
    ctx.beginPath();
    ctx.moveTo(s * 0.46, s * 0.22);
    ctx.lineTo(s * 0.54, s * 0.22);
    ctx.lineTo(s * 0.54, s * 0.50);
    ctx.lineTo(s * 0.62, s * 0.50);
    ctx.lineTo(s * 0.50, s * 0.66);
    ctx.lineTo(s * 0.38, s * 0.50);
    ctx.lineTo(s * 0.46, s * 0.50);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    _ext(ctx, s, "TORRENT");
}

// PACKAGE (deb/rpm/etc.)
function drawMimePackage(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, "#7a4a26");
    ctx.fillStyle = "#a4824a";
    ctx.fillRect(s * 0.28, s * 0.20, s * 0.44, s * 0.40);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.28, s * 0.20, s * 0.44, s * 0.40);
    // ribbon X
    ctx.fillStyle = _accent();
    ctx.fillRect(s * 0.46, s * 0.20, s * 0.08, s * 0.40);
    ctx.fillRect(s * 0.28, s * 0.36, s * 0.44, s * 0.08);
    _ext(ctx, s, (ext || "PKG").toUpperCase());
}

// 3D
function drawMime3D(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s, C.PALETTE.sageDeep);
    // wireframe cube
    ctx.save();
    ctx.translate(s * 0.5, s * 0.78);
    ctx.strokeStyle = _accent();
    ctx.lineWidth = s * 0.012;
    var p = [
        [-0.12, -0.06], [0.12, -0.06], [0.18, 0], [-0.06, 0],
        [-0.12, 0.06], [0.12, 0.06], [0.18, 0.12], [-0.06, 0.12]
    ];
    function l(a, b) {
        ctx.beginPath();
        ctx.moveTo(p[a][0] * s, p[a][1] * s);
        ctx.lineTo(p[b][0] * s, p[b][1] * s);
        ctx.stroke();
    }
    l(0,1); l(1,2); l(2,3); l(3,0);
    l(4,5); l(5,6); l(6,7); l(7,4);
    l(0,4); l(1,5); l(2,6); l(3,7);
    ctx.restore();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.08) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText((ext || "3D").toUpperCase(), s * 0.50, s * 0.30);
}

// GENERIC
function drawMimeGeneric(ctx, s, ext) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:_accent(), glow:_glow()});
    _page(ctx, s);
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.24, s * (0.32 + i * 0.07), s * (0.50 - (i % 2) * 0.10), s * 0.014);
    }
    if (ext) _ext(ctx, s, String(ext).toUpperCase(), _accent());
}

// helper — bottom-right extension tag
function _ext(ctx, s, label, col) {
    if (!label) return;
    ctx.save();
    var lab = String(label).toUpperCase().substring(0, 5);
    ctx.font = "700 " + Math.round(s * 0.10) + "px monospace";
    var w = Math.max(s * 0.20, ctx.measureText(lab).width + s * 0.08);
    var h = s * 0.16;
    ctx.fillStyle = col || C.PALETTE.bgCreamHi;
    C.roundRectPath(ctx, s * 0.82 - w, s * 0.86 - h, w, h, s * 0.02);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText(lab, s * 0.82 - w / 2, s * 0.86 - h / 2);
    ctx.restore();
}
