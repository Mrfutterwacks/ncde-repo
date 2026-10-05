// Rebuilt from oracle: decomp/CursorManager.c and writeXcursorFile in decomp/_global.c.
// Spec: Kithglass Xcursor theme; Settings_input.cpp publishes Kith size 16..128.
// DEFECTS FIXED vs oracle:
//  1. Root cursor installs reuse the connection-owned ARGB format and replace old cursors safely.
//  (2026-10-01) writeXcursorTheme/writeXcursorFile are back to the oracle exactly: the requested sizes
//     only (main passes 24/32/48/64), absolute alias symlinks, index.theme + cursor.theme. The earlier
//     "113 sizes + manifest + skip unchanged" rewrite never produced a single file (see KithCursors.cpp
//     writeXcursorFile) -> no XCURSOR_PATH, the Kith cursor jumped size/colour between apps and desktop.
//  4. Unknown cursor names and Qt custom cursor shapes are left safe instead of becoming black.

#include "CursorManager.h"
#include "KithCursors.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QPainter>
#include <QDataStream>
#include <QDebug>
#include <QtMath>
#include <xcb/xcb.h>
#include <xcb/render.h>
#include <xcb/xcb_renderutil.h>

#include <algorithm>
#include <cmath>

namespace {

QImage renderImage(const std::function<void(QImage &, int)> &renderer, int size)
{
    QImage image(KithCursors::imageSize(size), KithCursors::imageSize(size),
                 QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    renderer(image, size);
    return image;
}

} // namespace

const QList<CursorManager::Shape> &CursorManager::shapes()
{
    static const QList<Shape> value = {
        {Qt::ArrowCursor, QStringLiteral("left_ptr"), KithCursors::renderKithArrow, 0.16, 0.06},
        {Qt::PointingHandCursor, QStringLiteral("hand2"), KithCursors::renderKithPointer, 0.40, 0.06},
        {Qt::IBeamCursor, QStringLiteral("xterm"), KithCursors::renderKithText, 0.50, 0.50},
        {Qt::WaitCursor, QStringLiteral("watch"), KithCursors::renderKithWait, 0.50, 0.50},
        {Qt::WhatsThisCursor, QStringLiteral("question_arrow"), KithCursors::renderKithHelp, 0.16, 0.06},
        {Qt::SizeAllCursor, QStringLiteral("fleur"), KithCursors::renderKithMove, 0.50, 0.50},
        {Qt::SizeVerCursor, QStringLiteral("sb_v_double_arrow"),
         [](QImage &image, int size) { KithCursors::renderKithResize(image, size, 0.0); }, 0.50, 0.50},
        {Qt::SizeHorCursor, QStringLiteral("sb_h_double_arrow"),
         [](QImage &image, int size) { KithCursors::renderKithResize(image, size, 1.5707963267948966); }, 0.50, 0.50},
        {Qt::SizeBDiagCursor, QStringLiteral("fd_double_arrow"),
         [](QImage &image, int size) { KithCursors::renderKithResize(image, size, -0.7853981633974483); }, 0.50, 0.50},
        {Qt::SizeFDiagCursor, QStringLiteral("bd_double_arrow"),
         [](QImage &image, int size) { KithCursors::renderKithResize(image, size, 0.7853981633974483); }, 0.50, 0.50},
        {Qt::CrossCursor, QStringLiteral("crosshair"), KithCursors::renderKithCrosshair, 0.50, 0.50},
        {Qt::ForbiddenCursor, QStringLiteral("not-allowed"), KithCursors::renderKithNotAllowed, 0.50, 0.50},
        {Qt::OpenHandCursor, QStringLiteral("grab"),
         [](QImage &image, int size) { KithCursors::renderKithHand(image, size, false); }, 0.50, 0.50},
        {Qt::ClosedHandCursor, QStringLiteral("grabbing"),
         [](QImage &image, int size) { KithCursors::renderKithHand(image, size, true); }, 0.50, 0.50}
    };
    return value;
}

const QHash<QString, QString> &CursorManager::cursorAliases()
{
    static const QHash<QString, QString> value = {
        {QStringLiteral("default"), QStringLiteral("left_ptr")},
        {QStringLiteral("arrow"), QStringLiteral("left_ptr")},
        {QStringLiteral("top_left_arrow"), QStringLiteral("left_ptr")},
        {QStringLiteral("left_arrow"), QStringLiteral("left_ptr")},
        {QStringLiteral("draft_large"), QStringLiteral("left_ptr")},
        {QStringLiteral("draft_small"), QStringLiteral("left_ptr")},
        {QStringLiteral("context-menu"), QStringLiteral("left_ptr")},
        {QStringLiteral("copy"), QStringLiteral("left_ptr")},
        {QStringLiteral("alias"), QStringLiteral("left_ptr")},
        {QStringLiteral("pointer"), QStringLiteral("hand2")},
        {QStringLiteral("hand"), QStringLiteral("hand2")},
        {QStringLiteral("hand1"), QStringLiteral("hand2")},
        {QStringLiteral("pointing_hand"), QStringLiteral("hand2")},
        {QStringLiteral("9d800788f1b08800ae810202380a0822"), QStringLiteral("hand2")},
        {QStringLiteral("e29285e634086352946a0e7090d73106"), QStringLiteral("hand2")},
        {QStringLiteral("text"), QStringLiteral("xterm")},
        {QStringLiteral("ibeam"), QStringLiteral("xterm")},
        {QStringLiteral("vertical-text"), QStringLiteral("xterm")},
        {QStringLiteral("xterm_i"), QStringLiteral("xterm")},
        {QStringLiteral("wait"), QStringLiteral("watch")},
        {QStringLiteral("progress"), QStringLiteral("watch")},
        {QStringLiteral("half-busy"), QStringLiteral("watch")},
        {QStringLiteral("clock"), QStringLiteral("watch")},
        {QStringLiteral("left_ptr_watch"), QStringLiteral("watch")},
        {QStringLiteral("08e8e1c95fe2fc01f976f1e063a24ccd"), QStringLiteral("watch")},
        {QStringLiteral("help"), QStringLiteral("question_arrow")},
        {QStringLiteral("whats_this"), QStringLiteral("question_arrow")},
        {QStringLiteral("dnd-ask"), QStringLiteral("question_arrow")},
        {QStringLiteral("move"), QStringLiteral("fleur")},
        {QStringLiteral("all-scroll"), QStringLiteral("fleur")},
        {QStringLiteral("size_all"), QStringLiteral("fleur")},
        {QStringLiteral("ns-resize"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("size_ver"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("v_double_arrow"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("n-resize"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("s-resize"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("top_side"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("bottom_side"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("row-resize"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("double_arrow"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("00008160000006810000408080010102"), QStringLiteral("sb_v_double_arrow")},
        {QStringLiteral("ew-resize"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("size_hor"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("h_double_arrow"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("e-resize"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("w-resize"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("left_side"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("right_side"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("col-resize"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("028006030e0e7ebffc7f7070c0600140"), QStringLiteral("sb_h_double_arrow")},
        {QStringLiteral("nesw-resize"), QStringLiteral("fd_double_arrow")},
        {QStringLiteral("size_bdiag"), QStringLiteral("fd_double_arrow")},
        {QStringLiteral("ne-resize"), QStringLiteral("fd_double_arrow")},
        {QStringLiteral("sw-resize"), QStringLiteral("fd_double_arrow")},
        {QStringLiteral("top_right_corner"), QStringLiteral("fd_double_arrow")},
        {QStringLiteral("bottom_left_corner"), QStringLiteral("fd_double_arrow")},
        {QStringLiteral("fcf1c3c7cd4491d801f1e1c78f100000"), QStringLiteral("fd_double_arrow")},
        {QStringLiteral("nwse-resize"), QStringLiteral("bd_double_arrow")},
        {QStringLiteral("size_fdiag"), QStringLiteral("bd_double_arrow")},
        {QStringLiteral("nw-resize"), QStringLiteral("bd_double_arrow")},
        {QStringLiteral("se-resize"), QStringLiteral("bd_double_arrow")},
        {QStringLiteral("top_left_corner"), QStringLiteral("bd_double_arrow")},
        {QStringLiteral("bottom_right_corner"), QStringLiteral("bd_double_arrow")},
        {QStringLiteral("c7088f0f3e6c8088236ef8e1e3e70000"), QStringLiteral("bd_double_arrow")},
        {QStringLiteral("cross"), QStringLiteral("crosshair")},
        {QStringLiteral("tcross"), QStringLiteral("crosshair")},
        {QStringLiteral("forbidden"), QStringLiteral("not-allowed")},
        {QStringLiteral("no-drop"), QStringLiteral("not-allowed")},
        {QStringLiteral("circle"), QStringLiteral("not-allowed")},
        {QStringLiteral("crossed_circle"), QStringLiteral("not-allowed")},
        {QStringLiteral("openhand"), QStringLiteral("grab")},
        {QStringLiteral("closedhand"), QStringLiteral("grabbing")},
        {QStringLiteral("dnd-move"), QStringLiteral("grabbing")}
    };
    return value;
}

CursorManager::CursorManager(QObject *parent)
    : QObject(parent)
{
    loadAll(m_cursorSize);
}

CursorManager::~CursorManager()
{
    for (const QPointer<QWindow> &window : std::as_const(m_windows)) {
        if (window)
            window->removeEventFilter(this);
    }
}

QCursor CursorManager::renderCursor(const Shape &shape, int size) const
{
    return KithCursors::makeCursor(shape.renderer, size, shape.hotX, shape.hotY);
}

QCursor CursorManager::loadCursor(const QString &name, int size)
{
    QString canonical = name;
    if (cursorAliases().contains(canonical))
        canonical = cursorAliases().value(canonical);
    for (const Shape &shape : shapes()) {
        if (shape.fileName == canonical)
            return renderCursor(shape, size);
    }
    return renderCursor(shapes().first(), size);
}

void CursorManager::loadAll(int size)
{
    m_cursorSize = qBound(16, size, 128);
    m_cursors.clear();
    for (const Shape &shape : shapes())
        m_cursors.insert(shape.qtShape, renderCursor(shape, m_cursorSize));
}

void CursorManager::setTheme(const QString &theme, int size)
{
    m_themeName = theme.trimmed().isEmpty() ? QStringLiteral("Kith") : theme.trimmed();
    m_reloading = true;
    loadAll(size);
    applyToWindows();
    m_reloading = false;
}

void CursorManager::reload(int size)
{
    setTheme(m_themeName, size);
}

void CursorManager::install(QWindow *window)
{
    if (!window)
        return;
    for (const QPointer<QWindow> &existing : std::as_const(m_windows)) {
        if (existing == window) {
            window->setCursor(m_cursors.value(window->cursor().shape(), m_cursors.value(Qt::ArrowCursor)));
            return;
        }
    }
    m_windows.append(QPointer<QWindow>(window));
    window->installEventFilter(this);
    m_reloading = true;
    window->setCursor(m_cursors.value(window->cursor().shape(), m_cursors.value(Qt::ArrowCursor)));
    m_reloading = false;
}

bool CursorManager::eventFilter(QObject *watched, QEvent *event)
{
    if (!m_reloading && event && event->type() == QEvent::CursorChange) {
        auto *window = qobject_cast<QWindow *>(watched);
        if (window && m_cursors.contains(window->cursor().shape())) {
            m_reloading = true;
            window->setCursor(m_cursors.value(window->cursor().shape()));
            m_reloading = false;
        }
    }
    return QObject::eventFilter(watched, event);
}

void CursorManager::applyToWindows()
{
    auto it = m_windows.begin();
    while (it != m_windows.end()) {
        if (!*it) {
            it = m_windows.erase(it);
            continue;
        }
        QWindow *window = it->data();
        window->setCursor(m_cursors.value(window->cursor().shape(), m_cursors.value(Qt::ArrowCursor)));
        ++it;
    }
}

void CursorManager::installAsRootCursor(xcb_connection_t *connection, uint32_t root, int size)
{
    if (!connection) {
        qWarning("CursorManager::installAsRootCursor: no XCB connection");
        return;
    }
    size = qBound(16, size, 128);
    if (m_rootConnection == connection && m_rootWindow == root && m_rootSize == size && m_rootCursor)
        return;

    if (m_formatConnection != connection || !m_argbFormat) {
        const xcb_render_query_pict_formats_reply_t *formats = xcb_render_util_query_formats(connection);
        if (!formats) {
            qWarning("CursorManager::installAsRootCursor: XRender formats unavailable");
            return;
        }
        const xcb_render_pictforminfo_t *format =
            xcb_render_util_find_standard_format(formats, XCB_PICT_STANDARD_ARGB_32);
        if (!format) {
            qWarning("CursorManager::installAsRootCursor: ARGB32 format unavailable");
            return;
        }
        m_argbFormat = format->id;
        m_formatConnection = connection;
    }
    if (!m_argbFormat)
        return;

    const Shape &arrow = shapes().first();
    const QImage image = renderImage(arrow.renderer, size).convertToFormat(QImage::Format_ARGB32_Premultiplied);
    if (image.isNull() || image.width() > 0xffff || image.height() > 0xffff)
        return;

    const xcb_pixmap_t pixmap = xcb_generate_id(connection);
    const xcb_gcontext_t gc = xcb_generate_id(connection);
    xcb_create_pixmap(connection, 32, pixmap, root, quint16(image.width()), quint16(image.height()));
    xcb_create_gc(connection, gc, pixmap, 0, nullptr);
    const uint32_t bytes = uint32_t(image.width() * image.height() * 4);
    xcb_put_image(connection, XCB_IMAGE_FORMAT_Z_PIXMAP, pixmap, gc, quint16(image.width()),
                  quint16(image.height()), 0, 0, 0, 32, bytes, image.constBits());
    xcb_free_gc(connection, gc);

    const xcb_render_picture_t picture = xcb_generate_id(connection);
    xcb_render_create_picture(connection, picture, pixmap, m_argbFormat, 0, nullptr);
    xcb_free_pixmap(connection, pixmap);
    const xcb_cursor_t cursor = xcb_generate_id(connection);
    const QPoint hot = KithCursors::hotspotImage(size, arrow.hotX, arrow.hotY);
    xcb_render_create_cursor(connection, cursor, picture, quint16(hot.x()), quint16(hot.y()));
    xcb_render_free_picture(connection, picture);
    xcb_change_window_attributes(connection, root, XCB_CW_CURSOR, &cursor);
    xcb_flush(connection);

    if (m_rootConnection == connection && m_rootCursor)
        xcb_free_cursor(connection, m_rootCursor);
    m_rootConnection = connection;
    m_rootWindow = root;
    m_rootCursor = cursor;
    m_rootSize = size;
}

// Oracle writeXcursorTheme (decomp/CursorManager.c): <dir>/Kith/cursors, one Xcursor file per shape at the
// requested sizes, every alias an absolute symlink to its shape file, then index.theme + cursor.theme.
// A failing shape or alias is logged and makes the result false; the remaining shapes are still written.
bool CursorManager::writeXcursorTheme(const QString &themeDir, const QList<int> &requestedSizes)
{
    const QString theme = themeDir + QStringLiteral("/Kith");
    const QString cursorDir = theme + QStringLiteral("/cursors");
    if (!QDir().mkpath(cursorDir)) {
        qWarning() << "CursorManager: cannot create cursor theme dir" << cursorDir;
        return false;
    }
    bool ok = true;
    for (const Shape &shape : shapes()) {
        const QString path = cursorDir + QLatin1Char('/') + shape.fileName;
        const auto renderer = [shape](int size) { return renderImage(shape.renderer, size); };
        if (!KithCursors::writeXcursorFile(path, requestedSizes, renderer, shape.hotX, shape.hotY)) {
            ok = false;
            continue;
        }
        for (auto it = cursorAliases().cbegin(); it != cursorAliases().cend(); ++it) {
            if (it.value() != shape.fileName)
                continue;
            const QString aliasPath = cursorDir + QLatin1Char('/') + it.key();
            QFile::remove(aliasPath);
            if (!QFile(path).link(aliasPath)) {
                qWarning() << "CursorManager: cannot link cursor alias" << aliasPath;
                ok = false;
            }
        }
    }
    const QList<QPair<QString, QByteArray>> files = {
        {QStringLiteral("index.theme"),
         QByteArrayLiteral("[Icon Theme]\nName=Kith\nComment=NCDE stained-glass cursors, generated per-session from procedural art\n")},
        {QStringLiteral("cursor.theme"), QByteArrayLiteral("[Icon Theme]\nInherits=Kith\n")},
    };
    for (const auto &[name, bytes] : files) {
        QFile file(theme + QLatin1Char('/') + name);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate) || file.write(bytes) != bytes.size()) {
            qWarning() << "CursorManager: cannot write" << file.fileName() << file.errorString();
            ok = false;
        }
    }
    return ok;
}
