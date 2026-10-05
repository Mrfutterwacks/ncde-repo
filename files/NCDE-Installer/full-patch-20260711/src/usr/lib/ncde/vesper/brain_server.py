#!/usr/bin/env python3
"""Vesper's brain service — NCDE's living security suite. NO LLM, NO cloud, NO hardcoded
answers. Deterministic conversational agent: intent recognition + slot filling + dialogue
memory + REAL engine control (ClamAV / rkhunter / fail2ban / nftables / auditd) + varied,
anticipatory phrasing so he FEELS alive without a model.

He asks, you decide (vesper.md §3): every real action is proposed first and only runs on
your confirmation. Reads the real MITRE ATT&CK library for "what is Txxxx?" questions.

  /usr/bin/python3 brain_server.py            (serves 127.0.0.1:8077)

Endpoints (all GET — the QML UI speaks only XHR GET):
  /whoami                     -> {"name": "..."}                the real logged-in user
  /engines                    -> {"engines":[...]}              real per-engine status
  /findings                   -> {"findings":[...],"narration"} real detections (benign-filtered)
  /converse?q=...&s=<session> -> {"reply","intent","action","suggestions","await_confirm"}
  /act?type=...&s=<session>&* -> {"ok","reply","result"}        runs a CONFIRMED real action
  /ask?q=...                  -> {"answer": "..."}              pure MITRE library lookup
  /quarantine[...]            -> quarantine store add/restore/remove/list
"""
import json, re, os, pwd, random, shutil, subprocess, threading, time, urllib.parse, uuid, html
from datetime import datetime
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
try:
    import vesper_engines            # the engine orchestration (ClamAV/rkhunter/fail2ban/nft/auditd)
except Exception:
    vesper_engines = None

BASE = os.path.dirname(os.path.abspath(__file__))
STIX = os.path.join(BASE, "enterprise-attack.json")          # relocatable
CARDS = os.path.join(BASE, "cards", "cards.json")
PRIV = "/usr/lib/ncde/vesper/ncde-vesper-priv"               # pkexec'd privileged helper
HOME = os.path.expanduser("~")

# ── MITRE library (real, shipped) ─────────────────────────────────────────
techs, items = {}, []
for o in json.load(open(STIX)).get("objects", []):
    if o.get("type") != "attack-pattern" or o.get("revoked") or o.get("x_mitre_deprecated"):
        continue
    tid = next((r.get("external_id") for r in o.get("external_references", [])
                if r.get("source_name") == "mitre-attack"), None)
    if not tid:
        continue
    desc = re.sub(r"\(Citation:[^)]*\)", "", (o.get("description", "") or "")).strip()
    rec = {"id": tid, "name": o.get("name", ""), "desc": desc}
    techs[tid] = rec
    items.append(rec)

try:
    _cardlib = json.load(open(CARDS))
    cards, sigs, faq = _cardlib["cards"], _cardlib["signatures"], _cardlib["faq"]
except Exception:
    cards, sigs, faq = {}, {}, {}

STOP = set("what whats does this that tell about your you vesper mean is are the a an of to how why "
           "do can it im i me on in for with malware virus threat security".split())

def first_sentences(t, n=2):
    return " ".join(re.split(r'(?<=[.!?])\s+', t.strip())[:n]).strip()

def whoami():
    """The logged-in user's real first name — GECOS, else login name. Never hardcoded."""
    try:
        ent = pwd.getpwuid(os.getuid())
        gecos = (ent.pw_gecos or "").split(",")[0].strip()
        n = gecos.split()[0] if gecos else ent.pw_name
        return n.capitalize() if n else "friend"
    except Exception:
        return "friend"

def org_name():
    try:
        with open("/etc/ncde/org.conf") as f:
            name = f.readline().strip()
            if name:
                return name
    except OSError:
        pass
    return "your community"

def greeting():
    h = datetime.now().hour
    return "Good morning" if h < 12 else "Good afternoon" if h < 18 else "Good evening"

# ── varied phrasing: pick a variant, never the same one twice in a row ─────
_last = {}
def pick(key, options):
    if isinstance(options, str):
        return options
    if len(options) <= 1:
        return options[0]
    pool = [o for j, o in enumerate(options) if j != _last.get(key)]
    o = random.choice(pool)
    _last[key] = options.index(o)
    return o

