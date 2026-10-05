// AppMenuModel.cpp — oracle-facing app menu plus shared XDG application index.
// Rebuilt from oracle: decomp/AppMenuModel.c; DesktopIndex is the documented rebuild addition.
// Spec: NCDE-ARCHITECTURE-DIGEST.md §2, ncde-efficiency.md #7, gliatalk.md.
// DEFECTS FIXED vs oracle:
// 1. Desktop scans run on one worker thread and are coalesced; the GUI thread only installs results.
// 2. One shared index serves AppMenuModel and GliaSystemMenus; unchanged files are stat-cache hits.
// 3. XDG precedence, hidden user overrides, desktop-file IDs, visibility flags, and Exec tokenization
//    are handled once by DesktopEntry instead of duplicated ad-hoc QSettings loops.
// 4. The oracle's public AppMenuModel result shape and category/search rules are retained.
// 5. getApps() entries now also carry appId (the desktop-file id); without it Expose launched the
//    raw Exec line instead of gtk-launch like the dock (2026-10-01).

#include "AppMenuModel.h"

#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QFile>
#include <QFileSystemWatcher>
#include <QLocale>
#include <QProcess>
#include <QPointer>
#include <QRegularExpression>
#include <QSet>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>
#include <QThreadPool>
#include <QTimer>
#include <QVariantMap>

#include <algorithm>
#include <utility>

namespace {

QStringList splitSemicolonList(const QString &value)
{
    QStringList result = value.split(QLatin1Char(';'), Qt::SkipEmptyParts);
    for (QString &entry : result)
        entry = entry.trimmed();
    result.removeAll(QString());
    return result;
}

QStringList parseExec(const QString &exec, const QString &name, const QString &icon,
                      const QString &desktopFile, bool *ok)
{
    QStringList rawArguments;
    QString argument;
    bool quoted = false;
    bool escaped = false;
    bool started = false;

    for (const QChar ch : exec) {
        if (escaped) {
            argument.append(ch);
            escaped = false;
            started = true;
        } else if (ch == QLatin1Char('\\') && quoted) {
            escaped = true;
            started = true;
        } else if (ch == QLatin1Char('"')) {
            quoted = !quoted;
            started = true;
        } else if (ch.isSpace() && !quoted) {
            if (started) {
                rawArguments.append(argument);
                argument.clear();
                started = false;
            }
        } else {
            argument.append(ch);
            started = true;
        }
    }
    if (escaped || quoted) {
        if (ok)
            *ok = false;
        return {};
    }
    if (started)
        rawArguments.append(argument);

    QStringList result;
    for (const QString &raw : rawArguments) {
        if (raw == QStringLiteral("%i")) {
            if (!icon.isEmpty())
                result << QStringLiteral("--icon") << icon;
            continue;
        }

        QString expanded;
        for (qsizetype i = 0; i < raw.size(); ++i) {
            const QChar ch = raw.at(i);
            if (ch != QLatin1Char('%')) {
                expanded.append(ch);
                continue;
            }
            if (++i >= raw.size()) {
                if (ok)
                    *ok = false;
                return {};
            }
            switch (raw.at(i).unicode()) {
            case '%': expanded.append(QLatin1Char('%')); break;
            case 'c': expanded.append(name); break;
            case 'k': expanded.append(desktopFile); break;
            case 'f': case 'F': case 'u': case 'U':
            case 'd': case 'D': case 'n': case 'N':
            case 'v': case 'm':
                break;
            case 'i':
                if (ok)
                    *ok = false;
                return {};
            default:
                if (ok)
                    *ok = false;
                return {};
            }
        }
        if (!expanded.isEmpty())
            result.append(expanded);
    }

    if (ok)
        *ok = !result.isEmpty();
    return result;
}

bool executableAvailable(const QString &candidate)
{
    if (candidate.isEmpty())
        return true;
    if (candidate.contains(QLatin1Char('/'))) {
        const QFileInfo info(candidate);
        return info.isFile() && info.isExecutable();
    }
    return !QStandardPaths::findExecutable(candidate).isEmpty();
}

bool currentDesktopMatches(const QStringList &requested)
{
    if (requested.isEmpty())
        return true;
    const QStringList current = qEnvironmentVariable("XDG_CURRENT_DESKTOP")
                                    .split(QLatin1Char(':'), Qt::SkipEmptyParts);
    for (const QString &desktop : requested) {
        if (current.contains(desktop, Qt::CaseInsensitive))
            return true;
    }
    return false;
}

QString rawExecValue(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};

