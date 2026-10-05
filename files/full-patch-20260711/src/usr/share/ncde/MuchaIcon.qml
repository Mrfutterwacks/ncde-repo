// MuchaIcon.qml — NCDE Art Nouveau (Mucha-style) icon theme component.
// Drop-in replacement for MuchaAppIcon in Dock / BottomPanel / Expose.
//
// Visual language: cream tiles, gilded medallions, sage & rose accents,
// ornamental dotted rings, whiplash curves, halo arcs, laurel beads.
//
// All drawing is done in Canvas2D via shared JS libraries. No PNG/SVG assets.
//
// Root converted Canvas -> Item wrapping an inner Canvas, 2026-09-23, to fix
// hover-magnify blur in Dock.qml: the dock scales icons up via a plain QML
// `scale:` transform (up to DockPrefs' 2.5x zoom), which stretches an
// already-rasterized Canvas bitmap — classic scale-transform blur. Fix is
// supersampling: the inner Canvas now renders at `size * renderScale` pixel
// resolution (renderScale defaults 1.0, unchanged for every non-Dock caller)
// then transform-scales back DOWN to the normal `size x size` footprint, so
// when Dock.qml's OWN scale-up (up to 2.5x) is applied on top, the net
// result at max zoom is downscale-then-upscale by the same ratio — no
// resolution lost, since the raster was rendered at that density already.
// No live per-frame redraw needed during the hover spring animation: the
// canvas is supersampled once, at the STATIC max-possible zoom (Dock passes
// renderScale: dock.zoomPercent), not per-frame during the animation.
// Public property contract (appName/size/accentColor/etc.) is unchanged;
// `s = Math.min(width, height)` inside onPaint already read the Canvas's
// own resolution rather than the outer `size` directly, so every draw
// function below is already resolution-agnostic — nothing else changes.

import QtQuick 2.15
import "mucha-icons-core.js"       as Core
import "mucha-icons-apps.js"       as Apps
import "mucha-icons-tray.js"       as Tray
import "mucha-icons-places.js"     as Places
import "mucha-icons-devices.js"    as Devices
import "mucha-icons-mimetypes.js"  as Mimes

