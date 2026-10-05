// Settings — power (blank, suspend, lid, power button), idle (screensaver, idle lock, idle suspend) and the
// screen-lock half of security (require password + delay).
//
// Rebuilt from oracle: batBlank/batSuspend/acBlank/acSuspend/lidAction/powerButtonAction/showBatteryPct and
// setters, loadPower, savePower, applyPowerSettings, onScreenIdleChanged, setLelan, setAnimPolicy,
// loadScreensaver, saveScreensaver, previewScreensaver (both) + its finished lambda, screensaverRunning,
// saveSecurity, and main()'s screensaver lambdas (#1 timeout, #2 idle-reached, (int,bool)#1 relaunch).
// Spec: PowerTab.qml, ScreensaverTab.qml, SecurityTab.qml (what each control promises).
//
// DEFECTS FIXED vs oracle (the idle ones are described in IdlePolicy.h):
//  I1 suspend ~30 s after the last input on battery (any AnimPolicy change + screenIdle) -> IdlePolicy
//     counts the real idle minutes. onScreenIdleChanged no longer suspends.
//  I2 X's own screensaver timer was set to the suspend minutes, so xss-lock locked at suspend + 10 min
//     -> X's screensaver timer is kept off (xset s off); LaPivot's IdlePolicy is the one idle owner.
//  I3 "Require password" and its delay did nothing -> the idle lock follows them, and the lock before
//     sleep is skipped when it is off (usr/bin/ncde-lock-xss reads security.json for sleep locks).
//  I4 the screensaver came straight back after a key press (relaunch on exit != 0 while the WM's idle flag
//     was still set) -> relaunched only after a crash while nobody is back, 3 times per idle period.
//  P1 applyPowerSettings ran 3 x `xset` on every Lelan::batteryChanged (~every 3 s while charging) ->
//     only when the blank time actually changes (AC <-> battery or the setting).
//  P2 the screensaver's stdout/stderr were pipes nobody read (QProcess ReadWrite): a chatty saver fills the
//     pipe and blocks -> forwarded to LaPivot's own output (journal).
//  P3 "When the lid closes" (suspend / lock / nothing) did nothing: logind is told to ignore the lid
//     (logind.conf.d HandleLidSwitch=ignore) and nobody else listened -> Lelan::lidClosedChanged -> act.
//  P4 the screensaver timeout defaulted to 300 minutes when screensaver.json is missing (the tab shows 5,
//     its slider is 1-60) -> default 5, loaded value clamped to 0-60 (0 = off).
#include "Settings.h"
#include "Lelan.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QtLogging>

// ---- power properties ----
int Settings::batBlank() const { return m_batBlank; }
int Settings::batSuspend() const { return m_batSuspend; }
int Settings::acBlank() const { return m_acBlank; }
int Settings::acSuspend() const { return m_acSuspend; }
QString Settings::lidAction() const { return m_lidAction; }
QString Settings::powerButtonAction() const { return m_powerButtonAction; }
bool Settings::showBatteryPct() const { return m_showBatteryPct; }

#define SETTINGS_SETTER(Name, member, Type, signal)                                                  \
    void Settings::set##Name(Type v)                                                                \
    {                                                                                               \
        if (v == member)                                                                            \
            return;                                                                                 \
        member = v;                                                                                 \
        emit signal();                                                                              \
    }
SETTINGS_SETTER(BatBlank, m_batBlank, int, powerChanged)
SETTINGS_SETTER(BatSuspend, m_batSuspend, int, powerChanged)
SETTINGS_SETTER(AcBlank, m_acBlank, int, powerChanged)
SETTINGS_SETTER(AcSuspend, m_acSuspend, int, powerChanged)
SETTINGS_SETTER(LidAction, m_lidAction, const QString &, powerChanged)
SETTINGS_SETTER(PowerButtonAction, m_powerButtonAction, const QString &, powerChanged)
SETTINGS_SETTER(ShowBatteryPct, m_showBatteryPct, bool, powerChanged)

