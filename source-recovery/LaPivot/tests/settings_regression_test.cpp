#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlPropertyMap>
#include <QQuickView>
#include <QSaveFile>
#include <QSignalSpy>
#include <QTest>
#include <algorithm>
#include <cstdio>
#include <functional>

#define private public
#include "Lelan.h"
#include "Settings.h"
#undef private

static QStringList recordedCommands;
static QStringList recordedQueries;
static int failures = 0;

Settings::Settings(QObject *parent) : QObject(parent)
{
    m_configBase = QDir::homePath() + QStringLiteral("/.config/ncde/");
    m_assetBase = QDir::homePath() + QStringLiteral("/assets/");
    runDetached = [this](const QString &program, const QStringList &args) {
        recordedCommands << program + QLatin1Char(' ') + args.join(QLatin1Char(' '));
    };
    runQuery = [this](const QString &program, const QStringList &args, std::function<void(const QString &)> done) {
        recordedQueries << program + QLatin1Char(' ') + args.join(QLatin1Char(' '));
        if (program == QLatin1String("xinput") && args == QStringList{QStringLiteral("list")})
            done(QStringLiteral("  Test mouse id=12 [slave pointer (2)]\n"));
        else
            done(QStringLiteral("libinput Accel Speed (123):\t0.000000\n"));
    };
    runInput = [this](const QString &program, const QStringList &args, const QByteArray &) {
        recordedCommands << program + QLatin1Char(' ') + args.join(QLatin1Char(' ')) + QStringLiteral(" <recorded input>");
    };
}

Settings::~Settings() = default;

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;
void Lelan::setReduceMotionPref(bool) {}

static void check(bool ok, const char *message)
{
    std::printf("%s %s\n", ok ? "PASS" : "FAIL", message);
    if (!ok)
        ++failures;
}

static bool writeFile(const QString &path, const QByteArray &data)
{
    QDir().mkpath(QFileInfo(path).absolutePath());
    QFile f(path);
    return f.open(QIODevice::WriteOnly | QIODevice::Truncate) && f.write(data) == data.size();
}

