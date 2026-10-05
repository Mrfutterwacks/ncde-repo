// Settings — dock, language / keyboard layouts, default apps, autostart, notifications, wallpaper + slideshow,
// sound preferences.
//
// Rebuilt from oracle: loadDock, setDockApps, saveDockPrefs, dockApps, installedApps (Settings_apps.cpp),
// loadLocale, saveLocale, kbLayouts, activeKbLayout, setActiveKbLayout, addKbLayout, removeKbLayout,
// applyKbLayout, loadDefaults, saveDefaults, loadAutostart, saveAutostart, syncAutostartDesktops,
// loadNotifications, saveNotifications, getWallpaper, setWallpaper, loadWallpaperPrefs, saveWallpaperPrefs,
// customWallpapers, slideshowEnabled/Interval, setSlideshowEnabled/Interval, fitMode, setFitMode,
// setSlideshowPaused, slideshowPaused, loadSound, saveSound.
// Spec: DockTab / LanguageTab / SessionTab / NotificationsTab / WallpapersTab / SoundTab; the Handbook
// ("Turn on the slideshow to rotate a folder on a timer you choose").
//
// DEFECTS FIXED vs oracle:
//  W1 the wallpaper slideshow never changed the picture: slideshowAdvanced was declared and never emitted,
//     nothing ran a timer. Now: `interval` minutes after the last change the next picture of the current
//     wallpaper's folder (then the custom pictures) becomes the wallpaper. One single-shot timer armed per
//     step (no repeating poll); paused while the screen is idle/off (main.qml: setSlideshowPaused) with the
//     time left kept, so a pause does not restart the wait and an overdue step happens on return.
//  W6 setWallpaper's custom-list rule: the oracle tested startsWith("/home/<user>/Pictures/wallpapers"), so a
//     picture in a sibling folder such as ~/Pictures/wallpapers-old was taken for a gallery one and never listed;
//     the rule is now "not inside the gallery folder" (the tab: "Custom (non-bundled) wallpapers"). Pictures the
//     slideshow steps through are not added (each one of a custom folder would have joined the strip).
//  W7 setSlideshowEnabled / setSlideshowInterval saved the prefs (oracle) but changed nothing running; they now
//     (re)arm or stop the slideshow. The interval is kept to the tab's range, 1-60 min.
//  W2 setFitMode stored and saved but emitted nothing: the desktop (main.qml binds fillMode to
//     settings.fitMode) kept the old fit until LaPivot restarted -> wallpaperPrefsChanged.
//  W3 setDockApps stored the list without dockChanged: other views of the dock's apps stayed stale.
//  W4 the default apps (browser / mail / files / terminal) were saved and used by nothing: links and folders
//     opened from other apps went elsewhere or nowhere (this machine had no inode/directory or mailto
//     default at all). Now registered with xdg-mime (browser: http, https, text/html, xhtml; mail: mailto;
//     files: inode/directory) and $TERMINAL for programs that ask for "the terminal".
//  W5 autostart entries were written into .desktop files verbatim: a newline in a name or command added
//     arbitrary keys to the file -> one line each.
//  W6 (2026-10-01) W4 started its xdg-mime calls in parallel; each rewrites ~/.config/mimeapps.list through
//     the same mimeapps.list.new, so they raced ("mv: cannot stat mimeapps.list.new") and the losers'
//     defaults were silently dropped. Now one sh runs them in order.
#include "Settings.h"
#include "Lelan.h"

#include <QCollator>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QSaveFile>
#include <QStandardPaths>
#include <QTimer>

// ---- dock ----
QVariantList Settings::dockApps() const { return m_dockApps; }

void Settings::setDockApps(const QVariantList &apps)
{
    if (apps == m_dockApps)
        return;
    m_dockApps = apps;
    emit dockChanged();                                                          // W3
}

void Settings::loadDock()
{
    const QVariantMap m = readArea(QStringLiteral("dock"));
    if (m.isEmpty())
        return;
    auto i = [&](const char *k, int &v) { if (m.contains(QLatin1String(k))) v = m.value(QLatin1String(k)).toInt(); };
    auto d = [&](const char *k, double &v) { if (m.contains(QLatin1String(k))) v = m.value(QLatin1String(k)).toDouble(); };
    i("iconSize", m_dockIconSize);
    i("spacing", m_dockSpacing);
    d("zoomPercent", m_dockZoomPercent);
    i("zoomRange", m_dockZoomRange);
    i("animSpeed", m_dockAnimSpeed);
    d("magSpring", m_dockMagSpring);
    d("magDamping", m_dockMagDamping);
    d("magMass", m_dockMagMass);
    if (m.contains(QStringLiteral("apps")))
        m_dockApps = m.value(QStringLiteral("apps")).toList();
    emit dockChanged();
}

