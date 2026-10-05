// Rebuilt from oracle: IconProvider::IconProvider and requestPixmap.
// Spec: image://icon/<name> resolves themed application icons for AppMenu.qml.
// DEFECTS FIXED vs oracle:
//  1. Reject path-like IDs; QML requests can resolve theme icon names only.
//  2. Respect requested dimensions and return deterministic empty pixmap dimensions on misses.

#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QQuickImageProvider>

class QPixmap;
class QSize;
class QString;

class IconProvider final : public QQuickImageProvider
{
public:
    IconProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif
