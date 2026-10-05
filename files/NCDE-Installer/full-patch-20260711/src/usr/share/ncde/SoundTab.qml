// SoundTab.qml — output, input, per-app levels.
// Backend: lelan (the one owner of audio — NCDE-ARCHITECTURE-DIGEST §2; ncde/NCDEEngine is the colour
//   engine only). 2026-09-30: every audio binding here pointed at `ncde`, which has no outputDevices/
//   inputDevices/audio/balance/defaultSourceName/setOutputDevice/setInputDevice/setBalance — the typeof
//   guards hid it, so the device pickers were always empty and the balance slider did nothing.
// lelan.appStreams (list {name,meta,vol}), lelan.setAppVolume(name,v) — real, libpulse-backed.
//   ncde.balance/setBalance(v) — real as of 2026-07-01 (was a total UI stub before, no property, no
//   handler). ncde.outputDevices/inputDevices (list {name,description}) + setOutputDevice(name)/
//   setInputDevice(name) — real as of 2026-07-01 (were static non-interactive labels before).
//   settings.outputVolume, inputLevel — persisted prefs; settings.saveSound().
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: sd; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    readonly property var streams: gv(lelan,"appStreams",[])
    // Live microphone peak (0..1) from ncde-mic-helper -> ncde-mic.json, via MicLive.
    // Drives the INPUT "Level" meter, which was bound to the static settings.inputLevel.
    MicLive { id: micLive }
    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"Sound"; color:sd.k.wine2; font.family:sd.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"Output, input, and per-app levels."; color:sd.k.inkSoft; font.family:sd.k.fell; font.italic:true; font.pixelSize:k.md }

            Text { text:"OUTPUT"; color:sd.k.gilt1; font.family:sd.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Row { width:parent.width; spacing:12
                Text { text:"Device"; width:158; color:sd.k.ink; font.family:sd.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                Item {
                    id: outPicker; width:240; height:30; anchors.verticalCenter: parent.verticalCenter
                    readonly property var devs: sd.gv(lelan,"outputDevices",[])
                    readonly property string curName: sd.gv(lelan,"audio",{})["sink"] || ""
                    readonly property string curDesc: {
                        for (var i=0;i<devs.length;i++) if (devs[i].name===curName) return devs[i].description
                        return curName || "No output device found"
                    }
                    Rectangle {
                        id: outBtn; anchors.fill: parent; radius:8
                        color:sd.k.paper0; border.color:sd.k.gilt1; border.width:1.5
                        Text { anchors.left:parent.left; anchors.leftMargin:12; anchors.right: parent.right; anchors.rightMargin: 8
                               anchors.verticalCenter: parent.verticalCenter; elide: Text.ElideRight
                               text: outPicker.curDesc+"  ▾"; font.family:sd.k.gar; font.pixelSize:k.md; color:sd.k.ink }
                        TapHandler { onTapped: outDrop.visible = !outDrop.visible }
                    }
                    Rectangle {
                        id: outDrop; visible:false; z:20
                        anchors.top: outBtn.bottom; anchors.topMargin:4; anchors.left: outBtn.left; width: outBtn.width
                        height: Math.min(outPicker.devs.length*28, 168); radius:8; color:sd.k.paper0; border.color:sd.k.gilt1; border.width:1; clip:true
                        ListView { anchors.fill:parent; model: outPicker.devs
                            delegate: Rectangle { width: outDrop.width; height:28; color: oHov.hovered?sd.k.gilt4:"transparent"
                                Text { anchors.left:parent.left; anchors.leftMargin:10; anchors.verticalCenter: parent.verticalCenter
                                       text: modelData.description; font.family:sd.k.gar; font.pixelSize:k.md; color:sd.k.ink; elide: Text.ElideRight; width: parent.width-16 }
                                HoverHandler { id: oHov }
                                TapHandler { onTapped: { if(typeof lelan.setOutputDevice==="function") lelan.setOutputDevice(modelData.name); outDrop.visible=false } }
                            }
                        }
                    }
                } }
            Row { width:parent.width; spacing:12
                Text { text:"Volume"; width:158; color:sd.k.ink; font.family:sd.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue:0; maxValue:150; value: sd.gv(widget_data,"volume",50)
                    onMoved: function(v){ var iv=Math.round(v); widget_data.setVolume(iv); settings.outputVolume=iv; if(typeof settings.saveSound==="function") settings.saveSound() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: sd.gv(widget_data,"volume",50)+"%"; color:sd.k.ink; font.family:sd.k.fell; font.italic:true; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter } }
            Row { width:parent.width; spacing:12
                Text { text:"Balance"; width:158; color:sd.k.ink; font.family:sd.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue:0; maxValue:100; value: sd.gv(lelan,"balance",50)
                    onMoved: function(v){ if(typeof lelan.setBalance==="function") lelan.setBalance(Math.round(v)) }
                    anchors.verticalCenter: parent.verticalCenter }
                Text {
                    text: { var b = sd.gv(lelan,"balance",50); return b===50 ? "Centre" : (b<50 ? "Left "+(50-b) : "Right "+(b-50)) }
                    color:sd.k.ink; font.family:sd.k.fell; font.italic:true; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter } }

            Rectangle { width:parent.width; height:1; color:sd.k.gilt1; opacity:0.4 }
            Text { text:"INPUT"; color:sd.k.gilt1; font.family:sd.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Row { width:parent.width; spacing:12
                Text { text:"Microphone"; width:158; color:sd.k.ink; font.family:sd.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                Item {
                    id: inPicker; width:240; height:30; anchors.verticalCenter: parent.verticalCenter
                    readonly property var devs: sd.gv(lelan,"inputDevices",[])
                    readonly property string curName: sd.gv(lelan,"defaultSourceName","")
                    readonly property string curDesc: {
                        for (var i=0;i<devs.length;i++) if (devs[i].name===curName) return devs[i].description
                        return curName || "No microphone found"
                    }
                    Rectangle {
                        id: inBtn; anchors.fill: parent; radius:8
                        color:sd.k.paper0; border.color:sd.k.gilt1; border.width:1.5
                        Text { anchors.left:parent.left; anchors.leftMargin:12; anchors.right: parent.right; anchors.rightMargin: 8
                               anchors.verticalCenter: parent.verticalCenter; elide: Text.ElideRight
                               text: inPicker.curDesc+"  ▾"; font.family:sd.k.gar; font.pixelSize:k.md; color:sd.k.ink }
                        TapHandler { onTapped: inDrop.visible = !inDrop.visible }
                    }
                    Rectangle {
                        id: inDrop; visible:false; z:20
                        anchors.top: inBtn.bottom; anchors.topMargin:4; anchors.left: inBtn.left; width: inBtn.width
                        height: Math.min(inPicker.devs.length*28, 168); radius:8; color:sd.k.paper0; border.color:sd.k.gilt1; border.width:1; clip:true
                        ListView { anchors.fill:parent; model: inPicker.devs
                            delegate: Rectangle { width: inDrop.width; height:28; color: iHov.hovered?sd.k.gilt4:"transparent"
                                Text { anchors.left:parent.left; anchors.leftMargin:10; anchors.verticalCenter: parent.verticalCenter
                                       text: modelData.description; font.family:sd.k.gar; font.pixelSize:k.md; color:sd.k.ink; elide: Text.ElideRight; width: parent.width-16 }
                                HoverHandler { id: iHov }
                                TapHandler { onTapped: { if(typeof lelan.setInputDevice==="function") lelan.setInputDevice(modelData.name); inDrop.visible=false } }
                            }
                        }
                    }
                } }
            Row { width:parent.width; spacing:12
                Text { text:"Level"; width:158; color:sd.k.ink; font.family:sd.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                Rectangle { width:230; height:8; radius:4; color:sd.k.paper3; border.color:sd.k.gilt1; border.width:1; clip:true; anchors.verticalCenter: parent.verticalCenter
                    Rectangle { height:parent.height; width: parent.width*(micLive.level/100); radius:4
                        Behavior on width { NumberAnimation { duration: 80; easing.type: Easing.OutQuad } }
                        gradient: Gradient { orientation: Gradient.Horizontal
                            GradientStop{position:0;color:sd.k.verd} GradientStop{position:0.8;color:sd.k.amber} GradientStop{position:1;color:sd.k.rose} } } } }

            Rectangle { width:parent.width; height:1; color:sd.k.gilt1; opacity:0.4 }
            Text { text:"PER-APPLICATION"; color:sd.k.gilt1; font.family:sd.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Repeater {
                model: sd.streams
                Rectangle {
                    width: parent.width; height: 48; radius:8; color: Qt.rgba(sd.k.paper0.r, sd.k.paper0.g, sd.k.paper0.b, 0.35); border.color:sd.k.gilt1; border.width:1
                    Row {
                        anchors.left:parent.left; anchors.leftMargin:11; anchors.verticalCenter: parent.verticalCenter; spacing:11
                        Rectangle { width:30; height:30; radius:7; border.color:sd.k.gilt1; border.width:1; anchors.verticalCenter: parent.verticalCenter
                            gradient: Gradient { GradientStop{position:0;color:sd.k.paper0} GradientStop{position:1;color:sd.k.paper2} }
                            Text { anchors.centerIn:parent; text:"♪"; color:sd.k.gilt0; font.pixelSize:k.md } }
                        Column { anchors.verticalCenter: parent.verticalCenter
                            Text { text: modelData.name; color:sd.k.ink; font.family:sd.k.serif; font.pixelSize:k.lg; font.bold:true }
                            Text { text: modelData.meta; color:sd.k.inkSoft; font.family:sd.k.fell; font.italic:true; font.pixelSize:k.sm } } }
                    NCDESlider { width:150; anchors.right:parent.right; anchors.rightMargin:14; anchors.verticalCenter: parent.verticalCenter
                        minValue:0; maxValue:100; value: modelData.vol
                        onMoved: function(v){ if(typeof lelan.setAppVolume==="function") lelan.setAppVolume(modelData.name, v) } }
                }
            }
            Item { width:1; height:8 }
        }
    }
}
