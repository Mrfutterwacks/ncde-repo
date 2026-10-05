// Lelan — NCDE's nervous system (lelan.md): the one hub that subscribes to every system service
// (D-Bus: UPower, NetworkManager, BlueZ, UDisks2, logind, PowerProfiles, portals, MPRIS,
// Sentinel, KickassGuard, …) and exposes it to QML as `lelan.*`. Components are "lelan-compliant":
// they read these properties instead of polling backends themselves.
//
// Rebuilt from LaPivot oracle 3507b4c6…. The block between GENERATED markers is produced by
// tools/gen_header.py from the oracle's own moc metadata — do not edit it by hand; the QML binds
// to exactly these names. Implementation is split by subsystem: Lelan_<subsystem>.cpp.
#pragma once

#include <QObject>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusVariant>
#include <QHash>
#include <QMap>
#include <QQueue>
#include <QSet>
#include <QString>
#include <QStringList>
#include <QVariant>

#include <functional>

class AnimPolicy;
class QTimer;
struct pa_threaded_mainloop;
struct pa_context;
class ZenGovernor;

using SentinelTempMap = QMap<QString, double>;
using SentinelFanMap = QMap<QString, uint>;
using BlueZInterfaceMap = QMap<QString, QVariantMap>;
using BlueZObjectMap = QMap<QDBusObjectPath, BlueZInterfaceMap>;

// night = sunset..sunrise (wrapping midnight); hours are local 0..24 (Lelan_time.cpp)
bool lelanIsNight(double sunset, double sunrise, double nowHours);

