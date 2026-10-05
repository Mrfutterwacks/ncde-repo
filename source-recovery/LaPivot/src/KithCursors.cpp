// Rebuilt from oracle: decomp/_global.c renderKith* and kith* helpers,
// plus decomp/renderKithWait_int_.c.
// Spec: NCDE-ARCHITECTURE-DIGEST.md §2; PRODUCTION-PUNCHLIST.md §0.8/§0.11.
// 2026-10-01: the art is the oracle's again, translated line for line (an earlier rebuild had redrawn it).
// Measured pixel-identical to the oracle with tests/cursor_parity.sh (.kith-pristine frames).

#include "KithCursors.h"

#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QPixmap>
#include <QPolygonF>
#include <QFont>
#include <QTransform>
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QtEndian>
#include <QtMath>

namespace KithCursors {

int imageSize(int logicalSize)
{
    return qBound(8, logicalSize, 512) + 12;
}

QPoint hotspotImage(int logicalSize, double hx, double hy)
{
    const int size = qBound(8, logicalSize, 512);
    return QPoint(qBound(0, qRound(hx * size) + 6, size + 11),
                  qBound(0, qRound(hy * size) + 6, size + 11));
}

// ── Oracle art, translated line for line from decomp/_global.c (0x273d3e..0x27a3a3) ─────────────────
// Every renderer: QImage(size+12, ARGB32_Premultiplied), transparent, antialiased, origin at (6,6),
// all coordinates fractions of the logical size s. 2026-10-01: the previous rebuild redrew 12 of the
// 14 shapes (hand shown as an arrow, different I-beam, move/resize/crosshair/not-allowed/grab art) —
// the operator saw the Kith cursor change between windows and desktop. These are the oracle's.

QLinearGradient kithGlassFill(double x1, double y1, double x2, double y2)
{
    QLinearGradient g(x1, y1, x2, y2);
    g.setColorAt(0.0, QColor("#7fd0f0"));
    g.setColorAt(0.5, QColor("#3a78c8"));
    g.setColorAt(1.0, QColor("#15306a"));
    return g;
}

QLinearGradient kithRubyFill(double x1, double y1, double x2, double y2)
{
    QLinearGradient g(x1, y1, x2, y2);
    g.setColorAt(0.0, QColor("#f08098"));
    g.setColorAt(0.5, QColor("#d33a52"));
    g.setColorAt(1.0, QColor("#7a1020"));
    return g;
}

void kithCame(QPainter &painter, const QPainterPath &path, double width)
{
    QPen pen(QColor("#0b0b14"));
    pen.setWidthF(width);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    painter.strokePath(path, pen);
}

void kithSheen(QPainter &painter, double x, double y, double w, double h)
{
    QLinearGradient g(x, y, x, h * 0.6 + y);
    g.setColorAt(0.0, QColor(255, 255, 255, 128));
    g.setColorAt(1.0, QColor(255, 255, 255, 0));
    painter.fillRect(QRectF(x, y, w, h), QBrush(g));
}

namespace {

void begin(QImage &image, QPainter &p, int size)
{
    image = QImage(size + 12, size + 12, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    p.begin(&image);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.translate(6.0, 6.0);
}

void goldDot(QPainter &p, double x, double y, double r)
{
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#fff0c0"));
    p.drawEllipse(QPointF(x, y), r, r);
}

QPainterPath arrowPath(double s)
{
    QPainterPath path;
    path.moveTo(s * 0.16, s * 0.06);
    path.lineTo(s * 0.16, s * 0.78);
    path.lineTo(s * 0.34, s * 0.6);
    path.lineTo(s * 0.46, s * 0.86);
    path.lineTo(s * 0.58, s * 0.8);
    path.lineTo(s * 0.46, s * 0.54);
    path.lineTo(s * 0.7, s * 0.54);
    path.closeSubpath();
    return path;
}

} // namespace

void renderKithArrow(QImage &image, int size)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    const QPainterPath path = arrowPath(s);
    p.fillPath(path, QBrush(kithGlassFill(s * 0.16, s * 0.06, s * 0.6, s * 0.86)));
    kithCame(p, path, s * 0.07);
    p.save();
    p.setClipPath(path, Qt::ReplaceClip);
    QPen line(QColor(0xbf, 0xe6, 0xfb, 0xcc));
    line.setWidthF(s * 0.03);
    p.setPen(line);
    p.drawLine(QPointF(s * 0.2, s * 0.12), QPointF(s * 0.2, s * 0.62));
    kithSheen(p, s * 0.1, s * 0.04, s * 0.4, s * 0.5);
    p.restore();
    goldDot(p, s * 0.26, s * 0.2, s * 0.035);
    p.end();
}

void renderKithPointer(QImage &image, int size)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    QPainterPath path;
    path.moveTo(s * 0.36, s * 0.06);
    path.lineTo(s * 0.36, s * 0.46);
    path.lineTo(s * 0.3, s * 0.4);
    path.lineTo(s * 0.22, s * 0.48);
    path.cubicTo(s * 0.2, s * 0.54, s * 0.24, s * 0.62, s * 0.3, s * 0.72);
    path.lineTo(s * 0.34, s * 0.9);
    path.lineTo(s * 0.72, s * 0.9);
    path.lineTo(s * 0.78, s * 0.56);
    path.lineTo(s * 0.74, s * 0.4);
    path.lineTo(s * 0.68, s * 0.44);
    path.lineTo(s * 0.66, s * 0.4);
    path.lineTo(s * 0.6, s * 0.44);
    path.lineTo(s * 0.58, s * 0.4);
    path.lineTo(s * 0.52, s * 0.44);
    path.lineTo(s * 0.5, s * 0.3);
    path.lineTo(s * 0.44, s * 0.3);
    path.lineTo(s * 0.44, s * 0.06);
    path.closeSubpath();
    p.fillPath(path, QBrush(kithGlassFill(s * 0.2, s * 0.06, s * 0.8, s * 0.9)));
    kithCame(p, path, s * 0.065);
    p.save();
    p.setClipPath(path, Qt::ReplaceClip);
    kithSheen(p, s * 0.2, s * 0.04, s * 0.6, s * 0.5);
    p.restore();
    QPen grooves(QColor(0x0b, 0x0b, 0x14, 0x8c));
    grooves.setWidthF(s * 0.025);
    p.setPen(grooves);
    for (const double x : {0.52, 0.6, 0.68})
        p.drawLine(QPointF(x * s, s * 0.5), QPointF(x * s, s * 0.78));
    goldDot(p, s * 0.4, s * 0.12, s * 0.03);
    p.end();
}

