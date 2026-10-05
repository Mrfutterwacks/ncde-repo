// GliaLeapFrogBar.qml — Glia-styled bottom-bar menu for Leap Frog Ledger.
//
// FOUR top-level titles — Ledger / View / Pond / Sit by the Pond — the
// operator's original shape (see ~/my-project/docs/leapfrog-original/
// GliaLeapFrogBar.qml.original-4title). Reverted 2026-07-04 from a one-menu
// ("Ledger" with View/Pond nested as submenus) experiment: every attempt at
// that consolidated shape broke in practice across sessions 59-63 (menuLayer
// wiring dropped elsewhere, debug instrumentation left behind, etc.). Do not
// re-consolidate back into one title without the operator asking for it.
//
//   property var  app        // the LeapFrogLedger root id
//   property var  pond       // the LeapFrogPond context object (calBackend companion)
//   property Item menuLayer  // REQUIRED — the in-scene GliaDropMenu from the panel
//                            // overlay. Without it, GliaBar.presentActiveMenu()
//                            // bails and the menu never appears.
//
// Calendar actions use ONLY members the Ledger already has:
//   new / openFull / quit / today / reminders / view:*    → app.*
// Pond + Ledger-data actions use the pond backend / popups:
//   ledger.export.csv / .lilypad / .ics → pond.exportCsv() / pond.exportLilyPad() / calBackend.exportICSToFile()
//   ledger.import.ics            → calBackend.importICSFromFile() (via app.icsImportDlg)
//   ledger.reconcile             → pond.reconcile()
//   ledger.archive               → pond.archivePast()
//   pond.stock                   → PondPopup.openStock()  (jot a lily-pad note)
//   pond.tally                   → PondPopup.openTally()  (count the lily pads)
//
// Season card (Pond ▸ Season Card…): the manual promises it, so it's back
// (2026-09-24) — as an overlay INSIDE the Ledger window (app.seasonDlg), not
// LeapFrogSeasonCard.qml's own bypass-WM Window, which rendered broken
// (text overflow, dark rendering). That file stays on disk, un-instantiated.
//
// USAGE (mirrors how LeapFrogMenu was wired):
//   GliaLeapFrogBar {
//       anchors.verticalCenter: parent.verticalCenter
//       height: parent.height
//       app: leapFrogLedgerRoot
//       pond: pond                  // the context property from main.cpp
//       menuLayer: bottomDrop       // the in-scene GliaDropMenu from BottomPanel.qml
//   }
//
// All animation (scroll dropdowns, furl, hover wash, popup fade/scale) is
// inherited. View checkmark follows app.view live.
import QtQuick