class Lelan : public QObject
{
// ---- GENERATED: tools/gen_header.py Lelan ----
    Q_OBJECT
    Q_PROPERTY(QVariantMap network READ network NOTIFY networkChanged)
    Q_PROPERTY(QVariantMap vpn READ vpn NOTIFY vpnStateChanged)
    Q_PROPERTY(bool wifiEnabled READ wifiEnabled NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList wifiNetworks READ wifiNetworks NOTIFY wifiChanged)
    Q_PROPERTY(QVariantMap activeNetwork READ activeNetwork NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList vpnConnections READ vpnConnections NOTIFY vpnStateChanged)
    Q_PROPERTY(QVariantList users READ users NOTIFY usersChanged)
    Q_PROPERTY(QString userName READ userName NOTIFY userNameChanged)
    Q_PROPERTY(QVariantList printers READ printers NOTIFY printersChanged)
    Q_PROPERTY(QVariantMap battery READ battery NOTIFY batteryChanged)
    Q_PROPERTY(QString powerProfile READ powerProfile NOTIFY powerProfileChanged)
    Q_PROPERTY(int thermalPressure READ thermalPressure NOTIFY thermalPressureChanged)
    Q_PROPERTY(QVariantMap sentinelTemps READ sentinelTemps NOTIFY sentinelTempsChanged)
    Q_PROPERTY(QVariantMap sentinelFans READ sentinelFans NOTIFY sentinelFansChanged)
    Q_PROPERTY(QVariantMap audio READ audio NOTIFY audioChanged)
    Q_PROPERTY(int volume READ volume NOTIFY onAudioVolumeUpdated)
    Q_PROPERTY(int balance READ balance NOTIFY audioChanged)
    Q_PROPERTY(bool muted READ muted NOTIFY onAudioMuteUpdated)
    Q_PROPERTY(QVariantList appStreams READ appStreams NOTIFY appStreamsChanged)
    Q_PROPERTY(QVariantList outputDevices READ outputDevices NOTIFY audioDevicesChanged)
    Q_PROPERTY(QVariantList inputDevices READ inputDevices NOTIFY audioDevicesChanged)
    Q_PROPERTY(QString defaultSourceName READ defaultSourceName NOTIFY audioDeviceChanged)
    Q_PROPERTY(QVariantMap media READ media NOTIFY mediaChanged)
    Q_PROPERTY(bool mediaActive READ mediaActive NOTIFY mediaChanged)
    Q_PROPERTY(QVariantMap bluetooth READ bluetooth NOTIFY bluetoothChanged)
    Q_PROPERTY(bool bluetoothEnabled READ bluetoothEnabled NOTIFY bluetoothChanged)
    Q_PROPERTY(bool bluetoothDiscoverable READ bluetoothDiscoverable NOTIFY bluetoothChanged)
    Q_PROPERTY(QVariantList bluetoothDevices READ bluetoothDevices NOTIFY bluetoothChanged)
    Q_PROPERTY(QVariantMap bluetoothAudioDevice READ bluetoothAudioDevice NOTIFY bluetoothAudioDeviceChanged)
    Q_PROPERTY(QVariantList removableVolumes READ removableVolumes NOTIFY storageChanged)
    Q_PROPERTY(QVariantMap disk READ disk NOTIFY diskChanged)
    Q_PROPERTY(QVariantMap updates READ updates NOTIFY packageStateChanged)
    Q_PROPERTY(bool darkMode READ darkMode NOTIFY darkModeChanged)
    Q_PROPERTY(QString accentColor READ accentColor NOTIFY onAccentColorChanged)
    Q_PROPERTY(QString systemFont READ systemFont NOTIFY systemFontChanged)
    Q_PROPERTY(QVariantMap filigreePalette READ filigreePalette NOTIFY filigreePalettesChanged)
    Q_PROPERTY(QVariantMap location READ location NOTIFY placeNameChanged)
    Q_PROPERTY(QString placeName READ placeName NOTIFY placeNameChanged)
    Q_PROPERTY(QVariantMap clock READ clock NOTIFY clockChanged)
    Q_PROPERTY(QString timezone READ timezone NOTIFY timezoneChanged)
    Q_PROPERTY(bool locating READ locating NOTIFY timezoneChanged)
    Q_PROPERTY(QVariantList tray READ tray NOTIFY trayChanged)
    Q_PROPERTY(bool sessionActive READ sessionActive NOTIFY onSessionActiveChanged)
    Q_PROPERTY(int vtActive READ vtActive NOTIFY vtActiveChanged)
    Q_PROPERTY(bool screensaver READ screensaver NOTIFY screensaverChanged)
    Q_PROPERTY(QString hostname READ hostname NOTIFY hostnameChanged)
    Q_PROPERTY(QString locale READ locale NOTIFY localeChanged)
    Q_PROPERTY(QVariantMap kickass READ kickass NOTIFY kickassStatusChanged)
    Q_PROPERTY(QVariantList notifications READ notifications NOTIFY notificationsChanged)
    Q_PROPERTY(int animLevel READ animLevel NOTIFY animLevelChanged)
    Q_PROPERTY(bool reduceMotion READ reduceMotion NOTIFY animLevelChanged)
    Q_PROPERTY(QString hardwareTier READ hardwareTier NOTIFY hardwareTierChanged)
    Q_PROPERTY(double batteryPercent READ batteryPercent NOTIFY batteryChanged)
    Q_PROPERTY(bool batteryCharging READ batteryCharging NOTIFY batteryChanged)
    Q_PROPERTY(bool hasBattery READ hasBattery NOTIFY batteryChanged)
    Q_PROPERTY(bool networkOnline READ networkOnline NOTIFY networkChanged)
    Q_PROPERTY(bool networkUp READ networkUp NOTIFY networkChanged)
    Q_PROPERTY(QString mediaTitle READ mediaTitle NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaArtist READ mediaArtist NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaAlbum READ mediaAlbum NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaArtUrl READ mediaArtUrl NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaTrackId READ mediaTrackId NOTIFY mediaChanged)
    Q_PROPERTY(qlonglong mediaDuration READ mediaDuration NOTIFY mediaChanged)
    Q_PROPERTY(qlonglong mediaPosition READ mediaPosition NOTIFY mediaPositionChanged)
    Q_PROPERTY(bool mediaPlaying READ mediaPlaying NOTIFY mediaChanged)

public:
    QVariantMap network() const;
    QVariantMap vpn() const;
    bool wifiEnabled() const;
    QVariantList wifiNetworks() const;
    QVariantMap activeNetwork() const;
    QVariantList vpnConnections() const;
    QVariantList users() const;
    QString userName() const;
    QVariantList printers() const;
    QVariantMap battery() const;
    QString powerProfile() const;
    int thermalPressure() const;
    QVariantMap sentinelTemps() const;
    QVariantMap sentinelFans() const;
    QVariantMap audio() const;
    int volume() const;
    int balance() const;
    bool muted() const;
    QVariantList appStreams() const;
    QVariantList outputDevices() const;
    QVariantList inputDevices() const;
    QString defaultSourceName() const;
    QVariantMap media() const;
    bool mediaActive() const;
    QVariantMap bluetooth() const;
    bool bluetoothEnabled() const;
    bool bluetoothDiscoverable() const;
    QVariantList bluetoothDevices() const;
    QVariantMap bluetoothAudioDevice() const;
    QVariantList removableVolumes() const;
    QVariantMap disk() const;
    QVariantMap updates() const;
    bool darkMode() const;
    QString accentColor() const;
    QString systemFont() const;
    QVariantMap filigreePalette() const;
    QVariantMap location() const;
    QString placeName() const;
    QVariantMap clock() const;
    QString timezone() const;
    bool locating() const;
    QVariantList tray() const;
    bool sessionActive() const;
    int vtActive() const;
    bool screensaver() const;
    QString hostname() const;
    QString locale() const;
    QVariantMap kickass() const;
    QVariantList notifications() const;
    int animLevel() const;
    bool reduceMotion() const;
    QString hardwareTier() const;
    double batteryPercent() const;
    bool batteryCharging() const;
    bool hasBattery() const;
    bool networkOnline() const;
    bool networkUp() const;
    QString mediaTitle() const;
    QString mediaArtist() const;
    QString mediaAlbum() const;
    QString mediaArtUrl() const;
    QString mediaTrackId() const;
    qlonglong mediaDuration() const;
    qlonglong mediaPosition() const;
    bool mediaPlaying() const;

