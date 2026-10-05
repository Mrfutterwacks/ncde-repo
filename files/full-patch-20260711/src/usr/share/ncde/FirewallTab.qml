// FirewallTab.qml — Vesper's Armed / Disarmed control panel. The ONE switch for the whole
// security suite (operator, 2026-07-01: "vesper is the firewall etc it is a complete security
// suite... one toggle, vesper does it all") — nftables (the firewall) is one of the five engines
// below, not a separate control.
// Backend: settings.kickassArmed (real persisted property; setKickassArmed(bool) also really
// enables/disables + starts/stops vesper-brain.service via systemctl --user — not cosmetic).
// Live engine/finding status polls Vesper's real brain service directly (usr/lib/ncde/vesper/
// brain_server.py, 127.0.0.1:8077/engines + /findings) — the old lelan.kickass/
// org.ncde.KickassGuard D-Bus path is dead and unrelated to the real Vesper system.
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: fw; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }

    property bool  brainUp: false
    property var   engines: []
    property int   threatCount: 0
    function poll() {
        var x = new XMLHttpRequest()
        x.onreadystatechange = function() {
            if (x.readyState === XMLHttpRequest.DONE) {
                if (x.status === 200) {
                    try {
                        fw.engines = JSON.parse(x.responseText).engines || []
                        fw.brainUp = true
                    } catch (e) { fw.brainUp = false }
                } else fw.brainUp = false
            }
        }
        x.open("GET", "http://127.0.0.1:8077/engines"); x.send()
        var y = new XMLHttpRequest()
        y.onreadystatechange = function() {
            if (y.readyState === XMLHttpRequest.DONE && y.status === 200) {
                try { fw.threatCount = (JSON.parse(y.responseText).findings || []).length } catch (e) {}
            }
        }
        y.open("GET", "http://127.0.0.1:8077/findings"); y.send()
    }
    Timer { interval: 5000; running: true; repeat: true; onTriggered: fw.poll() }

    Component.onCompleted: {
        if (typeof settings.loadKickass === "function") settings.loadKickass()
        fw.poll()
    }

    Flickable {
        anchors.fill: parent; contentHeight: col.height + 24
        interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}

        Column {
            id: col; width: parent.width; spacing: 16; topPadding: 0

            // ── Title ──────────────────────────────────────────────────────────
            Text {
                text: "Vesper"
                color: fw.k.wine2
                font.family: fw.k.display; font.bold: true; font.pixelSize: fw.k.lg
            }
            Text {
                text: "Vesper security system. Five engines. One switch."
                color: fw.k.inkSoft
                font.family: fw.k.fell; font.italic: true; font.pixelSize: fw.k.md
            }

            Rectangle { width: parent.width; height: 1; color: fw.k.gilt1; opacity: 0.35 }

            // ── Armed toggle ───────────────────────────────────────────────────
            Row {
                width: parent.width; spacing: 14; topPadding: 4
                NCDEToggle {
                    id: armedToggle
                    anchors.verticalCenter: parent.verticalCenter
                    checked: (typeof lelan !== "undefined" && lelan.kickass && lelan.kickass["armed"]) || false
                    onToggled: function(v) {
                        if (typeof settings.setKickassArmed === "function")
                            settings.setKickassArmed(v)
                    }
                }
                Column {
                    anchors.verticalCenter: parent.verticalCenter; spacing: 2
                    Text {
                        text: armedToggle.checked ? "Armed" : "Disarmed"
                        color: armedToggle.checked ? fw.k.verd : fw.k.inkSoft
                        font.family: fw.k.display; font.bold: true; font.pixelSize: fw.k.md
                    }
                    Text {
                        text: armedToggle.checked
                            ? "All five engines active"
                            : "All engines stopped — machine is unprotected"
                        color: armedToggle.checked ? fw.k.inkSoft : fw.k.rose
                        font.family: fw.k.fell; font.italic: true; font.pixelSize: fw.k.sm
                    }
                }
            }

            // ── Status card ────────────────────────────────────────────────────
            Rectangle {
                width: parent.width; height: statusRow.height + 24; radius: 8
                color: fw.k.paper0
                border.color: armedToggle.checked ? fw.k.verd : fw.k.gilt1
                border.width: 1

                Row {
                    id: statusRow
                    anchors { left: parent.left; right: parent.right
                              top: parent.top; margins: 12 }
                    spacing: 10

                    Rectangle {
                        width: 10; height: 10; radius: 5
                        anchors.verticalCenter: parent.verticalCenter
                        color: armedToggle.checked ? fw.k.verd : fw.k.rose
                    }
                    Column {
                        anchors.verticalCenter: parent.verticalCenter; spacing: 4
                        Text {
                            // KickassGuard doesn't export itself on D-Bus yet (see daemon-rebuild task) —
                            // say so plainly rather than showing a fake "0 threats blocked today".
                            text: (typeof lelan !== "undefined" && lelan.kickass && lelan.kickass["armed"] !== undefined)
                                ? "0 threats blocked today"
                                : "Not connected to the security daemon"
                            color: fw.k.ink
                            font.family: fw.k.titles; font.pixelSize: fw.k.md
                        }
                    }
                }
            }

            Rectangle { width: parent.width; height: 1; color: fw.k.gilt1; opacity: 0.35 }

            // ── Engine list ────────────────────────────────────────────────────
            Text {
                text: "ENGINES"
                color: fw.k.gilt1
                font.family: fw.k.display; font.bold: true
                font.pixelSize: fw.k.sm; font.letterSpacing: 2
            }

            Repeater {
                model: [
                    { name: "ClamAV clamonacc",   desc: "On-access file scanning — blocks malicious executables before they run" },
                    { name: "audit/auditd",        desc: "Kernel behavioral detection — ransomware patterns, eBPF rootkit, credential theft" },
                    { name: "unbound DNS",         desc: "DNS threat filter — blocks phishing, malware, and C2 callback domains" },
                    { name: "nftables",            desc: "Network shield — C2 IP blocklist, port scan detection" },
                    { name: "rkhunter",            desc: "Daily rootkit scan — system binary integrity, hidden files, suspicious suid" },
                    { name: "fail2ban",            desc: "Brute force protection — SSH login failures → automatic IP ban" },
                ]

                delegate: Row {
                    width: col.width; spacing: 8; leftPadding: 4

                    Rectangle {
                        width: 6; height: 6; radius: 3
                        anchors.verticalCenter: parent.verticalCenter
                        color: armedToggle.checked ? fw.k.verd : fw.k.inkSoft
                    }
                    Column {
                        anchors.verticalCenter: parent.verticalCenter; spacing: 1
                        Text {
                            text: modelData.name
                            color: fw.k.ink
                            font.family: fw.k.titles; font.pixelSize: fw.k.sm
                        }
                        Text {
                            text: modelData.desc
                            color: fw.k.inkSoft
                            font.family: fw.k.fell; font.italic: true; font.pixelSize: fw.k.sm - 1
                            width: fw.col.width - 20; wrapMode: Text.WordWrap
                        }
                    }
                }
            }

            Item { width: 1; height: 8 }
        }
    }
}
