#!/bin/bash
# portal-debug.sh — reproduce ncde-portal startup OUT of band and capture the error.
# Runs portal on a spare VT (vt05) + spare display (:1) with a hard timeout, so it
# cannot hang the box and does not disturb the running SDDM session on :0/tty1.
# Run from a text console:  Ctrl+Alt+F3  ->  log in  ->  sudo bash ~/portal-debug.sh
set -u
LOG=/tmp/portal-debug.log
: > "$LOG"

echo "### ncde-portal out-of-band reproduction ###" | tee -a "$LOG"
echo "date: $(date)"                                 | tee -a "$LOG"
echo                                                 | tee -a "$LOG"

if [ "$(id -u)" -ne 0 ]; then
  echo "ERROR: run me with sudo (need root to own a VT, start X, call PAM)." | tee -a "$LOG"
  exit 1
fi

# Make sure nothing else is squatting our spare display
rm -f /tmp/.X1-lock /tmp/.X11-unix/X1 2>/dev/null

echo ">>> launching: ncde-portal --daemon --vt vt05 --display :1 --greeter-user ncde-portal" | tee -a "$LOG"
echo ">>> (hard 25s timeout; will be killed automatically)"                                  | tee -a "$LOG"
echo "-----------------------------------------------------------------------" | tee -a "$LOG"

# -s SIGTERM first, SIGKILL after 5s if it ignores. Capture BOTH streams.
timeout -k 5 25 \
  /usr/bin/ncde-portal --daemon --vt vt05 --display :1 --greeter-user ncde-portal \
  >>"$LOG" 2>&1
rc=$?
echo "-----------------------------------------------------------------------" | tee -a "$LOG"
echo ">>> ncde-portal exited rc=$rc  (124 = killed by timeout = it HUNG)"       | tee -a "$LOG"

# Whatever Xorg it spawned on :1, grab that log too — the real failure is often here
echo                                              | tee -a "$LOG"
echo "=== Xorg.1.log (tail) ==="                  | tee -a "$LOG"
tail -40 /var/log/Xorg.1.log 2>/dev/null | tee -a "$LOG" || echo "(no Xorg.1.log)" | tee -a "$LOG"
tail -40 "$HOME/.local/share/xorg/Xorg.1.log" 2>/dev/null | tee -a "$LOG"

# Clean up so the next attempt is clean
rm -f /tmp/.X1-lock /tmp/.X11-unix/X1 2>/dev/null
pkill -f 'Xorg.*:1' 2>/dev/null

echo                                              | tee -a "$LOG"
echo ">>> DONE. Full capture saved to $LOG"       | tee -a "$LOG"
echo ">>> Switch back to your desktop (Ctrl+Alt+F1 or F2) — nothing was changed."
