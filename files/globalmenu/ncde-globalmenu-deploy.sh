#!/bin/bash
# ncde-globalmenu-deploy.sh — install NCDE's GliaTalk GTK menu publisher.
#
# What it does: makes every GTK2/GTK3 app hand its real menu bar to GliaTalk
# (NCDE's in-house, D-Bus-free global menu). The module walks the app's own
# GtkMenuBar and publishes it as `_NCDE_MENUS` on the app's window — the exact
# shape LaPivot already reads and renders in Glia's bar — and activates items on
# the `_NCDE_MENU_INVOKE` ClientMessage. No D-Bus, no daemon. Foreign apps that
# expose no GtkMenuBar publish nothing and keep the shell's relay trio.
#
# Replaces the dead Canonical appmenu module (its .so isn't even installed here).
# The WM needs NOTHING new — LaPivot already carries the _NCDE_MENUS reader +
# invokeAppMenu sender (verified: 7 symbol hits).
#
# Ships beside this script: ncde-gtk-module.so (GTK3), ncde-gtk2-module.so (GTK2),
# ncde-menu-invoke (a debug sender). Idempotent; never deletes (renames aside).
# Run as root:  sudo bash ncde-globalmenu-deploy.sh      (then log out and back in)
#
# FIRST-RUN SAFETY: this deploys with NCDE_GLOBALMENU_HIDE=0, so apps KEEP their
# own menu bar AND publish to Glia — if the bar rendering needs a tweak, no app is
# left menu-less. Once you confirm the menus appear in Glia's bar, flip to the true
# global-menu look (menu bar hidden in-app) by changing that line to =1 and relog.

set -u
HERE="$(cd "$(dirname "$(readlink -f "$0")")" && pwd)"
[ "$(id -u)" = 0 ] || { echo "Run as root:  sudo bash $0"; exit 1; }
echo "== NCDE GliaTalk global-menu (GTK) deploy =="

# --- module install dirs ---
GTK3_DIR=/usr/lib/gtk-3.0/modules
GTK2_VER=$(pkg-config --variable=gtk_binary_version gtk+-2.0 2>/dev/null || echo 2.10.0)
GTK2_DIR=/usr/lib/gtk-2.0/$GTK2_VER/modules

install_mod() {   # $1 src .so  $2 destdir
    [ -f "$HERE/$1" ] || { echo "MISSING beside script: $1 — SKIP"; return 1; }
    mkdir -p "$2"
    [ -f "$2/ncde-gtk-module.so" ] && cp -a "$2/ncde-gtk-module.so" "$2/ncde-gtk-module.so.prebak-$(date +%Y%m%d)" 2>/dev/null
    install -m0644 -o root -g root "$HERE/$1" "$2/ncde-gtk-module.so"
    echo "OK  installed $2/ncde-gtk-module.so"
}
install_mod ncde-gtk-module.so  "$GTK3_DIR"
install_mod ncde-gtk2-module.so "$GTK2_DIR" || echo "  (GTK2 module optional — legacy apps only)"

# --- Qt6 platform theme (foreign Qt apps with a real menu bar; KDE's mechanism) ---
QT_PT_DIR=/usr/lib/qt6/plugins/platformthemes
if [ -f "$HERE/libncde-qpa.so" ]; then
    mkdir -p "$QT_PT_DIR"
    install -m0644 -o root -g root "$HERE/libncde-qpa.so" "$QT_PT_DIR/libncde-qpa.so"
    echo "OK  installed $QT_PT_DIR/libncde-qpa.so (Qt6 platform theme, key 'ncde')"
else
    echo "  (Qt6 theme libncde-qpa.so not beside script — SKIP)"
fi

# --- debug sender (not required by the WM; handy for testing) ---
if [ -f "$HERE/ncde-menu-invoke" ]; then
    install -m0755 -o root -g root "$HERE/ncde-menu-invoke" /usr/local/bin/ncde-menu-invoke
    echo "OK  installed /usr/local/bin/ncde-menu-invoke (debug tool)"
fi

# --- session env: load our module, retire the Canonical appmenu one ---
OLD=/etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh
NEW=/etc/X11/xinit/xinitrc.d/80-ncde-globalmenu.sh
if [ -f "$OLD" ]; then
    mv -- "$OLD" "$OLD.retired-$(date +%Y%m%d)"
    echo "OK  retired the Canonical appmenu module hook (renamed aside)"
fi
cat > "$NEW" <<'EOF'
#!/bin/sh
# NCDE GliaTalk global menu — load the in-house GTK menu publisher into every
# GTK2/GTK3 app (no D-Bus). Same GTK_MODULES mechanism the old appmenu used.
if [ -n "$GTK_MODULES" ]; then
    GTK_MODULES="${GTK_MODULES}:ncde-gtk-module"
else
    GTK_MODULES="ncde-gtk-module"
fi
export GTK_MODULES
# First-run: keep each app's own menu bar too (=0). Change to 1 for the true
# global-menu look (menu bar hidden in-app, only Glia's bar shows it).
export NCDE_GLOBALMENU_HIDE=0
# Qt6 global menu (foreign Qt apps). COMMENTED OUT until verified: this makes our
# theme the platform theme for EVERY Qt app, including LaPivot itself. Enable ONLY
# after confirming LaPivot + the house apps still behave, then relog. To enable:
# uncomment the next line. To revert: re-comment it (or delete this file) and relog.
#export QT_QPA_PLATFORMTHEME=ncde
EOF
chmod 0755 "$NEW"
echo "OK  wrote $NEW (GTK_MODULES=ncde-gtk-module, NCDE_GLOBALMENU_HIDE=0)"

echo
echo "== Done. LOG OUT and back in, then VERIFY: =="
echo "  1. Open GIMP (GTK3). Its File/Edit/… should appear in Glia's bar when it's focused."
echo "  2. Prove the publish directly:"
echo "       xprop -id \$(xdotool getactivewindow) _NCDE_MENUS      # (focus GIMP first)"
echo "     -> should print the menu JSON."
echo "  3. Click a menu in Glia's bar -> the GIMP action should fire."
echo "Once that looks right, edit $NEW: set NCDE_GLOBALMENU_HIDE=1 and relog for the"
echo "full global-menu look (GIMP's own menu bar hidden — also clears the frame-obscured-"
echo "at-top issue you saw). If anything's off, tell me BEFORE flipping to hide."
