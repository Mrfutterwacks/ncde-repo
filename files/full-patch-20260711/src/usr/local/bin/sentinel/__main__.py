"""ncde-sentinel — D-Bus service entry point.

D-Bus service:  io.ncde.Sentinel
Object path:    /io/ncde/Sentinel
Interface:      io.ncde.Sentinel

Hotplug signals:
  AudioDeviceChanged(action: s, name: s)
  DisplayConnected(connector: s)
  DisplayDisconnected(connector: s)
  BatteryStateChanged(on_battery: b, pct: i)
  NetworkStateChanged(iface: s, up: b)
  UsbDeviceAdded(vendor: s, product: s)
  UsbDeviceRemoved(vendor: s, product: s)
  InputDeviceAdded(name: s)
  InputDeviceRemoved(name: s)

Sensing signals (Phase 1):
  ThermalChanged(a{sd})
  FanChanged(a{su})
  ThermalCritical(sensor: s, tempC: d)
  PressureSensed(max_zone_c: d, cpu_saturated: b)   (pressure.py — Lelan's governor facts)
  DriverMissing(device: s, modalias: s, suggested_module: s)

Methods (Phase 2 — Lelan is the controller, Sentinel only acts on request):
  SetProcessTier(pid: u, tier: s) -> b
    tier: "foreground" | "background" | "hidden". Moves pid into a per-window
    cgroup v2 scope sized for that tier. Returns True on success.
  ClearProcessTier(pid: u)
    Tell Sentinel to stop tracking pid as tiered (window/process gone). Without
    this, ProcessTiers' "already tiered" cache goes stale once the pid's scope
    is garbage-collected (or the pid gets reused) and the next SetProcessTier
    call for it fails with NoSuchUnit/UnixProcessIdUnknown — confirmed live via
    journalctl 2026-07-02. Lelan calls this from its window-close path.
  GetHardwareTier() -> s
    "low" | "mid" | "high" — a one-shot heuristic (CPU cores, RAM, GPU
    acceleration) computed once at Sentinel startup and cached, since real
    hardware doesn't change mid-boot. Lelan calls this once at its own
    startup to set AnimPolicy's baseline decorative-richness floor — the
    "does NCDE actually adapt to the host's real hardware tier" half of the
    Amiga-chipset mission that was, until now, completely unimplemented
    (everything else is reactive-only: instantaneous temp/battery/load).

Reference-device enablement (sentinel-plan.md §4e):
  TouchscreenNotWorking(hid: s, reason: s)
    A Silead touchscreen controller (ACPI HID "MSSL*") is present but not
    producing a touch input device (missing driver bind and/or firmware).
    Detection only — Sentinel does not fetch/install firmware itself, see
    reference_devices.py's module docstring for why.
  AccelerometerOrientationChanged(orientation: s)
    Relayed from net.hadess.SensorProxy (iio-sensor-proxy), when running and
    an accelerometer is present. Silent no-op otherwise.
  TabletModeChanged(active: b)
    Relayed from a real SW_TABLET_MODE-capable input device, when this
    machine's kernel exposes one. Silent no-op otherwise.
"""

import os
import signal
import sys
import threading
import logging

import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib

from .hwmon import HwmonSensors, poll_sensors, battery_state
from .hwmon import POLL_SECONDS
from .drivers import scan_once
from .zen_hints import apply as apply_zen
from .zen_hints import apply_thermal_cap
from .zen_hints import _restore_all_caps as restore_zen_caps
from .udev_monitor import udev_thread
from .process_tier import ProcessTiers
from .gamemode import GameMode
from .kernel_caps import check_and_log as check_kernel_caps
from .hw_tier import check_and_log as check_hw_tier
from . import scx_select
from .pwm_guard import PwmGuard
from .pressure import lowest_trip_c
from .system_info import collect as collect_system_info
from . import rt_guard
from .reference_devices import check_touchscreen, SensorProxyBridge, TabletModeWatcher
from ._utils import sd_notify

logging.basicConfig(
    format="ncde-sentinel: %(levelname)s %(message)s",
    stream=sys.stderr,
    level=logging.INFO,
)
log = logging.getLogger(__name__)

BUS_NAME = "io.ncde.Sentinel"
OBJ_PATH = "/io/ncde/Sentinel"
IFACE    = "io.ncde.Sentinel"


