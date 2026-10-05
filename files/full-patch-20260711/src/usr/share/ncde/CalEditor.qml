// CalEditor.qml — appointment editor dialog for Leap Frog Ledger (NCDE).
// Used by LeapFrogLedger.qml as `CalEditor { id: editor }`. Calls calBackend.
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects
import "cal-logic.js" as Cal

Item {
    id: ed
    anchors.fill: parent
    visible: false
    property string editId: ""

    function openNew(dateObj, startMin, endMin) {
        editId = ""; dateBad = false; fTitle.text = ""; fDate.text = Cal.iso(dateObj);
        fStart.text = Cal.fmtTime(startMin, false); fEnd.text = Cal.fmtTime(endMin || startMin+60, false);
        fAllday.checked = false; fLoc.text = ""; fNotes.text = "";
        // the Reminders dialog's DEFAULT LEAD TIME is what a new appointment starts with
        // (was hard-wired to 15 min, so that setting never did anything)
        var dl = calBackend.settings ? calBackend.settings.defaultLead : 15;
        fRepeat.currentIndex = 0; fRemind.currentIndex = Math.max(0, [0,5,15,30,60,1440].indexOf(dl==null?15:dl)); cat = "azure";
        timeBad = false;
        delBtn.visible = false; ed.visible = true; fTitle.forceActiveFocus();
    }
    function openEdit(id) {
        var a = null, list = calBackend.appointments;
        for (var i=0;i<list.length;i++) if (list[i].id===id) { a=list[i]; break; }
        if (!a) return;
        editId = a.id; dateBad = false; timeBad = false; fTitle.text = a.title||""; fDate.text = a.date;
        fStart.text = Cal.fmtTime(a.start,false); fEnd.text = Cal.fmtTime(a.end,false);
        fAllday.checked = !!a.allDay; fLoc.text = a.location||""; fNotes.text = a.notes||"";
        fRepeat.currentIndex = ["none","daily","weekly","monthly","yearly"].indexOf(a.repeat||"none");
        fRemind.currentIndex = [0,5,15,30,60,1440].indexOf(a.reminder==null?15:a.reminder); if(fRemind.currentIndex<0)fRemind.currentIndex=2;
        cat = a.category||"azure"; delBtn.visible = true; ed.visible = true; fTitle.forceActiveFocus();
    }
    property string cat: "azure"
    property bool dateBad: false
    property bool timeBad: false
    function parseHM(s){ return Cal.parseHM(s); }

    // Enter saves from any single-line field, Esc cancels (Notes keeps Enter for newlines)
    Keys.onEscapePressed: ed.visible = false

    NCDEKit { id: k }

    // CSS #ed-backdrop: rgba(26,18,8,.55) — a modal scrim dims regardless of theme,
    // it isn't text-on-surface, so it stays a fixed dark tint (never adaptive).
    Rectangle { anchors.fill: parent; color: Qt.rgba(0.102, 0.071, 0.031, 0.55); TapHandler { onTapped: ed.visible=false } }

    Item {
        id: editorCardWrap
        anchors.centerIn: parent; width: 440
        height: Math.min(contentCol.implicitHeight + 36, ed.height - 40)

        // CSS .cal-editor-card box-shadow:0 24px 60px rgba(0,0,0,.5)
        MultiEffect {
            anchors.fill: cardBg; source: cardBg; shadowEnabled: true
            shadowColor: Qt.rgba(0,0,0,0.5); shadowBlur: 1.0
            shadowHorizontalOffset: 0; shadowVerticalOffset: 24
        }

        Rectangle {
            id: cardBg
            anchors.fill: parent
            radius: 12; border.color: k.gilt2; border.width: 2
            gradient: Gradient {
                GradientStop { position: 0; color: k.surfaceHi }
                GradientStop { position: 1; color: k.surface2 }
            }
            clip: true

        Flickable {
            anchors.fill: parent; anchors.margins: 18
            contentWidth: width; contentHeight: contentCol.implicitHeight
            clip: true; boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: NCDEScrollBar {}

            ColumnLayout {
                id: contentCol; width: parent.width; spacing: 9
                Text { text: ed.editId ? "Edit Appointment" : "Inscribe Appointment"; color: k.lineWine
                    font.family: theme?theme.titleFont:"serif"; font.pixelSize: theme ? theme.scale(19) : 19; font.bold: true; Layout.alignment: Qt.AlignHCenter }
                EdField { label: "Title";   TextField { id: fTitle; Layout.fillWidth: true; color: k.ink
                    placeholderText: "A proper name — Plato insists"; onAccepted: ed.save(); Keys.onEscapePressed: ed.visible = false
                    background: EdFieldBg { edTarget: fTitle } } }
                RowLayout { Layout.fillWidth: true; spacing: 10
                    EdField { label: "Date"; Layout.fillWidth: true; TextField { id: fDate; Layout.fillWidth: true; inputMask: "9999-99-99"; color: k.ink
                        onTextEdited: ed.dateBad = false; onAccepted: ed.save()
                        background: EdFieldBg { edTarget: fDate; bad: ed.dateBad } } }
                    RowLayout { CheckBox { id: fAllday } Text { text: "All day"; color: ncde.foreground; font.pixelSize: theme ? theme.scale(13) : 13 } }
                }
                RowLayout { Layout.fillWidth: true; spacing: 10; visible: !fAllday.checked
                    EdField { label: "Start"; Layout.fillWidth: true; TextField { id: fStart; enabled: !fAllday.checked; Layout.fillWidth: true; inputMask: "99:99"; color: k.ink
                        onTextEdited: ed.timeBad = false; onAccepted: ed.save()
                        background: EdFieldBg { edTarget: fStart; bad: ed.timeBad && ed.parseHM(fStart.text) === null } } }
                    EdField { label: "End";   Layout.fillWidth: true; TextField { id: fEnd; enabled: !fAllday.checked; Layout.fillWidth: true; inputMask: "99:99"; color: k.ink
                        onTextEdited: ed.timeBad = false; onAccepted: ed.save()
                        background: EdFieldBg { edTarget: fEnd; bad: ed.timeBad } } }
                }
                EdField { label: "Location"; TextField { id: fLoc; Layout.fillWidth: true; color: k.ink; onAccepted: ed.save()
                    background: EdFieldBg { edTarget: fLoc } } }
                RowLayout { Layout.fillWidth: true; spacing: 10
                    EdField { label: "Repeat"; Layout.fillWidth: true; ComboBox { id: fRepeat; Layout.fillWidth: true; model: ["Does not repeat","Daily","Weekly","Monthly","Yearly"]
                        background: EdFieldBg { edTarget: fRepeat } } }
                    EdField { label: "Reminder"; Layout.fillWidth: true; ComboBox { id: fRemind; Layout.fillWidth: true; model: ["At time","5 min before","15 min before","30 min before","1 hr before","1 day before"]
                        background: EdFieldBg { edTarget: fRemind } } }
                }
                EdField { label: "Notes"; TextArea { id: fNotes; Layout.fillWidth: true; Layout.preferredHeight: 48; color: k.ink
                    background: EdFieldBg { edTarget: fNotes } } }
                RowLayout { spacing: 7
                    Repeater {
                        model: Object.keys(Cal.CATEGORIES).map(function(id) { return [id, Cal.cat(id, k).gem] })
                        // CSS .ed-cat :hover scale(1.12); .sel border-color:ink + ring 0 0 0 2px gold-br
                        delegate: Item {
                            width: 28; height: 28
                            readonly property bool sel: ed.cat===modelData[0]
                            Rectangle {
                                anchors.centerIn: parent; width: 28; height: 28; radius: 14
                                color: "transparent"; border.width: 2; border.color: k.gilt4
                                visible: parent.sel
                            }
                            Rectangle {
                                anchors.centerIn: parent; width: 24; height: 24; radius: 12; color: modelData[1]
                                border.color: parent.sel ? k.ink : "transparent"; border.width: 2
                                scale: catHov.hovered ? 1.12 : 1.0
                                Behavior on scale { NumberAnimation { duration: 120 } }
                            }
                            HoverHandler { id: catHov }
                            TapHandler { onTapped: ed.cat = modelData[0] }
                        }
                    }
                }
                RowLayout { Layout.fillWidth: true; spacing: 8
                    Rectangle { Layout.fillWidth: true; implicitHeight: 34; radius: 7; color: ncde.accent; border.color: ncde.gilt2; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "INSCRIBE"; color: ncde.surface; font.family: theme?theme.titleFont:"serif"; font.pixelSize: theme ? theme.scale(12) : 12; font.letterSpacing: theme ? theme.letterSpacing : 1 }
                        TapHandler { onTapped: ed.save() } }
                    Rectangle { Layout.preferredWidth: 90; implicitHeight: 34; radius: 7; color: ncde.surfaceAlt; border.color: ncde.gilt2; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "CANCEL"; color: ncde.foreground; font.pixelSize: theme ? theme.scale(12) : 12 }
                        TapHandler { onTapped: ed.visible=false } }
                    Rectangle { id: delBtn; Layout.preferredWidth: 80; implicitHeight: 34; radius: 7; color: ncde.wine3; border.color: ncde.gilt2; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "DELETE"; color: ncde.surface; font.pixelSize: theme ? theme.scale(12) : 12 }
                        TapHandler { onTapped: { calBackend.deleteAppointment(ed.editId); ed.visible=false } } }
                }
                Text { visible: ed.timeBad; Layout.alignment: Qt.AlignHCenter
                    text: "Times are 24-hour HH:MM, and the end must come after the start."
                    color: k.lineWine; font.italic: true; font.pixelSize: theme ? theme.scale(12) : 12
                }
            }
        }
        }

        // CSS .cal-editor-card::before — inset:5px double-frame
        Rectangle {
            anchors.fill: cardBg; anchors.margins: 5; radius: 8
            color: "transparent"; border.width: 1; border.color: k.gilt0
            opacity: 0.5
        }
    }

    function save(){
        // refuse impossible dates (2026-07-21: the input mask allowed 2026-99-99
        // straight through to the backend) — the field turns wine-red instead.
        var dm = /^(\d{4})-(\d{2})-(\d{2})$/.exec(fDate.text.trim())
        var dOk = false
        if (dm) { var dt = new Date(+dm[1], +dm[2]-1, +dm[3])
            dOk = dt.getFullYear()===+dm[1] && dt.getMonth()===+dm[2]-1 && dt.getDate()===+dm[3] }
        if (!dOk) { ed.dateBad = true; return }
        ed.dateBad = false;
        var allDay = fAllday.checked;
        var s = ed.parseHM(fStart.text); var e = ed.parseHM(fEnd.text);
        if (allDay) { if (s===null) s=0; if (e===null) e=s; }
        // 2026-09-24: "25:99" used to sail through, and an end before the start was
        // silently replaced — now both fields ring wine-red and nothing is written.
        else if (s===null || e===null || e<=s) { ed.timeBad = true; return }
        ed.timeBad = false;
        calBackend.upsertAppointment({
            id: ed.editId || undefined, title: fTitle.text.trim()||"Untitled",
            date: fDate.text, start: s, end: e, allDay: allDay,
            location: fLoc.text.trim(), notes: fNotes.text.trim(),
            repeat: ["none","daily","weekly","monthly","yearly"][fRepeat.currentIndex],
            reminder: [0,5,15,30,60,1440][fRemind.currentIndex], category: ed.cat
        });
        ed.visible = false;
    }

    component EdField: ColumnLayout {
        property string label: ""
        default property alias content: holder.data
        spacing: 1
        Text { text: parent.label.toUpperCase(); color: ncde.gilt1; font.family: theme?theme.titleFont:"serif"; font.pixelSize: theme ? theme.scale(10) : 10; font.letterSpacing: theme ? theme.letterSpacing : 1.5 }
        ColumnLayout { id: holder; Layout.fillWidth: true }
    }

    // CSS .ed-field input/select/textarea — 1.5px gold border, radius 6, parchment
    // fill; :focus → gold-br border (approximates the CSS focus glow via a border
    // color shift + Behavior, rather than a per-field MultiEffect blur pass — this
    // project has repeatedly hit real CPU-pin issues from unnecessary shader work,
    // so a cheap border animation is used for 8 simultaneous field instances).
    component EdFieldBg: Rectangle {
        property Item edTarget: null
        property bool bad: false   // wine-red ring when save() refuses the value
        radius: 6
        color: Qt.rgba(k.surfaceHi.r, k.surfaceHi.g, k.surfaceHi.b, 0.9)
        border.width: 1.5
        border.color: bad ? k.lineWine : ((edTarget && edTarget.activeFocus) ? k.gilt4 : k.gilt2)
        Behavior on border.color { ColorAnimation { duration: 120 } }
    }
}
