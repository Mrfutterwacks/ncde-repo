// Settings — the shell's colour choices that FiligreeTab saves: glass surfaces, widget styles, colour
// overrides, per-section text colours, saved Filigree palettes. (The colours themselves are computed by
// NCDEEngine; Settings only stores what the user chose.)
//
// Rebuilt from oracle: saveSurfaceGlass, saveWidgetStyleMap, resetWidgetStyle, saveColorOverrides,
// saveSectionColors, loadSectionColors, saveFiligreepalette.
//
// DEFECTS FIXED vs oracle:
//  T1 glass colours were saved as #rrggbb (QColor::HexRgb): a translucent tint or border lost its alpha on the
//     next load. Opaque colours are still written #rrggbb (same files as before); translucent ones #aarrggbb.
#include "Settings.h"
#include "Lelan.h"

static QString colourName(const QColor &c)
{
    return c.alpha() < 255 ? c.name(QColor::HexArgb) : c.name(QColor::HexRgb);   // T1
}

void Settings::saveSurfaceGlass(const QString &key, const QColor &tint, double shine, double glow, const QColor &border, const QColor &glowColor)
{
    if (key.isEmpty())
        return;
    QVariantMap all = readArea(QStringLiteral("glass-surfaces"));
    all.insert(key, QVariantMap{{QStringLiteral("tint"), colourName(tint)}, {QStringLiteral("shine"), shine},
                                {QStringLiteral("glow"), glow}, {QStringLiteral("border"), colourName(border)},
                                {QStringLiteral("glowColor"), colourName(glowColor)}});
    writeArea(QStringLiteral("glass-surfaces"), all);
}

void Settings::saveWidgetStyleMap(const QString &key, const QVariantMap &map)
{
    if (key.isEmpty())
        return;
    QVariantMap all = readArea(QStringLiteral("widget-styles"));
    all.insert(key, map);
    writeArea(QStringLiteral("widget-styles"), all);
}

void Settings::resetWidgetStyle(const QString &key)
{
    QVariantMap all = readArea(QStringLiteral("widget-styles"));
    if (all.remove(key))
        writeArea(QStringLiteral("widget-styles"), all);
}

void Settings::saveColorOverrides()
{
    QVariantMap m;
    if (!m_accentOverride.isEmpty()) m.insert(QStringLiteral("accentOverride"), m_accentOverride);
    if (!m_accentMutedOverride.isEmpty()) m.insert(QStringLiteral("accentMutedOverride"), m_accentMutedOverride);
    if (!m_glowOverride.isEmpty()) m.insert(QStringLiteral("glowOverride"), m_glowOverride);
    if (!m_borderOverride.isEmpty()) m.insert(QStringLiteral("borderOverride"), m_borderOverride);
    writeArea(QStringLiteral("color-overrides"), m);
}

void Settings::saveSectionColors()
{
    writeArea(QStringLiteral("section-colors"), {
        {QStringLiteral("topPanelTextColor"), m_topPanelTextColor}, {QStringLiteral("gliaTextColor"), m_gliaTextColor},
        {QStringLiteral("dockHoverTextColor"), m_dockHoverTextColor}, {QStringLiteral("leapFrogTextColor"), m_leapFrogTextColor}});
}

void Settings::loadSectionColors()
{
    const QVariantMap m = readArea(QStringLiteral("section-colors"));
    if (m.isEmpty())
        return;
    if (m.contains(QStringLiteral("topPanelTextColor"))) m_topPanelTextColor = m.value(QStringLiteral("topPanelTextColor")).toString();
    if (m.contains(QStringLiteral("gliaTextColor"))) m_gliaTextColor = m.value(QStringLiteral("gliaTextColor")).toString();
    if (m.contains(QStringLiteral("dockHoverTextColor"))) m_dockHoverTextColor = m.value(QStringLiteral("dockHoverTextColor")).toString();
    if (m.contains(QStringLiteral("leapFrogTextColor"))) m_leapFrogTextColor = m.value(QStringLiteral("leapFrogTextColor")).toString();
    emit settingsChanged();
}

void Settings::saveFiligreepalette(const QString &name, double hue, double sat, const QVariantList &palette)
{
    if (name.isEmpty())
        return;
    QVariantMap all = readArea(QStringLiteral("filigree-palettes"));
    all.insert(name, QVariantMap{{QStringLiteral("hue"), hue}, {QStringLiteral("sat"), sat}, {QStringLiteral("palette"), palette}});
    writeArea(QStringLiteral("filigree-palettes"), all);
}
