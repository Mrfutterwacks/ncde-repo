import QtQuick
import "mucha-panels.js"   as P
import "mucha-wx-icons.js" as Wx

Item {
    id: root
    // no clip here: it cut the glass glow + shadow off at a square box (2026-09-24)
    property Item backgroundSource: null
    property var _surfaceGlass: null
    readonly property var sky: wxLive.sky   // weather window: shared with the Space card
    // the hemisphere's seasons for the Space card (autumn leaves); re-read whenever
    // the sky updates, which is when WeatherLive has learned where it is
    readonly property real latitude: { wxLive.sky; var c = wxLive.weatherCoords(); return (c && c.lat !== undefined) ? c.lat : 40 }
    Component.onCompleted: {
        _surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("weather") : null
    }
    Connections {
        target: ncde
        function onThemeChanged() {
            root._surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("weather") : null
        }
    }
    width: parent ? parent.width : 316
    // Script Shift (2026-09-24): the one text-size factor, read the same way LaPivot's
    // Theme does (fontSizeScale x uiScale; uiScale is retired and stays 1). The card
    // grows to fit its text; nothing else about it scales.
    readonly property real ts: (typeof settings !== "undefined" && settings.fontSizeScale > 0 ? settings.fontSizeScale : 1)
                             * (typeof settings !== "undefined" && settings.uiScale > 0 ? settings.uiScale : 1)
    // text growth: the town caption (12*ts, pushes the chips down) + the chips (30*ts)
    readonly property real capGrow: Math.round(12 * (ts - 1))
    readonly property real chipGrow: Math.round(30 * (ts - 1))
    height: 177 + capGrow + chipGrow
    onHeightChanged: weatherCanvas.requestPaint()
    NCDEGlass2 {   // Mucha glass: full NCDEGlassSurface layers + palette-driven ornamental frame
        cornerRadius: 14
        anchors {
            fill: parent
            leftMargin: 4; rightMargin: 4
            topMargin: 2; bottomMargin: 2
        }
        backgroundSource: root.backgroundSource
        revealPulse: intellihide.widgetRevealed
        glintPulse: intellihide.glintPulse
        // Iris Chroma baseline + Filigree override — resolved inside NCDEGlassSurface.
        surfaceKey: "weather"
        glass: root._surfaceGlass
    }
    // MuchaWeather content inlined under NCDEGlassSurface (glass merger 2026-06-13)
    Item {
        id: weather
        clip: true   // content clips here instead of at root, so the glass keeps its rounded glow
        width: parent.width - 20
        height: root.height - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        z: 1

        property var _widgetStyle: null
        // wallpaper ink: text + lit digits are painted, so repaint when it changes
        Connections { target: WallInk; function onInkSerialChanged() { weatherCanvas.requestPaint() } }
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

        // ── QML fallback fetch (added 2026-07-08, installed-node fix) ─────────
        // The WM's own fetch fires at tick 5 (~5s after login) and then only every
        // 30 min (tick % 1800) — a boot-time DNS race leaves the widget blank for
        // up to 30 min. While widget_data has no weather, this fetches the SAME
        // open-meteo endpoint the WM uses (URL taken verbatim from the binary) and
        // paints from it; the moment the WM's own data arrives it takes precedence.
        // WMO→icon table below was extracted from the binary's
        // WidgetData::wmoToYahooCode() — identical mapping, nothing invented.
        property var fx: null
        readonly property string wTemp:     (widget_data.weatherTemp     || (fx ? fx.temp     : ""))
        readonly property string wIcon:     ((widget_data.weatherTemp || "") !== "" ? widget_data.weatherIcon : (fx ? fx.icon : ""))
        readonly property string wHigh:     (widget_data.weatherHigh     || (fx ? fx.hi       : ""))
        readonly property string wLow:      (widget_data.weatherLow      || (fx ? fx.lo       : ""))
        readonly property string wHumidity: (widget_data.weatherHumidity || (fx ? fx.hum      : ""))
        readonly property string wWind:     (widget_data.weatherWind     || (fx ? fx.wind     : ""))
        readonly property string wSunrise:  (widget_data.weatherSunrise  || (fx ? fx.sunrise  : ""))
        readonly property string wSunset:   (widget_data.weatherSunset   || (fx ? fx.sunset   : ""))
        readonly property string wLocation: (widget_data.weatherLocation || (fx ? fx.loc      : ""))

        function wmoToYahoo(w) {
            if (w === 0)  return 32
            if (w === 1)  return 34
            if (w === 2)  return 30
            if (w === 3)  return 26
            if (w === 45 || w === 48) return 20
            if (w === 51 || w === 53 || w === 55) return 9
            if (w === 56 || w === 57) return 8
            if (w === 61) return 11
            if (w === 63 || w === 65) return 12
            if (w === 66 || w === 67) return 10
            if (w === 71 || w === 73 || w === 75) return 16
            if (w === 77) return 13
            if (w >= 80 && w <= 82) return 40
            if (w === 85 || w === 86) return 46
            if (w === 95 || w === 96 || w === 99) return 4
            return 26
        }
        function isoToClock(iso) {   // "2026-07-08T05:34" -> "5:34 AM" (parseTimeMin format)
            if (!iso || iso.indexOf("T") < 0) return ""
            var t = iso.split("T")[1].split(":")
            var h = parseInt(t[0]); var m = t[1]
            var ap = h >= 12 ? "PM" : "AM"
            h = h % 12; if (h === 0) h = 12
            return h + ":" + m + " " + ap
        }
        function fetchFx() {
            if ((widget_data.weatherTemp || "") !== "") return
            // 2026-09-25: coords from WeatherLive (pin, learned place, /etc/geolocation,
            // geoclue, IP) — geoclue alone left other laptops with no temperature at all
            var c = wxLive.weatherCoords()
            if (!c) return
            var lat = c.lat, lon = c.lon
            if (lat === undefined || lon === undefined || (lat === 0 && lon === 0)) return
            var url = "https://api.open-meteo.com/v1/forecast?latitude=" + lat + "&longitude=" + lon
                    + "&current=temperature_2m,relative_humidity_2m,wind_speed_10m,weather_code"
                    + "&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset"
                    + "&temperature_unit=fahrenheit&wind_speed_unit=mph&timezone=auto"
            var xhr = new XMLHttpRequest()
            xhr.onreadystatechange = function() {
                if (xhr.readyState !== XMLHttpRequest.DONE) return
                if (xhr.status !== 200) return
                try {
                    var j   = JSON.parse(xhr.responseText)
                    var cur = j.current || {}
                    var day = j.daily   || {}
                    weather.fx = {
                        temp:    (cur.temperature_2m        !== undefined ? Math.round(cur.temperature_2m) + "°"        : ""),
                        icon:    (cur.weather_code          !== undefined ? String(weather.wmoToYahoo(cur.weather_code)) : ""),
                        hi:      (day.temperature_2m_max && day.temperature_2m_max.length ? Math.round(day.temperature_2m_max[0]) + "°" : ""),
                        lo:      (day.temperature_2m_min && day.temperature_2m_min.length ? Math.round(day.temperature_2m_min[0]) + "°" : ""),
                        hum:     (cur.relative_humidity_2m  !== undefined ? Math.round(cur.relative_humidity_2m) + "%"  : ""),
                        wind:    (cur.wind_speed_10m        !== undefined ? Math.round(cur.wind_speed_10m) + " mph"     : ""),
                        sunrise: weather.isoToClock(day.sunrise && day.sunrise.length ? day.sunrise[0] : ""),
                        sunset:  weather.isoToClock(day.sunset  && day.sunset.length  ? day.sunset[0]  : ""),
                        loc:     ((typeof geo !== "undefined" && geo && geo.place) ? geo.place : "")
                    }
                    weatherCanvas.requestPaint()
                } catch (e) { /* malformed reply — retry timer keeps going */ }
            }
            xhr.open("GET", url)
            xhr.send()
        }
        Timer {
            // Runs ONLY while the WM has no weather data; fires at load, then every
            // 20s — so the widget populates within ~20s of connectivity instead of
            // waiting for the WM's next 30-min tick. Stops itself once real data lands.
            interval: 20000; repeat: true; triggeredOnStart: true
            running: (widget_data.weatherTemp || "") === ""
            onTriggered: weather.fetchFx()
        }
        // ── end QML fallback fetch ─────────────────────────────────────────────

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
            var sr = parseTimeMin(weather.wSunrise)
            var ss = parseTimeMin(weather.wSunset)
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
                var ws      = weather._widgetStyle
                var accent  = (ws && ws["accent"]  !== "" && ws["accent"]  !== undefined) ? Qt.color(ws["accent"])  : ncde.accent
                var glow    = (ws && ws["glow"]    !== "" && ws["glow"]    !== undefined) ? Qt.color(ws["glow"])    : ncde.glow
                var leading = (ws && ws["leading"] !== "" && ws["leading"] !== undefined) ? ws["leading"] : ncde.gilt4.toString()

                // Rose-window roundel on the left
                var rx = 8 + weather.roundelR
                var ry = 12 + weather.roundelR
                P.paintRoundel(ctx, rx, ry, weather.roundelR, accent, glow, leading)

                // Mucha stained-glass weather icon inside the halo ring
                var iconBox = weather.roundelR * 1.5
                ctx.save()
                ctx.beginPath()
                ctx.arc(rx, ry, weather.roundelR * 0.72, 0, Math.PI * 2)
                ctx.clip()
                ctx.translate(rx - iconBox/2, ry - iconBox/2)
                var code = weather.nightIcon(wxLive.liveIcon !== "" ? wxLive.liveIcon : weather.wIcon)
                Wx.drawMuchaWxIcon(ctx, iconBox, iconBox, code, accent, glow, leading)
                ctx.restore()

                // Temperature readout (seven-segment glass) on the right
                var tempRaw = (weather.wTemp || "").replace(/[^0-9\-]/g, "")
                if (tempRaw === "") tempRaw = "--"
                var tx = rx + weather.roundelR + 18
                var ty = 22
                P.paintTempReadout(ctx, tx, ty, tempRaw, 21, 35, 5, "F",
                                   theme.fontFamily, accent, glow, leading)

                // Location caption under temp
                // The town only — a trailing ZIP is dropped always, not just when it
                // doesn't fit (2026-09-25); then step the size down to fit the room.
                var place = ((wxLive.livePlace || weather.wLocation) || "").toUpperCase()
                var room = width - tx - 12
                var capPx = 12 * root.ts
                ctx.font = "italic 600 " + capPx + "px '" + theme.fontFamily + "', sans-serif"
                if (/[A-Z]/.test(place))
                    place = place.replace(/\s+\d[\d-]*$/, "")
                while (capPx > 9 * root.ts && ctx.measureText(place).width > room) {
                    capPx -= 0.5
                    ctx.font = "italic 600 " + capPx + "px '" + theme.fontFamily + "', sans-serif"
                }
                ctx.fillStyle = WallInk.inked(Qt.rgba(weather._gilt4.r, weather._gilt4.g, weather._gilt4.b, 0.8))
                ctx.textBaseline = "alphabetic"
                ctx.fillText(place, tx, ty + 49 + root.capGrow)   // baseline drops as the caption grows, so it never rides up into the digits

                // Mini-cartouche arcade along the bottom
                var chips = [
                    { l: "HI",   v: (weather.wHigh     || "—") },
                    { l: "LO",   v: (weather.wLow      || "—") },
                    { l: "HUM",  v: (weather.wHumidity || "—") },
                    { l: "WIND", v: (weather.wWind     || "—") }
                ]
                var chipY = 110 + root.capGrow
                var chipH = 30 * root.ts
                var totalGap = 8
                var chipW = (width - 16 - totalGap * (chips.length - 1)) / chips.length
                for (var i = 0; i < chips.length; i++) {
                    var cxp = 8 + i * (chipW + totalGap)
                    P.paintMiniCartouche(ctx, cxp, chipY, chipW, chipH,
                                         chips[i].l, chips[i].v,
                                         theme.fontFamily, accent, glow, leading)
                }
            }
        }
    }

    // Brass bezel + glass pane over the whole card (2026-09-24), like the dock
    // icons' bezel + glass cap. On top of everything; takes no input.
    NCDEWidgetPane { anchors.fill: parent; z: 50 }
}
