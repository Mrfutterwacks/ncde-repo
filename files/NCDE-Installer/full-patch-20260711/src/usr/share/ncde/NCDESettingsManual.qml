// NCDESettingsManual.qml — NCDE Settings Operating Manual.
// Digital book in Agatha's voice (Auntie Mame + Blanche + a dash of Rose).
// Left chapter rail + right content area. Opened from the About tab in Settings.
// Agatha narrates all 12 Settings chapters. Her domain, her wing, her arrangement.
import QtQuick
import QtQuick.Controls

Window {
    id: book

    flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint
           | Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus
    color: "transparent"
    width:  Math.min(860, Screen.width  - 80)
    height: Math.min(840, Screen.height - 60)
    x: Math.round((Screen.width  - width)  / 2)
    y: Math.round((Screen.height - height) / 2)
    visible: false

    NCDEKit { id: k }

    property int chapter: 0
    // k.ink is already dark/light-adaptive; the old k.gilt0 dark-mode branch
    // was a hardcoded, non-adaptive umber that read as too-dark-on-dark-parchment.
    readonly property color parchInk: k.ink

    function show() { visible = true; chapter = 0; raise() }
    function hide() { visible = false }

    // ── chapter definitions ──────────────────────────────────────────────────
    readonly property var chapters: [

        // 0 · OPENING
        { tab: "Opening",
          eyebrow: "my domain · poseidon",
          title: "A Word from Agatha",
          blocks: [
            { lead: "Oh, you found me. Good. I was beginning to wonder how long it would take." },
            { p: "This is the Settings panel -- and it is, in every meaningful sense, <i>my</i> wing of the house. I have arranged it personally. The colours, the type, the way things sound, the way the screen behaves late at night when you ought to be asleep -- all of that is here, and all of it is mine. Tap the gear on the dock, or find it in Glia's menu under the N. The panel opens with the three wings on the left and the current tab on the right." },
            { p: "You may move the panel by its title bar. The three jewels in the corner close, maximise, and minimise it, same as any other window. Every change you make writes at the moment you make it. No Save button, darling -- I do not have time for Save buttons." },
            { sign: "Take your time. I certainly will.  -- Agatha" }
          ]
        },

        // 1 · THREE WINGS
        { tab: "Three Wings",
          eyebrow: "the shape of the house",
          title: "The Three Wings",
          blocks: [
            { lead: "I have organised everything into three wings. It was the only sensible arrangement." },
            { kicker: "APPEARANCE" },
            { h: "Beauty first" },
            { p: "Wallpapers, Filigree, Fonts, and Screensaver -- the <i>look</i> of the house. I have spent the most time here. If you only have five minutes, spend them in Filigree. It changes everything." },
            { rule: true },
            { kicker: "DEVICES" },
            { h: "The machine itself" },
            { p: "Display, Input, Sound, Power, Storage, and Network. This is where you tell the machine how it ought to behave. Less glamorous than Appearance, but important. I keep Night Light on permanently. I consider it a public service." },
            { rule: true },
            { kicker: "SYSTEM" },
            { h: "Running the house" },
            { p: "Users, Date and Time, Notifications, Session, and the About tab -- where you found this manual. System is the part of the house most people never visit. I recommend visiting it once, setting things properly, and then coming back only when something interesting happens. Which it will, darling. It always does." }
          ]
        },

        // 2 · FILIGREE
        { tab: "Filigree",
          eyebrow: "colour · glass · type",
          title: "Filigree -- the Look",
          blocks: [
            { lead: "If the Settings panel had a throne room, this would be it." },
            { p: "Turn the <b>colour wheel</b> and a five-tone palette arranges itself beneath: Ground, Surface, Accent, Highlight, and Quill -- the colour of all your type. I once spent two hours on the wheel alone. I have no regrets. <b>Harmony</b> offers schemes: complementary, triadic, analogous. Choose based on your wallpaper and your mood. I choose based entirely on my mood." },
            { rule: true },
            { kicker: "BASE CALM" },
            { h: "Turning down the volume" },
            { p: "The <b>Base Calm</b> dial quiets your backgrounds while keeping the accent vivid. Think of it as lowering the lights but leaving the statement piece lit. <b>In Context</b> shows the palette live over your wallpaper -- absolutely worth doing. <b>Apply as Theme</b> changes everything at once. It is quite the entrance. I recommend a pause before and after." },
            { rule: true },
            { kicker: "GLASS" },
            { h: "Surfaces and depth" },
            { p: "Glass controls live below the palette -- one row per surface: panels, dock, widgets, and menus. Each takes a tint, a glow, and a border. Press <b>Link all to accent</b> to dress them as one, or tune each independently if you have the patience. I do. Dark mode is deeply, deeply atmospheric. I have left mine on for three months. I am not ashamed." }
          ]
        },

        // 3 · WALLPAPERS
        { tab: "Wallpapers",
          eyebrow: "dressing the room",
          title: "Wallpapers",
          blocks: [
            { lead: "The wallpaper is the first thing the room says about you. Make sure it says something good." },
            { p: "Choose from the built-in gallery -- each image selected with care, I may add -- or tap <b>Browse</b> to use your own picture. Set the fit: <b>Fill</b> is the most committed, and I admire commitment. Fit, Centre, Tile, and Span are also available for the undecided. Set a <b>slideshow</b> to rotate a folder on a timer; the change does one good." },
            { rule: true },
            { kicker: "THEME FROM WALLPAPER" },
            { h: "The room coordinates itself" },
            { p: "My personal favourite: tap <b>Theme from Wallpaper</b> and the system reads the dominant colour from your picture and hands it straight to Filigree. I used a photograph of a lily once and the whole desktop went the most extraordinary shade of gold. I kept it for six months. I may put it back." }
          ]
        },

        // 4 · FONTS
        { tab: "Fonts",
          eyebrow: "the type foundry",
          title: "Fonts -- Lady Lucrezia's Room",
          blocks: [
            { lead: "The Fonts room is Lady Lucrezia La Fonderie's domain and she keeps it spotless." },
            { p: "Set your <b>Interface</b> face for menus and titles, your <b>Document</b> face for reading long text, and your <b>Fixed-width</b> face for the terminal. Adjust the <b>size scale</b> to taste. The colour of type lives in Filigree -- colour is an aesthetic matter and aesthetic matters belong there." },
            { rule: true },
            { kicker: "INSTALLING FACES" },
            { h: "NCDECommand -- La Fonderie" },
            { p: "New typefaces are installed through NCDECommand's La Fonderie section -- Lady Lucrezia's personal wing of the software centre. Browse by name, preview each face rendered in its own hand, and install with one tap. She runs the font cache refresh herself. She would not trust anyone else with it. Frankly, neither would I." },
            { sign: "A bad font is a bad first impression.  -- Agatha (quoting Lady Lucrezia)" }
          ]
        },

        // 5 · DISPLAY
        { tab: "Display",
          eyebrow: "screens and light",
          title: "Display",
          blocks: [
            { lead: "Screens should be arranged properly. Nothing is more vexing than a window that falls off the edge of a monitor." },
            { p: "Drag your screens into position on the map, name a primary, and set each one's resolution, refresh rate, scale, and orientation. If you are running a single screen, most of this is decided for you. Still worth visiting, just to confirm that everything is as it should be." },
            { rule: true },
            { kicker: "NIGHT LIGHT" },
            { h: "The amber hour" },
            { p: "<b>Night Light</b> warms the display from sunset to sunrise without your having to set any times. NCDE already knows where you are from the network, so it follows the sun unattended. The warm amber is, I have to say, very flattering. Not just to the screen -- to everything around it. I strongly encourage it. Some things should simply be encouraged." }
          ]
        },

        // 6 · INPUT
        { tab: "Input",
          eyebrow: "keyboard · mouse · touchpad",
          title: "Input",
          blocks: [
            { lead: "How you speak to the machine matters. Settle this once and it will never trouble you again." },
            { p: "Set your <b>keyboard layout</b> -- if you write in two languages, you may add a second and switch between them. I find it suggests a person of wide acquaintance. <b>Repeat delay</b> and <b>rate</b> adjust how long a held key waits before repeating, and how quickly it does so once it starts. Set these to taste and forget about them." },
            { rule: true },
            { kicker: "MOUSE AND TOUCHPAD" },
            { h: "Pointer and touch" },
            { p: "<b>Pointer speed</b>, <b>natural scroll</b>, <b>tap-to-click</b>, and <b>disable while typing</b> -- all here. The cursor takes a theme and a size. I use the largest. One should always know precisely where one is going." }
          ]
        },

        // 7 · SOUND
        { tab: "Sound",
          eyebrow: "audio in and out",
          title: "Sound",
          blocks: [
            { lead: "Good audio is essential. Not just for music -- for the overall sense that the house is alive." },
            { p: "Choose your <b>output device</b> -- speakers, headphones, or external -- and set the volume and balance. Choose your <b>input device</b> for the microphone and watch the live level bar to confirm it is receiving. If the bar does not move when you speak, something is unplugged. This is the most common cause of confusion and always the simplest fix." },
            { rule: true },
            { kicker: "PER-APPLICATION MIXER" },
            { h: "Not everything at the same volume" },
            { p: "Below the device controls: a mixer with one row for every running program. Salon Nocturne may be loud; NCDECommand may be silent. This is correct. I have mine arranged in exactly this way and find it produces a properly orchestrated environment." }
          ]
        },

        // 8 · POWER
        { tab: "Power",
          eyebrow: "sleep and the machine",
          title: "Power",
          blocks: [
            { lead: "Tell the machine when to rest. It will listen. Most things do, if you are firm." },
            { p: "Two columns -- <b>on battery</b> and <b>plugged in</b> -- each sets a time to dim the screen and a time to suspend. <b>Never</b> is an option and I use it. Below: what the <b>lid</b> does when closed, and what the <b>power button</b> does when pressed. I have mine set to ask. I prefer to be consulted." },
            { rule: true },
            { kicker: "BATTERY DISPLAY" },
            { h: "The percentage" },
            { p: "A toggle shows the battery percentage in the top bar. I keep mine showing. One likes to know how much one has left. It is relevant information in rather more situations than one generally anticipates." }
          ]
        },

        // 9 · DATE & TIME
        { tab: "Date & Time",
          eyebrow: "the clock",
          title: "Date and Time",
          blocks: [
            { lead: "The clock keeps itself -- you should never have to set your timezone by hand." },
            { p: "NCDE finds where you are from the network. A map shows a pin and the badge <b>Located automatically</b>. Travel to another city and the clock follows without a word from you. The hour format may be 12-hour, 24-hour, or Auto. I use 12-hour. 14:30 always gives me a small shock, whereas two-thirty is perfectly comprehensible." },
            { rule: true },
            { kicker: "MANUAL TIMEZONE" },
            { h: "If you prefer to choose yourself" },
            { p: "An escape hatch at the foot of the map lets you choose your timezone directly. Doing so turns the automatic locating off until you ask for it again. I mention this not because I recommend it, but because I know some people like to be in charge of everything. I understand the impulse entirely." }
          ]
        },

        // 10 · NOTIFICATIONS
        { tab: "Notifications",
          eyebrow: "quiet hours · do not disturb",
          title: "Notifications",
          blocks: [
            { lead: "One cannot be interrupted every five minutes. This is where you establish the rules." },
            { p: "<b>Do Not Disturb</b> silences everything at once -- one tap and not a sound from anyone. I use it frequently and without apology. Choose which <b>corner</b> banners appear in -- I prefer top right, just out of the way but visible. Set <b>Quiet Hours</b> for a nightly span when only alarms may speak. I have mine from eleven until eight because I am not a morning person and I refuse to pretend otherwise." },
            { rule: true },
            { kicker: "PER-APPLICATION" },
            { h: "Choose who may speak" },
            { p: "Below the global controls: a list of every application with its own on/off toggle. Hummingbird Courier may call while NCDECommand stays entirely silent. Magpie Talker may announce itself while Verve does not. These are all sensible arrangements. Make your own." }
          ]
        },

        // 11 · SESSION & ABOUT
        { tab: "Session",
          eyebrow: "starting up · this machine",
          title: "Session and About",
          blocks: [
            { lead: "The last room in the wing -- and the most domestic." },
            { kicker: "AUTOSTART" },
            { h: "Who greets you at the door" },
            { p: "<b>Autostart</b> lists the programs that open when you log in. I have Magpie Talker and Hummingbird Courier in mine -- I like to arrive to a welcoming house. Add a program with the button at the top, give it a name and a command, and switch it on." },
            { rule: true },
            { kicker: "DEFAULT APPLICATIONS" },
            { h: "Who handles what" },
            { p: "Name your <b>browser</b>, your <b>mail client</b>, your <b>files manager</b>, and your <b>terminal</b>. NCDE uses these whenever a link or attachment needs opening. Set them once and never think about it again." },
            { rule: true },
            { kicker: "ABOUT" },
            { h: "This machine's particulars" },
            { p: "The About tab -- where you began this adventure -- shows your NCDE version, compositor, and machine specifications: processor, memory, graphics, and disk. The button there opens this manual again whenever you want a second reading. I expect most of you will manage without it, but the door is always open." },
            { sign: "This is your house now, darling. Make it extraordinary.  -- Agatha" }
          ]
        },

        // 12 · VESPER
        { tab: "Vesper",
          eyebrow: "a word from agatha",
          title: "My Great-Grand-Nephew",
          blocks: [
            { lead: "Before I close this manual, there is someone I want you to know about. He will not introduce himself. He never does." },
            { kicker: "WHO HE IS" },
            { h: "Vesper" },
            { p: "Vesper is my great-grand-nephew. Poor boy -- he has seen things, and done things. The child lost his parents at a young age due to a virus, and now he lives with me, his Auntie. He is often overlooked. Unassuming. Folks tend to ignore him." },
            { p: "But you will not. Will you." },
            { p: "He is quite an old soul -- little, but loud when need be. Some children are wise beyond their years, and when my Vesper speaks, folks ought to listen. He does not say a great deal. But when he does, it is because there is something to say." },
            { rule: true },
            { kicker: "WHAT HE DOES" },
            { h: "He watches when the rest of us cannot" },
            { p: "Vesper is the security intelligence of NCDE. He runs his own program, entirely separate from my wing. He monitors everything: files, processes, the network. Five engines report to him. When they find something, he tells you about it. In his terminal. In his voice." },
            { p: "His world is nothing like mine. Cold, green -- a phosphor terminal from another era entirely. The difference is intentional. When Vesper's window appears, something needs your attention. Pay it." },
            { rule: true },
            { kicker: "A WORD OF CAUTION" },
            { h: "When he knocks at your door" },
            { p: "He is not dramatic. He does not cry wolf. If Vesper tells you something is wrong, something is wrong. He has been in that machine since before most of us knew there was a machine. He knows every trick -- because he has tried every trick -- and he chose to use that knowledge to protect real people instead." },
            { p: "When he knocks at your door, dear ones -- ignore him at your peril." },
            { sign: "He is family. He is good at what he does. That is all I will say.  -- Agatha" }
          ]
        }
    ]

    // ── layout ───────────────────────────────────────────────────────────────
    Item {
        anchors.fill: parent

        NCDEParchmentSurface { anchors.fill: parent; cornerRadius: 16 }

        // ── left chapter rail ────────────────────────────────────────────────
        Rectangle {
            id: rail
            anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left
            anchors.topMargin: 16; anchors.bottomMargin: 16
            anchors.leftMargin: 16
            width: 148
            radius: 10
            color: Qt.rgba(k.wine1.r, k.wine1.g, k.wine1.b, 0.88)
            border.color: k.gilt1; border.width: 1

            Rectangle {
                anchors.fill: parent; anchors.margins: 3
                radius: parent.radius - 2; color: "transparent"
                border.color: Qt.rgba(k.gilt4.r, k.gilt4.g, k.gilt4.b, 0.18); border.width: 1
            }

            Column {
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                anchors.topMargin: 18
                spacing: 0

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "A"; font.family: k.display; font.bold: true
                    font.pixelSize: theme.scale(22); color: k.gilt4
                    font.letterSpacing: 1; bottomPadding: 4
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "SETTINGS"; font.family: k.titles
                    font.pixelSize: theme.scale(9); color: k.gilt2
                    font.letterSpacing: 3; bottomPadding: 12
                }

                Rectangle {
                    width: parent.width - 24
                    anchors.horizontalCenter: parent.horizontalCenter; height: 1
                    gradient: Gradient { orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "transparent" }
                        GradientStop { position: 0.5; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.5) }
                        GradientStop { position: 1.0; color: "transparent" }
                    }
                }
                Item { width: 1; height: 8 }

                Repeater {
                    model: book.chapters

                    Item {
                        width: rail.width; height: 34
                        property bool active: book.chapter === index
                        property bool hov: chHov.hovered

                        Rectangle {
                            anchors.fill: parent
                            anchors.leftMargin: 8; anchors.rightMargin: 8
                            radius: 6
                            color: active ? Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.22)
                                 : hov    ? Qt.rgba(k.gilt4.r, k.gilt4.g, k.gilt4.b, 0.10)
                                 : "transparent"
                            Behavior on color { ColorAnimation { duration: 100 } }

                            Rectangle {
                                visible: active
                                anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
                                anchors.leftMargin: -4
                                width: 3; radius: 1.5; color: k.gilt3
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: modelData.tab
                            font.family: k.titles; font.pixelSize: theme.scale(10)
                            font.bold: active; font.letterSpacing: active ? 1 : 0
                            color: active ? k.gilt4 : Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.85)
                            Behavior on color { ColorAnimation { duration: 100 } }
                        }

                        HoverHandler { id: chHov }
                        TapHandler { onTapped: { book.chapter = index; flick.contentY = 0 } }
                    }
                }
            }
        }

        // ── content area ─────────────────────────────────────────────────────
        Item {
            anchors.top: parent.top; anchors.bottom: parent.bottom
            anchors.left: rail.right; anchors.right: parent.right
            anchors.topMargin: 16; anchors.bottomMargin: 16
            anchors.leftMargin: 12; anchors.rightMargin: 16

            Column {
                id: chapterHead
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                anchors.topMargin: 20
                anchors.leftMargin: 20; anchors.rightMargin: 44
                spacing: 0

                Text {
                    text: book.chapters[book.chapter].eyebrow || ""
                    font.family: k.titles; font.pixelSize: theme.scale(10)
                    font.letterSpacing: 3; color: k.gilt1; opacity: 0.8
                }
                Item { width: 1; height: 3 }
                Text {
                    text: book.chapters[book.chapter].title || ""
                    font.family: k.display; font.bold: true
                    font.pixelSize: theme.scale(26); color: k.ink
                }
                Item { width: 1; height: 10 }
                Rectangle {
                    width: parent.width; height: 1
                    gradient: Gradient { orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.7) }
                        GradientStop { position: 0.7; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.15) }
                        GradientStop { position: 1.0; color: "transparent" }
                    }
                }
                Item { width: 1; height: 6 }
            }

            Flickable {
                id: flick
                anchors.top: chapterHead.bottom; anchors.bottom: parent.bottom
                anchors.left: parent.left; anchors.right: parent.right
                anchors.leftMargin: 20; anchors.rightMargin: 16
                anchors.bottomMargin: 8
                clip: true; contentWidth: width; contentHeight: body.implicitHeight
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: NCDEScrollBar {}

                Column {
                    id: body
                    width: flick.width; spacing: 0

                    Repeater {
                        model: book.chapters[book.chapter].blocks || []

                        delegate: Column {
                            width: body.width; spacing: 0

                            Item { width: 1; height: modelData.rule ? 12 : (modelData.kicker ? 10 : 0) }

                            Text {
                                visible: !!modelData.kicker
                                height: visible ? implicitHeight + 2 : 0
                                width: parent.width; text: modelData.kicker || ""
                                font.family: k.titles; font.pixelSize: theme.scale(10)
                                font.letterSpacing: 3; color: k.gilt1
                            }
                            Text {
                                visible: !!modelData.h
                                height: visible ? implicitHeight + 4 : 0
                                width: parent.width; text: modelData.h || ""
                                font.family: k.display; font.bold: true
                                font.pixelSize: theme.scale(19); color: k.ink
                                wrapMode: Text.WordWrap
                            }
                            Text {
                                visible: !!modelData.lead
                                height: visible ? implicitHeight + 7 : 0
                                width: parent.width; text: modelData.lead || ""
                                font.family: k.fell; font.italic: true
                                font.pixelSize: theme.scale(15); color: book.parchInk
                                wrapMode: Text.WordWrap; lineHeight: 1.45
                            }
                            Text {
                                visible: !!modelData.p
                                height: visible ? implicitHeight + 9 : 0
                                width: parent.width; text: modelData.p || ""
                                font.family: k.gar; font.pixelSize: theme.scale(14)
                                color: book.parchInk
                                textFormat: Text.RichText; wrapMode: Text.WordWrap
                                lineHeight: 1.55
                            }
                            Rectangle {
                                visible: !!modelData.rule
                                height: visible ? 1 : 0; width: parent.width
                                gradient: Gradient { orientation: Gradient.Horizontal
                                    GradientStop { position: 0.0;  color: "transparent" }
                                    GradientStop { position: 0.15; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.4) }
                                    GradientStop { position: 0.85; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.4) }
                                    GradientStop { position: 1.0;  color: "transparent" }
                                }
                            }
                            Text {
                                visible: !!modelData.sign
                                height: visible ? implicitHeight + 12 : 0
                                width: parent.width; text: modelData.sign || ""
                                font.family: k.fell; font.italic: true
                                font.pixelSize: theme.scale(14); color: k.ink
                                horizontalAlignment: Text.AlignHCenter
                                topPadding: 8
                            }
                        }
                    }

                    Item { width: 1; height: 20 }
                }

                Rectangle {
                    anchors.right: parent.right; anchors.rightMargin: -6
                    width: 3; radius: 1.5
                    color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.5)
                    visible: flick.contentHeight > flick.height
                    height: flick.height * (flick.height / flick.contentHeight)
                    y: flick.contentHeight > flick.height
                       ? (flick.contentY / (flick.contentHeight - flick.height)) * (flick.height - height)
                       : 0
                }
            }
        }

        // ── close jewel ──────────────────────────────────────────────────────
        Item {
            width: 30; height: 30
            anchors.top: parent.top; anchors.right: parent.right
            anchors.topMargin: 14; anchors.rightMargin: 16

            Canvas {
                anchors.fill: parent; renderStrategy: Canvas.Cooperative
                property bool hov: closeHov.hovered
                onHovChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d"); ctx.clearRect(0, 0, width, height)
                    var cx = width/2, cy = height/2, r = width/2 - 2
                    ctx.beginPath()
                    ctx.moveTo(cx, cy-r); ctx.lineTo(cx+r, cy); ctx.lineTo(cx, cy+r); ctx.lineTo(cx-r, cy); ctx.closePath()
                    ctx.fillStyle = hov ? k.wine4 : k.wine2; ctx.fill()
                    ctx.strokeStyle = hov ? k.gilt4 : k.gilt3; ctx.lineWidth = 1.5; ctx.stroke()
                    ctx.strokeStyle = k.surface; ctx.lineWidth = 1.8; ctx.lineCap = "round"
                    var d = r * 0.42
                    ctx.beginPath()
                    ctx.moveTo(cx-d, cy-d); ctx.lineTo(cx+d, cy+d)
                    ctx.moveTo(cx+d, cy-d); ctx.lineTo(cx-d, cy+d)
                    ctx.stroke()
                }
            }
            HoverHandler { id: closeHov }
            TapHandler { onTapped: book.hide() }
        }
    }
}
