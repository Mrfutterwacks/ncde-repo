// Lelan — Bluetooth: BlueZ adapter (power, discoverable, scanning), devices (connect, pair, remove),
// the Bluetooth audio device, and NCDE's own pairing agent (org.bluez.Agent1).
//
// Rebuilt from oracle: subscribeToBlueZ, rebuildBluetooth (+lambda), setBluetoothEnabled,
// setBluetoothDiscoverable, bluetoothConnect/Disconnect/Pair/Remove, bluetoothScan,
// onBlueZInterfacesAdded/Removed, onBlueZPropertiesChanged, the getters.
// Spec: lelan.md §4/§5 (BlueZ ObjectManager, InterfacesAdded/Removed, Device1 Connected/Name, BT
// audio), ncde-efficiency.md §5 #6 (patch the changed entry), OPEN-ITEMS "Bluetooth pairing —
// register org.bluez.Agent1 in Lelan (passkey -> QML confirm dialog; keyboards/braille/hearing aids)
// + branch BluetoothTab on `paired` to call bluetoothPair". Operator 2026-09-30: Lelan owns pairing;
// blueman is only the stopgap until this ships.
//
// DEFECTS FIXED vs oracle:
//  B1 every InterfacesAdded/Removed (any BlueZ object, GATT services included) and every relevant
//     property change re-fetched BlueZ's whole object tree (GetManagedObjects); during a scan that is
//     once per nearby device. Now devices/adapter are patched from the signal itself.
//  B2 bluetoothChanged fired on every rebuild, changed or not.
//  B3 bluetoothScan started discovery and never stopped it: the radio kept scanning for the rest of
//     the session (battery; it also degrades Bluetooth audio). Now it stops after 30 s, and before a
//     pairing starts. bluetoothScanning (Adapter Discovering) lets the tab show it.
//  B4 no pairing agent anywhere in the binary: pairing that needs a code or a confirmation (phones,
//     keyboards, hearing aids) could not complete. Lelan now registers org.bluez.Agent1
//     (KeyboardDisplay) as the default agent; requests appear as lelan.bluetoothPairing and are
//     answered with bluetoothPairingReply(). Unanswered requests are rejected after 60 s.
//  B5 a paired device was not marked Trusted, so it could not reconnect by itself (BlueZ asks the
//     agent to authorise each incoming connection of an untrusted device). Pair -> Trusted -> Connect.
//  B6 connect / disconnect / pair / remove / power failures were silent (asyncCall, no reply read):
//     bluetoothFailed(address, reason) now says why.
//  B7 the device type came from the Icon by substring: "input-mouse" and "input-gaming" became
//     "keyboard". Types now follow BlueZ's icon names (headset, keyboard, mouse, gamepad, phone,
//     computer, tablet).
//  B8 lelan.bluetooth (a Q_PROPERTY) was never written: always {}. It now carries the adapter summary
//     {adapter, name, address, powered, discoverable, discovering, connected}.
//  B9 with two adapters the one listed last won; now the current one is kept while present, else a
//     powered one, else the first. Devices of other adapters are not mixed in.
//  B10 turning Bluetooth on while it is rfkill soft-blocked (airplane mode, Fn key) failed silently.
//     Lelan now unblocks it (/dev/rfkill is the session's through uaccess) and powers the adapter; a
//     hardware block is reported through bluetoothFailed.
//  B11 nameless beacons found by a scan (no Name, only an address) filled the list. Unpaired devices
//     without a name are no longer listed.
#include "Lelan.h"
#include "lelan_dbus_relay.h"

#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusContext>
#include <QDBusError>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QtLogging>

#include <fcntl.h>
#include <linux/rfkill.h>
#include <unistd.h>

