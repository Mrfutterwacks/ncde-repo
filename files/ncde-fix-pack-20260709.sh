#!/bin/bash
# ncde-fix-pack-20260709.sh — NCDE Poseidon field fix pack, 2026-07-09.
# One script, five fixes, no ISO rebuild. Idempotent — safe to re-run.
# Run as root:  sudo bash ncde-fix-pack-20260709.sh
# Then LOG OUT and back in (the WM loads QML once per session).
#
# FIX 1  Accessibility "Text scale" slider (Settings) — engine never read
#        accessibilityTextScale; folded into SetTheme + panel geometry scales
#        with it so nothing clips.
# FIX 2  Filigree / La Fonderie text ignored the slider (bypassed SetTheme) —
#        170 references pointed at the scaled sizes.
# FIX 3  Bottom-panel launcher tooltips — the launcher model shipped tip
#        fields that were never rendered; now shown above each button.
# FIX 4  Weather shows the wrong town — geoclue GeoIP resolves the ISP's city
#        (BeaconDB has no WiFi coverage here). Writes /etc/geolocation
#        (geoclue's static source, already enabled) after asking your town.
# FIX 5  Network icon red X (sentinel udev_monitor.py) — session-86 fix for
#        already-installed nodes: aggregate any-iface-up + 3s re-check.
# FIX 6  Stats widget disk rows showed no used/total space — QML read
#        used/total/percent fields that never existed; engine ships
#        usedBytes/totalBytes. Computed + formatted in QML now.
# FIX 7  Storage not automounting (older installs) — session-84 class:
#        vendored trees ship stale pacman-hook-generated caches; the shipped
#        giomodule.cache lacked the gvfs volume-monitor modules, so drives
#        never automount. Re-runs the five cache regenerations (no-op when
#        already current).
#
# NOTE for older installs (pre round-4 ISO): also run ncde-install-fix.sh
# from the fix kit (/usr/local/share/ncde-fix/ or the install-stick ESP).

set -u
QML_DIR="/usr/share/ncde"
BAK=".prebak-20260709-fixpack"
SENTINEL="/usr/local/bin/sentinel/udev_monitor.py"
SENTINEL_FIXED_MD5="825ba23d95ab1a879d8064b2f04b5bcb"

[ "$(id -u)" -eq 0 ] || { echo "ERROR: run with sudo/root."; exit 1; }
[ -d "$QML_DIR" ]    || { echo "ERROR: $QML_DIR not found — is this an NCDE system?"; exit 1; }
command -v python3 >/dev/null || { echo "ERROR: python3 not found."; exit 1; }

echo "== NCDE fix pack 2026-07-09 =="

# ── FIX 1 + 2 + 3: QML patches (exact-anchor, count-checked, backed up) ──
python3 - "$QML_DIR" "$BAK" <<'PYEOF'
import sys, shutil, os
qml_dir, bak_suffix = sys.argv[1], sys.argv[2]

