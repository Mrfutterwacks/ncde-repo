// CalReminders.qml — Reminders settings dialog for Leap Frog Ledger (NCDE).
// Used by LeapFrogLedger.qml as `CalReminders { id: reminders }`. Persists via
// calBackend.saveSettings(); the cal-reminders daemon reads the same JSON.
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects
import "cal-logic.js" as Cal

Item {
    id: rem
    anchors.fill: parent
    visible: false
    // tap a pending reminder → the Ledger opens that appointment in the editor
    signal editRequested(string id)
    readonly property int horizonDays: 14
    property var pending: []
    function reloadPending(){
        var s = calBackend.settings || {};
        pending = Cal.upcomingReminders(calBackend.appointments, new Date(), horizonDays, s.defaultLead==null?15:s.defaultLead);
    }
    function whenLabel(d){
        var t = new Date(); t.setHours(0,0,0,0);
        var dd = new Date(d); dd.setHours(0,0,0,0);
        var diff = Math.round((dd - t)/86400000);
        var day = diff===0 ? "Today" : diff===1 ? "Tomorrow" : Cal.DOW[d.getDay()]+" "+Cal.MONTHS[d.getMonth()].slice(0,3)+" "+d.getDate();
        return day + " · " + Cal.fmtTime(d.getHours()*60+d.getMinutes());
    }
    Connections { target: calBackend; function onChanged(){ if (rem.visible) rem.reloadPending() } }
    Timer { interval: 60000; repeat: true; running: rem.visible; onTriggered: rem.reloadPending() }

    function open(){
        reloadPending();
        var s = calBackend.settings;
        cEnabled.checked = s.enabled !== false;
        cDesktop.checked = !!s.methodDesktop; cEmail.checked = !!s.methodEmail; cNtfy.checked = !!s.methodNtfy;
        fEmail.text = s.email||""; fTopic.text = s.ntfyTopic||"";
        leadBox.currentIndex = [0,5,15,30,60,1440].indexOf(s.defaultLead==null?15:s.defaultLead); if(leadBox.currentIndex<0)leadBox.currentIndex=2;
        note.text = ""; rem.visible = true;
    }
    NCDEKit { id: k }

    // CSS #ed-backdrop-equivalent: a modal scrim dims regardless of theme,
    // it isn't text-on-surface, so it stays a fixed dark tint (never adaptive).
    Rectangle { anchors.fill: parent; color: Qt.rgba(0.102, 0.071, 0.031, 0.55); TapHandler { onTapped: rem.visible=false } }

    Item {
        id: remCardWrap
        anchors.centerIn: parent; width: 440
        height: Math.min(col.implicitHeight + 36, rem.height - 40)

        MultiEffect {
            anchors.fill: remCardBg; source: remCardBg; shadowEnabled: true
            shadowColor: Qt.rgba(0,0,0,0.5); shadowBlur: 1.0
            shadowHorizontalOffset: 0; shadowVerticalOffset: 24
        }

        Rectangle {
            id: remCardBg
            anchors.fill: parent
            radius: 12; border.color: k.gilt2; border.width: 2
            gradient: Gradient {
                GradientStop { position: 0; color: k.surfaceHi }
                GradientStop { position: 1; color: k.surface2 }
            }
            clip: true

        Flickable {
            anchors.fill: parent; anchors.margins: 18
            contentWidth: width; contentHeight: col.implicitHeight
            clip: true; boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: NCDEScrollBar {}

            ColumnLayout {
                id: col; width: parent.width; spacing: 9
                Text { text: "🐸  Reminders"; color: k.lineWine; font.family: theme?theme.titleFont:"serif"; font.pixelSize: theme ? theme.scale(19) : 19; font.bold: true; Layout.alignment: Qt.AlignHCenter }

                // ── every pending reminder, soonest first (next two weeks) ──
                Text { text: "WAITING FOR THEIR MOMENT"; color: ncde.gilt1; font.pixelSize: theme ? theme.scale(10) : 10; font.letterSpacing: theme ? theme.letterSpacing : 1.5 }
                Text { visible: rem.pending.length === 0; Layout.fillWidth: true; wrapMode: Text.WordWrap
                    text: "Nothing is waiting in the next " + rem.horizonDays + " days. The pond is still."
                    color: k.inkLabel; font.italic: true; font.pixelSize: theme ? theme.scale(13) : 13 }
                Text { visible: rem.pending.length > 0 && !cEnabled.checked; Layout.fillWidth: true; wrapMode: Text.WordWrap
                    text: "Reminders are switched off — tick the box below and SAVE, or none of these will be sent."
                    color: k.lineWine; font.italic: true; font.pixelSize: theme ? theme.scale(12) : 12 }
                // ALL of them, in their own scroll well so the settings below stay in view
                ListView {
                    id: pendList
                    Layout.fillWidth: true; Layout.preferredHeight: Math.min(contentHeight, 5.5*42)
                    visible: rem.pending.length > 0
                    clip: true; spacing: 2; boundsBehavior: Flickable.StopAtBounds
                    interactive: contentHeight > height
                    ScrollBar.vertical: NCDEScrollBar {}
                    model: rem.pending
                    delegate: Rectangle {
                        width: pendList.width - 10; height: 40; radius: 6
                        color: pendHov.hovered ? Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.14) : Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.45)
                        Rectangle { width: 4; height: parent.height - 8; y: 4; x: 3; radius: 2
                            color: Cal.cat(modelData.appt.category, k).gem }
                        Column { x: 14; anchors.verticalCenter: parent.verticalCenter; width: parent.width - 20; spacing: 1
                            Text { width: parent.width; elide: Text.ElideRight; text: modelData.appt.title
                                color: k.ink; font.bold: true; font.pixelSize: theme ? theme.scale(13) : 13 }
                            Text { width: parent.width; elide: Text.ElideRight; color: k.inkLabel; font.pixelSize: theme ? theme.scale(11) : 11
                                text: (modelData.due ? "Sent · " : "Nudge " + rem.whenLabel(modelData.fireAt) + "  ·  ")
                                      + (modelData.appt.allDay ? "all day " + rem.whenLabel(modelData.startAt).split(" · ")[0].toLowerCase()
                                                               : "starts " + rem.whenLabel(modelData.startAt))
                                      + (modelData.due ? "" : "  (" + Cal.fmtLead(modelData.lead) + ")") }
                        }
                        HoverHandler { id: pendHov; cursorShape: Qt.PointingHandCursor }
                        TapHandler { onTapped: { rem.visible = false; rem.editRequested(modelData.appt._baseId || modelData.appt.id) } }
                    }
                }
                Text { visible: rem.pending.length > 5; text: rem.pending.length + " reminders in the next " + rem.horizonDays + " days — scroll for all"
                    color: k.inkLabel; font.italic: true; font.pixelSize: theme ? theme.scale(11) : 11 }
                Rectangle { Layout.fillWidth: true; implicitHeight: 1; color: Qt.rgba(k.gilt2.r, k.gilt2.g, k.gilt2.b, 0.4) }
                RowLayout { CheckBox { id: cEnabled } Text { text: "Send me reminders before appointments"; color: ncde.foreground; font.pixelSize: theme ? theme.scale(14) : 14 } }
                ColumnLayout { spacing: 1
                    Text { text: "DEFAULT LEAD TIME"; color: ncde.gilt1; font.pixelSize: theme ? theme.scale(10) : 10; font.letterSpacing: theme ? theme.letterSpacing : 1.5 }
                    ComboBox { id: leadBox; Layout.fillWidth: true; model: ["At time of event","5 minutes before","15 minutes before","30 minutes before","1 hour before","1 day before"]
                        background: RemFieldBg { edTarget: leadBox } }
                }
                MethodRow { id: cdRow; chk: cDesktop; title: "Desktop notification"; sub: "A bubble on this NCDE desktop" }
                CheckBox { id: cDesktop; visible: false }
                MethodRow { id: ceRow; chk: cEmail; title: "Email"; sub: "Reaches any phone via its mail app — most reliable" }
                CheckBox { id: cEmail; visible: false }
                ColumnLayout { visible: cEmail.checked; spacing: 1; Layout.leftMargin: 28
                    Text { text: "EMAIL ADDRESS"; color: ncde.gilt1; font.pixelSize: theme ? theme.scale(10) : 10; font.letterSpacing: theme ? theme.letterSpacing : 1.5 }
                    TextField { id: fEmail; Layout.fillWidth: true; placeholderText: "you@example.com"; color: k.ink
                        background: RemFieldBg { edTarget: fEmail } } }
                MethodRow { id: cnRow; chk: cNtfy; title: "Phone push (ntfy)"; sub: "Free, instant — install the ntfy app & subscribe to your topic" }
                CheckBox { id: cNtfy; visible: false }
                ColumnLayout { visible: cNtfy.checked; spacing: 1; Layout.leftMargin: 28
                    Text { text: "NTFY TOPIC"; color: ncde.gilt1; font.pixelSize: theme ? theme.scale(10) : 10; font.letterSpacing: theme ? theme.letterSpacing : 1.5 }
                    TextField { id: fTopic; Layout.fillWidth: true; placeholderText: "leapfrog-a8f3kd (keep it secret)"; color: k.ink
                        background: RemFieldBg { edTarget: fTopic } } }
                Text { id: note; color: ncde.gilt1; font.italic: true; font.pixelSize: theme ? theme.scale(12) : 12; Layout.alignment: Qt.AlignHCenter }
                RowLayout { Layout.fillWidth: true; spacing: 8
                    Rectangle { Layout.fillWidth: true; implicitHeight: 34; radius: 7; color: ncde.accent; border.color: ncde.gilt2; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "SAVE"; color: ncde.surface; font.pixelSize: theme ? theme.scale(12) : 12; font.letterSpacing: theme ? theme.letterSpacing : 1 }
                        TapHandler { onTapped: rem.save() } }
                    Rectangle { Layout.preferredWidth: 130; implicitHeight: 34; radius: 7; color: ncde.verd; border.color: ncde.gilt2; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "SEND TEST 🐸"; color: ncde.surface; font.pixelSize: theme ? theme.scale(12) : 12 }
                        TapHandler { onTapped: rem.test() } }
                    Rectangle { Layout.preferredWidth: 80; implicitHeight: 34; radius: 7; color: ncde.surfaceAlt; border.color: ncde.gilt2; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "CLOSE"; color: ncde.foreground; font.pixelSize: theme ? theme.scale(12) : 12 }
                        TapHandler { onTapped: rem.visible=false } }
                }
            }
        }
        }

        // CSS .cal-editor-card::before-equivalent — inset:5px double-frame
        Rectangle {
            anchors.fill: remCardBg; anchors.margins: 5; radius: 8
            color: "transparent"; border.width: 1; border.color: k.gilt0
            opacity: 0.5
        }
    }

    function save(){
        calBackend.saveSettings({
            enabled: cEnabled.checked, methodDesktop: cDesktop.checked, methodEmail: cEmail.checked,
            methodNtfy: cNtfy.checked, email: fEmail.text.trim(), ntfyTopic: fTopic.text.trim(),
            defaultLead: [0,5,15,30,60,1440][leadBox.currentIndex]
        });
        note.text = "Saved. The frog remembers. 🐸";
        reloadPending();
        timer.restart();
    }
    function test(){
        // Save first so calBackend.fireReminder uses current methods
        rem.save();
        calBackend.fireReminder("Test reminder", "Your reminders are working.");
        note.text = "Test dispatched via your chosen methods.";
    }
    // stays open after SAVE now — the pending list above is worth reading
    Timer { id: timer; interval: 2500; onTriggered: note.text = "" }

    component MethodRow: Rectangle {
        property var chk; property string title; property string sub
        Layout.fillWidth: true; implicitHeight: 46; radius: 7
        color: Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.5)
        border.color: rowHov.hovered ? ncde.gilt3 : ncde.gilt2; border.width: 1.5
        Behavior on border.color { ColorAnimation { duration: 120 } }
        RowLayout { anchors.fill: parent; anchors.margins: 8; spacing: 9
            CheckBox { checked: chk ? chk.checked : false; onToggled: if(chk) chk.checked = checked }
            ColumnLayout { spacing: 0
                Text { text: title; color: ncde.foreground; font.pixelSize: theme ? theme.scale(14) : 14; font.bold: true }
                Text { text: sub; color: ncde.gilt1; font.pixelSize: theme ? theme.scale(12) : 12 } }
        }
        HoverHandler { id: rowHov }
        TapHandler { onTapped: if(chk) chk.checked = !chk.checked }
    }

    // Mirrors CalEditor.qml's EdFieldBg — same rationale (cheap border-shift
    // focus feedback instead of a MultiEffect blur per field).
    component RemFieldBg: Rectangle {
        property Item edTarget: null
        radius: 6
        color: Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.9)
        border.width: 1.5
        border.color: (edTarget && edTarget.activeFocus) ? k.gilt4 : k.gilt2
        Behavior on border.color { ColorAnimation { duration: 120 } }
    }
}
