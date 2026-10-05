#!/bin/bash
# ncde-join-repo.sh — one time per machine: add the NCDE repo to pacman, so
# NCDE arrives with every system update (NCDE Command's System Update).
# Safe to run again; does nothing once joined.
set -u
[ "$(id -u)" -eq 0 ] || exec sudo bash "$0" "$@"
HERE="$(cd "$(dirname "$(readlink -f "$0")")" && pwd)"
REPO_URL="@REPO_URL@"
KEY_FPR="@KEY_FPR@"

# Trust the signing key, pinned by fingerprint. A bundled key is preferred; if
# there is none, fetch it from the release and accept it only if it matches.
if [ -f "$HERE/ncde-repo.gpg" ]; then
  KEY_SRC="$HERE/ncde-repo.gpg"
else
  KEY_SRC="$REPO_URL/ncde-repo.gpg"
fi
if [ -f "$KEY_SRC" ]; then
  GOT=$(gpg --show-keys --with-colons "$KEY_SRC" 2>/dev/null | awk -F: '/^fpr:/{print $10; exit}')
  if [ "$GOT" = "$KEY_FPR" ]; then
    pacman-key --add "$KEY_SRC" \
      && pacman-key --lsign-key "$KEY_FPR" \
      && SIG="Required DatabaseOptional" \
      || { echo "  ✗ could not trust the NCDE signing key — not joining"; exit 1; }
    echo "  ✓ NCDE signing key $KEY_FPR trusted"
  else
    echo "  ✗ $KEY_SRC is not the expected key ($GOT) — not joining"
    exit 1
  fi
else
  # 2026-09-29: never join unsigned — TrustAll would accept any package,
  # including the old-key build that locked machines out of the desktop.
  echo "  ✗ no signing key file available — not joining (put ncde-repo.gpg next to this script)"
  exit 1
fi

# Rewrite the [ncde] stanza rather than skipping when one is present: an
# existing stanza can carry a wrong Server URL or a stale SigLevel.
if grep -q '^\[ncde\]' /etc/pacman.conf; then
  cp -a /etc/pacman.conf "/etc/pacman.conf.prebak-$(date +%Y%m%d-%H%M%S)-ncde-repo"
  awk '/^\[ncde\]/{s=1;next} /^\[/{s=0} !s' /etc/pacman.conf > /tmp/ncde-join.conf.new \
    && mv /tmp/ncde-join.conf.new /etc/pacman.conf
  sed -i '/^# NCDE updates arrive with the system update/d' /etc/pacman.conf
  echo "  ✓ replaced existing [ncde] stanza"
fi
# A stale copy of a deleted db makes pacman fail on the old signing key forever.
rm -f /var/lib/pacman/sync/ncde.db /var/lib/pacman/sync/ncde.db.sig
cp -a /etc/pacman.conf "/etc/pacman.conf.prebak-$(date +%Y%m%d-%H%M%S)-ncde-repo2"
printf '\n# NCDE updates arrive with the system update (added by ncde-join-repo.sh)\n[ncde]\nSigLevel = %s\nServer = %s\n' \
  "$SIG" "$REPO_URL" >> /etc/pacman.conf
echo "  ✓ NCDE repo added to /etc/pacman.conf"

pacman -Sy --noconfirm || { echo "  ✗ pacman -Sy failed — see the URL above"; exit 1; }
# a full -Syu, never a partial -Sy (Arch doesn't support partial upgrades)
pacman -Syu --needed --noconfirm ncde ncde-qpa \
  && echo "  ✓ NCDE now updates through NCDE Command's System Update" \
  || { echo "  ✗ could not install from the NCDE repo (offline? repo not published yet?)"; exit 1; }
