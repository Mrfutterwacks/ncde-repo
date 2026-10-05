"""Driver detection — enumerate driverless PCI/USB devices.

A device with a `modalias` but NO `driver` symlink is "driverless". But many
devices are SUPPOSED to have no driver — on the dev machine the host bridge,
shared SRAM and the eSPI/ISA bridge sit driverless and are perfectly fine. So
we suppress infrastructure classes and only surface user-actionable gaps.
"""

import os
import glob
import subprocess
import logging

from gi.repository import GLib

from ._utils import read_sysfs

log = logging.getLogger(__name__)

_BENIGN_PCI_CLASS     = {0x05, 0x06}                    # memory controllers, bridges
_FUNCTIONAL_PCI_CLASS = {0x01, 0x02, 0x03, 0x04, 0x0d}  # storage/net/display/multimedia/wireless


def _pci_class_hi(devdir):
    c = read_sysfs(os.path.join(devdir, "class"))      # e.g. "0x060000"
    try:
        return int(c, 16) >> 16
    except ValueError:
        return -1


def _resolve_module(modalias):
    """The kernel module that SHOULD bind this modalias, or '' if none in-kernel."""
    try:
        r = subprocess.run(["modprobe", "--resolve-alias", modalias],
                           capture_output=True, text=True, timeout=5)
        lines = [l for l in r.stdout.splitlines() if l.strip()]
        return lines[0].strip() if lines else ""
    except Exception:
        return ""


def scan():
    """Returns [{device, modalias, suggested}] for driverless hardware worth
    surfacing. Infrastructure classes (bridges/RAM) are always suppressed; a
    no-module device is only surfaced if it is a user-facing class."""
    found = []
    for bus in ("pci", "usb"):
        for d in sorted(glob.glob(f"/sys/bus/{bus}/devices/*")):
            if os.path.exists(os.path.join(d, "driver")):
                continue
            ma = read_sysfs(os.path.join(d, "modalias"))
            if not ma:
                continue
            hi = _pci_class_hi(d) if bus == "pci" else -1
            if bus == "pci" and hi in _BENIGN_PCI_CLASS:
                continue
            suggested = _resolve_module(ma)
            if not suggested and bus == "pci" and hi not in _FUNCTIONAL_PCI_CLASS:
                continue   # no module + not user-facing (e.g. GNA accelerator) -> skip
            found.append({"device": os.path.basename(d), "modalias": ma, "suggested": suggested})
    return found


def scan_once(sentinel, state):
    """One driver-detection pass; emits DriverMissing for each NEW gap. Read-only
    — Phase 2 DETECTS only; auto-load/install is a later, consent-gated phase."""
    try:
        for f in scan():
            key = f["device"]
            if key in state["drivers"]:
                continue
            state["drivers"].add(key)
            GLib.idle_add(sentinel.DriverMissing, f["device"], f["modalias"], f["suggested"])
            log.info("driver gap: %s (%s) -> %s",
                     f["device"], f["modalias"], f["suggested"] or "<no in-kernel module>")
    except Exception as exc:
        log.warning("driver scan error: %s", exc)
    return False   # GLib.idle_add one-shot