    Q_INVOKABLE QVariantMap loadConfig(const QString &name);
    Q_INVOKABLE bool saveConfig(const QString &name, const QVariantMap &data);
    Q_INVOKABLE qlonglong monoRawMs();

signals:
    void networkChanged();
    void vpnStateChanged();
    void wifiChanged();
    void batteryChanged();
    void powerProfileChanged();
    void powerChanged();
    void thermalPressureChanged();
    void sentinelTempsChanged();
    void sentinelFansChanged();
    void driverMissing(const QString &device, const QString &modalias, const QString &suggestedModule);
    void statsChanged();
    void audioChanged();
    void audioDeviceChanged();
    void audioDevicesChanged();
    // DECLARED ADDITION (not in the oracle's moc interface, see tests/iface_additions/Lelan.txt).
    // The oracle's onSentinelInputDeviceAdded/Removed only emitted statsChanged, so a mouse
    // plugged in AFTER login kept the default pointer speed until input settings were re-applied
    // for some other reason. Settings::setLelan() connects this to applyInput so a hotplug takes
    // effect immediately (README: "Lelan devices: ADD signal inputDevicesChanged() emitted there").
    void inputDevicesChanged();
    void bluetoothAudioDeviceChanged();
    void onAudioVolumeUpdated();
    void onAudioMuteUpdated();
    void onFallbackSinkUpdated();
    void appStreamsChanged();
    void mediaChanged();
    void mediaPositionChanged();
    void appNameChanged();
    void appIconChanged();
    void durationChanged();
    void bluetoothChanged();
    void diskChanged();
    void diskDeviceChanged();
    void diskMountChanged();
    void storageChanged();
    void kickassChanged();
    void kickassStatusChanged();
    void kickassSiteBlocked(const QString &domain, const QString &detail);
    void kickassThreatBlocked(const QString &app, const QString &detail, int severity);
    void kickassThreatBehavioral(const QString &subject, const QString &detail, const QString &kind);
    void kickassNetworkAlert(const QString &src, const QString &detail);
    void packageStateChanged();
    void updatesChanged();
    void clockChanged();
    void timeJumped();
    void pulse(qulonglong tick);
    void leanSleeping();
    void leanWaking();
    void dateTimeChanged();
    void timezoneChanged();
    void weatherChanged();
    void placeNameChanged();
    void moonPositionChanged();
    void trayChanged();
    void onTrayBadgeChanged();
    void onTrayPercentChanged();
    void themeChanged();
    void darkModeChanged();
    void onAccentColorChanged();
    void wallpaperChanged();
    void systemFontChanged();
    void slideshowChanged();
    void filigreePalettesChanged();
    void onSessionActiveChanged();
    void vtActiveChanged();
    void screensaverChanged();
    void screenConfigChanged();
    void screenGeometryChanged();
    void hostnameChanged();
    void localeChanged();
    void userNameChanged();
    void usersChanged();
    void printersChanged();
    void notificationsChanged();
    void animLevelChanged();
    void hardwareTierChanged();

public slots:
    void onWMScreenConfig(int, int);
    void onWindowTierNeeded(uint pid, const QString &tier);
    void onWindowClosed(uint pid);
    void applyProperties(const QVariantMap &m);
    void fetchAndApply(const QString &key);
    void mediaPlayPause();
    void mediaNext();
    void mediaPrevious();
    void mediaSeek(qlonglong positionUs);
    void setVolume(int v);
    void toggleMute();
    void setBalance(int v);
    void setAppVolume(const QString &name, int volumePct);
    void setOutputDevice(const QString &name);
    void setInputDevice(const QString &name);
    void setWifiEnabled(bool on);
    void connectWifi(const QString &ssid, const QString &password);
    void disconnectWifi();
    void connectVpn(const QString &name);
    void disconnectVpn(const QString &name);
    void setBluetoothEnabled(bool on);
    void setBluetoothDiscoverable(bool on);
    void bluetoothConnect(const QString &address);
    void bluetoothDisconnect(const QString &address);
    void bluetoothPair(const QString &address);
    void bluetoothRemove(const QString &address);
    void bluetoothScan();
    void setTimezone(const QString &zone);
    void setNtp(bool on);
    void refreshLocation();
    void addUser(const QString &name, const QString &displayName, bool isAdmin);
    void removeUser(const QString &name);
    void setUserAdmin(const QString &name, bool admin);
    void changePassword(const QString &name, const QString &pwd);
    void setAutoLogin(const QString &name, bool on = true);
    void setUserAvatar(const QString &name, const QString &file);
    void setDefaultPrinter(const QString &name);
    void removePrinter(const QString &name);
    void mountVolume(const QString &objectPath);
    void unmountVolume(const QString &objectPath);
    void setAnimUtilClamp(bool boost);
    void setReduceMotionPref(bool on);
    void retryFallbackSink();

private slots:
    void onNameOwnerChanged(const QString &name, const QString &oldOwner, const QString &newOwner);
    void onSystemNameOwnerChanged(const QString &name, const QString &oldOwner, const QString &newOwner);
    void onCoalescedTick();
    void onPulse();
    void recomputeAnimLevel();
    void drainIdleQueue();
    void onNetworkStateChanged(uint state);
    void onNmPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onVpnStateChanged(uint state, uint reason);
    void onWifiPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onBatteryPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onBlueZInterfacesAdded(const QDBusObjectPath &path, const BlueZInterfaceMap &ifaces);
    void onBlueZInterfacesRemoved(const QDBusObjectPath &path, const QStringList &ifaces);
    void onBlueZPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onUDisks2InterfacesAdded(const QDBusObjectPath &path, const BlueZInterfaceMap &ifaces);
    void onUDisks2InterfacesRemoved(const QDBusObjectPath &path, const QStringList &ifaces);
    void onUDisks2FilesystemPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void applyPulseState(int volume, bool muted, const QString &sink, uint sinkIndex, int channels);
    void applyAppStreams(const QVariantList &streams);
    void applyOutputDevices(const QVariantList &devs);
    void applyInputDevices(const QVariantList &devs);
    void applyDefaultSource(const QString &name);
    void onPowerProfilesPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onPackageKitUpdatesChanged();
    void onPackageKitUpdatesPackage(uint info, const QString &packageId, const QString &summary);
    void onPackageKitUpdatesFinished(uint exit, uint runtime);
    void onPortalSettingChanged(const QString &ns, const QString &key, const QDBusVariant &value);
    void onLowMemoryWarning(uchar level);
    void onGeoClue2Location(const QDBusObjectPath &oldLoc, const QDBusObjectPath &newLoc);
    void onTimedate1PropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onHostname1PropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onLocale1PropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onSessionActiveChangedSlot(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onSessionLock();
    void onSessionUnlock();
    void onPrepareForSleep(bool before);
    void onScreenSaverActivated(bool active);
    void onActionInvoked(uint id, const QString &action);
    void onPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onAccountsPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &inval);
    void onAccountsUserAdded(const QDBusObjectPath &path);
    void onAccountsUserDeleted(const QDBusObjectPath &path);
    void onMprisSeeked(qlonglong positionUs);
    void onLayoutUpdated();
    void rebuildTray();
    void onTrayItemChanged();
    void onSentinelDisplayConnected(const QString &name);
    void onSentinelDisplayDisconnected(const QString &name);
    void onSentinelUsbDeviceAdded(const QString &id, const QString &name);
    void onSentinelUsbDeviceRemoved(const QString &id, const QString &name);
    void onSentinelInputDeviceAdded(const QString &name);
    void onSentinelInputDeviceRemoved(const QString &name);
    void onSentinelAudioDeviceChanged(const QString &id, const QString &name);
    void onSentinelBatteryStateChanged(bool onBattery, int percentage);
    void onSentinelNetworkStateChanged(const QString &iface, bool up);
    void onSentinelThermalChanged(const SentinelTempMap &temps);
    void onSentinelFanChanged(const SentinelFanMap &fans);
    void onSentinelThermalCritical(const QString &sensor, double tempC);
    void onSentinelDriverMissing(const QString &device, const QString &modalias, const QString &suggested);
    void onKickassStatusChanged(bool armed, int level);
    void onKickassThreatBlocked(const QString &app, const QString &detail, int severity);
    void onKickassThreatBehavioral(const QString &subject, const QString &detail, const QString &kind);
    void onKickassSiteBlocked(const QString &site, const QString &detail);
    void onKickassNetworkAlert(const QString &src, const QString &detail);
// ---- END GENERATED ----

public:
    // ---- additions beyond the oracle (declared in tests/iface_additions/Lelan.txt) ----
    // Settings > About facts sensed by Sentinel (GetSystemInfo): release, cpu, memory, gpu, disk.
    // settings-tabs.md: "AboutTab hardware grid — needs C++ (properties don't exist in binary)".
    Q_PROPERTY(QVariantMap systemInfo READ systemInfo NOTIFY systemInfoChanged)
public:
    QVariantMap systemInfo() const { return m_systemInfo; }
signals:
    void systemInfoChanged();

public:
    // Settings > Network: the cable (lelan.md §4 NetworkManager; NetworkTab showed Wi-Fi state there).
    Q_PROPERTY(QVariantMap wiredNetwork READ wiredNetwork NOTIFY networkChanged)
    QVariantMap wiredNetwork() const;
    // Settings > Network: add a VPN from an .ovpn / WireGuard .conf file (the nmtui entry was dead).
    Q_INVOKABLE void importVpn(const QString &file);
    Q_INVOKABLE void removeVpn(const QString &name);
    // Settings > Bluetooth: scanning shown while discovery runs (it stops by itself after 30 s).
    Q_PROPERTY(bool bluetoothScanning READ bluetoothScanning NOTIFY bluetoothChanged)
    bool bluetoothScanning() const;
    // Settings > Bluetooth pairing prompt (NCDE's org.bluez.Agent1): {kind, address, name, code}, {} = none.
    Q_PROPERTY(QVariantMap bluetoothPairing READ bluetoothPairing NOTIFY bluetoothPairingChanged)
    QVariantMap bluetoothPairing() const;
    Q_INVOKABLE void bluetoothPairingReply(bool accept, const QString &value);
    // Settings > Storage: safe removal (S2) and encrypted sticks (S6)
    Q_INVOKABLE void ejectVolume(const QString &path);
    Q_INVOKABLE void unlockVolume(const QString &path, const QString &passphrase);
    // Settings > Power "When the lid closes": the lid state from logind (Settings acts on it)
    Q_PROPERTY(bool lidClosed READ lidClosed NOTIFY lidClosedChanged)
    bool lidClosed() const;
public slots:
    // Settings > Storage "Auto-mount USB on insertion" (Settings::autoMountUsb; main() pushes it here on
    // start and on every Settings::storageChanged). Replaces the ncde-automount helper daemon (S7).
    void setAutoMountPref(bool on);
    // Settings > Privacy "Location" (Settings::locationEnabled): off = GeoClue stopped, coordinates dropped (T8)
    void setLocationAllowed(bool on);
signals:
    // a Wi-Fi join failed (wrong password, network gone, no address); NetworkTab shows `reason`
    void wifiConnectFailed(const QString &ssid, const QString &reason);
    void vpnImportFinished(bool ok, const QString &message);
    void bluetoothPairingChanged();
    // a Bluetooth action failed; address empty = the adapter itself (power, scan)
    void bluetoothFailed(const QString &address, const QString &reason);
    // a mount / unmount / eject / unlock failed (S1); `path` = the volume's UDisks object path
    void volumeFailed(const QString &path, const QString &reason);
    // the stick is unmounted and powered off: safe to remove (S2)
    void volumeEjected(const QString &label);
    void lidClosedChanged(bool closed);

public:
    // useSentinel: talk to io.ncde.Sentinel (system bus). main() passes true; tests pass false.
    explicit Lelan(QObject *parent = nullptr, bool useSentinel = true);
    ~Lelan() override;

