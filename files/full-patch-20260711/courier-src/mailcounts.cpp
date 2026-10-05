// mailcounts.cpp — see mailcounts.h. Blocking socket calls: runs only on the
// worker thread GoogleLink gives it, never the GUI thread.
#include "mailcounts.h"

#include <QRegularExpression>
#include <QSslSocket>
#include <QDateTime>
#include <cstdio>

namespace {
QByteArray quoted(const QByteArray &name)
{
    QByteArray q = name;
    q.replace('\\', "\\\\").replace('"', "\\\"");
    return '"' + q + '"';
}
}

ImapLink::~ImapLink() { drop(); }

void ImapLink::drop()
{
    if (!m_sock) return;
    if (m_sock->state() == QAbstractSocket::ConnectedState) {
        cmd("LOGOUT", 3000);
        m_sock->disconnectFromHost();
    }
    delete m_sock;
    m_sock = nullptr;
    m_buf.clear();
    m_loggedInAs.clear();
}

void CountsWorker::shutdown() { drop(); }

bool ImapLink::readLine(QByteArray *out, int timeoutMs)
{
    for (;;) {
        const int i = m_buf.indexOf("\r\n");
        if (i >= 0) { *out = m_buf.left(i); m_buf.remove(0, i + 2); return true; }
        if (!m_sock->waitForReadyRead(timeoutMs)) return false;
        m_buf += m_sock->readAll();
    }
}

ImapLink::Reply ImapLink::cmd(const QByteArray &command, int timeoutMs)
{
    Reply r;
    const QByteArray tag = "n" + QByteArray::number(++m_seq);
    m_sock->write(tag + ' ' + command + "\r\n");
    m_sock->flush();
    for (;;) {
        QByteArray line;
        if (!readLine(&line, timeoutMs)) { r.timedOut = true; return r; }
        if (line.startsWith('+')) { m_sock->write("\r\n"); m_sock->flush(); continue; }  // SASL error challenge
        if (line.startsWith(tag + ' ')) { r.status = line.mid(tag.size() + 1); return r; }
        // STATUS / LIST lines never carry literals for Gmail's folder names except
        // non-ASCII ones; pull a literal in so the line stays whole.
        static const QRegularExpression lit(QStringLiteral("\\{(\\d+)\\}$"));
        const auto m = lit.match(QString::fromLatin1(line));
        if (m.hasMatch()) {
            const qsizetype n = m.captured(1).toLongLong();
            while (m_buf.size() < n)
                if (!m_sock->waitForReadyRead(timeoutMs)) { r.timedOut = true; return r; }
                else m_buf += m_sock->readAll();
            QByteArray rest;
            const QByteArray lit = m_buf.left(n);
            m_buf.remove(0, n);
            if (!readLine(&rest, timeoutMs)) { r.timedOut = true; return r; }
            line = line.left(m.capturedStart()) + quoted(lit) + rest;
        }
        r.lines << line;
    }
}

bool ImapLink::ensureOpen(const QString &email, const QString &token, bool wantFolders, QString *why, bool *authFailed)
{
    if (m_sock && m_sock->state() == QAbstractSocket::ConnectedState && m_loggedInAs == email)
        return true;
    drop();
    m_sock = new QSslSocket;
    m_sock->connectToHostEncrypted(QStringLiteral("imap.gmail.com"), 993);
    if (!m_sock->waitForEncrypted(20000)) { *why = QStringLiteral("Could not reach Gmail: ") + m_sock->errorString(); drop(); return false; }
    QByteArray greet;
    if (!readLine(&greet, 15000) || !greet.startsWith("* OK")) { *why = QStringLiteral("Gmail did not greet us"); drop(); return false; }

    const QByteArray sasl = ("user=" + email.toUtf8() + "\x01" "auth=Bearer " + token.toUtf8() + "\x01\x01").toBase64();
    Reply r = cmd("AUTHENTICATE XOAUTH2 " + sasl);
    if (!r.ok()) {
        *why = QStringLiteral("Gmail refused the sign-in");
        *authFailed = !r.timedOut;
        drop();
        return false;
    }
    m_loggedInAs = email;

    // SPECIAL-USE names, once per connection (Gmail answers LIST slowly, ~5 s,
    // so it's never asked again while this connection lives).
    if (wantFolders && m_boxFor.isEmpty()) {
        r = cmd("LIST \"\" \"*\"", 30000);
        if (!r.ok()) { *why = QStringLiteral("Could not list Gmail's folders"); drop(); return false; }
        static const QRegularExpression listRe(QStringLiteral("^\\* LIST \\(([^)]*)\\) (?:\"[^\"]*\"|NIL) (.*)$"));
        static const QHash<QString, QString> idFor = {
            { QStringLiteral("\\Flagged"), QStringLiteral("starred") }, { QStringLiteral("\\Sent"), QStringLiteral("sent") },
            { QStringLiteral("\\Drafts"),  QStringLiteral("drafts") },  { QStringLiteral("\\All"),  QStringLiteral("archive") },
            { QStringLiteral("\\Junk"),    QStringLiteral("spam") },    { QStringLiteral("\\Trash"), QStringLiteral("trash") },
        };
        for (const QByteArray &l : r.lines) {
            const auto m = listRe.match(QString::fromUtf8(l));
            if (!m.hasMatch()) continue;
            QByteArray name = m.captured(2).toUtf8().trimmed();
            if (name.startsWith('"') && name.endsWith('"') && name.size() >= 2) {
                name = name.mid(1, name.size() - 2);
                name.replace("\\\"", "\"").replace("\\\\", "\\");
            }
            for (const QString &f : m.captured(1).split(QLatin1Char(' '), Qt::SkipEmptyParts))
                if (idFor.contains(f)) m_boxFor.insert(idFor.value(f), name);
        }
        m_boxFor.insert(QStringLiteral("inbox"), "INBOX");
    }
    return true;
}

