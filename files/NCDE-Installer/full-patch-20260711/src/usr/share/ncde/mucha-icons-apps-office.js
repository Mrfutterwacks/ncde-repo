// mucha-icons-apps-office.js — office suites, PDF/eBook readers.
.pragma library
.import "mucha-icons-core.js" as C

// Helper — sheet of paper as base
function _sheet(ctx, s, accentBand) {
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    C.roundRectPath(ctx, s * 0.16, s * 0.10, s * 0.62, s * 0.78, s * 0.02);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    // top band
    ctx.fillStyle = accentBand;
    ctx.fillRect(s * 0.16, s * 0.10, s * 0.62, s * 0.12);
}

// LibreOffice WRITER — blue band with W + ruled text
function drawLOWriter(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _sheet(ctx, s, C.PALETTE.indigoDeep);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px 'Cinzel',serif";
    ctx.textBaseline = "middle";
    ctx.fillText("W", s * 0.22, s * 0.16);
    // ruled text lines
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 7; i++) {
        ctx.fillRect(s * 0.22, s * (0.30 + i * 0.07), s * (0.50 - (i % 2) * 0.10), s * 0.013);
    }
    // pen at edge
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.74, s * 0.78);
    ctx.lineTo(s * 0.84, s * 0.86);
    ctx.lineTo(s * 0.80, s * 0.88);
    ctx.lineTo(s * 0.70, s * 0.80);
    ctx.closePath();
    ctx.fill();
}

// LibreOffice CALC — green band + grid
function drawLOCalc(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _sheet(ctx, s, C.PALETTE.sageDeep);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px 'Cinzel',serif";
    ctx.textBaseline = "middle";
    ctx.fillText("X", s * 0.22, s * 0.16);
    // spreadsheet grid
    ctx.strokeStyle = C.PALETTE.sageDeep;
    ctx.lineWidth = s * 0.008;
    for (var i = 0; i <= 4; i++) {
        ctx.beginPath();
        ctx.moveTo(s * 0.20, s * (0.28 + i * 0.13));
        ctx.lineTo(s * 0.76, s * (0.28 + i * 0.13));
        ctx.stroke();
    }
    for (var j = 0; j <= 3; j++) {
        ctx.beginPath();
        ctx.moveTo(s * (0.20 + j * 0.19), s * 0.28);
        ctx.lineTo(s * (0.20 + j * 0.19), s * 0.80);
        ctx.stroke();
    }
    // highlighted sum cell
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.57, s * 0.67, s * 0.19, s * 0.13);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.07) + "px monospace";
    ctx.fillText("Σ", s * 0.64, s * 0.745);
}

// LibreOffice IMPRESS — orange band + slide
function drawLOImpress(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _sheet(ctx, s, C.PALETTE.terra);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px 'Cinzel',serif";
    ctx.textBaseline = "middle";
    ctx.fillText("P", s * 0.22, s * 0.16);
    // slide thumbnail
    ctx.fillStyle = C.PALETTE.bgCream;
    ctx.fillRect(s * 0.22, s * 0.30, s * 0.50, s * 0.36);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.22, s * 0.30, s * 0.50, s * 0.36);
    // title line + bullets
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.fillRect(s * 0.26, s * 0.35, s * 0.30, s * 0.020);
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(s * 0.28, s * (0.46 + i * 0.06), s * 0.008, 0, Math.PI * 2);
        ctx.fillStyle = accent || C.PALETTE.gold;
        ctx.fill();
        ctx.fillStyle = C.PALETTE.ink;
        ctx.fillRect(s * 0.31, s * (0.455 + i * 0.06), s * 0.30, s * 0.012);
    }
    // play arrow corner
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.66, s * 0.78);
    ctx.lineTo(s * 0.76, s * 0.84);
    ctx.lineTo(s * 0.66, s * 0.90);
    ctx.closePath();
    ctx.fill();
}

