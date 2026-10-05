"""rt_guard — keep LaPivot's real-time boost from leaking into everything it launches.

Zen's self-boost (Lelan::applyZenStartupHints) puts LaPivot on SCHED_FIFO 1 so
the shell and its QSGRenderThreads always win the CPU and animations never
stall. SCHED_FIFO is inherited across fork, and LaPivot does not set
SCHED_RESET_ON_FORK, so every app it starts — terminal, shell, sudo, and
whatever that runs (mksquashfs, pacman, a compiler) — was also real-time.
Confirmed live 2026-09-30: ncde-terminal, zsh, claude, ps, awk all FIFO 1.

Two consequences:
  * App Nap and Zen were bypassed for every launched app: cgroup cpu.weight
    (ncde-nap scopes) and sched_ext (scx_bpfland) only schedule SCHED_OTHER
    tasks — a FIFO task ignores both.
  * A CPU-bound FIFO job on every core (mksquashfs zstd-19 during the ISO
    reauthor) starves Xorg, picom and kernel workers → the whole desktop
    freezes. kernel.sched_rt_runtime_us was 1000000 (no RT throttle), so
    nothing capped it.

Fix, event-driven (no polling): subscribe to the kernel proc connector and,
on every new PROCESS (not thread) that arrives carrying the inherited
SCHED_FIFO 1, move all its threads to SCHED_OTHER. LaPivot's own threads are
threads, not processes, so the shell keeps its boost; its children join App
Nap and bpfland like any other app. One startup sweep handles processes that
leaked before Sentinel started.
"""

import os
import socket
import struct
import logging
import threading

log = logging.getLogger(__name__)

NETLINK_CONNECTOR = 11
CN_IDX_PROC = 1
CN_VAL_PROC = 1
PROC_CN_MCAST_LISTEN = 1
PROC_EVENT_FORK = 0x00000001
NLMSG_DONE = 3
PF_KTHREAD = 0x00200000

LEAKED_PRIO = 1                 # the level LaPivot runs at — the only one we undo
SHELL_EXE = "/usr/local/bin/LaPivot"

_NLHDR = struct.Struct("=IHHII")
_CNMSG = struct.Struct("=IIIIHH")
_EVHDR = struct.Struct("=IIQ")
_FORK = struct.Struct("=IIII")


def _is_kthread(pid):
    try:
        with open("/proc/%d/stat" % pid) as f:
            stat = f.read()
        return int(stat.rsplit(")", 1)[1].split()[6]) & PF_KTHREAD != 0
    except (OSError, ValueError, IndexError):
        return True   # gone or unreadable — leave it alone


def _leaked(pid):
    try:
        return (os.sched_getscheduler(pid) == os.SCHED_FIFO
                and os.sched_getparam(pid).sched_priority == LEAKED_PRIO)
    except OSError:
        return False


def _demote(pid):
    """All threads of pid -> SCHED_OTHER. Returns True if anything changed."""
    changed = False
    try:
        tids = [int(t) for t in os.listdir("/proc/%d/task" % pid)]
    except OSError:
        tids = [pid]
    for tid in tids:
        try:
            if _leaked(tid):
                os.sched_setscheduler(tid, os.SCHED_OTHER, os.sched_param(0))
                changed = True
        except OSError:
            pass   # thread exited mid-walk
    return changed


def _comm(pid):
    try:
        with open("/proc/%d/comm" % pid) as f:
            return f.read().strip()
    except OSError:
        return "?"


def _is_shell(pid):
    try:
        return os.readlink("/proc/%d/exe" % pid) == SHELL_EXE
    except OSError:
        return False


def sweep():
    """Startup: undo leaks that happened before Sentinel was listening."""
    n = 0
    for d in os.listdir("/proc"):
        if not d.isdigit():
            continue
        pid = int(d)
        if _is_shell(pid) or _is_kthread(pid):
            continue
        if _demote(pid):
            n += 1
    if n:
        log.info("rt_guard: startup sweep returned %d leaked process(es) to SCHED_OTHER", n)


def _listen():
    s = socket.socket(socket.AF_NETLINK, socket.SOCK_DGRAM, NETLINK_CONNECTOR)
    s.bind((0, CN_IDX_PROC))
    op = struct.pack("=I", PROC_CN_MCAST_LISTEN)
    cn = _CNMSG.pack(CN_IDX_PROC, CN_VAL_PROC, 0, 0, len(op), 0) + op
    s.send(_NLHDR.pack(_NLHDR.size + len(cn), NLMSG_DONE, 0, 0, 0) + cn)
    off = _NLHDR.size + _CNMSG.size
    seen = set()
    while True:
        data = s.recv(4096)
        if len(data) < off + _EVHDR.size + _FORK.size:
            continue
        what = _EVHDR.unpack_from(data, off)[0]
        if what != PROC_EVENT_FORK:
            continue
        _, ptgid, cpid, ctgid = _FORK.unpack_from(data, off + _EVHDR.size)
        if cpid != ctgid or ptgid == 2:      # a new thread, or a kernel thread
            continue
        if _leaked(cpid) and _demote(cpid):
            # LaPivot re-spawns helpers (xset) every few seconds — name each program once
            name = _comm(cpid)
            if name not in seen:
                seen.add(name)
                log.info("rt_guard: %s[%d] (parent %d) -> SCHED_OTHER (further %s demotions not logged)",
                         name, cpid, ptgid, name)


def start():
    try:
        sweep()
    except OSError as exc:
        log.warning("rt_guard: startup sweep failed: %s", exc)

    def run():
        try:
            _listen()
        except OSError as exc:
            log.warning("rt_guard: proc connector unavailable (%s) — RT leak guard off", exc)

    threading.Thread(target=run, name="rt-guard", daemon=True).start()