# Block patches: (file, patched-marker, [(old, new), ...]) — each anchor must
# appear exactly once or the file is left untouched.
BLOCKS = [
    ("SetTheme.qml", "accessibilityTextScale", [(
"""    // ── Font sizes — scale-aware, mirror engine so all Settings tabs share one binding ──
    readonly property double sm: ncde.fontSize_sm
    readonly property double md: ncde.fontSize_md
    readonly property double lg: ncde.fontSize_lg""",
"""    // ── Font sizes — scale-aware, mirror engine so all Settings tabs share one binding ──
    // A11y fix 2026-07-09: the engine's recomputeFontSizes() only multiplies
    // fontSizeScale × uiScale — settings.accessibilityTextScale is saved but never
    // read, so the Accessibility "Text scale" slider did nothing. Fold it in here.
    readonly property double acc: (typeof settings !== "undefined" && settings.accessibilityTextScale > 0) ? settings.accessibilityTextScale : 1.0
    readonly property double sm: Math.round(ncde.fontSize_sm * acc)
    readonly property double md: Math.round(ncde.fontSize_md * acc)
    readonly property double lg: Math.round(ncde.fontSize_lg * acc)"""
    )]),
    ("SettingsPanel.qml", "k.acc", [
        ("    width: 940; height: 660",
         "    width: normalWidth; height: normalHeight"),
        ("""    readonly property int normalHeight: 660
    readonly property int normalWidth:  940""",
         """    // A11y fix 2026-07-09: panel + rail geometry follow SetTheme.acc so scaled
    // text never clips (capped to the screen like the expanded state).
    readonly property int normalHeight: Math.min(Math.round(660 * k.acc), Screen.height - 40)
    readonly property int normalWidth:  Math.min(Math.round(940 * k.acc), Screen.width - 40)"""),
        ("            spHeightAnim.to = 56; spHeightAnim.start()",
         "            spHeightAnim.to = Math.round(56 * k.acc); spHeightAnim.start()"),
        ("            spHeightAnim.to = collapsed ? 56 : normalHeight; spHeightAnim.start()",
         "            spHeightAnim.to = collapsed ? Math.round(56 * k.acc) : normalHeight; spHeightAnim.start()"),
        ("            settingsPanel.y = (Screen.height - (collapsed ? 56 : normalHeight)) / 2",
         "            settingsPanel.y = (Screen.height - (collapsed ? Math.round(56 * k.acc) : normalHeight)) / 2"),
        ("        width: parent.width - 24; height: 36",
         "        width: parent.width - 24; height: Math.round(36 * k.acc)"),
        ("        width: 158\n        radius: 8",
         "        width: Math.round(158 * k.acc)\n        radius: 8"),
        ("                                width: parent.width - 8; x: 4; height: 28; radius: 6",
         "                                width: parent.width - 8; x: 4; height: Math.round(28 * k.acc); radius: 6"),
    ]),
    ("BottomPanel.qml", "fpTipDelay", [(
"""                    HoverHandler { onHoveredChanged: fpBtn.hovered = hovered }
                    TapHandler {
                        onPressedChanged: fpBtn.pressed = pressed
                        onTapped: launcher.launchExec(modelData.exec)
                    }
                }""",
"""                    HoverHandler {
                        onHoveredChanged: {
                            fpBtn.hovered = hovered
                            if (hovered) fpTipDelay.restart()
                            else fpTipDelay.stop()
                        }
                    }
                    TapHandler {
                        onPressedChanged: fpBtn.pressed = pressed
                        onTapped: launcher.launchExec(modelData.exec)
                    }

                    // Tooltip cartouche (2026-07-09) — surfaces the launcher model's
                    // tip field, which shipped in the model but was never rendered.
                    Timer { id: fpTipDelay; interval: 450 }
                    Rectangle {
                        visible: fpBtn.hovered && !fpBtn.pressed && !fpTipDelay.running
                        y: -(height + 8)
                        x: Math.max((fpBtn.width - width) / 2, -(fpBtn.x + 4))
                        width: fpTipText.implicitWidth + 16
                        height: fpTipText.implicitHeight + 8
                        radius: 6
                        z: 10
                        color: Qt.rgba(ncde.panelBg.r, ncde.panelBg.g, ncde.panelBg.b, 0.94)
                        border.width: 1
                        border.color: Qt.rgba(ncde.gilt3.r, ncde.gilt3.g, ncde.gilt3.b, 0.9)
                        Text {
                            id: fpTipText
                            anchors.centerIn: parent
                            text: modelData.tip
                            color: ncde.panelText
                            font.family: ncde.titleFont
                            font.pixelSize: SetTheme.sm
                        }
                    }
                }"""
    )]),
    ("StatsPanel.qml", "usedBytes", [
        ("            property int count: widget_data.mountedVolumes ? widget_data.mountedVolumes.length : 0",
         """            property int count: widget_data.mountedVolumes ? widget_data.mountedVolumes.length : 0
                // Stats fix 2026-07-09: the engine ships usedBytes/totalBytes per
                // volume -- the used/total/percent fields this file read never
                // existed in the binary. Compute display values here.
                function pct(v)  { return (v && v.totalBytes > 0) ? (v.usedBytes / v.totalBytes) * 100 : 0 }
                function fmtB(b) {
                    if (b === undefined || b === null || b <= 0) return "\\u2014"
                    var gb = b / 1073741824
                    if (gb >= 1000) return (Math.round(gb / 102.4) / 10) + " TB"
                    if (gb >= 100)  return Math.round(gb) + " GB"
                    if (gb >= 1)    return (Math.round(gb * 10) / 10) + " GB"
                    return Math.round(b / 1048576) + " MB"
                }"""),
        ("Math.min((modelData.percent || 0) / 100, 1.0)",
         "Math.min(diskCol.pct(modelData) / 100, 1.0)"),
        ("if ((modelData.percent || 0) > 85) return",
         "if (diskCol.pct(modelData) > 85) return"),
        ('text: (modelData.used || "—") + " / " + (modelData.total || "—")',
         'text: diskCol.fmtB(modelData.usedBytes) + " / " + diskCol.fmtB(modelData.totalBytes)'),
    ]),
    ("MuchaStats.qml", "usedBytes", [
        ("        property int count: widget_data.mountedVolumes ? widget_data.mountedVolumes.length : 0",
         """        property int count: widget_data.mountedVolumes ? widget_data.mountedVolumes.length : 0
            // Stats fix 2026-07-09: the engine ships usedBytes/totalBytes per
            // volume -- the used/total/percent fields this file read never
            // existed in the binary. Compute display values here.
            function pct(v)  { return (v && v.totalBytes > 0) ? (v.usedBytes / v.totalBytes) * 100 : 0 }
            function fmtB(b) {
                if (b === undefined || b === null || b <= 0) return "\\u2014"
                var gb = b / 1073741824
                if (gb >= 1000) return (Math.round(gb / 102.4) / 10) + " TB"
                if (gb >= 100)  return Math.round(gb) + " GB"
                if (gb >= 1)    return (Math.round(gb * 10) / 10) + " GB"
                return Math.round(b / 1048576) + " MB"
            }"""),
        ("Math.min((modelData.percent || 0) / 100, 1.0)",
         "Math.min(diskCol.pct(modelData) / 100, 1.0)"),
        ("if ((modelData.percent || 0) > 85) return",
         "if (diskCol.pct(modelData) > 85) return"),
        ('text: (modelData.used || "—") + " / " + (modelData.total || "—")',
         'text: diskCol.fmtB(modelData.usedBytes) + " / " + diskCol.fmtB(modelData.totalBytes)'),
    ]),
]

