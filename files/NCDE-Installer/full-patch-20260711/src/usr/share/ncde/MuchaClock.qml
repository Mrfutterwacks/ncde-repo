// MuchaClock.qml — Mucha stained-glass digital clock section for NCDE.
// Drops into DesktopWidget.qml (or any QML host) as a section.
// Transparent background — NCDEGlassSurface behind it shows through.
// Pure Canvas 2D + theme.* tokens + ncde.* color tokens.
//
// Bindings (read, all already on widget_data):
//   widget_data.timeHour    — QString "HH" (12- or 24-hr per backend)
//   widget_data.timeMinute  — QString "MM"
//   widget_data.timeAMPM    — QString "AM"/"PM" ("" if 24-hr)
//   widget_data.colonOn     — bool   (blinks each second)
//   widget_data.dateString  — QString
//   widget_data.greeting    — QString
//   signal  widget_data.clockChanged
//
// No C++ changes. No PNG/SVG. TapHandler-free (purely decorative).

import QtQuick
import "mucha-clock.js" as Clock
import QtQuick.Effects 6.5

Item {
    id: clock
    width:  parent ? parent.width : 316
    height: 100

    property var _widgetStyle: null
    // wallpaper ink: text + lit digits are painted, so repaint when it changes
    Connections { target: WallInk; function onInkSerialChanged() { clockCanvas.requestPaint() } }
    Component.onCompleted: {
        _widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("clock") : null
        clockCanvas.requestPaint()
    }
    Connections {
        target: ncde
        function onThemeChanged() {
            clock._widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("clock") : null
            clockCanvas.requestPaint()
        }
    }

    // Seven-segment metrics (scaled to the section width)
    readonly property real digitW: 27
    readonly property real digitH: 46
    readonly property real segT:   6
    readonly property real gap:    7
    readonly property real colonW: 11

    // Repaint when the backend clock ticks (covers colon blink + minute roll)
    Connections {
        target: widget_data
        function onClockChanged() { if (visible) clockCanvas.requestPaint() }
    }

    // Frame
    Canvas {
        id: clockCanvas
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            var ws     = clock._widgetStyle
            var accent = (ws && ws["accent"] !== undefined && ws["accent"] !== "") ? Qt.color(ws["accent"]) : ncde.accent
            var glow   = ncde.glow

            // Ornate cartouche frame (leaves room for crest above + date below)
            var fx = 8, fy = 11
            var fw = width - 16
            var fh = 83
            Clock.paintClockFrame(ctx, fx, fy, fw, fh, accent, glow)

            // Compose the readout: HH : MM  (+ AM/PM column if present)
            var hh = widget_data.timeHour   || "  "
            var mm = widget_data.timeMinute || "  "
            var ampm = widget_data.timeAMPM || ""
            if (hh.length < 2) hh = " " + hh

            var readoutW = Clock.measureDigits(4, true, clock.digitW, clock.gap, clock.colonW)
            var ampmW = ampm !== "" ? 22 : 0
            var totalW = readoutW + ampmW
            var startX = (width - totalW) / 2
            var digY = fy + 14

            var cur = startX
            // HH
            Clock.paintDigit(ctx, hh.charAt(0), cur, digY, clock.digitW, clock.digitH, clock.segT, accent, glow)
            cur += clock.digitW + clock.gap
            Clock.paintDigit(ctx, hh.charAt(1), cur, digY, clock.digitW, clock.digitH, clock.segT, accent, glow)
            cur += clock.digitW + clock.gap
            // colon
            Clock.paintColon(ctx, cur + clock.colonW/2, digY, clock.digitH, 3.2,
                             widget_data.colonOn, accent, glow)
            cur += clock.colonW + clock.gap
            // MM
            Clock.paintDigit(ctx, mm.charAt(0), cur, digY, clock.digitW, clock.digitH, clock.segT, accent, glow)
            cur += clock.digitW + clock.gap
            Clock.paintDigit(ctx, mm.charAt(1), cur, digY, clock.digitW, clock.digitH, clock.segT, accent, glow)
            cur += clock.digitW + clock.gap
            // AM/PM
            if (ampm !== "") {
                Clock.paintAmpm(ctx, cur + 2, digY, clock.digitH, ampm, theme.fontFamily)
            }

            // Date ribbon-cartouche drawn into the glass below the digits
            var dateStr = (widget_data.dateString || "").toUpperCase()
            Clock.paintDateBanner(ctx, width / 2, digY + clock.digitH + 8,
                                  Math.min(fw - 60, 200), dateStr,
                                  theme.fontFamily, accent, glow)
        }
    }

    // Greeting — pinned ABOVE the frame, always cream + bold so it never gets lost in palette changes
    Text {
        id: greetingText
        anchors.top: parent.top
        anchors.topMargin: 0                     // lifted to the very top, clear of the frame crest at y≈11
        anchors.horizontalCenter: parent.horizontalCenter
        z: 10                                    // above the frame crest (was visually obscured)
        text: (widget_data.greeting || "") + (settings.userName ? " " + settings.userName : "")
        font.family: theme.fontFamily; font.letterSpacing: theme.letterSpacing
        font.italic: true
        font.bold: true                          // bold all the time — holds up over the ornament
        font.pixelSize: theme.fontSmall
        color: WallInk.inked(ncde.gilt4)                          // Glass text: fixed-bright, accent-hue-reactive, not theme.textColor (which shifts with the palette)
        visible: text !== ""
        style: theme.textStyle; styleColor: theme.textStyleColor
        layer.enabled: theme.textShadowEnabled
        layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
            shadowBlur: theme.textShadowRadius / 32.0
            shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
    }

}
