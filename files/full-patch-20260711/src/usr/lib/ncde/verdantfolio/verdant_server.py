#!/usr/bin/env python3
"""GiGi's helper (no LLM) — verdantfolio's language engine.
  GET  /advice?headline=...     -> profession tip
  GET  /spellcheck?text=...     -> misspelled words
  GET  /grammar?text=...        -> grammar errors + fixes
  GET  /suggest?word=...         -> thesaurus suggestions (GiGi's internal use)
  POST /export   {résumé, format} -> LibreOffice
  POST /send     {résumé, job_email} -> Hummingbird Courier
Serves :8078. All local, no online dependency.
"""
import json, os, re, shutil, subprocess, tempfile, urllib.parse
from http.server import BaseHTTPRequestHandler, HTTPServer

HERE = os.path.dirname(os.path.abspath(__file__))
ADV  = json.load(open(os.path.join(HERE, "professions.json")))
LANG = json.load(open(os.path.join(HERE, "language_tools.json")))
ENV  = {**os.environ, "DISPLAY": os.environ.get("DISPLAY", ":0")}
TMP  = tempfile.gettempdir()

# Common English words for spell checking
COMMON_WORDS = set("""
the be to of and a in that have i it for not on with he as you do at this but his by from
they we say her she or an will my one all would there their what so up out if about who get
which go me when make can like time no just him know take people into year your good some
could them see other than then now look only come its over think also back after use two
how our work first well way even new want because any these give day most us is are was
been has had have did does doing done being am were
""".split())

def advice_for(headline):
    h = (headline or "").lower()
    for p in ADV["professions"]:
        if any(k in h for k in p["keywords"]):
            return p
    return ADV["default"]

def spellcheck(text):
    """Return list of misspelled words with suggestions."""
    words = re.findall(r"[a-zA-Z']+", text)
    results = []
    for word in words:
        w = word.lower().strip("'")
        if len(w) < 2:
            continue
        if w in COMMON_WORDS:
            continue
        # Check if it's a known misspelling
        known_fix = None
        for rule in LANG["grammar_rules"]:
            if re.search(rule["pattern"], w, re.IGNORECASE):
                known_fix = rule["replacement"]
                break
        if known_fix and known_fix.lower() != w:
            results.append({"word": word, "suggestion": known_fix, "type": "spelling"})
            continue
        # Check dictionary
        if w in LANG["dictionary"]:
            continue
        # Check thesaurus keys
        if w in LANG["thesaurus"]:
            continue
        # Check if it looks like a real word (heuristic: contains vowels, no triple consonants)
        if re.search(r'[aeiou]', w) and not re.search(r'[^aeiouy]{4,}', w):
            continue
        # Unknown word — suggest closest match
        suggestions = _closest_words(w)
        results.append({"word": word, "suggestion": suggestions[0] if suggestions else None, "type": "unknown"})
    return results

