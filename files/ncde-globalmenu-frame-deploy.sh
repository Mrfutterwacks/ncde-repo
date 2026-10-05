#!/bin/bash
# ncde-globalmenu-frame-deploy.sh — the Unity LIM piece: draw a focused, UNMAXIMIZED
# window's published menu in its own MotifFrame titlebar (maximized windows keep using
# Glia's top bar). Installs GliaFrameMenu.qml + patches MotifFrame.qml (anchor-based,
# idempotent). No D-Bus — same _NCDE_MENUS the bar reads. Backup + relog. Run as root.
set -u
[ "$(id -u)" = 0 ] || { echo "Run as root: sudo bash $0"; exit 1; }
QML=/usr/share/ncde
[ -d "$QML" ] || { echo "no $QML"; exit 1; }
echo "== NCDE frame menu (Unity LIM) deploy =="

# 1. install the component
cat > "$QML/GliaFrameMenu.qml" <<'GFMEOF'
// GliaFrameMenu.qml — NCDE locally-integrated menu (Unity LIM, in the MotifFrame titlebar).
//
// The operator's design (Unity + Mac + CDE + Amiga): a MAXIMIZED window owns Glia's top bar
// (Mac screen-top); an UNMAXIMIZED window carries its menu right here in its own titlebar
// (Unity locally-integrated menus). Same GliaTalk source as the bar — the WM's published
// `_NCDE_MENUS` for the focused window — so any app that publishes (GTK/Qt via the modules,
// Orchidée, …) lights up in the frame with no extra wiring. No D-Bus.
//
// Drop-in contract (MotifFrame supplies these):
//   property string menusJson   — windowMgr.activeAppMenus (JSON) for THIS focused frame
//   property bool   active      — show it (e.g. isFocused && !maximized)
//   signal invoked(int id)      — wire to windowMgr.invokeAppMenu(id)
// Amiga touch: titles sit quiet until hovered, then glow; a click drops the menu.

import QtQuick

