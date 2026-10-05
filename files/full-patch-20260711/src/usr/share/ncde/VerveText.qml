// ╔══════════════════════════════════════════════════════════════════════╗
// ║  VerveText.qml — NCDE text editor · Belle Époque writing desk          ║
// ║  Frameless native NCDE window. Context properties (set by main.cpp):   ║
// ║    fileio — FileIO (read/write/list/recent/draft)                      ║
// ║    ncde · theme · settings · launcher                                  ║
// ║  Serif writing surface on a faint-ruled sheet; ink-blue accent.        ║
// ║  TapHandler / HoverHandler / DragHandler only — never MouseArea.       ║
// ╚══════════════════════════════════════════════════════════════════════╝
import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import NCDE.Glia

Window {
    id: win
    visible: true
    width: 980
    height: 680
    minimumWidth: 720
    minimumHeight: 480
    title: "Verve Text"
    flags: Qt.Window | Qt.FramelessWindowHint
    color: "transparent"

    // ── GliaTalk global-menu publishing (2026-07-12) ─────────────────────
    // verve-text published NO _NCDE_MENUS (glia half-measure). Publish its real
    // menus via the shared NCDE.Glia plugin so they appear in the top-panel
    // global bar. Every id below maps to an EXISTING verve function — no new
    // behavior invented.
    GliaTalkPublisher { id: glia }
    function handleGliaMenu(id) {
        if      (id === 101) win.guard("new")      // New (unsaved-guard, == toolbar New)
        else if (id === 102) win.pickerOpen = true // Open…
        else if (id === 103) win.saveCurrent()     // Save
        else if (id === 104) win.saveAsBegin()     // Save As…
        else if (id === 105) win.runAction("quit") // Quit
        else if (id === 201) win.findOpen = true   // Find
    }
    function publishGliaMenus() {
        glia.attach(win)
        glia.menusJson = JSON.stringify([
            { title: "File", items: [
                { label: "New",       id: 101 },
                { label: "Open…", id: 102 },
                { label: "Save",      id: 103 },
                { label: "Save As…", id: 104 },
                { label: "Quit",      id: 105 } ] },
            { title: "Edit", items: [
                { label: "Find",      id: 201 } ] }
        ])
    }
    Connections {
        target: glia
        function onInvoked(id) { win.handleGliaMenu(id) }
    }

    // ── palette (NCDEKit — responds to dark/light mode) ──────────────────
    NCDEKit { id: k }
    // Shared helper — was `Math.round(N * (theme.fontMedium / 13.0))` copy-pasted at
    // ~46 call sites. Identical formula, one definition; zero pixel-size change.
    // (The file's few k.fs(N) call sites are a different, genuinely separate formula
    // — untouched, not merged.)
    function fpx(n) { return Math.round(n * (theme.fontMedium / 13.0)) }
    // Ink-blue ramp: Concordia light = classic navy; Belle Époque dark = cerulean-to-midnight
    QtObject {
        id: vrd
        readonly property color ink1: k.dark ? Qt.darker(k.cer, 2.5)  : "#16233f"
        readonly property color ink2: k.dark ? Qt.darker(k.cer, 1.8)  : "#22365c"
        readonly property color ink3: k.dark ? k.cer                   : "#3a5a8b"
        readonly property color ink4: k.dark ? Qt.lighter(k.cer, 1.3) : "#6f93c0"
        readonly property color ink5: k.dark ? Qt.lighter(k.cer, 1.6) : "#a9c2e0"
    }

    // ── document state ─────────────────────────────────────────────────────
    property string currentPath: ""
    property string docName: "Untitled"
    property bool   modified: false
    property int    zoom: 100
    property bool   wrap: true
    property bool   pickerOpen: true
    property string pendingAction: ""    // for the unsaved guard

    property int editorFontSize: 18   // user-configurable base size
    readonly property int baseLine: 32

    // ── editor preferences (persisted to ~/.config/ncde/verve.json) ────────
    property string editorFont:         k.gar   // font family
    property string paperColorOverride: ""      // "" = auto (theme-responsive)
    property bool   formatOpen:         false

    function loadPrefs() {
        try {
            var obj = JSON.parse(settings.readConfig("verve.json"))
            if (obj.font)     win.editorFont = obj.font
            if (obj.fontSize) win.editorFontSize = obj.fontSize
            if (typeof obj.paper === "string") win.paperColorOverride = obj.paper
        } catch(e) {}
    }
    function savePrefs() {
        settings.saveConfig("verve.json",
            JSON.stringify({ font: win.editorFont, fontSize: win.editorFontSize, paper: win.paperColorOverride }))
    }

    function markModified(v){ modified = v }

    function newDoc(){
        editor.text = ""; currentPath = ""; docName = "Untitled"; markModified(false)
        fileio.clearDraft(); editor.forceActiveFocus()
    }
    function openPath(path){
        var t = fileio.read(path)
        if (fileio.lastError && fileio.lastError.length) { statusMsg = fileio.lastError; return }
        editor.text = t; currentPath = path; docName = fileio.baseName(path)
        markModified(false); fileio.addRecent(path); editor.forceActiveFocus()
        statusMsg = "Opened " + docName
    }
    function saveCurrent(){
        if (currentPath === "") { saveAsBegin(); return }
        if (fileio.write(currentPath, editor.text)) { markModified(false); fileio.clearDraft(); statusMsg = "Saved " + docName }
        else statusMsg = fileio.lastError
    }
    function saveAsBegin(){ saveAsName.text = (docName === "Untitled" ? "Untitled.txt" : docName); saveAsOpen = true }
    function saveAsCommit(){
        var path = fileio.joinDocuments(saveAsName.text)
        if (fileio.write(path, editor.text)) {
            currentPath = path; docName = fileio.baseName(path); markModified(false)
            fileio.clearDraft(); saveAsOpen = false; statusMsg = "Saved " + docName
        } else statusMsg = fileio.lastError
    }

    function toolbarAction(a){
        if (a === "new") guard("new")
        else if (a === "open") pickerOpen = !pickerOpen
        else if (a === "save") saveCurrent()
        else if (a === "saveas") saveAsBegin()
    }

    // unsaved guard
    function guard(action){
        if (modified) { pendingAction = action; guardOpen = true }
        else runAction(action)
    }
    function runAction(action){
        if (action === "new") newDoc()
        else if (action === "quit") Qt.quit()
        else if (action.indexOf("open:") === 0) openPath(action.substring(5))
    }

    property bool saveAsOpen: false
    property bool guardOpen: false
    property bool findOpen: false
    property string statusMsg: "Ready"

    // line/col + counts derived from the editor
    function lineColOf(pos){
        var before = editor.text.substring(0, pos)
        var line = before.split("\n").length
        var col = pos - before.lastIndexOf("\n")
        return [line, col]
    }
    property int wordCount: 0
    Timer {
        id: wordTimer
        interval: 800; repeat: false
        onTriggered: {
            var t = edText.text.trim()
            if (t.length === 0) { win.wordCount = 0; return }
            var mm = t.match(/\S+/g)
            win.wordCount = mm ? mm.length : 0
        }
    }

    // periodic draft autosave (crash safety)
    Timer {
        interval: 4000; running: win.modified; repeat: true
        onTriggered: fileio.saveDraft(win.currentPath, editor.text)
    }

    onClosing: function(close){
        if (win.modified) { close.accepted = false; win.guard("quit") }
    }

    // ── nib crest ────────────────────────────────────────────────────────
    component Nib: Canvas {
        property color tint:k.gilt4
        antialiasing:true; onTintChanged:requestPaint(); Component.onCompleted:requestPaint()
        onPaint:{
            var ctx=getContext("2d"); ctx.reset();
            var s=Math.min(width,height)/100.0; ctx.scale(s,s);
            ctx.fillStyle=tint;
            ctx.beginPath();
            ctx.moveTo(50,6); ctx.bezierCurveTo(58,30,70,44,70,64);
            ctx.bezierCurveTo(70,80,60,92,50,92); ctx.bezierCurveTo(40,92,30,80,30,64);
            ctx.bezierCurveTo(30,44,42,30,50,6); ctx.closePath(); ctx.fill();
            ctx.strokeStyle="#16233f"; ctx.globalAlpha=0.5; ctx.lineWidth=3;
            ctx.beginPath(); ctx.moveTo(50,30); ctx.lineTo(50,78); ctx.stroke();
            ctx.globalAlpha=0.55;
            ctx.beginPath(); ctx.arc(50,60,5,0,2*Math.PI); ctx.fillStyle="#16233f"; ctx.fill();
        }
    }

    // toolbar line-icon
    component Icon: Canvas {
        property string name:""
        property color tint:k.gilt1
        antialiasing:true; onTintChanged:requestPaint(); onNameChanged:requestPaint(); Component.onCompleted:requestPaint()
        onPaint:{
            var ctx=getContext("2d"); ctx.reset(); var s=Math.min(width,height)/24.0; ctx.scale(s,s);
            ctx.strokeStyle=tint; ctx.fillStyle=tint; ctx.lineWidth=1.7; ctx.lineCap="round"; ctx.lineJoin="round";
            var P=function(){ctx.beginPath();};
            if(name==="new"){ P(); ctx.moveTo(6,3);ctx.lineTo(14,3);ctx.lineTo(18,7);ctx.lineTo(18,21);ctx.lineTo(6,21);ctx.closePath();ctx.stroke(); P();ctx.moveTo(14,3);ctx.lineTo(14,7);ctx.lineTo(18,7);ctx.stroke(); }
            else if(name==="open"){ P(); ctx.moveTo(3,6);ctx.lineTo(9,6);ctx.lineTo(11,8);ctx.lineTo(21,8);ctx.lineTo(21,19);ctx.lineTo(3,19);ctx.closePath();ctx.stroke(); P();ctx.moveTo(3,10);ctx.lineTo(21,10);ctx.stroke(); }
            else if(name==="save"){ P(); ctx.moveTo(4,4);ctx.lineTo(17,4);ctx.lineTo(20,7);ctx.lineTo(20,20);ctx.lineTo(4,20);ctx.closePath();ctx.stroke(); P();ctx.moveTo(8,4);ctx.lineTo(8,9);ctx.lineTo(16,9);ctx.lineTo(16,4);ctx.stroke(); P();ctx.rect(8,14,8,6);ctx.stroke(); }
            else if(name==="saveas"){ P(); ctx.moveTo(4,4);ctx.lineTo(15,4);ctx.lineTo(20,9);ctx.lineTo(20,15);ctx.stroke(); P();ctx.moveTo(4,4);ctx.lineTo(4,20);ctx.lineTo(13,20);ctx.stroke(); P();ctx.moveTo(18,15);ctx.lineTo(18,22);ctx.stroke(); P();ctx.moveTo(15,19);ctx.lineTo(21,19);ctx.stroke(); }
            else if(name==="find"){ P(); ctx.arc(11,11,7,0,2*Math.PI);ctx.stroke(); P();ctx.moveTo(16,16);ctx.lineTo(21,21);ctx.stroke(); }
            else if(name==="doc"){ P(); ctx.moveTo(7,3);ctx.lineTo(14,3);ctx.lineTo(18,7);ctx.lineTo(18,21);ctx.lineTo(7,21);ctx.closePath();ctx.stroke(); P();ctx.moveTo(14,3);ctx.lineTo(14,7);ctx.lineTo(18,7);ctx.stroke(); }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"; radius: 16
        border.color: k.gilt0; border.width: 2

        // Mode-aware ground: Belle Époque midnight (dark) / Concordia aged vellum (light)
        Rectangle { anchors.fill: parent; radius: 16; color: k.panelBg }
        NCDEVellum { anchors.fill: parent; base: "transparent"; intensity: 0.85 }

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            // ── titlebar ──────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 46
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop{position:0;color:vrd.ink2} GradientStop{position:1;color:vrd.ink1} }
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:2; color:k.gilt4; opacity:.6 }
                DragHandler { target: null; onActiveChanged: if (active) win.startSystemMove() }

                RowLayout {
                    anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 14; spacing: 10
                    Nib { Layout.preferredWidth: 24; Layout.preferredHeight: 24; tint: k.gilt4 }
                    ColumnLayout { spacing: 2
                        Text { text:"Verve Text"; font.family:k.display; font.bold:true; font.pixelSize: fpx(15)
                               color:k.gilt5; font.letterSpacing:1.6 }
                        Text { text:"L'ÉCRITOIRE"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(10)
                               color:vrd.ink5; font.letterSpacing:3 } }
                    Item { Layout.fillWidth: true }
                    Text {
                        text: "?"
                        font.family: k.titles; font.pixelSize: k.fs(14); font.bold: true
                        color: vHelp.hovered ? k.gilt4 : k.gilt2
                        Behavior on color { ColorAnimation { duration: 100 } }
                        HoverHandler { id: vHelp }
                        TapHandler { onTapped: verveManual.show() }
                    }
                }
                VerveManual { id: verveManual }
                // centred document title + modified dot
                Row {
                    anchors.centerIn: parent; spacing: 8
                    Rectangle { width:8; height:8; radius:4; color:k.rose; opacity: win.modified?1:0
                                anchors.verticalCenter: parent.verticalCenter }
                    Text { text: win.docName; font.family:k.serif; font.italic:true; font.pixelSize: fpx(16); color:k.gilt5
                           anchors.verticalCenter: parent.verticalCenter }
                }
            }

            // ── toolbar ────────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 52
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop{position:0;color:k.surface2} GradientStop{position:1;color:k.panelBg} }
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color:k.gilt1 }
                RowLayout {
                    anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 14; spacing: 8

                    // file-op buttons
                    Repeater {
                        model: [
                            { ic:"new",    label:"New",     act:"new",    prim:false },
                            { ic:"open",   label:"Open",    act:"open",   prim:false },
                            { ic:"save",   label:"Save",    act:"save",   prim:true  },
                            { ic:"saveas", label:"Save As", act:"saveas", prim:false }
                        ]
                        Rectangle {
                            id: tbBtn
                            Layout.preferredHeight: 34; Layout.preferredWidth: tbRow.implicitWidth + 22
                            radius: 8; border.width: 1.5
                            property bool prim: modelData.prim
                            border.color: prim ? vrd.ink1 : (tbHov.hovered ? k.gilt3 : k.gilt1)
                            gradient: Gradient { orientation: Gradient.Vertical
                                GradientStop{position:0;color: tbBtn.prim ? vrd.ink3 : (tbHov.hovered?k.surfaceHi:k.surface)}
                                GradientStop{position:1;color: tbBtn.prim ? vrd.ink2 : k.surface2} }
                            Row { id: tbRow; anchors.centerIn: parent; spacing: 7
                                Icon { width:15; height:15; name: modelData.ic; tint: tbBtn.prim?k.surfaceHi:k.inkLabel
                                       anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData.label; font.family:k.titles; font.pixelSize: fpx(12)
                                       color: tbBtn.prim?k.surfaceHi:k.inkLabel; anchors.verticalCenter: parent.verticalCenter } }
                            HoverHandler { id: tbHov }
                            TapHandler { onTapped: win.toolbarAction(modelData.act) }
                        }
                    }

                    Rectangle { Layout.preferredWidth:1; Layout.preferredHeight:28; color:k.gilt1; opacity:.45 }

                    // find
                    Rectangle {
                        Layout.preferredHeight: 34; Layout.preferredWidth: findRow.implicitWidth + 22
                        radius: 8; border.width: 1.5; border.color: findHov.hovered ? k.gilt3 : k.gilt1
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color: findHov.hovered?k.surfaceHi:k.surface} GradientStop{position:1;color:k.surface2} }
                        Row { id: findRow; anchors.centerIn: parent; spacing: 7
                            Icon { width:15; height:15; name:"find"; tint:k.inkLabel; anchors.verticalCenter: parent.verticalCenter }
                            Text { text:"Find"; font.family:k.titles; font.pixelSize: fpx(12); color:k.inkLabel; anchors.verticalCenter: parent.verticalCenter } }
                        HoverHandler { id: findHov }
                        TapHandler { onTapped: { win.findOpen=true; findInput.forceActiveFocus() } }
                    }

                    Rectangle { Layout.preferredWidth:1; Layout.preferredHeight:28; color:k.gilt1; opacity:.45 }

                    // zoom
                    Row { spacing: 6
                        Rectangle { width:28;height:28;radius:6; border.color:k.gilt1; border.width:1.5; color:k.surfaceHi
                            Text{anchors.centerIn:parent;text:"−";font.family:k.titles;font.bold:true;font.pixelSize: fpx(16);color:k.inkLabel}
                            TapHandler{onTapped: win.zoom=Math.max(60,win.zoom-10)} }
                        Text { text: win.zoom+"%"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(12); color:k.inkSoft
                               width: 42; horizontalAlignment: Text.AlignHCenter; anchors.verticalCenter: parent.verticalCenter }
                        Rectangle { width:28;height:28;radius:6; border.color:k.gilt1; border.width:1.5; color:k.surfaceHi
                            Text{anchors.centerIn:parent;text:"+";font.family:k.titles;font.bold:true;font.pixelSize: fpx(16);color:k.inkLabel}
                            TapHandler{onTapped: win.zoom=Math.min(220,win.zoom+10)} }
                    }
                    Rectangle { Layout.preferredWidth:1; Layout.preferredHeight:28; color:k.gilt1; opacity:.45 }

                    // wrap toggle
                    Row { spacing: 7
                        Rectangle { width:38; height:20; radius:10; anchors.verticalCenter: parent.verticalCenter
                            border.color:k.gilt1; border.width:1.5
                            gradient: Gradient { orientation: Gradient.Vertical
                                GradientStop{position:0;color: win.wrap?vrd.ink3:k.surface2} GradientStop{position:1;color: win.wrap?vrd.ink2:k.surface2} }
                            Rectangle { width:16;height:16;radius:8; y:1; x: win.wrap?19:1
                                gradient: Gradient { orientation: Gradient.Vertical
                                    GradientStop{position:0;color:k.gilt5} GradientStop{position:1;color:k.gilt3} }
                                border.color:k.gilt0; border.width:1
                                Behavior on x { NumberAnimation{duration:160; easing.type:Easing.OutCubic} } }
                            TapHandler{onTapped: win.wrap=!win.wrap} }
                        Text { text:"Wrap"; font.family:k.titles; font.pixelSize: fpx(12); color:k.inkLabel; anchors.verticalCenter: parent.verticalCenter }
                    }
                    Item { Layout.fillWidth: true }

                    Rectangle { Layout.preferredWidth:1; Layout.preferredHeight:28; color:k.gilt1; opacity:.45 }

                    // format toggle "Aa"
                    Rectangle {
                        Layout.preferredHeight: 34; Layout.preferredWidth: 42; radius: 8; border.width: 1.5
                        border.color: win.formatOpen ? k.gilt3 : (fmtHov.hovered ? k.gilt2 : k.gilt1)
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color: win.formatOpen ? k.surfaceHi : (fmtHov.hovered?k.surfaceHi:k.surface)}
                            GradientStop{position:1;color:k.surface2} }
                        Text { anchors.centerIn:parent; text:"Aa"; font.family:k.display; font.pixelSize: fpx(13); color:k.inkLabel }
                        HoverHandler { id: fmtHov }
                        TapHandler { onTapped: win.formatOpen = !win.formatOpen }
                    }
                }
            }

            // ── format bar ─────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: win.formatOpen ? 46 : 0
                clip: true; visible: height > 0
                Behavior on Layout.preferredHeight { NumberAnimation { duration: 180; easing.type: Easing.OutCubic } }
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop { position: 0; color: k.surface }
                    GradientStop { position: 1; color: k.surface2 } }
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: k.gilt1; opacity: 0.6 }

                RowLayout {
                    anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 14; spacing: 10

                    // ── font family ────────────────────────────────────
                    Text { text: "FONT"; font.family: k.titles; font.pixelSize: fpx(9); font.letterSpacing: 2.5; color: k.inkLabel }
                    Repeater {
                        model: [
                            { label: "Garamond",  val: k.gar   },
                            { label: "Cormorant", val: k.serif  },
                            { label: "Fell",      val: k.fell   },
                            { label: "Cinzel",    val: k.titles },
                            { label: "Mono",      val: k.mono   }
                        ]
                        Rectangle {
                            Layout.preferredHeight: 26
                            Layout.preferredWidth: fntT.implicitWidth + 14
                            radius: 6; border.width: 1
                            border.color: win.editorFont === modelData.val ? k.gilt3 : k.gilt1
                            color: win.editorFont === modelData.val ? Qt.rgba(k.gilt3.r,k.gilt3.g,k.gilt3.b,0.18) : "transparent"
                            Text { id: fntT; anchors.centerIn: parent; text: modelData.label
                                   font.family: modelData.val; font.pixelSize: fpx(12)
                                   color: win.editorFont === modelData.val ? k.gilt3 : k.inkSoft }
                            TapHandler { onTapped: { win.editorFont = modelData.val; win.savePrefs() } }
                        }
                    }

                    Rectangle { Layout.preferredWidth: 1; Layout.preferredHeight: 24; color: k.gilt1; opacity: 0.4 }

                    // ── font size ──────────────────────────────────────
                    Text { text: "SIZE"; font.family: k.titles; font.pixelSize: fpx(9); font.letterSpacing: 2.5; color: k.inkLabel }
                    Repeater {
                        model: [14, 16, 18, 20, 24]
                        Rectangle {
                            Layout.preferredHeight: 26
                            Layout.preferredWidth: szT.implicitWidth + 12
                            radius: 6; border.width: 1
                            border.color: win.editorFontSize === modelData ? k.gilt3 : k.gilt1
                            color: win.editorFontSize === modelData ? Qt.rgba(k.gilt3.r,k.gilt3.g,k.gilt3.b,0.18) : "transparent"
                            Text { id: szT; anchors.centerIn: parent; text: modelData
                                   font.family: k.titles; font.pixelSize: fpx(11)
                                   color: win.editorFontSize === modelData ? k.gilt3 : k.inkSoft }
                            TapHandler { onTapped: { win.editorFontSize = modelData; win.savePrefs() } }
                        }
                    }

                    Rectangle { Layout.preferredWidth: 1; Layout.preferredHeight: 24; color: k.gilt1; opacity: 0.4 }

                    // ── paper color ────────────────────────────────────
                    Text { text: "PAPER"; font.family: k.titles; font.pixelSize: fpx(9); font.letterSpacing: 2.5; color: k.inkLabel }
                    Repeater {
                        model: [
                            { label: "Auto",    col: "" },
                            { label: "Cream",   col: "#f9f5ed" },
                            { label: "White",   col: "#fffef8" },
                            { label: "Tan",     col: "#f0e0c0" },
                            { label: "Dusk",    col: "#1e1b14" },
                            { label: "Night",   col: "#1a1d2e" }
                        ]
                        Column { spacing: 3
                            Rectangle {
                                width: 22; height: 22; radius: 11
                                color: modelData.col === "" ? (k.dark ? "#1e1b14" : "#f9f5ed") : modelData.col
                                border.color: win.paperColorOverride === modelData.col ? k.gilt4 : Qt.rgba(k.gilt1.r,k.gilt1.g,k.gilt1.b,0.5)
                                border.width: win.paperColorOverride === modelData.col ? 2 : 1
                                Text { anchors.centerIn: parent; text: modelData.col === "" ? "A" : ""
                                       font.family: k.titles; font.pixelSize: fpx(9)
                                       color: k.dark ? "#f4e9d2" : "#3a2418"; opacity: 0.5 }
                                TapHandler { onTapped: { win.paperColorOverride = modelData.col; win.savePrefs() } }
                            }
                            Text { anchors.horizontalCenter: parent.children[0].horizontalCenter
                                   text: modelData.label; font.family: k.titles; font.pixelSize: fpx(7)
                                   color: k.inkSoft; font.letterSpacing: 0.5 }
                        }
                    }

                    Item { Layout.fillWidth: true }
                }
            }

            // ── main ───────────────────────────────────────────────────────
            RowLayout {
                Layout.fillWidth: true; Layout.fillHeight: true; spacing: 0

                // document picker
                Rectangle {
                    Layout.preferredWidth: win.pickerOpen ? 260 : 0
                    Layout.fillHeight: true; clip: true
                    visible: width > 0
                    Behavior on Layout.preferredWidth { NumberAnimation { duration: 200; easing.type: Easing.OutCubic } }
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop{position:0;color:k.surface2} GradientStop{position:1;color:k.panelBg} }
                    Rectangle { anchors.right: parent.right; width:2; height: parent.height; color:k.gilt1 }
                    ColumnLayout {
                        anchors.fill: parent; spacing: 0
                        Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 56; color:"transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color:k.gilt1 }
                            Column { anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter; spacing: 2
                                Text { text:"Documents"; font.family:k.display; font.bold:true; font.pixelSize: fpx(14); color:vrd.ink2; font.letterSpacing:1 }
                                Text { text: fileio.documentsDir; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:k.inkSoft
                                       elide: Text.ElideMiddle; width: 220 } }
                        }
                        Flickable {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            contentHeight: pickCol.implicitHeight; clip: true
                            Column {
                                id: pickCol; width: parent.width; padding: 8; spacing: 1
                                Text { text:"In ~/Documents"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(10)
                                       font.letterSpacing:2; color:k.inkLabel; leftPadding: 6; bottomPadding: 4 }
                                Repeater {
                                    model: fileio.listDocuments()
                                    Rectangle {
                                        width: pickCol.width - 16; height: 50; radius: 7
                                        property bool sel: win.currentPath === modelData.path
                                        color: sel ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.2) : (dHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : "transparent")
                                        Row { anchors.left: parent.left; anchors.leftMargin: 11; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                            Icon { width:17; height:17; name:"doc"; tint:vrd.ink3; anchors.verticalCenter: parent.verticalCenter }
                                            Column { anchors.verticalCenter: parent.verticalCenter
                                                Text { text: modelData.name; font.family:k.serif; font.pixelSize: fpx(15); color:k.ink
                                                       elide: Text.ElideRight; width: 180 }
                                                Text { text: modelData.info; font.family:k.fell; font.italic:true; font.pixelSize: fpx(10); color:k.inkSoft } } }
                                        HoverHandler { id: dHov }
                                        TapHandler { onTapped: win.guard("open:" + modelData.path) }
                                    }
                                }
                                Item { width:1; height: 6 }
                                Text { text:"Recent"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(10)
                                       font.letterSpacing:2; color:k.inkLabel; leftPadding: 6; bottomPadding: 4
                                       visible: fileio.recent.length > 0 }
                                Repeater {
                                    model: fileio.recent
                                    Rectangle {
                                        width: pickCol.width - 16; height: 34; radius: 7
                                        color: rHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : "transparent"
                                        Row { anchors.left: parent.left; anchors.leftMargin: 11; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                            Icon { width:14; height:14; name:"doc"; tint:k.gilt2; anchors.verticalCenter: parent.verticalCenter }
                                            Text { text: modelData.name; font.family:k.serif; font.pixelSize: fpx(14); color:k.inkSoft
                                                   elide: Text.ElideRight; width: 190; anchors.verticalCenter: parent.verticalCenter } }
                                        HoverHandler { id: rHov }
                                        TapHandler { onTapped: win.guard("open:" + modelData.path) }
                                    }
                                }
                            }
                        }
                    }
                }

                // editor area
                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    color: "transparent"

                    Flickable {
                        id: edFlick
                        anchors.fill: parent; anchors.margins: 26
                        contentWidth: width; contentHeight: Math.max(sheet.height, height)
                        clip: true

                        Rectangle {
                            id: sheet
                            width: Math.min(720, edFlick.width)
                            x: Math.max(0, (edFlick.width - width)/2)
                            height: Math.max(edFlick.height, edText.implicitHeight + 78)
                            color: win.paperColorOverride !== "" ? win.paperColorOverride : (k.dark ? "#1e1b14" : "#f9f5ed"); border.color: k.gilt2; border.width: 1; radius: 3

                            // ruled writing lines + margin rule
                            Canvas {
                                id: rules
                                anchors.fill: parent
                                property real lh: win.baseLine * win.zoom/100
                                property bool isDark: {
                                    if (win.paperColorOverride === "") return k.dark
                                    var c = Qt.color(win.paperColorOverride)
                                    return (c.r * 0.299 + c.g * 0.587 + c.b * 0.114) < 0.5
                                }
                                onLhChanged: repaintRules.restart()
                                onHeightChanged: repaintRules.restart()
                                onWidthChanged: repaintRules.restart()
                                onIsDarkChanged: repaintRules.restart()
                                Component.onCompleted: requestPaint()
                                Timer { id: repaintRules; interval: 200; repeat: false; onTriggered: rules.requestPaint() }
                                onPaint: {
                                    var ctx=getContext("2d"); ctx.reset();
                                    ctx.strokeStyle = isDark ? "rgba(150,180,220,0.15)" : "rgba(58,90,139,0.10)";
                                    ctx.lineWidth=1;
                                    var top=18, x0=44, x1=width-30;
                                    for (var y=top+lh; y<height-10; y+=lh){
                                        ctx.beginPath(); ctx.moveTo(x0,y+0.5); ctx.lineTo(x1,y+0.5); ctx.stroke();
                                    }
                                    ctx.strokeStyle = isDark ? "rgba(220,150,150,0.20)" : "rgba(198,75,99,0.25)";
                                    ctx.beginPath();
                                    ctx.moveTo(30.5,0); ctx.lineTo(30.5,height); ctx.stroke();
                                }
                            }

                            TextEdit {
                                id: edText
                                objectName: "editor"
                                anchors.fill: parent
                                anchors.topMargin: 18; anchors.bottomMargin: 40
                                anchors.leftMargin: 44; anchors.rightMargin: 30
                                font.family: win.editorFont
                                font.pixelSize: Math.round(win.editorFontSize * win.zoom/100)
                                color: k.ink
                                selectionColor: Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.25)
                                selectedTextColor: k.ink
                                wrapMode: win.wrap ? TextEdit.Wrap : TextEdit.NoWrap
                                textFormat: TextEdit.PlainText
                                persistentSelection: true
                                onTextChanged: { win.markModified(true); wordTimer.restart() }
                                // keep caret in view
                                onCursorRectangleChanged: {
                                    var cy = cursorRectangle.y + y
                                    if (cy < edFlick.contentY) edFlick.contentY = cy
                                    else if (cy + cursorRectangle.height > edFlick.contentY + edFlick.height)
                                        edFlick.contentY = cy + cursorRectangle.height - edFlick.height
                                }
                            }
                            // expose as `editor`
                        }
                    }

                    // empty-state hint
                    Text {
                        anchors.centerIn: parent
                        visible: edText.text.length === 0 && !edText.activeFocus
                        text: "Begin writing…"
                        font.family: k.serif; font.italic: true; font.pixelSize: k.fs(20); color: k.inkSoft; opacity: 0.6
                    }

                    // ── find / replace bar ────────────────────────────────────
                    Rectangle {
                        id: findBar
                        visible: win.findOpen
                        anchors.top: parent.top; anchors.right: parent.right
                        anchors.topMargin: 14; anchors.rightMargin: 20
                        width: 320; height: findCol.implicitHeight + 20; radius: 10
                        color: k.surfaceHi; border.color: vrd.ink2; border.width: 2
                        Column {
                            id: findCol
                            anchors.left: parent.left; anchors.right: parent.right
                            anchors.top: parent.top; anchors.margins: 10; spacing: 8
                            Row { width: parent.width; spacing: 7
                                Rectangle { width: parent.width - 28; height: 30; radius: 6; color: k.surface
                                    border.color: k.gilt1; border.width: 1.5
                                    TextInput { id: findInput; anchors.fill: parent; anchors.margins: 7
                                        font.family: k.serif; font.pixelSize: k.fs(15); color: k.ink; clip: true; selectByMouse: true
                                        onAccepted: win.findNext(text)
                                        Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter; text:"Find…"
                                               font.family:k.serif; font.italic:true; font.pixelSize: fpx(15); color:k.inkSoft; opacity:.55
                                               visible: !findInput.text.length && !findInput.activeFocus } } }
                                Text { text:"✕"; color:vrd.ink2; font.pixelSize: fpx(16); anchors.verticalCenter: parent.verticalCenter
                                       TapHandler{onTapped: { win.findOpen=false; edText.forceActiveFocus() }} }
                            }
                            Rectangle { width: parent.width - 28; height: 30; radius: 6; color: k.surface
                                border.color: k.gilt1; border.width: 1.5
                                TextInput { id: replaceInput; anchors.fill: parent; anchors.margins: 7
                                    font.family: k.serif; font.pixelSize: k.fs(15); color: k.ink; clip: true; selectByMouse: true
                                    Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter; text:"Replace with…"
                                           font.family:k.serif; font.italic:true; font.pixelSize: fpx(15); color:k.inkSoft; opacity:.55
                                           visible: !replaceInput.text.length && !replaceInput.activeFocus } } }
                            Row { spacing: 7
                                Repeater {
                                    model: [ {t:"Find Next",a:"next"}, {t:"Replace",a:"one"}, {t:"All",a:"all"} ]
                                    Rectangle { height: 30; width: fbT.implicitWidth + 20; radius: 6
                                        border.color: vrd.ink1; border.width: 1.5
                                        gradient: Gradient { orientation: Gradient.Vertical
                                            GradientStop{position:0;color: fbHov.hovered?vrd.ink4:vrd.ink3} GradientStop{position:1;color:vrd.ink2} }
                                        Text { id: fbT; anchors.centerIn: parent; text: modelData.t
                                               font.family:k.titles; font.pixelSize: fpx(12); color:k.surfaceHi }
                                        HoverHandler { id: fbHov }
                                        TapHandler { onTapped: {
                                            if (modelData.a==="next") win.findNext(findInput.text)
                                            else if (modelData.a==="one") win.replaceOne(findInput.text, replaceInput.text)
                                            else win.replaceAll(findInput.text, replaceInput.text)
                                        } }
                                    }
                                }
                                Text { id: findCountT; text:""; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11)
                                       color:k.inkSoft; anchors.verticalCenter: parent.verticalCenter }
                            }
                        }
                    }
                }
            }

            // ── statusbar ───────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 26
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop{position:0;color:vrd.ink2} GradientStop{position:1;color:vrd.ink1} }
                Rectangle { anchors.top: parent.top; width: parent.width; height:1.5; color:k.gilt3 }
                Row { anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter; spacing: 16
                    Text { text: { var lc = win.lineColOf(edText.cursorPosition); return "Ln " + lc[0] + ", Col " + lc[1] }
                           font.family:k.gar; font.pixelSize: fpx(12); color:k.gilt4 }
                    Text { text: win.wordCount + " words"; font.family:k.gar; font.pixelSize: fpx(12); color:vrd.ink5 }
                    Text { text: edText.text.length + " characters"; font.family:k.gar; font.pixelSize: fpx(12); color:vrd.ink5 }
                }
                Row { anchors.right: parent.right; anchors.rightMargin: 16; anchors.verticalCenter: parent.verticalCenter; spacing: 16
                    Text { text: win.modified ? "Unsaved changes" : "Saved"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color: win.modified?k.gilt4:vrd.ink5 }
                    Text { text:"UTF-8"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:vrd.ink5 }
                    Text { text:"Verve Text v1.0"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:vrd.ink5 }
                }
                // status message (errors/confirmations from statusMsg) — displayed centred
                Text {
                    anchors.centerIn: parent
                    width: parent.width * 0.5
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    text: win.statusMsg
                    font.family: k.fell; font.italic: true; font.pixelSize: fpx(11); color: k.gilt4
                }
            }
        }
    }

    // expose the editor at window scope for the functions above
    property var editor: edText

    // find / replace logic
    function findNext(q){
        if (!q || q.length===0) return
        var from = editor.selectionEnd
        var idx = editor.text.indexOf(q, from)
        if (idx < 0) idx = editor.text.indexOf(q, 0)
        if (idx >= 0){
            editor.forceActiveFocus(); editor.select(idx, idx + q.length)
            var total = editor.text.split(q).length - 1
            findCountT.text = total + " found"
        } else findCountT.text = "none"
    }
    function replaceOne(q, r){
        if (!q) return
        if (editor.selectedText === q){
            var s = editor.selectionStart
            editor.remove(editor.selectionStart, editor.selectionEnd)
            editor.insert(s, r); win.markModified(true)
        }
        findNext(q)
    }
    function replaceAll(q, r){
        if (!q) return
        var n = editor.text.split(q).length - 1
        editor.text = editor.text.split(q).join(r)
        win.markModified(true); findCountT.text = n + " replaced"
    }

    // ── Save-As modal ───────────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.45); visible: win.saveAsOpen; z: 60
        TapHandler { onTapped: win.saveAsOpen = false }
        Rectangle {
            anchors.centerIn: parent; width: 420; height: 180; radius: 10
            color: k.surfaceHi; border.color: k.gilt0; border.width: 2
            TapHandler { }
            Column {
                anchors.fill: parent; anchors.margins: 22; spacing: 16
                Text { text:"Save As"; font.family:k.display; font.bold:true; font.pixelSize: fpx(18); color:vrd.ink2 }
                Text { text:"Name your file in ~/Documents"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(13); color:k.inkSoft }
                Rectangle { width: parent.width; height: 38; radius: 6; color:k.surface; border.color:k.gilt1; border.width:1.5
                    TextInput { id: saveAsName; anchors.fill: parent; anchors.margins: 10
                        font.family:k.serif; font.pixelSize: fpx(17); color:k.ink; clip:true; selectByMouse:true
                        onAccepted: win.saveAsCommit() } }
                Row { spacing: 10; anchors.right: parent.right
                    Rectangle { width: 90; height: 34; radius: 17; color:"transparent"; border.color:k.gilt1; border.width:1.5
                        Text{anchors.centerIn:parent;text:"Cancel";font.family:k.titles;font.pixelSize: fpx(13);color:k.inkLabel}
                        TapHandler{onTapped: win.saveAsOpen=false} }
                    Rectangle { width: 110; height: 34; radius: 17; border.color:vrd.ink1; border.width:1.5
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color:vrd.ink3} GradientStop{position:1;color:vrd.ink2} }
                        Text{anchors.centerIn:parent;text:"Save";font.family:k.titles;font.pixelSize: fpx(13);color:k.surfaceHi}
                        TapHandler{onTapped: win.saveAsCommit()} }
                }
            }
        }
    }

    // ── Unsaved-changes guard ─────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.5); visible: win.guardOpen; z: 70
        TapHandler { }
        Rectangle {
            anchors.centerIn: parent; width: 440; height: 180; radius: 10
            color: k.surfaceHi; border.color: k.gilt0; border.width: 2
            Column {
                anchors.fill: parent; anchors.margins: 24; spacing: 14
                Text { text:"Unsaved changes"; font.family:k.display; font.bold:true; font.pixelSize: fpx(18); color:k.rose }
                Text { text:"“" + win.docName + "” has changes that haven't been saved. Discard them?"
                       font.family:k.serif; font.pixelSize: fpx(16); color:k.ink; width: parent.width; wrapMode: Text.WordWrap }
                Row { spacing: 10; anchors.right: parent.right
                    Rectangle { width: 100; height: 34; radius: 17; color:"transparent"; border.color:k.gilt1; border.width:1.5
                        Text{anchors.centerIn:parent;text:"Cancel";font.family:k.titles;font.pixelSize: fpx(13);color:k.inkLabel}
                        TapHandler{onTapped: { win.guardOpen=false; win.pendingAction="" }} }
                    Rectangle { width: 120; height: 34; radius: 17; border.color:vrd.ink1; border.width:1.5
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color:vrd.ink3} GradientStop{position:1;color:vrd.ink2} }
                        Text{anchors.centerIn:parent;text:"Save first";font.family:k.titles;font.pixelSize: fpx(13);color:k.surfaceHi}
                        TapHandler{onTapped: { win.guardOpen=false; win.saveCurrent(); var a=win.pendingAction; win.pendingAction=""; if(!win.modified) win.runAction(a) }} }
                    Rectangle { width: 110; height: 34; radius: 17; border.color:k.rose; border.width:1.5
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color:k.rose} GradientStop{position:1;color:k.wine4} }
                        Text{anchors.centerIn:parent;text:"Discard";font.family:k.titles;font.pixelSize: fpx(13);color:k.surfaceHi}
                        TapHandler{onTapped: { win.guardOpen=false; win.modified=false; var a=win.pendingAction; win.pendingAction=""; win.runAction(a) }} }
                }
            }
        }
    }

    // ── keyboard shortcuts ────────────────────────────────────────────────────
    // StandardKeys carry multiple platform bindings (Ctrl+S + XF86Save, …);
    // the plural `sequences:` form binds them ALL — singular kept only the
    // first and warned in the journal on every launch.
    Shortcut { sequences: [StandardKey.Save];  onActivated: win.saveCurrent() }
    Shortcut { sequences: [StandardKey.Open];  onActivated: win.pickerOpen = !win.pickerOpen }
    Shortcut { sequences: [StandardKey.New];   onActivated: win.guard("new") }
    Shortcut { sequences: [StandardKey.Find];  onActivated: { win.findOpen=true; findInput.forceActiveFocus() } }
    Shortcut { sequence: "Ctrl+Shift+S";    onActivated: win.saveAsBegin() }
    Shortcut { sequences: [StandardKey.ZoomIn];  onActivated: win.zoom=Math.min(220,win.zoom+10) }
    Shortcut { sequences: [StandardKey.ZoomOut]; onActivated: win.zoom=Math.max(60,win.zoom-10) }
    // Undo/Redo were never wired (2026-07-05 audit) — TextEdit implements both
    // natively, the shortcuts just weren't declared. StandardKey.Redo covers
    // Ctrl+Shift+Z; Ctrl+Y is the second convention Notepad users expect.
    Shortcut { sequences: [StandardKey.Undo]; onActivated: if (edText.canUndo) edText.undo() }
    Shortcut { sequences: [StandardKey.Redo]; onActivated: if (edText.canRedo) edText.redo() }
    Shortcut { sequence: "Ctrl+Y";         onActivated: if (edText.canRedo) edText.redo() }
    Shortcut { sequence: "Escape"; onActivated: { win.findOpen=false; win.saveAsOpen=false } }

    // ── restore an unsaved draft from a prior crash ───────────────────────────
    Component.onCompleted: {
        win.publishGliaMenus()
        win.loadPrefs()
        var d = fileio.loadDraft()
        if (d && d.length) {
            try {
                var obj = JSON.parse(d)
                if (obj.text && obj.text.length) {
                    editor.text = obj.text
                    currentPath = obj.path || ""
                    docName = currentPath ? fileio.baseName(currentPath) : "Recovered draft"
                    markModified(true)
                    statusMsg = "Recovered an unsaved draft"
                }
            } catch(e) {}
        }
        editor.forceActiveFocus()
    }
}
