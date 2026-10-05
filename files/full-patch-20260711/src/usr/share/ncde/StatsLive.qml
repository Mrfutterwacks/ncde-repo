// StatsLive.qml — non-visual live reader for NCDE stats + backlight (2026-07-12).
//
// Mirrors the proven WeatherLive.qml pattern: a small userspace helper writes JSON
// atomically (~2s) to $XDG_RUNTIME_DIR/ncde-stats.json (fallback ~/.cache/ncde/
// stats.json); this file reads it via file:// XHR and republishes the values as
// QML properties the widgets bind to. Nothing here touches a binary.
//
// WHY (depth-audit gaps):
//   G3 — WidgetData in the stripped WM binary reads /proc/stat|meminfo only and
//        never iterates /proc/<pid>, so widget_data.top{1,2,3}name/cpu are always
//        empty. The helper computes the top processes; this bridges them to QML.
//   G5 — no backlight reader exists anywhere in the binary. The helper samples
//        /sys/class/backlight/*, and this exposes it + writes changes back.
//
// Exposes (read):
//   top1name/top1cpu .. top3name/top3cpu   highest-CPU processes this interval
//   brightnessAvailable, brCur, brMax, brPct
//   ts                                     unix epoch of the current sample
// Method:
//   setBrightness(pct)  writes /sys/class/backlight/<dev>/brightness. The brightness
//                       node is group-video, world-standard udev perms (mode 0664,
//                       group video) — the logged-in user is in `video`, so this
//                       needs NO root/polkit. No-op when no backlight is present.

import QtQuick
import Qt.labs.platform as Platform

Item {
    id: sl
    visible: false   // pure data brain, never drawn

    // ── published stats ─────────────────────────────────────────────
    property string top1name: "";  property real top1cpu: 0
    property string top2name: "";  property real top2cpu: 0
    property string top3name: "";  property real top3cpu: 0

    // ── published backlight ─────────────────────────────────────────
    property bool brightnessAvailable: false
    property int  brCur: 0
    property int  brMax: 0
    property int  brPct: 0

    property int  ts: 0

    // ── source paths (runtime dir first, cache fallback) ────────────
    function _strip(u) {
        u = ("" + u).replace(/^file:\/\//, "")
        if (u.length && u[u.length - 1] === "/") u = u.slice(0, -1)
        return u
    }
    function _runtimePath() {
        var b = _strip(Platform.StandardPaths.writableLocation(Platform.StandardPaths.RuntimeLocation))
        return b.length ? (b + "/ncde-stats.json") : ""
    }
    function _cachePath() {
        // GenericCacheLocation == ~/.cache ; helper writes ~/.cache/ncde/stats.json
        var b = _strip(Platform.StandardPaths.writableLocation(Platform.StandardPaths.GenericCacheLocation))
        return b.length ? (b + "/ncde/stats.json") : ""
    }

    // ── read one JSON path; on empty/failed body, invoke onMiss() ───
    function _readPath(path, onMiss) {
        if (!path) { if (onMiss) onMiss(); return }
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var body = "" + (xhr.responseText || "")
            if (body.trim() === "") { if (onMiss) onMiss(); return }
            try { sl._apply(JSON.parse(body)) }
            catch (e) { if (onMiss) onMiss() }
        }
        try { xhr.open("GET", "file://" + path); xhr.send() }
        catch (e) { if (onMiss) onMiss() }
    }

    function refresh() {
        _readPath(_runtimePath(), function() { sl._readPath(sl._cachePath(), null) })
    }

    function _apply(j) {
        if (!j || typeof j !== "object") return
        if (j.ts !== undefined) ts = j.ts | 0

        function nm(o) { return (o && o.name !== undefined && o.name !== null) ? ("" + o.name) : "" }
        function cp(o) { return (o && o.cpu  !== undefined && o.cpu  !== null) ? (o.cpu * 1)  : 0  }
        top1name = nm(j.top1); top1cpu = cp(j.top1)
        top2name = nm(j.top2); top2cpu = cp(j.top2)
        top3name = nm(j.top3); top3cpu = cp(j.top3)

        var b = j.brightness
        if (b && b.max !== undefined && (b.max | 0) > 0) {
            brCur = b.cur | 0
            brMax = b.max | 0
            brPct = (b.pct !== undefined) ? (b.pct | 0) : Math.round(brCur / brMax * 100)
            brightnessAvailable = true
            // the helper names the device it read (2026-09-25) -- write to that same one
            if (b.dev) _brPath = "" + b.dev
            else if (_brPath === "") _findBacklight()
        } else {
            brightnessAvailable = false   // desktop / no backlight — key omitted by helper
        }
    }

    // ── backlight write path discovery (helper JSON has no device name) ──
    property string _brPath: ""
    readonly property var _brCands: [
        "intel_backlight", "amdgpu_bl1", "amdgpu_bl0", "acpi_video0",
        "nvidia_0", "radeon_bl0", "apple_backlight"
    ]
    function _findBacklight() { _probe(0) }
    function _probe(i) {
        if (i >= _brCands.length) return
        var cand = _brCands[i]
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var n = parseInt(("" + (xhr.responseText || "")).trim())
            if (!isNaN(n) && n > 0) sl._brPath = "/sys/class/backlight/" + cand
            else sl._probe(i + 1)
        }
        try { xhr.open("GET", "file:///sys/class/backlight/" + cand + "/max_brightness"); xhr.send() }
        catch (e) { sl._probe(i + 1) }
    }

    // ── write a new brightness (pct 1..100). No root: group-video sysfs. ──
    function setBrightness(pct) {
        if (!brightnessAvailable || brMax <= 0) return
        pct = Math.max(1, Math.min(100, Math.round(pct)))   // never 0 -> never a black screen
        var val = Math.max(1, Math.round(brMax * pct / 100))
        // optimistic local update so the slider tracks smoothly; helper reconfirms in ~2s
        brCur = val; brPct = pct
        if (_brPath === "") _findBacklight()
        if (_brPath === "") return          // no device found yet: never guess one
        var xhr = new XMLHttpRequest()
        try { xhr.open("PUT", "file://" + _brPath + "/brightness"); xhr.send("" + val) }
        catch (e) { /* read-only / no perms — slider still reflects the attempt */ }
    }

    Component.onCompleted: refresh()
    Timer { interval: 2000; repeat: true; running: true; triggeredOnStart: false; onTriggered: sl.refresh() }
}
