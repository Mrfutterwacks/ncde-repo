// Lelan — network: NetworkManager state, Wi-Fi (radio, access points, the active network, connect
// and disconnect), VPN and WireGuard connections, and Sentinel's link up/down.
//
// Rebuilt from oracle: subscribeToNetworkManager (+lambda), onNetworkStateChanged,
// onNmPropertiesChanged, onVpnStateChanged, subscribeToWifi (+2 lambdas, +nested DeviceType
// lambda), rebuildAccessPoints (+ApAccum lambdas), readActiveNetwork (+3 nested lambdas),
// scheduleWifiChanged, syncWifiConnectedFlag, onWifiPropertiesChanged, setWifiEnabled,
// connectWifi (+lambda), disconnectWifi, refreshVpnConnections (+VAcc lambdas), markActiveVpns
// (+nested), connectVpn, disconnectVpn (+nested), onSentinelNetworkStateChanged, the getters, ay2str.
// Spec: lelan.md §4/§5 (NetworkManager State + PrimaryConnection, VPN), ncde-efficiency.md §5 #6
// (no full re-enumeration on micro-signals; patch the changed entry; coalesce wifiChanged).
//
// DEFECTS FIXED vs oracle:
//  N1 every LastScan / AccessPoints change re-fetched every access point (GetAll x N) and the list
//     only refreshed then, so signal bars were minutes old (measured 2026-09-30: NM sends the
//     active AP's Strength every ~6 s, no LastScan in 60 s). Now: access points are cached by
//     path, only new ones are fetched, and Strength changes patch the cache; the list is
//     republished only when something the Network tab shows changes (SSID set, lock, connected,
//     signal-bar step 25/50/75).
//  N2 onNmPropertiesChanged / onSentinelNetworkStateChanged / state changes emitted networkChanged
//     on every signal, changed or not.
//  N3 a failed Get(ActiveAccessPoint) fell through and cleared the active network, as if Wi-Fi
//     had disconnected.
//  N4 the IP was read only when the access point changed. NM sets ActiveAccessPoint on association,
//     before DHCP gives Ip4Config, so a fresh connection showed no IP ("IP: ") until the next AP
//     change; old ip/speed also stayed when moving to another network. Now Ip4Config changes on
//     the device re-read the IP, and a new access point starts from an empty record.
//  N5 connectWifi always called AddAndActivateConnection, which creates a new saved profile
//     each time ("Net", "Net 1", ...), even for a network that is already saved. It also always
//     used key-mgmt wpa-psk, which WPA3-only (SAE) networks reject. Now a saved profile is
//     activated (and its password updated when one is typed); new ones pick sae/wpa-psk from the
//     access point's flags; 802.1X networks are refused with a warning (need more than a password).
//  N6 with several APs sharing one SSID (mesh), the "connected" flag followed only the strongest
//     AP, so a rescan could mark the network you are on as not connected.
//  N7 WeatherLive keys its location memory on lelan.network.ssid, which the oracle never set
//     (the "home" memory could never match). network.ssid now carries the active Wi-Fi SSID.
//  V1 markActiveVpns tested Connection.Active "Vpn", which NetworkManager sets only for plugin VPNs:
//     WireGuard connections were listed but never shown as connected. Active connections are now
//     matched by their settings path.
//  V2 the VPN list refreshed only on VpnStateChanged: profiles added/removed never appeared, and
//     WireGuard (no VpnStateChanged) never updated. Now NM Settings NewConnection /
//     ConnectionRemoved refresh the list, and ActiveConnections changes re-mark connected.
//  V3 each refresh published the list with every connection disconnected, then marked the active
//     ones: two vpnStateChanged per refresh, the first one wrong. Now composed, then published once.
//  V4 disconnectVpn deactivated any active connection whose Id matched the name (a Wi-Fi profile
//     with the same name too); now only the VPN's own settings path.
//  N8 a failed join (wrong password, network gone, DHCP failure) was only a log line: NM accepts
//     AddAndActivate/ActivateConnection first and fails the device later, so the Network tab
//     never learned. Now the device's FAILED state (or a D-Bus error) raises wifiConnectFailed.
//  N9 link speed was read once at connect and then frozen; Bitrate changes now update it.
//  N10 with two Wi-Fi adapters the device whose reply arrived last won; now the current one is
//     kept while present, else the activated one, else the first.
//  N11 wired Ethernet had no record at all: the Network tab's cable panel showed the Wi-Fi state
//     and IP. wiredNetwork {present, connected, iface, ip, speed} now follows the cable.
//  N12 VPNs could not be added (the "Add VPN" entry ran nmtui without a terminal and was hidden).
//     importVpn(file) imports an OpenVPN (.ovpn) or WireGuard (.conf) file through nmcli.
#include "Lelan.h"
#include "lelan_dbus_relay.h"

#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusContext>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QRegularExpression>
#include <QUrl>
#include <QSet>
#include <QTimer>
#include <QUuid>
#include <QtLogging>

#include <functional>
#include <memory>

namespace {
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QString kNm = QStringLiteral("org.freedesktop.NetworkManager");
const QString kNmPath = QStringLiteral("/org/freedesktop/NetworkManager");
const QString kNmDevice = QStringLiteral("org.freedesktop.NetworkManager.Device");
const QString kNmWireless = QStringLiteral("org.freedesktop.NetworkManager.Device.Wireless");
const QString kNmAp = QStringLiteral("org.freedesktop.NetworkManager.AccessPoint");
const QString kNmActive = QStringLiteral("org.freedesktop.NetworkManager.Connection.Active");
const QString kNmSettings = QStringLiteral("org.freedesktop.NetworkManager.Settings");
const QString kNmSettingsPath = QStringLiteral("/org/freedesktop/NetworkManager/Settings");
const QString kNmSettingsConn = QStringLiteral("org.freedesktop.NetworkManager.Settings.Connection");

constexpr uint kNmStateConnectedGlobal = 70;
constexpr uint kNmDeviceTypeEthernet = 1;
constexpr uint kNmDeviceTypeWifi = 2;
constexpr uint kNmDeviceStateActivated = 100;
constexpr uint kNmDeviceStateFailed = 120;
// NM80211ApSecurityFlags
constexpr uint kKeyMgmtPsk = 0x100;
constexpr uint kKeyMgmt8021x = 0x200;
constexpr uint kKeyMgmtSae = 0x400;

using NmSettings = QMap<QString, QVariantMap>;

// oracle ay2str: an "ay" SSID (arrives as QDBusArgument or QByteArray) up to its first NUL
QString ay2str(const QVariant &v)
{
    QByteArray bytes;
    if (v.canConvert<QDBusArgument>())
        v.value<QDBusArgument>() >> bytes;
    else
        bytes = v.toByteArray();
    return QString::fromLocal8Bit(bytes.constData());
}

// NMDeviceStateReason -> what the person needs to know
QString failureText(uint reason)
{
    switch (reason) {
    case 7: case 8: case 9: case 10: return QStringLiteral("Wrong password");
    case 11: return QStringLiteral("The network did not answer");
    case 53: return QStringLiteral("Network not found");
    case 5: case 17: return QStringLiteral("Joined, but got no address from the network");
    default: return QStringLiteral("Could not join (NetworkManager reason %1)").arg(reason);
    }
}

// the Network tab draws 1-4 bars at 25/50/75 (NetworkTab.qml); only a step change is visible
int signalBars(uint strength) { return strength >= 75 ? 4 : strength >= 50 ? 3 : strength >= 25 ? 2 : 1; }

QDBusMessage nmGet(const QString &path, const QString &iface, const QString &prop)
{
    QDBusMessage m = QDBusMessage::createMethodCall(kNm, path, kFdProps, QStringLiteral("Get"));
    m << iface << prop;
    return m;
}

// Run `done` with the finished reply; the watcher deletes itself.
void onReply(QObject *ctx, const QDBusMessage &call, std::function<void(QDBusPendingCallWatcher *)> done)
{
    auto *w = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(call), ctx);
    QObject::connect(w, &QDBusPendingCallWatcher::finished, ctx, [done = std::move(done)](QDBusPendingCallWatcher *w) {
        w->deleteLater();
        done(w);
    });
}

