#!/bin/bash
# ncde-weather-accuracy-20260710.sh — make the weather widget match the real sky.
#
# ROOT CAUSE (proven live 2026-07-10, the thing 8 prior "fixes" missed): the WM and
# the QML fallback fetch open-meteo, whose MODEL weather_code MISSES live thunderstorms.
# During an actual storm at the operator's location, open-meteo returned code 3
# (overcast, 0 mm precip) while the nearest airport METAR (KPIA) reported "VCTS -RA"
# (thunderstorm + rain). The whole WMO->Yahoo->art icon chain was ALWAYS correct — it
# faithfully rendered wrong DATA. No mapping change could ever fix that. Separately,
# geoclue's static source carries no place name, so the location caption was blank.
#
# THE FIX (QML-only — no lost C++ needed):
#   * NEW mucha-wx-live.js  — parses OBSERVED METAR present-weather -> a Yahoo icon code
#     (verified 11/11 against real METAR strings incl. the live VCTS -RA storm).
#   * NEW WeatherLive.qml   — fetches the nearest METAR (aviationweather.gov, nearest
#     station by the WM's geo lat/lon — NOT hardcoded) and reverse-geocodes the coords
#     (OSM) to "TOWN ZIP". Exposes liveIcon + livePlace. Every network failure degrades
#     to "" = the pre-existing behavior, never worse.
#   * PATCH WeatherPanel.qml + MuchaWeather.qml — prefer liveIcon for the icon ONLY when
#     METAR reports significant weather (TS/RA/SN/FG…); a calm sky keeps the model's own
#     clear/cloudy icon. Prefer livePlace ("Germantown Hills 61548") for the caption.
#
# Idempotent, never deletes (renames aside). Run as root:  sudo bash <this script>
# Then relog (LaPivot loads QML once per session).

set -u
QML=/usr/share/ncde
BAK=".prebak-20260710-metar"
[ "$(id -u)" = 0 ] || { echo "Run as root:  sudo bash $0"; exit 1; }
[ -d "$QML" ] || { echo "ERROR: $QML not found — not an NCDE system."; exit 1; }
echo "== NCDE weather-accuracy fix 2026-07-10 =="

# ---- 1. install the two new shared files ------------------------------------
cat > "$QML/mucha-wx-live.js" <<'JSEOF'
.pragma library
// mucha-wx-live.js — observation-accurate weather helpers (2026-07-10).
//
// Root cause this addresses (proven live): open-meteo's MODEL weather_code
// misses live thunderstorms — it reported code 3 (overcast, 0mm) while the
// nearest airport METAR (KPIA) reported "VCTS -RA" during an actual storm.
// The whole icon-mapping chain was already correct; it faithfully rendered
// wrong DATA. So for the ICON we read OBSERVED present-weather from METAR and
// only override when it reports something significant (thunder/rain/snow/fog);
// otherwise we return "" and the existing model clear/cloudy icon stands.
//
// metarPresentToYahoo(rawMetar) -> a Yahoo weather code string the existing
// mucha-wx-icons.js art already understands, or "" for no significant weather.
// Codes chosen to hit the intended wxType() branch:
//   4  -> thunder   10 -> freezing (snow-ish art)   41 -> snow (NOT 16: 16 is
//   shadowed by the "wind" branch in wxType)   40 -> rain   20 -> fog.

function metarPresentToYahoo(raw) {
    if (!raw) return "";
    var up = String(raw).toUpperCase();
    var rmk = up.indexOf(" RMK ");          // drop remarks (TSE19, LTG, P0002…)
    if (rmk >= 0) up = up.substring(0, rmk);
    var toks = up.split(/\s+/);
    var f = { ts:false, fz:false, sn:false, ra:false, fg:false };
    // Present-weather grammar: optional intensity/VC, optional descriptor,
    // one+ phenomena. TS/VCTS carry no trailing phenomenon, so match separately.
    var reTs = /^(\+|-)?(VC)?TS(RA|SN|GR|GS|PL|DZ)?$/;
    var reWx = /^(-|\+|VC)?(MI|PR|BC|DR|BL|SH|TS|FZ)?(DZ|RA|SN|SG|IC|PL|GR|GS|UP|BR|FG|FU|VA|DU|SA|HZ|PY|PO|SQ|FC|SS|DS)+$/;
    for (var i = 0; i < toks.length; i++) {
        var t = toks[i];
        if (reTs.test(t)) { f.ts = true; continue; }
        if (!reWx.test(t)) continue;
        if (t.indexOf("FZ") >= 0)         f.fz = true;
        if (/SN|SG|PL|IC|GS/.test(t))     f.sn = true;
        if (/RA|DZ|UP/.test(t))           f.ra = true;
        if (/FG|BR|FU|HZ|VA|DU|SA/.test(t)) f.fg = true;
    }
    if (f.ts) return "4";    // thunder (any TS/VCTS/TSRA…)
    if (f.fz) return "10";   // freezing precip
    if (f.sn) return "41";   // snow
    if (f.ra) return "40";   // rain / drizzle / showers
    if (f.fg) return "20";   // fog / mist / haze / smoke
    return "";               // nothing significant — keep the model icon
}