// LibreOffice DRAW — yellow band + shapes
function drawLODraw(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _sheet(ctx, s, accent || C.PALETTE.gold);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.10) + "px 'Cinzel',serif";
    ctx.textBaseline = "middle";
    ctx.fillText("D", s * 0.22, s * 0.16);
    // overlapping shapes
    ctx.fillStyle = C.PALETTE.tealDeep;
    ctx.fillRect(s * 0.24, s * 0.36, s * 0.28, s * 0.28);
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.beginPath();
    ctx.arc(s * 0.58, s * 0.56, s * 0.16, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(s * 0.44, s * 0.72);
    ctx.lineTo(s * 0.66, s * 0.72);
    ctx.lineTo(s * 0.55, s * 0.86);
    ctx.closePath();
    ctx.fill();
}

// LibreOffice MATH — purple band + integral
function drawLOMath(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _sheet(ctx, s, C.PALETTE.plumDeep);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px 'Cinzel',serif";
    ctx.textBaseline = "middle";
    ctx.fillText("∫", s * 0.22, s * 0.16);
    // big integral
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "italic 700 " + Math.round(s * 0.40) + "px serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("∫", s * 0.36, s * 0.56);
    // expression
    ctx.font = "italic 600 " + Math.round(s * 0.11) + "px serif";
    ctx.textAlign = "left";
    ctx.fillText("f(x)dx", s * 0.42, s * 0.56);
}

// LibreOffice BASE — burgundy band + cabinet drawer
function drawLOBase(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    _sheet(ctx, s, C.PALETTE.roseDeep);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px 'Cinzel',serif";
    ctx.textBaseline = "middle";
    ctx.fillText("B", s * 0.22, s * 0.16);
    // 3 stacked database cylinders
    for (var i = 0; i < 3; i++) {
        var y = s * (0.34 + i * 0.16);
        ctx.fillStyle = i === 0 ? C.PALETTE.roseDeep : (i === 1 ? "#a86b58" : C.PALETTE.terraDark);
        ctx.beginPath();
        ctx.ellipse(s * 0.5, y, s * 0.22, s * 0.05, 0, 0, Math.PI * 2);
        ctx.fill();
        C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
        ctx.stroke();
        if (i < 2) {
            ctx.fillRect(s * 0.28, y, s * 0.44, s * 0.16);
        }
    }
}

// LibreOffice MAIN — five-pointed gilt star
function drawLOMain(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cx = s * 0.5, cy = s * 0.5;
    // big star
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    for (var i = 0; i < 10; i++) {
        var r = i % 2 ? s * 0.12 : s * 0.28;
        var a = i / 10 * Math.PI * 2 - Math.PI / 2;
        var x = cx + Math.cos(a) * r, y = cy + Math.sin(a) * r;
        if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // small offset star
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    for (var j = 0; j < 10; j++) {
        var rr = j % 2 ? s * 0.05 : s * 0.12;
        var aa = j / 10 * Math.PI * 2;
        var xx = cx + Math.cos(aa) * rr, yy = cy + Math.sin(aa) * rr;
        if (j === 0) ctx.moveTo(xx, yy); else ctx.lineTo(xx, yy);
    }
    ctx.closePath();
    ctx.fill();
}

// ONLYOFFICE — ribbon tabs with three coloured bands
function drawOnlyOffice(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // 3 tabs
    var tabs = [C.PALETTE.indigoDeep, C.PALETTE.sageDeep, C.PALETTE.terra];
    for (var i = 0; i < 3; i++) {
        var y = s * (0.18 + i * 0.22);
        ctx.fillStyle = tabs[i];
        C.roundRectPath(ctx, s * 0.16, y, s * 0.68, s * 0.18, s * 0.02);
        ctx.fill();
        // tab letter
        ctx.fillStyle = C.PALETTE.bgCreamHi;
        ctx.font = "700 " + Math.round(s * 0.12) + "px 'Cinzel',serif";
        ctx.textBaseline = "middle";
        ctx.fillText(["W","X","P"][i], s * 0.22, y + s * 0.09);
        // ribbon at right
        ctx.fillRect(s * 0.36, y + s * 0.07, s * (0.30 - i * 0.04), s * 0.020);
    }
}

// WPS — three-tier nested arches
function drawWPS(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    var cols = [C.PALETTE.indigoDeep, C.PALETTE.terra, C.PALETTE.sageDeep];
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(s * 0.5, s * 0.62, s * (0.32 - i * 0.10), Math.PI, 0);
        ctx.lineTo(s * (0.50 + 0.32 - i * 0.10), s * 0.78);
        ctx.lineTo(s * (0.50 - 0.32 + i * 0.10), s * 0.78);
        ctx.closePath();
        ctx.fillStyle = cols[i];
        ctx.fill();
    }
    // WPS letters
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.font = "700 " + Math.round(s * 0.10) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("W", s * 0.50, s * 0.32);
    ctx.fillText("P", s * 0.50, s * 0.46);
    ctx.fillText("S", s * 0.50, s * 0.60);
}

