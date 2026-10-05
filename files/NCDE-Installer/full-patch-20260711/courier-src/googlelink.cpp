// googlelink.cpp — see googlelink.h.
#include "googlelink.h"
#include "keyring.h"
#include "mailcounts.h"

#include <QCollator>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcess>
#include <QRandomGenerator>
#include <QRegularExpression>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QTimer>
#include <QUrlQuery>
#include <QTime>
#include <cstdio>

// Hummingbird's engine swallows Qt log lines; these go straight to its log.
#define courierLog(...) (std::fprintf(stderr, "%s ", qPrintable(QTime::currentTime().toString(QStringLiteral("HH:mm:ss.zzz")))), std::fprintf(stderr, __VA_ARGS__), std::fputc('\n', stderr), std::fflush(stderr))

namespace {

const char kAuthUrl[]     = "https://accounts.google.com/o/oauth2/v2/auth";
const char kTokenUrl[]    = "https://oauth2.googleapis.com/token";
const char kUserInfoUrl[] = "https://openidconnect.googleapis.com/v1/userinfo";
const char kCloudScope[]  = "https://www.googleapis.com/auth/cloud-platform";

// Everything asked for in the one consent, with the name the person sees.
struct Scope { const char *url; const char *name; };
const Scope kScopes[] = {
    { "https://mail.google.com/",                                "Gmail" },
    { "https://www.googleapis.com/auth/contacts.readonly",       "Contacts" },
    { "https://www.googleapis.com/auth/contacts.other.readonly", "Other contacts" },
    { "https://www.googleapis.com/auth/calendar",                "Calendar" },
};
const char kMailScope[]     = "https://mail.google.com/";
const char kContactsScope[] = "https://www.googleapis.com/auth/contacts.readonly";
const char kOtherScope[]    = "https://www.googleapis.com/auth/contacts.other.readonly";

const int kContactsEverySec = 5 * 60;    // Thunderbird uses 30 min; the operator wants it near real time
const int kCountsEverySec   = 60;        // folder numbers while Hummingbird is open

QString configDir()
{
    return QDir::homePath() + QStringLiteral("/.config/ncde/hummingbird/");
}

QString randomString(int n)
{
    static const char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~";
    QString s;
    s.reserve(n);
    for (int i = 0; i < n; ++i)
        s += QLatin1Char(alphabet[QRandomGenerator::system()->bounded(int(sizeof(alphabet) - 1))]);
    return s;
}

QJsonObject readJson(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) return {};
    return QJsonDocument::fromJson(f.readAll()).object();
}

bool writePrivate(const QString &path, const QByteArray &data)
{
    QDir().mkpath(QFileInfo(path).absolutePath());
    QFile f(path + QStringLiteral(".tmp"));
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;
    f.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    f.write(data);
    f.close();
    QFile::remove(path);
    return QFile::rename(path + QStringLiteral(".tmp"), path);
}

QNetworkRequest request(const QString &url)
{
    QNetworkRequest r{QUrl(url)};
    r.setTransferTimeout(30000);
    return r;
}

// Google error JSON → one readable line.
QString googleError(const QByteArray &body, int http, bool *serviceDisabled = nullptr,
                    bool *scopeMissing = nullptr)
{
    const QJsonObject o = QJsonDocument::fromJson(body).object();
    QString msg, reason;
    if (o.value(QStringLiteral("error")).isObject()) {
        const QJsonObject e = o.value(QStringLiteral("error")).toObject();
        msg = e.value(QStringLiteral("message")).toString();
        for (const QJsonValue &d : e.value(QStringLiteral("details")).toArray()) {
            const QString r = d.toObject().value(QStringLiteral("reason")).toString();
            if (!r.isEmpty()) reason = r;
        }
        if (reason.isEmpty()) reason = e.value(QStringLiteral("status")).toString();
    } else {
        reason = o.value(QStringLiteral("error")).toString();
        msg = o.value(QStringLiteral("error_description")).toString();
    }
    if (serviceDisabled)
        *serviceDisabled = reason == QLatin1String("SERVICE_DISABLED")
                           || msg.contains(QLatin1String("has not been used in project"))
                           || msg.contains(QLatin1String("is disabled"));
    if (scopeMissing)
        *scopeMissing = reason == QLatin1String("ACCESS_TOKEN_SCOPE_INSUFFICIENT")
                        || msg.contains(QLatin1String("insufficient authentication scopes"));
    if (msg.isEmpty()) msg = reason;
    if (msg.isEmpty()) msg = QStringLiteral("HTTP %1").arg(http);
    return msg.left(200);
}

// People API person → address-book entry {nm, em, tel, src}, the same shape
// as the engine's own contacts so the Address Book shows either unchanged.
QVariantMap personEntry(const QJsonObject &p, const QString &src)
{
    auto pick = [](const QJsonArray &a, const QString &key) {
        QString first;
        for (const QJsonValue &v : a) {
            const QJsonObject o = v.toObject();
            const QString val = o.value(key).toString().trimmed();
            if (val.isEmpty()) continue;
            if (o.value(QStringLiteral("metadata")).toObject().value(QStringLiteral("primary")).toBool())
                return val;
            if (first.isEmpty()) first = val;
        }
        return first;
    };
    const QString em  = pick(p.value(QStringLiteral("emailAddresses")).toArray(), QStringLiteral("value"));
    const QString tel = pick(p.value(QStringLiteral("phoneNumbers")).toArray(), QStringLiteral("value"));
    QString nm = pick(p.value(QStringLiteral("names")).toArray(), QStringLiteral("displayName"));
    if (nm.isEmpty()) nm = em.section(QLatin1Char('@'), 0, 0);
    if (nm.isEmpty()) nm = tel;
    if (em.isEmpty() && tel.isEmpty()) return {};
    QVariantMap e;
    e.insert(QStringLiteral("nm"), nm);
    e.insert(QStringLiteral("em"), em);
    e.insert(QStringLiteral("tel"), tel);
    e.insert(QStringLiteral("src"), src);
    return e;
}

