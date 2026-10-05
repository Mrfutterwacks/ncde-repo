// GliaMenuPopup.qml — fixed pool of GliaMenuWindow instances (never destroyed).
// Uses Instantiator (not Repeater) because GliaMenuWindow is a Window, not an Item.
// Switching menus only flips active + reassigns items/x/y — no map/unmap blink.
import QtQuick 2.15

Item {
    id: popup
    property var  items: []
    property bool openUpward: false
    signal actionTriggered(var actionId)
    signal dismissAll()
    readonly property int poolSize: 5
    property var levels: []

    function present(menuItems, sx, sy, up) { openUpward = up; levels = [ { items: menuItems, x: sx, y: sy } ] }
    function dismiss() { levels = [] }

    Instantiator {
        id: pool
        model: popup.poolSize
        delegate: GliaMenuWindow {
            readonly property var lvl: (index < popup.levels.length) ? popup.levels[index] : null
            active:     lvl !== null
            items:      lvl ? lvl.items : []
            screenX:    lvl ? lvl.x : 0
            screenY:    lvl ? lvl.y : 0
            openUpward: popup.openUpward
            depth:      index
            onActivated: function(id) { popup.actionTriggered(id) }
            onDismissAll: popup.dismissAll()
            onRequestSubmenu: function(d, subItems, sx, sy, toLeft) {
                var nl = popup.levels.slice(0, d + 1)
                if (nl.length < popup.poolSize) nl.push({ items: subItems, x: sx, y: sy })
                popup.levels = nl
            }
            onPruneBelow: function(d) {
                if (popup.levels.length > d + 1) popup.levels = popup.levels.slice(0, d + 1)
            }
        }
    }
}
