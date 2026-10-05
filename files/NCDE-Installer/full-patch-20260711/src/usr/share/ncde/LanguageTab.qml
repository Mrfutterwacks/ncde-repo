// LanguageTab.qml — system language, region, keyboard layouts.
// Backend: settings.systemLanguage, systemLocale, kbLayouts, activeKbLayout,
//   addKbLayout(code), removeKbLayout(code), setActiveKbLayout(code), saveLocale().
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: lg; clip: true
    property var k: SetTheme
    property bool showAddLayout: false
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    function save(){ if(typeof settings.saveLocale==="function") settings.saveLocale() }

    property var languages: [
        { label:"English (US)", lang:"en_US.UTF-8" },
        { label:"French",       lang:"fr_FR.UTF-8" },
        { label:"Spanish",      lang:"es_ES.UTF-8" },
        { label:"German",       lang:"de_DE.UTF-8" },
        { label:"Portuguese",   lang:"pt_PT.UTF-8" }
    ]
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

    Flickable {
        anchors.fill: parent; contentHeight: col.height; interactive: contentHeight>height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: col; width: parent.width; spacing: 14
            Text { text:"Language & Region"; color:lg.k.wine2; font.family:lg.k.display; font.bold:true; font.pixelSize:k.lg }
            Text { text:"Language, locale, and keyboard layouts."; color:lg.k.inkSoft; font.family:lg.k.fell; font.italic:true; font.pixelSize:k.md }

            // ── LANGUAGE section ──────────────────────────────────────────
            Text { text:"LANGUAGE"; color:lg.k.gilt1; font.family:lg.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2; topPadding:4 }
            Repeater {
                model: lg.languages
                delegate: Rectangle {
                    width: col.width; height: 34; radius: 6
                    color: modelData.lang===lg.gv(settings,"systemLanguage","en_US.UTF-8")
                        ? Qt.rgba(lg.k.gilt0.r,lg.k.gilt0.g,lg.k.gilt0.b,0.2) : "transparent"
                    border.color: modelData.lang===lg.gv(settings,"systemLanguage","en_US.UTF-8")
                        ? lg.k.gilt1 : "transparent"
                    border.width: 1
                    Row {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left; anchors.leftMargin: 12; spacing: 10
                        Text {
                            text: modelData.label
                            color: lg.k.ink; font.family: lg.k.titles; font.pixelSize: k.md
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            visible: modelData.lang===lg.gv(settings,"systemLanguage","en_US.UTF-8")
                            text:"✓"; color:lg.k.gilt1; font.pixelSize:k.md
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    TapHandler {
                        onTapped: {
                            settings.systemLanguage = modelData.lang
                            settings.systemLocale   = modelData.lang
                            lg.save()
                        }
                    }
                }
            }
            Text { text:"Full effect requires logout."; font.family:lg.k.fell; font.italic:true; font.pixelSize:k.sm; color:lg.k.inkSoft }

            // ── REGION section ────────────────────────────────────────────
            Rectangle { width:parent.width; height:1; color:lg.k.gilt1; opacity:0.4 }
            Text { text:"REGION"; color:lg.k.gilt1; font.family:lg.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
            Rectangle {
                width: parent.width; height: 72; radius: 8
                color: lg.k.paper0; border.color: lg.k.gilt1; border.width: 1
                Column {
                    anchors.fill: parent; anchors.margins: 12; spacing: 4
                    Row { spacing: 8
                        Text { text:"Date:";    width:60; color:lg.k.inkSoft; font.family:lg.k.fell; font.pixelSize:k.sm }
                        Text { text: Qt.formatDate(new Date(), "MMMM d, yyyy"); color:lg.k.ink; font.family:lg.k.gar; font.pixelSize:k.sm }
                    }
                    Row { spacing: 8
                        Text { text:"Time:";    width:60; color:lg.k.inkSoft; font.family:lg.k.fell; font.pixelSize:k.sm }
                        Text { text: Qt.formatTime(new Date(), "h:mm AP"); color:lg.k.ink; font.family:lg.k.gar; font.pixelSize:k.sm }
                    }
                    Row { spacing: 8
                        Text { text:"Numbers:"; width:60; color:lg.k.inkSoft; font.family:lg.k.fell; font.pixelSize:k.sm }
                        Text { text:"1,234.56"; color:lg.k.ink; font.family:lg.k.gar; font.pixelSize:k.sm }
                    }
                }
            }
            Text { text:"Region follows system language selection."; font.family:lg.k.fell; font.italic:true; font.pixelSize:k.sm; color:lg.k.inkSoft }

            // ── KEYBOARD LAYOUTS section ──────────────────────────────────
            Rectangle { width:parent.width; height:1; color:lg.k.gilt1; opacity:0.4 }
            Text { text:"KEYBOARD LAYOUTS"; color:lg.k.gilt1; font.family:lg.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }

            Repeater {
                model: settings.kbLayouts
                delegate: Rectangle {
                    id: layoutRow
                    width: col.width; height: 36; radius: 6
                    color: modelData===lg.gv(settings,"activeKbLayout","us")
                        ? Qt.rgba(lg.k.gilt0.r,lg.k.gilt0.g,lg.k.gilt0.b,0.2) : "transparent"
                    border.color: modelData===lg.gv(settings,"activeKbLayout","us") ? lg.k.gilt1 : lg.k.paper2
                    border.width: 1
                    Row {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left; anchors.leftMargin: 12
                        spacing: 10
                        Text { text:modelData; width:36; color:lg.k.inkSoft; font.family:lg.k.mono; font.pixelSize:k.sm; anchors.verticalCenter:parent.verticalCenter }
                        Text { text:lg.layoutName(modelData); width:200; color:lg.k.ink; font.family:lg.k.titles; font.pixelSize:k.md; anchors.verticalCenter:parent.verticalCenter }
                        Text {
                            visible: modelData===lg.gv(settings,"activeKbLayout","us")
                            text:"Active"; color:lg.k.gilt1; font.family:lg.k.fell; font.italic:true; font.pixelSize:k.sm
                            anchors.verticalCenter:parent.verticalCenter
                        }
                    }
                    // Tap row to set active
                    TapHandler {
                        onTapped: {
                            if (modelData!==lg.gv(settings,"activeKbLayout","us"))
                                settings.activeKbLayout = modelData; lg.save()
                        }
                    }
                    // × remove button
                    Rectangle {
                        anchors.right: parent.right; anchors.rightMargin: 12
                        anchors.verticalCenter: parent.verticalCenter
                        width: 22; height: 22; radius: 11
                        visible: settings.kbLayouts.length > 1
                        color: remHov.hovered ? Qt.rgba(lg.k.wine1.r,lg.k.wine1.g,lg.k.wine1.b,0.3) : "transparent"
                        Text { anchors.centerIn: parent; text:"×"; color:lg.k.inkSoft; font.pixelSize:k.lg }
                        HoverHandler { id: remHov }
                        TapHandler { onTapped: { settings.removeKbLayout(modelData); lg.save() } }
                    }
                }
            }

            // Add layout button
            Rectangle {
                width: 130; height: 30; radius: 8
                color: addHov.hovered ? Qt.rgba(lg.k.gilt0.r,lg.k.gilt0.g,lg.k.gilt0.b,0.2) : lg.k.paper0
                border.color: lg.k.gilt1; border.width: 1
                Text { anchors.centerIn: parent; text:"＋ Add Layout"; font.family:lg.k.titles; font.pixelSize:k.sm; color:lg.k.gilt1 }
                HoverHandler { id: addHov }
                TapHandler { onTapped: lg.showAddLayout = !lg.showAddLayout }
            }

            // Layout picker grid
            Grid {
                visible: lg.showAddLayout
                width: parent.width; columns: 3; spacing: 6
                Repeater {
                    model: lg.knownLayouts
                    delegate: Rectangle {
                        property bool alreadyAdded: settings.kbLayouts.indexOf(modelData.code) >= 0
                        width: (col.width - 12) / 3; height: 32; radius: 6
                        color: alreadyAdded
                            ? Qt.rgba(lg.k.gilt0.r,lg.k.gilt0.g,lg.k.gilt0.b,0.12)
                            : pickHov.hovered ? lg.k.paper1 : lg.k.paper0
                        border.color: lg.k.gilt1; border.width: 1
                        opacity: alreadyAdded ? 0.5 : 1.0
                        Column { anchors.centerIn: parent; spacing: 1
                            Text { anchors.horizontalCenter: parent.horizontalCenter; text:modelData.code; font.family:lg.k.mono; font.pixelSize:k.sm; color:lg.k.inkSoft }
                            Text { anchors.horizontalCenter: parent.horizontalCenter; text:modelData.name; font.family:lg.k.fell; font.pixelSize:k.sm; color:lg.k.ink }
                        }
                        HoverHandler { id: pickHov }
                        TapHandler {
                            onTapped: {
                                if (!alreadyAdded) { settings.addKbLayout(modelData.code); lg.save() }
                            }
                        }
                    }
                }
            }

            Item { width:1; height:8 }
        }
    }
}
