// Settings — construction and destruction. (Kept apart from Settings_core.cpp so unit tests can link the
// area code with a bare constructor of their own.)
//
// Rebuilt from oracle: Settings::Settings (field defaults are in Settings.h; oracle load order kept), ~Settings.
// The constructor also sets the command runners (runDetached / runQuery / runInput) that every applier uses;
// tests replace them or put recording stand-ins first on PATH.
#include "Settings.h"
#include "Lelan.h"

#include <QDir>
#include <QProcess>

Settings::Settings(QObject *parent) : QObject(parent)
{
    runDetached = [](const QString &program, const QStringList &args) { QProcess::startDetached(program, args); };
    runQuery = [this](const QString &program, const QStringList &args, std::function<void(const QString &)> done) {
        auto *p = new QProcess(this);
        connect(p, &QProcess::finished, this, [p, done](int, QProcess::ExitStatus) {
            p->deleteLater();
            done(QString::fromUtf8(p->readAllStandardOutput()));
        });
        p->start(program, args);
    };
    runInput = [this](const QString &program, const QStringList &args, const QByteArray &input) {
        auto *p = new QProcess(this);
        connect(p, &QProcess::finished, p, &QObject::deleteLater);
        connect(p, &QProcess::started, p, [p, input] { p->write(input); p->closeWriteChannel(); });
        p->start(program, args);
    };
    m_configBase = QDir::homePath() + QStringLiteral("/.config/ncde/");
    m_assetBase = qEnvironmentVariable("NCDE_ASSET_BASE", QStringLiteral("/usr/share/ncde/"));   // L2 test session
    if (!m_assetBase.endsWith(QLatin1Char('/')))
        m_assetBase += QLatin1Char('/');
    // oracle load order
    loadDisplay();
    loadPower();
    loadFonts();
    loadStorage();
    loadInput();
    loadAccessibility();
    loadPrivacy();
    loadScreensaver();
    loadDateTime();
    loadNetwork();
    loadDock();
    loadLocale();
    loadDefaults();
    loadNotifications();
    loadWallpaperPrefs();
    loadSound();
    loadKickass();
    loadSectionColors();
}

Settings::~Settings()
{
    if (m_saver && m_saver->state() != QProcess::NotRunning) {
        m_saverStopping = true;
        m_saver->terminate();
        m_saver->waitForFinished(2000);
    }
}