// Hummingbird's own Google desktop client, read from the installed program at
// runtime (never written anywhere), so no one has to supply it by hand.
bool embeddedClient(QString *id, QString *secret)
{
    QStringList paths;
    const QString self = QCoreApplication::applicationFilePath();
    if (QFileInfo(self).fileName() == QLatin1String("hummingbird-courier")) paths << self;
    paths << QStringLiteral("/usr/local/bin/hummingbird-courier");
    auto u16 = [](const char *s) {
        QByteArray out;
        for (const char *p = s; *p; ++p) { out += *p; out += '\0'; }
        return out;
    };
    auto okChar = [](char ch, bool upper) {
        return (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '-'
               || (upper && ((ch >= 'A' && ch <= 'Z') || ch == '_'));
    };
    static const QRegularExpression idShape(QStringLiteral("^\\d+-[a-z0-9]+$"));
    for (const QString &p : paths) {
        QFile f(p);
        if (!f.open(QIODevice::ReadOnly)) continue;
        const QByteArray d = f.readAll();
        QString gotId, gotSecret;
        const QByteArray host = u16(".apps.googleusercontent.com");
        for (qsizetype at = d.indexOf(host); at >= 0 && gotId.isEmpty(); at = d.indexOf(host, at + 2)) {
            qsizetype s = at;
            while (s >= 2 && d.at(s - 1) == 0 && okChar(d.at(s - 2), false)) s -= 2;
            QString prefix;
            for (qsizetype i = s; i < at; i += 2) prefix += QLatin1Char(d.at(i));
            if (idShape.match(prefix).hasMatch()) gotId = prefix + QStringLiteral(".apps.googleusercontent.com");
        }
        const QByteArray tag = u16("GOCSPX-");
        const qsizetype at = d.indexOf(tag);
        if (at >= 0) {
            QString s = QStringLiteral("GOCSPX-");
            for (qsizetype i = at + tag.size(); i + 1 < d.size() && d.at(i + 1) == 0 && okChar(d.at(i), true); i += 2)
                s += QLatin1Char(d.at(i));
            if (s.size() > 20) gotSecret = s;
        }
        if (!gotId.isEmpty() && !gotSecret.isEmpty()) { *id = gotId; *secret = gotSecret; return true; }
    }
    return false;
}

}  // namespace

GoogleLink::GoogleLink(QObject *parent)
    : QObject(parent), m_net(new QNetworkAccessManager(this))
{
    loadClient();
    loadState();
    loadCache();

    m_contactsTimer = new QTimer(this);
    m_contactsTimer->setInterval(kContactsEverySec * 1000);
    connect(m_contactsTimer, &QTimer::timeout, this, [this] {
        if (connected() && !m_busy && m_granted.contains(QLatin1String(kContactsScope))) syncContacts();
    });

    m_countsSoon = new QTimer(this);
    m_countsSoon->setSingleShot(true);
    connect(m_countsSoon, &QTimer::timeout, this, &GoogleLink::countNow);
    m_countsTimer = new QTimer(this);
    m_countsTimer->setInterval(kCountsEverySec * 1000);
    connect(m_countsTimer, &QTimer::timeout, this, &GoogleLink::countNow);

    // The one kept-open Gmail connection lives on its own thread.
    m_countsThread = new QThread(this);
    m_counter = new CountsWorker;
    m_counter->moveToThread(m_countsThread);
    connect(m_countsThread, &QThread::finished, m_counter, &QObject::deleteLater);
    connect(this, &GoogleLink::pollCounts, m_counter, &CountsWorker::poll);
    connect(m_counter, &CountsWorker::counted, this, [this](const QVariantMap &c) {
        m_counting = false;
        // Asked before a local change the server may not have caught up with:
        // keep what's on screen and ask again once it has.
        if (m_adjustedAt.isValid() && m_pollStartedAt < m_adjustedAt) { countsSoon(12000); return; }
        for (auto it = c.cbegin(); it != c.cend(); ++it)
            if (m_counts.contains(it.key()) && m_counts.value(it.key()) != it.value())
                Q_EMIT folderChanged(it.key());
        m_counts = c;
        QStringList line;
        for (auto it = c.cbegin(); it != c.cend(); ++it)
            line << QStringLiteral("%1 %2/%3").arg(it.key()).arg(it.value().toMap().value(QStringLiteral("unseen")).toInt())
                                                 .arg(it.value().toMap().value(QStringLiteral("total")).toInt());
        courierLog("[courier] Gmail numbers (unread/all): %s", qPrintable(line.join(QStringLiteral(", "))));
        Q_EMIT countsChanged();
    });
    connect(m_counter, &CountsWorker::failed, this, [this](const QString &why, bool authFailed) {
        m_counting = false;
        if (authFailed) m_access.clear();          // next count refreshes the token first
        courierLog("[courier] folder count failed: %s", qPrintable(why));
    });
    m_countsThread->start();

    // Inbox pushed to us (IMAP IDLE), on its own thread and connection.
    m_idleThread = new QThread(this);
    m_idler = new IdleWorker;
    m_idler->moveToThread(m_idleThread);
    connect(m_idleThread, &QThread::finished, m_idler, &QObject::deleteLater);
    connect(this, &GoogleLink::watchInbox, m_idler, &IdleWorker::watch);
    connect(m_idler, &IdleWorker::inboxChanged, this, [this] {
        courierLog("[courier] Gmail says the Inbox changed");
        countsSoon(0);
        Q_EMIT folderChanged(QStringLiteral("inbox"));
    });
    connect(m_idler, &IdleWorker::ended, this, [this](const QString &why, bool authFailed) {
        m_watching = false;
        if (m_idler->stop) return;
        if (authFailed) m_access.clear();
        courierLog("[courier] Inbox watch ended (%s) — resuming", qPrintable(why));
        QTimer::singleShot(why.isEmpty() ? 1000 : 15000, this, &GoogleLink::startWatching);
    });
    m_idleThread->start();
}

