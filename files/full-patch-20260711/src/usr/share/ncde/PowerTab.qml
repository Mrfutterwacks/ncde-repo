// PowerTab.qml — sleep, screen, lid, power button.
// Backend: settings.batBlank, batSuspend, acBlank, acSuspend (int minutes; 0=Never) — real as of
//   2026-07-01: blank uses xset dpms directly, suspend reuses the X11 idle timeout (xset s) already
//   forwarded to AnimPolicy::screenIdle, which now actually triggers `systemctl suspend`. Battery↔AC
//   transitions re-apply automatically. settings.lidAction, powerButtonAction (string) — still
//   persisted-only, needs a logind inhibitor lock (separate task, deliberately not rushed — physical
//   hardware risk). settings.showBatteryPct (bool), real. settings.loadPower() / savePower() — guarded.
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: pw; clip: true
    property var k: SetTheme

    readonly property var timeVals:   [0, 5, 15, 30]
    readonly property var timeLabels: ["Never", "5 min", "15 min", "30 min"]
    // A stored value outside the presets (e.g. the 10/20 C++ defaults) used to display as
    // "5 min" (old i<0→1 fallback) — now it shows as its own honest extra segment instead.
    function timeModel(v)  { return timeVals.indexOf(v) < 0 ? timeLabels.concat([v + " min"]) : timeLabels }
    function timeIdx(v)    { var i = timeVals.indexOf(v); return i < 0 ? timeLabels.length : i }
    function timeVal(i, v) { return i < timeVals.length ? timeVals[i] : v }

    readonly property var lidOpts: ["suspend", "lock", "nothing"]
    readonly property var pwrOpts: ["suspend", "poweroff", "ask"]
    function optIdx(arr, v, def) { var i = arr.indexOf(v); return i < 0 ? def : i }

    function save() { if (typeof settings.savePower === "function") settings.savePower() }

    Component.onCompleted: { if (typeof settings.loadPower === "function") settings.loadPower() }

    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14

            Text { text: "Power"; color: pw.k.wine2; font.family: pw.k.display; font.bold: true; font.pixelSize: k.lg }
            Text { text: "Sleep, screen, and what the lid does."; color: pw.k.inkSoft; font.family: pw.k.fell; font.italic: true; font.pixelSize: k.md }

            Text { text: "ON BATTERY"; color: pw.k.gilt1; font.family: pw.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2; topPadding: 4 }
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Blank screen after"; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.md }
                SetSegment {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    model: pw.timeModel(settings.batBlank)
                    currentIndex: pw.timeIdx(settings.batBlank)
                    onChose: function(i) { settings.batBlank = pw.timeVal(i, settings.batBlank); pw.save() }
                }
            }
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Suspend after"; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.md }
                SetSegment {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    model: pw.timeModel(settings.batSuspend)
                    currentIndex: pw.timeIdx(settings.batSuspend)
                    onChose: function(i) { settings.batSuspend = pw.timeVal(i, settings.batSuspend); pw.save() }
                }
            }

            Rectangle { width: parent.width; height: 1; color: pw.k.gilt1; opacity: 0.4 }
            Text { text: "PLUGGED IN"; color: pw.k.gilt1; font.family: pw.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Blank screen after"; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.md }
                SetSegment {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    model: pw.timeModel(settings.acBlank)
                    currentIndex: pw.timeIdx(settings.acBlank)
                    onChose: function(i) { settings.acBlank = pw.timeVal(i, settings.acBlank); pw.save() }
                }
            }
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Suspend after"; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.md }
                SetSegment {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    model: pw.timeModel(settings.acSuspend)
                    currentIndex: pw.timeIdx(settings.acSuspend)
                    onChose: function(i) { settings.acSuspend = pw.timeVal(i, settings.acSuspend); pw.save() }
                }
            }

            Rectangle { width: parent.width; height: 1; color: pw.k.gilt1; opacity: 0.4 }
            Text { text: "BEHAVIOUR"; color: pw.k.gilt1; font.family: pw.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "When lid closes"; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.md }
                SetSegment {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    model: ["Suspend", "Lock", "Nothing"]
                    currentIndex: pw.optIdx(pw.lidOpts, settings.lidAction, 0)
                    onChose: function(i) { settings.lidAction = pw.lidOpts[i]; pw.save() }
                }
            }
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Power button"; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.md }
                SetSegment {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    model: ["Suspend", "Power off", "Ask"]
                    currentIndex: pw.optIdx(pw.pwrOpts, settings.powerButtonAction, 1)
                    onChose: function(i) { settings.powerButtonAction = pw.pwrOpts[i]; pw.save() }
                }
            }
            // Honest caption: lidAction/powerButtonAction persist but nothing enforces them
            // yet (needs the inhibitor-lock C++ task) — without this note the dropdowns
            // silently lie ("Nothing" set, lid still suspends).
            Text {
                width: parent.width; wrapMode: Text.WordWrap
                text: "Lid and power-button choices are saved, but this release still follows the system's built-in behaviour for them."
                color: pw.k.inkSoft; font.family: pw.k.fell; font.italic: true; font.pixelSize: k.sm
            }
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Show battery %"; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.md }
                NCDEToggle {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    checked: settings.showBatteryPct
                    onToggled: function(v) { settings.showBatteryPct = v; pw.save() }
                }
            }
            Rectangle { width: parent.width; height: 1; color: pw.k.gilt1; opacity: 0.4; visible: sensorsCol.visible }
            Text {
                text: "SENSORS"; color: pw.k.gilt1; font.family: pw.k.display; font.bold: true
                font.pixelSize: k.sm; font.letterSpacing: 2; visible: sensorsCol.visible
            }
            Text {
                width: parent.width; wrapMode: Text.WordWrap
                text: "No hardware sensors detected."
                color: pw.k.inkSoft; font.family: pw.k.fell; font.italic: true; font.pixelSize: k.sm
                visible: !sensorsCol.visible
            }
            Column {
                id: sensorsCol; width: parent.width; spacing: 6
                visible: Object.keys(lelan.sentinelTemps).length > 0 || Object.keys(lelan.sentinelFans).length > 0
                Repeater {
                    model: Object.keys(lelan.sentinelTemps)
                    delegate: Item { width: sensorsCol.width; height: 24
                        Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                               text: modelData; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.sm }
                        Text { anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                               text: lelan.sentinelTemps[modelData].toFixed(1) + "°C"
                               color: pw.k.inkSoft; font.family: pw.k.titles; font.pixelSize: k.sm }
                    }
                }
                Repeater {
                    model: Object.keys(lelan.sentinelFans)
                    delegate: Item { width: sensorsCol.width; height: 24
                        Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                               text: modelData; color: pw.k.ink; font.family: pw.k.titles; font.pixelSize: k.sm }
                        Text { anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                               text: lelan.sentinelFans[modelData] + " RPM"
                               color: pw.k.inkSoft; font.family: pw.k.titles; font.pixelSize: k.sm }
                    }
                }
            }
            Item { width: 1; height: 8 }
        }
    }
}
