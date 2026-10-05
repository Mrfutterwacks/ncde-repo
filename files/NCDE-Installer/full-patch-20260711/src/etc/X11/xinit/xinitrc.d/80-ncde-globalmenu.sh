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