    QTextStream stream(&file);
    bool inDesktopEntry = false;
    while (!stream.atEnd()) {
        const QString line = stream.readLine().trimmed();
        if (line.startsWith(QLatin1Char('[')) && line.endsWith(QLatin1Char(']'))) {
            inDesktopEntry = line == QStringLiteral("[Desktop Entry]");
            continue;
        }
        if (inDesktopEntry && line.startsWith(QStringLiteral("Exec=")))
            return line.mid(5).trimmed();
    }
    return {};
}

} // namespace

namespace DesktopEntry {

QStringList applicationDirs()
{
    QString dataHome = qEnvironmentVariable("XDG_DATA_HOME");
    if (dataHome.isEmpty())
        dataHome = QDir::home().filePath(QStringLiteral(".local/share"));

    QString dataDirs = qEnvironmentVariable("XDG_DATA_DIRS");
    if (dataDirs.isEmpty())
        dataDirs = QStringLiteral("/usr/local/share:/usr/share");

    QStringList result;
    const QStringList roots = QStringList{dataHome}
        + dataDirs.split(QLatin1Char(':'), Qt::SkipEmptyParts);
    for (QString root : roots) {
        if (root.isEmpty())
            continue;
        root = QDir::cleanPath(QDir(root).filePath(QStringLiteral("applications")));
        if (!result.contains(root))
            result.append(root);
    }
    return result;
}

QStringList splitExec(const QString &exec, bool *ok)
{
    return parseExec(exec, {}, {}, {}, ok);
}

QString joinForSplitCommand(const QStringList &argv)
{
    QStringList quoted;
    quoted.reserve(argv.size());
    for (const QString &argument : argv) {
        if (argument.isEmpty()) {
            quoted.append(QStringLiteral("\"\""));
        } else if (argument.contains(QRegularExpression(QStringLiteral("[\\s\"\\\\]")))) {
            QString escaped = argument;
            escaped.replace(QLatin1Char('\\'), QStringLiteral("\\\\"));
            escaped.replace(QLatin1Char('"'), QStringLiteral("\\\""));
            quoted.append(QLatin1Char('"') + escaped + QLatin1Char('"'));
        } else {
            quoted.append(argument);
        }
    }
    return quoted.join(QLatin1Char(' '));
}

QString mapCategory(const QString &categories)
{
    const QStringList values = splitSemicolonList(categories);
    auto has = [&values](const QString &needle) {
        return std::any_of(values.cbegin(), values.cend(), [&needle](const QString &value) {
            return value.compare(needle, Qt::CaseInsensitive) == 0;
        });
    };

    if (has(QStringLiteral("AudioVideo")) || has(QStringLiteral("Audio"))
        || has(QStringLiteral("Video")))
        return QStringLiteral("Sound & Video");
    if (has(QStringLiteral("Development"))) return QStringLiteral("Development");
    if (has(QStringLiteral("Graphics"))) return QStringLiteral("Graphics");
    if (has(QStringLiteral("Network"))) return QStringLiteral("Internet");
    if (has(QStringLiteral("Office"))) return QStringLiteral("Office");
    if (has(QStringLiteral("Game"))) return QStringLiteral("Games");
    if (has(QStringLiteral("Accessibility"))) return QStringLiteral("Accessibility");
    if (has(QStringLiteral("Settings"))) return QStringLiteral("Settings");
    if (has(QStringLiteral("System"))) return QStringLiteral("System");
    if (has(QStringLiteral("Science"))) return QStringLiteral("Science & Math");
    if (has(QStringLiteral("Education"))) return QStringLiteral("Education");
    if (has(QStringLiteral("Utility"))) return QStringLiteral("Utilities");
    return QStringLiteral("Other");
}

QStringList terminalCommand()
{
    QString terminal = qEnvironmentVariable("TERMINAL").trimmed();
    if (!terminal.isEmpty()) {
        QStringList command = QProcess::splitCommand(terminal);
        if (!command.isEmpty() && executableAvailable(command.constFirst())) {
            command.append(QStringLiteral("-e"));
            return command;
        }
    }

    for (const QString &candidate : {QStringLiteral("x-terminal-emulator"),
                                     QStringLiteral("konsole"),
                                     QStringLiteral("kitty"),
                                     QStringLiteral("xterm")}) {
        const QString executable = QStandardPaths::findExecutable(candidate);
        if (!executable.isEmpty())
            return {executable, QStringLiteral("-e")};
    }
    return {};
}

bool parse(const QString &path, const QString &id, DesktopApp &out,
           const QStringList &terminal)
{
    QSettings settings(path, QSettings::IniFormat);
    settings.setFallbacksEnabled(false);
    settings.beginGroup(QStringLiteral("Desktop Entry"));

    const QString type = settings.value(QStringLiteral("Type"),
                                        QStringLiteral("Application")).toString();
    if (type != QStringLiteral("Application")
        || settings.value(QStringLiteral("Hidden")).toBool()
        || settings.value(QStringLiteral("NoDisplay")).toBool())
        return false;

    if (!currentDesktopMatches(splitSemicolonList(
            settings.value(QStringLiteral("OnlyShowIn")).toString())))
        return false;
    const QStringList excluded = splitSemicolonList(
        settings.value(QStringLiteral("NotShowIn")).toString());
    const QStringList current = qEnvironmentVariable("XDG_CURRENT_DESKTOP")
                                    .split(QLatin1Char(':'), Qt::SkipEmptyParts);
    for (const QString &desktop : excluded) {
        if (current.contains(desktop, Qt::CaseInsensitive))
            return false;
    }

    const QString name = settings.value(QStringLiteral("Name")).toString().trimmed();
    const QString icon = settings.value(QStringLiteral("Icon")).toString().trimmed();
    const QString rawExec = rawExecValue(path);
    if (name.isEmpty() || rawExec.isEmpty()
        || !executableAvailable(settings.value(QStringLiteral("TryExec")).toString().trimmed()))
        return false;

    bool execOk = false;
    QStringList argv = parseExec(rawExec, name, icon, path, &execOk);
    if (!execOk)
        return false;

    const bool terminalApp = settings.value(QStringLiteral("Terminal")).toBool();
    if (terminalApp && !terminal.isEmpty())
        argv = terminal + argv;

    out.id = id;
    out.file = QFileInfo(path).absoluteFilePath();
    out.name = name;
    out.icon = icon;
    out.argv = argv;
    out.exec = joinForSplitCommand(argv);
    out.workDir = settings.value(QStringLiteral("Path")).toString().trimmed();
    out.category = mapCategory(settings.value(QStringLiteral("Categories")).toString());
    out.terminal = terminalApp;
    return !out.argv.isEmpty();
}

} // namespace DesktopEntry

