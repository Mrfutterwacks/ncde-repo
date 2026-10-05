// Launcher — app/exec launcher, session commands, logout
// Rebuilt from oracle: Launcher::launchExec, launch, systemCommand, launchWithFiles, homePath, logout
// Spec: ncde-architecture.md §5 (Launcher is a QML context property)
// DEFECTS FIXED vs oracle: None — oracle implementation is clean

#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

class Launcher : public QObject
{
    Q_OBJECT
// ---- GENERATED: tools/gen_header.py Launcher ----

public:
    Q_INVOKABLE void launchExec(const QString &cmd);
    Q_INVOKABLE void launch(const QString &cmd);
    Q_INVOKABLE void systemCommand(const QString &cmd);
    Q_INVOKABLE void launchWithFiles(const QString &exec, const QVariantList &files);
    Q_INVOKABLE QString homePath();
    Q_INVOKABLE void logout();

// ---- END GENERATED ----

public:
    explicit Launcher(QObject *parent = nullptr);
    ~Launcher() override = default;
};