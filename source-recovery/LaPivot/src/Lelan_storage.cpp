// Lelan — storage: removable drives (UDisks2) — list, mount, unmount, eject (safe to remove), unlock
// encrypted sticks — and the root disk's usage.
//
// Rebuilt from oracle: subscribeToUDisks2, refreshRemovableVolumes (+lambda), mountVolume (+lambda),
// unmountVolume (+lambda), onUDisks2InterfacesAdded/Removed, onUDisks2FilesystemPropertiesChanged,
// refreshDiskUsage, removableVolumes, disk.
// Spec: lelan.md §4 (UDisks2 ObjectManager; a removable volume = Drive.Removable; mount state from
// Filesystem.MountPoints; removableVolumes = the StorageTab model), ncde-efficiency.md §5 #6.
//
// DEFECTS FIXED vs oracle:
//  S1 Mount/Unmount replies were never read and the list was re-read on a fixed 600 ms timer: a
//     failure ("target is busy" — a file still open) looked like success, and the stick could be pulled
//     while still mounted. Failures now arrive as volumeFailed(path, reason); the list follows UDisks.
//  S2 there was no eject: an unmounted stick stayed powered and never became safe to remove.
//     ejectVolume(path) unmounts every filesystem on that drive, locks encrypted ones, ejects and powers
//     the drive off, then volumeEjected(label) says it is safe to remove.
//  S3 every InterfacesAdded/Removed (UDisks job objects appear and vanish on each mount) and every
//     Filesystem property change re-read UDisks' whole object tree. Now only drive/block/filesystem/
//     encryption objects count, and bursts are coalesced into one read (150 ms).
//  S4 storageChanged fired on every read; now only when the list changed.
//  S5 volumes UDisks marks HintIgnore (e.g. an ISO stick's ARCHISO_EFI partition) were listed.
//  S6 encrypted (LUKS) sticks never appeared: the unlocked filesystem sits on a mapper device with no
//     Drive, and the locked one has no Filesystem. Locked ones are listed ("locked": true) and open
//     with unlockVolume(path, passphrase); unlocked ones are listed under their stick.
//  S7 "Auto-mount USB on insertion" (Settings::autoMountUsb) was never acted on by LaPivot; a separate
//     helper daemon (ncde-automount: udevadm monitor + udisksctl) did it, and it mounted anything with a
//     filesystem on the USB bus — including partitions UDisks says to leave alone (HintIgnore, e.g. an
//     ISO stick's ARCHISO_EFI) or not to auto-mount (HintAuto false), and re-mounted after a reformat.
//     Lelan now mounts a filesystem when it newly appears on a removable drive whose media arrived in the
//     last minute (Drive.TimeMediaDetected), only if the setting is on and UDisks' hints allow it. What
//     was plugged in before login, and what the user unmounted, is left alone. Unlocked LUKS contents are
//     mounted by unlockVolume itself.
#include "Lelan.h"
#include "lelan_dbus_relay.h"

#include <QDBusArgument>
#include <QDateTime>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QStorageInfo>
#include <QTimer>
#include <QtLogging>

#include <memory>

namespace {
const QString kUD = QStringLiteral("org.freedesktop.UDisks2");
const QString kUDPath = QStringLiteral("/org/freedesktop/UDisks2");
const QString kObjMgr = QStringLiteral("org.freedesktop.DBus.ObjectManager");
const QString kDrive = QStringLiteral("org.freedesktop.UDisks2.Drive");
const QString kBlock = QStringLiteral("org.freedesktop.UDisks2.Block");
const QString kFs = QStringLiteral("org.freedesktop.UDisks2.Filesystem");
const QString kEncrypted = QStringLiteral("org.freedesktop.UDisks2.Encrypted");
const QString kPartition = QStringLiteral("org.freedesktop.UDisks2.Partition");

using ManagedObjects = QMap<QDBusObjectPath, QMap<QString, QVariantMap>>;

QString objPath(const QVariant &v) { return v.value<QDBusObjectPath>().path(); }

// oracle ay2str: a byte string ("ay") up to its first NUL
QString bytesToString(const QVariant &v)
{
    QByteArray b;
    if (v.canConvert<QDBusArgument>()) v.value<QDBusArgument>() >> b;
    else b = v.toByteArray();
    return QString::fromLocal8Bit(b.constData());
}

QStringList mountPoints(const QVariant &v)
{
    QStringList out;
    if (!v.canConvert<QDBusArgument>())
        return out;
    const QDBusArgument arg = v.value<QDBusArgument>();
    arg.beginArray();
    while (!arg.atEnd()) {
        QByteArray b;
        arg >> b;
        if (!b.isEmpty())
            out << QString::fromLocal8Bit(b.constData());
    }
    arg.endArray();
    return out;
}

void onReply(QObject *ctx, const QDBusMessage &call, std::function<void(QDBusPendingCallWatcher *)> done, int timeoutMs = -1)
{
    auto *w = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(call, timeoutMs), ctx);
    QObject::connect(w, &QDBusPendingCallWatcher::finished, ctx, [done = std::move(done)](QDBusPendingCallWatcher *w) {
        w->deleteLater();
        done(w);
    });
}

