// WidgetSpacingStore.qml — the gap between Clock/Space/Weather/Stats/Salon in
// the desktop widget column (DesktopWidget.qml). Single source of truth: this
// singleton, not a per-file Settings{} instance, so DesktopWidget.qml and the
// Filigree "Widget Spacing" tab both read/write the exact same live value —
// no relaunch needed to see the other side update.
//
// Persisted via Qt.labs.settings (no LaPivot C++ change, no rebuild) to
// ~/.config/ncde/widget-spacing.conf. Deliberately separate from fontSizeScale/
// uiScale (Filigree's own "MEASURE" section) — this control only ever affects
// the gap between the five desktop widgets, never a font size, never any other
// widget's width/height/radius anywhere else in the shell.
//
// pragma Singleton; registered in qmldir: singleton WidgetSpacingStore 1.0 WidgetSpacingStore.qml
pragma Singleton
import QtQuick 2.15
import Qt.labs.settings 1.0

QtObject {
    property alias widgetSpacing: store.widgetSpacing

    // QtObject has no default property, so a bare `Settings { }` child (even
    // with an id) cannot be nested directly inside it -- confirmed live
    // 2026-07-14 ("Cannot assign to non-existent default property"), which
    // took down every native app sharing this singleton chain. The explicit
    // property below is what QtObject actually requires to hold a child at
    // all; it's deliberately named differently from the id so the two don't
    // collide in this file's identifier scope.
    property Settings _storeHolder: Settings {
        id: store
        fileName: settings.configBase + "widget-spacing.conf"
        category: "DesktopWidget"
        property real widgetSpacing: 6
    }
}
