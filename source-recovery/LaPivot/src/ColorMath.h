// ColorMath — Colour math utilities (namespace, not QObject).
// Rebuilt from oracle: decomp/ColorMath.c (1 function: poeticName).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2, docs/gtk.md, docs/gtk-designer-answers.md.
// DEFECTS FIXED vs oracle:
//  1. poeticName() extracted from oracle's single massive function — now standalone, testable.
//  2. Added CIELAB conversion, deltaE, mix, shade, lerp, contrastRatio for engine use.
//  3. Poetic name table (12 hues + 5 moods) made constexpr for compile-time init.
//  4. No static guards (__cxa_guard_acquire) — use function-local static constexpr.
//  5. All math is pure, no side effects, no allocations in hot path.

#ifndef COLORMATH_H
#define COLORMATH_H

#include <QColor>
#include <QString>
#include <array>
#include <utility>
#include <cmath>

namespace ColorMath
{
    // CIELAB conversion (D65 illuminant)
    struct Lab {
        double L = 0.0;
        double a = 0.0;
        double b = 0.0;
    };

    // Convert sRGB QColor to CIELAB (D65)
    Lab rgbToLab(const QColor &c);
    // Convert CIELAB to sRGB QColor (clamped)
    QColor labToRgb(const Lab &lab);
    // CIE76 distance in Lab space.
    double deltaE(const Lab &a, const Lab &b);
    // Linear interpolation in Lab space
    Lab lerpLab(const Lab &a, const Lab &b, double t);
    // Mix two colours in Lab space (ratio 0..1 of b into a)
    QColor mixLab(const QColor &a, const QColor &b, double ratio);
    // Shade a colour (factor >1 = lighter, <1 = darker) in Lab L*
    QColor shadeLab(const QColor &c, double factor);
    // Lerp in sRGB (for compatibility with GTK's shade())
    QColor lerpRgb(const QColor &a, const QColor &b, double t);
    // Shade in sRGB (GTK-compatible)
    QColor shadeRgb(const QColor &c, double factor);
    // Contrast ratio (WCAG)
    double contrastRatio(const QColor &fg, const QColor &bg);
    // Luminance (relative, 0..1)
    double luminance(const QColor &c);
    // Is dark (luminance < 0.5)
    bool isDark(const QColor &c);

    // Poetic name from hue (degrees 0..360) and mood weight (0..1)
    // Returns "Hue Mood" e.g. "Gilt Whisper", "Iris Drift"
    QString poeticName(double hueDeg, double moodWeight);

    // Hue from QColor (degrees 0..360)
    double hueDeg(const QColor &c);
    // Chroma from QColor
    double chroma(const QColor &c);

    // Internal: poetic name tables
    namespace Detail {
        constexpr std::array<std::pair<int, const char*>, 12> kPoeticHues = {{
            {  0, "Garnet"    },
            { 30, "Amber"     },
            { 45, "Gilt"      },
            { 60, "Saffron"   },
            { 90, "Absinthe"  },
            {120, "Verdigris" },
            {150, "Eau-de-Nil"},
            {165, "Cerulean"  },
            {180, "Cyan Salon"},
            {210, "Lapis"     },
            {240, "Iris"      },
            {300, "Plum"      },
        }};
        constexpr std::array<const char*, 5> kPoeticMoods = {{
            "Whisper",
            "Drift",
            "Gleam",
            "Hush",
            "Bloom"
        }};
    }
}

#endif // COLORMATH_H