// GliaSystemMenus.cpp — implementation
// Rebuilt from oracle: decomp/GliaSystemMenus.c (10 oracle functions).
// Spec: ncde-architecture.md §2, ncde-efficiency.md #7, gliatalk.md.
// DEFECTS FIXED vs oracle:
// 1. Applications use the shared asynchronous DesktopIndex rather than rescanning on the GUI thread.
// 2. Data-change signals are emitted only when exposed properties actually change.
// 3. Recent-file XBEL is parsed as XML, limited to the oracle's first 15 local existing files, and
//    watched even when the file does not exist yet.
// 4. Launch uses parsed argv directly instead of passing desktop Exec text through a shell.

#include "GliaSystemMenus.h"
#include "AppMenuModel_index.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QProcess>
#include <QStandardPaths>
#include <QTimer>
#include <QUrl>
#include <QXmlStreamReader>

GliaSystemMenus::GliaSystemMenus(QObject *parent)
    : QObject(parent)
    , m_index(DesktopIndex::instance())
{
    if (m_index->ready()) {
        onIndexReady();
    } else {
        connect(m_index, &DesktopIndex::appsChanged,
                this, &GliaSystemMenus::onIndexReady);
    }

    m_recentPath = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation))
                       .filePath(QStringLiteral("recently-used.xbel"));
    m_recentDirectory = QFileInfo(m_recentPath).absolutePath();
    m_recentWatcher = new QFileSystemWatcher(this);
    if (QDir(m_recentDirectory).exists())
        m_recentWatcher->addPath(m_recentDirectory);
    if (QFileInfo::exists(m_recentPath))
        m_recentWatcher->addPath(m_recentPath);
    connect(m_recentWatcher, &QFileSystemWatcher::fileChanged,
            this, &GliaSystemMenus::onRecentFileChanged);
    connect(m_recentWatcher, &QFileSystemWatcher::directoryChanged,
            this, &GliaSystemMenus::onRecentFileChanged);

    m_recentDebounce = new QTimer(this);
    m_recentDebounce->setSingleShot(true);
    m_recentDebounce->setInterval(100);
    connect(m_recentDebounce, &QTimer::timeout,
            this, &GliaSystemMenus::rebuildRecentFiles);
    rebuildRecentFiles();
}

GliaSystemMenus::~GliaSystemMenus() = default;

void GliaSystemMenus::onIndexReady()
{
    const QVariantList previousApplications = m_cachedApplications;
    const QVariantList previousPlaces = m_cachedPlaces;
    m_ready = true;
    rebuildApplications();
    rebuildPlaces();
    if (previousApplications != m_cachedApplications || previousPlaces != m_cachedPlaces)
        emit changed();
}

void GliaSystemMenus::rebuildApplications()
{
    QVariantList applications;
    const QList<DesktopApp> &apps = m_index->apps();
    applications.reserve(apps.size());
    for (const DesktopApp &app : apps) {
        QVariantMap entry;
        entry.insert(QStringLiteral("name"), app.name);
        entry.insert(QStringLiteral("exec"), app.exec);
        entry.insert(QStringLiteral("icon"), app.icon);
        entry.insert(QStringLiteral("category"), app.category);
        entry.insert(QStringLiteral("id"), app.id);
        applications.append(entry);
    }
    m_cachedApplications = std::move(applications);
}

void GliaSystemMenus::rebuildPlaces()
{
    static const QList<QPair<QString, QStandardPaths::StandardLocation>> locations = {
        {QStringLiteral("Home"), QStandardPaths::HomeLocation},
        {QStringLiteral("Desktop"), QStandardPaths::DesktopLocation},
        {QStringLiteral("Documents"), QStandardPaths::DocumentsLocation},
        {QStringLiteral("Downloads"), QStandardPaths::DownloadLocation},
        {QStringLiteral("Pictures"), QStandardPaths::PicturesLocation},
        {QStringLiteral("Music"), QStandardPaths::MusicLocation},
        {QStringLiteral("Videos"), QStandardPaths::MoviesLocation}
    };

    QVariantList places;
    for (const auto &location : locations) {
        const QString path = QStandardPaths::writableLocation(location.second);
        if (path.isEmpty() || !QDir(path).exists())
            continue;
        QVariantMap entry;
        entry.insert(QStringLiteral("name"), location.first);
        entry.insert(QStringLiteral("path"), path);
        places.append(entry);
    }
    m_cachedPlaces = std::move(places);
}

void GliaSystemMenus::rebuildRecentFiles()
{
    if (m_recentWatcher && QDir(m_recentDirectory).exists()) {
        if (!m_recentWatcher->directories().contains(m_recentDirectory))
            m_recentWatcher->addPath(m_recentDirectory);
        if (QFileInfo::exists(m_recentPath)
            && !m_recentWatcher->files().contains(m_recentPath))
            m_recentWatcher->addPath(m_recentPath);
    }

    QVariantList recent;
    QFile file(m_recentPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(&file);
        while (!xml.atEnd() && recent.size() < 15) {
            xml.readNext();
            if (!xml.isStartElement() || xml.name() != QStringLiteral("bookmark"))
                continue;

            const QUrl url(xml.attributes().value(QStringLiteral("href")).toString());
            if (!url.isLocalFile())
                continue;
            const QString localPath = url.toLocalFile();
            const QFileInfo info(localPath);
            if (!info.exists() || !info.isFile())
                continue;

            QVariantMap entry;
            entry.insert(QStringLiteral("name"), info.fileName());
            entry.insert(QStringLiteral("path"), localPath);
            recent.append(entry);
        }
    }

    if (m_cachedRecentFiles != recent) {
        m_cachedRecentFiles = std::move(recent);
        emit changed();
    }
}

void GliaSystemMenus::onRecentFileChanged(const QString &)
{
    m_recentDebounce->start();
}

QVariantList GliaSystemMenus::applications() const
{
    return m_cachedApplications;
}

QVariantList GliaSystemMenus::places() const
{
    return m_cachedPlaces;
}

QVariantList GliaSystemMenus::recentFiles() const
{
    return m_cachedRecentFiles;
}

void GliaSystemMenus::rescan()
{
    if (m_index)
        m_index->requestScan();
}

void GliaSystemMenus::launch(const QString &execOrId)
{
    QStringList command;
    QString workingDirectory;
    for (const DesktopApp &app : m_index->apps()) {
        if (app.id != execOrId)
            continue;
        command = app.argv;
        workingDirectory = app.workDir;
        break;
    }
    if (command.isEmpty())
        command = DesktopEntry::splitExec(execOrId);
    if (command.isEmpty())
        return;

    const QString executable = command.takeFirst();
    QProcess::startDetached(executable, command, workingDirectory);
}

void GliaSystemMenus::openPath(const QString &path)
{
    if (!path.isEmpty())
        QProcess::startDetached(QStringLiteral("xdg-open"), {path});
}
