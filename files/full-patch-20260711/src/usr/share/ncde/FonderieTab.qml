// ╔══════════════════════════════════════════════════════════════════════╗
// ║  FonderieTab.qml — "La Fonderie" ledger for NCDE Command.               ║
// ║  One ornate gilt frame; every repo font is a row set in its own face;   ║
// ║  tap a row to install it (pacman/yay) + fc-cache, then it's set before  ║
// ║  every NCDE app. Bound to the `fontMgr` context property (FontManager). ║
// ║                                                                        ║
// ║  Preview honesty: a row renders in its REAL face once installed (Qt can ║
// ║  resolve it); before that it shows the family NAME in NCDE's own serif  ║
// ║  plus category/weights — and re-renders in the true face the instant    ║
// ║  fontMgr.fontInstalled fires.                                           ║
// ║                                                                        ║
// ║  Lélan: TapHandler/HoverHandler only; no MouseArea; no Timer; integer   ║
// ║  font.pixelSize. Colours from ncde.* (falls back to the dark base).     ║
// ╚══════════════════════════════════════════════════════════════════════╝
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: tab
    clip: true

    // ── palette (ncde.* with dark fallbacks) ─────────────────────────────
    QtObject {
        id: k
        function c(n,f){ return (typeof ncde!=="undefined" && ncde[n]!==undefined && ncde[n]!==null) ? ncde[n] : f }
        readonly property color panel:  c("panelBg","#0c0907")
        readonly property color panel2: c("panelBg2","#0a0806")
        readonly property color surface:c("surface","#171009")
        readonly property color surface2:c("surface2",ncde.surface)
        readonly property color g0:ncde.gilt0; readonly property color g1:ncde.gilt1
        readonly property color g2:ncde.gilt2; readonly property color g3:ncde.gilt3
        readonly property color g4:ncde.gilt4; readonly property color g5:ncde.gilt5
        readonly property color wine1:ncde.wine1; readonly property color wine3:ncde.wine3; readonly property color wine4:ncde.wine4
        readonly property color verd:ncde.verd
        readonly property color ink: c("panelText",ncde.surface)
        readonly property color inkSoft:ncde.foreground; readonly property color inkDim:ncde.foreground
        readonly property string display:ncde.displayFont
        readonly property string titles:ncde.titleFont; readonly property string serif:ncde.bodyFont
        readonly property string fell:"IM Fell English"; readonly property string gar:"EB Garamond"
    }

    property string filter: "all"
    property string query: ""
    property string pendingPkg: ""
    property var families: (typeof fontMgr!=="undefined") ? fontMgr.families() : []
    function resolvable(fam){ return families.indexOf(fam) >= 0 }
    function catLabel(c){ return ({serif:"Serif",sans:"Sans",display:"Display",script:"Script",
        mono:"Monospace",black:"Blackletter",world:"World",biblical:"Biblical & Academic"})[c] || c }
    function pangram(c){ return ({
        serif:"Sphinx of black quartz, judge my vow",
        sans:"How vexingly quick daft zebras jump",
        display:"Pack my box with five dozen jugs",
        script:"Waltz, bad nymph, for quick jigs vex",
        mono:"ncde@poseidon ~ $ ls -la ~/Documents",
        black:"Zwei flinke Boxer jagen die Quadriga",
        world:"The quick brown fox leaps the lazy dog",
        biblical:"Ἐν ἀρχῇ ἦν ὁ λόγος — αβγδεζηθι · אבגדהוז"
    })[c] || "The quick brown fox leaps over the lazy dog" }

    Component.onCompleted: if (typeof fontMgr!=="undefined" && fontMgr.total===0) fontMgr.refresh()
    Connections {
        target: (typeof fontMgr!=="undefined") ? fontMgr : null
        function onFontsChanged(){ tab.families = fontMgr.families() }
        function onFontInstalled(pkg, family){ tab.families = fontMgr.families(); toast.show(family + " is ready — every app can use it now.") }
        // fontMgr.busy already exists and already works (drives the status-foot dot below);
        // it just was never wired to the row buttons themselves. Clear pendingPkg whenever a
        // font operation (install or remove) finishes, success or failure.
        function onBusyChanged(){ if (!fontMgr.busy) tab.pendingPkg = "" }
    }

    Column {
        anchors.fill: parent; spacing: 0

        // ── category strip ───────────────────────────────────────────────
        Rectangle {
            width: parent.width; height: 52; color: k.panel2
            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: k.g1 }
            Flickable {
                x: 20; y: 12
                width: parent.width - 202
                height: 28; clip: true
                contentWidth: chipRow.implicitWidth; contentHeight: 28
                Row {
                    id: chipRow
                    height: 28; spacing: 7
                    Repeater {
                        model: [ {c:"all",n:"All"}, {c:"serif",n:"Serif"}, {c:"sans",n:"Sans"}, {c:"display",n:"Display"},
                                 {c:"script",n:"Script"}, {c:"mono",n:"Monospace"}, {c:"black",n:"Blackletter"},
                                 {c:"biblical",n:"Scriptorium Dei"}, {c:"installed",n:"Installed"} ]
                        Rectangle {
                            height: 28; width: pl.implicitWidth + 26; radius: 14
                            property bool on: tab.filter === modelData.c
                            border.color: on ? k.g0 : k.g1; border.width: 1.5
                            gradient: Gradient { orientation: Gradient.Vertical
                                GradientStop { position: 0; color: on ? k.g4 : k.surface }
                                GradientStop { position: 1; color: on ? k.g3 : k.surface } }
                            Text { id: pl; anchors.centerIn: parent; text: modelData.n
                                   font.family: k.titles; font.pixelSize: SetTheme.sm; color: on ? k.wine1 : k.g2 }
                            HoverHandler { id: ph }
                            TapHandler { onTapped: tab.filter = modelData.c }
                        }
                    }
                }
            }
            // search
            Rectangle {
                id: searchRect
                anchors.right: parent.right; anchors.rightMargin: 20; anchors.verticalCenter: parent.verticalCenter
                width: 150; height: 30; radius: 15; color: "transparent"; clip: true; border.color: k.g1; border.width: 1.5
                Row { anchors.fill: parent; anchors.leftMargin: 13; anchors.rightMargin: 13; spacing: 8
                    Text { text:"\u26b2"; color: k.g2; font.pixelSize: SetTheme.md; anchors.verticalCenter: parent.verticalCenter }
                    TextInput { id: qIn; width: parent.width - 24; anchors.verticalCenter: parent.verticalCenter
                        font.family: k.serif; font.pixelSize: SetTheme.md; color: k.ink; clip: true; selectByMouse: true
                        onTextChanged: tab.query = text.toLowerCase().trim()
                        Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter; text:"Search faces…"
                               font.family: k.serif; font.italic: true; font.pixelSize: SetTheme.md; color: k.inkDim
                               visible: qIn.text.length===0 && !qIn.activeFocus } } }
            }
        }

        // ── the grand ornate ledger ──────────────────────────────────────
        Item {
            width: parent.width; height: parent.height - 52 - 30
            Rectangle {
                id: frame
                anchors.fill: parent; anchors.margins: 16; radius: 9
                color: k.surface; border.color: k.g2; border.width: 2
                gradient: Gradient { GradientStop { position: 0; color: k.surface } GradientStop { position: 1; color: k.panel2 } }
                Rectangle { anchors.fill: parent; anchors.margins: 5; radius: 5; color: "transparent"
                            border.color: k.g3; border.width: 1; opacity: 0.4; z: 3 }
                // corner florets
                Repeater { model: [ {x:-3,y:-3}, {x:frame.width-15,y:-3}, {x:-3,y:frame.height-15}, {x:frame.width-15,y:frame.height-15} ]
                    Rectangle { x: modelData.x; y: modelData.y; width: 18; height: 18; radius: 9; z: 4
                        border.color: k.g0; border.width: 1
                        gradient: Gradient { GradientStop { position: 0; color: k.g5 } GradientStop { position: 0.6; color: k.g3 } GradientStop { position: 1; color: k.g0 } } } }

                ListView {
                    id: list
                    anchors.fill: parent; anchors.margins: 6
                    clip: true; spacing: 0
                    ScrollBar.vertical: NCDEScrollBar {}
                    model: (typeof fontMgr!=="undefined") ? fontMgr.fonts : []

                    delegate: Item {
                        width: list.width
                        property var f: modelData
                        property bool show: {
                            var okC = tab.filter==="all" ? true
                                    : tab.filter==="installed" ? f.installed
                                    : f.category===tab.filter
                            var okQ = tab.query==="" || (""+f.family).toLowerCase().indexOf(tab.query) >= 0
                            return okC && okQ
                        }
                        height: show ? 78 : 0
                        visible: show
                        readonly property bool live: f.installed && tab.resolvable(f.family)

                        Rectangle {
                            anchors.fill: parent
                            color: rh.hovered ? Qt.rgba(0.79,0.54,0.23,0.12) : "transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: Qt.rgba(0.54,0.35,0.12,0.22) }

                            // specimen
                            Column {
                                anchors.left: parent.left; anchors.leftMargin: 22
                                anchors.verticalCenter: parent.verticalCenter
                                width: parent.width - 240; spacing: 1
                                Text {
                                    text: f.family
                                    font.family: parent.parent.live ? f.family : k.serif
                                    font.pixelSize: SetTheme.lg; color: rh.hovered ? ncde.surface : k.g5
                                    elide: Text.ElideRight; width: parent.width
                                }
                                Text {
                                    text: parent.parent.live ? tab.pangram(f.category)
                                          : (tab.catLabel(f.category) + " \u2014 preview after install")
                                    font.family: parent.parent.live ? f.family : k.fell
                                    font.italic: !parent.parent.live
                                    font.pixelSize: SetTheme.md; color: k.inkSoft
                                    elide: Text.ElideRight; width: parent.width
                                }
                            }

                            // meta + action
                            Column {
                                anchors.right: parent.right; anchors.rightMargin: 20
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 6; width: 200
                                Row {
                                    spacing: 8; anchors.right: parent.right
                                    Rectangle { height: 18; width: ct.implicitWidth+16; radius: 9; color: "transparent"
                                        border.color: k.g1; border.width: 1; anchors.verticalCenter: parent.verticalCenter
                                        Text { id: ct; anchors.centerIn: parent; text: tab.catLabel(f.category).toUpperCase()
                                               font.family: k.titles; font.pixelSize: SetTheme.sm; color: k.g3 } }
                                    Text { text: f.aur ? "AUR" : (f.repo!==undefined?(""+f.repo):"")
                                           font.family: k.gar; font.pixelSize: SetTheme.sm; color: k.inkDim
                                           anchors.verticalCenter: parent.verticalCenter }
                                }
                                Row {
                                    anchors.right: parent.right
                                    spacing: 8
                                    // REMOVE \u2014 installed rows only; wired to FontManager::removeFont(pkg)
                                    Rectangle {
                                        anchors.verticalCenter: parent.verticalCenter
                                        height: 28; width: rmT.implicitWidth + 26; radius: 14
                                        visible: f.installed && rh.hovered
                                        color: "transparent"; border.width: 1.5; border.color: k.wine1
                                        Text { id: rmT; anchors.centerIn: parent; text: "\u2715 Remove"
                                            font.family: k.titles; font.weight: Font.DemiBold; font.pixelSize: SetTheme.sm
                                            color: k.wine1 }
                                        TapHandler { gesturePolicy: TapHandler.ReleaseWithinBounds
                                            onTapped: { if (typeof fontMgr!=="undefined") fontMgr.removeFont(f.pkg) } }
                                    }
                                    Rectangle {
                                        anchors.verticalCenter: parent.verticalCenter
                                        height: 28; width: actT.implicitWidth + 26; radius: 14
                                        readonly property bool busyRow: tab.pendingPkg === f.pkg && (typeof fontMgr!=="undefined") && fontMgr.busy
                                        visible: f.installed || rh.hovered || busyRow
                                        border.width: 1.5
                                        border.color: f.installed ? k.verd : (f.aur ? k.wine1 : k.g0)
                                        opacity: busyRow ? 0.6 : 1.0
                                        gradient: Gradient { orientation: Gradient.Vertical
                                            GradientStop { position: 0; color: f.installed ? "transparent" : (f.aur ? k.wine3 : k.g4) }
                                            GradientStop { position: 1; color: f.installed ? "transparent" : (f.aur ? k.wine1 : k.g3) } }
                                        Text { id: actT; anchors.centerIn: parent
                                            text: parent.busyRow ? "Installing\u2026" : (f.installed ? "\u2713 Installed" : (f.aur ? "Install \u00b7 AUR" : "Install & Apply"))
                                            font.family: k.titles; font.weight: Font.DemiBold; font.pixelSize: SetTheme.sm
                                            color: f.installed ? k.verd : (f.aur ? k.g5 : k.wine1) }
                                    }
                                }
                            }

                            HoverHandler { id: rh }
                            TapHandler {
                                enabled: !(typeof fontMgr!=="undefined" && fontMgr.busy)
                                onTapped: {
                                    if (f.installed) { toast.show(f.family + " is already set before every app."); return }
                                    if (typeof fontMgr!=="undefined") { tab.pendingPkg = f.pkg; fontMgr.installFont(f.pkg) }
                                }
                            }
                        }
                    }

                    // empty state
                    Text {
                        anchors.centerIn: parent; visible: list.count===0
                        text: "No faces in this case."; font.family: k.serif; font.italic: true
                        font.pixelSize: SetTheme.lg; color: k.inkSoft
                    }
                }
            }
        }

        // ── status foot ──────────────────────────────────────────────────
        Rectangle {
            width: parent.width; height: 30; color: k.surface2
            Rectangle { anchors.top: parent.top; width: parent.width; height: 1; color: k.g1 }
            Row {
                anchors.left: parent.left; anchors.leftMargin: 20; anchors.verticalCenter: parent.verticalCenter; spacing: 12
                Rectangle { width: 7; height: 7; radius: 4; anchors.verticalCenter: parent.verticalCenter
                    color: (typeof fontMgr!=="undefined" && fontMgr.busy) ? k.g3 : k.verd }
                Text { text: (typeof fontMgr!=="undefined") ? fontMgr.status : "—"
                       font.family: k.fell; font.italic: true; font.pixelSize: SetTheme.sm; color: k.inkSoft
                       anchors.verticalCenter: parent.verticalCenter }
            }
            Text { anchors.right: parent.right; anchors.rightMargin: 20; anchors.verticalCenter: parent.verticalCenter
                   text: (typeof fontMgr!=="undefined") ? (fontMgr.installedCount + " of " + fontMgr.total + " installed") : ""
                   font.family: k.fell; font.italic: true; font.pixelSize: SetTheme.sm; color: k.inkSoft }
        }
    }

    // ── toast ────────────────────────────────────────────────────────────
    Rectangle {
        id: toast
        anchors.horizontalCenter: parent.horizontalCenter
        y: shown ? parent.height - 64 : parent.height + 20
        width: tt.implicitWidth + 40; height: 40; radius: 20; z: 60
        color: ncde.wine2; border.color: k.g3; border.width: 1.5
        property bool shown: false
        Behavior on y { NumberAnimation { duration: 260; easing.type: Easing.OutCubic } }
        Text { id: tt; anchors.centerIn: parent; text: ""; font.family: k.serif; font.pixelSize: SetTheme.lg; color: k.g5 }
        SequentialAnimation { id: hideAnim
            PauseAnimation { duration: 2600 }
            ScriptAction { script: toast.shown = false }
        }
        function show(m){ tt.text = m; shown = true; hideAnim.restart() }
    }
}
