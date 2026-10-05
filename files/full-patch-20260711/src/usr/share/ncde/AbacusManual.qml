// AbacusManual.qml — operating manual for Abacus.
// Window popup, opened from the ? button in the Abacus title bar.
// Voice: Edmund Cratchett, Senior Accountant — precise, dry, Victorian.
import QtQuick
import QtQuick.Controls

Window {
    id: win

    flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint
           | Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus
    color: "transparent"
    width:  Math.min(640, Screen.width  - 120)
    height: Math.min(720, Screen.height - 80)
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

                    // floret emblem in gold circle
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
                                var cx = width/2, cy = height/2
                                var R = Math.min(cx,cy) - 2
                                ctx.fillStyle = Qt.rgba(k.wine1.r, k.wine1.g, k.wine1.b, 0.88)
                                ctx.beginPath(); ctx.arc(cx,cy,R*0.22,0,2*Math.PI); ctx.fill()
                                for (var i = 0; i < 8; i++) {
                                    ctx.save(); ctx.translate(cx,cy); ctx.rotate(i * Math.PI/4)
                                    ctx.translate(0, -R*0.56); ctx.scale(0.4, 1.0)
                                    ctx.beginPath(); ctx.arc(0,0,R*0.3,0,2*Math.PI); ctx.fill(); ctx.restore()
                                }
                            }
                        }
                    }

                    Item { width: 1; height: 14 }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Abacus"
                        font.family: k.display; font.bold: true
                        font.pixelSize: theme.scale(28); color: k.ink
                        font.letterSpacing: 1
                    }
                    Item { width: 1; height: 4 }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Edmund Cratchett, Senior Accountant"
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
                        { kicker: "INTRODUCTION",
                          h:     "A figure entered correctly is a figure trusted",
                          lead:  "Good morning. I am Edmund Cratchett, Senior Accountant. I have kept the books here since the beginning. Abacus is a simple instrument — four operations, a decimal point, a clear button — and I intend to see it used properly.",
                          p:     "Tap any key to begin. The display accepts up to twelve digits. I find that is more than sufficient for most legitimate purposes." },

                        { rule: true,
                          kicker: "THE DISPLAY",
                          h:     "Two lines, one truth",
                          p:     "The upper line of the readout shows the <b>expression in progress</b> — the previous figure and the operator you have selected, so you may verify your intention before committing. The lower line shows the <b>current working figure</b> in large type. It does not lie. If it says Error, you have asked an impossible question." },

                        { rule: true,
                          kicker: "THE KEYS",
                          h:     "Each button has its assignment",
                          p:     "<b>AC</b> — All Clear. Closes the ledger entirely and returns the machine to zero. Use it freely; there is no shame in starting again.<br><br><b>±</b> — Reverses the sign of the current figure. Positive becomes negative. I have found this useful when balancing accounts.<br><br><b>%</b> — Converts to a percentage. If an operator is active, calculates that percentage of the previous figure. Otherwise divides by one hundred.<br><br><b>⌫</b> — Removes the last digit entered. A figure entered in haste may be corrected one digit at a time. This is preferable to clearing everything." },

                        { rule: true,
                          kicker: "THE FOUR OPERATORS",
                          h:     "Addition, subtraction, multiplication, division",
                          p:     "Tap an operator after entering the first figure, then enter the second, then tap <b>=</b>. The active operator is highlighted in gold while awaiting the second entry — a useful reminder that you are mid-calculation. Chaining is permitted: tap a new operator immediately after <b>=</b> to continue from the result.<br><br>A note on division: dividing by zero is not a legitimate accounting practice. The display will note this. I recommend against it." },

                        { rule: true,
                          kicker: "THE KEYBOARD",
                          h:     "For those who prefer not to tap",
                          p:     "The number keys, <b>+ − * /</b>, the decimal point, and <b>Enter</b> or <b>=</b> all function as expected. <b>Backspace</b> removes the last digit. <b>Escape</b> or <b>Delete</b> clears the machine entirely. The keyboard and the on-screen keys are identical in effect." },
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
                    text: "The books are balanced. That is all one can ask of any instrument.  — E. Cratchett, Sr."
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