GoogleLink::~GoogleLink()
{
    m_idler->stop = true;
    m_idleThread->quit();
    m_idleThread->wait(5000);
    QMetaObject::invokeMethod(m_counter, &CountsWorker::shutdown, Qt::BlockingQueuedConnection);
    m_countsThread->quit();
    m_countsThread->wait(5000);
}

void GoogleLink::setMailEngine(QObject *e)
{
    if (m_engine == e) return;
    m_engine = e;
    Q_EMIT mailEngineChanged();
    // Let the window and the engine settle first.
    QTimer::singleShot(3000, this, &GoogleLink::autoStep);
}

QString GoogleLink::lastSync() const
{
    return m_lastSync.isValid() ? m_lastSync.toLocalTime().toString(QStringLiteral("d MMM, h:mm ap"))
                                : QString();
}

QStringList GoogleLink::missing() const
{
    QStringList out;
    if (!connected()) return out;
    for (const Scope &s : kScopes)
        if (!m_granted.contains(QLatin1String(s.url))) out << QLatin1String(s.name);
    return out;
}

void GoogleLink::setGranted(const QString &scope)
{
    const QStringList g = scope.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (g.isEmpty() || g == m_granted) return;
    m_granted = g;
    saveState();
    Q_EMIT stateChanged();
}

// ── persisted state ────────────────────────────────────────────────────────

void GoogleLink::loadClient()
{
    // Your own Google project's desktop sign-in (the client_secret_….json Google
    // Cloud gives you) — its switches (People API, Calendar API) are yours to
    // turn on. Per person first, then one for the whole machine; Hummingbird's
    // built-in client only if neither exists.
    const bool was = configured();
    for (const QString &path : { configDir() + QStringLiteral("google-client.json"),
                                 QStringLiteral("/etc/ncde/hummingbird-google-client.json") }) {
        QJsonObject o = readJson(path);
        for (const char *wrap : {"installed", "web"})
            if (o.value(QLatin1String(wrap)).isObject()) o = o.value(QLatin1String(wrap)).toObject();
        const QString id = o.value(QStringLiteral("client_id")).toString().trimmed();
        const QString secret = o.value(QStringLiteral("client_secret")).toString().trimmed();
        if (!id.isEmpty() && !secret.isEmpty()) { m_clientId = id; m_clientSecret = secret; break; }
    }
    if (m_clientId.isEmpty() || m_clientSecret.isEmpty())
        embeddedClient(&m_clientId, &m_clientSecret);
    if (was != configured()) Q_EMIT stateChanged();
}

void GoogleLink::loadState()
{
    const QJsonObject o = readJson(configDir() + QStringLiteral("google-link.json"));
    m_email = o.value(QStringLiteral("email")).toString();
    m_name = o.value(QStringLiteral("name")).toString();
    m_autoPrompted = o.value(QStringLiteral("autoPrompted")).toBool();
    m_askedFor = o.value(QStringLiteral("askedFor")).toString();
    m_granted = o.value(QStringLiteral("granted")).toString().split(QLatin1Char(' '), Qt::SkipEmptyParts);
    m_enableAskedAt = QDateTime::fromString(o.value(QStringLiteral("enableAskedAt")).toString(), Qt::ISODate);
    const QString client = o.value(QStringLiteral("client")).toString();
    if (!m_email.isEmpty() && client != m_clientId) {
        // The saved Google sign-in was made with a different app (client):
        // Google won't renew it for this one, so ask once, fresh.
        m_email.clear();
        m_granted.clear();
        m_autoPrompted = false;
        m_askedFor.clear();
        m_enableAskedAt = {};
    }
}

void GoogleLink::saveState()
{
    QJsonObject o;
    o.insert(QStringLiteral("email"), m_email);
    o.insert(QStringLiteral("name"), m_name);
    o.insert(QStringLiteral("autoPrompted"), m_autoPrompted);
    o.insert(QStringLiteral("askedFor"), m_askedFor);
    o.insert(QStringLiteral("client"), m_clientId);
    o.insert(QStringLiteral("granted"), m_granted.join(QLatin1Char(' ')));
    if (m_enableAskedAt.isValid())
        o.insert(QStringLiteral("enableAskedAt"), m_enableAskedAt.toString(Qt::ISODate));
    writePrivate(configDir() + QStringLiteral("google-link.json"), QJsonDocument(o).toJson());
}

void GoogleLink::loadCache()
{
    const QJsonObject o = readJson(configDir() + QStringLiteral("google-contacts.json"));
    if (m_email.isEmpty() || o.value(QStringLiteral("account")).toString() != m_email) return;
    m_contacts = o.value(QStringLiteral("contacts")).toArray().toVariantList();
    m_lastSync = QDateTime::fromString(o.value(QStringLiteral("synced")).toString(), Qt::ISODate);
}

