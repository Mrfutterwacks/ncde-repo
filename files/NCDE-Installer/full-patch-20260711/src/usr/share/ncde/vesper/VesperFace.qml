import QtQuick

// VesperFace — the phosphor cartoon, drawn procedurally on a Canvas so every part
// animates: idle float, blink, eye-darts, brow emotes, viseme mouth while speaking,
// turning brass gears, visor/core glow. Cyberpunk-meets-steampunk in green phosphor.
// Data-driven: set `speaking` true while tokens stream; motion obeys `reduceMotion`.
Item {
    id: face
    property color p:    "#5fffba"
    property color pHi:  "#c4ffe6"
    property color copper:"#7fffcf"
    property color ground:"#020608"
    property bool  speaking: false
    property bool  reduceMotion: false

    implicitWidth: 280; implicitHeight: 320

    // animated state
    property real t: 0
    property real blink: 0           // 0 open … 1 shut
    property real mouthV: 0          // viseme index phase
    property real pupilDX: 0
    property real pupilDY: 0
    property real browLift: 0

    Timer {  // master clock ~30fps
        interval: 33; running: true; repeat: true
        onTriggered: { face.t += 0.033; canvas.requestPaint(); }
    }
    // blink
    Timer {
        interval: 3600; running: true; repeat: true
        onTriggered: if (!face.reduceMotion && Math.random() < 0.75) blinkAnim.restart()
    }
    SequentialAnimation {
        id: blinkAnim
        NumberAnimation { target: face; property: "blink"; to: 1; duration: 70 }
        NumberAnimation { target: face; property: "blink"; to: 0; duration: 90 }
    }
    // eye darts (only when idle)
    Timer {
        interval: 2800; running: true; repeat: true
        onTriggered: {
            if (face.speaking || face.reduceMotion) return;
            if (Math.random() < 0.6) {
                dartX.to = (Math.random()*2-1)*5; dartY.to = (Math.random()*2-1)*3;
                dartX.restart(); dartY.restart();
                resetDart.restart();
            }
        }
    }
    NumberAnimation { id: dartX; target: face; property: "pupilDX"; duration: 220; easing.type: Easing.OutQuad }
    NumberAnimation { id: dartY; target: face; property: "pupilDY"; duration: 220; easing.type: Easing.OutQuad }
    Timer { id: resetDart; interval: 900; onTriggered: { face.pupilDX = 0; face.pupilDY = 0; } }
    // brow lift when he starts speaking
    onSpeakingChanged: if (speaking) { browAnim.restart() }
    SequentialAnimation {
        id: browAnim
        NumberAnimation { target: face; property: "browLift"; to: 3; duration: 180 }
        PauseAnimation { duration: 700 }
        NumberAnimation { target: face; property: "browLift"; to: 0; duration: 240 }
    }

    Canvas {
        id: canvas
        anchors.fill: parent
        renderTarget: Canvas.Image
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            var W = width, H = height;
            ctx.clearRect(0,0,W,H);
            ctx.save();
            ctx.translate(W/2, H/2);
            // idle float
            var fy = face.reduceMotion ? 0 : Math.sin(face.t * 1.25) * 5;
            ctx.translate(0, fy);
            ctx.translate(-140, -170);   // work in 280x320 design space

            ctx.lineCap = "round"; ctx.lineJoin = "round";
            ctx.shadowColor = face.p; ctx.shadowBlur = 6;

            function stroke(w, col){ ctx.lineWidth = w; ctx.strokeStyle = col || face.p; ctx.stroke(); }
            function path(d){ ctx.beginPath(); _svg(ctx, d); }

            // gears (rotate)
            var ga = face.reduceMotion ? 0 : face.t;
            drawGear(ctx, 58, 138, 20,  ga, face.copper);
            drawGear(ctx, 222,138, 20, -ga*0.8, face.copper);

            // collar / shoulders
            path("M64 300 C70 256 100 236 140 236 C180 236 210 256 216 300 Z"); stroke(2.5);
            // chest core glow
            ctx.beginPath(); ctx.arc(140,286,14,0,Math.PI*2);
            ctx.fillStyle = glowCol(0.4 + 0.2*Math.sin(face.t*2)); ctx.fill();
            ctx.beginPath(); ctx.arc(140,286,9,0,Math.PI*2); stroke(2.5);

            // head + cap
            path("M86 150 C86 206 110 234 140 234 C170 234 194 206 194 150 C194 120 172 104 140 104 C108 104 86 120 86 150 Z"); stroke(2.5);
            path("M78 132 C80 86 104 64 140 64 C176 64 200 86 202 132 C202 132 178 120 140 120 C102 120 78 132 78 132 Z"); stroke(2.5);
            path("M74 132 C100 122 180 122 206 132"); stroke(2.5);

            // goggles on cap (copper)
            ctx.beginPath(); ctx.arc(106,120,13,0,Math.PI*2); stroke(2.5, face.copper);
            ctx.beginPath(); ctx.arc(174,120,13,0,Math.PI*2); stroke(2.5, face.copper);
            path("M119 120 H161"); stroke(1.4, face.copper);

            // cyber visor band (glow)
            ctx.beginPath(); ctx.rect(92,150,96,12);
            ctx.fillStyle = glowCol(0.5 + 0.4*Math.sin(face.t*2.4)); ctx.fill();

            // eyes
            drawEye(ctx, 116); drawEye(ctx, 164);

            // brows
            ctx.save(); ctx.translate(0,-face.browLift);
            path("M98 132 C108 126 126 126 134 132"); stroke(2.5);
            path("M146 132 C154 126 172 126 182 132"); stroke(2.5);
            ctx.restore();

            // mouth viseme
            drawMouth(ctx);

            // antenna
            path("M140 64 L140 44"); stroke(1.4);
            ctx.beginPath(); ctx.arc(140,40,4,0,Math.PI*2);
            ctx.fillStyle = face.p; ctx.fill();

            ctx.restore();
        }

        function glowCol(a){ return Qt.rgba(0.37,1.0,0.73, Math.max(0,Math.min(1,a))); }

        function drawEye(ctx, cx){
            ctx.save();
            ctx.beginPath(); ctx.ellipse(cx-20,160-22,40,44);
            ctx.fillStyle = face.ground; ctx.fill(); ctx.lineWidth=2.5; ctx.strokeStyle=face.p; ctx.stroke();
            // pupil
            if (face.blink < 0.5) {
                ctx.beginPath(); ctx.arc(cx+face.pupilDX,162+face.pupilDY,7,0,Math.PI*2);
                ctx.fillStyle = face.p; ctx.fill();
            }
            // eyelid
            if (face.blink > 0.01) {
                ctx.beginPath(); ctx.ellipse(cx-20,160-22,40,44*face.blink);
                ctx.fillStyle = face.ground; ctx.fill(); ctx.lineWidth=2.5; ctx.strokeStyle=face.p; ctx.stroke();
            }
            ctx.restore();
        }

        function drawMouth(ctx){
            ctx.beginPath(); ctx.lineWidth=2.5; ctx.strokeStyle=face.p;
            if (!face.speaking) { _svg(ctx, "M120 198 Q140 206 160 198"); ctx.stroke(); return; }
            var shapes = [
                "M122 197 Q140 210 158 197 Q140 205 122 197",
                "M118 196 Q140 216 162 196 Q140 208 118 196",
                "M132 198 Q140 195 148 198 Q150 207 140 209 Q130 207 132 198",
                "M122 200 H158"
            ];
            var idx = Math.floor(face.t*9) % shapes.length;
            _svg(ctx, shapes[idx]); ctx.stroke();
        }

        function drawGear(ctx, cx, cy, r, ang, col){
            ctx.save(); ctx.translate(cx,cy); ctx.rotate(ang);
            ctx.strokeStyle = col; ctx.lineWidth = 1.4;
            ctx.beginPath(); ctx.arc(0,0,r,0,Math.PI*2); ctx.stroke();
            ctx.beginPath(); ctx.arc(0,0,9,0,Math.PI*2); ctx.stroke();
            for (var i=0;i<8;i++){ var a=i*Math.PI/4;
                ctx.beginPath();
                ctx.moveTo(Math.cos(a)*r, Math.sin(a)*r);
                ctx.lineTo(Math.cos(a)*(r+6), Math.sin(a)*(r+6)); ctx.stroke(); }
            ctx.restore();
        }

        // minimal SVG-path 'd' executor: supports M L H V Q Z (abs)
        function _svg(ctx, d){
            var toks = d.match(/[A-Za-z]|-?\d*\.?\d+/g); if(!toks) return;
            var i=0, x=0, y=0, cmd="";
            function num(){ return parseFloat(toks[i++]); }
            while(i < toks.length){
                var tk = toks[i];
                if (/[A-Za-z]/.test(tk)) { cmd = tk; i++; }
                switch(cmd){
                    case "M": x=num(); y=num(); ctx.moveTo(x,y); break;
                    case "L": x=num(); y=num(); ctx.lineTo(x,y); break;
                    case "H": x=num(); ctx.lineTo(x,y); break;
                    case "V": y=num(); ctx.lineTo(x,y); break;
                    case "Q": { var cx=num(), cy=num(); x=num(); y=num(); ctx.quadraticCurveTo(cx,cy,x,y); break; }
                    case "C": { var c1x=num(),c1y=num(),c2x=num(),c2y=num(); x=num(); y=num(); ctx.bezierCurveTo(c1x,c1y,c2x,c2y,x,y); break; }
                    case "Z": ctx.closePath(); break;
                    default: i++;
                }
            }
        }
    }
}
