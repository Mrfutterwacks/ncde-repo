// Settings — accessibility, privacy, security (Vesper switch), date/time preferences, network proxy.
//
// Rebuilt from oracle: loadAccessibility, saveAccessibility, applyAccessibility, loadPrivacy, savePrivacy,
// saveConfPrivacy, loadKickass, setKickassArmed, kickassArmed, applyKickassArmed, loadDateTime, saveDateTime,
// loadNetwork, saveNetwork. Spec: AccessibilityTab, PrivacyTab, SecurityTab, DateTimeTab, NetworkTab (proxy).
//
// DEFECTS FIXED vs oracle:
//  A1 PrivacyTab saves with savePrivacy(), which was EMPTY: privacy switches were never written and came back
//     at the next login -> savePrivacy writes privacy.json (as saveConfPrivacy did).
//  A2 "Location" off changed nothing: GeoClue kept locating -> Lelan::setLocationAllowed (Lelan_time.cpp T8).
//  A3 "Larger cursor" set cursorSize but only saved accessibility.json: the cursor stayed the same size until
//     some other input change applied it -> saveAccessibility also saves + applies the input settings.
//  A4 the proxy (host, port, on/off) was stored and never applied: no app used it -> applied to GNOME-reading
//     apps (gsettings org.gnome.system.proxy: GTK, Chromium under GTK), to programs started from now on
//     (systemd --user environment + LaPivot's own environment: http(s)_proxy / no_proxy).
#include "Settings.h"
#include "Lelan.h"

#include <QDir>
#include <QFile>

// ---- accessibility ----
void Settings::loadAccessibility()
{
    const QVariantMap m = readArea(QStringLiteral("accessibility"));
    if (m.isEmpty())
        return;
    if (m.contains(QStringLiteral("accessibilityTextScale")))
        m_accessibilityTextScale = qBound(0.75, m.value(QStringLiteral("accessibilityTextScale")).toDouble(), 2.5);
    if (m.contains(QStringLiteral("highContrast"))) m_highContrast = m.value(QStringLiteral("highContrast")).toBool();
    if (m.contains(QStringLiteral("reduceMotion"))) m_reduceMotion = m.value(QStringLiteral("reduceMotion")).toBool();
    if (m.contains(QStringLiteral("largerCursor"))) m_largerCursor = m.value(QStringLiteral("largerCursor")).toBool();
    emit accessibilityChanged();
    applyAccessibility();
}

void Settings::saveAccessibility()
{
    writeArea(QStringLiteral("accessibility"), {
        {QStringLiteral("accessibilityTextScale"), m_accessibilityTextScale},
        {QStringLiteral("highContrast"), m_highContrast}, {QStringLiteral("reduceMotion"), m_reduceMotion},
        {QStringLiteral("largerCursor"), m_largerCursor}});
    applyAccessibility();
    saveInput();                                                                 // A3: cursor size applied now
}

void Settings::applyAccessibility()
{
    if (m_lelan)
        m_lelan->setReduceMotionPref(m_reduceMotion);
    emit accessibilityChanged();
    emit fontChanged();
}

// ---- privacy ----
void Settings::loadPrivacy()
{
    const QVariantMap m = readArea(QStringLiteral("privacy"));
    if (m.contains(QStringLiteral("locationEnabled"))) m_locationEnabled = m.value(QStringLiteral("locationEnabled")).toBool();
    if (m.contains(QStringLiteral("lockScreenNotifPreview")))
        m_lockScreenNotifPreview = m.value(QStringLiteral("lockScreenNotifPreview")).toBool();
    if (m_lelan)
        m_lelan->setLocationAllowed(m_locationEnabled);                          // A2
    emit privacyChanged();
}

void Settings::saveConfPrivacy()
{
    writeArea(QStringLiteral("privacy"), {
        {QStringLiteral("locationEnabled"), m_locationEnabled},
        {QStringLiteral("lockScreenNotifPreview"), m_lockScreenNotifPreview}});
    if (m_lelan)
        m_lelan->setLocationAllowed(m_locationEnabled);
}

void Settings::savePrivacy() { saveConfPrivacy(); }                              // A1

// ---- security: Vesper (the screen-lock half is in Settings_power.cpp) ----
bool Settings::kickassArmed() const { return m_kickassArmed; }

void Settings::loadKickass()
{
    const QVariantMap m = readArea(QStringLiteral("security"));
    if (!m.isEmpty()) {
        if (m.contains(QStringLiteral("requirePassword"))) m_requirePassword = m.value(QStringLiteral("requirePassword")).toBool();
        if (m.contains(QStringLiteral("requirePasswordDelay"))) m_requirePasswordDelay = m.value(QStringLiteral("requirePasswordDelay")).toInt();
        if (m.contains(QStringLiteral("kickassArmed"))) m_kickassArmed = m.value(QStringLiteral("kickassArmed")).toBool();
    }
    applyIdleConfig();
    applyKickassArmed();
    emit securityChanged();
}

void Settings::setKickassArmed(bool armed)
{
    m_kickassArmed = armed;
    saveSecurity();
    applyKickassArmed();
    emit securityChanged();
}

