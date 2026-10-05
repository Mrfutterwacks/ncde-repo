// bluetooth_qml_host — renders BluetoothTab.qml ($BLUETOOTH_TAB) with the rebuilt Lelan Bluetooth code as
// `lelan` on this machine's live BlueZ, offscreen. Test-only: two invented devices are injected into
// Lelan's cache (a paired, connected headset and a nearby phone) so every row state can be seen, then the
// pairing prompt kinds and a failure are shown. PNGs to $OUT; exits 1 on any QML warning.
#include <QGuiApplication>
#include <QDBusObjectPath>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlPropertyMap>
#include <QQuickItem>
#include <QQuickView>
#include <QTimer>
#include <cstdio>

#define private public
#include "Lelan.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;

static int g_warnings = 0;
static void handler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    if (msg.startsWith(QLatin1String("[lelan]")))
        return;
    if (msg.contains(QLatin1String(".qml")) || type >= QtWarningMsg) {
        ++g_warnings;
        std::printf("QMLWARN %s\n", qPrintable(msg));
    }
}

int main(int argc, char **argv)
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    qputenv("QT_QUICK_BACKEND", "software");
    QGuiApplication app(argc, argv);
    qInstallMessageHandler(handler);
    const QString out = qEnvironmentVariable("OUT");

    Lelan lelan(nullptr, false);
    lelan.subscribeToBlueZ();

    QQmlPropertyMap ncde, settings, anim;
    const QList<QPair<const char *, QVariant>> colours = {
        {"surface", QColor("#efe6d2")}, {"panelBg", QColor("#2a1f1a")}, {"panelText", QColor("#2a1f1a")},
        {"gilt", QColor("#a8842f")}, {"wine", QColor("#6b1f2a")}, {"verd", QColor("#3f6b4a")},
        {"amber", QColor("#c8892b")}, {"rose", QColor("#b0606a")}, {"cer", QColor("#3a5f8a")},
        {"darkMode", false}, {"bodyFont", "serif"}, {"displayFont", "serif"}, {"titleFont", "serif"},
        {"monoFont", "monospace"}, {"fontSize", 13}, {"fontSize_sm", 11}, {"fontSize_md", 13}, {"fontSize_lg", 17}};
    for (const auto &c : colours) ncde.insert(c.first, c.second);
    settings.insert("uiScale", 1.0); settings.insert("fontSizeScale", 1.0); settings.insert("accessibilityTextScale", 1.0);
    anim.insert("instant", true);

    QQuickView view;
    auto *ctx = view.engine()->rootContext();
    ctx->setContextProperty("lelan", &lelan);
    ctx->setContextProperty("ncde", &ncde);
    ctx->setContextProperty("settings", &settings);
    ctx->setContextProperty("animPolicy", &anim);
    view.setColor(QColor("#efe6d2"));
    view.resize(640, 600);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl::fromLocalFile(qEnvironmentVariable("BLUETOOTH_TAB")));
    if (view.status() != QQuickView::Ready) {
        for (const auto &e : view.errors()) std::printf("QMLERROR %s\n", qPrintable(e.toString()));
        return 2;
    }
    view.show();
    auto shot = [&](const char *name) { view.grabWindow().save(out + "/" + name + ".png"); std::printf("SHOT %s\n", name); };

    QTimer::singleShot(3000, [&] {
        shot("bt_real");
        const QVariant adapter = QVariant::fromValue(QDBusObjectPath(lelan.m_btAdapter));
        lelan.m_btDevices.insert(lelan.m_btAdapter + "/dev_AA_BB_CC_00_00_01", {
            {"Address", "AA:BB:CC:00:00:01"}, {"Name", "Sennheiser Momentum 4 Wireless Headphones"}, {"Alias", "Sennheiser Momentum 4 Wireless Headphones"},
            {"Icon", "audio-headset"}, {"Paired", true}, {"Connected", true}, {"Adapter", adapter}});
        lelan.m_btDevices.insert(lelan.m_btAdapter + "/dev_AA_BB_CC_00_00_02", {
            {"Address", "AA:BB:CC:00:00:02"}, {"Name", "Pixel 8"}, {"Alias", "Pixel 8"},
            {"Icon", "phone"}, {"Paired", false}, {"Connected", false}, {"Adapter", adapter}});
        lelan.m_btDevices.insert(lelan.m_btAdapter + "/dev_AA_BB_CC_00_00_03", {
            {"Address", "AA:BB:CC:00:00:03"}, {"Adapter", adapter}, {"Paired", false}});          // nameless beacon: hidden (B11)
        lelan.publishBluetooth();
        QTimer::singleShot(400, [&] {
            shot("bt_devices");
            lelan.btAgentShow("confirm", lelan.m_btAdapter + "/dev_AA_BB_CC_00_00_02", "042817");
            QTimer::singleShot(400, [&] {
                shot("bt_confirm");
                lelan.btAgentShow("passkey", lelan.m_btAdapter + "/dev_AA_BB_CC_00_00_02", "");
                QTimer::singleShot(400, [&] {
                    shot("bt_passkey");
                    lelan.btAgentCancel();
                    emit lelan.bluetoothFailed("AA:BB:CC:00:00:02", "Pairing was refused (wrong code, or declined on the device)");
                    QTimer::singleShot(400, [&] {
                        shot("bt_failed");
                        std::printf("QML warnings: %d\n", g_warnings);
                        app.exit(g_warnings ? 1 : 0);
                    });
                });
            });
        });
    });
    return app.exec();
}
