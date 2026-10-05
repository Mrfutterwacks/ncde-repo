// Settings — keyboard repeat, pointer / touchpad speed, natural scroll, tap-to-click, disable-while-typing,
// cursor size (InputTab), and the auto-mount switch (StorageTab).
//
// Rebuilt from oracle: loadInput, saveInput, applyInput (+ini lambda), applyLibinput, applyLibinputFiltered,
// loadStorage, saveStorage, autoMountUsb/setAutoMountUsb.
//
// What applying does (as the oracle): `xset r rate <delay> <rate>`; libinput properties through xinput
// (Accel Speed = (speed - 50) / 50 for pointers vs touchpads, Natural Scrolling, Tapping, Disable While
// Typing); cursor size = Kith theme at that size via xrdb Xcursor.*, GTK 3/4 settings.ini and gsettings.
//
// DEFECTS FIXED vs oracle:
//  N1 every apply ran xinput list + list-props per device + xrdb with waitForFinished on the GUI thread
//     (the shell froze while a slider moved) -> asynchronous.
//  N2 "libinput Accel Speed" was set on every non-touchpad device in `xinput list` — keyboards, power
//     buttons, the virtual core devices — each an xinput error; and only devices that have a property get it.
//  N3 a mouse or touchpad plugged in after login kept libinput's defaults: Lelan's input-device events only
//     emitted statsChanged. Now Lelan::inputDevicesChanged -> apply again.
//  N4 the auto-mount switch was stored but LaPivot never acted on it (a separate daemon did, badly — see
//     Lelan_storage.cpp S7): the value now goes to Lelan::setAutoMountPref on load and on every change.
#include "Settings.h"
#include "Lelan.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QRegularExpression>

// ---- auto-mount (StorageTab) ----
bool Settings::autoMountUsb() const { return m_autoMountUsb; }
void Settings::setAutoMountUsb(bool v)
{
    if (v == m_autoMountUsb)
        return;
    m_autoMountUsb = v;
    if (m_lelan)
        m_lelan->setAutoMountPref(v);                                            // N4
    emit storageChanged();
}

void Settings::loadStorage()
{
    const QVariantMap m = readArea(QStringLiteral("storage"));
    if (m.contains(QStringLiteral("autoMountUsb")))
        m_autoMountUsb = m.value(QStringLiteral("autoMountUsb")).toBool();
    if (m_lelan)
        m_lelan->setAutoMountPref(m_autoMountUsb);
    emit storageChanged();
}

void Settings::saveStorage()
{
    writeArea(QStringLiteral("storage"), {{QStringLiteral("autoMountUsb"), m_autoMountUsb}});
}

// ---- input ----
void Settings::loadInput()
{
    const QVariantMap m = readArea(QStringLiteral("input"));
    if (m.isEmpty())
        return;
    auto num = [&](const char *k, int &v, int lo, int hi) {
        if (m.contains(QLatin1String(k))) v = qBound(lo, m.value(QLatin1String(k)).toInt(), hi); };
    auto flag = [&](const char *k, bool &v) { if (m.contains(QLatin1String(k))) v = m.value(QLatin1String(k)).toBool(); };
    num("kbRepeatDelay", m_kbRepeatDelay, 100, 2000);
    num("kbRepeatRate", m_kbRepeatRate, 1, 100);
    num("pointerSpeed", m_pointerSpeed, 0, 100);
    num("touchpadSpeed", m_touchpadSpeed, 0, 100);
    flag("naturalScroll", m_naturalScroll);
    flag("tapToClick", m_tapToClick);
    flag("disableWhileTyping", m_disableWhileTyping);
    num("cursorSize", m_cursorSize, 16, 128);
    emit inputChanged();
    applyInput();
}

void Settings::saveInput()
{
    writeArea(QStringLiteral("input"), {
        {QStringLiteral("kbRepeatDelay"), m_kbRepeatDelay}, {QStringLiteral("kbRepeatRate"), m_kbRepeatRate},
        {QStringLiteral("pointerSpeed"), m_pointerSpeed}, {QStringLiteral("touchpadSpeed"), m_touchpadSpeed},
        {QStringLiteral("naturalScroll"), m_naturalScroll}, {QStringLiteral("tapToClick"), m_tapToClick},
        {QStringLiteral("disableWhileTyping"), m_disableWhileTyping}, {QStringLiteral("cursorSize"), m_cursorSize}});
    applyInput();
}

// `xinput list` -> the pointer devices (id, name); keyboards and virtual core devices are not pointers (N2)
QList<QPair<QString, QString>> Settings::parsePointers(const QString &xinputList)
{
    static const QRegularExpression line(QStringLiteral("^\\W*(.+?)\\s+id=(\\d+)\\s+\\[slave\\s+pointer"));
    QList<QPair<QString, QString>> out;
    for (const QString &l : xinputList.split(QLatin1Char('\n'))) {
        const QRegularExpressionMatch m = line.match(l);
        if (m.hasMatch() && !m.captured(1).contains(QLatin1String("XTEST")))
            out.append({m.captured(2), m.captured(1).trimmed()});
    }
    return out;
}