void warnReply(const char *what, const QDBusError &e)
{
    qWarning() << what << e.name() << e.message();
}

// WireGuard .conf -> NetworkManager settings (the same fields NM's own importer reads). Empty
// result + *error on anything NetworkManager cannot represent (PreUp/PostUp scripts, Table, ...).
NmSettings wireGuardSettings(const QString &text, const QString &name, QString *error)
{
    auto fail = [error](const QString &e) { *error = e; return NmSettings(); };
    auto list = [](const QString &v) {
        QStringList out;
        for (const QString &x : v.split(QLatin1Char(','), Qt::SkipEmptyParts))
            out << x.trimmed();
        return out;
    };
    static const QRegularExpression ifname(QStringLiteral("^[A-Za-z0-9_=+.-]{1,15}$"));
    if (!ifname.match(name).hasMatch())
        return fail(QStringLiteral("The file name must be a valid interface name (1-15 letters, digits, . _ - = +): %1").arg(name));

    QVariantMap wg, v4{{QStringLiteral("method"), QStringLiteral("disabled")}}, v6{{QStringLiteral("method"), QStringLiteral("disabled")}};
    QList<QVariantMap> peers, a4, a6;
    QStringList dns4, dns6, search;
    QVariantMap *peer = nullptr;
    enum { None, Iface, Peer } section = None;
    int lineNo = 0;
    for (QString line : text.split(QLatin1Char('\n'))) {
        ++lineNo;
        line = line.section(QLatin1Char('#'), 0, 0).trimmed();
        if (line.isEmpty())
            continue;
        if (line.compare(QLatin1String("[Interface]"), Qt::CaseInsensitive) == 0) { section = Iface; continue; }
        if (line.compare(QLatin1String("[Peer]"), Qt::CaseInsensitive) == 0) {
            section = Peer;
            peers.append(QVariantMap());
            peer = &peers.last();
            continue;
        }
        const int eq = line.indexOf(QLatin1Char('='));
        if (eq < 1 || section == None)
            return fail(QStringLiteral("Line %1 is not part of [Interface] or [Peer]").arg(lineNo));
        const QString key = line.left(eq).trimmed().toLower();
        const QString val = line.mid(eq + 1).trimmed();
        bool ok = true;
        if (section == Iface) {
            if (key == QLatin1String("privatekey")) wg.insert(QStringLiteral("private-key"), val);
            else if (key == QLatin1String("listenport")) wg.insert(QStringLiteral("listen-port"), val.toUInt(&ok));
            else if (key == QLatin1String("mtu")) wg.insert(QStringLiteral("mtu"), val.toUInt(&ok));
            else if (key == QLatin1String("fwmark")) wg.insert(QStringLiteral("fwmark"), val.toUInt(&ok, 0));
            else if (key == QLatin1String("address")) {
                for (const QString &a : list(val)) {
                    const QString ip = a.section(QLatin1Char('/'), 0, 0);
                    const bool six = ip.contains(QLatin1Char(':'));
                    const uint prefix = a.contains(QLatin1Char('/')) ? a.section(QLatin1Char('/'), 1).toUInt(&ok) : (six ? 128 : 32);
                    (six ? a6 : a4).append({{QStringLiteral("address"), ip}, {QStringLiteral("prefix"), prefix}});
                }
            } else if (key == QLatin1String("dns")) {
                for (const QString &d : list(val)) {
                    static const QRegularExpression ip(QStringLiteral("^[0-9.]+$|:"));
                    if (!ip.match(d).hasMatch()) search << d;
                    else (d.contains(QLatin1Char(':')) ? dns6 : dns4) << d;
                }
            } else if (key == QLatin1String("saveconfig")) {
                // wg-quick only; nothing to carry over
            } else {
                return fail(QStringLiteral("\"%1\" (line %2) is a wg-quick feature NetworkManager cannot run; remove it and import again")
                                .arg(line.left(eq).trimmed()).arg(lineNo));
            }
        } else {
            if (key == QLatin1String("publickey")) peer->insert(QStringLiteral("public-key"), val);
            else if (key == QLatin1String("presharedkey")) {
                peer->insert(QStringLiteral("preshared-key"), val);
                peer->insert(QStringLiteral("preshared-key-flags"), 0u);
            } else if (key == QLatin1String("allowedips")) peer->insert(QStringLiteral("allowed-ips"), list(val));
            else if (key == QLatin1String("endpoint")) peer->insert(QStringLiteral("endpoint"), val);
            else if (key == QLatin1String("persistentkeepalive")) peer->insert(QStringLiteral("persistent-keepalive"), val.toUInt(&ok));
            else return fail(QStringLiteral("Unknown [Peer] setting \"%1\" (line %2)").arg(line.left(eq).trimmed()).arg(lineNo));
        }
        if (!ok)
            return fail(QStringLiteral("Line %1: \"%2\" is not a valid number").arg(lineNo).arg(val));
    }
    if (wg.value(QStringLiteral("private-key")).toString().isEmpty())
        return fail(QStringLiteral("No PrivateKey in [Interface]"));
    for (const QVariantMap &pe : std::as_const(peers))
        if (pe.value(QStringLiteral("public-key")).toString().isEmpty())
            return fail(QStringLiteral("A [Peer] has no PublicKey"));
    if (!peers.isEmpty())
        wg.insert(QStringLiteral("peers"), QVariant::fromValue(peers));
    auto ip = [&search](QVariantMap &m, const QList<QVariantMap> &addrs, const QStringList &dns) {
        if (addrs.isEmpty())
            return;
        m.insert(QStringLiteral("method"), QStringLiteral("manual"));
        m.insert(QStringLiteral("address-data"), QVariant::fromValue(addrs));
        if (!dns.isEmpty()) m.insert(QStringLiteral("dns-data"), dns);
        if (!search.isEmpty()) m.insert(QStringLiteral("dns-search"), search);
    };
    ip(v4, a4, dns4);
    ip(v6, a6, dns6);
    NmSettings s;
    s.insert(QStringLiteral("connection"), {
        {QStringLiteral("id"), name},
        {QStringLiteral("uuid"), QUuid::createUuid().toString(QUuid::WithoutBraces)},
        {QStringLiteral("type"), QStringLiteral("wireguard")},
        {QStringLiteral("interface-name"), name},
        {QStringLiteral("autoconnect"), false},
        {QStringLiteral("permissions"), QStringList{QStringLiteral("user:") + QString::fromLocal8Bit(qgetenv("USER"))}},
    });
    s.insert(QStringLiteral("wireguard"), wg);
    s.insert(QStringLiteral("ipv4"), v4);
    s.insert(QStringLiteral("ipv6"), v6);
    return s;
}

} // namespace

