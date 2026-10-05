#!/bin/bash
# UNINSTALL-L2.sh — remove the L2 test session and its assets. Run ONLY by the operator.
# Agents write this; do not run it. Reverses INSTALL-L2.sh.
set -euo pipefail

BIN_DST="/usr/local/bin/LaPivot-L2"
ASSET_DST="/usr/share/ncde-l2/"
SESSION_SCRIPT="/usr/local/bin/ncde-x11-session-l2"
DESKTOP_FILE="/usr/share/xsessions/ncde-l2.desktop"

rm -f "$BIN_DST"
rm -rf "$ASSET_DST"
rm -f "$SESSION_SCRIPT"
rm -f "$DESKTOP_FILE"

echo "L2 uninstalled."