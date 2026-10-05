// LaPivot main() — builds every shell object, wires them, exposes them to QML and loads the shell.
//
// Rebuilt from oracle: main (0xf4190) and its lambdas main::{lambda()#1..#4}, main::{lambda(int,bool)#1}
// (decomp/_global.c "main", decomp/main.c; context-property objects and strings measured from the
// disassembly, see reports/main-l2.md §A).
// Spec: README "main() must" lines (RESUME item 4, work list), NCDE-ARCHITECTURE-DIGEST §2, the QML
// consumers of the 18 context properties.
//
// DEFECTS FIXED vs oracle:
//  M1 xdg-desktop-portal could not read LaPivot's settings requests ("Unable to open /proc/<pid>/root"):
//     cap_sys_nice makes the process non-dumpable, so /proc/<pid> is root-owned -> prctl(PR_SET_DUMPABLE,1)
//     first thing (operator-approved 2026-09-30; ptrace still needs the tracer to hold cap_sys_nice).
//  M2 the USB auto-mount switch never reached Lelan at start: Settings loads storage.json in its
//     constructor, before setLelan -> lelan.setAutoMountPref(settings.autoMountUsb()) after setLelan,
//     and again on Settings::storageChanged.
//  M3 idle decisions came from three places (WM 30 s flag -> AnimPolicy -> Settings suspend; WM
//     screensaver timeout -> lambda#2 starts the saver; lambda(int,bool)#1 relaunched a saver right after a
//     key press). Settings/IdlePolicy now owns idle (Settings_power.cpp I1-I4): main feeds it the WM's X idle
//     sample (NCDEWindowManager::idleSample -> Settings::onIdleSample) and the live query
//     (settings.idleMsSource = WM::userIdleMs). The oracle lambdas #1, #2 and (int,bool)#1 are NOT
//     re-created here — they would start/relaunch a second saver beside IdlePolicy.
//  M4 the panel clock ignored hourFormat/showSeconds: WidgetData had no Settings -> setSettings(settings).
//  M5 every Settings::inputChanged (keyboard repeat, pointer speed, ...) re-uploaded the root cursor and
//     re-announced the XSETTINGS cursor size -> only when the bounded cursor size actually changed.
//  M6 a cursor-size change reached only the root window and XSETTINGS; apps started afterwards still got
//     the login-time XCURSOR_SIZE -> the environment is updated with it.
//  M7 XSettingsManager::setCursorSize was still called after XSettingsManager::start had failed (another
//     XSETTINGS owner) -> only while LaPivot owns the selection.
//  M8 a missing <base>/main.qml loaded qrc:/Shell.qml, a developer harness that calls settings.savePower()
//     and settings.saveFontSettings() (rewriting the user's power/font files) and quits LaPivot 3.5 s later
//     -> the harness is no longer built in; the error is logged and LaPivot exits non-zero.
//  M9 the shell's asset base was hardcoded (/usr/share/ncde) -> ncde::assetBase() (NCDE_ASSET_BASE or the
//     compiled LAPIVOT_ASSET_BASE), so the L2 test session runs its own QML tree.
//  M10 FontManager was a function-static object, destroyed after QGuiApplication at exit -> a plain local
//     constructed after the application, destroyed before it.
//  M11 without XDG_RUNTIME_DIR the cursor theme went to the shared /tmp/ncde-cursors (any user could plant
//     it first) -> a per-user directory under the temp path.
// Deliberate parity deviation: the oracle called QGuiApplication(argc, argv, 0x60b01) — AA_Use96Dpi |
// AA_DisableNativeVirtualKeyboard | AA_SynthesizeTouchForUnhandledMouseEvents | AA_UseSoftwareOpenGL |
// AA_ShareOpenGLContexts (decoded from /usr/include/qt6/QtCore/qnamespace.h, bit 0 unused). Software
// OpenGL contradicts the design docs (threaded render loop, 4 QSGRenderThreads), so the rebuild uses the
// plain QGuiApplication(argc, argv). Measured, see reports/main-l2.md §A.1.
#include <sys/prctl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QGuiApplication>
#include <QIcon>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringList>
#include <QSurfaceFormat>
#include <QWindow>
#include <QtGui/qguiapplication_platform.h>

#include <xcb/xcb.h>

#include "ncde_paths.h"

#include "AnimPolicy.h"
#include "AppMenuModel.h"
#include "CalendarBackend.h"
#include "CursorManager.h"
#include "FontManager.h"
#include "GliaSystemMenus.h"
#include "HudManager.h"
#include "IconProvider.h"
#include "IdleInhibitService.h"
#include "Launcher.h"
#include "LeapFrogPond.h"
#include "Lelan.h"
#include "NCDEEngine.h"
#include "NCDEGeo.h"
#include "NCDEWindowManager.h"
#include "NCDEWorkspace.h"
#include "NotificationManager.h"
#include "ScreenInfo.h"
#include "Settings.h"
#include "Theme.h"
#include "WidgetData.h"
#include "WindowTyper.h"
#include "XSettingsManager.h"