QDBusMessage udCall(const QString &path, const QString &iface, const QString &method)
{
    QDBusMessage m = QDBusMessage::createMethodCall(kUD, path, iface, method);
    return m;
}

QString readable(const QDBusError &e)
{
    const QString n = e.name();
    if (n.endsWith(QLatin1String("DeviceBusy")) || e.message().contains(QLatin1String("target is busy")))
        return QStringLiteral("A program is still using the drive. Close its files and try again.");
    if (n.endsWith(QLatin1String("NotAuthorized")) || n.endsWith(QLatin1String("NotAuthorizedCanObtain")))
        return QStringLiteral("Not allowed (this drive needs an administrator)");
    if (n.endsWith(QLatin1String("UnknownObject")) || n.endsWith(QLatin1String("UnknownMethod"))
        || e.message().contains(QLatin1String("does not exist")))
        return QStringLiteral("This drive is no longer connected");
    if (n.endsWith(QLatin1String("AlreadyMounted"))) return QStringLiteral("Already mounted");
    if (n.endsWith(QLatin1String("NotMounted"))) return QStringLiteral("Not mounted");
    if (e.message().contains(QLatin1String("passphrase"), Qt::CaseInsensitive)
        || (n.endsWith(QLatin1String("Failed")) && e.message().contains(QLatin1String("key"))))
        return QStringLiteral("Wrong passphrase");
    return e.message().isEmpty() ? n : e.message();
}
} // namespace

// ---- getters ----
QVariantList Lelan::removableVolumes() const { return m_removableVolumes; }
QVariantMap Lelan::disk() const { return m_disk; }

// ---- subscription ----
void Lelan::subscribeToUDisks2()
{
    static const int registered = [] {
        qDBusRegisterMetaType<QMap<QString, QVariantMap>>();
        qDBusRegisterMetaType<ManagedObjects>();
        return 0;
    }();
    Q_UNUSED(registered);
    if (!m_storageTimer) {                                                      // S3: one read per burst
        m_storageTimer = new QTimer(this);
        m_storageTimer->setSingleShot(true);
        m_storageTimer->setInterval(150);
        connect(m_storageTimer, &QTimer::timeout, this, [this] { refreshRemovableVolumes(); });
    }
    QDBusConnection bus = QDBusConnection::systemBus();
    bus.connect(kUD, kUDPath, kObjMgr, QStringLiteral("InterfacesAdded"), this,
                SLOT(onUDisks2InterfacesAdded(QDBusObjectPath,BlueZInterfaceMap)));
    bus.connect(kUD, kUDPath, kObjMgr, QStringLiteral("InterfacesRemoved"), this,
                SLOT(onUDisks2InterfacesRemoved(QDBusObjectPath,QStringList)));
    // mount points and unlocks change properties, not interfaces; filtered to the two that matter
    if (!m_storageRelay) {
        m_storageRelay = new PropsRelay(this, [this](const QString &, const QString &iface, const QVariantMap &) {
            if (iface == kFs || iface == kEncrypted || iface == kBlock)
                m_storageTimer->start();
        });
        for (const QString &iface : {kFs, kEncrypted})
            bus.connect(kUD, QString(), QStringLiteral("org.freedesktop.DBus.Properties"), QStringLiteral("PropertiesChanged"),
                        {iface}, QStringLiteral("sa{sv}as"), m_storageRelay, SLOT(propertiesChanged(QString,QVariantMap,QStringList)));
    }
    refreshRemovableVolumes();
}

