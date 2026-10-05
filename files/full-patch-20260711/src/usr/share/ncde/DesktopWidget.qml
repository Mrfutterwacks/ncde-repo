import QtQuick 2.15

Item {
    id: widget
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.topMargin: 40
    anchors.bottom: parent.bottom
    // BottomPanel.qml sits at anchors.bottomMargin:12 + height:28 = 40px clearance
    // from the true screen bottom. This was 28 — 12px short of that, so Salon
    // Nocturne (last in the Column, sized to fill exactly to this widget's own
    // bottom edge) overlapped into the top of the bottom panel. The StatsPanel
    // maxHeight formula already reads widget.height generically, so fixing this
    // margin alone correctly shrinks Stats' cap too — no other file needs to change.
    anchors.bottomMargin: 40
    width: 340
    z: 1

    // Nothing may intersect (operator, 2026-09-29): the cards ran from y 44 to
    // 1039, under the top panel's ribbon band (art to y 62) and into the bottom
    // panel's (art from y 1024). Same clear zone as the dock (4px gap to each
    // band): the column scales evenly about its right-middle edge — every card
    // keeps its own internal layout, just ~4% smaller — until it fits.
    readonly property real zoneTop: 72      // ribbon twist dips lowest over this column
    readonly property real zoneBottom: parent.height - 60
    readonly property real _cy: y + height / 2
    readonly property real _cardsTop: y + widgetCol.topPadding
    readonly property real _cardsBottom: y + widgetCol.height
    scale: Math.min(1.0,
                    (_cy - zoneTop) / Math.max(1, _cy - _cardsTop),
                    (zoneBottom - _cy) / Math.max(1, _cardsBottom - _cy))
    transformOrigin: Item.Right

    property Item wallpaperSource: null

    // ── Intellihide (2026-09-23: the widget column never had this — Top/Dock/Bottom
    // all hide+reveal with the covering window, this stayed permanently visible). Same
    // transform-based technique as Dock.qml, mirrored for the right edge: anchors.right
    // still defines the resting position, a Translate slides it further right (off-
    // screen) rather than fighting the anchor with a direct x binding.
    // flat 220ms/OutExpo — matches TopPanel's reveal animation (TopPanel.qml has no
    // per-shell anim-speed setting either; Dock.qml's animSpeedVal is Dock-local,
    // reading settings.dockAnimSpeed, not a global — not reusable here)
    property real targetX: intellihide.widgetRevealed ? 0 : (width + 20)
    Behavior on targetX { NumberAnimation { duration: 220; easing.type: Easing.OutExpo } }
    transform: Translate { x: widget.targetX }

    opacity: intellihide.widgetRevealed ? 1.0 : 0.0
    Behavior on opacity { NumberAnimation { duration: 220; easing.type: Easing.OutExpo } }

    // 5px hover-trigger zone at the true right screen edge — always live even when
    // the column itself has translated away, same pattern as Dock's hoverTrigger.
    Item {
        id: widgetHoverTrigger
        width: 5; height: widget.height
        parent: widget.parent
        anchors.right: parent.right
        y: widget.y
        z: widget.z + 1
        HoverHandler {
            onHoveredChanged: {
                intellihide.widgetHovered = hovered
                if (hovered) intellihide.revealAll()
                else intellihide.scheduleHide()
            }
        }
    }

    HoverHandler {
        id: widgetHover
        onHoveredChanged: {
            intellihide.widgetHovered = hovered
            if (hovered) intellihide.revealAll()
            else intellihide.scheduleHide()
        }
    }

    Column {
        id: widgetCol
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        // Widget Spacing (Filigree "Widget Spacing" tab, 2026-07-14): the gap
        // between Clock/Space/Weather/Stats/Salon. WidgetSpacingStore is a
        // singleton (Qt.labs.settings-backed, no LaPivot C++ change, no
        // rebuild) so this and the settings-tab slider always read the same
        // live value — no relaunch needed to see the other side update.
        spacing: WidgetSpacingStore.widgetSpacing
        topPadding: 4

        // BUG FIXED 2026-07-15 (operator report): dragging the Widget Spacing
        // slider was visibly RESIZING StatsPanel instead of only moving the
        // widgets apart. Root cause: before this tab existed, `spacing` above
        // was the literal `6`, so StatsPanel's maxHeight formula's
        // `4 * widgetCol.spacing` term was always a constant (24). When the
        // slider replaced the literal with the live WidgetSpacingStore value,
        // that term went live too — so raising the slider silently shrank
        // Stats' height budget (and lowering it grew Stats) on every drag.
        // Fix: pin the budget to the ORIGINAL fixed baseline the layout was
        // designed around, independent of the live slider — the slider now
        // only ever changes `spacing` above (moves widgets), never this.
        readonly property real statsHeightBudgetGap: 4 * 6

        ClockPanel   { id: clockPanel;   width: parent.width; backgroundSource: widget.wallpaperSource }
        SpacePanel   { id: spacePanel;   width: parent.width; backgroundSource: widget.wallpaperSource; sky: weatherPanel.sky; latitude: weatherPanel.latitude }
        WeatherPanel { id: weatherPanel; width: parent.width; backgroundSource: widget.wallpaperSource }
        StatsPanel   {
            width: parent.width; backgroundSource: widget.wallpaperSource
            // Stats is the only variable-height widget in this stack: cap it to the
            // space left after the fixed siblings so Salon Nocturne can never be
            // pushed past the widget area (= the bottom panel's top edge). Budget
            // uses the FIXED baseline gap (see statsHeightBudgetGap above), not the
            // live spacing slider, so Stats never resizes as spacing changes.
            maxHeight: widget.height - widgetCol.topPadding - widgetCol.statsHeightBudgetGap
                       - clockPanel.height - spacePanel.height - weatherPanel.height
                       - salonPanel.height
        }
        SalonPanel   { id: salonPanel;   width: parent.width; backgroundSource: widget.wallpaperSource }
    }
}
