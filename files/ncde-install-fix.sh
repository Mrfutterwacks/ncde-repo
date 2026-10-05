#!/bin/bash
# ncde-install-fix.sh — post-install repair for NCDE installed nodes.
# Every fix here was ROOT-CAUSED LIVE on installed node "ncde", 2026-07-08.
# Idempotent: safe to re-run; skips anything already correct. Never deletes
# (leftovers are renamed aside). Run as root:  sudo bash ncde-install-fix.sh
#
# Fixes:
#  1. pacman keyring born empty  -> every update fails ("keyring is not writable",
#     "Errors occurred, no packages were upgraded"). Installer bug: the guard in
#     chrooted_post_install.sh:_init_pacman_keyring() checked trustdb.gpg EXISTENCE,
#     but gpg auto-creates a trustdb with zero keys; must check KEY COUNT.
#  2. /etc/mkinitcpio.conf.d/archiso.conf (live-ISO drop-in) left on target ->
#     every kernel update half-fails (archiso hooks not installed) and builds a
#     bloated no-autodetect initramfs (225MB vs 22MB, proven tonight).
#  3. /usr/bin/yay ships unpackaged with NO build toolchain (git/fakeroot/base-devel
#     all absent) -> ncde-command font/AUR installs detect yay but can never build.
#  4. ncde-sentinel.service ships active-but-disabled -> hardware guardian dies on
#     first reboot.
#  5. Weather widget blank after boot: the WM fetches at ~5s after login (before DNS
#     is up on most boots), then not again for 30 min, with no connectivity retry
#     (proven from the binary: WidgetData::onPulse -> fetchWeather at tick==5 and
#     tick%1800==0 only). C++ source is gone, so WeatherPanel.qml (loaded from disk
#     as plain text) carries a fallback: it fetches the SAME open-meteo endpoint
#     (URL + WMO icon table extracted verbatim from the binary) every 20s while the
#     WM has no data, and yields the moment real data arrives. Deploys only if the
#     target file md5-matches the known pristine version; original kept as .prebak.
#  6. Top-bar network icon shows red X while connected: sentinel's udev_monitor.py
#     reported per-event operstate for EVERY net iface (lo "unknown" -> false;
#     mid-reauth wifi "dormant" -> false with no follow-up udev event when it
#     settles) and Lelan stores the LAST event's bool -> stuck red X. Patched:
#     aggregate "any real iface up" + one-shot 3s re-check. Session 86.
#  8. Vesper brain wedged: engines ran INLINE per HTTP GET (a cold clamscan
#     reloads the whole ClamAV DB, ~30s+ on the reference Celeron) while the UI
#     polls every 6s into a single-threaded server -> accept queue jammed, every
#     endpoint timed out, Security tab blank. Patched: engines in one background
#     cache thread, clamdscan via the running clamav-daemon (~10ms),
#     ThreadingHTTPServer. Session 86.
#  9. rkhunter installed but Vesper reports it absent: Arch packages rkhunter
#     root-only (/usr/bin/rkhunter mode 0700), so the user-scope vesper-brain
#     can neither see nor run it — and nothing ever scheduled a scan anywhere.
#     Fix: ncde-rkhunter.timer (daily, root) runs rkhunter-scan.sh which writes
#     a world-readable report to /var/lib/ncde-vesper/rkhunter-report; the
#     patched vesper_engines.py (fix 8's file, updated) reads it. Plus
#     rkhunter.conf.local with the verified-benign Arch whitelists. Session 86 pt2.
# 10. SECURITY: /etc/ssh/sshd_config.d/10-archiso.conf (unowned live-ISO leftover,
#     same class as the gnupg mount unit) ships PermitRootLogin yes +
#     PasswordAuthentication yes onto every installed system, with sshd enabled.
#     Root password SSH login open on every install. Moved aside + explicit
#     PermitRootLogin no in the main sshd_config (which is also the only file
#     rkhunter 1.4.6 reads — drop-ins are invisible to it). Session 86 pt2.

set -u
LOG=/var/log/ncde-install-fix.log
say() { echo "[ncde-fix] $*" | tee -a "$LOG"; }

if [ "$(id -u)" != 0 ]; then
    echo "Run as root:  sudo bash $0"
    exit 1
fi
say "=== run started $(date '+%F %T') ==="