void renderKithText(QImage &image, int size)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    QPainterPath path;
    path.addRect(QRectF(s * 0.44, s * 0.12, s * 0.12, s * 0.76));
    path.addRect(QRectF(s * 0.32, s * 0.12, s * 0.36, s * 0.1));
    path.addRect(QRectF(s * 0.32, s * 0.78, s * 0.36, s * 0.1));
    p.fillPath(path, QBrush(kithGlassFill(s * 0.3, s * 0.1, s * 0.7, s * 0.9)));
    kithCame(p, path, s * 0.05);
    goldDot(p, s * 0.5, s * 0.22, s * 0.03);
    p.end();
}

void renderKithWait(QImage &image, int size)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    const double cx = s * 0.5;
    const double cy = s * 0.5;
    const double r = s * 0.42;
    const auto at = [&](double radius, double angle) {
        return QPointF(std::cos(angle) * radius + cx, std::sin(angle) * radius + cy);
    };
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#0b0b14"));
    p.drawEllipse(QPointF(cx, cy), r, r);
    for (int i = 0; i < 12; ++i) {
        const double a0 = (double(i) / 12.0 + double(i) / 12.0) * 3.141592653589793 + 0.06;
        const double f1 = double(i + 1) / 12.0;
        const double a1 = (f1 + f1) * 3.141592653589793 - 0.06;
        QPolygonF segment;
        segment << at(r * 0.94, a0) << at(r * 0.94, a1) << at(r * 0.52, a1) << at(r * 0.52, a0);
        QColor colour((i & 1) == 0 ? "#3a78c8" : "#eef4f8");
        colour.setAlphaF(float(std::pow(double(i) / 12.0, 1.5) * 0.6 + 0.4));
        p.setBrush(colour);
        p.drawPolygon(segment, Qt::OddEvenFill);
    }
    QPen ring(QColor("#0b0b14"));
    ring.setWidthF(s * 0.05);
    p.setPen(ring);
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(QPointF(cx, cy), r * 0.52, r * 0.52);
    ring.setWidthF(s * 0.035);
    p.setPen(ring);
    p.drawEllipse(QPointF(cx, cy), r * 0.96, r * 0.96);
    QRadialGradient hub(cx, cy, r * 0.3, cx - r * 0.1, cy - r * 0.1);
    hub.setColorAt(0.0, QColor("#fff0c0"));
    hub.setColorAt(1.0, QColor("#e6c785"));
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(hub));
    p.drawEllipse(QPointF(cx, cy), r * 0.3, r * 0.3);
    QPen hubRing(QColor("#0b0b14"));
    hubRing.setWidthF(s * 0.03);
    p.setPen(hubRing);
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(QPointF(cx, cy), r * 0.3, r * 0.3);
    p.end();
}