// ---- getters ----
QVariantMap Lelan::network() const { return m_network; }
QVariantMap Lelan::vpn() const { return m_vpn; }
bool Lelan::wifiEnabled() const { return m_wifiEnabled; }
QVariantList Lelan::wifiNetworks() const { return m_wifiNetworks; }
QVariantMap Lelan::activeNetwork() const { return m_activeNetwork; }
QVariantList Lelan::vpnConnections() const { return m_vpnConnections; }
bool Lelan::networkOnline() const { return m_network.value(QStringLiteral("state")).toUInt() == kNmStateConnectedGlobal; }
bool Lelan::networkUp() const { return m_network.value(QStringLiteral("up"), true).toBool(); }

// N2: one place that changes m_network, and only a real change is announced
void Lelan::setNetworkValue(const QString &key, const QVariant &value)
{
    if (!value.isValid()) {
        if (m_network.remove(key))
            emit networkChanged();
        return;
    }
    auto it = m_network.constFind(key);
    if (it != m_network.constEnd() && *it == value)
        return;
    m_network.insert(key, value);
    emit networkChanged();
}

// ---- NetworkManager core ----
void Lelan::subscribeToNetworkManager()
{
    static const QMetaType registered = qDBusRegisterMetaType<NmSettings>();    // a{sa{sv}}
    Q_UNUSED(registered);
    QDBusConnection bus = QDBusConnection::systemBus();
    onReply(this, nmGet(kNmPath, kNm, QStringLiteral("State")), [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> reply = *w;
        if (reply.isError()) {
            warnReply("[lelan] NetworkManager Get(State) failed:", reply.error());
            return;
        }
        setNetworkValue(QStringLiteral("state"), reply.value().toUInt());
    });
    bus.connect(kNm, kNmPath, kNm, QStringLiteral("StateChanged"), this, SLOT(onNetworkStateChanged(uint)));
    bus.connect(kNm, kNmPath, kFdProps, QStringLiteral("PropertiesChanged"), this,
                SLOT(onNmPropertiesChanged(QString,QVariantMap,QStringList)));
    // plugin VPNs report their state on their Connection.Active object (any path)
    bus.connect(kNm, QString(), QStringLiteral("org.freedesktop.NetworkManager.VPN.Connection"),
                QStringLiteral("VpnStateChanged"), this, SLOT(onVpnStateChanged(uint,uint)));
    // V2: saved profiles appearing / going away / edited
    if (!m_nmSettingsRelay) {
        m_nmSettingsRelay = new DBusSignalRelay(this, [this] { refreshVpnConnections(); });
        for (const char *sig : {"NewConnection", "ConnectionRemoved"})
            bus.connect(kNm, kNmSettingsPath, kNmSettings, QLatin1String(sig), m_nmSettingsRelay, SLOT(fire()));
        bus.connect(kNm, QString(), kNmSettingsConn, QStringLiteral("Updated"), m_nmSettingsRelay, SLOT(fire()));
    }
    refreshVpnConnections();
}

void Lelan::onNetworkStateChanged(uint state)
{
    setNetworkValue(QStringLiteral("state"), state);
}

void Lelan::onNmPropertiesChanged(const QString &, const QVariantMap &changed, const QStringList &)
{
    if (changed.contains(QStringLiteral("PrimaryConnection"))) {
        const QString primary = qvariant_cast<QDBusObjectPath>(changed.value(QStringLiteral("PrimaryConnection"))).path();
        setNetworkValue(QStringLiteral("primary"), primary);
        readActiveNetwork();
    }
    if (changed.contains(QStringLiteral("State")))
        setNetworkValue(QStringLiteral("state"), changed.value(QStringLiteral("State")).toUInt());
    if (changed.contains(QStringLiteral("WirelessEnabled"))) {
        const bool on = changed.value(QStringLiteral("WirelessEnabled")).toBool();
        if (on != m_wifiEnabled) {
            m_wifiEnabled = on;
            scheduleWifiChanged();
        }
    }
    if (changed.contains(QStringLiteral("ActiveConnections")))
        markActiveVpns();                                                        // V2
}

void Lelan::onVpnStateChanged(uint state, uint reason)
{
    QVariantMap next = m_vpn;
    next.insert(QStringLiteral("state"), state);
    next.insert(QStringLiteral("reason"), reason);
    if (next != m_vpn) {
        m_vpn = next;
        emit vpnStateChanged();
    }
    markActiveVpns();
}

void Lelan::onSentinelNetworkStateChanged(const QString &iface, bool up)
{
    // Sentinel's `up` is already the whole machine's answer (udev_monitor._net_up)
    QVariantMap next = m_network;
    next.insert(QStringLiteral("iface"), iface);
    next.insert(QStringLiteral("up"), up);
    if (next == m_network)
        return;
    m_network = next;
    emit networkChanged();
}

