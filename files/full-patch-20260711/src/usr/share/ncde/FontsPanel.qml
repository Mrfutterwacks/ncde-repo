import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    id: panel

    property string previewFamily: ncde.uiFont
    property real previewSize: ncde.uiFontSize * ncde.uiScale

    function updatePreview(family, sizePt) {
        previewFamily = family;
        previewSize = sizePt * ncde.uiScale;
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 16
        anchors.leftMargin: 36
        anchors.rightMargin: 36
        anchors.bottomMargin: 20
        spacing: 0

        // big preview
        Item {
            Layout.fillWidth: true; Layout.preferredHeight: 130
            ColumnLayout {
                anchors.centerIn: parent; spacing: 4
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "NCDE Desktop"
                    font.family: panel.previewFamily
                    font.pixelSize: panel.previewSize
                    font.letterSpacing: 2
                    color: theme.textColor
                    renderType: Text.NativeRendering
                }
                RowLayout {
                    Layout.alignment: Qt.AlignHCenter; spacing: 14
                    Text { text: "\u2014"; color: ncde.gilt0; font.pixelSize: theme.fontLarge }
                    Text {
                        text: "the quill of the kingdom"
                        font.family: ncde.titleFont; font.weight: Font.Bold
                        font.pixelSize: theme.fontLarge; font.letterSpacing: 4; color: ncde.gilt0
                    }
                    Text { text: "\u2014"; color: ncde.gilt0; font.pixelSize: theme.fontLarge }
                }
            }
        }

        // divider
        Rectangle {
            Layout.fillWidth: true; implicitHeight: 1
            color: ncde.gilt0; opacity: 0.25
            Layout.bottomMargin: 8
        }

        // GENERAL
        FontRow {
            label: "GENERAL"
            catFont: ncde.uiFont
            catSize: ncde.uiFontSize
            onDoFont: function(f) { ncde.setUiFont(f); ncde.saveTheme(settings.configBase + "active-theme.json") }
            onDoSize: function(s) { ncde.uiFontSize = s; ncde.saveTheme(settings.configBase + "active-theme.json") }
        }

        Rectangle { Layout.fillWidth: true; implicitHeight: 1; color: ncde.gilt0; opacity: 0.16 }

        // FIXED
        FontRow {
            label: "FIXED"; monoFilter: true
            catFont: ncde.monoFont
            catSize: 11
            onDoFont: function(f) { ncde.monoFont = f; ncde.saveTheme(settings.configBase + "active-theme.json") }
            onDoSize: function(s) { }
        }

        Rectangle { Layout.fillWidth: true; implicitHeight: 1; color: ncde.gilt0; opacity: 0.16 }

        // TITLE
        FontRow {
            label: "TITLE"
            catFont: ncde.titleFont
            catSize: ncde.titleFontSize
            onDoFont: function(f) { ncde.setTitleFont(f); ncde.saveTheme(settings.configBase + "active-theme.json") }
            onDoSize: function(s) { ncde.titleFontSize = s; ncde.saveTheme(settings.configBase + "active-theme.json") }
        }

        Rectangle { Layout.fillWidth: true; implicitHeight: 1; color: ncde.gilt0; opacity: 0.16 }

        // SMALL
        FontRow {
            label: "SMALL"
            catFont: ncde.smallFont
            catSize: ncde.smallFontSize
            onDoFont: function(f) { ncde.setSmallFont(f); ncde.saveTheme(settings.configBase + "active-theme.json") }
            onDoSize: function(s) { ncde.smallFontSize = s; ncde.saveTheme(settings.configBase + "active-theme.json") }
        }

        Item { Layout.fillHeight: true }
    }

    // inline font picker Popup (shared across all FontRow instances)
    Popup {
        id: fontPickerPopup
        x: (parent.width - width) / 2; y: (parent.height - height) / 2
        width: 320; height: 380; modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        background: Rectangle {
            color: ncde.surface; border.color: ncde.gilt0; border.width: 2; radius: 4
            Rectangle { anchors.fill: parent; anchors.margins: 4; color: "transparent"; border.color: ncde.gilt3; border.width: 1; radius: 2 }
        }

        property var onPick: null
        property bool monoFilter: false

        ColumnLayout {
            anchors.fill: parent; anchors.margins: 12; spacing: 8

            NCDEField {
                id: fontSearch
                Layout.fillWidth: true
                placeholder: "Search fonts\u2026"
            }

            Rectangle {
                Layout.fillWidth: true; Layout.fillHeight: true
                color: ncde.surface; border.color: ncde.gilt0; border.width: 1; clip: true

                ListView {
                    id: fontList
                    anchors.fill: parent; anchors.margins: 2
                    model: {
                        var all = settings.systemFonts();
                        var search = fontSearch.text.toLowerCase();
                        var filtered = [];
                        for (var i = 0; i < all.length; i++) {
                            if (search !== "" && all[i].toLowerCase().indexOf(search) < 0) continue;
                            if (fontPickerPopup.monoFilter) {
                                var n = all[i].toLowerCase();
                                if (n.indexOf("mono") < 0 && n.indexOf("code") < 0 && n.indexOf("typewriter") < 0 && n.indexOf("terminal") < 0) continue;
                            }
                            filtered.push(all[i]);
                        }
                        return filtered;
                    }
                    delegate: Item {
                        width: fontList.width; height: 36
                        Rectangle {
                            anchors.fill: parent; color: listHov.hovered ? ncde.wine2 : "transparent"
                            HoverHandler { id: listHov }
                        }
                        Text {
                            anchors.left: parent.left; anchors.leftMargin: 12; anchors.verticalCenter: parent.verticalCenter
                            text: modelData; font.family: modelData; font.pixelSize: theme.fontMedium
                            color: listHov.hovered ? ncde.gilt5 : ncde.wine2; elide: Text.ElideRight
                        }
                        TapHandler {
                            onTapped: {
                                if (fontPickerPopup.onPick) fontPickerPopup.onPick(modelData);
                                fontPickerPopup.close();
                            }
                        }
                    }
                    ScrollBar.vertical: NCDEScrollBar {}
                }
            }
        }
    }

    // FontRow component — one per category
    component FontRow: Item {
        id: row
        implicitHeight: 56; implicitWidth: parent ? parent.width : 400

        property string label: "CATEGORY"
        property string catFont: "sans-serif"
        property int catSize: 11
        property bool monoFilter: false

        signal doFont(string family)
        signal doSize(int size)

        RowLayout {
            anchors.fill: parent; spacing: 12

            Text {
                Layout.preferredWidth: 120; Layout.alignment: Qt.AlignVCenter
                text: row.label; font.family: ncde.titleFont; font.weight: Font.Bold
                font.pixelSize: theme.fontSmall; font.letterSpacing: 3; color: ncde.gilt0
            }

            OrnDropdown {
                Layout.fillWidth: true; Layout.preferredHeight: 42
                model: settings.systemFonts()
                currentFontFamily: row.catFont
                currentIndex: {
                    var all = settings.systemFonts();
                    for (var i = 0; i < all.length; i++) {
                        if (all[i] === row.catFont) return i;
                    }
                    return 0;
                }
                onActivated: function(idx, text) { row.doFont(text); }
            }

            Row {
                spacing: 2; Layout.alignment: Qt.AlignVCenter
                Rectangle {
                    width: 22; height: 22; radius: 2
                    color: ncde.wine2; border.color: ncde.gilt3; border.width: 1
                    Text { anchors.centerIn: parent; text: "\u2212"; color: ncde.gilt5; font.bold: true; font.pixelSize: theme.fontSmall }
                    TapHandler { onTapped: { if (row.catSize > 6) row.doSize(row.catSize - 1); } }
                }
                Rectangle {
                    width: 40; height: 22; radius: 2
                    color: ncde.panelBg; border.color: ncde.gilt0; border.width: 1
                    Text { anchors.centerIn: parent; text: row.catSize + "pt"; color: ncde.gilt5; font.family: ncde.bodyFont; font.pixelSize: theme.fontSmall; font.bold: true }
                }
                Rectangle {
                    width: 22; height: 22; radius: 2
                    color: ncde.wine2; border.color: ncde.gilt3; border.width: 1
                    Text { anchors.centerIn: parent; text: "+"; color: ncde.gilt5; font.bold: true; font.pixelSize: theme.fontSmall }
                    TapHandler { onTapped: { if (row.catSize < 32) row.doSize(row.catSize + 1); } }
                }
            }

            Item { Layout.preferredWidth: 8 }

            Rectangle {
                Layout.preferredWidth: 80; implicitHeight: 26; Layout.alignment: Qt.AlignVCenter; radius: 2
                color: "transparent"; border.color: ncde.gilt0; border.width: 1
                Text { anchors.centerIn: parent; text: "Choose\u2026"; color: ncde.gilt0; font.family: ncde.bodyFont; font.pixelSize: theme.fontSmall; font.italic: true }
                TapHandler {
                    onTapped: {
                        fontPickerPopup.onPick = function(f) { row.doFont(f); };
                        fontPickerPopup.monoFilter = row.monoFilter;
                        fontPickerPopup.open();
                    }
                }
            }
        }
    }
}
