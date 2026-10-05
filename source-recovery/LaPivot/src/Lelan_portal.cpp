// Lelan — xdg-desktop-portal Settings: the system's dark-mode preference and accent colour.
//
// Rebuilt from oracle: subscribeToPortalSettings (+lambda #1), onPortalSettingChanged,
// applyPortalAppearance, darkMode, accentColor.
// Spec: lelan.md §4 (portal.Settings on the session bus: ReadOne + SettingChanged; dark mode =
// org.freedesktop.appearance color-scheme 1; accent = accent-color).
//
// ORACLE-EXACT by operator rule (2026-09-30: hands off anything ncde-portal touches): same calls,
// same keys, same conversions, same signals, in the same order. No defect fixes in this file.
#include "Lelan.h"

#include <QColor>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QtLogging>

namespace {
const QString kPortal = QStringLiteral("org.freedesktop.portal.Desktop");
const QString kPortalPath = QStringLiteral("/org/freedesktop/portal/desktop");
const QString kPortalSettings = QStringLiteral("org.freedesktop.portal.Settings");
const QString kAppearance = QStringLiteral("org.freedesktop.appearance");
} // namespace

bool Lelan::darkMode() const { return m_darkMode; }
QString Lelan::accentColor() const { return m_accentColor; }

void Lelan::subscribeToPortalSettings()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    for (const QString &key : {QStringLiteral("color-scheme"), QStringLiteral("accent-color")}) {
        QDBusMessage m = QDBusMessage::createMethodCall(kPortal, kPortalPath, kPortalSettings, QStringLiteral("ReadOne"));
        m << QVariant(kAppearance) << QVariant(key);
        auto *w = new QDBusPendingCallWatcher(bus.asyncCall(m), this);
        connect(w, &QDBusPendingCallWatcher::finished, this, [this, key, w] {
            QDBusPendingReply<QDBusVariant> reply = *w;
            if (!reply.isValid()) {
                qWarning() << "[lelan] portal ReadOne failed for" << key << ":" << reply.error().name() << reply.error().message();
            } else {
                applyPortalAppearance(key, reply.value().variant());
            }
            w->deleteLater();
        });
    }
    bus.connect(kPortal, kPortalPath, kPortalSettings, QStringLiteral("SettingChanged"), this,
                SLOT(onPortalSettingChanged(QString,QString,QDBusVariant)));
}

void Lelan::onPortalSettingChanged(const QString &ns, const QString &key, const QDBusVariant &value)
{
    if (ns == QLatin1String("org.freedesktop.appearance"))
        applyPortalAppearance(key, value.variant());
}

// color-scheme: 1 = prefer dark. accent-color: (ddd) sRGB 0..1; anything out of range = no accent.
void Lelan::applyPortalAppearance(const QString &key, const QVariant &value)
{
    if (key == QLatin1String("color-scheme")) {
        m_darkMode = value.toUInt() == 1;
        emit darkModeChanged();
        emit themeChanged();
    } else if (key == QLatin1String("accent-color")) {
        double r = -1.0, g = -1.0, b = -1.0;
        if (value.canConvert<QDBusArgument>()) {
            const QDBusArgument arg = value.value<QDBusArgument>();
            arg.beginStructure();
            arg >> r >> g >> b;
            arg.endStructure();
        }
        if (r < 0.0 || r > 1.0 || g < 0.0 || g > 1.0 || b < 0.0 || b > 1.0)
            m_accentColor.clear();
        else
            m_accentColor = QColor::fromRgbF(float(r), float(g), float(b), 1.0f).name(QColor::HexRgb);
        emit onAccentColorChanged();
        emit themeChanged();
    }
}
