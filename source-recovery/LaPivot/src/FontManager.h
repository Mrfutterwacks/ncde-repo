// Rebuilt from oracle: decomp/FontManager.c; Q_OBJECT block from gen_header.py FontManager.
// Spec: NCDE-ARCHITECTURE-DIGEST.md §2; ncde-architecture.md; SESSION_HANDOFF.md §2.1.
// DEFECTS FIXED vs oracle:
//  1. Fontconfig discovery runs as an asynchronous fc-list child, not a blocking GUI-thread scan.
//  2. PackageKit transactions are asynchronous and fail gracefully when the system service is absent.
//  3. fontInstalled is emitted only after the newly installed family appears in a fresh fontconfig scan.
//  4. Preserve the exact 33-face oracle catalog and house-face repository/package metadata.

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QObject>
#include <QVariantList>
#include <QStringList>
#include <QDBusConnection>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <functional>
#include <utility>

class QProcess;

class FontManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList fonts READ fonts NOTIFY fontsChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY statusChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(int installedCount READ installedCount NOTIFY fontsChanged)
    Q_PROPERTY(int total READ total NOTIFY fontsChanged)

public:
    explicit FontManager(QObject *parent = nullptr);
    ~FontManager() override;

    QVariantList fonts() const;
    bool busy() const;
    QString status() const;
    int installedCount() const;
    int total() const;

    Q_INVOKABLE QStringList families();
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void installFont(const QString &pkg);

signals:
    void fontsChanged();
    void fontInstalled(const QString &pkg, const QString &family);
    void statusChanged();

private slots:
    void onResolvePackage(uint info, const QString &packageId, const QString &summary);
    void onResolveFinished(uint exitCode, uint runtime);
    void onInstallFinished(uint exitCode, uint runtime);
    void onPkError(uint code, const QString &details);

private:
    enum class TransactionState { None, Resolve, Install };
    struct CatalogEntry {
        QString family;
        QString package;
        QString category;
        bool aur = false;
        QString repository;
    };

    static const QList<CatalogEntry> &catalog();
    static QStringList parseFontconfigFamilies(const QByteArray &output);
    QString familyFor(const QString &package) const;
    QVariantList catalogRows() const;
    bool containsFamily(const QString &family) const;
    void setBusy(bool value);
    void setStatus(const QString &value);
    void beginResolve(const QDBusObjectPath &path);
    void beginInstall(const QDBusObjectPath &path);
    void callTransaction(const QString &path, const QString &method, const QVariantList &arguments);
    void connectTransaction(const QDBusObjectPath &path, TransactionState state);
    void disconnectTransaction();
    void onFontScanFinished(const QStringList &families, const QString &error);
    void finishInstall(bool success, const QString &message);

    template <typename Callback>
    void newTransaction(Callback callback)
    {
        const QString service = QStringLiteral("org.freedesktop.PackageKit");
        const QString object = QStringLiteral("/org/freedesktop/PackageKit");
        const QString interface = QStringLiteral("org.freedesktop.PackageKit");
        const QDBusMessage request = QDBusMessage::createMethodCall(service, object, interface,
                                                                    QStringLiteral("CreateTransaction"));
        auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(request), this);
        connect(watcher, &QDBusPendingCallWatcher::finished, this,
                [this, watcher, callback = std::move(callback)]() mutable {
            const QDBusPendingReply<QDBusObjectPath> reply = *watcher;
            watcher->deleteLater();
            if (reply.isError() || reply.value().path().isEmpty()) {
                const QString details = reply.isError()
                    ? reply.error().message()
                    : QStringLiteral("PackageKit returned no transaction.");
                finishInstall(false, QStringLiteral("The foundry's PackageKit service is unavailable: %1").arg(details));
                return;
            }
            callback(reply.value());
        });
    }

    QVariantList m_fonts;
    QStringList m_families;
    bool m_busy = false;
    QString m_status = QStringLiteral("The foundry is ready.");
    QProcess *m_scanProcess = nullptr;
    bool m_refreshPending = false;
    QString m_requestedPackage;
    QString m_requestedFamily;
    QString m_resolvedPackageId;
    QString m_pkError;
    QString m_activePath;
    TransactionState m_transactionState = TransactionState::None;
    bool m_installWaitingForRefresh = false;
    QString m_completedPackage;
    QString m_completedFamily;
    int m_installRefreshAttempts = 0;
};

#endif