void GoogleLink::saveCache()
{
    QJsonObject o;
    o.insert(QStringLiteral("account"), m_email);
    o.insert(QStringLiteral("synced"), m_lastSync.toString(Qt::ISODate));
    o.insert(QStringLiteral("contacts"), QJsonArray::fromVariantList(m_contacts));
    writePrivate(configDir() + QStringLiteral("google-contacts.json"), QJsonDocument(o).toJson());
}

void GoogleLink::setBusy(bool b, const QString &status)
{
    m_busy = b;
    if (!status.isNull()) m_status = status;
    Q_EMIT stateChanged();
}

void GoogleLink::fail(const QString &text)
{
    setBusy(false, text);
    Q_EMIT message(QStringLiteral("⚠ ") + text);
}

// ── what happens on its own ────────────────────────────────────────────────

QString GoogleLink::engineEmail() const
{
    return m_engine ? m_engine->property("accountEmail").toString() : QString();
}

bool GoogleLink::engineIsGoogle() const
{
    const QString em = engineEmail().toLower();
    return em.endsWith(QLatin1String("@gmail.com")) || em.endsWith(QLatin1String("@googlemail.com"));
}

bool GoogleLink::sameAccountAsMail() const
{
    return connected() && engineEmail().compare(m_email, Qt::CaseInsensitive) == 0;
}

void GoogleLink::autoStep()
{
    if (qEnvironmentVariableIsSet("NCDE_COURIER_DEBUG")) courierLog("[courier] autoStep %p", (void*)this);
    if (engineEmail().isEmpty()) return;                 // mail not set up yet
    if (connected()) {
        if (m_granted.isEmpty()) {         // older sign-in: ask Google what it covers first
            withToken([this](const QString &) { if (!m_granted.isEmpty()) autoStep(); },
                      [](const QString &why) { courierLog("[courier] %s", qPrintable(why)); });
            return;
        }
        m_countsTimer->start();
        countsSoon(0);
        startWatching();
        // Something Hummingbird needs wasn't granted: open Google's page by
        // itself — once for each new gap, so a person is never nagged.
        const QString gap = missing().join(QStringLiteral(", "));
        if (!gap.isEmpty() && gap != m_askedFor && !m_server) {
            m_askedFor = gap;
            saveState();
            Q_EMIT message(QStringLiteral("Google still needs your OK for: %1 — opening Google. Tick every box, then Continue.").arg(gap));
            startFlow(Flow::Link);
            return;
        }
        m_contactsTimer->start();
        if (m_granted.contains(QLatin1String(kContactsScope))
            && (!m_lastSync.isValid() || m_lastSync.secsTo(QDateTime::currentDateTimeUtc()) > kContactsEverySec))
            syncContacts();
        return;
    }
    if (!configured() || !engineIsGoogle() || m_autoPrompted) return;
    // Once per machine; after that the Address Book's button does it.
    m_autoPrompted = true;
    saveState();
    Q_EMIT message(QStringLiteral("One-time step: let Hummingbird show your Gmail contacts — opening Google…"));
    startFlow(Flow::Link);
}

// ── sign-in (both flows share the loopback + PKCE machinery) ───────────────

void GoogleLink::signIn()
{
    startFlow(Flow::Link);
}

void GoogleLink::startFlow(Flow flow)
{
    loadClient();
    if (!configured()) {
        fail(QStringLiteral("Could not find Hummingbird's Google app details"));
        return;
    }
    if (m_server) {
        Q_EMIT message(QStringLiteral("Google is already waiting in your browser"));
        return;
    }
    m_flow = flow;
    m_server = new QTcpServer(this);
    if (!m_server->listen(QHostAddress::LocalHost, 0)) {
        const QString e = m_server->errorString();
        m_server->deleteLater();
        m_server = nullptr;
        fail(QStringLiteral("Could not start the sign-in listener: ") + e);
        return;
    }
    connect(m_server, &QTcpServer::newConnection, this, &GoogleLink::onCallback);

    m_verifier = randomString(64);
    m_state = randomString(24);
    m_redirect = QStringLiteral("http://127.0.0.1:%1/callback").arg(m_server->serverPort());
    const QByteArray challenge = QCryptographicHash::hash(m_verifier.toLatin1(), QCryptographicHash::Sha256)
                                     .toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);

    QUrlQuery q;
    q.addQueryItem(QStringLiteral("client_id"), m_clientId);
    q.addQueryItem(QStringLiteral("redirect_uri"), m_redirect);
    q.addQueryItem(QStringLiteral("response_type"), QStringLiteral("code"));
    if (flow == Flow::Link) {
        QStringList scopes{QStringLiteral("openid"), QStringLiteral("email"), QStringLiteral("profile")};
        for (const Scope &s : kScopes) scopes << QLatin1String(s.url);
        q.addQueryItem(QStringLiteral("scope"), scopes.join(QLatin1Char(' ')));
        q.addQueryItem(QStringLiteral("access_type"), QStringLiteral("offline"));
        q.addQueryItem(QStringLiteral("prompt"), QStringLiteral("consent"));
    } else {
        q.addQueryItem(QStringLiteral("scope"), QStringLiteral("openid email %1").arg(QLatin1String(kCloudScope)));
        q.addQueryItem(QStringLiteral("access_type"), QStringLiteral("online"));
    }
    q.addQueryItem(QStringLiteral("include_granted_scopes"), QStringLiteral("true"));
    q.addQueryItem(QStringLiteral("code_challenge"), QString::fromLatin1(challenge));
    q.addQueryItem(QStringLiteral("code_challenge_method"), QStringLiteral("S256"));
    q.addQueryItem(QStringLiteral("state"), m_state);
    const QString hint = m_email.isEmpty() ? engineEmail() : m_email;
    if (!hint.isEmpty()) q.addQueryItem(QStringLiteral("login_hint"), hint);
    QUrl url{QLatin1String(kAuthUrl)};
    url.setQuery(q);
    const QString link = QString::fromLatin1(url.toEncoded());

    // Same browser order as Hummingbird's own sign-in.
    bool launched = false;
    for (const char *b : {"chromium", "firefox", "xdg-open"}) {
        const QString exe = QStandardPaths::findExecutable(QLatin1String(b));
        if (!exe.isEmpty() && QProcess::startDetached(exe, {link})) { launched = true; break; }
    }
    if (!launched) {
        m_server->close();
        m_server->deleteLater();
        m_server = nullptr;
        fail(QStringLiteral("Could not open a browser for Google"));
        return;
    }

    if (!m_flowTimeout) {
        m_flowTimeout = new QTimer(this);
        m_flowTimeout->setSingleShot(true);
        connect(m_flowTimeout, &QTimer::timeout, this, [this] {
            if (!m_server) return;
            m_server->close();
            m_server->deleteLater();
            m_server = nullptr;
            fail(QStringLiteral("Google didn't answer — tap “Connect Google” in the Address Book to try again"));
        });
    }
    m_flowTimeout->start(5 * 60 * 1000);
    setBusy(true, flow == Flow::Link ? QStringLiteral("Waiting for Google in your browser…")
                                     : QStringLiteral("Waiting for Google to switch contacts on…"));
}

