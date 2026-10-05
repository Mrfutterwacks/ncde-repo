// MagpieTalkerManual.qml — operating manual for Magpie Talker.
// Floats above the app as a frameless parchment window.
// Voice: The Raven — theatrical, poetic, absolutely delighted by messages.
import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window {
    id: win

    flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint
           | Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus
    color: "transparent"
    width:  Math.min(640, Screen.width  - 120)
    height: Math.min(740, Screen.height - 80)
    x: Math.round((Screen.width  - width)  / 2)
    y: Math.round((Screen.height - height) / 2)
    visible: false

    NCDEKit { id: k }

    // k.ink is already dark/light-adaptive; the old k.gilt0 dark-mode branch
    // was a hardcoded, non-adaptive umber that read as too-dark-on-dark-parchment.
    readonly property color parchInk: k.ink

    // Cerulean ramp — matches MagpieTalker.qml
    QtObject {
        id: crd
        readonly property color cer1: k.dark ? Qt.darker(k.cer, 3.0)  : k.cer
        readonly property color cer2: k.dark ? Qt.darker(k.cer, 2.0)  : k.cer
        readonly property color cer3: k.dark ? k.cer                   : k.cer
        readonly property color cer4: k.dark ? Qt.lighter(k.cer, 1.3) : k.cer
        readonly property color cer5: k.dark ? Qt.lighter(k.cer, 1.7) : k.cer
    }

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

                // ── frontispiece ─────────────────────────────────────────────
                Column {
                    width: parent.width; spacing: 0
                    topPadding: 26
                    leftPadding: 40; rightPadding: 40

                    // Raven emblem in dark cerulean circle
                    Item {
                        width: 66; height: 66
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            anchors.fill: parent; radius: width / 2
                            gradient: Gradient {
                                GradientStop { position: 0.0;  color: crd.cer2 }
                                GradientStop { position: 0.65; color: crd.cer1 }
                                GradientStop { position: 1.0;  color: Qt.darker(crd.cer1, 1.3) }
                            }
                            border.color: k.gilt2; border.width: 2
                            Rectangle {
                                anchors.centerIn: parent
                                width: parent.width + 10
                                height: parent.height + 10
                                radius: width / 2; color: "transparent"
                                border.color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.28)
                                border.width: 4; z: -1
                            }
                        }

                        // Raven silhouette (same drawing as Magpie component, gilt color)
                        Canvas {
                            anchors.fill: parent
                            renderStrategy: Canvas.Cooperative
                            onPaint: {
                                var ctx = getContext("2d"); ctx.reset()
                                var s = Math.min(width, height) / 100.0; ctx.scale(s, s)
                                ctx.fillStyle = k.gilt3
                                ctx.beginPath(); ctx.arc(62,20,10,0,2*Math.PI); ctx.fill()
                                ctx.beginPath(); ctx.moveTo(58,28); ctx.bezierCurveTo(64,40,66,56,56,70)
                                ctx.bezierCurveTo(70,64,78,48,74,30); ctx.bezierCurveTo(70,24,64,22,58,28); ctx.closePath(); ctx.fill()
                                ctx.beginPath(); ctx.moveTo(56,70); ctx.bezierCurveTo(48,80,34,88,18,92)
                                ctx.bezierCurveTo(30,80,40,64,50,54); ctx.bezierCurveTo(54,58,56,64,56,70); ctx.closePath(); ctx.fill()
                                ctx.beginPath(); ctx.moveTo(70,18); ctx.lineTo(84,13); ctx.lineTo(71,23); ctx.closePath(); ctx.fill()
                                ctx.fillStyle = crd.cer4; ctx.globalAlpha = 0.85
                                ctx.beginPath(); ctx.moveTo(58,36); ctx.bezierCurveTo(52,46,52,58,52,58)
                                ctx.bezierCurveTo(60,54,64,44,62,36); ctx.closePath(); ctx.fill(); ctx.globalAlpha = 1
                                ctx.fillStyle = k.gilt5; ctx.beginPath(); ctx.arc(65,18,1.6,0,2*Math.PI); ctx.fill()
                            }
                        }
                    }

                    Item { width: 1; height: 14 }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "On the Wire"
                        font.family: k.display; font.bold: true
                        font.pixelSize: theme.scale(30); color: crd.cer3
                        font.letterSpacing: 1
                    }

                    Item { width: 1; height: 4 }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "The Raven carries word across the darkness"
                        font.family: k.fell; font.italic: true
                        font.pixelSize: theme.scale(13); color: win.parchInk; opacity: 0.6
                    }

                    Item { width: 1; height: 18 }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter; spacing: 12
                        Rectangle {
                            width: 80; height: 1; anchors.verticalCenter: parent.verticalCenter
                            gradient: Gradient { orientation: Gradient.Horizontal
                                GradientStop { position: 0.0; color: "transparent" }
                                GradientStop { position: 1.0; color: Qt.rgba(k.gilt3.r,k.gilt3.g,k.gilt3.b,0.85) }
                            }
                        }
                        Rectangle { width: 8; height: 8; radius: 4
                            anchors.verticalCenter: parent.verticalCenter; color: k.gilt3 }
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
                        { kicker: "QUOTH THE RAVEN",
                          h:     "Oh, I have been waiting for you",
                          lead:  "AH! There you are! Come in, come in — do not mind the feathers, I shed terribly this time of year. I am The Raven, keeper of this wire, and I have EXCELLENT news: you can send messages to anyone on your network this very instant — and, if you know their screen name, to anyone else in the world besides.",
                          p:     "Magpie Talker is a <b>direct, private messenger</b>. No servers to sign up for, no clouds, no one reading your words on their way across. On your own network, the people nearby simply appear in the left panel — click one, say hello, I handle everything else. Further afield, I keep a second frequency open — <b>the World Band</b> — so you may reach anyone whose screen name you know, wherever in the world they happen to be. Either way: you type something, I carry it — swift as wings on a midnight wind — and it arrives. It is really rather marvellous when you think about it, and I think about it constantly." },

                        { rule: true,
                          kicker: "YOUR IDENTITY",
                          h:     "A name! A splendid, unique name!",
                          p:     "When you first arrived, I asked you to choose a <b>screen name</b>. This is who you are on the wire — two to twenty-four characters, letters and numbers and the occasional underscore. It is yours, and it is also your <b>callsign</b> on the World Band below — the thing another Raven-keeper types in to find you from anywhere. <b>Your display name</b> is what your friends actually see — you may make it as grand or as understated as you wish.<br><br>I also asked for a <b>password</b>, which I keep in your system keyring under lock and key. Your NCDE session unlocks it silently when you log in, so you will never need to type it again. If the keyring is unavailable for some reason, I will ask you once, politely, and then get on with things." },

                        { rule: true,
                          kicker: "THE WIRE — YOUR LOCAL NETWORK",
                          h:     "They appear! Like magic — actually, exactly like magic",
                          p:     "Every few seconds, Magpie Talker announces your presence to the local network. All the other Magpie Talkers on your network do the same. This is how we find each other nearby — <b>no setup, no server, no configuration</b>. One moment the sidebar is empty; then a name appears, then another. This is the wire coming alive.<br><br>If someone's machine goes quiet — they close the app, the network hiccups, they walk away — their name fades from the list within about twenty seconds. They have left the wire. Do not take it personally. They will return. <b>Your message history stays put</b> either way, safely stored on your machine." },

                        { rule: true,
                          kicker: "THE WORLD BAND — BEYOND THE WIRE",
                          h:     "Anyone, anywhere, if you know their name",
                          p:     "The local wire is delightful, but what of a friend three cities away? For that I keep a second frequency open — the <b>World Band</b>, serverless, reaching anywhere in the world without any company's server standing in the middle.<br><br>Tap <b>+ Add contact</b>, type their exact <b>screen name</b>, and press <b>Enter</b>. I will call out across the World Band and listen for an answer — you will see <i>\"Calling out on the world band…\"</i> while I do. If they are reachable, they appear in the results just like a wire neighbor; tap <b>Add</b> and you are connected. If no one answers, I will tell you plainly, honestly, without fuss — try again later, they may simply be away from any network just now.<br><br>Messages I carry this way are <b>end-to-end encrypted</b>, so only the two of you can ever read them, and I hold them for a little while if they have stepped away recently — but I am a raven, not a vault. This is text only for now, and best for someone who has been near a network recently, not a mailbox that holds forever." },

                        { rule: true,
                          kicker: "CONVERSATIONS",
                          h:     "Direct messages, and channels — now with a proper chorus",
                          p:     "The sidebar has two kinds of conversations. <b>Direct messages</b> (the top section) are private — just you and one other person, whether they are on your own network or answered from the World Band. Click a name and begin. Your history with that person loads immediately, right where you left it. Type in the composer at the bottom and press <b>Enter</b>, tap the paperclip to attach a file, or react to any message with an emoji; hover over it to find the smiley-face button.<br><br><b>Channels</b> (the lower section) now carry real weight — a message typed into a channel reaches everyone currently on the wire with you, over whichever path finds them. One honest caveat: a channel is <i>whoever is here right now</i>, not a room with a guest list — there is no persistent membership yet, so someone who joins the wire later will not see what was said before they arrived." },

                        { rule: true,
                          kicker: "YOUR PRESENCE",
                          h:     "Tell the wire how you are feeling today",
                          p:     "The row at the top of the sidebar is <b>you</b>. Your avatar, your name, the glowing dot that tells everyone your status. Tap it to cycle through <b>Online</b> (green — I am here, talk to me), <b>Away</b> (amber — I am here but wandering), <b>Busy</b> (red — I am here but for heaven's sake do not interrupt), and <b>Do Not Disturb</b> (which suppresses the notification sounds — a blessed setting).<br><br>You can also set a short <b>status message</b> — the text that appears beneath your name. Use it however you like. \"In a meeting.\" \"Writing a poem.\" \"Being followed by a raven.\" The choice is yours." },

                        { rule: true,
                          kicker: "NEARBY",
                          h:     "Who else is out there, roughly speaking",
                          p:     "Tap the little pin beside <b>+ Add contact</b> and I will offer you a quieter frequency: <b>Nearby</b>. It is off until you say otherwise — flip it on and I share only your rough neighborhood, never a precise fix, to anyone else who has done the same. Tap <b>Browse nearby</b> and I will listen a few moments for fellow Ravens in the area; each one you find still needs a proper <b>Add</b> before we speak, same as anywhere else on the World Band. Turn it off any time with a tap — I forget your neighborhood the moment you ask." },

                        { rule: true,
                          kicker: "FOREIGN CORRESPONDENTS",
                          h:     "Visitors from the other side of the wire",
                          p:     "If someone on your network is using <b>Pidgin</b>, <b>Kopete</b>, <b>macOS Messages</b>, or any other Bonjour-compatible messenger, they will appear in your sidebar with a small <b>❧ Bonjour</b> label beneath their name. I find these visitors rather charming — they arrive from their own messenger and have no idea they are talking to a Raven.<br><br>You can message them, nudge them, and carry on just as with any other contact. The only difference is what lives on the other end of the wire. From your perspective: the conversation is identical. From theirs: a mysterious message appeared from somewhere called Magpie Talker. Delightful." },

                        { rule: true,
                          kicker: "FACEBOOK MESSENGER",
                          h:     "Your Facebook friends, on my wire",
                          p:     "At the top of the sidebar sits <b>Messenger</b>. Tap it and the whole of Facebook Messenger opens right here, dressed in my own ink and paper: every chat, your full history, photos, voice and video calls. The first time, tap <b>Sign in to Messenger</b> and log in to Facebook; I keep the key, so you will not be asked again. Nothing extra to download.<br><br>Those conversations live on <b>Facebook</b>, not in my archive, so they are there on your phone too. While you are elsewhere on the wire, new Messenger letters pop up in the corner of your desktop, and the little number beside <b>Messenger</b> counts what is still unread. <b>Chats</b> takes you back to the conversation list, <b>Back</b> goes back a step, and <b>Refresh</b> reloads. Links your friends send open in your browser. To go back to Magpie's own conversations, tap any channel or name in the sidebar." },

                        { rule: true,
                          kicker: "THE ARCHIVE",
                          h:     "I remember everything. Everything.",
                          p:     "Every message sent and received is kept in your personal history at <b>~/.config/ncde/magpie/history/</b> — one file per conversation, safe on your own machine. When you open a conversation, I load its history at once.<br><br>To find something specific, use the <b>search bar</b> at the top of the message thread. Type a word or phrase and I will scan the current conversation immediately. I have an exceptional memory for these things. I would say I never forget anything, but that starts to sound ominous, and I am told I am <b>not</b> supposed to be scary." },
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
                            font.letterSpacing: 3; color: crd.cer3
                        }

                        Text {
                            visible: !!modelData.h
                            height: visible ? implicitHeight + 5 : 0
                            width: parent.width - 84
                            text: modelData.h || ""
                            font.family: k.display; font.bold: true
                            font.pixelSize: theme.scale(21); color: k.ink
                            wrapMode: Text.WordWrap
                        }

                        Text {
                            visible: !!modelData.lead
                            height: visible ? implicitHeight + 8 : 0
                            width: parent.width - 84
                            text: modelData.lead || ""
                            font.family: k.fell; font.italic: true
                            font.pixelSize: theme.scale(16); color: win.parchInk
                            wrapMode: Text.WordWrap; lineHeight: 1.45
                        }

                        Text {
                            visible: !!modelData.p
                            height: visible ? implicitHeight + 10 : 0
                            width: parent.width - 84
                            text: modelData.p || ""
                            font.family: k.gar; font.pixelSize: theme.scale(15)
                            color: win.parchInk
                            textFormat: Text.RichText; wrapMode: Text.WordWrap
                            lineHeight: 1.55
                        }

                        Rectangle {
                            visible: !!modelData.rule
                            height: visible ? 1 : 0
                            width: parent.width - 84
                            gradient: Gradient { orientation: Gradient.Horizontal
                                GradientStop { position: 0.0;  color: "transparent" }
                                GradientStop { position: 0.18; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.45) }
                                GradientStop { position: 0.82; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.45) }
                                GradientStop { position: 1.0;  color: "transparent" }
                            }
                        }
                    }
                }

                // ── sign-off ─────────────────────────────────────────────────
                Text {
                    width: parent.width - 84
                    leftPadding: 44
                    horizontalAlignment: Text.AlignHCenter
                    text: "And the Raven, never flitting, still is sitting — right here on the wire, waiting to carry your next message. Tap the × and go talk to someone. Nevermore shall you be unreachable.  — The Raven"
                    font.family: k.fell; font.italic: true
                    font.pixelSize: theme.scale(14); color: crd.cer3
                    topPadding: 16; bottomPadding: 28
                    wrapMode: Text.WordWrap
                }
            }
        }

        // ── close jewel — declared after Flickable so it sits on top ────────
        Item {
            width: 28; height: 28
            anchors.top: parent.top; anchors.right: parent.right
            anchors.topMargin: 14; anchors.rightMargin: 16
            Canvas {
                anchors.fill: parent; renderStrategy: Canvas.Cooperative
                property bool hov: closeHov.hovered
                onHovChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d"); ctx.clearRect(0,0,width,height)
                    var cx = width/2, cy = cx, r = cx - 2
                    ctx.beginPath()
                    ctx.moveTo(cx, cy-r); ctx.lineTo(cx+r, cy); ctx.lineTo(cx, cy+r); ctx.lineTo(cx-r, cy)
                    ctx.closePath()
                    ctx.fillStyle = hov ? crd.cer2 : crd.cer1; ctx.fill()
                    ctx.strokeStyle = hov ? k.gilt3 : k.gilt1; ctx.lineWidth = 1.5; ctx.stroke()
                    var d = r * 0.38; ctx.strokeStyle = k.gilt5; ctx.lineWidth = 1.8; ctx.lineCap = "round"
                    ctx.beginPath(); ctx.moveTo(cx-d, cy-d); ctx.lineTo(cx+d, cy+d)
                    ctx.moveTo(cx+d, cy-d); ctx.lineTo(cx-d, cy+d); ctx.stroke()
                }
            }
            HoverHandler { id: closeHov }
            TapHandler { onTapped: win.hide() }
        }
    }
}
