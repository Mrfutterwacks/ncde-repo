// Rebuilt from oracle: decomp/NcdeTheme.c (75 functions).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2, docs/gtk.md §1.
// DEFECTS FIXED vs oracle:
//  1. Removed unrelated system-service properties and invokables from this legacy colour class.
//  2. Palette input is validated and change-notified rather than being a no-op.
//  3. The superseded KickassGuard integration cannot expose a stale object.

#include "NcdeTheme.h"

#include <QColor>
#include <QMetaObject>

namespace
{
QColor colorValue(const QVariantMap &values, const QString &key, const char *fallback)
{
    const QColor color(values.value(key).toString());
    return color.isValid() ? color : QColor::fromString(QLatin1String(fallback));
}
}

NcdeTheme::NcdeTheme(QObject *parent)
    : QObject(parent)
{
}

NcdeTheme::~NcdeTheme() = default;

QColor NcdeTheme::accent() const { return colorValue(m_palette, QStringLiteral("accent"), "#6774bd"); }
QColor NcdeTheme::accentMuted() const { return colorValue(m_palette, QStringLiteral("accentMuted"), "#4e598f"); }
QColor NcdeTheme::border() const { return colorValue(m_palette, QStringLiteral("border"), "#495267"); }
bool NcdeTheme::darkMode() const { return m_palette.value(QStringLiteral("darkMode"), true).toBool(); }
int NcdeTheme::fontSize() const { return m_palette.value(QStringLiteral("fontSize"), 14).toInt(); }
QColor NcdeTheme::foreground() const { return colorValue(m_palette, QStringLiteral("foreground"), "#E6F1F2"); }
QColor NcdeTheme::gilt() const { return colorValue(m_palette, QStringLiteral("gilt"), "#b99c63"); }
QColor NcdeTheme::glow() const { return colorValue(m_palette, QStringLiteral("glow"), "#6774bd"); }
QColor NcdeTheme::panelBg() const { return colorValue(m_palette, QStringLiteral("panelBg"), "#263033"); }
QColor NcdeTheme::popupBg() const { return colorValue(m_palette, QStringLiteral("popupBg"), "#263033"); }
bool NcdeTheme::presetActive() const { return m_palette.value(QStringLiteral("presetActive"), false).toBool(); }
QColor NcdeTheme::surface() const { return colorValue(m_palette, QStringLiteral("surface"), "#1e2527"); }
QColor NcdeTheme::surfaceAlt() const { return colorValue(m_palette, QStringLiteral("surfaceAlt"), "#303a3d"); }
QColor NcdeTheme::surfaceGlass() const { return colorValue(m_palette, QStringLiteral("surfaceGlass"), "#263033"); }
QColor NcdeTheme::verd() const { return colorValue(m_palette, QStringLiteral("verd"), "#4f9183"); }
QString NcdeTheme::version() const { return QStringLiteral("1.0"); }
QString NcdeTheme::widgetStyle() const { return m_palette.value(QStringLiteral("widgetStyle"), QStringLiteral("NCDE")).toString(); }
QColor NcdeTheme::wine() const { return colorValue(m_palette, QStringLiteral("wine"), "#8b1e3f"); }
QObject *NcdeTheme::KickassGuard() const { return nullptr; }
int NcdeTheme::letterSpacing() const { return m_palette.value(QStringLiteral("letterSpacing"), 0).toInt(); }

void NcdeTheme::applyPalette(const QVariantMap &palette)
{
    static const QStringList colorKeys = {
        QStringLiteral("accent"), QStringLiteral("accentMuted"), QStringLiteral("border"),
        QStringLiteral("foreground"), QStringLiteral("gilt"), QStringLiteral("glow"),
        QStringLiteral("panelBg"), QStringLiteral("popupBg"), QStringLiteral("surface"),
        QStringLiteral("surfaceAlt"), QStringLiteral("surfaceGlass"), QStringLiteral("verd"),
        QStringLiteral("wine")
    };
    QVariantMap next = m_palette;
    for (const QString &key : colorKeys) {
        const auto it = palette.constFind(key);
        if (it == palette.cend())
            continue;
        const QColor color(it->toString());
        if (color.isValid())
            next.insert(key, color.name(QColor::HexArgb));
    }
    for (const QString &key : {QStringLiteral("darkMode"), QStringLiteral("presetActive"),
                               QStringLiteral("fontSize"), QStringLiteral("letterSpacing"),
                               QStringLiteral("widgetStyle")}) {
        const auto it = palette.constFind(key);
        if (it != palette.cend())
            next.insert(key, *it);
    }
    if (next == m_palette)
        return;
    m_palette = std::move(next);
    emit changed();
}

void NcdeTheme::setDarkMode(bool dark)
{
    if (darkMode() == dark)
        return;
    m_palette.insert(QStringLiteral("darkMode"), dark);
    emit changed();
}

void NcdeTheme::setAccentName(const QString &name)
{
    const QString clean = name.trimmed();
    if (clean.isEmpty() || m_palette.value(QStringLiteral("accentName")).toString() == clean)
        return;
    m_palette.insert(QStringLiteral("accentName"), clean);
    emit changed();
}

void NcdeTheme::setDarkModeLock(const QString &lock)
{
    const QString clean = lock.trimmed().toLower();
    if (clean != QStringLiteral("auto") && clean != QStringLiteral("light")
        && clean != QStringLiteral("dark"))
        return;
    if (m_palette.value(QStringLiteral("darkModeLock")).toString() == clean)
        return;
    m_palette.insert(QStringLiteral("darkModeLock"), clean);
    emit changed();
}

void NcdeTheme::setBaseColor(const QColor &base, const QColor &accentColor,
                             const QColor &panelTextColor)
{
    if (!base.isValid() || !accentColor.isValid() || !panelTextColor.isValid())
        return;
    applyPalette({{QStringLiteral("panelBg"), base},
                  {QStringLiteral("accent"), accentColor},
                  {QStringLiteral("foreground"), panelTextColor}});
}

void NcdeTheme::clearCustomBase()
{
    if (m_palette.isEmpty())
        return;
    m_palette.clear();
    emit changed();
}
