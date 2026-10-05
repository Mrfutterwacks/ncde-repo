import QtQuick 2.15

Item {
    id: intellihide

    property bool topHovered: false
    property bool dockHovered: false
    property bool btmHovered: false
    property bool widgetHovered: false
    property bool topRevealed: true
    property bool dockRevealed: true
    property bool btmRevealed: true
    property bool widgetRevealed: true

    function anyHovered() { return topHovered || dockHovered || btmHovered || widgetHovered }

    function revealAll() {
        topRevealed = true; dockRevealed = true; btmRevealed = true; widgetRevealed = true
        hideTimer.stop()
    }
    // Operator design (2026-07-06): "max is what makes everything go away." The shell hides
    // only while windowMgr.coveringCount > 0 — a maximized, non-minimized, really-mapped
    // window is covering the desktop. Unmax to a small window, minimize everything to the
    // bottom panel, or close everything → dock and panels come back on their own, no hover
    // needed. (Previously gated on raw windowMgr.count, which counts minimized rows and
    // stale tray-hidden rows too — that's why an empty-looking desktop stayed shell-less.)
    function scheduleHide() {
        if (windowMgr.coveringCount > 0 && !anyHovered())
            hideTimer.restart()
    }
    function cancelHide() { hideTimer.stop() }

    Timer {
        id: hideTimer; interval: 2000; repeat: false
        onTriggered: {
            intellihide.topRevealed = false
            intellihide.dockRevealed = false
            intellihide.btmRevealed = false
            intellihide.widgetRevealed = false
        }
    }

    // Operator (2026-07-06): the panel/dock glint must play EVERY time a maximized
    // window is unmaxed. The *Revealed flags alone can't carry that: the hide has a
    // 2s timer, so a quick max→unmax never actually hides the shell, the flags never
    // transition, and the glint looked like it "only does it once." coveringCount
    // returning to zero IS the unmax/minimize/close-of-the-covering-window moment,
    // whether or not the shell had time to hide — bump a counter the glass surfaces
    // observe (still one sweep per event, same epilepsy math as revealPulse).
    property int glintPulse: 0

    Connections {
        target: windowMgr
        function onCoveringCountChanged() {
            if (windowMgr.coveringCount === 0) { hideTimer.stop(); intellihide.revealAll(); intellihide.glintPulse++ }
            else intellihide.scheduleHide()
        }
        function onActiveIndexChanged() {
            if (windowMgr.activeIndex >= 0) intellihide.scheduleHide()
            else intellihide.revealAll()
        }
    }
}