void Settings::saveDockPrefs()
{
    writeArea(QStringLiteral("dock"), {
        {QStringLiteral("iconSize"), m_dockIconSize}, {QStringLiteral("spacing"), m_dockSpacing},
        {QStringLiteral("zoomPercent"), m_dockZoomPercent}, {QStringLiteral("zoomRange"), m_dockZoomRange},
        {QStringLiteral("animSpeed"), m_dockAnimSpeed}, {QStringLiteral("magSpring"), m_dockMagSpring},
        {QStringLiteral("magDamping"), m_dockMagDamping}, {QStringLiteral("magMass"), m_dockMagMass},
        {QStringLiteral("apps"), m_dockApps}});
}

// ---- language and keyboard layouts ----
QStringList Settings::kbLayouts() const { return m_kbLayouts; }
QString Settings::activeKbLayout() const { return m_activeKbLayout; }

void Settings::loadLocale()
{
    const QVariantMap m = readArea(QStringLiteral("locale"));
    if (m.isEmpty())
        return;
    if (m.contains(QStringLiteral("systemLanguage"))) m_systemLanguage = m.value(QStringLiteral("systemLanguage")).toString();
    if (m.contains(QStringLiteral("systemLocale"))) m_systemLocale = m.value(QStringLiteral("systemLocale")).toString();
    if (m.contains(QStringLiteral("kbLayouts"))) {
        m_kbLayouts.clear();
        for (const QVariant &v : m.value(QStringLiteral("kbLayouts")).toList())
            if (!v.toString().isEmpty() && !m_kbLayouts.contains(v.toString()))
                m_kbLayouts << v.toString();
        if (m_kbLayouts.isEmpty())
            m_kbLayouts << QStringLiteral("us");
    }
    if (m.contains(QStringLiteral("activeKbLayout"))) m_activeKbLayout = m.value(QStringLiteral("activeKbLayout")).toString();
    if (!m_kbLayouts.contains(m_activeKbLayout))
        m_activeKbLayout = m_kbLayouts.value(0);
    emit localeChanged();
    applyKbLayout();
}

void Settings::saveLocale()
{
    writeArea(QStringLiteral("locale"), {
        {QStringLiteral("systemLanguage"), m_systemLanguage}, {QStringLiteral("systemLocale"), m_systemLocale},
        {QStringLiteral("kbLayouts"), QVariant(m_kbLayouts).toList()}, {QStringLiteral("activeKbLayout"), m_activeKbLayout}});
    // system-wide language (polkit asks for the password; takes effect at the next login)
    runDetached(QStringLiteral("localectl"), {QStringLiteral("set-locale"), QStringLiteral("LANG=") + m_systemLocale});
}

void Settings::setActiveKbLayout(const QString &code)
{
    if (code == m_activeKbLayout || code.isEmpty())
        return;
    m_activeKbLayout = code;
    if (!m_kbLayouts.contains(code))
        m_kbLayouts << code;
    emit localeChanged();
    applyKbLayout();
}

void Settings::addKbLayout(const QString &code)
{
    if (code.isEmpty() || m_kbLayouts.contains(code))
        return;
    m_kbLayouts << code;
    emit localeChanged();
}

void Settings::removeKbLayout(const QString &code)
{
    if (!m_kbLayouts.removeAll(code))
        return;
    if (m_kbLayouts.isEmpty())
        m_kbLayouts << QStringLiteral("us");
    if (m_activeKbLayout == code) {
        m_activeKbLayout = m_kbLayouts.first();
        applyKbLayout();
    }
    emit localeChanged();
}

void Settings::applyKbLayout()
{
    if (!m_activeKbLayout.isEmpty())
        runDetached(QStringLiteral("setxkbmap"), {QStringLiteral("-layout"), m_activeKbLayout});
}