    bool onBattery() const { return m_onBattery; }
    // ~/.config/ncde/<name>.json (Lelan_config.cpp); Settings reads and writes through these
    static QString configDir();
    static QString configPath(const QString &name);
    static QVariantMap readConfig(const QString &name);
    static bool writeConfig(const QString &name, const QVariantMap &data);
    void setAnimPolicy(AnimPolicy *policy);
    void applyZenStartupHints();
    // Oracle had a setEngine forwarder to NCDEEngine. NCDEEngine is the colour/theme engine ONLY
    // (digest §2) and no longer reads system data, so the oracle's body was a no-op; kept for
    // interface parity. Not part of the oracle's moc-exposed interface.
    void setEngine(QObject *engine);
    // Run work later, when the machine is not in a low-power / screen-idle state (lelan.md
    // "idle queue"); jobs run under IO priority class IDLE.
    void deferWhenIdle(std::function<void()> job);

private:
    // ---- power (Lelan_power.cpp) ----
    void subscribeToUPower();
    void subscribeToPowerProfiles();
    void applyBattery(const QVariantMap &changes, bool fromSentinel);
    void requestSentinelPowerProfile();
    QVariantMap m_battery;                   // "percentage", "state", "timeToEmpty"
    bool m_onBattery = false;
    bool m_sentPowerProfileOnBattery = false;
    bool m_sentPowerProfileValid = false;
    QString m_powerProfile;

