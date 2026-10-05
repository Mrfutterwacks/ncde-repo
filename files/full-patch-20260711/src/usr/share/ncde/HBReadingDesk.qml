import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.platform as Platform

Item {
    id: readingDesk
    property var pal
    property var win

    // D-2 (HB-SEC-2): pending link state — set when checkLink returns non-clean
    property string pendingLinkUrl:    ""
    property string pendingLinkStatus: ""   // "blocked:<cat>" | "exec-attachment"
    property bool   trustExpanded:     false

    // Step D: inbound attachments — save-status banner + the part currently
    // targeted by the save dialog (partNumber is set right before .open()).
    property string attachStatus: ""
    property string savePartNumber: ""
    function humanSize(bytes) {
        if (!bytes || bytes <= 0) return "";
        if (bytes < 1024) return bytes + " B";
        if (bytes < 1024*1024) return Math.round(bytes/1024) + " KB";
        return (bytes/1024/1024).toFixed(1) + " MB";
    }
    Connections {
        target: mail
        function onAttachmentSaved(ok, message) {
            readingDesk.attachStatus = ok ? ("Saved to " + message) : ("Save failed: " + message)
            attachStatusTimer.restart()
        }
    }
    Timer { id: attachStatusTimer; interval: 4500; onTriggered: readingDesk.attachStatus = "" }

    FileDialog {
        id: saveAttachmentDialog
        title: "Save attachment"
        fileMode: FileDialog.SaveFile
        currentFolder: Platform.StandardPaths.writableLocation(Platform.StandardPaths.DownloadLocation)
        onAccepted: {
            mail.saveAttachment(readingDesk.savePartNumber,
                                 decodeURIComponent(String(selectedFile).replace(/^file:\/\//, "")))
        }
    }

    function initials(name) {
        if (!name) return "·";
        var parts = name.split(/\s+/).filter(function(x) { return x.length; });
        return parts.slice(0, 2).map(function(w) { return w[0]; }).join("").toUpperCase();
    }

    function richBody(html) {
        if (!html) return "";
        var s = html;
        // Strip MIME multipart structure before HTML processing
        s = s.replace(/This is a multi-part message[^.]*\./gi, "");
        s = s.replace(/--[A-Za-z0-9+\/=_.?:-]{4,}(?:--)?/g, "");
        s = s.replace(/Content-(?:Type|Transfer-Encoding|Disposition|ID)[^\n]*/gi, "");
        s = s.replace(/MIME-Version:[^\n]*/gi, "");
        // Strip full document shell — head, style blocks, scripts
        s = s.replace(/<head[\s\S]*?<\/head>/gi, "");
        s = s.replace(/<style[\s\S]*?<\/style>/gi, "");
        s = s.replace(/<script[\s\S]*?<\/script>/gi, "");
        s = s.replace(/<!DOCTYPE[^>]*>/gi, "");
        s = s.replace(/<\/?html[^>]*>/gi, "");
        s = s.replace(/<\/?body[^>]*>/gi, "");
        // Flatten table layout to inline text
        s = s.replace(/<\/td>/gi, " ");
        s = s.replace(/<\/tr>/gi, "");
        s = s.replace(/<t[dhr][^>]*>/gi, "");
        s = s.replace(/<\/t[dhr]>/gi, "");
        s = s.replace(/<table[^>]*>/gi, "");
        s = s.replace(/<\/table>/gi, "");
        // Strip sender's own class= and style= so their CSS cannot override ours
        s = s.replace(/ class=(["'])[^"']*\1/gi, "");
        s = s.replace(/ style=(["'])[^"']*\1/gi, "");
        // Images: strip file://, data: URIs and 1÷1 tracking pixels; allow http/https
        s = s.replace(/<img[^>]*\bsrc=(["'])(?:file:|data:)[^"']*(\1)[^>]*>/gi, "");
        s = s.replace(/<img(?=[^>]*\bwidth=(["'])1\3)[^>]*>/gi, "");
        s = s.replace(/<img(?=[^>]*\bheight=(["'])1\4)[^>]*>/gi, "");
        s = s.replace(/<link[^>]*>/gi, "");
        // Decode named entities
        s = s.replace(/&nbsp;/g, " ");
        s = s.replace(/&amp;/g, "&");
        s = s.replace(/&lt;/g, "<");
        s = s.replace(/&gt;/g, ">");
        s = s.replace(/&quot;/g, "\"");
        s = s.replace(/&#39;/g, "'");
        s = s.replace(/&apos;/g, "'");
        // Strip numeric entities (spam tracking invisible chars, e.g. &#8199; &#65279;)
        s = s.replace(/&#x[0-9a-fA-F]+;/gi, "");
        s = s.replace(/&#\d+;/g, "");
        // Normalize raw NBSP from QP-decoded Latin-1 (U+00A0 → plain space)
        s = s.replace(/\u00A0/g, " ");
        // Inject NCDE stylesheet — overrides everything that remains
        var css = "<style>"
            + "p { margin: 0 0 14px 0; }"
            + "b, strong { color: " + pal.wineText2 + "; font-weight: bold; }"
            + "i, em { color: " + pal.inkSoft + "; font-style: italic; }"
            + "a { color: " + pal.verd1 + "; text-decoration: none; }"
            + "blockquote { color: " + pal.inkSoft + "; margin: 8px 0 8px 20px; }"
            + "ul, ol { margin: 0 0 12px 20px; }"
            + "li { margin-bottom: 4px; }"
            + "</style>";
        return css + s.trim();
    }

    ColumnLayout {
        anchors.fill: parent; spacing: 0

        // action bar
        Rectangle {
            id: actionBar
            Layout.fillWidth: true; Layout.preferredHeight: backLbl.implicitHeight + 34; color: pal.paper2
            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: pal.gilt1 }
            // Too narrow for every label (big text dial / small window)? Secondary
            // buttons show just their icon rather than spilling off the edge.
            property bool compact: false
            Text { id: labelProbe; visible: false; font.family: pal.titles; font.pixelSize: theme.fontSmall
                   text: "Stationery Reply Reply All Forward Unread Archive Spam Delete" }
            onWidthChanged: compact = (labelProbe.implicitWidth + 8 * (theme.fontSmall * 2 + 30) + 40) > width
            Row {
                anchors.left: parent.left; anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter; spacing: 6

                // ← back to stationery gallery
                Rectangle {
                    height: backLbl.implicitHeight + 14; width: backRow.implicitWidth + 22; radius: height/2
                    border.color: pal.gilt1; border.width: 1.5
                    color: backHov.hovered ? pal.paper0 : "transparent"
                    Row { id: backRow; anchors.centerIn: parent; spacing: 6
                        Text { text: "←"; font.pixelSize: theme.fontMedium; color: pal.gilt0
                               font.family: pal.titles; anchors.verticalCenter: parent.verticalCenter }
                        Text { id: backLbl; text: "Stationery"; font.family: pal.titles
                               font.pixelSize: theme.fontSmall; color: pal.gilt0
                               anchors.verticalCenter: parent.verticalCenter }
                    }
                    HoverHandler { id: backHov }
                    TapHandler { onTapped: win.mailPaneView = "gallery" }
                }

                Repeater {
                    model: [ {a:"reply",    ic:"i-reply",     t:"Reply",    p:true  },
                             {a:"replyall", ic:"i-reply-all", t:"Reply All",p:false },
                             {a:"forward",  ic:"i-forward",   t:"Forward",  p:false },
                             {a:"unread",   ic:"i-draft",     t:"Unread",   p:false },
                             {a:"archive",  ic:"i-archive",   t:"Archive",  p:false },
                             {a:"spam",     ic:"i-spam",      t:"Spam",     p:false },
                             {a:"trash",    ic:"i-trash",     t:"Delete",   p:false } ]
                    Rectangle {
                        height: backLbl.implicitHeight + 14; width: raRow.implicitWidth + 22; radius: height/2
                        property bool prim: modelData.p
                        border.color: prim ? pal.verd1 : pal.gilt1; border.width: 1.5
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop { position: 0; color: prim ? pal.verd3 : (raHov.hovered ? pal.paper0 : pal.paper1) }
                            GradientStop { position: 1; color: prim ? pal.verd2 : pal.paper2 } }
                        Row { id: raRow; anchors.centerIn: parent; spacing: 7
                            HBIcon { width: theme.fontSmall; height: theme.fontSmall; name: modelData.ic
                                     tint: prim ? pal.paper0 : pal.gilt0
                                     anchors.verticalCenter: parent.verticalCenter }
                            Text { text: modelData.t; font.family: pal.titles; font.pixelSize: theme.fontSmall
                                   visible: prim || !actionBar.compact
                                   color: prim ? pal.paper0 : pal.gilt0
                                   anchors.verticalCenter: parent.verticalCenter }
                        }
                        HoverHandler { id: raHov }
                        TapHandler { onTapped: {
                            if (modelData.a === "unread" && win.activeMsgId !== "") {
                                win.noteChange("unread", [win.activeMsgId])
                                mail.markRead(win.activeMsgId, false)
                                win.activeMsgId = ""; win.mailPaneView = "gallery"
                            } else if (modelData.a === "archive" && win.activeMsgId !== "") {
                                win.noteChange("archive", [win.activeMsgId]); mail.archiveMessage(win.activeMsgId); win.activeMsgId = ""; win.mailPaneView = "gallery"
                            } else if (modelData.a === "trash" && win.activeMsgId !== "") {
                                win.noteChange("delete", [win.activeMsgId]); mail.deleteMessage(win.activeMsgId); win.activeMsgId = ""; win.mailPaneView = "gallery"
                            } else if (modelData.a === "spam" && win.activeMsgId !== "") {
                                win.noteChange("spam", [win.activeMsgId]); mail.reportSpam(win.activeMsgId); win.activeMsgId = ""; win.mailPaneView = "gallery"
                            } else if (modelData.a === "reply" || modelData.a === "replyall") {
                                win.composeTo   = mail.current.addr || ""
                                win.composeSubj = mail.current.subj ? "Re: " + mail.current.subj : ""
                                if (modelData.a === "replyall")
                                    win.composeCc = mail.current.to && mail.current.to !== "me" ? mail.current.to : ""
                                var rPlain = mail.current.body ? mail.current.body
                                    .replace(/This is a multi-part message[^.]*\./gi,"")
                                    .replace(/--[A-Za-z0-9+\/=_.?:-]{4,}(?:--)?/g,"")
                                    .replace(/Content-(?:Type|Transfer-Encoding|Disposition|ID)[^\n]*/gi,"")
                                    .replace(/MIME-Version:[^\n]*/gi,"")
                                    .replace(/<style[\s\S]*?<\/style>/gi,"")
                                    .replace(/<script[\s\S]*?<\/script>/gi,"")
                                    .replace(/<head[\s\S]*?<\/head>/gi,"")
                                    .replace(/<!--[\s\S]*?-->/g,"")
                                    .replace(/<[^>]*>/g,"")
                                    .replace(/&lt;/g,"<").replace(/&gt;/g,">").replace(/&amp;/g,"&").replace(/&nbsp;/g," ")
                                    .replace(/&#x[0-9a-fA-F]+;/gi,"").replace(/&#\d+;/g,"")
                                    .replace(/\s{2,}/g," ").trim() : ""
                                win.composeBody = "\n\n----- Original Message -----\nFrom: "
                                    + (mail.current.from || "") + " <" + (mail.current.addr || "") + ">\n"
                                    + "Date: " + (mail.current.date || "") + "\n\n"
                                    + rPlain
                                win.composeStationery = "damask"
                                win.mailPaneView = "writing"
                            } else if (modelData.a === "forward") {
                                win.composeSubj = mail.current.subj ? "Fwd: " + mail.current.subj : ""
                                var fPlain = mail.current.body ? mail.current.body
                                    .replace(/This is a multi-part message[^.]*\./gi,"")
                                    .replace(/--[A-Za-z0-9+\/=_.?:-]{4,}(?:--)?/g,"")
                                    .replace(/Content-(?:Type|Transfer-Encoding|Disposition|ID)[^\n]*/gi,"")
                                    .replace(/MIME-Version:[^\n]*/gi,"")
                                    .replace(/<style[\s\S]*?<\/style>/gi,"")
                                    .replace(/<script[\s\S]*?<\/script>/gi,"")
                                    .replace(/<head[\s\S]*?<\/head>/gi,"")
                                    .replace(/<!--[\s\S]*?-->/g,"")
                                    .replace(/<[^>]*>/g,"")
                                    .replace(/&lt;/g,"<").replace(/&gt;/g,">").replace(/&amp;/g,"&").replace(/&nbsp;/g," ")
                                    .replace(/&#x[0-9a-fA-F]+;/gi,"").replace(/&#\d+;/g,"")
                                    .replace(/\s{2,}/g," ").trim() : ""
                                win.composeBody = "\n\n----- Forwarded Message -----\nFrom: "
                                    + (mail.current.from || "") + " <" + (mail.current.addr || "") + ">\n"
                                    + "Date: " + (mail.current.date || "") + "\n"
                                    + "Subject: " + (mail.current.subj || "") + "\n\n"
                                    + fPlain
                                win.composeStationery = "damask"
                                win.mailPaneView = "writing"
                            }
                        } }
                    }
            }
        }
        }

        // letterhead
        Rectangle {
            Layout.fillWidth: true; Layout.preferredHeight: headCol.implicitHeight + 36
            color: "transparent"
            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 2; color: pal.gilt2 }
            Column {
                id: headCol
                anchors.left: parent.left; anchors.right: parent.right
                anchors.top: parent.top; anchors.margins: 22; anchors.topMargin: 20
                spacing: 14
                Text { text: mail.current.subj ? mail.current.subj : ""
                       font.family: pal.display; font.bold: true; font.pixelSize: theme.fontLarge
                       color: pal.wineText2; width: parent.width * 0.92; wrapMode: Text.WordWrap }
                Row {
                    width: parent.width; spacing: 13
                    HBSealAva {
                        diameter: 48; fontPx: 18
                        label: initials(mail.current.from)
                        seedKey: mail.current.id ? mail.current.id : "x"
                        pal: readingDesk.pal
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 48 - dateT.implicitWidth - 26
                        Text { text: mail.current.from ? mail.current.from : ""
                               font.family: pal.serif; font.bold: true; font.pixelSize: theme.fontLarge; color: pal.ink }
                        Text { text: mail.current.addr ? mail.current.addr : ""
                               font.family: pal.fell; font.italic: true; font.pixelSize: theme.fontMedium; color: pal.inkSoft }
                        Text { text: "to " + (mail.current.to ? mail.current.to : "me")
                               font.family: pal.garamond; font.pixelSize: theme.fontSmall; color: pal.inkSoft }
                    }
                    Text { id: dateT; text: mail.current.date ? mail.current.date : ""
                           font.family: pal.fell; font.italic: true; font.pixelSize: theme.fontMedium
                           color: pal.inkSoft; anchors.verticalCenter: parent.verticalCenter }
                }

                // D-1 (HB-SEC-1): SPF/DKIM/DMARC trust badge — tapped to expand detail
                Row {
                    visible: (mail.current.trust || "") !== ""
                    spacing: 8
                    Rectangle {
                        id: trustBadge
                        height: 22; radius: 11
                        width: trustLbl.implicitWidth + 20
                        property color trustColor: {
                            var t = mail.current.trust || "";
                            if (t === "verified")   return pal.verd1;
                            if (t === "suspicious") return pal.rose;
                            if (t === "partial")    return pal.gilt0;
                            return pal.inkSoft;
                        }
                        color: Qt.rgba(trustColor.r, trustColor.g, trustColor.b, 0.12)
                        border.width: 1; border.color: trustColor
                        Text {
                            id: trustLbl
                            anchors.centerIn: parent
                            text: {
                                var t = mail.current.trust || "";
                                if (t === "verified")   return "✓ Sender verified";
                                if (t === "suspicious") return "⚠ Sender suspicious";
                                if (t === "partial")    return "~ Partial auth";
                                return "? Unverified";
                            }
                            font.family: pal.fell; font.pixelSize: Math.round(11 * (theme.fontMedium / 13.0))
                            color: trustBadge.trustColor
                        }
                        HoverHandler {}
                        TapHandler { onTapped: readingDesk.trustExpanded = !readingDesk.trustExpanded }
                    }
                    Text {
                        visible: readingDesk.trustExpanded
                        text: mail.current.trustDetail || ""
                        font.family: pal.fell; font.italic: true; font.pixelSize: Math.round(11 * (theme.fontMedium / 13.0))
                        color: pal.inkSoft; anchors.verticalCenter: parent.verticalCenter
                    }
                }

                // D-1: Vesper warning for suspicious senders (DMARC fail)
                Item {
                    visible: mail.current.trust === "suspicious"
                    width: parent.width; height: susRow.implicitHeight + 14
                    Rectangle {
                        anchors.fill: parent; radius: 6
                        color: Qt.rgba(pal.rose.r, pal.rose.g, pal.rose.b, 0.08)
                        border.width: 1; border.color: pal.rose
                    }
                    Text {
                        id: susRow
                        anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter; margins: 10 }
                        text: "This sender failed authentication. The address may be forged."
                        font.family: pal.fell; font.italic: true; font.pixelSize: Math.round(12 * (theme.fontMedium / 13.0))
                        color: pal.rose; wrapMode: Text.WordWrap
                    }
                }
            }
        }

        // Step D: attachments of the currently-open message — only takes space
        // when there are any.
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: mail.currentAttachments.length > 0 ? (attachCol.implicitHeight + 20) : 0
            visible: mail.currentAttachments.length > 0
            color: pal.paper1
            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: pal.gilt1 }
            Column {
                id: attachCol
                anchors.left: parent.left; anchors.right: parent.right; anchors.margins: 20
                anchors.verticalCenter: parent.verticalCenter
                spacing: 6
                Text { visible: readingDesk.attachStatus !== ""; text: readingDesk.attachStatus
                       font.family: pal.fell; font.italic: true; font.pixelSize: theme.fontSmall; color: pal.verd1 }
                Repeater {
                    model: mail.currentAttachments
                    delegate: Rectangle {
                        width: attachCol.width; height: 34; radius: 6
                        color: attHov.hovered ? pal.paper2 : "transparent"
                        Row { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                              anchors.leftMargin: 8; spacing: 10
                            Text { text: modelData.inline ? "🖼" : "📎"; font.pixelSize: theme.fontMedium
                                   anchors.verticalCenter: parent.verticalCenter }
                            Text { text: modelData.filename; font.family: pal.serif; font.pixelSize: theme.fontMedium
                                   color: pal.ink; anchors.verticalCenter: parent.verticalCenter }
                            Text { text: readingDesk.humanSize(modelData.size); font.family: pal.fell; font.italic: true
                                   font.pixelSize: theme.fontSmall; color: pal.inkSoft
                                   anchors.verticalCenter: parent.verticalCenter }
                        }
                        Text { text: "Save…"; font.family: pal.titles; font.pixelSize: theme.fontSmall
                               color: pal.gilt0; anchors.right: parent.right; anchors.rightMargin: 8
                               anchors.verticalCenter: parent.verticalCenter
                               TapHandler { onTapped: {
                                   readingDesk.savePartNumber = modelData.partNumber
                                   saveAttachmentDialog.selectedFile = "file:///"
                                       + Platform.StandardPaths.writableLocation(Platform.StandardPaths.DownloadLocation)
                                           .toString().replace(/^file:\/\//, "") + "/" + modelData.filename
                                   saveAttachmentDialog.open()
                               } }
                        }
                        HoverHandler { id: attHov }
                    }
                }
            }
        }

        // D-2 (HB-SEC-2/SEC-3): link safety warning banner — appears between
        // letterhead and body when a flagged URL or exec attachment is tapped.
        Rectangle {
            id: linkWarnBanner
            visible: readingDesk.pendingLinkStatus !== ""
            Layout.fillWidth: true
            Layout.preferredHeight: visible ? (linkWarnCol.implicitHeight + 20) : 0
            color: Qt.rgba(pal.rose.r, pal.rose.g, pal.rose.b, 0.93)
            Column {
                id: linkWarnCol
                anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter; margins: 16 }
                spacing: 8
                Text {
                    width: parent.width
                    text: {
                        var s = readingDesk.pendingLinkStatus;
                        if (s === "exec-attachment")
                            return "This attachment can execute code. It will be scanned when saved to Downloads.";
                        return "Vesper: " + s.replace("blocked:", "").replace(/_/g, " ") + " — this domain is on the block list.";
                    }
                    font.family: pal.fell; font.italic: true; font.pixelSize: Math.round(13 * (theme.fontMedium / 13.0)); color: pal.paper0
                    wrapMode: Text.WordWrap
                }
                Row {
                    spacing: 10
                    Rectangle {
                        height: 28; width: openLbl.implicitWidth + 20; radius: 14
                        color: Qt.rgba(1, 1, 1, 0.2); border.width: 1; border.color: pal.paper0
                        Text { id: openLbl; anchors.centerIn: parent; text: "Open Anyway"
                               font.family: pal.fell; font.pixelSize: Math.round(12 * (theme.fontMedium / 13.0)); color: pal.paper0 }
                        TapHandler { onTapped: {
                            launcher.systemCommand("ncde-chromium " + readingDesk.pendingLinkUrl);
                            readingDesk.pendingLinkUrl = ""; readingDesk.pendingLinkStatus = "";
                        } }
                    }
                    Rectangle {
                        height: 28; width: cancelLbl.implicitWidth + 20; radius: 14
                        color: "transparent"; border.width: 1; border.color: pal.paper0
                        Text { id: cancelLbl; anchors.centerIn: parent; text: "Cancel"
                               font.family: pal.fell; font.pixelSize: Math.round(12 * (theme.fontMedium / 13.0)); color: pal.paper0 }
                        TapHandler { onTapped: {
                            readingDesk.pendingLinkUrl = ""; readingDesk.pendingLinkStatus = "";
                        } }
                    }
                }
            }
        }

        // body
        Flickable {
            id: rdFlickable
            Layout.fillWidth: true; Layout.fillHeight: true
            clip: true; contentWidth: width
            contentHeight: rdBody.implicitHeight
            Text {
                id: rdBody
                topPadding: 24; leftPadding: 30; rightPadding: 30; bottomPadding: 30
                text: richBody(mail.current.body ? mail.current.body : "")
                textFormat: Text.RichText
                font.family: pal.garamond; font.pixelSize: theme.fontLarge; color: pal.ink
                wrapMode: Text.WordWrap; lineHeight: 1.35; width: parent.width
                // D-2 (HB-SEC-2/SEC-3): intercept all link taps before passing to Chromium.
                // Executable-extension links get an attachment warning.
                // Blocked domains get a Vesper link-safety banner.
                onLinkActivated: function(url) {
                    var lower = url.toLowerCase();
                    var execExts = [".sh",".py",".appimage",".bin",".deb",".rpm",".run",".elf",".jar",".exe",".msi",".bat"];
                    var isExec = execExts.some(function(e){ return lower.endsWith(e); });
                    if (isExec) {
                        readingDesk.pendingLinkUrl    = url;
                        readingDesk.pendingLinkStatus = "exec-attachment";
                        return;
                    }
                    var result = mail.checkLink(url);
                    if (result.startsWith("blocked")) {
                        readingDesk.pendingLinkUrl    = url;
                        readingDesk.pendingLinkStatus = result;
                        return;
                    }
                    launcher.systemCommand("ncde-chromium " + url);
                }
            }
        }
    }
}
