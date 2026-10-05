// MuchaWeather.qml — Mucha stained-glass weather section for NCDE.
// Drops into DesktopWidget.qml as a section. Transparent background.
// Pure Canvas 2D + theme.* + ncde.*. The weather ICON is drawn by the
// project's existing mucha-weather.js (drawMuchaWeather) — this file only
// frames it in a rose-window roundel and adds the readouts.
//
// Bindings (read, all on widget_data):
//   weatherTemp, weatherHigh, weatherLow, weatherHumidity, weatherWind,
//   weatherPressure, weatherPrecip, weatherSunrise, weatherSunset,
//   weatherIcon (string code), weatherLocation
//   signal weatherChanged
//
// No C++ changes. No PNG/SVG.

import QtQuick
import "mucha-panels.js"   as P
import "mucha-wx-icons.js" as Wx

Item {
    id: weather
    width:  parent ? parent.width : 316
    height: 157

    property var _widgetStyle: null
    Component.onCompleted: {
        _widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("weather") : null
        weatherCanvas.requestPaint()
    }
    Connections {
        target: ncde
        function onThemeChanged() {
            weather._widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("weather") : null
            weatherCanvas.requestPaint()
        }
    }

    readonly property real roundelR: 45
    readonly property color _gilt4: ncde.gilt4

    WeatherLive { id: wxLive }
    Connections { target: wxLive
        function onLiveIconChanged()  { weatherCanvas.requestPaint() }
        function onLivePlaceChanged() { weatherCanvas.requestPaint() }
    }

    // Night-icon swap (sun below horizon → night variants), ported from the
    // original DesktopWidget so the hosted icon matches day/night.
    function parseTimeMin(s) {
        if (!s || s === "") return -1
        var parts = s.trim().split(" ")
        var tp = parts[0].split(":")
        if (tp.length < 2) return -1
        var h = parseInt(tp[0]); var m = parseInt(tp[1])
        if (parts.length >= 2) {
            var ap = parts[1].toUpperCase()
            if (ap === "PM" && h !== 12) h += 12
            if (ap === "AM" && h === 12) h = 0
        }
        return h * 60 + m
    }
    function isNight() {
        var now = new Date()
        var nowMin = now.getHours() * 60 + now.getMinutes()
        var sr = parseTimeMin(widget_data.weatherSunrise)
        var ss = parseTimeMin(widget_data.weatherSunset)
        if (sr < 0) sr = 360
        if (ss < 0) ss = 1200
        return nowMin < sr || nowMin >= ss
    }
    function nightIcon(icon) {
        if (!isNight()) return icon
        var map = { "32":"31","30":"29","28":"27","34":"33","40":"45",
                    "39":"45","37":"47","38":"47","42":"46","36":"31" }
        return map[icon] !== undefined ? map[icon] : icon
    }

    Connections {
        target: widget_data
        function onWeatherChanged() { if (visible) weatherCanvas.requestPaint() }
    }

    Canvas {
        id: weatherCanvas
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            var ws     = weather._widgetStyle
            var accent = (ws && ws["accent"] !== undefined && ws["accent"] !== "") ? Qt.color(ws["accent"]) : ncde.accent
            var glow   = ncde.glow

            // ── Rose-window roundel on the left ──
            var rx = 8 + weather.roundelR
            var ry = 12 + weather.roundelR
            P.paintRoundel(ctx, rx, ry, weather.roundelR, accent, glow)

            // Host the Mucha stained-glass weather icon inside the halo ring.
            // drawMuchaWxIcon(ctx, W, H, code, accent, glow) paints into a
            // 0..W / 0..H box, so translate to the roundel's inner square and
            // clip to the halo.
            var iconBox = weather.roundelR * 1.5
            ctx.save()
            ctx.beginPath()
            ctx.arc(rx, ry, weather.roundelR * 0.72, 0, Math.PI * 2)
            ctx.clip()
            ctx.translate(rx - iconBox/2, ry - iconBox/2)
            var code = weather.nightIcon(wxLive.liveIcon !== "" ? wxLive.liveIcon : widget_data.weatherIcon)
            Wx.drawMuchaWxIcon(ctx, iconBox, iconBox, code, accent, glow)
            ctx.restore()

            // ── Temperature readout (seven-segment glass) on the right ──
            var tempRaw = (widget_data.weatherTemp || "").replace(/[^0-9\-]/g, "")
            if (tempRaw === "") tempRaw = "--"
            var tx = rx + weather.roundelR + 18
            var ty = 22
            P.paintTempReadout(ctx, tempRaw, tx, ty, 21, 35, 5, "F",
                               theme.fontFamily, accent, glow)

            // Location caption under temp
            ctx.font = "italic 600 12px '" + theme.fontFamily + "', sans-serif"
            ctx.fillStyle = Qt.rgba(weather._gilt4.r, weather._gilt4.g, weather._gilt4.b, 0.8)
            ctx.textBaseline = "alphabetic"
            ctx.fillText(((wxLive.livePlace || widget_data.weatherLocation) || "").toUpperCase(), tx, ty + 49)

            // ── Mini-cartouche arcade along the bottom ──
            var chips = [
                { l: "HI",   v: (widget_data.weatherHigh     || "—") },
                { l: "LO",   v: (widget_data.weatherLow      || "—") },
                { l: "HUM",  v: (widget_data.weatherHumidity || "—") },
                { l: "WIND", v: (widget_data.weatherWind     || "—") }
            ]
            var chipY = 110
            var chipH = 30
            var totalGap = 8
            var chipW = (width - 16 - totalGap * (chips.length - 1)) / chips.length
            for (var i = 0; i < chips.length; i++) {
                var cxp = 8 + i * (chipW + totalGap)
                P.paintMiniCartouche(ctx, cxp, chipY, chipW, chipH,
                                     chips[i].l, chips[i].v,
                                     theme.fontFamily, accent, glow)
            }
        }
    }

}
