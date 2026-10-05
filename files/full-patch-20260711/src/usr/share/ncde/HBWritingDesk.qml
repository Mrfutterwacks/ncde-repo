import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs
import "hb-stationery.js" as Sta

Item {
    id: writingDesk
    property var pal
    property var win

    // Task #7: undo-send — Send starts a cancellable countdown instead of
    // dispatching immediately; win.despatch() (the real SMTP call) only fires
    // once the countdown elapses uncancelled.
    property bool sendPending: false
    property int  sendCountdown: 6
    function startUndoSend() {
        if (win.composeTo.trim() === "") return
        for (var i = 0; i < win.composeAttachments.length; i++) {
            if (win.composeAttachments[i].risky && !win.composeAttachments[i].confirmed)
                return // unconfirmed risky attachment — tap "send anyway?" on its chip first
        }
        sendPending = true
        sendCountdown = 6
        undoTimer.restart()
        tickTimer.restart()
    }
    function cancelUndoSend() {
        sendPending = false
        undoTimer.stop(); tickTimer.stop()
    }
    Timer { id: undoTimer; interval: 6000; onTriggered: { writingDesk.sendPending = false; win.despatch() } }
    Timer { id: tickTimer; interval: 1000; repeat: true
        onTriggered: { writingDesk.sendCountdown -= 1; if (writingDesk.sendCountdown <= 0) tickTimer.stop() } }

    // Step C/#8/#9: attachment helpers shared by the Attach button, drag-drop,
    // and paste. `entry` is {path, name, inline, risky, confirmed}.
    function addAttachment(path, inline) {
        var name = path.substring(Math.max(path.lastIndexOf("/"), path.lastIndexOf("\\")) + 1)
        var risky = !inline && mail.isExecutableAttachment(path)
        var next = win.composeAttachments.slice()
        next.push({ path: path, name: name, inline: !!inline, risky: risky, confirmed: !risky })
        win.composeAttachments = next
    }
    function removeAttachmentAt(idx) {
        var next = win.composeAttachments.slice()
        next.splice(idx, 1)
        win.composeAttachments = next
    }
    function confirmAttachmentAt(idx) {
        var next = win.composeAttachments.slice()
        next[idx].confirmed = true
        win.composeAttachments = next
    }

    component Hummingbird: Canvas {
        property color tint: ncde.gilt4
        property real  wingPhase: 0.0
        antialiasing: true
        onTintChanged: requestPaint()
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var s = Math.min(width, height) / 100.0;
            ctx.scale(s, s); ctx.fillStyle = tint;
            ctx.beginPath(); ctx.moveTo(14,30); ctx.bezierCurveTo(26,40,34,46,44,52);
            ctx.bezierCurveTo(36,50,22,50,10,54); ctx.bezierCurveTo(18,46,14,38,14,30);
            ctx.closePath(); ctx.fill();
            ctx.beginPath(); ctx.moveTo(40,50); ctx.bezierCurveTo(50,40,64,36,76,40);
            ctx.bezierCurveTo(70,48,60,56,50,60); ctx.bezierCurveTo(46,58,42,55,40,50);
            ctx.closePath(); ctx.fill();
            ctx.beginPath(); ctx.arc(76,40,8,0,2*Math.PI); ctx.fill();
            ctx.beginPath(); ctx.moveTo(83,39); ctx.lineTo(99,33); ctx.lineTo(84,43); ctx.closePath(); ctx.fill();
            var ang = (-26 + wingPhase * 46) * Math.PI/180;
            ctx.save(); ctx.translate(50,50); ctx.rotate(ang); ctx.translate(-50,-50);
            ctx.beginPath(); ctx.moveTo(50,50); ctx.bezierCurveTo(44,30,40,16,30,8);
            ctx.bezierCurveTo(46,14,58,30,60,48); ctx.bezierCurveTo(57,50,53,51,50,50);
            ctx.closePath(); ctx.globalAlpha = 0.92; ctx.fill(); ctx.globalAlpha = 1; ctx.restore();
            ctx.fillStyle = "#c64b63"; ctx.beginPath(); ctx.arc(70,46,3.2,0,2*Math.PI); ctx.fill();
        }
    }

    component WaxSeal: Canvas {
        antialiasing: true
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var cx=width/2, cy=height/2, R=Math.min(cx,cy)-1;
            var g = ctx.createRadialGradient(cx-R*0.3,cy-R*0.3,1,cx,cy,R);
            g.addColorStop(0,"#7aaa8a"); g.addColorStop(0.55,"#4a6650"); g.addColorStop(1,"#1b2e20");
            ctx.beginPath(); ctx.arc(cx,cy,R,0,2*Math.PI); ctx.fillStyle=g; ctx.fill();
            ctx.lineWidth=1; ctx.strokeStyle="#1b2e20"; ctx.stroke();
            ctx.strokeStyle="rgba(246,227,176,0.5)"; ctx.lineWidth=0.8;
            ctx.beginPath(); ctx.arc(cx,cy,R*0.8,0,2*Math.PI); ctx.stroke();
        }
    }

    onVisibleChanged: {
        if (visible) {
            toInput.text   = win.composeTo
            ccInput.text   = win.composeCc
            bccInput.text  = win.composeBcc
            subjInput.text = win.composeSubj
            bodyEdit.text  = win.composeBody
            writeCanvas.requestPaint()
            writeCrest.requestPaint()
            writeThumb.requestPaint()
            Qt.callLater(function() { bodyEdit.forceActiveFocus() })
        } else {
            // Cancel any not-yet-fired undo-send countdown before clearing fields —
            // navigating away mid-countdown must not later despatch() with blanked
            // To/Body. If a send already completed, despatch() already fired before
            // this ran (it's what set mailPaneView away in the first place), so this
            // is a harmless no-op in that case.
            cancelUndoSend()
            toInput.text = ""; ccInput.text = ""; bccInput.text = ""; subjInput.text = ""; bodyEdit.text = ""
            win.composeTo = ""; win.composeCc = ""; win.composeBcc = ""; win.composeSubj = ""; win.composeBody = ""
            win.composeAttachments = []
        }
    }

    ColumnLayout {
        anchors.fill: parent; spacing: 0

        // ── action bar ──────────────────────────────────────────────────────
        Rectangle {
            Layout.fillWidth: true; Layout.preferredHeight: Math.max(56, theme.fontMedium * 2 + 26); color: pal.paper2
            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: pal.gilt1 }

            Row {
                anchors.left: parent.left; anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter; spacing: 8
                Rectangle {
                    height: backLbl.implicitHeight + 14; width: backLbl.implicitWidth + 40; radius: height/2
                    border.color: pal.gilt1; border.width: 1.5
                    color: backHov.hovered ? pal.paper0 : "transparent"
                    Row { anchors.centerIn: parent; spacing: 6
                        Text { text: "←"; font.pixelSize: theme.fontMedium; color: pal.gilt0
                               font.family: pal.titles; anchors.verticalCenter: parent.verticalCenter }
                        Text { id: backLbl; text: "Gallery"; font.family: pal.titles
                               font.pixelSize: theme.fontSmall; color: pal.gilt0
                               anchors.verticalCenter: parent.verticalCenter }
                    }
                    HoverHandler { id: backHov }
                    TapHandler { onTapped: win.mailPaneView = "gallery" }
                }
            }

            Text { anchors.centerIn: parent
                   text: "A New Despatch"; font.family: pal.display; font.bold: true
                   font.pixelSize: theme.fontMedium; color: pal.wineText2; font.letterSpacing: 1.5 }

            Rectangle {
                anchors.right: parent.right; anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                height: sendRow.implicitHeight + 12; width: sendRow.implicitWidth + 30; radius: height/2
                border.color: pal.gilt0; border.width: 2
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop { position: 0; color: sendHov.hovered ? pal.verd3 : pal.verd2 }
                    GradientStop { position: 1; color: pal.verd1 } }
                Row { id: sendRow; anchors.centerIn: parent; spacing: 10
                    Text { text: "Send"; font.family: pal.titles; font.weight: Font.DemiBold
                           font.pixelSize: theme.fontMedium; color: pal.gilt5; font.letterSpacing: 1
                           anchors.verticalCenter: parent.verticalCenter }
                    WaxSeal { width: 24; height: 24; anchors.verticalCenter: parent.verticalCenter
                        Hummingbird { anchors.centerIn: parent; width: 14; height: 14; tint: pal.gilt5 } }
                }
                HoverHandler { id: sendHov }
                TapHandler {
                    onTapped: writingDesk.startUndoSend()
                }
            }
        }

        // ── address fields ───────────────────────────────────────────────────
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: addrCol.implicitHeight
            color: pal.paper1
            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: pal.gilt1 }
            Column {
                id: addrCol; width: parent.width

                Rectangle { width: parent.width; height: Math.max(40, theme.fontMedium * 2 + 8); color: "transparent"
                    Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: pal.gilt1 }
                    Row { anchors.fill: parent; anchors.leftMargin: 20; anchors.rightMargin: 20; spacing: 12
                        Text { text: "TO"; font.family: pal.fell; font.italic: true
                               font.pixelSize: theme.fontSmall; color: pal.gilt1; font.letterSpacing: 2; width: 60
                               anchors.verticalCenter: parent.verticalCenter }
                        TextInput { id: toInput; width: parent.width - 80
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.family: pal.serif; font.pixelSize: theme.fontLarge; color: pal.ink
                                    clip: true; selectByMouse: true
                                    onTextChanged: win.composeTo = text
                            Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                   text: "recipient@example.com"; font.family: pal.serif; font.pixelSize: theme.fontLarge
                                   color: pal.inkSoft; opacity: 0.5
                                   visible: !toInput.text.length && !toInput.activeFocus }
                        }
                    }
                }

                Rectangle { width: parent.width; height: Math.max(40, theme.fontMedium * 2 + 8); color: "transparent"
                    Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: pal.gilt1 }
                    Row { anchors.fill: parent; anchors.leftMargin: 20; anchors.rightMargin: 20; spacing: 12
                        Text { text: "CC"; font.family: pal.fell; font.italic: true
                               font.pixelSize: theme.fontSmall; color: pal.gilt1; font.letterSpacing: 2; width: 60
                               anchors.verticalCenter: parent.verticalCenter }
                        TextInput { id: ccInput; width: parent.width - 80
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.family: pal.serif; font.pixelSize: theme.fontLarge; color: pal.ink
                                    clip: true; selectByMouse: true
                                    onTextChanged: win.composeCc = text
                            Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                   text: "—"; font.family: pal.serif; font.pixelSize: theme.fontLarge
                                   color: pal.inkSoft; opacity: 0.5
                                   visible: !ccInput.text.length && !ccInput.activeFocus }
                        }
                    }
                }

                Rectangle { width: parent.width; height: Math.max(40, theme.fontMedium * 2 + 8); color: "transparent"
                    Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: pal.gilt1 }
                    Row { anchors.fill: parent; anchors.leftMargin: 20; anchors.rightMargin: 20; spacing: 12
                        Text { text: "BCC"; font.family: pal.fell; font.italic: true
                               font.pixelSize: theme.fontSmall; color: pal.gilt1; font.letterSpacing: 2; width: 60
                               anchors.verticalCenter: parent.verticalCenter }
                        TextInput { id: bccInput; width: parent.width - 80
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.family: pal.serif; font.pixelSize: theme.fontLarge; color: pal.ink
                                    clip: true; selectByMouse: true
                                    onTextChanged: win.composeBcc = text
                            Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                   text: "—"; font.family: pal.serif; font.pixelSize: theme.fontLarge
                                   color: pal.inkSoft; opacity: 0.5
                                   visible: !bccInput.text.length && !bccInput.activeFocus }
                        }
                    }
                }

                Rectangle { width: parent.width; height: Math.max(40, theme.fontMedium * 2 + 8); color: "transparent"
                    Row { anchors.fill: parent; anchors.leftMargin: 20; anchors.rightMargin: 20; spacing: 12
                        Text { text: "SUBJECT"; font.family: pal.fell; font.italic: true
                               font.pixelSize: theme.fontSmall; color: pal.gilt1; font.letterSpacing: 2; width: 60
                               anchors.verticalCenter: parent.verticalCenter }
                        TextInput { id: subjInput; width: parent.width - 80
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.family: pal.serif; font.pixelSize: theme.fontLarge; color: pal.ink
                                    clip: true; selectByMouse: true
                                    onTextChanged: win.composeSubj = text
                            Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                   text: "Regarding…"; font.family: pal.serif; font.pixelSize: theme.fontLarge
                                   color: pal.inkSoft; opacity: 0.5
                                   visible: !subjInput.text.length && !subjInput.activeFocus }
                        }
                    }
                }
            }
        }

        // ── stationery writing area ──────────────────────────────────────────
        Item {
            id: writeArea
            Layout.fillWidth: true; Layout.fillHeight: true
            TapHandler { onTapped: bodyEdit.forceActiveFocus() }

            Canvas {
                id: writeCanvas; anchors.fill: parent
                renderStrategy: Canvas.Cooperative
                onWidthChanged:  if (width > 0 && height > 0) requestPaint()
                onHeightChanged: if (width > 0 && height > 0) requestPaint()
                onPaint: {
                    var ctx = getContext("2d"); ctx.reset()
                    Sta.setByKey(win.composeStationery).paint(ctx, width, height)
                }
            }

            Connections {
                target: win
                function onComposeStationeryChanged() {
                    writeCanvas.requestPaint()
                    writeCrest.requestPaint()
                    writeThumb.requestPaint()
                }
            }

            // Task #8: drag a file onto the letter to attach it, same as tapping Attach.
            DropArea {
                id: writeDropArea
                anchors.fill: parent
                keys: ["text/uri-list"]
                onDropped: function(drop) {
                    if (!drop.hasUrls) return
                    for (var i = 0; i < drop.urls.length; i++)
                        writingDesk.addAttachment(decodeURIComponent(String(drop.urls[i]).replace(/^file:\/\//, "")), false)
                }
            }
            Rectangle {
                anchors.fill: parent; radius: 4; color: "transparent"
                border.width: 2; border.color: pal.gilt3
                visible: writeDropArea.containsDrag
            }

            ColumnLayout {
                anchors.top: parent.top; anchors.bottom: parent.bottom
                anchors.left: parent.left; anchors.right: parent.right
                anchors.leftMargin: Math.max(14, writeArea.width * (Sta.setByKey(win.composeStationery).bodyL || 0.2)) + 6
                anchors.rightMargin: 16; anchors.topMargin: 14; anchors.bottomMargin: 14
                spacing: 0

                Column {
                    Layout.fillWidth: true; spacing: 3
                    // Step E: "Plain" is the operator's "just a regular email" option —
                    // no crest, no injected salutation. Only the letter itself.
                    visible: win.composeStationery !== "plain"
                    Canvas {
                        id: writeCrest; width: 54; height: 28
                        renderStrategy: Canvas.Cooperative
                        onPaint: {
                            var ctx = getContext("2d"); ctx.reset()
                            Sta.crestMark(ctx, width, height, Sta.setByKey(win.composeStationery).nameC)
                        }
                    }
                    Text { text: mail.accountRole.length > 0 ? mail.accountRole : mail.accountName
                           color: Sta.setByKey(win.composeStationery).nameC
                           font.family: pal.display; font.bold: true; font.pixelSize: theme.fontMedium }
                    Text { width: parent.width; horizontalAlignment: Text.AlignRight
                           text: Qt.formatDate(new Date(), "MMMM d, yyyy")
                           color: Sta.setByKey(win.composeStationery).dark ? ncde.gilt5 : ncde.gilt1
                           font.family: pal.garamond; font.italic: true; font.pixelSize: theme.fontSmall }
                    Item { width: 1; height: 4 }
                    Text { text: Sta.setByKey(win.composeStationery).sal || "My dear friend,"
                           color: Sta.setByKey(win.composeStationery).bodyC
                           font.family: pal.garamond; font.italic: true; font.pixelSize: theme.fontMedium }
                    Item { width: 1; height: 6 }
                }

                Flickable {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    contentHeight: bodyEdit.implicitHeight; clip: true
                    TextEdit {
                        id: bodyEdit; width: parent.width; text: ""
                        font.family: pal.garamond; font.pixelSize: theme.fontLarge
                        color: Sta.setByKey(win.composeStationery).bodyC
                        wrapMode: TextEdit.Wrap; selectByMouse: true
                        onTextChanged: win.composeBody = text
                    }
                }

                Column {
                    Layout.fillWidth: true; spacing: 1
                    Item { width: 1; height: 8 }
                    // Step E: "Plain" keeps the sender's own name/signature below (that's
                    // the user's identity, not decoration) but skips the injected
                    // decorative signoff phrase ("Yours sincerely," etc.).
                    Text { visible: win.composeStationery !== "plain"
                           text: Sta.setByKey(win.composeStationery).signoff || "Yours sincerely,"
                           color: Sta.setByKey(win.composeStationery).bodyC
                           font.family: pal.garamond; font.italic: true; font.pixelSize: theme.fontMedium }
                    Text { text: mail.accountRole.length > 0 ? mail.accountRole : mail.accountName
                           color: Sta.setByKey(win.composeStationery).nameC
                           font.family: pal.serif; font.italic: true; font.pixelSize: theme.fontLarge }
                    Text { visible: mail.accountSignature.length > 0
                           text: mail.accountSignature
                           color: Sta.setByKey(win.composeStationery).bodyC; opacity: 0.75
                           font.family: pal.fell; font.italic: true; font.pixelSize: theme.fontSmall }
                }
            }
        }

        // ── attachment chips (Step C / Task #8) — only takes space when non-empty ──
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: win.composeAttachments.length > 0 ? 44 : 0
            visible: win.composeAttachments.length > 0
            clip: true; color: pal.paper1
            Rectangle { anchors.top: parent.top; width: parent.width; height: 1; color: pal.gilt1 }
            Flickable {
                anchors.fill: parent; anchors.margins: 6
                contentWidth: chipsRow.implicitWidth; contentHeight: height
                flickableDirection: Flickable.HorizontalFlick; clip: true
                Row {
                    id: chipsRow; spacing: 8; height: parent.height
                    Repeater {
                        model: win.composeAttachments
                        delegate: Rectangle {
                            height: 30; radius: 15
                            width: chipRow.implicitWidth + 16
                            color: modelData.risky && !modelData.confirmed ? Qt.rgba(0.6,0.2,0.1,0.18) : pal.paper2
                            border.width: 1.5
                            border.color: modelData.risky && !modelData.confirmed ? "#a83c1c" : pal.gilt1
                            Row { id: chipRow; anchors.centerIn: parent; spacing: 6
                                Text { text: modelData.inline ? "🖼" : "📎"; font.pixelSize: theme.fontSmall
                                       anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData.name; font.family: pal.serif; font.pixelSize: theme.fontSmall
                                       color: pal.ink; anchors.verticalCenter: parent.verticalCenter }
                                Text { visible: modelData.risky && !modelData.confirmed
                                       text: "— send anyway?"; font.family: pal.titles; font.pixelSize: theme.fontSmall
                                       color: "#a83c1c"; anchors.verticalCenter: parent.verticalCenter
                                       TapHandler { onTapped: writingDesk.confirmAttachmentAt(index) } }
                                Text { text: "✕"; font.pixelSize: theme.fontSmall; color: pal.gilt0
                                       anchors.verticalCenter: parent.verticalCenter
                                       TapHandler { onTapped: writingDesk.removeAttachmentAt(index) } }
                            }
                        }
                    }
                }
            }
        }

        FileDialog {
            id: attachPicker
            title: "Attach files"
            fileMode: FileDialog.OpenFiles
            onAccepted: {
                for (var i = 0; i < selectedFiles.length; i++)
                    writingDesk.addAttachment(decodeURIComponent(String(selectedFiles[i]).replace(/^file:\/\//, "")), false)
            }
        }

        // ── stationery picker bar ────────────────────────────────────────────
        Rectangle {
            Layout.fillWidth: true; Layout.preferredHeight: Math.max(52, theme.fontMedium * 2 + 22); color: pal.paper2
            Rectangle { anchors.top: parent.top; width: parent.width; height: 1; color: pal.gilt1 }
            Row {
                anchors.left: parent.left; anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter; spacing: 8
                Text { text: Sta.setByKey(win.composeStationery).name || "Stationery"
                       font.family: pal.fell; font.italic: true; font.pixelSize: theme.fontSmall; color: pal.inkSoft
                       anchors.verticalCenter: parent.verticalCenter }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 34; height: 26; radius: 4; clip: true
                    border.color: pal.gilt1; border.width: 1
                    Canvas {
                        id: writeThumb; anchors.fill: parent
                        renderStrategy: Canvas.Cooperative
                        Component.onCompleted: requestPaint()
                        onPaint: { var c=getContext("2d"); c.reset(); Sta.setByKey(win.composeStationery).paint(c,width,height) }
                    }
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    height: 26; width: chooseLbl.implicitWidth + 16; radius: 6
                    border.color: chooseHov.hovered ? pal.gilt3 : pal.gilt1; border.width: 1.5
                    color: Qt.rgba(0,0,0,0.06)
                    Text { id: chooseLbl; text: "Choose…"; font.family: pal.titles; font.pixelSize: theme.fontSmall
                           color: pal.gilt0; anchors.centerIn: parent }
                    HoverHandler { id: chooseHov }
                    TapHandler { onTapped: win.mailPaneView = "gallery" }
                }
            }

            // Step C: Attach — opens the native multi-file picker.
            Row {
                anchors.right: parent.right; anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                Rectangle {
                    height: 30; width: attachLbl.implicitWidth + 34; radius: 15
                    border.color: attachHov.hovered ? pal.gilt3 : pal.gilt1; border.width: 1.5
                    color: Qt.rgba(0,0,0,0.06)
                    Row { anchors.centerIn: parent; spacing: 6
                        Text { text: "📎"; font.pixelSize: theme.fontSmall; anchors.verticalCenter: parent.verticalCenter }
                        Text { id: attachLbl; text: "Attach…"; font.family: pal.titles; font.pixelSize: theme.fontSmall
                               color: pal.gilt0; anchors.verticalCenter: parent.verticalCenter }
                    }
                    HoverHandler { id: attachHov }
                    TapHandler { onTapped: attachPicker.open() }
                }
                Item { width: 10; height: 1 }
                Rectangle {
                    height: 30; width: imgLbl.implicitWidth + 34; radius: 15
                    border.color: imgHov.hovered ? pal.gilt3 : pal.gilt1; border.width: 1.5
                    color: Qt.rgba(0,0,0,0.06)
                    Row { anchors.centerIn: parent; spacing: 6
                        Text { text: "🖼"; font.pixelSize: theme.fontSmall; anchors.verticalCenter: parent.verticalCenter }
                        Text { id: imgLbl; text: "Insert Image…"; font.family: pal.titles; font.pixelSize: theme.fontSmall
                               color: pal.gilt0; anchors.verticalCenter: parent.verticalCenter }
                    }
                    HoverHandler { id: imgHov }
                    TapHandler { onTapped: inlineImagePicker.open() }
                }
            }
        }
    }

    // Task #7: undo-send banner — floats over the whole desk, not part of the
    // ColumnLayout's document flow (it was a layout child using raw anchors
    // before, which QML flags as undefined behavior — journal-caught live,
    // 2026-09-22 — and rendered unreliably/invisibly as a result).
    Rectangle {
        parent: writingDesk
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 64
        visible: writingDesk.sendPending
        width: undoRow.implicitWidth + 28; height: undoRow.implicitHeight + 16; radius: height/2; z: 60
        color: pal.wine2; border.color: pal.gilt2; border.width: 1.5
        Row { id: undoRow; anchors.centerIn: parent; spacing: 12
            Text { text: "Sending in " + writingDesk.sendCountdown + "s…"
                   font.family: pal.titles; font.pixelSize: theme.fontSmall; color: pal.gilt5
                   anchors.verticalCenter: parent.verticalCenter }
            Rectangle { height: 24; width: undoLbl.implicitWidth + 16; radius: 12
                color: undoHov.hovered ? pal.gilt1 : "transparent"
                border.color: pal.gilt4; border.width: 1
                Text { id: undoLbl; text: "Undo"; anchors.centerIn: parent
                       font.family: pal.titles; font.weight: Font.DemiBold
                       font.pixelSize: theme.fontSmall; color: pal.gilt5 }
                HoverHandler { id: undoHov }
                TapHandler { onTapped: writingDesk.cancelUndoSend() }
            }
        }
    }

    // Task #9: "inline image paste" — true OS-clipboard image interception isn't
    // reliably available on this Qt/NCDE stack (see the documented Clipboard
    // "Mechanism B" bug), so this is the honest working version: pick an image
    // file and it's embedded inline in the letter (Content-Disposition: inline,
    // referenced via cid: in the HTML body) rather than sent as a plain attachment.
    FileDialog {
        id: inlineImagePicker
        title: "Insert an image into the letter"
        fileMode: FileDialog.OpenFile
        nameFilters: ["Images (*.png *.jpg *.jpeg *.gif *.webp)"]
        onAccepted: {
            writingDesk.addAttachment(decodeURIComponent(String(selectedFile).replace(/^file:\/\//, "")), true)
        }
    }

    // stationery drawer lives inside this component — its taps stay here
    HBStationery {
        id: writeStationeryDrawer
        userName: mail.accountRole.length > 0 ? mail.accountRole : mail.accountName
        current: win.composeStationery
        onPicked: function(key) { win.composeStationery = key }
    }
}