namespace {
const QString kBlueZ = QStringLiteral("org.bluez");
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QString kObjMgr = QStringLiteral("org.freedesktop.DBus.ObjectManager");
const QString kAdapter = QStringLiteral("org.bluez.Adapter1");
const QString kDevice = QStringLiteral("org.bluez.Device1");
const QString kAgentPath = QStringLiteral("/org/ncde/lelan/bluetooth_agent");
constexpr int kScanMs = 30000;
constexpr int kPairingAnswerMs = 60000;

using ManagedObjects = QMap<QDBusObjectPath, QMap<QString, QVariantMap>>;

// BlueZ Icon names (freedesktop icon naming) -> the types the Bluetooth tab draws
QString deviceType(const QString &icon)
{
    if (icon.startsWith(QLatin1String("audio-"))) return QStringLiteral("headset");
    if (icon == QLatin1String("input-keyboard")) return QStringLiteral("keyboard");
    if (icon == QLatin1String("input-mouse")) return QStringLiteral("mouse");
    if (icon == QLatin1String("input-gaming")) return QStringLiteral("gamepad");
    if (icon == QLatin1String("input-tablet")) return QStringLiteral("tablet");
    if (icon == QLatin1String("phone")) return QStringLiteral("phone");
    if (icon == QLatin1String("computer")) return QStringLiteral("computer");
    return QString();
}

QString failureText(const QDBusError &e)
{
    const QString n = e.name();
    if (n.endsWith(QLatin1String("AuthenticationFailed")) || n.endsWith(QLatin1String("AuthenticationRejected")))
        return QStringLiteral("Pairing was refused (wrong code, or declined on the device)");
    if (n.endsWith(QLatin1String("AuthenticationCanceled"))) return QStringLiteral("Pairing was cancelled");
    if (n.endsWith(QLatin1String("AuthenticationTimeout")) || e.type() == QDBusError::NoReply)
        return QStringLiteral("The device did not answer in time");
    if (n.endsWith(QLatin1String("ConnectionAttemptFailed")) || n.endsWith(QLatin1String("Failed")))
        return e.message().isEmpty() ? QStringLiteral("Could not reach the device") : e.message();
    if (n.endsWith(QLatin1String("NotReady"))) return QStringLiteral("Bluetooth is off");
    return e.message().isEmpty() ? n : e.message();
}

// rfkill: is Bluetooth soft- / hard-blocked, and lift a soft block (uaccess gives the session /dev/rfkill)
struct RfkillState { bool present = false; bool soft = false; bool hard = false; };
RfkillState bluetoothRfkill()
{
    RfkillState st;
    const QDir dir(QStringLiteral("/sys/class/rfkill"));
    for (const QString &e : dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        auto read = [&](const char *f) {
            QFile file(dir.filePath(e) + QLatin1Char('/') + QLatin1String(f));
            return file.open(QIODevice::ReadOnly) ? QString::fromLatin1(file.readAll()).trimmed() : QString();
        };
        if (read("type") != QLatin1String("bluetooth"))
            continue;
        st.present = true;
        st.soft = st.soft || read("soft") == QLatin1String("1");
        st.hard = st.hard || read("hard") == QLatin1String("1");
    }
    return st;
}

bool unblockBluetooth()
{
    const int fd = ::open("/dev/rfkill", O_WRONLY | O_CLOEXEC);
    if (fd < 0)
        return false;
    rfkill_event ev{};
    ev.type = RFKILL_TYPE_BLUETOOTH;
    ev.op = RFKILL_OP_CHANGE_ALL;
    ev.soft = 0;
    const bool ok = ::write(fd, &ev, RFKILL_EVENT_SIZE_V1) == RFKILL_EVENT_SIZE_V1;
    ::close(fd);
    return ok;
}

void onReply(QObject *ctx, const QDBusMessage &call, std::function<void(QDBusPendingCallWatcher *)> done, int timeoutMs = -1)
{
    auto *w = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(call, timeoutMs), ctx);
    QObject::connect(w, &QDBusPendingCallWatcher::finished, ctx, [done = std::move(done)](QDBusPendingCallWatcher *w) {
        w->deleteLater();
        done(w);
    });
}

QDBusMessage btSet(const QString &path, const QString &iface, const QString &name, const QVariant &value)
{
    QDBusMessage m = QDBusMessage::createMethodCall(kBlueZ, path, kFdProps, QStringLiteral("Set"));
    m << iface << name << QVariant::fromValue(QDBusVariant(value));
    return m;
}
} // namespace

// org.bluez.Agent1, exported on the system bus. Each request is handed to Lelan, which shows it in the
// Bluetooth tab (lelan.bluetoothPairing) and answers through the message kept for a delayed reply.
class BluetoothAgent : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.bluez.Agent1")
public:
    explicit BluetoothAgent(Lelan *lelan) : QObject(lelan), m_lelan(lelan) {}
