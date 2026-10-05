// Settings — displays (xrandr: list, mode, rate, rotation, scale) and night light.
//
// Rebuilt from oracle: displays, refreshDisplays (+lambda: finish one output), applyDisplayMode /
// applyDisplayOrientation / applyDisplayScale (+900 ms re-read lambdas), saveDisplay, loadDisplay,
// applyNightLight, nightLightOn/nightWarmth/nightLightAuto + setters, setLelan lambda #1 (night auto).
// Spec: DisplayTab.qml; BEAUTIFY-NEXT.md #26 (Night Light 2700 K is on "so the desktop is more gaslit").
//
// Model (settings.displays), one map per connected output, as the oracle built it:
//   n (output name), pri (primary), sub ("WxH" current mode), hz (current rate), modes (["WxH",...]),
//   rates (rates of the current mode), orient (normal|left|inverted|right), scale (percent),
//   w / h (thumbnail size for the ARRANGEMENT row: pixels / 15, at least 40 x 24).
//   Added: modeRates ({"WxH": [rates]}) so the rate list follows a mode picked in the tab.
//
// DEFECTS FIXED vs oracle:
//  D1 refreshDisplays ran `xrandr --query` with waitForFinished on the GUI thread (up to 30 s frozen
//     shell on a slow/hung X query) -> asynchronous; displaysChanged only when the list changed.
//  D2 a resolution / rate / rotation / scale change had no way back: a mode the panel cannot show left a
//     black screen. Now the previous state is kept and reverted after 15 s unless confirmed
//     (displayChangePending(seconds) -> DisplayTab "Keep these settings?", confirmDisplayChange(),
//     revertDisplayChange()).
//  D3 rotation never worked: DisplayTab passes xrandr's names (left/inverted/right) but only UI labels
//     ("Portrait", "Inverted", "Port...") were recognised, so every choice became "normal".
//  D4 night light only lowered blue (linear 1.0 -> 0.5), leaving red and green at full: 2700 K looked
//     yellow-green, not gaslit. Now the gains follow the colour temperature (blackbody approximation,
//     normalised to 6500 K = 1:1:1).
//  D5 "Automatic" only acted at the next sunset/sunrise change: switched on at night, nothing happened
//     until morning. It now applies the current day/night state at once (and at start).
//  D6 a monitor plugged in later got no night light (gamma is per output) -> re-read + re-apply on
//     Lelan::screenConfigChanged.
#include "Settings.h"
#include "Lelan.h"

#include <QProcess>
#include <QRegularExpression>
#include <QTimer>
#include <QtLogging>

#include <cmath>

// ---- properties ----
QVariantList Settings::displays() const { return m_displays; }
bool Settings::nightLightOn() const { return m_nightLightOn; }
int Settings::nightWarmth() const { return m_nightWarmth; }
bool Settings::nightLightAuto() const { return m_nightLightAuto; }

void Settings::setNightLightOn(bool v)
{
    if (v == m_nightLightOn)
        return;
    m_nightLightOn = v;
    emit settingsChanged();
    applyNightLight();
}

void Settings::setNightWarmth(int v)
{
    if (v == m_nightWarmth)
        return;
    m_nightWarmth = v;
    emit settingsChanged();
    if (m_nightLightOn)
        applyNightLight();
}

void Settings::setNightLightAuto(bool v)
{
    if (v == m_nightLightAuto)
        return;
    m_nightLightAuto = v;
    emit settingsChanged();
    followDayNight();                                                            // D5
}

// night light follows Lelan's day/night flag (GeoClue sunset/sunrise) while "Automatic" is on
void Settings::followDayNight()
{
    if (!m_nightLightAuto || !m_lelan)
        return;
    const QVariantMap loc = m_lelan->location();
    if (loc.contains(QStringLiteral("night")))
        setNightLightOn(loc.value(QStringLiteral("night")).toBool());
}

// ---- xrandr ----
namespace {
QVariantMap finishOutput(QVariantMap out, const QStringList &modes, const QVariantMap &modeRates, const QString &current)
{
    out.insert(QStringLiteral("modes"), modes);
    out.insert(QStringLiteral("modeRates"), modeRates);
    out.insert(QStringLiteral("rates"), modeRates.value(current).toList());
    return out;
}
} // namespace

