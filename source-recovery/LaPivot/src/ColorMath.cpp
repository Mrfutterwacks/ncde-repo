// Rebuilt from oracle: decomp/ColorMath.c (poeticName).
// Spec: NCDE's palette and contrast contracts; pure colour math shared by the engine.
// DEFECTS FIXED vs oracle:
//  1. Extracted deterministic helpers make palette derivation and contrast testable.
//  2. Invalid colours and non-finite interpolation inputs are handled without propagating NaNs.

#include "ColorMath.h"

#include <algorithm>
#include <limits>

namespace ColorMath
{
namespace
{
double clamp01(double x)
{
    if (!std::isfinite(x))
        return 0.0;
    return std::clamp(x, 0.0, 1.0);
}

double srgbToLinear(double x)
{
    x = clamp01(x);
    return x <= 0.04045 ? x / 12.92 : std::pow((x + 0.055) / 1.055, 2.4);
}

double linearToSrgb(double x)
{
    x = std::clamp(x, 0.0, 1.0);
    return x <= 0.0031308 ? 12.92 * x : 1.055 * std::pow(x, 1.0 / 2.4) - 0.055;
}

double labF(double t)
{
    constexpr double delta = 6.0 / 29.0;
    constexpr double delta3 = delta * delta * delta;
    return t > delta3 ? std::cbrt(t) : t / (3.0 * delta * delta) + 4.0 / 29.0;
}

double labInvF(double t)
{
    constexpr double delta = 6.0 / 29.0;
    return t > delta ? t * t * t : 3.0 * delta * delta * (t - 4.0 / 29.0);
}
}

Lab rgbToLab(const QColor &color)
{
    if (!color.isValid())
        return {};

    const double r = srgbToLinear(color.redF());
    const double g = srgbToLinear(color.greenF());
    const double b = srgbToLinear(color.blueF());
    const double x = (0.4124564 * r + 0.3575761 * g + 0.1804375 * b) / 0.95047;
    const double y = 0.2126729 * r + 0.7151522 * g + 0.0721750 * b;
    const double z = (0.0193339 * r + 0.1191920 * g + 0.9503041 * b) / 1.08883;
    const double fx = labF(x);
    const double fy = labF(y);
    const double fz = labF(z);
    return {116.0 * fy - 16.0, 500.0 * (fx - fy), 200.0 * (fy - fz)};
}

QColor labToRgb(const Lab &lab)
{
    if (!std::isfinite(lab.L) || !std::isfinite(lab.a) || !std::isfinite(lab.b))
        return QColor();

    const double fy = (lab.L + 16.0) / 116.0;
    const double fx = fy + lab.a / 500.0;
    const double fz = fy - lab.b / 200.0;
    const double x = 0.95047 * labInvF(fx);
    const double y = labInvF(fy);
    const double z = 1.08883 * labInvF(fz);
    const double r = 3.2404542 * x - 1.5371385 * y - 0.4985314 * z;
    const double g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    const double b = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    return QColor::fromRgbF(clamp01(linearToSrgb(r)), clamp01(linearToSrgb(g)),
                            clamp01(linearToSrgb(b)));
}

double deltaE(const Lab &a, const Lab &b)
{
    const double dl = a.L - b.L;
    const double da = a.a - b.a;
    const double db = a.b - b.b;
    return std::sqrt(dl * dl + da * da + db * db);
}

Lab lerpLab(const Lab &a, const Lab &b, double t)
{
    t = clamp01(t);
    return {a.L + (b.L - a.L) * t, a.a + (b.a - a.a) * t, a.b + (b.b - a.b) * t};
}

QColor mixLab(const QColor &a, const QColor &b, double ratio)
{
    if (!a.isValid() || !b.isValid())
        return a.isValid() ? a : b;
    QColor mixed = labToRgb(lerpLab(rgbToLab(a), rgbToLab(b), ratio));
    mixed.setAlphaF(clamp01(a.alphaF() + (b.alphaF() - a.alphaF()) * clamp01(ratio)));
    return mixed;
}

QColor shadeLab(const QColor &color, double factor)
{
    if (!color.isValid() || !std::isfinite(factor))
        return color;
    Lab lab = rgbToLab(color);
    lab.L = std::clamp(lab.L * factor, 0.0, 100.0);
    QColor shaded = labToRgb(lab);
    shaded.setAlpha(color.alpha());
    return shaded;
}

QColor lerpRgb(const QColor &a, const QColor &b, double t)
{
    if (!a.isValid() || !b.isValid())
        return a.isValid() ? a : b;
    t = clamp01(t);
    return QColor::fromRgbF(clamp01(a.redF() + (b.redF() - a.redF()) * t),
                            clamp01(a.greenF() + (b.greenF() - a.greenF()) * t),
                            clamp01(a.blueF() + (b.blueF() - a.blueF()) * t),
                            clamp01(a.alphaF() + (b.alphaF() - a.alphaF()) * t));
}

QColor shadeRgb(const QColor &color, double factor)
{
    if (!color.isValid() || !std::isfinite(factor))
        return color;
    return QColor::fromRgbF(clamp01(color.redF() * factor),
                            clamp01(color.greenF() * factor),
                            clamp01(color.blueF() * factor), color.alphaF());
}

double luminance(const QColor &color)
{
    if (!color.isValid())
        return 0.0;
    return 0.2126 * srgbToLinear(color.redF())
         + 0.7152 * srgbToLinear(color.greenF())
         + 0.0722 * srgbToLinear(color.blueF());
}

double contrastRatio(const QColor &fg, const QColor &bg)
{
    const double l1 = luminance(fg);
    const double l2 = luminance(bg);
    const double lighter = std::max(l1, l2);
    const double darker = std::min(l1, l2);
    return (lighter + 0.05) / (darker + 0.05);
}

bool isDark(const QColor &color)
{
    return luminance(color) < 0.5;
}

QString poeticName(double hueDeg, double moodWeight)
{
    if (!std::isfinite(hueDeg))
        hueDeg = 0.0;
    hueDeg = std::fmod(hueDeg, 360.0);
    if (hueDeg < 0.0)
        hueDeg += 360.0;
    if (!std::isfinite(moodWeight))
        moodWeight = 0.0;

    const auto hue = std::min_element(Detail::kPoeticHues.cbegin(), Detail::kPoeticHues.cend(),
        [hueDeg](const auto &left, const auto &right) {
            const auto distance = [hueDeg](int candidate) {
                const double d = std::abs(hueDeg - candidate);
                return std::min(d, 360.0 - d);
            };
            return distance(left.first) < distance(right.first);
        });
    const auto moodIndex = static_cast<std::size_t>(
        std::clamp(std::lround(clamp01(moodWeight) * (Detail::kPoeticMoods.size() - 1)),
                   0L, static_cast<long>(Detail::kPoeticMoods.size() - 1)));
    return QString::fromLatin1(hue->second) + QLatin1Char(' ')
         + QString::fromLatin1(Detail::kPoeticMoods[moodIndex]);
}

double hueDeg(const QColor &color)
{
    if (!color.isValid() || color.hsvHueF() < 0.0)
        return 0.0;
    return color.hsvHueF() * 360.0;
}

double chroma(const QColor &color)
{
    const Lab lab = rgbToLab(color);
    return std::hypot(lab.a, lab.b);
}
}
