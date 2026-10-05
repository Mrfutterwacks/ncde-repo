// SetControls.qml — shared JS helpers for settings tabs.
import QtQuick 2.15
QtObject {
    function clampHex(t){ t=(""+t).trim(); if(t.length===6)t="#"+t; return /^#[0-9A-Fa-f]{6}$/.test(t)?t:"" }
    function pct(v){ return Math.round(v*100)+"%" }
}
