pragma Singleton
import QtQuick
import "ncde-color.js" as Col

// ShellLight — ONE light for the whole shell (2026-09-25, BEAUTIFY-NEXT #25).
// Every highlight used to pick its own "upper-left": the window frame's specular
// band and jewel glints, the icon bezels' glint, the glass domes' crescent and
// catch-light, the glass surface's shine and edge hairlines, the widget bezels'
// streak and glint. Most sat near 120°, but not all (the glass catch-light sat at
// 135° and landed as a loose white blob in the dock's round cap). They all read
// their direction and colour from here now, so metal, glass and lead are lit by
// the same lamp. Static: nothing moves, nothing animates.
//
// The light follows the sun (2026-09-25, BEAUTIFY-NEXT #26). Between sunrise and
// sunset (the weather's own times, widget_data.weatherSunrise/Sunset) the light
// crosses from low left (-145°) through overhead (-90°) to low right (-35°); low
// sun is softer (strength) and warmer (warmth, toward ncde.lamp). After sunset the
// frames' lamp takes over: the light returns to the upper left in lamplight.
// It is re-read every 5 minutes and snaps to 5° steps — a quiet repositioning,
// never a tween, so nothing animates (operator rule: no new animations).
// Canvas painters repaint on `signature`; bindings follow on their own.
//
// Direction is screen space: (lx, ly) is a unit vector pointing TOWARD the light.
// 0° = right, -90° = straight up; -120° = up and a little to the left.
QtObject {
    id: light

    // ── the sun ─────────────────────────────────────────────────────────────
    property int _nowMin: -1
    property Timer _tick: Timer {
        interval: 300000; running: true; repeat: true; triggeredOnStart: true
        onTriggered: { var d = new Date(); light._nowMin = d.getHours() * 60 + d.getMinutes() }
    }
    // "6:52 AM" / "18:52" → minutes after midnight, or -1
    function _min(s) {
        if (!s) return -1
        var parts = ("" + s).trim().split(" "), tp = parts[0].split(":")
        if (tp.length < 2) return -1
        var h = parseInt(tp[0]), m = parseInt(tp[1])
        if (isNaN(h) || isNaN(m)) return -1
        if (parts.length >= 2) {
            var ap = parts[1].toUpperCase()
            if (ap === "PM" && h !== 12) h += 12
            if (ap === "AM" && h === 12) h = 0
        }
        return h * 60 + m
    }
    readonly property bool _wd: typeof widget_data !== "undefined" && widget_data !== null
    readonly property int sunrise: { var v = _wd ? _min(widget_data.weatherSunrise) : -1; return v >= 0 ? v : 360 }
    readonly property int sunset:  { var v = _wd ? _min(widget_data.weatherSunset)  : -1; return v > sunrise ? v : 1200 }
    // 0 at sunrise .. 1 at sunset; outside that it is night
    readonly property real dayFrac: _nowMin < 0 ? 0.25 : (_nowMin - sunrise) / (sunset - sunrise)
    readonly property bool night: dayFrac < 0 || dayFrac > 1
    readonly property real elevation: night ? 0 : Math.sin(Math.PI * dayFrac)   // 0 horizon .. 1 noon

    readonly property real azimuth: night ? -120 : Math.round((-145 + 110 * dayFrac) / 5) * 5
    // how bright highlights are: full by mid-morning, softer near the horizon, lamplit at night
    readonly property real strength: night ? 0.72
                                     : Math.round((0.74 + 0.26 * Math.min(1, elevation / 0.5)) * 20) / 20
    // how much of the lamp's warmth is in the light: golden hours, and all night
    // Night Light (Settings > Display) already warms the whole screen to as low as
    // 2700K — "the desktop is more gaslit" (operator). While it is actually on (all
    // the time, or after sunset when set to Auto), the lamp's warmth steps back to a
    // third so the two never stack into orange highlights.
    readonly property bool _st: typeof settings !== "undefined" && settings !== null
    readonly property bool nightLightActive: _st && settings.nightLightOn === true
                                             && (settings.nightLightAuto !== true || night)
    readonly property real warmth: Math.round((night ? 0.45
                                   : Math.max(0, (0.42 - elevation) / 0.42) * 0.55)
                                   * (nightLightActive ? 0.35 : 1) * 20) / 20
    // Outside the shell the app's own engine copy is frozen: take the live palette
    // (IrisLive, 2026-09-26) so the one light is the same colour in every app.
    readonly property var _live: IrisLive.live
    function _tok(n) {
        if (_live && _live[n] !== undefined && _live[n] !== null) return Qt.color(_live[n])
        return (typeof ncde !== "undefined" && ncde && ncde[n] !== undefined) ? ncde[n] : undefined
    }
    readonly property color warmTone: Col.tone(_tok("lamp") !== undefined ? _tok("lamp") : Qt.rgba(0.96, 0.74, 0.36, 1), 90, 30)
    // one string that changes whenever anything a painter reads changes
    readonly property string signature: azimuth + "/" + strength + "/" + warmth + "/" + tone
    readonly property real _rad: azimuth * Math.PI / 180
    readonly property real lx: Math.cos(_rad)        // -0.50
    readonly property real ly: Math.sin(_rad)        // -0.87

    // Where the light's highlight sits on a round thing, as a fraction of its size
    // from the top-left: k = how far out from the centre (0 centre .. 0.5 rim).
    function hx(k) { return 0.5 + lx * k }
    function hy(k) { return 0.5 + ly * k }
    // The same, for a flat face: how strongly an edge facing (nx, ny) catches the
    // light (0..1). Top edge = (0,-1), left edge = (-1,0).
    function facing(nx, ny) { return Math.max(0, nx * lx + ny * ly) }
    // Rotation (degrees) that turns a top-to-bottom gradient so its bright end
    // faces the light — for circles, which look the same at any rotation.
    readonly property real gradientTurn: azimuth + 90   // -30

    // The light's colour: near-white with a breath of the palette's glow in it
    // (the same lightTone NCDEGlassSurface already used), so a green palette gets
    // green-white shine, never cold #fff. Falls back to white without a palette.
    readonly property color dayTone: _tok("glow") !== undefined ? Col.tone(_tok("glow"), 97, 6) : Qt.rgba(1, 1, 1, 1)
    readonly property color tone: warmth > 0 ? Col.mix(dayTone, warmTone, warmth) : dayTone
    // Glass with its own glow (NCDEGlassSurface's per-surface Filigree colour) warms the same way
    function warmed(c) { return warmth > 0 ? Col.mix(c, warmTone, warmth) : c }
    function lt(a) { return Qt.rgba(tone.r, tone.g, tone.b, a * strength) }
    function css(a) {
        return "rgba(" + Math.round(tone.r * 255) + "," + Math.round(tone.g * 255) + ","
                       + Math.round(tone.b * 255) + "," + (a * strength) + ")"
    }
}
