// Settings — the config-file watcher (hot reload), the installed-apps list, identity.
//
// Rebuilt from oracle: initWatcher (+lambda), saveConfig, userName, configBase, assetBase, installedApps.
// Spec: digest §2 ("Config store/façade … hot-reload via QFileSystemWatcher").
//
// DEFECTS FIXED vs oracle:
//  K1 the watcher only emitted settingsChanged when ~/.config/ncde changed — nothing was re-read, so an edit
//     from outside (another NCDE app, a restored backup, the operator's editor) did nothing until the next
//     login ("hot reload" in name only); and every save of Settings' own files fired it several times.
//     Now: directory and area-file changes are coalesced (300 ms); each area whose CONTENT differs from what
//     Settings last read or wrote is re-read with its own loader. Atomic and in-place own writes are ignored.
//  K2 saveConfig() (QML-invokable) did nothing; it now saves every area.
//  K3 installedApps(): a later [Desktop Action] group's Name=/Exec= overwrote the app's own; the same app in
//     ~/.local/share/applications and /usr/share/applications was listed twice (the user's copy must win);
//     the list was unsorted. Now: only the [Desktop Entry] group, user entries override by file name,
//     NoDisplay/Hidden skipped, sorted by name.
#include "Settings.h"
#include "Lelan.h"

#include <QCollator>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>
#include <QTimer>

QString Settings::userName() const { return QDir::home().dirName(); }
QString Settings::configBase() const { return m_configBase; }

// ---- tracked config IO: what Settings last read or wrote, per area (K1) ----
QVariantMap Settings::readArea(const QString &name)
{
    QFile f(Lelan::configPath(name));
    m_seen.insert(name, f.open(QIODevice::ReadOnly) ? f.readAll() : QByteArray());
    return Lelan::readConfig(name);
}

bool Settings::writeArea(const QString &name, const QVariantMap &data)
{
    const bool ok = Lelan::writeConfig(name, data);
    QFile f(Lelan::configPath(name));
    m_seen.insert(name, f.open(QIODevice::ReadOnly) ? f.readAll() : QByteArray());
    watchConfigFiles();
    return ok;
}

void Settings::initWatcher()
{
    if (m_watcherStarted)
        return;
    m_watcherStarted = true;
    QDir().mkpath(m_configBase);
    m_watcher.addPath(m_configBase);
    m_reloadTimer = new QTimer(this);
    m_reloadTimer->setSingleShot(true);
    m_reloadTimer->setInterval(300);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, m_reloadTimer, qOverload<>(&QTimer::start));
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, m_reloadTimer, qOverload<>(&QTimer::start));
    connect(m_reloadTimer, &QTimer::timeout, this, &Settings::reloadChangedAreas);
    watchConfigFiles();
}

void Settings::watchConfigFiles()
{
    if (!m_watcherStarted)
        return;
    const QStringList areas{
        QStringLiteral("display"), QStringLiteral("power"), QStringLiteral("fonts"), QStringLiteral("storage"),
        QStringLiteral("input"), QStringLiteral("accessibility"), QStringLiteral("privacy"),
        QStringLiteral("screensaver"), QStringLiteral("datetime"), QStringLiteral("network"),
        QStringLiteral("dock"), QStringLiteral("locale"), QStringLiteral("session-defaults"),
        QStringLiteral("notifications"), QStringLiteral("wallpaper-slideshow"), QStringLiteral("sound"),
        QStringLiteral("security"), QStringLiteral("section-colors")};
    const QStringList watched = m_watcher.files();
    for (const QString &area : areas) {
        const QString path = Lelan::configPath(area);
        if (QFile::exists(path) && !watched.contains(path))
            m_watcher.addPath(path);
    }
}