// ---- Wi-Fi ----
void Lelan::subscribeToWifi()
{
    onReply(this, nmGet(kNmPath, kNm, QStringLiteral("WirelessEnabled")), [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> reply = *w;
        if (reply.isError())
            return;
        const bool on = reply.value().toBool();
        if (on != m_wifiEnabled) {
            m_wifiEnabled = on;
            scheduleWifiChanged();
        }
    });

    if (!m_apRelay) {
        m_apRelay = new PropsRelay(this, [this](const QString &path, const QString &, const QVariantMap &changed) {
            onAccessPointChanged(path, changed);
        });
        QDBusConnection::systemBus().connect(kNm, QString(), kFdProps, QStringLiteral("PropertiesChanged"),
            {kNmAp}, QStringLiteral("sa{sv}as"), m_apRelay,
            SLOT(propertiesChanged(QString,QVariantMap,QStringList)));
    }

    QDBusMessage devices = QDBusMessage::createMethodCall(kNm, kNmPath, kNm, QStringLiteral("GetDevices"));
    onReply(this, devices, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QList<QDBusObjectPath>> reply = *w;
        if (reply.isError()) {
            warnReply("[lelan] NetworkManager GetDevices failed:", reply.error());
            return;
        }
        struct Dev { QString path; uint type = 0; uint state = 0; QString iface; };
        struct Acc { int pending = 0; QList<Dev> devs; };
        auto acc = std::make_shared<Acc>();
        const QList<QDBusObjectPath> paths = reply.value();
        acc->pending = paths.size();
        auto finish = [this, acc] {
            // N10: keep the current adapter while it exists; else the activated one; else the first
            auto pick = [&](uint type, const QString &current) {
                const Dev *first = nullptr, *activated = nullptr;
                for (const Dev &d : std::as_const(acc->devs)) {
                    if (d.type != type) continue;
                    if (d.path == current) return d;
                    if (!first) first = &d;
                    if (!activated && d.state == kNmDeviceStateActivated) activated = &d;
                }
                return activated ? *activated : first ? *first : Dev{};
            };
            const Dev wifi = pick(kNmDeviceTypeWifi, m_wifiDevice);
            const Dev wired = pick(kNmDeviceTypeEthernet, m_wiredDevice);
            QDBusConnection bus = QDBusConnection::systemBus();
            if (!wifi.path.isEmpty()) {
                if (wifi.path != m_wifiDevice) {
                    if (!m_wifiDevice.isEmpty())
                        bus.disconnect(kNm, m_wifiDevice, kFdProps, QStringLiteral("PropertiesChanged"), this,
                                       SLOT(onWifiPropertiesChanged(QString,QVariantMap,QStringList)));
                    m_wifiDevice = wifi.path;
                    m_apCache.clear();
                }
                bus.connect(kNm, wifi.path, kFdProps, QStringLiteral("PropertiesChanged"), this,
                            SLOT(onWifiPropertiesChanged(QString,QVariantMap,QStringList)));
                QDBusMessage scan = QDBusMessage::createMethodCall(kNm, wifi.path, kNmWireless, QStringLiteral("RequestScan"));
                scan << QVariantMap();
                bus.asyncCall(scan);
                rebuildAccessPoints();
                readActiveNetwork();
            }
            subscribeToWired(wired.path, wired.iface);
        };
        if (paths.isEmpty()) {
            finish();
            return;
        }
        for (const QDBusObjectPath &dev : paths) {
            const QString path = dev.path();
            QDBusMessage getAll = QDBusMessage::createMethodCall(kNm, path, kFdProps, QStringLiteral("GetAll"));
            getAll << kNmDevice;
            onReply(this, getAll, [acc, path, finish](QDBusPendingCallWatcher *w) {
                QDBusPendingReply<QVariantMap> props = *w;
                if (!props.isError()) {
                    const QVariantMap p = props.value();
                    acc->devs.append({path, p.value(QStringLiteral("DeviceType")).toUInt(),
                                      p.value(QStringLiteral("State")).toUInt(), p.value(QStringLiteral("Interface")).toString()});
                }
                if (--acc->pending == 0)
                    finish();
            });
        }
    });
}

void Lelan::onWifiPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &)
{
    if (iface == kNmDevice) {
        if (changed.contains(QStringLiteral("Ip4Config")))                       // N4
            readActiveIp(qvariant_cast<QDBusObjectPath>(changed.value(QStringLiteral("Ip4Config"))).path());
        if (changed.contains(QStringLiteral("StateReason"))) {                   // N8
            uint state = 0, reason = 0;
            const QDBusArgument arg = changed.value(QStringLiteral("StateReason")).value<QDBusArgument>();
            arg.beginStructure();
            arg >> state >> reason;
            arg.endStructure();
            if (state == kNmDeviceStateActivated)
                m_joiningSsid.clear();
            else if (state == kNmDeviceStateFailed && !m_joiningSsid.isEmpty())
                failJoin(reason == 7 && !m_joinHadPassword ? QStringLiteral("This network needs a password") : failureText(reason));
        }
        return;
    }
    if (iface != kNmWireless)
        return;
    if (changed.contains(QStringLiteral("Bitrate")) && !m_activeApPath.isEmpty())   // N9
        setActiveNetworkValue(QStringLiteral("speed"), changed.value(QStringLiteral("Bitrate")).toUInt() / 1000);
    if (changed.contains(QStringLiteral("LastScan")) || changed.contains(QStringLiteral("AccessPoints")))
        rebuildAccessPoints();
    if (changed.contains(QStringLiteral("ActiveAccessPoint")))
        readActiveNetwork();
}

// N1: fetch only access points not already cached; drop the ones that went away.
void Lelan::rebuildAccessPoints()
{
    if (m_wifiDevice.isEmpty())
        return;
    QDBusMessage call = QDBusMessage::createMethodCall(kNm, m_wifiDevice, kNmWireless, QStringLiteral("GetAllAccessPoints"));
    onReply(this, call, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QList<QDBusObjectPath>> reply = *w;
        if (reply.isError()) {
            warnReply("[lelan] NetworkManager GetAllAccessPoints failed:", reply.error());
            return;
        }
        QSet<QString> present;
        for (const QDBusObjectPath &ap : reply.value())
            present.insert(ap.path());
        for (auto it = m_apCache.begin(); it != m_apCache.end();)
            it = present.contains(it.key()) ? std::next(it) : m_apCache.erase(it);

        QStringList fresh;
        for (const QString &p : std::as_const(present))
            if (!m_apCache.contains(p))
                fresh << p;
        if (fresh.isEmpty()) {
            publishAccessPoints();
            return;
        }
        auto pending = std::make_shared<int>(fresh.size());
        for (const QString &path : std::as_const(fresh)) {
            QDBusMessage getAll = QDBusMessage::createMethodCall(kNm, path, kFdProps, QStringLiteral("GetAll"));
            getAll << kNmAp;
            onReply(this, getAll, [this, path, pending](QDBusPendingCallWatcher *w) {
                QDBusPendingReply<QVariantMap> props = *w;
                if (!props.isError()) {
                    const QVariantMap p = props.value();
                    ApInfo ap;
                    ap.ssid = ay2str(p.value(QStringLiteral("Ssid")));
                    ap.strength = p.value(QStringLiteral("Strength")).toUInt();
                    ap.wpaFlags = p.value(QStringLiteral("WpaFlags")).toUInt();
                    ap.rsnFlags = p.value(QStringLiteral("RsnFlags")).toUInt();
                    m_apCache.insert(path, ap);
                }
                if (--*pending == 0)
                    publishAccessPoints();
            });
        }
    });
}

void Lelan::onAccessPointChanged(const QString &path, const QVariantMap &changed)
{
    auto it = m_apCache.find(path);
    if (it == m_apCache.end())
        return;
    bool touched = false;
    if (changed.contains(QStringLiteral("Strength"))) {
        it->strength = changed.value(QStringLiteral("Strength")).toUInt();
        touched = true;
    }
    if (changed.contains(QStringLiteral("Ssid"))) {                              // hidden network revealed
        it->ssid = ay2str(changed.value(QStringLiteral("Ssid")));
        touched = true;
    }
    if (touched)
        publishAccessPoints();
}

