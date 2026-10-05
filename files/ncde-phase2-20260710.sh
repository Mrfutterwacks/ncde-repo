#!/bin/bash
# ncde-phase2-20260710.sh — Phase 2 cheap wins (now unblocked: pacman is free +
# the ownership sweep registered cups + blueman). Idempotent; never deletes.
# Run as root:  sudo bash ncde-phase2-20260710.sh    (then log out and back in)
#
# FIX A  PRINTER: the "+"/"Add Printer" buttons opened the raw CUPS web admin
#        (http://localhost:631/admin) — commercial.md B-F3. Now they launch the
#        native system-config-printer GUI via the shell's Launcher. (The in-WM
#        native flow via Lelan is source-gone; this is the pragmatic native fix.)
# FIX B  BLUETOOTH PAIRING: the in-tab pair button needs Lelan support that the
#        lost C++ blocks. blueman (now registered) ships a real org.bluez Agent1;
#        autostarting blueman-applet in the session makes pairing actually work
#        (agent + tray), using the session's existing crash-respawn pattern.
#
# NOTE: clipboard "Mechanism B" is deliberately NOT here — it's a WM paste-race
# best fixed at the source (Phase 3 reconstruction of NCDEWindowManager), not
# papered over with a clipboard-manager daemon that may not touch the race.

set -u
[ "$(id -u)" = 0 ] || { echo "Run as root:  sudo bash $0"; exit 1; }
echo "== NCDE Phase 2 (printer + bluetooth) =="

# ---- FIX A: native printer GUI ------------------------------------------------
if ! pacman -Q system-config-printer >/dev/null 2>&1; then
    if timeout 8 curl -sI https://geo.mirror.pkgbuild.com/ >/dev/null 2>&1; then
        echo "printer: installing system-config-printer..."
        pacman -S --needed --noconfirm system-config-printer >/dev/null 2>&1 \
            && echo "OK  system-config-printer installed" \
            || echo "printer: install FAILED — QML still points at it; install manually"
    else
        echo "printer: no network — install system-config-printer later; applying QML anyway"
    fi
else
    echo "printer: system-config-printer already installed"
fi
python3 - <<'PY'
import os, shutil
p="/usr/share/ncde/PrintersTab.qml"; bak=p+".prebak-20260710-printer"
if not os.path.isfile(p):
    print("printer: PrintersTab.qml missing — SKIP"); raise SystemExit
s=open(p,encoding="utf-8").read()
old='Qt.openUrlExternally("http://localhost:631/admin")'
new='launcher.launchExec("system-config-printer")'
if new in s and old not in s:
    print("printer: QML already patched — skip")
elif s.count(old)==0:
    print("printer: expected CUPS-URL anchor not found — left untouched")
else:
    if not os.path.exists(bak): shutil.copy2(p,bak)
    n=s.count(old); s=s.replace(old,new)
    open(p+".tmp","w",encoding="utf-8").write(s); os.replace(p+".tmp",p)
    print(f"OK  printer: {n} button(s) now launch system-config-printer (backup {os.path.basename(bak)})")
PY

# ---- FIX B: bluetooth pairing agent (blueman) ---------------------------------
SESS=/usr/local/bin/ncde-x11-session
if [ -f "$SESS" ]; then
    if grep -q "blueman-applet" "$SESS"; then
        echo "bluetooth: blueman-applet already in the session — skip"
    else
        cp -a "$SESS" "$SESS.prebak-20260710-blueman"
        python3 - "$SESS" <<'PY'
import sys
p=sys.argv[1]; s=open(p,encoding="utf-8").read()
anchor='[ -x /usr/lib/xembedsniproxy ] && ncde_respawn /usr/lib/xembedsniproxy'
add=('\n\n# NCDE Bluetooth pairing agent (2026-07-10): blueman provides the org.bluez\n'
     '# Agent1 so devices can pair (the in-tab pair button needs source-gone Lelan support).\n'
     'pkill -x blueman-applet 2>/dev/null || true\n'
     '[ -x /usr/bin/blueman-applet ] && ncde_respawn blueman-applet')
if anchor in s:
    s=s.replace(anchor, anchor+add, 1)
    open(p+".tmp","w",encoding="utf-8").write(s); import os; os.replace(p+".tmp",p)
    print("OK  bluetooth: blueman-applet autostart added after xembedsniproxy")
else:
    print("bluetooth: session anchor not found — add 'ncde_respawn blueman-applet' manually")
PY
    fi
else
    echo "bluetooth: $SESS missing — SKIP"
fi

# ---- refresh QML cache so the printer edit loads ------------------------------
for h in /home/*; do
    [ -d "$h/.cache/LaPivot/qmlcache" ] && rm -rf "$h/.cache/LaPivot/qmlcache"
done

echo
echo "== Done. LOG OUT and back in. =="
echo "Verify: Settings > Printers > '+' opens the system-config-printer window;"
echo "Bluetooth: a blueman tray icon appears — pairing a new device now prompts and works."