Item {
    id: fm
    property string menusJson: ""
    property bool   active: false
    signal invoked(int id)

    // theme tokens straight off the engine (MotifFrame uses ncde.* directly)
    readonly property color _ink:   (typeof ncde !== "undefined") ? ncde.gilt4 : "#e9c97c"
    readonly property color _hot:    (typeof ncde !== "undefined") ? ncde.gilt2 : "#f0d998"
    readonly property color _bg:    (typeof ncde !== "undefined") ? ncde.panelBg : Qt.rgba(0.06,0.04,0.02,0.97)
    readonly property color _bdr:   (typeof ncde !== "undefined") ? ncde.glow : Qt.rgba(0.37,0.9,0.82,1)
    readonly property string _font: (typeof ncde !== "undefined" && ncde.titleFont) ? ncde.titleFont : "sans-serif"

    property var _menus: []
    visible: active && _menus.length > 0
    implicitWidth: titleRow.implicitWidth
    implicitHeight: 24

    function _parse(j) {
        if (!j || j === "") return []
        try {
            var src = JSON.parse(j), out = []
            for (var m = 0; m < src.length; m++) {
                var items = [], si = src[m].items || []
                for (var i = 0; i < si.length; i++) {
                    var it = si[i]
                    if (it.separator) { items.push({ separator: true }); continue }
                    items.push({ label: it.label || "", shortcut: it.shortcut || "",
                                 id: it.id || 0, enabled: it.enabled !== false })
                }
                out.push({ title: src[m].title || "", items: items })
            }
            return out
        } catch (e) { return [] }
    }
    onMenusJsonChanged: { _menus = _parse(menusJson); drop.close() }
    Component.onCompleted: _menus = _parse(menusJson)

    // ── the title strip ────────────────────────────────────────────────────────
    Row {
        id: titleRow
        anchors.verticalCenter: parent.verticalCenter
        spacing: 2
        Repeater {
            model: fm._menus
            delegate: Rectangle {
                id: titleBtn
                width: lbl.implicitWidth + 14
                height: 22
                radius: 3
                property bool hovered: false
                property bool open: drop.visible && drop._owner === index
                color: (hovered || open) ? Qt.rgba(fm._ink.r, fm._ink.g, fm._ink.b, 0.14) : "transparent"
                Behavior on color { ColorAnimation { duration: 90 } }
                Text {
                    id: lbl
                    anchors.centerIn: parent
                    text: modelData.title
                    color: (hovered || open) ? fm._hot : fm._ink
                    font.family: fm._font
                    font.pixelSize: 13
                }
                HoverHandler { onHoveredChanged: titleBtn.hovered = hovered; cursorShape: Qt.PointingHandCursor }
                TapHandler {
                    onTapped: {
                        if (drop.visible && drop._owner === index) { drop.close(); return }
                        drop.openAt(index, modelData.items, titleBtn)
                    }
                }
            }
        }
    }

    // ── the dropdown ─────────────────────────────────────────────────────────────
    Rectangle {
        id: drop
        visible: false
        z: 9999
        property int _owner: -1
        property var _items: []
        width: Math.max(150, dcol.implicitWidth + 20)
        height: dcol.implicitHeight + 10
        color: fm._bg
        radius: 6
        border.width: 1
        border.color: Qt.rgba(fm._bdr.r, fm._bdr.g, fm._bdr.b, 0.8)

        function openAt(owner, items, anchorItem) {
            _owner = owner; _items = items
            var p = anchorItem.mapToItem(fm, 0, anchorItem.height)
            drop.x = Math.max(0, p.x); drop.y = p.y + 2
            drop.visible = true
        }
        function close() { drop.visible = false; drop._owner = -1 }

        Column {
            id: dcol
            x: 4; y: 5
            width: drop.width - 8
            Repeater {
                model: drop._items
                delegate: Item {
                    width: dcol.width
                    height: modelData.separator ? 7 : 24
                    Rectangle {   // separator
                        visible: modelData.separator === true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left; anchors.right: parent.right
                        anchors.leftMargin: 6; anchors.rightMargin: 6
                        height: 1
                        color: Qt.rgba(fm._ink.r, fm._ink.g, fm._ink.b, 0.20)
                    }
                    Rectangle {   // item row
                        visible: !modelData.separator
                        anchors.fill: parent
                        radius: 3
                        property bool hov: false
                        color: hov ? Qt.rgba(fm._ink.r, fm._ink.g, fm._ink.b, 0.16) : "transparent"
                        opacity: (modelData.enabled === false) ? 0.4 : 1.0
                        Text {
                            anchors.left: parent.left; anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData.label || ""
                            color: fm._ink; font.family: fm._font; font.pixelSize: 13
                        }
                        Text {
                            visible: (modelData.shortcut || "") !== ""
                            anchors.right: parent.right; anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData.shortcut || ""
                            color: Qt.rgba(fm._ink.r, fm._ink.g, fm._ink.b, 0.5)
                            font.family: fm._font; font.pixelSize: 11
                        }
                        HoverHandler { enabled: modelData.enabled !== false; onHoveredChanged: parent.hov = hovered }
                        TapHandler {
                            enabled: modelData.enabled !== false
                            onTapped: { fm.invoked(modelData.id || 0); drop.close() }
                        }
                    }
                }
            }
        }
    }
}
GFMEOF
chown root:root "$QML/GliaFrameMenu.qml"; chmod 644 "$QML/GliaFrameMenu.qml"
echo "OK  installed GliaFrameMenu.qml"

# 2. patch MotifFrame.qml (idempotent, anchor-based)
python3 - "$QML/MotifFrame.qml" <<'PYEOF'
import sys, os, shutil
p=sys.argv[1]
if not os.path.isfile(p): print("MotifFrame.qml missing — SKIP"); raise SystemExit
s=open(p,encoding="utf-8").read()
if "GliaFrameMenu {" in s: print("MotifFrame already patched — skip"); raise SystemExit
anchor="            // title text — shadow + main"
if anchor not in s:
    print("MotifFrame anchor not found (version differs) — NOT patched; tell the agent"); raise SystemExit
ins='''            // -- GliaTalk locally-integrated menu (Unity LIM) -------------------
            GliaFrameMenu {
                anchors.left: leftOrnament.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                z: 60
                menusJson: (typeof windowMgr !== "undefined" && windowMgr.activeAppMenus !== undefined) ? windowMgr.activeAppMenus : ""
                active: frame.isFocused && !frame.maximized
                onInvoked: function(id) { if (typeof windowMgr !== "undefined") windowMgr.invokeAppMenu(id) }
            }
'''
shutil.copy2(p, p+".prebak-20260710-framemenu")
s=s.replace(anchor, ins+anchor, 1)
open(p+".tmp","w",encoding="utf-8").write(s); os.replace(p+".tmp",p)
print("OK  patched MotifFrame.qml (backup .prebak-20260710-framemenu)")
PYEOF

for h in /home/*; do [ -d "$h/.cache/LaPivot/qmlcache" ] && rm -rf "$h/.cache/LaPivot/qmlcache"; done
echo "== Done. Log out and back in. Unmaximize a GTK/Orchidee window -> its menu shows in the titlebar. =="