namespace {

constexpr int kMinCursor = 24;
constexpr int kMaxCursor = 64;
const QString kCursorTheme = QStringLiteral("Kith");

int boundedCursorSize(const Settings &s)
{
    return qBound(kMinCursor, s.cursorSize(), kMaxCursor);
}

// main::{lambda()#3}: the root window's cursor, at the user's size
void installRootCursor(CursorManager &cursors, int size)
{
    auto *x11 = qGuiApp->nativeInterface<QNativeInterface::QX11Application>();
    if (!x11)
        return;
    xcb_connection_t *conn = x11->connection();
    if (!conn)
        return;
    const xcb_screen_iterator_t it = xcb_setup_roots_iterator(xcb_get_setup(conn));
    if (!it.data)
        return;
    cursors.installAsRootCursor(conn, it.data->root, size);
}

// M11: $XDG_RUNTIME_DIR/ncde-cursors, or a per-user temp directory
QString cursorThemeDir()
{
    const QString runtime = qEnvironmentVariable("XDG_RUNTIME_DIR");
    if (!runtime.isEmpty())
        return runtime + QStringLiteral("/ncde-cursors");
    return QDir::tempPath() + QStringLiteral("/ncde-cursors-") + QString::number(getuid());
}

// Kith rendered at the sizes Xcursor picks from, exported to every client LaPivot starts
void setUpCursorTheme(CursorManager &cursors, int size)
{
    cursors.setTheme(kCursorTheme, 32);
    const QString dir = cursorThemeDir();
    if (!cursors.writeXcursorTheme(dir, {24, 32, 48, 64}))
        return;
    const QString home = QDir::homePath();
    qputenv("XCURSOR_THEME", kCursorTheme.toUtf8());
    qputenv("XCURSOR_SIZE", QByteArray::number(size));
    qputenv("XCURSOR_PATH", (dir + QLatin1Char(':') + home + QStringLiteral("/.local/share/icons:") + home
                             + QStringLiteral("/.icons:/usr/share/icons:/usr/share/pixmaps")).toUtf8());
    // GTK/Xlib clients that ignore XCURSOR_PATH look in ~/.local/share/icons: point Kith there
    const QString icons = home + QStringLiteral("/.local/share/icons");
    QDir().mkpath(icons);
    const QString link = icons + QLatin1Char('/') + kCursorTheme;
    if (QFileInfo(link).isSymLink())
        QFile::remove(link);
    if (!QFileInfo::exists(link))
        QFile::link(dir + QLatin1Char('/') + kCursorTheme, link);
}

// icon theme chosen in the theme file + the user's own icon directory
void setUpIconTheme()
{
    QFile f(QDir::homePath() + QStringLiteral("/.config/ncde/active-theme.json"));
    if (f.open(QIODevice::ReadOnly)) {
        const QString name = QJsonDocument::fromJson(f.readAll()).object().value(QStringLiteral("iconTheme")).toString();
        if (!name.isEmpty())
            QIcon::setThemeName(name);
    }
    QStringList paths = QIcon::themeSearchPaths();
    paths << QDir::homePath() + QStringLiteral("/.local/share/icons") << QStringLiteral("/usr/share/icons");
    paths.removeDuplicates();
    QIcon::setThemeSearchPaths(paths);
}

} // namespace

