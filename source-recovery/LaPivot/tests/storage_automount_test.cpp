// storage_automount_test — S7 (auto-mount on insertion) in Lelan_storage.cpp. UDisks trees are built here
// and fed to Lelan::applyStorageObjects, so every rule can be hit without plugging anything in. A mount
// Lelan decides on goes to the real UDisks2: for invented object paths it answers "no such object" (seen
// here as volumeFailed on that path = a mount was attempted); AM_REAL_FS = a real throwaway loop image's
// filesystem object, which must end up really mounted (checked by storage_automount_test.sh).
#include <QCoreApplication>
#include <QDateTime>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusVariant>
#include <QTimer>
#include <cstdio>

#define private public
#include "Lelan.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;

static const QString B = "/org/freedesktop/UDisks2/block_devices/";
static const QString D = "/org/freedesktop/UDisks2/drives/";
static qint64 nowUs() { return QDateTime::currentMSecsSinceEpoch() * 1000; }

static QVariant realMountPoints()
{
    static QVariant v = [] {
        const QString dev = qEnvironmentVariable("AM_MOUNTED_BLOCK");            // e.g. sdb1 (read only)
        QDBusMessage m = QDBusMessage::createMethodCall("org.freedesktop.UDisks2", B + dev,
            "org.freedesktop.DBus.Properties", "Get");
        m << QString("org.freedesktop.UDisks2.Filesystem") << QString("MountPoints");
        const QDBusMessage r = QDBusConnection::systemBus().call(m);
        return r.arguments().value(0).value<QDBusVariant>().variant();
    }();
    return v;
}

struct Tree {
    BlueZObjectMap m;
    void drive(const QString &name, bool removable, qint64 detectedUs)
    {
        m[QDBusObjectPath(D + name)]["org.freedesktop.UDisks2.Drive"] = {
            {"Removable", removable}, {"Ejectable", true}, {"CanPowerOff", true},
            {"Vendor", "Test"}, {"Model", name}, {"TimeMediaDetected", detectedUs}};
    }
    // a filesystem; `path` may be a full object path (the real loop image) or a short name
    void fs(const QString &path, const QString &drive, bool hintAuto = true, bool hintIgnore = false,
            bool mounted = false, const QString &cryptoBacking = "/")
    {
        const QString p = path.startsWith('/') ? path : B + path;
        m[QDBusObjectPath(p)]["org.freedesktop.UDisks2.Block"] = {
            {"Drive", QVariant::fromValue(QDBusObjectPath(drive.isEmpty() ? "/" : D + drive))},
            {"Device", QByteArray("/dev/") + path.section('/', -1).toLatin1()}, {"IdLabel", path.section('/', -1)},
            {"IdType", "vfat"}, {"Size", 1000000000ULL}, {"HintAuto", hintAuto}, {"HintIgnore", hintIgnore},
            {"CryptoBackingDevice", QVariant::fromValue(QDBusObjectPath(cryptoBacking))}};
        // MountPoints is a D-Bus aay that only arrives off the bus (a hand-built QDBusArgument cannot be
        // read back), so a mounted one borrows a real mounted filesystem's MountPoints (read-only Get)
        QVariantMap f;
        if (mounted)
            f["MountPoints"] = realMountPoints();
        m[QDBusObjectPath(p)]["org.freedesktop.UDisks2.Filesystem"] = f;
    }
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Lelan l(nullptr, false);
    l.m_storageTimer = new QTimer(&l);                                           // mountVolume's reply restarts it
    l.m_storageTimer->setSingleShot(true);
    QStringList attempted;
    QObject::connect(&l, &Lelan::volumeFailed, [&](const QString &p, const QString &r) {
        attempted << p;
        std::printf("  (mount attempted %s: %s)\n", qPrintable(p.section('/', -1)), qPrintable(r)); });
    int fails = 0;
    const qint64 now = nowUs(), longAgo = now - 600LL * 1000000;