    // ---- governor (Lelan_zen.cpp) ----
    void subscribeToSentinel();
    void subscribeToMemoryMonitor();
    void fetchHardwareTier();
    void fetchSystemInfo();
    QVariantMap m_systemInfo;
    void onHardwareTierReceived(const QString &tier);
    void applyThermalCap(bool on);
    void onPressureChanged(int pressure);
    void callSentinel(const QString &method, const QVariantList &args);
    bool m_useSentinel = true;
    AnimPolicy *m_animPolicy = nullptr;
    ZenGovernor *m_zen = nullptr;
    QTimer *m_tickTimer = nullptr;
    quint64 m_tickCount = 0;
    int m_thermalPressure = 0;
    bool m_reduceMotion = false;
    int m_animLevel = 0;
    QString m_hardwareTier;
    int m_hardwareTierFloor = 0;             // "low" tier: never below Reduced
    SentinelTempMap m_sentinelTempsRaw;
    QVariantMap m_sentinelTemps;
    QVariantMap m_sentinelFans;
    QQueue<std::function<void()>> m_idleQueue;
    QTimer *m_idleTimer = nullptr;
    bool m_idleIoClass = true;

    // ---- kickass / packages (Lelan_kickass.cpp, Lelan_packages.cpp) ----
    QVariantMap m_kickass;                 // last KickassGuard property snapshot
    QVariantMap m_updates;                 // last PackageKit updates snapshot
    QVariantList m_updatePackages;
    QString m_updateTransaction;
    quint64 m_updatesGeneration = 0;

