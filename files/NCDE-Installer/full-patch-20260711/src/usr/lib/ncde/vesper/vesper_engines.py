#!/usr/bin/env python3
"""Vesper's engine orchestration — he CONTROLS all the security software. Each adapter
runs the REAL tool when it's installed (else reports present=False; it ships in the NCDE
tree). Returns normalized status + findings the brain serves to the UI. No LLM."""
import subprocess, shutil, os

WATCH = "/tmp/vesper-watch"          # the folder Vesper scans for malware
CLAMD_SOCK = "/run/clamav/clamd.ctl" # clamav-daemon.service's socket

def have(t): return shutil.which(t) is not None
def _run(cmd, timeout=180): return subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)

def clamav():
    # Prefer the RUNNING clamav-daemon (clamdscan: ~10ms) over a cold clamscan,
    # which reloads the entire signature DB per call (~30s+ on the reference
    # Celeron). Same "path: Sig FOUND" output either way.
    if have("clamdscan") and os.path.exists(CLAMD_SOCK):
        cmd = ["clamdscan", "--fdpass", "--no-summary", WATCH]
    elif have("clamscan"):
        cmd = ["clamscan", "-r", "--no-summary", WATCH]
    else:
        return {"engine": "ClamAV", "role": "malware scanner", "present": False, "findings": []}
    os.makedirs(WATCH, exist_ok=True)
    finds = []
    try:
        r = _run(cmd)
        for ln in r.stdout.splitlines():
            if ln.rstrip().endswith("FOUND"):
                path, sig = ln.rsplit(":", 1)
                finds.append({"engine": "ClamAV", "threat_class": "malware",
                              "path": path.strip(), "signature": sig.replace("FOUND", "").strip()})
    except Exception as e:
        return {"engine": "ClamAV", "role": "malware scanner", "present": True, "error": str(e), "findings": []}
    return {"engine": "ClamAV", "role": "malware scanner", "present": True, "findings": finds}

RK_REPORT = "/var/lib/ncde-vesper/rkhunter-report"   # written by ncde-rkhunter.timer (root)

def rkhunter():
    if have("rkhunter"):
        # directly runnable (only if this process is root) — scan inline
        finds = []
        try:
            r = _run(["rkhunter", "--check", "--sk", "--rwo"])     # report warnings only
            for ln in r.stdout.splitlines():
                if ln.strip():
                    finds.append({"engine": "rkhunter", "threat_class": "rootkit", "detail": ln.strip()})
        except Exception as e:
            return {"engine": "rkhunter", "role": "rootkit scanner", "present": True, "error": str(e), "findings": []}
        return {"engine": "rkhunter", "role": "rootkit scanner", "present": True, "findings": finds}
    if not os.path.exists("/usr/bin/rkhunter"):
        return {"engine": "rkhunter", "role": "rootkit scanner", "present": False, "findings": []}
    # Normal case: rkhunter is packaged root-only (0700), invisible to which() from a
    # user service — read the report the root-side ncde-rkhunter.timer writes instead.
    try:
        with open(RK_REPORT) as f:
            lines = f.read().splitlines()
    except OSError:
        return {"engine": "rkhunter", "role": "rootkit scanner", "present": True,
                "note": "awaiting first scheduled scan (ncde-rkhunter.timer)", "findings": []}
    finds, last = [], ""
    for ln in lines:
        t = ln.strip()
        if not t:
            continue
        if t.startswith("#"):
            if t.startswith("# ncde-rkhunter scan "):
                last = t.split()[-1]
            continue
        if ln[:1].isspace() and finds:
            # indented = continuation of the previous warning, one finding per warning
            finds[-1]["detail"] += " " + t
            continue
        finds.append({"engine": "rkhunter", "threat_class": "rootkit", "detail": t})
    res = {"engine": "rkhunter", "role": "rootkit scanner", "present": True, "findings": finds}
    if last:
        res["last_scan"] = last
    return res

def fail2ban():
    if not have("fail2ban-client"):
        return {"engine": "fail2ban", "role": "intrusion bans", "present": False, "findings": []}
    finds = []
    try:
        out = _run(["fail2ban-client", "status"], 15).stdout
        jails = []
        for ln in out.splitlines():
            if "Jail list:" in ln:
                jails = [j.strip() for j in ln.split(":", 1)[1].split(",") if j.strip()]
        for j in jails:
            js = _run(["fail2ban-client", "status", j], 15).stdout
            for ln in js.splitlines():
                if "Banned IP list:" in ln:
                    for ip in ln.split(":", 1)[1].split():
                        finds.append({"engine": "fail2ban", "threat_class": "intrusion", "ip": ip, "jail": j})
    except Exception as e:
        return {"engine": "fail2ban", "role": "intrusion bans", "present": True, "error": str(e), "findings": []}
    return {"engine": "fail2ban", "role": "intrusion bans", "present": True, "findings": finds}

def nftables():
    if not have("nft"):
        return {"engine": "nftables", "role": "firewall", "present": False, "findings": []}
    try:
        r = _run(["nft", "list", "ruleset"], 15)
        if r.returncode != 0:
            return {"engine": "nftables", "role": "firewall", "present": True, "note": "needs root", "findings": []}
        rules = sum(1 for l in r.stdout.splitlines() if l.strip())
        return {"engine": "nftables", "role": "firewall", "present": True, "rules": rules, "findings": []}
    except Exception as e:
        return {"engine": "nftables", "role": "firewall", "present": True, "error": str(e), "findings": []}

def auditd():
    if not have("auditctl"):
        return {"engine": "auditd", "role": "syscall audit", "present": False, "findings": []}
    try:
        r = _run(["auditctl", "-s"], 10)
        if r.returncode != 0:
            return {"engine": "auditd", "role": "syscall audit", "present": True, "note": "needs root", "findings": []}
        first = (r.stdout.strip().splitlines() or [""])[0]
        return {"engine": "auditd", "role": "syscall audit", "present": True, "status": first, "findings": []}
    except Exception as e:
        return {"engine": "auditd", "role": "syscall audit", "present": True, "error": str(e), "findings": []}

ENGINES = [clamav, rkhunter, fail2ban, nftables, auditd]

def status_all():
    return [fn() for fn in ENGINES]

def findings_all():
    out = []
    for fn in ENGINES:
        out.extend(fn().get("findings", []))
    return out