void GoogleLink::onCallback()
{
    while (m_server && m_server->hasPendingConnections()) {
        QTcpSocket *s = m_server->nextPendingConnection();
        connect(s, &QTcpSocket::disconnected, s, &QObject::deleteLater);
        auto *buf = new QByteArray;
        connect(s, &QObject::destroyed, [buf] { delete buf; });
        connect(s, &QTcpSocket::readyRead, this, [this, s, buf] {
            *buf += s->readAll();
            if (!buf->contains("\r\n\r\n")) {
                if (buf->size() > 16384) s->abort();
                return;
            }
            const QList<QByteArray> first = buf->left(buf->indexOf("\r\n")).split(' ');
            const QUrl u(QString::fromLatin1(first.value(1)));
            auto reply = [s](const QByteArray &status, const QString &body) {
                const QByteArray html =
                    "<!doctype html><meta charset=utf-8><title>Hummingbird Courier</title>"
                    "<body style=\"font:18px Georgia,serif;background:#f4ead6;color:#3a2418;"
                    "display:flex;align-items:center;justify-content:center;height:90vh\">"
                    "<p>" + body.toHtmlEscaped().toUtf8() + "</p></body>";
                s->write("HTTP/1.1 " + status + "\r\nContent-Type: text/html; charset=utf-8\r\n"
                         "Content-Length: " + QByteArray::number(html.size()) +
                         "\r\nConnection: close\r\n\r\n" + html);
                s->flush();
                s->disconnectFromHost();
            };
            if (u.path() != QLatin1String("/callback")) {
                reply("404 Not Found", QStringLiteral("Not here."));
                return;
            }
            const QUrlQuery q(u);
            const QString code = q.queryItemValue(QStringLiteral("code"), QUrl::FullyDecoded);
            const QString error = q.queryItemValue(QStringLiteral("error"));
            if (q.queryItemValue(QStringLiteral("state")) != m_state) {
                reply("400 Bad Request", QStringLiteral("This sign-in link is stale. Go back to Hummingbird and try again."));
                return;
            }
            if (m_flowTimeout) m_flowTimeout->stop();
            if (m_server) { m_server->close(); m_server->deleteLater(); m_server = nullptr; }
            if (code.isEmpty()) {
                reply("200 OK", QStringLiteral("Cancelled. You can close this tab."));
                fail(error == QLatin1String("access_denied")
                         ? QStringLiteral("Google step cancelled — tap “Connect Google” in the Address Book when you're ready")
                         : QStringLiteral("Google did not return a sign-in code (%1)").arg(error));
                return;
            }
            reply("200 OK", QStringLiteral("Got it — Hummingbird is finishing up. You can close this tab."));
            exchangeCode(code);
        });
    }
}

void GoogleLink::exchangeCode(const QString &code)
{
    QUrlQuery form;
    form.addQueryItem(QStringLiteral("code"), code);
    form.addQueryItem(QStringLiteral("client_id"), m_clientId);
    form.addQueryItem(QStringLiteral("client_secret"), m_clientSecret);
    form.addQueryItem(QStringLiteral("redirect_uri"), m_redirect);
    form.addQueryItem(QStringLiteral("grant_type"), QStringLiteral("authorization_code"));
    form.addQueryItem(QStringLiteral("code_verifier"), m_verifier);
    QNetworkRequest r = request(QLatin1String(kTokenUrl));
    r.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
    QNetworkReply *rep = m_net->post(r, form.toString(QUrl::FullyEncoded).toUtf8());
    connect(rep, &QNetworkReply::finished, this, [this, rep] {
        rep->deleteLater();
        const QByteArray body = rep->readAll();
        const int http = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QJsonObject o = QJsonDocument::fromJson(body).object();
        const QString access = o.value(QStringLiteral("access_token")).toString();
        if (http != 200 || access.isEmpty()) {
            fail(QStringLiteral("Google sign-in failed: ") + googleError(body, http));
            return;
        }
        if (m_flow == Flow::EnableApis) { enableApis(access); return; }
        const QString refresh = o.value(QStringLiteral("refresh_token")).toString();
        if (refresh.isEmpty()) {
            fail(QStringLiteral("Google did not return a lasting sign-in — remove Hummingbird at "
                                "myaccount.google.com → Security → Third-party access, then try again"));
            return;
        }
        finishLink(access, refresh, o.value(QStringLiteral("expires_in")).toInt(3600),
                   o.value(QStringLiteral("scope")).toString());
    });
}

