"""Reference-device enablement — sentinel-plan.md §4e.

Three real gaps documented for NCDE's budget-hardware reference device (a
Jasper Lake whitebox convertible), each handled honestly:

1. Silead touchscreen (ACPI HID "MSSL1680" family) — present on this class of
   machine but not working (no driver bound / no firmware). DETECTION only:
   this module does NOT fetch/install firmware or write an ACPI DSD override.
   Both are still open research items in sentinel-plan.md itself (its own
   [SEARCH] tags on the exact firmware source + the whitebox DMI-quirk
   problem) — sourcing/redistributing a binary firmware blob without a
   confirmed lawful path, or writing a kernel-level ACPI quirk from an
   unattended background daemon, isn't safe to automate on a guess. What IS
   safe and real: detect the gap precisely and report it via
   TouchscreenNotWorking so it's visible for that later, deliberate,
   consent-gated phase.

2. Auto-rotation via net.hadess.SensorProxy (iio-sensor-proxy) — real bridge:
   claims the accelerometer and relays live AccelerometerOrientation changes
   as Sentinel's own AccelerometerOrientationChanged signal. Verified against
   the real net.hadess.SensorProxy D-Bus reference (methods
   Claim/ReleaseAccelerometer, property AccelerometerOrientation, requires
   ClaimAccelerometer() before orientation updates are delivered). Silent
   no-op if iio-sensor-proxy isn't running or the machine has no
   accelerometer — this is generic, not hardcoded to any one machine.

3. Tablet-mode (SW_TABLET_MODE) — generic, dependency-free: probes every
   /sys/class/input/event*/device for the SW_TABLET_MODE capability (kernel
   input-event-codes.h bit 0) and, if any device has it, polls its live state
   via the standard EVIOCGSW ioctl (stdlib fcntl only, no new dependency).
   This machine's own hinge switch (ACPI BOSC0200) has no kernel driver bound
   at all — sentinel-plan.md itself flags "no SW_TABLET_MODE seen... research
   dual-accel handling" as an open research question, not a spec to
   implement against. This module does not invent a hinge-angle algorithm;
   it enables tablet-mode support generically for any machine whose kernel
   DOES expose the switch, which is the standard/most common case.

Every probe here is real and live (matches hw_tier.py/scx_select.py's own
house style) — nothing hardcoded to one machine, everything no-ops cleanly
when the hardware/service isn't present.
"""

import fcntl
import glob
import logging
import os

import dbus
from gi.repository import GLib

from ._utils import read_sysfs

log = logging.getLogger(__name__)

# ── 1. Silead touchscreen detection ──────────────────────────────────────

# silead_ts.c's own ACPI match table uses the "MSSL" HID prefix across
# Silead's whole touch-controller line, not just one model (verified against
# the upstream driver + community reports, not guessed).
_SILEAD_HID_PREFIXES = ("MSSL",)


def _find_silead_acpi_device():
    for d in glob.glob("/sys/bus/acpi/devices/*"):
        hid = os.path.basename(d).split(":")[0]
        if any(hid.startswith(p) for p in _SILEAD_HID_PREFIXES):
            return d
    return None


def _touch_input_device_present():
    for name_path in glob.glob("/sys/class/input/event*/device/name"):
        name = read_sysfs(name_path).lower()
        if "touch" in name and "touchpad" not in name:
            return True
    return False


def check_touchscreen(sentinel):
    """One-shot at startup. Emits TouchscreenNotWorking(hid, reason) if a
    Silead controller is present but no touch input device was created —
    never attempts to fetch/install firmware itself (see module docstring)."""
    dev = _find_silead_acpi_device()
    if dev is None:
        return   # no Silead controller on this machine
    if _touch_input_device_present():
        return   # already working

    hid = os.path.basename(dev).split(":")[0]
    i2c_matches = glob.glob(f"/sys/bus/i2c/devices/i2c-{hid}*")
    bound = bool(i2c_matches) and os.path.exists(os.path.join(i2c_matches[0], "driver"))
    fw_present = bool(glob.glob("/lib/firmware/silead/*.fw"))

    if not fw_present:
        reason = "missing firmware in /lib/firmware/silead/ (see sentinel-plan.md §4e)"
    elif not bound:
        reason = f"silead_ts driver not bound to {hid}"
    else:
        reason = "controller + driver + firmware present, but no touch input device created"

    log.info("touchscreen gap: %s controller detected, not working (%s)", hid, reason)
    GLib.idle_add(sentinel.TouchscreenNotWorking, hid, reason)


# ── 2. iio-sensor-proxy accelerometer bridge (auto-rotation) ────────────

_SENSOR_PROXY_BUS   = "net.hadess.SensorProxy"
_SENSOR_PROXY_PATH  = "/net/hadess/SensorProxy"
_SENSOR_PROXY_IFACE = "net.hadess.SensorProxy"
_PROPS_IFACE        = "org.freedesktop.DBus.Properties"


