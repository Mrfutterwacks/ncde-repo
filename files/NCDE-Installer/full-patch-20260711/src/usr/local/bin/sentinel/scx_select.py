"""sched_ext scheduler selection — config-driven, per-machine, never hardcoded.

Operator's explicit correction (2026-07-03): the Amiga-chipset mission ships on
arbitrary end-user hardware, not just this dev laptop — a scheduler choice
picked for one machine's CPU topology must not become every machine's default.
Real, live probes only (same discipline as hw_tier.py/kernel_caps.py): does
this kernel even support sched_ext, does this CPU have hybrid P/E cores (a
real signal, not guessed — /sys/devices/system/cpu/types only appears on true
hybrid parts), and which scx schedulers are actually installed. If any check
comes back negative, this silently no-ops and the machine keeps running the
stock kernel scheduler — never an error, never a hard requirement.

Chosen defaults (adopting existing, already-production prior art rather than
NCDE writing its own eBPF scheduler — see project-ncde-harmony-amiga-mission):
  - hybrid P/E-core CPU  -> scx_lavd (its per-core-type domain partitioning is
    real value on hybrid hardware; that's exactly what it's for)
  - uniform-core CPU     -> scx_bpfland (scx_lavd's extra domain machinery is
    dead weight on a single-core-type CPU; scx_bpfland's simpler design is a
    real, live-verified lower-risk pick — see the memory-leak issue tracked
    upstream at sched-ext/scx#3340 for scx_lavd's performance mode. Re-checked
    2026-07-04: still open/unfixed upstream (reported against CachyOS 6.19.2,
    ~34GB leak + pegged CPU specifically under scx_lavd's "--performance"
    mode) — this module writes default_mode="Auto" below, not "performance",
    so exposure looks reduced, but that hasn't been independently confirmed
    against scx_loader's own mode semantics; treat scx_lavd as still a live
    risk to watch, not a cleared one)
Either choice only applies if that binary is actually present; the other is
tried as a fallback; if neither is installed, this is a no-op.
"""

import glob
import logging
import os
import shutil
import subprocess

log = logging.getLogger(__name__)

CONFIG_PATH = "/etc/scx_loader/config.toml"
NCDE_MARKER = "# NCDE-managed (scx_select.py) — hand-edit removes this marker, and this file is then left alone\n"


def sched_ext_supported():
    return os.path.isdir("/sys/kernel/sched_ext")


def hybrid_cpu():
    """True only on real hybrid P/E-core parts — /sys/devices/system/cpu/types
    is a kernel-standard interface that only exists at all on hybrid hardware
    (confirmed absent on this dev host's uniform-core Celeron N5095)."""
    return len(glob.glob("/sys/devices/system/cpu/types/*")) > 1


def _scx_binary_installed(name):
    return shutil.which(name) is not None


def select_scheduler():
    """Return the scx binary name to use, or None if nothing should be
    changed (unsupported kernel, or no scx scheduler actually installed)."""
    if not sched_ext_supported():
        return None
    preferred = "scx_lavd" if hybrid_cpu() else "scx_bpfland"
    fallback = "scx_bpfland" if preferred == "scx_lavd" else "scx_lavd"
    if _scx_binary_installed(preferred):
        return preferred
    if _scx_binary_installed(fallback):
        return fallback
    return None


def _file_is_ncde_managed_or_absent():
    if not os.path.exists(CONFIG_PATH):
        return True
    try:
        with open(CONFIG_PATH) as f:
            return f.readline() == NCDE_MARKER
    except OSError:
        return False


def _write_config(sched_name):
    os.makedirs(os.path.dirname(CONFIG_PATH), exist_ok=True)
    with open(CONFIG_PATH, "w") as f:
        f.write(NCDE_MARKER)
        f.write(f'default_sched = "{sched_name}"\n')
        f.write('default_mode = "Auto"\n')


def _scx_loader_service_present():
    return bool(glob.glob("/usr/lib/systemd/system/scx_loader.service")
                or glob.glob("/etc/systemd/system/scx_loader.service"))


def apply():
    """One-shot, idempotent — call at Sentinel startup. Never touches a
    config file the operator hand-edited (marker check); never errors if scx
    isn't installed; never restarts a service that isn't there."""
    sched = select_scheduler()
    if sched is None:
        log.info("sched_ext: no supported scheduler available (unsupported kernel or scx not installed) — leaving stock scheduler")
        return
    if not _file_is_ncde_managed_or_absent():
        log.info("sched_ext: %s config exists and was hand-edited — leaving it alone", CONFIG_PATH)
        return
    _write_config(sched)
    log.info("sched_ext: selected %s (hybrid_cpu=%s), wrote %s", sched, hybrid_cpu(), CONFIG_PATH)
    if _scx_loader_service_present():
        try:
            subprocess.run(["systemctl", "restart", "scx_loader"], capture_output=True, text=True, timeout=10)
        except (OSError, subprocess.TimeoutExpired):
            log.warning("sched_ext: scx_loader restart failed", exc_info=True)
