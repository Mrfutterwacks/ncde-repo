// storage_live_test — one Lelan_storage.cpp action per run against the real UDisks2 (driven by
// storage_live_test.sh on throwaway loop images). ST_MODE: list | watch | mount | unmount | unlock | eject;
// ST_PATH = volume object path; ST_PASS = passphrase. Prints LIST (removableVolumes), FAILED/EJECTED
// lines, and ME=<bus name> (so the script can count this process's own GetManagedObjects calls).
#include <QCoreApplication>
#include <QDBusConnection>
#include <QJsonDocument>
#include <QTimer>
#include <cstdio>

#define private public
#include "Lelan.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    const QString mode = qEnvironmentVariable("ST_MODE", "list"), path = qEnvironmentVariable("ST_PATH");
    Lelan l(nullptr, false);
    int storageChanged = 0;
    QObject::connect(&l, &Lelan::storageChanged, [&] { ++storageChanged; });
    QObject::connect(&l, &Lelan::volumeFailed, [](const QString &p, const QString &r) { std::printf("FAILED %s | %s\n", qPrintable(p), qPrintable(r)); std::fflush(stdout); });
    QObject::connect(&l, &Lelan::volumeEjected, [](const QString &label) { std::printf("EJECTED %s\n", qPrintable(label)); std::fflush(stdout); });
    std::printf("ME=%s\n", qPrintable(QDBusConnection::systemBus().baseService())); std::fflush(stdout);
    l.subscribeToUDisks2();
    auto list = [&] { std::printf("LIST %s\n", QJsonDocument::fromVariant(l.removableVolumes()).toJson(QJsonDocument::Compact).constData()); std::fflush(stdout); };
    QTimer::singleShot(1500, [&] {
        if (mode == "list") { list(); app.quit(); return; }
        if (mode == "watch") {                    // stay subscribed while the script makes a burst of changes
            QTimer::singleShot(qEnvironmentVariableIntValue("WATCH_MS") ?: 15000, [&] {
                std::printf("WATCH storageChanged=%d\n", storageChanged); list(); app.quit(); });
            return;
        }
        if (mode == "mount") l.mountVolume(path);
        else if (mode == "unmount") l.unmountVolume(path);
        else if (mode == "unlock") l.unlockVolume(path, qEnvironmentVariable("ST_PASS"));
        else if (mode == "eject") l.ejectVolume(path);
        QTimer::singleShot(qEnvironmentVariableIntValue("ACT_MS") ?: 6000, [&] { list(); app.quit(); });
    });
    return app.exec();
}