int main(int argc, char **argv)
{
    // M1: file capabilities (cap_sys_nice) make the process non-dumpable; xdg-desktop-portal then cannot
    // open /proc/<pid>/root and refuses LaPivot's Settings reads.
    if (prctl(PR_SET_DUMPABLE, 1, 0, 0, 0) != 0)
        qWarning("LaPivot: prctl(PR_SET_DUMPABLE) failed: %s", strerror(errno));

    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setAlphaBufferSize(8);                                    // translucent shell windows
    QSurfaceFormat::setDefaultFormat(fmt);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.text.emojisegmenter.warning=false"));

    QGuiApplication app(argc, argv);

    // ---- the shell objects, in the oracle's order ----
    Lelan lelan(nullptr, true);
    NCDEEngine engine;
    // Oracle: engine.setLelan(&lelan) — dropped; NCDEEngine is colour-only (digest §2), system state is lelan.*
    lelan.setEngine(&engine);

    Settings settings;
    settings.setLelan(&lelan);
    lelan.setAutoMountPref(settings.autoMountUsb());                         // M2
    QObject::connect(&settings, &Settings::storageChanged, &lelan,
                     [&] { lelan.setAutoMountPref(settings.autoMountUsb()); });

    Theme theme;
    theme.setSettings(&settings);
    theme.setEngine(&engine);

    WidgetData widgetData;
    widgetData.setLelan(&lelan);
    widgetData.setSettings(&settings);                                      // M4

    AnimPolicy animPolicy;
    lelan.setAnimPolicy(&animPolicy);
    settings.setAnimPolicy(&animPolicy);
    widgetData.setAnimPolicy(&animPolicy);

    Launcher launcher;
    NotificationManager notifications;
    notifications.setSettings(&settings);
    CalendarBackend calendar;
    NCDEWorkspace workspace;
    AppMenuModel appMenuModel;
    ScreenInfo screenInfo;
    LeapFrogPond pond(nullptr, &calendar);
    GliaSystemMenus gliaSystem;
    NCDEGeo geo;
    geo.setLelan(&lelan);
    HudManager hudManager;

    lelan.applyZenStartupHints();

    WindowTyper windowTyper;
    NCDEWindowManager windowMgr;
    IdleInhibitService idleInhibit;
    windowMgr.start();
    windowMgr.setAnimPolicy(&animPolicy);

    // ---- idle: the WM samples X idle, Settings/IdlePolicy decides (M3) ----
    settings.idleMsSource = [&windowMgr] { return windowMgr.userIdleMs(); };
    QObject::connect(&windowMgr, &NCDEWindowManager::idleSample, &settings, &Settings::onIdleSample);

    // ---- WM -> Lelan (App Nap tiers, screen geometry) ----
    QObject::connect(&windowMgr, &NCDEWindowManager::screenConfigChanged, &lelan, &Lelan::onWMScreenConfig);
    QObject::connect(&windowMgr, &NCDEWindowManager::windowTierNeeded, &lelan, &Lelan::onWindowTierNeeded);
    QObject::connect(&windowMgr, &NCDEWindowManager::windowClosed, &lelan, &Lelan::onWindowClosed);

    // ---- cursor: Kith theme files, root cursor, XSETTINGS ----
    CursorManager cursors;
    int cursorSize = boundedCursorSize(settings);
    setUpCursorTheme(cursors, cursorSize);
    installRootCursor(cursors, cursorSize);

    XSettingsManager xsettings;
    const bool ownXSettings = xsettings.start(kCursorTheme, cursorSize);
    if (!ownXSettings)
        qWarning() << "XSETTINGS: another manager owns the selection;"
                   << "already-running clients unavailable this session";

    QObject::connect(&settings, &Settings::inputChanged, &settings, [&] {
        const int size = boundedCursorSize(settings);
        if (size == cursorSize)                                             // M5
            return;
        cursorSize = size;
        qputenv("XCURSOR_SIZE", QByteArray::number(size));                  // M6
        installRootCursor(cursors, size);
        if (ownXSettings)                                                   // M7
            xsettings.setCursorSize(size);
    });

    setUpIconTheme();

    // ---- QML ----
    QQmlApplicationEngine qml;
    qml.addImageProvider(QStringLiteral("icon"), new IconProvider);          // engine owns it
    QQmlContext *ctx = qml.rootContext();
    ctx->setContextProperty(QStringLiteral("lelan"), &lelan);
    ctx->setContextProperty(QStringLiteral("ncde"), &engine);
    ctx->setContextProperty(QStringLiteral("settings"), &settings);
    ctx->setContextProperty(QStringLiteral("theme"), &theme);
    FontManager fontMgr;                                                    // M10: scoped to the QML engine
    ctx->setContextProperty(QStringLiteral("fontMgr"), &fontMgr);
    ctx->setContextProperty(QStringLiteral("widget_data"), &widgetData);
    ctx->setContextProperty(QStringLiteral("animPolicy"), &animPolicy);
    ctx->setContextProperty(QStringLiteral("launcher"), &launcher);
    ctx->setContextProperty(QStringLiteral("notifications"), &notifications);
    ctx->setContextProperty(QStringLiteral("windowMgr"), &windowMgr);
    ctx->setContextProperty(QStringLiteral("calBackend"), &calendar);
    ctx->setContextProperty(QStringLiteral("ncdeWorkspace"), &workspace);
    ctx->setContextProperty(QStringLiteral("appMenuModel"), &appMenuModel);
    ctx->setContextProperty(QStringLiteral("window"), &screenInfo);
    ctx->setContextProperty(QStringLiteral("pond"), &pond);
    ctx->setContextProperty(QStringLiteral("gliaSystem"), &gliaSystem);
    ctx->setContextProperty(QStringLiteral("geo"), &geo);
    ctx->setContextProperty(QStringLiteral("hudManager"), &hudManager);

    const QString base = ncde::assetBase();                                 // M9
    const QString mainQml = base + QStringLiteral("main.qml");
    if (!QFile::exists(mainQml)) {                                          // M8
        qCritical("LaPivot: %s not found (asset base %s, NCDE_ASSET_BASE=%s) - nothing to show",
                  qPrintable(mainQml), qPrintable(base), qgetenv("NCDE_ASSET_BASE").constData());
        return 1;
    }
    qml.addImportPath(base);
    qml.load(QUrl::fromLocalFile(mainQml));
    if (qml.rootObjects().isEmpty()) {
        qCritical("LaPivot: %s failed to load (see the QML errors above)", qPrintable(mainQml));
        return -1;
    }
    if (auto *win = qobject_cast<QWindow *>(qml.rootObjects().first()))
        cursors.install(win);

    return app.exec();
}
