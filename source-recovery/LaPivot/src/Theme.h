// Theme — typography/accessibility facade for the QML context "theme".
// Rebuilt from oracle: decomp/Theme.c (26 functions).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2, docs/filigree-phase1-20260720.md.
// DEFECTS FIXED vs oracle:
//  1. Removed the unsafe, untyped settings-property reads; typed Settings properties provide
//     typography/accessibility while colour values come from NCDEEngine.
//  2. Font-size accessors consistently apply accessibilityTextScale after engine font scaling.
//  3. Settings and engine changes invalidate QML bindings through one changed() signal.

#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QColor>
#include <QString>
#include <QVariant>
#include <QPointer>

class NCDEEngine;
class Settings;

class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fontFamily READ fontFamily NOTIFY changed)
    Q_PROPERTY(QString titleFont READ titleFont NOTIFY changed)
    Q_PROPERTY(double letterSpacing READ letterSpacing NOTIFY changed)
    Q_PROPERTY(int fontSmall READ fontSmall NOTIFY changed)
    Q_PROPERTY(int fontMedium READ fontMedium NOTIFY changed)
    Q_PROPERTY(int fontLarge READ fontLarge NOTIFY changed)
    Q_PROPERTY(QString textColor READ textColor NOTIFY changed)
    Q_PROPERTY(int textStyle READ textStyle NOTIFY changed)
    Q_PROPERTY(QString textStyleColor READ textStyleColor NOTIFY changed)
    Q_PROPERTY(QString textShadowColor READ textShadowColor NOTIFY changed)
    Q_PROPERTY(bool textShadowEnabled READ textShadowEnabled NOTIFY changed)
    Q_PROPERTY(double textShadowRadius READ textShadowRadius NOTIFY changed)
    Q_PROPERTY(double textShadowOffsetX READ textShadowOffsetX NOTIFY changed)
    Q_PROPERTY(double textShadowOffsetY READ textShadowOffsetY NOTIFY changed)

public:
    explicit Theme(QObject *parent = nullptr);
    ~Theme() override;

    // Getters (NOTIFY changed)
    QString fontFamily() const;
    QString titleFont() const;
    double letterSpacing() const;
    int fontSmall() const;
    int fontMedium() const;
    int fontLarge() const;
    QString textColor() const;
    int textStyle() const;
    QString textStyleColor() const;
    QString textShadowColor() const;
    bool textShadowEnabled() const;
    double textShadowRadius() const;
    double textShadowOffsetX() const;
    double textShadowOffsetY() const;

    // Q_INVOKABLE
    Q_INVOKABLE double scale(double base) const;

    // Wiring (called once at startup from main.cpp)
    void setEngine(NCDEEngine *engine);
    void setSettings(Settings *settings);

signals:
    void changed();

private:
    int orcScaled(int base) const;
    QPointer<NCDEEngine> m_engine;
    QPointer<Settings> m_settings;
};

#endif // THEME_H