public slots:
    void Release() {}
    QString RequestPinCode(const QDBusObjectPath &device)
    {
        defer(QStringLiteral("pin"), device, QString());
        return QString();
    }
    void DisplayPinCode(const QDBusObjectPath &device, const QString &pincode)
    {
        m_lelan->btAgentShow(QStringLiteral("display"), device.path(), pincode);
    }
    uint RequestPasskey(const QDBusObjectPath &device)
    {
        defer(QStringLiteral("passkey"), device, QString());
        return 0;
    }
    void DisplayPasskey(const QDBusObjectPath &device, uint passkey, ushort)
    {
        m_lelan->btAgentShow(QStringLiteral("display"), device.path(), QStringLiteral("%1").arg(passkey, 6, 10, QLatin1Char('0')));
    }
    void RequestConfirmation(const QDBusObjectPath &device, uint passkey)
    {
        defer(QStringLiteral("confirm"), device, QStringLiteral("%1").arg(passkey, 6, 10, QLatin1Char('0')));
    }
    void RequestAuthorization(const QDBusObjectPath &device)
    {
        defer(QStringLiteral("authorize"), device, QString());
    }
    void AuthorizeService(const QDBusObjectPath &device, const QString &)
    {
        // a paired device's services are its own; anything else is refused
        if (!m_lelan->btDevicePaired(device.path()))
            sendErrorReply(QStringLiteral("org.bluez.Error.Rejected"), QStringLiteral("Not paired"));
    }
    void Cancel() { m_lelan->btAgentCancel(); }
private:
    void defer(const QString &kind, const QDBusObjectPath &device, const QString &code)
    {
        setDelayedReply(true);
        m_lelan->btAgentAsk(kind, device.path(), code, message(), connection().name());
    }
    Lelan *m_lelan;
};

// ---- getters ----
QVariantMap Lelan::bluetooth() const { return m_bluetooth; }
bool Lelan::bluetoothEnabled() const { return m_btPowered; }
bool Lelan::bluetoothDiscoverable() const { return m_btDiscoverable; }
QVariantList Lelan::bluetoothDevices() const { return m_bluetoothDevices; }
QVariantMap Lelan::bluetoothAudioDevice() const { return m_bluetoothAudioDevice; }
bool Lelan::bluetoothScanning() const { return m_btDiscovering; }
QVariantMap Lelan::bluetoothPairing() const { return m_bluetoothPairing; }

// ---- subscription ----
void Lelan::subscribeToBlueZ()
{
    static const int registered = [] {
        qDBusRegisterMetaType<QMap<QString, QVariantMap>>();
        qDBusRegisterMetaType<ManagedObjects>();
        return 0;
    }();
    Q_UNUSED(registered);
    QDBusConnection bus = QDBusConnection::systemBus();
    bus.connect(kBlueZ, QStringLiteral("/"), kObjMgr, QStringLiteral("InterfacesAdded"), this,
                SLOT(onBlueZInterfacesAdded(QDBusObjectPath,BlueZInterfaceMap)));
    bus.connect(kBlueZ, QStringLiteral("/"), kObjMgr, QStringLiteral("InterfacesRemoved"), this,
                SLOT(onBlueZInterfacesRemoved(QDBusObjectPath,QStringList)));
    if (!m_btRelay) {
        m_btRelay = new PropsRelay(this, [this](const QString &path, const QString &iface, const QVariantMap &changed) {
            if (iface == kDevice)
                patchBtDevice(path, changed);
            else if (iface == kAdapter && path == m_btAdapter)
                onBlueZPropertiesChanged(iface, changed, {});
        });
        for (const QString &iface : {kDevice, kAdapter})
            bus.connect(kBlueZ, QString(), kFdProps, QStringLiteral("PropertiesChanged"), {iface},
                        QStringLiteral("sa{sv}as"), m_btRelay, SLOT(propertiesChanged(QString,QVariantMap,QStringList)));
    }
    if (!m_btScanTimer) {
        m_btScanTimer = new QTimer(this);
        m_btScanTimer->setSingleShot(true);
        m_btScanTimer->setInterval(kScanMs);
        connect(m_btScanTimer, &QTimer::timeout, this, [this] { stopBtScan(); });
        m_btPairingTimer = new QTimer(this);
        m_btPairingTimer->setSingleShot(true);
        m_btPairingTimer->setInterval(kPairingAnswerMs);
        connect(m_btPairingTimer, &QTimer::timeout, this, [this] { bluetoothPairingReply(false, QString()); });
    }
    registerBtAgent();
    rebuildBluetooth();
}