static bool storageRelevant(const QStringList &ifaces)
{
    for (const QString &i : ifaces)
        if (i == kDrive || i == kBlock || i == kFs || i == kEncrypted || i == kPartition)
            return true;
    return false;                                                                // Job, Loop, ... (S3)
}

void Lelan::onUDisks2InterfacesAdded(const QDBusObjectPath &, const BlueZInterfaceMap &ifaces)
{
    if (storageRelevant(ifaces.keys()))
        m_storageTimer->start();
}

void Lelan::onUDisks2InterfacesRemoved(const QDBusObjectPath &, const QStringList &ifaces)
{
    if (storageRelevant(ifaces))
        m_storageTimer->start();
}

void Lelan::onUDisks2FilesystemPropertiesChanged(const QString &, const QVariantMap &, const QStringList &)
{
    m_storageTimer->start();                                                     // (the relay delivers these now)
}

// The volumes the Storage tab shows: every filesystem (and every locked LUKS container) on a removable
// drive, except those UDisks says to hide.
void Lelan::refreshRemovableVolumes()
{
    onReply(this, udCall(kUDPath, kObjMgr, QStringLiteral("GetManagedObjects")), [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<ManagedObjects> reply = *w;
        if (reply.isError()) {
            qWarning() << "[lelan] UDisks2 GetManagedObjects failed:" << reply.error().name() << reply.error().message();
            return;
        }
        applyStorageObjects(reply.value());
    });
}

void Lelan::setAutoMountPref(bool on)
{
    m_autoMount = on;                                                            // S7
}

void Lelan::applyStorageObjects(const BlueZObjectMap &objs)
{
    QHash<QString, QVariantMap> drives;                                      // removable drives only
    for (auto it = objs.cbegin(); it != objs.cend(); ++it)
        if (it->contains(kDrive) && it->value(kDrive).value(QStringLiteral("Removable")).toBool())
            drives.insert(it.key().path(), it->value(kDrive));
    auto driveOf = [&](const QVariantMap &block) {                          // S6: mapper -> backing stick
        QString d = objPath(block.value(QStringLiteral("Drive")));
        const QString backing = objPath(block.value(QStringLiteral("CryptoBackingDevice")));
        if ((d.isEmpty() || d == QLatin1String("/")) && !backing.isEmpty() && backing != QLatin1String("/"))
            d = objPath(objs.value(QDBusObjectPath(backing)).value(kBlock).value(QStringLiteral("Drive")));
        return d;
    };

    QVariantList list;
    QHash<QString, QString> driveOfVolume;
    QSet<QString> filesystems;
    QStringList toAutoMount;                                                     // S7
    for (auto it = objs.cbegin(); it != objs.cend(); ++it) {
        const QVariantMap block = it->value(kBlock);
        if (block.isEmpty() || block.value(QStringLiteral("HintIgnore")).toBool())
            continue;                                                        // S5
        const QString drive = driveOf(block);
        if (!drives.contains(drive))
            continue;
        const bool hasFs = it->contains(kFs);
        const bool locked = it->contains(kEncrypted)
            && objPath(it->value(kEncrypted).value(QStringLiteral("CleartextDevice"))) == QLatin1String("/");
        if (!hasFs && !locked)
            continue;
        const QStringList mps = hasFs ? mountPoints(it->value(kFs).value(QStringLiteral("MountPoints"))) : QStringList();
        QString label = block.value(QStringLiteral("IdLabel")).toString();
        if (label.isEmpty() && !objPath(block.value(QStringLiteral("CryptoBackingDevice"))).isEmpty()) {
            const QVariantMap backing = objs.value(QDBusObjectPath(objPath(block.value(QStringLiteral("CryptoBackingDevice"))))).value(kBlock);
            label = backing.value(QStringLiteral("IdLabel")).toString();
        }
        const QVariantMap d = drives.value(drive);
        list.append(QVariantMap{
            {QStringLiteral("path"), it.key().path()},
            {QStringLiteral("device"), bytesToString(block.value(QStringLiteral("Device")))},
            {QStringLiteral("label"), label},
            {QStringLiteral("size"), block.value(QStringLiteral("Size")).toULongLong()},
            {QStringLiteral("fsType"), block.value(QStringLiteral("IdType")).toString()},
            {QStringLiteral("mounted"), !mps.isEmpty()},
            {QStringLiteral("mountPoint"), mps.value(0)},
            {QStringLiteral("canUnmount"), !mps.isEmpty()},
            {QStringLiteral("locked"), locked},                                               // S6
            {QStringLiteral("encrypted"), locked || (!objPath(block.value(QStringLiteral("CryptoBackingDevice"))).isEmpty()
                                                 && objPath(block.value(QStringLiteral("CryptoBackingDevice"))) != QLatin1String("/"))},
            {QStringLiteral("canEject"), d.value(QStringLiteral("Ejectable")).toBool() || d.value(QStringLiteral("CanPowerOff")).toBool()},
            {QStringLiteral("drive"), [&] {
                const QString vendor = d.value(QStringLiteral("Vendor")).toString().trimmed();
                const QString model = d.value(QStringLiteral("Model")).toString().trimmed();
                return (vendor + QLatin1Char(' ') + model).trimmed(); }()},
        });
        driveOfVolume.insert(it.key().path(), drive);
        if (hasFs) {                                                             // S7: a new filesystem
            filesystems.insert(it.key().path());
            const QString backing = objPath(block.value(QStringLiteral("CryptoBackingDevice")));
            // inserted = the stick's media arrived in the last minute (not a partition made later, e.g. by
            // formatting a stick that has been in for an hour); the first read = plugged in before login
            const qint64 insertedUs = d.value(QStringLiteral("TimeMediaDetected")).toLongLong();
            const bool justInserted = insertedUs > 0 && QDateTime::currentMSecsSinceEpoch() * 1000 - insertedUs < 60LL * 1000000;
            if (m_storageSeeded && justInserted && !m_seenFilesystems.contains(it.key().path()) && mps.isEmpty()
                && block.value(QStringLiteral("HintAuto")).toBool()
                && (backing.isEmpty() || backing == QLatin1String("/")))         // unlockVolume mounts those
                toAutoMount << it.key().path();
        }
    }
    m_volumeDrive = driveOfVolume;
    m_storageObjects = objs;
    if (list != m_removableVolumes) {                                        // S4
        m_removableVolumes = list;
        emit storageChanged();
    }
    m_seenFilesystems = filesystems;                                             // gone = may come back as new
    m_storageSeeded = true;
    if (m_autoMount)
        for (const QString &fs : std::as_const(toAutoMount))
            mountVolume(fs);
}