void renderKithHelp(QImage &image, int size)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    const double a = s * 0.78;                       // the help arrow is the arrow at 78 %
    const QPainterPath path = arrowPath(a);
    p.fillPath(path, QBrush(kithGlassFill(a * 0.16, a * 0.06, a * 0.6, a * 0.86)));
    kithCame(p, path, a * 0.07);
    p.save();
    p.setClipPath(path, Qt::ReplaceClip);
    QPen line(QColor(0xbf, 0xe6, 0xfb, 0xcc));
    line.setWidthF(a * 0.03);
    p.setPen(line);
    p.drawLine(QPointF(a * 0.2, a * 0.12), QPointF(a * 0.2, a * 0.62));
    kithSheen(p, a * 0.1, a * 0.04, a * 0.4, a * 0.5);
    p.restore();
    goldDot(p, a * 0.26, a * 0.2, a * 0.035);
    p.save();
    p.translate(s * 0.52, s * 0.52);
    QPainterPath badge;
    badge.addEllipse(QPointF(0.0, 0.0), s * 0.26, s * 0.26);
    p.fillPath(badge, QBrush(kithRubyFill(-s * 0.2, -s * 0.2, s * 0.2, s * 0.2)));
    QPen rim(QColor("#0b0b14"));
    rim.setWidthF(s * 0.045);
    p.setPen(rim);
    p.setBrush(Qt::NoBrush);
    p.drawPath(badge);
    p.setPen(QColor("#fff0c0"));
    QFont font = p.font();
    font.setBold(true);
    font.setFamily(QStringLiteral("serif"));
    font.setPixelSize(qRound(s * 0.34));
    p.setFont(font);
    p.drawText(QRectF(-s * 0.3, -s * 0.3, s * 0.6, s * 0.6), Qt::AlignCenter, QStringLiteral("?"));
    p.restore();
    p.end();
}

void renderKithMove(QImage &image, int size)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    const double cx = s * 0.5;
    const double cy = s * 0.5;
    const double r = s * 0.4;
    const double w = s * 0.1;
    const double h = s * 0.18;
    const QPointF arm[7] = {{-w, -w}, {-w, h - r}, {-h, h - r}, {0.0, -r}, {h, h - r}, {w, h - r}, {w, -w}};
    QPainterPath path;
    for (int i = 0; i < 4; ++i) {
        QTransform t;
        t.rotate(double(i) * 90.0, Qt::ZAxis);
        path.moveTo(t.map(arm[0]) + QPointF(cx, cy));
        for (int j = 1; j < 7; ++j)
            path.lineTo(t.map(arm[j]) + QPointF(cx, cy));
    }
    p.fillPath(path, QBrush(kithGlassFill(cx - s * 0.4, cy - s * 0.4, s * 0.4 + cx, s * 0.4 + cy)));
    kithCame(p, path, s * 0.055);
    goldDot(p, cx, cy, s * 0.05);
    p.end();
}