static bool waitForWallpaper(Settings &settings, const QString &path, int timeoutMs)
{
    for (int elapsed = 0; elapsed < timeoutMs; elapsed += 50) {
        QCoreApplication::processEvents();
        if (settings.getWallpaper() == path)
            return true;
        QTest::qWait(50);
    }
    return settings.getWallpaper() == path;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Settings settings;

    const QColor tint(0x12, 0x34, 0x56, 0x4d);
    settings.saveSurfaceGlass(QStringLiteral("test-surface"), tint, 0.2, 0.3,
                              QColor(1, 2, 3, 0x80), QColor(4, 5, 6, 0x20));
    const QVariantMap surface = Lelan::readConfig(QStringLiteral("glass-surfaces"))
                                    .value(QStringLiteral("test-surface")).toMap();
    const QColor restored(surface.value(QStringLiteral("tint")).toString());
    check(surface.value(QStringLiteral("tint")).toString() == QLatin1String("#4d123456")
              && restored.alpha() == 0x4d && restored.red() == 0x12,
          "translucent glass tint persists and QColor restores its alpha");

    settings.setFitMode(QStringLiteral("tile"));
    check(settings.fitMode() == QLatin1String("tile")
              && Lelan::readConfig(QStringLiteral("wallpaper-slideshow")).value(QStringLiteral("fitMode")).toString()
                     == QLatin1String("tile"),
          "fit mode is stored, saved, and round-trips from the wallpaper config");
    settings.setFitMode(QStringLiteral("invalid"));
    check(settings.fitMode() == QLatin1String("fill"), "invalid fit mode falls back to Fill");

    const QString home = QDir::homePath();
    const QString gallery = home + QStringLiteral("/Pictures/wallpapers");
    const QString bundled = home + QStringLiteral("/assets");
    const QString siblingDir = home + QStringLiteral("/Pictures/wallpapers-old");
    const QString galleryOne = gallery + QStringLiteral("/01.png");
    const QString galleryTwo = gallery + QStringLiteral("/02.bmp");
    const QString galleryThree = gallery + QStringLiteral("/03.GIF");
    const QString bundledPath = bundled + QStringLiteral("/ship.jpg");
    const QString siblingPath = siblingDir + QStringLiteral("/outside.png");
    const QString customPath = home + QStringLiteral("/custom.webp");
    check(writeFile(galleryOne, "1") && writeFile(galleryTwo, "2") && writeFile(galleryThree, "3")
              && writeFile(bundledPath, "b") && writeFile(siblingPath, "s") && writeFile(customPath, "c"),
          "scratch wallpaper fixtures created");
    settings.m_assetBase = bundled + QLatin1Char('/');
    settings.setWallpaper(galleryOne);
    settings.setWallpaper(bundledPath);
    settings.setWallpaper(siblingPath);
    settings.setWallpaper(customPath);
    const QStringList custom = settings.customWallpapers();
    check(!custom.contains(galleryOne) && !custom.contains(bundledPath)
              && custom.contains(siblingPath) && custom.contains(customPath),
          "wallpaper list excludes gallery and bundled art but includes external files without prefix collisions");
    const QStringList cycle = settings.slideshowPictures(galleryOne);
    check(cycle.size() >= 3 && cycle.at(0) == galleryOne && cycle.at(1) == galleryTwo
              && cycle.at(2) == galleryThree,
          "slideshow includes gallery image types accepted by the tab, case-insensitively and in stable order");

    settings.slideshowMinuteMs = 1500;
    settings.setWallpaper(galleryOne);
    settings.setSlideshowInterval(1);
    QObject::connect(&settings, &Settings::slideshowAdvanced, &app, [&](const QString &) {});
    settings.setSlideshowEnabled(true);
    const bool advanced = waitForWallpaper(settings, galleryTwo, 3500);
    check(advanced, "single-shot slideshow advances to the next ordered image");
    settings.setSlideshowEnabled(false);
    settings.slideshowMinuteMs = 2500;
    settings.setSlideshowEnabled(true);
    QTest::qWait(200);
    settings.setSlideshowPaused(true);
    QTest::qWait(3000);
    const QString held = settings.getWallpaper();
    check(held == galleryTwo, "slideshow timer remains stopped while idle");
    settings.setSlideshowPaused(false);
    QTest::qWait(1300);
    check(settings.getWallpaper() == held, "resuming preserves remaining slideshow time after a long idle pause");
    QTest::qWait(1500);
    check(settings.getWallpaper() != held, "slideshow resumes and advances after the preserved remainder");
    settings.setSlideshowEnabled(false);

    settings.setTopPanelTextColor(QStringLiteral("#112233"));
    settings.initWatcher();
    int settingsSignals = 0;
    QObject::connect(&settings, &Settings::settingsChanged, &app, [&] { ++settingsSignals; });
    settings.saveSectionColors();
    QTest::qWait(500);
    check(settingsSignals == 0, "watcher ignores Settings' own atomic config write without a reload loop");
    const QString sectionPath = Lelan::configPath(QStringLiteral("section-colors"));
    QSaveFile external(sectionPath);
    const QByteArray externalJson = QJsonDocument(QJsonObject{{QStringLiteral("topPanelTextColor"),
                                                               QStringLiteral("#445566")}})
                                        .toJson(QJsonDocument::Compact);
    bool externalSaved = external.open(QIODevice::WriteOnly) && external.write(externalJson) == externalJson.size()
                         && external.commit();
    QTest::qWait(1200);
    check(settings.topPanelTextColor() == QLatin1String("#445566"), "watcher applies external section-colour values");
    const int afterReload = settingsSignals;
    QTest::qWait(500);
    check(externalSaved && afterReload > 0 && settingsSignals == afterReload,
          "watcher reloads external atomic edits and settles without repeated notifications");

    Lelan lelan(nullptr, false);
    settings.setLelan(&lelan);
    recordedCommands.clear();
    recordedQueries.clear();
    emit lelan.audioDevicesChanged();
    check(recordedQueries.isEmpty(), "audio-device changes do not spuriously reapply pointer settings");
    emit lelan.inputDevicesChanged();
    check(recordedQueries.contains(QStringLiteral("xinput list"))
              && recordedCommands.contains(QStringLiteral("xinput set-prop 12 libinput Accel Speed 0")),
          "inputDevicesChanged immediately queries and applies configured pointer speed");

    recordedCommands.clear();
    emit lelan.batteryChanged();
    check(recordedCommands.isEmpty(), "repeated battery notification on the same power source does not rerun xset");
    lelan.m_onBattery = true;
    emit lelan.batteryChanged();
    check(recordedCommands.contains(QStringLiteral("xset dpms 600 600 600"))
              && recordedCommands.contains(QStringLiteral("xset s off")),
          "AC-to-battery transition applies the new blanking policy once");

    settings.setLargerCursor(true);
    settings.setCursorSize(48);
    recordedCommands.clear();
    int accessibilitySignals = 0;
    int fontSignals = 0;
    QObject::connect(&settings, &Settings::accessibilityChanged, &app, [&] { ++accessibilitySignals; });
    QObject::connect(&settings, &Settings::fontChanged, &app, [&] { ++fontSignals; });
    settings.saveAccessibility();
    check(Lelan::readConfig(QStringLiteral("input")).value(QStringLiteral("cursorSize")).toInt() == 48
              && std::any_of(recordedCommands.cbegin(), recordedCommands.cend(), [](const QString &s) {
                     return s.startsWith(QLatin1String("xrdb -merge <recorded input>"));
                 }),
          "saving Larger Cursor immediately persists and applies the new Xcursor size");
    check(accessibilitySignals == 1 && fontSignals == 1,
          "applying accessibility notifies accessibility and font consumers");

    QQmlPropertyMap ncde;
    const QStringList ncdeProperties{
        QStringLiteral("accent"), QStringLiteral("background"), QStringLiteral("darkMode"),
        QStringLiteral("detectedZone"), QStringLiteral("fontSize_lg"), QStringLiteral("fontSize_md"),
        QStringLiteral("fontSize_sm"), QStringLiteral("gilt0"), QStringLiteral("gilt1"),
        QStringLiteral("gilt2"), QStringLiteral("gilt3"), QStringLiteral("gilt4"),
        QStringLiteral("gilt5"), QStringLiteral("locating"), QStringLiteral("monoFont"),
        QStringLiteral("panelBg"), QStringLiteral("panelText"), QStringLiteral("previewWallpaperAsync"),
        QStringLiteral("refreshLocation"), QStringLiteral("rose"), QStringLiteral("saveTheme"),
        QStringLiteral("setBaseColor"), QStringLiteral("setNtp"), QStringLiteral("setTimezone"),
        QStringLiteral("surface"), QStringLiteral("surfaceAlt"), QStringLiteral("titleFont"),
        QStringLiteral("usingCustomBase"), QStringLiteral("verd"), QStringLiteral("wine1"),
        QStringLiteral("wine2"), QStringLiteral("wine3"), QStringLiteral("wine4")};
    const QStringList colorProperties{
        QStringLiteral("accent"), QStringLiteral("background"), QStringLiteral("gilt0"),
        QStringLiteral("gilt1"), QStringLiteral("gilt2"), QStringLiteral("gilt3"),
        QStringLiteral("gilt4"), QStringLiteral("gilt5"), QStringLiteral("panelBg"),
        QStringLiteral("panelText"), QStringLiteral("rose"), QStringLiteral("surface"),
        QStringLiteral("surfaceAlt"), QStringLiteral("verd"), QStringLiteral("wine1"),
        QStringLiteral("wine2"), QStringLiteral("wine3"), QStringLiteral("wine4")};
    for (const QString &name : ncdeProperties)
        ncde.insert(name, colorProperties.contains(name) ? QVariant(QStringLiteral("#805a3a"))
                                                         : QVariant(QString()));
    ncde.insert(QStringLiteral("darkMode"), false);
    ncde.insert(QStringLiteral("usingCustomBase"), false);
    ncde.insert(QStringLiteral("fontSize_lg"), 20.0);
    ncde.insert(QStringLiteral("fontSize_md"), 16.0);
    ncde.insert(QStringLiteral("fontSize_sm"), 12.0);
    ncde.insert(QStringLiteral("locating"), false);
    QQmlPropertyMap lelanContext;
    lelanContext.insert(QStringLiteral("sentinelFans"), QVariantList{});
    lelanContext.insert(QStringLiteral("sentinelTemps"), QVariantList{});
    lelanContext.insert(QStringLiteral("kickass"), QVariantMap{});
    QQmlPropertyMap launcher;
    launcher.insert(QStringLiteral("logout"), QString());
    launcher.insert(QStringLiteral("systemCommand"), QString());
    QQmlPropertyMap notifications;
    notifications.insert(QStringLiteral("notify"), QString());
    QQmlPropertyMap animPolicy;
    animPolicy.insert(QStringLiteral("screenIdle"), false);
    QQmlPropertyMap theme;
    theme.insert(QStringLiteral("json"), QVariantMap{});
    const QString qmlRoot = QStringLiteral("/run/media/stephen/NCDE-BACKUP/my-project/files/full-patch-20260711/src/usr/share/ncde");
    const QStringList tabs{
        QStringLiteral("DisplayTab.qml"), QStringLiteral("PowerTab.qml"), QStringLiteral("SecurityTab.qml"),
        QStringLiteral("ScreensaverTab.qml"), QStringLiteral("SessionTab.qml"), QStringLiteral("WallpapersTab.qml"),
        QStringLiteral("DateTimeTab.qml"), QStringLiteral("InputTab.qml"), QStringLiteral("AccessibilityTab.qml"),
        QStringLiteral("DockTab.qml"), QStringLiteral("DockAppsTab.qml"), QStringLiteral("LanguageTab.qml")};
    bool renderedEveryTab = true;
    for (const QString &tab : tabs) {
        std::printf("RENDER %s\n", qPrintable(tab));
        std::fflush(stdout);
        QQuickView view;
        view.setColor(QColor(QStringLiteral("#efe6d2")));
        view.resize(1024, 768);
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.engine()->addImportPath(qmlRoot);
        QQmlContext *ctx = view.engine()->rootContext();
        ctx->setContextProperty(QStringLiteral("settings"), &settings);
        ctx->setContextProperty(QStringLiteral("ncde"), &ncde);
        ctx->setContextProperty(QStringLiteral("lelan"), &lelanContext);
        ctx->setContextProperty(QStringLiteral("launcher"), &launcher);
        ctx->setContextProperty(QStringLiteral("notifications"), &notifications);
        ctx->setContextProperty(QStringLiteral("animPolicy"), &animPolicy);
        ctx->setContextProperty(QStringLiteral("theme"), &theme);
        view.setSource(QUrl::fromLocalFile(qmlRoot + QLatin1Char('/') + tab));
        const bool loaded = view.status() == QQuickView::Ready;
        if (!loaded) {
            for (const auto &error : view.errors())
                std::printf("QMLERROR %s: %s\n", qPrintable(tab), qPrintable(error.toString()));
        } else {
            view.show();
            QTest::qWait(120);
            view.grabWindow().save(QDir::homePath() + QStringLiteral("/%1.png").arg(tab));
        }
        check(loaded, qPrintable(QStringLiteral("offscreen render of %1").arg(tab)));
        renderedEveryTab = renderedEveryTab && loaded;
    }
    check(renderedEveryTab, "all existing Settings-owned tabs render with the rebuilt Settings object");

    check(failures == 0, "all Settings regression checks passed");
    return failures == 0 ? 0 : 1;
}
