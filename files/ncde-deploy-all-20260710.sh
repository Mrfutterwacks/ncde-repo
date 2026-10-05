#!/bin/bash
# ncde-deploy-all-20260710.sh — EVERY fix from 2026-07-10, in dependency order, for the
# OTHER installed nodes (not the machine the ISO was built on). Each sub-script is
# idempotent (safe to re-run; skips what's already correct). Copy the whole
# my-project/files/ dir to a USB, then on each node:
#     sudo bash ncde-deploy-all-20260710.sh
# Then LOG OUT and back in (some fixes load at session start), and REBOOT once for
# the lid/power change.
#
# Order matters: ownership adoption registers packages that later fixes install into,
# so it runs before the fix packs.

set -u
HERE="$(cd "$(dirname "$(readlink -f "$0")")" && pwd)"
[ "$(id -u)" = 0 ] || { echo "Run as root:  sudo bash $0"; exit 1; }
LOG=/var/log/ncde-deploy-all-20260710.log; : > "$LOG"
say() { echo "$*" | tee -a "$LOG"; }

run() {   # $1 = script (relative to HERE), rest = args
    local rel="$1"; shift
    local s="$HERE/$rel"
    say ""
    say "========== $rel =========="
    if [ -f "$s" ]; then
        bash "$s" "$@" 2>&1 | tee -a "$LOG"
        local rc=${PIPESTATUS[0]}
        [ "$rc" = 0 ] && say "-- OK ($rel)" || say "-- WARNING: $rel exited $rc (continuing; it's idempotent, re-runnable)"
    else
        say "-- MISSING: $rel (not beside this script) — SKIPPED"
    fi
}

say "==================================================="
say " NCDE full field deploy — 2026-07-10 — node $(hostname)"
say " $(date '+%F %T')"
say "==================================================="

# 1. install-node repair (keyring / initcpio / toolchain / sentinel / weather-qml / audio)
run ncde-install-fix.sh

# 2. ownership disease cure — registers ~387 upstream packages (pacman will prompt to confirm)
run ncde-adopt-orphans-fast.sh --apply

# 3. core fixes (needs registered packages): gst-libav, sched_ext, audit/fail2ban/nftables,
#    iio-sensor-proxy, pre-update snapshot hook, pacman-init/timeshift aside, LaPivot cap
run ncde-fix-pack-20260710.sh

# 4. polish: lid/power via logind, bluez adopt, update-notify timer, Vesper launcher, theme cleanup
run ncde-polish-20260710.sh

# 5. weather: real observed conditions (METAR icon) + town/ZIP
run ncde-weather-accuracy-20260710.sh

# 6. Phase 2: native printer GUI + Bluetooth pairing agent
run ncde-phase2-20260710.sh

# 7. GliaTalk global menu (GTK2/3 module + Qt6 platform theme + tools)
run globalmenu/ncde-globalmenu-deploy.sh

# 8. GliaTalk frame menu (Unity LIM) — unmaximized windows show their menu in the titlebar
run ncde-globalmenu-frame-deploy.sh

say ""
say "==================================================="
say " DONE on $(hostname). Full log: $LOG"
say " NOW: (1) log out and back in;  (2) reboot once for the lid/power change."
say "==================================================="
