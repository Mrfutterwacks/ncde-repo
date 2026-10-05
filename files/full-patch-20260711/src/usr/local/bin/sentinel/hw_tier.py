"""Hardware-tier detection — the missing piece of the Amiga-chipset mission.

Everything else Sentinel/Lelan/Zen do is REACTIVE: respond to instantaneous
temp/battery/load. This module is the one thing that asks "what kind of
machine is this at all" — a one-time probe at Sentinel startup (hardware
doesn't change mid-boot), cached, exposed to Lelan so it can set a baseline
decorative-richness floor instead of only ever reacting to live conditions.

Real, live probes only — same discipline as kernel_caps.py. No PCI ID
database lookups (would need a vendored `pci.ids`, out of scope for a v1
heuristic); GPU classification below is deliberately coarse: "is there a
real accelerated DRM driver bound at all," not integrated-vs-discrete.

Per [[feedback_dev_machine_not_install_target]]: thresholds below are
generic heuristics, not tuned to any one machine — this ships on arbitrary
end-user hardware, low-end and high-end alike.
"""

import glob
import logging
import os

log = logging.getLogger(__name__)

# DRM driver names that mean "a real accelerated GPU driver is bound," as
# opposed to no driver at all (bare framebuffer only) or a software-only
# stub. Not exhaustive of every possible driver — the ones actually likely
# to be shipped on NCDE's supported hardware classes.
_ACCEL_DRIVERS = {
    "i915", "xe",                     # Intel
    "amdgpu", "radeon",               # AMD
    "nvidia", "nouveau",              # Nvidia
    "vc4", "v3d",                     # Raspberry Pi class
    "panfrost", "lima",               # ARM Mali
}


def _cpu_cores():
    try:
        n = os.cpu_count()
        return n if n else 1
    except Exception:
        return 1


def _ram_gb():
    try:
        with open("/proc/meminfo") as f:
            for line in f:
                if line.startswith("MemTotal:"):
                    kb = int(line.split()[1])
                    return kb / (1024 * 1024)
    except (OSError, ValueError, IndexError):
        pass
    return 0.0


def _gpu_accelerated():
    """True if at least one /sys/class/drm/card*/device has a real
    accelerated driver bound. Connector subdirs (card1-DP-1 etc.) never
    have a `device` symlink so the glob naturally skips them."""
    for dev_path in glob.glob("/sys/class/drm/card*/device"):
        driver_link = os.path.join(dev_path, "driver")
        try:
            driver = os.path.basename(os.readlink(driver_link))
        except OSError:
            continue
        if driver in _ACCEL_DRIVERS:
            return True
    return False


def detect():
    """Probe real, live hardware-capability signals. Pure heuristic scoring
    (not a benchmark) — cores/RAM/GPU-acceleration are the three signals
    the design pass settled on as cheaply-probeable and broadly meaningful
    across NCDE's target hardware range (old/low-end through new/high-end)."""
    cores = _cpu_cores()
    ram_gb = _ram_gb()
    gpu_accel = _gpu_accelerated()

    score = 0
    score += 0 if cores <= 2 else 1 if cores <= 4 else 2 if cores <= 8 else 3
    score += 0 if ram_gb < 4 else 1 if ram_gb < 8 else 2 if ram_gb < 16 else 3
    score += 1 if gpu_accel else 0

    tier = "low" if score <= 2 else "mid" if score <= 5 else "high"

    return {
        "tier": tier,
        "score": score,
        "cores": cores,
        "ram_gb": round(ram_gb, 1),
        "gpu_accelerated": gpu_accel,
    }


def check_and_log():
    """Probe once and log the result — hardware doesn't change mid-boot,
    so unlike kernel_caps.py there's no 'changed since last boot' check,
    just a straight one-shot probe logged for visibility."""
    caps = detect()
    log.info(
        "hardware tier=%s (score=%d) cores=%d ram_gb=%.1f gpu_accelerated=%s",
        caps["tier"], caps["score"], caps["cores"], caps["ram_gb"], caps["gpu_accelerated"],
    )
    return caps
