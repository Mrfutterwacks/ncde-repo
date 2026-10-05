#!/bin/bash
# upload-github.sh <repo-folder> — put the built NCDE repo on GitHub Releases.
# pacman downloads from .../releases/download/x86_64/, so everything goes into
# one release tagged x86_64. Release files can't be symlinks, so ncde.db and
# ncde.files are uploaded as real copies. A second release, "installer", holds
# the double-click installer + join script for brand-new machines.
set -eu
cd "$(dirname "$(readlink -f "$0")")"
. ./repo.conf
DIR="$1"
gh auth status >/dev/null 2>&1 || { echo "Not logged in to GitHub — run: gh auth login"; exit 1; }

# public, so machines download without logging in
gh repo view "$GH_REPO" >/dev/null 2>&1 \
  || gh repo create "$GH_REPO" --public --description "NCDE desktop updates (pacman repo)"
# a release needs a commit to hang on
# (GitHub's repo "size" lags for minutes after the first commit; ask for the file)
gh api "repos/$GH_REPO/contents/README.md" >/dev/null 2>&1 \
  || gh api -X PUT "repos/$GH_REPO/contents/README.md" -f message="NCDE update repo" \
       -f content="$(printf '# NCDE updates\n\npacman repo for NCDE. Machines get it through NCDE Command'"'"'s System Update.\n' | base64 -w0)" >/dev/null

# 2026-09-29: pacman reads the repo from the "$REPO_TAG" release (repo.conf) —
# this used to upload to a separate "x86_64" release that no machine reads, so
# published updates never arrived. Packages + db go to $REPO_TAG, same place
# as the installer and key.
gh release view "$REPO_TAG" -R "$GH_REPO" >/dev/null 2>&1 \
  || gh release create "$REPO_TAG" -R "$GH_REPO" --title "NCDE installer + packages" \
       --notes "pacman repo for NCDE, plus the installer for new machines."

STAGE="$(mktemp -d)"; trap 'rm -rf "$STAGE"' EXIT
for f in "$DIR"/*; do
  case "$f" in *.old|*.old2|*.old.sig|*.asc) continue ;; esac
  cp -L "$f" "$STAGE/$(basename "$f")"   # -L: db symlinks -> real files
done
gh release upload "$REPO_TAG" -R "$GH_REPO" --clobber "$STAGE"/*

# drop old package files that are no longer in the repo folder
gh release view "$REPO_TAG" -R "$GH_REPO" --json assets -q '.assets[].name' | while read -r a; do
  case "$a" in ncde-2*.pkg.tar.zst|ncde-2*.pkg.tar.zst.sig|ncde-qpa-*.pkg.tar.zst*) ;; *) continue ;; esac
  [ -e "$STAGE/$a" ] || gh release delete-asset "$REPO_TAG" "$a" -R "$GH_REPO" -y
done

# installer for new machines
up=(../../my-project/files/ncde-full-patch-20260711.sh ../ncde-join-repo.sh)
[ -f ../ncde-repo.gpg ] && up+=(../ncde-repo.gpg)
gh release upload "$REPO_TAG" -R "$GH_REPO" --clobber "${up[@]}"
echo "Uploaded to https://github.com/$GH_REPO/releases"