class Sentinel(dbus.service.Object):

    def __init__(self, bus, path):
        dbus.service.Object.__init__(self, bus, path)
        # NCDE GameMode (2026-07-12): system-wide game optimization. restore_power
        # re-applies the normal governor/EPP for the current AC/battery state when
        # the last game exits; GameModeChanged lets the session react too. The
        # per-window tier manager feeds it detected game PIDs.
        self._gamemode = GameMode(
            restore_power=lambda: apply_zen(battery_state()[0]),
            emit_changed=self.GameModeChanged,
        )
        self._tiers = ProcessTiers(bus, gamemode=self._gamemode)
        # Hardware doesn't change mid-boot — probe once, cache, serve from memory.
        self._hw_tier = check_hw_tier()["tier"]

    # ── hotplug ──
    @dbus.service.signal(IFACE, signature="ss")
    def AudioDeviceChanged(self, action, name): pass

    @dbus.service.signal(IFACE, signature="s")
    def DisplayConnected(self, connector): pass

    @dbus.service.signal(IFACE, signature="s")
    def DisplayDisconnected(self, connector): pass

    @dbus.service.signal(IFACE, signature="bi")
    def BatteryStateChanged(self, on_battery, pct): pass

    def report_battery(self, on_battery, pct):
        """Emit BatteryStateChanged only when the state actually changed. This laptop's
        battery controller sends a power_supply uevent every few seconds with nothing new;
        each one used to reach Lelan -> batteryChanged -> Settings::applyPowerSettings ->
        2-3 `xset` spawns (~60/min, measured 2026-09-30). Lelan acts on change, not on noise."""
        state = (bool(on_battery), int(pct))
        if state == getattr(self, "_last_battery", None):
            return False
        self._last_battery = state
        self.BatteryStateChanged(*state)
        return False   # one-shot when used via GLib.idle_add

    @dbus.service.signal(IFACE, signature="sb")
    def NetworkStateChanged(self, iface, up): pass

    @dbus.service.signal(IFACE, signature="ss")
    def UsbDeviceAdded(self, vendor, product): pass

    @dbus.service.signal(IFACE, signature="ss")
    def UsbDeviceRemoved(self, vendor, product): pass

    @dbus.service.signal(IFACE, signature="s")
    def InputDeviceAdded(self, name): pass

    @dbus.service.signal(IFACE, signature="s")
    def InputDeviceRemoved(self, name): pass

    # ── sensing (Phase 1) ──
    @dbus.service.signal(IFACE, signature="a{sd}")
    def ThermalChanged(self, temps): pass

    @dbus.service.signal(IFACE, signature="a{su}")
    def FanChanged(self, fans): pass

    @dbus.service.signal(IFACE, signature="sd")
    def ThermalCritical(self, sensor, tempC): pass

    @dbus.service.signal(IFACE, signature="sss")
    def DriverMissing(self, device, modalias, suggested_module): pass

    # ── reference-device enablement (§4e) ──
    @dbus.service.signal(IFACE, signature="ss")
    def TouchscreenNotWorking(self, hid, reason): pass

    @dbus.service.signal(IFACE, signature="s")
    def AccelerometerOrientationChanged(self, orientation): pass

    @dbus.service.signal(IFACE, signature="b")
    def TabletModeChanged(self, active): pass

    # GameMode active/inactive (2026-07-12) — emitted when an actual game starts/
    # stops. The session (e.g. a future Lelan hook) can react; Sentinel already
    # applies the governor/GPU/screensaver actuators itself in gamemode.py.
    @dbus.service.signal(IFACE, signature="b")
    def GameModeChanged(self, active): pass

    # ── methods (Phase 2) ──
    # Lelan is the controller (operator, 2026-07-01): Sentinel only acts here,
    # never decides on its own which window deserves which tier.
    # sender_keyword (2026-07-04): io.ncde.Sentinel.conf allows any local user
    # to reach this method, and it freezes/throttles a caller-supplied pid's
    # cgroup as root — so the caller's real uid (resolved by the D-Bus daemon
    # itself via get_unix_user, not anything the caller could spoof) must be
    # checked against the target pid's actual owner. See
    # process_tier.py::_caller_may_tier for the real gate.
    @dbus.service.method(IFACE, in_signature="us", out_signature="b", sender_keyword="sender")
    def SetProcessTier(self, pid, tier, sender=None):
        try:
            caller_uid = int(self.connection.get_unix_user(sender))
        except dbus.DBusException:
            log.warning("SetProcessTier(%d): could not resolve caller uid — rejected", pid)
            return False
        return self._tiers.set_tier(int(pid), str(tier), caller_uid)

    @dbus.service.method(IFACE, in_signature="u")
    def ClearProcessTier(self, pid):
        self._tiers.drop(int(pid))

    # Guard for the two machine-wide root actuators below (2026-07-05 audit — same
    # reasoning that gated SetProcessTier in session 69): the D-Bus policy lets any
    # local user reach them, and they write root-owned system state (governor/EPP/
    # dirty_ratio, RAPL power cap). Root always may; a non-root caller must own an
    # ACTIVE logind session — i.e. be the person actually at the machine, which is
    # Lelan's case. Caller uid comes from the D-Bus daemon itself (get_unix_user),
    # session state from logind — neither is spoofable by the caller.
    def _caller_may_actuate(self, sender, method):
        try:
            uid = int(self.connection.get_unix_user(sender))
        except dbus.DBusException:
            log.warning("%s: could not resolve caller uid — rejected", method)
            return False
        if uid == 0:
            return True
        try:
            mgr = dbus.Interface(
                self.connection.get_object("org.freedesktop.login1", "/org/freedesktop/login1"),
                "org.freedesktop.login1.Manager")
            for s in mgr.ListSessions():   # a(susso): id, uid, user, seat, object path
                if int(s[1]) != uid:
                    continue
                props = dbus.Interface(self.connection.get_object("org.freedesktop.login1", s[4]),
                                       "org.freedesktop.DBus.Properties")
                if str(props.Get("org.freedesktop.login1.Session", "State")) == "active":
                    return True
        except dbus.DBusException:
            log.warning("%s: logind check failed — rejecting uid %d", method, uid)
            return False
        log.warning("%s: uid %d has no active session — rejected", method, uid)
        return False

    # Lelan is the controller here too (zen.md §4/"EFFICIENCY GAPS" — this closes
    # the chain-of-command gap zen.md itself flagged as still open): Lelan learns
    # AC/battery state independently via UPower and calls this to apply the real
    # governor/EPP/dirty_ratio state; Sentinel no longer decides this on its own
    # from its own udev power_supply event (see udev_monitor.py).
    @dbus.service.method(IFACE, in_signature="b", out_signature="b", sender_keyword="sender")
    def SetPowerProfile(self, on_battery, sender=None):
        if not self._caller_may_actuate(sender, "SetPowerProfile"):
            return False
        try:
            apply_zen(bool(on_battery))
            # Don't let an AC/battery event mid-game knock the game off the
            # performance governor — GameMode re-forces it if a game is running.
            self._gamemode.reassert_governor()
            return True
        except Exception:
            log.warning("SetPowerProfile failed", exc_info=True)
            return False

    # Fan-bypass fallback (2026-07-02) — Lelan is the controller: it already
    # tracks m_thermalHot (checkThermalZones' 89C/84C hysteresis) and calls this
    # on transitions. Sentinel just applies the RAPL power cap; see zen_hints.py
    # for why this exists (no controllable fan on the reference device).
    @dbus.service.method(IFACE, in_signature="b", out_signature="b", sender_keyword="sender")
    def SetThermalCap(self, active, sender=None):
        if not self._caller_may_actuate(sender, "SetThermalCap"):
            return False
        try:
            apply_thermal_cap(bool(active))
            return True
        except Exception:
            log.warning("SetThermalCap failed", exc_info=True)
            return False

    # Hardware-tier detection (2026-07-03) — the "does NCDE actually adapt to
    # the host's real hardware" half of the Amiga-chipset mission. One-shot,
    # cached at __init__ (see there) since hardware doesn't change mid-boot.
    @dbus.service.method(IFACE, out_signature="s")
    def GetHardwareTier(self):
        return self._hw_tier

    # Governor facts for Lelan (pressure.py, 2026-09-30): Sentinel senses, Lelan decides.
    @dbus.service.signal(IFACE, signature="db")
    def PressureSensed(self, max_zone_c, cpu_saturated): pass

    @dbus.service.method(IFACE, out_signature="d")
    def GetThermalTrip(self):
        return float(lowest_trip_c())

    # Settings > About facts (system_info.py, 2026-09-30): Sentinel senses, Lelan exposes.
    @dbus.service.method(IFACE, out_signature="a{ss}")
    def GetSystemInfo(self):
        return dbus.Dictionary(collect_system_info(), signature="ss")