DesktopIndex *DesktopIndex::instance()
{
    static QPointer<DesktopIndex> index;
    if (!index) {
        QObject *parent = QCoreApplication::instance();
        index = new DesktopIndex(parent);
    }
    return index;
}

DesktopIndex::DesktopIndex(QObject *parent, const QStringList &dirs)
    : QObject(parent)
    , m_dirs(dirs.isEmpty() ? DesktopEntry::applicationDirs() : dirs)
    , m_watcher(new QFileSystemWatcher(this))
    , m_debounce(new QTimer(this))
{
    m_pool.setMaxThreadCount(1);
    m_pool.setExpiryTimeout(-1);
    m_debounce->setSingleShot(true);
    m_debounce->setInterval(150);
    connect(m_watcher, &QFileSystemWatcher::directoryChanged,
            m_debounce, qOverload<>(&QTimer::start));
    connect(m_watcher, &QFileSystemWatcher::fileChanged,
            m_debounce, qOverload<>(&QTimer::start));
    connect(m_debounce, &QTimer::timeout, this, &DesktopIndex::requestScan);
    QTimer::singleShot(0, this, &DesktopIndex::requestScan);
}

DesktopIndex::~DesktopIndex()
{
    m_pool.waitForDone();
}

DesktopIndex::ScanResult DesktopIndex::scan(const QStringList &dirs,
                                             QHash<QString, CacheEntry> cache)
{
    ScanResult result;
    QSet<QString> seenIds;
    const QStringList terminal = DesktopEntry::terminalCommand();

    for (const QString &root : dirs) {
        const QDir rootDir(root);
        if (!rootDir.exists())
            continue;
        const QString absoluteRoot = rootDir.absolutePath();
        result.watchDirs.append(absoluteRoot);

        QDirIterator directories(absoluteRoot, QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                                 QDirIterator::Subdirectories);
        while (directories.hasNext()) {
            directories.next();
            result.watchDirs.append(directories.fileInfo().absoluteFilePath());
        }

        QDirIterator files(absoluteRoot, QStringList{QStringLiteral("*.desktop")},
                           QDir::Files | QDir::NoSymLinks,
                           QDirIterator::Subdirectories);
        while (files.hasNext()) {
            const QString path = QFileInfo(files.next()).absoluteFilePath();
            QString id = QDir(absoluteRoot).relativeFilePath(path);
            id.replace(QLatin1Char('/'), QLatin1Char('-'));
            result.watchDirs.append(path);

            if (seenIds.contains(id))
                continue;
            seenIds.insert(id);

            const QFileInfo info(path);
            const auto cached = cache.constFind(path);
            if (cached != cache.cend()
                && cached->mtime == info.lastModified()
                && cached->size == info.size()) {
                result.cache.insert(path, cached.value());
                if (cached->show)
                    result.apps.append(cached->app);
                continue;
            }

            CacheEntry entry;
            entry.mtime = info.lastModified();
            entry.size = info.size();
            entry.show = DesktopEntry::parse(path, id, entry.app, terminal);
            result.cache.insert(path, entry);
            ++result.parses;
            if (entry.show)
                result.apps.append(entry.app);
        }
    }

    std::sort(result.apps.begin(), result.apps.end(), [](const DesktopApp &left,
                                                          const DesktopApp &right) {
        const int nameOrder = QString::compare(left.name, right.name, Qt::CaseInsensitive);
        return nameOrder == 0 ? left.id < right.id : nameOrder < 0;
    });
    result.watchDirs.removeDuplicates();
    std::sort(result.watchDirs.begin(), result.watchDirs.end());
    return result;
}

