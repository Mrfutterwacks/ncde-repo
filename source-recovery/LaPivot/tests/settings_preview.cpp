// settings_preview — a normal desktop window showing the payload's Settings › Network and › Bluetooth tabs
// on the rebuilt Lelan (network + Bluetooth code) against the live NetworkManager and BlueZ, so the
// operator can use them before the rebuilt LaPivot exists. Installs nothing; closing the window ends it.
// While it runs, its pairing agent is BlueZ's default (it goes away with the window).
// `ncde` / `settings` / `animPolicy` / `notifications` are stand-ins (colours, scales, a print).
#include <QColor>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlPropertyMap>
#include <QUrl>
#include <cstdio>

#define private public
#include "Lelan.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;

class Notifications : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void notify(const QString &title, const QString &body, const QString &, int)
    {
        std::printf("NOTIFY %s: %s\n", qPrintable(title), qPrintable(body));
        std::fflush(stdout);
    }
};

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("NCDE Settings preview");
    const QString dir = qEnvironmentVariable("NCDE_QML_DIR");

    Lelan lelan(nullptr, false);
    lelan.subscribeToNetworkManager();
    lelan.subscribeToWifi();
    lelan.subscribeToBlueZ();
    QObject::connect(&lelan, &Lelan::bluetoothFailed, [](const QString &a, const QString &r) {
        std::printf("BLUETOOTH FAILED %s: %s\n", qPrintable(a), qPrintable(r)); std::fflush(stdout); });
    QObject::connect(&lelan, &Lelan::wifiConnectFailed, [](const QString &s, const QString &r) {
        std::printf("WIFI FAILED %s: %s\n", qPrintable(s), qPrintable(r)); std::fflush(stdout); });

    QQmlPropertyMap ncde, settings, anim;
    // colours only where SetTheme has no fallback of its own; fonts fall back to the NCDE faces
    ncde.insert("surface", QColor("#efe6d2")); ncde.insert("panelBg", QColor("#2a1f1a"));
    ncde.insert("panelText", QColor("#2a1e0e")); ncde.insert("darkMode", false);
    ncde.insert("fontSize_sm", 12); ncde.insert("fontSize_md", 14); ncde.insert("fontSize_lg", 19);
    settings.insert("userName", qEnvironmentVariable("USER"));
    settings.insert("proxyEnabled", false);
    settings.insert("uiScale", 1.0); settings.insert("fontSizeScale", 1.0); settings.insert("accessibilityTextScale", 1.0);
    anim.insert("instant", false);
    Notifications notifications;

    QQmlApplicationEngine engine;
    auto *ctx = engine.rootContext();
    ctx->setContextProperty("lelan", &lelan);
    ctx->setContextProperty("ncde", &ncde);
    ctx->setContextProperty("settings", &settings);
    ctx->setContextProperty("animPolicy", &anim);
    ctx->setContextProperty("notifications", &notifications);
    ctx->setContextProperty("ncdeQmlDir", QUrl::fromLocalFile(dir + "/").toString());
    engine.loadData(R"QML(
import QtQuick 2.15
import QtQuick.Window 2.15
Window {
    id: win; visible: true; width: 860; height: 640
    title: "NCDE Settings preview — rebuilt Lelan (nothing installed)"
    color: "#efe6d2"
    property string tab: "NetworkTab"
    Row {
        id: bar; x: 16; y: 12; spacing: 8
        Repeater {
            model: [["NetworkTab", "Network"], ["BluetoothTab", "Bluetooth"]]
            Rectangle {
                width: 120; height: 30; radius: 4
                color: win.tab === modelData[0] ? "#e9c97c" : "transparent"
                border.color: "#8a5a20"; border.width: 1
                Text { anchors.centerIn: parent; text: modelData[1]; color: "#2a1e0e"; font.family: "Cinzel"; font.pixelSize: 14; font.bold: true }
                TapHandler { onTapped: win.tab = modelData[0] }
            }
        }
    }
    Loader {
        anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
        anchors.top: bar.bottom; anchors.margins: 16
        source: ncdeQmlDir + win.tab + ".qml"
    }
}
)QML");
    if (engine.rootObjects().isEmpty())
        return 2;
    return app.exec();
}

#include "settings_preview.moc"
