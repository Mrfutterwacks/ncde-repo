#!/bin/bash
# UNINSTALL-L2.sh — remove the NCDE L2 test session (the normal NCDE session is never touched).
set -euo pipefail
[ "$(id -u)" = 0 ] || { echo "run with sudo"; exit 1; }
rm -f /usr/share/xsessions/ncde-l2.desktop /usr/local/bin/ncde-x11-session-l2 /usr/local/bin/LaPivot-L2
rm -rf /usr/share/ncde-l2
echo "NCDE L2 removed."
