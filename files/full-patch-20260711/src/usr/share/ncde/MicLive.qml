// MicLive.qml — non-visual live microphone-peak reader (2026-07-12).
//
// Mirrors the proven WeatherLive.qml / StatsLive.qml pattern: the userspace
// helper `ncde-mic-helper` opens a `parec` record stream on the default
// PulseAudio/PipeWire source and writes the true input peak ~10x/sec to
// $XDG_RUNTIME_DIR/ncde-mic.json (fallback ~/.cache/ncde/mic.json). This file
// reads it via file:// XHR and republishes it as a QML property.
//
// WHY (Sound-tab gap): the INPUT "Level" meter in SoundTab.qml was bound to
// settings.inputLevel — a PERSISTED preference with no live source — so the bar
// never moved. The stripped LaPivot binary exposes no live source-peak property
// and cannot be recompiled, so the meter is bridged here. Nothing touches a binary.
//
// Exposes (read):
//   level   0..100  true input peak of the last ~100 ms window (0 in silence)
//   live    bool    a record stream is actually open on a source
//   ts      int     unix epoch of the current sample

import QtQuick
import Qt.labs.platform as Platform

Item {
    id: mic
    visible: false   // pure data brain, never drawn

    property int  level: 0     // 0..100
    property bool live:  false
    property int  ts:    0

    function _strip(u) {
        u = ("" + u).replace(/^file:\/\//, "")
        if (u.length && u[u.length - 1] === "/") u = u.slice(0, -1)
        return u
    }
    function _runtimePath() {
        var b = _strip(Platform.StandardPaths.writableLocation(Platform.StandardPaths.RuntimeLocation))
        return b.length ? (b + "/ncde-mic.json") : ""
    }
    function _cachePath() {
        var b = _strip(Platform.StandardPaths.writableLocation(Platform.StandardPaths.GenericCacheLocation))
        return b.length ? (b + "/ncde/mic.json") : ""
    }

    function _readPath(path, onMiss) {
        if (!path) { if (onMiss) onMiss(); return }
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var body = "" + (xhr.responseText || "")
            if (body.trim() === "") { if (onMiss) onMiss(); return }
            try { mic._apply(JSON.parse(body)) }
            catch (e) { if (onMiss) onMiss() }
        }
        try { xhr.open("GET", "file://" + path); xhr.send() }
        catch (e) { if (onMiss) onMiss() }
    }

    function refresh() {
        _readPath(_runtimePath(), function() { mic._readPath(mic._cachePath(), null) })
    }

    function _apply(j) {
        if (!j || typeof j !== "object") return
        if (j.ts !== undefined) ts = j.ts | 0
        var lv = (j.level !== undefined && j.level !== null) ? (j.level | 0) : 0
        if (lv < 0) lv = 0; else if (lv > 100) lv = 100
        level = lv
        live = (j.live === true)
    }

    Component.onCompleted: refresh()
    // ~10 Hz to match the helper's write cadence -> a live, moving meter.
    Timer { interval: 100; repeat: true; running: true; triggeredOnStart: false; onTriggered: mic.refresh() }
}
