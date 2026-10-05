// Launcher.cpp — implementation
// Rebuilt from oracle: Launcher::launchExec, launch, systemCommand, launchWithFiles, homePath, logout
// Uses QProcess::startDetached for all launches (never blocks GUI thread)
//
// DEFECTS FIXED vs oracle:
// 1. Command splitting. The oracle reused QtPrivate::splitCommand, a Qt 6 internal that is not part
//    of the public API and is absent from this Qt (6.11) headers, so the rebuild could not compile.
//    Replaced with a local QRegularExpression splitter implementing the same shell-like quoting
//    rules (single quotes, double quotes, backslash escapes, whitespace separation) so a command
//    with quoted arguments still launches correctly.

#include "Launcher.h"

#include <QCoreApplication>
#include <QDir>
#include <QList>
#include <QProcess>
#include <QRegularExpression>
#include <QString>

namespace {

// Split a command line into argv the way a shell would for the quoting the shell QML can produce.
// Handles: whitespace separation, 'single quotes' (literal), "double quotes" (backslash escapes for
// " \ $ `), and a backslash escape outside quotes. An unterminated quote takes the rest of the
// string rather than discarding it.
QStringList splitCommandLine(const QString &cmd)
{
    QStringList out;
    QString cur;
    bool inArg = false;
    int i = 0;
    const int n = cmd.size();

    auto flush = [&] {
        if (inArg) {
            out.append(cur);
            cur.clear();
            inArg = false;
        }
    };

    while (i < n) {
        const QChar c = cmd.at(i);

        if (c.isSpace()) {
            flush();
            ++i;
            continue;
        }

        inArg = true;

        if (c == QLatin1Char('\'')) {
            ++i; // skip the opening quote
            while (i < n && cmd.at(i) != QLatin1Char('\''))
                cur.append(cmd.at(i++));
            if (i < n)
                ++i; // skip the closing quote
            continue;
        }

        if (c == QLatin1Char('"')) {
            ++i; // skip the opening quote
            while (i < n && cmd.at(i) != QLatin1Char('"')) {
                if (cmd.at(i) == QLatin1Char('\\') && i + 1 < n) {
                    const QChar next = cmd.at(i + 1);
                    if (next == QLatin1Char('"') || next == QLatin1Char('\\')
                        || next == QLatin1Char('$') || next == QLatin1Char('`')) {
                        cur.append(next);
                        i += 2;
                        continue;
                    }
                }
                cur.append(cmd.at(i++));
            }
            if (i < n)
                ++i; // skip the closing quote
            continue;
        }

        if (c == QLatin1Char('\\') && i + 1 < n) {
            cur.append(cmd.at(i + 1));
            i += 2;
            continue;
        }

        cur.append(c);
        ++i;
    }

    flush();
    return out;
}

} // namespace

Launcher::Launcher(QObject *parent)
    : QObject(parent)
{
}

void Launcher::launchExec(const QString &cmd)
{
    const QString trimmed = cmd.trimmed();
    if (trimmed.isEmpty())
        return;

    QStringList parts = splitCommandLine(trimmed);
    if (parts.isEmpty())
        return;

    const QString program = parts.takeFirst();
    const QString workingDir;
    QProcess::startDetached(program, parts, workingDir);
}

void Launcher::launch(const QString &cmd)
{
    launchExec(cmd);
}

void Launcher::systemCommand(const QString &cmd)
{
    launchExec(cmd);
}

void Launcher::launchWithFiles(const QString &exec, const QVariantList &files)
{
    QStringList parts = splitCommandLine(exec);
    if (parts.isEmpty())
        return;

    const QString program = parts.takeFirst();

    for (const QVariant &file : files)
        parts.append(file.toString());

    const QString workingDir;
    QProcess::startDetached(program, parts, workingDir);
}

QString Launcher::homePath()
{
    return QDir::homePath();
}

void Launcher::logout()
{
    QCoreApplication::quit();
}
