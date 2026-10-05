// Rebuilt from oracle: decomp/IconProvider.c.
// Spec: AppMenu.qml's image://icon/<desktop-icon-name> rows use the active icon theme.
// DEFECTS FIXED vs oracle:
//  1. Path traversal/file paths cannot escape the icon theme lookup.
//  2. Extension-bearing theme IDs get a name-only fallback instead of an unrelated suffix lookup.
//  3. Missing icons report the requested size and produce an empty pixmap for QML's error handling.

#include "IconProvider.h"

#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QFileInfo>

IconProvider::IconProvider()
    : QQuickImageProvider(QQmlImageProviderBase::Pixmap)
{
}

QPixmap IconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QSize target(64, 64);
    if (requestedSize.isValid() && requestedSize.width() > 0 && requestedSize.height() > 0)
        target = requestedSize;

    QString name = id.section(QLatin1Char('?'), 0, 0).trimmed();
    if (name.contains(QLatin1Char('/')) || name.contains(QLatin1Char('\\')) || name == QStringLiteral(".."))
        name.clear();

    QIcon icon;
    if (!name.isEmpty()) {
        icon = QIcon::fromTheme(name);
        if (icon.isNull()) {
            const QString stem = QFileInfo(name).completeBaseName();
            if (!stem.isEmpty() && stem != name)
                icon = QIcon::fromTheme(stem);
        }
    }

    QPixmap result;
    if (!icon.isNull())
        result = icon.pixmap(target, QIcon::Normal, QIcon::Off);
    if (size)
        *size = result.isNull() ? target : result.size();
    return result;
}