// One entry per SSID (the strongest AP, as the oracle kept), sorted by SSID (oracle QMap order).
// Published only when the Network tab would draw something different.
void Lelan::publishAccessPoints()
{
    QMap<QString, QVariantMap> bySsid;
    for (auto it = m_apCache.cbegin(); it != m_apCache.cend(); ++it) {
        const ApInfo &ap = it.value();
        if (ap.ssid.isEmpty())
            continue;
        const bool here = (it.key() == m_activeApPath);
        auto cur = bySsid.find(ap.ssid);
        if (cur == bySsid.end() || cur->value(QStringLiteral("signal")).toUInt() < ap.strength) {
            const bool groupConnected = here || (cur != bySsid.end() && cur->value(QStringLiteral("connected")).toBool());
            bySsid.insert(ap.ssid, QVariantMap{
                {QStringLiteral("ssid"), ap.ssid},
                {QStringLiteral("signal"), ap.strength},
                {QStringLiteral("secured"), ap.wpaFlags != 0 || ap.rsnFlags != 0},
                {QStringLiteral("connected"), groupConnected},                  // N6
                {QStringLiteral("saved"), m_wifiProfiles.contains(ap.ssid)},    // Connect needs no password
            });
        } else if (here) {
            cur->insert(QStringLiteral("connected"), true);                     // N6
        }
    }
    QVariantList next;
    next.reserve(bySsid.size());
    for (const QVariantMap &e : std::as_const(bySsid))
        next.append(e);

    auto visible = [](const QVariantList &list) {
        QList<std::tuple<QString, bool, bool, int, bool>> out;
        for (const QVariant &v : list) {
            const QVariantMap e = v.toMap();
            out.append({e.value(QStringLiteral("ssid")).toString(), e.value(QStringLiteral("secured")).toBool(),
                        e.value(QStringLiteral("connected")).toBool(), signalBars(e.value(QStringLiteral("signal")).toUInt()),
                        e.value(QStringLiteral("saved")).toBool()});
        }
        return out;
    };
    if (visible(next) == visible(m_wifiNetworks))
        return;
    m_wifiNetworks = next;
    scheduleWifiChanged();
}

void Lelan::readActiveNetwork()
{
    if (m_wifiDevice.isEmpty())
        return;
    onReply(this, nmGet(m_wifiDevice, kNmWireless, QStringLiteral("ActiveAccessPoint")), [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> reply = *w;
        if (reply.isError()) {                                                   // N3
            warnReply("[lelan] NetworkManager Get(ActiveAccessPoint) failed:", reply.error());
            return;
        }
        const QString ap = qvariant_cast<QDBusObjectPath>(reply.value()).path();
        const bool none = ap.isEmpty() || ap == QLatin1String("/");
        if (ap != m_activeApPath) {
            m_activeApPath = none ? QString() : ap;
            if (!m_activeNetwork.isEmpty()) {                                    // N4: no stale ip/speed
                m_activeNetwork.clear();
                scheduleWifiChanged();
            }
            publishAccessPoints();
        }
        if (none) {
            setNetworkValue(QStringLiteral("ssid"), QVariant());                // N7
            syncWifiConnectedFlag({});
            return;
        }
        onReply(this, nmGet(ap, kNmAp, QStringLiteral("Ssid")), [this, ap](QDBusPendingCallWatcher *w) {
            QDBusPendingReply<QVariant> ssid = *w;
            if (ssid.isError() || ap != m_activeApPath)
                return;
            const QString name = ay2str(ssid.value());
            setActiveNetworkValue(QStringLiteral("ssid"), name);
            setNetworkValue(QStringLiteral("ssid"), name);                      // N7
            syncWifiConnectedFlag(name);
        });
        onReply(this, nmGet(m_wifiDevice, kNmWireless, QStringLiteral("Bitrate")), [this, ap](QDBusPendingCallWatcher *w) {
            QDBusPendingReply<QVariant> rate = *w;
            if (!rate.isError() && ap == m_activeApPath)
                setActiveNetworkValue(QStringLiteral("speed"), rate.value().toUInt() / 1000);   // kb/s -> Mb/s
        });
        onReply(this, nmGet(m_wifiDevice, kNmDevice, QStringLiteral("Ip4Config")), [this](QDBusPendingCallWatcher *w) {
            QDBusPendingReply<QVariant> cfg = *w;
            if (!cfg.isError())
                readActiveIp(qvariant_cast<QDBusObjectPath>(cfg.value()).path());
        });
    });
}

void Lelan::readActiveIp(const QString &ip4Config)
{
    if (ip4Config.isEmpty() || ip4Config == QLatin1String("/") || m_activeApPath.isEmpty())
        return;
    onReply(this, nmGet(ip4Config, QStringLiteral("org.freedesktop.NetworkManager.IP4Config"), QStringLiteral("AddressData")),
            [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> reply = *w;
        if (reply.isError() || m_activeApPath.isEmpty())
            return;
        const QDBusArgument arg = reply.value().value<QDBusArgument>();
        QString address;
        arg.beginArray();
        if (!arg.atEnd()) {
            QVariantMap first;
            arg >> first;
            address = first.value(QStringLiteral("address")).toString();
        }
        arg.endArray();
        if (!address.isEmpty())
            setActiveNetworkValue(QStringLiteral("ip"), address);
    });
}

void Lelan::setActiveNetworkValue(const QString &key, const QVariant &value)
{
    auto it = m_activeNetwork.constFind(key);
    if (it != m_activeNetwork.constEnd() && *it == value)
        return;
    m_activeNetwork.insert(key, value);
    scheduleWifiChanged();
}

// Many replies land in one event-loop pass; QML hears one wifiChanged (oracle coalescing).
void Lelan::scheduleWifiChanged()
{
    if (m_wifiChangedPending)
        return;
    m_wifiChangedPending = true;
    QTimer::singleShot(0, this, [this] {
        m_wifiChangedPending = false;
        emit wifiChanged();
    });
}

void Lelan::syncWifiConnectedFlag(const QString &ssid)
{
    bool changed = false;
    for (QVariant &entry : m_wifiNetworks) {
        QVariantMap network = entry.toMap();
        const bool connected = !ssid.isEmpty()
                               && network.value(QStringLiteral("ssid")).toString() == ssid;
        if (network.value(QStringLiteral("connected")).toBool() == connected)
            continue;
        network.insert(QStringLiteral("connected"), connected);
        entry = network;
        changed = true;
    }
    if (changed)
        scheduleWifiChanged();
}

void Lelan::setWifiEnabled(bool on)
{
    QDBusMessage m = QDBusMessage::createMethodCall(kNm, kNmPath, kFdProps, QStringLiteral("Set"));
    m << kNm << QStringLiteral("WirelessEnabled") << QVariant::fromValue(QDBusVariant(on));
    QDBusConnection::systemBus().asyncCall(m);
}

