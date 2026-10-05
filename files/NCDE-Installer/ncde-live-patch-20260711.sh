#!/bin/bash
# ==========================================================================
# ncde-live-patch-20260711.sh
# All-inclusive live patch for the RUNNING NCDE system (node "ncde").
#
# Fixes, this run:
#   1. VESPER — rebuilt as a LIVING, interactive security suite (no LLM):
#      • intent-driven conversation that ACTUALLY runs the engines (ClamAV
#        scan, quarantine, re-baseline, definition update, ban check)
#      • fixes "type quarantine and nothing happens" (the window used to
#        VANISH the instant a finding cleared — Main.qml visible gate)
#      • anticipatory quick-reply chips; varied, alive phrasing
#   2. VESPER FALSE ALARMS — rkhunter benign-desktop warnings suppressed
#      (dunst shm, Steam /dev/shm) + re-baseline (telnet inode) so Vesper
#      stops crying wolf. Belt-and-suspenders: brain also filters them.
#   3. Privileged helper + polkit so Vesper can run maintenance headlessly.
#   4. Quarantine store generated.
#   5. GLIATALK hygiene — retire the resurrected Canonical D-Bus appmenu
#      module (violates NCDE's "no D-Bus, ever").
#
# RUN AS:  sudo bash ncde-live-patch-20260711.sh
# Idempotent. Every replaced file is backed up as *.prebak-20260711-livepatch.
# The WM "close a window -> black screen" bug is tracked separately (C++/WM,
# under investigation) — NOT in this script.
# ==========================================================================
set -u
TAG="prebak-20260711-livepatch"
# PORTABLE (2026-07-13, live-caught on another node: was hardcoded to
# /home/stephen and USER_NAME="stephen" — a real "missing source directory"
# failure on any machine that isn't this one). SRC honors VESPER_SRC if the
# calling master patch already extracted it somewhere (e.g. a self-contained
# single-file run); otherwise falls back to a sibling dir next to this script,
# same pattern as ncde-full-patch-20260711.sh's own BASE/SRC.
BASE="$(cd "$(dirname "$(readlink -f "$0")")" && pwd)"
SRC="${VESPER_SRC:-$BASE/vesper-patch-20260711}"
USER_NAME="${SUDO_USER:-$(logname 2>/dev/null || echo "${USER:-root}")}"
USER_UID="$(id -u "$USER_NAME")"
RUNDIR="/run/user/${USER_UID}"
ok(){ printf '  \033[32m✓\033[0m %s\n' "$*"; }
warn(){ printf '  \033[33m!\033[0m %s\n' "$*"; }
step(){ printf '\n\033[1m== %s ==\033[0m\n' "$*"; }

if [ "$(id -u)" -ne 0 ]; then echo "Run with sudo."; exit 1; fi
if [ ! -d "$SRC" ]; then echo "Missing source dir $SRC"; exit 1; fi

bak(){ # bak <file>  -> back it up once if it exists and no backup yet
  [ -f "$1" ] && [ ! -f "$1.$TAG" ] && cp -a "$1" "$1.$TAG" && ok "backed up $1"
}
install_as(){ # install_as <src> <dst> <mode>
  bak "$2"; install -Dm"$3" "$1" "$2" && ok "deployed $2"
}

# --------------------------------------------------------------------------
step "1/5  VESPER — brain (conversational + engine control)"
install_as "$SRC/brain_server.py"  /usr/lib/ncde/vesper/brain_server.py  644
install_as "$SRC/ncde-vesper-priv" /usr/lib/ncde/vesper/ncde-vesper-priv 755

step "2/5  VESPER — UI (window-vanish fix + chips + /converse routing)"
install_as "$SRC/VesperBackend.qml" /usr/share/ncde/vesper/VesperBackend.qml 644
install_as "$SRC/Main.qml"          /usr/share/ncde/vesper/Main.qml          644
install_as "$SRC/Terminal.qml"      /usr/share/ncde/vesper/Terminal.qml      644