    // ---- session (Lelan_session.cpp) ----
    void subscribeToLogind();
    void subscribeToScreenSaver();
    void setLocked(bool locked);
    bool m_sessionActive = false;
    int m_vtActive = 0;
    bool m_screensaver = false;
    void setLidClosed(bool closed);
    bool m_lidClosed = false;
    QObject *m_lidRelay = nullptr;
    QVariantList m_users;
    QString m_currentUserName;
    QHash<QString, QDBusObjectPath> m_userPaths;
    QSet<QString> m_usersBeingCreated;
    QHash<QString, QString> m_pendingUserPasswords;
    quint64 m_usersGeneration = 0;
    QVariantList m_printers;
    quint64 m_printersGeneration = 0;
    QVariantList m_tray;
    QVariantList m_notifications;
    QHash<QString, QVariantMap> m_trayItems;
    QSet<QString> m_registeredTrayItems;
    quint64 m_trayGeneration = 0;

    // ---- subscriptions implemented in their subsystem files ----
    void subscribeToNetworkManager();      // Lelan_network.cpp
    void subscribeToWifi();                // Lelan_network.cpp
    void subscribeToPlayers();             // Lelan_media.cpp
    void removePlayer(const QString &service);
    void subscribeToPortalSettings();      // Lelan_portal.cpp
    void subscribeToKickassGuard();        // Lelan_kickass.cpp
    void subscribeToAccountsService();     // Lelan_users.cpp
    void refreshUsers();                  // Lelan_users.cpp
    void updateCurrentUserName();
    void withUserPath(const QString &name, std::function<void(const QDBusObjectPath &)> ready);
    void callUser(const QString &name, const QString &method, const QVariantList &args,
                  std::function<void()> done = {});
    void refreshPrinters();               // Lelan_printers.cpp
    void subscribeTrayOwner();             // Lelan_tray.cpp
    void publishTrayItems(const QVariantList &items);
    void readTrayItem(const QString &service, const QString &path, quint64 generation);
    void publishNotifications();
    void subscribeToBlueZ();               // Lelan_bluetooth.cpp
    void subscribeToUDisks2();             // Lelan_storage.cpp
    void subscribeToGeoClue();             // Lelan_time.cpp
    void subscribeToTimeDate();            // Lelan_time.cpp
    void subscribeToHostnameLocale();      // Lelan_time.cpp
    void subscribeToPackageKit();          // Lelan_packages.cpp
    void fetchPackageKitUpdates();         // Lelan_packages.cpp

