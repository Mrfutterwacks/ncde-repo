import QtQuick

// AlertCard — the "he comes to you" moment. Calm authority, never alarmist.
// Renders a finding in plain language + the choices. Pure surface: every field
// is bound from backend.finding; the buttons emit the named hooks.
Item {
    id: card
    property var tokens
    property var finding: null          // { id, threat_class, basis, verdict, recommendation, explanation, mitre[] }
    property string userName: ""
    signal block(string id)
    signal allow(string id)
    signal analyse(string id)
    signal askTechnique(string tid)
    signal dismiss()

    visible: finding !== null
    implicitHeight: col.implicitHeight + tokens.pad*2

    // severity accent — calm: benign=phosphor, suspicious=amber, malicious=danger
    function accent(){
        if (!finding) return tokens.p;
        return finding.verdict === "malicious" ? tokens.danger
             : finding.verdict === "suspicious" ? tokens.amber : tokens.p;
    }

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0.02,0.10,0.07,0.6)
        border.color: card.accent(); border.width: 1; radius: tokens.radius
    }

    Column {
        id: col
        x: tokens.pad; y: tokens.pad
        width: parent.width - tokens.pad*2
        spacing: tokens.fs(12)

        Row {
            spacing: tokens.fs(10)
            Rectangle { width: 8; height: 8; radius: 4; y: tokens.fs(6); color: card.accent() }
            Text {
                text: finding ? (finding.verdict || "").toUpperCase() + " · " + (finding.threat_class || "") : ""
                color: card.accent(); font.family: tokens.mono; font.pixelSize: tokens.small
                font.letterSpacing: 2
            }
            Text {
                // 2026-07-05 audit: was a fabricated "92% confidence" — there is no
                // probability model. Show the engine's real basis instead.
                text: finding ? (finding.basis || "") : ""
                color: tokens.pDim; font.family: tokens.mono; font.pixelSize: tokens.small
            }
        }

        // plain-language explanation (his words, from the model — never hardcoded)
        Text {
            width: parent.width
            text: finding ? finding.explanation : ""
            color: tokens.pHi; font.family: tokens.mono; font.pixelSize: tokens.body
            wrapMode: Text.WordWrap; lineHeight: 1.4
        }

        // MITRE techniques: each is an "ask what is Txxx?" affordance
        Flow {
            width: parent.width; spacing: tokens.fs(8)
            visible: finding && finding.mitre && finding.mitre.length > 0
            Repeater {
                model: finding && finding.mitre ? finding.mitre : []
                Rectangle {
                    height: tokens.fs(24); radius: 4
                    width: tlabel.implicitWidth + tokens.fs(16)
                    color: "transparent"; border.color: tokens.pDim; border.width: 1
                    Text { id: tlabel; anchors.centerIn: parent; text: modelData
                        color: tokens.p; font.family: tokens.mono; font.pixelSize: tokens.small }
                    MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor
                        onClicked: card.askTechnique(modelData) }
                }
            }
        }

        // choices — obvious, calm, not buried
        Row {
            spacing: tokens.fs(10)
            VesperButton { tokens: card.tokens; label: "Block";   accent: tokens.danger
                onClicked: if (finding) card.block(finding.id) }
            VesperButton { tokens: card.tokens; label: "Allow";   accent: tokens.p
                onClicked: if (finding) card.allow(finding.id) }
            VesperButton { tokens: card.tokens; label: "Analyse"; accent: tokens.amber
                onClicked: if (finding) card.analyse(finding.id) }
            VesperButton { tokens: card.tokens; label: "Dismiss"; ghost: true
                onClicked: card.dismiss() }
        }
    }
}
