// AboutTab.qml — version, hardware, manual.
// Backend (guarded): ncde.version; lelan.hostname; lelan.systemInfo {release, compositor, cpu, memory,
//   gpu, disk} — sensed by Sentinel (GetSystemInfo), exposed by Lelan (2026-09-30). These used to be
//   read from ncde (NCDEEngine = the colour engine), which never had them, so the grid only ever showed
//   its placeholders. Manual: NCDESettingsManual (Agatha's digital book).
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: ab; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    readonly property var si: gv(lelan, "systemInfo", ({}))
    function info(key, fallback) { var v = si ? si[key] : undefined; return (v !== undefined && v !== "") ? v : fallback }

    NCDESettingsManual { id: agatha }

    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14
            Text { text:"About"; color:ab.k.wine2; font.family:ab.k.display; font.bold:true; font.pixelSize:ab.k.lg }
            Text { text:"Oh, you found me. Good."; color:ab.k.inkSoft; font.family:ab.k.fell; font.italic:true; font.pixelSize:ab.k.md }

            Column {
                width: parent.width; spacing: 8; topPadding: 8
                Rectangle {
                    width: 80; height: 80; radius: 40; anchors.horizontalCenter: parent.horizontalCenter
                    border.color: ab.k.gilt0; border.width: 2
                    gradient: Gradient { GradientStop{position:0;color:ab.k.gilt4} GradientStop{position:0.65;color:ab.k.gilt2} GradientStop{position:1;color:ab.k.gilt0} }
                    Text { anchors.centerIn: parent; text:"N"; font.family:ab.k.display; font.bold:true; font.pixelSize: Math.round(34 * (theme.fontMedium / 13.0)); color:ab.k.wine1 }
                }
                Text { text:"NCDE"; anchors.horizontalCenter: parent.horizontalCenter; font.family:ab.k.display; font.bold:true; font.pixelSize: Math.round(22 * (theme.fontMedium / 13.0)); color:ab.k.wine2; font.letterSpacing:2 }
                Text { text:"New Common Desktop Environment · '" + ab.info("release","NCDE Poseidon").replace(/^NCDE\s+/, "") + "'"; anchors.horizontalCenter: parent.horizontalCenter
                       font.family:ab.k.fell; font.italic:true; font.pixelSize:ab.k.md; color:ab.k.inkSoft }

                Grid {
                    anchors.horizontalCenter: parent.horizontalCenter; columns: 2; columnSpacing: 18; rowSpacing: 6; topPadding: 10
                    property var rowData: [
                        ["Version",   ab.gv(ncde,"version","Poseidon")],
                        ["Compositor",ab.info("compositor","LaPivot · Qt 6 · X11")],
                        ["Device",    ab.gv(lelan,"hostname","") || "ncde-machine"],
                        ["Processor", ab.info("cpu","--")],
                        ["Memory",    ab.info("memory","--")],
                        ["Graphics",  ab.info("gpu","--")],
                        ["Disk",      ab.info("disk","--")]
                    ]
                    Repeater {
                        model: parent.rowData.length * 2
                        Text {
                            property int r: Math.floor(index/2)
                            property bool isKey: index % 2 === 0
                            text: parent.rowData[r][isKey?0:1]
                            horizontalAlignment: isKey ? Text.AlignRight : Text.AlignLeft
                            width: isKey ? 110 : 220
                            font.family: isKey ? ab.k.titles : ab.k.gar
                            font.pixelSize: isKey ? ab.k.sm : ab.k.md
                            color: isKey ? ab.k.gilt1 : ab.k.ink
                        }
                    }
                }

                Item { width: 1; height: 4 }
                Rectangle {
                    width: 220; height: 32; radius: 8; anchors.horizontalCenter: parent.horizontalCenter
                    color: ab.k.paper0; border.color: ab.k.gilt1; border.width: 1.5
                    Text { anchors.centerIn: parent; text:"Consult the Operating Manual"; font.family:ab.k.titles; font.pixelSize:ab.k.sm; color:ab.k.gilt0 }
                    TapHandler { onTapped: agatha.show() }
                }
            }
            Item { width:1; height:8 }
        }
    }
}
