// NotificationsTab.qml — DND, position, quiet hours, per-app.
// Backend: settings.dnd, notifPosition, quietHoursOn, quietFrom, quietTo — all real, and quiet
//   hours + DND are now actually enforced in NotificationManager::notify() (2026-07-01), not just
//   persisted. notifications.notifyApps (list {name,icon,meta,on}) grows for distinct application
//   names received through org.freedesktop.Notifications; direct QML notifications use their title
//   as the fallback application identity. notifications.setAppNotify(name,on) gates future events.
//   settings.saveNotifications().
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: nt; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    function save(){ if(typeof settings.saveNotifications==="function") settings.saveNotifications() }
    readonly property var apps: gv(notifications,"notifyApps",[])
    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"Notifications"; color:nt.k.wine2; font.family:nt.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"Where they appear, and when to keep quiet."; color:nt.k.inkSoft; font.family:nt.k.fell; font.italic:true; font.pixelSize:k.md }

            Text { text:"GENERAL"; color:nt.k.gilt1; font.family:nt.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Row { width:parent.width; spacing:12
                Text { text:"Do not disturb"; width:158; color:nt.k.ink; font.family:nt.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: nt.gv(settings,"dnd",false); onToggled: function(v){ settings.dnd=v; nt.save() } anchors.verticalCenter: parent.verticalCenter }
                Text { text:"Silence everything but alarms"; anchors.verticalCenter: parent.verticalCenter; font.family:nt.k.fell; font.italic:true; font.pixelSize:k.sm; color:nt.k.inkSoft } }
            Row { width:parent.width; spacing:12
                Text { text:"Position"; width:158; color:nt.k.ink; font.family:nt.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                SetSegment { model:["Top-L","Top-R","Bot-R"]; currentIndex: nt.gv(settings,"notifPosition",1); onChose: function(i){ settings.notifPosition=i; nt.save() } anchors.verticalCenter: parent.verticalCenter } }

            Rectangle { width:parent.width; height:1; color:nt.k.gilt1; opacity:0.4 }
            Text { text:"QUIET HOURS"; color:nt.k.gilt1; font.family:nt.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Row { width:parent.width; spacing:12
                Text { text:"Enabled"; width:158; color:nt.k.ink; font.family:nt.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: nt.gv(settings,"quietHoursOn",true); onToggled: function(v){ settings.quietHoursOn=v; nt.save() } anchors.verticalCenter: parent.verticalCenter } }
            Row { width:parent.width; spacing:12
                Text { text:"From"; width:158; color:nt.k.ink; font.family:nt.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDETimePicker { id: fromPicker; anchors.verticalCenter: parent.verticalCenter
                    value: nt.gv(settings,"quietFrom","10:00 PM")
                    onPicked: function(v){ settings.quietFrom = v; nt.save() } }
                Text { text:"to"; width:24; horizontalAlignment: Text.AlignHCenter; color:nt.k.ink; font.family:nt.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDETimePicker { id: toPicker; anchors.verticalCenter: parent.verticalCenter
                    value: nt.gv(settings,"quietTo","7:00 AM")
                    onPicked: function(v){ settings.quietTo = v; nt.save() } } }

            Rectangle { width:parent.width; height:1; color:nt.k.gilt1; opacity:0.4 }
            Text { text:"PER-APPLICATION"; color:nt.k.gilt1; font.family:nt.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Repeater {
                model: nt.apps
                Rectangle {
                    width: parent.width; height: 48; radius:8; color: Qt.rgba(nt.k.paper0.r, nt.k.paper0.g, nt.k.paper0.b, 0.35); border.color:nt.k.gilt1; border.width:1
                    Row { anchors.left:parent.left; anchors.leftMargin:11; anchors.verticalCenter: parent.verticalCenter; spacing:11
                        Rectangle { width:30; height:30; radius:7; border.color:nt.k.gilt1; border.width:1; anchors.verticalCenter: parent.verticalCenter
                            gradient: Gradient { GradientStop{position:0;color:nt.k.paper0} GradientStop{position:1;color:nt.k.paper2} }
                            Text { anchors.centerIn:parent; text: modelData.icon; color:nt.k.gilt0; font.family:nt.k.titles; font.pixelSize:k.md } }
                        Column { anchors.verticalCenter: parent.verticalCenter
                            Text { text: modelData.name; color:nt.k.ink; font.family:nt.k.serif; font.pixelSize:k.lg; font.bold:true }
                            Text { text: modelData.meta; color:nt.k.inkSoft; font.family:nt.k.fell; font.italic:true; font.pixelSize:k.sm } } }
                    NCDEToggle { anchors.right:parent.right; anchors.rightMargin:14; anchors.verticalCenter: parent.verticalCenter
                        checked: modelData.on
                        onToggled: function(v){ if(typeof notifications.setAppNotify==="function") notifications.setAppNotify(modelData.name, v) } }
                }
            }
            Item { width:1; height:8 }
        }
    }
}
