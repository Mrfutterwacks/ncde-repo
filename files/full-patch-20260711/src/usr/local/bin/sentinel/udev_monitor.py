"""udev hotplug monitor — dispatches kernel events to D-Bus signals.

Subsystems: sound, drm, power_supply, net, usb, input.
"""

import os
import threading
import logging

import pyudev
from gi.repository import GLib

from ._utils import read_sysfs
from .hwmon import battery_state

log = logging.getLogger(__name__)


def _net_up():
    """True if ANY real interface is up — the desktop-wide answer Lelan
    stores in its single m_network["up"] slot. The per-event operstate of
    the triggering iface is the wrong thing to report for that slot: an
    event about lo (operstate 'unknown') or a secondary iface overwrote
    the global state and painted the panel's red X while wlan0 was
    connected."""
    try:
        ifaces = os.listdir("/sys/class/net")
    except OSError:
        return False
    for iface in ifaces:
        if iface == "lo":
            continue
        if read_sysfs(f"/sys/class/net/{iface}/operstate") == "up":
            return True
        if read_sysfs(f"/sys/class/net/{iface}/carrier") == "1":
            return True
    return False


def _emit_net_state(sentinel, iface):
    sentinel.NetworkStateChanged(iface, _net_up())
    return False  # one-shot GLib timer


def handle_udev(sentinel, device):
    sub    = device.subsystem or ""
    action = device.action    or ""

    if sub == "sound":
        name = device.get("ID_MODEL") or device.get("ID_VENDOR") or "Unknown"
        GLib.idle_add(sentinel.AudioDeviceChanged, action, name)

    elif sub == "drm":
        connector = device.sys_name
        if any(x in connector for x in ("HDMI", "DP", "DisplayPort", "VGA")):
            status = read_sysfs(f"/sys/class/drm/{connector}/status")
            if status == "connected":
                GLib.idle_add(sentinel.DisplayConnected, connector)
            elif status == "disconnected":
                GLib.idle_add(sentinel.DisplayDisconnected, connector)

    elif sub == "power_supply":
        # Sentinel only SENSES + REPORTS here (zen.md's stated chain of command:
        # "Sentinel is a watcher... it speaks to Lelan who controls that"). Lelan
        # independently learns AC/battery state via UPower and is the one that
        # calls SetPowerProfile back on Sentinel to actually apply governor/EPP/
        # dirty_ratio — see __main__.py's SetPowerProfile method. Sentinel no
        # longer decides+acts on its own for this udev event (removed 2026-07-02;
        # it used to call zen_hints.apply() here directly, racing Lelan's decision
        # and, until the hwmon.py fix, doing so with the wrong on_battery value).
        on_battery, pct = battery_state()
        GLib.idle_add(sentinel.report_battery, on_battery, pct)

    elif sub == "net":
        iface = device.sys_name
        GLib.idle_add(sentinel.NetworkStateChanged, iface, _net_up())
        # operstate lags the event during wifi reauth (dormant/down), and no
        # further udev event fires when it finally settles to "up" — re-check
        # once the dust settles so the LAST word Lelan hears matches reality.
        GLib.timeout_add_seconds(3, _emit_net_state, sentinel, iface)

    elif sub == "usb" and device.device_type == "usb_device":
        vendor  = device.get("ID_VENDOR",  "") or ""
        product = device.get("ID_MODEL",   "") or ""
        if action == "add":
            GLib.idle_add(sentinel.UsbDeviceAdded, vendor, product)
        elif action == "remove":
            GLib.idle_add(sentinel.UsbDeviceRemoved, vendor, product)

    elif sub == "input":
        name = (device.get("NAME") or device.sys_name).strip('"')
        if action == "add":
            GLib.idle_add(sentinel.InputDeviceAdded, name)
        elif action == "remove":
            GLib.idle_add(sentinel.InputDeviceRemoved, name)


def udev_thread(sentinel):
    ctx     = pyudev.Context()
    monitor = pyudev.Monitor.from_netlink(ctx)
    for sub in ("sound", "drm", "power_supply", "net", "usb", "input"):
        monitor.filter_by(sub)
    monitor.start()
    log.info("udev monitor active")
    for device in iter(monitor.poll, None):
        try:
            handle_udev(sentinel, device)
        except Exception as exc:
            log.warning("dispatch error: %s", exc)