# ---- 0. archiso gnupg tmpfs mount unit — THE keyring killer -------------------
# Live-ISO unit that ships onto targets (unowned). While the file exists, pacman's
# gpg sockets pull an EMPTY tmpfs over the real keyring at every boot -> updates
# fail even when the on-disk keyring is fully populated. Root-caused 2026-07-09
# on a VM install (180 keys on disk UNDER the tmpfs) + operator node (same).
MU=/etc/systemd/system/etc-pacman.d-gnupg.mount
if [ -f "$MU" ]; then
    say "gnupg-mount: live-ISO tmpfs unit present — removing (it hides the real keyring)"
    systemctl stop etc-pacman.d-gnupg.mount 2>/dev/null || true
    mv -- "$MU" "$MU.iso-leftover-disabled"
    if [ -f /etc/systemd/system/pacman-init.service ]; then
        mv -- /etc/systemd/system/pacman-init.service \
              /etc/systemd/system/pacman-init.service.iso-leftover-disabled
    fi
    systemctl daemon-reload
    say "gnupg-mount: removed — real /etc/pacman.d/gnupg is now the live one"
else
    say "gnupg-mount: not present — OK"
fi

# ---- 1. pacman keyring -------------------------------------------------------
pubs=$(pacman-key --list-keys 2>/dev/null | grep -c '^pub')
if [ "${pubs:-0}" -eq 0 ]; then
    say "keyring: EMPTY -> pacman-key --init && --populate"
    pacman-key --init 2>&1 | tail -2 | tee -a "$LOG"
    pacman-key --populate 2>&1 | tail -2 | tee -a "$LOG"
    pubs=$(pacman-key --list-keys 2>/dev/null | grep -c '^pub')
    if [ "${pubs:-0}" -gt 0 ]; then
        say "keyring: OK — $pubs public keys loaded"
    else
        say "keyring: STILL EMPTY after init — STOP and investigate before updating"
    fi
else
    say "keyring: OK ($pubs keys) — skipping"
fi

# ---- 2. live-ISO mkinitcpio leftover ----------------------------------------
DROPIN=/etc/mkinitcpio.conf.d/archiso.conf
if [ -f "$DROPIN" ]; then
    say "mkinitcpio: disabling live-ISO leftover (renamed, not deleted)"
    mv -- "$DROPIN" "$DROPIN.iso-leftover-disabled"
    say "mkinitcpio: rebuilding all presets"
    if mkinitcpio -P 2>&1 | tee -a "$LOG" | grep -q "ERROR"; then
        say "mkinitcpio: ERRORS during rebuild — DO NOT REBOOT until resolved (see $LOG)"
    else
        say "mkinitcpio: clean rebuild"
    fi
else
    say "mkinitcpio: no archiso leftover — skipping"
fi

# ---- 3. AUR/build toolchain for yay + ncde-command fonts ---------------------
# The ISO tree carries the toolchain's FILES (gcc/make/fakeroot/git/gdb, 4493 files
# across 24 packages) copied in WITHOUT pacman DB entries — so audits saw a complete
# system while pacman refuses to install over the unowned duplicates ("exists in
# filesystem"). --overwrite lets the real packages take ownership; every conflicting
# file was verified unowned (pacman -Qo: "No package owns") on node "ncde" 2026-07-08.
if ! pacman -Q git >/dev/null 2>&1 || ! pacman -Q fakeroot >/dev/null 2>&1; then
    say "aur: base-devel/git missing — installing (full sync; needs network + fix 1)"
    pacman -Syu --needed --noconfirm --overwrite '*' base-devel git >>"$LOG" 2>&1
    rc=$?
    if [ $rc -eq 0 ] && pacman -Q git >/dev/null 2>&1 && pacman -Q fakeroot >/dev/null 2>&1; then
        say "aur: toolchain installed and registered — yay can now build AUR packages"
    else
        say "aur: install FAILED (exit $rc) — see $LOG, fix cause, re-run this script"
    fi
else
    say "aur: toolchain already present — skipping"
fi

# ---- 4. ncde-sentinel enablement ---------------------------------------------
if systemctl cat ncde-sentinel.service >/dev/null 2>&1; then
    if [ "$(systemctl is-enabled ncde-sentinel.service 2>/dev/null)" != "enabled" ]; then
        systemctl enable ncde-sentinel.service 2>&1 | tee -a "$LOG"
        say "sentinel: enabled (was going to die on next reboot)"
    else
        say "sentinel: already enabled — skipping"
    fi
else
    say "sentinel: unit not present on this node — skipping"
fi

