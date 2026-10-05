// ClockCalendarPopup.qml — Leap Frog Ledger dropdown for the TOP-PANEL CLOCK.
// Clicking the clock toggles this parchment panel just beneath it (the same
// pattern as NCDE's volume / power popups). Compact month grid + the selected
// day's agenda + quick-add; a button opens the full LeapFrogLedger window.
//
// ── WIRING (in qml/compositor/main.qml top panel) ────────────────────────
// Give the clock Text a handle + TapHandler, and host the popup in its own
// always-on-top frameless Window so it floats above client windows:
//
//   Text {
//       id: panelClock
//       text: widget_data.timeHour + ":" + widget_data.timeMinute
//       // …existing styling…
//       TapHandler { onTapped: clockCalWin.toggleAt(panelClock) }
//   }
//
//   Window {
//       id: clockCalWin
//       flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint | Qt.WindowStaysOnTopHint
//       color: "transparent"; visible: false
//       width: 360; height: 470
//       function toggleAt(anchorItem) {
//           if (visible) { visible = false; return; }
//           var p = anchorItem.mapToGlobal(0, anchorItem.height);
//           // keep it on-screen, nudged left so it sits under the clock
//           x = Math.min(p.x - width/2, desktop.width - width - 8);
//           y = p.y + 4;
//           visible = true;
//       }
//       ClockCalendarPopup {
//           anchors.fill: parent
//           onCloseRequested: clockCalWin.visible = false
//           onOpenFull: launcher.launchExec("leap-frog-ledger")  // or load LeapFrogLedger.qml in a managed Window
//       }
//   }
//
// Click-away close: give the Window a MouseArea sibling or track focus; NCDE's
// existing popups already do this — mirror that.

import QtQuick
import QtQuick.Layouts
import "cal-logic.js" as Cal
import "cal-art.js"   as Art

