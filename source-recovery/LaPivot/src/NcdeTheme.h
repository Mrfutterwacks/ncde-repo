// NcdeTheme — legacy colour object retained as an unconstructed compatibility class.
// Rebuilt from oracle: decomp/NcdeTheme.c (75 functions).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2 (NcdeTheme = 83 symbols, never constructed in LaPivot).
// DEFECTS FIXED vs oracle:
//  1. Removed non-colour system forwarders; this class is never constructed and no QML context
//     property binds to it.
//  2. applyPalette now changes its own colour state and emits changed() only when values differ.
//  3. KickassGuard is null because the former LLM service is superseded by Vesper.
//  4. Unset colours use the documented canonical GTK fallback palette.

#ifndef NCDETHEME_H
#define NCDETHEME_H

#include <QObject>
#include <QColor>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>

class NcdeTheme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor accent READ accent NOTIFY changed)
    Q_PROPERTY(QColor accentMuted READ accentMuted NOTIFY changed)
    Q_PROPERTY(QColor border READ border NOTIFY changed)
    Q_PROPERTY(bool darkMode READ darkMode NOTIFY changed)
    Q_PROPERTY(int fontSize READ fontSize NOTIFY changed)
    Q_PROPERTY(QColor foreground READ foreground NOTIFY changed)
    Q_PROPERTY(QColor gilt READ gilt NOTIFY changed)
    Q_PROPERTY(QColor glow READ glow NOTIFY changed)
    Q_PROPERTY(QColor panelBg READ panelBg NOTIFY changed)
    Q_PROPERTY(QColor popupBg READ popupBg NOTIFY changed)
    Q_PROPERTY(bool presetActive READ presetActive NOTIFY changed)
    Q_PROPERTY(QColor surface READ surface NOTIFY changed)
    Q_PROPERTY(QColor surfaceAlt READ surfaceAlt NOTIFY changed)
    Q_PROPERTY(QColor surfaceGlass READ surfaceGlass NOTIFY changed)
    Q_PROPERTY(QColor verd READ verd NOTIFY changed)
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(QString widgetStyle READ widgetStyle NOTIFY changed)
    Q_PROPERTY(QColor wine READ wine NOTIFY changed)
    Q_PROPERTY(QObject* KickassGuard READ KickassGuard CONSTANT)
    Q_PROPERTY(int letterSpacing READ letterSpacing NOTIFY changed)

public:
    explicit NcdeTheme(QObject *parent = nullptr);
    ~NcdeTheme() override;

    // Colour getters (NOTIFY changed) — return fallback bridge palette
    QColor accent() const;
    QColor accentMuted() const;
    QColor border() const;
    bool darkMode() const;
    int fontSize() const;
    QColor foreground() const;
    QColor gilt() const;
    QColor glow() const;
    QColor panelBg() const;
    QColor popupBg() const;
    bool presetActive() const;
    QColor surface() const;
    QColor surfaceAlt() const;
    QColor surfaceGlass() const;
    QColor verd() const;
    QString version() const;
    QString widgetStyle() const;
    QColor wine() const;
    QObject* KickassGuard() const;

    int letterSpacing() const;
signals:
    void changed();

public slots:
    void applyPalette(const QVariantMap &p);
    void setDarkMode(bool dark);
    void setAccentName(const QString &name);
    void setDarkModeLock(const QString &lock);
    void setBaseColor(const QColor &base, const QColor &accent, const QColor &panelText);
    void clearCustomBase();

private:
    QVariantMap m_palette;
};

#endif // NCDETHEME_H