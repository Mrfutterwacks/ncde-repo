// Settings — the shell's type and text treatment (FontsTab, FiligreeTab text colour/outline/shadow):
// ~/.config/ncde/fonts.json. The shell's theme reads these properties; applying = fontChanged.
//
// Rebuilt from oracle: loadFonts (+4 typed lambdas), saveFontsJson, applyFontSettings, saveFontSettings,
// saveTextColor. The properties themselves are in Settings_props.cpp.
//
// DEFECTS FIXED vs oracle:
//  F1 values from fonts.json were used as they came: a damaged or hand-edited file with uiScale 0 or
//     fontSizeScale 40 collapsed or exploded the whole shell at login. Loaded values are clamped to what
//     FontsTab can set (size 0.6-1.8, UI 0.6-2.0, spacing -1.5..8 px, line 0.8-2.5, weight 100-900) and
//     sane bounds for the text effects.
#include "Settings.h"
#include "Lelan.h"

void Settings::loadFonts()
{
    const QVariantMap m = readArea(QStringLiteral("fonts"));
    if (m.isEmpty())
        return;
    auto str = [&](const char *k, QString &v) { if (m.contains(QLatin1String(k))) v = m.value(QLatin1String(k)).toString(); };
    auto num = [&](const char *k, double &v, double lo, double hi) {
        if (m.contains(QLatin1String(k))) v = qBound(lo, m.value(QLatin1String(k)).toDouble(), hi); };   // F1
    auto flag = [&](const char *k, bool &v) { if (m.contains(QLatin1String(k))) v = m.value(QLatin1String(k)).toBool(); };
    str("fontFamily", m_fontFamily);
    if (m.contains(QStringLiteral("fontWeight")))
        m_fontWeight = qBound(100, m.value(QStringLiteral("fontWeight")).toInt(), 900);
    flag("fontItalic", m_fontItalic);
    num("fontSizeScale", m_fontSizeScale, 0.6, 1.8);
    num("letterSpacing", m_letterSpacing, -1.5, 8.0);
    num("lineHeight", m_lineHeight, 0.8, 2.5);
    num("uiScale", m_uiScale, 0.6, 2.0);
    str("textColor", m_textColor);
    flag("textOutlineEnabled", m_textOutlineEnabled);
    str("textOutlineColor", m_textOutlineColor);
    num("textOutlineWidth", m_textOutlineWidth, 0.0, 10.0);
    flag("textShadowEnabled", m_textShadowEnabled);
    str("textShadowColor", m_textShadowColor);
    num("textShadowOffsetX", m_textShadowOffsetX, -32.0, 32.0);
    num("textShadowOffsetY", m_textShadowOffsetY, -32.0, 32.0);
    num("textShadowRadius", m_textShadowRadius, 0.0, 32.0);
    if (m_fontFamily.trimmed().isEmpty())
        m_fontFamily = QStringLiteral("Cormorant Garamond");
    emit fontChanged();
}

void Settings::saveFontsJson()
{
    writeArea(QStringLiteral("fonts"), {
        {QStringLiteral("fontFamily"), m_fontFamily}, {QStringLiteral("fontWeight"), m_fontWeight},
        {QStringLiteral("fontItalic"), m_fontItalic}, {QStringLiteral("fontSizeScale"), m_fontSizeScale},
        {QStringLiteral("letterSpacing"), m_letterSpacing}, {QStringLiteral("lineHeight"), m_lineHeight},
        {QStringLiteral("uiScale"), m_uiScale}, {QStringLiteral("textColor"), m_textColor},
        {QStringLiteral("textOutlineEnabled"), m_textOutlineEnabled}, {QStringLiteral("textOutlineColor"), m_textOutlineColor},
        {QStringLiteral("textOutlineWidth"), m_textOutlineWidth}, {QStringLiteral("textShadowEnabled"), m_textShadowEnabled},
        {QStringLiteral("textShadowColor"), m_textShadowColor}, {QStringLiteral("textShadowOffsetX"), m_textShadowOffsetX},
        {QStringLiteral("textShadowOffsetY"), m_textShadowOffsetY}, {QStringLiteral("textShadowRadius"), m_textShadowRadius}});
}

void Settings::applyFontSettings() { emit fontChanged(); }
void Settings::saveFontSettings() { saveFontsJson(); }
void Settings::saveTextColor() { saveFontsJson(); }
