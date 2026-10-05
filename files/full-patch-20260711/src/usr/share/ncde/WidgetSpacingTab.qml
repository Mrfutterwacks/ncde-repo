// WidgetSpacingTab.qml — the gap between Clock/Space/Weather/Stats/Salon in
// the desktop widget column. Deliberately separate from Filigree's own "MEASURE"
// section (font size/spacing) — this ONLY ever touches the space between the
// five desktop widgets, nothing else, and shares no property with font sizing.
// Backend: WidgetSpacingStore (singleton, Qt.labs.settings-backed) — same live
// value DesktopWidget.qml reads, no relaunch needed to see a change apply.
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: ws; clip: true
    property var k: SetTheme

    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: c; width: parent.width; spacing: 14

            Text { text: "Widget Spacing"; color: ws.k.wine2; font.family: ws.k.display; font.bold: true; font.pixelSize: ws.k.lg }
            Text {
                width: parent.width; wrapMode: Text.WordWrap
                text: "The gap between the Clock, Space, Weather, Stats, and Salon widgets on the desktop. This only moves them apart or closer together — it never changes any font size."
                color: ws.k.inkSoft; font.family: ws.k.fell; font.italic: true; font.pixelSize: ws.k.md
            }

            Row {
                width: parent.width; spacing: 12
                Text { text: "Gap"; width: 78; color: ws.k.ink; font.family: ws.k.titles; font.pixelSize: ws.k.md; anchors.verticalCenter: parent.verticalCenter }
                NCDESlider {
                    minValue: 0; maxValue: 40
                    value: WidgetSpacingStore.widgetSpacing
                    onMoved: function(v) { WidgetSpacingStore.widgetSpacing = v }
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    text: Math.round(WidgetSpacingStore.widgetSpacing) + "px"
                    color: ws.k.ink; font.family: ws.k.mono; font.pixelSize: ws.k.sm
                    width: 40; anchors.verticalCenter: parent.verticalCenter
                }
            }

            // Live preview: five plain bars standing in for Clock/Space/Weather/
            // Stats/Salon, spaced by the real live value — what you drag above is
            // exactly what you see here, and exactly what the desktop uses.
            Rectangle {
                width: parent.width; height: preview.height + 20; radius: 8
                color: ws.k.paper1; border.color: ws.k.gilt1; border.width: 1
                Column {
                    id: preview
                    anchors.centerIn: parent
                    width: 120; spacing: WidgetSpacingStore.widgetSpacing
                    Repeater {
                        model: ["Clock", "Space", "Weather", "Stats", "Salon"]
                        Rectangle {
                            width: 120; height: 16; radius: 3
                            color: ws.k.gilt3; opacity: 0.55
                            Text { anchors.centerIn: parent; text: modelData; font.pixelSize: Math.round(9 * (theme.fontMedium / 13.0)); color: ws.k.paper0; font.family: ws.k.titles }
                        }
                    }
                }
            }

            Row {
                spacing: 10
                NCDEButton {
                    text: "Reset to Default"
                    onClicked: WidgetSpacingStore.widgetSpacing = 6
                }
            }

            Item { width: 1; height: 8 }
        }
    }
}
