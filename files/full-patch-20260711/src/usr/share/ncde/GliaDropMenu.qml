// GliaDropMenu.qml — plain in-scene dropdown overlay.
// Parented to the desktop root at z:1500, above all panels.
// Positioned via mapToItem — no global/screen coordinates, no Windows, no pool.
//
// API (called by GliaBar):
//   open(items, titleItem, upward, actionCb)  — show primary card
//   close()                                   — hide everything
// Signal:
//   dismissed()  — emitted when an item is chosen or click-away; GliaBar connects
//                  this to bar.close() so the title pill clears.
import QtQuick
import QtQuick.Effects 6.5

Item {
    id: dropRoot

    // ── public API ────────────────────────────────────────────────
    signal dismissed()

    function open(items, titleItem, upward, actionCb) {
        _actionCb  = actionCb
        _upward    = upward
        _subItems  = []
        _items     = items || []

        // Position primary card relative to THIS item (the overlay root).
        var edgeY  = upward ? 0 : titleItem.height
        var pos    = titleItem.mapToItem(dropRoot, 0, edgeY)
        _anchorX   = pos.x
        _anchorY   = pos.y
    }

    function close() {
        _items    = []
        _subItems = []
        _actionCb = null
    }

    // ── private state ─────────────────────────────────────────────
    property var  _items:   []
    property var  _subItems: []
    property bool _upward:  false
    property real _anchorX: 0
    property real _anchorY: 0
    property var  _actionCb: null

    property real _subX: 0
    property real _subY: 0

    NCDEKit { id: k }

    // palette — FULLY wired to NCDEKit so the live Glia menus follow the whole
    // filigree palette (hue + light/dark), not just a light/dark flag. Card fill
    // tracks k.surface; gold border/separators track k.gilt1; the dim/shortcut/
    // arrow text are k.ink at reduced alpha so they always read on the resulting
    // surface. The former literals matched these token defaults exactly
    // (surface #f6efdc, gilt1 #8a5a20), so the look is preserved while a custom
    // palette now drives the menu colours too.
    readonly property color _cardBg:  Qt.rgba(k.surface.r, k.surface.g, k.surface.b, 0.96)
    readonly property color _cardBdr: Qt.rgba(k.gilt1.r, k.gilt1.g, k.gilt1.b, k.dark ? 0.20 : 0.40)
    readonly property color _sep:     Qt.rgba(k.gilt1.r, k.gilt1.g, k.gilt1.b, k.dark ? 0.15 : 0.30)
    readonly property color _textDim: Qt.rgba(k.ink.r, k.ink.g, k.ink.b, 0.40)
    readonly property color _textSc:  Qt.rgba(k.ink.r, k.ink.g, k.ink.b, 0.50)
    readonly property color _textArr: Qt.rgba(k.ink.r, k.ink.g, k.ink.b, 0.55)

    // Only visible when a menu is open.
    visible: _items.length > 0

    // dismissAll() is called by the click-away layer in main.qml (z:499, below panels)
    function dismissAll() { close(); dismissed() }

    // ── shared row heights ────────────────────────────────────────
    readonly property int _rowH:  26
    readonly property int _sepH:  9
    readonly property int _padV:  4
    readonly property int _minW:  180
    readonly property int _padHL: 12
    readonly property int _padHR: 10

    // ── helper: compute card width from an items array ────────────
    function _cardWidth(items) {
        if (!items || items.length === 0) return _minW
        var maxW = _minW
        for (var i = 0; i < items.length; i++) {
            var it = items[i]
            if (it.separator) continue
            // rough estimate: label chars * ~7px + padding + shortcut
            var w = (it.label ? it.label.length * 7 : 0)
                  + _padHL + _padHR + 8
            if (it.shortcut) w += it.shortcut.length * 6 + 20
            if (it.submenu && it.submenu.length) w += 20
            if (w > maxW) maxW = w
        }
        return maxW
    }

    // ── helper: compute card height from an items array ──────────
    function _cardHeight(items) {
        if (!items || items.length === 0) return 0
        var h = _padV * 2
        for (var i = 0; i < items.length; i++)
            h += items[i].separator ? _sepH : _rowH
        return h
    }

    // ── primary card ──────────────────────────────────────────────
    Rectangle {
        id: primaryCard
        visible: dropRoot._items.length > 0

        readonly property real cardW: dropRoot._cardWidth(dropRoot._items)
        readonly property real cardH: dropRoot._cardHeight(dropRoot._items)

        x: Math.max(4, Math.min(dropRoot._anchorX, dropRoot.width  - cardW - 4))
        y: dropRoot._upward
           ? Math.max(4, dropRoot._anchorY - cardH)
           : Math.min(dropRoot._anchorY, dropRoot.height - cardH - 4)
        width:  cardW
        height: cardH

        color:  dropRoot._cardBg
        border.color: dropRoot._cardBdr
        border.width: 1
        radius: 4

        Column {
            x: 0; y: dropRoot._padV
            width: parent.width

            Repeater {
                model: dropRoot._items
                delegate: Item {
                    width: primaryCard.cardW
                    height: modelData.separator === true ? dropRoot._sepH : dropRoot._rowH

                    // ── separator ───────────────────────────────
                    Rectangle {
                        visible: modelData.separator === true
                        anchors.left: parent.left;  anchors.leftMargin:  8
                        anchors.right: parent.right; anchors.rightMargin: 8
                        anchors.verticalCenter: parent.verticalCenter
                        height: 1
                        color: dropRoot._sep
                    }

                    // ── action row ───────────────────────────────
                    Rectangle {
                        visible: modelData.separator !== true
                        anchors.fill: parent
                        anchors.margins: 2
                        radius: 3
                        color: (rowHov.hovered && modelData.enabled !== false)
                               ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.28)
                               : "transparent"
                        Behavior on color { ColorAnimation { duration: 80 } }
                    }

                    // ── check-state glyph (checkable menu items) ──
                    // Sits in the existing left pad gutter; shown when the
                    // row's model entry is checked (e.g. Leap Frog View menu).
                    Text {
                        visible: modelData.separator !== true
                              && modelData.checkable === true
                              && modelData.checked === true
                        anchors.left: parent.left
                        anchors.leftMargin: 2
                        anchors.verticalCenter: parent.verticalCenter
                        text: "✓"
                        color: WallInk.inked(modelData.enabled === false
                               ? dropRoot._textDim
                               : (settings.gliaTextColor !== "" ? settings.gliaTextColor : theme.textColor))
                        font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                        font.pixelSize: theme.fontSmall
                    }

                    Text {
                        visible: modelData.separator !== true
                        anchors.left: parent.left
                        anchors.leftMargin: dropRoot._padHL
                        anchors.right: rowTail.left
                        anchors.rightMargin: 4
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.label || ""
                        elide: Text.ElideRight
                        color: WallInk.inked(modelData.enabled === false
                               ? dropRoot._textDim
                               : (settings.gliaTextColor !== "" ? settings.gliaTextColor : theme.textColor))
                        font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                        font.pixelSize: theme.fontMedium
                        style: theme.textStyle; styleColor: theme.textStyleColor
                        layer.enabled: theme.textShadowEnabled
                        layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                            shadowBlur: theme.textShadowRadius / 32.0
                            shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
                    }

                    // shortcut or submenu arrow
                    Item {
                        id: rowTail
                        visible: modelData.separator !== true
                        anchors.right: parent.right
                        anchors.rightMargin: dropRoot._padHR
                        anchors.verticalCenter: parent.verticalCenter
                        width: hasSub ? 12 : scText.implicitWidth
                        height: parent.height

                        // modelData.submenu is often undefined (menu items are free to omit
                        // the key entirely) -- JS && returns the first falsy operand as-is,
                        // so `undefined && ...` yields undefined, not false, and QML throws
                        // "Unable to assign [undefined] to bool" on every such item.
                        readonly property bool hasSub: !!(modelData.submenu && modelData.submenu.length > 0)

                        Text {
                            id: scText
                            visible: !rowTail.hasSub && (modelData.shortcut || "") !== ""
                            text: modelData.shortcut || ""
                            color: WallInk.inked(dropRoot._textSc)
                            font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                            font.pixelSize: theme.fontSmall
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            visible: rowTail.hasSub
                            text: "▶"
                            color: WallInk.inked(dropRoot._textArr)
                            font.pixelSize: theme.fontSmall
                            anchors.centerIn: parent
                        }
                    }

                    HoverHandler {
                        id: rowHov
                        enabled: modelData.separator !== true && modelData.enabled !== false
                        onHoveredChanged: {
                            if (!hovered) return
                            if (modelData.submenu && modelData.submenu.length > 0) {
                                // anchor sub-card to the right edge of this row
                                var rp = parent.mapToItem(dropRoot, primaryCard.cardW, 0)
                                dropRoot._subX = rp.x
                                dropRoot._subY = rp.y
                                dropRoot._subItems = modelData.submenu
                            } else {
                                dropRoot._subItems = []
                            }
                        }
                    }
                    TapHandler {
                        enabled: modelData.separator !== true
                              && modelData.enabled !== false
                              && !(modelData.submenu && modelData.submenu.length > 0)
                        onTapped: {
                            if (dropRoot._actionCb) dropRoot._actionCb(modelData.actionId)
                            dropRoot.dismissAll()
                        }
                    }
                }
            }
        }
    }

    // ── submenu card (one level) ──────────────────────────────────
    Rectangle {
        id: subCard
        visible: dropRoot._subItems.length > 0

        readonly property real cardW: dropRoot._cardWidth(dropRoot._subItems)
        readonly property real cardH: dropRoot._cardHeight(dropRoot._subItems)

        // Flip left if not enough room to the right
        readonly property bool flipLeft:
            (dropRoot._subX + cardW + 4) > dropRoot.width

        x: flipLeft
           ? Math.max(4, dropRoot._subX - primaryCard.cardW - cardW + 4)
           : Math.min(dropRoot._subX, dropRoot.width - cardW - 4)
        y: Math.max(4, Math.min(dropRoot._subY, dropRoot.height - cardH - 4))
        width:  cardW
        height: cardH

        color:  dropRoot._cardBg
        border.color: dropRoot._cardBdr
        border.width: 1
        radius: 4

        Column {
            x: 0; y: dropRoot._padV
            width: parent.width

            Repeater {
                model: dropRoot._subItems
                delegate: Item {
                    width: subCard.cardW
                    height: modelData.separator === true ? dropRoot._sepH : dropRoot._rowH

                    Rectangle {
                        visible: modelData.separator === true
                        anchors.left: parent.left;  anchors.leftMargin:  8
                        anchors.right: parent.right; anchors.rightMargin: 8
                        anchors.verticalCenter: parent.verticalCenter
                        height: 1
                        color: dropRoot._sep
                    }

                    Rectangle {
                        visible: modelData.separator !== true
                        anchors.fill: parent
                        anchors.margins: 2
                        radius: 3
                        color: (subHov.hovered && modelData.enabled !== false)
                               ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.28)
                               : "transparent"
                        Behavior on color { ColorAnimation { duration: 80 } }
                    }

                    Text {
                        visible: modelData.separator !== true
                        anchors.left: parent.left
                        anchors.leftMargin: dropRoot._padHL
                        anchors.right: subTail.left
                        anchors.rightMargin: 4
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.label || ""
                        elide: Text.ElideRight
                        color: WallInk.inked(modelData.enabled === false
                               ? dropRoot._textDim
                               : (settings.gliaTextColor !== "" ? settings.gliaTextColor : theme.textColor))
                        font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                        font.pixelSize: theme.fontMedium
                        style: theme.textStyle; styleColor: theme.textStyleColor
                        layer.enabled: theme.textShadowEnabled
                        layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                            shadowBlur: theme.textShadowRadius / 32.0
                            shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
                    }

                    Item {
                        id: subTail
                        visible: modelData.separator !== true
                        anchors.right: parent.right
                        anchors.rightMargin: dropRoot._padHR
                        anchors.verticalCenter: parent.verticalCenter
                        width: subSc.implicitWidth
                        height: parent.height

                        Text {
                            id: subSc
                            visible: (modelData.shortcut || "") !== ""
                            text: modelData.shortcut || ""
                            color: WallInk.inked(dropRoot._textSc)
                            font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                            font.pixelSize: theme.fontSmall
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    HoverHandler { id: subHov; enabled: modelData.separator !== true && modelData.enabled !== false }
                    TapHandler {
                        enabled: modelData.separator !== true && modelData.enabled !== false
                        onTapped: {
                            if (dropRoot._actionCb) dropRoot._actionCb(modelData.actionId)
                            dropRoot.dismissAll()
                        }
                    }
                }
            }
        }
    }
}
