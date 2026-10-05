pragma Singleton
import QtQuick
import QtCore

// IrisLive — the live Iris palette, read ONCE per app (2026-09-26).
// main.qml (the shell, whose engine Iris Chroma + Filigree drive) publishes every
// token NCDEKit reads to ~/.config/ncde/iris-live.json. Apps outside the shell
// carry frozen engine copies that never hear an Iris click, so NCDEKit takes its
// tokens from here instead. One reader per app, shared by every NCDEKit instance
// (22 controls each make their own kit — they must not each poll the file).
// Inside the shell `live` stays null: the kits read the engine directly.
QtObject {
    id: iris
    readonly property bool inShell: typeof intellihide !== "undefined"
    property var live: null
    property string _raw: ""
    readonly property string _url: StandardPaths.writableLocation(StandardPaths.ConfigLocation) + "/ncde/iris-live.json"
    function read() {
        var x = new XMLHttpRequest()
        x.onreadystatechange = function() {
            if (x.readyState !== XMLHttpRequest.DONE) return
            var t = (x.responseText || "").trim()
            if (t === "" || t === iris._raw) return
            try { var o = JSON.parse(t); iris._raw = t; iris.live = o } catch (e) { }
        }
        try { x.open("GET", _url); x.send() } catch (e) { }
    }
    property Timer _poll: Timer {
        interval: 1000; repeat: true; running: !iris.inShell; triggeredOnStart: true
        onTriggered: iris.read()
    }
}