Item {
    id: lf
    implicitHeight: 28
    implicitWidth: bar.implicitWidth

    property var app: null
    property var pond: null
    property Item menuLayer: null
    signal showAbout()      // source-compat with the old menu

    function run(action) {
        // ── calendar (Ledger's own API) ──
        if (action === "new")            { if (app && app.editorDlg) { app.openFull(); app.editorDlg.openNew(app.cursor, 9 * 60) } }
        else if (action === "openFull")  { if (app) app.openFull() }
        else if (action === "quit")      { if (app) app.closeRequested() }
        else if (action === "today")     { if (app) { app.openFull(); app.cursor = new Date(); app.refresh(); app.updateCtx() } }
        else if (action === "reminders") { if (app && app.remindersDlg) { app.openFull(); app.remindersDlg.open() } }
        else if (action.indexOf("view:") === 0) { if (app) { app.view = action.slice(5); app.refresh(); app.updateCtx(); app.openFull() } }
        // ── hand-off to Hummingbird Courier (mail) ──
        else if (action === "mail.selected") {
            if (app && app.selectedApptId) calBackend.composeForHummingbird(app.selectedApptId)
            // 2026-07-21: never a silent no-op — say what to do instead
            else if (app) { app.openFull(); app.notice("Open an appointment first — then send it as a letter") }
        }
        // ── ledger data ops (pond backend) ──
        else if (action === "export.csv")     { if (pond) pond.exportCsv() }
        else if (action === "export.lilypad") { if (pond) pond.exportLilyPad() }
        else if (action === "reconcile")      { if (pond) pond.reconcile() }
        else if (action === "archive")        { if (pond) pond.archivePast() }
        // ── ICS import/export (calBackend, the original calendar's own data ops) ──
        else if (action === "import.ics")     { if (app && app.icsImportDlg) { app.openFull(); app.icsImportDlg.open() } }
        else if (action === "export.ics") {
            var path = "/home/" + settings.userName + "/leapfrog.ics"
            var ok = calBackend.exportICSToFile(path)
            if (app) app.notice(ok ? ("Exported to " + path) : "Export failed")
        }
        // ── pond ──
        else if (action === "pond.stock")     { pondPopup.openStock() }
        else if (action === "pond.tally")     { pondPopup.openTally() }
        else if (action === "pond.season")    { if (app && app.seasonDlg) { app.openFull(); app.seasonDlg.open() } }
        else if (action === "pond.manual")    { if (app) { app.openFull(); app.aboutDlg.open() } }
    }

    // FOUR top-level titles — Ledger / View / Pond / Sit by the Pond — the
    // operator's original shape.
    function buildMenus() {
        var v = app ? app.view : "month"
        return [
            { title: "Ledger", items: [
                { label: "New Appointment…", shortcut: "Ctrl+N", actionId: "new" },
                { label: "Open Full Window",                     actionId: "openFull" },
                { separator: true },
                { label: "Send as Hummingbird message…",         actionId: "mail.selected" },
                { separator: true },
                { label: "Import .ics…",                         actionId: "import.ics" },
                { label: "Export", submenu: [
                    { label: "As .ics…",         actionId: "export.ics" },
                    { label: "As CSV…",          actionId: "export.csv" },
                    { label: "Lily-Pad Digest…", actionId: "export.lilypad" }
                ]},
                { label: "Reconcile",                            actionId: "reconcile" },
                { label: "Archive Past Entries",                 actionId: "archive" },
                { separator: true },
                { label: "Quit",                                 actionId: "quit" }
            ]},
            { title: "View", items: [
                { label: "Month",  checkable: true, checked: v === "month",  actionId: "view:month" },
                { label: "Week",   checkable: true, checked: v === "week",   actionId: "view:week" },
                { label: "Day",    checkable: true, checked: v === "day",    actionId: "view:day" },
                { label: "Year",   checkable: true, checked: v === "year",   actionId: "view:year" },
                { label: "Agenda", checkable: true, checked: v === "agenda", actionId: "view:agenda" }
            ]},
            { title: "Pond", items: [
                { label: "Today",            shortcut: "Ctrl+T", actionId: "today" },
                { label: "Reminders…",                           actionId: "reminders" },
                { separator: true },
                { label: "Stock the Pond…",                      actionId: "pond.stock" },
                { label: "Tally the Lily Pads",                  actionId: "pond.tally" },
                { separator: true },
                { label: "Today's Season Card…",                 actionId: "pond.season" }
            ]},
            // Sit by the Pond opens the operating manual inside the full Ledger window.
            { title: "Sit by the Pond", actionId: "pond.manual" }
        ]
    }

    GliaBar {
        id: bar
        anchors.fill: parent
        brand: "Leap Frog"
        openUpward: true
        collapsible: true
        brandSize: theme.fontSmall
        titleSize: theme.fontSmall
        menuLayer: lf.menuLayer
        overrideTextColor: settings.leapFrogTextColor

        onDocRequested: function(key) { leapDoc.show(key) }

        menuModel: GliaMenuModel {
            id: model
            mode: "static"
            staticAppName: "Leap Frog"
            staticMenus: lf.buildMenus()
            onActionInvoked: function(id) { lf.run(id) }
        }
    }

    Connections {
        target: lf.app
        ignoreUnknownSignals: true
        function onViewChanged() { model.staticMenus = lf.buildMenus() }
    }

    GliaDocPopup       { id: leapDoc }
    PondPopup          { id: pondPopup; pond: lf.pond }
}