// ---- actions ----
void Lelan::mountVolume(const QString &path)
{
    if (path.isEmpty())
        return;
    QDBusMessage m = udCall(path, kFs, QStringLiteral("Mount"));
    m << QVariantMap();
    onReply(this, m, [this, path](QDBusPendingCallWatcher *w) {
        if (w->isError() && !w->error().name().endsWith(QLatin1String("AlreadyMounted")))
            emit volumeFailed(path, readable(w->error()));
        m_storageTimer->start();
    }, 120000);
}

void Lelan::unmountVolume(const QString &path)
{
    if (path.isEmpty())
        return;
    QDBusMessage m = udCall(path, kFs, QStringLiteral("Unmount"));
    m << QVariantMap();
    onReply(this, m, [this, path](QDBusPendingCallWatcher *w) {
        if (w->isError() && !w->error().name().endsWith(QLatin1String("NotMounted")))
            emit volumeFailed(path, readable(w->error()));                      // S1
        m_storageTimer->start();
    }, 120000);
}

// S6: open a locked LUKS stick, then mount what is inside
void Lelan::unlockVolume(const QString &path, const QString &passphrase)
{
    if (path.isEmpty())
        return;
    QDBusMessage m = udCall(path, kEncrypted, QStringLiteral("Unlock"));
    m << passphrase << QVariantMap();
    onReply(this, m, [this, path](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QDBusObjectPath> reply = *w;
        if (reply.isError()) {
            emit volumeFailed(path, readable(reply.error()));
            return;
        }
        mountVolume(reply.value().path());
    }, 120000);
}

