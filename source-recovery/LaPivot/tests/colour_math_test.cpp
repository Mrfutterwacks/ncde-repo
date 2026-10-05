#include "ColorMath.h"

#include <cmath>
#include <iostream>
#include <limits>

namespace
{
int failures = 0;

void check(bool ok, const char *message)
{
    std::cout << (ok ? "PASS " : "FAIL ") << message << '\n';
    if (!ok)
        ++failures;
}

bool close(double a, double b, double epsilon = 0.02)
{
    return std::abs(a - b) <= epsilon;
}
}

int main()
{
    using namespace ColorMath;

    const QColor white(Qt::white);
    const QColor black(Qt::black);
    const QColor roundTrip = labToRgb(rgbToLab(QColor("#7e4b2a")));
    check(std::abs(roundTrip.red() - 126) <= 1
          && std::abs(roundTrip.green() - 75) <= 1
          && std::abs(roundTrip.blue() - 42) <= 1,
          "sRGB to Lab and back preserves an in-gamut colour");
    check(close(contrastRatio(white, black), 21.0), "WCAG contrast ratio uses linear luminance");
    check(close(deltaE(rgbToLab(white), rgbToLab(white)), 0.0), "identical Lab colours have zero delta");
    check(mixLab(black, white, 0.0) == black && mixLab(black, white, 1.0) == white,
          "Lab mix endpoints preserve their inputs");
    check(shadeLab(QColor("#808080"), 1.5).lightness() > QColor("#808080").lightness(),
          "Lab shade increases lightness for a factor above one");
    check(lerpRgb(black, white, 0.5).red() >= 127, "sRGB interpolation reaches the midpoint");
    check(shadeRgb(QColor("#808080"), 1.5).red() > 128, "sRGB shade scales channels");
    check(isDark(QColor("#000000")) && !isDark(QColor("#ffffff")), "darkness follows relative luminance");
    check(hueDeg(QColor("#ff0000")) == 0.0 && close(chroma(QColor("#808080")), 0.0),
          "hue and chroma handle primary and achromatic colours");
    check(poeticName(0.0, 0.0) == QStringLiteral("Garnet Whisper")
          && poeticName(240.0, 1.0) == QStringLiteral("Iris Bloom"),
          "poetic names map hue and mood deterministically");
    check(!labToRgb({std::numeric_limits<double>::quiet_NaN(), 0.0, 0.0}).isValid(),
          "non-finite Lab input is rejected");

    return failures == 0 ? 0 : 1;
}