def _closest_words(word, max_results=3):
    """Find closest words by simple edit distance."""
    word = word.lower()
    candidates = list(LANG["dictionary"].keys()) + list(LANG["thesaurus"].keys())
    scored = []
    for candidate in candidates:
        dist = _levenshtein(word, candidate)
        if dist <= max(2, len(word) // 3):
            scored.append((dist, candidate))
    scored.sort()
    return [s[1] for s in scored[:max_results]]

def _levenshtein(s1, s2):
    """Simple Levenshtein distance."""
    if len(s1) < len(s2):
        return _levenshtein(s2, s1)
    if len(s2) == 0:
        return len(s1)
    prev = list(range(len(s2) + 1))
    for i, c1 in enumerate(s1):
        curr = [i + 1]
        for j, c2 in enumerate(s2):
            curr.append(min(prev[j + 1] + 1, curr[j] + 1, prev[j] + (c1 != c2)))
        prev = curr
    return prev[-1]

def grammar_check(text):
    """Check text for grammar errors, return list of issues."""
    results = []
    for rule in LANG["grammar_rules"]:
        for match in re.finditer(rule["pattern"], text, re.IGNORECASE):
            results.append({
                "word": match.group(),
                "suggestion": rule["replacement"],
                "description": rule["description"],
                "position": match.start()
            })
    # Check for repeated words
    for match in re.finditer(r'\b(\w+)\s+\1\b', text, re.IGNORECASE):
        results.append({
            "word": match.group(),
            "suggestion": match.group(1),
            "description": "Repeated word",
            "position": match.start()
        })
    # Check for spaces before punctuation
    for match in re.finditer(r'\s+([.,;:!?])', text):
        results.append({
            "word": match.group(),
            "suggestion": match.group(1),
            "description": "Extra space before punctuation",
            "position": match.start()
        })
    return results

def suggest(word):
    """Get thesaurus suggestions for a word (GiGi's internal use)."""
    w = word.lower()
    if w in LANG["thesaurus"]:
        return LANG["thesaurus"][w]
    return []

def define(word):
    """Get dictionary definition (GiGi's internal use)."""
    w = word.lower()
    if w in LANG["dictionary"]:
        return LANG["dictionary"][w]
    return None

def html_resume(r):
    def e(s): return (s or "").replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
    h = ["<html><body style='font-family:Georgia,serif;max-width:720px;margin:48px auto;color:#23201a'>"]
    h.append(f"<h1 style='margin:0'>{e(r.get('name','')) or 'Your Name'}</h1>")
    if r.get('headline'): h.append(f"<div style='color:#6a5a3a;font-style:italic;font-size:15px'>{e(r['headline'])}</div>")
    contact = " &middot; ".join(filter(None, [r.get('email',''), r.get('phone',''), r.get('location','')]))
    if contact: h.append(f"<div style='font-size:12px'>{contact}</div><hr>")
    if r.get('summary'):    h.append(f"<p>{e(r['summary'])}</p>")
    exp = r.get('experience', [])
    if exp:
        h.append("<h3>Experience</h3>")
        for item in exp:
            title = e(item.get('title', ''))
            company = e(item.get('company', ''))
            dates = e(item.get('start', '')) + ' – ' + e(item.get('end', 'Present'))
            desc = e(item.get('description', ''))
            h.append(f"<p><strong>{title}</strong> — <em>{company}</em><br><small>{dates}</small><br>{desc}</p>")
    if r.get('education'): h.append("<h3>Education</h3><p>" + e(r['education']) + "</p>")
    skills = []
    if r.get('skills_tech'): skills.append(f"<strong>Technical:</strong> {e(r['skills_tech'])}")
    if r.get('skills_soft'): skills.append(f"<strong>Soft:</strong> {e(r['skills_soft'])}")
    if r.get('skills_lang'): skills.append(f"<strong>Languages:</strong> {e(r['skills_lang'])}")
    if skills: h.append("<h3>Skills</h3><p>" + "<br>".join(skills) + "</p>")
    h.append("</body></html>")
    return "\n".join(h)

class H(BaseHTTPRequestHandler):
    def log_message(self, *a): pass
    def _send(self, obj):
        b = json.dumps(obj).encode()
        self.send_response(200); self.send_header("Content-Type", "application/json")
        self.send_header("Access-Control-Allow-Origin", "*"); self.send_header("Content-Length", str(len(b)))
        self.end_headers(); self.wfile.write(b)

    def do_GET(self):
        u = urllib.parse.urlparse(self.path)
        q = urllib.parse.parse_qs(u.query)
        if u.path == "/advice":
            p = advice_for(q.get("headline", [""])[0])
            self._send({"gigi": p["gigi"], "summary": p.get("summary", ""), "skills": ", ".join(p.get("skills", []))})
        elif u.path == "/spellcheck":
            text = q.get("text", [""])[0]
            self._send({"errors": spellcheck(text)})
        elif u.path == "/grammar":
            text = q.get("text", [""])[0]
            self._send({"errors": grammar_check(text)})
        elif u.path == "/suggest":
            word = q.get("word", [""])[0]
            self._send({"suggestions": suggest(word)})
        elif u.path == "/define":
            word = q.get("word", [""])[0]
            self._send({"definition": define(word)})
        else:
            self._send({"ok": True})

    def do_POST(self):
        ln = int(self.headers.get("Content-Length", 0))
        data = json.loads(self.rfile.read(ln) or b"{}")
        u = urllib.parse.urlparse(self.path)
        if u.path == "/export":
            fmt = (data.get("format") or "open").lower()
            src = os.path.join(TMP, "verdant-resume.html")
            open(src, "w").write(html_resume(data))
            try:
                if fmt == "open":
                    subprocess.Popen(["libreoffice", "--writer", src], env=ENV)
                    msg = "Opening your résumé in LibreOffice — save it as PDF, DOCX, or ODT from there, darlin'."
                else:
                    ext = {"pdf": "pdf", "docx": "docx", "odt": "odt"}.get(fmt, "pdf")
                    subprocess.run(["libreoffice", "--headless", "--convert-to", ext, "--outdir", TMP, src],
                                   env=ENV, timeout=60)
                    out = os.path.join(TMP, "verdant-resume." + ext)
                    subprocess.Popen(["xdg-open", out], env=ENV)
                    msg = f"Saved your résumé as {ext.upper()} and opened it ({out})."
                self._send({"status": msg})
            except Exception as ex:
                self._send({"status": f"LibreOffice hand-off hiccup: {ex}"})
        elif u.path == "/send":
            user = data.get("name") or "Applicant"
            to   = data.get("job_email") or ""
            dear = data.get("recipient_name") or "Hiring Manager"
            role = data.get("headline") or "the position"
            src = os.path.join(TMP, "verdant-resume.html"); open(src, "w").write(html_resume(data))
            attach = src
            try:
                subprocess.run(["libreoffice", "--headless", "--convert-to", "pdf", "--outdir", TMP, src], env=ENV, timeout=60)
                attach = os.path.join(TMP, "verdant-resume.pdf")
            except Exception:
                pass
            subject = f"Application — {user}"
            body = (f"Dear {dear},\n\nPlease find my résumé attached for your consideration for {role}. "
                    f"I would welcome the opportunity to discuss how I can contribute to your team.\n\n"
                    f"Thank you for your time.\n\nSincerely,\n{user}")
            hb = shutil.which("hummingbird-courier") or "/usr/local/bin/hummingbird-courier"
            if os.path.exists(hb) and os.access(hb, os.X_OK):
                try:
                    subprocess.Popen([hb, "--compose", "--to", to, "--subject", subject,
                                      "--body", body, "--attach", attach], env=ENV)
                    handed = ("Opened in Hummingbird Courier — subject, letter, and résumé attached. "
                              f"Type the recipient ({to or 'their address'}) in the To field and hit Send.")
                except Exception as ex:
                    handed = f"Email composed (Hummingbird hand-off: {ex})."
            else:
                handed = "Couldn't find Hummingbird Courier on this system — your email text is composed above; copy it into your mail app."
            self._send({"status": f"To: {to or '—'}  ·  Subject: {subject}  ·  résumé.pdf attached\n\"Dear {dear}, … Sincerely, {user}\"\n{handed}"})
        else:
            self._send({"ok": True})

print("verdant_server: advice + spellcheck + grammar + LibreOffice + Hummingbird, serving 127.0.0.1:8078", flush=True)
HTTPServer(("127.0.0.1", 8078), H).serve_forever()
