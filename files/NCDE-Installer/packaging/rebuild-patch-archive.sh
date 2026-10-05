#!/bin/bash
# rebuild-patch-archive.sh
# Rebuilds the embedded base64 tar.gz archive inside ncde-full-patch-20260711.sh
# from the canonical project source directories.
# Run as yourself (not with sudo) from any directory.
set -eu

# 2026-10-04: this used to hardcode /run/media/stephen/... (the other laptop's
# mount), so it silently failed on any other machine. Derive the path from this
# script's own location instead: <project>/files/NCDE-Installer/packaging/..
# 2026-10-04: only my-project/files is canonical. The field-kit copy next to
# NCDE-Installer/ holds a STALE full-patch-20260711/ tree of its own, so resolving
# "upward to whatever looks like a files dir" silently rebuilt from the wrong tree
# (585 files instead of 666). Resolve to my-project/files explicitly, from wherever
# this mirror of the script lives, and refuse anything else.
HERE="$(cd "$(dirname "$(readlink -f "$0")")" && pwd)"
FILES=""
for up in "$HERE/../.." "$HERE/../../my-project/files" "$HERE/../my-project/files"; do
  case "$(cd "$up" 2>/dev/null && pwd || true)" in
    */my-project/files) FILES="$(cd "$up" && pwd)"; break ;;
  esac
done
[ -n "$FILES" ] || { echo "ERROR: canonical my-project/files not found above $HERE — not rebuilding"; exit 1; }
PATCH="$FILES/ncde-full-patch-20260711.sh"

echo "[1/4] Locating marker line..."
MARKER_LINE="$(grep -an -m1 '^__NCDE_PATCH_ARCHIVE_BELOW__$' "$PATCH" | cut -d: -f1)"
echo "      Marker is at line $MARKER_LINE"

echo "[2/4] Building new archive from source directories..."
TMPDIR="$(mktemp -d /tmp/ncde-rebuild.XXXXXX)"
trap 'rm -rf "$TMPDIR"' EXIT

NEW_ARCHIVE="$TMPDIR/patch.tar.gz"

# Build from the three canonical source items — same structure as the original.
# NUL-safe file list with backup/Python-cache exclusions, per
# .github/copilot-instructions.md "Required fold-in and self-extractor procedure".
# Without this the staged tree's 91 *.prebak files and __pycache__ would ship.
cd "$FILES"
find full-patch-20260711 ncde-live-patch-20260711.sh vesper-patch-20260711 \
  \( -type d -name '__pycache__' -prune \) -o \
  \( -type f \( -name '*.pyc' -o -name '*prebak*' -o -name '*.reverted-*' \) -prune \) -o \
  -type f -print0 > "$TMPDIR/ncde-payload-files"

tar --null -T "$TMPDIR/ncde-payload-files" -czf "$NEW_ARCHIVE"

echo "      Files included: $(tr -cd '\0' < "$TMPDIR/ncde-payload-files" | wc -c)"

echo "      Archive built: $(du -sh "$NEW_ARCHIVE" | cut -f1)"

echo "[3/4] Splicing new archive into patch script..."
PREBAK="$PATCH.prebak-$(date +%Y%m%d-%H%M%S)"
cp -p "$PATCH" "$PREBAK"
echo "      Backup saved: $PREBAK"

# Write header lines (up to and including the marker) + new base64 archive
head -n "$MARKER_LINE" "$PATCH" > "$TMPDIR/new_patch.sh"
base64 "$NEW_ARCHIVE" >> "$TMPDIR/new_patch.sh"
chmod 755 "$TMPDIR/new_patch.sh"

# Verify the new script parses cleanly
bash -n "$TMPDIR/new_patch.sh" || { echo "ERROR: rebuilt patch has bash syntax error!"; exit 1; }

# Verify the archive round-trips cleanly
VERIFY_DIR="$(mktemp -d /tmp/ncde-verify.XXXXXX)"
VERIFY_MARKER="$(grep -an -m1 '^__NCDE_PATCH_ARCHIVE_BELOW__$' "$TMPDIR/new_patch.sh" | cut -d: -f1)"
tail -n "+$((VERIFY_MARKER + 1))" "$TMPDIR/new_patch.sh" | base64 -d | tar xzf - -C "$VERIFY_DIR" \
    || { echo "ERROR: rebuilt archive cannot be extracted!"; rm -rf "$VERIFY_DIR"; exit 1; }
rm -rf "$VERIFY_DIR"
echo "      Round-trip extraction: OK"

mv "$TMPDIR/new_patch.sh" "$PATCH"
echo "[4/4] Done. Patch rebuilt: $PATCH"
echo ""
echo "New size: $(wc -l < "$PATCH") lines / $(du -sh "$PATCH" | cut -f1)"
echo "Backup at: $PREBAK"
echo ""
echo "Next step: run publish.sh --check to verify, then publish."
