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

// The icon from a FRESH observation (2026-10-01). Same rule as metarSky (the orrery): an observation
// <= 2 h old decides. Significant present weather -> as metarPresentToYahoo; otherwise the OBSERVED
// cloud cover (it is not raining because the station says so — the forecast's rain icon must not stay up
// after the rain has stopped, which is what the operator saw: orrery cloudy, card still raining).
// No/stale observation -> "" (the forecast icon speaks). Day codes; the widgets map them for night.
function metarIcon(m, nowSec) {
    if (!m || !m.rawOb) return "";
    if (m.obsTime && nowSec && nowSec - m.obsTime > 7200) return "";        // stale
    var sig = metarPresentToYahoo(m.rawOb);
    if (sig !== "") return sig;
    var cov = m.cover || "";
    if (cov === "OVC" || cov === "OVX") return "26";   // overcast
    if (cov === "BKN") return "28";                     // mostly cloudy
    if (cov === "SCT") return "30";                     // partly cloudy
    if (cov === "FEW") return "34";                     // fair
    if (cov === "CLR" || cov === "SKC" || cov === "CAVOK") return "32";   // clear
    return "";                                          // cover not reported -> forecast
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

// ── Weather window (2026-09-24) ─────────────────────────────────
// The Space card's orrery is seen through a window that shows the real
// weather outside. Sky kinds, in the order the painter knows them:
//   clear | cloudy | fog | rain | storm | sleet | snow | hail | tornado
// level 1..3 = light / moderate / heavy (METAR "-" / none / "+").
// Accuracy order: an NWS Tornado Warning or Severe Thunderstorm Warning for
// the exact point beats everything; then the nearest station's OBSERVED
// present weather (METAR, <= 2 h old); only with neither does the forecast
// icon speak. Wind (METAR wdir/wspd) slants rain and snow the real way.
function metarSky(m, nowSec) {
    if (!m || !m.rawOb) return null;
    if (m.obsTime && nowSec && nowSec - m.obsTime > 7200) return null;   // stale
    var up = String(m.rawOb).toUpperCase();
    var rmk = up.indexOf(" RMK ");
    if (rmk >= 0) up = up.substring(0, rmk);
    var toks = up.split(/\s+/);
    var sky = { kind: "clear", level: 1 };
    var hail = false, pellets = false;   // extras a higher-ranked kind still shows
    var rank = { clear:0, cloudy:1, fog:2, rain:3, sleet:4, snow:5, hail:6, storm:7, tornado:8 };
    function take(kind, lvl) {
        if (rank[kind] > rank[sky.kind] || (kind === sky.kind && lvl > sky.level))
            sky = { kind: kind, level: lvl };
    }
    var reWx = /^(-|\+|VC)?(MI|PR|BC|DR|BL|SH|TS|FZ)?((?:DZ|RA|SN|SG|IC|PL|GR|GS|UP|BR|FG|FU|VA|DU|SA|HZ|PY|PO|SQ|FC|SS|DS)*)$/;
    for (var i = 1; i < toks.length; i++) {
        var t = toks[i], mm = reWx.exec(t);
        if (!mm || (mm[2] === undefined && !mm[3])) continue;
        var pre = mm[1] || "", desc = mm[2] || "", ph = mm[3] || "";
        if (pre === "VC" && ph.indexOf("FC") < 0 && desc !== "TS") continue;  // "in the vicinity" isn't here
        var lvl = pre === "-" ? 1 : pre === "+" ? 3 : 2;
        if (ph.indexOf("FC") >= 0) { take("tornado", 3); continue; }   // funnel cloud / tornado
        if (desc === "TS") { take("storm", ph ? Math.max(2, lvl) : 2); if (/GR|GS/.test(ph)) hail = true; continue; }
        if (/GR|GS/.test(ph)) { take("hail", lvl); hail = true; }
        if (/PL|IC/.test(ph) || (desc === "FZ" && /RA|DZ/.test(ph))) { take("sleet", lvl); pellets = true; }
        if (/SN|SG/.test(ph)) take("snow", lvl);
        if (/RA|DZ|UP/.test(ph) && desc !== "FZ") take("rain", /DZ/.test(ph) && !/RA/.test(ph) ? 1 : lvl);
        if (/FG|BR|FU|HZ|VA|DU|SA/.test(ph)) take("fog", /FG/.test(ph) ? 2 : 1);
        if (ph === "SQ") take("storm", 2);
    }
    if (sky.kind === "clear") {
        var cov = m.cover || "";
        if (cov === "OVC" || cov === "OVX") sky = { kind: "cloudy", level: 2 };
        else if (cov === "BKN") sky = { kind: "cloudy", level: 1 };
    }
    sky.hail = hail; sky.pellets = pellets;
    var wd = Number(m.wdir), ws = Number(m.wspd);
    sky.windDir = isNaN(wd) ? -1 : wd;          // -1 = variable
    sky.windKt  = isNaN(ws) ? 0 : ws;
    sky.source  = "observed " + (m.icaoId || "");
    return sky;
}

// NWS active-alert features for the point -> sky override, or null.
function alertSky(features) {
    if (!features || !features.length) return null;
    var storm = null;
    for (var i = 0; i < features.length; i++) {
        var ev = ((features[i].properties || {}).event || "");
        if (ev === "Tornado Warning") return { kind: "tornado", level: 3, source: "NWS " + ev };
        if (ev === "Severe Thunderstorm Warning") storm = { kind: "storm", level: 3, source: "NWS " + ev };
    }
    return storm;
}

// Forecast icon (Yahoo code) -> sky: the last resort when nothing is observed.
function yahooSky(code) {
    var c = parseInt(code, 10);
    if (isNaN(c)) return { kind: "clear", level: 1, source: "none" };
    var k = c === 0 ? "tornado" : (c <= 4 || c === 37 || c === 38 || c === 39 || c === 45 || c === 47) ? "storm"
          : (c === 5 || c === 6 || c === 7 || c === 8 || c === 10 || c === 18) ? "sleet"
          : (c === 17 || c === 35) ? "hail"
          : (c === 9 || c === 11 || c === 12 || c === 40) ? "rain"
          : (c >= 13 && c <= 16) || (c >= 41 && c <= 43) || c === 46 ? "snow"
          : (c >= 19 && c <= 22) ? "fog"
          : (c >= 26 && c <= 28) ? "cloudy" : "clear";
    var lvl = (c === 41 || c === 43 || c === 12 || c === 3 || c === 0) ? 3 : 2;
    return { kind: k, level: lvl, source: "forecast " + c };
}
