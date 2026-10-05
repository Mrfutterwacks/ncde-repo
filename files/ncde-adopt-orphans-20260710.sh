#!/bin/bash
# ncde-adopt-orphans-20260710.sh — cure the "vendored-but-unregistered" disease at the root.
#
# The NCDE image was built by rsync-vendoring files into the tree instead of installing
# packages, so hundreds of /usr binaries+libraries exist on disk with NO pacman DB entry.
# They can never be updated or security-patched, and pacman refuses to install over them
# ("exists in filesystem"). Every symptom fixed one-at-a-time this week (scx, gst-libav,
# wireplumber, bluez) was ONE instance of this. This script finds them all and adopts the
# ones that cleanly belong to a single upstream package — and leaves house/local files alone.
#
# SAFE BY DESIGN:
#   * REPORT MODE IS THE DEFAULT. It changes nothing. Run it, read the plan, THEN decide.
#   * Adoption only happens with --apply, and even then pacman shows the full transaction
#     and asks you to confirm (no --noconfirm).
#   * Files no upstream package provides (your NCDE house tools, /usr/local/*, anything
#     hand-built) map to ZERO providers and are NEVER touched.
#   * Files whose provider is ALREADY installed (a local override / replaced file) are
#     listed but NOT auto-reinstalled — that's a per-file judgement call, not a sweep.
#   * Files provided by MORE THAN ONE package are flagged for manual review, never guessed.
#   * Nothing is deleted. Adoption via --overwrite only re-registers + refreshes files.
#
# Usage:  sudo bash ncde-adopt-orphans-20260710.sh            # report only (default)
#         sudo bash ncde-adopt-orphans-20260710.sh --apply    # adopt the clean candidates
#
# Scope: /usr/bin and /usr/lib (the two trees the disease has bitten). /usr/local is
# excluded (house tools). Re-runnable; idempotent.

set -u
export LC_ALL=C
MODE=report
[ "${1:-}" = "--apply" ] && MODE=apply

[ "$(id -u)" = 0 ] || { echo "Run as root:  sudo bash $0 [--apply]"; exit 1; }

WORK=/var/lib/ncde-adopt
mkdir -p "$WORK"
REPORT="$WORK/report-$(date +%Y%m%d).txt"
CAND="$WORK/candidates.pkglist"
say() { echo "$*" | tee -a "$REPORT"; }
: > "$REPORT"

say "=== NCDE orphan-adoption $MODE run — $(date '+%F %T') ==="

# 1. sync the pacman FILE database (needed to map a path -> its package).
if ! timeout 8 curl -sI https://geo.mirror.pkgbuild.com/ >/dev/null 2>&1; then
    say "ABORT: no mirror reachable — the file database can't sync. Connect and re-run."
    exit 1
fi
say "[1/5] syncing pacman file database (pacman -Fy)..."
pacman -Fy >>"$REPORT" 2>&1 || { say "ABORT: pacman -Fy failed (see $REPORT)"; exit 1; }

# 2. build the owned-file set and the present-file set, diff to unowned.
say "[2/5] enumerating unowned files under /usr/bin and /usr/lib..."
pacman -Qlq 2>/dev/null | sort -u > "$WORK/owned.list"
find /usr/bin /usr/lib \( -type f -o -type l \) 2>/dev/null | sort -u > "$WORK/present.list"
comm -23 "$WORK/present.list" "$WORK/owned.list" > "$WORK/unowned.list"
UNOWNED=$(wc -l < "$WORK/unowned.list")
say "      $UNOWNED unowned files found."

