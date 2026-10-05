// HudManager.cpp — implementation
// Rebuilt from oracle: HudManager::requestHud, dismissHud

#include "HudManager.h"

HudManager::HudManager(QObject *parent)
    : QObject(parent)
{
}

void HudManager::requestHud()
{
    emit hudRequested();
}

void HudManager::dismissHud()
{
    emit hudDismissed();
}