// ABIWORD — quill writing capital A
function drawAbiword(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // A
    ctx.fillStyle = C.PALETTE.terraDark;
    ctx.font = "700 " + Math.round(s * 0.50) + "px 'Cinzel',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("A", s * 0.5, s * 0.5);
    // quill diag
    ctx.save();
    ctx.translate(s * 0.74, s * 0.30);
    ctx.rotate(0.5);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(0, -s * 0.16);
    ctx.lineTo(s * 0.04, -s * 0.16);
    ctx.lineTo(s * 0.06, s * 0.08);
    ctx.lineTo(-s * 0.02, s * 0.10);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.008);
    ctx.stroke();
    ctx.restore();
}

// GNUMERIC — abacus
function drawGnumeric(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // frame
    ctx.fillStyle = "#7a4a26";
    ctx.fillRect(s * 0.16, s * 0.18, s * 0.68, s * 0.64);
    ctx.fillStyle = C.PALETTE.bgCream;
    ctx.fillRect(s * 0.20, s * 0.22, s * 0.60, s * 0.56);
    // rods (4 rows of 5 beads)
    var bcols = [C.PALETTE.terra, C.PALETTE.sageDeep, accent || C.PALETTE.gold, C.PALETTE.indigoDeep];
    for (var r = 0; r < 4; r++) {
        ctx.strokeStyle = C.PALETTE.ink;
        ctx.lineWidth = s * 0.006;
        ctx.beginPath();
        ctx.moveTo(s * 0.22, s * (0.30 + r * 0.13));
        ctx.lineTo(s * 0.78, s * (0.30 + r * 0.13));
        ctx.stroke();
        for (var b = 0; b < 5; b++) {
            ctx.beginPath();
            ctx.arc(s * (0.26 + b * 0.10), s * (0.30 + r * 0.13), s * 0.030, 0, Math.PI * 2);
            ctx.fillStyle = bcols[r];
            ctx.fill();
            C.setStroke(ctx, C.PALETTE.ink, s * 0.006);
            ctx.stroke();
        }
    }
}

// CALLIGRA — calligraphic capital C
function drawCalligra(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // ornamental C
    ctx.save();
    ctx.strokeStyle = C.PALETTE.plumDeep;
    ctx.lineWidth = s * 0.07;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.5, s * 0.22, Math.PI * 0.20, Math.PI * 1.80);
    ctx.stroke();
    // gilt inner
    ctx.strokeStyle = accent || C.PALETTE.goldHi;
    ctx.lineWidth = s * 0.022;
    ctx.beginPath();
    ctx.arc(s * 0.5, s * 0.5, s * 0.22, Math.PI * 0.20, Math.PI * 1.80);
    ctx.stroke();
    ctx.restore();
    // terminals (ball serifs)
    ctx.fillStyle = accent || C.PALETTE.gold;
    var t1 = [s * 0.5 + Math.cos(Math.PI * 0.20) * s * 0.22, s * 0.5 + Math.sin(Math.PI * 0.20) * s * 0.22];
    var t2 = [s * 0.5 + Math.cos(Math.PI * 1.80) * s * 0.22, s * 0.5 + Math.sin(Math.PI * 1.80) * s * 0.22];
    [t1, t2].forEach(function(p) {
        ctx.beginPath();
        ctx.arc(p[0], p[1], s * 0.035, 0, Math.PI * 2);
        ctx.fill();
    });
    // floral flourish to the right
    C.drawFloralStem(ctx, s * 0.72, s * 0.70, s * 0.20, C.PALETTE.sageDeep, accent || C.PALETTE.gold);
}