// ---- default apps ----
void Settings::loadDefaults()
{
    const QVariantMap m = readArea(QStringLiteral("session-defaults"));
    if (!m.isEmpty()) {
        if (m.contains(QStringLiteral("browser"))) m_defaultBrowser = m.value(QStringLiteral("browser")).toString();
        if (m.contains(QStringLiteral("mail"))) m_defaultMail = m.value(QStringLiteral("mail")).toString();
        if (m.contains(QStringLiteral("files"))) m_defaultFiles = m.value(QStringLiteral("files")).toString();
        if (m.contains(QStringLiteral("terminal"))) m_defaultTerminal = m.value(QStringLiteral("terminal")).toString();
        emit sessionChanged();
    }
    applyDefaults();
}

void Settings::saveDefaults()
{
    writeArea(QStringLiteral("session-defaults"), {
        {QStringLiteral("browser"), m_defaultBrowser}, {QStringLiteral("mail"), m_defaultMail},
        {QStringLiteral("files"), m_defaultFiles}, {QStringLiteral("terminal"), m_defaultTerminal}});
    applyDefaults();
}

// "<app>.desktop" if the system has it (user entries first, as xdg-mime resolves them)
QString Settings::desktopFileFor(const QString &app)
{
    if (app.isEmpty())
        return {};
    const QString name = app.endsWith(QLatin1String(".desktop")) ? app : app + QStringLiteral(".desktop");
    for (const QString &dir : QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation))
        if (QFile::exists(dir + QLatin1Char('/') + name))
            return name;
    return {};
}

void Settings::applyDefaults()                                                   // W4
{
    // W6: pairs of (desktop file, space-separated mime types) for one sequential sh; the desktop name
    // stays a positional argument (never shell code), the type lists are the constants below
    QStringList pairs;
    auto mime = [&](const QString &app, const char *types) {
        const QString desktop = desktopFileFor(app);
        if (!desktop.isEmpty())
            pairs << desktop << QLatin1String(types);
    };
    mime(m_defaultBrowser, "x-scheme-handler/http x-scheme-handler/https text/html application/xhtml+xml");
    mime(m_defaultMail, "x-scheme-handler/mailto");
    mime(m_defaultFiles, "inode/directory");
    if (!pairs.isEmpty())
        runDetached(QStringLiteral("sh"), QStringList{QStringLiteral("-c"),
                    QStringLiteral("while [ $# -ge 2 ]; do xdg-mime default \"$1\" $2; shift 2; done"),
                    QStringLiteral("ncde-default-apps")} + pairs);
    if (!m_defaultTerminal.isEmpty()) {
        qputenv("TERMINAL", m_defaultTerminal.toUtf8());
        runDetached(QStringLiteral("systemctl"), {QStringLiteral("--user"), QStringLiteral("set-environment"),
                                                  QStringLiteral("TERMINAL=") + m_defaultTerminal});
    }
}

// ---- autostart (SessionTab; entries {name, command, enabled}) ----
QString Settings::loadAutostart()
{
    const QVariantList entries = readArea(QStringLiteral("autostart")).value(QStringLiteral("entries")).toList();
    return QString::fromUtf8(QJsonDocument(QJsonArray::fromVariantList(entries)).toJson(QJsonDocument::Compact));
}

void Settings::saveAutostart(const QString &json)
{
    const QJsonArray arr = QJsonDocument::fromJson(json.toUtf8()).array();
    writeArea(QStringLiteral("autostart"), {{QStringLiteral("entries"), arr.toVariantList()}});
    syncAutostartDesktops(arr);
}

// one ~/.config/autostart/ncde-auto-<name>.desktop per entry; stale ncde-auto-* files removed
void Settings::syncAutostartDesktops(const QJsonArray &entries)
{
    const QString dir = QDir::homePath() + QStringLiteral("/.config/autostart");
    QDir().mkpath(dir);
    static const QRegularExpression unsafe(QStringLiteral("[^A-Za-z0-9]+"));
    static const QRegularExpression lineBreaks(QStringLiteral("[\\r\\n]+"));
    QStringList wanted;
    for (const QJsonValue &v : entries) {
        const QJsonObject o = v.toObject();
        const QString name = o.value(QStringLiteral("name")).toString().replace(lineBreaks, QStringLiteral(" ")).trimmed();   // W5
        const QString cmd = o.value(QStringLiteral("command")).toString().replace(lineBreaks, QStringLiteral(" ")).trimmed();
        if (name.isEmpty() || cmd.isEmpty())
            continue;
        const QString file = QStringLiteral("ncde-auto-") + QString(name).replace(unsafe, QStringLiteral("-")) + QStringLiteral(".desktop");
        wanted << file;
        QSaveFile f(dir + QLatin1Char('/') + file);
        if (!f.open(QIODevice::WriteOnly))
            continue;
        f.write(QStringLiteral("[Desktop Entry]\nType=Application\nName=%1\nExec=%2\nX-GNOME-Autostart-enabled=%3\n")
                    .arg(name, cmd, o.value(QStringLiteral("enabled")).toBool(true) ? QStringLiteral("true") : QStringLiteral("false"))
                    .toUtf8());
        f.commit();
    }
    for (const QString &old : QDir(dir).entryList({QStringLiteral("ncde-auto-*.desktop")}, QDir::Files))
        if (!wanted.contains(old))
            QFile::remove(dir + QLatin1Char('/') + old);
}

