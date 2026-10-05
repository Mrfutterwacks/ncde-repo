#!/bin/bash
# ncde-fix-pack-20260710.sh — NCDE Poseidon live-system fix pack, 2026-07-10.
# Built from the full docs-vs-live audit of node "ncde" (session 87):
# four parallel audit passes (Lelan/Sentinel/Zen, Vesper/security,
# completeness/commercial, apps/GliaTalk/recovery) + the installer-fix review.
# Idempotent — safe to re-run. NEVER deletes (renames aside). Run as root:
#   sudo bash ncde-fix-pack-20260710.sh
#
# FIX 1  Audio packages unregistered + not global-enabled (field-kit fix 7 was
#        never run on this node): wireplumber/pipewire-pulse absent from the
#        pacman DB (they can never update) and `systemctl --global` disabled
#        (a NEW user account would get no sound). Your own session works via
#        user-scope enables — this makes it durable and updatable.
# FIX 2  GStreamer libav plugin is DEAD system-wide: the vendored (unowned)
#        libgstlibav.so was built against libjxl.so.0.11; system has 0.12 →
#        every H.264/AAC/libav decode path fails to load. Fix = install the
#        real gst-libav package (adopts the orphan, stays updated).
# FIX 3  sched_ext REGRESSION: Sentinel selects scx_bpfland but scx_loader
#        fails — "org.scx.loader.manage-schedulers is not registered". The
#        scx binaries are hand-copied (unowned) and the polkit action file
#        never shipped. Fix = install scx-tools (owns scx_loader + the
#        org.scx.Loader.policy) + scx-scheds (owns scx_bpfland), restart.
# FIX 4  iio-sensor-proxy absent (sentinel-plan §4e wants it; Sentinel logs
#        "auto-rotation unavailable"). Install + enable.
# FIX 5  Three of Vesper's five engines have no data source: fail2ban, auditd,
#        nftables all disabled/inactive while the Settings toggle says "All
#        five engines active". Enables auditd, fail2ban (sshd jail, systemd
#        backend), and nftables with the kickass-guard.md §9.7 table
#        (policy ACCEPT — watcher rules only, cannot block Magpie/LAN).
# FIX 6  /etc/systemd/system/pacman-init.service — live-ISO leftover still on
#        disk (the gnupg mount unit's companion; the unit file itself is the
#        hazard class from §0.17). Renamed aside like the field kit does.
# FIX 7  Timeshift is still user-visible (completeness rm-list item): orphaned
#        timeshift-gtk.desktop shipped although Soundings is the restore path.
#        .desktop renamed aside (binaries left for the operator's own rm).
# FIX 8  Pre-update snapshot hook (commercial.md high-impact item): the
#        ncde-snapshot helper exists but only runs at boot. Installs a pacman
#        PreTransaction hook so every update is preceded by a Soundings
#        snapshot (tagged "update"; failure never blocks the update).
# FIX 9  This node never got the in-image field kit (/usr/local/share/ncde-fix
#        — it was installed from the pre-fix ISO). Installs the current kit
#        (v2, fixes 0-10) + companions + both fix packs from the best source.
# FIX 10 Dormant drift hazard: /usr/share/ncde/controls/ duplicate widgets
#        never got the B-S1 reduce-motion gating the live copies have.
#        Gates their animation durations the same way (guarded, backed up).
# FIX 11 (PROMPT) LaPivot cap_sys_nice trade-off: the file capability makes
#        the WM non-dumpable, so xdg-desktop-portal cannot read
#        /proc/<pid>/root and Lelan's portal Settings leg fails (journal:
#        "Portal operation not allowed"). KEEPING the cap keeps the RT boost
#        (SCHED_FIFO) and loses the portal leg (affects sandboxed-app
#        dark/light detection only — NCDE's own GTK bridge is unaffected and
#        verified writing). Removing it heals the portal but drops the boost.
#        Default: KEEP (no change). Asked interactively.

set -u
LOG=/var/log/ncde-fix-20260710.log
say() { echo "[ncde-fix-0710] $*" | tee -a "$LOG"; }

if [ "$(id -u)" != 0 ]; then
    echo "Run as root:  sudo bash $0"
    exit 1
fi
say "=== run started $(date '+%F %T') ==="

NET_OK=0
if timeout 8 curl -sI https://geo.mirror.pkgbuild.com/ >/dev/null 2>&1; then NET_OK=1; fi
[ "$NET_OK" = 1 ] || say "WARNING: no mirror reachable — package fixes (1,2,3,4,5) will be skipped this run"