// B4: NCDE's pairing agent, default for the machine while LaPivot runs
void Lelan::registerBtAgent()
{
    if (!m_btAgent) {
        m_btAgent = new BluetoothAgent(this);
        if (!QDBusConnection::systemBus().registerObject(kAgentPath, m_btAgent, QDBusConnection::ExportAllSlots))
            qWarning() << "[lelan] could not export the Bluetooth agent:" << QDBusConnection::systemBus().lastError().message();
    }
    QDBusMessage reg = QDBusMessage::createMethodCall(kBlueZ, QStringLiteral("/org/bluez"), QStringLiteral("org.bluez.AgentManager1"),
                                                      QStringLiteral("RegisterAgent"));
    reg << QVariant::fromValue(QDBusObjectPath(kAgentPath)) << QStringLiteral("KeyboardDisplay");
    onReply(this, reg, [this](QDBusPendingCallWatcher *w) {
        if (w->isError() && !w->error().name().endsWith(QLatin1String("AlreadyExists"))) {
            qWarning() << "[lelan] BlueZ RegisterAgent failed:" << w->error().name() << w->error().message();
            return;
        }
        QDBusMessage def = QDBusMessage::createMethodCall(kBlueZ, QStringLiteral("/org/bluez"), QStringLiteral("org.bluez.AgentManager1"),
                                                          QStringLiteral("RequestDefaultAgent"));
        def << QVariant::fromValue(QDBusObjectPath(kAgentPath));
        onReply(this, def, [this](QDBusPendingCallWatcher *w) {
            m_btAgentDefault = !w->isError();
            if (w->isError())
                qWarning() << "[lelan] BlueZ RequestDefaultAgent failed:" << w->error().name() << w->error().message();
        });
    });
}

// Whole tree once (start, BlueZ restart); afterwards only patches.
void Lelan::rebuildBluetooth()
{
    QDBusMessage call = QDBusMessage::createMethodCall(kBlueZ, QStringLiteral("/"), kObjMgr, QStringLiteral("GetManagedObjects"));
    onReply(this, call, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<ManagedObjects> reply = *w;
        if (reply.isError()) {
            qWarning() << "[lelan] BlueZ GetManagedObjects failed:" << reply.error().name() << reply.error().message();
            return;
        }
        const ManagedObjects objects = reply.value();
        // B9: pick the adapter
        QString keep, powered, first;
        for (auto it = objects.cbegin(); it != objects.cend(); ++it) {
            if (!it->contains(kAdapter)) continue;
            const QString p = it.key().path();
            if (p == m_btAdapter) keep = p;
            if (powered.isEmpty() && it->value(kAdapter).value(QStringLiteral("Powered")).toBool()) powered = p;
            if (first.isEmpty()) first = p;
        }
        m_btAdapter = !keep.isEmpty() ? keep : !powered.isEmpty() ? powered : first;
        m_btAdapterProps = m_btAdapter.isEmpty() ? QVariantMap() : objects.value(QDBusObjectPath(m_btAdapter)).value(kAdapter);
        m_btDevices.clear();
        for (auto it = objects.cbegin(); it != objects.cend(); ++it)
            if (it->contains(kDevice))
                m_btDevices.insert(it.key().path(), it->value(kDevice));
        publishBluetooth();
        if (m_btWantPowered && !m_btAdapter.isEmpty() && !m_btPowered)
            setBluetoothEnabled(true);                                          // B10: adapter came back after unblock
    });
}

void Lelan::onBlueZInterfacesAdded(const QDBusObjectPath &path, const BlueZInterfaceMap &ifaces)
{
    if (ifaces.contains(kAdapter)) {
        rebuildBluetooth();                                                      // adapters are rare: re-pick
        return;
    }
    if (!ifaces.contains(kDevice))
        return;                                                                  // B1: GATT etc. ignored
    m_btDevices.insert(path.path(), ifaces.value(kDevice));
    publishBluetooth();
}

void Lelan::onBlueZInterfacesRemoved(const QDBusObjectPath &path, const QStringList &ifaces)
{
    if (ifaces.contains(kAdapter) && path.path() == m_btAdapter) {
        rebuildBluetooth();
        return;
    }
    if (ifaces.contains(kDevice) && m_btDevices.remove(path.path()))
        publishBluetooth();
}

