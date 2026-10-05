// DisplayTab.qml — screens, resolution, scale, night light.
// Backend: settings.displays (list of {n,pri,w,h,sub,hz,modes,rates,orient,scale}),
//   settings.applyDisplayMode(name,mode,hz), settings.applyDisplayOrientation(name,orient),
//   settings.applyDisplayScale(name,pct), settings.nightLightOn, settings.nightWarmth,
//   settings.nightLightAuto (real as of 2026-07-01 — follows Lelan's GeoClue2-derived sunset/
//   sunrise day-night flip when on), settings.saveDisplay().
//   Keep-or-revert (2026-09-30, rebuilt LaPivot): after a resolution / rate / scale / rotation change
//   settings.displayChangePending(seconds) starts a countdown; settings.confirmDisplayChange() keeps it,
//   settings.revertDisplayChange() (or doing nothing for 15 s) puts the previous setting back.
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: dp; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }

    property int keepLeft: 0                  // seconds until a display change reverts by itself; 0 = none
    Connections {
        target: (typeof settings !== "undefined") ? settings : null
        ignoreUnknownSignals: true
        function onDisplayChangePending(seconds) { dp.keepLeft = seconds }
    }
    Timer { interval: 1000; repeat: true; running: dp.keepLeft > 0; onTriggered: dp.keepLeft = Math.max(0, dp.keepLeft - 1) }

    // G5 fix (2026-07-12): the WM binary has no backlight reader/control at all.
    // StatsLive reads the helper JSON's brightness{cur,max,pct} and writes changes
    // back to /sys/class/backlight/<dev>/brightness (group-video sysfs, no root).
    StatsLive { id: blLive }

    // Primary display — first display with pri=true, or first in list
    readonly property var primaryDisp: {
        var disps = gv(settings,"displays",[])
        for (var i = 0; i < disps.length; i++) if (disps[i].pri) return disps[i]
        return disps.length ? disps[0] : null
    }

    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"Display"; color:dp.k.wine2; font.family:dp.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"Screens, resolution, and the warmth of the light."; color:dp.k.inkSoft; font.family:dp.k.fell; font.italic:true; font.pixelSize:k.md }

            // keep-or-revert after a display change (the old setting comes back by itself if nothing is chosen)
            Rectangle {
                visible: dp.keepLeft > 0
                width: parent.width; height: keepRow.height + 20; radius: 8
                color: Qt.rgba(dp.k.gilt4.r, dp.k.gilt4.g, dp.k.gilt4.b, 0.30); border.color: dp.k.gilt2; border.width: 1.5
                Row {
                    id: keepRow
                    anchors.left: parent.left; anchors.leftMargin: 12; anchors.right: parent.right; anchors.rightMargin: 12
                    anchors.verticalCenter: parent.verticalCenter; spacing: 10
                    Text { width: parent.width - keepBtn.width - backBtn.width - 20; wrapMode: Text.WordWrap
                           anchors.verticalCenter: parent.verticalCenter
                           text: "Keep these display settings? Going back in " + dp.keepLeft + " s."
                           color: dp.k.ink; font.family: dp.k.titles; font.pixelSize: k.md }
                    Rectangle {
                        id: keepBtn; width: 80; height: 26; radius: 4; anchors.verticalCenter: parent.verticalCenter
                        color: Qt.rgba(dp.k.gilt1.r, dp.k.gilt1.g, dp.k.gilt1.b, 0.14); border.color: dp.k.gilt1; border.width: 1
                        Text { anchors.centerIn: parent; text: "Keep"; color: dp.k.gilt1; font.family: dp.k.titles; font.pixelSize: k.sm; font.bold: true }
                        TapHandler { onTapped: settings.confirmDisplayChange() }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                    }
                    Rectangle {
                        id: backBtn; width: 80; height: 26; radius: 4; anchors.verticalCenter: parent.verticalCenter
                        color: Qt.rgba(dp.k.rose.r, dp.k.rose.g, dp.k.rose.b, 0.12); border.color: dp.k.rose; border.width: 1
                        Text { anchors.centerIn: parent; text: "Go back"; color: dp.k.rose; font.family: dp.k.titles; font.pixelSize: k.sm; font.bold: true }
                        TapHandler { onTapped: settings.revertDisplayChange() }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                    }
                }
            }

            Text { text:"ARRANGEMENT"; color:dp.k.gilt1; font.family:dp.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Rectangle {
                width: parent.width; height: 116; radius:10; color: Qt.rgba(0,0,0,0.05); border.color:dp.k.gilt1; border.width:1
                Row {
                    anchors.centerIn: parent; spacing: 14
                    Repeater {
                        model: gv(settings,"displays",[])
                        Rectangle {
                            width: modelData.w; height: modelData.h; radius:6
                            border.color: modelData.pri ? dp.k.gilt3 : dp.k.gilt0; border.width: modelData.pri?3:2
                            gradient: Gradient { GradientStop{position:0;color:"#2a4a55"} GradientStop{position:1;color:"#1c333c"} }
                            Column { anchors.centerIn: parent; spacing:2
                                Text { text: modelData.n; color:dp.k.gilt5; font.family:dp.k.titles; font.pixelSize:k.sm; anchors.horizontalCenter: parent.horizontalCenter }
                                Text { text: modelData.sub; color:dp.k.gilt4; font.family:dp.k.gar; font.pixelSize:k.sm; anchors.horizontalCenter: parent.horizontalCenter } }
                            Rectangle { visible: modelData.pri; anchors.top:parent.top; anchors.left:parent.left; anchors.margins:4
                                width:lbl.implicitWidth+8; height:13; radius:3; color:dp.k.gilt4
                                Text { id:lbl; anchors.centerIn:parent; text:"Primary"; font.family:dp.k.fell; font.italic:true; font.pixelSize:k.sm; color:dp.k.wine1 } }
                        }
                    }
                    Text {
                        visible: gv(settings,"displays",[]).length === 0
                        text: "No display data"; anchors.verticalCenter: parent.verticalCenter
                        color: dp.k.inkSoft; font.family: dp.k.fell; font.italic: true; font.pixelSize: k.sm
                    }
                }
            }

            // ── Resolution ─────────────────────────────────────────
            Row { id: resRow; width:parent.width; spacing:12
                Text { text:"Resolution"; width:158; color:dp.k.ink; font.family:dp.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                Item {
                    id: resPicker
                    width: 200; height: 30
                    anchors.verticalCenter: parent.verticalCenter
                    property var modes: dp.primaryDisp ? dp.primaryDisp.modes : []
                    property string current: dp.primaryDisp ? dp.primaryDisp.sub : "—"

                    Rectangle {
                        id: resBtn; anchors.fill: parent; radius:8
                        color:dp.k.paper0; border.color:dp.k.gilt1; border.width:1.5
                        Text { anchors.left:parent.left; anchors.leftMargin:12; anchors.verticalCenter: parent.verticalCenter
                               text: resPicker.current.replace("x"," × ")+"  ▾"
                               font.family:dp.k.gar; font.pixelSize:k.md; color:dp.k.ink }
                        TapHandler { onTapped: resDrop.visible = !resDrop.visible }
                    }
                    Rectangle {
                        id: resDrop; visible: false; z: 20
                        anchors.top: resBtn.bottom; anchors.topMargin: 4
                        anchors.left: resBtn.left; width: resBtn.width
                        height: Math.min(resPicker.modes.length * 30, 180)
                        radius: 8; color: dp.k.paper0; border.color: dp.k.gilt1; border.width: 1; clip: true
                        ListView {
                            anchors.fill: parent
                            model: resPicker.modes
                            delegate: Rectangle {
                                width: resDrop.width; height: 30
                                color: rHov.hovered ? dp.k.gilt4 : "transparent"
                                Text { anchors.left:parent.left; anchors.leftMargin:12; anchors.verticalCenter: parent.verticalCenter
                                       text: modelData.replace("x"," × "); font.family:dp.k.gar; font.pixelSize:k.md; color:dp.k.ink }
                                HoverHandler { id: rHov }
                                TapHandler { onTapped: {
                                    if (dp.primaryDisp) settings.applyDisplayMode(dp.primaryDisp.n, modelData, 0)
                                    resDrop.visible = false
                                }}
                            }
                        }
                    }
                }
            }

            // ── Refresh rate ────────────────────────────────────────
            Row { width:parent.width; spacing:12
                Text { text:"Refresh rate"; width:158; color:dp.k.ink; font.family:dp.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                Item {
                    id: ratePicker
                    width: 280; height: 30
                    anchors.verticalCenter: parent.verticalCenter
                    property var rates: dp.primaryDisp && dp.primaryDisp.rates ? dp.primaryDisp.rates : []
                    property var rateLabels: {
                        var arr = []; for (var i=0;i<rates.length;i++) arr.push(Math.round(rates[i])+" Hz"); return arr
                    }
                    property int currentIndex: {
                        var hz = dp.primaryDisp ? dp.primaryDisp.hz : 0
                        for (var i=0;i<rates.length;i++) if (Math.abs(rates[i]-hz)<0.5) return i; return 0
                    }
                    SetSegment {
                        anchors.fill: parent
                        model: ratePicker.rateLabels.length ? ratePicker.rateLabels : ["—"]
                        currentIndex: ratePicker.currentIndex
                        onChose: function(i) {
                            if (dp.primaryDisp && ratePicker.rates.length > i)
                                settings.applyDisplayMode(dp.primaryDisp.n, dp.primaryDisp.sub, ratePicker.rates[i])
                        }
                    }
                }
            }

            // ── Scale ───────────────────────────────────────────────
            Row { width:parent.width; spacing:12
                Text { text:"Scale"; width:158; color:dp.k.ink; font.family:dp.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                SetSegment {
                    model:["100%","125%","150%","200%"]
                    currentIndex: {
                        var pcts = [100, 125, 150, 200]
                        var s = dp.primaryDisp ? dp.primaryDisp.scale : 100
                        var idx = pcts.indexOf(s); return idx >= 0 ? idx : 0
                    }
                    anchors.verticalCenter: parent.verticalCenter
                    onChose: function(i) {
                        var pcts = [100, 125, 150, 200]
                        if (dp.primaryDisp) settings.applyDisplayScale(dp.primaryDisp.n, pcts[i])
                    }
                }
            }

            // ── Orientation ─────────────────────────────────────────
            Row { width:parent.width; spacing:12
                Text { text:"Orientation"; width:158; color:dp.k.ink; font.family:dp.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                SetSegment {
                    model:["Landscape","Portrait","Inverted","Port. Inv."]
                    currentIndex: {
                        var orients = ["normal","left","inverted","right"]
                        var o = dp.primaryDisp ? dp.primaryDisp.orient : "normal"
                        var idx = orients.indexOf(o); return idx >= 0 ? idx : 0
                    }
                    anchors.verticalCenter: parent.verticalCenter
                    onChose: function(i) {
                        var orients = ["normal","left","inverted","right"]
                        if (dp.primaryDisp) settings.applyDisplayOrientation(dp.primaryDisp.n, orients[i])
                    }
                }
            }

            // ── Brightness (backlight) — G5 ─────────────────────────
            Rectangle { visible: blLive.brightnessAvailable; width:parent.width; height:1; color:dp.k.gilt1; opacity:0.4 }
            Text { visible: blLive.brightnessAvailable; text:"BRIGHTNESS"; color:dp.k.gilt1; font.family:dp.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Row { visible: blLive.brightnessAvailable; width:parent.width; spacing:12
                Text { text:"Screen brightness"; width:158; color:dp.k.ink; font.family:dp.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue:1; maxValue:100; value: blLive.brPct
                    onMoved: function(v){ blLive.setBrightness(v) }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: blLive.brPct+"%"; color:dp.k.ink; font.family:dp.k.fell; font.italic:true; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter } }

            Rectangle { width:parent.width; height:1; color:dp.k.gilt1; opacity:0.4 }
            // SOLEI-LUNE (light/dark appearance mode) moved to Filigree's Glass tab, 2026-07-02 —
            // belongs alongside the other appearance controls, not under Devices → Display.
            Text { text:"NIGHT LIGHT"; color:dp.k.gilt1; font.family:dp.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Rectangle { width:parent.width; height:80; radius:10; border.color:dp.k.gilt1; border.width:1
                gradient: Gradient { orientation: Gradient.Horizontal
                    GradientStop{position:0;color:"#cfe6f0"} GradientStop{position:0.5;color:ncde.gilt5} GradientStop{position:1;color:"#e89a6a"} }
                Text { anchors.left:parent.left; anchors.bottom:parent.bottom; anchors.margins:10
                       text:"warmer ← → cooler · auto from sunset to sunrise (by your location)"
                       font.family:dp.k.fell; font.italic:true; font.pixelSize:k.sm; color:dp.k.wine1 } }
            Row { width:parent.width; spacing:12
                Text { text:"Night light"; width:158; color:dp.k.ink; font.family:dp.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: dp.gv(settings,"nightLightOn",false)
                    onToggled: function(v){ settings.nightLightOn = v; settings.saveDisplay() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text:"On / Off"; anchors.verticalCenter: parent.verticalCenter; font.family:dp.k.fell; font.italic:true; font.pixelSize:k.sm; color:dp.k.inkSoft } }
            Row { width:parent.width; spacing:12
                Text { text:"Auto (location)"; width:158; color:dp.k.ink; font.family:dp.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: dp.gv(settings,"nightLightAuto",false)
                    onToggled: function(v){ settings.nightLightAuto = v; settings.saveDisplay() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text:"On at sunset · Off at sunrise"; anchors.verticalCenter: parent.verticalCenter; font.family:dp.k.fell; font.italic:true; font.pixelSize:k.sm; color:dp.k.inkSoft } }
            Row { width:parent.width; spacing:12
                Text { text:"Warmth"; width:158; color:dp.k.ink; font.family:dp.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue:2700; maxValue:6500; value: dp.gv(settings,"nightWarmth",3800)
                    onMoved: function(v){ settings.nightWarmth = Math.round(v); settings.saveDisplay() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: Math.round(dp.gv(settings,"nightWarmth",3800))+"K"; color:dp.k.ink; font.family:dp.k.fell; font.italic:true; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter } }
            Item { width:1; height:8 }
        }
    }
}
