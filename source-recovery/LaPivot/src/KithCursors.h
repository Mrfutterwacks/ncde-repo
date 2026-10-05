// KithCursors — procedural cursor rendering for the "Kithglass" cursor theme
//
// Rebuilt from oracle: decomp/_global.c renderKith* functions and helpers.
// All functions render into a QImage of size (cursorSize + 12) x (cursorSize + 12)
// with a 6px transparent border. The logical cursor size is cursorSize.
//
// Color palette (from oracle):
//   Glass blue:  #7fd0f0 (top), #3a78c8 (mid), #15306a (bottom)
//   Ruby red:    #f08098 (top), #d33a52 (mid), #7a1020 (bottom)
//   Came (outline): #0b0b14
//   Sheen:       white with alpha gradient
//   Accent dot:  #fff0c0
//
// DEFECTS FIXED vs oracle:
//  1. Oracle used QImage::Format_ARGB32 (6) without premultiplied alpha for xcb.
//     Fixed: use Format_ARGB32_Premultiplied for correct xcb rendering.
//  2. Oracle hardcoded many magic numbers. Fixed: extracted as named constants.
//  3. Oracle did not verify hotspots inside image bounds. Fixed: assertions in debug.

#ifndef KITHCURSORS_H
#define KITHCURSORS_H

#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPointF>
#include <QRectF>
#include <QCursor>
#include <cmath>
#include <functional>

namespace KithCursors {

// Image size = logical size + 12 (6px border each side for xcb ARGB32 pixmap)
int imageSize(int logicalSize);

// Hotspot in image coordinates = logical hotspot * scale + 6
QPoint hotspotImage(int logicalSize, double hx, double hy);

// --- Gradient helpers ---

// Glass blue gradient (arrow, help, pointer, move, resize, hand)
QLinearGradient kithGlassFill(double x1, double y1, double x2, double y2);

// Ruby red gradient (wait center, not-allowed, help ?)
QLinearGradient kithRubyFill(double x1, double y1, double x2, double y2);

// Came (dark outline) stroke on a path
void kithCame(QPainter &painter, const QPainterPath &path, double width);

// Sheen (white highlight gradient)
void kithSheen(QPainter &painter, double x, double y, double w, double h);

// --- Cursor renderers ---
// Each renders into a pre-allocated QImage of size imageSize(logicalSize) x imageSize(logicalSize)
// The image is assumed to be filled with transparent (0x00000000).
// Hotspot is NOT set here; caller wraps with correct hotspot.

void renderKithArrow(QImage &img, int logicalSize);
void renderKithPointer(QImage &img, int logicalSize);
void renderKithText(QImage &img, int logicalSize);
void renderKithWait(QImage &img, int logicalSize);
void renderKithHelp(QImage &img, int logicalSize);
void renderKithMove(QImage &img, int logicalSize);
void renderKithResize(QImage &img, int logicalSize, double angleRadians);
void renderKithCrosshair(QImage &img, int logicalSize);
void renderKithNotAllowed(QImage &img, int logicalSize);
void renderKithHand(QImage &img, int logicalSize, bool closed);

// --- High-level: render and return QCursor with correct hotspot ---
// Hotspot fractions (logical coordinates / logicalSize):
//   Arrow, Help:     (0.16, 0.06)
//   Pointer:         (0.40, 0.06)
//   Text, Wait, Move, Crosshair, NotAllowed, Resize, Hand: (0.50, 0.50)

QCursor makeCursor(std::function<void(QImage&, int)> renderer, int logicalSize, double hx, double hy);

bool writeXcursorFile(const QString &path, const QList<int> &sizes,
                      const std::function<QImage(int)> &renderer, double hx, double hy);

} // namespace KithCursors

#endif // KITHCURSORS_H