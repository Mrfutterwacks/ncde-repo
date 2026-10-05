// AccessibilityTab.qml — text scale, motion, contrast, cursor size.
// Backend: settings.accessibilityTextScale, reduceMotion, highContrast, largerCursor, saveAccessibility().
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: ac; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    function save(){ if(typeof settings.saveAccessibility==="function") settings.saveAccessibility() }
    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"Accessibility"; color:ac.k.wine2; font.family:ac.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"Vision, motion, and interaction adjustments."; color:ac.k.inkSoft; font.family:ac.k.fell; font.italic:true; font.pixelSize:k.md }

            Text { text:"SEEING"; color:ac.k.gilt1; font.family:ac.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Row { width:parent.width; spacing:12
                Text { text:"Script Shift"; width:158; color:ac.k.ink; font.family:ac.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider {
                    // Script Shift (2026-09-24): the same single text dial as Filigree > Fonts
                    // (settings.fontSizeScale, which LaPivot applies everywhere). The old
                    // accessibilityTextScale only ever reached the Settings panel.
                    minValue: 0.75; maxValue: 2.0
                    value: ac.gv(settings,"fontSizeScale",1.0)
                    onMoved: function(v){ settings.fontSizeScale=v; settings.saveFontSettings(); settings.applyFontSettings() }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Sample Ag"
                    color: ac.k.ink
                    font.family: ac.k.gar
                    font.pixelSize: Math.round(13 * ac.gv(settings,"fontSizeScale",1.0))
                }
            }
            Row { width:parent.width; spacing:12
                Text { text:"High contrast"; width:158; color:ac.k.ink; font.family:ac.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle {
                    checked: ac.gv(settings,"highContrast",false)
                    onToggled: function(v){ settings.highContrast=v; ac.save() }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text { text:"May override your Filigree theme"; anchors.verticalCenter: parent.verticalCenter; font.family:ac.k.fell; font.italic:true; font.pixelSize:k.sm; color:ac.k.inkSoft }
            }

            Rectangle { width:parent.width; height:1; color:ac.k.gilt1; opacity:0.4 }
            Text { text:"MOTION"; color:ac.k.gilt1; font.family:ac.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Row { width:parent.width; spacing:12
                Text { text:"Reduce motion"; width:158; color:ac.k.ink; font.family:ac.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle {
                    checked: ac.gv(settings,"reduceMotion",false)
                    onToggled: function(v){ settings.reduceMotion=v; ac.save() }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text { text:"Recommended for motion sensitivity or older hardware"; anchors.verticalCenter: parent.verticalCenter; font.family:ac.k.fell; font.italic:true; font.pixelSize:k.sm; color:ac.k.inkSoft }
            }

            Rectangle { width:parent.width; height:1; color:ac.k.gilt1; opacity:0.4 }
            Text { text:"CURSOR"; color:ac.k.gilt1; font.family:ac.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Row { width:parent.width; spacing:12
                Text { text:"Larger cursor"; width:158; color:ac.k.ink; font.family:ac.k.titles; font.pixelSize:k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle {
                    checked: ac.gv(settings,"largerCursor",false)
                    onToggled: function(v){
                        settings.largerCursor=v
                        settings.cursorSize = v ? 48 : 24
                        ac.save()
                    }
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Item { width:1; height:8 }
        }
    }
}