QVariantList Settings::parseXrandr(const QString &text, const QMap<QString, QVariant> &scales)
{
    static const QRegularExpression outRe(QStringLiteral("^(\\S+) connected( primary)? (\\d+)x(\\d+)\\+"));
    static const QRegularExpression modeRe(QStringLiteral("^\\s+(\\d+x\\d+)\\S*\\s+(.*\\S)\\s*$"));
    static const QRegularExpression rotRe(QStringLiteral("\\+\\d+\\+\\d+\\s+(normal|left|inverted|right)\\b"));
    static const QRegularExpression ws(QStringLiteral("\\s+"));
    QVariantList list;
    QVariantMap cur;
    QStringList modes;
    QVariantMap modeRates;
    QString currentMode;
    auto flush = [&] {
        if (!cur.isEmpty())
            list.append(finishOutput(cur, modes, modeRates, currentMode));
        cur.clear(); modes.clear(); modeRates.clear(); currentMode.clear();
    };
    for (const QString &line : text.split(QLatin1Char('\n'))) {
        const QRegularExpressionMatch o = outRe.match(line);
        if (o.hasMatch()) {
            flush();
            const QString name = o.captured(1);
            const int w = o.captured(3).toInt(), h = o.captured(4).toInt();
            const QRegularExpressionMatch r = rotRe.match(line);
            cur = {{QStringLiteral("n"), name}, {QStringLiteral("pri"), !o.captured(2).isEmpty()},
                   {QStringLiteral("sub"), QStringLiteral("%1x%2").arg(w).arg(h)},
                   {QStringLiteral("w"), qMax(40, w / 15)}, {QStringLiteral("h"), qMax(24, h / 15)},
                   {QStringLiteral("hz"), 0.0},
                   {QStringLiteral("orient"), r.hasMatch() ? r.captured(1) : QStringLiteral("normal")},
                   {QStringLiteral("scale"), scales.value(name, 100).toInt()}};
            continue;
        }
        if (line.size() && !line.at(0).isSpace())
            flush();                                                             // a disconnected output's block
        if (cur.isEmpty())
            continue;
        const QRegularExpressionMatch m = modeRe.match(line);
        if (!m.hasMatch())
            continue;
        const QString mode = m.captured(1);
        QVariantList rates;
        for (QString r : m.captured(2).split(ws, Qt::SkipEmptyParts)) {
            const bool now = r.contains(QLatin1Char('*'));
            r.remove(QLatin1Char('*')).remove(QLatin1Char('+'));
            bool ok = false;
            const double hz = r.toDouble(&ok);
            if (!ok)
                continue;
            rates.append(hz);
            if (now) {
                currentMode = mode;
                cur.insert(QStringLiteral("sub"), mode);
                cur.insert(QStringLiteral("hz"), hz);
            }
        }
        if (!modes.contains(mode)) {
            modes.append(mode);
            modeRates.insert(mode, rates);
        }
    }
    flush();
    return list;
}

void Settings::refreshDisplays()
{
    auto *p = new QProcess(this);
    connect(p, &QProcess::finished, this, [this, p](int code, QProcess::ExitStatus st) {   // D1
        p->deleteLater();
        if (st != QProcess::NormalExit || code != 0)
            return;
        const QVariantList list = parseXrandr(QString::fromUtf8(p->readAllStandardOutput()), m_scales);
        if (list != m_displays) {
            m_displays = list;
            emit displaysChanged();
            applyNightLight();                  // gamma is per output: new / re-moded outputs get it too (D6)
        }
    });
    p->start(QStringLiteral("xrandr"), {QStringLiteral("--query")});
}

// the change the tab asked for, with the previous state kept for a revert (D2)
void Settings::changeDisplay(const QString &name, const QStringList &args, const QStringList &revertArgs)
{
    runDetached(QStringLiteral("xrandr"), QStringList{QStringLiteral("--output"), name} + args);
    if (m_displayRevertTimer && m_displayRevertTimer->isActive() && !m_displayRevert.isEmpty()) {
        // a second change while the first is pending: keep the ORIGINAL state as the way back
    } else {
        m_displayRevert = QStringList{QStringLiteral("--output"), name} + revertArgs;
    }
    if (!m_displayRevertTimer) {
        m_displayRevertTimer = new QTimer(this);
        m_displayRevertTimer->setSingleShot(true);
        m_displayRevertTimer->setInterval(15000);
        connect(m_displayRevertTimer, &QTimer::timeout, this, &Settings::revertDisplayChange);
    }
    m_displayRevertTimer->start();
    emit displayChangePending(15);
    QTimer::singleShot(900, this, &Settings::refreshDisplays);                  // oracle's re-read
}