# Token sweeps: every ncde.fontSize_* -> SetTheme.* (slider-aware, safe
# fallback to 1.0 in contexts without the settings object).
SWEEPS = [
    ("FiligreeTab.qml", 155), ("FonderieTab.qml", 13), ("FPSubpanel.qml", 2),
]
TOKENS = [("ncde.fontSize_sm", "SetTheme.sm"),
          ("ncde.fontSize_md", "SetTheme.md"),
          ("ncde.fontSize_lg", "SetTheme.lg")]

failed = False

def backup(path):
    bak = path + bak_suffix
    if not os.path.exists(bak):
        shutil.copy2(path, bak)
    return os.path.basename(bak)

def write(path, text):
    tmp = path + ".fixtmp"
    with open(tmp, "w", encoding="utf-8") as f:
        f.write(text)
    os.replace(tmp, path)

for fname, marker, edits in BLOCKS:
    path = os.path.join(qml_dir, fname)
    if not os.path.isfile(path):
        print(f"ERROR {fname}: missing"); failed = True; continue
    src = open(path, encoding="utf-8").read()
    if marker in src:
        print(f"SKIP  {fname}: already patched"); continue
    bad = [o.splitlines()[0].strip()[:55] for o, _ in edits if src.count(o) != 1]
    if bad:
        print(f"ERROR {fname}: unexpected version, anchors not unique: {bad} — untouched")
        failed = True; continue
    b = backup(path)
    for o, n in edits:
        src = src.replace(o, n, 1)
    write(path, src)
    print(f"OK    {fname}: {len(edits)} edit(s), backup {b}")

