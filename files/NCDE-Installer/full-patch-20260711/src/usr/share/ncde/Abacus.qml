// ╔══════════════════════════════════════════════════════════════════════╗
// ║  Abacus.qml — NCDE calculator · Belle Époque                          ║
// ║  Frameless native NCDE window. Pure QML — no C++ backend; arithmetic  ║
// ║  is evaluated in JS here. Context properties (set by main.cpp before  ║
// ║  load): ncde · theme · settings · launcher.                           ║
// ║  TapHandler / HoverHandler / DragHandler only — never MouseArea.      ║
// ╚══════════════════════════════════════════════════════════════════════╝
import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import NCDE.Glia

Window {
    id: win
    visible: true
    width: 420
    height: 620
    minimumWidth: 360
    minimumHeight: 540
    title: "Abacus"
    flags: Qt.Window | Qt.FramelessWindowHint
    color: "transparent"

    // ── GliaTalk global-menu publishing (2026-07-12) ─────────────────────
    // Abacus published NO _NCDE_MENUS (glia half-measure). Publish its real
    // menus via the shared NCDE.Glia plugin so they appear in the top-panel
    // global bar. Every id below maps to an EXISTING Abacus function — no new
    // behavior invented.
    GliaTalkPublisher { id: glia }
    function handleGliaMenu(id) {
        if      (id === 101) Qt.quit()          // Quit
        else if (id === 201) win.clearAll()     // Clear (== AC key)
        else if (id === 202) win.backspace()    // Backspace (== ⌫ key)
        else if (id === 203) win.negate()       // Negate (== ± key)
        else if (id === 204) win.percent()      // Percent (== % key)
        else if (id === 205) win.equals()       // Equals (== = key)
    }
    function publishGliaMenus() {
        glia.attach(win)
        glia.menusJson = JSON.stringify([
            { title: "File", items: [
                { label: "Quit",       id: 101 } ] },
            { title: "Edit", items: [
                { label: "Clear",      id: 201 },
                { label: "Backspace",  id: 202 },
                { label: "Negate",     id: 203 },
                { label: "Percent",    id: 204 },
                { label: "Equals",     id: 205 } ] }
        ])
    }
    Connections {
        target: glia
        function onInvoked(id) { win.handleGliaMenu(id) }
    }

    // ── palette (NCDEKit — responds to dark/light mode) ──────────────────
    NCDEKit { id: k }
    // verd ramp: kit provides single k.verd accent; derive the 4-grade gradient
    // for operator buttons.
    QtObject {
        id: vrd
        readonly property color v1: Qt.darker(k.verd, 2.5)
        readonly property color v2: Qt.darker(k.verd, 1.5)
        readonly property color v4: Qt.lighter(k.verd, 1.5)
    }

    // ── calculator state ───────────────────────────────────────────────────
    property string curr: "0"
    property string prevVal: ""
    property string op: ""
    property bool   awaitingOperand: false
    property bool   justEvaluated: false
    property string statusMsg: "Ready"

    readonly property var opSym: ({ "+":"+", "-":"−", "*":"×", "/":"÷" })

    function fmt(n) {
        if (isNaN(n))     return "Error";
        if (!isFinite(n)) return "∞";
        var s = (Math.round(n*1e10)/1e10).toString();
        if (s.length > 12) s = n.toPrecision(9);
        return s;
    }
    function compute(a,b,o){ a=parseFloat(a); b=parseFloat(b);
        return o==="+"?a+b : o==="-"?a-b : o==="*"?a*b : o==="/"?(b===0?NaN:a/b) : b; }
    function inputDigit(d){
        if (justEvaluated){ curr="0"; justEvaluated=false; }
        if (awaitingOperand){ curr=d; awaitingOperand=false; return; }
        if (curr.length >= 12) return;
        curr = (curr==="0") ? d : curr+d;
    }
    function inputDot(){
        if (justEvaluated){ curr="0"; justEvaluated=false; }
        if (awaitingOperand){ curr="0."; awaitingOperand=false; return; }
        if (curr.indexOf(".")<0) curr += ".";
    }
    function setOp(o){
        if (op!=="" && !awaitingOperand){ var r=compute(prevVal,curr,op); curr=fmt(r); prevVal=curr; }
        else prevVal=curr;
        op=o; awaitingOperand=true; justEvaluated=false; statusMsg="Working…";
    }
    function equals(){
        if (op==="") return;
        var r=compute(prevVal,curr,op); curr=fmt(r);
        statusMsg = (!isFinite(r)) ? "Division by zero" : "= "+curr;
        prevVal=""; op=""; awaitingOperand=false; justEvaluated=true;
    }
    function clearAll(){ curr="0"; prevVal=""; op=""; awaitingOperand=false; justEvaluated=false; statusMsg="Ready"; }
    function negate(){ curr=fmt(parseFloat(curr)*-1); }
    function percent(){
        var v = parseFloat(curr) / 100;
        if (op !== "" && prevVal !== "") v = parseFloat(prevVal) * v;
        curr = fmt(v);
    }
    function backspace(){ if(!justEvaluated && !awaitingOperand){ curr = curr.length>1 ? curr.slice(0,-1) : "0"; } }

    function press(key){
        if (/^[0-9]$/.test(key)) inputDigit(key);
        else if (key===".") inputDot();
        else if (key==="clear") clearAll();
        else if (key==="neg") negate();
        else if (key==="pct") percent();
        else if (key==="=") equals();
        else if (key==="back") backspace();
        else if ("+-*/".indexOf(key)>=0 && key!=="") setOp(key);
    }

    // ── 8-petal floret crest ─────────────────────────────────────────────────
    component Floret: Canvas {
        property color tint:k.gilt4
        antialiasing:true; onTintChanged:requestPaint(); Component.onCompleted:requestPaint()
        onPaint:{
            var ctx=getContext("2d"); ctx.reset();
            var cx=width/2,cy=height/2,R=Math.min(cx,cy)-1;
            ctx.fillStyle=tint;
            ctx.beginPath(); ctx.arc(cx,cy,R*0.22,0,2*Math.PI); ctx.fill();
            for(var i=0;i<8;i++){ ctx.save(); ctx.translate(cx,cy); ctx.rotate(i*Math.PI/4);
                ctx.translate(0,-R*0.56); ctx.scale(0.4,1.0);
                ctx.beginPath(); ctx.arc(0,0,R*0.3,0,2*Math.PI); ctx.fill(); ctx.restore(); }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        radius: 16
        border.color: k.gilt0; border.width: 2

        // Mode-aware ground: Belle Époque warm black (dark) / Concordia aged vellum (light)
        Rectangle { anchors.fill: parent; radius: 16; color: k.panelBg }
        NCDEVellum { anchors.fill: parent; base: "transparent"; intensity: 0.85 }

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            // ── titlebar ──────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 46
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop{position:0;color:k.wine3} GradientStop{position:1;color:k.wine1} }
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:2; color:k.gilt3; opacity:.7 }
                DragHandler { target: null; onActiveChanged: if (active) win.startSystemMove() }

                RowLayout {
                    anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 14; spacing: 10
                    Floret { Layout.preferredWidth: 24; Layout.preferredHeight: 24; tint: k.gilt4 }
                    ColumnLayout { spacing: 2
                        Text { text:"Abacus"; font.family:k.display; font.bold:true; font.pixelSize: Math.round(15 * (theme.fontMedium / 13.0))
                               color:k.gilt5; font.letterSpacing:1.6 }
                        Text { text:"LE CALCULATEUR"; font.family:k.fell; font.italic:true; font.pixelSize: Math.round(10 * (theme.fontMedium / 13.0))
                               color:k.gilt3; font.letterSpacing:3 } }
                    Item { Layout.fillWidth: true }
                    Text {
                        text: "?"
                        font.family: k.titles; font.pixelSize: k.fs(14); font.bold: true
                        color: helpHov.hovered ? k.gilt4 : k.gilt2
                        Behavior on color { ColorAnimation { duration: 100 } }
                        HoverHandler { id: helpHov }
                        TapHandler { onTapped: manual.show() }
                    }
                }
                AbacusManual { id: manual }
            }

            // ── body ──────────────────────────────────────────────────────
            ColumnLayout {
                Layout.fillWidth: true; Layout.fillHeight: true
                Layout.margins: 18; spacing: 16

                // readout
                Rectangle {
                    Layout.fillWidth: true; Layout.preferredHeight: 104
                    radius: 10; border.color: k.gilt0; border.width: 2
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop{position:0;color:k.surfaceHi} GradientStop{position:1;color:k.surface2} }
                    // corner brackets
                    Repeater { model: [[1,1],[1,0],[0,1],[0,0]]
                        Rectangle { width:14; height:14; color:"transparent"
                            border.color:k.gilt3; border.width:2; opacity:.7
                            anchors.top: modelData[0]===1?parent.top:undefined
                            anchors.bottom: modelData[0]===0?parent.bottom:undefined
                            anchors.left: modelData[1]===1?parent.left:undefined
                            anchors.right: modelData[1]===0?parent.right:undefined
                            anchors.margins: 5 } }
                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 16; spacing: 2
                        Text { Layout.fillWidth: true; horizontalAlignment: Text.AlignRight
                               text: (win.prevVal!=="" && win.op!=="") ? (win.prevVal+" "+win.opSym[win.op]) : " "
                               font.family:k.fell; font.italic:true; font.pixelSize: Math.round(16 * (theme.fontMedium / 13.0)); color:k.inkSoft }
                        Item { Layout.fillHeight: true }
                        Text { Layout.fillWidth: true; horizontalAlignment: Text.AlignRight
                               text: win.curr; font.family:k.titles; font.weight:Font.DemiBold
                               font.pixelSize: Math.round(44 * (theme.fontMedium / 13.0)); color:k.dark ? k.gilt4 : k.wine2; elide: Text.ElideLeft }
                    }
                }

                // keypad
                GridLayout {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    columns: 4; rowSpacing: 10; columnSpacing: 10

                    // rows 1–4
                    Repeater {
                        model: [
                            {k:"clear",t:"AC",cls:"fn"}, {k:"neg",t:"±",cls:"fn"}, {k:"pct",t:"%",cls:"fn"}, {k:"/",t:"÷",cls:"op"},
                            {k:"7",t:"7",cls:""},  {k:"8",t:"8",cls:""},  {k:"9",t:"9",cls:""},  {k:"*",t:"×",cls:"op"},
                            {k:"4",t:"4",cls:""},  {k:"5",t:"5",cls:""},  {k:"6",t:"6",cls:""},  {k:"-",t:"−",cls:"op"},
                            {k:"1",t:"1",cls:""},  {k:"2",t:"2",cls:""},  {k:"3",t:"3",cls:""},  {k:"+",t:"+",cls:"op"}
                        ]
                        Rectangle {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            radius: 12; border.width: 2
                            property bool isOp: modelData.cls==="op"
                            property bool isFn: modelData.cls==="fn"
                            property bool opActive: isOp && !win.justEvaluated && win.op===modelData.k && win.awaitingOperand
                            border.color: opActive ? k.gilt0 : (isOp ? vrd.v1 : k.gilt0)
                            gradient: Gradient { orientation: Gradient.Vertical
                                GradientStop{position:0;color: kHov.hovered
                                    ? (opActive? k.gilt4 : isOp? vrd.v4 : isFn? k.surface  : k.surfaceHi)
                                    : (opActive? k.gilt4 : isOp? k.verd  : isFn? k.surface2 : k.surfaceHi)}
                                GradientStop{position:1;color: opActive? k.gilt3 : isOp? vrd.v2 : isFn? k.surface2 : k.surface2} }
                            Text { anchors.centerIn: parent; text: modelData.t
                                   font.family: k.titles; font.weight: Font.DemiBold
                                   font.pixelSize: parent.isOp?Math.round(26 * (theme.fontMedium / 13.0)):(parent.isFn?Math.round(19 * (theme.fontMedium / 13.0)):Math.round(22 * (theme.fontMedium / 13.0)))
                                   color: parent.opActive? k.wine1 : (parent.isOp? k.surfaceHi : (parent.isFn? k.inkLabel : k.ink)) }
                            scale: kTap.pressed ? 0.95 : 1.0
                            Behavior on scale { NumberAnimation { duration: 60 } }
                            HoverHandler { id: kHov }
                            TapHandler { id: kTap; onTapped: win.press(modelData.k) }
                        }
                    }
                    // row 5
                    Rectangle {
                        Layout.fillWidth: true; Layout.fillHeight: true
                        radius: 12; border.color: k.gilt0; border.width: 2
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color: z0Hov.hovered?k.surface:k.surfaceHi} GradientStop{position:1;color:k.surface2} }
                        Text { anchors.centerIn: parent; text:"0"; font.family:k.titles; font.weight:Font.DemiBold; font.pixelSize: Math.round(22 * (theme.fontMedium / 13.0)); color:k.ink }
                        scale: z0Tap.pressed ? 0.97 : 1.0; Behavior on scale { NumberAnimation { duration:60 } }
                        HoverHandler { id: z0Hov } TapHandler { id: z0Tap; onTapped: win.press("0") }
                    }
                    Rectangle {
                        Layout.fillWidth: true; Layout.fillHeight: true
                        radius: 12; border.color: k.gilt0; border.width: 2
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color: bkHov.hovered?k.surface:k.surfaceHi} GradientStop{position:1;color:k.surface2} }
                        Text { anchors.centerIn: parent; text:"⌫"; font.family:k.titles; font.weight:Font.DemiBold; font.pixelSize: Math.round(20 * (theme.fontMedium / 13.0)); color:k.inkSoft }
                        scale: bkTap.pressed ? 0.95 : 1.0; Behavior on scale { NumberAnimation { duration:60 } }
                        HoverHandler { id: bkHov } TapHandler { id: bkTap; onTapped: win.press("back") }
                    }
                    Rectangle {
                        Layout.fillWidth: true; Layout.fillHeight: true
                        radius: 12; border.color: k.gilt0; border.width: 2
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color: dotHov.hovered?k.surface:k.surfaceHi} GradientStop{position:1;color:k.surface2} }
                        Text { anchors.centerIn: parent; text:"."; font.family:k.titles; font.weight:Font.DemiBold; font.pixelSize: Math.round(22 * (theme.fontMedium / 13.0)); color:k.ink }
                        scale: dotTap.pressed ? 0.95 : 1.0; Behavior on scale { NumberAnimation { duration:60 } }
                        HoverHandler { id: dotHov } TapHandler { id: dotTap; onTapped: win.press(".") }
                    }
                    Rectangle {
                        Layout.fillWidth: true; Layout.fillHeight: true
                        radius: 12; border.color: k.wine1; border.width: 2
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color: eqHov.hovered?k.wine4:k.wine3} GradientStop{position:1;color:k.wine1} }
                        Text { anchors.centerIn: parent; text:"="; font.family:k.titles; font.weight:Font.DemiBold; font.pixelSize: Math.round(26 * (theme.fontMedium / 13.0)); color:k.gilt5 }
                        scale: eqTap.pressed ? 0.95 : 1.0; Behavior on scale { NumberAnimation { duration:60 } }
                        HoverHandler { id: eqHov } TapHandler { id: eqTap; onTapped: win.press("=") }
                    }
                }
            }

            // ── statusbar ───────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 24
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop{position:0;color:k.wine2} GradientStop{position:1;color:k.wine1} }
                Rectangle { anchors.top: parent.top; width: parent.width; height:1.5; color:k.gilt3 }
                Row { anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                    Rectangle { width:6;height:6;radius:3; color:k.verd; anchors.verticalCenter: parent.verticalCenter }
                    Text { text: win.statusMsg; font.family:k.fell; font.italic:true; font.pixelSize: Math.round(11 * (theme.fontMedium / 13.0)); color:k.gilt4
                           anchors.verticalCenter: parent.verticalCenter } }
                Text { anchors.right: parent.right; anchors.rightMargin: 14; anchors.verticalCenter: parent.verticalCenter
                       text:"Abacus"; font.family:k.fell; font.italic:true; font.pixelSize: Math.round(11 * (theme.fontMedium / 13.0)); color:k.gilt4 }
            }
        }
    }

    // ── keyboard ───────────────────────────────────────────────────────────
    Item {
        anchors.fill: parent; focus: true
        Keys.onPressed: function(e) {
            var key = e.text;
            if (e.key===Qt.Key_Return || e.key===Qt.Key_Enter || e.key===Qt.Key_Equal) win.press("=");
            else if (e.key===Qt.Key_Escape) win.press("clear");
            else if (e.key===Qt.Key_Backspace) win.press("back");
            else if (e.key===Qt.Key_Delete) win.press("clear");
            else if (key==="%") win.press("pct");
            else if (/^[0-9]$/.test(key)) win.press(key);
            else if (key==="." || key==="+" || key==="-" || key==="*" || key==="/") win.press(key);
            e.accepted = true;
        }
    }

    // Publish menus to the GliaTalk global bar. Abacus had no Window-scope
    // Component.onCompleted, so this is the sole one on the Window.
    Component.onCompleted: win.publishGliaMenus()
}
