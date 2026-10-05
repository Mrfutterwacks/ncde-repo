#include "NCDEWindowManager.h"

#include <QGuiApplication>
#include <QVariant>

#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    NCDEWindowManager manager;
    if (manager.rowCount() != 0 || manager.count() != 0)
        return EXIT_FAILURE;

    const auto roles = manager.roleNames();
    if (roles.value(NCDEWindowManager::WinIdRole) != QByteArrayLiteral("winId")
        || roles.value(NCDEWindowManager::NameRole) != QByteArrayLiteral("name")
        || roles.value(NCDEWindowManager::ActiveRole) != QByteArrayLiteral("active"))
        return EXIT_FAILURE;

    manager.setSnapZone(3);
    if (manager.snapZone() != 3)
        return EXIT_FAILURE;
    manager.setSnapZone(3);
    if (manager.screenWidth() < 0 || manager.screenHeight() < 0
        || manager.userIdleMs() != 0 || manager.winIdForName(QStringLiteral("missing")) != 0
        || manager.hasWindowForName(QStringLiteral("missing"))
        || manager.isMinimizedForName(QStringLiteral("missing"))
        || manager.isActiveForName(QStringLiteral("missing"))
        || manager.isMaximizedForName(QStringLiteral("missing")))
        return EXIT_FAILURE;

    manager.activateWindow(0);
    manager.minimizeWindow(0);
    manager.unminimizeWindow(0);
    manager.moveWindow(0, 10, 20);
    manager.resizeWindow(0, 640, 480);
    manager.moveTiledWindow(0, 0, 0, 640, 480);
    manager.setTiled(0, true);
    manager.setMaximized(0, true);
    manager.closeWindow(0);
    manager.invokeAppMenu(1);

    std::puts("PASS: initial model is empty and role names are stable");
    std::puts("PASS: detached-display queries and unknown-window actions are safe no-ops");
    return EXIT_SUCCESS;
}
