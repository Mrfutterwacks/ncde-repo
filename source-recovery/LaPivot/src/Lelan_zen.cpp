// Lelan — governor glue: animation level, coalesced tick, idle queue, Sentinel link, App Nap.
//
 // Rebuilt from oracle: recomputeAnimLevel, setReduceMotionPref, onCoalescedTick, deferWhenIdle,
 // drainIdleQueue (+IdleIoScope), monoRawMs, setAnimPolicy, setAnimUtilClamp, subscribeToSentinel,
 // onSentinelThermalChanged/FanChanged/ThermalCritical, fetchHardwareTier, onHardwareTierReceived,
 // applyThermalCap, subscribeToMemoryMonitor, onLowMemoryWarning, onWindowTierNeeded,
 // onWindowClosed. The pure decisions live in ZenGovernor (tested against the oracle).
 #include "Lelan.h"
 #include "AnimPolicy.h"
 #include "ZenGovernor.h"
 #include "IdleIoScope.h"

 #include <QDBusConnection>
 #include <QDBusMessage>
 #include <QDBusPendingCallWatcher>
 #include <QDBusPendingReply>
 #include <QDBusMetaType>
 #include <QTimer>
 #include <QtLogging>

 #include <time.h>
 #include <unistd.h>

 namespace {
 const QString kSentinel = QStringLiteral("io.ncde.Sentinel");
 const QString kSentinelPath = QStringLiteral("/io/ncde/Sentinel");
 } // namespace

 // ---- getters ----------------------------------------------------------------------------------

 int Lelan::thermalPressure() const { return m_thermalPressure; }
 int Lelan::animLevel() const { return m_animLevel; }
 bool Lelan::reduceMotion() const { return m_reduceMotion; }
 QString Lelan::hardwareTier() const { return m_hardwareTier; }
 QVariantMap Lelan::sentinelTemps() const { return m_sentinelTemps; }
 QVariantMap Lelan::sentinelFans() const { return m_sentinelFans; }

 qlonglong Lelan::monoRawMs()
 {
     timespec ts {};
     clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
     return qlonglong(ts.tv_sec) * 1000 + ts.tv_nsec / 1000000;
 }

 // ---- animation level --------------------------------------------------------------------------

 void Lelan::setAnimPolicy(AnimPolicy *policy)
 {
     m_animPolicy = policy;
     // Zen decides, Lelan carries the verdict to AnimPolicy. These two hops were
     // declared in ZenGovernor.h but never connected, so Sentinel's cpu_saturated
     // and the portal's memory pressure stopped at Zen and lowPower stayed
     // permanently false. Push current state first so an already-pressing machine
     // is reflected before the first signal.
     if (m_zen && policy) {
         connect(m_zen, &ZenGovernor::cpuPeggedChanged, policy, &AnimPolicy::setLowPowerCpu);
         connect(m_zen, &ZenGovernor::memoryPressureChanged, policy, &AnimPolicy::setLowPowerMemory);
         policy->setLowPowerCpu(m_zen->cpuPegged());
         policy->setLowPowerMemory(m_zen->memoryLevel() > 0);
     }
     recomputeAnimLevel();
 }

 void Lelan::setReduceMotionPref(bool on)
 {
     if (on == m_reduceMotion)
         return;
     m_reduceMotion = on;
     recomputeAnimLevel();
 }

 void Lelan::recomputeAnimLevel()
 {
     const int level = zen::animLevel(m_onBattery, int(batteryPercent()), m_reduceMotion,
                                      m_thermalPressure, m_hardwareTierFloor > 0);
     if (level != m_animLevel) {
         m_animLevel = level;
         emit animLevelChanged();
     }
     if (m_animPolicy) {
         m_animPolicy->setReduceMotion(m_reduceMotion);
         m_animPolicy->setLevel(m_animLevel);
         m_animPolicy->setLowPowerBattery(m_onBattery && batteryPercent() < 16);
     }
 }

 void Lelan::onPressureChanged(int pressure)
 {
     m_thermalPressure = pressure;
     emit thermalPressureChanged();
     recomputeAnimLevel();
     if (m_animPolicy)
         m_animPolicy->setThermalPressure(pressure > 0);
 }

 // Z2: uclamp boost for the thread that asks. Public slot (oracle interface); ZenGovernor applies
 // it to render threads itself — see LaPivot main().
 void Lelan::setAnimUtilClamp(bool boost)
 {
     ZenGovernor::setUtilClampMin(boost);
 }

 // ---- idle queue -------------------------------------------------------------------------------

 void Lelan::deferWhenIdle(std::function<void()> job)
 {
     m_idleQueue.enqueue(std::move(job));
     if (m_idleTimer && !m_idleTimer->isActive())
         m_idleTimer->start();
 }

 void Lelan::drainIdleQueue()
 {
     if (m_idleQueue.isEmpty()) {
         if (m_idleTimer)
             m_idleTimer->stop();
         return;
     }
     const bool held = m_animPolicy && (m_animPolicy->screenIdle() || m_animPolicy->lowPower());
     const bool powered = batteryCharging() || batteryPercent() > 19;
     if (held || !powered)
         return;                                         // try again next 250 ms tick
     std::function<void()> job = m_idleQueue.dequeue();
     if (job) {
         IdleIoScope io(m_idleIoClass);
         job();
     }
 }

 // ---- Sentinel ---------------------------------------------------------------------------------

 void Lelan::callSentinel(const QString &method, const QVariantList &args)
 {
     if (!m_useSentinel)
         return;
     QDBusMessage msg = QDBusMessage::createMethodCall(kSentinel, kSentinelPath, kSentinel, method);
     msg.setArguments(args);
     QDBusConnection::systemBus().asyncCall(msg);
 }

 void Lelan::subscribeToSentinel()
 {
     qDBusRegisterMetaType<SentinelTempMap>();
     qDBusRegisterMetaType<SentinelFanMap>();
     QDBusConnection bus = QDBusConnection::systemBus();
     const struct { const char *signal; const char *slot; } links[] = {
         {"DisplayConnected", SLOT(onSentinelDisplayConnected(QString))},
         {"DisplayDisconnected", SLOT(onSentinelDisplayDisconnected(QString))},
         {"UsbDeviceAdded", SLOT(onSentinelUsbDeviceAdded(QString,QString))},
         {"UsbDeviceRemoved", SLOT(onSentinelUsbDeviceRemoved(QString,QString))},
         {"InputDeviceAdded", SLOT(onSentinelInputDeviceAdded(QString))},
         {"InputDeviceRemoved", SLOT(onSentinelInputDeviceRemoved(QString))},
         {"AudioDeviceChanged", SLOT(onSentinelAudioDeviceChanged(QString,QString))},
         {"BatteryStateChanged", SLOT(onSentinelBatteryStateChanged(bool,int))},
         {"NetworkStateChanged", SLOT(onSentinelNetworkStateChanged(QString,bool))},
         {"ThermalChanged", SLOT(onSentinelThermalChanged(SentinelTempMap))},
         {"FanChanged", SLOT(onSentinelFanChanged(SentinelFanMap))},
         {"ThermalCritical", SLOT(onSentinelThermalCritical(QString,double))},
         {"DriverMissing", SLOT(onSentinelDriverMissing(QString,QString,QString))},
     };
     for (const auto &l : links)
         bus.connect(kSentinel, kSentinelPath, kSentinel, QString::fromLatin1(l.signal), this, l.slot);
     // Z6: Sentinel senses pressure, the governor decides. Connected to ZenGovernor (not a Lelan
     // slot) so Lelan's QML-facing interface stays identical to the oracle's.
     if (m_zen) {
         bus.connect(kSentinel, kSentinelPath, kSentinel, QStringLiteral("PressureSensed"),
                     m_zen, SLOT(onPressureSensed(double,bool)));
         QDBusMessage trip = QDBusMessage::createMethodCall(kSentinel, kSentinelPath, kSentinel,
                                                            QStringLiteral("GetThermalTrip"));
         auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(trip), this);
         connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
             QDBusPendingReply<double> reply = *w;
             w->deleteLater();
             if (!reply.isError() && m_zen)
                 m_zen->setThermalTrip(reply.value());
         });
     }
     fetchHardwareTier();
     fetchSystemInfo();
 }

 void Lelan::fetchSystemInfo()
 {
     auto publish = [this](QVariantMap info) {
         // the one fact only the shell knows
         info.insert(QStringLiteral("compositor"),
                     QStringLiteral("LaPivot · Qt %1 · X11").arg(QString::fromLatin1(qVersion())));
         if (info == m_systemInfo)
             return;
         m_systemInfo = info;
         emit systemInfoChanged();
     };
     if (!m_useSentinel) {
         publish({});
         return;
     }
     // Sentinel answers a{ss}; QDBusPendingReply<QMap<QString,QString>> qFatal()s (abort) unless
     // the type is registered with QtDBus first — that killed the L2 session at login.
     static const QMetaType factsType = qDBusRegisterMetaType<QMap<QString, QString>>();   // a{ss}
     Q_UNUSED(factsType);
     QDBusMessage msg = QDBusMessage::createMethodCall(kSentinel, kSentinelPath, kSentinel, QStringLiteral("GetSystemInfo"));
     auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(msg), this);
     connect(watcher, &QDBusPendingCallWatcher::finished, this, [publish](QDBusPendingCallWatcher *w) {
         QDBusPendingReply<QMap<QString, QString>> reply = *w;
         w->deleteLater();
         QVariantMap info;
         if (!reply.isError()) {
             const QMap<QString, QString> facts = reply.value();
             for (auto it = facts.cbegin(); it != facts.cend(); ++it)
                 info.insert(it.key(), it.value());
         }
         publish(info);
     });
 }

 void Lelan::onSentinelThermalChanged(const SentinelTempMap &temps)
 {
     QVariantMap m;
     for (auto it = temps.cbegin(); it != temps.cend(); ++it)
         m.insert(it.key(), it.value());
     if (m == m_sentinelTemps)
         return;
     m_sentinelTemps = m;
     emit sentinelTempsChanged();
 }

 void Lelan::onSentinelFanChanged(const SentinelFanMap &fans)
 {
     QVariantMap m;
     for (auto it = fans.cbegin(); it != fans.cend(); ++it)
         m.insert(it.key(), it.value());
     if (m == m_sentinelFans)
         return;
     m_sentinelFans = m;
     emit sentinelFansChanged();
 }

 void Lelan::onSentinelThermalCritical(const QString &sensor, double tempC)
 {
     qWarning("[lelan] Sentinel-reported CRITICAL: %s = %.1fC", qPrintable(sensor), tempC);
     if (m_zen)
         m_zen->onSentinelThermalCritical();
 }

 void Lelan::applyThermalCap(bool on)
 {
     callSentinel(QStringLiteral("SetThermalCap"), {on});
 }

 void Lelan::fetchHardwareTier()
 {
     if (!m_useSentinel)
         return;
     QDBusMessage msg = QDBusMessage::createMethodCall(kSentinel, kSentinelPath, kSentinel, QStringLiteral("GetHardwareTier"));
     auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(msg), this);
     connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
         QDBusPendingReply<QString> reply = *w;
         w->deleteLater();
         if (!reply.isError())
             onHardwareTierReceived(reply.value());
     });
 }

 void Lelan::onHardwareTierReceived(const QString &tier)
 {
     if (tier == m_hardwareTier)
         return;
     m_hardwareTier = tier;
     m_hardwareTierFloor = tier == QLatin1String("low") ? 1 : 0;
     emit hardwareTierChanged();
     recomputeAnimLevel();
 }

 // ---- memory -----------------------------------------------------------------------------------

 void Lelan::subscribeToMemoryMonitor()
 {
     QDBusConnection::sessionBus().connect(QStringLiteral("org.freedesktop.portal.Desktop"),
         QStringLiteral("/org/freedesktop/portal/desktop"), QStringLiteral("org.freedesktop.portal.MemoryMonitor"),
         QStringLiteral("LowMemoryWarning"), this, SLOT(onLowMemoryWarning(uchar)));
 }

 void Lelan::onLowMemoryWarning(uchar level)
 {
     if (m_zen)
         m_zen->onLowMemoryWarning(level);
 }

 // ---- App Nap (Sentinel executes, Lelan decides) -----------------------------------------------

 void Lelan::onWindowTierNeeded(uint pid, const QString &tier)
 {
     if (!m_useSentinel)
         return;
     QString t = tier;
     // a hidden window whose process is the one playing media keeps its sound: background, not hidden
     if (t == QLatin1String("hidden") && m_mediaPid != 0 && pid == m_mediaPid && mediaPlaying())
         t = QStringLiteral("background");
     callSentinel(QStringLiteral("SetProcessTier"), {pid, t});
 }

 void Lelan::onWindowClosed(uint pid)
 {
     if (pid != 0)
         callSentinel(QStringLiteral("ClearProcessTier"), {pid});
 }