// OKULAR — open book with bookmark ribbon
function drawOkular(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // book pages (two halves)
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.22);
    ctx.lineTo(s * 0.18, s * 0.28);
    ctx.lineTo(s * 0.18, s * 0.80);
    ctx.lineTo(s * 0.50, s * 0.76);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(s * 0.50, s * 0.22);
    ctx.lineTo(s * 0.82, s * 0.28);
    ctx.lineTo(s * 0.82, s * 0.80);
    ctx.lineTo(s * 0.50, s * 0.76);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.stroke();
    // text lines
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.22, s * (0.32 + i * 0.08), s * 0.24, s * 0.012);
        ctx.fillRect(s * 0.54, s * (0.32 + i * 0.08), s * 0.24, s * 0.012);
    }
    // bookmark ribbon
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.beginPath();
    ctx.moveTo(s * 0.66, s * 0.22);
    ctx.lineTo(s * 0.74, s * 0.22);
    ctx.lineTo(s * 0.74, s * 0.42);
    ctx.lineTo(s * 0.70, s * 0.38);
    ctx.lineTo(s * 0.66, s * 0.42);
    ctx.closePath();
    ctx.fill();
}

// EVINCE — folded page corner with text
function drawEvince(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // page
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    ctx.moveTo(s * 0.20, s * 0.14);
    ctx.lineTo(s * 0.68, s * 0.14);
    ctx.lineTo(s * 0.80, s * 0.26);
    ctx.lineTo(s * 0.80, s * 0.86);
    ctx.lineTo(s * 0.20, s * 0.86);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.014);
    ctx.stroke();
    // fold triangle
    ctx.fillStyle = C.PALETTE.bgPaper;
    ctx.beginPath();
    ctx.moveTo(s * 0.68, s * 0.14);
    ctx.lineTo(s * 0.68, s * 0.26);
    ctx.lineTo(s * 0.80, s * 0.26);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    // text
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 7; i++) {
        ctx.fillRect(s * 0.26, s * (0.30 + i * 0.07), s * (0.46 - (i % 2) * 0.10), s * 0.012);
    }
    // PDF tag
    ctx.fillStyle = accent || C.PALETTE.gold;
    C.roundRectPath(ctx, s * 0.24, s * 0.74, s * 0.18, s * 0.10, s * 0.01);
    ctx.fill();
    ctx.fillStyle = C.PALETTE.ink;
    ctx.font = "700 " + Math.round(s * 0.07) + "px monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText("PDF", s * 0.33, s * 0.79);
}

// FOLIATE — leaf turning a page
function drawFoliate(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"medallion", accent:accent, glow:glow});
    // book base
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.20, s * 0.36, s * 0.60, s * 0.42);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.012);
    ctx.strokeRect(s * 0.20, s * 0.36, s * 0.60, s * 0.42);
    // spine
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.20, s * 0.36, s * 0.04, s * 0.42);
    // a turning leaf
    ctx.save();
    ctx.translate(s * 0.5, s * 0.34);
    ctx.rotate(-0.4);
    ctx.fillStyle = C.PALETTE.sageDeep;
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.bezierCurveTo(s * 0.20, -s * 0.16, s * 0.22, s * 0.16, 0, s * 0.20);
    ctx.bezierCurveTo(-s * 0.04, s * 0.10, -s * 0.04, s * 0.04, 0, 0);
    ctx.closePath();
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(0, 0); ctx.lineTo(0, s * 0.20);
    ctx.stroke();
    ctx.restore();
}

