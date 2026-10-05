// NCDEHandbook.qml — the NCDE Operating Manual, as a digital book.
// Left chapter rail + right content area. Glia narrates throughout.
// One page per chapter; each app gets a brief intro + pointer to its own guide.
// Opened by GliaGlobalMenus "NCDE Handbook" — wired in TopPanel.qml.
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

        // 0 · WELCOME
        { tab: "Welcome",
          eyebrow: "your new home · Poseidon",
          title: "Welcome to NCDE",
          blocks: [
            { lead: "A friend of mine — Debbie D. Bus — built this beautiful place and left me here to keep it for you. She had to move along, deep into the machine where I cannot follow. But before she left, she handed me the keys and said: look after them." },
            { p: "You are standing in <b>NCDE</b> — New Common Desktop Environment. This is your home now. The walls are warm, the windows are leaded, and everything works the way a good house should — quietly, reliably, waiting for you. Nothing here requires a command line or a config file. You will never need to be a technician to live well in this house." },
            { rule: true },
            { kicker: "WHO WILL HELP YOU" },
            { h: "Your guides" },
            { p: "Every room in this house has a guide — a character who knows it best and will show you around. <b>Agatha</b> is the mistress of the Settings wing; she has arranged every colour and preference personally. <b>Plato</b> the frog tends the calendar at the foot of the screen. <b>Petal</b> the hummingbird carries your post. <b>Poe</b> the raven carries your messages across the room. <b>Veronica</b> will help you write. <b>Edmund</b> keeps the numbers. <b>Lord Nigel</b> runs the software centre with all the fervour of a Victorian explorer. His wife, <b>Lady Lucrezia</b>, tends the type foundry within. <b>Verda</b> tends the warm kitchen. <b>GiGi</b> presides over the résumé atelier. And <b>Vesper</b> -- Agatha's great-grand-nephew -- watches from the dark so the rest of us can sleep. I keep the keys to all of it." },
            { p: "Each guide has their own operating manual inside their own program. Tap their menu and look for the door — it will have their name on it." },
            { sign: "I am Glia — and this is your home." }
          ]
        },

        // 1 · THE MENU BAR
        { tab: "Menu Bar",
          eyebrow: "the bar at the top",
          title: "Glia's Menu",
          blocks: [
            { lead: "Move your hand to the top of the screen and I appear — the long stripe of menus that stretches from corner to corner. When you step away, I fold back out of the light." },
            { kicker: "THE N MARK" },
            { h: "The house menu" },
            { p: "The letter <b>N</b> at the far left is my drawer-pull. Tap it and the house menu opens: <b>Meet Glia</b> (my introduction), <b>Settings</b> (every preference in the house), <b>Lock Screen</b> for stepping away, and <b>Log Out</b>." },
            { rule: true },
            { kicker: "APPLICATIONS · PLACES · SYSTEM" },
            { h: "The three doors" },
            { p: "<b>Applications</b> holds every program on this machine sorted into groups — tap one to open it, or use <b>Run Command</b> (Alt+F2) to type a name directly. <b>Places</b> takes you straight to your rooms: Home, Documents, Downloads, Pictures, Music, and Binnie the Trash. <b>System</b> covers Preferences (appearance, display, keyboard, mouse), Administration (users, network, time), and the session controls — Lock, Log Out, Shut Down." },
            { rule: true },
            { kicker: "FILE · EDIT · VIEW" },
            { h: "Always within reach — and they listen" },
            { p: "Toward the right end of the bar: <b>File</b> (New, Open, Open Recent, Save, Close), <b>Edit</b> (Undo, Redo, Cut, Copy, Paste, Select All), and <b>View</b> (Zoom In, Zoom Out, Full Screen). These are always there whether a window is open or not — File opens Orchidée's rooms, and Zoom truly grows the words in your browser and your documents." },
            { p: "And here is the house's quiet marvel: when one of our own programs stands in front, <b>its real menus take the bar</b>. Bring Orchidée forward and File and View become <i>her</i> File and View — New Folder, Rename, Toss to Bin, her views and her Bin — spoken directly to her, not guessed at. Step to another window and the bar returns to its usual self. No other house does this the way ours does." },
            { rule: true },
            { kicker: "INTELLIHIDE" },
            { h: "The bar gets out of the way" },
            { p: "When a window covers the top of the screen I fold myself away so you have the full room. Move your hand to the very top edge and I reappear at once. I will always come back." }
          ]
        },

        // 2 · THE DESKTOP
        { tab: "Desktop",
          eyebrow: "the room itself",
          title: "Your Desktop",
          blocks: [
            { lead: "The desktop is the room you return to. Everything starts here and comes back here." },
            { kicker: "THE WALLPAPER" },
            { h: "The view from the window" },
            { p: "The wallpaper dresses the whole room. Right-click anywhere on it to open a quick menu — change the wallpaper, open a program, or bring up Settings. The wallpaper is set in full in <b>Settings → Wallpapers</b>." },
            { rule: true },
            { kicker: "THE WIDGETS" },
            { h: "The right column" },
            { p: "A column of live widgets sits on the right side of the desktop: a <b>clock</b> with the date, the <b>weather</b> for your location, <b>system stats</b> (processor, memory, and disk), and <b>Salon Nocturne</b> — the music player, which can play what is on the desk or your own collection. The widgets breathe with the wallpaper's colour." },
            { rule: true },
            { kicker: "THE DOCK" },
            { h: "The left edge" },
            { p: "The dock hides on the left edge of the screen. Hover to bring it out. Each icon opens a program; a small light beneath it means the program is already running. Right-click any icon to pin it, unpin it, or open a new window." },
            { rule: true },
            { kicker: "WINDOWS" },
            { h: "Opening and moving things" },
            { p: "Every window <b>opens filling the room</b> — one thing at a time, the way work deserves. The three jewels in the title bar: the gold one <b>minimises</b>, the teal one <b>maximises</b>, the wine one <b>closes</b>. Open windows show their titles in the <b>task strip</b> at the bottom; click a title to bring it forward, click again to tuck it away. Press <b>F1</b> or <b>Super</b> for Exposé — a bird's-eye view of all open windows." },
            { rule: true },
            { kicker: "THE TILE GRID" },
            { h: "Working with several at once" },
            { p: "Un-maximise a window and it takes a place in the <b>tile grid</b> — up to eight windows, four above and four below, each in its own pane. Hold a tiled window's title bar and <b>drag it over another pane</b>: the others make way, and you may arrange the grid to your liking. Maximise any tile and it returns to filling the room. One window alone, un-maximised, sits as a modest centred window — as it should." }
          ]
        },

        // 3 · YOUR GUIDES
        { tab: "Your Guides",
          eyebrow: "the characters of the house",
          title: "Meet Your Guides",
          blocks: [
            { lead: "Every program in this house has someone who knows it best. Here is who to look for and where to find them." },
            { kicker: "SETTINGS" },
            { h: "Agatha -- The Settings panel" },
            { p: "Agatha is the mistress of the Settings wing -- every colour, font, screen arrangement, and notification rule passes through her. She has arranged things personally and she has opinions about all of it. Tap <b>Consult the Operating Manual</b> in the About tab and she opens her twelve-chapter book." },
            { rule: true },
            { kicker: "THE CALENDAR" },
            { h: "Plato — Leap Frog Ledger" },
            { p: "Plato is a wise frog who lives at the pond at the foot of your screen. He keeps your appointments, tasks, and reminders in five views: Month, Week, Day, Year, and Agenda. Tap <b>Sit by the Pond</b> in the Leap Frog bar and he will show you around his home." },
            { rule: true },
            { kicker: "YOUR POST" },
            { h: "Petal — Hummingbird Courier" },
            { p: "Petal the hummingbird carries your correspondence. She connects to Gmail, Outlook, or any mail account. Open Hummingbird Courier and look for the <b>Operating Manual</b> in its sidebar — Petal will walk you through stationery, the writing desk, and your address book." },
            { rule: true },
            { kicker: "THE FILES & THE BIN" },
            { h: "Glia &amp; Papa Binnie — Orchidée and the Bin" },
            { p: "I did mention this is my house — and <b>Orchidée</b> is my own room, the file manager. Browse in columns, grid, or list; <b>drag anything onto a folder, a place, or the tree</b> and it moves; press <b>Ctrl+H</b> and the shy dotfiles step into the light. Start typing in a list and I will jump to the match. Rename with <b>F2</b>, cut, copy and paste with the usual keys, and <b>Ctrl+Z</b> unwinds your last move or toss." },
            { p: "My father, <b>Binnie</b>, keeps the Bin. Toss a file — the Delete key, the TOSS jewel, or a drag onto the Bin — and Papa holds it for a full day: <b>REWIND</b> puts it back where it lived, or drag it out of the Bin into any folder you please. Nothing is gone until Papa lets it go. And do not worry about the house itself: neither of us will ever toss the walls — the system's own rooms are sealed against accidents." },
            { p: "Should you truly need to work inside the house's own rooms, press <b>Ctrl+Alt+E</b> — the <b>Sovereign Seal</b>. The gilt fleur appears in Orchidée's bar, the house asks for your password, and for a short while your hands hold the keys. It seals itself again; the keys are never left lying about." },
            { rule: true },
            { kicker: "MESSAGES NEAR & FAR" },
            { h: "Poe — Magpie Talker" },
            { p: "Poe the raven carries messages <b>across the room and across the world</b>. In the same building he finds your people all by himself, no internet needed; and on the <b>world band</b> he reaches your circle wherever they are — a congregation across town or a friend across the ocean — by callsign, like a good ham radio. His voice is his own: theatrical, literary, absolutely delighted by the whole enterprise. Open Magpie Talker and tap the <b>?</b> in its title bar when you are ready to hear from him." },
            { rule: true },
            { kicker: "WRITING" },
            { h: "Veronica — Verve" },
            { p: "Veronica is very excited you opened a new document. She guides you through L'Écritoire — the writing desk — with its ruled paper sheet, document picker, find and replace, zoom, and autosave. Tap the <b>?</b> in Verve's title bar and she will take it from there." },
            { rule: true },
            { kicker: "THE CALCULATOR" },
            { h: "Edmund — Abacus" },
            { p: "Edmund Cratchett, Senior Accountant, keeps the numbers. He is precise, he is formal, and he has very strong opinions about division by zero. Open Abacus from the dock and tap the <b>?</b> in the title bar for his briefing." },
            { rule: true },
            { kicker: "THE SOFTWARE CENTRE" },
            { h: "Lord Nigel — NCDECommand" },
            { p: "Lord Nigel is a Victorian explorer of extraordinary conviction — every software installation is a trek across uncharted ground, every update a dispatch from the frontier. NCDECommand is his base camp and the NCDE software centre: browse the full catalogue of available programs, install what you need, remove what you don't, and collect updates as they arrive. His celestial status bar watches the sky — a star for idle, the sun while an expedition is underway, the moon when it is safely concluded. Open NCDECommand from the dock and consult his field journal for the complete expedition briefing." },
            { rule: true },
            { kicker: "THE TYPE FOUNDRY" },
            { h: "Lady Lucrezia La Fonderie — Fonts" },
            { p: "While Lord Nigel is off mapping rivers, Lady Lucrezia La Fonderie minds the type foundry — the Fonts section inside NCDECommand. Browse available typefaces by name or style, install them with one tap, and remove what you no longer need. Every face is rendered in its own hand so you can see exactly what you are choosing. Lady Lucrezia keeps immaculate records and will not permit a sloppy font on the premises." },
            { rule: true },
            { kicker: "THE WARM KITCHEN" },
            { h: "Verda Teminae — the terminal" },
            { p: "Verda is la abuela of the NCDE house — the warm kitchen where plain words get things done. The terminal is there for those who want to speak directly to the machine. Verda is patient and will not hurry you. Press <b>F1</b> inside the terminal for her keyboard guide." },
            { rule: true },
            { kicker: "THE ATELIER" },
            { h: "GiGi — VerdantFolio" },
            { p: "GiGi presides over the atelier — VerdantFolio, the résumé studio. She does not believe in lists; she believes in portraits. A résumé, in her hands, becomes something a person would actually want to read. GiGi keeps her own handbook inside VerdantFolio — open the program and look for the door with her name on it." },
            { rule: true },
            { kicker: "SECURITY" },
            { h: "Vesper" },
            { p: "Vesper is Agatha's great-grand-nephew — though you would not know they were related at a glance. Where Agatha keeps the parlour warm, Vesper keeps watch in the dark. He guards this machine: monitoring every file that arrives, every process that runs, every connection that tries to leave. When something needs your attention, his window appears — green on black, a phosphor terminal from another world. He tells you what he found. You decide what to do. He never lectures. He never pads. When Vesper speaks, listen."  }
          ]
        },

        // 4 · APPEARANCE
        { tab: "Appearance",
          eyebrow: "settings — appearance",
          title: "How the House Looks",
          blocks: [
            { lead: "Everything that governs the colour, glass, type, and art of the desktop lives in the Appearance wing of Settings." },
            { kicker: "WALLPAPERS" },
            { h: "Dressing the desk" },
            { p: "Choose a wallpaper from the built-in gallery or tap <b>Browse</b> to use your own picture. Set the fit mode — fill, fit, centre, tile, or span. Turn on the <b>slideshow</b> to rotate a folder on a timer you choose. <b>Theme from Wallpaper</b> samples the picture and hands its colour to Filigree, so the whole shell breathes with the image behind it." },
            { rule: true },
            { kicker: "FILIGREE" },
            { h: "Colour, glass, and the whole look" },
            { p: "Filigree is the visual-design authority. Turn the <b>colour wheel</b> and a five-tone palette is drawn beneath it — Ground, Surface, Accent, Highlight, and Quill (the text colour). <b>Harmony</b> offers single, complementary, triadic, or analogous schemes. <b>Contrast Guard</b> checks live that text stays readable. Tap <b>Apply as Theme</b> to dress the shell." },
            { p: "Glass settings per surface — Panels, Dock, Widgets, and Menus each take their own <b>Tint, Shine, Glow,</b> and <b>Border</b>, or press <b>Link all to accent</b> to keep them of one cloth. Palettes may be named and saved." },
            { rule: true },
            { kicker: "FONTS" },
            { h: "Typefaces and scale" },
            { p: "Set the <b>Interface</b> face (menus and titles), the <b>Document</b> face (reading), and the <b>Fixed-width</b> face (terminal and code). Adjust the size scale and UI scale. The colour of type is set next door in Filigree." },
            { rule: true },
            { kicker: "SCREENSAVER" },
            { h: "Les Saisons Nocturnes" },
            { p: "Four generative seasonal paintings play after the screen has been idle for a set time — blossoms in Spring, fireflies in Summer, embers in Autumn, frost in Winter. The screensaver locks the screen; your password returns it." }
          ]
        },

        // 5 · DEVICES
        { tab: "Devices",
          eyebrow: "settings — devices",
          title: "Your Machine",
          blocks: [
            { lead: "Display, input, sound, power, storage, and network — the machine and all its senses." },
            { kicker: "DISPLAY" },
            { h: "Screens and Night Light" },
            { p: "Arrange your screens by sight, name a primary, and set each one's resolution, refresh rate, scale, and orientation. <b>Night Light</b> warms the screen after sunset — NCDE finds your timezone from the network and follows the sun automatically." },
            { rule: true },
            { kicker: "INPUT" },
            { h: "Keyboard, mouse, touchpad" },
            { p: "Set your keyboard layout (a second may be added for a second language), repeat delay and rate. For mouse and touchpad: pointer speed, natural scroll, tap-to-click, disable-while-typing. Cursor size may be small, medium, or large." },
            { rule: true },
            { kicker: "SOUND" },
            { h: "Audio in and out" },
            { p: "Choose the output device (speakers or headphones), its volume and balance. Choose the input device (microphone) and check the live level. A <b>per-application mixer</b> lets one program sing while another is muted." },
            { rule: true },
            { kicker: "POWER" },
            { h: "Sleep and the lid" },
            { p: "Two columns — on battery and plugged in — set when the screen dims and when the machine sleeps. Set what the lid does when closed and what the power button does when pressed." },
            { rule: true },
            { kicker: "STORAGE & NETWORK" },
            { h: "Drives and connections" },
            { p: "<b>Storage</b> shows your built-in drive and any connected USB sticks or external disks. Tap Mount or Unmount to manage them; always unmount before pulling a drive out. <b>Network</b> connects you to Wi-Fi or a wired connection and reconnects automatically when a known network is in range. <b>Bluetooth</b> pairs headphones, keyboards, and other devices." }
          ]
        },

        // 6 · SYSTEM SETTINGS
        { tab: "System",
          eyebrow: "settings — system",
          title: "Running the House",
          blocks: [
            { lead: "Users, time, notifications, session, and the full account of this machine." },
            { kicker: "USERS & GROUPS" },
            { h: "Who lives here" },
            { p: "Add or remove the people who use this machine. Each person gets their own password, home folder, and settings. An <b>administrator</b> account can change anything; a <b>standard</b> account can only change its own settings." },
            { rule: true },
            { kicker: "DATE & TIME" },
            { h: "The clock keeps itself" },
            { p: "NCDE finds your timezone from the network — a pin on the map confirms the location. The clock stays true with network time. Hour format may be 12-hour, 24-hour, or Auto. Travel to another city and the clock follows. Tap <b>Set manually</b> for a fixed zone." },
            { rule: true },
            { kicker: "NOTIFICATIONS" },
            { h: "Quiet the room" },
            { p: "<b>Do Not Disturb</b> silences all notices at once. <b>Quiet Hours</b> sets a nightly span when only an alarm may speak. Each application has its own on/off switch, so Petal may call while La Fonderie stays quiet. Choose which corner banners appear in." },
            { rule: true },
            { kicker: "SESSION" },
            { h: "Starting up and winding down" },
            { p: "<b>Autostart</b> lists programs that wake with you at login — add a name and switch it on. <b>Default Applications</b> names your browser, mail, file manager, and terminal — used whenever NCDE needs to open a link or file. Lock and Log Out wait at the foot." },
            { rule: true },
            { kicker: "ABOUT" },
            { h: "Agatha -- This machine" },
            { p: "The About tab is Agatha's room -- she narrates the full Settings operating manual from there. It shows your NCDE version, compositor, and machine particulars: processor, memory, graphics, and disk. Tap <b>Consult the Operating Manual</b> and Agatha opens her book, twelve chapters covering every wing of the Settings panel." }
          ]
        },

        // 7 · RECOVERY
        { tab: "Recovery",
          eyebrow: "the safety net",
          title: "System Recovery",
          blocks: [
            { lead: "NCDE keeps seven rolling snapshots of itself — one taken at every startup. If something goes wrong, the repair is already here." },
            { kicker: "HOW TO RESTORE" },
            { h: "One button brings you back" },
            { p: "Press <b>Ctrl+Alt+R</b> at any time while on the desktop. A recovery window opens, showing a table of snapshots with their dates and sizes. Select the one you want, enter your password, and the restore runs in the background. A progress bar tracks completion. When it is finished, the machine restarts, good as new." },
            { rule: true },
            { kicker: "WHAT IS SAFE" },
            { h: "Your files are never touched" },
            { p: "The restore overwrites the <b>operating system</b> only. Your photos, documents, music, email, and calendar are kept entirely safe — the restore does not touch your home folder. Think of it as repainting the walls without moving the furniture." },
            { rule: true },
            { kicker: "NO DISC NEEDED" },
            { h: "Built into the house" },
            { p: "There is no recovery disc to find, no USB stick to boot from, and no technician to call. The snapshots live on a dedicated partition and the recovery tool lives in the running desktop. The repair is built into the house — it is always there when you need it." },
            { sign: "The house remembers itself.  — Glia" }
          ]
        },

        // 8 · SHORTCUTS
        { tab: "Shortcuts",
          eyebrow: "quick reference",
          title: "Quick Keys",
          blocks: [
            { lead: "The most useful keys in the house — all in one place." },
            { kicker: "WINDOWS" },
            { h: "Managing what is open" },
            { p: "<b>Alt+F4</b> — close the front window  ·  <b>F1</b> or <b>Super</b> — Exposé (see all open windows at once)  ·  <b>F11</b> — Full Screen  ·  <b>Alt+F2</b> — Run Command (open any program by name)" },
            { rule: true },
            { kicker: "THE HOUSE" },
            { h: "Glia and the system" },
            { p: "<b>Ctrl+,</b> — open Settings  ·  <b>Super+L</b> — Lock Screen  ·  <b>Ctrl+Alt+R</b> — System Recovery" },
            { rule: true },
            { kicker: "STANDARD WORK" },
            { h: "File, Edit, View" },
            { p: "<b>Ctrl+N</b> — New  ·  <b>Ctrl+O</b> — Open  ·  <b>Ctrl+S</b> — Save  ·  <b>Ctrl+Z</b> — Undo  ·  <b>Ctrl+Shift+Z</b> — Redo  ·  <b>Ctrl+X</b> — Cut  ·  <b>Ctrl+C</b> — Copy  ·  <b>Ctrl+V</b> — Paste  ·  <b>Ctrl+A</b> — Select All  ·  <b>Ctrl+W</b> — Close Window  ·  <b>Ctrl+=</b> — Zoom In  ·  <b>Ctrl+−</b> — Zoom Out  ·  <b>Ctrl+0</b> — Reset Zoom" },
            { rule: true },
            { kicker: "IN ORCHIDÉE" },
            { h: "My room's own keys" },
            { p: "<b>Ctrl+H</b> — show or tuck away hidden files  ·  <b>F2</b> — rename  ·  <b>Delete</b> — toss to the Bin  ·  <b>Ctrl+Z</b> — unwind the last move or toss  ·  <b>Ctrl+Alt+E</b> — the Sovereign Seal" },
            { sign: "Wander freely — I will be right where you left me.  — Glia" }
          ]
        },

        // 9 · SECURITY
        { tab: "Security",
          eyebrow: "vesper",
          title: "Vesper's Watch",
          blocks: [
            { lead: "I want to tell you about Vesper. He is Agatha's great-grand-nephew — and as different from her as the cold from the warm. But he is family, and he is the reason you will never need to worry about what moves in the dark corners of this machine." },
            { kicker: "WHO HE IS" },
            { h: "The void engineer" },
            { p: "Vesper is the security intelligence of NCDE. He monitors everything that runs, every file that arrives, every connection that tries to leave. He has been in the kernel since before most people knew what a kernel was. He knows every trick. He uses that knowledge to protect you." },
            { p: "You will not see him unless he has something to tell you. When he does appear, his world is nothing like mine — cold, green, a phosphor terminal from another era. The shift is the signal. It means: pay attention." },
            { rule: true },
            { kicker: "FIVE ENGINES, ONE VOICE" },
            { h: "What he watches" },
            { p: "Five security engines run quietly behind everything — scanning files, watching the network, checking every process against every known threat. They never address you. When any of them finds something, they tell Vesper. Vesper tells you. In his voice. In his terminal. You will never need to know what is underneath. You will only need to read what he wrote." },
            { rule: true },
            { kicker: "THE PARTNERSHIP" },
            { h: "He asks. You decide." },
            { p: "Vesper never acts alone — except when he has no choice. If something is actively running that must be stopped, he stops it first and tells you immediately. For everything else, he holds it and waits. He tells you what he found, in as few words as he needs, and then he waits for your decision." },
            { p: "Type <b>block</b> to quarantine it. Type <b>allow</b> if you trust it. Type <b>analyse</b> and he runs a full examination, streaming his findings into the terminal as he works. Ask him anything — <b>what is T1071?</b> — and he will answer." },
            { rule: true },
            { kicker: "QUARANTINE" },
            { h: "Nothing is destroyed" },
            { p: "Files Vesper quarantines are not deleted — they are held in isolation, permission-locked, safe. Type <b>quarantine</b> in his terminal to see everything he is holding and why. Restore anything caught by mistake. Delete permanently when you are certain. He keeps a record of every hash he has ever seen — he will recognise a threat the second time, without asking." },
            { sign: "He catches things in the dark and brings them into the light. You decide what to do with them.  — Glia" }
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

            // inner gilt inset line
            Rectangle {
                anchors.fill: parent; anchors.margins: 3
                radius: parent.radius - 2
                color: "transparent"
                border.color: Qt.rgba(k.gilt4.r, k.gilt4.g, k.gilt4.b, 0.18)
                border.width: 1
            }

            Column {
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                anchors.topMargin: 18
                spacing: 0

                // N monogram at top
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "N"; font.family: k.display; font.bold: true
                    font.pixelSize: theme.scale(22); color: k.gilt4
                    font.letterSpacing: 1
                    bottomPadding: 4
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "NCDE"; font.family: k.titles
                    font.pixelSize: theme.scale(9); color: k.gilt2
                    font.letterSpacing: 3; bottomPadding: 14
                }

                Rectangle {
                    width: parent.width - 24
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 1
                    gradient: Gradient { orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "transparent" }
                        GradientStop { position: 0.5; color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.5) }
                        GradientStop { position: 1.0; color: "transparent" }
                    }
                }
                Item { width: 1; height: 10 }

                // chapter buttons
                Repeater {
                    model: book.chapters

                    Item {
                        width: rail.width; height: 36
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
                                width: 3; radius: 1.5
                                color: k.gilt3
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: modelData.tab
                            font.family: k.titles
                            font.pixelSize: theme.scale(11)
                            font.bold: active
                            font.letterSpacing: active ? 1 : 0
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

            // chapter header
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

            // scrollable chapter body
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
                                width: parent.width
                                text: modelData.kicker || ""
                                font.family: k.titles; font.pixelSize: theme.scale(10)
                                font.letterSpacing: 3; color: k.gilt1
                            }
                            Text {
                                visible: !!modelData.h
                                height: visible ? implicitHeight + 4 : 0
                                width: parent.width
                                text: modelData.h || ""
                                font.family: k.display; font.bold: true
                                font.pixelSize: theme.scale(19); color: k.ink
                                wrapMode: Text.WordWrap
                            }
                            Text {
                                visible: !!modelData.lead
                                height: visible ? implicitHeight + 7 : 0
                                width: parent.width
                                text: modelData.lead || ""
                                font.family: k.fell; font.italic: true
                                font.pixelSize: theme.scale(15); color: book.parchInk
                                wrapMode: Text.WordWrap; lineHeight: 1.45
                            }
                            Text {
                                visible: !!modelData.p
                                height: visible ? implicitHeight + 9 : 0
                                width: parent.width
                                text: modelData.p || ""
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
                                width: parent.width
                                text: modelData.sign || ""
                                font.family: k.fell; font.italic: true
                                font.pixelSize: theme.scale(14); color: k.ink
                                horizontalAlignment: Text.AlignHCenter
                                topPadding: 8
                            }
                        }
                    }

                    Item { width: 1; height: 20 }
                }

                // slim gold scrollbar
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
            TapHandler { onTapped: book.hide() }
        }
    }
}