void GoogleLink::finishLink(const QString &access, const QString &refresh, int expiresIn,
                            const QString &grantedScope)
{
    QNetworkRequest r = request(QLatin1String(kUserInfoUrl));
    r.setRawHeader("Authorization", "Bearer " + access.toUtf8());
    QNetworkReply *rep = m_net->get(r);
    connect(rep, &QNetworkReply::finished, this, [=, this] {
        rep->deleteLater();
        const QByteArray body = rep->readAll();
        const int http = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QJsonObject o = QJsonDocument::fromJson(body).object();
        const QString email = o.value(QStringLiteral("email")).toString();
        if (http != 200 || email.isEmpty()) {
            fail(QStringLiteral("Could not read your Google address: ") + googleError(body, http));
            return;
        }
        std::string err;
        if (!m_email.isEmpty() && m_email != email)
            courier_keyring::clear(m_email.toStdString(), nullptr);
        if (!courier_keyring::store(email.toStdString(), refresh.toStdString(), &err))
            Q_EMIT message(QStringLiteral("⚠ Keyring refused to save the Google sign-in (%1)")
                               .arg(QString::fromStdString(err)));
        if (m_email != email) { m_contacts.clear(); m_lastSync = {}; Q_EMIT contactsChanged(); }
        m_email = email;
        m_name = o.value(QStringLiteral("name")).toString();
        m_access = access;
        m_accessExpiry = QDateTime::currentDateTimeUtc().addSecs(expiresIn);
        m_granted = grantedScope.split(QLatin1Char(' '), Qt::SkipEmptyParts);
        saveState();
        courierLog("[courier] Google granted: %s", qPrintable(grantedScope));

        const QStringList miss = missing();
        if (!miss.isEmpty())
            fail(QStringLiteral("Google left out: %1 — that box wasn't ticked on Google's page. "
                                "Tap “Try again” and tick it.").arg(miss.join(QStringLiteral(", "))));
        else
            setBusy(false, QStringLiteral("Connected as ") + email);
        if (!sameAccountAsMail())
            Q_EMIT message(QStringLiteral("⚠ Google signed in as %1, but Hummingbird's mail is %2")
                               .arg(email, engineEmail()));
        autoStep();
    });
}

// ── an API switched off for Hummingbird's Google project: owner turns it on ─

void GoogleLink::enableApis(const QString &access)
{
    setBusy(true, QStringLiteral("Switching Gmail contacts on for Hummingbird…"));
    const QString project = m_clientId.section(QLatin1Char('-'), 0, 0);
    QNetworkRequest r = request(QStringLiteral(
        "https://serviceusage.googleapis.com/v1/projects/%1/services:batchEnable").arg(project));
    r.setRawHeader("Authorization", "Bearer " + access.toUtf8());
    r.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    QNetworkReply *rep = m_net->post(r, QByteArray(
        "{\"serviceIds\":[\"people.googleapis.com\",\"calendar-json.googleapis.com\"]}"));
    connect(rep, &QNetworkReply::finished, this, [this, rep, access] {
        rep->deleteLater();
        const QByteArray body = rep->readAll();
        const int http = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        courierLog("[courier] enable APIs: HTTP %d", http);
        if (http == 403) {
            fail(QStringLiteral("Only the owner of Hummingbird's Google project can switch contacts on"));
            return;
        }
        if (http != 200) {
            fail(QStringLiteral("Could not switch contacts on: ") + googleError(body, http));
            return;
        }
        const QJsonObject op = QJsonDocument::fromJson(body).object();
        if (op.value(QStringLiteral("done")).toBool() || op.value(QStringLiteral("name")).toString().isEmpty()) {
            m_enableRetries = 6;
            syncContacts();
        } else {
            pollOperation(access, op.value(QStringLiteral("name")).toString(), 20);
        }
    });
}

void GoogleLink::pollOperation(const QString &access, const QString &name, int triesLeft)
{
    QTimer::singleShot(3000, this, [=, this] {
        QNetworkRequest r = request(QStringLiteral("https://serviceusage.googleapis.com/v1/") + name);
        r.setRawHeader("Authorization", "Bearer " + access.toUtf8());
        QNetworkReply *rep = m_net->get(r);
        connect(rep, &QNetworkReply::finished, this, [=, this] {
            rep->deleteLater();
            const QJsonObject op = QJsonDocument::fromJson(rep->readAll()).object();
            if (op.value(QStringLiteral("done")).toBool() || triesLeft <= 1) {
                m_enableRetries = 6;           // Google takes a little while to spread it
                syncContacts();
            } else {
                pollOperation(access, name, triesLeft - 1);
            }
        });
    });
}

// ── tokens ─────────────────────────────────────────────────────────────────

