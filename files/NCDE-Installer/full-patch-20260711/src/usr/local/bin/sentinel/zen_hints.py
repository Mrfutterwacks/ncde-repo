"""Zen kernel tuning — cpufreq governor + EPP + vm.dirty_ratio.

ncde-sentinel runs as a root system service (fixed session 46 — see zen.md
§5), so this is a REAL, live writer now, not the harmless EACCES no-op
zen.md originally documented. It is the single source of truth for these
three knobs — governor/EPP picks only a value the running kernel's policy
actually advertises as available (never hardcoded), matching
/usr/local/lib/ncde/ncde-zen-power.sh's proven fallback logic exactly so the
two don't drift apart. Values per zen.md §2/§4: AC -> schedutil/
balance_performance/dirty_ratio=15, battery -> powersave/balance_power/
dirty_ratio=5, each with an availability-aware fallback chain.
"""

import atexit
import glob
import logging

from ._utils import read_sysfs

log = logging.getLogger(__name__)

_GOVERNOR_FALLBACKS = {
    True:  ("powersave", "schedutil", "conservative", "ondemand"),      # battery
    # AC: the governor that SCALES. On intel_pstate (active) the only two are
    # "performance powersave" — there "powersave" IS the dynamic, HWP-driven
    # governor (EPP below sets its bias), and "performance" pins every core at
    # max clock forever. 2026-09-26 the old chain ended on "performance" and did
    # exactly that on every Intel laptop: hot at idle, fighting Zen's design.
    # "performance" is GameMode's alone (gamemode.py), never the AC default.
    False: ("schedutil", "powersave", "ondemand", "conservative"),      # AC
}
_EPP_FALLBACKS = {
    True:  ("balance_power", "power", "default"),                      # battery
    False: ("balance_performance", "performance", "default"),          # AC
}
_DIRTY_RATIO = {True: "5", False: "15"}


def _pick(avail_str, fallbacks):
    avail = (avail_str or "").split()
    for cand in fallbacks:
        if cand in avail:
            return cand
    return None


def _write_if_changed(path, value):
    if read_sysfs(path) == value:
        return
    try:
        with open(path, "w") as f:
            f.write(value)
    except OSError:
        pass


def apply(on_battery):
    """Switch cpufreq governor, EPP hint, and vm.dirty_ratio for the Zen kernel power state."""
    for cpufreq in glob.glob("/sys/devices/system/cpu/cpu*/cpufreq"):
        gov = _pick(read_sysfs(f"{cpufreq}/scaling_available_governors"), _GOVERNOR_FALLBACKS[on_battery])
        if gov:
            _write_if_changed(f"{cpufreq}/scaling_governor", gov)

        epp = _pick(read_sysfs(f"{cpufreq}/energy_performance_available_preferences"), _EPP_FALLBACKS[on_battery])
        if epp:
            _write_if_changed(f"{cpufreq}/energy_performance_preference", epp)

    _write_if_changed("/proc/sys/vm/dirty_ratio", _DIRTY_RATIO[on_battery])


# ── RAPL thermal-cap fallback (2026-07-02) ──────────────────────────────────
# Reference device (low-end Celeron N5095 whitebox laptop) has NO controllable
# fan by any known mechanism — confirmed via sensors-detect (no Super I/O/EC
# hwmon chip found on this board) and the DSDT (no PNP0C0B ACPI fan device,
# no _FIF/_FPS/_FSL/_FST). The EC's own fan logic (\_SB.PC00.LPCB.H_EC, custom
# ECRD/ECWR/CFAN methods) is undocumented and whitebox-specific — deliberately
# not touched (operator's standing order: no EC register work without real
# chipset docs). RAPL package power capping is the safe substitute: it's a
# standard Intel mechanism (virtually every Intel CPU since ~2011), reduces
# heat AT THE SOURCE by capping CPU package power draw, and is Intel-only —
# silently a no-op on AMD/other hardware where intel-rapl doesn't exist, same
# detect-and-skip discipline as every other knob in this module.
_THERMAL_CAP_FRACTION = 0.6   # conservative reduction — only used under real thermal pressure
_capped_zones = set()   # RAPL package zones currently under our reduced cap


def _restore_all_caps():
    """Exit fail-safe (2026-07-04 polish pass) — mirrors pwm_guard.py's own
    atexit restore for the identical reason: a daemon that dies mid-cap must
    never leave the CPU permanently underclocked. atexit-only, deliberately —
    this module does not register its own SIGTERM/SIGINT handler because
    signal.signal only keeps the LAST registered handler per signal — a
    competing registration here would silently replace the real one.
    CLOSED 2026-07-05: __main__.py now installs the one shared shutdown
    handler (registered after PwmGuard, so it owns the signals) calling BOTH
    PwmGuard.release_all() and this module's _restore_all_caps(); atexit
    below stays as the belt for non-signal exits."""
    for z in list(_capped_zones):
        max_uw = read_sysfs(f"{z}/constraint_0_max_power_uw")
        if max_uw:
            _write_if_changed(f"{z}/constraint_0_power_limit_uw", max_uw)
        _capped_zones.discard(z)


atexit.register(_restore_all_caps)


def _rapl_packages():
    """Top-level Intel RAPL package zones on THIS machine (never hardcoded —
    a multi-socket machine has more than one). Excludes core/uncore/dram
    sub-domains — confirmed on the reference device these report no real
    constraint (empty max_power_uw), only the package-level zone is usable."""
    return [z for z in glob.glob("/sys/class/powercap/intel-rapl:*")
            if read_sysfs(f"{z}/name").startswith("package-")]


def apply_thermal_cap(active):
    """Reduce (or restore) CPU package power limit for hardware with no
    controllable fan. Only ever writes a value <= the hardware's own reported
    max — never raises above it, so this cannot push the chip outside its own
    safe envelope. No-op (zero zones found) on non-Intel or Intel hardware
    without RAPL exposed — never assumed present."""
    for z in _rapl_packages():
        max_uw = read_sysfs(f"{z}/constraint_0_max_power_uw")
        if not max_uw:
            continue
        try:
            max_uw = int(max_uw)
        except ValueError:
            continue
        target = str(int(max_uw * _THERMAL_CAP_FRACTION)) if active else str(max_uw)
        _write_if_changed(f"{z}/constraint_0_power_limit_uw", target)
        if active:
            _capped_zones.add(z)
        else:
            _capped_zones.discard(z)