Item {
    id: pop
    width: 360; height: 470
    signal closeRequested()
    signal openFull()
    // 2026-07-21: the popup's controls now do what they say (see TopPanel wiring)
    signal quickAdd(date d)          // open editor on this day
    signal openAppt(string apptId)   // open THIS appointment to read/edit

    property date cursor: new Date()
    property date selected: new Date()
    NCDEKit { id: k }
    readonly property color ink: k.ink
    readonly property color faint: k.inkLabel
    readonly property color gold: k.gilt2
    readonly property color burgundy: k.lineWine

    function appts(){ return calBackend.appointments; }
    function refresh(){ bg.requestPaint(); emblem.requestPaint(); monthGrid.rebuild(); agendaRepeater.model = Cal.apptsOn(appts(), selected); }
    Component.onCompleted: refresh()
    Connections { target: calBackend; function onChanged(){ pop.refresh() } }
    Connections { target: ncde; function onThemeChanged(){ pop.refresh() } }

    // drop shadow + parchment card
    Rectangle { anchors.fill: parent; anchors.margins: 2; radius: 12; color: "#000"; opacity: 0.28 }
    Canvas {
        id: bg; anchors.fill: parent; renderStrategy: Canvas.Threaded
        onPaint: { var c=getContext("2d"); Art.CalArt.paintPage(c,width,height,k.dark,k.surface.toString(),k.surface2.toString()); Art.CalArt.paintBorder(c,width,height,8); }
    }

    ColumnLayout {
        anchors.fill: parent; anchors.margins: 16; spacing: 8

        // header
        RowLayout {
            Layout.fillWidth: true
            Canvas { id: emblem; Layout.preferredWidth: 38; Layout.preferredHeight: 38; renderStrategy: Canvas.Threaded
                onPaint: { var c=getContext("2d"); c.clearRect(0,0,38,38); Art.CalArt.paintEmblem(c,19,16,12); } }
            ColumnLayout { spacing: 0
                Text { text: "Leap Frog Ledger"; color: WallInk.inked(pop.burgundy); font.family: theme?theme.titleFont:"serif"; font.pixelSize: Math.round(16 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); font.bold: true }
                Text { id: monthLbl; color: WallInk.inked(pop.faint); font.italic: true; font.pixelSize: Math.round(12 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0))
                    text: Cal.MONTHS[pop.cursor.getMonth()] + " " + pop.cursor.getFullYear() } }
            Item { Layout.fillWidth: true }
            PopBtn { text: "‹"; onClicked: pop.shift(-1) }
            PopBtn { text: "›"; onClicked: pop.shift(1) }
        }

        // weekday header
        RowLayout {
            Layout.fillWidth: true; spacing: 0
            Repeater { model: Cal.DOW; delegate: Text { Layout.fillWidth: true; horizontalAlignment: Text.AlignHCenter
                text: modelData.charAt(0); color: WallInk.inked(pop.burgundy); font.family: theme?theme.titleFont:"serif"; font.pixelSize: Math.round(12 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); font.letterSpacing: 1 } }
        }

        // month grid
        Grid {
            id: monthGrid; Layout.fillWidth: true; columns: 7; rowSpacing: 2; columnSpacing: 2
            property var cells: []
            function rebuild(){
                monthLbl.text = Cal.MONTHS[pop.cursor.getMonth()] + " " + pop.cursor.getFullYear();
                var arr=[]; var start=Cal.startOfWeek(new Date(pop.cursor.getFullYear(), pop.cursor.getMonth(), 1));
                for (var i=0;i<42;i++) arr.push(Cal.addDays(start,i));
                cells = arr;
            }
            Repeater {
                model: monthGrid.cells
                delegate: Rectangle {
                    width: (monthGrid.width - 6*2)/7; height: 40; radius: 5
                    property bool inMonth: modelData.getMonth()===pop.cursor.getMonth()
                    property bool isToday: Cal.sameDay(modelData, new Date())
                    property bool isSel: Cal.sameDay(modelData, pop.selected)
                    property var dayAppts: Cal.apptsOn(pop.appts(), modelData)
                    property int apptCount: dayAppts.length
                    color: isSel ? Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.85) : "transparent"
                    border.color: isToday ? pop.gold : "transparent"; border.width: isToday ? 2 : 0
                    opacity: inMonth ? 1 : 0.38
                    Text { anchors.centerIn: parent; text: modelData.getDate(); color: WallInk.inked(isToday?pop.burgundy:pop.ink)
                        font.family: theme?theme.titleFont:"serif"; font.pixelSize: Math.round(13 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); font.bold: isToday||isSel }
                    Row { anchors.bottom: parent.bottom; anchors.bottomMargin: 4; anchors.horizontalCenter: parent.horizontalCenter; spacing: 2
                        // one dot per appointment, in ITS category colour (2026-07-21:
                        // was a flat gold count — the category gems are the whole point)
                        Repeater { model: dayAppts.slice(0,3); delegate: Rectangle { width:4; height:4; radius:2
                            color: (Cal.CATEGORIES[modelData.category]||Cal.CATEGORIES.azure).gem } } }
                    TapHandler { onTapped: { pop.selected = modelData; agendaRepeater.model = Cal.apptsOn(pop.appts(), modelData); } 
                                 onDoubleTapped: pop.openFull() }
                }
            }
        }

        Rectangle { Layout.fillWidth: true; height: 1; color: Qt.rgba(k.lineOchre.r, k.lineOchre.g, k.lineOchre.b, 0.3) }

        // selected-day agenda
        Text { color: WallInk.inked(pop.burgundy); font.family: theme?theme.titleFont:"serif"; font.pixelSize: Math.round(12 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); font.letterSpacing: 1
            text: Cal.DOW_FULL[pop.selected.getDay()].toUpperCase() + " · " + Cal.MONTHS[pop.selected.getMonth()].slice(0,3) + " " + pop.selected.getDate() }
        Flickable {
            Layout.fillWidth: true; Layout.fillHeight: true; contentHeight: agendaCol.height; clip: true
            Column {
                id: agendaCol; width: parent.width; spacing: 3
                Repeater {
                    id: agendaRepeater
                    delegate: Rectangle {
                        width: agendaCol.width; height: 34; radius: 5; color: Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.5)
                        Rectangle { width: 4; height: parent.height; radius: 2; color: (Cal.CATEGORIES[modelData.category]||Cal.CATEGORIES.azure).gem }
                        Row { anchors.fill: parent; anchors.leftMargin: 12; anchors.rightMargin: 8; spacing: 8
                            Text { anchors.verticalCenter: parent.verticalCenter; width: 64; color: WallInk.inked(pop.faint); font.pixelSize: Math.round(12 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0))
                                text: modelData.allDay ? "all day" : Cal.fmtTime(modelData.start) }
                            Text { anchors.verticalCenter: parent.verticalCenter; color: WallInk.inked(pop.ink); font.pixelSize: Math.round(14 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); elide: Text.ElideRight
                                width: parent.width - 80; text: modelData.title } }
                        TapHandler { onTapped: pop.openAppt(modelData._baseId||modelData.id) }
                    }
                }
                Text { visible: agendaRepeater.count===0; color: WallInk.inked(pop.faint); font.italic: true; font.pixelSize: Math.round(13 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0))
                    text: "  The pond is calm — nothing scheduled." }
            }
        }

        // footer
        RowLayout {
            Layout.fillWidth: true
            PopBtn { text: "✛ Quick add"; onClicked: pop.quickAdd(pop.selected) }
            Item { Layout.fillWidth: true }
            PopBtn { text: "Open Ledger ▸"; accent: true; onClicked: pop.openFull() }
        }
    }

    function shift(d){ var c=new Date(pop.cursor); c.setMonth(c.getMonth()+d); pop.cursor=c; monthGrid.rebuild(); }

    component PopBtn: Rectangle {
        property alias text: l.text; property bool accent: false; signal clicked()
        implicitWidth: l.implicitWidth+18; implicitHeight: 28; radius: 6
        color: accent ? k.accent : Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 1); border.color: pop.gold; border.width: 1.5
        Text { id: l; anchors.centerIn: parent; font.family: theme?theme.titleFont:"serif"; font.pixelSize: Math.round(12 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); color: WallInk.inked(parent.accent?k.surface:pop.ink) }
        TapHandler { onTapped: parent.clicked() }
    }
}
