// Rebuilt from oracle: decomp/Theme.c (26 functions).
// Spec: NCDE-ARCHITECTURE-DIGEST.md §2 and Filigree Phase 1 typography/accessibility rules.
// DEFECTS FIXED vs oracle:
//  1. Settings values are read through typed properties instead of unchecked dynamic reads.
//  2. Font properties use the active engine/settings values, with consistent fallbacks.
//  3. Scale and text metrics include the documented accessibility scale and refresh bindings.

#include "Theme.h"

#include "NCDEEngine.h"
#include "Settings.h"

#include <QtMath>
#include <cmath>

namespace
{
double positiveScale(double value)
{
    return std::isfinite(value) && value > 0.0 ? value : 1.0;
}

QString nonEmpty(const QString &value, const QString &fallback)
{
    return value.trimmed().isEmpty() ? fallback : value;
}
}

Theme::Theme(QObject *parent)
    : QObject(parent)
{
}

Theme::~Theme() = default;

void Theme::setEngine(NCDEEngine *engine)
{
    if (m_engine == engine)
        return;
    if (m_engine)
        disconnect(m_engine, nullptr, this, nullptr);
    m_engine = engine;
    if (m_engine)
        connect(m_engine, &NCDEEngine::changed, this, &Theme::changed);
    emit changed();
}

void Theme::setSettings(Settings *settings)
{
    if (m_settings == settings)
        return;
    if (m_settings)
        disconnect(m_settings, nullptr, this, nullptr);
    m_settings = settings;
    if (m_settings) {
        connect(m_settings, &Settings::fontChanged, this, &Theme::changed);
        connect(m_settings, &Settings::accessibilityChanged, this, &Theme::changed);
    }
    emit changed();
}

// Oracle Theme::scaled(int) (decomp/Theme.c 001a1a52): int(base * fontSizeScale * uiScale), a
// product <= 0 counts as 1. The rebuild had dropped fontSizeScale and uiScale here (engine size *
// accessibility only), so every theme.fontSmall/Medium/Large in the shell was ~20% smaller than the
// live LaPivot at the operator's fontSizeScale 1.25 (2026-10-01). accessibilityTextScale (a declared
// addition, 1.0 unless set) multiplies on top.
int Theme::orcScaled(int base) const
{
    if (!m_settings)
        return base;
    double k = m_settings->fontSizeScale() * m_settings->uiScale();
    if (k <= 0.0)
        k = 1.0;
    return int(k * positiveScale(m_settings->accessibilityTextScale()) * double(base));
}

QString Theme::fontFamily() const
{
    const QString fallback = m_engine ? m_engine->bodyFont() : QStringLiteral("Cormorant Garamond");
    return nonEmpty(m_settings ? m_settings->fontFamily() : QString(), fallback);
}

QString Theme::titleFont() const
{
    const QString fallback = fontFamily();
    return nonEmpty(m_engine ? m_engine->titleFont() : QString(), fallback);
}

double Theme::letterSpacing() const
{
    return m_settings ? m_settings->letterSpacing()
                      : (m_engine ? m_engine->letterSpacing() : 0.0);
}

int Theme::fontSmall() const
{
    return orcScaled(11);
}

int Theme::fontMedium() const
{
    return orcScaled(14);
}

int Theme::fontLarge() const
{
    return orcScaled(20);
}

QString Theme::textColor() const
{
    const QString configured = m_settings ? m_settings->textColor() : QString();
    if (!configured.trimmed().isEmpty())
        return configured;
    return m_engine ? m_engine->panelText().name(QColor::HexArgb) : QStringLiteral("#f4e9d2");
}

int Theme::textStyle() const
{
    if (!m_settings)
        return 0;
    if (m_settings->textOutlineEnabled())
        return 1;
    return m_settings->textShadowEnabled() ? 2 : 0;
}

QString Theme::textStyleColor() const
{
    if (m_settings && m_settings->textOutlineEnabled()
        && !m_settings->textOutlineColor().trimmed().isEmpty())
        return m_settings->textOutlineColor();
    return textShadowColor();
}

QString Theme::textShadowColor() const
{
    return m_settings ? m_settings->textShadowColor() : QString();
}

bool Theme::textShadowEnabled() const
{
    return m_settings && m_settings->textShadowEnabled();
}

double Theme::textShadowRadius() const
{
    return m_settings ? m_settings->textShadowRadius() : 0.0;
}

double Theme::textShadowOffsetX() const
{
    return m_settings ? m_settings->textShadowOffsetX() : 0.0;
}

double Theme::textShadowOffsetY() const
{
    return m_settings ? m_settings->textShadowOffsetY() : 0.0;
}

double Theme::scale(double base) const
{
    if (!std::isfinite(base))
        return 0.0;
    const double uiScale = m_settings ? m_settings->uiScale()
                                      : (m_engine ? m_engine->uiScale() : 1.0);
    const double fontScale = m_settings ? m_settings->fontSizeScale()
                                        : (m_engine ? m_engine->fontSizeScale() : 1.0);
    const double accessibilityScale = m_settings ? m_settings->accessibilityTextScale() : 1.0;
    return base * positiveScale(fontScale) * positiveScale(uiScale)
         * positiveScale(accessibilityScale);
}
