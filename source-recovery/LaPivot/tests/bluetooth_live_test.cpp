// bluetooth_live_test — Lelan_bluetooth.cpp against this machine's BlueZ. BT_MODE selects:
//   state   : dump what Lelan publishes (judged against bluetoothctl by bluetooth_live_test.sh)
//   scan    : bluetoothScan(); report scanning + device count over 40 s (discovery must stop at ~30 s)
//   agent   : register the agent, print the bus name, then answer pairing prompts as AGENT_ANSWERS says
//             ("accept,reject,passkey:123456" one per prompt) — the script plays BlueZ against it
//   enable  : setBluetoothEnabled(true) (used after the script soft-blocks Bluetooth)
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <cstdio>

#define private public
#include "Lelan.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;

static void out(const char *fmt, const QByteArray &a = {}) { std::printf(fmt, a.constData()); std::printf("\n"); std::fflush(stdout); }
static QByteArray json(const QVariant &v) { return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact); }

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    const QString mode = qEnvironmentVariable("BT_MODE", "state");
    Lelan l(nullptr, false);
    int changed = 0;
    QStringList answers = qEnvironmentVariable("AGENT_ANSWERS").split(',', Qt::SkipEmptyParts);
    QObject::connect(&l, &Lelan::bluetoothChanged, [&] { ++changed; });
    QObject::connect(&l, &Lelan::bluetoothFailed, [&](const QString &a, const QString &r) {
        out("FAILED %s", (a + " | " + r).toUtf8());
    });
    l.subscribeToBlueZ();

    auto state = [&] {
        QVariantMap m{{"bluetooth", l.bluetooth()}, {"enabled", l.bluetoothEnabled()}, {"discoverable", l.bluetoothDiscoverable()},
                      {"scanning", l.bluetoothScanning()}, {"devices", l.bluetoothDevices()}, {"audio", l.bluetoothAudioDevice()},
                      {"agentDefault", l.m_btAgentDefault}};
        return json(m);
    };

    if (mode == "state") {
        QTimer::singleShot(3000, [&] { out("STATE %s", state()); app.quit(); });
    } else if (mode == "scan") {
        QTimer::singleShot(3000, [&] {
            changed = 0;
            l.bluetoothScan();
            for (int s = 5; s <= 40; s += 5)
                QTimer::singleShot(s * 1000, [&, s] {
                    out(QString("SCAN t=%1s scanning=%2 devices=%3 bluetoothChanged=%4")
                            .arg(s).arg(l.bluetoothScanning()).arg(l.bluetoothDevices().size()).arg(changed).toUtf8().constData());
                    if (s == 40) app.quit();
                });
        });
    } else if (mode == "agent") {
        QObject::connect(&l, &Lelan::bluetoothPairingChanged, [&] {
            const QVariantMap p = l.bluetoothPairing();
            out("PROMPT %s", json(p));
            if (p.isEmpty() || answers.isEmpty()) return;
            const QString a = answers.takeFirst();
            QTimer::singleShot(300, [&l, a] {
                if (a.startsWith("passkey:")) l.bluetoothPairingReply(true, a.mid(8));
                else l.bluetoothPairingReply(a == "accept", QString());
            });
        });
        // test only: the system bus lets only root (bluetoothd) call an agent, so the script plays BlueZ
        // against the same agent object exported on the session bus
        QDBusConnection::sessionBus().registerObject("/org/ncde/lelan/bluetooth_agent", l.m_btAgent, QDBusConnection::ExportAllSlots);
        QTimer::singleShot(2500, [&] {
            out("AGENT bus=%s", QDBusConnection::sessionBus().baseService().toUtf8() + " default=" + (l.m_btAgentDefault ? "1" : "0"));
        });
        QTimer::singleShot(qEnvironmentVariableIntValue("RUN_MS") ?: 20000, [&] { app.quit(); });
    } else if (mode == "enable") {
        QTimer::singleShot(2000, [&] { out("BEFORE %s", state()); l.setBluetoothEnabled(true); });
        QTimer::singleShot(8000, [&] { out("AFTER %s", state()); app.quit(); });
    }
    return app.exec();
}
