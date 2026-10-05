// display_test — Settings_display.cpp: the xrandr parser on this machine's real `xrandr --query` (read-only)
// and on a rotated/two-output sample, rotation names (D3), night-light gains (D4), keep/revert (D2),
// night auto (D5). Every xrandr change is RECORDED, never run.
#include <QCoreApplication>
#include <QEventLoop>
#include <QProcess>
#include <QTimer>
#include <cstdio>

#define private public
#include "Lelan.h"
#include "Settings.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;
Settings::Settings(QObject *parent) : QObject(parent) {}
Settings::~Settings() = default;

static int g_fails = 0;
static void check(bool ok, const QString &what) { if (!ok) ++g_fails; std::printf("%s %s\n", ok ? "PASS" : "FAIL", qPrintable(what)); }
static void wait(int ms) { QEventLoop l; QTimer::singleShot(ms, &l, &QEventLoop::quit); l.exec(); }

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    std::setvbuf(stdout, nullptr, _IOLBF, 0);
    QStringList log;
    Settings s;
    s.runDetached = [&](const QString &p, const QStringList &a) { log << p + " " + a.join(' '); };

    // real machine, read-only
    QProcess q; q.start("xrandr", {"--query"}); q.waitForFinished();
    const QVariantList real = Settings::parseXrandr(QString::fromUtf8(q.readAllStandardOutput()), {});
    check(!real.isEmpty(), QString("real xrandr: %1 connected output(s)").arg(real.size()));
    if (!real.isEmpty()) {
        const QVariantMap d = real[0].toMap();
        std::printf("  real: n=%s pri=%d sub=%s hz=%.2f orient=%s modes=%lld rates=%s w=%d h=%d\n", qPrintable(d["n"].toString()),
                    d["pri"].toBool(), qPrintable(d["sub"].toString()), d["hz"].toDouble(), qPrintable(d["orient"].toString()),
                    qlonglong(d["modes"].toStringList().size()), qPrintable(QVariant(d["rates"]).toStringList().join(',')), d["w"].toInt(), d["h"].toInt());
        check(d["n"] == "eDP-1" && d["pri"].toBool() && d["sub"] == "1920x1200" && qAbs(d["hz"].toDouble() - 60.0) < 0.01
              && d["orient"] == "normal" && d["w"] == 128 && d["h"] == 80, "real: eDP-1 primary 1920x1200 @ 60 Hz, normal, thumbnail 128x80");
        check(d["modes"].toStringList().contains("1920x1080") && d["modeRates"].toMap()["1920x1080"].toList().size() == 2,
              "real: every mode listed with its own rates (1920x1080 has 2)");
    }
    const QString sample =
        "Screen 0: minimum 8 x 8, current 3120 x 1920, maximum 32767 x 32767\n"
        "eDP-1 connected 1200x1920+0+0 left (normal left inverted right x axis y axis) 309mm x 174mm\n"
        "   1920x1200     60.00*+  48.00  \n"
        "HDMI-1 disconnected (normal left inverted right x axis y axis)\n"
        "   1024x768      60.00  \n"
        "DP-2 connected primary 1920x1080+1200+0 (normal left inverted right x axis y axis) 527mm x 296mm\n"
        "   1920x1080     60.00 +  74.97*   50.00  \n"
        "   1280x720      60.00  \n";
    const QVariantList two = Settings::parseXrandr(sample, {{"DP-2", 125}});
    check(two.size() == 2, "sample: 2 connected outputs, the disconnected one's modes not mixed in");
    if (two.size() == 2) {
        check(two[0].toMap()["orient"] == "left" && two[0].toMap()["sub"] == "1920x1200", "rotated output: orient left, mode 1920x1200");
        check(two[1].toMap()["pri"].toBool() && qAbs(two[1].toMap()["hz"].toDouble() - 74.97) < 0.001 && two[1].toMap()["scale"] == 125
              && !two[1].toMap()["modes"].toStringList().contains("1024x768"), "DP-2: primary, 74.97 Hz current, scale 125, no HDMI-1 modes");
    }

    // D3 rotation, recorded
    s.m_displays = two;
    s.applyDisplayOrientation("DP-2", "left"); s.applyDisplayOrientation("DP-2", "inverted"); s.applyDisplayOrientation("DP-2", "right");
    s.applyDisplayOrientation("DP-2", "Portrait");
    check(log.filter("--rotate").join("|") == "xrandr --output DP-2 --rotate left|xrandr --output DP-2 --rotate inverted|"
                                               "xrandr --output DP-2 --rotate right|xrandr --output DP-2 --rotate left",
          "rotation: left/inverted/right from the tab reach xrandr (oracle: all became normal)");
    // D2 revert: the ORIGINAL state comes back after several pending changes
    int pending = -1;
    QObject::connect(&s, &Settings::displayChangePending, [&](int sec) { pending = sec; });
    log.clear(); s.revertDisplayChange();
    check(log.join("|") == "xrandr --output DP-2 --rotate normal" && pending == 0, "revert restores the state before the first change (normal)");
    log.clear(); s.applyDisplayMode("DP-2", "1280x720", 60);
    check(pending == 15 && log.join("|") == "xrandr --output DP-2 --mode 1280x720 --rate 60", "mode change: applied, 15 s to keep it");
    log.clear(); s.confirmDisplayChange(); wait(100);
    check(pending == 0 && log.isEmpty() && !s.m_displayRevertTimer->isActive(), "kept: nothing reverted");
    log.clear(); s.m_displayRevertTimer = nullptr; s.applyDisplayScale("DP-2", 150);
    s.m_displayRevertTimer->setInterval(300); s.m_displayRevertTimer->start(); wait(600);
    check(log.join("|") == "xrandr --output DP-2 --scale 0.6667x0.6667|xrandr --output DP-2 --scale 0.8000x0.8000",
          "scale 150 %, not kept: back to 125 % by itself (" + log.join("|") + ")");

    // D4 night light
    const auto g27 = Settings::nightGains(2700), g65 = Settings::nightGains(6500);
    std::printf("  2700 K gains %.3f:%.3f:%.3f\n", g27[0], g27[1], g27[2]);
    check(g65 == QVector<double>{1, 1, 1}, "6500 K = 1:1:1 (off-colour)");
    check(g27[0] == 1.0 && g27[1] < 0.8 && g27[1] > 0.6 && g27[2] < 0.5 && g27[1] > g27[2],
          "2700 K warm: red full, green reduced, blue reduced most (oracle: 1.0:1.0:0.65, yellow-green)");
    log.clear(); s.m_displays = two; s.m_nightWarmth = 2700; s.setNightLightOn(true);
    check(log.size() == 2 && log[0].startsWith("xrandr --output eDP-1 --gamma 1.000:0.") && log[1].contains("DP-2 --gamma"), "night light: gamma on every output");

    // D5 night auto follows the current day/night state at once
    Lelan lelan(nullptr, false);
    lelan.m_location = {{"night", true}};
    s.m_nightLightOn = false; s.m_nightLightAuto = false; s.m_lelan = &lelan;
    s.setNightLightAuto(true);
    check(s.m_nightLightOn, "automatic switched on at night: night light on at once (oracle: waited for sunrise/sunset)");
    lelan.m_location = {{"night", false}}; s.followDayNight();
    check(!s.m_nightLightOn, "day: off");

    std::printf("RESULT %s\n", g_fails ? "FAIL" : "PASS");
    return g_fails ? 1 : 0;
}