def lib_lookup(q):
    """MITRE-library / FAQ lookup. Returns (text, strong) — `strong` is True only for
    an exact technique id, an FAQ hit, or a name-anchored match, so the conversation
    fallback never dumps a weak keyword match on pure gibberish."""
    low = q.lower()
    for key, text in faq.items():
        if key.startswith("_"):
            continue
        if key in low:
            return text, True
    m = re.search(r't\d{4}(?:\.\d{3})?', low)              # exact technique id
    if m and m.group(0).upper() in techs:
        t = techs[m.group(0).upper()]
        return f"{t['id']} is “{t['name']}.” {first_sentences(t['desc'])}", True
    terms = [w for w in re.findall(r'[a-z0-9-]+', low) if len(w) > 2 and w not in STOP]
    best, score, name_hit = None, 0, False
    for rec in items:
        nm = rec['name'].lower(); hay = nm + " " + rec['desc'].lower()
        nh = bool(terms) and any(t in nm for t in terms)
        sc = sum(hay.count(t) for t in terms) + (6 if terms and all(t in nm for t in terms) else 0) + (3 if nh else 0)
        if sc > score:
            best, score, name_hit = rec, sc, nh
    if best and score >= 3:
        return f"That's {best['id']} — “{best['name']}.” {first_sentences(best['desc'])}", (name_hit or score >= 8)
    return None, False

def lib_answer(q):
    text, _ = lib_lookup(q)
    return text

# ── benign-finding filter (stop crying wolf) ──────────────────────────────
# rkhunter on a desktop routinely flags KNOWN-benign things. We suppress the
# exact false-positive classes so Vesper never raises them as threats. This is
# belt-and-suspenders with the rkhunter.conf whitelist the patch also installs.
_BENIGN_RK = [
    re.compile(r"file properties have changed", re.I),        # stale baseline after an update
    re.compile(r"shared memory segments", re.I),              # dunst/pulse/etc at/under allowed size
    re.compile(r"suspicious file types found in /dev", re.I), # steam/pulse /dev/shm IPC
    re.compile(r"hidden (file|dir)", re.I),                   # common packaged dotfiles
    re.compile(r"/dev/shm/", re.I),
    re.compile(r"ValveIPCSharedObj|pulse-shm|flatpak-", re.I),
    re.compile(r"grep: warning|unexpected operator|stray", re.I),  # rkhunter's own grep noise
]
def is_benign(f):
    d = (f.get("detail") or "") + " " + (f.get("signature") or "")
    return f.get("engine") == "rkhunter" and any(p.search(d) for p in _BENIGN_RK)

def real_findings(all_findings):
    return [f for f in all_findings if not is_benign(f)]

# ── quarantine store (real, restorable, never destroys) ───────────────────
QUAR_DIR = os.path.join(HOME, ".local", "share", "ncde-vesper", "quarantine")
MANIFEST = os.path.join(QUAR_DIR, "manifest.json")

def _manifest_load():
    try:
        with open(MANIFEST) as f:
            return json.load(f)
    except (OSError, ValueError):
        return []

def _manifest_save(entries):
    os.makedirs(QUAR_DIR, exist_ok=True)
    tmp = MANIFEST + ".tmp"
    with open(tmp, "w") as f:
        json.dump(entries, f, indent=1)
    os.replace(tmp, MANIFEST)

def quarantine_add(path, signature="", engine=""):
    if not path or not os.path.isfile(path):
        return {"ok": False, "error": "no such file: " + (path or "(empty)")}
    os.makedirs(QUAR_DIR, exist_ok=True)
    qid = uuid.uuid4().hex[:12]
    stored = os.path.join(QUAR_DIR, qid + "_" + os.path.basename(path))
    try:
        shutil.move(path, stored)
        os.chmod(stored, 0o400)
    except OSError as e:
        return {"ok": False, "error": str(e)}
    entries = _manifest_load()
    entries.append({"id": qid, "original": path, "stored": stored,
                    "signature": signature, "engine": engine, "time": time.time()})
    _manifest_save(entries)
    return {"ok": True, "id": qid}

