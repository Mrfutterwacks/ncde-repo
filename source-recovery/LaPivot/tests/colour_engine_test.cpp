#include "NCDEEngine.h"
#include "NcdeTheme.h"
#include "ColorMath.h"

#include <QCoreApplication>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QImage>
#include <QThread>

#include <iostream>

namespace
{
int failures = 0;

void check(bool ok, const char *message)
{
    std::cout << (ok ? "PASS " : "FAIL ") << message << '\n';
    if (!ok)
        ++failures;
}

}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    const QString home = QDir::homePath();
    check(!home.isEmpty(), "test HOME is available");

    NCDEEngine engine;
    check(engine.presets().size() == 90, "engine exposes all 90 Iris Chroma presets");
    check(engine.metaObject()->indexOfProperty("wifiEnabled") < 0
          && engine.metaObject()->indexOfProperty("users") < 0
          && engine.metaObject()->indexOfMethod("connectNetwork(QString,QString)") < 0,
          "colour engine metaobject has no system-service forwarding surface");

    bool everyPresetAccessible = true;
    for (const QVariant &entry : engine.presets()) {
        engine.applyPreset(entry.toMap().value(QStringLiteral("id")).toString());
        everyPresetAccessible = everyPresetAccessible
            && ColorMath::contrastRatio(engine.ink(), engine.panelBg()) >= 7.0
            && ColorMath::contrastRatio(engine.ink(), engine.surface()) >= 7.0;
    }
    check(everyPresetAccessible, "all 90 curated palettes meet the 7:1 ink floor");

    int changedSignals = 0;
    QObject::connect(&engine, &NCDEEngine::changed, &app, [&] { ++changedSignals; });
    engine.applyPreset(QStringLiteral("mucha"));
    check(changedSignals == 1, "one palette selection emits one consolidated changed signal");
    const int afterSelection = changedSignals;
    engine.applyPreset(QStringLiteral("mucha"));
    check(changedSignals == afterSelection, "reselecting the same palette emits no redundant change");
    check(engine.accentName() == QStringLiteral("Mucha") && !engine.darkMode(),
          "preset selection updates palette identity and mode");
    check(ColorMath::contrastRatio(engine.ink(), engine.panelBg()) >= 7.0
          && ColorMath::contrastRatio(engine.ink(), engine.surface()) >= 7.0,
          "selected preset meets the documented 7:1 ink floor");

    for (int i = 0; i < 30; ++i)
        engine.setOverrideAccent(QStringLiteral("#%1%2%3").arg(i % 10).arg((i + 1) % 10).arg((i + 2) % 10));
    QElapsedTimer burstTimer;
    burstTimer.start();
    while (burstTimer.elapsed() < 60) {
        QCoreApplication::processEvents();
        QThread::msleep(5);
    }
    check(changedSignals == afterSelection + 1,
          "burst property updates coalesce into one recompute notification");

    // Design (operator 2026-10-01: "only users lock it", "that was a design choice"): a palette pick
    // sets that palette's own mode and never touches the lock; only the user's Solei-Lune tap sets it.
    engine.setDarkModeLock(QStringLiteral("dark"));
    check(engine.darkMode(), "user's dark lock turns dark mode on");
    engine.applyPreset(QStringLiteral("tiffany"));
    check(!engine.darkMode() && engine.darkModeLock() == QStringLiteral("dark"),
          "a palette pick sets the palette's own mode and leaves the user's lock alone");
    engine.setDarkModeLock(QStringLiteral("auto"));
    check(!engine.darkMode(), "automatic mode returns to the selected preset's mode");

    engine.applyPalette({{QStringLiteral("panelBg"), QColor("#777777")},
                         {QStringLiteral("surface"), QColor("#777777")},
                         {QStringLiteral("ink"), QColor("#808080")}});
    check(ColorMath::contrastRatio(engine.ink(), engine.panelBg()) >= 7.0
          && ColorMath::contrastRatio(engine.ink(), engine.surface()) >= 7.0,
          "custom/woven token override cannot bypass the ink contrast floor");

    const QString imagePath = QDir(home).filePath(QStringLiteral("test-wallpaper.png"));
    QImage image(8, 8, QImage::Format_ARGB32);
    image.fill(QColor("#2185d0"));
    check(image.save(imagePath), "test wallpaper is created inside scratch HOME");
    check(engine.sampleWallpaper(imagePath), "wallpaper sampling accepts a readable image");
    const QString inkBefore = engine.ink().name(), panelBefore = engine.panelBg().name();
    const QVariantMap preview = engine.previewWallpaper(imagePath);
    check(preview.value(QStringLiteral("valid")).toBool()
              && QColor(preview.value(QStringLiteral("text")).toString()).isValid()
              && QColor(preview.value(QStringLiteral("panelBg")).toString()).isValid()
              && QColor(preview.value(QStringLiteral("accent")).toString()).isValid()
              && QColor(preview.value(QStringLiteral("surface")).toString()).isValid(),
          "wallpaper preview carries the keys WallpapersTab reads (valid, panelBg, accent, surface, text)");
    check(engine.ink().name() == inkBefore && engine.panelBg().name() == panelBefore,
          "wallpaper preview leaves the live palette untouched");

    const QString themePath = QDir(home).filePath(QStringLiteral(".config/ncde/active-theme.json"));
    check(engine.saveTheme(themePath), "active theme saves atomically under scratch HOME");
    const QString savedAccent = engine.accentName();
    engine.setAccentName(QStringLiteral("Custom label"));
    check(engine.loadTheme(themePath) && engine.accentName() == savedAccent,
          "active-theme reload restores the saved palette selection");

    const QString gtkrcPath = QDir(home).filePath(QStringLiteral(".gtkrc-2.0"));
    // the bridge writes on its own thread, in order: wait for the LATEST palette, not just the file
    const QByteArray wantBg = "bg[NORMAL]      = \"" + engine.panelBg().name().toLatin1() + "\"";
    const QByteArray wantFg = "fg[NORMAL]      = \"" + engine.ink().name().toLatin1() + "\"";
    bool gtkrcMatches = false;
    QElapsedTimer gtkTimer;
    gtkTimer.start();
    while (!gtkrcMatches && gtkTimer.elapsed() < 4000) {
        QFile gtkrc(gtkrcPath);
        if (gtkrc.open(QIODevice::ReadOnly)) {
            const QByteArray rc = gtkrc.readAll();
            gtkrcMatches = rc.contains(wantBg) && rc.contains(wantFg);
        }
        if (!gtkrcMatches) {
            QCoreApplication::processEvents();
            QThread::msleep(20);
        }
    }
    check(gtkrcMatches, "GTK2 ~/.gtkrc-2.0 carries the live palette (panelBg ground, ink text)");

    NcdeTheme legacy;
    check(legacy.KickassGuard() == nullptr && legacy.accent().isValid(),
          "legacy colour facade has safe Vesper and palette fallbacks");
    const QColor before = legacy.accent();
    legacy.applyPalette({{QStringLiteral("accent"), QStringLiteral("#224466")}});
    check(legacy.accent() == QColor("#224466") && legacy.accent() != before,
          "legacy palette slot applies a changed colour");
    check(legacy.metaObject()->indexOfProperty("wifiEnabled") < 0
          && legacy.metaObject()->indexOfMethod("connectNetwork(QString,QString)") < 0,
          "legacy colour facade exposes no system forwarders");

    return failures == 0 ? 0 : 1;
}
