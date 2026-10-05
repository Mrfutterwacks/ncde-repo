// ncde_paths.h — where LaPivot's shipped assets (QML tree, helper scripts, avatars, wallpapers) live.
//
// The oracle hardcoded "/usr/share/ncde" (main(): QML base; Settings ctor and Lelan::setUserAvatar:
// "/usr/share/ncde/"). The rebuilt LaPivot is first installed BESIDE the current one as a test session
// ("NCDE L2", README RESUME item 4): its QML lives in /usr/share/ncde-l2/ while the old LaPivot keeps
// /usr/share/ncde/. Every asset path must therefore come from ONE place:
//
//   ncde::assetBase()  = $NCDE_ASSET_BASE if set and non-empty, else the compiled default
//                        (CMake option LAPIVOT_ASSET_BASE, default "/usr/share/ncde/").
//                        Always absolute, always ends in '/'.
//   ncde::assetPath(r) = assetBase() + r   (r relative, e.g. "main.qml", "ncde-kith-tint")
//
// Parity rule kept from the oracle main(): a binary named "ncde-test" with no NCDE_ASSET_BASE uses
// "/usr/share/ncde-test/".
//
// The L2 session script sets NCDE_ASSET_BASE=/usr/share/ncde-l2/; after PROMOTE-L2 nothing sets it and
// the compiled default applies, so the same binary serves both without a rebuild.
#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QString>

#ifndef LAPIVOT_ASSET_BASE
#define LAPIVOT_ASSET_BASE "/usr/share/ncde/"
#endif

namespace ncde {

inline QString normalisedBase(QString b)
{
    if (!QDir::isAbsolutePath(b))
        b = QStringLiteral("/usr/share/ncde/");
    b = QDir::cleanPath(b);
    if (!b.endsWith(QLatin1Char('/')))
        b += QLatin1Char('/');
    return b;
}

inline QString assetBase()
{
    // not cached: cheap, and correct whether or not QCoreApplication exists yet
    const QString env = qEnvironmentVariable("NCDE_ASSET_BASE");
    if (!env.isEmpty() && QDir::isAbsolutePath(env))
        return normalisedBase(env);
    if (QCoreApplication::instance()
        && QFileInfo(QCoreApplication::applicationFilePath()).fileName() == QLatin1String("ncde-test"))
        return QStringLiteral("/usr/share/ncde-test/");
    return normalisedBase(QStringLiteral(LAPIVOT_ASSET_BASE));
}

inline QString assetPath(const QString &relative)
{
    return assetBase() + relative;
}

} // namespace ncde
