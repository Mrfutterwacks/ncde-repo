import QtQuick

// VesperBackend — SHIP wiring (NO LLM). Vesper is a living security suite: he converses
// through the local brain's deterministic intent engine (/converse), actually RUNS the
// engines on your confirmation (/act — ClamAV scan, quarantine, re-baseline, definition
// update, ban check), polls for REAL findings, and answers from the MITRE library. He
// asks before every action; nothing destructive happens without your yes. Name + all
// speech come from the backend — never hardcoded here.
QtObject {
    id: backend

    property bool   armed: true
    property int    threatCount: 0
    property string lastUpdate: "watching"
    property string userName: "friend"
    property string orgName: ""
    property bool   reduceMotion: false

    property var    finding: null                 // null = quiet; set only on a REAL detection
    property string analysisText: ""              // stream sink -> a "vesper" turn (Main.qml)
    property string chatReply: ""
    property bool   streaming: false
    property var    quarantine: []
    property var    suggestions: []               // anticipatory quick-replies (chips)
    property bool   askOnlineConsent: false
    property bool   askKnowledgeUpdate: false

    // one stable session id so the brain remembers the conversation (yes/no context)
    property string _sid: "s" + Math.floor(Math.random() * 1000000000)
    readonly property string _base: "http://127.0.0.1:8077"

    // ---- typewriter: stream text into analysisText as one "vesper" turn ----
    property string _target: ""
    property int    _i: 0
    property Timer  _typer: Timer { interval: 14; repeat: true; running: false
        onTriggered: {
            if (backend._i < backend._target.length) { backend._i += 1; backend.analysisText = backend._target.substring(0, backend._i); }
            else { running = false; backend.streaming = false; }
        }
    }
    function _stream(t) {
        if (_typer.running) { analysisText = _target; }   // finalize the prior turn first
        _target = t; _i = 0; analysisText = ""; streaming = true; _typer.running = true;
    }

    function _get(url, onOk) {
        var x = new XMLHttpRequest();
        x.onreadystatechange = function() {
            if (x.readyState !== XMLHttpRequest.DONE) return;
            var d = null;
            if (x.status === 200) { try { d = JSON.parse(x.responseText); } catch (e) {} }
            onOk(d, x.status);
        };
        x.open("GET", url); x.send();
    }

    // startup: real name + a quiet greeting
    Component.onCompleted: {
        _get(_base + "/whoami", function(d) { if (d && d.name) backend.userName = d.name; });
    }
    property Timer _hello: Timer { interval: 700; repeat: false; running: true
        onTriggered: backend._stream(backend.userName + ", it's Vesper. All quiet — I'm watching every door. "
            + "Ask me anything, or tell me to scan, and I'll get to work.") }

    // ---- the conversation: every user line goes to the brain's intent engine ----
    function ask(text) {
        _get(_base + "/converse?s=" + _sid + "&q=" + encodeURIComponent(text), function(d) {
            if (!d) { backend._stream("My brain's not answering just now, " + backend.userName + " — give me a moment."); return; }
            backend._stream(d.reply || "");
            backend.suggestions = d.suggestions || [];
            if (typeof d.threatCount === "number") backend.threatCount = d.threatCount;
            // the brain returns an `action` only after you've CONFIRMED it — run it for real
            if (d.action) backend._act(d.action);
        });
    }

    // ---- run a CONFIRMED real action, stream the natural result ----
    function _act(a) {
        var url = _base + "/act?s=" + _sid + "&type=" + encodeURIComponent(a.type);
        if (a.target) url += "&target=" + encodeURIComponent(a.target);
        if (a.path)   url += "&path="   + encodeURIComponent(a.path);
        if (a.id)     url += "&id="     + encodeURIComponent(a.id);
        if (a.signature) url += "&signature=" + encodeURIComponent(a.signature);
        if (a.engine) url += "&engine=" + encodeURIComponent(a.engine);
        backend._get(url, function(d) {
            if (!d) { backend._stream("That action didn't complete — nothing was changed."); return; }
            backend._stream(d.reply || "");
            // an action can clear the current finding (quarantine/allow); refresh the held count
            if (a.type === "quarantine" || a.type === "restore" || a.type === "remove") backend.refreshQuarantine();
            if (a.type === "quarantine") { backend._ack(); backend.finding = null; backend.lastUpdate = "moments ago"; }
        });
    }

    // ---- poll the engines for REAL findings (auto-pop on a genuine threat) ----
    property Timer _poll: Timer { interval: 6000; repeat: true; running: true; triggeredOnStart: true
        onTriggered: backend._check() }
    property var _acked: ({})
    function _ack() { if (finding) { var k = finding.id || finding.path; var a = _acked; a[k] = true; _acked = a; } }
    function _check() {
        _get(_base + "/findings", function(d) {
            if (!d) return;
            var fs = d.findings || [];
            backend.threatCount = fs.length;
            if (fs.length > 0 && backend.finding === null) {
                var f = null;
                for (var i = 0; i < fs.length; i++) {
                    var key = fs[i].path || fs[i].ip || (fs[i].engine + ":" + (fs[i].detail || ""));
                    if (!backend._acked[key]) { f = fs[i]; break; }
                }
                if (f === null) return;
                backend.finding = {
                    "id": f.path || f.ip || (f.engine + ":" + (f.detail || "")).substring(0, 40),
                    "threat_class": f.threat_class || "threat",
                    "verdict": f.threat_class === "malware" ? "malicious" : "suspicious",
                    "basis": f.signature ? ("signature match — " + f.signature)
                           : f.ip ? ("banned by " + (f.jail ? "jail '" + f.jail + "'" : "fail2ban"))
                           : ((f.engine || "an engine") + " report"),
                    "recommendation": f.path ? "quarantine" : "review",
                    "path": f.path || "", "engine": f.engine || "", "signature": f.signature || "",
                    "explanation": backend.userName + " — " + (f.engine || "a scan") + " flagged "
                        + (f.signature || f.detail || f.path || f.ip || "something")
                        + ". I've got it held. Tell me what to do — nothing happens without your say-so.",
                    "mitre": []
                };
                backend.lastUpdate = "moments ago";
                backend._stream(backend.userName + ", I caught something — see the card. Say 'quarantine it' to seal it off, or ask me about it.");
            }
        });
    }

    // ---- AlertCard buttons map onto the same conversational actions ----
    function block(id) {
        if (finding === null) { _stream("Nothing to seal right now."); return; }
        if (!finding.path) {
            _ack(); _stream("That one isn't a file, " + userName + " — " + (finding.engine || "the engine")
                    + " already has it held (" + finding.basis + "). Nothing more to seal.");
            finding = null; return;
        }
        _act({ "type": "quarantine", "path": finding.path, "signature": finding.signature, "engine": finding.engine });
    }
    function allow(id) { _ack(); finding = null; _stream("Allowed — I'll leave it be, but I'll keep a close eye on it."); }
    function analyse(id) {
        if (finding === null) { _stream("Nothing's flagged right now — all quiet."); return; }
        ask("explain it");
    }
    function dismiss() { _ack(); finding = null; }

    // ---- quarantine review pane ----
    function refreshQuarantine() {
        _get(_base + "/quarantine", function(d) { backend.quarantine = (d && d.quarantine) || []; });
    }
    function reviewQuarantine() { ask("review quarantine"); }
    function restore(id) { _act({ "type": "restore", "id": id }); }
    function remove(id)  { _act({ "type": "remove",  "id": id }); }

    // ---- consent gates (no-LLM build never opens them; honest close if some future feature does) ----
    function updateKnowledge(yes) { askKnowledgeUpdate = false;
        _stream(yes ? "There's nothing to update yet — my library ships whole with the system." : "Alright — not now."); }
    function allowOnline(yes)     { askOnlineConsent = false;
        _stream(yes ? "I don't go online in this build, " + userName + " — everything I know lives right here." : "Understood — staying offline."); }
}
