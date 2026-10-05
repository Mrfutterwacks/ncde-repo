#!/bin/bash
# PUBLISH-TO-GITHUB.sh — the one command: puts NCDE on GitHub as a pacman repo.
# Installs the GitHub CLI if missing, logs in once, then runs publish.sh
# (build ncde + ncde-qpa, make the repo database, upload to Releases).
# Run as yourself (not with sudo); it asks for your password only to install gh.
set -eu
cd "$(dirname "$(readlink -f "$0")")"
. ./repo.conf
OWNER="${GH_REPO%%/*}"

command -v gh >/dev/null || sudo pacman -S --needed --noconfirm github-cli
if ! gh auth status >/dev/null 2>&1; then
  # a token instead of the one-time device code (codes expire and are easy to mistype)
  URL="https://github.com/settings/tokens/new?scopes=repo,read:org&description=NCDE%20publish"
  echo "Log in to GitHub as $OWNER:"
  echo "  1. On the page that opens, scroll down and click 'Generate token'"
  echo "  2. Click the copy icon next to the new token (starts with ghp_)"
  echo "  3. Paste it here and press Enter (it stays hidden)"
  xdg-open "$URL" >/dev/null 2>&1 || echo "  Open: $URL"
  read -rsp "Token: " TOKEN; echo
  printf '%s\n' "$TOKEN" | gh auth login --hostname github.com --git-protocol https --with-token \
    || { echo "GitHub didn't accept that token — run this script again"; exit 1; }
  unset TOKEN
fi
ME="$(gh api user -q .login)"
[ "$ME" = "$OWNER" ] || { echo "Logged in as '$ME', but the repo belongs to '$OWNER' — run: gh auth login"; exit 1; }

./publish.sh