# ---- 1. audio: register + global-enable wireplumber/pipewire-pulse -----------
if [ "$(systemctl --global is-enabled wireplumber.service 2>/dev/null)" != "enabled" ]; then
    say "audio: enabling wireplumber + pipewire-pulse for all users"
    systemctl --global enable wireplumber.service pipewire-pulse.socket 2>&1 | tee -a "$LOG"
else
    say "audio: global enable already present — skipping"
fi
if ! pacman -Q wireplumber >/dev/null 2>&1 && [ "$NET_OK" = 1 ]; then
    say "audio: registering wireplumber/pipewire-pulse in the pacman DB"
    pacman -S --needed --noconfirm --overwrite '*' wireplumber pipewire-pulse >>"$LOG" 2>&1 \
        && say "audio: registered (updates will now arrive)" \
        || say "audio: registration FAILED — see $LOG"
elif pacman -Q wireplumber >/dev/null 2>&1; then
    say "audio: packages already registered — skipping"
fi

# ---- 2. gst-libav vs libjxl 0.12 ---------------------------------------------
if ! pacman -Q gst-libav >/dev/null 2>&1 && [ "$NET_OK" = 1 ]; then
    say "gstreamer: installing gst-libav (vendored copy is linked to missing libjxl.so.0.11)"
    pacman -S --needed --noconfirm --overwrite '*' gst-libav >>"$LOG" 2>&1 \
        && say "gstreamer: gst-libav installed — verify as your user: gst-inspect-1.0 avdec_h264" \
        || say "gstreamer: install FAILED — see $LOG"
elif pacman -Q gst-libav >/dev/null 2>&1; then
    say "gstreamer: gst-libav already registered — skipping"
fi

# ---- 3. sched_ext: scx-tools/scx-scheds + polkit action ----------------------
if [ ! -f /usr/share/polkit-1/actions/org.scx.Loader.policy ] && [ "$NET_OK" = 1 ]; then
    say "scx: installing scx-tools + scx-scheds (adopts unowned scx_loader/scx_bpfland, ships the polkit action)"
    pacman -S --needed --noconfirm --overwrite '*' scx-tools scx-scheds >>"$LOG" 2>&1
    if [ -f /usr/share/polkit-1/actions/org.scx.Loader.policy ]; then
        systemctl daemon-reload
        systemctl restart scx_loader.service 2>&1 | tee -a "$LOG"
        sleep 3
        state=$(cat /sys/kernel/sched_ext/state 2>/dev/null)
        say "scx: polkit action installed; sched_ext state now: ${state:-unknown}"
        say "scx: if still 'disabled', it engages after Sentinel's next selection: sudo systemctl restart ncde-sentinel"
    else
        say "scx: install FAILED (policy still absent) — see $LOG"
    fi
else
    [ -f /usr/share/polkit-1/actions/org.scx.Loader.policy ] && say "scx: polkit action already present — skipping"
fi

# ---- 4. iio-sensor-proxy ------------------------------------------------------
if ! pacman -Q iio-sensor-proxy >/dev/null 2>&1 && [ "$NET_OK" = 1 ]; then
    say "sensors: installing iio-sensor-proxy (Sentinel auto-rotation bridge)"
    pacman -S --needed --noconfirm iio-sensor-proxy >>"$LOG" 2>&1 \
        && systemctl enable --now iio-sensor-proxy.service 2>&1 | tee -a "$LOG" \
        && say "sensors: installed + enabled (Sentinel's SensorProxyBridge picks it up on its next start)" \
        || say "sensors: install FAILED — see $LOG"
elif pacman -Q iio-sensor-proxy >/dev/null 2>&1; then
    say "sensors: iio-sensor-proxy already installed — skipping"
fi

# ---- 5. Vesper engine backends: auditd, fail2ban, nftables --------------------
# 5a. auditd — stock rules; the Vesper adapter reads ausearch.
if [ "$(systemctl is-enabled auditd.service 2>/dev/null)" != "enabled" ]; then
    systemctl enable --now auditd.service 2>&1 | tee -a "$LOG"
    say "vesper: auditd enabled + started"
else
    say "vesper: auditd already enabled — skipping"
