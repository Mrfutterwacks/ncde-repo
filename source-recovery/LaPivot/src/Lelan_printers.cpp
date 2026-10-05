// Lelan — CUPS printer inventory and explicitly requested queue changes.
// Rebuilt from oracle: refreshPrinters, printers, setDefaultPrinter, removePrinter.
// Spec: settings-tabs.md PrintersTab consumer; keep CUPS work asynchronous and argument-separated.
//
// DEFECTS FIXED vs oracle:
// 1. Printer discovery is nonblocking (lpstat runs in QProcess; no waitForFinished on the GUI thread).
// 2. Queue names are validated and always passed as distinct argv entries, never through a shell.
#include "Lelan.h"

#include <QProcess>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTimer>
#include <QtLogging>

#include <algorithm>
#include <memory>
#include <utility>

namespace {
const QRegularExpression kQueueName(QStringLiteral("^[A-Za-z0-9_.-]{1,127}$"));

void runPrinterCommand(QObject *owner, const QString &program, const QStringList &args,
                       std::function<void(bool, const QByteArray &, const QString &)> finished)
{
    auto *process = new QProcess(owner);
    process->setProgram(program);
    process->setArguments(args);
    process->setProcessChannelMode(QProcess::SeparateChannels);
    auto *timeout = new QTimer(process);
    timeout->setSingleShot(true);
    timeout->setInterval(5000);
    QObject::connect(timeout, &QTimer::timeout, process, [process] {
        process->terminate();
        QTimer::singleShot(500, process, [process] {
            if (process->state() != QProcess::NotRunning)
                process->kill();
        });
    });
    QObject::connect(process, &QProcess::started, timeout, qOverload<>(&QTimer::start));
    QObject::connect(process, &QProcess::errorOccurred, process,
                     [process, finished](QProcess::ProcessError error) mutable {
        if (error != QProcess::FailedToStart)
            return;
        finished(false, {}, process->errorString());
        process->deleteLater();
    });
    QObject::connect(process, qOverload<int, QProcess::ExitStatus>(&QProcess::finished),
                     process, [process, timeout, finished]
                     (int code, QProcess::ExitStatus status) mutable {
        timeout->stop();
        const QByteArray output = process->readAllStandardOutput();
        const QString error = QString::fromLocal8Bit(process->readAllStandardError()).trimmed();
        finished(status == QProcess::NormalExit && code == 0, output, error);
        process->deleteLater();
    });
    process->start();
}
} // namespace

QVariantList Lelan::printers() const { return m_printers; }

void Lelan::refreshPrinters()
{
    const QString lpstat = QStandardPaths::findExecutable(QStringLiteral("lpstat"));
    if (lpstat.isEmpty()) {
        if (!m_printers.isEmpty()) {
            m_printers.clear();
            emit printersChanged();
        }
        return;
    }

    const quint64 generation = ++m_printersGeneration;
    struct Results {
        QByteArray detail;
        QString defaultPrinter;
        int remaining = 2;
        bool detailOk = false;
    };
    auto results = std::make_shared<Results>();
    auto complete = [this, generation, results] {
        if (--results->remaining != 0 || generation != m_printersGeneration)
            return;
        if (!results->detailOk)
            return;
        QVariantList next;
        {
            const QString output = QString::fromLocal8Bit(results->detail);
            const QStringList lines = output.split(QLatin1Char('\n'));
            QVariantMap current;
            auto saveCurrent = [&] {
                if (!current.isEmpty()) {
                    current.insert(QStringLiteral("isDefault"),
                                   current.value(QStringLiteral("name")).toString() == results->defaultPrinter);
                    next.append(current);
                }
            };
            for (const QString &line : lines) {
                static const QRegularExpression head(
                    QStringLiteral("^printer\\s+(\\S+)\\s+is\\s+(.+?)(?:\\.|,|$)"));
                const auto match = head.match(line);
                if (match.hasMatch()) {
                    saveCurrent();
                    const QString rawStatus = match.captured(2).trimmed();
                    QString status = rawStatus;
                    if (rawStatus.contains(QLatin1String("disabled"), Qt::CaseInsensitive)
                        || rawStatus.contains(QLatin1String("stopped"), Qt::CaseInsensitive))
                        status = QStringLiteral("Error");
                    else if (rawStatus.contains(QLatin1String("printing"), Qt::CaseInsensitive))
                        status = QStringLiteral("Printing");
                    else
                        status = QStringLiteral("Ready");
                    current = {{QStringLiteral("name"), match.captured(1)},
                               {QStringLiteral("status"), status},
                               {QStringLiteral("location"), QString{}},
                               {QStringLiteral("model"), QString{}}};
                    continue;
                }
                const qsizetype colon = line.indexOf(QLatin1Char(':'));
                if (current.isEmpty() || colon < 0)
                    continue;
                const QString key = line.left(colon).trimmed();
                const QString value = line.mid(colon + 1).trimmed();
                if (key.compare(QLatin1String("Location"), Qt::CaseInsensitive) == 0)
                    current.insert(QStringLiteral("location"), value);
                else if (key.compare(QLatin1String("Description"), Qt::CaseInsensitive) == 0
                         || key.compare(QLatin1String("Model"), Qt::CaseInsensitive) == 0)
                    current.insert(QStringLiteral("model"), value);
            }
            saveCurrent();
        }
        if (next != m_printers) {
            m_printers = next;
            emit printersChanged();
        }
    };

    runPrinterCommand(this, lpstat, {QStringLiteral("-l"), QStringLiteral("-p")},
                      [results, complete](bool ok, const QByteArray &out, const QString &error) {
        results->detailOk = ok;
        results->detail = out;
        if (!ok && !error.isEmpty())
            qWarning() << "[lelan] lpstat printer list failed:" << error;
        complete();
    });
    runPrinterCommand(this, lpstat, {QStringLiteral("-d")},
                      [results, complete](bool ok, const QByteArray &out, const QString &) {
        if (ok) {
            const QString line = QString::fromLocal8Bit(out).trimmed();
            const QString prefix = QStringLiteral("system default destination:");
            if (line.startsWith(prefix, Qt::CaseInsensitive))
                results->defaultPrinter = line.mid(prefix.size()).trimmed();
        }
        complete();
    });
}

void Lelan::setDefaultPrinter(const QString &name)
{
    if (!kQueueName.match(name).hasMatch()) {
        qWarning() << "[lelan] refused invalid CUPS queue name";
        return;
    }
    const QString lpadmin = QStandardPaths::findExecutable(QStringLiteral("lpadmin"));
    if (lpadmin.isEmpty()) {
        qWarning() << "[lelan] lpadmin is not installed";
        return;
    }
    runPrinterCommand(this, lpadmin, {QStringLiteral("-d"), name},
                      [this](bool ok, const QByteArray &, const QString &error) {
        if (!ok)
            qWarning() << "[lelan] setting the default printer failed:" << error;
        else
            refreshPrinters();
    });
}

void Lelan::removePrinter(const QString &name)
{
    if (!kQueueName.match(name).hasMatch()) {
        qWarning() << "[lelan] refused invalid CUPS queue name";
        return;
    }
    const QString lpadmin = QStandardPaths::findExecutable(QStringLiteral("lpadmin"));
    if (lpadmin.isEmpty()) {
        qWarning() << "[lelan] lpadmin is not installed";
        return;
    }
    runPrinterCommand(this, lpadmin, {QStringLiteral("-x"), name},
                      [this](bool ok, const QByteArray &, const QString &error) {
        if (!ok)
            qWarning() << "[lelan] removing the printer failed:" << error;
        else
            refreshPrinters();
    });
}
