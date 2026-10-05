// ============================================================
//  Main.qml — NCDE System Restore ("Soundings")
//  A nautical Time Machine: descend through the water column of past
//  system states. Each btrfs snapshot is a stratum at a depth; the
//  gauge on the right is the timeline. QtQuick + Canvas/paint, ocean +
//  parchment (Mucha) confirm veil, animated celestial progress bar.
//
//  NO hardcoded data. Snapshots + restore come from `backend` (a context
//  property injected by the C++/helper layer — see README). In a bare
//  qmlscene run with no backend, the model is simply empty.
// ============================================================
import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: win
    visible: true
    width: 1100; height: 680
    color: "#020608"
    title: "NCDE System Restore"

    // ---- palette ----
    readonly property color abyssDeep: "#020608"
    readonly property color teal:      "#1a4a5a"
    readonly property color gold:      "#b88a2c"
    readonly property color goldHi:    "#e2c772"
    readonly property color goldDeep:  "#6f4f15"
    readonly property color parch:     "#e8d6a9"
    readonly property color parchHi:   "#f3e3b5"
    readonly property color ink:       "#2a1a08"
    readonly property color sepia:     "#4a2c10"
    readonly property color burgundy:  "#6b2018"
    readonly property color bone:      "#c9a96b"

    // ---- data (from btrfs via backend; never hardcoded) ----
    // Each item: { id, date, word, kernel, size, tag, depth }
    property var snaps: []
    property int cur: 0
    property bool restoring: false

    // backend is injected as a context property. Guard so the file still
    // loads (empty) in a plain qmlscene preview.
    property var backend: (typeof appBackend !== "undefined") ? appBackend : null

    Component.onCompleted: reload()
    function reload() {
        if (!backend) { snaps = []; return; }
        // backend.listBackups() returns a JS array of snapshot objects read
        // from `btrfs subvolume list /restore` (+ metadata). Surface (index 0)
        // is synthesised by the backend as "the present".
        snaps = backend.listBackups();
        cur = 0;
    }

    // ============================================================
    //  the sea (water column — light surface to abyss)
    // ============================================================
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0;  color: "#2f6e80" }
            GradientStop { position: 0.22; color: "#1a4a5a" }
            GradientStop { position: 0.48; color: "#08222e" }
            GradientStop { position: 0.72; color: "#04101a" }
            GradientStop { position: 1.0;  color: "#020608" }
        }
    }

    // ============================================================
    //  top chrome
    // ============================================================
    Item {
        id: topbar; height: 64
        anchors { top: parent.top; left: parent.left; right: parent.right }
        Text {
            anchors.verticalCenter: parent.verticalCenter; x: 26
            text: "SYSTEM RESTORE"; color: win.goldHi
            font.family: "Cinzel"; font.pixelSize: 15; font.letterSpacing: 4; font.bold: true
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 26
            text: "· PER · PROFVNDVM ·"; color: win.bone
            font.family: "IM Fell DW Pica SC"; font.pixelSize: 11; font.letterSpacing: 5
        }
    }

    // ============================================================
    //  the deep — receding stack of snapshot plates
    // ============================================================
    Item {
        id: stage
        anchors.fill: parent
        z: 10
        Repeater {
            model: win.snaps.length
            delegate: Rectangle {
                id: plate
                property int idx: index
                property int d: idx - win.cur
                width: 560; height: 360; radius: 2
                x: (stage.width - width) / 2
                y: (stage.height - height) / 2 + d * 120 - 24
                z: 100 - Math.abs(d)
                opacity: d === 0 ? 1 : Math.max(0, 1 - Math.abs(d) * 0.26)
                scale: d === 0 ? 1 : Math.max(0.6, 1 - Math.abs(d) * 0.12)
                border.color: win.goldDeep
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#0d2a36" }
                    GradientStop { position: 1.0; color: "#061a24" }
                }
                Behavior on y       { NumberAnimation { duration: 600; easing.type: Easing.OutCubic } }
                Behavior on opacity { NumberAnimation { duration: 600 } }
                Behavior on scale   { NumberAnimation { duration: 600; easing.type: Easing.OutCubic } }

                // selection frame
                Rectangle {
                    anchors.fill: parent; anchors.margins: 0; color: "transparent"
                    border.color: plate.d === 0 ? win.gold : "transparent"; border.width: 2
                }
                Column {
                    anchors.centerIn: parent; spacing: 12; width: parent.width * 0.84
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: win.snaps.length ? (plate.idx === 0 ? "· THE PRESENT ·" : win.snaps[plate.idx].date) : ""
                        color: win.goldHi; font.family: "IM Fell DW Pica SC"; font.pixelSize: 12; font.letterSpacing: 3
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: win.snaps.length ? win.snaps[plate.idx].word : ""
                        color: win.parchHi; font.family: "Cormorant Garamond"; font.italic: true; font.pixelSize: 40
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            if (!win.snaps.length) return "";
                            var s = win.snaps[plate.idx];
                            return plate.idx === 0 ? "Your system as it stands now"
                                 : (s.id + "   ·   kernel " + s.kernel + "   ·   " + s.size);
                        }
                        color: win.bone; font.family: "JetBrains Mono"; font.pixelSize: 12
                    }
                }
                MouseArea { anchors.fill: parent; onClicked: win.cur = plate.idx }
            }
        }
    }

    // ============================================================
    //  depth gauge (the timeline)
    // ============================================================
    Column {
        id: gauge
        z: 20
        anchors { right: parent.right; rightMargin: 34; top: parent.top; topMargin: 90; bottom: controls.top; bottomMargin: 16 }
        width: 188; spacing: 0
        Text { text: "SOUNDINGS"; color: win.bone; font.family: "IM Fell DW Pica SC"; font.pixelSize: 10; font.letterSpacing: 4; anchors.right: parent.right }
        Repeater {
            model: win.snaps.length
            delegate: Item {
                width: gauge.width
                height: (gauge.height - 24) / Math.max(1, win.snaps.length)
                property bool on: index === win.cur
                Row {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                    Column {
                        Text {
                            text: win.snaps.length ? win.snaps[index].word : ""
                            color: parent.parent.parent.on ? win.parchHi : "#7f93a0"
                            font.family: "Cormorant Garamond"; font.italic: true; font.pixelSize: 15
                            horizontalAlignment: Text.AlignRight; anchors.right: parent.right
                        }
                        Text {
                            text: win.snaps.length ? (index === 0 ? "now" : win.snaps[index].date.split(" ")[0]) : ""
                            color: parent.parent.parent.on ? win.goldHi : win.bone
                            font.family: "JetBrains Mono"; font.pixelSize: 11
                            horizontalAlignment: Text.AlignRight; anchors.right: parent.right
                        }
                    }
                    Rectangle {
                        width: 11; height: 11; radius: 6; anchors.verticalCenter: parent.verticalCenter
                        color: parent.parent.on ? win.goldHi : win.abyssDeep
                        border.color: parent.parent.on ? win.gold : win.goldDeep; border.width: 2
                        Behavior on color { ColorAnimation { duration: 180 } }
                    }
                }
                MouseArea { anchors.fill: parent; onClicked: win.cur = index }
            }
        }
    }

    // ============================================================
    //  bottom controls
    // ============================================================
    Rectangle {
        id: controls
        height: 108; anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
        gradient: Gradient {
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 0.5; color: "#020608cc" }
            GradientStop { position: 1.0; color: "#020608" }
        }
        Row {
            anchors.centerIn: parent; spacing: 26
            NavChevron { text: "▲"; enabled: win.cur > 0;                   onTapped: win.cur-- }
            Column {
                anchors.verticalCenter: parent.verticalCenter; spacing: 2
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: win.snaps.length ? (win.cur === 0 ? "— SURFACE · THE PRESENT —"
                          : "— " + win.snaps[win.cur].id + " —") : "— no snapshots —"
                    color: win.bone; font.family: "IM Fell DW Pica SC"; font.pixelSize: 10; font.letterSpacing: 4
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: win.snaps.length ? (win.cur === 0 ? "Now" : win.snaps[win.cur].date) : ""
                    color: win.parchHi; font.family: "Cormorant Garamond"; font.italic: true; font.pixelSize: 26
                }
            }
            NavChevron { text: "▼"; enabled: win.cur < win.snaps.length - 1; onTapped: win.cur++ }
            Rectangle {
                visible: win.cur > 0
                width: restoreLbl.width + 44; height: 50; radius: 3; color: win.burgundy
                border.color: "#3a0a06"
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    id: restoreLbl; anchors.centerIn: parent
                    text: "↻  RESTORE TO THIS POINT"; color: win.parchHi
                    font.family: "Cinzel"; font.bold: true; font.pixelSize: 14; font.letterSpacing: 1
                }
                MouseArea { anchors.fill: parent; onClicked: confirmVeil.open() }
            }
        }
    }

    // nav chevron component
    component NavChevron: Rectangle {
        property alias text: chevTxt.text
        signal tapped()
        width: 54; height: 54; radius: 27; color: "#04101a"
        border.color: win.goldDeep; opacity: enabled ? 1 : 0.3
        anchors.verticalCenter: parent.verticalCenter
        Text { id: chevTxt; anchors.centerIn: parent; color: win.goldHi; font.pixelSize: 22 }
        MouseArea { anchors.fill: parent; enabled: parent.enabled; onClicked: parent.tapped() }
    }

    // ============================================================
    //  parchment confirm veil (Mucha) + celestial progress
    // ============================================================
    Rectangle {
        id: confirmVeil
        anchors.fill: parent; z: 60; visible: false; opacity: 0
        color: "#04101aee"
        function open()  { visible = true; opacity = 1; pwField.text = ""; pwField.forceActiveFocus();
                           // reset the WHOLE veil, not just the field's inner box —
                           // after an aborted restore pwGroup stayed faded out and
                           // celGroup kept the stale phase text + old percentage,
                           // so a second RESTORE attempt showed no password field.
                           pwGroup.opacity = 1; pwGroup.y = 0;
                           celGroup.opacity = 0; celPhase.text = ""; celBar.progress = 0;
                           celBar.visible = false; win.restoring = false; }
        function close() { opacity = 0; closeTimer.start(); }
        Behavior on opacity { NumberAnimation { duration: 600 } }
        Timer { id: closeTimer; interval: 600; onTriggered: confirmVeil.visible = false }

        MouseArea { anchors.fill: parent }   // swallow clicks behind the panel

        // the parchment panel
        Rectangle {
            id: panel
            anchors.centerIn: parent; width: 760; height: 460; radius: 4
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#f3e3b5" }
                GradientStop { position: 1.0; color: "#dcc890" }
            }
            border.color: win.goldDeep
            // gilt inner rules
            Rectangle { anchors.fill: parent; anchors.margins: 6; color: "transparent"; border.color: win.gold }
            Rectangle { anchors.fill: parent; anchors.margins: 9; color: "transparent"; border.color: win.goldDeep; opacity: 0.5 }

            Column {
                anchors.centerIn: parent; spacing: 14; width: parent.width * 0.8
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "· SIGILLVM · ADMINISTRI ·"; color: win.sepia
                    font.family: "IM Fell DW Pica SC"; font.pixelSize: 11; font.letterSpacing: 5
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Confirm the descent"; color: win.ink
                    font.family: "Cormorant Garamond"; font.italic: true; font.pixelSize: 44
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter; width: parent.width
                    horizontalAlignment: Text.AlignHCenter; wrapMode: Text.WordWrap
                    text: win.snaps.length && win.cur > 0
                          ? "Enter the administrator seal to restore " + win.snaps[win.cur].id + "."
                          : ""
                    color: win.sepia; font.family: "IM Fell DW Pica"; font.italic: true; font.pixelSize: 17
                }

                // password field — fades + rises out on Enter
                Item {
                    id: pwGroup; width: parent.width; height: 84
                    anchors.horizontalCenter: parent.horizontalCenter
                    Behavior on opacity { NumberAnimation { duration: 500 } }
                    Behavior on y       { NumberAnimation { duration: 500; easing.type: Easing.OutCubic } }
                    Column {
                        anchors.horizontalCenter: parent.horizontalCenter; spacing: 12
                        Rectangle {
                            width: 340; height: 50; radius: 3; color: "#fbf4df"
                            border.color: pwField.activeFocus ? win.burgundy : win.goldDeep
                            anchors.horizontalCenter: parent.horizontalCenter
                            TextInput {
                                id: pwField; anchors.fill: parent; anchors.margins: 12
                                echoMode: TextInput.Password; color: win.ink
                                font.family: "Cormorant Garamond"; font.pixelSize: 22
                                horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignVCenter
                                onAccepted: if (text.length > 0) beginRestore()   // Enter
                            }
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Press Enter to begin."; color: win.sepia
                            font.family: "IM Fell DW Pica"; font.italic: true; font.pixelSize: 13
                        }
                    }
                }

                // celestial progress — fades in after Enter
                Column {
                    id: celGroup; width: parent.width; spacing: 6; opacity: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    Behavior on opacity { NumberAnimation { duration: 600 } }
                    CelestialBar {
                        id: celBar; visible: false
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 640; height: 120
                    }
                    Row {
                        width: 640; anchors.horizontalCenter: parent.horizontalCenter
                        Text { id: celPhase; text: ""; color: win.sepia; font.family: "JetBrains Mono"; font.pixelSize: 12 }
                        Item { width: parent.width - celPhase.width - celPct.width; height: 1 }
                        Text { id: celPct; text: Math.round(celBar.progress) + "%"; color: win.burgundy; font.family: "JetBrains Mono"; font.pixelSize: 12 }
                    }
                }
            }

            // cancel
            Text {
                anchors { horizontalCenter: parent.horizontalCenter; bottom: parent.bottom; bottomMargin: 18 }
                visible: !win.restoring
                text: "Cancel"; color: win.sepia
                font.family: "IM Fell DW Pica SC"; font.pixelSize: 12; font.letterSpacing: 3
                MouseArea { anchors.fill: parent; anchors.margins: -10; onClicked: confirmVeil.close() }
            }
        }
    }

    // ---- restore flow ----
    function beginRestore() {
        win.restoring = true;
        pwGroup.opacity = 0; pwGroup.y = -16;          // field fades + rises out
        celGroup.opacity = 1; celBar.visible = true;   // celestial bar fades in
        if (!backend) return;
        // backend streams progress via the celestialProgress / celestialPhase
        // signals (wired from `btrfs`/rsync restore output). NO simulation here.
        backend.runRestore(win.snaps[win.cur].id, pwField.text);
    }

    // backend → UI signal bridges (connected only if backend exists)
    Connections {
        target: win.backend
        ignoreUnknownSignals: true
        function onRestoreProgress(pct)   { celBar.progress = pct; }
        function onRestorePhase(text)     { celPhase.text = text; }
        function onRestoreDone()          { celPhase.text = "✦ Restored — surfacing to your realm."; if (backend) backend.reboot(); }
        function onRestoreError(msg)      { celPhase.text = msg; win.restoring = false; }
        function onBackupsChanged()       { win.reload(); }
    }
}