// CALIBRE — calipers measuring a book
function drawCalibre(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgPaper, {shape:"square", accent:accent, glow:glow});
    // book
    ctx.fillStyle = C.PALETTE.indigoDeep;
    ctx.fillRect(s * 0.32, s * 0.30, s * 0.36, s * 0.50);
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.34, s * 0.32, s * 0.32, s * 0.46);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.fillRect(s * 0.34, s * 0.32, s * 0.04, s * 0.46);
    // calipers across top
    ctx.fillStyle = "#9b9bb0";
    ctx.fillRect(s * 0.20, s * 0.20, s * 0.60, s * 0.06);
    ctx.fillRect(s * 0.30, s * 0.16, s * 0.04, s * 0.16);
    ctx.fillRect(s * 0.66, s * 0.16, s * 0.04, s * 0.16);
    // tick marks
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 8; i++) {
        ctx.fillRect(s * (0.24 + i * 0.07), s * 0.20, s * 0.004, s * 0.04);
    }
    // value label
    ctx.fillStyle = accent || C.PALETTE.gold;
    C.roundRectPath(ctx, s * 0.40, s * 0.85, s * 0.20, s * 0.08, s * 0.01);
    ctx.fill();
}

// ZATHURA — reading lamp + page
function drawZathura(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // page
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.fillRect(s * 0.22, s * 0.34, s * 0.42, s * 0.48);
    C.setStroke(ctx, C.PALETTE.ink, s * 0.010);
    ctx.strokeRect(s * 0.22, s * 0.34, s * 0.42, s * 0.48);
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.26, s * (0.40 + i * 0.07), s * (0.32 - (i % 2) * 0.08), s * 0.012);
    }
    // lamp
    ctx.save();
    ctx.translate(s * 0.70, s * 0.30);
    ctx.fillStyle = "#3b3a30";
    ctx.beginPath();
    ctx.moveTo(0, 0); ctx.lineTo(s * 0.12, 0); ctx.lineTo(s * 0.08, s * 0.10); ctx.lineTo(s * 0.04, s * 0.10);
    ctx.closePath();
    ctx.fill();
    ctx.fillStyle = "#2a2520";
    ctx.fillRect(s * 0.054, s * 0.10, s * 0.012, s * 0.30);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(s * 0.02, s * 0.40, s * 0.08, s * 0.020);
    // light cone
    ctx.fillStyle = "rgba(255,235,180,0.35)";
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.lineTo(s * 0.12, 0);
    ctx.lineTo(s * 0.20, s * 0.30);
    ctx.lineTo(-s * 0.08, s * 0.30);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}

// MUPDF / QPDFVIEW / SIOYEK — annotated manuscript scroll
function drawMuPDF(ctx, s, accent, glow) {
    C.drawTile(ctx, s, C.PALETTE.bgCream, {shape:"square", accent:accent, glow:glow});
    // scroll
    ctx.fillStyle = C.PALETTE.bgCreamHi;
    ctx.beginPath();
    C.roundRectPath(ctx, s * 0.20, s * 0.22, s * 0.60, s * 0.56, s * 0.04);
    ctx.fill();
    C.setStroke(ctx, C.PALETTE.goldDark, s * 0.012);
    ctx.stroke();
    // text
    ctx.fillStyle = C.PALETTE.ink;
    for (var i = 0; i < 5; i++) {
        ctx.fillRect(s * 0.26, s * (0.30 + i * 0.08), s * (0.48 - (i % 2) * 0.08), s * 0.012);
    }
    // highlighter
    ctx.fillStyle = "rgba(184,140,74,0.5)";
    ctx.fillRect(s * 0.26, s * 0.46, s * 0.34, s * 0.020);
    // small pencil
    ctx.save();
    ctx.translate(s * 0.74, s * 0.74);
    ctx.rotate(-Math.PI / 4);
    ctx.fillStyle = accent || C.PALETTE.gold;
    ctx.fillRect(-s * 0.020, -s * 0.16, s * 0.040, s * 0.20);
    ctx.fillStyle = C.PALETTE.ink;
    ctx.beginPath();
    ctx.moveTo(-s * 0.020, -s * 0.16);
    ctx.lineTo(s * 0.020, -s * 0.16);
    ctx.lineTo(0, -s * 0.22);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}
