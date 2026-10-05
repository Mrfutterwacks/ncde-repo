// WeatherLive.qml — intelligent location brain + observation-accurate weather (2026-07-12).
//
// ARCHITECTURE (operator's design): Lelan is the BRAIN. geoclue is one dumb
// sensor; Sentinel is the sister that watches and reports; Lelan reasons about
// where you are from everything it knows — it does NOT blindly trust one sensor.
// An intelligent Lelan LEARNS your places by their WiFi fingerprint, exactly
// like a phone's location cache, but private — nothing ever leaves the machine:
//
//   /.config/ncde/location-memory.json = { "<ssid>": { place, lat, lon }, ... }
//
//   * At a network Lelan has seen before (home = SSID `lelan.network.ssid`), it
//     KNOWS the place instantly and exactly — stable, correct, zero lookups, no
//     wander. Home is home because Lelan recognizes home.
//   * At a new network it resolves once (best available fix) and LEARNS it, so
//     the map fills in wherever you actually go. Free, private, gets smarter.
//   * That one resolved location drives place + weather + (later) sun/moon.
//
// geoclue fuzzes wifi/ip to city-level for privacy and dropped reverse-geocoding
// post-MLS, so it can never be a stable town/ZIP source on its own — which is
// precisely why the brain remembers instead of re-asking. Exact coords come from
// the install-set /etc/geolocation (world-readable) when present; otherwise the
// live geo bridge. Every network failure degrades to "" — never worse.
//
// Overrides the widgets prefer: liveIcon (significant METAR present-weather ->
// Yahoo code, "" when calm) and livePlace (the learned "TOWN ZIP", stable).

import QtQuick
import Qt.labs.platform as Platform
import "mucha-wx-live.js" as Live