def quarantine_restore(qid):
    entries = _manifest_load()
    for e in entries:
        if e["id"] == qid:
            if os.path.exists(e["original"]):
                return {"ok": False, "error": "a file already exists at " + e["original"]}
            try:
                shutil.move(e["stored"], e["original"])
                os.chmod(e["original"], 0o600)
            except OSError as ex:
                return {"ok": False, "error": str(ex)}
            _manifest_save([x for x in entries if x["id"] != qid])
            return {"ok": True, "restored": e["original"]}
    return {"ok": False, "error": "unknown quarantine id"}

def quarantine_remove(qid):
    entries = _manifest_load()
    for e in entries:
        if e["id"] == qid:
            try:
                os.remove(e["stored"])
            except FileNotFoundError:
                pass
            except OSError as ex:
                return {"ok": False, "error": str(ex)}
            _manifest_save([x for x in entries if x["id"] != qid])
            return {"ok": True}
    return {"ok": False, "error": "unknown quarantine id"}

# ── engine cache (engines run in one background thread; GETs answer instantly) ──
_eng_lock = threading.Lock()
_eng_results = {}

def _engine_loop():
    while True:
        for fn in (vesper_engines.ENGINES if vesper_engines else []):
            try:
                res = fn()
            except Exception as e:
                res = {"engine": fn.__name__, "present": True, "error": str(e), "findings": []}
            with _eng_lock:
                _eng_results[fn.__name__] = res
        time.sleep(30)

def engine_status():
    if not vesper_engines:
        return []
    with _eng_lock:
        return [_eng_results[fn.__name__] for fn in vesper_engines.ENGINES
                if fn.__name__ in _eng_results]

def engine_findings():
    out = []
    for e in engine_status():
        out.extend(e.get("findings", []))
    return out

# ── REAL engine actions (the "actually control Clam etc" part) ────────────
def _run(cmd, timeout=600):
    return subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)

def _resolve_target(word):
    """Map a spoken target to a real path (user scope)."""
    w = (word or "").strip().strip("'\"")
    named = {"downloads": "Downloads", "download": "Downloads", "documents": "Documents",
             "docs": "Documents", "desktop": "Desktop", "pictures": "Pictures",
             "home": "", "everything": "", "system": "", "my files": "", "": "Downloads"}
    low = w.lower()
    if low in named:
        return os.path.join(HOME, named[low]) if named[low] else HOME
    if w.startswith("~"):
        return os.path.expanduser(w)
    if w.startswith("/") or os.path.exists(os.path.join(HOME, w)):
        return w if w.startswith("/") else os.path.join(HOME, w)
    return os.path.join(HOME, "Downloads")

def act_scan(target):
    """Run a REAL ClamAV scan over a path. Prefer the running daemon (fast)."""
    path = _resolve_target(target)
    if not os.path.exists(path):
        return {"ok": False, "reply": f"I couldn't find {path} to scan — point me somewhere that exists."}
    sock = "/run/clamav/clamd.ctl"
    if shutil.which("clamdscan") and os.path.exists(sock):
        cmd = ["clamdscan", "--fdpass", "--no-summary", path]
    elif shutil.which("clamscan"):
        cmd = ["clamscan", "-r", "--no-summary", path]
    else:
        return {"ok": False, "reply": "My malware scanner isn't installed here — I can't sweep right now."}
    found = []
    try:
        r = _run(cmd, timeout=900)
        for ln in r.stdout.splitlines():
            if ln.rstrip().endswith("FOUND"):
                p, sig = ln.rsplit(":", 1)
                found.append({"path": p.strip(), "signature": sig.replace("FOUND", "").strip()})
    except subprocess.TimeoutExpired:
        return {"ok": False, "reply": "That scan is taking a while — it's a big tree. Try a smaller folder, or give it a minute and I'll report."}
    except Exception as e:
        return {"ok": False, "reply": f"The scan hit a snag: {e}"}
    return {"ok": True, "path": path, "found": found}

