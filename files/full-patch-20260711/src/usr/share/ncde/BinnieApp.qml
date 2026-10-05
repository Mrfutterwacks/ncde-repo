// BinnieApp.qml — Binnie, NCDE's trash app. The window Binnie lives in.
//
// Frameless PARCHMENT window with its own close jewel (no MotifFrame). Left: the
// stage where Binnie performs (BinnieCanvas) with a speech scroll + caption.
// Right: the freedesktop Trash list — each tossed file shows a 24h rewind ring;
// REWIND restores it, the bin glyph deletes it forever, EMPTY clears all, TOSS
// drops one in. Every action makes Binnie react.
//
// Backend: `binnieTrash` (BinnieTrash.cpp) provides the model + operations and
// emits changed(); this is a thin view over it. Pure QtQuick primitives +
// TapHandler/HoverHandler (no QtQuick.Controls), per NCDE rules.
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs
import NCDE.Glia

Window {
    id: app
    width: 980; height: 624
    minimumWidth: 760; minimumHeight: 520
    visible: true
    color: "transparent"
    title: "Binnie"
    flags: Qt.Window | Qt.FramelessWindowHint

    // ── GliaTalk global-menu publishing (2026-07-12) ─────────────────────
    // Binnie published NO _NCDE_MENUS (glia half-measure). Publish its real
    // menus via the shared NCDE.Glia plugin so they appear in the top-panel
    // global bar. Every id below maps to an EXISTING Binnie action (the same
    // handlers the on-screen buttons/close jewel call) — no new behavior.
    GliaTalkPublisher { id: glia }
    function handleGliaMenu(id) {
        if      (id === 101) tossPicker.open()          // Toss a File… (== TOSS A FILE)
        else if (id === 102) app.confirmEmptyOpen = true // Empty Binnie… (== EMPTY BINNIE)
        else if (id === 103) app.close()                 // Close (== close jewel)
    }
    function publishGliaMenus() {
        glia.attach(app)
        glia.menusJson = JSON.stringify([
            { title: "File", items: [
                { label: "Toss a File…", id: 101 },
                { label: "Empty Binnie…", id: 102 },
                { label: "Close",         id: 103 } ] }
        ])
    }
    Connections {
        target: glia
        function onInvoked(id) { app.handleGliaMenu(id) }
    }
    // 2026-07-05 audit: gate for the EMPTY BINNIE confirmation veil (one tap used
    // to permanently delete ALL trash with no confirmation — real data-loss risk).
    property bool confirmEmptyOpen: false
    Behavior on opacity { NumberAnimation { duration: 280 } }

    // where the animation cels live. Dev build bundles them at qrc:/anim/; in the
    // NCDE shell, set this to the on-disk folder (e.g. settings.assetBase + "/binnie/").
    property string binnieAssets: "qrc:/anim/"

    NCDEKit { id: k }
    // m = palette proxy passed to TrashRow / PillButton as pal:m
    QtObject {
        id: m
        readonly property color gold:     k.gilt4
        readonly property color goldSoft: Qt.rgba(k.gilt1.r, k.gilt1.g, k.gilt1.b, 0.25)
        readonly property color goldDeep: k.gilt1
        readonly property color gold1:    k.inkSoft
        readonly property color gold2:    k.gilt1
        readonly property color burg2:    k.wine2
        readonly property color burg4:    k.wine4
        readonly property color ink:      k.ink
        readonly property color cream:    k.surfaceHi
    }

    // palette — NCDEKit-wired, adapts light/dark
    readonly property color gold:     k.gilt4
    readonly property color goldSoft: Qt.rgba(k.gilt1.r, k.gilt1.g, k.gilt1.b, 0.25)
    readonly property color goldDeep: k.gilt1
    readonly property color burg2:    k.wine2
    readonly property color burg4:    k.wine4
    readonly property color ink:      k.ink
    readonly property color gold1:    k.inkSoft
    readonly property color cream:    k.surfaceHi
    property string fadeOrchideeDir: ""
    function fadeToOrchidee(dir) {
        fadeOrchideeDir = dir
        app.opacity = 0.0
        orchideeTimer.start()
    }

    readonly property var quips: ({
        poke:   ["Hé! You tickle ze couvercle, you cheeky one!",
                 "Oui oui, I am 'ere! Calme-toi, ma chérie.",
                 "Ohoho, doucement! Binnie is ticklish, eet is true."],
        restore:["Voilà! Rescued from ze abyss, ma chérie!",
                 "Back to ze future eet goes! Bravo, mon ami!",
                 "You 'ave excellent taste. Zis file, I liked 'im too!"],
        empty:  ["Miam miam! All gone. Binnie, 'e is très satisfait.",
                 "Pouf! Empty like ze dance floor at sunrise.",
                 "Hasta la vista, garbáge! Ohoho!"],
        toss:   ["Miam! Anuzzer morsel for Binnie. Merci!",
                 "Down ze hatch! Twenty-four hours to change your mind, oui?",
                 "Into ze bin you go, mon petit fichier. Bon appétit!"],
        forever:["Adieu, mon ami… gone for ze ever. *sniff*",
                 "Too late, ma chérie… ze twenty-four hours, zey 'ave passed.",
                 "I could not save 'im. Even Binnie, 'e 'as ze limits."],
        talk:   ["Bonjour, bonjour! Welcome to ze bin of Binnie!",
                 "Allow me — Binnie, gardien des ordures!"],
        talkFromOrchidee: [
                 "Ah, ma fille! She sends ze work already. Binnie, 'e is 'appy!",
                 "Glia! She deletes ze files, and Binnie, 'e must catch zem. Bien sûr.",
                 "Ohoho! Ze daughter, she 'as been busy today, non?"],
        receive:["Ah, ma fille! She sends ze orphans — bienvenu, mes petits!",
                 "Oho! Glia's darlings arrive. Binnie, 'e will take care of zem!"]
    })
    function pick(a){ return a[Math.floor(Math.random()*a.length)] }
    function speak(kind){
        binnie.react(kind)
        var q = quips[kind]; if (q) bubble.show(pick(q))
    }

    Rectangle { anchors.fill: parent; radius: 16; color: k.panelBg }
    NCDEVellum { anchors.fill: parent; base: "transparent"; intensity: 0.85 }

    // drag the frameless window by its body
    DragHandler {
        target: null
        onActiveChanged: if (active) app.startSystemMove()
    }

    Row {
        anchors.fill: parent
        anchors.margins: 2

        // ════ LEFT: Binnie's stage ════
        Item {
            id: stage
            width: 348; height: parent.height

            Rectangle {                                  // soft stage wash
                anchors.fill: parent
                anchors.rightMargin: 1
                gradient: Gradient {
                    GradientStop { position: 0; color: k.dark ? Qt.rgba(0.12,0.08,0.04,0.55) : Qt.rgba(1,0.97,0.88,0.55) }
                    GradientStop { position: 1; color: k.dark ? Qt.rgba(0.07,0.04,0.02,0.35) : Qt.rgba(0.85,0.8,0.66,0.35) }
                }
                radius: 15
            }
            Rectangle { anchors.right: parent.right; width: 1; height: parent.height; color: app.goldDeep; opacity: 0.5 }

            // speech scroll
            Item {
                id: bubble
                property string text: ""
                property bool shown: false
                anchors.top: parent.top; anchors.topMargin: 14
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 36; height: cloud.height
                opacity: shown ? 1 : 0
                Behavior on opacity { NumberAnimation { duration: 200 } }
                function show(t){ text = t; shown = true; hideT.restart() }
                Timer { id: hideT; interval: 3800; onTriggered: bubble.shown = false }

                Rectangle {
                    id: cloud
                    width: parent.width; radius: 16
                    height: msg.implicitHeight + 24
                    color: k.surfaceHi; border.width: 2; border.color: k.dark ? k.gilt1 : "#37231a"
                    Text {
                        id: msg; anchors.centerIn: parent
                        width: parent.width - 28
                        text: bubble.text; wrapMode: Text.WordWrap; horizontalAlignment: Text.AlignHCenter
                        font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; lineHeight: theme.lineHeight; font.italic: true
                        font.pixelSize: theme.fontMedium; color: app.burg4
                    }
                }
            }

            // Binnie himself
            BinnieCanvas {
                id: binnie
                assetBase: app.binnieAssets
                anchors.top: bubble.bottom; anchors.topMargin: 2
                anchors.bottom: cap.top
                anchors.left: parent.left; anchors.right: parent.right
                TapHandler { onTapped: app.speak("poke") }
            }

            // invisible layout spacer — real text content keeps cap.height identical
            // to the original so binnie.bottom: cap.top is unchanged
            Column {
                id: cap
                visible: false
                anchors.bottom: parent.bottom; anchors.bottomMargin: 16
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 2
                Text { text: "BINNIE"
                       font.family: theme.titleFont; font.bold: true; font.letterSpacing: 2
                       font.pixelSize: theme.fontMedium }
                Text { text: "all that is left of CDE — now he lives"
                       font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; font.italic: true
                       font.pixelSize: theme.fontSmall + theme.scale(1) }
                Text { text: "with his daughter, Glia"
                       font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; font.italic: true
                       font.pixelSize: theme.fontSmall + theme.scale(1) }
            }

            // caption above Binnie's head
            Column {
                z: 1
                anchors.top: bubble.bottom; anchors.topMargin: 6
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 2
                Text { anchors.horizontalCenter: parent.horizontalCenter; text: "BINNIE"
                       font.family: theme.titleFont; font.bold: true; font.letterSpacing: 2
                       font.pixelSize: theme.fontMedium; color: k.dark ? k.gilt4 : app.burg4 }
                Text { anchors.horizontalCenter: parent.horizontalCenter
                       text: "all that is left of CDE — now he lives"; horizontalAlignment: Text.AlignHCenter
                       font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; font.italic: true
                       font.pixelSize: theme.fontSmall + theme.scale(1); color: k.dark ? k.gilt3 : app.burg2 }
                Text { anchors.horizontalCenter: parent.horizontalCenter
                       text: "with his daughter, Glia"; horizontalAlignment: Text.AlignHCenter
                       font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; font.italic: true
                       font.pixelSize: theme.fontSmall + theme.scale(1); color: k.dark ? k.gilt3 : app.burg2 }
            }
        }

        // ════ RIGHT: the trash ════
        Item {
            width: parent.width - stage.width; height: parent.height

            // header
            Item {
                id: head
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                height: 54
                Column {
                    anchors.left: parent.left; anchors.leftMargin: 18
                    anchors.verticalCenter: parent.verticalCenter; spacing: 1
                    Text { text: "Recently Tossed"; font.family: theme.titleFont
                           font.pixelSize: theme.fontMedium + theme.scale(2); color: app.burg4 }
                    Text { text: (binnieTrash.items.length || 0) + " in the bin — rewind within "
                                 + binnieTrash.rewindHours + "h"
                           font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; font.italic: true
                           font.pixelSize: theme.fontSmall; color: app.gold1 }
                }
                Row {
                    anchors.right: parent.right; anchors.rightMargin: 56
                    anchors.verticalCenter: parent.verticalCenter; spacing: 10
                    PillButton { pal: m; label: "TOSS A FILE"; primary: false
                        // 2026-07-05 audit: was a demo button trashing invented /tmp
                        // paths — now a real picker (the drag/drop + file-manager
                        // routes into binnieTrash.trash(path) are unchanged).
                        onClicked: tossPicker.open() }
                    PillButton { pal: m; label: "EMPTY BINNIE"; primary: true
                        onClicked: app.confirmEmptyOpen = true }
                }
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: app.goldDeep; opacity: 0.6 }
            }

            // list
            ListView {
                id: list
                anchors.top: head.bottom; anchors.bottom: parent.bottom
                anchors.left: parent.left; anchors.right: parent.right
                anchors.margins: 10
                clip: true; spacing: 2
                model: binnieTrash.items
                delegate: TrashRow {
                    pal: m
                    win: app
                    width: list.width
                    entry: modelData
                    onRewind: {
                        var destDir = modelData.path || ""
                        binnieTrash.restore(modelData.name)
                        win.speak("restore")
                        if (destDir !== "") win.fadeToOrchidee(destDir)
                    }
                    onForever: { binnieTrash.remove(modelData.name); win.speak("forever") }
                }
                Text {
                    anchors.centerIn: parent; visible: list.count === 0
                    text: "Binnie, 'e is empty, ma chérie.\nNothing to rewind… for now."
                    horizontalAlignment: Text.AlignHCenter
                    font.family: theme.fontFamily; font.weight: settings.fontWeight; font.letterSpacing: theme.letterSpacing; font.italic: true
                    font.pixelSize: theme.fontMedium; color: app.gold1
                }
            }
        }
    }

    // ── close jewel (burgundy diamond + ivory X) ──
    Item {
        width: 30; height: 30
        anchors.top: parent.top; anchors.right: parent.right
        anchors.topMargin: 14; anchors.rightMargin: 16
        Canvas {
            anchors.fill: parent; renderStrategy: Canvas.Cooperative
            property bool hov: closeHov.hovered
            onHovChanged: requestPaint()
            onPaint: {
                var ctx = getContext("2d"); ctx.reset()
                var cx = width/2, cy = height/2, r = width/2 - 2
                ctx.beginPath(); ctx.moveTo(cx,cy-r); ctx.lineTo(cx+r,cy); ctx.lineTo(cx,cy+r); ctx.lineTo(cx-r,cy); ctx.closePath()
                ctx.fillStyle = hov ? k.wine4 : k.wine2; ctx.fill()
                ctx.strokeStyle = hov ? k.gilt4 : k.gilt3; ctx.lineWidth = 1.5; ctx.stroke()
                ctx.strokeStyle = k.surface; ctx.lineWidth = 1.8; ctx.lineCap = "round"
                var d = r*0.42
                ctx.beginPath(); ctx.moveTo(cx-d,cy-d); ctx.lineTo(cx+d,cy+d); ctx.moveTo(cx+d,cy-d); ctx.lineTo(cx-d,cy+d); ctx.stroke()
            }
        }
        HoverHandler { id: closeHov }
        TapHandler { onTapped: app.close() }
    }

    // greeting
    Component.onCompleted: { app.publishGliaMenus(); greetT.start() }
    Timer {
        id: greetT; interval: 700
        onTriggered: {
            binnie.react("talk")
            var q = (typeof fromOrchidee !== "undefined" && fromOrchidee)
                    ? app.quips.talkFromOrchidee : app.quips.talk
            bubble.show(app.pick(q))
        }
    }

    // Orchidée → Binnie: animate when external file arrives in trash
    Connections {
        target: binnieTrash
        function onItemsReceived() {
            binnie.react("toss")
            bubble.show(app.pick(app.quips.receive))
        }
    }

    // fade-switch to Orchidée after REWIND
    Timer { id: orchideeTimer; interval: 330; onTriggered: { binnieTrash.launchOrchidee(app.fadeOrchideeDir); closeTimer.start() } }
    Timer { id: closeTimer;    interval: 60;  onTriggered: app.close() }

    // Real "toss a file" picker (2026-07-05 audit — replaced the demoFile() stub
    // that trashed invented /tmp paths).
    FileDialog {
        id: tossPicker
        title: "Choose files to toss into Binnie"
        fileMode: FileDialog.OpenFiles
        onAccepted: {
            for (var i = 0; i < selectedFiles.length; i++)
                binnieTrash.trash(decodeURIComponent(String(selectedFiles[i]).replace(/^file:\/\//, "")))
            app.speak("toss")
        }
    }

    // EMPTY BINNIE confirmation veil — mirrors verve-text's unsaved-changes guard
    // (the established NCDE confirm pattern), binnie's own tokens.
    Rectangle {
        anchors.fill: parent; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.5); visible: app.confirmEmptyOpen; z: 70
        TapHandler { }
        Rectangle {
            anchors.centerIn: parent; width: 460; height: 180; radius: 10
            color: k.surfaceHi; border.color: k.gilt0; border.width: 2
            Column {
                anchors.fill: parent; anchors.margins: 24; spacing: 14
                Text { text: "Empty Binnie?"; font.family: k.display; font.bold: true; font.pixelSize: Math.round(18 * (theme.fontMedium / 13.0)); color: k.rose }
                Text { text: (binnieTrash.items.length || 0) + " item(s) will be gone for good — this cannot be rewound."
                       font.family: k.serif; font.pixelSize: Math.round(16 * (theme.fontMedium / 13.0)); color: k.ink; width: parent.width; wrapMode: Text.WordWrap }
                Row { spacing: 10; anchors.right: parent.right
                    Rectangle { width: 100; height: 34; radius: 17; color: "transparent"; border.color: k.gilt1; border.width: 1.5
                        Text{ anchors.centerIn: parent; text: "Cancel"; font.family: k.titles; font.pixelSize: Math.round(13 * (theme.fontMedium / 13.0)); color: k.inkLabel }
                        TapHandler{ onTapped: app.confirmEmptyOpen = false } }
                    Rectangle { width: 140; height: 34; radius: 17; border.color: k.rose; border.width: 1.5
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{ position: 0; color: k.rose } GradientStop{ position: 1; color: k.wine4 } }
                        Text{ anchors.centerIn: parent; text: "Empty Binnie"; font.family: k.titles; font.pixelSize: Math.round(13 * (theme.fontMedium / 13.0)); color: k.surfaceHi }
                        TapHandler{ onTapped: { app.confirmEmptyOpen = false; binnieTrash.emptyAll(); app.speak("empty") } } }
                }
            }
        }
    }
}
