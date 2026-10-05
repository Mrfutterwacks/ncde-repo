// network_live_test — Lelan_network.cpp against the machine's real NetworkManager (read-only: it
// subscribes and reads; it never connects, disconnects or toggles anything). Built and judged by
// network_live_test.sh, which compares the dump with nmcli / ip ground truth.
//
// Prints after SETTLE_MS: one JSON line with network, wifiEnabled, wifiNetworks, activeNetwork,
// vpnConnections; then watches WATCH_MS and prints how often each NOTIFY signal fired.
#include <QCoreApplication>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <cstdio>

#define private public
#include "Lelan.h"
#undef private

// Test-only construction: the real constructor (Lelan.cpp) wires every subsystem; this one only
// gives the network code a live object.
Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    const int settleMs = qEnvironmentVariableIntValue("SETTLE_MS") ?: 5000;
    const int watchMs = qEnvironmentVariableIntValue("WATCH_MS") ?: 40000;

    Lelan l(nullptr, false);
    int wifi = 0, net = 0, vpn = 0;
    QObject::connect(&l, &Lelan::wifiChanged, [&] { ++wifi; });
    QObject::connect(&l, &Lelan::networkChanged, [&] { ++net; });
    QObject::connect(&l, &Lelan::vpnStateChanged, [&] { ++vpn; });

    l.subscribeToNetworkManager();
    l.subscribeToWifi();

    // IMPORT_TEST=<file>: importVpn(file); print the result and the list once it updates
    const QString importFile = qEnvironmentVariable("IMPORT_TEST");
    if (!importFile.isEmpty()) {
        QObject::connect(&l, &Lelan::vpnImportFinished, [&](bool ok, const QString &msg) {
            std::printf("IMPORT_FINISHED ok=%d msg=%s\n", ok, qPrintable(msg));
            std::fflush(stdout);
        });
        QTimer::singleShot(settleMs, [&] {
            l.importVpn(importFile);
            QTimer::singleShot(settleMs, [&] {
                std::printf("IMPORT_LIST %s\n", QJsonDocument::fromVariant(l.vpnConnections()).toJson(QJsonDocument::Compact).constData());
                app.quit();
            });
        });
        return app.exec();
    }

    // REMOVE_TEST=<vpn name>: removeVpn(name); the list must drop it
    const QString removeName = qEnvironmentVariable("REMOVE_TEST");
    if (!removeName.isEmpty()) {
        QTimer::singleShot(settleMs, [&] {
            std::printf("REMOVE_BEFORE %s\n", QJsonDocument::fromVariant(l.vpnConnections()).toJson(QJsonDocument::Compact).constData());
            l.removeVpn(removeName);
            QTimer::singleShot(settleMs, [&] {
                std::printf("REMOVE_AFTER %s\n", QJsonDocument::fromVariant(l.vpnConnections()).toJson(QJsonDocument::Compact).constData());
                app.quit();
            });
        });
        return app.exec();
    }

    // VPN_TEST=<profile name>: connect it through Lelan, then disconnect it, dumping the list after each
    const QString vpnName = qEnvironmentVariable("VPN_TEST");
    if (!vpnName.isEmpty()) {
        auto dump = [&](const char *tag) {
            std::printf("%s vpnStateChanged=%d %s\n", tag, vpn,
                        QJsonDocument::fromVariant(l.vpnConnections()).toJson(QJsonDocument::Compact).constData());
            std::fflush(stdout);
        };
        QTimer::singleShot(settleMs, [&, dump] {
            dump("VPN_BEFORE");
            vpn = 0;
            l.connectVpn(vpnName);
            QTimer::singleShot(settleMs, [&, dump] {
                dump("VPN_CONNECTED");
                vpn = 0;
                l.disconnectVpn(vpnName);
                QTimer::singleShot(settleMs, [&, dump] { dump("VPN_DISCONNECTED"); app.quit(); });
            });
        });
        return app.exec();
    }

    QTimer::singleShot(settleMs, [&] {
        QJsonObject o;
        o["network"] = QJsonObject::fromVariantMap(l.network());
        o["networkOnline"] = l.networkOnline();
        o["wifiEnabled"] = l.wifiEnabled();
        o["wifiNetworks"] = QJsonValue::fromVariant(l.wifiNetworks());
        o["activeNetwork"] = QJsonObject::fromVariantMap(l.activeNetwork());
        o["wiredNetwork"] = QJsonObject::fromVariantMap(l.wiredNetwork());
        o["vpnConnections"] = QJsonValue::fromVariant(l.vpnConnections());
        o["apCache"] = int(l.m_apCache.size());
        o["wifiProfiles"] = QJsonValue::fromVariant(QVariant(QStringList(l.m_wifiProfiles.keys())));
        std::printf("DUMP %s\n", QJsonDocument(o).toJson(QJsonDocument::Compact).constData());
        std::fflush(stdout);
        wifi = net = vpn = 0;
        QObject::connect(&l, &Lelan::wifiChanged, [&] {
            const QVariantList nets = l.wifiNetworks();
            QStringList bars;
            for (const QVariant &v : nets) {
                const QVariantMap e = v.toMap();
                bars << e.value("ssid").toString() + "=" + e.value("signal").toString();
            }
            std::printf("WIFICHANGED %s\n", qPrintable(bars.join(' ')));
            std::fflush(stdout);
        });
        QTimer::singleShot(watchMs, [&] {
            std::printf("WATCH %d ms: wifiChanged=%d networkChanged=%d vpnStateChanged=%d\n", watchMs, wifi, net, vpn);
            std::printf("FINALTIME %.6f\n", QDateTime::currentMSecsSinceEpoch() / 1000.0);
            for (auto it = l.m_apCache.cbegin(); it != l.m_apCache.cend(); ++it)
                std::printf("APCACHE %s %u\n", qPrintable(it.key()), it->strength);
            std::printf("FINALSPEED %u\n", l.activeNetwork().value("speed").toUInt());
            app.quit();
        });
    });
    return app.exec();
}
