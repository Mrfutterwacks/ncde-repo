// Lelan — per-component JSON config in ~/.config/ncde/<name>.json (Settings and QML read/write through it).
//
// Rebuilt from oracle: configDir, configPath, readConfig, writeConfig, loadConfig, saveConfig.
//
// DEFECTS FIXED vs oracle:
//  C1 loadConfig/saveConfig are callable from QML with any name; "../../x" read or wrote x.json anywhere in
//     the home directory. Names are now plain file names (no '/', no "..", not empty).
//  C2 saveConfig returned nothing to QML although the call can fail (disk full, read-only); it now returns
//     whether the file was written (the oracle's moc already declared bool).
#include "Lelan.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QtLogging>

QString Lelan::configDir()
{
    const QString dir = QDir::homePath() + QStringLiteral("/.config/ncde");
    QDir().mkpath(dir);
    return dir;
}

static bool plainName(const QString &name)
{
    return !name.isEmpty() && !name.contains(QLatin1Char('/')) && !name.contains(QLatin1String(".."));   // C1
}

QString Lelan::configPath(const QString &name)
{
    return configDir() + QLatin1Char('/') + name + QStringLiteral(".json");
}

QVariantMap Lelan::readConfig(const QString &name)
{
    if (!plainName(name))
        return {};
    QFile f(configPath(name));
    if (!f.open(QIODevice::ReadOnly))
        return {};
    return QJsonDocument::fromJson(f.readAll()).object().toVariantMap();
}

bool Lelan::writeConfig(const QString &name, const QVariantMap &data)
{
    if (!plainName(name)) {
        qWarning() << "[lelan] refused config name" << name;
        return false;
    }
    QSaveFile f(configPath(name));
    if (!f.open(QIODevice::WriteOnly))
        return false;
    f.write(QJsonDocument(QJsonObject::fromVariantMap(data)).toJson(QJsonDocument::Indented));
    return f.commit();
}

QVariantMap Lelan::loadConfig(const QString &name) { return readConfig(name); }
bool Lelan::saveConfig(const QString &name, const QVariantMap &data) { return writeConfig(name, data); }   // C2