for fname, expected in SWEEPS:
    path = os.path.join(qml_dir, fname)
    if not os.path.isfile(path):
        print(f"SKIP  {fname}: not present on this node"); continue
    src = open(path, encoding="utf-8").read()
    count = sum(src.count(t) for t, _ in TOKENS)
    if count == 0:
        print(f"SKIP  {fname}: already swept"); continue
    if count != expected:
        print(f"NOTE  {fname}: {count} refs (expected {expected}) — sweeping anyway, all tokens exact")
    b = backup(path)
    for t, r in TOKENS:
        src = src.replace(t, r)
    left = sum(src.count(t) for t, _ in TOKENS)
    if left != 0:
        print(f"ERROR {fname}: {left} tokens left after sweep — restoring");
        shutil.copy2(path + bak_suffix, path); failed = True; continue
    write(path, src)
    print(f"OK    {fname}: {count} font refs now follow the a11y slider, backup {b}")

sys.exit(1 if failed else 0)
PYEOF
[ $? -eq 0 ] || { echo "QML patching reported errors — stopping before system fixes."; exit 1; }

# ── FIX 4: /etc/geolocation (geoclue static source) ─────────────────────
if [ -s /etc/geolocation ]; then
    echo "SKIP  /etc/geolocation: already present"
elif [ ! -t 0 ]; then
    echo "SKIP  /etc/geolocation: no terminal for the town prompt (run interactively to set it)"
