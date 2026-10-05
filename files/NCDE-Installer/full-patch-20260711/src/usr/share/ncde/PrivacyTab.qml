// PrivacyTab.qml — location services, lock screen notification preview.
// Backend: settings.locationEnabled, settings.lockScreenNotifPreview, settings.savePrivacy().
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: pr; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    function save(){ if(typeof settings.savePrivacy==="function") settings.savePrivacy() }
    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"Privacy"; color:pr.k.wine2; font.family:pr.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"Location and lock screen settings."; color:pr.k.inkSoft; font.family:pr.k.fell; font.italic:true; font.pixelSize:k.md }

            Text { text:"LOCATION"; color:pr.k.gilt1; font.family:pr.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Row { width:parent.width; spacing:12
                Text { text:"Location Services"; width:200; color:pr.k.ink; font.family:pr.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: pr.gv(settings,"locationEnabled",true); onToggled: function(v){ settings.locationEnabled=v; pr.save() } anchors.verticalCenter: parent.verticalCenter }
                Text { text:"Used by Date & Time for automatic timezone detection"; anchors.verticalCenter: parent.verticalCenter; font.family:pr.k.fell; font.italic:true; font.pixelSize:k.sm; color:pr.k.inkSoft } }

            Rectangle { width:parent.width; height:1; color:pr.k.gilt1; opacity:0.4 }
            Text { text:"LOCK SCREEN"; color:pr.k.gilt1; font.family:pr.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Row { width:parent.width; spacing:12
                Text { text:"Show notification content"; width:200; color:pr.k.ink; font.family:pr.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle { checked: pr.gv(settings,"lockScreenNotifPreview",true); onToggled: function(v){ settings.lockScreenNotifPreview=v; pr.save() } anchors.verticalCenter: parent.verticalCenter }
                Text { text:"When off, only the app name is shown on the lock screen"; anchors.verticalCenter: parent.verticalCenter; font.family:pr.k.fell; font.italic:true; font.pixelSize:k.sm; color:pr.k.inkSoft } }

            Item { width:1; height:8 }
        }
    }
}
