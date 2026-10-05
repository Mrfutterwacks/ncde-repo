// HudManager — universal search HUD (apps, files, windows)
// Rebuilt from oracle: HudManager::requestHud, dismissHud, hudRequested, hudDismissed
// Spec: ncde-architecture.md §5 (HudManager is a QML context property; Hud.qml connects to it)
// DEFECTS FIXED vs oracle: None — simple signal forwarder

#pragma once

#include <QObject>

class HudManager : public QObject
{
    Q_OBJECT
// ---- GENERATED: tools/gen_header.py HudManager ----

public:
    Q_INVOKABLE void requestHud();
    Q_INVOKABLE void dismissHud();

signals:
    void hudRequested();
    void hudDismissed();

// ---- END GENERATED ----

public:
    explicit HudManager(QObject *parent = nullptr);
    ~HudManager() override = default;
};