"""Kernel-capability detection — re-probed whenever the kernel changes.

Not a periodic maintenance job: a kernel update only takes effect after a
reboot, and Sentinel already restarts every boot, so "re-probe at startup,
log only when something actually changed" is the entire mechanism. Zero user
action, zero scheduled job (operator, 2026-07-01: "users should never have to
perform maintenance of any kind on NCDE").

Real, live probes only — never assumed — same discipline as
ncde-zen-power.sh's scaling_available_governors check.
"""

import glob
import logging
import os
import platform

log = logging.getLogger(__name__)

STATE_DIR = os.environ.get("STATE_DIRECTORY", "/var/lib/ncde-sentinel")
CACHE_FILE = os.path.join(STATE_DIR, "last-kernel")


def _read_first(pattern):
    for p in sorted(glob.glob(pattern)):
        try:
            with open(p) as f:
                return f.read().strip()
        except OSError:
            continue
    return ""


def _has_cgroup_freeze():
    """cgroup.freeze only ever appears on a NON-root cgroup (root never has
    it) — checking the root path always reads False regardless of real
    support. The correct live check is this process's own cgroup, which is
    guaranteed non-root under systemd (every service gets its own)."""
    try:
        with open("/proc/self/cgroup") as f:
            # cgroup v2 unified hierarchy: "0::/path"
            path = f.read().strip().split(":")[-1]
    except (OSError, IndexError):
        return False
    return os.path.exists("/sys/fs/cgroup" + path + "/cgroup.freeze")


def detect():
    """Probe real, live capabilities of the running kernel/hardware."""
    governors = _read_first("/sys/devices/system/cpu/cpu*/cpufreq/scaling_available_governors")
    epp = _read_first("/sys/devices/system/cpu/cpu*/cpufreq/energy_performance_available_preferences")
    available_cong = _read_first("/proc/sys/net/ipv4/tcp_available_congestion_control")
    controllers = _read_first("/sys/fs/cgroup/cgroup.controllers")
    return {
        "kernel": platform.release(),
        "governors": governors,
        "epp": epp,
        "bbr_available": "bbr" in available_cong.split(),
        "cgroup_controllers": controllers,
        "cgroup_freezer": _has_cgroup_freeze(),
    }


def check_and_log():
    """Re-probe and log only when the kernel actually changed since last
    boot. Best-effort cache write — a missed write just means we log again
    next boot, never a hard failure."""
    caps = detect()
    last = ""
    try:
        with open(CACHE_FILE) as f:
            last = f.read().strip()
    except OSError:
        pass

    if caps["kernel"] != last:
        log.info(
            "kernel %s -> %s — capabilities: governors=[%s] epp=[%s] bbr_available=%s "
            "cgroup_controllers=[%s] cgroup_freezer=%s",
            last or "(first boot)", caps["kernel"], caps["governors"], caps["epp"],
            caps["bbr_available"], caps["cgroup_controllers"], caps["cgroup_freezer"],
        )
        try:
            os.makedirs(STATE_DIR, exist_ok=True)
            with open(CACHE_FILE, "w") as f:
                f.write(caps["kernel"])
        except OSError:
            pass

    return caps
