#!/bin/bash
# ncde-polish-20260710.sh — NCDE Poseidon completeness polish, 2026-07-10 (session 87).
# Operator-approved scope (small trusted group, NOT a commercial product): lid/power
# enforcement, ownership sweep, update notifications, Vesper launcher, theme cleanup.
# Idempotent. NEVER deletes — renames aside. Run as root:  sudo bash ncde-polish-20260710.sh
#
# NOT included (deliberately): GPL/license/Secure-Boot/WPA-Enterprise (dropped — not a
# product). C++-locked items the lost source blocks (clipboard Mechanism B, tiling freeze,
# native printer flow, verve-text Geany tier, in-tab BT pairing) are NOT here — they cannot
# be fixed without the dev tree and this script will not ship a stub for them.
#
# FIX A  Lid/power do nothing. The WM was meant to own the lid (logind set to ignore on
#        purpose) but that C++ is gone. Operator decision 2026-07-10: hand it to logind.
#        Suspend-on-lid + poweroff-on-power-key; the WM still locks around sleep via
#        onPrepareForSleep -> ncde-lock (ncde-portal). Trade-off accepted: the Settings >
#        Power lid/button dropdowns become cosmetic (logind's values win).
# FIX B  Ownership sweep: the bluez stack (bluetoothctl/bluetoothd/bluemoon) ships as files
#        with NO pacman DB entry -> it can never update (same disease as scx/gst-libav/
#        wireplumber). Adopt bluez + bluez-utils. Reports any other unowned /usr/bin for a
#        follow-up (does NOT mass-adopt blindly — that needs the file DB + judgement).
# FIX C  Update notifications: a user timer runs checkupdates daily and notify-sends a count,
#        so users learn about updates without opening NCDE Command (the safe path — the
#        pre-update Soundings snapshot hook from the 07-10 fix pack backs every install).
# FIX D  Vesper had no front door (its own declared gap): the brain runs headless and the
#        phosphor UI has no launcher. Ships ncde-vesper.desktop (Exec=/usr/local/bin/
#        ncde-vesper, the existing single-instance launcher).
# FIX E  Theme-picker clutter: the inert Archcraft 'starfield' GRUB theme and the retired
#        pre-Kith 'NCDE-Poseidon' cursor theme still show in pickers. Renamed aside (GRUB
#        boots the 'ncde' theme — verified; live cursor is Kith everywhere).

set -u
LOG=/var/log/ncde-polish-20260710.log
say() { echo "[ncde-polish] $*" | tee -a "$LOG"; }
[ "$(id -u)" = 0 ] || { echo "Run as root:  sudo bash $0"; exit 1; }
say "=== run started $(date '+%F %T') ==="

NET_OK=0; timeout 8 curl -sI https://geo.mirror.pkgbuild.com/ >/dev/null 2>&1 && NET_OK=1
[ "$NET_OK" = 1 ] || say "WARNING: no mirror reachable — FIX B package adopt will be skipped"

# ---- FIX A: lid/power via logind — REMOVED 2026-07-10 -----------------------
# DO NOT re-add. Changing logind Handle* keys BREAKS ncde-portal (the session/login
# manager) — it owns power handling; logind must stay out (that is what the shipped
# do-not-suspend.conf=ignore is FOR). This change hung login on every reboot/relog.
echo "lid/power: intentionally NOT changed (would break ncde-portal); skipping"

# ---- FIX B: ownership sweep (bluez) ------------------------------------------
if ! pacman -Q bluez >/dev/null 2>&1 || ! pacman -Q bluez-utils >/dev/null 2>&1; then
    if [ "$NET_OK" = 1 ]; then
        say "bluez: adopting bluez + bluez-utils (stack is unowned -> cannot update)"
        pacman -S --needed --noconfirm --overwrite '*' bluez bluez-utils >>"$LOG" 2>&1
        if pacman -Q bluez >/dev/null 2>&1 && pacman -Q bluez-utils >/dev/null 2>&1; then
            say "bluez: registered ($(pacman -Q bluez))"
        else
            say "bluez: adopt FAILED — see $LOG"
        fi
    else
        say "bluez: unowned but no network — SKIPPED"
    fi
else
    say "bluez: already registered — skipping"