void Lelan::connectWifi(const QString &ssid, const QString &password)
{
    if (ssid.isEmpty())
        return;
    m_joiningSsid = ssid;
    m_joinHadPassword = !password.isEmpty() || m_wifiProfiles.contains(ssid);
    if (m_wifiDevice.isEmpty()) {
        failJoin(QStringLiteral("No Wi-Fi adapter"));
        return;
    }

    // the AP's security flags decide how a password is used (N5)
    uint flags = 0;
    for (const ApInfo &ap : std::as_const(m_apCache))
        if (ap.ssid == ssid)
            flags |= ap.wpaFlags | ap.rsnFlags;
    if ((flags & kKeyMgmt8021x) && !(flags & (kKeyMgmtPsk | kKeyMgmtSae))) {
        qWarning() << "[lelan] connectWifi:" << ssid << "uses 802.1X (enterprise); a password alone cannot join it";
        failJoin(QStringLiteral("This network needs an enterprise (802.1X) login, not just a password"));
        return;
    }
    const QString keyMgmt = ((flags & kKeyMgmtSae) && !(flags & kKeyMgmtPsk)) ? QStringLiteral("sae") : QStringLiteral("wpa-psk");
    const QVariantMap security{{QStringLiteral("key-mgmt"), keyMgmt}, {QStringLiteral("psk"), password}};

    auto finished = [this](const char *what) {
        return [this, what](QDBusPendingCallWatcher *w) {
            if (w->isError()) {
                warnReply(what, w->error());
                failJoin(w->error().message());
                return;
            }
            readActiveNetwork();
            scheduleWifiChanged();
        };
    };
    auto activate = [this, finished](const QString &profile) {
        QDBusMessage m = QDBusMessage::createMethodCall(kNm, kNmPath, kNm, QStringLiteral("ActivateConnection"));
        m << QVariant::fromValue(QDBusObjectPath(profile)) << QVariant::fromValue(QDBusObjectPath(m_wifiDevice))
          << QVariant::fromValue(QDBusObjectPath(QStringLiteral("/")));
        onReply(this, m, finished("[lelan] connectWifi failed:"));
    };

    const QString saved = m_wifiProfiles.value(ssid);
    if (!saved.isEmpty()) {
        if (password.isEmpty()) {
            activate(saved);
            return;
        }
        // a typed password replaces the saved one on the same profile
        QDBusMessage get = QDBusMessage::createMethodCall(kNm, saved, kNmSettingsConn, QStringLiteral("GetSettings"));
        onReply(this, get, [this, saved, security, activate](QDBusPendingCallWatcher *w) {
            QDBusPendingReply<NmSettings> reply = *w;
            if (reply.isError()) {
                warnReply("[lelan] connectWifi GetSettings failed:", reply.error());
                failJoin(reply.error().message());
                return;
            }
            NmSettings s = reply.value();
            s.insert(QStringLiteral("802-11-wireless-security"), security);
            QDBusMessage update = QDBusMessage::createMethodCall(kNm, saved, kNmSettingsConn, QStringLiteral("Update"));
            update << QVariant::fromValue(s);
            onReply(this, update, [this, saved, activate](QDBusPendingCallWatcher *w) {
                if (w->isError()) {
                    warnReply("[lelan] connectWifi Update failed:", w->error());
                    failJoin(w->error().message());
                    return;
                }
                activate(saved);
            });
        });
        return;
    }

    NmSettings s;
    s.insert(QStringLiteral("connection"), QVariantMap{
        {QStringLiteral("id"), ssid},
        {QStringLiteral("type"), QStringLiteral("802-11-wireless")},
        {QStringLiteral("uuid"), QUuid::createUuid().toString(QUuid::WithoutBraces)},
        {QStringLiteral("permissions"), QStringList{QStringLiteral("user:") + QString::fromLocal8Bit(qgetenv("USER"))}},
    });
    s.insert(QStringLiteral("802-11-wireless"), QVariantMap{
        {QStringLiteral("ssid"), ssid.toUtf8()},
        {QStringLiteral("mode"), QStringLiteral("infrastructure")},
    });
    if (!password.isEmpty())
        s.insert(QStringLiteral("802-11-wireless-security"), security);
    QDBusMessage m = QDBusMessage::createMethodCall(kNm, kNmPath, kNm, QStringLiteral("AddAndActivateConnection"));
    m << QVariant::fromValue(s) << QVariant::fromValue(QDBusObjectPath(m_wifiDevice))
      << QVariant::fromValue(QDBusObjectPath(QStringLiteral("/")));
    onReply(this, m, finished("[lelan] connectWifi failed:"));
}

void Lelan::disconnectWifi()
{
    if (m_wifiDevice.isEmpty())
        return;
    QDBusConnection::systemBus().asyncCall(
        QDBusMessage::createMethodCall(kNm, m_wifiDevice, kNmDevice, QStringLiteral("Disconnect")));
}

void Lelan::failJoin(const QString &reason)
{
    const QString ssid = m_joiningSsid;
    m_joiningSsid.clear();
    emit wifiConnectFailed(ssid, reason);
}

// ---- wired Ethernet (N11) ----
QVariantMap Lelan::wiredNetwork() const { return m_wiredNetwork; }

void Lelan::setWiredValue(const QString &key, const QVariant &value)
{
    auto it = m_wiredNetwork.constFind(key);
    if (it != m_wiredNetwork.constEnd() && *it == value)
        return;
    m_wiredNetwork.insert(key, value);
    emit networkChanged();
}

void Lelan::subscribeToWired(const QString &device, const QString &iface)
{
    if (!m_wiredRelay) {
        m_wiredRelay = new PropsRelay(this, [this](const QString &path, const QString &ifc, const QVariantMap &changed) {
            if (path != m_wiredDevice)
                return;
            if (ifc == kNmDevice) {
                if (changed.contains(QStringLiteral("State")))
                    applyWiredState(changed.value(QStringLiteral("State")).toUInt());
                if (changed.contains(QStringLiteral("Ip4Config")))
                    readWiredIp(qvariant_cast<QDBusObjectPath>(changed.value(QStringLiteral("Ip4Config"))).path());
            } else if (ifc == QLatin1String("org.freedesktop.NetworkManager.Device.Wired") && changed.contains(QStringLiteral("Speed"))) {
                setWiredValue(QStringLiteral("speed"), changed.value(QStringLiteral("Speed")).toUInt());
            }
        });
    }
    QDBusConnection bus = QDBusConnection::systemBus();
    if (device != m_wiredDevice && !m_wiredDevice.isEmpty())
        bus.disconnect(kNm, m_wiredDevice, kFdProps, QStringLiteral("PropertiesChanged"), m_wiredRelay,
                       SLOT(propertiesChanged(QString,QVariantMap,QStringList)));
    m_wiredDevice = device;
    if (device.isEmpty()) {
        const QVariantMap none{{QStringLiteral("present"), false}, {QStringLiteral("connected"), false}};
        if (m_wiredNetwork != none) {
            m_wiredNetwork = none;
            emit networkChanged();
        }
        return;
    }
    bus.connect(kNm, device, kFdProps, QStringLiteral("PropertiesChanged"), m_wiredRelay,
                SLOT(propertiesChanged(QString,QVariantMap,QStringList)));
    setWiredValue(QStringLiteral("present"), true);
    setWiredValue(QStringLiteral("iface"), iface);
    onReply(this, nmGet(device, kNmDevice, QStringLiteral("State")), [this, device](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> r = *w;
        if (!r.isError() && device == m_wiredDevice)
            applyWiredState(r.value().toUInt());
    });
    onReply(this, nmGet(device, QStringLiteral("org.freedesktop.NetworkManager.Device.Wired"), QStringLiteral("Speed")),
            [this, device](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> r = *w;
        if (!r.isError() && device == m_wiredDevice)
            setWiredValue(QStringLiteral("speed"), r.value().toUInt());
    });
}

