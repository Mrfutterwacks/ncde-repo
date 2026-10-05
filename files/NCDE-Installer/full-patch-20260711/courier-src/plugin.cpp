// plugin.cpp — registers `import NCDE.Courier` (GoogleLink) for Hummingbird.
#include <QQmlExtensionPlugin>
#include <QQmlEngine>
#include <qqml.h>
#include "googlelink.h"
#include <QCoreApplication>
#include <QFileInfo>

// The engine's delete diagnostics also print the first ~200 characters of every
// letter opened ("HB-DIAG … body-head=[…]"). Letters don't belong in logs:
// drop exactly those lines, pass everything else through.
static QtMessageHandler s_previousHandler = nullptr;
static void courierMessageHandler(QtMsgType type, const QMessageLogContext &ctx, const QString &msg)
{
    if (msg.contains(QLatin1String("body-head=")) || msg.contains(QLatin1String("body-len=")))
        return;
    if (s_previousHandler) s_previousHandler(type, ctx, msg);
    else qt_message_output(type, ctx, msg);
}

class NcdeCourierPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri) override
    {
        const bool inHummingbird = QFileInfo(QCoreApplication::applicationFilePath()).fileName()
                                   == QLatin1String("hummingbird-courier");
        if (inHummingbird && !s_previousHandler) s_previousHandler = qInstallMessageHandler(courierMessageHandler);
        qmlRegisterType<GoogleLink>(uri, 1, 0, "GoogleLink");
    }
};

#include "plugin.moc"
