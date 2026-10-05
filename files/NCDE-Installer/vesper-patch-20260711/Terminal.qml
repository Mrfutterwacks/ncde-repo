import QtQuick

// Terminal — conversation mode + live streaming. Renders the running transcript,
// appends backend.analysisText / backend.chatReply as tokens arrive, and emits
// ask(text). No persona text is hardcoded — every Vesper line is backend-driven.
Item {
    id: term
    property var tokens
    property var backend
    property string userName: ""
    property string orgName: ""

    // transcript model: { who: "you"|"vesper"|"system", text }
    property var turns: []
    function pushTurn(who, text){ var a = turns.slice(); a.push({who:who, text:text}); turns = a; }
    function appendLast(text){
        if (turns.length === 0) return;
        var a = turns.slice(); a[a.length-1] = { who:a[a.length-1].who, text:a[a.length-1].text + text };
        turns = a;
    }

    Column {
        anchors.fill: parent; spacing: tokens.fs(10)

        ListView {
            id: list
            width: parent.width
            height: parent.height - promptRow.height - chips.height - tokens.fs(20)
            clip: true; model: term.turns
            boundsBehavior: Flickable.StopAtBounds
            onCountChanged: positionViewAtEnd()
            delegate: Column {
                width: list.width; bottomPadding: tokens.fs(12)
                Text {
                    text: modelData.who === "you" ? (term.userName || "you").toLowerCase()
                        : modelData.who === "system" ? "system" : "vesper"
                    color: tokens.pDim; font.family: tokens.mono; font.pixelSize: tokens.small
                    font.letterSpacing: 2
                }
                Text {
                    width: list.width
                    text: modelData.text
                    color: modelData.who === "vesper" ? tokens.pHi
                         : modelData.who === "system" ? tokens.pDim : tokens.p
                    opacity: modelData.who === "you" ? 0.85 : 1
                    font.family: tokens.mono; font.pixelSize: tokens.body
                    wrapMode: Text.WordWrap; lineHeight: 1.4
                }
            }
        }

        // anticipation chips — the brain's suggested next steps, tappable (feels alive)
        Flow {
            id: chips
            width: parent.width; spacing: tokens.fs(8)
            Repeater {
                model: (term.backend && term.backend.suggestions) ? term.backend.suggestions : []
                delegate: Rectangle {
                    radius: tokens.fs(6)
                    color: chipHover.hovered ? tokens.ground2 : "transparent"
                    border.color: tokens.pDim; border.width: 1
                    height: chipTxt.implicitHeight + tokens.fs(8)
                    width: chipTxt.implicitWidth + tokens.fs(16)
                    Text { id: chipTxt; anchors.centerIn: parent; text: modelData
                        color: tokens.p; font.family: tokens.mono; font.pixelSize: tokens.small }
                    HoverHandler { id: chipHover; cursorShape: Qt.PointingHandCursor }
                    TapHandler { onTapped: { term.pushTurn("you", modelData); term.backend.ask(modelData); } }
                }
            }
        }

        Row {
            id: promptRow
            width: parent.width; spacing: tokens.fs(10)
            Text { text: "you>"; color: tokens.pDim; font.family: tokens.mono
                font.pixelSize: tokens.body; anchors.verticalCenter: parent.verticalCenter }
            TextInput {
                id: field
                width: parent.width - tokens.fs(60)
                anchors.verticalCenter: parent.verticalCenter
                color: tokens.p; font.family: tokens.mono; font.pixelSize: tokens.body
                clip: true
                focus: true
                Component.onCompleted: forceActiveFocus()
                onAccepted: {
                    var v = text.trim(); if (!v) return;
                    term.pushTurn("you", v);
                    backend.ask(v); text = "";
                }
                // blinking cursor block
                Rectangle { id: vesperCursor; width: 9; height: tokens.body; color: tokens.p
                    x: field.cursorRectangle.x; visible: field.activeFocus
                    SequentialAnimation on opacity { loops: Animation.Infinite; running: vesperCursor.visible && Qt.application.state === Qt.ApplicationActive
                        NumberAnimation { to:0; duration:530 } NumberAnimation { to:1; duration:530 } } }
            }
        }
    }

    // stream sinks: append tokens to the latest vesper turn as they arrive
    property string _chatSeen: ""
    Connections {
        target: backend
        function onChatReplyChanged() {
            var full = backend.chatReply;
            if (full.length < term._chatSeen.length) term._chatSeen = "";
            term.appendLast(full.slice(term._chatSeen.length));
            term._chatSeen = full;
        }
    }
}
