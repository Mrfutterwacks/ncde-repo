"""Shared sysfs helpers for Sentinel modules."""

import os
import socket


def sd_notify(state):
    """Minimal systemd sd_notify client (no python-systemd dependency — this
    project vendors what it needs into the tree, so a raw datagram socket to
    $NOTIFY_SOCKET is the dependency-free way to do READY=1/WATCHDOG=1).
    Silent no-op outside a systemd unit (no NOTIFY_SOCKET set) or on any
    socket error — notification is a liveness nicety, never worth crashing
    the daemon over."""
    addr = os.environ.get("NOTIFY_SOCKET")
    if not addr:
        return
    if addr[0] == "@":
        addr = "\0" + addr[1:]
    try:
        with socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM) as sock:
            sock.connect(addr)
            sock.sendall(state.encode())
    except OSError:
        pass


def read_sysfs(path):
    try:
        with open(path) as f:
            return f.read().strip()
    except OSError:
        return ""


def read_int(path):
    """Read an integer sysfs value; None if missing/unreadable."""
    v = read_sysfs(path)
    if not v:
        return None
    try:
        return int(v)
    except ValueError:
        return None