void renderKithResize(QImage &image, int size, double angleRadians)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    const double cx = s * 0.5;
    const double cy = s * 0.5;
    const double r = s * 0.4;
    const double w = s * 0.085;
    const double h = s * 0.18;
    const QPointF outline[14] = {{-w, -w}, {-w, h - r}, {-h, h - r}, {0.0, -r}, {h, h - r}, {w, h - r}, {w, -w},
                                 {w, w},   {w, r - h},  {h, r - h},  {0.0, r},  {-h, r - h}, {-w, r - h}, {-w, w}};
    QTransform t;
    t.rotate(qRadiansToDegrees(angleRadians), Qt::ZAxis);
    const QPointF c(cx, cy);
    QPainterPath path;
    path.moveTo(t.map(outline[0]) + c);
    for (int i = 1; i < 14; ++i)
        path.lineTo(t.map(outline[i]) + c);
    path.closeSubpath();
    const QPointF from = t.map(QPointF(0.0, -r)) + c;
    const QPointF to = t.map(QPointF(0.0, r)) + c;
    p.fillPath(path, QBrush(kithGlassFill(from.x(), from.y(), to.x(), to.y())));
    kithCame(p, path, s * 0.055);
    goldDot(p, cx, cy, s * 0.045);
    p.end();
}

void renderKithCrosshair(QImage &image, int size)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    const double cx = s * 0.5;
    const double cy = s * 0.5;
    const double r = s * 0.42;
    const double w = s * 0.05;
    QPainterPath path;
    path.addRect(QRectF(cx - w, cy - r, w + w, r + r));
    path.addRect(QRectF(cx - r, cy - w, r + r, w + w));
    p.fillPath(path, QBrush(kithGlassFill(cx - r, cy - r, cx + r, cy + r)));
    kithCame(p, path, s * 0.04);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#d33a52"));
    p.drawEllipse(QPointF(cx, cy), s * 0.05, s * 0.05);
    QPen rim(QColor("#0b0b14"));
    rim.setWidthF(s * 0.02);
    p.setPen(rim);
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(QPointF(cx, cy), s * 0.05, s * 0.05);
    p.end();
}

void renderKithNotAllowed(QImage &image, int size)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    const double cx = s * 0.5;
    const double cy = s * 0.5;
    QPen came(QColor("#0b0b14"));
    came.setWidthF(s * 0.14);
    p.setPen(came);
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(QPointF(cx, cy), s * 0.4, s * 0.4);
    const QPen ring(QBrush(kithRubyFill(cx - s * 0.4, cy - s * 0.4, s * 0.4 + cx, s * 0.4 + cy)), s * 0.1,
                    Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    p.setPen(ring);
    p.drawEllipse(QPointF(cx, cy), s * 0.4, s * 0.4);
    QTransform t;
    t.rotate(-45.0, Qt::ZAxis);
    QPolygonF outer = t.map(QPolygonF(QRectF(s * -0.4, s * -0.07, s * 0.8, s * 0.14)));
    outer.translate(cx, cy);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#0b0b14"));
    p.drawPolygon(outer, Qt::OddEvenFill);
    QPolygonF bar = t.map(QPolygonF(QRectF(s * -0.4, s * -0.05, s * 0.8, s * 0.1)));
    bar.translate(cx, cy);
    const QPointF from = t.map(QPointF(s * -0.4, 0.0)) + QPointF(cx, cy);
    const QPointF to = t.map(QPointF(s * 0.4, 0.0)) + QPointF(cx, cy);
    p.setBrush(QBrush(kithRubyFill(from.x(), from.y(), to.x(), to.y())));
    p.drawPolygon(bar, Qt::OddEvenFill);
    p.end();
}