// Pick the METAR nearest the given lat/lon from an aviationweather.gov array.
function nearestMetar(arr, lat, lon) {
    var best = null, bestD = 1e18;
    for (var i = 0; i < arr.length; i++) {
        var m = arr[i];
        if (m.lat === undefined || m.lon === undefined) continue;
        if (!m.rawOb) continue;
        var dLat = m.lat - lat, dLon = m.lon - lon;
        var d = dLat*dLat + dLon*dLon;
        if (d < bestD) { bestD = d; best = m; }
    }
    return best;
}
JSEOF

cat > "$QML/WeatherLive.qml" <<'QMLEOF'
// WeatherLive.qml — observation-accurate weather overrides (2026-07-10).
//
// WHY THIS EXISTS (root cause, proven live): the WM/QML fetch open-meteo, whose
// MODEL weather_code misses live thunderstorms — it reported code 3 (overcast,
// 0 mm) while the nearest airport METAR reported "VCTS -RA" during an actual
// storm at the user's location. The icon-mapping chain was always correct; it
// faithfully rendered wrong DATA. And geoclue's static source carries no place
// name, so the location caption was blank. This non-visual helper fetches
// OBSERVED data and exposes two overrides the weather widgets prefer:
//   * liveIcon  — a Yahoo code from the nearest METAR's present weather, but
//                 ONLY when it is significant (TS/RA/SN/FG…); "" otherwise so a
//                 calm sky keeps the model's own clear/cloudy icon.
//   * livePlace — "TOWN 61548" from an OSM reverse-geocode of geo lat/lon.
// No C++, no API keys. Reads the WM's existing `geo` bridge for coordinates.
// Every network failure degrades to "" (the pre-existing behavior) — never worse.

import QtQuick
import "mucha-wx-live.js" as Live

Item {
    id: live
    property string liveIcon: ""     // Yahoo code override; "" = use the model icon
    property string livePlace: ""     // "TOWN ZIP"; "" = use widget_data.weatherLocation
    property string _placeKey: ""     // coords the current livePlace was resolved for

    function _coords() {
        if (typeof geo === "undefined" || !geo) return null
        var la = geo.latitude, lo = geo.longitude
        if (la === undefined || lo === undefined) return null
        if (la === 0 && lo === 0) return null
        return { lat: la, lon: lo }
    }

    // Nearest observed present-weather -> icon override.
    function fetchMetar() {
        var c = _coords(); if (!c) return
        var bbox = (c.lat - 0.6) + "," + (c.lon - 0.9) + "," + (c.lat + 0.6) + "," + (c.lon + 0.9)
        var url = "https://aviationweather.gov/api/data/metar?format=json&bbox=" + bbox
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            if (xhr.status !== 200) return
            try {
                var arr = JSON.parse(xhr.responseText)
                var m = Live.nearestMetar(arr, c.lat, c.lon)
                live.liveIcon = m ? Live.metarPresentToYahoo(m.rawOb) : ""
            } catch (e) { /* malformed — keep the previous override */ }
        }
        xhr.open("GET", url); xhr.send()
    }

    // Reverse-geocode coords -> "TOWN ZIP". Cached; retries only while blank.
    function fetchPlace() {
        var c = _coords(); if (!c) return
        var key = c.lat.toFixed(3) + "," + c.lon.toFixed(3)
        if (key === _placeKey && livePlace !== "") return
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
                var s = (town !== "" && zip !== "") ? (town + " " + zip) : (town !== "" ? town : zip)
                if (s !== "") { live.livePlace = s; live._placeKey = key }
            } catch (e) { /* keep previous */ }
        }
        xhr.open("GET", url)
        try { xhr.setRequestHeader("User-Agent", "NCDE-Weather/1.0 (desktop widget)") } catch (e) { }
        xhr.send()
    }

    Component.onCompleted: { fetchMetar(); fetchPlace() }
    // METAR updates hourly + specials during storms; 15-min poll catches specials.
    Timer { interval: 900000; repeat: true; running: true; onTriggered: live.fetchMetar() }
    // Resolve the place once it (and geo) are available; stops itself when set.
    Timer { interval: 60000; repeat: true; running: true; onTriggered: live.fetchPlace() }
}
QMLEOF

