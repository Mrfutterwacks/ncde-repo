import QtQuick
import QtQuick.Window

// Main — Vesper's window. Frameless phosphor surface (a real desktop window, not
// a TTY). Composes the face + status + alert + terminal + quarantine + consent
// gates, and routes every action to backend hooks. STATE is driven by the
// backend (finding present → alert; user opens chat → conversation; etc.).
//
// Wiring layer: replace `VesperBackend {}` below with the Lelan-bound backend.
// This file contains NO data and NO hardcoded Vesper speech.
Window {
    id: win
    width: 1000; height: 680
    // Visible whenever this window PROCESS is running — it is only ever launched on
    // demand (the user opens Vesper to talk) or by the shell's threat trigger, so if
    // the window exists it should be shown. (The old `finding !== null` gate made the
    // whole window VANISH the instant a finding was cleared — e.g. right after you
    // quarantined something — which read as "I typed quarantine and nothing happened.")
    // "Armed but quiet = no window" is achieved by simply not launching this process.
    visible: true
    color: tokens.ground
    flags: Qt.FramelessWindowHint | Qt.Window
    title: "Vesper"
    Component.onCompleted: requestActivate()
    onClosing: Qt.quit()   // closing exits cleanly so the single-instance launcher reopens fresh

    VesperTokens { id: tokens; uiScale: backend.uiScale; highContrast: backend.highContrast }
    VesperBackend { id: backend
        property real uiScale: 1.0
        property bool highContrast: false
    }

    // ambient: when disarmed/idle with no finding, he's a quiet presence.
    property bool hasFinding: backend.finding !== null
    property bool showQuarantine: false
    // the held-count in the header must be real whenever the window is up
    onVisibleChanged: if (visible) backend.refreshQuarantine()

    // ---- CRT ground + scanlines (AnimPolicy/reduce-motion governed) ----
    Rectangle { anchors.fill: parent; color: tokens.ground }
    Canvas {
        id: scan; anchors.fill: parent; opacity: 0.5
        onPaint: { var c=getContext("2d"); c.clearRect(0,0,width,height);
            c.fillStyle = Qt.rgba(0,0,0,0.32);
            for (var y=0;y<height;y+=3) c.fillRect(0,y,width,1); }
        Component.onCompleted: requestPaint()
    }

    // ---- header: identity + ambient status (armed / threats / last update) ----
    Item {
        id: header
        x: tokens.pad; y: tokens.fs(14)
        width: parent.width - tokens.pad*2; height: tokens.fs(30)
        Text {
            text: "VESPER // SENTINEL SHELL"
            color: tokens.pDim; font.family: tokens.mono; font.pixelSize: tokens.small
            font.letterSpacing: 3
        }
        Row {
            anchors.right: parent.right; spacing: tokens.fs(16)
            Text { text: backend.armed ? "● armed" : "○ standby"
                color: backend.armed ? tokens.p : tokens.pDim
                font.family: tokens.mono; font.pixelSize: tokens.small }
            Text { text: backend.threatCount + " watched"
                color: tokens.pDim; font.family: tokens.mono; font.pixelSize: tokens.small }
            // opens the quarantine review pane (§2.8) — underlines on hover so it reads as a control
            Text { text: backend.quarantine.length + " held"
                color: win.showQuarantine ? tokens.pHi : tokens.pDim
                font.family: tokens.mono; font.pixelSize: tokens.small
                font.underline: qh.hovered
                HoverHandler { id: qh; cursorShape: Qt.PointingHandCursor }
                TapHandler { onTapped: { backend.refreshQuarantine(); win.showQuarantine = !win.showQuarantine } }
            }
            Text { text: backend.lastUpdate ? "updated " + backend.lastUpdate : ""
                color: tokens.pDim; font.family: tokens.mono; font.pixelSize: tokens.small }
        }
    }

    // ---- left: the character ----
    VesperFace {
        id: vesper
        x: tokens.fs(30); y: tokens.fs(70)
        width: tokens.fs(280); height: tokens.fs(300)
        p: tokens.p; pHi: tokens.pHi; copper: "#7fffcf"; ground: tokens.ground
        speaking: backend.streaming
        reduceMotion: backend.reduceMotion !== undefined ? backend.reduceMotion : false
    }
    Column {
        anchors.horizontalCenter: vesper.horizontalCenter
        anchors.top: vesper.bottom; spacing: 2
        Text { text: "VESPER"; color: tokens.pHi; font.family: tokens.mono
            font.pixelSize: tokens.title; font.letterSpacing: 4
            anchors.horizontalCenter: parent.horizontalCenter }
        Text { text: "Living Protections"; color: tokens.pDim; font.family: tokens.mono
            font.pixelSize: tokens.small; font.letterSpacing: 4
            anchors.horizontalCenter: parent.horizontalCenter }
    }

    // ---- right: alert (when a finding exists) over the conversation ----
    Item {
        id: rightPane
        x: tokens.fs(340); y: tokens.fs(70)
        width: parent.width - tokens.fs(340) - tokens.pad
        height: parent.height - tokens.fs(70) - tokens.pad

        AlertCard {
            id: alert
            width: parent.width
            tokens: tokens
            finding: backend.finding
            userName: backend.userName
            onBlock: function(id){ backend.block(id) }
            onAllow: function(id){ backend.allow(id) }
            onAnalyse: function(id){ backend.analyse(id) }
            onAskTechnique: function(tid){ backend.ask("What is " + tid + "?") }
            onDismiss: backend.dismiss()
        }

        Terminal {
            id: terminal
            anchors.top: alert.visible ? alert.bottom : parent.top
            anchors.topMargin: alert.visible ? tokens.fs(14) : 0
            width: parent.width
            height: parent.height - (alert.visible ? alert.height + tokens.fs(14) : 0)
            tokens: tokens; backend: backend
            userName: backend.userName; orgName: backend.orgName
        }
    }

    // ---- quarantine review pane (§2.8) — overlays the right pane while open ----
    QuarantinePane {
        anchors.fill: rightPane
        tokens: tokens; backend: backend
        visible: win.showQuarantine
        onClosed: win.showQuarantine = false
    }

    // ---- analysis streaming → terminal as a vesper turn ----
    property string _analysisSeen: ""
    Connections {
        target: backend
        function onAnalysisTextChanged() {
            var full = backend.analysisText;
            if (full.length < win._analysisSeen.length) { win._analysisSeen=""; }
            if (win._analysisSeen.length === 0 && full.length > 0) terminal.pushTurn("vesper","");
            terminal.appendLast(full.slice(win._analysisSeen.length));
            win._analysisSeen = full;
        }
    }

    // ---- consent gates (shown only when backend flips them true) ----
    ConsentBar {
        id: onlineConsent; tokens: tokens
        visible: backend.askOnlineConsent
        prompt: "Vesper wants to look something up online. Allow a quiet background check?"
        onYes: backend.allowOnline(true); onNo: backend.allowOnline(false)
        anchors.bottom: parent.bottom; width: parent.width
    }
    ConsentBar {
        id: updateConsent; tokens: tokens
        visible: backend.askKnowledgeUpdate && !backend.askOnlineConsent
        prompt: "New threats are circulating. Update Vesper's knowledge?"
        yesLabel: "Yes"; noLabel: "Not now"
        onYes: backend.updateKnowledge(true); onNo: backend.updateKnowledge(false)
        anchors.bottom: parent.bottom; width: parent.width
    }
}
