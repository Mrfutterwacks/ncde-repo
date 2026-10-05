"""hwmon sensing — auto-discovers every chip on THIS machine.

Keyed by chip name file (hwmon numbers shuffle across reboots).
"""

import os
import glob
import logging

from gi.repository import GLib

from ._utils import read_sysfs, read_int

log = logging.getLogger(__name__)

# ── Sensing tunables ──────────────────────────────────────────────────────
POLL_SECONDS = 3       # coalesced sensor poll interval (light; one timer)
TEMP_EPSILON = 0.5     # only re-emit ThermalChanged on a >= 0.5 C move
CRIT_HYST    = 3.0     # re-arm a critical sensor once it drops 3 C below crit


class HwmonSensors:
    """Auto-discovers every hwmon chip on THIS machine — no hardcoded chip
    names (hwmon numbers shuffle across reboots, so we key everything by the
    chip's `name` file). Reads temps/fans on demand; the daemon polls us."""

    def __init__(self):
        self.temps = []   # list of {label, input, crit}
        self.fans  = []   # list of {label, input}
        self._discover()

    def _discover(self):
        for chip in sorted(glob.glob("/sys/class/hwmon/hwmon*")):
            name = read_sysfs(os.path.join(chip, "name")) or os.path.basename(chip)

            for inp in sorted(glob.glob(os.path.join(chip, "temp*_input"))):
                base = inp[: -len("_input")]                 # .../tempN
                idx  = os.path.basename(base)               # tempN
                label = read_sysfs(base + "_label") or idx
                self.temps.append({
                    "label": f"{name}: {label}",
                    "input": inp,
                    "crit":  base + "_crit",                 # may not exist; read guarded
                })

            for inp in sorted(glob.glob(os.path.join(chip, "fan*_input"))):
                base = inp[: -len("_input")]                 # .../fanN
                idx  = os.path.basename(base)               # fanN
                label = read_sysfs(base + "_label") or idx
                self.fans.append({
                    "label": f"{name}: {label}",
                    "input": inp,
                })

        log.info("hwmon: %d temp sensor(s), %d fan(s) discovered",
                 len(self.temps), len(self.fans))

    def read_temps(self):
        """label -> degrees C (float, 1 dp). Skips sensors that read nothing."""
        out = {}
        for t in self.temps:
            mc = read_int(t["input"])
            if mc is None:
                continue
            out[t["label"]] = round(mc / 1000.0, 1)
        return out

    def read_fans(self):
        """label -> RPM (int). Skips fans that read nothing."""
        out = {}
        for f in self.fans:
            rpm = read_int(f["input"])
            if rpm is None:
                continue
            out[f["label"]] = rpm
        return out

    def crit_for(self, label):
        """degrees C critical threshold for a temp label, or None."""
        for t in self.temps:
            if t["label"] == label:
                mc = read_int(t["crit"])
                return round(mc / 1000.0, 1) if mc is not None else None
        return None


def _temps_differ(a, b):
    """True if the temp dicts differ in keys or any value moved >= EPSILON."""
    if a.keys() != b.keys():
        return True
    return any(abs(a[k] - b.get(k, -1e9)) >= TEMP_EPSILON for k in a)


def poll_sensors(sentinel, sensors, state, pwm_guard=None):
    """One coalesced poll: read all sensors, emit only on real change.
    Returns True so GLib keeps the timer running.

    pwm_guard (optional, see pwm_guard.py): the §1.C thermal-guardian
    backstop. Engaged the instant any sensor crosses critical; released once
    EVERY sensor has cooled back below its hysteresis band (was_critical
    guards this so release is only called on the real transition, not every
    poll — release_all() is itself idempotent/safe regardless)."""
    try:
        temps = sensors.read_temps()
        if temps and _temps_differ(temps, state["temps"]):
            state["temps"] = temps
            GLib.idle_add(sentinel.ThermalChanged, temps)

        fans = sensors.read_fans()
        if fans and fans != state["fans"]:
            state["fans"] = fans
            GLib.idle_add(sentinel.FanChanged, fans)

        was_critical = bool(state["critical"])
        for label, c in list(temps.items()):
            crit = sensors.crit_for(label)
            if crit is None:
                continue
            if c >= crit and label not in state["critical"]:
                state["critical"].add(label)
                GLib.idle_add(sentinel.ThermalCritical, label, c)
                log.warning("CRITICAL %s = %.1f C (crit %.1f)", label, c, crit)
                if pwm_guard is not None:
                    pwm_guard.engage()
            elif label in state["critical"] and c <= crit - CRIT_HYST:
                state["critical"].discard(label)   # cooled — re-arm

        if pwm_guard is not None and was_critical and not state["critical"]:
            pwm_guard.release_all()   # every sensor cooled below crit-hysteresis — hand back to automatic

        # Lelan's governor facts (hottest thermal zone, CPU saturation) — same timer, emit on change.
        from . import pressure
        pressure.poll(sentinel, state)
    except Exception as exc:
        log.warning("sensor poll error: %s", exc)
    return True


def battery_state():
    """Returns (on_battery: bool, pct: int).

    on_battery is derived from the Mains/AC supply's `online` flag, NOT the
    battery's own `status` string — "Not charging" is a normal state at 100%
    while plugged in and must never be read as "on battery" (confirmed live
    2026-07-02: AC connected, BAT0 100% "Not charging", yet the old string
    check here reported on_battery=True, corrupting governor/dirty_ratio/EPP
    and Lelan's own BatteryStateChanged reading). Matches
    ncde-zen-power.sh's detect_on_ac(): a Mains node reporting online=0 means
    on battery; no Mains node at all means a desktop (always AC).
    Battery percentage still comes from the Battery device itself.
    """
    found_mains = False
    mains_online = False
    capacity = 100
    for ps_type in glob.glob("/sys/class/power_supply/*/type"):
        base = os.path.dirname(ps_type)
        kind = read_sysfs(ps_type)
        if kind == "Mains":
            found_mains = True
            if read_sysfs(f"{base}/online") == "1":
                mains_online = True
        elif kind == "Battery":
            capacity = int(read_sysfs(f"{base}/capacity") or "0")
    if found_mains:
        return (not mains_online), capacity
    return False, capacity