def main():
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    # Lelan (Lelan_Bridges.cpp) subscribes to io.ncde.Sentinel via
    # QDBusConnection::systemBus() — this MUST match, or the two sides never
    # see each other regardless of any D-Bus policy/permission fix. (Confirmed
    # 2026-07-01: this was SessionBus() here, so all 9 of Lelan's onSentinel*
    # handlers were dead code — Sentinel never registered where Lelan listens.)
    try:
        bus = dbus.SystemBus()
    except dbus.DBusException:
        log.error("system bus unavailable")
        sys.exit(1)

    try:
        _name = dbus.service.BusName(BUS_NAME, bus)
    except dbus.DBusException as exc:
        log.error("cannot claim %s: %s", BUS_NAME, exc)
        sys.exit(1)

    sentinel = Sentinel(bus, OBJ_PATH)

    # Re-probe kernel capabilities (governors, EPP, BBR, cgroup freezer) — logs
    # only if the kernel actually changed since last boot. No user action ever.
    check_kernel_caps()

    # sched_ext scheduler selection (2026-07-03) — per-machine, never hardcoded to
    # this dev host's CPU topology. No-ops cleanly if unsupported/not installed.
    scx_select.apply()

    # Emit initial battery state so NCDEEngine knows the starting condition
    # before any udev event fires.
    on_battery, pct = battery_state()
    apply_zen(on_battery)
    GLib.idle_add(sentinel.report_battery, on_battery, pct)

    # hwmon sensing — discover once, then poll on one coalesced timer.
    sensors = HwmonSensors()
    state = {"temps": {}, "fans": {}, "critical": set(), "drivers": set()}
    # §1.C thermal-guardian backstop (pwm_guard.py) — discovers once at startup;
    # a silent no-op on hardware with no controllable PWM fan (e.g. this
    # reference dev machine — see pwm_guard.py's own docstring).
    pwm_guard = PwmGuard()
    # One SHARED shutdown fail-safe (2026-07-05 audit, closes zen_hints.py's own
    # flagged gap): SIGTERM/SIGINT must restore BOTH the PWM fans AND any active
    # RAPL power cap. atexit alone never runs on a SIG_DFL re-raise, so a systemd
    # stop mid-cap previously left the machine silently power-capped until reboot.
    # Registered AFTER PwmGuard() so this is the LAST signal.signal() call and
    # owns the signals (signal.signal keeps only the last handler per signal).
    def _shutdown(signum, _frame):
        pwm_guard.release_all()
        restore_zen_caps()
        sentinel._gamemode.shutdown_restore()   # never leave GPU/screensaver pinned
        signal.signal(signum, signal.SIG_DFL)
        os.kill(os.getpid(), signum)   # re-raise so systemd sees the expected termination
    for _sig in (signal.SIGTERM, signal.SIGINT):
        signal.signal(_sig, _shutdown)
    # Prime the first reading immediately, then on the interval.
    GLib.idle_add(lambda: (poll_sensors(sentinel, sensors, state, pwm_guard), False)[1])
    GLib.timeout_add_seconds(POLL_SECONDS, poll_sensors, sentinel, sensors, state, pwm_guard)

    # Driver detection (Phase 2) — one-shot scan at startup (safe, read-only).
    GLib.idle_add(scan_once, sentinel, state)

    # Reference-device enablement (§4e) — each piece is a real, live probe
    # that no-ops cleanly if the hardware/service isn't present (see
    # reference_devices.py's module docstring).
    GLib.idle_add(check_touchscreen, sentinel)
    sensor_proxy = SensorProxyBridge(bus, sentinel)
    tablet_mode = TabletModeWatcher(sentinel)
    if tablet_mode.active:
        GLib.timeout_add_seconds(2, tablet_mode.poll)

    # GameMode liveness sweep — a game's helper PIDs aren't all explicitly
    # cleared by Lelan, so reap dead ones every few seconds and switch GameMode
    # off once the last game process is gone (restores governor/GPU/screensaver).
    GLib.timeout_add_seconds(5, sentinel._gamemode.reap)

    t = threading.Thread(target=udev_thread, args=(sentinel,), daemon=True)
    t.start()

    # Zen: LaPivot's SCHED_FIFO boost stays on the shell; apps it launches are
    # returned to SCHED_OTHER so App Nap and scx_bpfland can govern them (rt_guard.py).
    rt_guard.start()

    log.info("started — D-Bus name: %s", BUS_NAME)
    # Type=notify + WatchdogSec=30 in the unit — READY=1 tells systemd startup
    # actually finished (not just process-spawned); the recurring WATCHDOG=1
    # ping (well under the 30s timeout) catches a hung GLib mainloop that
    # Restart=on-failure alone would never detect (a hang isn't a crash).
    sd_notify("READY=1")
    GLib.timeout_add_seconds(10, lambda: (sd_notify("WATCHDOG=1"), True)[1])
    GLib.MainLoop().run()


if __name__ == "__main__":
    main()