else
    echo
    echo "FIX 4 — weather location. GeoIP puts this machine in the ISP's city,"
    echo "so weather shows the wrong town. Enter the town to pin it (or press"
    echo "Enter to skip):"
    read -r -p "  Town, State (e.g. Germantown Hills, IL): " TOWN
    if [ -n "$TOWN" ]; then
        GEO=$(curl -s --max-time 15 "https://geocoding-api.open-meteo.com/v1/search?name=$(python3 -c "import urllib.parse,sys;print(urllib.parse.quote(sys.argv[1]))" "$TOWN")&count=1")
        LINE=$(printf '%s' "$GEO" | python3 -c "
import json,sys
try:
    r=json.load(sys.stdin)['results'][0]
    print(r['latitude'], r['longitude'], r.get('elevation',200.0), r['name'], r.get('admin1',''))
except Exception:
    pass")
        if [ -z "$LINE" ]; then
            echo "SKIP  geocoding found nothing for '$TOWN' — /etc/geolocation not written"
        else
            set -- $LINE
            LAT=$1; LON=$2; ELEV=$3; shift 3; PLACE="$*"
            echo "  Found: $PLACE  ($LAT, $LON)"
            read -r -p "  Write this as the machine's location? [y/N] " YN
            if [ "$YN" = "y" ] || [ "$YN" = "Y" ]; then
                {
                    echo "# NCDE location fix 2026-07-09 — static location for geoclue."
                    echo "# $PLACE — written by ncde-fix-pack-20260709.sh"
                    echo "# Format (geoclue(5)): latitude / longitude / elevation m / accuracy m"
                    echo "$LAT"; echo "$LON"; echo "$ELEV"; echo "100"
                } > /etc/geolocation
                echo "OK    /etc/geolocation written ($PLACE) — geoclue reloads it automatically"
            else
                echo "SKIP  /etc/geolocation not written"
            fi
        fi
    else
        echo "SKIP  /etc/geolocation (no town entered)"
    fi
fi

# ── FIX 5: sentinel network red-X (udev_monitor.py, session-86 fix) ─────
if [ -f "$SENTINEL" ]; then
    CUR=$(md5sum "$SENTINEL" | cut -d' ' -f1)
    if [ "$CUR" = "$SENTINEL_FIXED_MD5" ]; then
        echo "SKIP  sentinel udev_monitor.py: already the fixed version"
    else
        cp -p "$SENTINEL" "$SENTINEL$BAK" 2>/dev/null || true
        base64 -d > "$SENTINEL.fixtmp" <<'B64EOF'
IiIidWRldiBob3RwbHVnIG1vbml0b3Ig4oCUIGRpc3BhdGNoZXMga2VybmVsIGV2ZW50cyB0byBE
LUJ1cyBzaWduYWxzLgoKU3Vic3lzdGVtczogc291bmQsIGRybSwgcG93ZXJfc3VwcGx5LCBuZXQs
IHVzYiwgaW5wdXQuCiIiIgoKaW1wb3J0IG9zCmltcG9ydCB0aHJlYWRpbmcKaW1wb3J0IGxvZ2dp
bmcKCmltcG9ydCBweXVkZXYKZnJvbSBnaS5yZXBvc2l0b3J5IGltcG9ydCBHTGliCgpmcm9tIC5f
dXRpbHMgaW1wb3J0IHJlYWRfc3lzZnMKZnJvbSAuaHdtb24gaW1wb3J0IGJhdHRlcnlfc3RhdGUK
CmxvZyA9IGxvZ2dpbmcuZ2V0TG9nZ2VyKF9fbmFtZV9fKQoKCmRlZiBfbmV0X3VwKCk6CiAgICAi
IiJUcnVlIGlmIEFOWSByZWFsIGludGVyZmFjZSBpcyB1cCDigJQgdGhlIGRlc2t0b3Atd2lkZSBh
bnN3ZXIgTGVsYW4KICAgIHN0b3JlcyBpbiBpdHMgc2luZ2xlIG1fbmV0d29ya1sidXAiXSBzbG90
LiBUaGUgcGVyLWV2ZW50IG9wZXJzdGF0ZSBvZgogICAgdGhlIHRyaWdnZXJpbmcgaWZhY2UgaXMg
dGhlIHdyb25nIHRoaW5nIHRvIHJlcG9ydCBmb3IgdGhhdCBzbG90OiBhbgogICAgZXZlbnQgYWJv
dXQgbG8gKG9wZXJzdGF0ZSAndW5rbm93bicpIG9yIGEgc2Vjb25kYXJ5IGlmYWNlIG92ZXJ3cm90
ZQogICAgdGhlIGdsb2JhbCBzdGF0ZSBhbmQgcGFpbnRlZCB0aGUgcGFuZWwncyByZWQgWCB3aGls
ZSB3bGFuMCB3YXMKICAgIGNvbm5lY3RlZC4iIiIKICAgIHRyeToKICAgICAgICBpZmFjZXMgPSBv
cy5saXN0ZGlyKCIvc3lzL2NsYXNzL25ldCIpCiAgICBleGNlcHQgT1NFcnJvcjoKICAgICAgICBy
ZXR1cm4gRmFsc2UKICAgIGZvciBpZmFjZSBpbiBpZmFjZXM6CiAgICAgICAgaWYgaWZhY2UgPT0g
ImxvIjoKICAgICAgICAgICAgY29udGludWUKICAgICAgICBpZiByZWFkX3N5c2ZzKGYiL3N5cy9j
bGFzcy9uZXQve2lmYWNlfS9vcGVyc3RhdGUiKSA9PSAidXAiOgogICAgICAgICAgICByZXR1cm4g
VHJ1ZQogICAgICAgIGlmIHJlYWRfc3lzZnMoZiIvc3lzL2NsYXNzL25ldC97aWZhY2V9L2NhcnJp
ZXIiKSA9PSAiMSI6CiAgICAgICAgICAgIHJldHVybiBUcnVlCiAgICByZXR1cm4gRmFsc2UKCgpk
ZWYgX2VtaXRfbmV0X3N0YXRlKHNlbnRpbmVsLCBpZmFjZSk6CiAgICBzZW50aW5lbC5OZXR3b3Jr
U3RhdGVDaGFuZ2VkKGlmYWNlLCBfbmV0X3VwKCkpCiAgICByZXR1cm4gRmFsc2UgICMgb25lLXNo
b3QgR0xpYiB0aW1lcgoKCmRlZiBoYW5kbGVfdWRldihzZW50aW5lbCwgZGV2aWNlKToKICAgIHN1
YiAgICA9IGRldmljZS5zdWJzeXN0ZW0gb3IgIiIKICAgIGFjdGlvbiA9IGRldmljZS5hY3Rpb24g
ICAgb3IgIiIKCiAgICBpZiBzdWIgPT0gInNvdW5kIjoKICAgICAgICBuYW1lID0gZGV2aWNlLmdl
dCgiSURfTU9ERUwiKSBvciBkZXZpY2UuZ2V0KCJJRF9WRU5ET1IiKSBvciAiVW5rbm93biIKICAg
ICAgICBHTGliLmlkbGVfYWRkKHNlbnRpbmVsLkF1ZGlvRGV2aWNlQ2hhbmdlZCwgYWN0aW9uLCBu
YW1lKQoKICAgIGVsaWYgc3ViID09ICJkcm0iOgogICAgICAgIGNvbm5lY3RvciA9IGRldmljZS5z
eXNfbmFtZQogICAgICAgIGlmIGFueSh4IGluIGNvbm5lY3RvciBmb3IgeCBpbiAoIkhETUkiLCAi
RFAiLCAiRGlzcGxheVBvcnQiLCAiVkdBIikpOgogICAgICAgICAgICBzdGF0dXMgPSByZWFkX3N5
c2ZzKGYiL3N5cy9jbGFzcy9kcm0ve2Nvbm5lY3Rvcn0vc3RhdHVzIikKICAgICAgICAgICAgaWYg
c3RhdHVzID09ICJjb25uZWN0ZWQiOgogICAgICAgICAgICAgICAgR0xpYi5pZGxlX2FkZChzZW50
aW5lbC5EaXNwbGF5Q29ubmVjdGVkLCBjb25uZWN0b3IpCiAgICAgICAgICAgIGVsaWYgc3RhdHVz
ID09ICJkaXNjb25uZWN0ZWQiOgogICAgICAgICAgICAgICAgR0xpYi5pZGxlX2FkZChzZW50aW5l
bC5EaXNwbGF5RGlzY29ubmVjdGVkLCBjb25uZWN0b3IpCgogICAgZWxpZiBzdWIgPT0gInBvd2Vy
X3N1cHBseSI6CiAgICAgICAgIyBTZW50aW5lbCBvbmx5IFNFTlNFUyArIFJFUE9SVFMgaGVyZSAo
emVuLm1kJ3Mgc3RhdGVkIGNoYWluIG9mIGNvbW1hbmQ6CiAgICAgICAgIyAiU2VudGluZWwgaXMg
YSB3YXRjaGVyLi4uIGl0IHNwZWFrcyB0byBMZWxhbiB3aG8gY29udHJvbHMgdGhhdCIpLiBMZWxh
bgogICAgICAgICMgaW5kZXBlbmRlbnRseSBsZWFybnMgQUMvYmF0dGVyeSBzdGF0ZSB2aWEgVVBv
d2VyIGFuZCBpcyB0aGUgb25lIHRoYXQKICAgICAgICAjIGNhbGxzIFNldFBvd2VyUHJvZmlsZSBi
YWNrIG9uIFNlbnRpbmVsIHRvIGFjdHVhbGx5IGFwcGx5IGdvdmVybm9yL0VQUC8KICAgICAgICAj
IGRpcnR5X3JhdGlvIOKAlCBzZWUgX19tYWluX18ucHkncyBTZXRQb3dlclByb2ZpbGUgbWV0aG9k
LiBTZW50aW5lbCBubwogICAgICAgICMgbG9uZ2VyIGRlY2lkZXMrYWN0cyBvbiBpdHMgb3duIGZv
ciB0aGlzIHVkZXYgZXZlbnQgKHJlbW92ZWQgMjAyNi0wNy0wMjsKICAgICAgICAjIGl0IHVzZWQg
dG8gY2FsbCB6ZW5faGludHMuYXBwbHkoKSBoZXJlIGRpcmVjdGx5LCByYWNpbmcgTGVsYW4ncyBk
ZWNpc2lvbgogICAgICAgICMgYW5kLCB1bnRpbCB0aGUgaHdtb24ucHkgZml4LCBkb2luZyBzbyB3
aXRoIHRoZSB3cm9uZyBvbl9iYXR0ZXJ5IHZhbHVlKS4KICAgICAgICBvbl9iYXR0ZXJ5LCBwY3Qg
PSBiYXR0ZXJ5X3N0YXRlKCkKICAgICAgICBHTGliLmlkbGVfYWRkKHNlbnRpbmVsLkJhdHRlcnlT
dGF0ZUNoYW5nZWQsIG9uX2JhdHRlcnksIHBjdCkKCiAgICBlbGlmIHN1YiA9PSAibmV0IjoKICAg
ICAgICBpZmFjZSA9IGRldmljZS5zeXNfbmFtZQogICAgICAgIEdMaWIuaWRsZV9hZGQoc2VudGlu
ZWwuTmV0d29ya1N0YXRlQ2hhbmdlZCwgaWZhY2UsIF9uZXRfdXAoKSkKICAgICAgICAjIG9wZXJz
dGF0ZSBsYWdzIHRoZSBldmVudCBkdXJpbmcgd2lmaSByZWF1dGggKGRvcm1hbnQvZG93biksIGFu
ZCBubwogICAgICAgICMgZnVydGhlciB1ZGV2IGV2ZW50IGZpcmVzIHdoZW4gaXQgZmluYWxseSBz
ZXR0bGVzIHRvICJ1cCIg4oCUIHJlLWNoZWNrCiAgICAgICAgIyBvbmNlIHRoZSBkdXN0IHNldHRs
ZXMgc28gdGhlIExBU1Qgd29yZCBMZWxhbiBoZWFycyBtYXRjaGVzIHJlYWxpdHkuCiAgICAgICAg
R0xpYi50aW1lb3V0X2FkZF9zZWNvbmRzKDMsIF9lbWl0X25ldF9zdGF0ZSwgc2VudGluZWwsIGlm
YWNlKQoKICAgIGVsaWYgc3ViID09ICJ1c2IiIGFuZCBkZXZpY2UuZGV2aWNlX3R5cGUgPT0gInVz
Yl9kZXZpY2UiOgogICAgICAgIHZlbmRvciAgPSBkZXZpY2UuZ2V0KCJJRF9WRU5ET1IiLCAgIiIp
IG9yICIiCiAgICAgICAgcHJvZHVjdCA9IGRldmljZS5nZXQoIklEX01PREVMIiwgICAiIikgb3Ig
IiIKICAgICAgICBpZiBhY3Rpb24gPT0gImFkZCI6CiAgICAgICAgICAgIEdMaWIuaWRsZV9hZGQo
c2VudGluZWwuVXNiRGV2aWNlQWRkZWQsIHZlbmRvciwgcHJvZHVjdCkKICAgICAgICBlbGlmIGFj
dGlvbiA9PSAicmVtb3ZlIjoKICAgICAgICAgICAgR0xpYi5pZGxlX2FkZChzZW50aW5lbC5Vc2JE
ZXZpY2VSZW1vdmVkLCB2ZW5kb3IsIHByb2R1Y3QpCgogICAgZWxpZiBzdWIgPT0gImlucHV0IjoK
ICAgICAgICBuYW1lID0gKGRldmljZS5nZXQoIk5BTUUiKSBvciBkZXZpY2Uuc3lzX25hbWUpLnN0
cmlwKCciJykKICAgICAgICBpZiBhY3Rpb24gPT0gImFkZCI6CiAgICAgICAgICAgIEdMaWIuaWRs
ZV9hZGQoc2VudGluZWwuSW5wdXREZXZpY2VBZGRlZCwgbmFtZSkKICAgICAgICBlbGlmIGFjdGlv
biA9PSAicmVtb3ZlIjoKICAgICAgICAgICAgR0xpYi5pZGxlX2FkZChzZW50aW5lbC5JbnB1dERl
dmljZVJlbW92ZWQsIG5hbWUpCgoKZGVmIHVkZXZfdGhyZWFkKHNlbnRpbmVsKToKICAgIGN0eCAg
ICAgPSBweXVkZXYuQ29udGV4dCgpCiAgICBtb25pdG9yID0gcHl1ZGV2Lk1vbml0b3IuZnJvbV9u
ZXRsaW5rKGN0eCkKICAgIGZvciBzdWIgaW4gKCJzb3VuZCIsICJkcm0iLCAicG93ZXJfc3VwcGx5
IiwgIm5ldCIsICJ1c2IiLCAiaW5wdXQiKToKICAgICAgICBtb25pdG9yLmZpbHRlcl9ieShzdWIp
CiAgICBtb25pdG9yLnN0YXJ0KCkKICAgIGxvZy5pbmZvKCJ1ZGV2IG1vbml0b3IgYWN0aXZlIikK
ICAgIGZvciBkZXZpY2UgaW4gaXRlcihtb25pdG9yLnBvbGwsIE5vbmUpOgogICAgICAgIHRyeToK
ICAgICAgICAgICAgaGFuZGxlX3VkZXYoc2VudGluZWwsIGRldmljZSkKICAgICAgICBleGNlcHQg
RXhjZXB0aW9uIGFzIGV4YzoKICAgICAgICAgICAgbG9nLndhcm5pbmcoImRpc3BhdGNoIGVycm9y
OiAlcyIsIGV4YykK
B64EOF
        NEW=$(md5sum "$SENTINEL.fixtmp" | cut -d' ' -f1)
        if [ "$NEW" = "$SENTINEL_FIXED_MD5" ]; then
            chown root:root "$SENTINEL.fixtmp"; chmod 755 "$SENTINEL.fixtmp"
            mv "$SENTINEL.fixtmp" "$SENTINEL"
            systemctl try-restart ncde-sentinel.service 2>/dev/null && \
                echo "OK    sentinel udev_monitor.py replaced + sentinel restarted (backup kept)" || \
                echo "OK    sentinel udev_monitor.py replaced (backup kept) — restart sentinel or reboot"
        else
            rm -f "$SENTINEL.fixtmp"
            echo "ERROR embedded sentinel payload failed its md5 check — sentinel untouched"
        fi
    fi
else
    echo "SKIP  sentinel not found at $SENTINEL"
fi

# ── FIX 7: regenerate pacman-hook caches (session-84 stale-cache class) ─
# The gvfs volume monitors live in giomodule.cache — when the shipped cache
# predates the vendored modules, drives never automount in Orchidée.
run() { "$@"; }
echo
echo "FIX 7 — regenerating generated caches (fixes storage automount on"
echo "older installs; harmless no-op elsewhere):"
GIOMOD="/usr/lib/gio/modules"
[ -d "$GIOMOD" ] && BEFORE=$(awk 'NF && $1 !~ /^#/ {n++} END {print n+0}' "$GIOMOD/giomodule.cache" 2>/dev/null)
[ -d /usr/share/glib-2.0/schemas ]   && run glib-compile-schemas /usr/share/glib-2.0/schemas/ && echo "  OK glib schemas"
[ -d /usr/share/icons/hicolor ]      && run gtk-update-icon-cache -f -t /usr/share/icons/hicolor >/dev/null 2>&1 && echo "  OK icon cache"
[ -d /usr/share/mime ]               && run update-mime-database /usr/share/mime >/dev/null 2>&1 && echo "  OK mime database"
[ -d /usr/share/applications ]       && run update-desktop-database /usr/share/applications && echo "  OK desktop database"
if [ -d "$GIOMOD" ]; then
    run gio-querymodules "$GIOMOD" && echo "  OK gio modules"
    AFTER=$(awk 'NF && $1 !~ /^#/ {n++} END {print n+0}' "$GIOMOD/giomodule.cache" 2>/dev/null)
    echo "  gio modules in cache: ${BEFORE:-0} -> ${AFTER:-0}"
    ls "$GIOMOD" | grep -q gvfs || echo "  WARNING: no gvfs modules installed at all — automount needs the gvfs package; tell the agent"
fi
run ldconfig && echo "  OK ld.so cache"

echo
echo "== Done. LOG OUT and back in to load the QML fixes. =="
echo "Then: Settings > Accessibility > Text scale now really resizes text;"
echo "hover the five launcher buttons for tooltips; weather follows the"
echo "town set above within ~30 min (or immediately after the relogin)."
echo "Tip: if the speakers are too quiet at 100%, this boosts them (run as"
echo "your normal user, not root):  wpctl set-volume @DEFAULT_AUDIO_SINK@ 1.3"