# ---- 5. weather widget: QML fallback fetch -----------------------------------
WP=/usr/share/ncde/WeatherPanel.qml
PRISTINE_MD5="8f25de8a1f35f5f48b209ee1dd94271d"
PATCHED_MD5="8623eebaeee818d0f261ee70de383af2"
PATCH_SRC="$(dirname "$(readlink -f "$0")")/WeatherPanel.qml.patched"
if [ -f "$WP" ] && [ -f "$PATCH_SRC" ]; then
    cur=$(md5sum "$WP" | cut -d' ' -f1)
    if [ "$cur" = "$PATCHED_MD5" ]; then
        say "weather: patch already deployed — skipping"
    elif [ "$cur" = "$PRISTINE_MD5" ]; then
        cp -a -- "$WP" "$WP.prebak-$(date +%Y%m%d)-weatherfix"
        cp -- "$PATCH_SRC" "$WP"
        chown root:root "$WP" && chmod 644 "$WP"
        say "weather: patched WeatherPanel.qml deployed (original kept as .prebak)."
        say "weather: takes effect at next login/session restart."
    else
        say "weather: $WP is an UNKNOWN version (md5 $cur) — NOT touching it."
    fi
else
    [ -f "$PATCH_SRC" ] || say "weather: WeatherPanel.qml.patched not found next to this script — skipping"
fi

# ---- 6. network icon: sentinel udev aggregate --------------------------------
UM=/usr/local/bin/sentinel/udev_monitor.py
UM_PRISTINE="25eb32b6a4147ca563d20388fd6dab87"
UM_PATCHED="825ba23d95ab1a879d8064b2f04b5bcb"
UM_SRC="$(dirname "$(readlink -f "$0")")/udev_monitor.py"
if [ -f "$UM" ] && [ -f "$UM_SRC" ]; then
    cur=$(md5sum "$UM" | cut -d' ' -f1)
    if [ "$cur" = "$UM_PATCHED" ]; then
        say "neticon: patch already deployed — skipping"
    elif [ "$cur" = "$UM_PRISTINE" ]; then
        cp -a -- "$UM" "$UM.prebak-$(date +%Y%m%d)-netaggregate"
        cp -- "$UM_SRC" "$UM"
        chown root:root "$UM" && chmod 644 "$UM"
        systemctl try-restart ncde-sentinel.service 2>/dev/null || true
        say "neticon: sentinel udev aggregate deployed + sentinel restarted"
    else
        say "neticon: $UM is an UNKNOWN version (md5 $cur) — NOT touching it."
    fi
else
    [ -f "$UM_SRC" ] || say "neticon: udev_monitor.py not found next to this script — skipping"
    [ -f "$UM" ] || say "neticon: sentinel not present on this node — skipping"
fi

# ---- 7. audio: wireplumber/pipewire-pulse never preset-enabled ----------------
# Third instance of the unregistered-tree-copy disease (2026-07-09): the packages'
# files ship but pacman never ran their install hooks, so the user-session enables
# don't exist -> PipeWire runs with NO session manager -> zero sinks, no sound on
# every install. Enable globally + adopt the packages so updates work.
if [ "$(systemctl --global is-enabled wireplumber.service 2>/dev/null)" != "enabled" ]; then
    say "audio: enabling wireplumber + pipewire-pulse for all users"
    systemctl --global enable wireplumber.service pipewire-pulse.socket 2>&1 | tee -a "$LOG"
    say "audio: enabled — takes effect at next login"
else
    say "audio: already enabled — skipping"
fi
if ! pacman -Q wireplumber >/dev/null 2>&1; then
    say "audio: registering wireplumber/pipewire-pulse in pacman DB (needs network)"
    pacman -S --needed --noconfirm --overwrite '*' wireplumber pipewire-pulse >>"$LOG" 2>&1 \
        && say "audio: registered" || say "audio: registration FAILED — re-run with network"
fi