// Adapter1 properties of the adapter in use (delivered by the relay, which knows the path).
void Lelan::onBlueZPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &)
{
    if (iface != kAdapter)
        return;
    for (auto it = changed.cbegin(); it != changed.cend(); ++it)
        m_btAdapterProps.insert(it.key(), it.value());
    publishBluetooth();
}

void Lelan::patchBtDevice(const QString &path, const QVariantMap &changed)
{
    auto it = m_btDevices.find(path);
    if (it == m_btDevices.end())
        return;
    for (auto c = changed.cbegin(); c != changed.cend(); ++c)
        it->insert(c.key(), c.value());
    publishBluetooth();                                                          // published only on a visible change
}

bool Lelan::btDevicePaired(const QString &path) const
{
    return m_btDevices.value(path).value(QStringLiteral("Paired")).toBool();
}

// B2/B8/B11: recompute everything the shell sees from the cached BlueZ state; emit only what changed.
void Lelan::publishBluetooth()
{
    const bool powered = m_btAdapterProps.value(QStringLiteral("Powered")).toBool();
    const bool discoverable = m_btAdapterProps.value(QStringLiteral("Discoverable")).toBool();
    const bool discovering = m_btAdapterProps.value(QStringLiteral("Discovering")).toBool();

    QVariantList devices;
    QHash<QString, QString> byAddress;
    QVariantMap audio;
    int connected = 0;
    for (auto it = m_btDevices.cbegin(); it != m_btDevices.cend(); ++it) {
        const QVariantMap &d = it.value();
        if (d.value(QStringLiteral("Adapter")).value<QDBusObjectPath>().path() != m_btAdapter)
            continue;                                                            // B9
        const bool paired = d.value(QStringLiteral("Paired")).toBool();
        const QString name = d.value(QStringLiteral("Name")).toString();
        if (!paired && name.isEmpty())
            continue;                                                            // B11
        const QString alias = d.value(QStringLiteral("Alias")).toString();
        const QString address = d.value(QStringLiteral("Address")).toString();
        const bool isConnected = d.value(QStringLiteral("Connected")).toBool();
        const QVariantMap entry{
            {QStringLiteral("name"), alias.isEmpty() ? name : alias},
            {QStringLiteral("address"), address},
            {QStringLiteral("type"), deviceType(d.value(QStringLiteral("Icon")).toString())},   // B7
            {QStringLiteral("paired"), paired},
            {QStringLiteral("connected"), isConnected},
        };
        devices.append(entry);
        byAddress.insert(address, it.key());
        connected += isConnected;
        if (audio.isEmpty() && isConnected && entry.value(QStringLiteral("type")) == QLatin1String("headset"))
            audio = entry;
    }
    m_btAddrToPath = byAddress;
    const QVariantMap summary{
        {QStringLiteral("adapter"), m_btAdapter},
        {QStringLiteral("name"), m_btAdapterProps.value(QStringLiteral("Alias"))},
        {QStringLiteral("address"), m_btAdapterProps.value(QStringLiteral("Address"))},
        {QStringLiteral("powered"), powered},
        {QStringLiteral("discoverable"), discoverable},
        {QStringLiteral("discovering"), discovering},
        {QStringLiteral("connected"), connected},
    };
    if (!discovering && m_btScanTimer && m_btScanTimer->isActive())
        m_btScanTimer->stop();                                                   // someone else stopped it
    const bool changed = powered != m_btPowered || discoverable != m_btDiscoverable || discovering != m_btDiscovering
                         || devices != m_bluetoothDevices || summary != m_bluetooth;
    m_btPowered = powered;
    m_btDiscoverable = discoverable;
    m_btDiscovering = discovering;
    m_bluetoothDevices = devices;
    m_bluetooth = summary;
    if (changed)
        emit bluetoothChanged();
    if (audio != m_bluetoothAudioDevice) {
        m_bluetoothAudioDevice = audio;
        emit bluetoothAudioDeviceChanged();
    }
}