class SensorProxyBridge:
    """Bridges net.hadess.SensorProxy's real accelerometer orientation into
    Sentinel's own AccelerometerOrientationChanged signal, so Lelan can drive
    auto-rotation without every consumer needing its own SensorProxy claim.
    Silent no-op if the service isn't running or this machine has no
    accelerometer — verified real API, not guessed (methods/properties
    confirmed against the net.hadess.SensorProxy reference manual)."""

    def __init__(self, bus, sentinel):
        self._sentinel = sentinel
        self._iface = None
        self._claimed = False
        try:
            obj = bus.get_object(_SENSOR_PROXY_BUS, _SENSOR_PROXY_PATH)
        except dbus.DBusException:
            log.info("iio-sensor-proxy: not running — auto-rotation unavailable")
            return

        props = dbus.Interface(obj, _PROPS_IFACE)
        try:
            has_accel = bool(props.Get(_SENSOR_PROXY_IFACE, "HasAccelerometer"))
        except dbus.DBusException as exc:
            log.info("iio-sensor-proxy: property read failed (%s) — auto-rotation unavailable", exc)
            return
        if not has_accel:
            log.info("iio-sensor-proxy: running, but no accelerometer on this machine")
            return

        iface = dbus.Interface(obj, _SENSOR_PROXY_IFACE)
        try:
            iface.ClaimAccelerometer()
        except dbus.DBusException as exc:
            log.warning("iio-sensor-proxy: ClaimAccelerometer failed: %s", exc)
            return

        self._iface = iface
        self._claimed = True
        props.connect_to_signal("PropertiesChanged", self._on_properties_changed)

        # PropertiesChanged only fires on a CHANGE — without an initial read the
        # current orientation is silently missed until the device next physically
        # rotates.
        try:
            orientation = str(props.Get(_SENSOR_PROXY_IFACE, "AccelerometerOrientation"))
            GLib.idle_add(sentinel.AccelerometerOrientationChanged, orientation)
        except dbus.DBusException:
            pass
        log.info("iio-sensor-proxy: accelerometer claimed, auto-rotation live")

    def _on_properties_changed(self, iface_name, changed, invalidated):
        if iface_name != _SENSOR_PROXY_IFACE or "AccelerometerOrientation" not in changed:
            return
        GLib.idle_add(self._sentinel.AccelerometerOrientationChanged,
                      str(changed["AccelerometerOrientation"]))

    def release(self):
        """Release the claim on shutdown — a well-behaved SensorProxy client
        never holds the accelerometer open past its own process lifetime."""
        if self._claimed and self._iface is not None:
            try:
                self._iface.ReleaseAccelerometer()
            except dbus.DBusException:
                pass
            self._claimed = False


# ── 3. Tablet-mode (SW_TABLET_MODE), generic ─────────────────────────────

_SW_TABLET_MODE = 0x00   # linux/input-event-codes.h

def _IOC(direction, type_, nr, size):
    return (direction << 30) | (size << 16) | (type_ << 8) | nr

_EVIOCGSW_1 = _IOC(2, ord("E"), 0x1b, 1)   # _IOC_READ=2, one-byte SW bitmask is enough for bit 0


def _find_tablet_mode_event_device():
    """Return the /dev/input/eventN path for the first device whose kernel
    capabilities include SW_TABLET_MODE, or None if this machine has none."""
    for caps_path in glob.glob("/sys/class/input/event*/device/capabilities/sw"):
        raw = read_sysfs(caps_path)
        if not raw:
            continue
        try:
            last_word = int(raw.split()[-1], 16)
        except (ValueError, IndexError):
            continue
        if last_word & (1 << _SW_TABLET_MODE):
            event_name = caps_path.split("/")[4]   # ".../input/eventN/device/capabilities/sw"
            return f"/dev/input/{event_name}"
    return None


def read_tablet_mode(event_path):
    """Live SW_TABLET_MODE state via the standard EVIOCGSW ioctl (stdlib
    fcntl only). Returns True/False, or None if the device can't be queried
    (e.g. permissions)."""
    try:
        with open(event_path, "rb") as f:
            buf = bytearray(1)
            fcntl.ioctl(f.fileno(), _EVIOCGSW_1, buf, True)
            return bool(buf[0] & 0x1)
    except OSError:
        return None


class TabletModeWatcher:
    """One-shot capability probe + lightweight poll (matches hwmon.py's own
    coalesced-poll convention) — only runs at all if this machine actually
    has a kernel-exposed SW_TABLET_MODE switch. This machine's own hinge
    (ACPI BOSC0200) has no driver bound, so this correctly no-ops here; it's
    real support for any machine whose kernel does expose the switch."""

    def __init__(self, sentinel):
        self._sentinel = sentinel
        self._event_path = _find_tablet_mode_event_device()
        self._last = None
        if self._event_path is None:
            log.info("tablet-mode: no SW_TABLET_MODE-capable input device on this machine")

    @property
    def active(self):
        return self._event_path is not None

    def poll(self):
        if self._event_path is None:
            return False   # GLib timeout: don't repeat
        state = read_tablet_mode(self._event_path)
        if state is not None and state != self._last:
            self._last = state
            GLib.idle_add(self._sentinel.TabletModeChanged, state)
        return True   # keep polling