void GoogleLink::refreshAccess(const QString &refreshToken,
                               std::function<void(const QString &, int, const QString &)> ok, ErrorFn bad)
{
    QUrlQuery form;
    form.addQueryItem(QStringLiteral("client_id"), m_clientId);
    form.addQueryItem(QStringLiteral("client_secret"), m_clientSecret);
    form.addQueryItem(QStringLiteral("refresh_token"), refreshToken);
    form.addQueryItem(QStringLiteral("grant_type"), QStringLiteral("refresh_token"));
    QNetworkRequest r = request(QLatin1String(kTokenUrl));
    r.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
    QNetworkReply *rep = m_net->post(r, form.toString(QUrl::FullyEncoded).toUtf8());
    connect(rep, &QNetworkReply::finished, this, [rep, ok, bad] {
        rep->deleteLater();
        const QByteArray body = rep->readAll();
        const int http = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QJsonObject o = QJsonDocument::fromJson(body).object();
        const QString access = o.value(QStringLiteral("access_token")).toString();
        if (http == 200 && !access.isEmpty()) {
            ok(access, o.value(QStringLiteral("expires_in")).toInt(3600), o.value(QStringLiteral("scope")).toString());
            return;
        }
        bad(o.value(QStringLiteral("error")).toString() == QLatin1String("invalid_grant")
                ? QStringLiteral("invalid_grant") : googleError(body, http));
    });
}

void GoogleLink::withToken(TokenFn fn, ErrorFn onError)
{
    auto bad = [this, onError](const QString &why) { if (onError) onError(why); else fail(why); };
    if (!m_access.isEmpty() && m_accessExpiry > QDateTime::currentDateTimeUtc().addSecs(90)) { fn(m_access); return; }
    loadClient();
    std::string err;
    const QString refresh = QString::fromStdString(courier_keyring::lookup(m_email.toStdString(), &err));
    if (refresh.isEmpty()) {
        bad(err.empty() ? QStringLiteral("Google sign-in is missing — tap “Connect Google” in the Address Book")
                        : QStringLiteral("Keyring is locked or unavailable (%1)").arg(QString::fromStdString(err)));
        return;
    }
    refreshAccess(refresh, [this, fn](const QString &access, int expires, const QString &scope) {
        m_access = access;
        m_accessExpiry = QDateTime::currentDateTimeUtc().addSecs(expires);
        setGranted(scope);                 // Google says what this sign-in covers every time
        fn(access);
    }, [this, bad](const QString &why) {
        if (why == QLatin1String("invalid_grant")) {
            courier_keyring::clear(m_email.toStdString(), nullptr);
            m_email.clear();
            m_granted.clear();
            m_autoPrompted = false;            // so the next step opens Google by itself
            m_askedFor.clear();
            saveState();
            Q_EMIT stateChanged();
            bad(QStringLiteral("Google sign-in expired — opening Google to sign in again"));
            QTimer::singleShot(0, this, &GoogleLink::autoStep);
            return;
        }
        bad(QStringLiteral("Could not refresh Google access: ") + why);
    });
}

// ── folder numbers ─────────────────────────────────────────────────────────

void GoogleLink::countsSoon(int delayMs)
{
    if (qEnvironmentVariableIsSet("NCDE_COURIER_DEBUG")) courierLog("[courier] countsSoon(%d)", delayMs);
    if (!sameAccountAsMail() || !m_granted.contains(QLatin1String(kMailScope))) return;
    // Keep an already-scheduled count if it comes sooner; otherwise bring it forward.
    if (m_countsSoon->isActive() && m_countsSoon->remainingTime() <= delayMs) return;
    m_countsSoon->start(qMax(0, delayMs));
}

void GoogleLink::startWatching()
{
    if (m_watching || !sameAccountAsMail() || !m_granted.contains(QLatin1String(kMailScope))) return;
    m_watching = true;
    m_idler->stop = false;
    withToken([this](const QString &access) { Q_EMIT watchInbox(m_email, access); },
              [this](const QString &why) {
                  m_watching = false;
                  courierLog("[courier] Inbox watch waiting: %s", qPrintable(why));
                  QTimer::singleShot(60000, this, &GoogleLink::startWatching);
              });
}

void GoogleLink::countNow()
{
    if (m_counting || !sameAccountAsMail() || !m_granted.contains(QLatin1String(kMailScope))) return;
    if (qEnvironmentVariableIsSet("NCDE_COURIER_DEBUG")) courierLog("[courier] countNow %p", (void*)this);
    m_counting = true;
    m_pollStartedAt = QDateTime::currentDateTimeUtc();
    withToken([this](const QString &access) { Q_EMIT pollCounts(m_email, access); },
              [this](const QString &why) {
                  m_counting = false;
                  courierLog("[courier] folder count skipped: %s", qPrintable(why));
              });
}

void GoogleLink::adjustCount(const QString &folderId, int dUnseen, int dTotal)
{
    if (!m_counts.contains(folderId)) return;
    QVariantMap one = m_counts.value(folderId).toMap();
    one.insert(QStringLiteral("unseen"), qMax(0, one.value(QStringLiteral("unseen")).toInt() + dUnseen));
    one.insert(QStringLiteral("total"),  qMax(0, one.value(QStringLiteral("total")).toInt() + dTotal));
    m_counts.insert(folderId, one);
    m_adjustedAt = QDateTime::currentDateTimeUtc();
    Q_EMIT countsChanged();
}

// ── contacts ───────────────────────────────────────────────────────────────

