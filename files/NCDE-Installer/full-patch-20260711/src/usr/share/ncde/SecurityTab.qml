// SecurityTab.qml — screen lock + Vesper (the whole security suite, one switch).
// Screen lock backend: settings.requirePassword, requirePasswordDelay, saveSecurity().
// Vesper backend: settings.kickassArmed (real persisted property — setKickassArmed(bool) really
// enables/disables + starts/stops vesper-brain.service via systemctl --user, not cosmetic).
// nftables (the firewall) is one of Vesper's five engines, not a separate control (operator,
// 2026-07-01: "vesper is the firewall etc it is a complete security suite... one toggle, vesper
// does it all" / "it lives in security tab"). Live engine/finding status polls Vesper's real brain
// service directly (usr/lib/ncde/vesper/brain_server.py, 127.0.0.1:8077/engines + /findings) — the
// old lelan.kickass/org.ncde.KickassGuard D-Bus path is dead and unrelated to the real system.
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: sc; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    function save(){ if(typeof settings.saveSecurity==="function") settings.saveSecurity() }

    property bool brainUp: false
    property var  engines: []
    property int  threatCount: 0
    function poll() {
        var x = new XMLHttpRequest()
        x.onreadystatechange = function() {
            if (x.readyState === XMLHttpRequest.DONE) {
                if (x.status === 200) {
                    try { sc.engines = JSON.parse(x.responseText).engines || []; sc.brainUp = true }
                    catch (e) { sc.brainUp = false }
                } else sc.brainUp = false
            }
        }
        x.open("GET", "http://127.0.0.1:8077/engines"); x.send()
        var y = new XMLHttpRequest()
        y.onreadystatechange = function() {
            if (y.readyState === XMLHttpRequest.DONE && y.status === 200) {
                try { sc.threatCount = (JSON.parse(y.responseText).findings || []).length } catch (e) {}
            }
        }
        y.open("GET", "http://127.0.0.1:8077/findings"); y.send()
    }
    Timer { interval: 5000; running: true; repeat: true; onTriggered: sc.poll() }

    Component.onCompleted: {
        if (typeof settings.loadKickass === "function") settings.loadKickass()
        sc.poll()
    }

    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"Security"; color:sc.k.wine2; font.family:sc.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"Screen lock and Vesper."; color:sc.k.inkSoft; font.family:sc.k.fell; font.italic:true; font.pixelSize:k.md }

            Text { text:"SCREEN LOCK"; color:sc.k.gilt1; font.family:sc.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Row { width:parent.width; spacing:12
                Text { text:"Require password"; width:200; color:sc.k.ink; font.family:sc.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle {
                    id: reqPwdToggle
                    checked: sc.gv(settings,"requirePassword",true)
                    onToggled: function(v){ settings.requirePassword=v; sc.save() }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text { text:"after sleep or screensaver begins"; anchors.verticalCenter: parent.verticalCenter; font.family:sc.k.fell; font.italic:true; font.pixelSize:k.sm; color:sc.k.inkSoft }
            }
            Row {
                width: parent.width; spacing: 12
                visible: sc.gv(settings,"requirePassword",true)
                Text { text:"After delay"; width:200; color:sc.k.ink; font.family:sc.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                SetSegment {
                    model: ["Immediately","5 seconds","1 minute","5 minutes"]
                    currentIndex: {
                        var d = sc.gv(settings,"requirePasswordDelay",0)
                        return d===0 ? 0 : d===5 ? 1 : d===60 ? 2 : 3
                    }
                    onChose: function(i){
                        var vals=[0,5,60,300]; settings.requirePasswordDelay=vals[i]; sc.save()
                    }
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Rectangle { width:parent.width; height:1; color:sc.k.gilt1; opacity:0.4 }
            Text { text:"VESPER"; color:sc.k.gilt1; font.family:sc.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Text { text:"Vesper security system. Five engines. One switch."; color:sc.k.inkSoft; font.family:sc.k.fell; font.italic:true; font.pixelSize:k.sm; topPadding:-4 }

            Row { width:parent.width; spacing:12
                NCDEToggle {
                    id: armedToggle
                    checked: sc.gv(settings,"kickassArmed", true)
                    onToggled: function(v){ if(typeof settings.setKickassArmed==="function") settings.setKickassArmed(v) }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Column { anchors.verticalCenter:parent.verticalCenter; spacing:2
                    Text { text: armedToggle.checked ? "Armed" : "Disarmed"; color: armedToggle.checked ? sc.k.verd : sc.k.inkSoft; font.family:sc.k.titles; font.pixelSize:k.md }
                    Text { text: armedToggle.checked ? "All five engines active" : "All engines stopped — machine is unprotected"; color: armedToggle.checked ? sc.k.inkSoft : sc.k.rose; font.family:sc.k.fell; font.italic:true; font.pixelSize:k.sm }
                }
            }
            Rectangle {
                width:parent.width; height:statusCard.height + 24; radius:8
                color:sc.k.paper0; border.color: armedToggle.checked ? sc.k.verd : sc.k.gilt1; border.width:1
                Row {
                    id: statusCard
                    anchors { left:parent.left; right:parent.right; top:parent.top; margins:12 }
                    spacing:10
                    Rectangle { width:10; height:10; radius:5; anchors.verticalCenter:parent.verticalCenter; color: !armedToggle.checked ? sc.k.inkSoft : sc.brainUp ? sc.k.verd : sc.k.rose }
                    Column { anchors.verticalCenter:parent.verticalCenter; spacing:3
                        Text {
                            text: !armedToggle.checked
                                ? "Disarmed — engines stopped"
                                : sc.brainUp
                                    ? (sc.threatCount + " threat" + (sc.threatCount===1?"":"s") + " found today")
                                    : "Starting…"
                            color:sc.k.ink; font.family:sc.k.titles; font.pixelSize:k.sm
                        }
                    }
                }
            }

            Rectangle { width:parent.width; height:1; color:sc.k.gilt1; opacity:0.35 }
            Text { text:"ENGINES"; color:sc.k.gilt1; font.family:sc.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Repeater {
                model: sc.engines.length ? sc.engines : [
                    { engine:"ClamAV",    role:"malware scanner", present:false },
                    { engine:"rkhunter",  role:"rootkit scanner", present:false },
                    { engine:"fail2ban",  role:"intrusion bans",  present:false },
                    { engine:"nftables",  role:"firewall",        present:false },
                    { engine:"auditd",    role:"syscall audit",   present:false }
                ]
                delegate: Row {
                    width: c.width; spacing: 8; leftPadding: 4
                    Rectangle {
                        width:6; height:6; radius:3; anchors.verticalCenter: parent.verticalCenter
                        color: armedToggle.checked && modelData.present ? sc.k.verd : sc.k.inkSoft
                    }
                    Column { anchors.verticalCenter: parent.verticalCenter; spacing:1
                        Text { text: modelData.engine; color:sc.k.ink; font.family:sc.k.titles; font.pixelSize:k.sm }
                        Text {
                            text: modelData.role + (modelData.present ? "" : " — not installed")
                            color:sc.k.inkSoft; font.family:sc.k.fell; font.italic:true; font.pixelSize:k.sm-1
                            width: c.width-20; wrapMode: Text.WordWrap
                        }
                    }
                }
            }

            Item { width:1; height:8 }
        }
    }
}
