// MuchaAppIcon.qml — NCDE system-wide Canvas icon component (Mucha Art Nouveau)
// ALL icons drawn via Canvas 2D — NO Image/SVG/PNG.
// TapHandlers/HoverHandlers must stay on the PARENT Item (Rule #14).

import QtQuick 2.15
import "mucha-icons-apps.js" as Apps
import "mucha-icons-tray.js" as Tray
import "mucha-icons-places.js" as Places
import "mucha-icons-devices.js" as Devices
import "mucha-icons-mimetypes.js" as Mimes

Canvas {
    id: root
    renderStrategy: Canvas.Cooperative

    // ── Standard properties (NCDEAppIcon-compatible) ────────────
    property string appName: ""
    property string appIcon: ""
    property int    size:    48
    property color  accentColor: ncde.accent
    property color  glowColor:   ncde.glow

    // ── Category router ─────────────────────────────────────────
    property string iconCategory: "app"   // "app" | "tray" | "place" | "device" | "mime"
    property string mimeType: ""
    property string fileExtension: ""

    // ── Tray properties ─────────────────────────────────────────
    property int    traySubType: 0
    property bool   trayActive: false
    property real   trayPercent: 50
    property bool   trayCharging: false
    property int    trayBars: 3
    property int    trayBadge: 0

    // Backward-compat aliases
    property alias trayStrength: root.trayBars
    property alias trayCount: root.trayBadge
    property alias trayHasNew: root.trayBadge
    // Deprecated — kept to avoid QML binding errors
    property bool trayConnected: false
    onTrayConnectedChanged: {}
    property int trayLevel: 50
    onTrayLevelChanged: {}

    width: size; height: size

    onAppNameChanged:       requestPaint()
    onAppIconChanged:       requestPaint()
    onSizeChanged:          requestPaint()
    onAccentColorChanged:   requestPaint()
    onGlowColorChanged:     requestPaint()
    onIconCategoryChanged:  requestPaint()
    onMimeTypeChanged:      requestPaint()
    onFileExtensionChanged: requestPaint()
    onTraySubTypeChanged:   requestPaint()
    onTrayActiveChanged:    requestPaint()
    onTrayPercentChanged:   requestPaint()
    onTrayChargingChanged:  requestPaint()
    onTrayBarsChanged:      requestPaint()
    onTrayBadgeChanged:     requestPaint()

    Component.onCompleted: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        if (!ctx) { Qt.callLater(requestPaint); return; }
        ctx.clearRect(0, 0, width, height)
        var s = Math.min(width, height)

        switch (root.iconCategory) {
            case "tray":    drawTrayIcon(ctx, s); break;
            case "place":   drawPlaceIcon(ctx, s); break;
            case "device":  drawDeviceIcon(ctx, s); break;
            case "mime":    drawMimeIcon(ctx, s); break;
            default:        drawAppIcon(ctx, s); break;
        }
    }

    // ── App icons (default) ─────────────────────────────────────
    function drawAppIcon(ctx, s) {
        Apps.matchAppIcon(ctx, s, appName + " " + appIcon, appIcon, "" + accentColor, "" + glowColor);
    }

    // ── Tray / status icons ─────────────────────────────────────
    function drawTrayIcon(ctx, s) {
        Tray.setTrayTheme("" + accentColor, "" + glowColor);
        switch (traySubType) {
            case 0:  Tray.drawTrayAudio(ctx, s, trayActive); break;
            case 1:  Tray.drawTrayMic(ctx, s, trayActive); break;
            case 2:  Tray.drawTrayBattery(ctx, s, trayPercent, trayCharging); break;
            case 3:  Tray.drawTrayWifi(ctx, s, trayBars); break;
            case 4:  Tray.drawTrayEthernet(ctx, s, trayActive); break;
            case 5:  Tray.drawTrayBluetooth(ctx, s, trayActive); break;
            case 6:  Tray.drawTrayNotifications(ctx, s, trayBadge); break;
            case 7:  Tray.drawTrayClipboard(ctx, s); break;
            case 8:  Tray.drawTrayBrightness(ctx, s, trayPercent); break;
            case 9:  Tray.drawTrayKeyboard(ctx, s); break;
            case 10: Tray.drawTrayPower(ctx, s); break;
            case 11: Tray.drawTrayUpdates(ctx, s, trayBadge); break;
            case 12: Tray.drawTrayCalendar(ctx, s); break;
            case 13: Tray.drawTrayMail(ctx, s, trayBadge); break;
            case 14: Tray.drawTrayVPN(ctx, s, trayActive); break;
            case 15: Tray.drawTrayNightLight(ctx, s, trayActive); break;
            default: Tray.drawTrayDefault(ctx, s); break;
        }
    }

    // ── Place / folder icons ────────────────────────────────────
    function drawPlaceIcon(ctx, s) {
        Places.matchPlaceIcon(ctx, s, appName + " " + appIcon, "" + accentColor, "" + glowColor);
    }

    // ── Device icons ────────────────────────────────────────────
    function drawDeviceIcon(ctx, s) {
        Devices.matchDeviceIcon(ctx, s, appName + " " + appIcon, "" + accentColor, "" + glowColor);
    }

    // ── MIME type icons ─────────────────────────────────────────
    function drawMimeIcon(ctx, s) {
        Mimes.matchMimeIcon(ctx, s, mimeType, fileExtension, "" + accentColor, "" + glowColor);
    }
}
