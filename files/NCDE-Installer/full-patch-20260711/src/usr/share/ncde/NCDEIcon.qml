// NCDEIcon.qml — Universal QML-drawn icon for NCDE
// Bind accentColor/glowColor/bgColor/textColor to ncde.* or fm.* at call site.
// Repaints on any color/type/size change — wallpaper theme picker propagates instantly.

import QtQuick 2.15

Canvas {
    id: root
    renderStrategy: Canvas.Cooperative
    property string type:        "unknown"
    property int    size:        36
    property color  accentColor: ncde.verd
    property color  glowColor:   ncde.verd
    property color  bgColor:     "#263033"
    property color  textColor:   "#E6F1F2"

    width: size; height: size

    onTypeChanged:        requestPaint()
    onSizeChanged:        requestPaint()
    onAccentColorChanged: requestPaint()
    onGlowColorChanged:   requestPaint()
    onBgColorChanged:     requestPaint()
    onTextColorChanged:   requestPaint()
    Component.onCompleted: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        ctx.clearRect(0,0,width,height)
        var s = Math.min(width,height)
        switch(type) {
            case "folder":           drawFolder(ctx,s);          break
            case "image":            drawImage(ctx,s);           break
            case "audio":            drawAudio(ctx,s);           break
            case "video":            drawVideo(ctx,s);           break
            case "text":             drawText(ctx,s);            break
            case "code":             drawCode(ctx,s);            break
            case "archive":          drawArchive(ctx,s);         break
            case "pdf":              drawPdf(ctx,s);             break
            case "spreadsheet":      drawSheet(ctx,s);           break
            case "presentation":     drawPresent(ctx,s);         break
            case "executable":       drawExec(ctx,s);            break
            case "network-up":       drawNetUp(ctx,s);           break
            case "network-down":     drawNetDown(ctx,s);         break
            case "battery-full":     drawBattery(ctx,s,1.00,false); break
            case "battery-high":     drawBattery(ctx,s,0.70,false); break
            case "battery-mid":      drawBattery(ctx,s,0.40,false); break
            case "battery-low":      drawBattery(ctx,s,0.15,false); break
            case "battery-charging": drawBattery(ctx,s,0.60,true);  break
            case "volume-high":      drawVolume(ctx,s,2);        break
            case "volume-low":       drawVolume(ctx,s,1);        break
            case "volume-muted":     drawVolume(ctx,s,0);        break
            case "brightness":       drawBright(ctx,s);          break
            case "notification":     drawBell(ctx,s);            break
            default:                 drawUnknown(ctx,s);         break
        }
    }

    function rrect(ctx,x,y,w,h,r) {
        ctx.beginPath()
        ctx.moveTo(x+r,y); ctx.lineTo(x+w-r,y); ctx.arcTo(x+w,y,x+w,y+r,r)
        ctx.lineTo(x+w,y+h-r); ctx.arcTo(x+w,y+h,x+w-r,y+h,r)
        ctx.lineTo(x+r,y+h); ctx.arcTo(x,y+h,x,y+h-r,r)
        ctx.lineTo(x,y+r); ctx.arcTo(x,y,x+r,y,r); ctx.closePath()
    }
    function ac(a) { return Qt.rgba(accentColor.r,accentColor.g,accentColor.b,a).toString() }
    function gCol(a) { return Qt.rgba(glowColor.r,glowColor.g,glowColor.b,a).toString() }
    function tc(a) { return Qt.rgba(textColor.r,textColor.g,textColor.b,a).toString() }
    function bc(a) { return Qt.rgba(bgColor.r,bgColor.g,bgColor.b,a).toString() }

    function drawFolder(ctx,s) {
        ctx.beginPath()
        ctx.moveTo(s*.08,s*.38); ctx.lineTo(s*.08,s*.28)
        ctx.arcTo(s*.08,s*.20,s*.16,s*.20,s*.07); ctx.lineTo(s*.40,s*.20)
        ctx.arcTo(s*.48,s*.20,s*.50,s*.28,s*.08); ctx.lineTo(s*.52,s*.38)
        ctx.closePath(); ctx.fillStyle=ac(.95); ctx.fill()
        rrect(ctx,s*.08,s*.34,s*.84,s*.52,s*.08); ctx.fillStyle=ac(.80); ctx.fill()
        rrect(ctx,s*.16,s*.44,s*.68,s*.34,s*.06); ctx.fillStyle=gCol(.18); ctx.fill()
    }
    function drawImage(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=tc(.08); ctx.fill()
        ctx.strokeStyle=tc(.20); ctx.lineWidth=s*.04; ctx.stroke()
        rrect(ctx,s*.10,s*.10,s*.80,s*.80,s*.08)
        var g=ctx.createLinearGradient(0,s*.10,0,s*.90)
        g.addColorStop(0,ac(.35)); g.addColorStop(1,bc(.60))
        ctx.fillStyle=g; ctx.fill()
        ctx.beginPath(); ctx.moveTo(s*.10,s*.90); ctx.lineTo(s*.38,s*.48)
        ctx.lineTo(s*.58,s*.68); ctx.lineTo(s*.74,s*.52); ctx.lineTo(s*.90,s*.90)
        ctx.closePath(); ctx.fillStyle=tc(.35); ctx.fill()
        ctx.beginPath(); ctx.arc(s*.74,s*.26,s*.10,0,Math.PI*2)
        ctx.fillStyle=gCol(.90); ctx.fill()
    }
    function drawAudio(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=ac(.15); ctx.fill()
        ctx.strokeStyle=ac(.90); ctx.lineWidth=s*.08; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.55,s*.25); ctx.lineTo(s*.55,s*.62); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.55,s*.25)
        ctx.bezierCurveTo(s*.75,s*.28,s*.78,s*.44,s*.58,s*.46); ctx.stroke()
        ctx.beginPath(); ctx.ellipse(s*.38,s*.60,s*.16,s*.12,-0.4,0,Math.PI*2)
        ctx.fillStyle=ac(.90); ctx.fill()
    }
    function drawVideo(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=bc(.90); ctx.fill()
        ctx.fillStyle=tc(.15)
        for(var i=0;i<5;i++) {
            rrect(ctx,s*(.10+i*.18),s*.06,s*.10,s*.10,s*.02); ctx.fill()
            rrect(ctx,s*(.10+i*.18),s*.84,s*.10,s*.10,s*.02); ctx.fill()
        }
        ctx.beginPath(); ctx.moveTo(s*.34,s*.30); ctx.lineTo(s*.34,s*.70)
        ctx.lineTo(s*.72,s*.50); ctx.closePath(); ctx.fillStyle=ac(.90); ctx.fill()
    }
    function drawText(ctx,s) {
        var fold=s*.18
        ctx.beginPath(); ctx.moveTo(s*.14,s*.06); ctx.lineTo(s*.86-fold,s*.06)
        ctx.lineTo(s*.86,s*.06+fold); ctx.lineTo(s*.86,s*.94)
        ctx.lineTo(s*.14,s*.94); ctx.closePath()
        ctx.fillStyle=tc(.06); ctx.fill()
        ctx.strokeStyle=tc(.25); ctx.lineWidth=s*.04; ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.86-fold,s*.06)
        ctx.lineTo(s*.86-fold,s*.06+fold); ctx.lineTo(s*.86,s*.06+fold)
        ctx.closePath(); ctx.fillStyle=tc(.15); ctx.fill()
        ctx.fillStyle=tc(.30)
        var ls=[.32,.44,.56,.68]
        for(var i=0;i<ls.length;i++)
            ctx.fillRect(s*.22,s*ls[i],s*(i===ls.length-1?.42:.54),s*.06)
    }
    function drawCode(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=bc(.90); ctx.fill()
        ctx.strokeStyle=ac(.90); ctx.lineWidth=s*.07; ctx.lineCap="round"; ctx.lineJoin="round"
        ctx.beginPath(); ctx.moveTo(s*.38,s*.32); ctx.lineTo(s*.22,s*.50); ctx.lineTo(s*.38,s*.68); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.62,s*.32); ctx.lineTo(s*.78,s*.50); ctx.lineTo(s*.62,s*.68); ctx.stroke()
        ctx.strokeStyle=gCol(.70)
        ctx.beginPath(); ctx.moveTo(s*.56,s*.28); ctx.lineTo(s*.44,s*.72); ctx.stroke()
    }
    function drawArchive(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=Qt.rgba(.55,.40,.20,.20).toString(); ctx.fill()
        rrect(ctx,s*.18,s*.30,s*.64,s*.60,s*.06); ctx.fillStyle=Qt.rgba(.65,.48,.28,.80).toString(); ctx.fill()
        rrect(ctx,s*.14,s*.22,s*.72,s*.14,s*.04); ctx.fillStyle=Qt.rgba(.75,.56,.34,.90).toString(); ctx.fill()
        ctx.fillStyle=ac(.60); ctx.fillRect(s*.44,s*.30,s*.12,s*.60)
        ctx.fillStyle=ac(.90)
        for(var i=0;i<4;i++) ctx.fillRect(s*.44,s*(.36+i*.13),s*.12,s*.06)
    }
    function drawPdf(ctx,s) {
        var fold=s*.16
        ctx.beginPath(); ctx.moveTo(s*.14,s*.06); ctx.lineTo(s*.86-fold,s*.06)
        ctx.lineTo(s*.86,s*.06+fold); ctx.lineTo(s*.86,s*.94); ctx.lineTo(s*.14,s*.94); ctx.closePath()
        ctx.fillStyle="white"; ctx.fill()
        ctx.fillStyle="#CC2222"
        ctx.fillRect(s*.14,s*.06,s*.72-fold,s*.26); ctx.fillRect(s*.14,s*.06+fold,s*.72,s*.26-fold)
        ctx.beginPath(); ctx.moveTo(s*.86-fold,s*.06); ctx.lineTo(s*.86-fold,s*.06+fold)
        ctx.lineTo(s*.86,s*.06+fold); ctx.closePath(); ctx.fillStyle="#FF6666"; ctx.fill()
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.20)+"px sans-serif"
        ctx.textAlign="center"; ctx.textBaseline="middle"; ctx.fillText("PDF",s*.48,s*.19)
        ctx.fillStyle="#CCCCCC"
        for(var i=0;i<3;i++) ctx.fillRect(s*.22,s*(.44+i*.14),i===2?s*.36:s*.56,s*.05)
    }
    function drawSheet(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=Qt.rgba(.10,.60,.25,.15).toString(); ctx.fill()
        var gx=s*.12,gy=s*.16,gw=s*.76,gh=s*.70,cols=3,rows=4,cw=gw/cols,rh=gh/rows
        ctx.fillStyle=Qt.rgba(.10,.60,.25,.40).toString(); ctx.fillRect(gx,gy,gw,rh)
        ctx.strokeStyle=Qt.rgba(.10,.60,.25,.50).toString(); ctx.lineWidth=s*.03
        for(var c=0;c<=cols;c++){ctx.beginPath();ctx.moveTo(gx+c*cw,gy);ctx.lineTo(gx+c*cw,gy+gh);ctx.stroke()}
        for(var r=0;r<=rows;r++){ctx.beginPath();ctx.moveTo(gx,gy+r*rh);ctx.lineTo(gx+gw,gy+r*rh);ctx.stroke()}
        ctx.fillStyle=ac(.60); ctx.fillRect(gx+cw*2+s*.03,gy+rh*2+s*.03,cw*.65,rh-s*.06)
    }
    function drawPresent(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=ac(.12); ctx.fill()
        rrect(ctx,s*.10,s*.14,s*.80,s*.54,s*.06); ctx.fillStyle=bc(.80); ctx.fill()
        ctx.strokeStyle=ac(.50); ctx.lineWidth=s*.04; ctx.stroke()
        ctx.fillStyle=ac(.70); ctx.fillRect(s*.18,s*.22,s*.40,s*.08)
        ctx.fillStyle=tc(.25)
        ctx.fillRect(s*.18,s*.34,s*.56,s*.05); ctx.fillRect(s*.18,s*.42,s*.48,s*.05)
        ctx.fillRect(s*.18,s*.50,s*.36,s*.05)
        ctx.strokeStyle=tc(.30); ctx.lineWidth=s*.05; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.50,s*.68); ctx.lineTo(s*.50,s*.84); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.30,s*.86); ctx.lineTo(s*.70,s*.86); ctx.stroke()
    }
    function drawExec(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=bc(.90); ctx.fill()
        ctx.fillStyle=tc(.50)
        for(var t=0;t<8;t++) {
            var ang=t*Math.PI*2/8
            ctx.save(); ctx.translate(s/2,s/2); ctx.rotate(ang)
            ctx.fillRect(-s*.06,-s*.46,s*.12,s*.10); ctx.restore()
        }
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.34,0,Math.PI*2); ctx.fillStyle=tc(.40); ctx.fill()
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.20,0,Math.PI*2); ctx.fillStyle=bc(.90); ctx.fill()
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.08,0,Math.PI*2); ctx.fillStyle=ac(.80); ctx.fill()
    }
    function drawUnknown(ctx,s) {
        rrect(ctx,0,0,s,s,s*.14); ctx.fillStyle=tc(.08); ctx.fill()
        ctx.strokeStyle=tc(.20); ctx.lineWidth=s*.04; ctx.stroke()
        ctx.fillStyle=tc(.40); ctx.font="bold "+Math.round(s*.50)+"px sans-serif"
        ctx.textAlign="center"; ctx.textBaseline="middle"; ctx.fillText("?",s/2,s/2+s*.04)
    }
    function drawNetUp(ctx,s) {
        ctx.lineCap="round"
        var rs=[s*.38,s*.26,s*.14],ws=[s*.08,s*.07,s*.06]
        for(var i=0;i<3;i++){
            ctx.strokeStyle=ac(1.0); ctx.lineWidth=ws[i]
            ctx.beginPath(); ctx.arc(s/2,s*.65,rs[i],-Math.PI*.75,-Math.PI*.25); ctx.stroke()
        }
        ctx.beginPath(); ctx.arc(s/2,s*.78,s*.07,0,Math.PI*2); ctx.fillStyle=ac(1.0); ctx.fill()
    }
    function drawNetDown(ctx,s) {
        ctx.lineCap="round"
        for(var i=0;i<3;i++){
            ctx.strokeStyle=tc(.30); ctx.lineWidth=s*.06
            ctx.beginPath(); ctx.arc(s/2,s*.65,s*(.14+i*.12),-Math.PI*.75,-Math.PI*.25); ctx.stroke()
        }
        ctx.strokeStyle="#EF4444"; ctx.lineWidth=s*.12
        ctx.beginPath(); ctx.moveTo(s*.30,s*.25); ctx.lineTo(s*.70,s*.75); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.70,s*.25); ctx.lineTo(s*.30,s*.75); ctx.stroke()
    }
    function drawBattery(ctx,s,level,charging) {
        var bx=s*.10,by=s*.26,bw=s*.68,bh=s*.48
        ctx.fillStyle=tc(.60); ctx.fillRect(s*.78,s*.38,s*.14,s*.24)
        rrect(ctx,bx,by,bw,bh,s*.06); ctx.strokeStyle=tc(.70); ctx.lineWidth=s*.06; ctx.stroke()
        rrect(ctx,bx+s*.06,by+s*.06,(bw-s*.12)*level,bh-s*.12,s*.03)
        ctx.fillStyle=(level<=.20)?"#EF4444":ac(.90); ctx.fill()
        if(charging){
            ctx.strokeStyle="white"; ctx.lineWidth=s*.08; ctx.lineCap="round"; ctx.lineJoin="round"
            ctx.beginPath(); ctx.moveTo(s*.52,s*.30); ctx.lineTo(s*.38,s*.52)
            ctx.lineTo(s*.50,s*.52); ctx.lineTo(s*.36,s*.74); ctx.stroke()
        }
    }
    function drawVolume(ctx,s,waves) {
        ctx.fillStyle=waves>0?ac(.90):tc(.40)
        ctx.beginPath(); ctx.moveTo(s*.20,s*.36); ctx.lineTo(s*.38,s*.36)
        ctx.lineTo(s*.54,s*.20); ctx.lineTo(s*.54,s*.80)
        ctx.lineTo(s*.38,s*.64); ctx.lineTo(s*.20,s*.64); ctx.closePath(); ctx.fill()
        ctx.strokeStyle=ac(.90); ctx.lineCap="round"; ctx.lineWidth=s*.07
        if(waves===0){
            ctx.strokeStyle="#EF4444"
            ctx.beginPath(); ctx.moveTo(s*.64,s*.34); ctx.lineTo(s*.80,s*.66); ctx.stroke()
            ctx.beginPath(); ctx.moveTo(s*.80,s*.34); ctx.lineTo(s*.64,s*.66); ctx.stroke()
        } else {
            ctx.beginPath(); ctx.arc(s*.54,s*.50,s*.14,-Math.PI*.50,Math.PI*.50); ctx.stroke()
            if(waves>=2){ctx.beginPath(); ctx.arc(s*.54,s*.50,s*.26,-Math.PI*.50,Math.PI*.50); ctx.stroke()}
        }
    }
    function drawBright(ctx,s) {
        ctx.strokeStyle=ac(.80); ctx.lineWidth=s*.07; ctx.lineCap="round"
        for(var i=0;i<8;i++){
            var ang=i*Math.PI/4
            ctx.beginPath()
            ctx.moveTo(s/2+Math.cos(ang)*s*.28,s/2+Math.sin(ang)*s*.28)
            ctx.lineTo(s/2+Math.cos(ang)*s*.42,s/2+Math.sin(ang)*s*.42); ctx.stroke()
        }
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.20,0,Math.PI*2); ctx.fillStyle=ac(.90); ctx.fill()
    }
    function drawBell(ctx,s) {
        ctx.fillStyle=ac(.90)
        ctx.beginPath(); ctx.moveTo(s*.50,s*.14)
        ctx.bezierCurveTo(s*.24,s*.14,s*.16,s*.36,s*.16,s*.58)
        ctx.lineTo(s*.16,s*.66); ctx.lineTo(s*.84,s*.66); ctx.lineTo(s*.84,s*.58)
        ctx.bezierCurveTo(s*.84,s*.36,s*.76,s*.14,s*.50,s*.14)
        ctx.closePath(); ctx.fill()
        ctx.beginPath(); ctx.arc(s*.50,s*.76,s*.10,0,Math.PI*2); ctx.fill()
        ctx.strokeStyle=ac(.90); ctx.lineWidth=s*.08; ctx.lineCap="round"
        ctx.beginPath(); ctx.arc(s*.50,s*.14,s*.08,Math.PI,Math.PI*2); ctx.stroke()
    }
}
