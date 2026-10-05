// ScreenInfo — the primary screen's size for QML (`window.width` / `window.height`, TilingManager.qml).
//
// Rebuilt from oracle: decomp/ScreenInfo.c (ctor, width, height, changed; 10 functions incl. moc/dtors).
// Spec: lepivot-gaps.md ("Le Pivot's `window` (ScreenInfo) ... `window` data"), TilingManager.qml consumers.
//
// DEFECTS FIXED vs oracle:
//  S1 the oracle connected QScreen::geometryChanged of the primary screen ONCE in the constructor. When the
//     primary screen changes (monitor plugged/unplugged, xrandr --primary) the old screen's signal kept the
//     connection and the new one had none: `changed` never fired again although width/height now read the new
//     screen. Now follows QGuiApplication::primaryScreenChanged and re-connects.
//  S2 `changed` was emitted on every geometryChanged even when the size did not change (a primary screen moved
//     in the virtual desktop): QML re-evaluated every TilingManager binding for nothing. Emitted on a size
//     change only.
#pragma once

#include <QMetaObject>
#include <QObject>
#include <QSize>

class QScreen;

class ScreenInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width NOTIFY changed)
    Q_PROPERTY(int height READ height NOTIFY changed)

public:
    explicit ScreenInfo(QObject *parent = nullptr);
    int width() const;
    int height() const;

signals:
    void changed();

private:
    void follow(QScreen *s);
    void recheck();
    QMetaObject::Connection m_geomConn;
    QSize m_last;
};