# 3. classify each unowned file by its provider(s).
say "[3/5] mapping each unowned file to its upstream package..."
say "      (~13k files on this system — expect several minutes; progress shown below)"
: > "$WORK/local.list"        # no provider  -> leave alone
: > "$WORK/installed.list"    # provider already installed -> per-file call, skip
: > "$WORK/ambiguous.list"    # >1 provider  -> manual review
: > "$WORK/adopt.map"         # file<TAB>pkg  (single, not-installed provider)
declare -A INSTALLED_CACHE
n=0
while IFS= read -r f; do
    n=$((n+1)); [ $((n % 200)) -eq 0 ] && printf '      ...%d/%d\r' "$n" "$UNOWNED" >&2
    mapfile -t prov < <(pacman -Fq "$f" 2>/dev/null | sed 's|^[^/]*/||' | sort -u)
    case ${#prov[@]} in
        0) echo "$f" >> "$WORK/local.list" ;;
        1) p=${prov[0]}
           if [ -z "${INSTALLED_CACHE[$p]+x}" ]; then
               pacman -Q "$p" >/dev/null 2>&1 && INSTALLED_CACHE[$p]=1 || INSTALLED_CACHE[$p]=0
           fi
           if [ "${INSTALLED_CACHE[$p]}" = 1 ]; then echo "$f  ($p)" >> "$WORK/installed.list"
           else printf '%s\t%s\n' "$f" "$p" >> "$WORK/adopt.map"; fi ;;
        *) echo "$f  [${prov[*]}]" >> "$WORK/ambiguous.list" ;;
    esac
done < "$WORK/unowned.list"
printf '                              \r' >&2

# 4. summarize.
cut -f2 "$WORK/adopt.map" 2>/dev/null | sort -u > "$CAND"
NCAND=$(wc -l < "$CAND"); NADOPTFILES=$(wc -l < "$WORK/adopt.map")
NLOCAL=$(wc -l < "$WORK/local.list"); NINST=$(wc -l < "$WORK/installed.list")
NAMB=$(wc -l < "$WORK/ambiguous.list")
say ""
say "[4/5] classification:"
say "  ADOPTABLE : $NADOPTFILES files -> $NCAND distinct packages (clean single owner, not installed)"
say "  local     : $NLOCAL files (no upstream package — house/hand-built, LEFT ALONE)"
say "  installed : $NINST files (provider already installed — likely local override, LEFT ALONE)"
say "  ambiguous : $NAMB files (>1 provider — needs your eyes, LEFT ALONE)"
say ""
say "  Candidate packages to adopt (full list in $CAND):"
if [ "$NCAND" -gt 0 ]; then sed 's/^/    /' "$CAND" | tee -a "$REPORT"; else say "    (none)"; fi
say ""
say "  Lists written under $WORK/ : local.list installed.list ambiguous.list adopt.map"

# 5. apply, or explain how.
if [ "$MODE" = report ]; then
    say "[5/5] REPORT ONLY — nothing changed. Review the candidate list above, then run:"
    say "        sudo bash $0 --apply"
    say "      (pacman will still show the full transaction and ask you to confirm.)"
    exit 0
fi

if [ "$NCAND" -eq 0 ]; then
    say "[5/5] --apply: no clean candidates to adopt. Nothing to do."
    exit 0
fi
say "[5/5] --apply: adopting $NCAND packages. pacman will show the transaction and prompt —"
say "      review it before answering yes. Conflicts on vendored files are expected and are"
say "      resolved with --overwrite (re-registers + refreshes; never deletes house files)."
# shellcheck disable=SC2046
pacman -S --needed --overwrite '*' $(cat "$CAND") 2>&1 | tee -a "$REPORT"
rc=${PIPESTATUS[0]}
say ""
if [ "$rc" -eq 0 ]; then
    say "adopt: pacman transaction OK. Re-run in report mode to confirm the counts dropped."
else
    say "adopt: pacman exited $rc — read the transaction output above / $REPORT. Common cause:"
    say "       a single stubborn conflict; re-run --apply after resolving, or adopt that one"
    say "       package alone: pacman -S --overwrite '*' <pkg>."
fi
say "=== done $(date '+%F %T') — full report: $REPORT ==="