# ---- 8. vesper brain: engine cache + clamdscan --------------------------------
VD=/usr/lib/ncde/vesper
# known-good md5 chains: pristine (pre-session-86) and the interim enginecache
# versions are both acceptable upgrade bases; PATCHED = session-86-pt2 (rkhunter).
BS_KNOWN="2ee60f66011f9c4867156114c48a2768 08184be8f109863adf80af1a3c379ec3"
BS_PATCHED="ca2a97603e38887a9a3c44d28aa16c23"
VE_KNOWN="20f04ff1cc548cfa7b64fc766042ff74 37c737d38da4f7bf49ec60385c9bc8a0 aba02e725e881363e4bc10bef83e741c"
VE_PATCHED="f5b5f873916947ce9b0145f9c16118b5"
KITDIR="$(dirname "$(readlink -f "$0")")"
vesper_deploy() {  # $1=file $2=known-md5s(space-sep) $3=patched-md5 -> 0 if deployed/current
    local f="$VD/$1" src="$KITDIR/$1" cur known ok=0
    [ -f "$f" ] && [ -f "$src" ] || { say "vesper: $1 or its kit copy missing — skipping"; return 1; }
    cur=$(md5sum "$f" | cut -d' ' -f1)
    if [ "$cur" = "$3" ]; then say "vesper: $1 already patched"; return 0; fi
    for known in $2; do [ "$cur" = "$known" ] && ok=1; done
    if [ "$ok" != 1 ]; then say "vesper: $1 UNKNOWN version (md5 $cur) — NOT touching it."; return 1; fi
    cp -a -- "$f" "$f.prebak-$(date +%Y%m%d)-enginecache"
    cp -- "$src" "$f"; chown root:root "$f"; chmod 644 "$f"
    say "vesper: $1 deployed"; return 0
}
if vesper_deploy brain_server.py "$BS_KNOWN" "$BS_PATCHED" \
   && vesper_deploy vesper_engines.py "$VE_KNOWN" "$VE_PATCHED"; then
    # restart the USER unit as the real desktop user — NEVER hardcode a name
    RUSER="${SUDO_USER:-}"
    if [ -z "$RUSER" ] || [ "$RUSER" = root ]; then
        RUSER=$(loginctl list-sessions --no-legend 2>/dev/null | awk '$3!="" && $3!="root" {print $3; exit}')
    fi
    if [ -n "$RUSER" ]; then
        RUID=$(id -u "$RUSER")
        runuser -u "$RUSER" -- env XDG_RUNTIME_DIR="/run/user/$RUID" \
            systemctl --user try-restart vesper-brain.service 2>/dev/null \
            && say "vesper: brain restarted for $RUSER" \
            || say "vesper: brain not running for $RUSER — fixed code starts at next login"
    else
        say "vesper: no desktop user logged in — fixed code starts at next login"
    fi
fi

# ---- 9. rkhunter activation for Vesper ----------------------------------------
if [ -f /usr/bin/rkhunter ]; then
    changed=0
    for pair in "rkhunter-scan.sh:/usr/lib/ncde/vesper/rkhunter-scan.sh:0755" \
                "ncde-rkhunter.service:/usr/lib/systemd/system/ncde-rkhunter.service:0644" \
                "ncde-rkhunter.timer:/usr/lib/systemd/system/ncde-rkhunter.timer:0644" \
                "rkhunter.conf.local:/etc/rkhunter.conf.local:0600"; do
        src="$KITDIR/${pair%%:*}"; rest="${pair#*:}"; dst="${rest%%:*}"; mode="${rest##*:}"
        [ -f "$src" ] || { say "rkhunter: ${pair%%:*} not found next to this script — skipping fix 9"; changed=-1; break; }
        if [ ! -f "$dst" ] || ! cmp -s "$src" "$dst"; then
            install -m"$mode" -o root -g root "$src" "$dst"
            say "rkhunter: installed $dst"
            changed=1
        fi
    done
    if [ "$changed" -ge 0 ]; then
        [ "$changed" = 1 ] && systemctl daemon-reload
        if [ "$(systemctl is-enabled ncde-rkhunter.timer 2>/dev/null)" != "enabled" ]; then
            systemctl enable --now ncde-rkhunter.timer 2>&1 | tee -a "$LOG"
            say "rkhunter: daily scan timer enabled"
        else
            say "rkhunter: timer already enabled — skipping"
        fi
        if [ ! -f /var/lib/ncde-vesper/rkhunter-report ]; then
            say "rkhunter: starting first scan in background (~2-5 min; Vesper shows it when done)"
            systemctl start --no-block ncde-rkhunter.service
        fi
    fi
else
    say "rkhunter: not installed on this node — skipping"
fi

# ---- 10. SECURITY: archiso sshd drop-in allows root password login -------------
SD=/etc/ssh/sshd_config.d/10-archiso.conf
sshd_changed=0
if [ -f "$SD" ]; then
    mv -- "$SD" "$SD.iso-leftover-disabled"
    say "sshd: root-login drop-in moved aside (was PermitRootLogin yes)"
    sshd_changed=1
fi
if ! grep -q '^PermitRootLogin no' /etc/ssh/sshd_config; then
    printf '\n# NCDE hardening (ncde-install-fix fix 10)\nPermitRootLogin no\nProtocol 2\n' >> /etc/ssh/sshd_config
    say "sshd: PermitRootLogin no pinned in main sshd_config"
    sshd_changed=1
fi
if [ "$sshd_changed" = 1 ]; then
    if /usr/sbin/sshd -t 2>>"$LOG"; then
        systemctl try-restart sshd 2>/dev/null || true
        say "sshd: config valid, service restarted"
    else
        say "sshd: CONFIG TEST FAILED — see $LOG, sshd NOT restarted"
    fi
else
    say "sshd: already hardened — skipping"
fi

say "=== done $(date '+%F %T') — full log: $LOG ==="