// Vesper is one switch: its brain service (systemd --user) runs or not
void Settings::applyKickassArmed()
{
    const QStringList units{QStringLiteral("/usr/lib/systemd/user/vesper-brain.service"),
                            QStringLiteral("/etc/systemd/user/vesper-brain.service"),
                            QDir::homePath() + QStringLiteral("/.config/systemd/user/vesper-brain.service")};
    bool installed = false;
    for (const QString &u : units)
        installed = installed || QFile::exists(u);
    if (!installed)
        return;
    runDetached(QStringLiteral("systemctl"), {QStringLiteral("--user"),
                                              m_kickassArmed ? QStringLiteral("enable") : QStringLiteral("disable"),
                                              QStringLiteral("--now"), QStringLiteral("vesper-brain.service")});
}

// ---- date/time preferences (the zone and NTP themselves go through Lelan / timedate1) ----
void Settings::loadDateTime()
{
    const QVariantMap m = readArea(QStringLiteral("datetime"));
    if (m.isEmpty())
        return;
    if (m.contains(QStringLiteral("hourFormat"))) m_hourFormat = m.value(QStringLiteral("hourFormat")).toString();
    if (m.contains(QStringLiteral("showSeconds"))) m_showSeconds = m.value(QStringLiteral("showSeconds")).toBool();
    if (m.contains(QStringLiteral("ntpEnabled"))) m_ntpEnabled = m.value(QStringLiteral("ntpEnabled")).toBool();
    if (m.contains(QStringLiteral("timezoneManual"))) m_timezoneManual = m.value(QStringLiteral("timezoneManual")).toString();
    emit settingsChanged();
}

void Settings::saveDateTime()
{
    writeArea(QStringLiteral("datetime"), {
        {QStringLiteral("hourFormat"), m_hourFormat}, {QStringLiteral("showSeconds"), m_showSeconds},
        {QStringLiteral("ntpEnabled"), m_ntpEnabled}, {QStringLiteral("timezoneManual"), m_timezoneManual}});
}

// ---- network proxy ----
void Settings::loadNetwork()
{
    const QVariantMap m = readArea(QStringLiteral("network"));
    if (!m.isEmpty()) {
        if (m.contains(QStringLiteral("proxyEnabled"))) m_proxyEnabled = m.value(QStringLiteral("proxyEnabled")).toBool();
        if (m.contains(QStringLiteral("proxyHost"))) m_proxyHost = m.value(QStringLiteral("proxyHost")).toString().trimmed();
        if (m.contains(QStringLiteral("proxyPort"))) m_proxyPort = qBound(1, m.value(QStringLiteral("proxyPort")).toInt(), 65535);
        emit settingsChanged();
    }
    applyProxy();
}

void Settings::saveNetwork()
{
    writeArea(QStringLiteral("network"), {
        {QStringLiteral("proxyEnabled"), m_proxyEnabled}, {QStringLiteral("proxyHost"), m_proxyHost},
        {QStringLiteral("proxyPort"), m_proxyPort}});
    applyProxy();
}

// A4: one HTTP(S) proxy for everything, or none
void Settings::applyProxy()
{
    const bool on = m_proxyEnabled && !m_proxyHost.trimmed().isEmpty();
    const QString host = m_proxyHost.trimmed();
    const QString port = QString::number(qBound(1, m_proxyPort, 65535));
    const QString gs = QStringLiteral("gsettings");
    const QString set = QStringLiteral("set");
    runDetached(gs, {set, QStringLiteral("org.gnome.system.proxy"), QStringLiteral("mode"),
                     on ? QStringLiteral("manual") : QStringLiteral("none")});
    if (on) {
        for (const char *scheme : {"org.gnome.system.proxy.http", "org.gnome.system.proxy.https"}) {
            runDetached(gs, {set, QLatin1String(scheme), QStringLiteral("host"), host});
            runDetached(gs, {set, QLatin1String(scheme), QStringLiteral("port"), port});
        }
    }
    const QString url = QStringLiteral("http://%1:%2/").arg(host, port);
    const QStringList vars{QStringLiteral("http_proxy"), QStringLiteral("https_proxy"),
                           QStringLiteral("HTTP_PROXY"), QStringLiteral("HTTPS_PROXY")};
    if (on) {
        QStringList env;
        for (const QString &v : vars) {
            env << v + QLatin1Char('=') + url;
            qputenv(v.toLatin1(), url.toUtf8());
        }
        env << QStringLiteral("no_proxy=localhost,127.0.0.1,::1");
        qputenv("no_proxy", "localhost,127.0.0.1,::1");
        runDetached(QStringLiteral("systemctl"), QStringList{QStringLiteral("--user"), QStringLiteral("set-environment")} + env);
    } else {
        for (const QString &v : vars)
            qunsetenv(v.toLatin1());
        qunsetenv("no_proxy");
        runDetached(QStringLiteral("systemctl"), QStringList{QStringLiteral("--user"), QStringLiteral("unset-environment")}
                                                     + vars + QStringList{QStringLiteral("no_proxy")});
    }
}