// ---- notifications ----
void Settings::loadNotifications()
{
    const QVariantMap m = readArea(QStringLiteral("notifications"));
    if (m.isEmpty())
        return;
    if (m.contains(QStringLiteral("dnd"))) m_dnd = m.value(QStringLiteral("dnd")).toBool();
    if (m.contains(QStringLiteral("notifPosition"))) m_notifPosition = qBound(0, m.value(QStringLiteral("notifPosition")).toInt(), 2);
    if (m.contains(QStringLiteral("quietHoursOn"))) m_quietHoursOn = m.value(QStringLiteral("quietHoursOn")).toBool();
    if (m.contains(QStringLiteral("quietFrom"))) m_quietFrom = m.value(QStringLiteral("quietFrom")).toString();
    if (m.contains(QStringLiteral("quietTo"))) m_quietTo = m.value(QStringLiteral("quietTo")).toString();
    emit notifsChanged();
}

void Settings::saveNotifications()
{
    writeArea(QStringLiteral("notifications"), {
        {QStringLiteral("dnd"), m_dnd}, {QStringLiteral("notifPosition"), m_notifPosition},
        {QStringLiteral("quietHoursOn"), m_quietHoursOn}, {QStringLiteral("quietFrom"), m_quietFrom},
        {QStringLiteral("quietTo"), m_quietTo}});
}

// ---- wallpaper ----
QString Settings::getWallpaper()
{
    QFile f(QDir::homePath() + QStringLiteral("/.config/ncde/wallpaper.conf"));
    if (!f.open(QIODevice::ReadOnly))
        return {};
    return QString::fromUtf8(f.readLine()).trimmed();
}

void Settings::setWallpaper(const QString &path)
{
    writeWallpaper(path, true);
}

// WallpapersTab's custom strip excludes both the gallery and wallpapers shipped with NCDE.
static bool pathWithin(const QString &path, const QString &directory)
{
    if (path.isEmpty() || directory.isEmpty())
        return false;
    const QString candidate = QDir::cleanPath(QFileInfo(path).absoluteFilePath());
    const QString root = QDir::cleanPath(QFileInfo(directory).absoluteFilePath());
    return candidate == root || candidate.startsWith(root + QLatin1Char('/'));
}

static bool isGalleryOrBundledWallpaper(const QString &path, const QString &assetBase)
{
    const QString canonical = QFileInfo(path).canonicalFilePath();
    const QStringList candidates{path, canonical};
    const QString gallery = QDir::homePath() + QStringLiteral("/Pictures/wallpapers");
    for (const QString &candidate : candidates) {
        if (candidate.isEmpty())
            continue;
        if (pathWithin(candidate, gallery) || pathWithin(candidate, assetBase))
            return true;
    }
    return false;
}

void Settings::writeWallpaper(const QString &path, bool userChoice)
{
    if (path.isEmpty())
        return;
    QDir().mkpath(QDir::homePath() + QStringLiteral("/.config/ncde"));
    QSaveFile f(QDir::homePath() + QStringLiteral("/.config/ncde/wallpaper.conf"));
    if (f.open(QIODevice::WriteOnly)) {
        f.write(path.toUtf8() + '\n');
        f.commit();
    }
    // W6: gallery entries are already shown by FolderListModel; don't classify shipped art as custom.
    if (userChoice && !isGalleryOrBundledWallpaper(path, m_assetBase) && !m_customWallpapers.contains(path)) {
        m_customWallpapers << path;
        emit wallpaperPrefsChanged();
        saveWallpaperPrefs();
    }
    emit wallpaperChanged(path);
    if (userChoice) {
        m_slideshowDue = 0;
        m_slideshowRemainingMs = m_slideshowPaused ? qint64(m_slideshowInterval) * slideshowMinuteMs : -1;
        updateSlideshowTimer();
    }
}