void Lelan::applyWiredState(uint state)
{
    const bool connected = (state == kNmDeviceStateActivated);
    setWiredValue(QStringLiteral("connected"), connected);
    if (!connected) {
        if (m_wiredNetwork.remove(QStringLiteral("ip")))
            emit networkChanged();
        return;
    }
    onReply(this, nmGet(m_wiredDevice, kNmDevice, QStringLiteral("Ip4Config")), [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> r = *w;
        if (!r.isError())
            readWiredIp(qvariant_cast<QDBusObjectPath>(r.value()).path());
    });
}

void Lelan::readWiredIp(const QString &ip4Config)
{
    if (ip4Config.isEmpty() || ip4Config == QLatin1String("/"))
        return;
    onReply(this, nmGet(ip4Config, QStringLiteral("org.freedesktop.NetworkManager.IP4Config"), QStringLiteral("AddressData")),
            [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> reply = *w;
        if (reply.isError() || !m_wiredNetwork.value(QStringLiteral("connected")).toBool())
            return;
        const QDBusArgument arg = reply.value().value<QDBusArgument>();
        QString address;
        arg.beginArray();
        if (!arg.atEnd()) {
            QVariantMap first;
            arg >> first;
            address = first.value(QStringLiteral("address")).toString();
        }
        arg.endArray();
        if (!address.isEmpty())
            setWiredValue(QStringLiteral("ip"), address);
    });
}

// ---- VPN / WireGuard ----
// Every saved profile's settings: VPN/WireGuard entries for the list, Wi-Fi SSIDs for connectWifi.
void Lelan::refreshVpnConnections()
{
    QDBusMessage call = QDBusMessage::createMethodCall(kNm, kNmSettingsPath, kNmSettings, QStringLiteral("ListConnections"));
    const quint64 generation = ++m_vpnRefreshGeneration;
    onReply(this, call, [this, generation](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QList<QDBusObjectPath>> reply = *w;
        if (reply.isError()) {
            warnReply("[lelan] NetworkManager ListConnections failed:", reply.error());
            return;
        }
        struct Acc {
            int pending = 0;
            QMap<QString, QVariantMap> vpns;       // settings path -> {name, type}
            QHash<QString, QString> wifi;          // ssid -> settings path
        };
        auto acc = std::make_shared<Acc>();
        const QList<QDBusObjectPath> paths = reply.value();
        acc->pending = paths.size();
        auto finish = [this, acc, generation] {
            if (generation != m_vpnRefreshGeneration)
                return;                            // a newer refresh is running
            if (m_wifiProfiles != acc->wifi) {
                m_wifiProfiles = acc->wifi;
                publishAccessPoints();                                           // "saved" flags
            }
            m_vpnProfiles.clear();
            m_vpnPaths.clear();
            for (auto it = acc->vpns.cbegin(); it != acc->vpns.cend(); ++it) {
                m_vpnProfiles.append({it.key(), it->value(QStringLiteral("name")).toString(), it->value(QStringLiteral("type")).toString()});
                m_vpnPaths.insert(it->value(QStringLiteral("name")).toString(), it.key());
            }
            markActiveVpns();                                                    // V3: publish once, marked
        };
        if (paths.isEmpty()) {
            finish();
            return;
        }
        for (const QDBusObjectPath &p : paths) {
            const QString path = p.path();
            QDBusMessage get = QDBusMessage::createMethodCall(kNm, path, kNmSettingsConn, QStringLiteral("GetSettings"));
            onReply(this, get, [acc, path, finish](QDBusPendingCallWatcher *w) {
                QDBusPendingReply<NmSettings> settings = *w;
                if (!settings.isError()) {
                    const NmSettings s = settings.value();
                    const QVariantMap conn = s.value(QStringLiteral("connection"));
                    const QString type = conn.value(QStringLiteral("type")).toString();
                    const QString id = conn.value(QStringLiteral("id")).toString();
                    if (type == QLatin1String("vpn") || type == QLatin1String("wireguard")) {
                        QString kind = type;
                        if (s.contains(QStringLiteral("vpn")))
                            kind = s.value(QStringLiteral("vpn")).value(QStringLiteral("service-type")).toString();
                        // "org.freedesktop.NetworkManager.openvpn" -> "openvpn" (oracle section('.', -1))
                        acc->vpns.insert(path, {{QStringLiteral("name"), id}, {QStringLiteral("type"), kind.section(QLatin1Char('.'), -1)}});
                    } else if (type == QLatin1String("802-11-wireless")) {
                        const QByteArray ssid = s.value(QStringLiteral("802-11-wireless")).value(QStringLiteral("ssid")).toByteArray();
                        if (!ssid.isEmpty())
                            acc->wifi.insert(QString::fromLocal8Bit(ssid.constData()), path);
                    }
                }
                if (--acc->pending == 0)
                    finish();
            });
        }
    });
}

