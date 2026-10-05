// mailcounts.h — keeps Hummingbird's folder numbers true, the way Thunderbird
// does: ONE Gmail IMAP connection kept open on a worker thread (never a new
// login per question), SPECIAL-USE folder names looked up once, then
// STATUS (MESSAGES UNSEEN) for each folder whenever asked.
//
// It never changes mail. Delete, read and move stay with Hummingbird's engine.
#pragma once
#include <QObject>
#include <QVariantMap>
#include <QHash>
#include <QByteArray>

class QSslSocket;

#include <atomic>

// One Gmail IMAP connection (XOAUTH2), blocking calls on its own thread.
class ImapLink : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
    ~ImapLink() override;
protected:
    struct Reply { QList<QByteArray> lines; QByteArray status; bool timedOut = false;
                   bool ok() const { return !timedOut && status.startsWith("OK"); } };
    bool ensureOpen(const QString &email, const QString &token, bool wantFolders, QString *why, bool *authFailed);
    Reply cmd(const QByteArray &command, int timeoutMs = 20000);
    bool readLine(QByteArray *out, int timeoutMs);
    void drop();

    QSslSocket *m_sock = nullptr;
    QByteArray m_buf;
    QHash<QString, QByteArray> m_boxFor;   // folder id → Gmail mailbox name
    QString m_loggedInAs;
    int m_seq = 0;
};

class CountsWorker : public ImapLink
{
    Q_OBJECT
public:
    using ImapLink::ImapLink;

public Q_SLOTS:
    // Folder ids are Hummingbird's: inbox starred sent drafts archive spam trash.
    void poll(const QString &email, const QString &accessToken);
    void shutdown();

Q_SIGNALS:
    // counts: { folderId: { unseen: int, total: int } }
    void counted(const QVariantMap &counts);
    // authFailed = Gmail refused the sign-in (token needs refreshing)
    void failed(const QString &why, bool authFailed);

};

// Thunderbird's "use_idle": a second kept-open connection parked in IMAP IDLE
// on the Inbox, so Gmail tells us the moment a letter arrives or goes.
class IdleWorker : public ImapLink
{
    Q_OBJECT
public:
    using ImapLink::ImapLink;
    std::atomic_bool stop{false};
public Q_SLOTS:
    void watch(const QString &email, const QString &accessToken);   // blocks until stop or error
Q_SIGNALS:
    void inboxChanged();
    void ended(const QString &why, bool authFailed);
};
