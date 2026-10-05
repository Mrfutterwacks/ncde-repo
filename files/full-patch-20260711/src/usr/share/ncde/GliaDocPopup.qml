// GliaDocPopup.qml — scrollable parchment document popup.
// Centered on the desktop like the settings panel. Sized to the content.
// Book layout: N-crest frontispiece · kicker/heading/lead/body/rule/sign-off.
// NCDEKit wired — parchment is always ivory so ink is forced dark in both modes.
//
// Block types: { kicker:"" } { h:"" } { lead:"" } { p:"" } { rule:true } { sign:"" }
import QtQuick
import QtQuick.Controls

Window {
    id: win

    flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint
           | Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus
    color: "transparent"
    width:  Math.min(760, Screen.width  - 120)
    height: Math.min(820, Screen.height - 80)
    x: Math.round((Screen.width  - width)  / 2)
    y: Math.round((Screen.height - height) / 2)
    visible: false

    NCDEKit { id: k }

    property var content: ({ eyebrow: "", title: "", blocks: [] })
    // k.ink is already dark/light-adaptive; the old "parchment is always ivory"
    // assumption was false (NCDEParchmentSurface's background does go dark in
    // dark mode) and the k.gilt0 branch it fed was a hardcoded, non-adaptive
    // umber that read as too-dark-on-dark-parchment.
    readonly property color parchInk: k.ink

    signal closed()

    function show(key) { content = win.docFor(key); visible = true; raise() }
    function hide()    { visible = false; closed() }

    // ── built-in documents ───────────────────────────────────────────────────
    function docFor(key) {
        if (key === "about-ncde") return {
            eyebrow: "an introduction · Poseidon release",
            title: "Meet Glia",
            blocks: [
                { lead: "A friend of mine — Debbie D. Bus — built this beautiful place and left me here to keep it for you. She had to move along, deep into the machine where I cannot follow. But before she left, she handed me the keys and said: look after them." },
                { p: "You are standing in <b>NCDE</b> — New Common Desktop Environment. This is your home now. The walls are warm, the windows are leaded, and everything works the way a good house should — quietly, reliably, waiting for you." },
                { rule: true },
                { kicker: "WHERE I LIVE" },
                { h: "The bar at the top" },
                { p: "I live at the very top of your screen — the long stripe of menus that stretches from corner to corner. When you need me, move your hand to the top of the screen and I appear. When you step away, I fold back out of the light and let the room breathe." },
                { rule: true },
                { kicker: "THE HOUSE MENU" },
                { h: "Touch the N" },
                { p: "Far to the left sits the letter <b>N</b> — that is mine, the drawer-pull for the whole house. Touch it and the NCDE house menu opens. Here you will find <b>Meet Glia</b> (this introduction), <b>Settings</b> for every preference in the house, <b>Lock Screen</b> for stepping away, and <b>Log Out</b>. Everything for tending the house itself lives right there." },
                { rule: true },
                { kicker: "OPENING THINGS" },
                { h: "Applications" },
                { p: "<b>Applications</b> holds every program on this machine, sorted into groups. <b>Orchidée</b> for your files, <b>Hummingbird</b> for your post, <b>Verve</b> for writing, <b>Abacus</b> for sums, <b>Magpie</b> for talking across the room. Tap Applications, find the one you want, and it opens." },
                { rule: true },
                { kicker: "YOUR ROOMS" },
                { h: "Places" },
                { p: "<b>Places</b> takes you straight to your rooms — <b>Home</b>, <b>Documents</b>, <b>Downloads</b>, <b>Pictures</b>, <b>Music</b>. Tap a name and Orchidée opens right there. Binnie, the little bin in the corner, is in Places too." },
                { rule: true },
                { kicker: "THE HOUSE ITSELF" },
                { h: "System" },
                { p: "<b>System</b> is where the house is tuned. <b>Preferences</b> covers how things look and feel — appearance, display, keyboard, and mouse. <b>Administration</b> covers the guest list and the network. At the foot of the menu: <b>Lock Screen</b>, <b>Log Out</b>, and <b>Shut Down</b> — the proper way to leave for the night." },
                { rule: true },
                { kicker: "ALWAYS WITHIN REACH" },
                { h: "File · Edit · View" },
                { p: "Toward the right end of the bar you will find <b>File</b>, <b>Edit</b>, and <b>View</b>. These carry the standard commands for whatever you are working on — New, Open, Save, Undo, Copy, Paste, Zoom. They are always there whether a window is open or not." },
                { h: "The Handbook" },
                { p: "At the far right of the bar sits <b>NCDE Handbook</b> — a fuller guide to every room of this place and how to use it. Go there whenever you want more detail." },
                { sign: "I am Glia — and this is your home." }
            ]
        }
        if (key === "handbook") return {
            eyebrow: "the complete reference · Poseidon release",
            title: "The Glia Handbook",
            blocks: [
                { lead: "Everything in this house — its rooms, its programs, its dials, and the quiet machinery beneath the floor — explained in plain language for someone who has just arrived." },
                { rule: true },
                { kicker: "YOUR NEW HOME" },
                { h: "What NCDE is" },
                { p: "NCDE is a complete desktop — your programs, your files, your settings, your calendar, and your post — all in one warm and familiar place. Nothing requires a command line or a config file. If you are arriving from Windows, think of NCDE as your new house: different rooms, same furniture, better light." },
                { rule: true },
                { kicker: "THE MENU BAR" },
                { h: "Glia — the bar at the top" },
                { p: "Move your hand to the top of the screen and the menu bar appears. It folds away when you do not need it and comes back the moment you reach for it. <b>N</b> opens the house menu: Meet Glia, Settings, Lock Screen, Log Out. <b>Applications</b> holds every program, sorted into groups. <b>Places</b> takes you to Home, Documents, Downloads, Pictures, and Music. <b>System</b> covers preferences, administration, and the power controls. <b>File</b>, <b>Edit</b>, and <b>View</b> carry the standard commands — New, Open, Save, Undo, Copy, Paste — always within reach. <b>NCDE Handbook</b> (this document) lives at the far right." },
                { rule: true },
                { kicker: "THE DESKTOP" },
                { h: "What you see when you arrive" },
                { p: "The desktop shows your wallpaper with a column of live widgets on the right — a clock, weather, system stats, and Salon Nocturne. The <b>dock</b> sits on the left edge; hover to reveal it and click any icon to open a program. The <b>Leap Frog bar</b> runs along the bottom, keeping your calendar always at hand. Right-click anywhere on the wallpaper for a quick menu." },
                { h: "Windows and the dock" },
                { p: "Open windows show their titles in the <b>task bar</b> along the bottom. Click a title to bring it forward; click it again to minimise. A minimised window becomes a small jewelled pill in the task bar — click it to restore. The dock holds your most-used programs; right-click any icon to pin or unpin it." },
                { rule: true },
                { kicker: "NATIVE APPLICATIONS" },
                { h: "Orchidée — files and folders" },
                { p: "<b>Orchidée</b> is your file manager. It opens on your Home folder and lets you navigate, copy, move, rename, and delete files in grid, list, or column view. The sidebar shows your main folders and any connected USB drives. Drag files between windows the way you would in Windows Explorer. Right-click a file or folder for its full menu of actions." },
                { h: "Hummingbird Courier — your post" },
                { p: "<b>Hummingbird Courier</b> connects to Gmail, Outlook, or any IMAP account. On first open, enter your email address and an app password, then tap <b>Connect</b>. Your post arrives styled with the stationery you chose — Garden, Formal, or Professional. Compose on a writing desk with your stationery framing the page. The <b>Address Book</b> holds your correspondents; open a card to write to them directly." },
                { h: "Magpie Talker — local chat" },
                { p: "<b>Magpie Talker</b> lets you talk to anyone on the same building network — no internet needed, no account to create. Open it, see who is on the network, tap a name, and start a conversation. Good for offices, classrooms, and sanctuaries." },
                { h: "Verve — writing" },
                { p: "<b>Verve</b> is a clean text editor for notes, drafts, and plain writing. Open or create a file through <b>File</b> in the menu bar, or drag a file onto the window." },
                { h: "Abacus — calculator" },
                { p: "<b>Abacus</b> is the desk calculator — standard arithmetic, scientific functions, and a history of recent calculations. Open it from the dock or Applications." },
                { h: "Leap Frog Ledger — your calendar" },
                { p: "<b>Leap Frog Ledger</b> lives in the bar at the foot of the screen and keeps your appointments, tasks, and reminders in five views: Month, Week, Day, Year, and Agenda. Tap <b>Sit by the Pond</b> in the Leap Frog bar for Plato's full tour of the calendar." },
                { h: "NCDECommand — app store and tools" },
                { p: "<b>NCDECommand</b> is where you install new programs, manage fonts, and run system tools — all without a command line. The <b>Store</b> tab shows available programs; tap one and press <b>Install</b>. The <b>Fonts</b> tab (La Fonderie) lets you add and remove typefaces with a live preview. The <b>Tools</b> tab carries system utilities. Think of it as the NCDE equivalent of the Windows Store." },
                { h: "Binnie — the bin" },
                { p: "<b>Binnie</b> holds deleted files until you empty it. Open it from Places or the dock. Drag files out to restore them; tap <b>Empty</b> to clear it. Always unmount USB drives through Storage in Settings before pulling them out." },
                { rule: true },
                { kicker: "SETTINGS — OPENING" },
                { h: "How the settings panel works" },
                { p: "Open Settings from the dock, from <b>N → Settings</b>, or from <b>System → Preferences</b>. The panel carries its own title bar — drag it anywhere. Every change takes effect the moment you make it; there is no Save button. Changes to the theme and glass redress the desktop live, without a logout. The panel has three wings: <b>Appearance</b>, <b>Devices</b>, and <b>System</b>." },
                { rule: true },
                { kicker: "APPEARANCE — WALLPAPERS" },
                { h: "Dressing the desk" },
                { p: "Choose from the built-in gallery or tap <b>Browse</b> to use your own picture. Set the <b>fit mode</b> — fill, fit, centre, tile, or span. Turn on the <b>slideshow</b> to rotate a folder on a timer. <b>Theme from Wallpaper</b> samples the picture and hands its colour to Filigree, so the whole shell breathes with the image behind it." },
                { kicker: "APPEARANCE — FILIGREE" },
                { h: "Colour, glass, and the look of the house" },
                { p: "Filigree is the visual-design authority for the whole desktop. Turn the <b>colour wheel</b> and a five-tone palette is drawn beneath it — Ground, Surface, Accent, Highlight, and Quill (the text colour). Tap <b>Apply as Theme</b> to dress the shell. <b>Harmony</b> offers single, complementary, triadic, or analogous colour schemes. <b>Contrast Guard</b> checks live that text stays readable. <b>In Context</b> previews the palette over your real wallpaper." },
                { p: "Each surface takes its own glass settings — <b>Panels, Dock, Widgets,</b> and <b>Menus</b> each have their own Tint, Shine, Glow, and Border, or press <b>Link all to accent</b> to keep them of one cloth. Palettes may be named and saved — Filigree suggests a name in the period manner." },
                { kicker: "APPEARANCE — FONTS" },
                { h: "Typefaces and scale" },
                { p: "Set the <b>Interface</b> face (menus and titles), the <b>Document</b> face (reading and editing), and the <b>Fixed-width</b> face (terminal and code). Adjust the size scale and the UI scale here. The <i>colour</i> of type is set in Filigree next door." },
                { kicker: "APPEARANCE — SCREENSAVER" },
                { h: "Les Saisons Nocturnes" },
                { p: "Four generative seasonal paintings play after the screen has been idle for a set time. They know the season and paint accordingly — blossoms in Spring, fireflies in Summer, embers in Autumn, frost in Winter. The screensaver locks the screen; your password returns it." },
                { rule: true },
                { kicker: "DEVICES — DISPLAY" },
                { h: "Screens and Night Light" },
                { p: "Arrange your screens by sight, name a primary, and set each one's resolution, refresh rate, scale, and orientation. <b>Night Light</b> warms the screen after sunset automatically — NCDE finds your timezone from the network, so no times are needed." },
                { kicker: "DEVICES — INPUT" },
                { h: "Keyboard, mouse, and touchpad" },
                { p: "Set your <b>keyboard layout</b> (a second layout may be added for a second language) with repeat delay and rate. For mouse and touchpad: pointer speed, natural scroll, tap-to-click, disable-while-typing. The cursor takes a theme and a size." },
                { kicker: "DEVICES — SOUND" },
                { h: "Audio in and out" },
                { p: "Choose the output device (speakers or headphones) and its volume and balance. Choose the input device (microphone) and watch the live level. A <b>per-application mixer</b> lets one program sing while another is muted." },
                { kicker: "DEVICES — POWER" },
                { h: "Sleep and the lid" },
                { p: "Two columns — <b>on battery</b> and <b>plugged in</b> — set when the screen dims and when the machine sleeps. Set what the lid does when closed and what the power button does when pressed. The battery percentage may be shown or hidden in the panel." },
                { kicker: "DEVICES — STORAGE" },
                { h: "Drives and USB" },
                { p: "Lists your built-in drive and any connected USB sticks or external disks. Tap <b>Mount</b> or <b>Unmount</b> to manage removable media. Always unmount before pulling a drive out." },
                { kicker: "DEVICES — NETWORK & BLUETOOTH" },
                { h: "Connecting to the world" },
                { p: "<b>Network</b>: connect to Wi-Fi, manage saved networks, or configure a wired connection. NCDE reconnects automatically when a known network is in range. <b>Bluetooth</b>: pair headphones, keyboards, and other devices — tap the device name and confirm the code." },
                { rule: true },
                { kicker: "USERS & SYSTEM" },
                { h: "Users & Groups" },
                { p: "Add or remove the people who use this machine. Each person gets their own password, their own home folder, and their own settings. An <b>administrator</b> account can change anything; a <b>standard</b> account can only change its own settings." },
                { h: "Date & Time" },
                { p: "NCDE finds your timezone automatically from the network — a pin on the map confirms the location. The clock stays true with network time. Hour format may be 12-hour, 24-hour, or Auto. Travel to another city and the clock follows. Tap <b>Set manually</b> for a fixed zone." },
                { h: "Notifications" },
                { p: "<b>Do Not Disturb</b> silences all notices at once. <b>Quiet Hours</b> sets a nightly span when only an alarm may speak. Each application has its own switch. Choose the corner where banners appear." },
                { h: "Session" },
                { p: "<b>Autostart</b> lists programs that open when you log in — add a name and switch it on. <b>Default Applications</b> names your browser, mail, file manager, and terminal — used whenever NCDE opens a link or file. Lock and Log Out wait at the foot." },
                { h: "About" },
                { p: "The NCDE version, the compositor, and your machine's particulars — processor, memory, graphics, and disk. The operating manual opens again from here." },
                { rule: true },
                { kicker: "GTK APPLICATIONS" },
                { h: "Programs from the wider world" },
                { p: "NCDE runs all standard Linux programs as well as its native ones — the GTK family includes web browsers (ncde-chromium, Firefox), LibreOffice, GIMP, and anything else you install through NCDECommand. These programs draw their menus and windows in the same Glia bar and take the same Motif frame as native apps. The <b>GTK Apps</b> section of Settings lets you tune their appearance to match the NCDE theme, so a browser or a document editor looks at home in the house rather than like a guest." },
                { rule: true },
                { kicker: "SYSTEM RECOVERY" },
                { h: "One button brings you back" },
                { p: "NCDE keeps seven rolling snapshots of itself — one taken at every startup. If something goes wrong, press <b>Ctrl+Alt+R</b> at any time while on the desktop. A recovery window opens, showing a table of snapshots with their dates. Select one, enter your password, and the restore runs in the background. Your files, photos, and documents are never touched — only the system is restored. When it is finished, the machine restarts, good as new. There is no recovery disc, no USB to boot, and no technician to call. The repair is built into the house." },
                { rule: true },
                { kicker: "SHORTCUTS" },
                { h: "Quick keys" },
                { p: "<b>N (hover top)</b> — house menu  ·  <b>Alt+F4</b> — close window  ·  <b>F1</b> or <b>Super</b> — Exposé (see all windows)  ·  <b>Alt+F2</b> — Run Command  ·  <b>Ctrl+,</b> — Settings  ·  <b>Super+L</b> — Lock Screen  ·  <b>F11</b> — Full Screen  ·  <b>Ctrl+Alt+R</b> — System Recovery" },
                { sign: "Wander freely — I will be right where you left me.  — Glia" }
            ]
        }
        if (key === "about-leapfrog") return {
            eyebrow: "a ledger and a pond",
            title: "Leap Frog",
            blocks: [
                { lead: "Leap Frog is your planner — a ledger of days and a pond of reminders, kept at the foot of the screen." },
                { p: "Plato the frog lives there. He tends the pond and knows every lily pad by name. He will show you around. Open the Leap Frog bar at the bottom of the screen and tap <b>Sit by the Pond</b> for his full operating manual." },
                { sign: "Hop lightly.  — Plato" }
            ]
        }
        return { eyebrow: "", title: "", blocks: [] }
    }

    // ── entrance fade + scale ────────────────────────────────────────────────
    opacity: 0
    Behavior on opacity { NumberAnimation { duration: 220; easing.type: Easing.OutCubic } }
    onVisibleChanged: opacity = visible ? 1 : 0

    Item {
        anchors.fill: parent
        scale: win.opacity < 1 ? 0.97 : 1.0
        transformOrigin: Item.Center
        Behavior on scale { NumberAnimation { duration: 220; easing.type: Easing.OutCubic } }

        // ── parchment surface ────────────────────────────────────────────────
        NCDEParchmentSurface { anchors.fill: parent; cornerRadius: 16 }

        // ── frontispiece ─────────────────────────────────────────────────────
        Column {
            id: frontPiece
            anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
            anchors.topMargin: 32
            anchors.leftMargin: 40; anchors.rightMargin: 40
            spacing: 0

            // N-crest circle
            Rectangle {
                width: 68; height: 68; radius: 34
                anchors.horizontalCenter: parent.horizontalCenter
                gradient: Gradient {
                    GradientStop { position: 0.0;  color: k.gilt4 }
                    GradientStop { position: 0.65; color: k.gilt2 }
                    GradientStop { position: 1.0;  color: k.gilt0 }
                }
                border.color: k.gilt0; border.width: 2
                // outer glow ring
                Rectangle {
                    anchors.centerIn: parent
                    width: parent.width + 10; height: parent.height + 10
                    radius: (parent.width + 10) / 2
                    color: "transparent"
                    border.color: Qt.rgba(k.gilt4.r, k.gilt4.g, k.gilt4.b, 0.28)
                    border.width: 4
                    z: -1
                }
                Text {
                    anchors.centerIn: parent
                    text: "N"; font.family: k.display; font.bold: true
                    font.pixelSize: theme.scale(28); color: k.wine1
                }
            }

            Item { width: 1; height: 14 }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: win.content.title || ""
                font.family: k.display; font.bold: true
                font.pixelSize: theme.scale(30); color: k.wine2
                font.letterSpacing: 1
            }

            Item { width: 1; height: 6 }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: win.content.eyebrow || ""
                font.family: k.fell; font.italic: true
                font.pixelSize: theme.scale(14); color: win.parchInk; opacity: 0.6
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

        // ── scrollable body ──────────────────────────────────────────────────
        Flickable {
            id: flick
            anchors.top: frontPiece.bottom
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            anchors.leftMargin: 44; anchors.rightMargin: 40
            anchors.bottomMargin: 28
            clip: true; contentWidth: width; contentHeight: body.implicitHeight
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: body
                width: flick.width
                spacing: 0

                Repeater {
                    model: win.content.blocks || []

                    delegate: Column {
                        width: body.width; spacing: 0

                        // ── pre-spacing ──
                        Item {
                            width: 1
                            height: modelData.rule ? 14
                                  : modelData.kicker ? 12
                                  : 0
                        }

                        // ── kicker label ──
                        Text {
                            visible: !!modelData.kicker
                            height: visible ? implicitHeight + 3 : 0
                            width: parent.width
                            text: modelData.kicker || ""
                            font.family: k.titles; font.pixelSize: theme.scale(11)
                            font.letterSpacing: 3; color: k.gilt1
                            textFormat: Text.PlainText
                        }

                        // ── section heading ──
                        Text {
                            visible: !!modelData.h
                            height: visible ? implicitHeight + 5 : 0
                            width: parent.width
                            text: modelData.h || ""
                            font.family: k.display; font.bold: true
                            font.pixelSize: theme.scale(21); color: k.wine2
                            textFormat: Text.PlainText; wrapMode: Text.WordWrap
                        }

                        // ── lead paragraph (fell italic) ──
                        Text {
                            visible: !!modelData.lead
                            height: visible ? implicitHeight + 8 : 0
                            width: parent.width
                            text: modelData.lead || ""
                            font.family: k.fell; font.italic: true
                            font.pixelSize: theme.scale(16); color: win.parchInk
                            textFormat: Text.PlainText; wrapMode: Text.WordWrap
                            lineHeight: 1.45
                        }

                        // ── body paragraph (EB Garamond, rich text) ──
                        Text {
                            visible: !!modelData.p
                            height: visible ? implicitHeight + 10 : 0
                            width: parent.width
                            text: modelData.p || ""
                            font.family: k.gar; font.pixelSize: theme.scale(15)
                            color: win.parchInk
                            textFormat: Text.RichText; wrapMode: Text.WordWrap
                            lineHeight: 1.55
                        }

                        // ── horizontal rule ──
                        Rectangle {
                            visible: !!modelData.rule
                            height: visible ? 1 : 0; width: parent.width
                            gradient: Gradient { orientation: Gradient.Horizontal
                                GradientStop { position: 0.0;  color: "transparent" }
                                GradientStop { position: 0.18; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.45) }
                                GradientStop { position: 0.82; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.45) }
                                GradientStop { position: 1.0;  color: "transparent" }
                            }
                        }

                        // ── sign-off ──
                        Text {
                            visible: !!modelData.sign
                            height: visible ? implicitHeight + 14 : 0
                            width: parent.width
                            text: modelData.sign || ""
                            font.family: k.fell; font.italic: true
                            font.pixelSize: theme.scale(15); color: k.wine4
                            horizontalAlignment: Text.AlignHCenter
                            topPadding: 10
                        }
                    }
                }

                Item { width: 1; height: 28 }
            }

            // slim gold scrollbar
            Rectangle {
                anchors.right: parent.right; anchors.rightMargin: -8
                width: 3; radius: 1.5
                color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.55)
                visible: flick.contentHeight > flick.height
                height: flick.height * (flick.height / flick.contentHeight)
                y: flick.contentHeight > flick.height
                   ? (flick.contentY / (flick.contentHeight - flick.height)) * (flick.height - height)
                   : 0
            }
        }

        // ── close jewel (burgundy faceted diamond + ivory X) ─────────────────
        Item {
            width: 30; height: 30
            anchors.top: parent.top; anchors.right: parent.right
            anchors.topMargin: 14; anchors.rightMargin: 16

            Canvas {
                anchors.fill: parent
                renderStrategy: Canvas.Cooperative
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
            TapHandler { onTapped: win.hide() }
        }
    }
}