    // each step: feed a tree, wait for UDisks' replies, then compare which invented paths were mounted
    struct Step { const char *what; Tree t; bool autoMount; QStringList expect; };
    QList<Step> steps;
    auto base = [&] { Tree t; t.drive("OLD", true, longAgo); t.fs("old1", "OLD"); return t; };
    { Tree t = base(); t.drive("NEW", true, now); t.fs("new1", "NEW");
      steps.append({"first read (plugged in before login): nothing mounted", t, true, {}}); }
    { Tree t = base(); t.drive("S2", true, now); t.fs("s2a", "S2"); t.fs("s2b", "S2");
      steps.append({"stick inserted, setting on: both partitions mounted", t, true, {"s2a", "s2b"}}); }
    { Tree t = base(); t.drive("S2", true, now); t.fs("s2a", "S2"); t.fs("s2b", "S2");
      steps.append({"same stick next read (user unmounted it): not re-mounted", t, true, {}}); }
    { Tree t = base(); t.drive("ISO", true, now); t.fs("efi", "ISO", true, true); t.fs("nohint", "ISO", false);
      steps.append({"HintIgnore (ARCHISO_EFI) and HintAuto=false partitions: left alone", t, true, {}}); }
    { Tree t = base(); t.drive("OFF", true, now); t.fs("off1", "OFF");
      steps.append({"setting off: inserted stick left alone", t, false, {}}); }
    { Tree t = base(); t.fs("reform", "OLD");
      steps.append({"new filesystem on a stick in for 10 min (reformat): left alone", t, true, {}}); }
    { Tree t = base(); t.drive("MNT", true, now); t.fs("mnt1", "MNT", true, false, true);
      steps.append({"inserted but already mounted: no second mount", t, true, {}}); }
    { Tree t = base(); t.drive("LUKS", true, now); t.fs("clear1", "", true, false, false, B + "luks0");
      t.m[QDBusObjectPath(B + "luks0")]["org.freedesktop.UDisks2.Block"] = {
          {"Drive", QVariant::fromValue(QDBusObjectPath(D + "LUKS"))}, {"HintAuto", true},
          {"CryptoBackingDevice", QVariant::fromValue(QDBusObjectPath("/"))}};
      steps.append({"unlocked LUKS contents: left to unlockVolume", t, true, {}}); }
    { Tree t = base(); t.drive("HDD", false, now); t.fs("hdd1", "HDD");
      steps.append({"non-removable drive: left alone", t, true, {}}); }
    { Tree t = base();
      steps.append({"stick pulled", t, true, {}}); }
    { Tree t = base(); t.drive("S2", true, now); t.fs("s2a", "S2"); t.fs("s2b", "S2");
      steps.append({"same stick plugged in again: mounted again", t, true, {"s2a", "s2b"}}); }
    const QString real = qEnvironmentVariable("AM_REAL_FS");
    if (!real.isEmpty()) {
        Tree t = base(); t.drive("S2", true, now); t.fs("s2a", "S2"); t.fs("s2b", "S2");
        t.drive("REAL", true, now); t.fs(real, "REAL");
        steps.append({"real loop image presented as an inserted stick: mounted for real", t, true, {}});
    }

    int i = 0;
    std::function<void()> next = [&] {
        if (i == steps.size()) {
            std::printf("RESULT %s\n", fails ? "FAIL" : "PASS");
            app.exit(fails ? 1 : 0);
            return;
        }
        const Step &s = steps[i++];
        attempted.clear();
        l.setAutoMountPref(s.autoMount);
        l.applyStorageObjects(s.t.m);
        QTimer::singleShot(1500, [&, s] {
            QStringList got;
            for (const QString &p : attempted) got << p.section('/', -1);
            got.sort();
            const bool ok = got == s.expect;
            if (!ok) ++fails;
            std::printf("%s %s%s\n", ok ? "PASS" : "FAIL", s.what,
                        ok ? "" : qPrintable(" — mounted: [" + got.join(',') + "] want [" + s.expect.join(',') + "]"));
            next();
        });
    };
    next();
    return app.exec();
}
