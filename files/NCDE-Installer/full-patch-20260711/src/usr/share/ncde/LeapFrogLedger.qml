// LeapFrogLedger.qml — the full Leap Frog Ledger application (NCDE).
// Illuminated-manuscript calendar: Month / Week / Day / Year / Agenda + To-Do,
// with the appointment editor and Reminders. Canvas ornaments from cal-art.js,
// shared logic from cal-logic.js, data + persistence from C++ `calBackend`.
//
// Theme-integrated build: colours come from NCDEKit (k.*) so the window
// re-themes with Filigree; Pond/ledger-data ops use the `pond` backend and
// PondPopup; About loads LeapFrogManual.qml. Month/Week/Day/Year/Agenda + To-Do
// all fully wired.
//
// Run as a managed NCDE window (like NCDE Command). Register calBackend + pond
// in main.cpp and launch this as the root of a QQuickWindow, or load via Loader.

import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Effects
import "cal-logic.js" as Cal
import "cal-art.js"   as Art
import "ncde-color.js" as Col

Item {
    id: app
    anchors.fill: parent
    property date cursor: new Date()
    property string view: "month"
    readonly property color parch: k.surfaceAlt
    readonly property color ink: WallInk.inked(k.ink)
    // faint/burgundy read k's dark/light-ADAPTIVE tokens (not the raw gilt1/wine4 ramp) —
    // those stay a fixed dark hue always, so Filigree dark mode made this text unreadable
    // against a dark parchment background (2026-07-04 fix).
    readonly property color faint: WallInk.inked(k.inkLabel)
    readonly property color gold: k.gilt2
    readonly property color goldBr: k.gilt4
    readonly property color burgundy: k.lineWine
    readonly property color leaf: k.verd

    property real _startWinX: 0; property real _startWinY: 0
    property alias editorDlg: editor
    property alias remindersDlg: reminders
    property alias aboutDlg: aboutPanel
    property alias icsImportDlg: icsImportDialog
    property alias seasonDlg: seasonDlg
    signal closeRequested()
    function openFull() { Window.window.visible = true; Window.window.raise() }

    // last appointment opened for editing — read by GliaLeapFrogBar's
    // "Send as Hummingbird message…" action (calBackend.composeForHummingbird).
    // One choke-point: record the id, then open the editor. Every appointment
    // tap in Month/Week/Day/Agenda routes through here.
    property string selectedApptId: ""
    function editAppt(id) { selectedApptId = id; editor.openEdit(id) }

    // transient rail-status line (import/export feedback) — read by the notice Text in the rail;
    // also drives the CSS-fidelity .cal-toast slide-in card (toastRoot, near CalEditor below) —
    // both read the same _notice string, kept deliberately as one flat message (no separate
    // title/timestamp fields exist in the data model today, not invented here).
    property string _notice: ""
    function notice(msg) { app._notice = msg; noticeTimer.restart(); toastRoot.shown = true }
    Timer { id: noticeTimer; interval: 4000; onTriggered: { app._notice = ""; toastRoot.shown = false } }

    FileDialog {
        id: icsImportDialog
        title: "Import .ics"
        nameFilters: ["iCalendar files (*.ics)", "All files (*)"]
        onAccepted: {
            var path = icsImportDialog.selectedFile.toString().slice(7)
            var n = calBackend.importICSFromFile(path)
            app.notice(n + (n === 1 ? " appointment imported" : " appointments imported"))
            app.refresh()
        }
    }

    function appts() { return calBackend.appointments; }
    // Year mini-month cell count — ported verbatim from the prototype's cal-views.js
    // year(): 5 weeks (35 cells) when the month fits, else 6 (42). Was previously a
    // hardcoded 42 (always 6 rows) in this file.
    function yearMiniCellCount(year, monthIndex) {
        var lead = new Date(year, monthIndex, 1).getDay();
        var dim  = new Date(year, monthIndex+1, 0).getDate();
        return (lead + dim) > 35 ? 42 : 35;
    }
    function refresh() { pageBg.requestPaint(); headerArt.requestPaint(); emblem.requestPaint(); viewLoader.reload(); }
    Component.onCompleted: { refresh(); updateCtx() }
    // the header line follows every cursor/view change, not just the ‹ › buttons
    onCursorChanged: { updateCtx(); app._keepY = -1 }
    onViewChanged: { updateCtx(); app._keepY = -1 }

    // Week/Day scroll position survives a data refresh (moving a block used to fling
    // the grid back to midnight); a new date or view starts fresh (see _autoY).
    property real _keepY: -1
    function _autoY(firstMin) {
        var now = new Date()
        if (app.view === "day" ? Cal.sameDay(app.cursor, now)
                               : Cal.sameDay(Cal.startOfWeek(app.cursor), Cal.startOfWeek(now)))
            return Math.max(0, (now.getHours()*60 + now.getMinutes() - 90)/60*48)
        return Math.max(0, ((firstMin == null ? 7*60 : Math.min(firstMin, 7*60)) - 30)/60*48)
    }

    // "today" glows on the right day even when the Ledger stays open past midnight
    property string _todayIso: Cal.iso(new Date())
    Timer { interval: 30000; repeat: true; running: true
        onTriggered: { var t = Cal.iso(new Date()); if (t !== app._todayIso) { app._todayIso = t; app.refresh() } } }

    // Ctrl+N / Ctrl+T — the shortcuts the bottom-bar menu advertises
    Shortcut { sequence: "Ctrl+N"; onActivated: editor.openNew(app.cursor, 9*60) }
    Shortcut { sequence: "Ctrl+T"; onActivated: app.cursor = new Date() }
    Shortcut { sequence: "Escape"
        enabled: editor.visible || reminders.visible || aboutPanel.visible || loreDlg2.visible || seasonDlg.visible
        onActivated: { editor.visible = false; reminders.visible = false; aboutPanel.close(); loreDlg2.close(); seasonDlg.close() } }
    Connections { target: calBackend; function onChanged(){ app.refresh() } }
    // An Iris palette swap (or wallpaper ink) repaints the page, header and emblem
    // too; bindings follow on their own, Canvases only on requestPaint. Same hook
    // ClockCalendarPopup already has.
    Connections { target: ncde; function onThemeChanged(){ app.refresh() } }
    Connections { target: WallInk; function onInkSerialChanged(){ app.refresh() } }

    NCDEKit { id: k }
    // Shared helper — was `theme ? theme.scale(N) : N` copy-pasted at ~50 call
    // sites. Identical formula, one definition; zero pixel-size change.
    function fpx(n) { return theme ? theme.scale(n) : n }

    // ── Parchment background ──
    Canvas {
        id: pageBg; anchors.fill: parent; renderStrategy: Canvas.Cooperative; layer.enabled: true
        onPaint: { var c=getContext("2d"); Art.CalArt.paintPage(c, width, height, k.dark, k.surface.toString(), k.surface2.toString()); }
    }

    // ── Layout ──
    ColumnLayout {
        anchors.fill: parent; spacing: 0

        // HEADER
        Rectangle {
            Layout.fillWidth: true; Layout.preferredHeight: 66; color: "transparent"
            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 2; color: app.gold }
            Canvas { id: emblem; width: 54; height: 54; x: 16; anchors.verticalCenter: parent.verticalCenter
                renderStrategy: Canvas.Cooperative; layer.enabled: true
                onPaint: { var c=getContext("2d"); c.clearRect(0,0,54,54); Art.CalArt.paintEmblem(c,27,23,18); } }
            Column {
                x: 80; anchors.verticalCenter: parent.verticalCenter; spacing: 2
                Text { text: "Leap Frog Ledger"; color: app.burgundy; font.family: theme?theme.titleFont:"serif"; font.pixelSize: k.fs(28); font.bold: true }
                Text { id: ctxLine; color: app.faint; font.italic: true; font.pixelSize: fpx(14)
                    text: Cal.MONTHS[app.cursor.getMonth()] + " " + app.cursor.getFullYear() }
            }
            Canvas { id: headerArt; width: 280; height: 60; anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top
                renderStrategy: Canvas.Cooperative; layer.enabled: true
                onPaint: { var c=getContext("2d"); c.clearRect(0,0,280,60); Art.CalArt.paintSeasonHeader(c,0,0,280,60,Cal.season(app.cursor.getMonth())); } }
            Row {
                anchors.right: parent.right; anchors.rightMargin: 52; anchors.verticalCenter: parent.verticalCenter; spacing: 6
                CalBtn { text:"‹"; onClicked: app.step(-1) }
                CalBtn { text:"TODAY"; onClicked: { app.cursor = new Date(); app.refresh(); app.updateCtx(); } }
                CalBtn { text:"›"; onClicked: app.step(1) }
                CalBtn { text:"✛ NEW"; accent:true; onClicked: editor.openNew(app.cursor, 9*60) }
            }

            // ── close button ──
            Item {
                z: 10; width: 28; height: 28
                anchors.right: parent.right; anchors.rightMargin: 12
                anchors.top: parent.top; anchors.topMargin: 8
                HoverHandler { id: ledgerCloseHov }
                TapHandler { grabPermissions: TapHandler.CanTakeOverFromAnything; onTapped: app.closeRequested() }
                Canvas {
                    id: ledgerCloseCanvas
                    anchors.fill: parent; enabled: false
                    Connections { target: ledgerCloseHov; function onHoveredChanged() { ledgerCloseCanvas.requestPaint() } }   // by id: `parent` here isn't the Canvas (2026-09-24)
                    Connections { target: ncde; function onThemeChanged() { ledgerCloseCanvas.requestPaint() } }
                    onPaint: {
                        var ctx = getContext("2d"); ctx.reset()
                        var hv = ledgerCloseHov.hovered; var r = 4
                        // still a red close button, in the palette's red (ncde-color.js)
                        ctx.fillStyle   = Col.css(Col.harmonize("#aa1800", k.accent, hv ? 46 : 38, 62, 0.1))
                        ctx.strokeStyle = Col.css(Col.harmonize("#cc3311", k.accent, hv ? 62 : 52, 62, 0.1))
                        ctx.lineWidth = 1.5
                        ctx.beginPath()
                        ctx.moveTo(r,0); ctx.lineTo(width-r,0); ctx.arcTo(width,0,width,r,r)
                        ctx.lineTo(width,height-r); ctx.arcTo(width,height,width-r,height,r)
                        ctx.lineTo(r,height); ctx.arcTo(0,height,0,height-r,r)
                        ctx.lineTo(0,r); ctx.arcTo(0,0,r,0,r)
                        ctx.closePath(); ctx.fill(); ctx.stroke()
                        ctx.strokeStyle = "#ffffff"; ctx.lineWidth = 2.2; ctx.lineCap = "round"
                        ctx.beginPath()
                        ctx.moveTo(8,8); ctx.lineTo(width-8,height-8)
                        ctx.moveTo(width-8,8); ctx.lineTo(8,height-8)
                        ctx.stroke()
                    }
                }
            }

            // ── drag zone — excludes rightmost 50px so close button gets events ──
            Item {
                x: 0; y: 0; width: parent.width - 50; height: parent.height; z: 8
                DragHandler {
                    target: null; dragThreshold: 4
                    grabPermissions: DragHandler.CanTakeOverFromAnything
                    onActiveChanged: {
                        if (active) {
                            app._startWinX = Window.window.x
                            app._startWinY = Window.window.y
                        } else {
                            // clamp to the REAL screen (2026-07-21: was hardcoded
                            // 1920x1200 — the dev monitor — wrong on every other
                            // machine this ISO installs to)
                            var w = Window.window
                            var sw = (w && w.screen) ? w.screen.width  : 1920
                            var sh = (w && w.screen) ? w.screen.height : 1200
                            w.x = Math.max(0, Math.min(sw - w.width,  w.x))
                            w.y = Math.max(0, Math.min(sh - w.height, w.y))
                        }
                    }
                    onTranslationChanged: {
                        Window.window.x = app._startWinX + translation.x
                        Window.window.y = app._startWinY + translation.y
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true; Layout.fillHeight: true; spacing: 0

            // LEFT RAIL
            Rectangle {
                Layout.preferredWidth: 168; Layout.fillHeight: true; color: "transparent"
                Rectangle { anchors.right: parent.right; height: parent.height; width: 2; color: app.gold }
                Flickable {
                    anchors.fill: parent; anchors.margins: 12; clip: true
                    contentWidth: width; contentHeight: railCol.height
                    // CSS ::-webkit-scrollbar{width:9px} thumb rgba(184,134,44,.5) radius5 — same rail-overflow fix as the to-do panel's ListView
                    ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded
                        contentItem: Rectangle { implicitWidth: 9; radius: 5; color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.5) } }
                    Column {
                        id: railCol
                        width: parent.width; spacing: 6
                        Repeater {
                        model: [["month","Month"],["week","Week"],["day","Day"],["year","Year"],["agenda","Agenda"]]
                        delegate: Rectangle {
                            id: navTab
                            readonly property bool active: app.view===modelData[0]
                            width: parent.width; height: 38; radius: 7
                            color: active ? Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 1) : (navHov.hovered ? Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.12) : "transparent")
                            border.color: active ? app.gold : "transparent"; border.width: 1.5
                            // CSS .cal-tab.active box-shadow: inset 0 0 0 1px rgba(110,79,23,.25) — the inset ring
                            Rectangle { anchors.fill: parent; anchors.margins: 1; radius: 6; color: "transparent"
                                visible: navTab.active; border.width: 1; border.color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.25) }
                            Row { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 12; spacing: 9
                                // CSS .cal-tab .tg — glow dot (box-shadow: 0 0 5px var(--gold-br))
                                Canvas {
                                    width: 12; height: 12; anchors.verticalCenter: parent.verticalCenter; visible: navTab.active
                                    renderStrategy: Canvas.Cooperative; layer.enabled: true
                                    onPaint: { var c = getContext("2d"); c.clearRect(0,0,12,12); Art.CalArt.paintGlowDot(c, 6, 6, 4.5, app.gold); }
                                }
                                Text { text: modelData[1].toUpperCase(); font.family: theme?theme.titleFont:"serif"
                                    font.pixelSize: fpx(13); font.letterSpacing: theme ? theme.letterSpacing : 2
                                    color: navTab.active ? app.ink : app.faint } }
                            HoverHandler { id: navHov }
                            TapHandler { onTapped: { app.view = modelData[0]; app.refresh(); app.updateCtx(); } }
                        }
                    }
                    Rectangle { width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.28) }
                    Rectangle { width: parent.width; height: 38; radius: 7; color: "transparent"; border.color: "transparent"
                        Row { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 12; spacing: 9
                            Rectangle { width:9; height:9; radius:5; color: app.burgundy; anchors.verticalCenter: parent.verticalCenter }
                            Text { text: "REMINDERS"; font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(13); font.letterSpacing: theme ? theme.letterSpacing : 2; color: app.faint } }
                        TapHandler { onTapped: reminders.open() }
                    }

                    // ── ICS import/export — the original calendar's own data ops (calBackend),
                    // distinct from the Pond's CSV/lily-pad export below. Was fully built in
                    // calBackend (importICS/importICSFromFile/exportICSToFile) but never reached
                    // any control here — restored 2026-07-04.
                    Rectangle { width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.28) }
                    RailItem { text: "IMPORT ICS…"; dot: app.gold; onClicked: icsImportDialog.open() }
                    RailItem { text: "EXPORT ICS…"; dot: app.gold
                        onClicked: {
                            var path = "/home/" + settings.userName + "/leapfrog.ics"
                            app.notice(calBackend.exportICSToFile(path) ? ("Exported to " + path) : "Export failed")
                        } }
                    Text { visible: !!app._notice; text: app._notice; width: parent.width; wrapMode: Text.WordWrap
                        color: app.faint; font.italic: true; font.pixelSize: fpx(11)
                        horizontalAlignment: Text.AlignHCenter }

                    // ── Pond / Ledger-data ops — mirrors the consolidated bottom-bar "Ledger" menu ──
                    Rectangle { width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.28) }
                    RailItem { text: "STOCK THE POND";       dot: app.leaf;     onClicked: pondPopup.openStock() }
                    RailItem { text: "TALLY THE LILY PADS";  dot: app.leaf;     onClicked: pondPopup.openTally() }
                    Rectangle { width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.28) }
                    RailItem { text: "EXPORT CSV…";          dot: app.gold;     onClicked: pond.exportCsv() }
                    RailItem { text: "EXPORT LILY-PAD…";     dot: app.gold;     onClicked: pond.exportLilyPad() }
                    Rectangle { width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.28) }
                    RailItem { text: "RECONCILE";            dot: app.gold;     onClicked: pond.reconcile() }
                    RailItem { text: "ARCHIVE PAST ENTRIES"; dot: app.gold;     onClicked: pond.archivePast() }
                    Rectangle { width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.28) }
                    RailItem { text: "SEASON CARD…";         dot: app.leaf;     onClicked: seasonDlg.open() }
                    RailItem { text: "SIT BY THE POND…";     dot: app.burgundy; onClicked: app.aboutDlg.open() }
                    }
                }
            }

            // MAIN VIEW
            Loader {
                id: viewLoader; Layout.fillWidth: true; Layout.fillHeight: true
                function reload(){ active=false; active=true }
                sourceComponent: app.view==="month" ? monthView
                               : app.view==="day"   ? dayView
                               : app.view==="agenda"? agendaView
                               : app.view==="year"  ? yearView
                               : app.view==="week"  ? weekView : monthView
            }

            // TO-DO PANEL
            Rectangle {
                Layout.preferredWidth: 248; Layout.fillHeight: true; color: "transparent"
                Rectangle { anchors.left: parent.left; height: parent.height; width: 2; color: app.gold }
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 12; spacing: 8
                    Text { text: "Tasks & Intentions"; color: app.burgundy; font.family: theme?theme.titleFont:"serif"
                        font.pixelSize: fpx(16); Layout.alignment: Qt.AlignHCenter }
                    RowLayout {
                        Layout.fillWidth: true; spacing: 5
                        TextField { id: todoInput; Layout.fillWidth: true; placeholderText: "Add a task…"
                            background: Rectangle { radius: 5; color: Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.8); border.color: app.gold; border.width: 1.5 }
                            color: app.ink; onAccepted: app.addTodo() }
                        CalBtn { text: "✛"; onClicked: app.addTodo() }
                    }
                    ListView {
                        id: todoList
                        Layout.fillWidth: true; Layout.fillHeight: true; clip: true; spacing: 2
                        model: calBackend.todos
                        Text { visible: todoList.count === 0; width: todoList.width; topPadding: 14
                            horizontalAlignment: Text.AlignHCenter; wrapMode: Text.WordWrap
                            text: "The reeds are empty.\nType an intention above and press Enter."
                            color: app.faint; font.italic: true; font.pixelSize: fpx(12) }
                        // CSS ::-webkit-scrollbar{width:9px} thumb rgba(184,134,44,.5) radius5
                        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded
                            contentItem: Rectangle { implicitWidth: 9; radius: 5; color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.5) } }
                        delegate: Rectangle {
                            id: todoRow
                            // 12px gutter: the scrollbar overlays the right edge and ate taps on ✕
                            width: ListView.view.width - 12; height: 34
                            color: todoHov.hovered ? Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.10) : "transparent"
                            // hover the whole row to reveal ✕ (2026-09-24: the hover lived on the
                            // invisible ✕ itself, so it could never appear — tasks were undeletable)
                            HoverHandler { id: todoHov }
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.2) }
                            Row { anchors.fill: parent; anchors.leftMargin: 4; anchors.rightMargin: 24; spacing: 8
                                Rectangle { width: 16; height: 16; radius: 4; anchors.verticalCenter: parent.verticalCenter
                                    border.color: app.gold; border.width: 1.5
                                    color: modelData.done ? app.gold : "transparent"
                                    Text { anchors.centerIn: parent; text: "✓"; color: k.surface; font.pixelSize: fpx(11); visible: modelData.done }
                                    TapHandler { onTapped: calBackend.toggleTodo(modelData.id) } }
                                Text { anchors.verticalCenter: parent.verticalCenter; text: modelData.text
                                    width: parent.width - 24; elide: Text.ElideRight
                                    font.family: theme?theme.fontFamily:"serif"; font.pixelSize: fpx(14)
                                    color: modelData.done ? app.faint : app.ink
                                    font.strikeout: modelData.done } }
                            Text { anchors.right: parent.right; anchors.rightMargin: 4; anchors.verticalCenter: parent.verticalCenter
                                width: 20; height: parent.height; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                                text: "✕"; color: dh.hovered ? app.burgundy : app.faint; visible: todoHov.hovered
                                font.pixelSize: fpx(13)
                                TapHandler { onTapped: calBackend.deleteTodo(modelData.id) }
                                HoverHandler { id: dh; cursorShape: Qt.PointingHandCursor } }
                        }
                    }
                }
            }
        }
    }

    function addTodo(){ var t = todoInput.text.trim(); if(t){ calBackend.upsertTodo({text:t,done:false,due:null,priority:0}); todoInput.text=""; } }
    function step(dir){
        var c = new Date(app.cursor);
        if (view==="year") c.setFullYear(c.getFullYear()+dir);
        else if (view==="week") c.setDate(c.getDate()+7*dir);
        else if (view==="day") c.setDate(c.getDate()+dir);
        else c.setMonth(c.getMonth()+dir);
        app.cursor = c; app.refresh(); app.updateCtx();
    }
    function updateCtx(){
        if (view==="year") ctxLine.text = app.cursor.getFullYear() + " · the whole pond";
        else if (view==="day") ctxLine.text = Cal.DOW_FULL[app.cursor.getDay()] + ", " + Cal.MONTHS[app.cursor.getMonth()] + " " + app.cursor.getDate();
        else if (view==="week") { var ws=Cal.startOfWeek(app.cursor); var we=Cal.addDays(ws,6); ctxLine.text = Cal.MONTHS[ws.getMonth()]+" "+ws.getDate()+" – "+Cal.MONTHS[we.getMonth()]+" "+we.getDate()+", "+we.getFullYear(); }
        else if (view==="agenda") ctxLine.text = "Agenda · the coming thirty days";
        else { var se=Cal.season(app.cursor.getMonth()); ctxLine.text = Cal.MONTHS[app.cursor.getMonth()]+" "+app.cursor.getFullYear()+" · "+Cal.ZODIAC_NAME[Cal.zodiacOfMonth(app.cursor.getMonth())]+" · "+se.charAt(0).toUpperCase()+se.slice(1); }
    }

    // ── Reusable button ──
    component CalBtn: Rectangle {
        property alias text: lbl.text
        property bool accent: false
        signal clicked()
        implicitWidth: lbl.implicitWidth + 22; implicitHeight: 30; radius: 6
        color: accent ? k.accent : k.surfaceHi
        border.color: app.gold; border.width: 1.5
        Text { id: lbl; anchors.centerIn: parent; font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(12); font.letterSpacing: theme ? theme.letterSpacing : 1
            color: parent.accent ? k.surface : app.ink }
        TapHandler { onTapped: parent.clicked() }
        HoverHandler { id: bh }
    }

    // ── Reusable side-rail menu row (Pond/Export/Reconcile/Archive/manual) ──
    component RailItem: Rectangle {
        id: ri
        property alias text: rlbl.text
        property color dot: app.burgundy
        signal clicked()
        width: parent.width; height: 32; radius: 7; color: rih.hovered ? Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.6) : "transparent"
        Row { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 12; anchors.right: parent.right; anchors.rightMargin: 10; spacing: 9
            Rectangle { width:9; height:9; radius:5; color: ri.dot; anchors.verticalCenter: parent.verticalCenter }
            Text { id: rlbl; width: parent.width - 9 - 9; elide: Text.ElideRight
                font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(13); font.letterSpacing: theme ? theme.letterSpacing : 2; color: app.faint } }
        HoverHandler { id: rih }
        TapHandler { onTapped: ri.clicked() }
    }

    // ── Week/Day time-block: move (vertical, same column) · resize (bottom handle) ──
    // Mirrors cal-app.js lines 102-172 exactly: SNAP=15min, PXH=48px/hour (already this
    // app's existing per-hour scale), move is vertical-only (no cross-column/day drag —
    // the prototype only ever changes .style.top, never re-parents into another column),
    // resize only changes end (min = start+SNAP), both commit via a single upsertAppointment
    // call carrying the full existing record with start/end updated (calendarbackend.h has
    // no separate move/resize method) and requestPaint the whole view via app.refresh().
    // Overlap is unhandled in the prototype too (no collision rejection) — matched as-is.
    component TimeBlock: Rectangle {
        id: tb
        property var apptData
        readonly property int  pxPerHour: 48
        readonly property int  snapMin: 15
        property real dragDY: 0
        property real dragEndDY: 0

        // overlapping blocks share the column side by side (Cal.layoutLanes sets _lane/_lanes)
        readonly property int lanes: Math.max(1, apptData._lanes || 1)
        readonly property real laneW: (parent.width - 6) / lanes
        x: 3 + (apptData._lane || 0) * laneW; width: laneW - (lanes > 1 ? 2 : 0)
        y: apptData.start/60*pxPerHour + dragDY
        height: Math.max(20, (apptData.end - apptData.start)/60*pxPerHour + dragEndDY)
        radius: 4
        color: Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, moveDrag.active ? 0.85 : 0.92)
        opacity: moveDrag.active ? 0.85 : 1.0   // CSS .cal-time-block.dragging opacity:0.85
        z: (moveDrag.active || resizeDrag.active) ? 20 : 1   // CSS .dragging z-index:20

        function _fullRecord() {
            var id = apptData._baseId || apptData.id
            var list = app.appts()
            for (var i=0;i<list.length;i++) if (list[i].id === id) return list[i]
            return null
        }
        function commitMove(newStartMin) {
            var full = tb._fullRecord(); if (!full) return
            var dur = full.end - full.start
            var s = Math.max(0, Math.min(24*60 - dur, newStartMin))
            var rec = Object.assign({}, full); rec.start = s; rec.end = s + dur
            calBackend.upsertAppointment(rec); app.notice("Moved “" + rec.title + "”"); app.refresh()
        }
        function commitResize(newEndMin) {
            var full = tb._fullRecord(); if (!full) return
            var rec = Object.assign({}, full); rec.end = Math.max(full.start + tb.snapMin, newEndMin)
            calBackend.upsertAppointment(rec); app.notice("Resized “" + rec.title + "”"); app.refresh()
        }

        Rectangle { width: 4; height: parent.height; radius: 2; color: Cal.cat(apptData.category, k).gem }
        Column { x: 9; y: 3; width: parent.width-12
            Text { text: Cal.fmtTime(apptData.start); color: Cal.cat(apptData.category, k).color; font.pixelSize: fpx(9); font.bold: true }
            Text { text: apptData.title; color: app.ink; font.pixelSize: fpx(12); font.bold: true; elide: Text.ElideRight; width: parent.width }
            Text { text: apptData.location||""; color: app.faint; font.italic: true; font.pixelSize: fpx(10); visible: !!apptData.location }
        }

        // ── move (vertical only — cal-app.js never touches horizontal position) ──
        DragHandler {
            id: moveDrag
            target: null
            dragThreshold: 3
            onActiveChanged: {
                if (!active) {
                    if (Math.abs(tb.dragDY) > 0) {
                        var deltaMin = Math.round((tb.dragDY / tb.pxPerHour) * 60 / tb.snapMin) * tb.snapMin
                        tb.commitMove(apptData.start + deltaMin)
                    }
                    tb.dragDY = 0
                }
            }
            onTranslationChanged: { if (active) tb.dragDY = translation.y }
        }
        // exclusive, so the empty-grid tap-to-create underneath doesn't also fire
        TapHandler { gesturePolicy: TapHandler.ReleaseWithinBounds
            onTapped: if (!moveDrag.active) app.editAppt(apptData._baseId||apptData.id) }

        // ── resize (CSS .cal-tb-resize — bottom 8px strip, cursor ns-resize) ──
        Item {
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            height: 8
            HoverHandler { cursorShape: Qt.SizeVerCursor }
            DragHandler {
                id: resizeDrag
                target: null
                onActiveChanged: {
                    if (!active) {
                        if (Math.abs(tb.dragEndDY) > 0) {
                            var deltaMin = Math.round((tb.dragEndDY / tb.pxPerHour) * 60 / tb.snapMin) * tb.snapMin
                            tb.commitResize(apptData.end + deltaMin)
                        }
                        tb.dragEndDY = 0
                    }
                }
                onTranslationChanged: { if (active) tb.dragEndDY = translation.y }
            }
        }
    }

    // ── Week/Day empty-column drag-to-create (cal-app.js "create" mode) — dragging on
    // empty grid area shows a dashed ghost, then opens the editor pre-filled with the
    // dragged start/end (does NOT silently insert — matches cal-app.js: newAppt() opens
    // the editor, the user still confirms via Save). ──
    component CreateDragArea: Item {
        id: cda
        property date colDate
        readonly property int pxPerHour: 48
        readonly property int snapMin: 15
        property bool dragging: false
        property real gS: 0; property real gE: 0   // ghost start/end (px)

        function _snap(px) {
            var raw = Math.max(0, Math.min(24*60, px/pxPerHour*60))
            return Math.round(raw/snapMin)*snapMin
        }

        Rectangle {
            visible: cda.dragging
            x: 0; width: parent.width; y: cda.gS/60*cda.pxPerHour; height: Math.max(4, (cda.gE-cda.gS)/60*cda.pxPerHour)
            radius: 4; color: Qt.rgba(k.accent.r, k.accent.g, k.accent.b, 0.22); border.width: 1.5; border.color: k.gilt2
            Canvas {
                anchors.fill: parent
                onPaint: { var c = getContext("2d"); c.clearRect(0,0,width,height); Art.CalArt.paintDashedFrame(c, width, height, k.gilt2) }
            }
        }

        // a plain tap on an empty hour opens the editor at that hour (the manual's
        // "tap any hour in Day or Week view" — only drag-to-create existed before)
        TapHandler {
            onTapped: function(ev) {
                var m = Math.floor(ev.position.y / cda.pxPerHour) * 60
                editor.openNew(cda.colDate, Math.min(m, 23*60), Math.min(m + 60, 23*60 + 59))
            }
        }

        DragHandler {
            id: createDrag
            target: null
            property real y0: 0
            onActiveChanged: {
                if (active) {
                    y0 = centroid.position.y
                    cda.gS = cda._snap(y0); cda.gE = cda.gS + cda.snapMin; cda.dragging = true
                } else {
                    cda.dragging = false
                    if (cda.gE - cda.gS >= cda.snapMin) editor.openNew(cda.colDate, cda.gS, cda.gE)
                }
            }
            onCentroidChanged: {
                if (!active) return
                var y = centroid.position.y
                var s = cda._snap(Math.min(y0, y)); var e = Math.max(s + cda.snapMin, cda._snap(Math.max(y0, y)))
                cda.gS = s; cda.gE = e
            }
        }
    }

    // ── Views ──
    Component {
        id: monthView
        Item {
            id: monthRoot
            // ── week-number gutter width — CSS: grid-template-columns:34px repeat(7,1fr) ──
            readonly property int wkGutter: 34
            Column {
                anchors.fill: parent; anchors.margins: 10; spacing: 3
                Row { width: parent.width; height: 20; spacing: 3
                    // CSS .cal-wk-corner — "Wk" label over the week-number gutter
                    Text { width: monthRoot.wkGutter; horizontalAlignment: Text.AlignHCenter; opacity: 0.7
                        text: "Wk"; color: app.faint; font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(9) }
                    Repeater { model: Cal.DOW; delegate: Text { width: (parent.width-monthRoot.wkGutter)/7; horizontalAlignment: Text.AlignHCenter
                        text: modelData.toUpperCase(); color: app.burgundy; font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(11); font.letterSpacing: theme ? theme.letterSpacing : 2 } }
                }
                Column {
                    id: monthBody
                    width: parent.width; height: parent.height - 26; spacing: 3
                    readonly property real rowH: (height - 5*3)/6
                    Repeater {
                        model: 6
                        delegate: Row {
                            id: weekRow
                            width: monthBody.width; height: monthBody.rowH; spacing: 3
                            property int wk: index
                            property date weekStart: Cal.addDays(Cal.startOfWeek(new Date(app.cursor.getFullYear(), app.cursor.getMonth(), 1)), wk*7)
                            // CSS .cal-wk-num — ISO week number for this row
                            Text { width: monthRoot.wkGutter; height: parent.height; topPadding: 5; horizontalAlignment: Text.AlignHCenter; opacity: 0.6
                                text: Cal.weekNumber(weekRow.weekStart); color: app.faint; font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(10) }
                            Repeater {
                                model: 7
                                delegate: Rectangle {
                                    id: dayCell
                                    width: (weekRow.width - monthRoot.wkGutter - 6*3)/7; height: weekRow.height; radius: 5
                                    property date cellDate: Cal.addDays(weekRow.weekStart, index)
                                    property bool inMonth: cellDate.getMonth() === app.cursor.getMonth()
                                    property bool isToday: Cal.iso(cellDate) === app._todayIso
                                    property bool isSel: inMonth && !isToday && Cal.sameDay(cellDate, app.cursor)
                                    property var dayAppts: Cal.apptsOn(app.appts(), cellDate)
                                    clip: true
                                    // CSS .cal-day{background:rgba(255,250,235,.45)} / :hover{.8} / .today{rgba(244,228,180,.7)}
                                    color: isToday ? Qt.rgba(k.gilt5.r, k.gilt5.g, k.gilt5.b, 0.7)
                                                   : Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, dayHov.hovered ? 0.8 : 0.45)
                                    opacity: inMonth ? 1 : 0.42
                                    // today = gold fill + ring; the selected day (where ✛ NEW lands) = burgundy ring
                                    border.color: isToday ? app.gold : (isSel ? app.burgundy : Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.28))
                                    border.width: (isToday || isSel) ? 2 : 1
                                    Row { x: 4; y: 3; width: parent.width-8; height: 16
                                        Text { text: dayCell.cellDate.getDate(); color: dayCell.isToday?app.burgundy:(dayCell.inMonth?app.ink:app.faint); font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(13); font.bold: true }
                                        Item { width: parent.width - 34; height: 1 }
                                        Canvas { width: 14; height: 14; anchors.verticalCenter: parent.verticalCenter
                                            renderStrategy: Canvas.Cooperative; layer.enabled: true
                                            onPaint: { var c=getContext("2d"); Art.CalArt.paintMoon(c,7,7,6,Cal.moonPhase(dayCell.cellDate)); } }
                                    }
                                    // CSS .cal-holiday — italic burgundy holiday name, one line.
                                    // Tap it to open the feast's lore card (operator ask, 2026-07-06).
                                    Text {
                                        x: 4; y: 19; width: parent.width-8; visible: !!Cal.holiday(dayCell.cellDate)
                                        text: Cal.holiday(dayCell.cellDate) || ""; elide: Text.ElideRight
                                        font.italic: true; font.pixelSize: fpx(10); color: app.burgundy
                                        font.underline: hh.hovered
                                        HoverHandler { id: hh }
                                        TapHandler { onTapped: loreDlg2.openFor(dayCell.cellDate) }
                                    }
                                    Column {
                                        x: 4; y: !!Cal.holiday(dayCell.cellDate) ? 33 : 22; width: parent.width-8; spacing: 2
                                        // up to three appointments, as the manual promises — then "+N more"
                                        Repeater {
                                            model: dayCell.dayAppts.slice(0,3)
                                            delegate: Rectangle {
                                                width: parent.width; height: 16; radius: 3
                                                color: Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.55)
                                                Rectangle { width: 3; height: parent.height; radius: 1; color: Cal.cat(modelData.category, k).gem }
                                                Text { x: 7; width: parent.width-9; anchors.verticalCenter: parent.verticalCenter; elide: Text.ElideRight
                                                    text: (modelData.allDay?"":Cal.fmtTime(modelData.start)+" ") + modelData.title
                                                    color: app.ink; font.family: theme?theme.fontFamily:"serif"; font.pixelSize: fpx(11) }
                                                // exclusive tap: a chip opens its appointment and nothing else
                                                // (the day cell underneath no longer also reacts to the same tap)
                                                TapHandler { gesturePolicy: TapHandler.ReleaseWithinBounds
                                                    onTapped: app.editAppt(modelData._baseId||modelData.id) }
                                            }
                                        }
                                        // CSS .cal-more — "+N more" overflow line; tap it to see the whole day
                                        Text {
                                            visible: dayCell.dayAppts.length > 3
                                            text: "+" + (dayCell.dayAppts.length - 3) + " more"
                                            font.italic: true; font.pixelSize: fpx(10); color: app.faint
                                            font.underline: moreHov.hovered
                                            HoverHandler { id: moreHov; cursorShape: Qt.PointingHandCursor }
                                            TapHandler { gesturePolicy: TapHandler.ReleaseWithinBounds
                                                onTapped: { app.cursor = dayCell.cellDate; app.view = "day"; app.refresh() } }
                                        }
                                    }
                                    HoverHandler { id: dayHov }
                                    // single tap selects (in-month only — selecting a grey neighbour-month day
                                    // re-laid the grid under the pointer, so a double-tap hit the wrong date);
                                    // double tap opens a new appointment on exactly this day
                                    TapHandler { onTapped: { if (dayCell.inMonth) app.cursor = dayCell.cellDate }
                                                 onDoubleTapped: editor.openNew(dayCell.cellDate, 9*60) }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: dayView
        Column {
            id: dayRoot
            width: parent.width; height: parent.height; spacing: 0
            readonly property var lore: Cal.holidayLore(app.cursor)
            // CSS .cal-allday-strip data — all-day appointments were previously filtered
            // out of Day view entirely with no UI to show them at all (2026-07-04 fix)
            readonly property var dayAllday: Cal.apptsOn(app.appts(), app.cursor).filter(function(a){ return a.allDay; })

            // ── "On this day" holiday-lore card — matches the original browser prototype's
            // .cal-holiday-card (cal-styles.css): gold border + a burgundy accent stripe on
            // the left edge (2026-07-04 fix; QML has no per-side border, so a thin Rectangle
            // fakes the stripe). ──
            Rectangle {
                width: parent.width; height: dayRoot.lore ? 58 : 0; visible: !!dayRoot.lore
                color: app.parch; border.color: app.gold; border.width: 1; radius: 4; clip: true
                Rectangle { anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
                    width: 4; color: app.burgundy }
                Row {
                    anchors.fill: parent; anchors.margins: 8; anchors.leftMargin: 12; spacing: 10
                    Canvas { width: 36; height: 36; anchors.verticalCenter: parent.verticalCenter
                        onPaint: { var c = getContext("2d"); c.clearRect(0,0,36,36)
                            Art.CalArt.paintHolidaySeal(c, 18, 18, 18, app.gold, k.gilt0, app.parch, app.burgundy) } }
                    Column {
                        anchors.verticalCenter: parent.verticalCenter; width: parent.width - 52; spacing: 1
                        Text { text: dayRoot.lore ? dayRoot.lore.name : ""; color: app.burgundy
                            font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(13); font.bold: true }
                        Text { text: dayRoot.lore ? dayRoot.lore.lore : ""; color: app.ink
                            font.family: k.serif; font.italic: true; font.pixelSize: fpx(12)
                            wrapMode: Text.WordWrap; width: parent.width; maximumLineCount: 2; elide: Text.ElideRight }
                    }
                }
            }

            // CSS .cal-allday-strip — non-scrolling row above the hourly grid, one gem-
            // colored pill per all-day appointment (Week view's equivalent is the per-
            // column .cal-allday-block, added in weekView below). 2026-07-04: previously
            // all-day appointments had no UI in Day/Week view at all — filtered straight
            // out of both grids with nowhere else to show them.
            Item {
                id: dayAllDayStrip
                width: parent.width
                visible: dayRoot.dayAllday.length > 0
                height: visible ? allDayFlow.implicitHeight + 10 : 0
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1
                    color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.3) }
                Flow {
                    id: allDayFlow
                    anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                    anchors.topMargin: 5; anchors.leftMargin: 10; anchors.rightMargin: 10
                    spacing: 6
                    Text { text: "ALL DAY"; font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(10)
                        font.letterSpacing: 1; color: app.faint; height: 20; verticalAlignment: Text.AlignVCenter }
                    Repeater {
                        model: dayRoot.dayAllday
                        delegate: Rectangle {
                            readonly property color gem: Cal.cat(modelData.category, k).gem
                            width: pillText.implicitWidth + 18; height: 20; radius: height/2; color: gem
                            Text { id: pillText; anchors.centerIn: parent; text: modelData.title; color: "#fff"; font.pixelSize: fpx(11) }
                            TapHandler { onTapped: app.editAppt(modelData._baseId||modelData.id) }
                        }
                    }
                }
            }

            Flickable {
                id: flickDay; width: parent.width; height: parent.height - (dayRoot.lore ? 58 : 0) - dayAllDayStrip.height; contentHeight: 24*48; clip: true
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded
                    contentItem: Rectangle { implicitWidth: 9; radius: 5; color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.5) } }
                // open on the morning (or on "now", for today) — not on midnight
                Component.onCompleted: {
                    var timed = Cal.apptsOn(app.appts(), app.cursor).filter(function(a){ return !a.allDay })
                    var y = app._keepY >= 0 ? app._keepY : app._autoY(timed.length ? timed[0].start : null)
                    // after layout, so the clamp uses the real viewport height
                    Qt.callLater(function() { contentY = Math.max(0, Math.min(y, contentHeight - height)) })
                }
                onContentYChanged: app._keepY = contentY
                Column {
                    Repeater { model: 24; delegate: Row { width: flickDay.width; height: 48
                        Text { width: 48; text: ((index%12)||12)+(index<12?" AM":" PM"); color: app.faint; font.pixelSize: fpx(9); horizontalAlignment: Text.AlignRight; rightPadding: 5 }
                        Rectangle { width: 1; height: 48; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.2) } } }
                }
                Item {
                    x: 49; width: parent.width-49; height: 24*48
                    CreateDragArea { anchors.fill: parent; colDate: app.cursor }
                    Repeater {
                        model: Cal.layoutLanes(Cal.apptsOn(app.appts(), app.cursor).filter(function(a){return !a.allDay;}))
                        delegate: TimeBlock { apptData: modelData }
                    }
                    // CSS .cal-nowline — burgundy 2px line + glow dot, today only (cal-app.js: nowMin/60*PXH)
                    Item {
                        id: dayNowLine
                        visible: Cal.iso(app.cursor) === app._todayIso
                        property real nowY: { var t = new Date(); return (t.getHours()*60 + t.getMinutes())/60*48; }
                        Timer { interval: 60000; running: dayNowLine.visible; repeat: true
                            onTriggered: { var t = new Date(); dayNowLine.nowY = (t.getHours()*60 + t.getMinutes())/60*48; } }
                        Rectangle { y: dayNowLine.nowY - 1; width: parent.width; height: 2; color: app.burgundy }
                        Canvas {
                            id: dayNowDot
                            x: -8; y: dayNowLine.nowY - 8; width: 16; height: 16
                            renderStrategy: Canvas.Cooperative; layer.enabled: true
                            onPaint: { var c = getContext("2d"); c.clearRect(0,0,16,16); Art.CalArt.paintGlowDot(c, 8, 8, 4, app.burgundy); }
                            Connections { target: dayNowLine; function onNowYChanged() { dayNowDot.requestPaint() } }   // by id, not `parent` (2026-09-24)
                        }
                    }
                }
            }
        }
    }

    Component {
        id: agendaView
        ListView {
            id: agendaList
            clip: true; anchors.fill: parent; anchors.margins: 12; spacing: 2
            Text { visible: agendaList.count === 0; width: agendaList.width; topPadding: 40
                horizontalAlignment: Text.AlignHCenter; wrapMode: Text.WordWrap
                text: "Nothing on the water for the next thirty days.\nTap ✛ NEW to inscribe something."
                color: app.faint; font.italic: true; font.pixelSize: fpx(15) }
            ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded
                contentItem: Rectangle { implicitWidth: 9; radius: 5; color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.5) } }
            model: {
                var from = new Date(app.cursor); from.setHours(0,0,0,0);
                var occ = Cal.occurrencesInRange(app.appts(), from, Cal.addDays(from,30));
                occ.sort(function(a,b){ var da=Cal.fromIso(a.date).getTime()+(a.allDay?0:a.start*60000); var db=Cal.fromIso(b.date).getTime()+(b.allDay?0:b.start*60000); return da-db; });
                return occ;
            }
            delegate: Rectangle {
                width: ListView.view.width; height: 44; color: "transparent"
                Row { anchors.fill: parent; anchors.leftMargin: 10; spacing: 10
                    // CSS .cal-ag-gem — box-shadow: 0 0 6px var(--gem) glow
                    Canvas {
                        width: 18; height: 18; anchors.verticalCenter: parent.verticalCenter
                        renderStrategy: Canvas.Cooperative; layer.enabled: true
                        onPaint: { var c = getContext("2d"); c.clearRect(0,0,18,18)
                            Art.CalArt.paintGlowDot(c, 9, 9, 5.5, Cal.cat(modelData.category, k).gem) }
                    }
                    Text { width: 110; anchors.verticalCenter: parent.verticalCenter; color: app.faint; font.pixelSize: fpx(11)
                        text: { var d=Cal.fromIso(modelData.date); return Cal.DOW[d.getDay()]+" "+Cal.MONTHS[d.getMonth()].slice(0,3)+" "+d.getDate()+"\n"+(modelData.allDay?"all day":Cal.fmtTime(modelData.start)); } }
                    Column { anchors.verticalCenter: parent.verticalCenter
                        Text { text: modelData.title; color: app.ink; font.pixelSize: fpx(16); font.bold: true }
                        Text { text: modelData.location||""; color: app.faint; font.italic: true; font.pixelSize: fpx(12); visible: !!modelData.location } } }
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.18) }
                TapHandler { onTapped: app.editAppt(modelData._baseId||modelData.id) }
            }
        }
    }

    Component {
        id: yearView
        // The whole year page scrolls: the 12-month grid sizes itself off the REAL available
        // width (the old build hardcoded 22×17px day cells — a large accessibility font scale
        // overran them and a small unmaxed window pushed the fixed 154px minis off screen),
        // and the year's feast days are listed beneath — tap one to open its lore.
        Flickable {
            id: yroot
            clip: true
            contentHeight: ycol.implicitHeight + 20
            ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded
                contentItem: Rectangle { implicitWidth: 9; radius: 5; color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.5) } }
            Column {
                id: ycol
                x: 10; y: 10; width: yroot.width - 20; spacing: 16
                Grid {
                    id: yg
                    width: parent.width
                    columns: 4; rowSpacing: 12; columnSpacing: 12
                    Repeater {
                        model: 12
                        delegate: Column {
                            id: mcol
                            width: Math.floor((yg.width - 3*yg.columnSpacing)/4); spacing: 2
                            property int monthIndex: index          // named — inner day-grid index must NOT be used as month
                            // day cells divide the mini-month's real width; text clamps to the cell
                            property int cellW: Math.max(11, Math.floor(width/7))
                            property int cellH: Math.max(10, Math.round(cellW*0.78))
                            property int cellFont: Math.max(7, Math.min(fpx(10), cellH - 3))
                            Row { spacing: 5
                                Canvas { width: 18; height: 18; renderStrategy: Canvas.Cooperative; layer.enabled: true
                                    onPaint: { var c=getContext("2d"); Art.CalArt.paintZodiac(c, Cal.zodiacOfMonth(monthIndex), 9,9,6, k.gilt2); } }
                                Text { text: Cal.MONTHS[monthIndex]; color: app.burgundy; font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(13); font.bold: true
                                       width: mcol.width - 23; elide: Text.ElideRight } }
                            Grid {
                                columns: 7
                                Repeater {
                                    model: app.yearMiniCellCount(app.cursor.getFullYear(), monthIndex)
                                    delegate: Item {
                                        width: mcol.cellW; height: mcol.cellH
                                        property date cd: Cal.addDays(Cal.startOfWeek(new Date(app.cursor.getFullYear(), monthIndex, 1)), model.index)
                                        property bool inM: cd.getMonth()===monthIndex
                                        property bool isT: Cal.iso(cd) === app._todayIso
                                        // CSS .cal-mini-day.has-appt::after — 3px dot, in-month days with appointments only
                                        property bool hasAppt: inM && Cal.apptsOn(app.appts(), cd).length > 0
                                        Rectangle { anchors.centerIn: parent; width: mcol.cellW - 4; height: mcol.cellH - 3; radius: 3; visible: isT; color: app.gold }
                                        Text { anchors.centerIn: parent; text: cd.getDate(); font.pixelSize: mcol.cellFont
                                            color: isT ? "#fff" : (inM ? app.ink : Qt.rgba(k.inkDim.r, k.inkDim.g, k.inkDim.b, 0.3)) }
                                        Rectangle {
                                            visible: hasAppt; anchors.bottom: parent.bottom; anchors.bottomMargin: 1
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width: 3; height: 3; radius: 1.5; color: app.burgundy
                                        }
                                    }
                                }
                            }
                            TapHandler { onTapped: { var c=new Date(app.cursor); c.setMonth(monthIndex); c.setDate(1); app.cursor=c; app.view="month"; app.refresh(); app.updateCtx(); } }
                        }
                    }
                }
                // ── Feasts & Holy Days of the year — listed; tap a row to open its lore ──
                Column {
                    width: parent.width; spacing: 0
                    // Fixed feasts + the computed Christian and Jewish holy days (2026-09-24):
                    // Cal.holidaysInYear() builds the whole year, already sorted.
                    property var feastRows: Cal.holidaysInYear(app.cursor.getFullYear())
                    Row {
                        spacing: 8; height: 34
                        Canvas { width: 22; height: 22; anchors.verticalCenter: parent.verticalCenter
                            renderStrategy: Canvas.Cooperative; layer.enabled: true
                            onPaint: { var c=getContext("2d"); c.clearRect(0,0,22,22); Art.CalArt.paintHolidaySeal(c, 11, 11, 11, app.gold, k.gilt0, app.parch, app.burgundy) } }
                        Text { text: "Feasts & Holy Days of " + app.cursor.getFullYear(); color: app.burgundy
                               font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(15); font.bold: true
                               anchors.verticalCenter: parent.verticalCenter }
                    }
                    Repeater {
                        model: parent.feastRows
                        delegate: Rectangle {
                            width: parent.width; height: 30
                            color: fh.hovered ? Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.14) : "transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1
                                        color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.22) }
                            Row {
                                anchors.verticalCenter: parent.verticalCenter; x: 6; spacing: 12
                                Text { text: Cal.MONTHS[modelData.d.getMonth()].slice(0,3) + " " + modelData.d.getDate()
                                       color: app.faint; font.family: theme?theme.titleFont:"serif"
                                       font.pixelSize: fpx(12); width: 52 }
                                Text { text: modelData.name; color: app.ink; font.italic: true
                                       font.pixelSize: fpx(13) }
                            }
                            Text { text: "open the lore ›"; anchors.right: parent.right; anchors.rightMargin: 8
                                   anchors.verticalCenter: parent.verticalCenter; visible: fh.hovered
                                   color: app.burgundy; font.italic: true; font.pixelSize: fpx(11) }
                            HoverHandler { id: fh }
                            TapHandler { onTapped: loreDlg2.openFor(modelData.d) }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: weekView
        Item {
            id: weekRoot
            property date weekStart: Cal.startOfWeek(app.cursor)
            Rectangle { anchors.fill: parent; color: k.surface; z: -1 }
            Flickable {
                anchors.fill: parent; id: flickWeek
                contentHeight: 28 + 24*48; clip: true
                boundsBehavior: Flickable.StopAtBounds
                Component.onCompleted: {
                    var first = null
                    for (var i = 0; i < 7; i++) {
                        var t = Cal.apptsOn(app.appts(), Cal.addDays(weekRoot.weekStart, i)).filter(function(a){ return !a.allDay })
                        if (t.length && (first === null || t[0].start < first)) first = t[0].start
                    }
                    var y = app._keepY >= 0 ? app._keepY : app._autoY(first)
                    // after layout, so the clamp uses the real viewport height
                    Qt.callLater(function() { contentY = Math.max(0, Math.min(y, contentHeight - height)) })
                }
                onContentYChanged: app._keepY = contentY
                // CSS ::-webkit-scrollbar{width:9px} thumb rgba(184,134,44,.5) radius5
                ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded
                    contentItem: Rectangle { implicitWidth: 9; radius: 5; color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.5) } }
                Row {
                    width: flickWeek.width; height: flickWeek.contentHeight
                    // Time gutter
                    Item {
                        width: 48; height: parent.height
                        Repeater {
                            model: 24
                            delegate: Item {
                                x: 0; y: 28 + index*48; width: 48; height: 48
                                Text { anchors.right: parent.right; anchors.rightMargin: 5; anchors.verticalCenter: parent.verticalCenter
                                    text: ((index%12)||12)+(index<12?" AM":" PM")
                                    color: app.faint; font.pixelSize: fpx(9) }
                            }
                        }
                    }
                    // 7 day columns
                    Repeater {
                        model: 7
                        delegate: Item {
                            id: dayCol
                            property date colDate: Cal.addDays(weekRoot.weekStart, index)
                            property bool colToday: Cal.iso(colDate) === app._todayIso
                            width: (flickWeek.width - 48) / 7; height: flickWeek.contentHeight
                            Rectangle { x: 0; y: 0; width: 1; height: parent.height; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.2) }
                            // Day header
                            Rectangle {
                                x: 1; y: 0; width: parent.width-1; height: 28
                                color: colToday ? k.surface : k.surface
                                border.color: app.gold; border.width: 1
                                Column { anchors.centerIn: parent; spacing: 0
                                    Text { anchors.horizontalCenter: parent.horizontalCenter
                                        text: Cal.DOW[colDate.getDay()].toUpperCase()
                                        color: colToday ? app.burgundy : app.faint
                                        font.pixelSize: fpx(9); font.letterSpacing: theme ? theme.letterSpacing : 1 }
                                    Text { anchors.horizontalCenter: parent.horizontalCenter
                                        text: colDate.getDate()
                                        color: colToday ? app.burgundy : app.ink
                                        font.pixelSize: fpx(13); font.bold: true }
                                }
                            }
                            // Hour grid lines
                            Repeater {
                                model: 24
                                delegate: Rectangle {
                                    x: 1; y: 28 + index*48; width: dayCol.width-1; height: 48; color: k.surface
                                    Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.15) }
                                }
                            }
                            // Appointments — same TimeBlock as Day view (CSS .cal-time-block is
                            // shared markup between .cal-week-scroll/.cal-day-scroll, not two
                            // separate styles; unifying here matches the prototype more closely
                            // than the previous single-line-only Week rendering did)
                            Item {
                                x: 1; y: 28; width: parent.width-2; height: 24*48
                                CreateDragArea { anchors.fill: parent; colDate: dayCol.colDate }
                                Repeater {
                                    model: Cal.layoutLanes(Cal.apptsOn(app.appts(), dayCol.colDate).filter(function(a){ return !a.allDay; }))
                                    delegate: TimeBlock { apptData: modelData }
                                }
                            }
                            // CSS .cal-allday-block — stacked at the top of each day column, exactly
                            // like the browser prototype (overlaps the earliest hour slots by design;
                            // Day view's equivalent is the non-scrolling .cal-allday-strip above).
                            // 2026-07-04: previously all-day appointments had no UI in Week view at all.
                            Repeater {
                                model: Cal.apptsOn(app.appts(), dayCol.colDate).filter(function(a){ return a.allDay; })
                                delegate: Rectangle {
                                    readonly property color gem: Cal.cat(modelData.category, k).gem
                                    x: 4; y: 28 + index*18; width: dayCol.width-8; height: 16; radius: 3; color: gem
                                    Text { anchors.centerIn: parent; text: modelData.title; color: "#fff"
                                        font.pixelSize: fpx(9); elide: Text.ElideRight; width: parent.width - 6 }
                                    TapHandler { onTapped: app.editAppt(modelData._baseId||modelData.id) }
                                }
                            }
                            // CSS .cal-nowline — today's column only (bonus fidelity item, mirrors Day view)
                            Item {
                                id: weekNowLine
                                visible: dayCol.colToday
                                x: 1; y: 28; width: parent.width-2; height: 24*48
                                property real nowY: { var t = new Date(); return (t.getHours()*60 + t.getMinutes())/60*48; }
                                Timer { interval: 60000; running: weekNowLine.visible; repeat: true
                                    onTriggered: { var t = new Date(); weekNowLine.nowY = (t.getHours()*60 + t.getMinutes())/60*48; } }
                                Rectangle { y: weekNowLine.nowY - 1; width: parent.width; height: 2; color: app.burgundy }
                                Canvas {
                                    id: weekNowDot
                                    x: -8; y: weekNowLine.nowY - 8; width: 16; height: 16
                                    renderStrategy: Canvas.Cooperative; layer.enabled: true
                                    onPaint: { var c = getContext("2d"); c.clearRect(0,0,16,16); Art.CalArt.paintGlowDot(c, 8, 8, 4, app.burgundy); }
                                    Connections { target: weekNowLine; function onNowYChanged() { weekNowDot.requestPaint() } }   // by id, not `parent` (2026-09-24)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // ── Appointment editor + Reminders dialogs live in separate files ──
    CalEditor   { id: editor }
    CalReminders{ id: reminders; onEditRequested: function(id) { app.editAppt(id) } }
    PondPopup   { id: pondPopup; pond: pond }

    // ── CSS .cal-toast — slide-in notification card, bottom-right ──
    Item {
        id: toastRoot
        property bool shown: false
        anchors.right: parent.right; anchors.rightMargin: 18
        anchors.bottom: parent.bottom; anchors.bottomMargin: 18
        width: 300; height: toastCard.implicitHeight
        z: 500
        visible: app._notice !== ""

        // CSS transform:translateX(120%) → 0, transition .4s cubic-bezier(.2,.9,.3,1)
        x: toastRoot.shown ? 0 : width + 18
        Behavior on x {
            NumberAnimation { duration: 400; easing.type: Easing.BezierSpline
                easing.bezierCurve: [0.2, 0.9, 0.3, 1, 1, 1] }
        }

        Rectangle {
            id: toastCard
            width: parent.width; implicitHeight: toastRow.implicitHeight + 22
            radius: 10; border.color: app.gold; border.width: 2
            gradient: Gradient {
                GradientStop { position: 0; color: k.surfaceHi }
                GradientStop { position: 1; color: k.surface2 }
            }

            MultiEffect {
                anchors.fill: parent; source: toastCard; z: -1
                shadowEnabled: true; shadowColor: Qt.rgba(0,0,0,0.4)
                shadowBlur: 0.94; shadowVerticalOffset: 10
            }

            RowLayout {
                id: toastRow
                anchors.fill: parent; anchors.margins: 11; spacing: 11
                Canvas {
                    Layout.preferredWidth: 34; Layout.preferredHeight: 34
                    renderStrategy: Canvas.Cooperative; layer.enabled: true
                    onPaint: { var c = getContext("2d"); c.clearRect(0,0,34,34); Art.CalArt.paintFrog(c, 17, 17, 30) }
                }
                ColumnLayout {
                    Layout.fillWidth: true; spacing: 1
                    Text { text: "LEAP FROG LEDGER"; color: app.burgundy
                        font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(13)
                        font.letterSpacing: theme?theme.letterSpacing:1 }
                    Text { text: app._notice; color: app.ink; wrapMode: Text.WordWrap
                        Layout.fillWidth: true; font.pixelSize: fpx(14) }
                }
                Text { text: "✕"; color: app.faint; font.pixelSize: fpx(14)
                    Layout.alignment: Qt.AlignTop
                    TapHandler { onTapped: { app._notice = ""; toastRoot.shown = false; noticeTimer.stop() } } }
            }
        }
    }

    // ── Holiday lore card — opened from the Year view's feast list and the Month view's
    // holiday names (operator ask, 2026-07-06). Same scrim + gilt card language as the
    // command palette; same seal + burgundy stripe as the Day view's "On this day" card. ──
    Item {
        id: loreDlg2
        anchors.fill: parent; z: 620; visible: false
        property var lore: null          // { name, lore } from Cal.holidayLore()
        property string dateLabel: ""
        function openFor(d) {
            var h = Cal.holidayLore(d)
            if (!h) return
            lore = h
            dateLabel = Cal.DOW_FULL[d.getDay()] + ", " + Cal.MONTHS[d.getMonth()] + " " + d.getDate() + ", " + d.getFullYear()
            visible = true
        }
        function close() { visible = false }

        Rectangle { anchors.fill: parent; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.5); TapHandler { onTapped: loreDlg2.close() } }

        Item {
            x: (parent.width - width)/2
            y: Math.max(20, (parent.height - height)/2)
            width: Math.min(520, parent.width*0.92)
            height: loreCard.implicitHeight

            MultiEffect {
                anchors.fill: loreCard; source: loreCard; shadowEnabled: true
                shadowColor: Qt.rgba(0,0,0,0.5); shadowBlur: 1.0
                shadowHorizontalOffset: 0; shadowVerticalOffset: 24
            }
            Rectangle {
                id: loreCard
                width: parent.width; implicitHeight: loreCol.implicitHeight + 32
                radius: 12; border.color: app.gold; border.width: 2
                gradient: Gradient {
                    GradientStop { position: 0; color: k.surfaceHi }
                    GradientStop { position: 1; color: k.surface2 }
                }
                Rectangle { x: 2; y: 12; width: 4; height: parent.height - 24; radius: 2; color: app.burgundy }
                Column {
                    id: loreCol
                    x: 20; y: 16; width: parent.width - 40; spacing: 8
                    Row {
                        spacing: 12; width: parent.width
                        Canvas { width: 36; height: 36; anchors.verticalCenter: parent.verticalCenter
                            renderStrategy: Canvas.Cooperative; layer.enabled: true
                            onPaint: { var c=getContext("2d"); c.clearRect(0,0,36,36); Art.CalArt.paintHolidaySeal(c, 18, 18, 18, app.gold, k.gilt0, app.parch, app.burgundy) } }
                        Column {
                            spacing: 1; width: parent.width - 48 - 30
                            Text { text: loreDlg2.lore ? loreDlg2.lore.name : ""; color: app.burgundy
                                   font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(18); font.bold: true
                                   width: parent.width; wrapMode: Text.WordWrap }
                            Text { text: loreDlg2.dateLabel; color: app.faint; font.italic: true
                                   font.pixelSize: fpx(12) }
                        }
                        Text { text: "✕"; color: app.faint; font.pixelSize: fpx(14)
                            TapHandler { onTapped: loreDlg2.close() } }
                    }
                    Text { text: loreDlg2.lore ? loreDlg2.lore.lore : ""; color: app.ink
                           width: parent.width; wrapMode: Text.WordWrap
                           font.pixelSize: fpx(14) }
                }
            }
        }
    }


    // ── Today's season card — Pond ▸ "Season Card…" (the manual's "consult today's
    // season card"). Rebuilt 2026-09-24 as an in-window overlay like the lore card:
    // the old LeapFrogSeasonCard.qml was its own bypass-WM Window and rendered broken.
    Item {
        id: seasonDlg
        anchors.fill: parent; z: 630; visible: false
        property date today: new Date()
        readonly property string season: Cal.season(today.getMonth())
        readonly property var meta: ({
            "spring": { title: "Spring", eyebrow: "THE POND WAKES", sky: ["#bfe3d0", "#7fc6a6"],
                        lines: ["New shoots keep no record of last winter — begin again.",
                                "The frog leaps not because it is sure, but because it is spring.",
                                "Small green things are patient. Be likewise.",
                                "Every lily pad was once a seed that refused to quit."] },
            "summer": { title: "Summer", eyebrow: "THE POND AT ITS FULLEST", sky: ["#cfe6f2", "#7db6d8"],
                        lines: ["Long days are a gift; do not spend them all indoors.",
                                "Still water and a warm sun — ambition can wait an hour.",
                                "The pond is widest now. Swim out a little.",
                                "Bask, then leap. In that order."] },
            "autumn": { title: "Autumn", eyebrow: "THE POND TURNS GOLD", sky: ["#f0dcae", "#cf9a52"],
                        lines: ["Gather what the season gave you; let the rest drift.",
                                "A falling leaf is not failure — it is a debt repaid.",
                                "Store light for the dark months. You will need it.",
                                "The pond keeps what matters and lets the leaves go."] },
            "winter": { title: "Winter", eyebrow: "THE POND RESTS", sky: ["#dfe7ef", "#9fb2c4"],
                        lines: ["Under the ice, the frog dreams. Rest is also work.",
                                "Quiet is not empty. The pond is only thinking.",
                                "Keep one small lamp lit; spring is reading the map.",
                                "What sleeps in winter leaps in spring."] }
        })
        readonly property var info: meta[season]
        readonly property int dayOfYear: Math.floor((today - new Date(today.getFullYear(), 0, 0)) / 86400000)
        readonly property string thought: info.lines[dayOfYear % info.lines.length]
        readonly property var lore: Cal.holidayLore(today)
        function open()  { today = new Date(); visible = true; plate.requestPaint() }
        function close() { visible = false }

        Rectangle { anchors.fill: parent; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.5); TapHandler { onTapped: seasonDlg.close() } }

        Item {
            x: (parent.width - width)/2
            y: Math.max(20, (parent.height - height)/2)
            width: Math.min(520, parent.width*0.92)
            height: seasonCardBg.implicitHeight

            MultiEffect {
                anchors.fill: seasonCardBg; source: seasonCardBg; shadowEnabled: true
                shadowColor: Qt.rgba(0,0,0,0.5); shadowBlur: 1.0; shadowVerticalOffset: 24
            }
            Rectangle {
                id: seasonCardBg
                width: parent.width; implicitHeight: seasonCol.implicitHeight + 40
                radius: 14; border.color: app.gold; border.width: 2
                gradient: Gradient {
                    GradientStop { position: 0; color: k.surfaceHi }
                    GradientStop { position: 1; color: k.surface2 }
                }
                TapHandler { }   // taps on the card don't fall through to the scrim
                Column {
                    id: seasonCol
                    x: 26; y: 22; width: parent.width - 52; spacing: 6
                    Text { width: parent.width; horizontalAlignment: Text.AlignHCenter
                        text: seasonDlg.info.eyebrow; color: app.faint
                        font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(11); font.letterSpacing: 4 }
                    Text { width: parent.width; horizontalAlignment: Text.AlignHCenter
                        text: seasonDlg.info.title; color: app.burgundy
                        font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(30); font.bold: true }
                    Text { width: parent.width; horizontalAlignment: Text.AlignHCenter
                        text: Cal.DOW_FULL[seasonDlg.today.getDay()] + ", " + seasonDlg.today.getDate() + " "
                              + Cal.MONTHS[seasonDlg.today.getMonth()] + " " + seasonDlg.today.getFullYear()
                              + "  ·  " + Cal.ZODIAC_NAME[Cal.zodiacOfMonth(seasonDlg.today.getMonth())]
                        color: app.faint; font.italic: true; font.pixelSize: fpx(13) }
                    Item { width: 1; height: 6 }
                    Rectangle {
                        width: parent.width; height: Math.round(width * 0.42); radius: 10
                        border.color: app.goldBr; border.width: 2; clip: true
                        gradient: Gradient {
                            GradientStop { position: 0; color: seasonDlg.info.sky[0] }
                            GradientStop { position: 1; color: seasonDlg.info.sky[1] }
                        }
                        Canvas {
                            id: plate
                            anchors.fill: parent; anchors.margins: 2
                            renderStrategy: Canvas.Cooperative
                            onPaint: { var c = getContext("2d"); c.reset()
                                Art.CalArt.paintSeasonHeader(c, 0, 0, width, height, seasonDlg.season) }
                        }
                    }
                    Item { width: 1; height: 6 }
                    Text { width: parent.width; horizontalAlignment: Text.AlignHCenter; wrapMode: Text.WordWrap
                        text: "“" + seasonDlg.thought + "”"; color: app.ink
                        font.italic: true; font.pixelSize: fpx(16); lineHeight: 1.3 }
                    Text { visible: !!seasonDlg.lore; width: parent.width; horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WordWrap; topPadding: 4
                        text: seasonDlg.lore ? ("Today is " + seasonDlg.lore.name + ".") : ""
                        color: app.burgundy; font.pixelSize: fpx(13)
                        font.underline: seasonLoreHov.hovered
                        HoverHandler { id: seasonLoreHov; cursorShape: Qt.PointingHandCursor }
                        TapHandler { onTapped: { seasonDlg.close(); loreDlg2.openFor(seasonDlg.today) } } }
                    Item { width: 1; height: 4 }
                    CalBtn { text: "CLOSE"; anchors.horizontalCenter: parent.horizontalCenter; onClicked: seasonDlg.close() }
                }
            }
        }
    }

    // ── Command palette — mirrors cal-app.js openCmd()/renderCmd() exactly (lines 282-347):
    // "/" opens search mode, "g"/"G" opens jump mode, guarded against firing while a text
    // field has focus (matches the prototype's own `e.target.tagName === "INPUT"` guard). ──
    // Shortcut is not an Item, so the Window.window attached property can't attach to it
    // (Qt warned at load and the guard never engaged) — read it through the root `app` Item.
    Shortcut {
        sequence: "/"
        enabled: !editor.visible && !reminders.visible && !cmdPalette.visible &&
                 !(app.Window.window && app.Window.window.activeFocusItem && app.Window.window.activeFocusItem.hasOwnProperty("selectedText"))
        onActivated: cmdPalette.open("search")
    }
    Shortcut {
        sequence: "G"
        enabled: !editor.visible && !reminders.visible && !cmdPalette.visible &&
                 !(app.Window.window && app.Window.window.activeFocusItem && app.Window.window.activeFocusItem.hasOwnProperty("selectedText"))
        onActivated: cmdPalette.open("jump")
    }

    Item {
        id: cmdPalette
        anchors.fill: parent
        visible: false
        z: 600
        property string mode: "search"
        property int selIndex: 0

        function open(m) { mode = m; cmdInput.text = ""; selIndex = 0; visible = true; cmdInput.forceActiveFocus() }
        function close() { visible = false }
        function gotoDate(d) {
            cmdPalette.close(); app.cursor = d
            if (app.view === "year") app.view = "month"
            app.refresh(); app.updateCtx()
        }

        // flat row model — one JS array covering all 3 row kinds, mirrors renderCmd() exactly:
        // jump mode = single ok/dim row; search mode = up to 20 appts then up to 10 todos.
        property var resultRows: {
            if (cmdPalette.mode === "jump") {
                var jd = Cal.parseJump(cmdInput.text)
                return [{ kind:"jump", ok: !!jd, date: jd,
                    label: jd ? ("Go to " + Cal.DOW_FULL[jd.getDay()] + ", " + Cal.MONTHS[jd.getMonth()] + " " + jd.getDate() + ", " + jd.getFullYear())
                              : "Type a date, then press Enter" }]
            }
            var q = cmdInput.text
            if (!q.trim()) return []
            var res = Cal.searchAll(app.appts(), calBackend.todos, q)
            var rows = []
            res.appts.slice(0,20).forEach(function(a){
                var d = Cal.fromIso(a.date)
                rows.push({ kind:"appt", id:(a._baseId||a.id), title:a.title,
                    gem:Cal.cat(a.category, k).gem,
                    meta: Cal.MONTHS[d.getMonth()].slice(0,3)+" "+d.getDate()+(a.allDay?"":" · "+Cal.fmtTime(a.start)),
                    date: d })
            })
            res.todos.slice(0,10).forEach(function(t){
                rows.push({ kind:"todo", text:t.text, done: !!t.done })
            })
            return rows
        }

        function activate(row) {
            if (!row) return
            if (row.kind === "jump") { if (row.ok) cmdPalette.gotoDate(row.date) }
            else if (row.kind === "appt") {
                cmdPalette.close(); app.cursor = row.date; app.view = "day"; app.refresh(); app.updateCtx()
                app.editAppt(row.id)
            } else if (row.kind === "todo") { cmdPalette.close() }
        }
        function moveSel(d) {
            if (resultRows.length === 0) return
            selIndex = Math.max(0, Math.min(resultRows.length-1, selIndex + d))
        }

        Rectangle { anchors.fill: parent; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.5); TapHandler { onTapped: cmdPalette.close() } }

        Item {
            id: cmdWrap
            // CSS .cmd-panel: left:50%, top:14%, width:min(560px,92vw)
            x: (parent.width - width)/2
            y: parent.height * 0.14
            width: Math.min(560, parent.width*0.92)
            height: cmdCardBg.implicitHeight

            MultiEffect {
                anchors.fill: cmdCardBg; source: cmdCardBg; shadowEnabled: true
                shadowColor: Qt.rgba(0,0,0,0.5); shadowBlur: 1.0
                shadowHorizontalOffset: 0; shadowVerticalOffset: 24
            }

            Rectangle {
                id: cmdCardBg
                width: parent.width; implicitHeight: cmdCol.implicitHeight + 28
                radius: 12; border.color: k.gilt2; border.width: 2
                gradient: Gradient {
                    GradientStop { position: 0; color: k.surfaceHi }
                    GradientStop { position: 1; color: k.surface2 }
                }

                ColumnLayout {
                    id: cmdCol
                    anchors.fill: parent; anchors.margins: 14; spacing: 8

                    TextField {
                        id: cmdInput
                        Layout.fillWidth: true
                        font.family: theme?theme.fontFamily:"serif"; font.pixelSize: fpx(18)
                        color: k.ink
                        placeholderText: cmdPalette.mode === "jump"
                            ? "Jump to…  2026-07-15 · today · tomorrow · +7 · Jul 4"
                            : "Search appointments & tasks…"
                        background: Rectangle {
                            radius: 8; color: Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.92)
                            border.width: 1.5; border.color: cmdInput.activeFocus ? k.gilt4 : k.gilt2
                        }
                        onTextChanged: cmdPalette.selIndex = 0
                        Keys.onEscapePressed: cmdPalette.close()
                        Keys.onReturnPressed: cmdPalette.activate(cmdPalette.resultRows[cmdPalette.selIndex])
                        Keys.onDownPressed: cmdPalette.moveSel(1)
                        Keys.onUpPressed: cmdPalette.moveSel(-1)
                    }

                    Text {
                        Layout.fillWidth: true; Layout.topMargin: 8
                        visible: cmdPalette.mode === "search" && !cmdInput.text.trim()
                        text: "Search across every appointment and task."
                        font.italic: true; color: app.faint; horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: fpx(13)
                    }
                    Text {
                        Layout.fillWidth: true; Layout.topMargin: 8
                        visible: cmdPalette.mode === "search" && !!cmdInput.text.trim() && cmdPalette.resultRows.length === 0
                        text: "No matches in the ledger."
                        font.italic: true; color: app.faint; horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: fpx(13)
                    }

                    ListView {
                        id: cmdList
                        Layout.fillWidth: true
                        Layout.preferredHeight: Math.min(contentHeight, 320)
                        visible: cmdPalette.resultRows.length > 0
                        clip: true; interactive: contentHeight > height
                        model: cmdPalette.resultRows
                        delegate: Rectangle {
                            width: cmdList.width; height: 38; radius: 7
                            readonly property bool sel: index === cmdPalette.selIndex
                            color: (sel || rowHov.hovered) ? Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.16) : "transparent"
                            Row {
                                anchors.fill: parent; anchors.leftMargin: 10; anchors.rightMargin: 10; spacing: 9
                                // gem dot — appt category color / fixed task burgundy / hidden for jump row
                                Canvas {
                                    width: 9; height: 9; anchors.verticalCenter: parent.verticalCenter
                                    visible: modelData.kind !== "jump"
                                    onPaint: {
                                        var c = getContext("2d"); c.clearRect(0,0,9,9)
                                        Art.CalArt.paintGlowDot(c, 4.5, 4.5, 3, modelData.kind === "todo" ? k.lineWine : modelData.gem)
                                    }
                                }
                                Text {
                                    width: parent.width - 9 - 90 - 18; anchors.verticalCenter: parent.verticalCenter
                                    elide: Text.ElideRight; font.pixelSize: fpx(14)
                                    text: modelData.kind === "jump" ? modelData.label : (modelData.kind === "appt" ? modelData.title : modelData.text)
                                    color: modelData.kind === "jump" && !modelData.ok ? app.faint : app.ink
                                    font.italic: modelData.kind === "jump" && !modelData.ok
                                }
                                Text {
                                    width: 90; anchors.verticalCenter: parent.verticalCenter
                                    horizontalAlignment: Text.AlignRight; elide: Text.ElideRight
                                    font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(11)
                                    color: app.faint
                                    text: modelData.kind === "appt" ? modelData.meta : (modelData.kind === "todo" ? ("task" + (modelData.done?" · done":"")) : "")
                                }
                            }
                            HoverHandler { id: rowHov }
                            TapHandler { onTapped: cmdPalette.activate(modelData) }
                        }
                    }

                    Text {
                        Layout.fillWidth: true; Layout.topMargin: 6
                        horizontalAlignment: Text.AlignHCenter
                        font.family: theme?theme.titleFont:"serif"; font.pixelSize: fpx(10)
                        font.letterSpacing: theme?theme.letterSpacing:1
                        color: app.faint
                        text: "↑↓ navigate · ↵ select · esc close"
                    }
                }
            }

            // CSS .cmd-panel::before — inset:5px double-frame
            Rectangle {
                anchors.fill: cmdCardBg; anchors.margins: 5; radius: 8
                color: "transparent"; border.width: 1; border.color: k.gilt0
                opacity: 0.4
            }
        }
    }

    // ── About / Help dialog ──
    Item {
        id: aboutPanel
        anchors.fill: parent; visible: false; z: 10
        function open()  { aboutPanel.visible = true }
        function close() { aboutPanel.visible = false }

        Rectangle {
            anchors.fill: parent
            color: Qt.rgba(k.wine1.r, k.wine1.g, k.wine1.b, 0.72)
            TapHandler { onTapped: aboutPanel.visible = false }
        }

        Rectangle {
            anchors.centerIn: parent
            width: Math.min(720, parent.width - 80)
            height: Math.min(640, parent.height - 80)
            radius: 14
            border.color: k.gilt0; border.width: 2
            gradient: Gradient { orientation: Gradient.Vertical
                GradientStop { position: 0; color: k.surface  }
                GradientStop { position: 1; color: k.surface2 }
            }
            TapHandler { }

            ColumnLayout {
                anchors.fill: parent; spacing: 0

                Loader {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    source: "LeapFrogManual.qml"
                }

                Rectangle {
                    Layout.fillWidth: true; Layout.preferredHeight: 38
                    Layout.leftMargin: 24; Layout.rightMargin: 24
                    Layout.bottomMargin: 18; radius: 8
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop { position: 0; color: k.wine3 }
                        GradientStop { position: 1; color: k.wine1 }
                    }
                    border.color: k.gilt2; border.width: 1.5
                    Text { anchors.centerIn: parent; text: "CLOSE"
                           font.family: k.titles; font.pixelSize: k.fs(13)
                           font.letterSpacing: 2; color: k.gilt5 }
                    TapHandler { onTapped: aboutPanel.visible = false }
                }
            }
        }
    }

}
