#!/bin/bash
# step10-sync-live-to-image.sh — ISO rebuild PHASE 1: copy every file-level fix from the
# working LIVE system into the image tree (~/ncde-ISO/airootfs). Package registration is
# PHASE 2 (separate). Run as root:  sudo bash step10-sync-live-to-image.sh
#
# Idempotent, additive. Never deletes image content (retired files renamed aside).
# After this, PHASE 2 registers packages, then mksquashfs, then xorriso.

set -u
A=/home/stephen/ncde-ISO/airootfs
[ "$(id -u)" = 0 ] || { echo "Run as root: sudo bash $0"; exit 1; }
[ -d "$A/usr/share/ncde" ] || { echo "image tree $A missing/incomplete"; exit 1; }
LOG=/var/log/ncde-iso-phase1.log; : > "$LOG"
say(){ echo "$*" | tee -a "$LOG"; }
cp2(){ # cp live->image if the live file exists; make parent dirs
    local src="$1" dst="$A$1"
    [ -e "$src" ] || { say "  skip (no live $1)"; return; }
    mkdir -p "$(dirname "$dst")"
    cp -a "$src" "$dst" && say "  + $1"
}
say "== ISO Phase 1: sync live fixes -> image ($(date '+%F %T')) =="

# 1. the whole NCDE QML/UI payload (weather, phase2 printer, frame menu, fixpack QML, MotifFrame…)
say "[1] /usr/share/ncde (all QML + GliaFrameMenu + patched MotifFrame)"
rsync -a --delete-excluded \
      --exclude='*.prebak*' --exclude='*.bak' --exclude='qmlcache' \
      /usr/share/ncde/ "$A/usr/share/ncde/" 2>&1 | tail -1
say "  rsynced /usr/share/ncde  (frame menu present in image: $([ -f "$A/usr/share/ncde/GliaFrameMenu.qml" ] && echo YES || echo NO))"

# 2. global-menu modules
say "[2] global-menu modules"
cp2 /usr/lib/gtk-3.0/modules/ncde-gtk-module.so
GTK2=/usr/lib/gtk-2.0/2.10.0/modules/ncde-gtk-module.so; [ -f "$GTK2" ] && cp2 "$GTK2"
cp2 /usr/lib/qt6/plugins/platformthemes/libncde-qpa.so

# 3. tools + helpers
say "[3] tools"
cp2 /usr/local/bin/ncde-menu-invoke
cp2 /usr/local/bin/ncde-update-notify
cp2 /usr/local/bin/ncde-x11-session          # blueman autostart added
cp2 /usr/local/lib/ncde/ncde-snapshot-preupdate

# 4. session + system config
say "[4] configs"
cp2 /etc/X11/xinit/xinitrc.d/80-ncde-globalmenu.sh
# retire the Canonical appmenu hook inside the image (rename aside, never delete)
OLD="$A/etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh"
[ -f "$OLD" ] && mv -- "$OLD" "$OLD.retired" && say "  ~ retired image appmenu hook"
# (lid/logind change removed — it breaks ncde-portal)
cp2 /etc/systemd/user/ncde-update-check.service
cp2 /etc/systemd/user/ncde-update-check.timer
cp2 /usr/share/applications/ncde-vesper.desktop
cp2 /etc/fail2ban/jail.d/ncde-sshd.local
cp2 /etc/nftables.conf
cp2 /etc/pacman.d/hooks/00-ncde-snapshot.hook
cp2 /etc/geoclue/geoclue.conf

# 5. enable the new services in the image (symlinks; installs inherit them)
say "[5] enable services in the image"
ln_svc(){ # $1 unit, $2 wants-target
    local wl="$A/etc/systemd/system/$2.wants"; mkdir -p "$wl"
    [ -e "$A/usr/lib/systemd/system/$1" ] && ln -sf "/usr/lib/systemd/system/$1" "$wl/$1" && say "  enabled $1"
}
ln_svc auditd.service   multi-user.target
ln_svc fail2ban.service multi-user.target
ln_svc nftables.service multi-user.target
ln_svc iio-sensor-proxy.service multi-user.target 2>/dev/null || true
# user-scope: wireplumber/pipewire-pulse + update-check (global presets)
GW="$A/etc/systemd/user"; mkdir -p "$GW/timers.target.wants" "$GW/default.target.wants"
[ -e "$A/usr/lib/systemd/user/wireplumber.service" ] && ln -sf /usr/lib/systemd/user/wireplumber.service "$GW/default.target.wants/wireplumber.service" && say "  enabled wireplumber (user)"
[ -f "$A/etc/systemd/user/ncde-update-check.timer" ] && ln -sf /etc/systemd/user/ncde-update-check.timer "$GW/timers.target.wants/ncde-update-check.timer" && say "  enabled update-check timer (user)"

# 6. retire user-visible cruft in the image (aside)
say "[6] theme/cruft cleanup in image"
for junk in usr/share/applications/timeshift-gtk.desktop boot/grub/themes/starfield usr/share/icons/NCDE-Poseidon etc/systemd/system/pacman-init.service; do
    [ -e "$A/$junk" ] && mv -- "$A/$junk" "$A/$junk.iso-aside" && say "  ~ aside $junk"
done

say ""
say "== Phase 1 done. Verify a few, then Phase 2 (packages). =="
say "  frame menu:   $([ -f "$A/usr/share/ncde/GliaFrameMenu.qml" ] && echo IN-IMAGE || echo MISSING)"
say "  GTK module:   $([ -f "$A/usr/lib/gtk-3.0/modules/ncde-gtk-module.so" ] && echo IN-IMAGE || echo MISSING)"
say "  Qt theme:     $([ -f "$A/usr/lib/qt6/plugins/platformthemes/libncde-qpa.so" ] && echo IN-IMAGE || echo MISSING)"
say "  weather fix:  $(grep -lq WeatherLive "$A/usr/share/ncde/WeatherPanel.qml" 2>/dev/null && echo IN-IMAGE || echo MISSING)"
say "  logind power: $([ -f "$A/etc/systemd/logind.conf.d/90-ncde-power.conf" ] && echo IN-IMAGE || echo MISSING)"
say "== log: $LOG =="