step "3/5  VESPER — privileged maintenance (polkit) + quarantine store"
install_as "$SRC/org.ncde.vesper.policy" /usr/share/polkit-1/actions/org.ncde.vesper.policy 644
install_as "$SRC/49-ncde-vesper.rules"   /etc/polkit-1/rules.d/49-ncde-vesper.rules          644
# quarantine store, owned by the user (the brain runs user-scope and writes here)
QDIR="/home/${USER_NAME}/.local/share/ncde-vesper/quarantine"
if [ ! -d "$QDIR" ]; then
  install -d -o "$USER_NAME" -g "$USER_NAME" -m 700 "$QDIR" && ok "created quarantine store $QDIR"
else ok "quarantine store already present"; fi

step "4/5  VESPER false alarms — rkhunter whitelist + re-baseline"
RKCONF=/etc/rkhunter.conf
if [ -f "$RKCONF" ]; then
  bak "$RKCONF"
  if ! grep -q "NCDE / Vesper rkhunter false-positive whitelist" "$RKCONF"; then
    printf '\n' >> "$RKCONF"; cat "$SRC/rkhunter-ncde-whitelist.conf" >> "$RKCONF"
    ok "appended NCDE whitelist to $RKCONF"
  else ok "whitelist already present in $RKCONF"; fi
  # re-baseline (clears "file properties changed" e.g. /usr/bin/telnet after updates)
  if command -v rkhunter >/dev/null; then
    rkhunter --propupd --nocolors >/dev/null 2>&1 && ok "rkhunter baseline re-taught (--propupd)"
    # refresh the report Vesper reads, now that config + baseline are clean
    [ -x /usr/lib/ncde/vesper/rkhunter-scan.sh ] && /usr/lib/ncde/vesper/rkhunter-scan.sh >/dev/null 2>&1 && ok "rkhunter report refreshed"
  else warn "rkhunter not found — skipped re-baseline"; fi
else warn "$RKCONF not found — skipped rkhunter whitelist"; fi

step "5/5  GLIATALK hygiene — retire the Canonical D-Bus appmenu module"
HOOK=/etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh
if [ -f "$HOOK" ]; then bak "$HOOK"; mv -f "$HOOK" "$HOOK.retired-20260711" && ok "retired $HOOK"; fi
# keep it from being loaded into GTK3 apps + resurrecting on update
if command -v pacman >/dev/null && pacman -Qq appmenu-gtk-module >/dev/null 2>&1; then
  if ! grep -q 'appmenu-gtk-module' /etc/pacman.conf; then
    warn "appmenu-gtk-module is installed; add a NoExtract to /etc/pacman.conf to stop it"
    warn "  (left as an operator decision — removing the package may need dependency review)"
  fi
fi

# --------------------------------------------------------------------------
step "restart Vesper's brain (user scope)"
runuser -u "$USER_NAME" -- env XDG_RUNTIME_DIR="$RUNDIR" \
  systemctl --user restart vesper-brain.service 2>/dev/null \
  && ok "vesper-brain.service restarted" \
  || warn "could not restart vesper-brain as $USER_NAME — restart it yourself: systemctl --user restart vesper-brain.service"

# --------------------------------------------------------------------------
step "VERIFY (proof, not claims)"
sleep 2
printf '  brain up?  '; runuser -u "$USER_NAME" -- curl -s --max-time 4 http://127.0.0.1:8077/whoami || echo '(not answering yet)'; echo
printf '  a real conversation turn:\n'
runuser -u "$USER_NAME" -- curl -s --max-time 6 -G http://127.0.0.1:8077/converse \
  --data-urlencode 'q=am I safe?' --data-urlencode 's=verify' \
  | python3 -c 'import sys,json;print("   vesper>",json.load(sys.stdin)["reply"])' 2>/dev/null || echo '   (converse not answering — check the service)'
printf '  real findings after benign filter (expect 0 if only the desktop false-alarms remain):\n'
runuser -u "$USER_NAME" -- curl -s --max-time 6 http://127.0.0.1:8077/findings \
  | python3 -c 'import sys,json;d=json.load(sys.stdin);print("   ",len(d["findings"]),"real finding(s)")' 2>/dev/null || echo '   (findings not answering)'

echo
echo "Done. Open Vesper (launch ncde-vesper, or Settings -> Security while armed):"
echo "  • type 'am I safe?', 'scan my downloads', 'who is knocking?', 'what is T1486?'"
echo "  • type 'quarantine' — the window now STAYS and responds (no more vanish)"
echo "  • tap a chip under the prompt to see him anticipate your next move"
echo "Backups: *.$TAG next to each replaced file."
