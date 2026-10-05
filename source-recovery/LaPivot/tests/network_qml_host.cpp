// network_qml_host — loads the payload's real NetworkTab.qml with the rebuilt Lelan network code as
// `lelan`, on this machine's live NetworkManager (read-only), offscreen. `ncde` / `settings` /
// `animPolicy` are stand-ins (colours and scales only); `notifications` prints. Saves PNGs of the
// Wi-Fi, Ethernet and a failed-join view to $OUT, prints every QML warning, exits 1 if there are any.
#include <QGuiApplication>
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

class Notifications : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void notify(const QString &title, const QString &body, const QString &, int)
    {
        std::printf("NOTIFY %s: %s\n", qPrintable(title), qPrintable(body));
    }
};

static int g_warnings = 0;
static void handler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    if (msg.contains(QLatin1String(".qml")) || type >= QtWarningMsg) {
        if (msg.startsWith(QLatin1String("[lelan]")))
            return;                                   // Lelan's own D-Bus logs are not QML problems
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
    const QString qml = qEnvironmentVariable("NETWORK_TAB");
    const QString out = qEnvironmentVariable("OUT");

    Lelan lelan(nullptr, false);
    lelan.subscribeToNetworkManager();
    lelan.subscribeToWifi();

    QQmlPropertyMap ncde, settings, anim;
    const QList<QPair<const char *, QVariant>> colours = {
        {"surface", QColor("#efe6d2")}, {"panelBg", QColor("#2a1f1a")}, {"panelText", QColor("#2a1f1a")},
        {"gilt", QColor("#a8842f")}, {"wine", QColor("#6b1f2a")}, {"verd", QColor("#3f6b4a")},
        {"amber", QColor("#c8892b")}, {"rose", QColor("#b0606a")}, {"cer", QColor("#3a5f8a")},
        {"darkMode", false}, {"bodyFont", "serif"}, {"displayFont", "serif"}, {"titleFont", "serif"},
        {"monoFont", "monospace"}, {"fontSize", 13},
        {"fontSize_sm", 11}, {"fontSize_md", 13}, {"fontSize_lg", 17}};
    for (const auto &c : colours) ncde.insert(c.first, c.second);
    settings.insert("userName", qEnvironmentVariable("USER"));
    settings.insert("proxyEnabled", false);
    settings.insert("uiScale", 1.0);
    settings.insert("fontSizeScale", 1.0);
    settings.insert("accessibilityTextScale", 1.0);
    anim.insert("instant", true);
    Notifications notifications;

    QQuickView view;
    view.engine()->rootContext()->setContextProperty("lelan", &lelan);
    view.engine()->rootContext()->setContextProperty("ncde", &ncde);
    view.engine()->rootContext()->setContextProperty("settings", &settings);
    view.engine()->rootContext()->setContextProperty("animPolicy", &anim);
    view.engine()->rootContext()->setContextProperty("notifications", &notifications);
    view.setColor(QColor("#efe6d2"));
    view.resize(780, 560);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl::fromLocalFile(qml));
    if (view.status() != QQuickView::Ready) {
        for (const auto &e : view.errors()) std::printf("QMLERROR %s\n", qPrintable(e.toString()));
        return 2;
    }
    view.show();
    QQuickItem *root = view.rootObject();

    auto shot = [&](const char *name) { view.grabWindow().save(out + "/" + name + ".png"); std::printf("SHOT %s\n", name); };
    QTimer::singleShot(5000, [&] {
        shot("wifi");
        root->setProperty("selectedIface", 1);
        QTimer::singleShot(500, [&] {
            shot("ethernet");
            // a failed join, as NetworkManager would report it, on the second network in the list
            root->setProperty("selectedIface", 0);
            const QVariantList nets = lelan.wifiNetworks();
            int idx = -1;
            for (int i = 0; i < nets.size(); ++i)
                if (!nets[i].toMap().value("connected").toBool()) { idx = i; break; }
            if (idx >= 0) {
                root->setProperty("selectedNet", idx);
                emit lelan.wifiConnectFailed(nets[idx].toMap().value("ssid").toString(), QStringLiteral("Wrong password"));
            }
            QTimer::singleShot(500, [&] {
                shot("wifi_failed_join");
                std::printf("QML warnings: %d\n", g_warnings);
                app.exit(g_warnings ? 1 : 0);
            });
        });
    });
    return app.exec();
}

#include "network_qml_host.moc"