void Settings::confirmDisplayChange()
{
    if (m_displayRevertTimer)
        m_displayRevertTimer->stop();
    m_displayRevert.clear();
    emit displayChangePending(0);
    saveDisplay();
}

void Settings::revertDisplayChange()
{
    if (m_displayRevertTimer)
        m_displayRevertTimer->stop();
    if (!m_displayRevert.isEmpty()) {
        const QString name = m_displayRevert.value(1);
        const int i = m_displayRevert.indexOf(QStringLiteral("--scale"));
        if (i >= 0)
            m_scales.insert(name, m_displayRevertScale);
        runDetached(QStringLiteral("xrandr"), m_displayRevert);
    }
    m_displayRevert.clear();
    emit displayChangePending(0);
    QTimer::singleShot(900, this, &Settings::refreshDisplays);
}

QVariantMap Settings::displayByName(const QString &name) const
{
    for (const QVariant &v : m_displays)
        if (v.toMap().value(QStringLiteral("n")).toString() == name)
            return v.toMap();
    return {};
}

void Settings::applyDisplayMode(const QString &name, const QString &mode, double hz)
{
    const QVariantMap d = displayByName(name);
    QStringList args{QStringLiteral("--mode"), mode};
    if (hz > 0)
        args << QStringLiteral("--rate") << QString::number(hz);
    QStringList back{QStringLiteral("--mode"), d.value(QStringLiteral("sub")).toString()};
    if (d.value(QStringLiteral("hz")).toDouble() > 0)
        back << QStringLiteral("--rate") << QString::number(d.value(QStringLiteral("hz")).toDouble());
    changeDisplay(name, args, back);
}

static QString xrandrRotation(const QString &o)
{
    // D3: xrandr names as DisplayTab sends them, and the UI labels the oracle expected
    if (o == QLatin1String("left") || o.startsWith(QLatin1String("Portrait")))
        return QStringLiteral("left");
    if (o == QLatin1String("inverted") || o.startsWith(QLatin1String("Inverted")))
        return QStringLiteral("inverted");
    if (o == QLatin1String("right") || o.startsWith(QLatin1String("Port")))
        return QStringLiteral("right");
    return QStringLiteral("normal");
}

void Settings::applyDisplayOrientation(const QString &name, const QString &orient)
{
    const QVariantMap d = displayByName(name);
    changeDisplay(name, {QStringLiteral("--rotate"), xrandrRotation(orient)},
                  {QStringLiteral("--rotate"), d.value(QStringLiteral("orient"), QStringLiteral("normal")).toString()});
}

static QString xrandrScale(int pct)
{
    const double f = pct < 1 ? 1.0 : 100.0 / pct;                              // 125 % -> 0.8 (larger UI)
    return QStringLiteral("%1x%1").arg(f, 0, 'f', 4);
}

void Settings::applyDisplayScale(const QString &name, int pct)
{
    // the way back is the scale the output has now (as listed), and stays the FIRST one while changes pile up
    const int now = displayByName(name).value(QStringLiteral("scale"), m_scales.value(name, 100)).toInt();
    if (!(m_displayRevertTimer && m_displayRevertTimer->isActive()))
        m_displayRevertScale = now;
    const QString back = xrandrScale(now);
    m_scales.insert(name, pct);
    changeDisplay(name, {QStringLiteral("--scale"), xrandrScale(pct)}, {QStringLiteral("--scale"), back});
}