fi
# 5b. fail2ban — sshd jail (sshd is enabled+active on this node), systemd
#     backend (Arch has no auth.log), nftables banaction. ArchWiki-verified shape.
F2B=/etc/fail2ban/jail.d/ncde-sshd.local
if [ ! -f "$F2B" ]; then
    cat > "$F2B" <<'EOF'
# NCDE fix 2026-07-10 — minimal sshd jail so Vesper's fail2ban engine has a
# data source (vesper.md: five engines; fail2ban was installed but never ran).
[sshd]
enabled   = true
backend   = systemd
banaction = nftables
maxretry  = 5
findtime  = 1d
bantime   = 2w
ignoreip  = 127.0.0.1/8 ::1
EOF
    say "vesper: fail2ban sshd jail written ($F2B)"
else
    say "vesper: fail2ban jail already present — skipping write"
fi
if [ "$(systemctl is-enabled fail2ban.service 2>/dev/null)" != "enabled" ]; then
    systemctl enable --now fail2ban.service 2>&1 | tee -a "$LOG"
    sleep 2
    fail2ban-client status sshd >>"$LOG" 2>&1 && say "vesper: fail2ban running, sshd jail active" \
        || say "vesper: fail2ban started but sshd jail NOT confirmed — see $LOG"
else
    say "vesper: fail2ban already enabled — skipping"
fi
# 5c. nftables — the kickass-guard.md §9.7 watcher table (policy ACCEPT: a
#     portscan meter + C2 blocklist set; the retired Ollama-UID rule dropped).
#     The stock Arch /etc/nftables.conf is a policy-DROP firewall that would
#     break Magpie LAN discovery — it is moved aside, never merged.
NFT=/etc/nftables.conf
if ! grep -q "table inet kickass" "$NFT" 2>/dev/null; then
    [ -f "$NFT" ] && mv -- "$NFT" "$NFT.stock-aside-20260710" && say "vesper: stock policy-drop nftables.conf set aside"
    cat > "$NFT" <<'EOF'
#!/usr/bin/nft -f
# NCDE fix 2026-07-10 — kickass-guard.md §9.7 watcher table (non-LLM Vesper era).
# Policy ACCEPT on both hooks: this table only meters portscans and drops
# traffic to the C2 blocklist set (fed by a future ThreatEngine; empty = inert).
# It cannot block Magpie/avahi/normal traffic.
destroy table inet kickass
table inet kickass {
  set c2_blocklist { type ipv4_addr; flags interval; }
  chain input {
    type filter hook input priority filter; policy accept;
    tcp flags & (fin|syn|rst|ack) == syn ct state new limit rate over 10/second burst 20 packets log prefix "KICKASS_PORTSCAN: " counter drop
  }
  chain output {
    type filter hook output priority filter; policy accept;
    ip daddr @c2_blocklist log prefix "KICKASS_C2_BLOCK: " counter drop
  }
}
EOF
    if nft -c -f "$NFT" >>"$LOG" 2>&1; then
        say "vesper: kickass nftables ruleset written + syntax-checked"
    else
        say "vesper: nft syntax check FAILED — restoring stock file, NOT enabling"
        mv -- "$NFT" "$NFT.failed-20260710"
        [ -f "$NFT.stock-aside-20260710" ] && mv -- "$NFT.stock-aside-20260710" "$NFT"
    fi
else
    say "vesper: kickass table already in nftables.conf — skipping write"
fi
if grep -q "table inet kickass" "$NFT" 2>/dev/null; then
    if [ "$(systemctl is-enabled nftables.service 2>/dev/null)" != "enabled" ]; then
        systemctl enable --now nftables.service 2>&1 | tee -a "$LOG"
        nft list tables 2>/dev/null | grep -q kickass && say "vesper: nftables active, kickass table loaded" \
            || say "vesper: nftables enabled but kickass table NOT listed — check $LOG"
    else
        say "vesper: nftables already enabled — skipping"
    fi
fi

# ---- 6. pacman-init.service leftover ------------------------------------------
PI=/etc/systemd/system/pacman-init.service
if [ -f "$PI" ]; then
    mv -- "$PI" "$PI.iso-leftover-disabled"
    systemctl daemon-reload
    say "pacman-init: live-ISO leftover unit renamed aside"
else
    say "pacman-init: not present — OK"
fi