// ---- adapter ----
void Lelan::setBluetoothEnabled(bool on)
{
    m_btWantPowered = on;
    if (on) {                                                                    // B10
        const RfkillState rf = bluetoothRfkill();
        if (rf.hard) {
            emit bluetoothFailed(QString(), QStringLiteral("Bluetooth is switched off by a hardware switch or key"));
            return;
        }
        if (rf.soft && !unblockBluetooth()) {
            emit bluetoothFailed(QString(), QStringLiteral("Bluetooth is blocked (airplane mode) and could not be unblocked"));
            return;
        }
        if (rf.soft || m_btAdapter.isEmpty())
            return;                                                              // the adapter (re)appears; rebuildBluetooth powers it
    }
    if (m_btAdapter.isEmpty())
        return;
    onReply(this, btSet(m_btAdapter, kAdapter, QStringLiteral("Powered"), on), [this](QDBusPendingCallWatcher *w) {
        if (w->isError())
            emit bluetoothFailed(QString(), failureText(w->error()));
    });
}

void Lelan::setBluetoothDiscoverable(bool on)
{
    if (m_btAdapter.isEmpty())
        return;
    onReply(this, btSet(m_btAdapter, kAdapter, QStringLiteral("Discoverable"), on), [this](QDBusPendingCallWatcher *w) {
        if (w->isError())
            emit bluetoothFailed(QString(), failureText(w->error()));
    });
}

// B3: a scan runs 30 s, then stops (pressing Scan again restarts the 30 s)
void Lelan::bluetoothScan()
{
    if (m_btAdapter.isEmpty() || !m_btPowered) {
        emit bluetoothFailed(QString(), QStringLiteral("Bluetooth is off"));
        return;
    }
    m_btScanTimer->start();
    if (m_btDiscovering)
        return;
    QDBusMessage m = QDBusMessage::createMethodCall(kBlueZ, m_btAdapter, kAdapter, QStringLiteral("StartDiscovery"));
    onReply(this, m, [this](QDBusPendingCallWatcher *w) {
        if (w->isError() && !w->error().name().endsWith(QLatin1String("InProgress"))) {
            m_btScanTimer->stop();
            emit bluetoothFailed(QString(), failureText(w->error()));
        }
    });
}

void Lelan::stopBtScan()
{
    m_btScanTimer->stop();
    if (m_btAdapter.isEmpty() || !m_btDiscovering)
        return;
    QDBusConnection::systemBus().asyncCall(QDBusMessage::createMethodCall(kBlueZ, m_btAdapter, kAdapter, QStringLiteral("StopDiscovery")));
}

// ---- devices ----
void Lelan::bluetoothConnect(const QString &address)
{
    const QString path = m_btAddrToPath.value(address);
    if (path.isEmpty())
        return;
    onReply(this, QDBusMessage::createMethodCall(kBlueZ, path, kDevice, QStringLiteral("Connect")), [this, address](QDBusPendingCallWatcher *w) {
        if (w->isError() && !w->error().name().endsWith(QLatin1String("AlreadyConnected")))
            emit bluetoothFailed(address, failureText(w->error()));
    }, 45000);
}

void Lelan::bluetoothDisconnect(const QString &address)
{
    const QString path = m_btAddrToPath.value(address);
    if (path.isEmpty())
        return;
    onReply(this, QDBusMessage::createMethodCall(kBlueZ, path, kDevice, QStringLiteral("Disconnect")), [this, address](QDBusPendingCallWatcher *w) {
        if (w->isError())
            emit bluetoothFailed(address, failureText(w->error()));
    });
}

// B4/B5: pair (the agent handles codes), then trust, then connect
void Lelan::bluetoothPair(const QString &address)
{
    const QString path = m_btAddrToPath.value(address);
    if (path.isEmpty())
        return;
    stopBtScan();                                                                // discovery disturbs pairing
    onReply(this, QDBusMessage::createMethodCall(kBlueZ, path, kDevice, QStringLiteral("Pair")), [this, address, path](QDBusPendingCallWatcher *w) {
        btAgentCancel();                                                         // any code shown is done with
        if (w->isError() && !w->error().name().endsWith(QLatin1String("AlreadyExists"))) {
            emit bluetoothFailed(address, failureText(w->error()));
            return;
        }
        onReply(this, btSet(path, kDevice, QStringLiteral("Trusted"), true), [this, address](QDBusPendingCallWatcher *w) {
            if (w->isError())
                qWarning() << "[lelan] could not trust" << address << w->error().message();
            bluetoothConnect(address);
        });
    }, 90000);
}