// S2: everything on that stick unmounted (and locked), then eject + power off -> safe to remove
void Lelan::ejectVolume(const QString &path)
{
    const QString drive = m_volumeDrive.value(path);
    if (drive.isEmpty()) {                                                       // pulled / gone meanwhile
        emit volumeFailed(path, QStringLiteral("This drive is no longer connected"));
        m_storageTimer->start();
        return;
    }
    QString label;
    QStringList mounted, cleartextToLock;
    for (auto it = m_storageObjects.cbegin(); it != m_storageObjects.cend(); ++it) {
        const QVariantMap block = it->value(kBlock);
        if (block.isEmpty())
            continue;
        const QString backing = objPath(block.value(QStringLiteral("CryptoBackingDevice")));
        const bool onDrive = objPath(block.value(QStringLiteral("Drive"))) == drive
            || (!backing.isEmpty() && backing != QLatin1String("/")
                && objPath(m_storageObjects.value(QDBusObjectPath(backing)).value(kBlock).value(QStringLiteral("Drive"))) == drive);
        if (!onDrive)
            continue;
        if (it->contains(kFs) && !mountPoints(it->value(kFs).value(QStringLiteral("MountPoints"))).isEmpty())
            mounted << it.key().path();
        if (it->contains(kEncrypted) && objPath(it->value(kEncrypted).value(QStringLiteral("CleartextDevice"))) != QLatin1String("/"))
            cleartextToLock << it.key().path();
        if (it.key().path() == path)
            label = block.value(QStringLiteral("IdLabel")).toString();
    }
    const QVariantMap d = m_storageObjects.value(QDBusObjectPath(drive)).value(kDrive);
    if (label.isEmpty())
        label = (d.value(QStringLiteral("Vendor")).toString().trimmed() + QLatin1Char(' ') + d.value(QStringLiteral("Model")).toString().trimmed()).trimmed();

    // a chain of steps; the first failure stops it and says why
    auto steps = std::make_shared<QList<QDBusMessage>>();
    for (const QString &fs : std::as_const(mounted)) {
        QDBusMessage m = udCall(fs, kFs, QStringLiteral("Unmount"));
        m << QVariantMap();
        steps->append(m);
    }
    for (const QString &enc : std::as_const(cleartextToLock)) {
        QDBusMessage m = udCall(enc, kEncrypted, QStringLiteral("Lock"));
        m << QVariantMap();
        steps->append(m);
    }
    if (d.value(QStringLiteral("Ejectable")).toBool()) {
        QDBusMessage m = udCall(drive, kDrive, QStringLiteral("Eject"));
        m << QVariantMap();
        steps->append(m);
    }
    if (d.value(QStringLiteral("CanPowerOff")).toBool()) {
        QDBusMessage m = udCall(drive, kDrive, QStringLiteral("PowerOff"));
        m << QVariantMap();
        steps->append(m);
    }
    auto run = std::make_shared<std::function<void()>>();
    *run = [this, steps, run, path, label] {
        if (steps->isEmpty()) {
            emit volumeEjected(label);
            m_storageTimer->start();
            return;
        }
        const QDBusMessage m = steps->takeFirst();
        onReply(this, m, [this, run, path, m](QDBusPendingCallWatcher *w) {
            const QString n = w->isError() ? w->error().name() : QString();
            // a drive that is already gone / not mounted / media already out is fine
            if (w->isError() && !n.endsWith(QLatin1String("NotMounted")) && !n.endsWith(QLatin1String("NotSupported"))
                && !(m.member() == QLatin1String("Eject") && n.endsWith(QLatin1String("Failed")))) {
                emit volumeFailed(path, readable(w->error()));
                m_storageTimer->start();
                return;
            }
            (*run)();
        }, 120000);
    };
    (*run)();
}

// ---- root disk (the once-a-minute coalesced tick calls this) ----
void Lelan::refreshDiskUsage()
{
    const QStorageInfo root(QStringLiteral("/"));
    if (!root.isValid() || !root.isReady() || root.bytesTotal() < 1)
        return;
    const qint64 total = root.bytesTotal();
    const qint64 free = root.bytesFree();
    const qint64 used = total - free;
    const int pct = int(double(used) / double(total) * 100.0 + 0.5);
    if (pct == m_disk.value(QStringLiteral("usedPercent")).toInt() && total == m_disk.value(QStringLiteral("totalBytes")).toLongLong())
        return;                                                                  // oracle's own change check
    m_disk.insert(QStringLiteral("usedBytes"), used);
    m_disk.insert(QStringLiteral("freeBytes"), free);
    m_disk.insert(QStringLiteral("totalBytes"), total);
    m_disk.insert(QStringLiteral("usedPercent"), pct);
    emit diskChanged();
}
