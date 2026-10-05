// GliaBar.qml — the Glia menu strip. One instance per panel.
//
//   TOP panel    : menuModel.mode === "dbus" + prependMenus (the always-present
//                  NCDE house + Applications/Places/System), then the focused
//                  window's File/Edit/View/Help. collapsible:true → the titles
//                  FURL into nothing; the panel's N icon toggles `expanded`,
//                  and they slide out / back like a CDE drawer.
//   BOTTOM panel : menuModel.mode === "static" → Leap Frog. openUpward:true so
//                  cascades rise out of the bottom pill. Not collapsible.
//
// Menu titles use theme.titleFont. A title's hover/active state is an
// ncde.accent-tinted pill with a gold-leading base. Click a title to open its
// GliaMenuPopup (a parchment scroll); while open, sliding across sibling titles
// switches menus. HoverHandler / TapHandler only.
//
// Type is COMPACT by default (titleSize / brandSize → theme.fontSmall) so a
// chunky display face never overflows a 28px pill.
import QtQuick
import QtQuick.Effects

Item {
    id: bar

    // ── API ──────────────────────────────────────────────────────────────
    property var    menuModel: null          // a GliaMenuModel
    property string brand: ""                 // far-left brand label (bottom bar)
    property bool   openUpward: false         // bottom panel → menus rise
    property bool   showBrand: true
    property Item   menuLayer: null          // in-scene GliaDropMenu from main.qml

    // drawer: when collapsible, `expanded` furls/unfurls the titles with a slide.
    property bool   collapsible: false
    property bool   expanded: !collapsible    // collapsible bars start furled
    // cap: when > 0 the drawer never grows past this width, so a long menu row
    // cannot slide under neighbouring chrome (e.g. the panel clock). Clipped
    // titles show the overflow caret below. 0 = uncapped (default).
    property real   maxDrawerWidth: 0

    // menu-bar type — compact; raise per-panel if you want it larger
    property int    titleSize: theme.fontSmall
    property int    brandSize: theme.fontSmall

    // per-instance text color override — set by callers that have their own
    // section color (e.g. GliaLeapFrogBar uses leapFrogTextColor).
    // Empty string falls through to the global settings.gliaTextColor chain.
    property string overrideTextColor: ""

    readonly property color goldLeading: k.gilt4
    readonly property color goldSoft:    Qt.rgba(k.gilt4.r, k.gilt4.g, k.gilt4.b, 0.45)
    readonly property var   menus: menuModel ? menuModel.menus : []
    readonly property string label: brand !== "" ? brand
                                   : (menuModel ? menuModel.appName : "")

    NCDEKit { id: k }

    // index of the open menu, or -1
    property int activeIndex: -1
    readonly property bool open: activeIndex >= 0

    function toggle()  { if (collapsible) { if (open) close(); expanded = !expanded } }
    function furl()    { close(); expanded = false }
    function unfurl()  { expanded = true }

    // a title flagged { doc: "handbook" } opens a scrollable popup (Help) instead
    // of a cascading menu. Wire this to a GliaDocPopup in the panel.
    signal docRequested(string doc)

    implicitHeight: 28
    implicitWidth: rowLayout.implicitWidth
    clip: true

    function openMenu(i) {
        if (i === activeIndex) { activeIndex = -1; return }   // toggle off
        var m = menus[i]
        if (m && m.doc) { close(); bar.docRequested(m.doc); return }   // Help → doc popup
        if (m && m.actionId !== undefined && !(m.items && m.items.length)) {
            close(); if (menuModel) menuModel.invoke(m.actionId); return   // action title → invoke
        }
        if (menuModel && menuModel.aboutToShow) menuModel.aboutToShow(i)
        activeIndex = i
    }
    function close() { activeIndex = -1; if (menuLayer) menuLayer.close() }

    // furling closes any open menu
    onExpandedChanged: if (!expanded) close()

    Row {
        id: rowLayout
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        spacing: 0

        // ── brand / app name (bottom bar) — also the drawer handle ────────
        Row {
            id: brandRow
            visible: bar.showBrand && bar.label !== ""
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8
            leftPadding: 4
            rightPadding: 8

            // when collapsible, clicking the brand furls/unfurls the menus
            TapHandler { enabled: bar.collapsible; onTapped: bar.toggle() }
            HoverHandler { id: brandHov; enabled: bar.collapsible }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: bar.label
                color: WallInk.inked(bar.goldLeading)
                font.family: theme.titleFont
                font.pixelSize: bar.brandSize
                font.bold: true
                font.letterSpacing: 1.5
                opacity: (bar.collapsible && brandHov.hovered) ? 1.0 : 0.92
            }
            // tiny furl/unfurl caret when collapsible
            Text {
                anchors.verticalCenter: parent.verticalCenter
                visible: bar.collapsible
                text: bar.expanded ? "\u25C2" : "\u25B8"
                color: WallInk.inked(bar.goldSoft)
                font.pixelSize: bar.brandSize
            }
            Rectangle {                                  // gold leading divider
                anchors.verticalCenter: parent.verticalCenter
                visible: bar.expanded
                width: 1; height: bar.height * 0.46
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "transparent" }
                    GradientStop { position: 0.5; color: bar.goldSoft }
                    GradientStop { position: 1.0; color: "transparent" }
                }
            }
        }

        // ── furling drawer: clips the titles to width 0 when collapsed ─────
        Item {
            id: drawer
            anchors.verticalCenter: parent.verticalCenter
            height: bar.height
            clip: true
            width: bar.expanded ? (bar.maxDrawerWidth > 0 ? Math.min(titlesRow.implicitWidth, bar.maxDrawerWidth) : titlesRow.implicitWidth) : 0
            opacity: bar.expanded ? 1 : 0
            Behavior on width   { NumberAnimation { duration: 300; easing.type: Easing.OutCubic } }
            Behavior on opacity { NumberAnimation { duration: 220; easing.type: Easing.OutCubic } }

            Row {
                id: titlesRow
                anchors.verticalCenter: parent.verticalCenter
                spacing: 4
                leftPadding: 2

                Repeater {
                    id: titleRepeater
                    model: bar.menus
                    delegate: Item {
                        id: titleItem
                        anchors.verticalCenter: parent.verticalCenter
                        readonly property bool isSpacer: modelData.spacer === true
                        width: isSpacer ? 13
                                        : titleLabel.implicitWidth + 16
                        height: bar.height - 8

                        readonly property bool isActive: bar.activeIndex === index
                        readonly property bool lit: isActive || titleHov.hovered

                        Rectangle {                          // gold divider for spacer entries
                            visible: titleItem.isSpacer
                            anchors.centerIn: parent
                            width: 1; height: parent.height * 0.62
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: "transparent" }
                                GradientStop { position: 0.5; color: bar.goldSoft }
                                GradientStop { position: 1.0; color: "transparent" }
                            }
                        }
                        HoverHandler {
                            id: titleHov
                            enabled: !titleItem.isSpacer
                            onHoveredChanged: if (hovered && bar.open && !isActive && !(modelData.doc) && !(modelData.actionId)) bar.openMenu(index)
                        }
                        TapHandler { enabled: !titleItem.isSpacer; onTapped: bar.openMenu(index) }

                        Rectangle {                          // accent pill
                            visible: !titleItem.isSpacer
                            anchors.fill: parent
                            radius: height / 2
                            opacity: titleItem.lit ? 1 : 0
                            Behavior on opacity { NumberAnimation { duration: 120; easing.type: Easing.OutCubic } }
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, titleItem.isActive ? 0.5 : 0.30) }
                                GradientStop { position: 1.0; color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, titleItem.isActive ? 0.28 : 0.15) }
                            }
                            border.width: titleItem.isActive ? 1 : 0
                            border.color: bar.goldSoft
                        }

                        Text {
                            id: titleLabel
                            visible: !titleItem.isSpacer
                            anchors.centerIn: parent
                            text: modelData.title || ""
                            color: WallInk.inked(titleItem.lit ? k.ink
                                                 : (bar.overrideTextColor !== "" ? bar.overrideTextColor
                                                 : (settings.gliaTextColor !== "" ? settings.gliaTextColor
                                                 : theme.textColor)))
                            font.family: theme.titleFont
                            font.pixelSize: bar.titleSize
                            font.letterSpacing: 0.5
                            style: theme.textStyle; styleColor: theme.textStyleColor
                            layer.enabled: theme.textShadowEnabled
                            layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                                shadowBlur: theme.textShadowRadius / 32.0
                                shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
                        }
                    }
                }
            }
        }

        // overflow caret: shown while the cap clips titles, so a cut row reads as "more"
        Text {
            anchors.verticalCenter: parent.verticalCenter
            visible: bar.maxDrawerWidth > 0 && bar.expanded && titlesRow.implicitWidth > drawer.width + 1
            text: "›"
            color: bar.goldSoft
            font.pixelSize: bar.titleSize
        }
    }

    // ── in-scene menu layer (GliaDropMenu in main.qml via menuLayer prop) ──
    Connections {
        target: bar.menuLayer
        ignoreUnknownSignals: true
        function onDismissed() { bar.close() }
    }

    onActiveIndexChanged: {
        if (!open) { if (bar.menuLayer) bar.menuLayer.close(); return }
        presentActiveMenu()
    }
    function presentActiveMenu() {
        if (!open || !bar.menuLayer) return
        var t = titleRepeater.itemAt(activeIndex)
        if (!t) { bar.menuLayer.close(); return }
        var m = menus[activeIndex]
        if (!m) { bar.menuLayer.close(); return }
        bar.menuLayer.open(
            m.items || [],
            t,
            bar.openUpward,
            function(id) { if (bar.menuModel) bar.menuModel.invoke(id) }
        )
    }
}
