// ScreenInfo — see ScreenInfo.h for the spec and the defect list.
// Rebuilt from oracle: decomp/ScreenInfo.c (ScreenInfo 0x18286e, width 0x182974, height 0x1829dc).
#include "ScreenInfo.h"

#include <QGuiApplication>
#include <QScreen>

ScreenInfo::ScreenInfo(QObject *parent) : QObject(parent)
{
    follow(QGuiApplication::primaryScreen());
    // S1
    if (auto *app = qobject_cast<QGuiApplication *>(QCoreApplication::instance()))
        connect(app, &QGuiApplication::primaryScreenChanged, this, [this](QScreen *s) { follow(s); });
}

void ScreenInfo::follow(QScreen *s)
{
    disconnect(m_geomConn);
    if (s)
        m_geomConn = connect(s, &QScreen::geometryChanged, this, &ScreenInfo::recheck);
    recheck();
}

void ScreenInfo::recheck()
{
    const QSize now(width(), height());
    if (now != m_last) {                               // S2
        const bool first = !m_last.isValid();
        m_last = now;
        if (!first)
            emit changed();
    }
}

int ScreenInfo::width() const
{
    QScreen *s = QGuiApplication::primaryScreen();
    return s ? s->geometry().width() : 0;
}

int ScreenInfo::height() const
{
    QScreen *s = QGuiApplication::primaryScreen();
    return s ? s->geometry().height() : 0;
}
