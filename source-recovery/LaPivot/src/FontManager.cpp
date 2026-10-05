// Rebuilt from oracle: decomp/FontManager.c, with its 33 catalog records decoded from
// FontManager::refresh()::CATALOG in oracle/LaPivot.oracle.
// Spec: SESSION_HANDOFF.md §2.1; ncde-architecture.md §2; FonderieTab.qml fontMgr contract.
// DEFECTS FIXED vs oracle:
//  1. fontconfig's potentially long scan runs in an asynchronous child process.
//  2. PackageKit's system-bus calls and all transaction callbacks are asynchronous.
//  3. Missing PackageKit, empty Resolve results, and ErrorCode signals reset busy state with a message.
//  4. Installed status and fontInstalled are published only after fontconfig sees the installed family.

#include "FontManager.h"

#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QDBusConnection>
#include <QProcess>
#include <QProcessEnvironment>
#include <QSet>
#include <QTimer>
#include <QVariantMap>

namespace {

constexpr auto kPackageKitService = "org.freedesktop.PackageKit";
constexpr auto kTransactionInterface = "org.freedesktop.PackageKit.Transaction";

} // namespace

const QList<FontManager::CatalogEntry> &FontManager::catalog()
{
    static const QList<CatalogEntry> entries = {
        {QStringLiteral("Cormorant Garamond"), {}, QStringLiteral("serif"), false, QStringLiteral("NCDE")},
        {QStringLiteral("IM FELL English"), {}, QStringLiteral("serif"), false, QStringLiteral("NCDE")},
        {QStringLiteral("EB Garamond"), {}, QStringLiteral("serif"), true, {}},
        {QStringLiteral("DejaVu Serif"), QStringLiteral("ttf-dejavu"), QStringLiteral("serif"), false, QStringLiteral("extra")},
        {QStringLiteral("Liberation Serif"), QStringLiteral("ttf-liberation"), QStringLiteral("serif"), false, QStringLiteral("extra")},
        {QStringLiteral("Noto Serif"), QStringLiteral("noto-fonts"), QStringLiteral("serif"), false, QStringLiteral("extra")},
        {QStringLiteral("FreeSerif"), QStringLiteral("gnu-free-fonts"), QStringLiteral("serif"), false, QStringLiteral("extra")},
        {QStringLiteral("Comfortaa"), {}, QStringLiteral("sans"), false, QStringLiteral("NCDE")},
        {QStringLiteral("Noto Sans"), QStringLiteral("noto-fonts"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("DejaVu Sans"), QStringLiteral("ttf-dejavu"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("Liberation Sans"), QStringLiteral("ttf-liberation"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("FreeSans"), QStringLiteral("gnu-free-fonts"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("Ubuntu"), QStringLiteral("ttf-ubuntu-font-family"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("Cantarell"), QStringLiteral("cantarell-fonts"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("Roboto"), QStringLiteral("ttf-roboto"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("Open Sans"), QStringLiteral("ttf-opensans"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("Fira Sans"), QStringLiteral("ttf-fira-sans"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("Lato"), QStringLiteral("ttf-lato"), QStringLiteral("sans"), false, QStringLiteral("extra")},
        {QStringLiteral("Cinzel"), {}, QStringLiteral("display"), false, QStringLiteral("NCDE")},
        {QStringLiteral("Cinzel Decorative"), {}, QStringLiteral("display"), false, QStringLiteral("NCDE")},
        {QStringLiteral("Marcellus"), {}, QStringLiteral("display"), false, QStringLiteral("NCDE")},
        {QStringLiteral("IM FELL DW Pica SC"), {}, QStringLiteral("display"), false, QStringLiteral("NCDE")},
        {QStringLiteral("TerminalVector"), {}, QStringLiteral("mono"), false, QStringLiteral("NCDE")},
        {QStringLiteral("JetBrains Mono"), {}, QStringLiteral("mono"), false, QStringLiteral("NCDE")},
        {QStringLiteral("DejaVu Sans Mono"), QStringLiteral("ttf-dejavu"), QStringLiteral("mono"), false, QStringLiteral("extra")},
        {QStringLiteral("Liberation Mono"), QStringLiteral("ttf-liberation"), QStringLiteral("mono"), false, QStringLiteral("extra")},
        {QStringLiteral("Noto Sans Mono"), QStringLiteral("noto-fonts"), QStringLiteral("mono"), false, QStringLiteral("extra")},
        {QStringLiteral("Ubuntu Mono"), QStringLiteral("ttf-ubuntu-font-family"), QStringLiteral("mono"), false, QStringLiteral("extra")},
        {QStringLiteral("FreeMono"), QStringLiteral("gnu-free-fonts"), QStringLiteral("mono"), false, QStringLiteral("extra")},
        {QStringLiteral("Noto Rashi Hebrew"), {}, QStringLiteral("biblical"), false, QStringLiteral("NCDE")},
        {QStringLiteral("Noto Naskh Arabic"), {}, QStringLiteral("world"), false, QStringLiteral("NCDE")},
        {QStringLiteral("Noto Kufi Arabic"), {}, QStringLiteral("world"), false, QStringLiteral("NCDE")},
        {QStringLiteral("Noto Nastaliq Urdu"), {}, QStringLiteral("world"), false, QStringLiteral("NCDE")}
    };
    return entries;
}

FontManager::FontManager(QObject *parent)
    : QObject(parent)
{
    m_fonts = catalogRows();
    refresh();
}

FontManager::~FontManager()
{
    disconnectTransaction();
    if (m_scanProcess && m_scanProcess->state() != QProcess::NotRunning)
        m_scanProcess->terminate();
}

QVariantList FontManager::fonts() const
{
    return m_fonts;
}

bool FontManager::busy() const
{
    return m_busy;
}

QString FontManager::status() const
{
    return m_status;
}

int FontManager::installedCount() const
{
    int count = 0;
    for (const QVariant &value : m_fonts) {
        if (value.toMap().value(QStringLiteral("installed")).toBool())
            ++count;
    }
    return count;
}

int FontManager::total() const
{
    return m_fonts.size();
}

QStringList FontManager::families()
{
    return m_families;
}

QStringList FontManager::parseFontconfigFamilies(const QByteArray &output)
{
    QSet<QString> unique;
    for (const QString &line : QString::fromUtf8(output).split(QLatin1Char('\n'))) {
        for (QString family : line.split(QLatin1Char(','))) {
            family = family.trimmed();
            if (!family.isEmpty())
                unique.insert(family);
        }
    }
    QStringList result = unique.values();
    result.sort(Qt::CaseInsensitive);
    return result;
}

QVariantList FontManager::catalogRows() const
{
    QVariantList rows;
    rows.reserve(catalog().size());
    for (const CatalogEntry &entry : catalog()) {
        QVariantMap row;
        row.insert(QStringLiteral("family"), entry.family);
        row.insert(QStringLiteral("pkg"), entry.package);
        row.insert(QStringLiteral("category"), entry.category);
        row.insert(QStringLiteral("aur"), entry.aur);
        row.insert(QStringLiteral("repo"), entry.repository);
        row.insert(QStringLiteral("installed"), containsFamily(entry.family));
        rows.append(row);
    }
    return rows;
}

bool FontManager::containsFamily(const QString &family) const
{
    return std::any_of(m_families.cbegin(), m_families.cend(), [&family](const QString &candidate) {
        return candidate.compare(family, Qt::CaseInsensitive) == 0;
    });
}

QString FontManager::familyFor(const QString &package) const
{
    for (const CatalogEntry &entry : catalog()) {
        if ((!entry.package.isEmpty() && entry.package == package) || entry.family == package)
            return entry.family;
    }
    return package;
}

void FontManager::refresh()
{
    if (m_scanProcess) {
        m_refreshPending = true;
        return;
    }
    auto *process = new QProcess(this);
    m_scanProcess = process;
    process->setProgram(QStringLiteral("fc-list"));
    process->setArguments({QStringLiteral("--format=%{family}\\n")});
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    environment.insert(QStringLiteral("LC_ALL"), QStringLiteral("C"));
    process->setProcessEnvironment(environment);
    connect(process, &QProcess::finished, this,
            [this, process](int exitCode, QProcess::ExitStatus exitStatus) {
        if (m_scanProcess != process)
            return;
        const QByteArray output = process->readAllStandardOutput();
        const QString error = (exitStatus == QProcess::NormalExit && exitCode == 0)
            ? QString() : QString::fromLocal8Bit(process->readAllStandardError()).trimmed();
        m_scanProcess = nullptr;
        process->deleteLater();
        onFontScanFinished(parseFontconfigFamilies(output), error);
    });
    connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError) {
        if (m_scanProcess != process)
            return;
        const QString error = process->errorString();
        m_scanProcess = nullptr;
        process->deleteLater();
        onFontScanFinished({}, error);
    });
    process->start();
}

void FontManager::onFontScanFinished(const QStringList &families, const QString &error)
{
    if (error.isEmpty()) {
        m_families = families;
        const QVariantList updated = catalogRows();
        if (updated != m_fonts) {
            m_fonts = updated;
            emit fontsChanged();
        } else {
            emit fontsChanged();
        }
        if (m_installWaitingForRefresh) {
            if (containsFamily(m_completedFamily)) {
                const QString package = m_completedPackage;
                const QString family = m_completedFamily;
                m_installWaitingForRefresh = false;
                emit fontInstalled(package, family);
                finishInstall(true, family + QStringLiteral(" is ready — set before every app."));
            } else if (++m_installRefreshAttempts < 3) {
                QTimer::singleShot(300, this, &FontManager::refresh);
            } else {
                m_installWaitingForRefresh = false;
                finishInstall(false, QStringLiteral("PackageKit installed the package, but fontconfig cannot yet see %1.")
                                         .arg(m_completedFamily));
            }
        } else if (!m_busy) {
            setStatus(QStringLiteral("The foundry is ready."));
        }
    } else {
        qWarning("FontManager: fontconfig scan failed: %s", qPrintable(error));
        if (m_installWaitingForRefresh) {
            m_installWaitingForRefresh = false;
            finishInstall(false, QStringLiteral("The installed face is not yet visible to fontconfig: %1").arg(error));
        } else if (m_fonts.isEmpty()) {
            setStatus(QStringLiteral("Fontconfig could not read the installed font catalog."));
        }
    }
    if (m_refreshPending) {
        m_refreshPending = false;
        QTimer::singleShot(0, this, &FontManager::refresh);
    }
}

void FontManager::installFont(const QString &package)
{
    if (m_busy) {
        setStatus(QStringLiteral("The foundry is already pouring — one face at a time."));
        return;
    }
    const QString requested = package.trimmed();
    if (requested.isEmpty()) {
        setStatus(QStringLiteral("That face travels with NCDE itself — nothing to fetch."));
        return;
    }
    const QString family = familyFor(requested);
    if (containsFamily(family)) {
        setStatus(family + QStringLiteral(" is already available to every app."));
        return;
    }

    m_requestedPackage = requested;
    m_requestedFamily = family;
    m_resolvedPackageId.clear();
    m_pkError.clear();
    m_transactionState = TransactionState::Resolve;
    setBusy(true);
    setStatus(QStringLiteral("Sending for %1…").arg(family));
    newTransaction([this](const QDBusObjectPath &path) { beginResolve(path); });
}

void FontManager::beginResolve(const QDBusObjectPath &path)
{
    connectTransaction(path, TransactionState::Resolve);
    callTransaction(path.path(), QStringLiteral("Resolve"),
                    {QVariant::fromValue(quint32(0)), QVariant::fromValue(QStringList{m_requestedFamily})});
}

void FontManager::beginInstall(const QDBusObjectPath &path)
{
    connectTransaction(path, TransactionState::Install);
    callTransaction(path.path(), QStringLiteral("InstallPackages"),
                    {QVariant::fromValue(quint32(0)), QVariant::fromValue(QStringList{m_resolvedPackageId})});
}

void FontManager::callTransaction(const QString &path, const QString &method, const QVariantList &arguments)
{
    QDBusMessage request = QDBusMessage::createMethodCall(
        QString::fromLatin1(kPackageKitService), path, QString::fromLatin1(kTransactionInterface), method);
    request.setArguments(arguments);
    auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(request), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this, watcher, path] {
        const QDBusPendingReply<> reply = *watcher;
        watcher->deleteLater();
        if (reply.isError() && path == m_activePath)
            finishInstall(false, QStringLiteral("PackageKit could not start the font transaction: %1")
                                     .arg(reply.error().message()));
    });
}

void FontManager::connectTransaction(const QDBusObjectPath &path, TransactionState state)
{
    disconnectTransaction();
    m_activePath = path.path();
    m_transactionState = state;
    QDBusConnection bus = QDBusConnection::systemBus();
    const QString service = QString::fromLatin1(kPackageKitService);
    const QString interface = QString::fromLatin1(kTransactionInterface);
    if (state == TransactionState::Resolve) {
        bus.connect(service, m_activePath, interface, QStringLiteral("Package"), this,
                    SLOT(onResolvePackage(uint,QString,QString)));
        bus.connect(service, m_activePath, interface, QStringLiteral("Finished"), this,
                    SLOT(onResolveFinished(uint,uint)));
    } else {
        bus.connect(service, m_activePath, interface, QStringLiteral("Finished"), this,
                    SLOT(onInstallFinished(uint,uint)));
    }
    bus.connect(service, m_activePath, interface, QStringLiteral("ErrorCode"), this,
                SLOT(onPkError(uint,QString)));
}

void FontManager::disconnectTransaction()
{
    if (m_activePath.isEmpty())
        return;
    QDBusConnection bus = QDBusConnection::systemBus();
    const QString service = QString::fromLatin1(kPackageKitService);
    const QString interface = QString::fromLatin1(kTransactionInterface);
    bus.disconnect(service, m_activePath, interface, QStringLiteral("Package"), this,
                   SLOT(onResolvePackage(uint,QString,QString)));
    bus.disconnect(service, m_activePath, interface, QStringLiteral("Finished"), this,
                   SLOT(onResolveFinished(uint,uint)));
    bus.disconnect(service, m_activePath, interface, QStringLiteral("Finished"), this,
                   SLOT(onInstallFinished(uint,uint)));
    bus.disconnect(service, m_activePath, interface, QStringLiteral("ErrorCode"), this,
                   SLOT(onPkError(uint,QString)));
    m_activePath.clear();
}

void FontManager::onResolvePackage(uint, const QString &packageId, const QString &)
{
    if (m_transactionState == TransactionState::Resolve && m_resolvedPackageId.isEmpty())
        m_resolvedPackageId = packageId;
}

void FontManager::onResolveFinished(uint exitCode, uint)
{
    if (m_transactionState != TransactionState::Resolve)
        return;
    disconnectTransaction();
    if (exitCode != 1 || m_resolvedPackageId.isEmpty()) {
        finishInstall(false, m_pkError.isEmpty()
                                 ? QStringLiteral("The foundry couldn't find that face in the cases.")
                                 : m_pkError);
        return;
    }
    setStatus(QStringLiteral("Pouring %1…").arg(m_requestedFamily));
    newTransaction([this](const QDBusObjectPath &path) { beginInstall(path); });
}

void FontManager::onInstallFinished(uint exitCode, uint)
{
    if (m_transactionState != TransactionState::Install)
        return;
    disconnectTransaction();
    if (exitCode != 1) {
        finishInstall(false, m_pkError.isEmpty()
                                 ? QStringLiteral("The pour didn't take — the face was not installed.")
                                 : m_pkError);
        return;
    }
    m_installWaitingForRefresh = true;
    m_completedPackage = m_requestedPackage;
    m_completedFamily = m_requestedFamily;
    m_installRefreshAttempts = 0;
    refresh();
}

void FontManager::onPkError(uint, const QString &details)
{
    m_pkError = details.trimmed();
    if (m_pkError.isEmpty())
        m_pkError = QStringLiteral("PackageKit reported an unspecified error.");
    qWarning("FontManager: PackageKit error: %s", qPrintable(m_pkError));
    finishInstall(false, m_pkError);
}

void FontManager::finishInstall(bool success, const QString &message)
{
    disconnectTransaction();
    m_installWaitingForRefresh = false;
    m_completedPackage.clear();
    m_completedFamily.clear();
    m_transactionState = TransactionState::None;
    const QString details = (!success && !m_pkError.isEmpty())
        ? QStringLiteral(" (%1)").arg(m_pkError) : QString();
    setBusy(false);
    setStatus(message + details);
    m_requestedPackage.clear();
    m_requestedFamily.clear();
    m_resolvedPackageId.clear();
    m_pkError.clear();
}

void FontManager::setBusy(bool value)
{
    if (m_busy == value)
        return;
    m_busy = value;
    emit statusChanged();
}

void FontManager::setStatus(const QString &value)
{
    if (m_status == value)
        return;
    m_status = value;
    emit statusChanged();
}