QStringList Settings::customWallpapers() const { return m_customWallpapers; }
bool Settings::slideshowEnabled() const { return m_slideshowEnabled; }
int Settings::slideshowInterval() const { return m_slideshowInterval; }
QString Settings::fitMode() const { return m_fitMode; }
bool Settings::slideshowPaused() const { return m_slideshowPaused; }

void Settings::setSlideshowEnabled(bool v)
{
    if (v == m_slideshowEnabled)
        return;
    m_slideshowEnabled = v;
    m_slideshowDue = 0;
    m_slideshowRemainingMs = -1;
    emit wallpaperPrefsChanged();
    saveWallpaperPrefs();                                                        // (oracle) + W7: arms / stops
}

void Settings::setSlideshowInterval(int v)
{
    v = qBound(1, v, 60);                                                        // the tab's slider
    if (v == m_slideshowInterval)
        return;
    m_slideshowInterval = v;
    m_slideshowDue = 0;
    m_slideshowRemainingMs = m_slideshowPaused ? qint64(v) * slideshowMinuteMs : -1;
    emit wallpaperPrefsChanged();
    saveWallpaperPrefs();
}

void Settings::setFitMode(const QString &v)
{
    static const QStringList modes{QStringLiteral("fill"), QStringLiteral("fit"),
                                   QStringLiteral("center"), QStringLiteral("tile")};
    const QString mode = modes.contains(v) ? v : QStringLiteral("fill");
    if (mode == m_fitMode)
        return;
    m_fitMode = mode;
    saveWallpaperPrefs();
    emit wallpaperPrefsChanged();                                                // W2
}

void Settings::setSlideshowPaused(bool p)
{
    if (p == m_slideshowPaused)
        return;
    m_slideshowPaused = p;
    emit settingsChanged();
    updateSlideshowTimer();
}

void Settings::loadWallpaperPrefs()
{
    const QVariantMap m = readArea(QStringLiteral("wallpaper-slideshow"));
    if (!m.isEmpty()) {
        const bool oldEnabled = m_slideshowEnabled;
        const int oldInterval = m_slideshowInterval;
        if (m.contains(QStringLiteral("enabled"))) m_slideshowEnabled = m.value(QStringLiteral("enabled")).toBool();
        if (m.contains(QStringLiteral("interval"))) m_slideshowInterval = qBound(1, m.value(QStringLiteral("interval")).toInt(), 60);
        if (m.contains(QStringLiteral("fitMode"))) {
            const QString mode = m.value(QStringLiteral("fitMode")).toString();
            if (mode == QLatin1String("fill") || mode == QLatin1String("fit")
                || mode == QLatin1String("center") || mode == QLatin1String("tile"))
                m_fitMode = mode;
        }
        if (m.contains(QStringLiteral("custom"))) {
            m_customWallpapers.clear();
            for (const QVariant &v : m.value(QStringLiteral("custom")).toList())
                if (!v.toString().isEmpty())
                    m_customWallpapers << v.toString();
        }
        if (oldEnabled != m_slideshowEnabled || oldInterval != m_slideshowInterval) {
            m_slideshowDue = 0;
            m_slideshowRemainingMs = m_slideshowPaused && m_slideshowEnabled
                                         ? qint64(m_slideshowInterval) * slideshowMinuteMs : -1;
        }
        emit wallpaperPrefsChanged();
    }
    updateSlideshowTimer();
}

void Settings::saveWallpaperPrefs()
{
    writeArea(QStringLiteral("wallpaper-slideshow"), {
        {QStringLiteral("enabled"), m_slideshowEnabled}, {QStringLiteral("interval"), m_slideshowInterval},
        {QStringLiteral("fitMode"), m_fitMode}, {QStringLiteral("custom"), QVariant(m_customWallpapers).toList()}});
    updateSlideshowTimer();
}