// area file -> its loader (every file Settings reads)
void Settings::reloadChangedAreas()
{
    const QList<QPair<QString, void (Settings::*)()>> areas = {
        {QStringLiteral("display"), &Settings::loadDisplay}, {QStringLiteral("power"), &Settings::loadPower},
        {QStringLiteral("fonts"), &Settings::loadFonts}, {QStringLiteral("storage"), &Settings::loadStorage},
        {QStringLiteral("input"), &Settings::loadInput}, {QStringLiteral("accessibility"), &Settings::loadAccessibility},
        {QStringLiteral("privacy"), &Settings::loadPrivacy}, {QStringLiteral("screensaver"), &Settings::loadScreensaver},
        {QStringLiteral("datetime"), &Settings::loadDateTime}, {QStringLiteral("network"), &Settings::loadNetwork},
        {QStringLiteral("dock"), &Settings::loadDock}, {QStringLiteral("locale"), &Settings::loadLocale},
        {QStringLiteral("session-defaults"), &Settings::loadDefaults}, {QStringLiteral("notifications"), &Settings::loadNotifications},
        {QStringLiteral("wallpaper-slideshow"), &Settings::loadWallpaperPrefs}, {QStringLiteral("sound"), &Settings::loadSound},
        {QStringLiteral("security"), &Settings::loadKickass}, {QStringLiteral("section-colors"), &Settings::loadSectionColors}};
    bool any = false;
    for (const auto &a : areas) {
        QFile f(Lelan::configPath(a.first));
        const QByteArray now = f.open(QIODevice::ReadOnly) ? f.readAll() : QByteArray();
        if (!m_seen.contains(a.first) || now == m_seen.value(a.first))
            continue;                                                            // unchanged, or ours
        (this->*a.second)();                                                     // re-read (updates m_seen)
        any = true;
    }
    watchConfigFiles();
    if (any)
        emit settingsChanged();
}

void Settings::saveConfig()                                                      // K2
{
    saveDisplay(); savePower(); saveFontsJson(); saveStorage(); saveInput(); saveAccessibility();
    saveConfPrivacy(); saveScreensaver(); saveDateTime(); saveNetwork(); saveDockPrefs(); saveLocale();
    saveDefaults(); saveNotifications(); saveWallpaperPrefs(); saveSound(); saveSecurity(); saveSectionColors();
}

// ---- installed applications (dock / launcher pickers): [{name, exec, icon}] ----
QVariantList Settings::installedApps()
{
    static const QRegularExpression fieldCodes(QStringLiteral("%[fFuUdDnNickvm]"));
    const QStringList dirs{QStringLiteral("/usr/share/applications"), QStringLiteral("/usr/local/share/applications"),
                           QDir::homePath() + QStringLiteral("/.local/share/applications")};
    QMap<QString, QVariantMap> byFile;                                           // later dirs override (K3)
    for (const QString &dir : dirs) {
        for (const QString &file : QDir(dir).entryList({QStringLiteral("*.desktop")}, QDir::Files)) {
            QFile f(QDir(dir).filePath(file));
            if (!f.open(QIODevice::ReadOnly))
                continue;
            QTextStream in(&f);
            bool entry = false, hidden = false;
            QString name, exec, icon;
            while (!in.atEnd()) {
                const QString line = in.readLine().trimmed();
                if (line.startsWith(QLatin1Char('['))) {
                    if (entry)
                        break;                                                   // K3: only [Desktop Entry]
                    entry = line == QLatin1String("[Desktop Entry]");
                    continue;
                }
                if (!entry)
                    continue;
                if (line.startsWith(QLatin1String("Name=")) && name.isEmpty()) name = line.mid(5).trimmed();
                else if (line.startsWith(QLatin1String("Exec="))) exec = line.mid(5).trimmed();
                else if (line.startsWith(QLatin1String("Icon="))) icon = line.mid(5).trimmed();
                else if (line.startsWith(QLatin1String("NoDisplay=")) || line.startsWith(QLatin1String("Hidden=")))
                    hidden = hidden || line.section(QLatin1Char('='), 1).trimmed().compare(QLatin1String("true"), Qt::CaseInsensitive) == 0;
            }
            if (hidden) {
                byFile.remove(file);                                             // a user copy can hide a system app
                continue;
            }
            if (name.isEmpty() || exec.isEmpty())
                continue;
            byFile.insert(file, QVariantMap{{QStringLiteral("name"), name},
                                            {QStringLiteral("exec"), QString(exec).remove(fieldCodes).trimmed()},
                                            {QStringLiteral("icon"), icon}});
        }
    }
    QVariantList out;
    for (const QVariantMap &m : std::as_const(byFile))
        out.append(m);
    QCollator c;
    c.setCaseSensitivity(Qt::CaseInsensitive);
    std::sort(out.begin(), out.end(), [&](const QVariant &a, const QVariant &b) {
        return c.compare(a.toMap().value(QStringLiteral("name")).toString(), b.toMap().value(QStringLiteral("name")).toString()) < 0;
    });
    return out;
}
