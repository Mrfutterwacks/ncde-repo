// NCDESectionLabel.qml — gilt all-caps section heading (Cinzel Decorative).
import QtQuick 2.15
Text {
    id: lbl
    NCDEKit { id: k }
    font.family: k.display
    font.bold: true
    font.pixelSize: k.fs(11)
    font.letterSpacing: 2
    color: k.gilt3

    Accessible.role: Accessible.StaticText
    Accessible.name: lbl.text
}