// W1: one single-shot timer to the next step. Pausing stores the remaining duration instead of letting an
// absolute deadline expire while the screen is idle.
void Settings::updateSlideshowTimer()
{
    if (!m_slideshowEnabled) {
        m_slideshowDue = 0;
        m_slideshowRemainingMs = -1;
        if (m_slideshowTimer)
            m_slideshowTimer->stop();
        return;
    }
    if (!m_slideshowTimer) {
        m_slideshowTimer = new QTimer(this);
        m_slideshowTimer->setSingleShot(true);
        m_slideshowTimer->setTimerType(Qt::VeryCoarseTimer);
        connect(m_slideshowTimer, &QTimer::timeout, this, &Settings::advanceSlideshow);
    }
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (m_slideshowPaused) {
        if (m_slideshowDue != 0) {
            m_slideshowRemainingMs = qMax<qint64>(0, m_slideshowDue - now);
            m_slideshowDue = 0;
        } else if (m_slideshowRemainingMs < 0) {
            m_slideshowRemainingMs = qint64(m_slideshowInterval) * slideshowMinuteMs;
        }
        m_slideshowTimer->stop();
        return;
    }
    if (m_slideshowDue == 0) {
        const qint64 delay = m_slideshowRemainingMs >= 0
                                 ? m_slideshowRemainingMs
                                 : qint64(m_slideshowInterval) * slideshowMinuteMs;
        m_slideshowDue = now + delay;
        m_slideshowRemainingMs = -1;
    }
    m_slideshowTimer->start(int(qBound<qint64>(1000, m_slideshowDue - now, qint64(60) * slideshowMinuteMs)));
}

// the pictures the slideshow rotates: the current wallpaper's folder, then the custom ones, no repeats
QStringList Settings::slideshowPictures(const QString &current) const
{
    QStringList out;
    const QFileInfo cur(current);
    if (!current.isEmpty() && cur.dir().exists()) {
        static const QStringList extensions{QStringLiteral("bmp"), QStringLiteral("gif"), QStringLiteral("jpeg"),
                                             QStringLiteral("jpg"), QStringLiteral("png"), QStringLiteral("tif"),
                                             QStringLiteral("tiff"), QStringLiteral("webp")};
        QStringList names;
        for (const QString &name : cur.dir().entryList(QDir::Files)) {
            const QString suffix = QFileInfo(name).suffix().toLower();
            if (extensions.contains(suffix))
                names << name;
        }
        QCollator c;
        c.setNumericMode(true);
        std::sort(names.begin(), names.end(), [&](const QString &a, const QString &b) { return c.compare(a, b) < 0; });
        for (const QString &n : std::as_const(names))
            out << cur.dir().absoluteFilePath(n);
    }
    for (const QString &p : m_customWallpapers)
        if (!out.contains(p) && QFile::exists(p))
            out << p;
    return out;
}

void Settings::advanceSlideshow()
{
    if (m_slideshowPaused || !m_slideshowEnabled)
        return;
    if (QDateTime::currentMSecsSinceEpoch() + 500 < m_slideshowDue) {             // early wake (coarse timer): wait on
        updateSlideshowTimer();
        return;
    }
    m_slideshowDue = 0;
    m_slideshowRemainingMs = -1;
    const QString current = getWallpaper();
    const QStringList pics = slideshowPictures(current);
    if (pics.size() >= 2) {
        const QString next = pics.value((pics.indexOf(current) + 1) % pics.size());
        writeWallpaper(next, false);
        emit slideshowAdvanced(next);                                            // main.qml: re-sample the colours
    }
    updateSlideshowTimer();                                                      // the next step
}

// ---- sound preferences (the live audio is Lelan's) ----
void Settings::loadSound()
{
    const QVariantMap m = readArea(QStringLiteral("sound"));
    if (m.isEmpty())
        return;
    if (m.contains(QStringLiteral("outputVolume"))) m_outputVolume = qBound(0, m.value(QStringLiteral("outputVolume")).toInt(), 150);
    if (m.contains(QStringLiteral("inputVolume"))) m_inputVolume = qBound(0, m.value(QStringLiteral("inputVolume")).toInt(), 150);
    if (m.contains(QStringLiteral("outputDevice"))) m_outputDevice = m.value(QStringLiteral("outputDevice")).toString();
    if (m.contains(QStringLiteral("inputDevice"))) m_inputDevice = m.value(QStringLiteral("inputDevice")).toString();
    emit soundChanged();
}

void Settings::saveSound()
{
    writeArea(QStringLiteral("sound"), {
        {QStringLiteral("outputVolume"), m_outputVolume}, {QStringLiteral("inputVolume"), m_inputVolume},
        {QStringLiteral("outputDevice"), m_outputDevice}, {QStringLiteral("inputDevice"), m_inputDevice}});
}