    // ---- portal appearance (Lelan_portal.cpp, oracle-exact) ----
    void applyPortalAppearance(const QString &key, const QVariant &value);
    bool m_darkMode = false;
    QString m_accentColor;                   // "#rrggbb", empty = none

    // ---- time, place, host (Lelan_time.cpp) ----
    void setTimezoneValue(const QString &tz);
    void updateClock();
    void updateNightFlag(bool force = false);
    void setLocating(bool on);
    QVariantMap m_location;                  // lat, lon, sunrise, sunset, night
    QString m_placeName;
    QVariantMap m_clock;                     // epoch
    QString m_timezone;
    bool m_locating = true;                  // until GeoClue answers or fails
    QString m_hostname;
    QString m_locale;
    QString m_geoClient;
    bool m_locationAllowed = true;

    // ---- audio (Lelan_audio.cpp) ----
public:
    // libpulse callbacks (pulse mainloop thread) queue onto Lelan's thread through these; plain
    // methods, not slots, so the QML-facing interface stays the oracle's.
    void applyPulseStateFromBridge(int volume, bool muted, const QString &sink, uint sinkIndex, int channels);
    void applyOutputDevicesFromBridge(const QVariantList &devs);
    void applyInputDevicesFromBridge(const QVariantList &devs);
    void applyAppStreamsFromBridge(const QVariantList &streams);
    void applyDefaultSourceFromBridge(const QString &name);
private:
    void subscribeToAudio();
    void stopPulse();
    void applyChannelVolumes();
    pa_threaded_mainloop *m_pulseLoop = nullptr;
    pa_context *m_pulseCtx = nullptr;
    uint m_sinkIndex = 0xFFFFFFFFu;          // PA_INVALID_INDEX
    int m_sinkChannels = 2;
    QString m_sinkName;
    int m_volume = 0;
    bool m_muted = false;
    int m_balance = 50;                      // 0..100, 50 = centre
    QVariantMap m_audio;                     // "volume", "muted", "sink"
    QVariantList m_appStreams;
    QVariantList m_outputDevices;
    QVariantList m_inputDevices;
    QString m_defaultSourceName;

    // ---- network (Lelan_network.cpp) ----
    struct ApInfo { QString ssid; uint strength = 0; uint wpaFlags = 0; uint rsnFlags = 0; };
    struct VpnProfile { QString path, name, type; };
    void setNetworkValue(const QString &key, const QVariant &value);   // invalid value = remove
    void setActiveNetworkValue(const QString &key, const QVariant &value);
    void rebuildAccessPoints();
    void publishAccessPoints();
    void onAccessPointChanged(const QString &path, const QVariantMap &changed);
    void readActiveNetwork();
    void syncWifiConnectedFlag(const QString &ssid);
    void readActiveIp(const QString &ip4Config);
    void scheduleWifiChanged();
    void refreshVpnConnections();
    void markActiveVpns();
    QVariantMap m_network;                   // state, primary, iface, up, ssid
    QVariantMap m_vpn;                       // state, reason (last VpnStateChanged)
    bool m_wifiEnabled = false;
    QVariantList m_wifiNetworks;             // {ssid, signal, secured, connected}
    QVariantMap m_activeNetwork;             // {ssid, speed, ip}
    QVariantList m_vpnConnections;           // {name, type, connected}
    QString m_wifiDevice;
    QString m_activeApPath;
    bool m_wifiChangedPending = false;
    QHash<QString, ApInfo> m_apCache;        // AP object path -> what the list needs
    QObject *m_apRelay = nullptr;
    QObject *m_nmSettingsRelay = nullptr;
    QHash<QString, QString> m_wifiProfiles;  // ssid -> saved profile path
    QList<VpnProfile> m_vpnProfiles;
    QHash<QString, QString> m_vpnPaths;      // VPN name -> saved profile path
    QHash<QString, QString> m_activeVpnByProfile;   // saved profile path -> active connection path
    quint64 m_vpnRefreshGeneration = 0;
    quint64 m_vpnMarkGeneration = 0;
    QString m_joiningSsid;                   // connectWifi in flight (N8)
    bool m_joinHadPassword = false;
    void failJoin(const QString &reason);
    QVariantMap m_wiredNetwork{{QStringLiteral("present"), false}, {QStringLiteral("connected"), false}};
    QString m_wiredDevice;
    QObject *m_wiredRelay = nullptr;
    void subscribeToWired(const QString &device, const QString &iface);
    void setWiredValue(const QString &key, const QVariant &value);
    void applyWiredState(uint state);
    void readWiredIp(const QString &ip4Config);
    void importWireGuard(const QString &path);
    void runNmcli(const QStringList &args, std::function<void(bool, const QString &)> done);