// ---- screensaver / security properties ----
int Settings::screensaverTimeout() const { return m_screensaverTimeout; }
QString Settings::screensaverSeason() const { return m_screensaverSeason; }
bool Settings::screensaverClockVisible() const { return m_screensaverClockVisible; }
int Settings::screensaverFps() const { return m_screensaverFps; }
bool Settings::requirePassword() const { return m_requirePassword; }
int Settings::requirePasswordDelay() const { return m_requirePasswordDelay; }
SETTINGS_SETTER(ScreensaverTimeout, m_screensaverTimeout, int, settingsChanged)
SETTINGS_SETTER(ScreensaverSeason, m_screensaverSeason, const QString &, settingsChanged)
SETTINGS_SETTER(ScreensaverClockVisible, m_screensaverClockVisible, bool, settingsChanged)
SETTINGS_SETTER(ScreensaverFps, m_screensaverFps, int, settingsChanged)
SETTINGS_SETTER(RequirePassword, m_requirePassword, bool, securityChanged)
SETTINGS_SETTER(RequirePasswordDelay, m_requirePasswordDelay, int, securityChanged)

// ---- wiring ----
void Settings::setLelan(Lelan *lelan)
{
    m_lelan = lelan;
    if (!m_lelan)
        return;
    connect(m_lelan, &Lelan::placeNameChanged, this, &Settings::followDayNight);          // night auto
    connect(m_lelan, &Lelan::screenConfigChanged, this, &Settings::refreshDisplays);      // D6
    connect(m_lelan, &Lelan::batteryChanged, this, &Settings::applyPowerSettings);          // P1: change-checked
    connect(m_lelan, &Lelan::lidClosedChanged, this, [this](bool closed) {                  // P3
        if (!closed)
            return;
        if (m_lidAction == QLatin1String("suspend"))
            runDetached(QStringLiteral("systemctl"), {QStringLiteral("suspend")});
        else if (m_lidAction == QLatin1String("lock"))
            runDetached(QStringLiteral("loginctl"), {QStringLiteral("lock-session")});
    });
    connect(m_lelan, &Lelan::leanWaking, this, [this] { m_idle.userPresent(); });
    connect(m_lelan, &Lelan::inputDevicesChanged, this, &Settings::applyInput);  // N3: re-apply on input hotplug
    applyPowerSettings();
    followDayNight();                                                            // D5: the state now
}

void Settings::setAnimPolicy(QObject *policy)
{
    m_animPolicy = policy;                   // I1: no longer connected to onScreenIdleChanged
}

// I1: the oracle suspended from here on any AnimPolicy change while the screen was idle. Kept for the
// interface (QML/metadata); idle actions come from onIdleSample.
void Settings::onScreenIdleChanged() {}

// ---- power ----
void Settings::loadPower()
{
    const QVariantMap m = readArea(QStringLiteral("power"));
    if (m.isEmpty())
        return;
    m_batBlank = m.value(QStringLiteral("batBlank"), m_batBlank).toInt();
    m_batSuspend = m.value(QStringLiteral("batSuspend"), m_batSuspend).toInt();
    m_acBlank = m.value(QStringLiteral("acBlank"), m_acBlank).toInt();
    m_acSuspend = m.value(QStringLiteral("acSuspend"), m_acSuspend).toInt();
    m_lidAction = m.value(QStringLiteral("lidAction"), m_lidAction).toString();
    m_powerButtonAction = m.value(QStringLiteral("powerButtonAction"), m_powerButtonAction).toString();
    m_showBatteryPct = m.value(QStringLiteral("showBatteryPct"), m_showBatteryPct).toBool();
    emit powerChanged();
    applyPowerSettings();
}

void Settings::savePower()
{
    writeArea(QStringLiteral("power"), {
        {QStringLiteral("batBlank"), m_batBlank}, {QStringLiteral("batSuspend"), m_batSuspend},
        {QStringLiteral("acBlank"), m_acBlank}, {QStringLiteral("acSuspend"), m_acSuspend},
        {QStringLiteral("lidAction"), m_lidAction}, {QStringLiteral("powerButtonAction"), m_powerButtonAction},
        {QStringLiteral("showBatteryPct"), m_showBatteryPct}});
    applyPowerSettings();
}

void Settings::applyPowerSettings()
{
    applyIdleConfig();
    const bool battery = m_lelan && m_lelan->onBattery();
    const int blankSec = (battery ? m_batBlank : m_acBlank) * 60;
    if (blankSec == m_appliedBlank)
        return;                                                                  // P1
    m_appliedBlank = blankSec;
    const QString s = QString::number(blankSec);
    runDetached(QStringLiteral("xset"), {QStringLiteral("dpms"), s, s, s});    // 0 = never blank
    runDetached(QStringLiteral("xset"), {QStringLiteral("s"), QStringLiteral("off")});      // I2
}

