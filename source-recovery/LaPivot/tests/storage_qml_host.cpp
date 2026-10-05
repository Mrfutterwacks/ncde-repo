// storage_qml_host — renders StorageTab.qml ($STORAGE_TAB) with the rebuilt Lelan storage code as `lelan`
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
#undef private

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
    const QString out = qEnvironmentVariable("OUT");

    Lelan lelan(nullptr, false);
    lelan.subscribeToUDisks2();
    QStringList lelanCalls;                           // what reached Lelan from the tab, via UDisks' answers
    QObject::connect(&lelan, &Lelan::volumeFailed, [&](const QString &p, const QString &r) {
        lelanCalls << p.section('/', -1); std::printf("  volumeFailed %s | %s\n", qPrintable(p.section('/', -1)), qPrintable(r)); });

    QQmlPropertyMap ncde, settings, anim;
    const QList<QPair<const char *, QVariant>> colours = {
        {"surface", QColor("#efe6d2")}, {"panelBg", QColor("#2a1f1a")}, {"panelText", QColor("#2a1f1a")},
        {"gilt", QColor("#a8842f")}, {"wine", QColor("#6b1f2a")}, {"verd", QColor("#3f6b4a")},
        {"amber", QColor("#c8892b")}, {"rose", QColor("#b0606a")}, {"cer", QColor("#3a5f8a")},
        {"darkMode", false}, {"bodyFont", "serif"}, {"displayFont", "serif"}, {"titleFont", "serif"},
        {"monoFont", "monospace"}, {"fontSize", 13}, {"fontSize_sm", 11}, {"fontSize_md", 13}, {"fontSize_lg", 17}};
    for (const auto &c : colours) ncde.insert(c.first, c.second);
    settings.insert("uiScale", 1.0); settings.insert("fontSizeScale", 1.0); settings.insert("accessibilityTextScale", 1.0);
    settings.insert("autoMountUsb", true);
    anim.insert("instant", true);

    QQuickView view;
    auto *ctx = view.engine()->rootContext();
    ctx->setContextProperty("lelan", &lelan);
    ctx->setContextProperty("ncde", &ncde);
    ctx->setContextProperty("settings", &settings);
    ctx->setContextProperty("animPolicy", &anim);
    view.setColor(QColor("#efe6d2"));
    view.resize(640, 760);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl::fromLocalFile(qEnvironmentVariable("STORAGE_TAB")));
    if (view.status() != QQuickView::Ready) {
        for (const auto &e : view.errors()) std::printf("QMLERROR %s\n", qPrintable(e.toString()));
        return 2;
    }
    view.show();
    QQuickItem *root = view.rootObject();
    auto shot = [&](const char *name) { view.grabWindow().save(out + "/" + name + ".png"); std::printf("SHOT %s\n", name); };
    auto said = [&] { QStringList t; texts(root, t); return t.join(" | "); };
    auto click = [&](const QString &path, const QString &label) {
        QQuickItem *r = rowFor(root, path);
        QQuickItem *b = r ? button(r, label) : nullptr;
        check(b != nullptr, "button \"" + label + "\" shown on " + path.section('/', -1));
        if (!b) return;
        const QPointF c = b->mapToScene(QPointF(b->width() / 2, b->height() / 2));
        QTest::mouseClick(&view, Qt::LeftButton, {}, c.toPoint());
    };

    // the scenes run one after another, 1.5 s apart (UDisks answers in well under that)
    QList<std::function<void()>> scenes;
    scenes << [&] {
        shot("storage_real");
        const QString t = said();
        for (const QVariant &v : lelan.m_removableVolumes) {
            const QVariantMap m = v.toMap();
            check(t.contains(m.value("label").toString()) && t.contains("Mounted at " + m.value("mountPoint").toString()),
                  "real stick shown with its mount point: " + m.value("label").toString());
        }
        check(!t.contains("ARCHISO_EFI"), "ARCHISO_EFI not shown");
        check(t.contains(" GB"), "sizes human-readable (GB), not raw bytes");
        // invented sticks, appended after the real ones
        QVariantList l = lelan.m_removableVolumes;
        l << QVariantMap{{"path", FAKE + "sdx1"}, {"device", "/dev/sdx1"}, {"label", ""}, {"drive", "SanDisk Ultra Fit USB 3.1 Flash Drive With A Very Long Model Name"},
                         {"size", 61530439680ULL}, {"fsType", "exfat"}, {"mounted", false}, {"mountPoint", ""}, {"canUnmount", false},
                         {"locked", false}, {"encrypted", false}, {"canEject", true}};
        l << QVariantMap{{"path", FAKE + "sdy1"}, {"device", "/dev/sdy1"}, {"label", "PRIVATE"}, {"drive", "Kingston DataTraveler"},
                         {"size", 15500000000ULL}, {"fsType", "crypto_LUKS"}, {"mounted", false}, {"mountPoint", ""}, {"canUnmount", false},
                         {"locked", true}, {"encrypted", true}, {"canEject", true}};
        l << QVariantMap{{"path", FAKE + "sdz1"}, {"device", "/dev/sdz1"}, {"label", "CAMERA"}, {"drive", "Generic SD"},
                         {"size", 7900000ULL}, {"fsType", "vfat"}, {"mounted", true}, {"mountPoint", "/run/media/stephen/CAMERA"}, {"canUnmount", true},
                         {"locked", false}, {"encrypted", false}, {"canEject", true}};
        // from here on the list is the test's: after each UDisks answer Lelan re-reads the real tree
        // (correct), which would drop the invented rows — so the re-read timer is cut for the rest
        QObject::disconnect(lelan.m_storageTimer, nullptr, nullptr, nullptr);
        lelan.m_removableVolumes = l;
        emit lelan.storageChanged();
    };
    scenes << [&] {
        shot("storage_rows");
        const QString t = said();
        check(t.contains("SanDisk Ultra Fit"), "nameless stick shown by its drive name");
        check(t.contains("sdx1 · exfat · 62 GB"), "details line: device · type · size");
        check(t.contains("sdy1 · encrypted · 16 GB") && t.contains("Locked"), "locked stick: encrypted + Locked");
        check(t.contains("7.9 MB"), "small size to one decimal");
        check(rowFor(root, FAKE + "sdy1") && !button(rowFor(root, FAKE + "sdy1"), "Mount"), "locked stick has no Mount button");
        click(FAKE + "sdx1", "Mount");
        check(said().contains("Working…"), "Mount pressed: row says Working…");
    };
    scenes << [&] {
        check(lelanCalls.contains("ncdetest_sdx1"), "Mount reached Lelan::mountVolume (UDisks answered for that path)");
        const QString t = said();
        check(t.contains("This drive is no longer connected") && !t.contains("Working…"), "failure shown under the row, Working… cleared");
        shot("storage_failed");
        click(FAKE + "sdy1", "Unlock");
    };
    scenes << [&] {
        check(said().contains("Passphrase"), "Unlock opens the passphrase field");
        for (const char ch : QByteArray("secret")) QTest::keyClick(&view, ch);   // (keyClicks is QWidget-only)
        shot("storage_unlock");
        QTest::keyClick(&view, Qt::Key_Return);
    };
    scenes << [&] {
        check(lelanCalls.contains("ncdetest_sdy1"), "Enter in the field reached Lelan::unlockVolume");
        check(!said().contains("secret"), "passphrase not shown anywhere");
        shot("storage_unlock_failed");
        click(FAKE + "sdz1", "Eject");
    };
    scenes << [&] {
        check(lelanCalls.count("ncdetest_sdz1") == 1, "Eject reached Lelan::ejectVolume (gone drive reported, not silent)");
        emit lelan.volumeEjected("CAMERA");
    };
    scenes << [&] {
        check(said().contains("CAMERA can be removed safely."), "safe-to-remove note after an eject");
        shot("storage_ejected");
        lelan.m_removableVolumes.clear();
        emit lelan.storageChanged();
    };
    scenes << [&] {
        check(said().contains("No removable drives detected."), "empty state");
        shot("storage_empty");
        std::printf("QML warnings: %d, failed checks: %d\n", g_warnings, g_fails);
        QGuiApplication::exit(g_warnings || g_fails ? 1 : 0);
    };

    int i = 0;
    std::function<void()> run = [&] { if (i < scenes.size()) { scenes[i++](); QTimer::singleShot(1500, run); } };
    QTimer::singleShot(3000, run);
    return app.exec();
}