    // ---- Bluetooth (Lelan_bluetooth.cpp) ----
    friend class BluetoothAgent;
    void rebuildBluetooth();
    void registerBtAgent();
    void publishBluetooth();
    void patchBtDevice(const QString &path, const QVariantMap &changed);
    bool btDevicePaired(const QString &path) const;
    void stopBtScan();
    void btAgentAsk(const QString &kind, const QString &devicePath, const QString &code, const QDBusMessage &request,
                    const QString &bus);
    void btAgentShow(const QString &kind, const QString &devicePath, const QString &code);
    void btAgentCancel();
    QString m_btAdapter;                     // BlueZ adapter object path in use
    QVariantMap m_btAdapterProps;            // its Adapter1 properties
    QMap<QString, QVariantMap> m_btDevices;  // device path -> Device1 properties
    QHash<QString, QString> m_btAddrToPath;  // address -> device path
    bool m_btPowered = false;
    bool m_btDiscoverable = false;
    bool m_btDiscovering = false;
    bool m_btWantPowered = false;
    bool m_btAgentDefault = false;
    QVariantMap m_bluetooth;                 // adapter summary (B8)
    QVariantList m_bluetoothDevices;         // {name, address, type, paired, connected}
    QVariantMap m_bluetoothAudioDevice;
    QVariantMap m_bluetoothPairing;
    QDBusMessage m_btPairingRequest;         // agent call awaiting the tab's answer
    QString m_btPairingBus;                  // connection name it arrived on
    QObject *m_btRelay = nullptr;
    QObject *m_btAgent = nullptr;
    QTimer *m_btScanTimer = nullptr;
    QTimer *m_btPairingTimer = nullptr;

    // ---- storage (Lelan_storage.cpp) ----
    void refreshRemovableVolumes();
    void refreshDiskUsage();
    QVariantList m_removableVolumes;
    QVariantMap m_disk;                      // usedBytes, freeBytes, totalBytes, usedPercent
    QTimer *m_storageTimer = nullptr;
    QObject *m_storageRelay = nullptr;
    QHash<QString, QString> m_volumeDrive;   // volume path -> its drive
    BlueZObjectMap m_storageObjects;         // last UDisks2 object tree (same a{oa{sa{sv}}} shape)
    void applyStorageObjects(const BlueZObjectMap &objs);   // one UDisks2 tree -> removableVolumes (+ S7)
    bool m_autoMount = false;                // S7: Settings::autoMountUsb
    bool m_storageSeeded = false;            // S7: first tree read = what was plugged in before login
    QSet<QString> m_seenFilesystems;         // S7: filesystems already seen (mount each insertion once)

    // ---- media (Lelan_media.cpp) ----
    struct PlayerState {
        QString status;                      // PlaybackStatus: Playing | Paused | Stopped
        QString title, artist, album, artUrl, trackId;
        qlonglong position = 0;              // µs, as of positionAtMs
        qlonglong length = 0;                // µs
        QString app;                         // bus name minus org.mpris.MediaPlayer2.
        qint64 positionAtMs = 0;             // monotonic ms when `position` was true
        double rate = 1.0;
        QString owner;                       // unique bus name (signals arrive from it)
    };
    void addPlayer(const QString &name);
    void fetchPlayer(const QString &name);
    void applyPlayerProps(const QString &name, const QVariantMap &props);
    void readPlayerPosition(const QString &name);
    void publishMedia();
    void refreshMediaPosition();
    void refreshActiveMediaPid();
    void callActivePlayer(const QString &method, const QVariantList &args);
    qlonglong playerPosition(const PlayerState &p) const;
    QHash<QString, PlayerState> m_players;   // well-known bus name -> state
    QHash<QString, QString> m_playerByOwner; // unique name -> well-known name
    QString m_activePlayer;                  // the "now playing" player
    QString m_publishedPlayer;
    QVariantMap m_media;
    bool m_mediaActive = false;
    int m_positionPulses = 0;
    QObject *m_mprisRelay = nullptr;
    uint m_mediaPid = 0;                     // pid of the MPRIS player currently playing
};

Q_DECLARE_METATYPE(SentinelTempMap)
Q_DECLARE_METATYPE(SentinelFanMap)
Q_DECLARE_METATYPE(BlueZInterfaceMap)