// V1/V3: which saved VPN profiles are active, by settings path; list published only on change.
void Lelan::markActiveVpns()
{
    const quint64 generation = ++m_vpnMarkGeneration;
    onReply(this, nmGet(kNmPath, kNm, QStringLiteral("ActiveConnections")), [this, generation](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> reply = *w;
        if (reply.isError()) {
            warnReply("[lelan] NetworkManager Get(ActiveConnections) failed (markActiveVpns):", reply.error());
            return;
        }
        const QList<QDBusObjectPath> active = qdbus_cast<QList<QDBusObjectPath>>(reply.value());
        struct Acc { int pending = 0; QSet<QString> settingsPaths; QHash<QString, QString> activeByProfile; };
        auto acc = std::make_shared<Acc>();
        acc->pending = active.size();
        auto finish = [this, acc, generation] {
            if (generation != m_vpnMarkGeneration)
                return;
            m_activeVpnByProfile = acc->activeByProfile;
            QVariantList list;
            for (const VpnProfile &v : std::as_const(m_vpnProfiles))
                list.append(QVariantMap{{QStringLiteral("name"), v.name}, {QStringLiteral("type"), v.type},
                                        {QStringLiteral("connected"), acc->settingsPaths.contains(v.path)}});
            if (list != m_vpnConnections) {
                m_vpnConnections = list;
                emit vpnStateChanged();
            }
        };
        if (active.isEmpty()) {
            finish();
            return;
        }
        for (const QDBusObjectPath &a : active) {
            const QString activePath = a.path();
            onReply(this, nmGet(activePath, kNmActive, QStringLiteral("Connection")), [acc, activePath, finish](QDBusPendingCallWatcher *w) {
                QDBusPendingReply<QVariant> conn = *w;
                if (!conn.isError()) {
                    const QString profile = qvariant_cast<QDBusObjectPath>(conn.value()).path();
                    acc->settingsPaths.insert(profile);
                    acc->activeByProfile.insert(profile, activePath);
                }
                if (--acc->pending == 0)
                    finish();
            });
        }
    });
}

// N12: a VPN can be removed from Settings (the only way before was the dead nmtui "Edit" button)
void Lelan::removeVpn(const QString &name)
{
    const QString profile = m_vpnPaths.value(name);
    if (profile.isEmpty())
        return;
    QDBusConnection::systemBus().asyncCall(QDBusMessage::createMethodCall(kNm, profile, kNmSettingsConn, QStringLiteral("Delete")));
}

void Lelan::connectVpn(const QString &name)
{
    const QString profile = m_vpnPaths.value(name);
    if (profile.isEmpty())
        return;
    QDBusMessage m = QDBusMessage::createMethodCall(kNm, kNmPath, kNm, QStringLiteral("ActivateConnection"));
    m << QVariant::fromValue(QDBusObjectPath(profile)) << QVariant::fromValue(QDBusObjectPath(QStringLiteral("/")))
      << QVariant::fromValue(QDBusObjectPath(QStringLiteral("/")));
    QDBusConnection::systemBus().asyncCall(m);
}

void Lelan::disconnectVpn(const QString &name)
{
    const QString active = m_activeVpnByProfile.value(m_vpnPaths.value(name));    // V4
    if (active.isEmpty())
        return;
    QDBusMessage m = QDBusMessage::createMethodCall(kNm, kNmPath, kNm, QStringLiteral("DeactivateConnection"));
    m << QVariant::fromValue(QDBusObjectPath(active));
    QDBusConnection::systemBus().asyncCall(m);
}

// N12: nmcli does the import (it loads the VPN plugin's own importer); the new profile reaches the
// list through Settings NewConnection. .conf = WireGuard, anything else = OpenVPN.
// Connecting stays an explicit choice (the Connect button). Measured 2026-09-30: NetworkManager
// auto-activates an nmcli-imported WireGuard profile within 3 ms (a later "down" still left it up
// 74 ms: traffic could move onto the VPN), and saves an OpenVPN import with autoconnect=yes (it would
// start by itself next time Wi-Fi comes up). So WireGuard is parsed here and added with
// autoconnect off + BLOCK_AUTOCONNECT (it can never start on its own, and no private key goes on a
// command line); OpenVPN (plugin-specific format) goes through nmcli, then autoconnect is switched off.
void Lelan::importVpn(const QString &file)
{
    QString path = file;
    if (path.startsWith(QLatin1String("file://")))
        path = QUrl(path).toLocalFile();
    if (path.endsWith(QLatin1String(".conf"), Qt::CaseInsensitive)) {
        importWireGuard(path);
        return;
    }
    runNmcli({QStringLiteral("connection"), QStringLiteral("import"), QStringLiteral("type"), QStringLiteral("openvpn"),
              QStringLiteral("file"), path},
             [this](bool ok, const QString &out) {
        if (!ok) {
            emit vpnImportFinished(false, out);
            return;
        }
        // "Connection 'name' (uuid) successfully added."
        const QString uuid = QRegularExpression(QStringLiteral("\\(([0-9a-f-]{36})\\)")).match(out).captured(1);
        if (uuid.isEmpty()) {
            emit vpnImportFinished(true, out);
            return;
        }
        runNmcli({QStringLiteral("connection"), QStringLiteral("modify"), QStringLiteral("uuid"), uuid,
                  QStringLiteral("connection.autoconnect"), QStringLiteral("no")}, [this, uuid, out](bool, const QString &) {
            runNmcli({QStringLiteral("connection"), QStringLiteral("down"), QStringLiteral("uuid"), uuid},
                     [this, out](bool, const QString &) { emit vpnImportFinished(true, out); });   // "down" fails if never up: fine
        });
    });
}

void Lelan::importWireGuard(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        emit vpnImportFinished(false, QStringLiteral("Cannot read %1: %2").arg(path, f.errorString()));
        return;
    }
    QString error;
    const NmSettings settings = wireGuardSettings(QString::fromUtf8(f.readAll()), QFileInfo(path).completeBaseName(), &error);
    if (settings.isEmpty()) {
        emit vpnImportFinished(false, error);
        return;
    }
    static const QMetaType peersType = qDBusRegisterMetaType<QList<QVariantMap>>();   // aa{sv}
    Q_UNUSED(peersType);
    QDBusMessage add = QDBusMessage::createMethodCall(kNm, kNmSettingsPath, kNmSettings, QStringLiteral("AddConnection2"));
    constexpr uint kToDisk = 0x1, kBlockAutoconnect = 0x20;
    add << QVariant::fromValue(settings) << (kToDisk | kBlockAutoconnect) << QVariantMap();
    const QString name = settings.value(QStringLiteral("connection")).value(QStringLiteral("id")).toString();
    onReply(this, add, [this, name](QDBusPendingCallWatcher *w) {
        if (w->isError()) {
            emit vpnImportFinished(false, w->error().message());
            return;
        }
        emit vpnImportFinished(true, QStringLiteral("Connection '%1' added. Press Connect to use it.").arg(name));
    });
}

void Lelan::runNmcli(const QStringList &args, std::function<void(bool, const QString &)> done)
{
    auto *proc = new QProcess(this);
    connect(proc, &QProcess::finished, this, [proc, done](int code, QProcess::ExitStatus status) {
        proc->deleteLater();
        const bool ok = status == QProcess::NormalExit && code == 0;
        QString msg = QString::fromLocal8Bit(ok ? proc->readAllStandardOutput() : proc->readAllStandardError()).trimmed();
        if (!ok && msg.isEmpty())
            msg = QStringLiteral("nmcli failed (exit %1)").arg(code);
        done(ok, msg);
    });
    connect(proc, &QProcess::errorOccurred, this, [proc, done](QProcess::ProcessError e) {
        if (e != QProcess::FailedToStart)
            return;
        proc->deleteLater();
        done(false, QStringLiteral("nmcli is not installed"));
    });
    proc->start(QStringLiteral("nmcli"), args);
}