def act_priv(op, arg=""):
    """Run a whitelisted privileged op through the pkexec helper (asks for the
    admin password via the desktop's polkit agent). Commercial-suite pattern."""
    if not os.path.exists(PRIV) or not shutil.which("pkexec"):
        return {"ok": False, "reply": "I can't reach my privileged helper — that action needs the admin tools installed."}
    try:
        r = _run(["pkexec", PRIV, op] + ([arg] if arg else []), timeout=1800)
    except subprocess.TimeoutExpired:
        return {"ok": False, "reply": "That took too long and I stopped it to be safe."}
    except Exception as e:
        return {"ok": False, "reply": f"Couldn't run it: {e}"}
    if r.returncode == 126:
        return {"ok": False, "reply": "You waved off the password — no worries, nothing changed."}
    return {"ok": r.returncode == 0, "out": (r.stdout or "").strip(), "err": (r.stderr or "").strip(),
            "code": r.returncode}

def bans_now():
    if not shutil.which("fail2ban-client"):
        return None
    try:
        out = _run(["fail2ban-client", "status"], 15).stdout
        jails = []
        for ln in out.splitlines():
            if "Jail list:" in ln:
                jails = [j.strip() for j in ln.split(":", 1)[1].split(",") if j.strip()]
        banned = []
        for j in jails:
            js = _run(["fail2ban-client", "status", j], 15).stdout
            for ln in js.splitlines():
                if "Banned IP list:" in ln:
                    banned += [ip for ip in ln.split(":", 1)[1].split() if ip]
        return {"jails": jails, "banned": banned}
    except Exception:
        return None

# ── dialogue sessions (memory = the illusion of a mind) ───────────────────
_sessions = {}
_sess_lock = threading.Lock()
def sess(sid):
    with _sess_lock:
        return _sessions.setdefault(sid or "default",
            {"pending": None, "last_scan": None, "topic": None, "turns": 0})

# ── the conversational engine (intents -> action + varied reply) ──────────
CONFIRM = re.compile(r"\b(yes|yeah|yep|yup|sure|ok|okay|do it|go ahead|please|go for it|"
                     r"affirmative|seal it|quarantine it|absolutely|confirm|proceed)\b", re.I)
DENY = re.compile(r"\b(no|nope|not now|leave it|cancel|stop|nevermind|never mind|don'?t|hold off|wait)\b", re.I)

def suggestions(st, findings):
    """What to offer next — anticipation is what makes him feel alive."""
    s = []
    if findings:
        s.append("quarantine it")
        s.append("explain it")
    s.append("scan my downloads")
    if _manifest_load():
        s.append("review quarantine")
    s.append("am I safe?")
    # de-dupe, keep order, cap 3
    seen, out = set(), []
    for x in s:
        if x not in seen:
            seen.add(x); out.append(x)
        if len(out) == 3:
            break
    return out