// ---- persistence ----
void Settings::saveDisplay()
{
    QVariantList outs;
    for (const QVariant &v : m_displays) {
        const QVariantMap d = v.toMap();
        outs.append(QVariantMap{{QStringLiteral("n"), d.value(QStringLiteral("n"))},
                                {QStringLiteral("mode"), d.value(QStringLiteral("sub"))},
                                {QStringLiteral("hz"), d.value(QStringLiteral("hz"))},
                                {QStringLiteral("orient"), d.value(QStringLiteral("orient"))},
                                {QStringLiteral("scale"), m_scales.value(d.value(QStringLiteral("n")).toString(), 100)}});
    }
    writeArea(QStringLiteral("display"), {
        {QStringLiteral("outputs"), outs}, {QStringLiteral("nightLightOn"), m_nightLightOn},
        {QStringLiteral("nightWarmth"), m_nightWarmth}, {QStringLiteral("nightLightAuto"), m_nightLightAuto}});
}

void Settings::loadDisplay()
{
    const QVariantMap m = readArea(QStringLiteral("display"));
    for (const QVariant &v : m.value(QStringLiteral("outputs")).toList()) {
        const QVariantMap o = v.toMap();
        const QString n = o.value(QStringLiteral("n")).toString();
        if (n.isEmpty())
            continue;
        QStringList args{QStringLiteral("--output"), n};
        const QString mode = o.value(QStringLiteral("mode")).toString();
        if (!mode.isEmpty() && mode.contains(QLatin1Char('x'))) {
            args << QStringLiteral("--mode") << mode;
            if (o.value(QStringLiteral("hz")).toDouble() > 0)
                args << QStringLiteral("--rate") << QString::number(o.value(QStringLiteral("hz")).toDouble());
        }
        const QString orient = o.value(QStringLiteral("orient")).toString();
        if (!orient.isEmpty())
            args << QStringLiteral("--rotate") << xrandrRotation(orient);
        const int scale = o.value(QStringLiteral("scale"), 100).toInt();
        m_scales.insert(n, scale);
        if (scale != 100)
            args << QStringLiteral("--scale") << xrandrScale(scale);
        if (args.size() > 2)
            runDetached(QStringLiteral("xrandr"), args);
    }
    if (m.contains(QStringLiteral("nightLightOn"))) m_nightLightOn = m.value(QStringLiteral("nightLightOn")).toBool();
    if (m.contains(QStringLiteral("nightWarmth"))) m_nightWarmth = m.value(QStringLiteral("nightWarmth")).toInt();
    if (m.contains(QStringLiteral("nightLightAuto"))) m_nightLightAuto = m.value(QStringLiteral("nightLightAuto")).toBool();
    refreshDisplays();
}

// ---- night light ----
// RGB gains for a colour temperature, normalised so 6500 K = 1:1:1 (Tanner Helland's blackbody fit)
QVector<double> Settings::nightGains(int kelvin)
{
    auto rgb = [](double k) {
        const double t = k / 100.0;
        double r = t <= 66 ? 255 : 329.698727446 * std::pow(t - 60, -0.1332047592);
        double g = t <= 66 ? 99.4708025861 * std::log(t) - 161.1195681661 : 288.1221695283 * std::pow(t - 60, -0.0755148492);
        double b = t >= 66 ? 255 : t <= 19 ? 0 : 138.5177312231 * std::log(t - 10) - 305.0447927307;
        return QVector<double>{qBound(0.0, r, 255.0), qBound(0.0, g, 255.0), qBound(0.0, b, 255.0)};
    };
    const QVector<double> c = rgb(qBound(1000, kelvin, 6500)), w = rgb(6500);
    return {qBound(0.1, c[0] / w[0], 1.0), qBound(0.1, c[1] / w[1], 1.0), qBound(0.1, c[2] / w[2], 1.0)};
}

void Settings::applyNightLight()
{
    QString gamma = QStringLiteral("1.0:1.0:1.0");
    if (m_nightLightOn) {
        const QVector<double> g = nightGains(m_nightWarmth);                     // D4
        gamma = QStringLiteral("%1:%2:%3").arg(g[0], 0, 'f', 3).arg(g[1], 0, 'f', 3).arg(g[2], 0, 'f', 3);
    }
    for (const QVariant &v : std::as_const(m_displays))
        runDetached(QStringLiteral("xrandr"), {QStringLiteral("--output"), v.toMap().value(QStringLiteral("n")).toString(),
                                               QStringLiteral("--gamma"), gamma});
}
