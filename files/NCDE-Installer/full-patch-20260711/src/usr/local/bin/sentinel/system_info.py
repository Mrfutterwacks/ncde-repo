"""system_info — the machine facts the About tab shows (Settings > About).

settings-tabs.md recorded the About hardware grid as "needs C++ (properties don't exist in
binary)": AboutTab asked ncde (NCDEEngine, the colour engine) for cpuInfo/memInfo/gpuInfo/
diskInfo/hostName/releaseName, which it never had, so the tab showed placeholders. Chain of
command (2026-09-30): Sentinel SENSES hardware, Lelan EXPOSES it (lelan.systemInfo), QML reads
lelan. Every value is read from interfaces present on any Linux machine; anything unreadable is
simply omitted and the tab keeps its fallback text.

  GetSystemInfo() -> a{ss}
    release  "NCDE Poseidon"                      /etc/ncde-release
    cpu      "Intel Celeron N5095 @ 2.00GHz · 4 cores"   /proc/cpuinfo (+ ARM device-tree model)
    memory   "31.1 GB"                            /proc/meminfo MemTotal
    gpu      "Intel JasperLake [UHD Graphics]"    /sys/class/drm/card*/device + hwdata pci.ids
    disk     "931 GB · 480 GB free · <model>"     statvfs("/") + /sys/block/<disk>/device/model
"""

import glob
import os
import re

PCI_IDS = ("/usr/share/hwdata/pci.ids", "/usr/share/misc/pci.ids", "/usr/share/pci.ids")


def _read(path):
    try:
        with open(path, errors="replace") as f:
            return f.read().strip()
    except OSError:
        return ""


def _tidy(name):
    name = re.sub(r"\((R|TM|tm|r)\)|\bCPU\b", "", name)
    return re.sub(r"\s+", " ", name).strip()


def release():
    return _read("/etc/ncde-release").splitlines()[0] if _read("/etc/ncde-release") else ""


def cpu():
    text = _read("/proc/cpuinfo")
    model = ""
    for key in ("model name", "Model", "Hardware", "cpu model"):
        m = re.search(r"^%s\s*:\s*(.+)$" % re.escape(key), text, re.M)
        if m:
            model = m.group(1)
            break
    if not model:
        model = _read("/sys/firmware/devicetree/base/model").rstrip("\x00")
    cores = os.cpu_count() or 0
    model = _tidy(model)
    if not model:
        return ""
    return "%s · %d core%s" % (model, cores, "" if cores == 1 else "s") if cores else model


def memory():
    m = re.search(r"^MemTotal:\s+(\d+) kB", _read("/proc/meminfo"), re.M)
    return "%.1f GB" % (int(m.group(1)) / 1048576.0) if m else ""


def _pci_names(vendor, device):
    for path in PCI_IDS:
        try:
            with open(path, errors="replace") as f:
                vname = None
                for line in f:
                    if line.startswith("#") or not line.strip():
                        continue
                    if not line.startswith("\t"):
                        if vname is not None:
                            break                      # left our vendor block without a device match
                        if line[:4].lower() == vendor:
                            vname = line[4:].strip()
                    elif vname is not None and not line.startswith("\t\t") and line[1:5].lower() == device:
                        return vname, line[5:].strip()
                if vname:
                    return vname, ""
        except OSError:
            continue
    return "", ""


def gpu():
    names = []
    for card in sorted(glob.glob("/sys/class/drm/card[0-9]*")):
        if "-" in os.path.basename(card):
            continue                                   # connectors (card1-HDMI-A-1), not cards
        vendor = _read(card + "/device/vendor").lower().replace("0x", "")
        device = _read(card + "/device/device").lower().replace("0x", "")
        vname, dname = _pci_names(vendor, device) if vendor and device else ("", "")
        if dname:
            vshort = vname.split()[0] if vname else ""
            label = "%s %s" % (vshort, dname) if vshort and not dname.startswith(vshort) else dname
        else:
            try:
                label = os.path.basename(os.readlink(card + "/device/driver"))
            except OSError:
                label = ""
        if label and label not in names:
            names.append(label)
    return " + ".join(names)


def _root_disk_model():
    try:
        st = os.stat("/")
        major, minor = os.major(st.st_dev), os.minor(st.st_dev)
        dev = os.path.realpath("/sys/dev/block/%d:%d" % (major, minor))
    except OSError:
        return ""
    cands = [dev, os.path.dirname(dev)]
    # btrfs/LVM report an anonymous st_dev: use the mount table's real source device instead
    for line in _read("/proc/self/mountinfo").splitlines():
        f = line.split()
        if len(f) > 4 and f[4] == "/" and " - " in line:
            src = line.split(" - ", 1)[1].split()[1]
            if src.startswith("/dev/"):
                blk = os.path.realpath("/sys/class/block/" + os.path.basename(os.path.realpath(src)))
                cands += [blk, os.path.dirname(blk)]
            break
    # a partition's parent directory is the whole disk
    for d in cands:
        model = _read(os.path.join(d, "device", "model"))
        if model:
            return re.sub(r"\s+", " ", model)
    return ""


def disk():
    try:
        s = os.statvfs("/")
    except OSError:
        return ""
    total = s.f_blocks * s.f_frsize / 1e9
    free = s.f_bavail * s.f_frsize / 1e9
    parts = ["%.0f GB" % total, "%.0f GB free" % free]
    model = _root_disk_model()
    if model:
        parts.append(model)
    return " · ".join(parts)


def collect():
    info = {}
    for key, fn in (("release", release), ("cpu", cpu), ("memory", memory), ("gpu", gpu), ("disk", disk)):
        try:
            v = fn()
        except Exception:
            v = ""
        if v:
            info[key] = v
    return info