void CountsWorker::poll(const QString &email, const QString &accessToken)
{
    // One retry on a fresh connection: Gmail closes idle sessions after a while.
    for (int attempt = 0; attempt < 2; ++attempt) {
        QString why;
        bool authFailed = false;
        if (!ensureOpen(email, accessToken, true, &why, &authFailed)) {
            if (authFailed || attempt == 1) { Q_EMIT failed(why, authFailed); return; }
            continue;
        }
        QVariantMap counts;
        bool broken = false;
        static const QRegularExpression statusRe(QStringLiteral("\\((.*)\\)\\s*$"));
        for (auto it = m_boxFor.cbegin(); it != m_boxFor.cend(); ++it) {
            const Reply r = cmd("STATUS " + quoted(it.value()) + " (MESSAGES UNSEEN)");
            if (r.timedOut) { broken = true; break; }
            if (!r.ok()) continue;
            for (const QByteArray &l : r.lines) {
                if (qEnvironmentVariableIsSet("NCDE_COURIER_DEBUG")) std::fprintf(stderr, "[courier] raw: %s | %s\n", l.constData(), r.status.constData());
                if (!l.startsWith("* STATUS")) continue;
                const auto m = statusRe.match(QString::fromUtf8(l));
                if (!m.hasMatch()) continue;
                const QStringList kv = m.captured(1).split(QLatin1Char(' '), Qt::SkipEmptyParts);
                QVariantMap one;
                for (int i = 0; i + 1 < kv.size(); i += 2) {
                    if (kv[i] == QLatin1String("MESSAGES")) one.insert(QStringLiteral("total"), kv[i + 1].toInt());
                    if (kv[i] == QLatin1String("UNSEEN"))   one.insert(QStringLiteral("unseen"), kv[i + 1].toInt());
                }
                counts.insert(it.key(), one);
            }
        }
        if (broken) { drop(); continue; }
        Q_EMIT counted(counts);
        return;
    }
}

void IdleWorker::watch(const QString &email, const QString &accessToken)
{
    QString why;
    bool authFailed = false;
    drop();                                   // always a fresh session for a fresh token
    if (!ensureOpen(email, accessToken, false, &why, &authFailed)) { Q_EMIT ended(why, authFailed); return; }
    Reply r = cmd("EXAMINE \"INBOX\"");     // read-only: watching never changes anything
    if (!r.ok()) { drop(); Q_EMIT ended(QStringLiteral("Could not open the Inbox"), false); return; }

    while (!stop) {
        const QByteArray tag = "n" + QByteArray::number(++m_seq);
        m_sock->write(tag + " IDLE\r\n");
        m_sock->flush();
        QByteArray line;
        if (!readLine(&line, 15000) || !line.startsWith('+')) {
            drop(); Q_EMIT ended(QStringLiteral("Gmail would not IDLE"), false); return;
        }
        // RFC 2177: leave IDLE and re-enter at least every 29 minutes.
        const qint64 until = QDateTime::currentMSecsSinceEpoch() + 25LL * 60 * 1000;
        bool changed = false;
        while (!stop && QDateTime::currentMSecsSinceEpoch() < until) {
            const int nl = m_buf.indexOf("\r\n");
            if (nl < 0) {
                if (!m_sock->waitForReadyRead(1000)) {
                    if (m_sock->state() != QAbstractSocket::ConnectedState) {
                        drop(); Q_EMIT ended(QStringLiteral("Gmail closed the connection"), false); return;
                    }
                    // coalesce a burst (EXISTS + FETCH …) into one notice
                    if (changed) { changed = false; Q_EMIT inboxChanged(); }
                    continue;
                }
                m_buf += m_sock->readAll();
                continue;
            }
            const QByteArray l = m_buf.left(nl);
            m_buf.remove(0, nl + 2);
            if (l.startsWith("* BYE")) { drop(); Q_EMIT ended(QStringLiteral("Gmail ended the session"), false); return; }
            if (l.startsWith("* ") && (l.contains(" EXISTS") || l.contains(" EXPUNGE") || l.contains(" FETCH")))
                changed = true;
        }
        if (changed) Q_EMIT inboxChanged();
        m_sock->write("DONE\r\n");
        m_sock->flush();
        for (;;) {                             // drain to the IDLE's tagged answer
            if (!readLine(&line, 15000)) { drop(); Q_EMIT ended(QStringLiteral("no answer to DONE"), false); return; }
            if (line.startsWith(tag + ' ')) break;
            if (line.startsWith("* ") && (line.contains(" EXISTS") || line.contains(" EXPUNGE"))) Q_EMIT inboxChanged();
        }
    }
    drop();
    Q_EMIT ended(QString(), false);
}