void Settings::applyInput()
{
    runDetached(QStringLiteral("xset"), {QStringLiteral("r"), QStringLiteral("rate"),
                                         QString::number(m_kbRepeatDelay), QString::number(m_kbRepeatRate)});
    const QString pointerAccel = QString::number(qBound(-1.0, (m_pointerSpeed - 50) / 50.0, 1.0));
    const QString touchAccel = QString::number(qBound(-1.0, (m_touchpadSpeed - 50) / 50.0, 1.0));
    const QString natural = m_naturalScroll ? QStringLiteral("1") : QStringLiteral("0");
    const QString tap = m_tapToClick ? QStringLiteral("1") : QStringLiteral("0");
    const QString dwt = m_disableWhileTyping ? QStringLiteral("1") : QStringLiteral("0");
    runQuery(QStringLiteral("xinput"), {QStringLiteral("list")}, [=](const QString &list) {           // N1
        for (const auto &dev : parsePointers(list)) {
            const QString id = dev.first;
            const bool touchpad = dev.second.contains(QLatin1String("touchpad"), Qt::CaseInsensitive);
            runQuery(QStringLiteral("xinput"), {QStringLiteral("list-props"), id}, [=](const QString &props) {
                auto set = [&](const char *prop, const QString &value) {
                    if (props.contains(QLatin1String(prop)))                                           // N2
                        runDetached(QStringLiteral("xinput"), {QStringLiteral("set-prop"), id, QLatin1String(prop), value});
                };
                set("libinput Accel Speed", touchpad ? touchAccel : pointerAccel);
                set("libinput Natural Scrolling Enabled", natural);
                set("libinput Tapping Enabled", tap);
                set("libinput Disable While Typing Enabled", dwt);
            });
        }
    });
    applyCursorSize();
}

// Kith at the chosen size: X (xrdb), GTK 3 and 4 (settings.ini), GNOME-reading apps (gsettings)
void Settings::applyCursorSize()
{
    runInput(QStringLiteral("xrdb"), {QStringLiteral("-merge")},
             QStringLiteral("Xcursor.theme: Kith\nXcursor.size: %1\n").arg(m_cursorSize).toUtf8());
    for (const char *rel : {"/gtk-3.0/settings.ini", "/gtk-4.0/settings.ini"})
        setIniKeys(QDir::homePath() + QStringLiteral("/.config") + QLatin1String(rel),
                   {{QStringLiteral("gtk-cursor-theme-name"), QStringLiteral("Kith")},
                    {QStringLiteral("gtk-cursor-theme-size"), QString::number(m_cursorSize)}});
    runDetached(QStringLiteral("gsettings"), {QStringLiteral("set"), QStringLiteral("org.gnome.desktop.interface"),
                                              QStringLiteral("cursor-theme"), QStringLiteral("Kith")});
    runDetached(QStringLiteral("gsettings"), {QStringLiteral("set"), QStringLiteral("org.gnome.desktop.interface"),
                                              QStringLiteral("cursor-size"), QString::number(m_cursorSize)});
}

// set key=value lines in the [Settings] group of a GTK settings.ini, keeping everything else
void Settings::setIniKeys(const QString &path, const QList<QPair<QString, QString>> &kv)
{
    QDir().mkpath(QFileInfo(path).absolutePath());
    QString text;
    {
        QFile f(path);
        if (f.open(QIODevice::ReadOnly))
            text = QString::fromUtf8(f.readAll());
    }
    if (text.trimmed().isEmpty())
        text = QStringLiteral("[Settings]\n");
    else if (!text.contains(QLatin1String("[Settings]")))
        text = QStringLiteral("[Settings]\n") + text;
    for (const auto &p : kv) {
        const QRegularExpression re(QStringLiteral("(?m)^\\s*%1\\s*=.*$").arg(QRegularExpression::escape(p.first)));
        const QString line = p.first + QLatin1Char('=') + p.second;
        if (text.contains(re)) {
            text.replace(re, line);
        } else {
            const int at = text.indexOf(QLatin1String("[Settings]")) + int(qstrlen("[Settings]"));
            text.insert(at, QLatin1Char('\n') + line);
        }
    }
    QFile f(path);
    if (f.open(QIODevice::WriteOnly | QIODevice::Truncate))
        f.write(text.toUtf8());
}

// applyLibinput / applyLibinputFiltered: the oracle's per-property device loops, kept for callers; both go
// through the same asynchronous, pointer-only path.
void Settings::applyLibinput(const QString &prop, const QString &value)
{
    runQuery(QStringLiteral("xinput"), {QStringLiteral("list")}, [=](const QString &list) {
        for (const auto &dev : parsePointers(list)) {
            const QString id = dev.first;
            runQuery(QStringLiteral("xinput"), {QStringLiteral("list-props"), id}, [=](const QString &props) {
                if (props.contains(prop))
                    runDetached(QStringLiteral("xinput"), {QStringLiteral("set-prop"), id, prop, value});
            });
        }
    });
}

void Settings::applyLibinputFiltered(const QString &prop, const QString &value, bool touchpad)
{
    runQuery(QStringLiteral("xinput"), {QStringLiteral("list")}, [=](const QString &list) {
        for (const auto &dev : parsePointers(list)) {
            if (dev.second.contains(QLatin1String("touchpad"), Qt::CaseInsensitive) != touchpad)
                continue;
            const QString id = dev.first;
            runQuery(QStringLiteral("xinput"), {QStringLiteral("list-props"), id}, [=](const QString &props) {
                if (props.contains(prop))
                    runDetached(QStringLiteral("xinput"), {QStringLiteral("set-prop"), id, prop, value});
            });
        }
    });
}
