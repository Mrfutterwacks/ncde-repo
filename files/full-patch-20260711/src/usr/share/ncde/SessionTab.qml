// SessionTab.qml — autostart + default apps + logout/lock.
// Backend: settings.loadAutostart()/saveAutostart(json) — array of {name,command,enabled}.
//   settings.defaultBrowser, defaultMail, defaultFiles, defaultTerminal; settings.saveDefaults().
//   launcher.logout(); launcher.systemCommand("ncde-portal --lock").
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: ss; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }

    ListModel { id: autostartModel }
    Component.onCompleted: {
        try {
            var raw = settings.loadAutostart()
            var arr = JSON.parse(raw)
            for (var i = 0; i < arr.length; i++) autostartModel.append(arr[i])
        } catch(e) {}
    }
    function setDefault(key, val) {
        if (key === "defaultBrowser")       settings.defaultBrowser  = val
        else if (key === "defaultMail")     settings.defaultMail     = val
        else if (key === "defaultFiles")    settings.defaultFiles    = val
        else if (key === "defaultTerminal") settings.defaultTerminal = val
        settings.saveDefaults()
    }
    function saveAutostart() {
        var arr = []
        for (var i = 0; i < autostartModel.count; i++)
            arr.push({name:autostartModel.get(i).name, command:autostartModel.get(i).command, enabled:autostartModel.get(i).enabled})
        if (typeof settings.saveAutostart === "function") settings.saveAutostart(JSON.stringify(arr, null, 2))
    }

    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"Session"; color:ss.k.wine2; font.family:ss.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"What starts with you, and your default tools."; color:ss.k.inkSoft; font.family:ss.k.fell; font.italic:true; font.pixelSize:k.md }

            Text { text:"AUTOSTART"; color:ss.k.gilt1; font.family:ss.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Column {
                width: parent.width; spacing: 6
                Repeater {
                    model: autostartModel
                    Rectangle {
                        width: parent.width; height: 48; radius:8; color: Qt.rgba(ss.k.paper0.r, ss.k.paper0.g, ss.k.paper0.b, 0.35); border.color:ss.k.gilt1; border.width:1
                        Row { anchors.left:parent.left; anchors.leftMargin:11; anchors.verticalCenter: parent.verticalCenter; spacing:11
                            Rectangle { width:30; height:30; radius:7; border.color:ss.k.gilt1; border.width:1; anchors.verticalCenter: parent.verticalCenter
                                gradient: Gradient { GradientStop{position:0;color:ss.k.paper0} GradientStop{position:1;color:ss.k.paper2} }
                                Text { anchors.centerIn:parent; text:"▸"; color:ss.k.gilt0; font.pixelSize:k.md } }
                            Column { anchors.verticalCenter: parent.verticalCenter
                                // Was read-only Text — "+ Add a program" appended an entry whose
                                // command could never be typed in, so it autostarted nothing.
                                // Inline TextInputs, written back to the model + saved on edit end.
                                TextInput { width: 320; clip: true; selectByMouse: true
                                    text: model.name; color:ss.k.ink; font.family:ss.k.serif; font.pixelSize:k.lg; font.bold:true
                                    onEditingFinished: if (text !== model.name) { autostartModel.setProperty(index,"name",text); ss.saveAutostart() } }
                                TextInput { id: cmdIn; width: 320; clip: true; selectByMouse: true
                                    text: model.command; color:ss.k.inkSoft; font.family:ss.k.mono; font.pixelSize:k.sm
                                    onEditingFinished: if (text !== model.command) { autostartModel.setProperty(index,"command",text); ss.saveAutostart() }
                                    Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                        text: "click to type the command to run"
                                        color:ss.k.inkSoft; opacity: 0.6; font.family:ss.k.fell; font.italic:true; font.pixelSize:k.sm
                                        visible: cmdIn.text === "" && !cmdIn.activeFocus } } } }
                        Row { anchors.right:parent.right; anchors.rightMargin:12; anchors.verticalCenter: parent.verticalCenter; spacing:12
                            NCDEToggle { checked: model.enabled; anchors.verticalCenter: parent.verticalCenter
                                onToggled: function(v){ autostartModel.setProperty(index,"enabled",v); ss.saveAutostart() } }
                            Text { text:"x"; color:ss.k.wine3; font.family:ss.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter
                                TapHandler { onTapped: { autostartModel.remove(index); ss.saveAutostart() } } } }
                    }
                }
                Rectangle {
                    width: parent.width; height: 36; radius:8; color: Qt.rgba(ss.k.paper0.r, ss.k.paper0.g, ss.k.paper0.b, 0.2); border.color:ss.k.gilt2; border.width:1.5
                    Text { anchors.centerIn:parent; text:"+ Add a program"; font.family:ss.k.titles; font.pixelSize:k.sm; color:ss.k.gilt0 }
                    HoverHandler { id: addH }
                    Rectangle { anchors.fill:parent; radius:8; color:ss.k.gilt4; opacity: addH.hovered?0.25:0 }
                    TapHandler { onTapped: { autostartModel.append({name:"New Program", command:"", enabled:true}); ss.saveAutostart() } }
                }
            }

            Rectangle { width:parent.width; height:1; color:ss.k.gilt1; opacity:0.4 }
            Text { text:"DEFAULT APPLICATIONS"; color:ss.k.gilt1; font.family:ss.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Repeater {
                model: [
                    {l:"Web browser", key:"defaultBrowser",  opts:[{d:"Chromium",      v:"chromium"}]},
                    {l:"Mail",        key:"defaultMail",      opts:[{d:"Hummingbird",   v:"hummingbird-courier"}]},
                    {l:"Files",       key:"defaultFiles",     opts:[{d:"Orchidée",      v:"orchidee"}]},
                    {l:"Terminal",    key:"defaultTerminal",  opts:[{d:"NCDE Terminal", v:"ncde-terminal"}]}
                ]
                Column {
                    id: defRow; width: parent.width; spacing: 0
                    property var app: modelData
                    property bool dropOpen: false
                    Row { width: parent.width; height: 38; spacing: 12
                        Text { text: defRow.app.l; width:158; color:ss.k.ink; font.family:ss.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                        Rectangle { width:200; height:30; radius:8; color:ss.k.paper0; border.color:ss.k.gilt1; border.width:1.5; anchors.verticalCenter: parent.verticalCenter
                            Text { anchors.left:parent.left; anchors.leftMargin:12; anchors.verticalCenter: parent.verticalCenter
                                   text: ss.gv(settings, defRow.app.key, defRow.app.opts[0].v)+"  ▾"
                                   font.family:ss.k.gar; font.pixelSize:k.md; color:ss.k.ink }
                            TapHandler { onTapped: defRow.dropOpen = !defRow.dropOpen } }
                    }
                    Rectangle {
                        visible: defRow.dropOpen
                        width: 200; radius: 6; color: ss.k.paper0
                        border.color: ss.k.gilt1; border.width: 1.5; z: 10
                        height: defRow.app.opts.length * 30
                        Column {
                            anchors.fill: parent
                            Repeater {
                                model: defRow.app.opts
                                Rectangle {
                                    width: parent.width; height: 30
                                    color: optHov.hovered ? ss.k.gilt4 : "transparent"
                                    Text { anchors.left:parent.left; anchors.leftMargin:12; anchors.verticalCenter: parent.verticalCenter
                                           text: modelData.d; font.family:ss.k.gar; font.pixelSize:k.md; color:ss.k.ink }
                                    HoverHandler { id: optHov }
                                    TapHandler { onTapped: { ss.setDefault(defRow.app.key, modelData.v); defRow.dropOpen = false } }
                                }
                            }
                        }
                    }
                }
            }

            Rectangle { width:parent.width; height:1; color:ss.k.gilt1; opacity:0.4 }
            Row { width:parent.width; spacing:10
                Rectangle { width:120; height:34; radius:8; border.color:ss.k.gilt0; border.width:2
                    gradient: Gradient { GradientStop{position:0;color:ss.k.wine3} GradientStop{position:1;color:ss.k.wine1} }
                    Text { anchors.centerIn:parent; text:"Log Out"; color:ss.k.gilt5; font.family:ss.k.titles; font.pixelSize:k.md }
                    TapHandler { onTapped: if(typeof launcher.logout==="function") launcher.logout() } }
                Rectangle { width:100; height:34; radius:8; color:ss.k.paper0; border.color:ss.k.gilt1; border.width:1.5
                    Text { anchors.centerIn:parent; text:"Lock"; color:ss.k.gilt0; font.family:ss.k.titles; font.pixelSize:k.md }
                    TapHandler { onTapped: if(typeof launcher.systemCommand==="function") launcher.systemCommand("ncde-portal --lock") } } }
            Item { width:1; height:8 }
        }
    }
}