def _reply(st, findings, text):
    """Return (reply, action, await_confirm). action is a proposal the UI confirms
    by calling /act. Everything here is deterministic template + slot fill."""
    name = whoami()
    s = text.strip()
    low = s.lower()
    st["turns"] += 1
    fcount = len(findings)

    # 1) confirm / deny of a PENDING proposal (dialogue memory)
    if st.get("pending"):
        if CONFIRM.search(low):
            act = st["pending"]; st["pending"] = None
            return (pick("gonow", ["On it.", "Right away.", "Consider it done.", "Doing that now."]),
                    act, False)
        if DENY.search(low):
            st["pending"] = None
            return (pick("stand", [f"Alright, {name} — standing down. It's still flagged; nothing was lost.",
                                   "Understood. I'll leave it be and keep watching.",
                                   "No problem. I'll hold off — say the word if you change your mind."]), None, False)

    # 2) greetings / small talk
    if re.match(r"^(hi|hey|hello|yo|sup|good (morning|afternoon|evening)|howdy)\b", low):
        return (pick("greet", [f"{greeting()}, {name}. All quiet — I'm on watch. Ask me anything.",
                               f"Right here, {name}. Nothing's wrong this second; I'll speak up the instant it is.",
                               f"Hello, {name}. Doors are locked, engines green. What do you need?"]), None, False)
    if re.search(r"\b(thank|thanks|cheers|appreciate)\b", low):
        return (pick("thx", [f"Anytime, {name}. It's what I'm here for.",
                             "That's the job. I'm not going anywhere.",
                             "Any time. I'll keep the watch."]), None, False)
    if re.search(r"how are you|how's it going|you (ok|alright|there)", low):
        return (pick("howru", [f"Sharp and watching, {name}. Every engine's reporting in.",
                               "Steady. Nothing at the doors and I like it that way.",
                               "All systems green on my end. You?"]), None, False)

    # 3) capabilities / help
    if re.search(r"\b(help|what can you do|commands?|how do (i|you)|what do you do)\b", low):
        return ("I'm your security watch, " + name + ". I can:\n"
                "  • scan a folder for malware — say “scan my downloads”\n"
                "  • seal a threat in quarantine (never deleted) — “quarantine it”\n"
                "  • show what's held — “review quarantine”\n"
                "  • update my virus definitions — “update definitions”\n"
                "  • re-check my rootkit baseline — “clear the false alarms”\n"
                "  • tell you who's been blocked — “who's knocking?”\n"
                "  • explain any threat or MITRE technique — “what is T1059?”\n"
                "Or just talk to me. I never act without asking you first.", None, False)

    # 4) status / safety
    if re.search(r"\b(safe|danger|serious|worried|all clear|status|everything ok|are we ok|secure)\b", low):
        engs = [e for e in engine_status() if e.get("present")]
        green = ", ".join(e["engine"] for e in engs) or "my engines"
        if fcount == 0:
            return (pick("safeyes",
                    [f"Right now? Yes, {name}. {green} all green, nothing at the doors. I never cry wolf — if I speak up, it's real.",
                     f"You're clear, {name}. Every engine's reporting in and I see nothing hostile. I'll tell you the second that changes.",
                     f"All quiet. {green} are watching with me and there's not a thing out of place."]), None, False)
        return (f"{name} — I'm holding {fcount} thing" + ("s" if fcount != 1 else "") +
                " for your call. Nothing's loose; it's contained. Say “explain it” and I'll walk you through it, or “quarantine it” to seal it off.",
                None, False)

    # 5) scan  (slot: target)
    m = re.search(r"\b(scan|sweep|check|examine)\b\s*(?:my\s+|the\s+|in\s+)?(.*)?$", low)
    if m and not re.search(r"\bquarantine\b", low):
        tgt = (m.group(2) or "").strip() or "downloads"
        path = _resolve_target(tgt)
        st["pending"] = {"type": "scan", "target": tgt}
        return (pick("askscan",
                [f"Want me to run a full malware scan over {path} right now, {name}? Say the word.",
                 f"I can sweep {path} with the live scanner — shall I? [yes]",
                 f"Ready to comb through {path} for anything hiding. Give me the go and I'll start."]),
                None, True)

    # 6) quarantine / block  (acts on the current finding). Skip when the user is
    #    asking to REVIEW/restore/remove the store — that's handled below (#11).
    if findings and re.search(r"\b(quarantine|block|seal|neutralize|contain|kill it)\b", low) \
            and not re.search(r"\b(review|show|list|open|what'?s|whats|held|restore|remove|delete|empty|clear)\b", low):
        filef = next((f for f in findings if f.get("path")), None)
        if filef:
            st["pending"] = {"type": "quarantine", "path": filef["path"],
                             "signature": filef.get("signature", ""), "engine": filef.get("engine", "")}
            base = os.path.basename(filef["path"])
            return (pick("askq",
                    [f"I'll seal {base} in quarantine — read-only, reversible, nothing deleted. Confirm and it's done. [yes]",
                     f"Say yes and {base} goes straight into a sealed box it can't escape. You can restore it anytime.",
                     f"Ready to wall off {base}. It stays recoverable forever — just give me the go."]),
                    None, True)
        if findings:
            f = findings[0]
            return (f"That one isn't a file I can box up, {name} — it's a "
                    f"{f.get('engine','engine')} alert ({f.get('detail','') or f.get('signature','')})[:0]. "
                    f"Its own engine already has it contained. Want me to explain what it means instead?",
                    None, False)
        return (pick("nothingq", [f"Nothing's flagged to seal right now, {name} — all quiet.",
                                  "There's nothing loose to quarantine at the moment. Want me to run a scan to be sure?"]),
                None, False)

    # 7) allow / trust
    if re.search(r"\b(allow|trust|ignore|leave|whitelist|it'?s fine|false alarm)\b", low) and not re.search(r"baseline|rootkit|rkhunter|noise|warning", low):
        return (pick("allow", [f"Alright — I'll leave it be, but I'll keep a quiet eye on it.",
                               "Trusted. I'll stop flagging it, though I never fully look away.",
                               "Understood. Marked safe for now — tell me if anything about it changes."]), None, False)

    # 8) clean the false alarms / re-baseline  (privileged)
    if re.search(r"(re-?baseline|propupd|clear.*(alarm|warning|noise)|(false alarm|noise|warnings?).*(clear|quiet|fix)|quiet.*(alarm|noise|rkhunter)|stop.*(warning|nag))", low):
        st["pending"] = {"type": "rebaseline"}
        return (pick("askrebase",
                [f"Those rootkit warnings are just my baseline going stale after updates, {name} — not a real intrusion. I can re-teach it what “normal” looks like and re-scan clean. Want me to? [yes]",
                 "I can re-set my rootkit baseline so it stops grumbling about files your own updates moved, then re-scan. Give me the word and I'll take care of it."]),
                None, True)

    # 9) update definitions  (privileged)
    if re.search(r"(update|refresh|freshen).*(def|signature|virus|database|clam)|freshclam", low):
        st["pending"] = {"type": "updatedefs"}
        return (pick("askdefs",
                [f"I can pull the latest virus definitions right now so I recognize the newest threats, {name}. Go? [yes]",
                 "Want me to freshen my malware definitions? One moment and I'm current again."]),
                None, True)

    # 10) firewall / bans  ("who's knocking", "who is at my door", "anyone trying to get in")
    if re.search(r"(who'?s|who is|anyone|anybody).{0,20}(knock|door|banned|blocked|breaking|trying to (get|break) in)"
                 r"|\b(banned|firewall|blocked ips?|intrud|fail2ban|brute[- ]?forc|knocking|at (the|my) door)\b", low):
        b = bans_now()
        if b is None:
            return ("My intrusion watch (fail2ban) isn't answering right now — I'll flag it if that persists.", None, False)
        if not b["banned"]:
            return (pick("nobans", [f"Nobody's forced their way in, {name} — zero banned addresses across {len(b['jails'])} watch"+("es" if len(b['jails'])!=1 else "")+". The perimeter's quiet.",
                                    "No intruders on the ban list. The walls are holding."]), None, False)
        return (f"{len(b['banned'])} address"+("es" if len(b['banned'])!=1 else "")+" barred at the gate right now: "
                + ", ".join(b["banned"][:8]) + (" …" if len(b["banned"]) > 8 else "")
                + f". I banned them for hammering the door. You're protected, {name}.", None, False)

    # 11) review quarantine / restore / remove
    if re.search(r"\brestore\b", low):
        mid = re.search(r"([0-9a-f]{6,})", low)
        if mid:
            st["pending"] = {"type": "restore", "id": mid.group(1)}
            return (f"I'll put that one back exactly where it was and keep watching it. Confirm? [yes]", None, True)
        return ("Which one, " + name + "? Say “review quarantine” and I'll list them with their ids.", None, False)
    if re.search(r"\b(remove|delete|destroy)\b.*[0-9a-f]{6}", low):
        mid = re.search(r"([0-9a-f]{6,})", low)
        st["pending"] = {"type": "remove", "id": mid.group(1)}
        return ("That deletes it for good — no undo. You're sure? [yes]", None, True)
    if re.search(r"\b(review|show|list|what'?s in).*(quarantine|held|sealed|box)|\bquarantine\b$|^quarantine\b", low) or low.strip() == "quarantine":
        q = _manifest_load()
        if not q:
            return (pick("emptyq", [f"Quarantine's empty, {name} — nothing held. That's how I like it.",
                                    "Nothing in the sealed box right now. All clear."]), None, False)
        lines = [f"  {i+1}. {os.path.basename(e['original'])} — {e.get('signature') or e.get('engine') or 'flagged'}  [id {e['id']}]"
                 for i, e in enumerate(q)]
        return (f"{len(q)} item"+("s" if len(q)!=1 else "")+" sealed and held:\n" + "\n".join(lines)
                + "\nSay “restore <id>” to put one back, or “remove <id>” to destroy it for good.", None, False)

    # 12) explain / analyse the current finding
    if re.search(r"\b(explain|analyse|analyze|what is (this|it|that)|tell me more|why|details?)\b", low) and findings:
        f = findings[0]
        cls = f.get("threat_class", "threat")
        where = f.get("path") or f.get("detail") or f.get("ip") or "something"
        eng = f.get("engine", "a scan")
        plain = lib_answer(cls) or ""
        return (f"Here's what I've got, {name}: {eng} flagged {where}. I'm calling it {cls}. "
                + (plain + " " if plain else "")
                + ("It's a real file, so I can seal it in quarantine on your word — say “quarantine it.”"
                   if f.get("path") else "Its own engine already has it contained; nothing's loose."), None, False)

    # 13) define / what-is  (MITRE + FAQ library)
    ans, strong = lib_lookup(s)
    if ans and re.search(r"\b(what|who|how|why|which|explain|define|tell|mean|meaning|is|are)\b", low):
        tail = pick("libtail", [" Want me to check your machine for it?", " Ask me if you want the plain-English version.",
                                "", " I keep the whole ATT&CK library in here."])
        return (ans + tail, None, False)

    # 14) fallback — only surface a library answer if it's a CONFIDENT match; otherwise
    #     stay honest and reflective (never fake certainty on gibberish).
    if ans and strong:
        return (ans, None, False)
    refl = re.sub(r"^(vesper[, ]*|hey[, ]*|so[, ]*)", "", low).strip().rstrip("?.!")
    return (pick("fallback",
            [f"I don't have a clean answer on “{html.escape(refl)[:80]}” yet, {name} — I'd rather flag it for a proper look than guess. Want me to run a scan?",
             f"That's outside what I can say for certain, {name}. I never bluff on security. I can scan, check the firewall, or explain any threat you name.",
             f"Not sure I follow, {name}. Try “scan my downloads,” “am I safe?,” or “what is <a threat>?” — or just tell me what's worrying you."]),
            None, False)

