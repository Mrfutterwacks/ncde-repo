// WallInk.qml — "wallpaper ink" state, shared by every shell file (2026-09-24).
// A palette picked from Filigree → Iris → "From your wallpaper" re-inks shell
// text in the wallpaper's own hue (math in ncde-ink.js). Text sites wrap their
// colour: color: WallInk.inked(ncde.gilt4). Off = the colour passes through.
//
// Why a singleton: the first cut hung inked()/setInk() on ThemeTokens.qml, but
// the global `theme` context property is LaPivot's C++ Theme object —
// ThemeTokens.qml is never instantiated. Every theme.inked(...) binding threw
// "Property 'inked' of object Theme is not a function", so the text fell back
// to black and never followed a theme change.
//
// pragma Singleton; registered in qmldir: singleton WallInk 1.0 WallInk.qml
pragma Singleton
import QtQuick 2.15
import "ncde-ink.js" as Ink

QtObject {
    property bool inkOn: false
    property real inkHue: 0
    // bumps on every change so Canvas painters can requestPaint()
    property int  inkSerial: 0
    readonly property string _inkPath: settings.configBase + "wallpaper-ink.json"

    function inked(c) {
        inkSerial                          // binding dependency: re-evaluate on change
        return Ink.color(c)
    }
    function setInk(on, hue) {
        Ink.set(on, hue)
        inkHue = Ink.hue
        inkOn = Ink.on
        inkSerial++
        // XHR PUT overwrites without truncating: a shorter write ("true" after
        // "false") would leave a stray "}" and the file would no longer parse.
        // Pad to a fixed width — JSON ignores trailing whitespace.
        var s = JSON.stringify({ on: Ink.on, hue: Ink.hue }, null, 2)
        while (s.length < 96) s += " "
        var x = new XMLHttpRequest()
        try { x.open("PUT", "file://" + _inkPath); x.send(s) } catch (e) { }
    }
    Component.onCompleted: {
        var x = new XMLHttpRequest()
        x.onreadystatechange = function() {
            if (x.readyState !== XMLHttpRequest.DONE) return
            var j
            try { j = JSON.parse(x.responseText) } catch (e) { return }
            if (!j || j.on !== true) return
            Ink.set(true, j.hue)
            inkHue = Ink.hue; inkOn = true; inkSerial++
        }
        try { x.open("GET", "file://" + _inkPath); x.send() } catch (e) { /* no ink file — ink stays off */ }
    }
}