bool DesktopIndex::install(ScanResult result)
{
    const bool changed = !m_ready || m_apps != result.apps;
    m_apps = std::move(result.apps);
    m_cache = std::move(result.cache);
    m_ready = true;
    return changed;
}

void DesktopIndex::rewatch(const QStringList &paths)
{
    const QStringList oldFiles = m_watcher->files();
    const QStringList oldDirs = m_watcher->directories();
    if (!oldFiles.isEmpty())
        m_watcher->removePaths(oldFiles);
    if (!oldDirs.isEmpty())
        m_watcher->removePaths(oldDirs);

    QStringList files;
    QStringList dirs;
    for (const QString &path : paths) {
        const QFileInfo info(path);
        if (!info.exists())
            continue;
        (info.isDir() ? dirs : files).append(info.absoluteFilePath());
    }
    if (!files.isEmpty())
        m_watcher->addPaths(files);
    if (!dirs.isEmpty())
        m_watcher->addPaths(dirs);
}

void DesktopIndex::requestScan()
{
    if (m_asyncRunning) {
        m_asyncAgain = true;
        return;
    }

    m_asyncRunning = true;
    ++m_scans;
    const quint64 generation = ++m_gen;
    const QStringList dirs = m_dirs;
    const QHash<QString, CacheEntry> cache = m_cache;
    m_pool.start([this, dirs, cache, generation] {
        ScanResult result = scan(dirs, cache);
        QMetaObject::invokeMethod(this,
            [this, generation, result = std::move(result)]() mutable {
                m_asyncRunning = false;
                if (generation != m_gen) {
                    if (m_asyncAgain) {
                        m_asyncAgain = false;
                        requestScan();
                    }
                    return;
                }
                if (m_asyncAgain) {
                    m_asyncAgain = false;
                    requestScan();
                    return;
                }
                m_parses += result.parses;
                rewatch(result.watchDirs);
                if (install(std::move(result)))
                    emit appsChanged();
            }, Qt::QueuedConnection);
    });
}