# ---- 7. Timeshift .desktop (Soundings is the restore path) --------------------
TS=/usr/share/applications/timeshift-gtk.desktop
if [ -f "$TS" ]; then
    mv -- "$TS" "$TS.ncde-hidden-20260710"
    command -v update-desktop-database >/dev/null && update-desktop-database /usr/share/applications
    say "timeshift: menu entry renamed aside (binaries untouched — operator's rm call)"
else
    say "timeshift: menu entry already gone — OK"
fi

# ---- 8. pre-update Soundings snapshot hook -------------------------------------
WRAP=/usr/local/lib/ncde/ncde-snapshot-preupdate
HOOK=/etc/pacman.d/hooks/00-ncde-snapshot.hook
if [ -x /usr/local/lib/ncde/ncde-snapshot ]; then
    if [ ! -f "$WRAP" ]; then
        cat > "$WRAP" <<'EOF'
#!/bin/bash
# ncde-snapshot-preupdate — runs the standard Soundings boot snapshotter before
# a pacman transaction, then retags the newest snapshot's sidecar "update" so
# the recovery UI shows why it exists. Never blocks the update (hook has no
# AbortOnFail); ncde-snapshot's own KEEP/space-valve pruning applies unchanged.
/usr/local/lib/ncde/ncde-snapshot || exit 0
meta=$(ls -1 /restore/BAK-*.meta 2>/dev/null | sort | tail -1)
[ -n "$meta" ] && sed -i 's/"tag":"boot"/"tag":"update"/' "$meta"
exit 0
EOF
        chmod 755 "$WRAP"
        say "snapshot-hook: wrapper installed ($WRAP)"
    else
        say "snapshot-hook: wrapper already present — skipping"
    fi
    if [ ! -f "$HOOK" ]; then
        mkdir -p /etc/pacman.d/hooks
        cat > "$HOOK" <<'EOF'
# NCDE fix 2026-07-10 — pre-update Soundings snapshot (commercial.md high-impact
# item: "pre-update snapshot hook"). PreTransaction, no AbortOnFail: a snapshot
# failure logs but never blocks the update.
[Trigger]
Operation = Install
Operation = Upgrade
Operation = Remove
Type = Package
Target = *

[Action]
Description = Soundings: snapshotting system before package changes...
When = PreTransaction
Exec = /usr/local/lib/ncde/ncde-snapshot-preupdate
EOF
        say "snapshot-hook: pacman hook installed ($HOOK)"
    else
        say "snapshot-hook: hook already present — skipping"
    fi
else
    say "snapshot-hook: /usr/local/lib/ncde/ncde-snapshot missing — SKIPPED (investigate)"
fi

# ---- 9. field kit onto this node (/usr/local/share/ncde-fix) -------------------
KIT=/usr/local/share/ncde-fix
SRC=""
for c in /home/stephen/ncde-ISO/staging/stick-kit /run/media/stephen/ARCHISO_EFI /run/media/stephen/EFF2-E845/my-project/files; do
    [ -f "$c/ncde-install-fix.sh" ] && SRC="$c" && break