void renderKithHand(QImage &image, int size, bool closed)
{
    QPainter p;
    begin(image, p, size);
    const double s = size;
    const double k = closed ? 0.42 : 0.3;            // knuckle line: lower when the hand is closed
    QPainterPath path;
    path.moveTo(s * 0.24, s * 0.62);
    path.lineTo(s * 0.24, (k + 0.08) * s);
    path.cubicTo(s * 0.24, k * s, s * 0.34, k * s, s * 0.34, (k + 0.04) * s);
    path.lineTo(s * 0.34, k * s);
    path.cubicTo(s * 0.34, (k - 0.06) * s, s * 0.46, (k - 0.06) * s, s * 0.46, k * s);
    path.cubicTo(s * 0.46, (k - 0.08) * s, s * 0.58, (k - 0.08) * s, s * 0.58, k * s);
    path.cubicTo(s * 0.58, (k - 0.06) * s, s * 0.7, (k - 0.06) * s, s * 0.7, (k + 0.02) * s);
    path.lineTo(s * 0.74, s * 0.5);
    path.cubicTo(s * 0.78, s * 0.66, s * 0.7, s * 0.86, s * 0.54, s * 0.88);
    path.lineTo(s * 0.4, s * 0.88);
    path.cubicTo(s * 0.3, s * 0.86, s * 0.24, s * 0.74, s * 0.24, s * 0.62);
    path.closeSubpath();
    p.fillPath(path, QBrush(kithGlassFill(s * 0.2, k * s, s * 0.78, s * 0.9)));
    kithCame(p, path, s * 0.055);
    p.save();
    p.setClipPath(path, Qt::ReplaceClip);
    kithSheen(p, s * 0.2, k * s, s * 0.6, s * 0.4);
    p.restore();
    QPen grooves(QColor(0x0b, 0x0b, 0x14, 0x80));
    grooves.setWidthF(s * 0.022);
    p.setPen(grooves);
    for (const double x : {0.34, 0.46, 0.58})
        p.drawLine(QPointF(x * s, (k + 0.02) * s), QPointF(x * s, (k + 0.16) * s));
    p.end();
}

QCursor makeCursor(std::function<void(QImage &, int)> renderer, int logicalSize, double hx, double hy)
{
    const int size = qBound(8, logicalSize, 512);
    QImage image;
    renderer(image, size);
    if (image.isNull())
        return QCursor(Qt::ArrowCursor);
    const QPoint hot = hotspotImage(size, hx, hy);
    return QCursor(QPixmap::fromImage(image), hot.x(), hot.y());
}

// Oracle writeXcursorFile (decomp/_global.c 0x27df4b): one frame per requested size, hotspot
// qRound(size*h)+6, everything streamed little-endian through ONE QDataStream on the QFile; success =
// no file error after close. The earlier rebuild mixed a QDataStream with direct QByteArray appends:
// the stream's buffer position never moved past the appended pixels, so the second frame header
// overwrote the first frame, the size check failed and NO Kith file was ever written (2026-10-01:
// no XCURSOR_PATH -> apps fell back to another cursor, size/colour jump between windows and desktop).
bool writeXcursorFile(const QString &path, const QList<int> &sizes,
                      const std::function<QImage(int)> &renderer, double hx, double hy)
{
    struct Frame { QImage image; int size; int hotX; int hotY; };
    QList<Frame> frames;
    for (const int size : sizes) {
        const QImage image = renderer(size).convertToFormat(QImage::Format_ARGB32_Premultiplied);
        frames.append({image, size, qRound(size * hx) + 6, qRound(size * hy) + 6});
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "CursorManager: cannot write cursor file" << path << file.errorString();
        return false;
    }
    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);
    const quint32 count = quint32(frames.size());
    stream << quint32(0x72756358) << quint32(16) << quint32(0x10000) << count;
    quint32 position = count * 12 + 16;
    for (const Frame &frame : frames) {
        stream << quint32(0xfffd0002) << quint32(frame.size) << position;
        position += quint32((frame.image.width() * frame.image.height() + 9) * 4);
    }
    for (const Frame &frame : frames) {
        stream << quint32(36) << quint32(0xfffd0002) << quint32(frame.size) << quint32(1)
               << quint32(frame.image.width()) << quint32(frame.image.height())
               << quint32(frame.hotX) << quint32(frame.hotY) << quint32(0);
        for (int y = 0; y < frame.image.height(); ++y) {
            const auto *line = reinterpret_cast<const quint32 *>(frame.image.constScanLine(y));
            for (int x = 0; x < frame.image.width(); ++x)
                stream << line[x];
        }
    }
    file.close();
    const bool ok = file.error() == QFileDevice::NoError;
    if (!ok)
        qWarning() << "CursorManager: short write on cursor file" << path << file.errorString();
    return ok;
}

} // namespace KithCursors