// ---- idle ----
void Settings::applyIdleConfig()
{
    const bool battery = m_lelan && m_lelan->onBattery();
    IdlePolicy::Config c;
    c.saverMinutes = m_screensaverTimeout;
    c.suspendMinutes = battery ? m_batSuspend : m_acSuspend;
    c.requirePassword = m_requirePassword;
    c.passwordDelaySec = m_requirePasswordDelay;
    m_idle.setConfig(c);
}

void Settings::onIdleSample(qint64 idleMs)
{
    const unsigned a = m_idle.sample(idleMs, screensaverRunning());
    if (a & IdlePolicy::StopSaver)
        stopSaver();
    if (a & IdlePolicy::StartSaver)
        startSaver();
    if (a & IdlePolicy::Lock)
        runDetached(QStringLiteral("loginctl"), {QStringLiteral("lock-session")});   // xss-lock runs the locker
    if (a & IdlePolicy::Suspend)
        runDetached(QStringLiteral("systemctl"), {QStringLiteral("suspend")});       // xss-lock: sleep lock (I3)
}

// ---- screensaver ----
void Settings::loadScreensaver()
{
    const QVariantMap m = readArea(QStringLiteral("screensaver"));
    m_screensaverTimeout = qBound(0, m.value(QStringLiteral("timeout"), m_screensaverTimeout).toInt(), 60);   // P4: the tab's range
    m_screensaverSeason = m.value(QStringLiteral("season"), m_screensaverSeason).toString();
    m_screensaverClockVisible = m.value(QStringLiteral("clockVisible"), m_screensaverClockVisible).toBool();
    m_screensaverFps = m.value(QStringLiteral("fps"), m_screensaverFps).toInt();
    applyIdleConfig();
    emit settingsChanged();
}

void Settings::saveScreensaver()
{
    writeArea(QStringLiteral("screensaver"), {
        {QStringLiteral("timeout"), m_screensaverTimeout}, {QStringLiteral("season"), m_screensaverSeason},
        {QStringLiteral("clockVisible"), m_screensaverClockVisible}, {QStringLiteral("fps"), m_screensaverFps}});
    applyIdleConfig();
}

bool Settings::screensaverRunning()
{
    return m_saver && m_saver->state() != QProcess::NotRunning;
}

void Settings::previewScreensaver() { previewScreensaver(m_screensaverSeason); }

void Settings::previewScreensaver(const QString &season)
{
    if (screensaverRunning())
        return;
    if (!m_saver) {
        m_saver = new QProcess(this);
        m_saver->setProcessChannelMode(QProcess::ForwardedChannels);             // P2
        connect(m_saver, &QProcess::finished, this, [this](int code, QProcess::ExitStatus status) {
            onSaverFinished(code, status == QProcess::CrashExit);
        });
    }
    m_saverStopping = false;
    m_saver->setProgram(saverProgram);
    m_saver->setArguments({QStringLiteral("--screensaver"), QStringLiteral("--season"),
                           season.isEmpty() ? QStringLiteral("auto") : season});
    m_saver->start(QIODevice::NotOpen);
}

void Settings::startSaver() { previewScreensaver(QStringLiteral("auto")); }

void Settings::stopSaver()
{
    if (!screensaverRunning())
        return;
    m_saverStopping = true;
    m_saver->terminate();
}

void Settings::onSaverFinished(int exitCode, bool crashed)
{
    emit screensaverFinished(exitCode, crashed);
    if (m_saverStopping) {
        m_saverStopping = false;
        return;
    }
    if (idleMsSource && m_idle.saverEnded(crashed || exitCode != 0, idleMsSource()))
        startSaver();                                                            // I4
    else if (crashed || exitCode != 0)
        qWarning() << "screensaver: exited" << exitCode << (crashed ? "(crash)" : "") << "- not relaunched";
}

// ---- security: the screen-lock half (loadKickass reads security.json; Settings_security.cpp) ----
void Settings::saveSecurity()
{
    writeArea(QStringLiteral("security"), {
        {QStringLiteral("requirePassword"), m_requirePassword},
        {QStringLiteral("requirePasswordDelay"), m_requirePasswordDelay},
        {QStringLiteral("kickassArmed"), m_kickassArmed}});
    applyIdleConfig();
}