Item {
    id: root

    // ---- Public contract ----
    property string appName: ""
    property string appIcon: ""
    property int    size: 48
    property bool   kithEmblem: false

    // Static supersample factor — set by callers that scale-transform this
    // icon up (Dock's hover magnify). 1.0 = no supersampling, same cost as
    // before. Not meant to track a LIVE animated scale; pass the max
    // possible zoom once (e.g. dock.zoomPercent), not a per-frame value.
    property real   renderScale: 1.0

    // Theme-aware tints supplied by NCDE
    property color  accentColor: (typeof ncde !== 'undefined' && ncde.accent) ? ncde.accent : "#b58c4a"
    property color  glowColor:   (typeof ncde !== 'undefined' && ncde.glow)   ? ncde.glow   : "#d4b27a"

    // Category router
    property string iconCategory: "app"   // "app" | "tray" | "place" | "device" | "mime"

    // Tray parameters
    property int    traySubType: 0
    property bool   trayActive: true
    property int    trayPercent: 100
    property bool   trayCharging: false
    property int    trayBars: 3
    property int    trayBadge: 0

    // Mime parameters
    property string mimeType: ""
    property string fileExtension: ""

    // Place / Device parameters
    property string placeName: ""
    property string deviceName: ""

    width: size
    height: size

    Canvas {
        id: canvas
        readonly property real factor: Math.max(1.0, root.renderScale)
        width: root.size * factor
        height: root.size * factor
        anchors.centerIn: parent
        scale: 1 / factor

        antialiasing: true
        renderStrategy: Canvas.Cooperative

        // Repaint hooks — every input property must trigger requestPaint()
        Connections {
            target: root
            function onAppNameChanged()       { canvas.requestPaint() }
            function onAppIconChanged()       { canvas.requestPaint() }
            function onKithEmblemChanged()    { canvas.requestPaint() }
            function onSizeChanged()          { canvas.requestPaint() }
            function onRenderScaleChanged()   { canvas.requestPaint() }
            function onAccentColorChanged()   { canvas.requestPaint() }
            function onGlowColorChanged()     { canvas.requestPaint() }
            function onIconCategoryChanged()  { canvas.requestPaint() }
            function onTraySubTypeChanged()   { canvas.requestPaint() }
            function onTrayActiveChanged()    { canvas.requestPaint() }
            function onTrayPercentChanged()   { canvas.requestPaint() }
            function onTrayChargingChanged()  { canvas.requestPaint() }
            function onTrayBarsChanged()      { canvas.requestPaint() }
            function onTrayBadgeChanged()     { canvas.requestPaint() }
            function onMimeTypeChanged()      { canvas.requestPaint() }
            function onFileExtensionChanged() { canvas.requestPaint() }
            function onPlaceNameChanged()     { canvas.requestPaint() }
            function onDeviceNameChanged()    { canvas.requestPaint() }
        }

        Component.onCompleted: requestPaint()

        onPaint: {
            var ctx = getContext("2d")
            if (!ctx) { Qt.callLater(requestPaint); return; }
            ctx.clearRect(0, 0, width, height)
            var s = Math.min(width, height)

            // Pass accent/glow as strings (CSS-compatible) — never as QML color objects.
            var accent = "" + root.accentColor
            var glow   = "" + root.glowColor

            switch (root.iconCategory) {
                case "tray":   drawTray(ctx, s, accent, glow); break;
                case "place":  drawPlace(ctx, s, accent, glow); break;
                case "device": drawDevice(ctx, s, accent, glow); break;
                case "mime":   drawMime(ctx, s, accent, glow); break;
                default:       drawApp(ctx, s, accent, glow); break;
            }
        }

        // ---- Category delegates ----
        function drawApp(ctx, s, accent, glow) {
            Apps.matchAppIcon(ctx, s, root.appName + " " + root.appIcon, root.appIcon, accent, glow, root.kithEmblem);
        }
        function drawTray(ctx, s, accent, glow) {
            Tray.setTrayTheme(accent, glow);
            switch (root.traySubType) {
                case 0:  Tray.drawTrayAudio(ctx, s, root.trayActive); break;
                case 1:  Tray.drawTrayMic(ctx, s, root.trayActive); break;
                case 2:  Tray.drawTrayBattery(ctx, s, root.trayPercent, root.trayCharging); break;
                case 3:  Tray.drawTrayWifi(ctx, s, root.trayBars); break;
                case 4:  Tray.drawTrayEthernet(ctx, s, root.trayActive); break;
                case 5:  Tray.drawTrayBluetooth(ctx, s, root.trayActive); break;
                case 6:  Tray.drawTrayNotifications(ctx, s, root.trayBadge); break;
                case 7:  Tray.drawTrayClipboard(ctx, s); break;
                case 8:  Tray.drawTrayBrightness(ctx, s, root.trayPercent); break;
                case 9:  Tray.drawTrayKeyboard(ctx, s); break;
                case 10: Tray.drawTrayPower(ctx, s); break;
                case 11: Tray.drawTrayUpdates(ctx, s, root.trayBadge); break;
                case 12: Tray.drawTrayCalendar(ctx, s); break;
                case 13: Tray.drawTrayMail(ctx, s, root.trayBadge); break;
                case 14: Tray.drawTrayVPN(ctx, s, root.trayActive); break;
                case 15: Tray.drawTrayNightLight(ctx, s, root.trayActive); break;
                default: Tray.drawTrayDefault(ctx, s); break;
            }
        }
        function drawPlace(ctx, s, accent, glow) {
            Places.matchPlaceIcon(ctx, s, root.placeName, accent, glow);
        }
        function drawDevice(ctx, s, accent, glow) {
            Devices.matchDeviceIcon(ctx, s, root.deviceName, accent, glow);
        }
        function drawMime(ctx, s, accent, glow) {
            Mimes.matchMimeIcon(ctx, s, root.mimeType, root.fileExtension, accent, glow);
        }
    }
}
