// display_qml_host — renders DisplayTab.qml ($DISPLAY_TAB) with the rebuilt Settings as `settings` (display list
// from this machine's real xrandr, read-only; every change RECORDED, never applied). Checks the keep-or-revert bar
// and clicks Keep for real. Was: storage_qml_host — renders StorageTab.qml ($STORAGE_TAB) with the rebuilt Lelan storage code as `lelan`
// on this machine's live UDisks2, offscreen. The operator's own sticks are only DISPLAYED — never clicked.
// Test-only: invented volumes (object paths that do not exist in UDisks) are added to Lelan's list so every
// row state can be seen; their buttons are clicked for real, so the real Lelan calls go to UDisks, which
// answers "no such object" — that proves each button reaches Lelan and that the failure reaches the row.
// PNGs to $OUT. Prints CHECK lines; exits 1 on any QML warning or failed check.
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlPropertyMap>
#include <QQuickItem>
#include <QQuickView>
#include <QTest>
#include <QTimer>
#include <cstdio>
#include <functional>

#define private public
#include "Lelan.h"
#include "Settings.h"
#undef private

Settings::Settings(QObject *parent) : QObject(parent) {}
Settings::~Settings() = default;

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;

static int g_warnings = 0, g_fails = 0;
static void handler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    if (msg.startsWith(QLatin1String("[lelan]")))
        return;
    if (msg.contains(QLatin1String(".qml")) || type >= QtWarningMsg) {
        ++g_warnings;
        std::printf("QMLWARN %s\n", qPrintable(msg));
    }
}
static void check(bool ok, const QString &what)
{
    if (!ok) ++g_fails;
    std::printf("%s %s\n", ok ? "PASS" : "FAIL", qPrintable(what));
}

static const QString FAKE = "/org/freedesktop/UDisks2/block_devices/ncdetest_";

// every visible Text under `root` (depth first), for "what does the tab say" checks
static void texts(QQuickItem *it, QStringList &out)
{
    if (!it->isVisible()) return;
    const QVariant t = it->property("text");
    if (t.isValid() && it->metaObject()->indexOfProperty("elide") >= 0 && !t.toString().isEmpty())
        out << t.toString();
    for (QQuickItem *c : it->childItems()) texts(c, out);
}
// the visible row whose `vol.path` == path
static QQuickItem *rowFor(QQuickItem *it, const QString &path)
{
    if (!it->isVisible()) return nullptr;
    const QVariant v = it->property("vol");
    if (v.isValid() && v.toMap().value("path").toString() == path) return it;
    for (QQuickItem *c : it->childItems()) if (QQuickItem *r = rowFor(c, path)) return r;
    return nullptr;
}
// the visible button labelled `label` inside `row`
static QQuickItem *button(QQuickItem *it, const QString &label)
{
    if (!it->isVisible()) return nullptr;
    if (it->property("label").toString() == label && it->metaObject()->indexOfSignal("clicked()") >= 0) return it;
    for (QQuickItem *c : it->childItems()) if (QQuickItem *b = button(c, label)) return b;
    return nullptr;
}

int main(int argc, char **argv)
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    qputenv("QT_QUICK_BACKEND", "software");
    QGuiApplication app(argc, argv);
    qInstallMessageHandler(handler);
    std::setvbuf(stdout, nullptr, _IOLBF, 0);
    const QString out = qEnvironmentVariable("OUT");
    Lelan lelan(nullptr, false);
    Settings settings;
    QStringList log;
    settings.runDetached = [&](const QString &p, const QStringList &a) { log << p + " " + a.join(' '); };
    settings.refreshDisplays();                        // real `xrandr --query`, read-only
    QQmlPropertyMap ncde, anim;
    ncde.insert("darkMode", false);
    anim.insert("instant", true);
    QQuickView view;
    auto *ctx = view.engine()->rootContext();
    ctx->setContextProperty("lelan", &lelan);
    ctx->setContextProperty("ncde", &ncde);
    ctx->setContextProperty("settings", &settings);
    ctx->setContextProperty("animPolicy", &anim);
    view.setColor(QColor("#efe6d2"));
    view.resize(640, 820);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QTimer::singleShot(1500, [&] {
        view.setSource(QUrl::fromLocalFile(qEnvironmentVariable("DISPLAY_TAB")));
        if (view.status() != QQuickView::Ready) {
            for (const auto &e : view.errors()) std::printf("QMLERROR %s\n", qPrintable(e.toString()));
            QGuiApplication::exit(2); return;
        }
        view.show();
        QQuickItem *root = view.rootObject();
        auto shot = [&](const char *n) { view.grabWindow().save(out + "/" + n + ".png"); std::printf("SHOT %s\n", n); };
        auto said = [&] { QStringList t; texts(root, t); return t.join(" | "); };
        QTimer::singleShot(800, [&, root, shot, said] {
            shot("display_real");
            check(said().contains("1920 × 1200") || said().contains("1920x1200"), "real display's resolution shown");
            check(!said().contains("Keep these display settings"), "no keep bar before a change");
            settings.m_displayRevertTimer = nullptr;
            settings.applyDisplayOrientation("eDP-1", "left");          // recorded only
            QTimer::singleShot(1300, [&, root, shot, said] {
                shot("display_keep");
                check(said().contains("Keep these display settings? Going back in"), "keep bar with countdown: " + said().section("Keep these", 1, 1).left(40));
                QQuickItem *keep = nullptr;
                std::function<void(QQuickItem *)> find = [&](QQuickItem *it) {
                    for (QQuickItem *c : it->childItems()) {
                        if (c->property("text").toString() == "Keep" && c->parentItem()) keep = c->parentItem();
                        find(c);
                    }
                };
                find(root);
                check(keep, "Keep button present");
                if (keep) QTest::mouseClick(&view, Qt::LeftButton, {}, keep->mapToScene(QPointF(keep->width() / 2, keep->height() / 2)).toPoint());
                QTimer::singleShot(600, [&, shot, said] {
                    check(!said().contains("Keep these display settings") && !settings.m_displayRevertTimer->isActive(), "Keep clicked: bar gone, no revert");
                    check(log.contains("xrandr --output eDP-1 --rotate left") && !log.contains("xrandr --output eDP-1 --rotate normal"),
                          "recorded: rotate left, never reverted (" + log.filter("rotate").join(";") + ")");
                    shot("display_kept");
                    std::printf("QML warnings: %d, failed checks: %d\n", g_warnings, g_fails);
                    QGuiApplication::exit(g_warnings || g_fails ? 1 : 0);
                });
            });
        });
    });
    return app.exec();
}
