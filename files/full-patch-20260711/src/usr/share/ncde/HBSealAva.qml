import QtQuick

Item {
    property string label:    "·"
    property string seedKey:  "x"
    property real   diameter: 42
    property int    fontPx:   16
    property var    pal

    width: diameter; height: diameter

    function sealPair(key) {
        var pairs = [["#2f6f63","#1d3f38"],[ncde.wine4,ncde.wine2],[ncde.gilt2,ncde.gilt0],
                     ["#4f6f8b","#27384a"],["#7a5a8b","#3a2a4a"],["#a85a3a","#5a2a18"]];
        var h = 0;
        for (var i = 0; i < key.length; i++) h = (h * 31 + key.charCodeAt(i)) & 0xffff;
        return pairs[h % pairs.length];
    }

    Rectangle {
        anchors.fill: parent; radius: width / 2
        border.color: pal ? pal.gilt0 : "#c4a44a"; border.width: 1.5
        gradient: Gradient {
            orientation: Gradient.Vertical   // diagonal is not a QQuickGradient orientation (only Horizontal/Vertical); the old enum was undefined and fell back to vertical anyway — this is pixel-identical and stops the journal flood (1,244 errors/session, 2026-07-07)
            GradientStop { position: 0.0; color: sealPair(seedKey)[0] }
            GradientStop { position: 1.0; color: sealPair(seedKey)[1] }
        }
        Text {
            anchors.centerIn: parent; text: label
            font.family: pal ? pal.display : "serif"; font.bold: true; font.pixelSize: fontPx
            color: pal ? pal.paper0 : ncde.surface
        }
    }
}
