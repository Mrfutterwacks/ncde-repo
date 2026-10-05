"""pressure — the facts Lelan's governor decides on: CPU temperature and CPU saturation.

Chain of command (sentinel-plan.md §0, operator 2026-09-30: "Lelan listens to Sentinel and
drives Zen"): Sentinel SENSES, Lelan DECIDES, Sentinel/Zen ACT. Until 2026-09-30 Lelan (LaPivot)
read /sys/class/thermal and every core's cpufreq itself once a second — sensing in two places.
Now Sentinel reads them on its one coalesced poll and reports them; Lelan only decides.

  PressureSensed(max_c: d, cpu_saturated: b)  — emitted when either fact changes (whole °C)
  GetThermalTrip() -> d                        — the machine's own "too hot" point in °C
                                                 (-1 if it exposes none); Lelan derives its
                                                 hot/clear thresholds from it

MUST WORK ON EVERY MACHINE, not one (operator, 2026-09-30). Measured on the operator's
intel_pstate/HWP laptop: the oracle's "every core >= 95% of max frequency" test was TRUE at idle
(2.8 of 2.9 GHz), so Lelan held animations at Reduced permanently. Modern Intel HWP and AMD
amd-pstate both park clocks near max at light load, so frequency is not load. Sources used here
mean the same thing on any hardware:
  * saturation: real busy time from /proc/stat (every kernel, every CPU, VMs, ARM), >= 90%
    across all cores, sustained for 2 polls (~6 s) — zen.md "all cores pegged => pressure
    (debounced)".
  * temperature: ACPI thermal zones when present; otherwise the CPU's own hwmon chip
    (coretemp, k10temp, zenpower, cpu_thermal, ...), for machines/VMs without thermal zones.
  * trip point: lowest thermal-zone "critical"/"hot" trip; otherwise the CPU chip's own
    temp*_crit / temp*_max; otherwise -1 (Lelan falls back to 89/84 °C).
"""

import glob
import os

THERMAL = "/sys/class/thermal"
HWMON = "/sys/class/hwmon"
PROC_STAT = "/proc/stat"

CPU_HWMON_CHIPS = ("coretemp", "k10temp", "zenpower", "cpu_thermal", "soc_thermal",
                   "cpu-thermal", "k8temp", "via_cputemp", "atk0110", "thinkpad", "acpitz")
SATURATED_PCT = 90.0
SATURATED_POLLS = 2


def _read(path):
    try:
        with open(path) as f:
            return f.read().strip()
    except OSError:
        return ""


def _int(s, default=None):
    try:
        return int(s)
    except (TypeError, ValueError):
        return default


# ---- temperature --------------------------------------------------------------------------------

def _zone_temps():
    out = []
    for zone in glob.glob(os.path.join(THERMAL, "thermal_zone*")):
        v = _int(_read(os.path.join(zone, "temp")))
        if v is not None and v > 0:
            out.append(v // 1000)
    return out


def _cpu_hwmon_dirs():
    for d in glob.glob(os.path.join(HWMON, "hwmon*")):
        if _read(os.path.join(d, "name")) in CPU_HWMON_CHIPS:
            yield d


def _hwmon_temps():
    out = []
    for d in _cpu_hwmon_dirs():
        for f in glob.glob(os.path.join(d, "temp*_input")):
            v = _int(_read(f))
            if v is not None and v > 0:
                out.append(v // 1000)
    return out


def max_temp_c():
    """Hottest CPU-relevant temperature in whole °C; 0 if the machine exposes none."""
    temps = _zone_temps() or _hwmon_temps()
    return max(temps) if temps else 0


def lowest_trip_c():
    """The machine's own 'too hot' point in °C, -1.0 if it has none."""
    lowest = -1.0
    for zone in glob.glob(os.path.join(THERMAL, "thermal_zone*")):
        for tfile in glob.glob(os.path.join(zone, "trip_point_*_type")):
            if _read(tfile) not in ("critical", "hot"):
                continue
            v = _int(_read(tfile[: -len("_type")] + "_temp"))
            if v and v > 0 and (lowest < 0 or v / 1000.0 < lowest):
                lowest = v / 1000.0
    if lowest > 0:
        return lowest
    for d in _cpu_hwmon_dirs():
        for pat in ("temp*_crit", "temp*_max"):
            for f in glob.glob(os.path.join(d, pat)):
                v = _int(_read(f))
                if v and v > 0 and (lowest < 0 or v / 1000.0 < lowest):
                    lowest = v / 1000.0
        if lowest > 0:
            break
    return lowest


# ---- CPU saturation -----------------------------------------------------------------------------

def read_cpu_times(text=None):
    """(busy, total) jiffies summed over all CPUs, from the aggregate 'cpu' line of /proc/stat.
    busy excludes idle and iowait (waiting on disk is not CPU pressure)."""
    if text is None:
        text = _read(PROC_STAT)
    for line in text.splitlines():
        if line.startswith("cpu "):
            v = [int(x) for x in line.split()[1:]]
            v += [0] * (8 - len(v))
            user, nice, system, idle, iowait, irq, softirq, steal = v[:8]
            total = user + nice + system + idle + iowait + irq + softirq + steal
            return total - idle - iowait, total
    return 0, 0


class Saturation:
    """Busy % between consecutive polls; saturated after SATURATED_POLLS polls in a row >= 90%."""

    def __init__(self):
        self._last = None
        self._streak = 0
        self.saturated = False

    def update(self, busy, total):
        if self._last is not None:
            db, dt = busy - self._last[0], total - self._last[1]
            pct = 100.0 * db / dt if dt > 0 else 0.0
            self._streak = self._streak + 1 if pct >= SATURATED_PCT else 0
            self.saturated = self._streak >= SATURATED_POLLS
        self._last = (busy, total)
        return self.saturated


# ---- poll hook ----------------------------------------------------------------------------------

def poll(sentinel, state):
    """Called from hwmon.poll_sensors on the shared 3 s timer. Emits only on change."""
    sat = state.setdefault("saturation", Saturation())
    facts = (max_temp_c(), sat.update(*read_cpu_times()))
    if facts != state.get("pressure"):
        state["pressure"] = facts
        from gi.repository import GLib
        GLib.idle_add(sentinel.PressureSensed, float(facts[0]), facts[1])
