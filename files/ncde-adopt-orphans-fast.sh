#!/bin/bash
# ncde-adopt-orphans-fast.sh — same job as ncde-adopt-orphans-20260710.sh, but maps
# all ~13k unowned files in ONE batched pass (xargs pacman -F) instead of forking
# pacman 13,000 times. ~3 minutes instead of hours. Benchmarked: 500 files in 7s.
#
# Same safety model: REPORT is the default (changes nothing); --apply adopts only
# clean not-installed packages and pacman still shows the transaction + prompts.
# House/local files (no upstream package) never appear in pacman -F output, so they
# are never touched. Never deletes.
#
# Usage:  sudo bash ncde-adopt-orphans-fast.sh           # report only (default)
#         sudo bash ncde-adopt-orphans-fast.sh --apply   # adopt the clean candidates
#
# NOTE: kill the slow run first:  sudo pkill -f ncde-adopt-orphans-20260710

set -u
export LC_ALL=C
MODE=report; [ "${1:-}" = "--apply" ] && MODE=apply
[ "$(id -u)" = 0 ] || { echo "Run as root:  sudo bash $0 [--apply]"; exit 1; }

WORK=/var/lib/ncde-adopt; mkdir -p "$WORK"
REPORT="$WORK/report-fast.txt"; CAND="$WORK/candidates.pkglist"; : > "$REPORT"
say(){ echo "$*" | tee -a "$REPORT"; }
say "=== NCDE orphan-adoption (FAST) $MODE run — starting ==="

# 1. sync the file database (needed for pacman -F)
if ! timeout 8 curl -sI https://geo.mirror.pkgbuild.com/ >/dev/null 2>&1; then
    say "ABORT: no mirror reachable — can't sync the file DB."; exit 1; fi
say "[1/5] pacman -Fy (sync file database)..."
pacman -Fy >>"$REPORT" 2>&1 || { say "ABORT: pacman -Fy failed"; exit 1; }

# 2. unowned files under /usr/bin + /usr/lib (fast set diff, no forks)
say "[2/5] enumerating unowned files..."
pacman -Qlq 2>/dev/null | sort -u > "$WORK/owned"
find /usr/bin /usr/lib \( -type f -o -type l \) 2>/dev/null | sort -u > "$WORK/present"
comm -23 "$WORK/present" "$WORK/owned" > "$WORK/unowned"
say "      $(wc -l < "$WORK/unowned") unowned files."

# 3. ONE batched map: xargs runs pacman -F in a few big chunks (the whole speedup)
say "[3/5] mapping files -> packages in one batched pass (this is the ~3-min step)..."
xargs -d '\n' -a "$WORK/unowned" pacman -F 2>/dev/null | grep -F " is owned by " > "$WORK/mapped"
say "      $(wc -l < "$WORK/mapped") files map to a package; the rest are local/house (left alone)."

# 4. distinct provider packages -> keep only those NOT installed
sed 's/.* is owned by //' "$WORK/mapped" | awk '{print $1}' | sed 's#^[^/]*/##' | sort -u > "$WORK/providers"
: > "$CAND"
while read -r p; do pacman -Q "$p" >/dev/null 2>&1 || echo "$p" >> "$CAND"; done < "$WORK/providers"
NPROV=$(wc -l < "$WORK/providers"); NCAND=$(wc -l < "$CAND")
say ""
say "[4/5] $NPROV distinct upstream packages referenced; $NCAND are NOT installed (adoption candidates):"
[ "$NCAND" -gt 0 ] && sed 's/^/    /' "$CAND" | tee -a "$REPORT" || say "    (none — everything already registered)"
say ""
say "  Lists in $WORK/: unowned mapped providers candidates.pkglist"

# 5. apply or explain
if [ "$MODE" = report ]; then
    say "[5/5] REPORT ONLY — nothing changed. Review the list, then:  sudo bash $0 --apply"
    say "      (pacman will still show the full transaction and ask you to confirm.)"
    exit 0
fi
if [ "$NCAND" -eq 0 ]; then say "[5/5] --apply: nothing to adopt."; exit 0; fi
say "[5/5] --apply: adopting $NCAND packages. Review pacman's transaction before answering yes."
# shellcheck disable=SC2046
pacman -S --needed --overwrite '*' $(cat "$CAND") 2>&1 | tee -a "$REPORT"
rc=${PIPESTATUS[0]}
say ""
[ "$rc" -eq 0 ] && say "adopt: OK. Re-run report mode to confirm the count dropped." \
                || say "adopt: pacman exited $rc — see $REPORT; resolve + re-run, or adopt one pkg at a time."
say "=== done ==="
