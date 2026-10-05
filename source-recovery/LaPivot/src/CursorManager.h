// Rebuilt from oracle: CursorManager::CursorManager, loadCursor, loadAll, setTheme,
// reload, install, eventFilter, installAsRootCursor, writeXcursorTheme.
// Spec: NCDE-ARCHITECTURE-DIGEST.md §2; PRODUCTION-PUNCHLIST.md §0.8/§0.11/§0.12(c);
// gtk.md for Kith propagation through xrdb, GTK and gsettings.
// DEFECTS FIXED vs oracle:
//  1. Keep the XRender format cached per XCB connection; do not free libxcb-render-util's
//     connection-owned formats reply (repeated root installs no longer corrupt it).
//  2. Reuse identical cursor files and skip rendering when the complete Kith theme is unchanged.
//  3. Derive file/root hotspots from the image-space hot spot plus the 6px art inset.
//  4. Release temporary X pixmap/GC/picture resources and replace old root cursor resources.
//  5. Write variants for every supported Settings size (16..128), not only main()'s initial list.

#ifndef CURSORMANAGER_H
#define CURSORMANAGER_H

#include <QObject>
#include <QCursor>
#include <QHash>
#include <QList>
#include <QPointer>
#include <QSet>
#include <QString>
#include <QWindow>
#include <functional>
#include <cstdint>

struct xcb_connection_t;
class QImage;

class CursorManager final : public QObject
{
    Q_OBJECT

public:
    explicit CursorManager(QObject *parent = nullptr);
    ~CursorManager() override;

    QCursor loadCursor(const QString &name, int size);
    void loadAll(int size);
    void setTheme(const QString &theme, int size);
    void reload(int size);
    void install(QWindow *window);
    bool eventFilter(QObject *watched, QEvent *event) override;
    void installAsRootCursor(xcb_connection_t *connection, uint32_t root, int size);
    bool writeXcursorTheme(const QString &themeDir, const QList<int> &sizes);

private:
    struct Shape {
        Qt::CursorShape qtShape;
        QString fileName;
        std::function<void(QImage &, int)> renderer;
        double hotX;
        double hotY;
    };

    static const QList<Shape> &shapes();
    static const QHash<QString, QString> &cursorAliases();
    QCursor renderCursor(const Shape &shape, int size) const;
    void applyToWindows();

    QString m_themeName = QStringLiteral("Kith");
    int m_cursorSize = 32;
    QHash<Qt::CursorShape, QCursor> m_cursors;
    QList<QPointer<QWindow>> m_windows;
    bool m_reloading = false;

    xcb_connection_t *m_formatConnection = nullptr;
    uint32_t m_argbFormat = 0;
    xcb_connection_t *m_rootConnection = nullptr;
    uint32_t m_rootWindow = 0;
    uint32_t m_rootCursor = 0;
    int m_rootSize = 0;
};

#endif