void Lelan::bluetoothRemove(const QString &address)
{
    const QString path = m_btAddrToPath.value(address);
    if (path.isEmpty() || m_btAdapter.isEmpty())
        return;
    QDBusMessage m = QDBusMessage::createMethodCall(kBlueZ, m_btAdapter, kAdapter, QStringLiteral("RemoveDevice"));
    m << QVariant::fromValue(QDBusObjectPath(path));
    onReply(this, m, [this, address](QDBusPendingCallWatcher *w) {
        if (w->isError())
            emit bluetoothFailed(address, failureText(w->error()));
    });
}

// ---- pairing agent <-> Bluetooth tab ----
void Lelan::btAgentAsk(const QString &kind, const QString &devicePath, const QString &code, const QDBusMessage &request,
                       const QString &bus)
{
    if (m_btPairingRequest.type() == QDBusMessage::MethodCallMessage)            // BlueZ asks one thing at a time;
        QDBusConnection(m_btPairingBus).send(m_btPairingRequest.createErrorReply(  // a stale one is refused
            QStringLiteral("org.bluez.Error.Canceled"), QStringLiteral("Superseded")));
    m_btPairingRequest = request;
    m_btPairingBus = bus;                                                        // answer on the bus it came from
    btAgentShow(kind, devicePath, code);
    m_btPairingTimer->start();
}

void Lelan::btAgentShow(const QString &kind, const QString &devicePath, const QString &code)
{
    const QVariantMap d = m_btDevices.value(devicePath);
    // a device BlueZ has not reported yet still has its address in the path: .../dev_AA_BB_CC_DD_EE_FF
    QString address = d.value(QStringLiteral("Address")).toString();
    if (address.isEmpty())
        address = devicePath.section(QLatin1Char('/'), -1).remove(QStringLiteral("dev_")).replace(QLatin1Char('_'), QLatin1Char(':'));
    QString name = d.value(QStringLiteral("Alias")).toString();
    if (name.isEmpty()) name = d.value(QStringLiteral("Name")).toString();
    if (name.isEmpty()) name = address;
    m_bluetoothPairing = {
        {QStringLiteral("kind"), kind},                // confirm | pin | passkey | authorize | display
        {QStringLiteral("address"), address},
        {QStringLiteral("name"), name},
        {QStringLiteral("code"), code},
    };
    emit bluetoothPairingChanged();
}

void Lelan::btAgentCancel()
{
    m_btPairingTimer->stop();
    m_btPairingRequest = QDBusMessage();
    if (m_bluetoothPairing.isEmpty())
        return;
    m_bluetoothPairing.clear();
    emit bluetoothPairingChanged();
}

// The tab's answer. accept=false rejects (or cancels a shown code); value = typed PIN / passkey.
void Lelan::bluetoothPairingReply(bool accept, const QString &value)
{
    const QString kind = m_bluetoothPairing.value(QStringLiteral("kind")).toString();
    const QDBusMessage request = m_btPairingRequest;
    const QString address = m_bluetoothPairing.value(QStringLiteral("address")).toString();
    QDBusConnection bus = m_btPairingBus.isEmpty() ? QDBusConnection::systemBus() : QDBusConnection(m_btPairingBus);
    btAgentCancel();
    if (request.type() != QDBusMessage::MethodCallMessage) {
        if (!accept && kind == QLatin1String("display") && m_btAddrToPath.contains(address))   // stop a shown-code pairing
            QDBusConnection::systemBus().asyncCall(
                QDBusMessage::createMethodCall(kBlueZ, m_btAddrToPath.value(address), kDevice, QStringLiteral("CancelPairing")));
        return;
    }
    if (!accept) {
        bus.send(request.createErrorReply(QStringLiteral("org.bluez.Error.Rejected"), QStringLiteral("Declined")));
        return;
    }
    if (kind == QLatin1String("pin")) {
        bus.send(request.createReply(QVariant(value)));
    } else if (kind == QLatin1String("passkey")) {
        bool ok = false;
        const uint passkey = value.toUInt(&ok);
        if (!ok || passkey > 999999) {
            bus.send(request.createErrorReply(QStringLiteral("org.bluez.Error.Rejected"), QStringLiteral("Not a 6-digit code")));
            emit bluetoothFailed(address, QStringLiteral("The code must be 6 digits"));
            return;
        }
        bus.send(request.createReply(QVariant(passkey)));
    } else {
        bus.send(request.createReply());                                         // confirm / authorize
    }
}

#include "Lelan_bluetooth.moc"
