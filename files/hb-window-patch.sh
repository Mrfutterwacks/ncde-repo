#!/bin/bash
# hb-window-patch.sh — apply ONLY the Hummingbird bulk-window 40->128 fix (guarded).
# Audit-proven: fetch window `sub $0x27,%eax` @0x49da8 and search window
# `sub $0x28,%rax` @0x5a82f; raise both imm8 to 0x7f (127) => 128-message window.
# GUARDED: only writes if the original byte matches, self-aborts otherwise. Backs up once.
# RUN:  sudo bash ~/my-project/files/hb-window-patch.sh
set -u
HB=/usr/local/bin/hummingbird-courier
[ "$(id -u)" -eq 0 ] || { echo "run with sudo"; exit 1; }
[ -f "$HB" ] || { echo "missing $HB"; exit 1; }
[ -f "$HB.prebak-20260711-hbwindow" ] || cp -a "$HB" "$HB.prebak-20260711-hbwindow"
p(){ local off="$1" exp="$2"; local cur; cur=$(xxd -s "$off" -l 1 -p "$HB")
  if [ "$cur" = "7f" ]; then echo "  @$off already 0x7f"; return 0; fi
  [ "$cur" = "$exp" ] || { echo "  @$off is 0x$cur not 0x$exp — ABORT (unknown binary)"; exit 2; }
  printf '\x7f' | dd of="$HB" bs=1 seek="$off" count=1 conv=notrunc 2>/dev/null
  echo "  @$off 0x$exp -> 0x$(xxd -s "$off" -l 1 -p "$HB")"; }
p $((0x49daa)) 27
p $((0x5a832)) 28
file "$HB" | grep -q ELF && echo "OK: valid ELF; restart Hummingbird to pick it up." || echo "WARN: not ELF!"