Item {
    id: live
    property string liveIcon:  ""    // Yahoo code from a fresh observation (weather or cloud cover); "" = use the model icon
    property string livePlace: ""    // learned "TOWN ZIP"; "" = use widget_data.weatherLocation
    // Weather window (2026-09-24): what the orrery's window shows. Kind/level/wind come from
    // Live.metarSky/alertSky/yahooSky (see mucha-wx-live.js for the accuracy order).
    property var    sky: ({ kind: "clear", level: 1, windDir: -1, windKt: 0, hail: false, pellets: false, source: "none" })
    property var    _obsSky: null     // from the nearest METAR (null = none / stale / failed)
    property var    _alertSky: null   // from NWS active alerts at the point
    function _updateSky() {
        var s = _alertSky ? _alertSky : _obsSky ? _obsSky : Live.yahooSky(widget_data.weatherIcon)
        if (_alertSky && _obsSky) { s.windDir = _obsSky.windDir; s.windKt = _obsSky.windKt; s.hail = _obsSky.hail }
        var o = sky
        if (!o || o.kind !== s.kind || o.level !== s.level || o.windDir !== s.windDir || o.windKt !== s.windKt
               || o.hail !== s.hail || o.pellets !== s.pellets) {
            sky = s
            console.log("NCDE weather window: " + s.kind + " " + s.level + " (" + s.source + ")")
        }
    }
    function fetchAlerts() {
        var c = _skyCoords()
        if (!c) return
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            if (xhr.status !== 200) return          // keep the last answer on a failed poll
            try { live._alertSky = Live.alertSky(JSON.parse(xhr.responseText).features); live._updateSky() }
            catch (e) { /* keep previous */ }
        }
        // NWS covers the US only; elsewhere this 404s and the observed METAR rules alone.
        xhr.open("GET", "https://api.weather.gov/alerts/active?point=" + c.lat.toFixed(4) + "," + c.lon.toFixed(4))
        xhr.setRequestHeader("Accept", "application/geo+json")
        xhr.send()
    }
    function _skyCoords() {
        var pin = _mem["_pinned"], known = _mem[_ssid()]
        return (pin && pin.lat !== undefined) ? { lat: pin.lat, lon: pin.lon }
             : (known && known.lat !== undefined) ? { lat: known.lat, lon: known.lon } : _coords()
    }

    // The learned network->location memory (SSID -> {place,lat,lon}). Private, on disk.
    property var    _mem: ({})
    property bool   _memLoaded: false
    property var _healTried: ({})    // keys already given one town lookup this session
    property string _curSsid: ""     // network we resolved the current livePlace for

    function _cfgDir() {
        var base = Platform.StandardPaths.writableLocation(Platform.StandardPaths.ConfigLocation)
        base = ("" + base).replace(/^file:\/\//, "")
        if (base.length && base[base.length - 1] === "/") base = base.slice(0, -1)
        return base + "/ncde"
    }
    function _memPath() { return _cfgDir() + "/location-memory.json" }

    // Current WiFi fingerprint from Lelan the brain (lelan.network.ssid).
    function _ssid() {
        try {
            if (typeof lelan !== "undefined" && lelan && lelan.network) {
                var s = lelan.network.ssid
                if (s && ("" + s).length) return "" + s
            }
        } catch (e) { }
        return ""   // wired / unknown network -> single "" bucket, still learned
    }

    // Exact, unfuzzed coords: install-set /etc/geolocation first, else geo bridge.
    property var _fileCoords: null
    function _loadFileCoords() {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            try {
                var lines = ("" + xhr.responseText).split("\n").filter(function(l){
                    l = l.trim(); return l.length && l[0] !== "#" })
                if (lines.length >= 2) {
                    var la = parseFloat(lines[0]), lo = parseFloat(lines[1])
                    if (!isNaN(la) && !isNaN(lo) && !(la === 0 && lo === 0))
                        live._fileCoords = { lat: la, lon: lo }
                }
            } catch (e) { }
        }
        try { xhr.open("GET", "file:///etc/geolocation"); xhr.send() } catch (e) { }
    }
    function _liveGeoCoords() {
        if (typeof geo === "undefined" || !geo) return null
        var la = geo.latitude, lo = geo.longitude
        if (la === undefined || lo === undefined || (la === 0 && lo === 0)) return null
        return { lat: la, lon: lo }
    }
    // Home = the current network's LEARNED coords already match the install-set
    // file (i.e. this SSID was previously confirmed as where the static fix
    // applies). Bug fixed 2026-07-13: _coords() used to return _fileCoords
    // unconditionally, so the FIRST time you connected from anywhere new/away,
    // that network got permanently learned as HOME's coordinates instead of
    // resolving from the live geo bridge — the opposite of "the city where the
    // laptop actually is," like a phone. Now the static file only wins once a
    // network is confirmed home; anywhere else prefers the live fix, falling
    // back to the file only if geoclue has no fix at all yet (never worse).
    function _isHomeNetwork() {
        if (!_fileCoords) return false
        var known = _mem[_ssid()]
        if (!known || known.lat === undefined || known.lon === undefined) return false
        return Math.abs(known.lat - _fileCoords.lat) < 0.01
            && Math.abs(known.lon - _fileCoords.lon) < 0.01
    }
    function _coords() {
        if (_isHomeNetwork()) return _fileCoords
        var g = _liveGeoCoords()
        if (g) return g
        return _fileCoords || _ipCoords
    }
    // Last resort (2026-09-25): a laptop whose geoclue has no fix and whose install
    // never wrote /etc/geolocation had NO coords at all, so it showed no temperature
    // and no weather. Ask the network's own IP where it is (town-level) — only when
    // every other source is empty, and only until one of them answers.
    property var _ipCoords: null
    property bool _ipAsked: false
    function _askIp() {
        if (_ipAsked || _fileCoords || _liveGeoCoords()) return
        _ipAsked = true
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            if (xhr.status !== 200) { live._ipAsked = false; return }   // retry on the next 60 s cycle
            try {
                var j = JSON.parse(xhr.responseText)
                if (j.success !== false && !isNaN(parseFloat(j.latitude)) && !isNaN(parseFloat(j.longitude))) {
                    live._ipCoords = { lat: parseFloat(j.latitude), lon: parseFloat(j.longitude) }
                    if (live.livePlace === "" && j.city) live.livePlace = ("" + j.city).toUpperCase()
                    live.fetchMetar()          // straight away: resolvePlace may be waiting on a file read
                    live.resolvePlace()
                } else live._ipAsked = false
            } catch (e) { live._ipAsked = false }
        }
        xhr.open("GET", "https://ipwho.is/?fields=success,latitude,longitude,city")
        xhr.send()
    }
    // The one place-of-truth for every weather consumer (the WM's own fetch keys off
    // geoclue only; the Weather card's fallback asks here instead): the user's pin,
    // then the place learned for this network, then the best live/installed/IP fix.
    function weatherCoords() {
        var pin = _mem["_pinned"], known = _mem[_ssid()]
        if (pin && pin.lat !== undefined) return { lat: pin.lat, lon: pin.lon }
        if (known && known.lat !== undefined) return { lat: known.lat, lon: known.lon }
        return _coords()
    }

    // Load the learned memory. Re-read on every call (2026-07-21): the
    // Settings > Date & Time > Weather tab writes the "_pinned" entry from a
    // different component — a one-shot cache here would ignore the user's pin
    // until relogin. The file is tiny and local; this runs on the existing
    // 60 s resolve cycle, so a fresh pin lands on the widgets within a minute.
    function _loadMem(then) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            try { var j = JSON.parse(xhr.responseText); if (j && typeof j === "object") live._mem = j }
            catch (e) { live._mem = ({}) }
            live._memLoaded = true
            if (then) then()
        }
        try { xhr.open("GET", "file://" + _memPath()); xhr.send() }
        catch (e) { _memLoaded = true; if (then) then() }
    }

    // Persist the learned memory (best-effort; PUT via file://).
    function _saveMem() {
        var xhr = new XMLHttpRequest()
        try { xhr.open("PUT", "file://" + _memPath()); xhr.send(JSON.stringify(live._mem, null, 2)) }
        catch (e) { /* read-only fs or no dir — memory still serves this session */ }
    }

    // Rural fallback (2026-09-24): a house outside any village boundary reverse-
    // geocodes to only "ZIP, County" (operator's own home read "61548"), and a ZIP
    // often spans several towns, so name it after the nearest OSM settlement node.
    // Villages/towns/cities within 8 km win over hamlets; cb("") when none.
    function _nearestTown(lat, lon, cb) {
        var q = '[out:json][timeout:15];node(around:8000,' + lat + ',' + lon
              + ')[place~"^(city|town|village|hamlet)$"];out;'
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var best = "", bestD = 1e9
            try {
                var els = JSON.parse(xhr.responseText).elements || []
                for (var i = 0; i < els.length; i++) {
                    var e = els[i], nm = e.tags && e.tags.name
                    if (!nm) continue
                    var dx = (e.lon - lon) * Math.cos(lat * Math.PI / 180), dy = e.lat - lat
                    var d = Math.sqrt(dx*dx + dy*dy) * (e.tags.place === "hamlet" ? 3 : 1)
                    if (d < bestD) { bestD = d; best = nm }
                }
            } catch (err) { }
            cb(best)
        }
        xhr.open("GET", "https://overpass-api.de/api/interpreter?data=" + encodeURIComponent(q))
        // Overpass answers 406 to Qt's default request headers
        try { xhr.setRequestHeader("User-Agent", "NCDE-Weather/1.0 (desktop widget)") } catch (e) { }
        xhr.send()
    }

    // A learned/pinned place that is only digits (a bare ZIP) gets its town added once.
    function _healPlace(key) {
        var e = live._mem[key]
        if (!e || /[A-Za-z]/.test(e.place) || e.lat === undefined) return
        if (live._healTried[key]) return
        live._healTried[key] = true
        _nearestTown(e.lat, e.lon, function(town) {
            if (!town) return
            e.place = town + " " + e.place
            live._mem[key] = e
            live._saveMem()
            live.livePlace = e.place
        })
    }

    // THE BRAIN: decide the place for the current network.
    function resolvePlace() {
        _loadMem(function() {
            var ssid = _ssid()
            // USER PIN (2026-07-21, Settings > Date & Time > Weather): the
            // answer to GeoIP wrong-city — a small town's IP often "locates"
            // to the ISP's hub city (operator's own machine read Chicago,
            // 170 km off). A typed town is the user TELLING Lelan where they
            // are; it outranks every sensor until cleared (empty field =
            // automatic brain, exactly the behavior above this line).
            var pin = live._mem["_pinned"]
            if (pin && pin.place && pin.lat !== undefined && pin.lon !== undefined) {
                live._curSsid = ssid
                if (live.livePlace !== pin.place) live.livePlace = pin.place
                live._healPlace("_pinned")
                live.fetchMetar()
                return
            }
            var known = live._mem[ssid]
            if (known && known.place) {                 // recognized -> instant, stable, correct
                live._curSsid = ssid
                if (live.livePlace !== known.place) live.livePlace = known.place
                live._healPlace(ssid)
                live.fetchMetar()
                return
            }
            // new network: resolve once from exact coords, then LEARN it.
            var c = _coords(); if (!c) { live._askIp(); return }
            var fromIp = (c === live._ipCoords)   // town-level guess: use it, never LEARN it
            var url = "https://nominatim.openstreetmap.org/reverse?format=json&addressdetails=1&zoom=18"
                    + "&lat=" + c.lat + "&lon=" + c.lon
            var xhr = new XMLHttpRequest()
            xhr.onreadystatechange = function() {
                if (xhr.readyState !== XMLHttpRequest.DONE) return
                if (xhr.status !== 200) return
                try {
                    var a = (JSON.parse(xhr.responseText).address) || {}
                    var town = a.town || a.village || a.city || a.hamlet || a.suburb || a.municipality || ""
                    var zip  = a.postcode || ""
                    var learn = function(s) {
                        if (s === "") return
                        live.livePlace = s
                        live._curSsid = ssid
                        if (!fromIp) {
                            live._mem[ssid] = { place: s, lat: c.lat, lon: c.lon }  // LEARN
                            live._saveMem()
                        }
                        live.fetchMetar()
                    }
                    if (town) learn(zip ? town + " " + zip : town)
                    else live._nearestTown(c.lat, c.lon, function(t) {
                        learn(t && zip ? t + " " + zip : (t || zip))
                    })
                } catch (e) { /* keep previous */ }
            }
            xhr.open("GET", url)
            try { xhr.setRequestHeader("User-Agent", "NCDE-Weather/1.0 (desktop widget)") } catch (e) { }
            xhr.send()
        })
    }

    // Nearest observed present-weather -> icon override (uses the resolved coords).
    function fetchMetar() {
        var ssid = _ssid()
        var pin = _mem["_pinned"]
        var known = _mem[ssid]
        var c = (pin && pin.lat !== undefined) ? { lat: pin.lat, lon: pin.lon }
              : (known && known.lat !== undefined) ? { lat: known.lat, lon: known.lon } : _coords()
        if (!c) return
        var bbox = (c.lat - 0.6) + "," + (c.lon - 0.9) + "," + (c.lat + 0.6) + "," + (c.lon + 0.9)
        var url = "https://aviationweather.gov/api/data/metar?format=json&bbox=" + bbox
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            if (xhr.status !== 200) return
            try {
                var arr = JSON.parse(xhr.responseText)
                var m = Live.nearestMetar(arr, c.lat, c.lon)
                live.liveIcon = Live.metarIcon(m, Date.now() / 1000)
                live._obsSky = Live.metarSky(m, Date.now() / 1000)
                live._updateSky()
            } catch (e) { /* keep previous */ }
        }
        xhr.open("GET", url); xhr.send()
    }

    // Re-resolve whenever the network changes (Lelan reports it) — that's how the
    // place follows you to a new town and learns it, and snaps back home instantly.
    Connections {
        target: (typeof lelan !== "undefined") ? lelan : null
        ignoreUnknownSignals: true
        function onNetworkChanged() { live.resolvePlace() }
    }

    Component.onCompleted: { _loadFileCoords(); resolvePlace() }
    // METAR refresh (hourly + storm specials); 15-min poll catches specials.
    Timer { interval: 900000; repeat: true; running: true; onTriggered: live.fetchMetar() }
    // NWS alerts every 5 min (warnings are short-fused); forecast changes re-derive the fallback.
    Timer { interval: 300000; repeat: true; running: true; triggeredOnStart: true; onTriggered: live.fetchAlerts() }
    Connections { target: widget_data; function onWeatherChanged() { live._updateSky() } }
    // Re-check the network/place until resolved, then it just confirms.
    // The IP fallback is checked here too, independent of resolvePlace(): with file://
    // reads blocked (QML_XHR_ALLOW_FILE_READ unset) _loadMem's callback never fires, and
    // a laptop with no geoclue fix would otherwise wait forever with no weather.
    Timer { interval: 60000; repeat: true; running: true
            onTriggered: { live.resolvePlace(); if (!live.weatherCoords()) live._askIp() } }
    Timer { interval: 5000; running: true; onTriggered: if (!live.weatherCoords()) live._askIp() }
}
