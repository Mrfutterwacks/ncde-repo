// LeapFrogManual.qml — operating manual for Leap Frog Ledger.
// Loaded by the aboutPanel Loader in LeapFrogLedger.qml.
// Same book layout as GliaDocPopup: frontispiece · kicker/heading/lead/body/rule/sign-off.
// Voice: Plato the frog, showing you around his home.
import QtQuick
import QtQuick.Controls
import "cal-art.js" as Art

Item {
    NCDEKit { id: k }

    // The dialog behind this Loader (LeapFrogLedger.qml's aboutPanel) uses the real
    // adaptive k.surface/k.surface2 background, which DOES go dark in dark mode — the
    // old "always ivory" assumption here was false and produced dark-on-dark text
    // (2026-07-04 fix). k.ink is already dark/light-adaptive; use it directly.
    readonly property color parchInk: k.ink

    // ── scrollable body ──────────────────────────────────────────────────────
    Flickable {
        anchors.fill: parent
        contentHeight: page.implicitHeight
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: NCDEScrollBar {}

        Column {
            id: page
            width: parent.width
            spacing: 0

            // ── frontispiece ─────────────────────────────────────────────────
            Column {
                width: parent.width
                spacing: 0
                leftPadding: 40; rightPadding: 40
                topPadding: 28

                // Plato emblem — frog in a gold circle
                Item {
                    width: 68; height: 68
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
                            width: parent.width + 10
                            height: parent.height + 10
                            radius: (parent.width + 10) / 2
                            color: "transparent"
                            border.color: Qt.rgba(k.gilt4.r, k.gilt4.g, k.gilt4.b, 0.28)
                            border.width: 4; z: -1
                        }
                    }
                    Canvas {
                        anchors.fill: parent
                        renderStrategy: Canvas.Cooperative
                        onPaint: {
                            var ctx = getContext("2d")
                            var cx = width / 2
                            Art.CalArt.paintEmblem(ctx, cx, cx * 0.88, cx * 0.62)
                        }
                    }
                }

                Item { width: 1; height: 14 }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Sit by the Pond"
                    font.family: k.display; font.bold: true
                    font.pixelSize: theme.scale(30); color: k.ink
                    font.letterSpacing: 1
                }

                Item { width: 1; height: 6 }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Plato shows you around the pond"
                    font.family: k.fell; font.italic: true
                    font.pixelSize: theme.scale(14); color: parchInk; opacity: 0.6
                }

                Item { width: 1; height: 18 }

                // ornament: line · dot · line
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 12
                    Rectangle {
                        width: 90; height: 1
                        anchors.verticalCenter: parent.verticalCenter
                        gradient: Gradient { orientation: Gradient.Horizontal
                            GradientStop { position: 0.0; color: "transparent" }
                            GradientStop { position: 1.0; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.85) }
                        }
                    }
                    Rectangle {
                        width: 9; height: 9; radius: 5
                        anchors.verticalCenter: parent.verticalCenter; color: k.gilt3
                        Rectangle {
                            anchors.centerIn: parent
                            width: parent.width + 6; height: parent.height + 6
                            radius: (parent.width + 6) / 2
                            color: "transparent"
                            border.color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.3)
                            border.width: 1
                        }
                    }
                    Rectangle {
                        width: 90; height: 1
                        anchors.verticalCenter: parent.verticalCenter
                        gradient: Gradient { orientation: Gradient.Horizontal
                            GradientStop { position: 0.0; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.85) }
                            GradientStop { position: 1.0; color: "transparent" }
                        }
                    }
                }

                Item { width: 1; height: 8 }
            }

            // ── body sections ────────────────────────────────────────────────
            Repeater {
                model: [
                    { kicker: "WELCOME TO THE POND",
                      h:     "Five ways to look at your time",
                      lead:  "Come in, come in! Sit anywhere — not there, that is my favourite log. Over here, yes. Now. I have devised FIVE ways to look at your days. Five! I have toured every calendar on the riverbank, and not one of them has thought of this.",
                      p:     "<b>Month</b> gives you the whole pond at a glance — every day in a magnificent grid, today glowing gold, each cell showing its moon phase and up to three appointments in their proper gem colours. <b>Week</b> arrays your seven days side by side, hour by hour, so you may see the week as it truly is. <b>Day</b> descends upon a single day from morning to midnight — the full picture, nothing omitted. <b>Year</b> draws back and shows all twelve months beneath their zodiac signs; tap any one and you leap straight in. And <b>Agenda</b> — my personal favourite on busy mornings — lists what is coming in plain order. Switch between them at any time using the rail on the left. It is quite the system." },
                    { rule: true,
                      kicker: "THE TOP OF THE PAGE",
                      h:     "The seasons are mine",
                      p:     "The illustration at the top of the page — that is my work, and I change it with every season. Spring blossoms, Summer dragonflies, Autumn embers, Winter frost. I repaint the whole scene each time. The pond looks very different in March than it does in October, and I have always felt a calendar ought to reflect that. The <b>‹</b> and <b>›</b> arrows step you backward and forward one period at a time. Lost your place in the grand sweep of things? <b>TODAY</b> returns you to the present at once. <b>✛ NEW</b> opens a fresh appointment — I recommend using it often." },
                    { rule: true,
                      kicker: "MAKING AN APPOINTMENT",
                      h:     "Give it a proper name — I insist",
                      p:     "When something important approaches — a meeting, a birthday, a journey across town, a luncheon that must not be missed — tap <b>✛ NEW</b>, or double-tap the day in Month view, or tap any hour in Day or Week view. The appointment form opens. Now: give the thing a <b>title</b>. A name is the very least it deserves. Then set the <b>start</b> and <b>end time</b>. You may add a <b>location</b>, some <b>notes</b>, a <b>colour category</b> from my celebrated six, whether it <b>repeats</b>, and how far ahead you require a <b>reminder</b>. For whole-day occasions, tap <b>All Day</b>. If you have made an error — and we all do — simply tap the appointment wherever it appears and correct it. I do not judge." },
                    { rule: true,
                      kicker: "THE SIX COLOURS",
                      h:     "A gem for every occasion — six of them",
                      p:     "I have devised a colour system of which I am enormously proud. Every appointment wears a gem colour as a stripe down its side — you can read the shape of an entire week before you have deciphered a single word. <b>Affairs</b> is sapphire blue, for the business of the world. <b>Personal</b> is verdant green — yours alone, no one else's. <b>Urgent</b> is garnet red, and you will know it immediately. <b>Social</b> is amethyst purple, the agreeable kind of busy. <b>Travel</b> is amber gold, like late sun on the water. <b>Health</b> is teal — steady, clear, not to be ignored. A week rendered entirely in red tells quite a different story than one in purple. This is the genius of the system." },
                    { rule: true,
                      kicker: "TASKS & INTENTIONS",
                      h:     "The reeds hold everything",
                      p:     "On the right side of the Ledger I maintain a second list — not appointments with a fixed time, but intentions. Things you mean to do. Type one into <b>Add a task…</b> and press Enter. I will hold it in the reeds indefinitely. When the thing is done, tap its little box and a gold tick appears — deeply satisfying, I find. Rest your pointer on a task and a <b>✕</b> appears; tap it and the task vanishes entirely. Your tasks persist between sessions without fail. I have an excellent memory for the things entrusted to me. They will be there, in precisely the order you left them, every time you return." },
                    { rule: true,
                      kicker: "REMINDERS",
                      h:     "I will not let you forget",
                      p:     "When you record an appointment, tell me how early you require a nudge — five minutes, half an hour, a whole day ahead. At the appointed moment I shall send a notice up to the surface of your screen. The appointment will not ambush you with your feet in the mud. I have arranged it so that it cannot. To review all your pending reminders at once, tap <b>REMINDERS</b> in the left rail. They are all there, marshalled in order, waiting for their moment. I watch them so you do not have to." },
                    { rule: true,
                      kicker: "QUICK PAWS",
                      h:     "For those who prefer the keyboard",
                      p:     "Press <b>/</b> and I will search every appointment and task for you — title, place, or notes. Press <b>G</b> and tell me where to leap: <i>today</i>, <i>tomorrow</i>, <i>+7</i>, <i>Jul 4</i>, <i>2026-12-25</i>. <b>Ctrl+N</b> begins a fresh appointment, <b>Ctrl+T</b> returns you to today, and <b>Esc</b> closes whatever I have opened. In the appointment form, <b>Enter</b> inscribes it. Times are written the continental way — <b>14:30</b>, not half past two — and if the end comes before the start I shall turn the field red rather than guess." },
                    { rule: true,
                      kicker: "THE BAR AT THE BOTTOM",
                      h:     "I remain, always, at the foot of the screen",
                      p:     "Even when you close the Ledger window, I do not go away. I am at the foot of your screen, ready. <b>Ledger</b> opens a fresh appointment at once, or brings the full window forward. <b>View</b> lets you switch between Month, Week, Day, Year, and Agenda from anywhere on the desktop — no need to open the window first. <b>Pond</b> is for quick manoeuvres: leap to Today, review your Reminders, leave a lily-pad note, consult today's season card. And <b>Sit by the Pond</b> returns you here whenever you wish. I shall be waiting." },
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
                        font.family: k.titles; font.pixelSize: theme.scale(11)
                        font.letterSpacing: 3; color: k.inkLabel
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
                        font.pixelSize: theme.scale(16); color: parchInk
                        wrapMode: Text.WordWrap; lineHeight: 1.45
                    }

                    Text {
                        visible: !!modelData.p
                        height: visible ? implicitHeight + 10 : 0
                        width: parent.width - 84
                        text: modelData.p || ""
                        font.family: k.gar; font.pixelSize: theme.scale(15)
                        color: parchInk
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

            // ── sign-off ─────────────────────────────────────────────────────
            Text {
                width: parent.width - 84
                leftPadding: 44
                horizontalAlignment: Text.AlignHCenter
                text: "There is no finer pond in all the world. I have visited the others. They do not compare.  — Plato"
                font.family: k.fell; font.italic: true
                font.pixelSize: theme.scale(15); color: k.ink
                topPadding: 16; bottomPadding: 28
            }
        }
    }
}