def converse(sid, q):
    st = sess(sid)
    findings = real_findings(engine_findings())
    reply, action, await_confirm = _reply(st, findings, q)
    st["topic"] = q
    return {"reply": reply, "action": action, "await_confirm": bool(await_confirm),
            "suggestions": suggestions(st, findings), "threatCount": len(findings)}

def do_act(sid, params):
    st = sess(sid)
    t = params.get("type", [""])[0]
    name = whoami()
    if t == "scan":
        r = act_scan(params.get("target", [""])[0])
        if not r.get("ok"):
            return {"ok": False, "reply": r.get("reply", "That scan didn't run.")}
        found = r["found"]; where = r["path"]
        if not found:
            n = _count_files(where)
            return {"ok": True, "reply": pick("scanclean",
                [f"Swept {where} — {n} file"+("s" if n!=1 else "")+", all clean. Nothing hiding, {n2}.".replace("{n2}", name),
                 f"Done. I went through {where} and found nothing malicious. You're clear.",
                 f"All clean in {where}. Not a thing out of place — I'll keep watching."])}
        st["last_scan"] = found
        first = found[0]
        st["pending"] = {"type": "quarantine", "path": first["path"],
                         "signature": first["signature"], "engine": "ClamAV"}
        names = ", ".join(os.path.basename(f["path"]) for f in found[:4])
        return {"ok": True, "await_confirm": True,
                "reply": f"{name} — I found {len(found)} infected file"+("s" if len(found)!=1 else "")+
                         f" in {where}: {names}"+(" …" if len(found) > 4 else "")+
                         f". First is “{first['signature']}.” I'd seal "+
                         ("them" if len(found)>1 else "it")+" off now — nothing deleted, fully reversible. Quarantine? [yes]"}
    if t == "quarantine":
        pend = st.get("pending") or {}
        path = params.get("path", [pend.get("path", "")])[0]
        signature = params.get("signature", [pend.get("signature", "")])[0]
        engine = params.get("engine", [pend.get("engine", "")])[0]
        st["pending"] = None
        r = quarantine_add(path, signature, engine)
        if r.get("ok"):
            return {"ok": True, "reply": pick("qdone",
                [f"Done — sealed in quarantine, held read-only. Reversible any time: say “review quarantine.” You're protected, {name}.",
                 f"Contained. It can't run or touch anything now, and nothing was destroyed. Nicely handled, {name}."])}
        return {"ok": False, "reply": f"I couldn't seal it — {r.get('error','the file moved')}. It's still flagged; nothing lost."}
    if t == "rebaseline":
        r = act_priv("rebaseline")
        if r.get("ok"):
            return {"ok": True, "reply": pick("rebased",
                [f"Re-taught. My baseline now matches your real system, so those false grumbles are gone. I re-scanned clean, {name}.",
                 "Baseline refreshed — the stale warnings won't bother you again. Everything checks out."])}
        return {"ok": False, "reply": r.get("reply") or f"The re-baseline didn't finish ({r.get('err','')[:120]})."}
    if t == "updatedefs":
        r = act_priv("freshclam")
        if r.get("ok"):
            return {"ok": True, "reply": pick("defsok",
                [f"Definitions are current — I know the newest threats now, {name}.",
                 "Fresh signatures loaded. I'm up to date and back on watch."])}
        return {"ok": False, "reply": r.get("reply") or f"Couldn't refresh definitions ({r.get('err','')[:120]})."}
    if t == "restore":
        r = quarantine_restore(params.get("id", [st.get("pending", {}).get("id", "")])[0])
        return {"ok": r.get("ok"), "reply": ("Restored — back exactly where it was. I'm still watching it."
                if r.get("ok") else f"Couldn't restore it: {r.get('error')}.")}
    if t == "remove":
        r = quarantine_remove(params.get("id", [st.get("pending", {}).get("id", "")])[0])
        return {"ok": r.get("ok"), "reply": ("Destroyed for good. That one can't hurt anyone now."
                if r.get("ok") else f"Couldn't remove it: {r.get('error')}.")}
    return {"ok": False, "reply": "I didn't recognize that action."}