bool DesktopIndex::scanNow()
{
    ++m_scans;
    ++m_gen;
    m_asyncAgain = false;
    ScanResult result = scan(m_dirs, m_cache);
    m_parses += result.parses;
    rewatch(result.watchDirs);
    const bool changed = install(std::move(result));
    if (changed)
        emit appsChanged();
    return changed;
}

AppMenuModel::AppMenuModel(QObject *parent)
    : QObject(parent)
    , m_index(DesktopIndex::instance())
{
    if (m_index->ready()) {
        onIndexReady();
    } else {
        connect(m_index, &DesktopIndex::appsChanged, this, &AppMenuModel::onIndexReady);
    }
}

AppMenuModel::~AppMenuModel() = default;

void AppMenuModel::onIndexReady()
{
    m_ready = true;
    rebuildCache();
}

void AppMenuModel::rebuildCache()
{
    m_cachedApps = m_index->apps();
    QStringList categories{QStringLiteral("All")};
    for (const DesktopApp &app : m_cachedApps) {
        if (!app.category.isEmpty() && !categories.contains(app.category))
            categories.append(app.category);
    }
    std::sort(categories.begin() + 1, categories.end());
    m_cachedCategories = std::move(categories);
    emit changed();
}

void AppMenuModel::reload()
{
    if (m_index)
        m_index->requestScan();
}

QStringList AppMenuModel::getCategories() const
{
    return m_cachedCategories;
}

QVariantList AppMenuModel::getApps(const QString &category, const QString &search) const
{
    QVariantList result;
    const QString searchLower = search.trimmed().toLower();
    for (const DesktopApp &app : m_cachedApps) {
        if (!category.isEmpty() && category != QStringLiteral("All")
            && app.category != category)
            continue;
        if (!searchLower.isEmpty()
            && !app.name.toLower().contains(searchLower)
            && !app.exec.toLower().contains(searchLower))
            continue;

        QVariantMap entry;
        entry.insert(QStringLiteral("name"), app.name);
        entry.insert(QStringLiteral("exec"), app.exec);
        entry.insert(QStringLiteral("icon"), app.icon);
        entry.insert(QStringLiteral("category"), app.category);
        // 5: the oracle sent no appId, so Expose always fell back to the raw Exec line; with it,
        // Expose launches through gtk-launch like the dock (field codes, D-Bus activation, flatpak)
        QString appId = app.id;
        if (appId.endsWith(QLatin1String(".desktop")))
            appId.chop(8);
        entry.insert(QStringLiteral("appId"), appId);
        result.append(entry);
    }
    return result;
}

QString AppMenuModel::mapCategory(const QString &categories) const
{
    return DesktopEntry::mapCategory(categories);
}
