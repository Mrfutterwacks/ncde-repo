// glass-modes.js — per-surface "Follow Iris palette" vs "Custom glass" flag.
// .pragma library: one shared copy per engine, so Filigree's writes are what
// every NCDEGlassSurface reads.
//
// Why this exists: Iris Chroma drives the engine (applyPreset → ncde.accent/
// glow/gilt*), and Filigree's per-surface glass (ncde.surfaceGlass) is meant to
// layer ON TOP of it. The old consumers gated every Filigree value behind
// !ncde.presetActive — and main.qml reapplies the saved preset at every login,
// so presetActive is effectively always true and the Glass tab was dead UI.
// The engine has setSurfaceGlass but no way to clear an entry, so "go back to
// following the palette" can't be expressed through it; this flag is that
// missing bit. Stored with QtQuick.LocalStorage (SQLite under the engine's
// offline-storage path) — no C++ change, no new config file writer.
//
// Default for every key is "palette": nothing changes for a surface until the
// user actually customises it in Filigree.
.pragma library
.import QtQuick.LocalStorage 2.0 as Sql

var _cache = null

function _db() {
    return Sql.LocalStorage.openDatabaseSync("ncde-glass-modes", "1.0", "NCDE Filigree glass modes", 4096)
}

function _load() {
    if (_cache !== null) return _cache
    _cache = {}
    try {
        _db().transaction(function(tx) {
            tx.executeSql("CREATE TABLE IF NOT EXISTS modes (k TEXT PRIMARY KEY, custom INTEGER)")
            var rs = tx.executeSql("SELECT k, custom FROM modes")
            for (var i = 0; i < rs.rows.length; i++)
                _cache[rs.rows.item(i).k] = rs.rows.item(i).custom === 1
        })
    } catch (e) { console.warn("glass-modes: load failed:", e) }
    return _cache
}

function isCustom(key) {
    if (!key) return false
    return _load()[key] === true
}

function setCustom(key, on) {
    _load()[key] = !!on
    try {
        _db().transaction(function(tx) {
            tx.executeSql("CREATE TABLE IF NOT EXISTS modes (k TEXT PRIMARY KEY, custom INTEGER)")
            tx.executeSql("INSERT OR REPLACE INTO modes (k, custom) VALUES (?, ?)", [key, on ? 1 : 0])
        })
    } catch (e) { console.warn("glass-modes: save failed:", e) }
}
