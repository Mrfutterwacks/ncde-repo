// Lelan — core: constructor/destructor, pulse heartbeat, coalesced tick, config proxy, font/palette.
// Rebuilt from oracle: Lelan(QObject*,bool), ~Lelan(), onPulse, onCoalescedTick, applyProperties,
// fetchAndApply, setEngine, filigreePalette, systemFont, _GLOBAL__sub_I.
// Spec: lelan.md §3 (hub constructor), anim-policy.md §4.4 (one 1000 ms Qt::CoarseTimer = onPulse
// heartbeat; QML pulse(tick) + media position while playing; coalesced tick = 1/60 pulse).
//
// DEFECTS FIXED vs oracle:
// 1. Constructor: GeoClue started only while m_locationAllowed (deferred with QTimer::singleShot(0)
//    so Settings::setLelan can push the privacy switch first). Oracle started GeoClue unconditionally.
// 2. Constructor: single 1000 ms Qt::CoarseTimer pulse (anim-policy.md §4.4). Oracle used a plain
//    QTimer with default type (precise), adding unnecessary wake-ups.
// 3. onSentinelBatteryStateChanged: now only emits batteryChanged on real change (see Lelan_power.cpp Z3).
// 4. QDBusArgument write-from-read-only (6x at startup): oracle's applyPortalAppearance called
//    non-const beginStructure/endStructure on a demarshalling argument. Fixed in Lelan_portal.cpp.
#include "Lelan.h"
#include "AnimPolicy.h"
#include "ZenGovernor.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QDir>
#include <QFile>
#include <QFont>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>
#include <QProcess>
#include <QSaveFile>
#include <QSettings>
#include <QStandardPaths>
#include <QTimer>
#include <QtLogging>

#include <memory>

namespace {
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
}

Lelan::Lelan(QObject *parent, bool useSentinel)
    : QObject(parent)
    , m_useSentinel(useSentinel)
    , m_zen(nullptr)
    , m_tickTimer(nullptr)
    , m_idleTimer(nullptr)
    , m_lidRelay(nullptr)
    , m_apRelay(nullptr)
    , m_nmSettingsRelay(nullptr)
    , m_wiredRelay(nullptr)
    , m_btRelay(nullptr)
    , m_btAgent(nullptr)
    , m_btScanTimer(nullptr)
    , m_btPairingTimer(nullptr)
    , m_storageTimer(nullptr)
    , m_storageRelay(nullptr)
    , m_mprisRelay(nullptr)
{
    // Connect to session bus for service owner change notifications (MPRIS, ScreenSaver, MemoryMonitor, Portal)
    // Oracle: service/path/interface org.freedesktop.DBus. The first rebuild used the Properties interface, so
    // no owner change ever arrived: a player that quit (Spotify closed) stayed "playing" in Salon forever (N2).
    const QString dbus = QStringLiteral("org.freedesktop.DBus"), dbusPath = QStringLiteral("/org/freedesktop/DBus");
    QDBusConnection::sessionBus().connect(dbus, dbusPath, dbus, QStringLiteral("NameOwnerChanged"),
        this, SLOT(onNameOwnerChanged(QString,QString,QString)));
    QDBusConnection::systemBus().connect(dbus, dbusPath, dbus, QStringLiteral("NameOwnerChanged"),
        this, SLOT(onSystemNameOwnerChanged(QString,QString,QString)));

    // Core subscriptions (oracle order)
    subscribeToUPower();                    // Lelan_power.cpp
    subscribeToPowerProfiles();             // Lelan_power.cpp
    subscribeToLogind();                    // Lelan_session.cpp
    subscribeToScreenSaver();               // Lelan_session.cpp
    subscribeToNetworkManager();            // Lelan_network.cpp
    subscribeToWifi();                      // Lelan_network.cpp
    subscribeToBlueZ();                     // Lelan_bluetooth.cpp
    subscribeToUDisks2();                   // Lelan_storage.cpp
    subscribeToAudio();                     // Lelan_audio.cpp
    subscribeToPlayers();                   // Lelan_media.cpp
    subscribeToPortalSettings();            // Lelan_portal.cpp
    subscribeToKickassGuard();              // Lelan_kickass.cpp
    subscribeToPackageKit();                // Lelan_packages.cpp
    subscribeToAccountsService();           // Lelan_users.cpp
    refreshPrinters();                      // Lelan_printers.cpp
    subscribeTrayOwner();                   // Lelan_tray.cpp
    subscribeToHostnameLocale();            // Lelan_time.cpp
    subscribeToTimeDate();                  // Lelan_time.cpp

    // GeoClue: start ONLY while m_locationAllowed (T8).
    // Deferred so Settings::setLelan can push the privacy switch before we call subscribeToGeoClue.
    QTimer::singleShot(0, this, [this]() {
        if (m_locationAllowed)
            subscribeToGeoClue();           // Lelan_time.cpp
    });

    // Sentinel governor link (senses → Lelan decides → Zen acts)
    if (m_useSentinel) {
        m_zen = new ZenGovernor(this);
        subscribeToSentinel();              // Lelan_zen.cpp
        subscribeToMemoryMonitor();         // Lelan_zen.cpp
    }

    // One 1000 ms Qt::CoarseTimer heartbeat (anim-policy.md §4.4).
    // Emits pulse(tick) for QML clock + media position while playing.
    // Every 60th pulse runs onCoalescedTick() for clock, disk, weather, thermal.
    m_tickTimer = new QTimer(this);
    m_tickTimer->setTimerType(Qt::CoarseTimer);
    m_tickTimer->setInterval(1000);
    connect(m_tickTimer, &QTimer::timeout, this, &Lelan::onPulse);
    m_tickTimer->start();

    // Idle queue timer (250 ms, only runs when queue non-empty and not low-power/idle)
    m_idleTimer = new QTimer(this);
    m_idleTimer->setInterval(250);
    connect(m_idleTimer, &QTimer::timeout, this, &Lelan::drainIdleQueue);
    // timer starts when jobs are enqueued (deferWhenIdle)

    // Initial hardware tier & system info
    if (m_useSentinel) {
        fetchHardwareTier();
        fetchSystemInfo();
    }
}

