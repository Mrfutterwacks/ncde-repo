import QtQuick
import QtQuick.Window
import QtQuick.Controls
// standalone: VerdantKit in same dir (no shell parent import)

// VerdantFolio — NCDE's résumé atelier, host GiGi (a peacock). NO LLM.
// User-facing: spell check, grammar check, resume editor.
// GiGi's internal: career library, thesaurus, dictionary, grammar rules.
Window {
    id: win
    width: 1280; height: 820
    visible: true
    color: k.panelBg
    title: "VerdantFolio"
    Component.onCompleted: { requestActivate(); bubbleMsg = "Welcome to the atelier, darlin'. Fill in your story on the left — I'll set it on the page as you go. Press “Check” and I'll catch any spelling or grammar slips." }

    VerdantKit { id: k }

    // ── Iris Chroma palette ──
    readonly property color iris0:   k.inkDim
    readonly property color iris1:   k.surface2
    readonly property color iris2:   k.surface
    readonly property color iris3:   k.surfaceHi
    readonly property color irisInk: k.ink
    readonly property color irisGold: k.gilt4
    readonly property color irisGoldSoft: k.gilt0
    readonly property color irisAccent: k.accent
    readonly property color irisAccentSoft: k.accentSoft
    readonly property color irisPaper: k.surfaceHi
    readonly property color irisPaperEdge: k.gilt0

    readonly property string serif: "Georgia"
    readonly property string sans: "DejaVu Sans"

    // ── Weak word library (GiGi's internal) ──
    readonly property var weakWords: ({
        "helped": "drove", "responsible for": "owned", "worked on": "led", "did": "executed",
        "made": "built", "used": "leveraged", "good": "proven", "a lot of": "extensive",
        "stuff": "initiatives", "things": "deliverables", "talked to": "advised",
        "in charge of": "directed", "handled": "managed", "worked with": "collaborated with",
        "was responsible": "spearheaded", "helped with": "facilitated", "assisted": "enabled",
        "part of": "integral to", "member of": "key contributor to", "joined": "launched",
        "started": "initiated", "ran": "operated", "kept": "maintained", "found": "identified",
        "fixed": "resolved", "changed": "transformed", "improved": "optimized", "learned": "mastered"
    })

    // ── State ──
    property var findings: []
    property int fIdx: -1
    property string bubbleMsg: ""
    property bool bubbleWord: fIdx >= 0 && fIdx < findings.length
    property bool matchOpen: false
    property bool sendOpen: false
    property int templateIndex: 0
    readonly property var templates: ["Chronological", "Functional", "Combination"]
    property var spellErrors: []
    property var grammarErrors: []

    // ── Resume data model ──
    property string rName: ""
    property string rHeadline: ""
    property string rEmail: ""
    property string rPhone: ""
    property string rLocation: ""
    property string rSummary: ""
    property string rEducation: ""
    property var rExperience: []
    property string rSkillsTech: ""
    property string rSkillsSoft: ""
    property string rSkillsLang: ""

    // ── HTTP helper ──
    function _get(path, callback) {
        var x = new XMLHttpRequest();
        x.onreadystatechange = function() { if (x.readyState === 4 && x.status === 200) { callback(JSON.parse(x.responseText)); } };
        x.open("GET", "http://127.0.0.1:8078" + path); x.send();
    }
    function _post(path, payload) {
        status.text = "Working…";
        var x = new XMLHttpRequest();
        x.onreadystatechange = function() { if (x.readyState === 4) { var s = "(no response)"; if (x.status === 200) { try { s = JSON.parse(x.responseText).status; } catch (e) {} } status.text = s; } };
        x.open("POST", "http://127.0.0.1:8078" + path); x.setRequestHeader("Content-Type", "application/json"); x.send(payload);
    }

    function _advise() {
        _get("/advice?headline=" + encodeURIComponent(rHeadline), function(data) {
            status.text = "GiGi's tip: " + data.gigi;
        });
    }

    function _resume(extra) {
        var r = {
            "name": rName, "headline": rHeadline, "email": rEmail,
            "phone": rPhone, "location": rLocation, "summary": rSummary,
            "education": rEducation, "experience": rExperience,
            "skills_tech": rSkillsTech, "skills_soft": rSkillsSoft, "skills_lang": rSkillsLang,
            "template": templates[templateIndex]
        };
        if (extra) for (var key in extra) r[key] = extra[key];
        return JSON.stringify(r);
    }

    // ── Spell check ──
    function _spellcheck() {
        var text = rSummary + " " + rSkillsTech + " " + rSkillsSoft + " " + rSkillsLang + " " + JSON.stringify(rExperience);
        _get("/spellcheck?text=" + encodeURIComponent(text), function(data) {
            spellErrors = data.errors;
            if (data.errors.length === 0) {
                gigi.play("cheer"); bubbleMsg = "Not a single misspelling, darlin'. Your résumé is clean as a whistle. ✨";
            } else {
                gigi.play("tilt"); bubbleMsg = "Found " + data.errors.length + " spelling " + (data.errors.length === 1 ? "slip" : "slips") + ", sugar. Let's fix them one by one.";
                findings = data.errors.map(function(e) { return e.word; });
                fIdx = -1;
                _nextSpell();
            }
        });
    }
    function _nextSpell() {
        fIdx += 1;
        if (fIdx >= findings.length) { gigi.play("cheer"); bubbleMsg = "All spelling fixed, darlin'. Looking sharp! ✨"; return; }
        var err = spellErrors[fIdx];
        bubbleMsg = "" + err.word + " doesn't look right, sugar — did you mean " + (err.suggestion || "…") + "?"
    }
    function _applySpell() {
        if (fIdx < 0 || fIdx >= spellErrors.length) return;
        var err = spellErrors[fIdx];
        if (!err.suggestion) { _nextSpell(); return; }
        var re = new RegExp("\\b" + err.word + "\\b", "gi");
        rSummary = rSummary.replace(re, err.suggestion);
        rSkillsTech = rSkillsTech.replace(re, err.suggestion);
        rSkillsSoft = rSkillsSoft.replace(re, err.suggestion);
        rSkillsLang = rSkillsLang.replace(re, err.suggestion);
        for (var i = 0; i < rExperience.length; i++) {
            rExperience[i].description = rExperience[i].description.replace(re, err.suggestion);
        }
        _nextSpell();
    }

    // ── Grammar check ──
    function _grammarCheck() {
        var text = rSummary + " " + JSON.stringify(rExperience);
        _get("/grammar?text=" + encodeURIComponent(text), function(data) {
            grammarErrors = data.errors;
            if (data.errors.length === 0) {
                gigi.play("cheer"); bubbleMsg = "Grammar's clean, darlin'. Not a comma out of place. ✨";
            } else {
                gigi.play("tilt"); bubbleMsg = "Found " + data.errors.length + " grammar " + (data.errors.length === 1 ? "hiccup" : "hiccups") + ", sugar. Let's smooth them out.";
                findings = data.errors.map(function(e) { return e.word; });
                fIdx = -1;
                _nextGrammar();
            }
        });
    }
    function _nextGrammar() {
        fIdx += 1;
        if (fIdx >= findings.length) { gigi.play("cheer"); bubbleMsg = "All grammar fixed, darlin'. Smooth as silk! ✨"; return; }
        var err = grammarErrors[fIdx];
        bubbleMsg = err.description + ": “" + err.word + "” → " + err.suggestion;
    }
    function _applyGrammar() {
        if (fIdx < 0 || fIdx >= grammarErrors.length) return;
        var err = grammarErrors[fIdx];
        var re = new RegExp(err.word.replace(/[.*+?^${}()|[\]\\]/g, '\\$&'), "gi");
        rSummary = rSummary.replace(re, err.suggestion);
        for (var i = 0; i < rExperience.length; i++) {
            rExperience[i].description = rExperience[i].description.replace(re, err.suggestion);
        }
        _nextGrammar();
    }

    // ── GiGi's polish scan (weak words) ──
    function _scan() {
        gigi.play("fan");
        _advise();
        var hay = (rSummary + " " + JSON.stringify(rExperience)).toLowerCase();
        var found = [];
        for (var w in weakWords) if (hay.indexOf(w) !== -1) found.push(w);
        findings = found; fIdx = -1;
        if (found.length === 0) { gigi.play("cheer"); bubbleMsg = "Looking sharp, darlin' — not a timid word in sight. ✨"; }
        else _next();
    }
    function _next() {
        fIdx += 1;
        if (fIdx >= findings.length) { gigi.play("cheer"); bubbleMsg = "That's the lot, sugar — much stronger now. ✨"; return; }
        var w = findings[fIdx];
        bubbleMsg = "" + w + " is a touch timid, darlin' — try " + weakWords[w] + "."
    }
    function _apply() {
        if (!bubbleWord) return;
        var w = findings[fIdx], s = weakWords[w];
        var re = new RegExp(w, "i");
        rSummary = rSummary.replace(re, s);
        for (var i = 0; i < rExperience.length; i++) {
            rExperience[i].description = rExperience[i].description.replace(re, s);
        }
        _next();
    }

    // ── Job matching ──
    function _match(job) {
        var STOP = "the a an and or to of in for with on is are be you your our we will work team role job position company experience years ability strong skills able must should have has this that they their".split(" ");
        var words = job.toLowerCase().match(/[a-z][a-z+#.]{3,}/g) || [];
        var seen = ({}), kws = [];
        for (var i = 0; i < words.length; i++) { var kw = words[i]; if (STOP.indexOf(kw) === -1 && !seen[kw]) { seen[kw] = 1; kws.push(kw); } }
        var folio = (rSummary + " " + JSON.stringify(rExperience) + " " + rSkillsTech + " " + rSkillsSoft + " " + rHeadline).toLowerCase();
        var hit = [], miss = [];
        for (var j = 0; j < kws.length; j++) (folio.indexOf(kws[j]) !== -1 ? hit : miss).push(kws[j]);
        bubbleMsg = "Cross-referenced, darlin'. You already hit: " + (hit.slice(0, 8).join(", ") || "—")
                  + ". Missing from your folio: " + (miss.slice(0, 8).join(", ") || "nothing!") + " — weave those in, sugar.";
        matchOpen = false;
    }

    // ── Experience entry management ──
    function addExperience() {
        rExperience.push({ title: "", company: "", start: "", end: "", description: "" });
        rExperience = rExperience.slice();
    }
    function removeExperience(idx) {
        rExperience.splice(idx, 1);
        rExperience = rExperience.slice();
    }

    // ── Self-contained field component ──
    component Field: Column {
        id: fld
        property alias text: ti.text
        property string label: ""
        property string hint: ""
        property real boxH: 36
        width: parent.width; spacing: 4
        VerdantKit { id: fk }
        Text { text: fld.label; color: fk.gilt4; font.family: "DejaVu Sans"; font.pixelSize: 11; font.letterSpacing: 1 }
        Rectangle { width: parent.width; height: fld.boxH; color: fk.surface2; border.color: fk.gilt0; radius: 4
            TextEdit { id: ti; x: 9; y: 7; width: parent.width - 18; height: parent.height - 14; color: fk.ink; font.family: "DejaVu Sans"; font.pixelSize: 14; wrapMode: TextEdit.Wrap; selectByMouse: true }
            Text { visible: ti.text === ""; x: 11; y: 8; text: fld.hint; color: fk.inkDim; font.italic: true; font.family: "DejaVu Sans"; font.pixelSize: 13 }
        }
    }

    component ExpEntry: Column {
        id: ee
        property alias title: tiTitle.text
        property alias company: tiCompany.text
        property alias start: tiStart.text
        property alias end: tiEnd.text
        property alias description: tiDesc.text
        property int index: 0
        width: parent.width; spacing: 6
        VerdantKit { id: ek }
        Rectangle { width: parent.width; color: ek.surface2; border.color: ek.gilt0; radius: 6
            Column { x: 14; y: 10; width: parent.width - 28; spacing: 6
                Row { spacing: 8
                    Column { width: 180; spacing: 3
                        Text { text: "JOB TITLE"; color: ek.gilt4; font.pixelSize: 10; font.family: "DejaVu Sans" }
                        Rectangle { width: parent.width; height: 32; color: ek.surface; border.color: ek.gilt0; radius: 3
                            TextInput { id: tiTitle; anchors.fill: parent; anchors.margins: 7; color: ek.ink; font.family: "DejaVu Sans"; font.pixelSize: 13; selectByMouse: true } } }
                    Column { width: 180; spacing: 3
                        Text { text: "COMPANY"; color: ek.gilt4; font.pixelSize: 10; font.family: "DejaVu Sans" }
                        Rectangle { width: parent.width; height: 32; color: ek.surface; border.color: ek.gilt0; radius: 3
                            TextInput { id: tiCompany; anchors.fill: parent; anchors.margins: 7; color: ek.ink; font.family: "DejaVu Sans"; font.pixelSize: 13; selectByMouse: true } } }
                    Column { width: 90; spacing: 3
                        Text { text: "FROM"; color: ek.gilt4; font.pixelSize: 10; font.family: "DejaVu Sans" }
                        Rectangle { width: parent.width; height: 32; color: ek.surface; border.color: ek.gilt0; radius: 3
                            TextInput { id: tiStart; anchors.fill: parent; anchors.margins: 7; color: ek.ink; font.family: "DejaVu Sans"; font.pixelSize: 13; selectByMouse: true } } }
                    Column { width: 90; spacing: 3
                        Text { text: "TO"; color: ek.gilt4; font.pixelSize: 10; font.family: "DejaVu Sans" }
                        Rectangle { width: parent.width; height: 32; color: ek.surface; border.color: ek.gilt0; radius: 3
                            TextInput { id: tiEnd; anchors.fill: parent; anchors.margins: 7; color: ek.ink; font.family: "DejaVu Sans"; font.pixelSize: 13; selectByMouse: true } } }
                    Rectangle { width: 32; height: 32; radius: 4; color: "transparent"; border.color: ek.gilt0
                        anchors.verticalCenter: parent.verticalCenter
                        Text { anchors.centerIn: parent; text: "✕"; color: ek.inkDim; font.pixelSize: 14 }
                        MouseArea { anchors.fill: parent; onClicked: win.removeExperience(ee.index) } } }
                Column { spacing: 3
                    Text { text: "DESCRIPTION (one achievement per line)"; color: ek.gilt4; font.pixelSize: 10; font.family: "DejaVu Sans" }
                    Rectangle { width: parent.width; height: 72; color: ek.surface; border.color: ek.gilt0; radius: 3
                        TextEdit { id: tiDesc; anchors.fill: parent; anchors.margins: 7; color: ek.ink; font.family: "DejaVu Sans"; font.pixelSize: 13; wrapMode: TextEdit.Wrap; selectByMouse: true } } }
            } }
    }

    // ── Header ──
    Rectangle { id: header; width: parent.width; height: 62; color: iris2
        Text { x: 24; anchors.verticalCenter: parent.verticalCenter; text: "❖ VerdantFolio"; color: irisGold; font.family: serif; font.pixelSize: 25; font.bold: true }
        Text { x: 232; anchors.verticalCenter: parent.verticalCenter; text: "Résumé Atelier"; color: iris0; font.family: serif; font.italic: true; font.pixelSize: 16 }
        Text { anchors.right: parent.right; anchors.rightMargin: 22; anchors.verticalCenter: parent.verticalCenter; text: "GiGi 🦚"; color: iris0; font.family: sans; font.pixelSize: 14 }
        Rectangle { anchors.right: parent.right; anchors.rightMargin: 96; anchors.verticalCenter: parent.verticalCenter; width: 122; height: 30; radius: 5; color: mb.containsMouse ? iris3 : iris1; border.color: irisGold
            Text { anchors.centerIn: parent; text: "🔍 MATCH a job"; color: irisGold; font.family: sans; font.pixelSize: 11 }
            MouseArea { id: mb; anchors.fill: parent; hoverEnabled: true; onClicked: win.matchOpen = true } }
        Rectangle { width: parent.width; height: 2; anchors.bottom: parent.bottom; color: irisGold; opacity: 0.5 }
    }

    // ── Form panel (left) ──
    Flickable { id: form; x: 0; y: header.height; width: 520; height: parent.height - header.height - footer.height; clip: true
        contentHeight: formCol.height + 30
        Column { id: formCol; x: 20; y: 16; width: parent.width - 40; spacing: 10

            // Template selector
            Column { spacing: 4
                Text { text: "TEMPLATE"; color: irisGold; font.family: sans; font.pixelSize: 11; font.letterSpacing: 1 }
                Row { spacing: 6
                    Repeater { model: win.templates
                        delegate: Rectangle { width: 130; height: 30; radius: 4; color: win.templateIndex === index ? irisAccent : iris1; border.color: win.templateIndex === index ? irisAccent : irisGoldSoft
                            Text { anchors.centerIn: parent; text: modelData; color: win.templateIndex === index ? "#fff" : irisInk; font.family: sans; font.pixelSize: 11 }
                            MouseArea { anchors.fill: parent; onClicked: win.templateIndex = index } } } } }

            Field { id: fName; label: "FULL NAME"; hint: "Jane Q. Applicant"; onTextChanged: rName = text }
            Field { id: fHead; label: "HEADLINE"; hint: "Office Administrator · 10 years"; onTextChanged: rHeadline = text }
            Field { id: fEmail; label: "EMAIL"; hint: "jane@example.com"; onTextChanged: rEmail = text }
            Field { id: fPhone; label: "PHONE"; hint: "(217) 555-0190"; onTextChanged: rPhone = text }
            Field { id: fLocation; label: "LOCATION"; hint: "Springfield, IL"; onTextChanged: rLocation = text }
            Field { id: fSummary; label: "PROFESSIONAL SUMMARY"; hint: "A sentence or two about you."; boxH: 76; onTextChanged: rSummary = text }
            Field { id: fEducation; label: "EDUCATION"; hint: "Degree — School — Year"; boxH: 46; onTextChanged: rEducation = text }

            // Experience entries
            Column { spacing: 6; width: parent.width
                Row { spacing: 8
                    Text { text: "EXPERIENCE"; color: irisGold; font.family: sans; font.pixelSize: 11; font.letterSpacing: 1; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle { width: 100; height: 26; radius: 4; color: iris1; border.color: irisGold
                        anchors.verticalCenter: parent.verticalCenter
                        Text { anchors.centerIn: parent; text: "+ Add entry"; color: irisGold; font.family: sans; font.pixelSize: 10 }
                        MouseArea { anchors.fill: parent; onClicked: win.addExperience() } } }
                Repeater { model: win.rExperience
                    delegate: ExpEntry { index: modelData.index } } }

            // Skills
            Column { spacing: 4; width: parent.width
                Text { text: "SKILLS"; color: irisGold; font.family: sans; font.pixelSize: 11; font.letterSpacing: 1 }
                Field { id: fSkillsTech; label: "TECHNICAL"; hint: "Python, Git, SQL…"; boxH: 40; onTextChanged: rSkillsTech = text }
                Field { id: fSkillsSoft; label: "SOFT SKILLS"; hint: "Leadership, communication…"; boxH: 40; onTextChanged: rSkillsSoft = text }
                Field { id: fSkillsLang; label: "LANGUAGES"; hint: "English, Spanish…"; boxH: 40; onTextChanged: rSkillsLang = text }
            }
        }
    }

    // ── Preview panel (right) ──
    Rectangle { x: 520; y: header.height; width: parent.width - 520; height: parent.height - header.height; color: iris2
        Rectangle { anchors.fill: parent; anchors.margins: 20; anchors.rightMargin: 200; color: irisPaper; radius: 8
            Rectangle { anchors.fill: parent; color: irisPaperEdge; radius: 8; opacity: 0.3 }
            Flickable { anchors.fill: parent; anchors.margins: 40; contentHeight: prevCol.height; clip: true
                Column { id: prevCol; width: parent.width; spacing: 8
                    Text { text: rName !== "" ? rName : "Your Name"; color: irisInk; font.family: serif; font.pixelSize: 32; font.bold: true }
                    Text { visible: rHeadline !== ""; text: rHeadline; color: iris0; font.family: serif; font.italic: true; font.pixelSize: 16 }
                    Text { text: (rEmail !== "" ? rEmail : "your@email") + "   ·   " + (rPhone !== "" ? rPhone : "your phone") + (rLocation !== "" ? "   ·   " + rLocation : ""); color: irisInk; font.family: sans; font.pixelSize: 12 }
                    Rectangle { width: parent.width; height: 1; color: irisGold; opacity: 0.6 }
                    Text { visible: rSummary !== ""; width: parent.width; wrapMode: Text.WordWrap; text: rSummary; color: irisInk; font.family: serif; font.pixelSize: 14; lineHeight: 1.4 }
                    Text { visible: rExperience.length > 0; text: "EXPERIENCE"; color: irisGold; font.family: sans; font.pixelSize: 12; font.bold: true }
                    Repeater { model: win.rExperience
                        delegate: Column { width: parent.width; spacing: 2
                            Text { text: (title !== "" ? title : "Job Title") + " — " + (company !== "" ? company : "Company"); color: irisInk; font.family: serif; font.pixelSize: 14; font.bold: true }
                            Text { visible: start !== "" || end !== ""; text: (start !== "" ? start : "???") + " – " + (end !== "" ? end : "Present"); color: iris0; font.family: sans; font.pixelSize: 11 }
                            Text { visible: description !== ""; width: parent.width; wrapMode: Text.WordWrap; text: description; color: irisInk; font.family: serif; font.pixelSize: 13; lineHeight: 1.3 } } }
                    Text { visible: rEducation !== ""; text: "EDUCATION"; color: irisGold; font.family: sans; font.pixelSize: 12; font.bold: true }
                    Text { visible: rEducation !== ""; width: parent.width; wrapMode: Text.WordWrap; text: rEducation; color: irisInk; font.family: serif; font.pixelSize: 13 }
                    Text { visible: rSkillsTech !== "" || rSkillsSoft !== "" || rSkillsLang !== ""; text: "SKILLS"; color: irisGold; font.family: sans; font.pixelSize: 12; font.bold: true }
                    Text { visible: rSkillsTech !== ""; text: "Technical: " + rSkillsTech; color: irisInk; font.family: sans; font.pixelSize: 12 }
                    Text { visible: rSkillsSoft !== ""; text: "Soft: " + rSkillsSoft; color: irisInk; font.family: sans; font.pixelSize: 12 }
                    Text { visible: rSkillsLang !== ""; text: "Languages: " + rSkillsLang; color: irisInk; font.family: sans; font.pixelSize: 12 }
                }
            }
        }
    }

    // ── Match panel ──
    Rectangle { id: matchPanel; visible: win.matchOpen
        x: 520; y: header.height; width: parent.width - 520; height: parent.height - header.height; color: k.panelBg
        Column { x: 30; y: 24; width: parent.width - 60; spacing: 12
            Text { width: parent.width; wrapMode: Text.WordWrap; text: "Paste the job posting, darlin' — I'll cross-reference every word against your folio."; color: iris0; font.family: serif; font.italic: true; font.pixelSize: 14 }
            Rectangle { width: parent.width; height: 300; color: k.panelBg2; border.color: k.gilt0; radius: 4
                Flickable { anchors.fill: parent; anchors.margins: 8; contentHeight: jt.implicitHeight; clip: true
                    TextEdit { id: jt; width: parent.width; color: k.ink; font.family: sans; font.pixelSize: 13; wrapMode: TextEdit.Wrap; selectByMouse: true } } }
            Row { spacing: 10
                Rectangle { width: 160; height: 36; radius: 5; color: k.surface2; border.color: irisGold
                    Text { anchors.centerIn: parent; text: "Cross-reference"; color: k.ink; font.family: sans; font.pixelSize: 13 }
                    MouseArea { anchors.fill: parent; onClicked: win._match(jt.text) } }
                Rectangle { width: 90; height: 36; radius: 5; color: "transparent"; border.color: irisGold
                    Text { anchors.centerIn: parent; text: "Close"; color: irisGold; font.family: sans; font.pixelSize: 13 }
                    MouseArea { anchors.fill: parent; onClicked: win.matchOpen = false } } } }
    }

    // ── Send panel ──
    Rectangle { id: sendPanel; visible: win.sendOpen
        x: 520; y: header.height; width: parent.width - 520; height: parent.height - header.height; color: k.panelBg
        Column { x: 30; y: 30; width: parent.width - 60; spacing: 14
            Text { width: parent.width; wrapMode: Text.WordWrap; text: "I'll attach your résumé and write the note, darlin'. Who's it going to?"; color: iris0; font.family: serif; font.italic: true; font.pixelSize: 14 }
            Text { text: "SEND TO (job email)"; color: irisGold; font.family: sans; font.pixelSize: 11 }
            Rectangle { width: parent.width; height: 36; color: k.panelBg2; border.color: k.gilt0; radius: 4
                TextInput { id: toEmail; anchors.fill: parent; anchors.margins: 9; color: k.ink; font.family: sans; font.pixelSize: 14; selectByMouse: true } }
            Text { text: "DEAR… (hiring contact's name)"; color: irisGold; font.family: sans; font.pixelSize: 11 }
            Rectangle { width: parent.width; height: 36; color: k.panelBg2; border.color: k.gilt0; radius: 4
                TextInput { id: toName; anchors.fill: parent; anchors.margins: 9; color: k.ink; font.family: sans; font.pixelSize: 14; selectByMouse: true } }
            Row { spacing: 10
                Rectangle { width: 250; height: 38; radius: 5; color: k.surface2; border.color: irisGold
                    Text { anchors.centerIn: parent; text: "Compose & hand to Hummingbird 🕊"; color: k.ink; font.family: sans; font.pixelSize: 11 }
                    MouseArea { anchors.fill: parent; onClicked: { win.sendOpen = false; win._post("/send", win._resume({"job_email": toEmail.text, "recipient_name": toName.text})); } } }
                Rectangle { width: 80; height: 38; radius: 5; color: "transparent"; border.color: irisGold
                    Text { anchors.centerIn: parent; text: "Close"; color: irisGold; font.family: sans; font.pixelSize: 13 }
                    MouseArea { anchors.fill: parent; onClicked: win.sendOpen = false } } } }
    }

    // ── GiGi herself (2026-09-29) — cel-animated like Binnie; see GigiCanvas.qml.
    // Stands in her own lane right of the paper, feet on the panel floor; her
    // speech bubble hangs from above her head.
    GigiCanvas { id: gigi
        width: 180; height: implicitHeight
        anchors.right: parent.right; anchors.rightMargin: 10
        anchors.bottom: parent.bottom; anchors.bottomMargin: 14
    }
    onBubbleMsgChanged: if (bubbleMsg !== "") gigi.say()

    // ── GiGi's bubble (glass + bezel + ShellLight shine) ──
    Rectangle { id: bubble
        visible: win.bubbleMsg !== ""
        anchors.right: parent.right; anchors.rightMargin: 16
        anchors.bottom: gigi.top; anchors.bottomMargin: 6
        width: 372; height: bcol.implicitHeight + 24
        radius: 14
        color: Qt.rgba(0.98, 0.95, 0.85, 0.92)
        border.color: irisGold; border.width: 1.5
        Rectangle { anchors.fill: parent; radius: 14
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.25) }
                GradientStop { position: 0.3; color: Qt.rgba(1, 1, 1, 0.05) }
                GradientStop { position: 1.0; color: Qt.rgba(0, 0, 0, 0.08) }
            } }
        Rectangle { anchors.fill: parent; anchors.margins: 1; radius: 13; color: "transparent"; border.color: irisGoldSoft; border.width: 0.5; opacity: 0.6 }
        Column { id: bcol; x: 14; y: 12; width: parent.width - 28; spacing: 9
            Text { text: "🦚  GiGi"; color: iris2; font.family: serif; font.bold: true; font.pixelSize: 13 }
            Text { width: parent.width; wrapMode: Text.WordWrap; text: win.bubbleMsg; color: "#3a3320"; font.family: serif; font.pixelSize: 14 }
            Row { spacing: 8; visible: win.bubbleWord
                Rectangle { width: 84; height: 28; radius: 4; color: k.surface2; border.color: k.gilt0
                    Text { anchors.centerIn: parent; text: "Apply"; color: k.ink; font.pixelSize: 12; font.family: sans }
                    MouseArea { anchors.fill: parent; onClicked: win._apply() } }
                Rectangle { width: 70; height: 28; radius: 4; color: "transparent"; border.color: irisGold
                    Text { anchors.centerIn: parent; text: "Skip"; color: irisGold; font.pixelSize: 12; font.family: sans }
                    MouseArea { anchors.fill: parent; onClicked: win._next() } } } }
        Text { anchors.right: parent.right; anchors.top: parent.top; anchors.margins: 7; text: "✕"; color: "#9a8b5a"; font.pixelSize: 13
            MouseArea { anchors.fill: parent; anchors.margins: -6; onClicked: win.bubbleMsg = "" } }
    }

    // ── Status + Footer ──
    Text { id: status; x: 22; width: 476; anchors.bottom: footer.top; anchors.bottomMargin: 5; wrapMode: Text.WordWrap; color: irisGold; font.family: sans; font.pixelSize: 12; text: "" }
    // footer (2026-09-29): was anchored to `parent.parent` — not an anchor line — so it
    // sat at y=0 over the header; and 736px of buttons overflowed its 520px. Flow wraps.
    Flow { id: footer; x: 16; anchors.bottom: parent.bottom; spacing: 10; bottomPadding: 12; topPadding: 10; width: 488
        Rectangle { width: 150; height: 36; radius: 5; color: pol.containsMouse ? iris3 : iris1; border.color: irisGold
            Text { anchors.centerIn: parent; text: "GiGi, polish ✨"; color: k.ink; font.pixelSize: 13; font.family: sans }
            MouseArea { id: pol; anchors.fill: parent; hoverEnabled: true; onClicked: win._scan() } }
        Rectangle { width: 132; height: 36; radius: 5; color: sp.containsMouse ? iris3 : iris1; border.color: irisGold
            Text { anchors.centerIn: parent; text: "Spell Check"; color: k.ink; font.pixelSize: 13; font.family: sans }
            MouseArea { id: sp; anchors.fill: parent; hoverEnabled: true; onClicked: win._spellcheck() } }
        Rectangle { width: 132; height: 36; radius: 5; color: gr.containsMouse ? iris3 : iris1; border.color: irisGold
            Text { anchors.centerIn: parent; text: "Grammar Check"; color: k.ink; font.pixelSize: 13; font.family: sans }
            MouseArea { id: gr; anchors.fill: parent; hoverEnabled: true; onClicked: win._grammarCheck() } }
        Rectangle { width: 132; height: 36; radius: 5; color: exp.containsMouse ? iris3 : iris1; border.color: k.gilt0
            Text { anchors.centerIn: parent; text: "Export → LibreOffice"; color: k.inkSoft; font.pixelSize: 11; font.family: sans }
            MouseArea { id: exp; anchors.fill: parent; hoverEnabled: true; onClicked: win._post("/export", win._resume({"format": "open"})) } }
        Rectangle { width: 150; height: 36; radius: 5; color: snd.containsMouse ? iris3 : iris1; border.color: k.gilt0
            Text { anchors.centerIn: parent; text: "Save & Send"; color: k.inkSoft; font.pixelSize: 13; font.family: sans }
            MouseArea { id: snd; anchors.fill: parent; hoverEnabled: true; onClicked: win.sendOpen = true } }
    }
}