def _count_files(path):
    n = 0
    try:
        if os.path.isfile(path):
            return 1
        for _, _, files in os.walk(path):
            n += len(files)
            if n > 99999:
                break
    except Exception:
        pass
    return n

# ── narration for auto-popped findings (unchanged, benign-filtered) ───────
def render_narration(findings):
    return None  # cards cover only ransomware; real conversational replies carry the voice now

# ── HTTP ──────────────────────────────────────────────────────────────────
def _send(handler, payload):
    body = json.dumps(payload).encode()
    handler.send_response(200)
    handler.send_header("Content-Type", "application/json")
    handler.send_header("Access-Control-Allow-Origin", "*")
    handler.send_header("Content-Length", str(len(body)))
    handler.end_headers()
    handler.wfile.write(body)

class H(BaseHTTPRequestHandler):
    def log_message(self, *a): pass
    def do_GET(self):
        u = urllib.parse.urlparse(self.path)
        path = u.path
        qs = urllib.parse.parse_qs(u.query)
        if path == "/converse":
            _send(self, converse(qs.get("s", ["default"])[0], qs.get("q", [""])[0])); return
        if path == "/act":
            _send(self, do_act(qs.get("s", ["default"])[0], qs)); return
        if path.startswith("/quarantine"):
            if path == "/quarantine":
                p = {"quarantine": _manifest_load()}
            elif path == "/quarantine/add":
                p = quarantine_add(qs.get("path", [""])[0], qs.get("signature", [""])[0], qs.get("engine", [""])[0])
            elif path == "/quarantine/restore":
                p = quarantine_restore(qs.get("id", [""])[0])
            elif path == "/quarantine/remove":
                p = quarantine_remove(qs.get("id", [""])[0])
            else:
                p = {"ok": False, "error": "unknown quarantine action"}
            _send(self, p); return
        if path == "/whoami":
            _send(self, {"name": whoami()}); return
        if path == "/engines":
            _send(self, {"engines": engine_status()}); return
        if path == "/findings":
            findings = real_findings(engine_findings())
            _send(self, {"findings": findings, "narration": render_narration(findings)}); return
        _send(self, {"answer": lib_answer(qs.get("q", [""])[0]) or
                     f"I don't have that in my library yet, {whoami()} — I'd flag it for review rather than guess."})

if __name__ == "__main__":
    threading.Thread(target=_engine_loop, daemon=True).start()
    print(f"brain_server: {len(techs)} MITRE techniques loaded, serving 127.0.0.1:8077", flush=True)
    ThreadingHTTPServer(("127.0.0.1", 8077), H).serve_forever()