done
if [ -n "$SRC" ]; then
    mkdir -p "$KIT"
    for f in ncde-install-fix.sh udev_monitor.py WeatherPanel.qml.patched brain_server.py \
             vesper_engines.py ncde-rkhunter.service ncde-rkhunter.timer rkhunter-scan.sh rkhunter.conf.local; do
        [ -f "$SRC/$f" ] && [ ! -f "$KIT/$f" ] && cp -- "$SRC/$f" "$KIT/$f"
    done
    # both fix packs ride along so the node carries its full repair history
    for p in /run/media/stephen/EFF2-E845/my-project/files/ncde-fix-pack-20260709.sh \
             /run/media/stephen/EFF2-E845/my-project/files/ncde-fix-pack-20260710.sh; do
        [ -f "$p" ] && [ ! -f "$KIT/$(basename "$p")" ] && cp -- "$p" "$KIT/"
    done
    chmod 755 "$KIT"/*.sh 2>/dev/null
    say "field-kit: installed to $KIT from $SRC ($(ls "$KIT" | wc -l) files)"
else
    say "field-kit: no source found (mount the install stick ESP or docs USB) — SKIPPED"
fi

# ---- 10. reduce-motion gating for dormant /usr/share/ncde/controls copies ------
python3 - <<'PYEOF' 2>&1 | tee -a "$LOG"
import os, re, shutil
d = "/usr/share/ncde/controls"
bak = ".prebak-20260710-reducemotion"
if not os.path.isdir(d):
    print("controls: dir absent — skipping")
    raise SystemExit
for fn in ("NCDEToggle.qml","NCDEButton.qml","NCDESlider.qml","NCDEField.qml","NCDECheck.qml","NCDEProgressBar.qml"):
    p = os.path.join(d, fn)
    if not os.path.isfile(p):
        print(f"controls: {fn} absent — skip"); continue
    src = open(p, encoding="utf-8").read()
    if "animPolicy" in src:
        print(f"controls: {fn} already gated — skip"); continue
    # Same gating the live copies got in session 77 (B-S1), guarded for
    # engines that lack the animPolicy context property.
    new, n = re.subn(r"duration:\s*(\d+)\b",
        r'duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : \1', src)
    if n == 0:
        print(f"controls: {fn} no duration literals — skip"); continue
    if not os.path.exists(p + bak):
        shutil.copy2(p, p + bak)
    tmp = p + ".fixtmp"
    open(tmp, "w", encoding="utf-8").write(new)
    os.replace(tmp, p)
    print(f"controls: {fn} gated {n} duration(s), backup kept")
PYEOF

# ---- 11. (PROMPT) LaPivot cap_sys_nice vs portal Settings leg ------------------
if [ -t 0 ]; then
    cur=$(getcap /usr/local/bin/LaPivot 2>/dev/null)
    echo
    echo "FIX 11 — trade-off decision. LaPivot currently: ${cur:-no capability}"
    echo "  KEEP the capability (default): WM keeps its SCHED_FIFO boost; the"
    echo "  xdg-desktop-portal Settings leg stays broken (sandboxed apps can't"
    echo "  read dark/light from the portal — NCDE's own theming unaffected)."
    echo "  REMOVE it: portal heals on next login; WM loses the RT boost."
    read -r -p "  Remove cap_sys_nice from LaPivot? [y/N] " YN
    if [ "$YN" = "y" ] || [ "$YN" = "Y" ]; then
        setcap -r /usr/local/bin/LaPivot && say "lapivot: capability removed — relog to take effect"
    else
        say "lapivot: capability kept (default) — portal Settings leg remains a known-open"
    fi
else
    say "lapivot: non-interactive run — capability left as-is (see FIX 11 header)"
fi

# ---- verification summary -------------------------------------------------------
say "=== verification ==="
v() { printf '[ncde-fix-0710] %-34s %s\n' "$1" "$2" | tee -a "$LOG"; }
v "audio --global wireplumber:"   "$(systemctl --global is-enabled wireplumber.service 2>&1)"
v "audio pacman wireplumber:"     "$(pacman -Q wireplumber 2>&1)"
v "gst-libav registered:"         "$(pacman -Q gst-libav 2>&1)"
v "scx polkit action:"            "$([ -f /usr/share/polkit-1/actions/org.scx.Loader.policy ] && echo present || echo MISSING)"
v "sched_ext state:"              "$(cat /sys/kernel/sched_ext/state 2>/dev/null || echo unknown)"
v "iio-sensor-proxy:"             "$(systemctl is-active iio-sensor-proxy.service 2>&1)"
v "auditd:"                       "$(systemctl is-active auditd.service 2>&1)"
v "fail2ban:"                     "$(systemctl is-active fail2ban.service 2>&1)"
v "nftables kickass table:"       "$(nft list tables 2>/dev/null | grep -c kickass) loaded"
v "pacman-init leftover:"         "$([ -f /etc/systemd/system/pacman-init.service ] && echo STILL-PRESENT || echo clear)"
v "timeshift menu entry:"         "$([ -f /usr/share/applications/timeshift-gtk.desktop ] && echo STILL-PRESENT || echo hidden)"
v "pre-update snapshot hook:"     "$([ -f /etc/pacman.d/hooks/00-ncde-snapshot.hook ] && echo installed || echo MISSING)"
v "field kit on node:"            "$(ls /usr/local/share/ncde-fix 2>/dev/null | wc -l) files"
say "=== done $(date '+%F %T') — full log: $LOG ==="
echo
echo "Post-run checks (as your normal user):"
echo "  gst-inspect-1.0 avdec_h264          # FIX 2 — must load, no libjxl error"
echo "  cat /sys/kernel/sched_ext/state     # FIX 3 — 'enabled' after sentinel restart"
echo "  fail2ban-client status sshd         # FIX 5 — jail listed"
echo "  next pacman -Syu: a new BAK-* with tag 'update' appears in /restore  # FIX 8"