void GoogleLink::syncContacts()
{
    if (!connected()) { signIn(); return; }
    if (m_server) return;                  // a Google page is already open
    if (!m_granted.contains(QLatin1String(kContactsScope))) {
        fail(QStringLiteral("Google left out Contacts — tap “Try again” and tick the Contacts box"));
        return;
    }
    setBusy(true, QStringLiteral("Fetching your Gmail contacts…"));
    withToken([this](const QString &access) {
        const QString conn = QStringLiteral(
            "https://people.googleapis.com/v1/people/me/connections"
            "?personFields=names,emailAddresses,phoneNumbers&pageSize=1000&sortOrder=FIRST_NAME_ASCENDING");
        fetchPages(access, conn, QStringLiteral("connections"), {}, [this, access](Page saved) {
            if (saved.disabled) {
                courierLog("[courier] People API is switched off for Hummingbird's project");
                if (m_enableRetries > 0) {           // just switched on; Google still spreading it
                    --m_enableRetries;
                    setBusy(true, QStringLiteral("Google is switching contacts on…"));
                    QTimer::singleShot(20000, this, &GoogleLink::syncContacts);
                    return;
                }
                const QDateTime now = QDateTime::currentDateTimeUtc();
                if (!m_enableAskedAt.isValid() || m_enableAskedAt.secsTo(now) > 3600) {
                    m_enableAskedAt = now;
                    saveState();
                    Q_EMIT message(QStringLiteral("One more Google step: switch Gmail contacts on for Hummingbird — opening Google…"));
                    startFlow(Flow::EnableApis);
                    return;
                }
                fail(QStringLiteral("Gmail contacts are switched off for Hummingbird's Google project"));
                return;
            }
            if (!saved.error.isEmpty()) { fail(saved.error); return; }
            m_enableRetries = 0;
            auto finish = [this, saved](const Page &more) {
                // Saved contacts first, then Gmail's "Other contacts" (people you've written to).
                QVariantList all;
                QSet<QString> seen;
                auto add = [&](const QVariantList &people, const QString &src) {
                    for (const QVariant &v : people) {
                        const QVariantMap e = personEntry(QJsonObject::fromVariantMap(v.toMap()), src);
                        if (e.isEmpty()) continue;
                        const QString em = e.value(QStringLiteral("em")).toString().toLower();
                        const QString key = em.isEmpty()
                            ? e.value(QStringLiteral("nm")).toString().toLower() + '|' + e.value(QStringLiteral("tel")).toString()
                            : em;
                        if (seen.contains(key)) continue;
                        seen.insert(key);
                        all << e;
                    }
                };
                add(saved.people, QStringLiteral("google"));
                add(more.people, QStringLiteral("google-other"));
                QCollator col;
                col.setCaseSensitivity(Qt::CaseInsensitive);
                col.setNumericMode(true);
                std::sort(all.begin(), all.end(), [&](const QVariant &a, const QVariant &b) {
                    return col.compare(a.toMap().value(QStringLiteral("nm")).toString(),
                                       b.toMap().value(QStringLiteral("nm")).toString()) < 0;
                });
                courierLog("[courier] contacts: %lld saved + %lld other → %lld in the Address Book",
                      qint64(saved.people.size()), qint64(more.people.size()), qint64(all.size()));
                m_contacts = all;
                m_lastSync = QDateTime::currentDateTimeUtc();
                saveCache();
                Q_EMIT contactsChanged();
                setBusy(false, more.error.isEmpty() ? QString()
                                                    : QStringLiteral("Other contacts: ") + more.error);
            };
            if (!m_granted.contains(QLatin1String(kOtherScope))) { finish(Page{}); return; }
            const QString other = QStringLiteral(
                "https://people.googleapis.com/v1/otherContacts"
                "?readMask=names,emailAddresses,phoneNumbers&pageSize=1000");
            fetchPages(access, other, QStringLiteral("otherContacts"), {}, finish);
        });
    });
}

void GoogleLink::fetchPages(const QString &access, const QString &url, const QString &field,
                            QVariantList acc, std::function<void(Page)> done)
{
    QNetworkRequest r = request(url);
    r.setRawHeader("Authorization", "Bearer " + access.toUtf8());
    QNetworkReply *rep = m_net->get(r);
    connect(rep, &QNetworkReply::finished, this, [=, this]() mutable {
        rep->deleteLater();
        const QByteArray body = rep->readAll();
        const int http = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (http != 200) {
            Page p;
            p.error = googleError(body, http, &p.disabled, &p.scopeMissing);
            courierLog("[courier] %s: HTTP %d %s", qPrintable(field), http, qPrintable(p.error));
            if (http == 401) m_access.clear();
            if (p.scopeMissing)
                p.error = QStringLiteral("Google left out Contacts — tap “Try again” and tick the Contacts box");
            else if (http == 0)
                p.error = QStringLiteral("Could not reach Google: ") + rep->errorString();
            p.people = acc;
            done(p);
            return;
        }
        const QJsonObject o = QJsonDocument::fromJson(body).object();
        acc += o.value(field).toArray().toVariantList();
        const QString next = o.value(QStringLiteral("nextPageToken")).toString();
        if (next.isEmpty() || acc.size() > 50000) {
            Page p;
            p.people = acc;
            done(p);
            return;
        }
        QUrl u(url);
        QUrlQuery q(u);
        q.removeAllQueryItems(QStringLiteral("pageToken"));
        q.addQueryItem(QStringLiteral("pageToken"), next);
        u.setQuery(q);
        fetchPages(access, u.toString(), field, acc, done);
    });
}

void GoogleLink::forget()
{
    if (!m_email.isEmpty()) courier_keyring::clear(m_email.toStdString(), nullptr);
    m_email.clear();
    m_name.clear();
    m_access.clear();
    m_granted.clear();
    m_contacts.clear();
    m_counts.clear();
    m_lastSync = {};
    m_countsTimer->stop();
    m_contactsTimer->stop();
    m_idler->stop = true;
    saveState();
    QFile::remove(configDir() + QStringLiteral("google-contacts.json"));
    Q_EMIT contactsChanged();
    Q_EMIT countsChanged();
    setBusy(false, QString());
}
