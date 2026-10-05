// InputTab.qml — keyboard, mouse, touchpad, cursor.
// Backend (guarded): settings.kbLayouts/activeKbLayout/addKbLayout/removeKbLayout
//   (same real backend LanguageTab.qml uses — settings.saveLocale()); kbRepeatDelay,
//   kbRepeatRate, pointerSpeed, touchpadSpeed, naturalScroll, tapToClick, disableWhileTyping,
//   cursorSize; settings.saveInput(). NCDE has no cursor-theme concept (single
//   built-in KithGlass hardware cursor) — no cursorTheme control here.
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: ip; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    function save(){ if(typeof settings.saveInput==="function") settings.saveInput() }
    function saveLocale(){ if(typeof settings.saveLocale==="function") settings.saveLocale() }

    property bool showAddLayout: false
    // Same known-layout list LanguageTab.qml offers — a static display list, not a
    // second backend; both tabs call the identical settings.addKbLayout/removeKbLayout.
    property var knownLayouts: [
        { code:"us", name:"English (US)"       },
        { code:"gb", name:"English (UK)"       },
        { code:"fr", name:"French (AZERTY)"    },
        { code:"de", name:"German (QWERTZ)"    },
        { code:"es", name:"Spanish"            },
        { code:"pt", name:"Portuguese"         },
        { code:"ru", name:"Russian"            },
        { code:"it", name:"Italian"            },
        { code:"nl", name:"Dutch"              },
        { code:"pl", name:"Polish"             },
        { code:"ja", name:"Japanese"           },
        { code:"ko", name:"Korean"             },
        { code:"zh", name:"Chinese (Pinyin)"   },
        { code:"ar", name:"Arabic"             },
        { code:"he", name:"Hebrew"             }
    ]
    function layoutName(code) {
        for (var i=0; i<knownLayouts.length; i++)
            if (knownLayouts[i].code===code) return knownLayouts[i].name
        return code
    }
    property var layoutModel: {
        var out = []
        for (var i=0; i<settings.kbLayouts.length; i++)
            out.push({ code: settings.kbLayouts[i], name: ip.layoutName(settings.kbLayouts[i]) })
        return out
    }
    property int activeLayoutIndex: {
        for (var i=0; i<layoutModel.length; i++)
            if (layoutModel[i].code === ip.gv(settings,"activeKbLayout","us")) return i
        return 0
    }

    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"Input"; color:ip.k.wine2; font.family:ip.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"Keyboard, mouse, touchpad, and cursor."; color:ip.k.inkSoft; font.family:ip.k.fell; font.italic:true; font.pixelSize:k.md }

            Text { text:"KEYBOARD"; color:ip.k.gilt1; font.family:ip.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Row { width:parent.width; spacing:12
                Text { text:"Layout"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEComboBox {
                    width:200; anchors.verticalCenter: parent.verticalCenter
                    model: ip.layoutModel; textRole:"name"; currentIndex: ip.activeLayoutIndex
                    onActivated: function(i){ settings.activeKbLayout = ip.layoutModel[i].code; ip.saveLocale() }
                }
                Rectangle {
                    width:26; height:26; radius:13; anchors.verticalCenter: parent.verticalCenter
                    visible: settings.kbLayouts.length > 1
                    color: remHov.hovered ? Qt.rgba(ip.k.wine1.r,ip.k.wine1.g,ip.k.wine1.b,0.3) : "transparent"
                    Text { anchors.centerIn: parent; text:"×"; color:ip.k.inkSoft; font.pixelSize:k.lg }
                    HoverHandler { id: remHov }
                    TapHandler { onTapped: { settings.removeKbLayout(settings.activeKbLayout); ip.saveLocale() } }
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: addLbl.implicitWidth + 20; height:26; radius:13
                    color: addHov.hovered ? Qt.rgba(ip.k.gilt0.r,ip.k.gilt0.g,ip.k.gilt0.b,0.2) : "transparent"
                    border.color: ip.k.gilt1; border.width:1
                    Text { id: addLbl; anchors.centerIn: parent; text:"＋ add a second layout"; font.family:ip.k.fell; font.italic:true; font.pixelSize:k.sm; color:ip.k.inkSoft }
                    HoverHandler { id: addHov }
                    TapHandler { onTapped: ip.showAddLayout = !ip.showAddLayout }
                } }
            Grid {
                visible: ip.showAddLayout
                width:parent.width; columns:4; spacing:6
                Repeater {
                    model: ip.knownLayouts
                    delegate: Rectangle {
                        property bool alreadyAdded: settings.kbLayouts.indexOf(modelData.code) >= 0
                        width:(c.width-18)/4; height:30; radius:6
                        color: alreadyAdded ? Qt.rgba(ip.k.gilt0.r,ip.k.gilt0.g,ip.k.gilt0.b,0.12) : pickHov.hovered ? ip.k.paper1 : ip.k.paper0
                        border.color: ip.k.gilt1; border.width:1; opacity: alreadyAdded ? 0.5 : 1.0
                        Text { anchors.centerIn: parent; text:modelData.name; font.family:ip.k.fell; font.pixelSize:k.sm; color:ip.k.ink }
                        HoverHandler { id: pickHov }
                        TapHandler { onTapped: { if (!alreadyAdded) { settings.addKbLayout(modelData.code); ip.saveLocale() } } }
                    }
                }
            }
            Row { width:parent.width; spacing:12
                Text { text:"Repeat delay"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue:150; maxValue:600; value: ip.gv(settings,"kbRepeatDelay",300); onMoved: function(v){ settings.kbRepeatDelay=v; ip.save() } anchors.verticalCenter: parent.verticalCenter }
                Text { text: Math.round(ip.gv(settings,"kbRepeatDelay",300))+" ms"; color:ip.k.ink; font.family:ip.k.fell; font.italic:true; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter } }
            Row { width:parent.width; spacing:12
                Text { text:"Repeat rate"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue:10; maxValue:60; value: ip.gv(settings,"kbRepeatRate",30); onMoved: function(v){ settings.kbRepeatRate=v; ip.save() } anchors.verticalCenter: parent.verticalCenter }
                Text { text: Math.round(ip.gv(settings,"kbRepeatRate",30))+"/s"; color:ip.k.ink; font.family:ip.k.fell; font.italic:true; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter } }

            Rectangle { width:parent.width; height:1; color:ip.k.gilt1; opacity:0.4 }
            Text { text:"MOUSE & TOUCHPAD"; color:ip.k.gilt1; font.family:ip.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Row { width:parent.width; spacing:12
                Text { text:"Mouse speed"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue:0; maxValue:100; value: ip.gv(settings,"pointerSpeed",50); onMoved: function(v){ settings.pointerSpeed=v; ip.save() } anchors.verticalCenter: parent.verticalCenter } }
            Row { width:parent.width; spacing:12
                Text { text:"Touchpad speed"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider { minValue:0; maxValue:100; value: ip.gv(settings,"touchpadSpeed",50); onMoved: function(v){ settings.touchpadSpeed=v; ip.save() } anchors.verticalCenter: parent.verticalCenter } }
            Row { width:parent.width; spacing:12
                Text { text:"Natural scroll"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: ip.gv(settings,"naturalScroll",true); onToggled: function(v){ settings.naturalScroll=v; ip.save() } anchors.verticalCenter: parent.verticalCenter } }
            Row { width:parent.width; spacing:12
                Text { text:"Tap to click"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: ip.gv(settings,"tapToClick",true); onToggled: function(v){ settings.tapToClick=v; ip.save() } anchors.verticalCenter: parent.verticalCenter } }
            Row { width:parent.width; spacing:12
                Text { text:"Disable while typing"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: ip.gv(settings,"disableWhileTyping",true); onToggled: function(v){ settings.disableWhileTyping=v; ip.save() } anchors.verticalCenter: parent.verticalCenter } }

            Rectangle { width:parent.width; height:1; color:ip.k.gilt1; opacity:0.4 }
            Text { text:"CURSOR"; color:ip.k.gilt1; font.family:ip.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Row { width:parent.width; spacing:12
                Text { text:"Size"; width:158; color:ip.k.ink; font.family:ip.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                SetSegment { model:["Small","Medium","Large"]; currentIndex: settings.cursorSize <= 24 ? 0 : settings.cursorSize >= 48 ? 2 : 1; onChose: function(i){ var sz=[24,32,48]; settings.cursorSize=sz[i]; ip.save() } anchors.verticalCenter: parent.verticalCenter } }
            Item { width:1; height:8 }
        }
    }
}