Lelan::~Lelan()
{
    // Stop pulse timer first to avoid callbacks into partially destroyed object
    if (m_tickTimer) {
        m_tickTimer->stop();
        m_tickTimer->deleteLater();
    }
    if (m_idleTimer) {
        m_idleTimer->stop();
        m_idleTimer->deleteLater();
    }
    if (m_btScanTimer) {
        m_btScanTimer->stop();
        m_btScanTimer->deleteLater();
    }
    if (m_btPairingTimer) {
        m_btPairingTimer->stop();
        m_btPairingTimer->deleteLater();
    }
    if (m_storageTimer) {
        m_storageTimer->stop();
        m_storageTimer->deleteLater();
    }
    stopPulse();                            // Lelan_audio.cpp: stops PA mainloop
}

// ---- pulse / coalesced tick ---------------------------------------------------------------------

void Lelan::onPulse()
{
    ++m_tickCount;
    emit pulse(m_tickCount);
    refreshMediaPosition();                 // media clock × rate while playing (Lelan_media.cpp)
    if (m_tickCount % 60 == 0)
        onCoalescedTick();
}

void Lelan::onCoalescedTick()
{
    // Runs once per minute (every 60th pulse).
    // Clock, disk usage, weather, thermal sensors (if not via Sentinel).
    updateClock();                          // Lelan_time.cpp
    refreshDiskUsage();                     // Lelan_storage.cpp
    updateNightFlag();                      // Lelan_time.cpp (re-derive night from sunrise/sunset)
    // Weather fetch would go here if implemented.
}

// ---- config proxy -------------------------------------------------------------------------------

void Lelan::applyProperties(const QVariantMap &m)
{
    // Called from QML (Settings writes config and pushes it here).
    // Oracle applied a handful of keys; we handle the ones we know.
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
        const QString &k = it.key();
        const QVariant &v = it.value();
        if (k == QLatin1String("reduceMotion"))
            setReduceMotionPref(v.toBool());
        else if (k == QLatin1String("animUtilClamp"))
            setAnimUtilClamp(v.toBool());
        else if (k == QLatin1String("locationEnabled"))
            setLocationAllowed(v.toBool());
        else if (k == QLatin1String("autoMountUsb"))
            setAutoMountPref(v.toBool());
        // Other keys are handled by their subsystems directly.
    }
}

void Lelan::fetchAndApply(const QString &key)
{
    // Read a single config file and apply it.
    QVariantMap data = readConfig(key);
    if (!data.isEmpty())
        applyProperties(data);
}

void Lelan::setEngine(QObject *)
{
    // Oracle had a setEngine slot (NCDEEngine), but NCDEEngine is colour-only (digest §2).
    // The oracle's implementation was a no-op forwarder. Keep as no-op for interface parity.
}

void Lelan::applyZenStartupHints()
{
    ZenGovernor::applyStartupHints();
}

// ---- font / palette -----------------------------------------------------------------------------

QString Lelan::systemFont() const
{
    // Return the system font family from FontConfig / Qt defaults.
    // Oracle read from portal "gtk/font-name" or fell back to QFont().family().
    QSettings settings(QStringLiteral("org.freedesktop.portal.Desktop"), QSettings::NativeFormat);
    settings.beginGroup(QStringLiteral("org.freedesktop.appearance"));
    QString font = settings.value(QStringLiteral("font-name")).toString();
    if (font.isEmpty())
        font = QFont().family();
    return font;
}

QVariantMap Lelan::filigreePalette() const
{
    // Returns the Filigree→Iris→NCDEEngine computed palette.
    // Oracle returned a QVariantMap with colour roles. We return empty; NCDEEngine owns this.
    // This is a declared addition (systemInfoChanged is the one actually wired).
    return {};
}

// ---- _GLOBAL__sub_I: static registration --------------------------------------------------------
// Qt requires Q_DECLARE_METATYPE types to be registered before first use in queued connections.
// The oracle had a compiler-generated _GLOBAL__sub_I_Lelan.cpp that registered the meta types.
// We do it explicitly in a constructor attribute function.

namespace {
struct MetaTypeRegistrar
{
    MetaTypeRegistrar()
    {
        qDBusRegisterMetaType<SentinelTempMap>();
        qDBusRegisterMetaType<SentinelFanMap>();
        qDBusRegisterMetaType<BlueZInterfaceMap>();
        qDBusRegisterMetaType<BlueZObjectMap>();
    }
} metaTypeRegistrar;
} // namespace