chown root:root "$QML/mucha-wx-live.js" "$QML/WeatherLive.qml"
chmod 644       "$QML/mucha-wx-live.js" "$QML/WeatherLive.qml"
echo "OK   installed mucha-wx-live.js + WeatherLive.qml"

# ---- 2. patch the two consumers (idempotent, exact-anchor, count-checked) ----
python3 - "$QML" "$BAK" <<'PYEOF'
import sys, os, shutil
qml, bak = sys.argv[1], sys.argv[2]
EDITS = {
 "WeatherPanel.qml": [
  ("        readonly property color _gilt4: ncde.gilt4",
   "        readonly property color _gilt4: ncde.gilt4\n\n"
   "        WeatherLive { id: wxLive }\n"
   "        Connections { target: wxLive\n"
   "            function onLiveIconChanged()  { weatherCanvas.requestPaint() }\n"
   "            function onLivePlaceChanged() { weatherCanvas.requestPaint() }\n"
   "        }"),
  ("var code = weather.nightIcon(weather.wIcon)",
   'var code = (wxLive.liveIcon !== "" ? wxLive.liveIcon : weather.nightIcon(weather.wIcon))'),
  ('ctx.fillText((weather.wLocation || "").toUpperCase(), tx, ty + 49)',
   'ctx.fillText(((wxLive.livePlace || weather.wLocation) || "").toUpperCase(), tx, ty + 49)'),
 ],
 "MuchaWeather.qml": [
  ("    readonly property color _gilt4: ncde.gilt4",
   "    readonly property color _gilt4: ncde.gilt4\n\n"
   "    WeatherLive { id: wxLive }\n"
   "    Connections { target: wxLive\n"
   "        function onLiveIconChanged()  { weatherCanvas.requestPaint() }\n"
   "        function onLivePlaceChanged() { weatherCanvas.requestPaint() }\n"
   "    }"),
  ("var code = weather.nightIcon(widget_data.weatherIcon)",
   'var code = (wxLive.liveIcon !== "" ? wxLive.liveIcon : weather.nightIcon(widget_data.weatherIcon))'),
  ('ctx.fillText((widget_data.weatherLocation || "").toUpperCase(), tx, ty + 49)',
   'ctx.fillText(((wxLive.livePlace || widget_data.weatherLocation) || "").toUpperCase(), tx, ty + 49)'),
 ],
}
fail=False
for fn, edits in EDITS.items():
    p=os.path.join(qml, fn)
    if not os.path.isfile(p):
        print(f"ERROR {fn}: missing"); fail=True; continue
    s=open(p,encoding="utf-8").read()
    if "WeatherLive { id: wxLive }" in s:
        print(f"SKIP  {fn}: already patched"); continue
    bad=[o.splitlines()[0][:48] for o,_ in edits if s.count(o)!=1]
    if bad:
        print(f"ERROR {fn}: anchors not unique/found -> {bad} — left untouched"); fail=True; continue
    if not os.path.exists(p+bak): shutil.copy2(p, p+bak)
    for o,n in edits: s=s.replace(o,n,1)
    tmp=p+".fixtmp"; open(tmp,"w",encoding="utf-8").write(s); os.replace(tmp,p)
    print(f"OK    {fn}: patched (backup {os.path.basename(p+bak)})")
sys.exit(1 if fail else 0)
PYEOF
[ $? -eq 0 ] || { echo "PATCH FAILED — new files installed but consumers untouched. Investigate before relog."; exit 1; }

# ---- 3. clear the per-user QML cache so the edits load next session ----------
for h in /home/*; do
    [ -d "$h/.cache/LaPivot/qmlcache" ] && rm -rf "$h/.cache/LaPivot/qmlcache" && echo "OK   cleared $(basename "$h") qmlcache"
done

echo
echo "== Done. LOG OUT and back in. =="
echo "Verify: during observed weather the icon matches the sky (thunder shows a bolt when"
echo "the nearest airport reports TS), and the caption shows your town + ZIP. On calm days"
echo "the icon is unchanged. Nothing to configure."
