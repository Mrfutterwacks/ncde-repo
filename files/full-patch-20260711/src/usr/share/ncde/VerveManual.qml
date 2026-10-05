// VerveManual.qml — operating manual for Verve Text.
// Window popup, opened from the ? button in the Verve title bar.
// Voice: Veronica — valley girl, 80s sleepover energy. Warm, fast, excitable.
import QtQuick
import QtQuick.Controls

Window {
    id: win

    flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint
           | Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus
    color: "transparent"
    width:  Math.min(660, Screen.width  - 120)
    height: Math.min(760, Screen.height - 80)
    x: Math.round((Screen.width  - width)  / 2)
    y: Math.round((Screen.height - height) / 2)
    visible: false

    NCDEKit { id: k }
    // k.ink is already dark/light-adaptive; the old k.gilt0 dark-mode branch
    // was a hardcoded, non-adaptive umber that read as too-dark-on-dark-parchment.
    readonly property color parchInk: k.ink

    function show() { visible = true; raise() }
    function hide() { visible = false }

    Item {
        anchors.fill: parent

        NCDEParchmentSurface { anchors.fill: parent; cornerRadius: 16 }

        Flickable {
            anchors.fill: parent
            anchors.topMargin: 12; anchors.bottomMargin: 12
            contentHeight: page.implicitHeight; clip: true
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: page
                width: parent.width
                spacing: 0

                // ── frontispiece ──────────────────────────────────────────────
                Column {
                    width: parent.width; spacing: 0
                    topPadding: 26
                    leftPadding: 40; rightPadding: 40

                    // nib emblem in gold circle
                    Item {
                        width: 62; height: 62
                        anchors.horizontalCenter: parent.horizontalCenter
                        Rectangle {
                            anchors.fill: parent; radius: width / 2
                            gradient: Gradient {
                                GradientStop { position: 0.0;  color: k.gilt4 }
                                GradientStop { position: 0.65; color: k.gilt2 }
                                GradientStop { position: 1.0;  color: k.gilt0 }
                            }
                            border.color: k.gilt0; border.width: 2
                            Rectangle {
                                anchors.centerIn: parent
                                width: parent.width + 10; height: parent.height + 10
                                radius: width / 2; color: "transparent"
                                border.color: Qt.rgba(k.gilt4.r, k.gilt4.g, k.gilt4.b, 0.28)
                                border.width: 4; z: -1
                            }
                        }
                        Canvas {
                            anchors.fill: parent
                            renderStrategy: Canvas.Cooperative
                            onPaint: {
                                var ctx = getContext("2d"); ctx.reset()
                                var s = Math.min(width, height) / 100.0; ctx.scale(s, s)
                                ctx.fillStyle = Qt.rgba(k.wine1.r, k.wine1.g, k.wine1.b, 0.90)
                                ctx.beginPath()
                                ctx.moveTo(50,6); ctx.bezierCurveTo(58,30,70,44,70,64)
                                ctx.bezierCurveTo(70,80,60,92,50,92)
                                ctx.bezierCurveTo(40,92,30,80,30,64)
                                ctx.bezierCurveTo(30,44,42,30,50,6); ctx.closePath(); ctx.fill()
                                ctx.strokeStyle = Qt.rgba(k.gilt0.r, k.gilt0.g, k.gilt0.b, 0.5)
                                ctx.globalAlpha = 0.5; ctx.lineWidth = 3
                                ctx.beginPath(); ctx.moveTo(50,30); ctx.lineTo(50,78); ctx.stroke()
                                ctx.globalAlpha = 0.55
                                ctx.beginPath(); ctx.arc(50,60,5,0,2*Math.PI)
                                ctx.fillStyle = Qt.rgba(k.gilt0.r, k.gilt0.g, k.gilt0.b, 0.6); ctx.fill()
                            }
                        }
                    }

                    Item { width: 1; height: 14 }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Verve Text"
                        font.family: k.display; font.bold: true
                        font.pixelSize: theme.scale(28); color: k.ink; font.letterSpacing: 1
                    }
                    Item { width: 1; height: 4 }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Veronica's writing desk"
                        font.family: k.fell; font.italic: true
                        font.pixelSize: theme.scale(13); color: win.parchInk; opacity: 0.6
                    }
                    Item { width: 1; height: 16 }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter; spacing: 12
                        Rectangle {
                            width: 80; height: 1; anchors.verticalCenter: parent.verticalCenter
                            gradient: Gradient { orientation: Gradient.Horizontal
                                GradientStop { position: 0.0; color: "transparent" }
                                GradientStop { position: 1.0; color: Qt.rgba(k.gilt3.r,k.gilt3.g,k.gilt3.b,0.85) }
                            }
                        }
                        Rectangle {
                            width: 8; height: 8; radius: 4
                            anchors.verticalCenter: parent.verticalCenter; color: k.gilt3
                        }
                        Rectangle {
                            width: 80; height: 1; anchors.verticalCenter: parent.verticalCenter
                            gradient: Gradient { orientation: Gradient.Horizontal
                                GradientStop { position: 0.0; color: Qt.rgba(k.gilt3.r,k.gilt3.g,k.gilt3.b,0.85) }
                                GradientStop { position: 1.0; color: "transparent" }
                            }
                        }
                    }
                    Item { width: 1; height: 8 }
                }

                // ── body sections ─────────────────────────────────────────────
                Repeater {
                    model: [
                        { kicker: "OKAY HI",
                          h:     "Welcome to the writing desk",
                          lead:  "Oh my gosh, you opened Verve! Okay so I'm Veronica and I am so excited to show you around. This is L'Écritoire — the writing desk — and it is like, genuinely the prettiest place to write anything.",
                          p:     "You get a real paper sheet, ruled lines, a red margin — the whole thing. Just start typing and the words go. That's literally it. But there's a lot more here when you want it, so let me show you." },

                        { rule: true,
                          kicker: "THE PAPER SHEET",
                          h:     "Your actual writing surface",
                          p:     "The big white sheet in the middle? That's where you write. It has faint blue ruled lines — super subtle, just enough to keep things feeling like real paper — and a little red margin line on the left. Very classic notebook. The font is EB Garamond which is like, genuinely gorgeous for writing. Everything is centered on the sheet so nothing feels cramped." },

                        { rule: true,
                          kicker: "NEW · OPEN · SAVE",
                          h:     "The buttons across the top",
                          p:     "<b>New</b> starts a fresh blank document. If you have unsaved changes it will ask you first — it's not going to just delete your stuff, okay, I would never. <b>Open</b> toggles the file sidebar on the left where all your documents live. <b>Save</b> — the blue one — saves your work right now. Hit it a lot. <b>Save As</b> lets you give a document a new name and save it to your Documents folder. The title bar shows a little red dot when you have unsaved changes. Watch for that." },

                        { rule: true,
                          kicker: "THE FILE SIDEBAR",
                          h:     "Your Documents, all in one place",
                          p:     "Tap <b>Open</b> in the toolbar and the sidebar slides out on the left. It shows everything in your Documents folder — tap any file to open it. Below that is <b>Recent</b>, which remembers the last few files you worked on. Super handy. Tap Open again to tuck it away when you want more writing room." },

                        { rule: true,
                          kicker: "FIND & REPLACE",
                          h:     "For when you need to find a thing",
                          p:     "Tap <b>Find</b> in the toolbar — or press <b>Ctrl+F</b> — and a little panel floats in the top right. Type what you're looking for and tap <b>Find Next</b> to step through every match. Add something in the Replace field and tap <b>Replace</b> to swap just the one you're on, or <b>All</b> to replace every single one at once. Press Escape to close it when you're done." },

                        { rule: true,
                          kicker: "ZOOM & WORD WRAP",
                          h:     "Make it comfortable for you",
                          p:     "The <b>−</b> and <b>+</b> buttons zoom the text from 60% all the way up to 220% — so if you want the words big, make them big. No one is judging. <b>Ctrl+−</b> and <b>Ctrl++</b> do the same thing from the keyboard. The <b>Wrap</b> toggle controls whether long lines wrap inside the sheet or scroll sideways. Wrap on is usually what you want for writing; wrap off is great for code or lists." },

                        { rule: true,
                          kicker: "AUTOSAVE & RECOVERY",
                          h:     "Your words are safe, I promise",
                          p:     "Every four seconds while you're writing, Verve quietly saves a draft in the background — so if something crashes, your work is not gone. Next time you open Verve it will find that draft and recover it automatically. The status bar at the bottom shows <b>Saved</b> or <b>Unsaved changes</b> so you always know where you stand. And the status bar also shows your line, column, word count, and character count — great for when you have a word limit." },

                        { rule: true,
                          kicker: "KEYBOARD SHORTCUTS",
                          h:     "Quick reference",
                          p:     "<b>Ctrl+S</b> — Save  ·  <b>Ctrl+Shift+S</b> — Save As  ·  <b>Ctrl+N</b> — New  ·  <b>Ctrl+O</b> — Toggle sidebar  ·  <b>Ctrl+F</b> — Find  ·  <b>Ctrl++</b> — Zoom in  ·  <b>Ctrl+−</b> — Zoom out  ·  <b>Escape</b> — Close Find or Save As" },
                    ]

                    Column {
                        width: page.width
                        leftPadding: 44; rightPadding: 40
                        spacing: 0

                        Item { width: 1; height: modelData.rule ? 14 : (modelData.kicker ? 12 : 0) }

                        Text {
                            visible: !!modelData.kicker
                            height: visible ? implicitHeight + 3 : 0
                            width: parent.width - 84
                            text: modelData.kicker || ""
                            font.family: k.titles; font.pixelSize: theme.scale(10)
                            font.letterSpacing: 3; color: k.gilt1
                        }
                        Text {
                            visible: !!modelData.h
                            height: visible ? implicitHeight + 5 : 0
                            width: parent.width - 84
                            text: modelData.h || ""
                            font.family: k.display; font.bold: true
                            font.pixelSize: theme.scale(19); color: k.ink
                            wrapMode: Text.WordWrap
                        }
                        Text {
                            visible: !!modelData.lead
                            height: visible ? implicitHeight + 8 : 0
                            width: parent.width - 84
                            text: modelData.lead || ""
                            font.family: k.fell; font.italic: true
                            font.pixelSize: theme.scale(15); color: win.parchInk
                            wrapMode: Text.WordWrap; lineHeight: 1.45
                        }
                        Text {
                            visible: !!modelData.p
                            height: visible ? implicitHeight + 10 : 0
                            width: parent.width - 84
                            text: modelData.p || ""
                            font.family: k.gar; font.pixelSize: theme.scale(14)
                            color: win.parchInk
                            textFormat: Text.RichText; wrapMode: Text.WordWrap
                            lineHeight: 1.55
                        }
                        Rectangle {
                            visible: !!modelData.rule
                            height: visible ? 1 : 0; width: parent.width - 84
                            gradient: Gradient { orientation: Gradient.Horizontal
                                GradientStop { position: 0.0;  color: "transparent" }
                                GradientStop { position: 0.18; color: Qt.rgba(k.gilt3.r,k.gilt3.g,k.gilt3.b,0.45) }
                                GradientStop { position: 0.82; color: Qt.rgba(k.gilt3.r,k.gilt3.g,k.gilt3.b,0.45) }
                                GradientStop { position: 1.0;  color: "transparent" }
                            }
                        }
                    }
                }

                // ── sign-off ──────────────────────────────────────────────────
                Text {
                    width: parent.width - 84
                    leftPadding: 44
                    horizontalAlignment: Text.AlignHCenter
                    text: "Okay! Go write something amazing. I totally believe in you.  — Veronica"
                    font.family: k.fell; font.italic: true
                    font.pixelSize: theme.scale(14); color: k.ink
                    topPadding: 16; bottomPadding: 28
                    wrapMode: Text.WordWrap
                }
            }
        }

        // ── close jewel ──────────────────────────────────────────────────────
        Item {
            width: 28; height: 28
            anchors.top: parent.top; anchors.right: parent.right
            anchors.topMargin: 14; anchors.rightMargin: 16
            Canvas {
                anchors.fill: parent
                renderStrategy: Canvas.Cooperative
                property bool hov: closeHov.hovered
                onHovChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d"); ctx.clearRect(0,0,width,height)
                    var cx = width/2, cy = width/2, r = cx - 2
                    ctx.beginPath()
                    ctx.moveTo(cx,cy-r); ctx.lineTo(cx+r,cy); ctx.lineTo(cx,cy+r); ctx.lineTo(cx-r,cy)
                    ctx.closePath()
                    ctx.fillStyle = hov ? k.wine4 : k.wine2; ctx.fill()
                    ctx.strokeStyle = hov ? k.gilt4 : k.gilt3; ctx.lineWidth = 1.5; ctx.stroke()
                    var d = r * 0.40; ctx.strokeStyle = k.surface; ctx.lineWidth = 1.8; ctx.lineCap = "round"
                    ctx.beginPath(); ctx.moveTo(cx-d,cy-d); ctx.lineTo(cx+d,cy+d)
                    ctx.moveTo(cx+d,cy-d); ctx.lineTo(cx-d,cy+d); ctx.stroke()
                }
            }
            HoverHandler { id: closeHov }
            TapHandler { onTapped: win.hide() }
        }
    }
}
