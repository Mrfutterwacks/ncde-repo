// googlelink.h — NCDE.Courier's GoogleLink: Hummingbird's one Google sign-in
// for the things its engine can't do by itself.
//   • Address Book = your Gmail contacts (saved + "Other contacts", People API),
//     refreshed every 30 minutes like Thunderbird's address book sync
//   • true folder numbers (MailCounts: one kept-open Gmail connection)
//   • the calendar permission for LeapFrog, asked in the same consent
// Like Thunderbird (OAuth2Providers.sys.mjs) it asks for mail + contacts +
// calendar together, and reads back what Google actually granted; a box left
// unticked on Google's page is shown on screen with a way to try again.
// The engine's own mail login is never touched.
#pragma once
#include <QObject>
#include <QPointer>
#include <QVariantList>
#include <QVariantMap>
#include <QDateTime>
#include <QStringList>
#include <functional>

class QNetworkAccessManager;
class QTcpServer;
class QTimer;
class QThread;
class CountsWorker;
class IdleWorker;

class GoogleLink : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *mailEngine READ mailEngine WRITE setMailEngine NOTIFY mailEngineChanged)
    Q_PROPERTY(bool configured READ configured NOTIFY stateChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY stateChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY stateChanged)
    Q_PROPERTY(QString email READ email NOTIFY stateChanged)
    Q_PROPERTY(QString status READ status NOTIFY stateChanged)
    // Plain names of what Google did NOT grant: "Gmail", "Contacts", "Other contacts", "Calendar"
    Q_PROPERTY(QStringList missing READ missing NOTIFY stateChanged)
    Q_PROPERTY(QString lastSync READ lastSync NOTIFY contactsChanged)
    Q_PROPERTY(QVariantList contacts READ contacts NOTIFY contactsChanged)
    Q_PROPERTY(int contactCount READ contactCount NOTIFY contactsChanged)
    // { folderId: { unseen, total } } straight from Gmail; empty until first answer
    Q_PROPERTY(QVariantMap counts READ counts NOTIFY countsChanged)

public:
    explicit GoogleLink(QObject *parent = nullptr);
    ~GoogleLink() override;

    QObject *mailEngine() const { return m_engine; }
    void setMailEngine(QObject *e);
    bool configured() const { return !m_clientId.isEmpty() && !m_clientSecret.isEmpty(); }
    bool connected() const { return !m_email.isEmpty(); }
    bool busy() const { return m_busy; }
    QString email() const { return m_email; }
    QString status() const { return m_status; }
    QStringList missing() const;
    QString lastSync() const;
    QVariantList contacts() const { return m_contacts; }
    int contactCount() const { return m_contacts.size(); }
    QVariantMap counts() const { return m_counts; }

    Q_INVOKABLE void signIn();
    Q_INVOKABLE void syncContacts();
    // Ask Gmail for fresh folder numbers after delayMs (calls within the delay merge).
    Q_INVOKABLE void countsSoon(int delayMs = 1500);
    // Instant local change while Gmail catches up (a delete, a read); Gmail's
    // own numbers replace it at the next count.
    Q_INVOKABLE void adjustCount(const QString &folderId, int dUnseen, int dTotal);
    Q_INVOKABLE void forget();

Q_SIGNALS:
    void mailEngineChanged();
    void stateChanged();
    void contactsChanged();
    void countsChanged();
    void message(const QString &text);
    void pollCounts(const QString &email, const QString &access);   // → worker thread
    void watchInbox(const QString &email, const QString &access);   // → IDLE thread
    // Gmail announced a change in this folder (IDLE, or a count that moved)
    void folderChanged(const QString &folderId);

private:
    enum class Flow { Link, EnableApis };
    struct Page { QVariantList people; QString error; bool disabled = false; bool scopeMissing = false; };
    using TokenFn = std::function<void(const QString &)>;
    using ErrorFn = std::function<void(const QString &)>;

    void loadClient();
    void loadState();
    void saveState();
    void loadCache();
    void saveCache();
    void setBusy(bool b, const QString &status = QString());
    void fail(const QString &text);
    void setGranted(const QString &scope);

    void autoStep();
    bool engineIsGoogle() const;
    QString engineEmail() const;
    bool sameAccountAsMail() const;

    void startFlow(Flow flow);
    void onCallback();
    void exchangeCode(const QString &code);
    void finishLink(const QString &access, const QString &refresh, int expiresIn, const QString &grantedScope);
    void enableApis(const QString &access);
    void pollOperation(const QString &access, const QString &name, int triesLeft);

    void refreshAccess(const QString &refreshToken, std::function<void(const QString &, int, const QString &)> ok, ErrorFn bad);
    void withToken(TokenFn fn, ErrorFn onError = {});
    void fetchPages(const QString &access, const QString &url, const QString &field,
                    QVariantList acc, std::function<void(Page)> done);
    void countNow();
    void startWatching();

    QNetworkAccessManager *m_net = nullptr;
    QTcpServer *m_server = nullptr;
    QTimer *m_flowTimeout = nullptr;
    QTimer *m_contactsTimer = nullptr;
    QTimer *m_countsTimer = nullptr;
    QTimer *m_countsSoon = nullptr;
    QThread *m_countsThread = nullptr;
    CountsWorker *m_counter = nullptr;
    QThread *m_idleThread = nullptr;
    IdleWorker *m_idler = nullptr;
    bool m_watching = false;
    QPointer<QObject> m_engine;
    Flow m_flow = Flow::Link;

    QString m_clientId, m_clientSecret;
    QString m_email, m_name, m_status;
    QString m_verifier, m_state, m_redirect;
    QString m_access;
    QStringList m_granted;
    QDateTime m_accessExpiry;
    QDateTime m_lastSync;
    QDateTime m_enableAskedAt;
    QDateTime m_pollStartedAt, m_adjustedAt;
    QVariantList m_contacts;
    QVariantMap m_counts;
    bool m_autoPrompted = false;
    QString m_askedFor;                 // the missing permissions we last opened Google for
    bool m_busy = false;
    bool m_counting = false;
    int m_enableRetries = 0;
};