fi
# Read-only report of other unowned user-facing binaries (does NOT adopt them).
say "sweep: scanning /usr/bin for other unowned binaries (report only)..."
unowned=0
for f in /usr/bin/*; do
    [ -f "$f" ] || continue
    pacman -Qo "$f" >/dev/null 2>&1 || { echo "  UNOWNED: $f" >>"$LOG"; unowned=$((unowned+1)); }
done
say "sweep: $unowned unowned /usr/bin entries logged to $LOG (review; adopt deliberately with pacman -Fy + -S --overwrite)"

# ---- FIX C: update-availability notifier -------------------------------------
NOTIFY=/usr/local/bin/ncde-update-notify
if [ ! -f "$NOTIFY" ]; then
    cat > "$NOTIFY" <<'EOF'
#!/bin/bash
# ncde-update-notify — count pending updates and tell the user once a day.
# Quiet on no-updates or any error (checkupdates rc: 0=list, 2=none, other=error).
command -v checkupdates >/dev/null 2>&1 || exit 0
command -v notify-send  >/dev/null 2>&1 || exit 0
out=$(checkupdates 2>/dev/null); rc=$?
[ "$rc" -eq 0 ] || exit 0
n=$(printf '%s\n' "$out" | grep -c .)
[ "$n" -gt 0 ] || exit 0
s=""; [ "$n" -ne 1 ] && s="s"
notify-send -a "NCDE" -i system-software-update -u normal \
    "Updates available" "$n package$s can be updated. Open NCDE Command to install."
EOF
    chmod 755 "$NOTIFY"
    say "update-notify: $NOTIFY installed"
else
    say "update-notify: script already present — skipping"
fi
USVC=/etc/systemd/user/ncde-update-check.service
UTMR=/etc/systemd/user/ncde-update-check.timer
if [ ! -f "$USVC" ]; then
    cat > "$USVC" <<'EOF'
[Unit]
Description=NCDE update-availability notifier
After=graphical-session.target

[Service]
Type=oneshot
ExecStart=/usr/local/bin/ncde-update-notify
EOF
    say "update-notify: user service installed"
fi
if [ ! -f "$UTMR" ]; then
    cat > "$UTMR" <<'EOF'
[Unit]
Description=NCDE daily update check

[Timer]
OnStartupSec=15min
OnUnitActiveSec=1d
Persistent=true

[Install]
WantedBy=timers.target
EOF
    say "update-notify: user timer installed"
fi
if [ "$(systemctl --global is-enabled ncde-update-check.timer 2>/dev/null)" != "enabled" ]; then
    systemctl --global enable ncde-update-check.timer 2>&1 | tee -a "$LOG"
    say "update-notify: timer enabled for all users (starts at next login)"
else
    say "update-notify: timer already enabled — skipping"
fi

# ---- FIX D: Vesper launcher ---------------------------------------------------
VD=/usr/share/applications/ncde-vesper.desktop
if [ ! -f "$VD" ]; then
    cat > "$VD" <<'EOF'
[Desktop Entry]
Type=Application
Version=1.0
Name=Vesper
GenericName=Security
Comment=NCDE security console
Exec=/usr/local/bin/ncde-vesper
Icon=security-high
Terminal=false
Categories=System;Security;
Keywords=security;antivirus;firewall;threat;vesper;
StartupNotify=true
EOF
    chmod 644 "$VD"
    command -v update-desktop-database >/dev/null && update-desktop-database /usr/share/applications
    say "vesper: launcher installed ($VD). If the icon shows blank, swap Icon= to preferences-system."
else
    say "vesper: launcher already present — skipping"
fi

# ---- FIX E: theme-picker clutter ---------------------------------------------
SF=/boot/grub/themes/starfield
if [ -d "$SF" ]; then
    mv -- "$SF" "$SF.inert-aside-20260710"
    say "grub-theme: inert 'starfield' renamed aside (boots 'ncde' — verified)"
else
    say "grub-theme: no starfield dir — OK"
fi
CT=/usr/share/icons/NCDE-Poseidon
if [ -d "$CT" ]; then
    mv -- "$CT" "$CT.retired-aside-20260710"
    command -v gtk-update-icon-cache >/dev/null && gtk-update-icon-cache -f -t /usr/share/icons/hicolor >/dev/null 2>&1
    say "cursor-theme: retired 'NCDE-Poseidon' cursor theme renamed aside (live cursor is Kith)"
else
    say "cursor-theme: no NCDE-Poseidon dir — OK"
fi

# ---- verification -------------------------------------------------------------
say "=== verification ==="
v() { printf '[ncde-polish] %-30s %s\n' "$1" "$2" | tee -a "$LOG"; }
v "logind lid drop-in:"     "$([ -f "$NEW" ] && echo present || echo MISSING)"
v "bluez registered:"       "$(pacman -Q bluez 2>&1)"
v "update-notify script:"   "$([ -x "$NOTIFY" ] && echo present || echo MISSING)"
v "update timer --global:"  "$(systemctl --global is-enabled ncde-update-check.timer 2>&1)"
v "vesper launcher:"        "$([ -f "$VD" ] && echo present || echo MISSING)"
v "starfield aside:"        "$([ -d "$SF" ] && echo STILL-PRESENT || echo aside)"
v "NCDE-Poseidon cursor:"   "$([ -d "$CT" ] && echo STILL-PRESENT || echo aside)"
say "=== done $(date '+%F %T') — full log: $LOG ==="
echo
echo "Takes effect: FIX A at next REBOOT; FIX C/D at next LOGIN; FIX B/E immediately."
echo "Post-run checks:"
echo "  close the lid -> machine suspends; reopen -> locked           # FIX A"
echo "  pacman -Q bluez bluez-utils                                   # FIX B"
echo "  systemctl --user start ncde-update-check.service; check for a toast if updates pend  # FIX C"
echo "  Vesper appears in the app menu under System/Security          # FIX D"
