#!/usr/bin/env bash
# ncde-zen-power.sh — NCDE "Zen" performance-governor ACTUATOR (root helper)
#
# Target install path : /usr/local/lib/ncde/ncde-zen-power.sh   (root:root 0755)
# Invoked by          : /etc/udev/rules.d/90-ncde-zen.rules  (power_supply change)
#                       ncde-zen-power.service                (once at boot)
#
# WHY THIS EXISTS
#   zen.md §2/§5: ncde-sentinel._apply_zen_hints is the SOLE writer of the cpufreq
#   scaling_governor and /proc/sys/vm/dirty_ratio, but ncde-sentinel runs as a
#   USER systemd service with no privilege, so those sysfs/proc writes EACCES and
#   silently fail (best-effort try/except). This helper performs the SAME writes
#   from a root context (udev RUN runs as root; the boot unit is a system unit),
#   so the governor switch actually takes.
#
# VALUES — must match zen.md §2 EXACTLY:
#   scaling_governor : schedutil (AC)  ·  powersave (battery)
#   vm.dirty_ratio   : 15 (AC)         ·  5 (battery)
#
# Idempotent. Exits 0 even when paths are missing (desktop w/o battery, no
# cpufreq, locked-down /proc). Never fails the udev event or the boot.

set -u

PS_GLOB=/sys/class/power_supply
CPU_GLOB='/sys/devices/system/cpu/cpu*/cpufreq'
DIRTY_RATIO=/proc/sys/vm/dirty_ratio

# ---- 1. Detect AC vs battery -------------------------------------------------
# on_ac=1 unless we positively find a Mains/AC supply that reports online=0.
# Rationale (matches ncde-sentinel._battery_state): a machine with no Mains
# adapter node is a desktop — always powered — so it gets the AC profile.
detect_on_ac() {
    local f type online found_mains=0 any_online=0

    # Preferred: explicit AC* adapter nodes (AC, AC0, ACAD, ADP1 commonly typed Mains).
    for f in "$PS_GLOB"/*/type; do
        [ -r "$f" ] || continue
        type=$(cat "$f" 2>/dev/null) || continue
        [ "$type" = "Mains" ] || continue
        found_mains=1
        online=$(cat "${f%/type}/online" 2>/dev/null) || online=""
        [ "$online" = "1" ] && any_online=1
    done

    if [ "$found_mains" -eq 1 ]; then
        # At least one mains adapter present: on AC iff one reports online.
        [ "$any_online" -eq 1 ] && return 0 || return 1
    fi

    # No Mains node at all -> desktop / always-powered -> AC profile.
    return 0
}

# ---- 2. Pick a governor honoring scaling_available_governors ------------------
# Writes only a governor the policy actually supports; falls back gracefully.
# Preference order keeps intent: AC favors responsiveness, battery favors thrift.
apply_governor() {
    local want="$1" cpufreq gov_path avail_path avail chosen cand
    local fallbacks

    if [ "$want" = "schedutil" ]; then
        # intel_pstate (active) offers only "performance powersave": "powersave"
        # is its dynamic HWP governor, "performance" pins max clock. Never the
        # AC default (2026-09-26: it kept every Intel laptop hot at idle) —
        # only GameMode (sentinel/gamemode.py) pins performance, per game.
        fallbacks="schedutil powersave ondemand conservative"     # AC
    else
        fallbacks="powersave schedutil conservative ondemand"     # battery
    fi

    for cpufreq in $CPU_GLOB; do
        gov_path="$cpufreq/scaling_governor"
        avail_path="$cpufreq/scaling_available_governors"
        [ -w "$gov_path" ] || continue
        [ -r "$avail_path" ] || continue
        avail=" $(cat "$avail_path" 2>/dev/null) "

        chosen=""
        for cand in $fallbacks; do
            case "$avail" in
                *" $cand "*) chosen="$cand"; break ;;
            esac
        done
        [ -n "$chosen" ] || continue   # nothing usable (e.g. amd-pstate passive) -> skip

        # Idempotent: only write if it differs from the current setting.
        if [ "$(cat "$gov_path" 2>/dev/null)" != "$chosen" ]; then
            echo "$chosen" > "$gov_path" 2>/dev/null || true
        fi
    done
}

# ---- 2b. Pick an EPP hint honoring energy_performance_available_preferences ---
# The real lever on intel_pstate-active-mode hardware (confirmed live 2026-07-01
# on a genuinely low-end test machine, Intel Celeron N5095: with intel_pstate in
# active mode, scaling_available_governors is ONLY "performance powersave" —
# schedutil/ondemand/conservative don't exist there, so apply_governor's AC
# fallback silently lands on "performance" and the governor knob barely does
# anything on this whole hardware class. energy_performance_preference is what
# actually varies AC-vs-battery behavior there — previously untouched by
# anything in NCDE. No-op (both paths absent) on hardware without EPP support
# (e.g. amd_pstate passive, or a driver too old to expose it) — never assumed.
apply_epp() {
    local want="$1" cpufreq epp_path avail_path avail chosen cand
    local fallbacks

    if [ "$want" = "performance" ]; then
        fallbacks="balance_performance performance default"   # AC
    else
        fallbacks="balance_power power default"               # battery
    fi

    for cpufreq in $CPU_GLOB; do
        epp_path="$cpufreq/energy_performance_preference"
        avail_path="$cpufreq/energy_performance_available_preferences"
        [ -w "$epp_path" ] || continue
        [ -r "$avail_path" ] || continue
        avail=" $(cat "$avail_path" 2>/dev/null) "

        chosen=""
        for cand in $fallbacks; do
            case "$avail" in
                *" $cand "*) chosen="$cand"; break ;;
            esac
        done
        [ -n "$chosen" ] || continue

        if [ "$(cat "$epp_path" 2>/dev/null)" != "$chosen" ]; then
            echo "$chosen" > "$epp_path" 2>/dev/null || true
        fi
    done
}

# ---- 3. dirty_ratio ----------------------------------------------------------
apply_dirty_ratio() {
    local want="$1"
    [ -w "$DIRTY_RATIO" ] || return 0
    if [ "$(cat "$DIRTY_RATIO" 2>/dev/null)" != "$want" ]; then
        echo "$want" > "$DIRTY_RATIO" 2>/dev/null || true
    fi
}

# ---- main --------------------------------------------------------------------
if detect_on_ac; then
    apply_governor schedutil
    apply_epp performance
    apply_dirty_ratio 15
else
    apply_governor powersave
    apply_epp power
    apply_dirty_ratio 5
fi

exit 0
