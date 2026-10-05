import QtQuick

Canvas {
    property string name: ""
    property color  tint: ncde.gilt1
    antialiasing: true
    renderStrategy: Canvas.Cooperative
    onTintChanged: requestPaint()
    onNameChanged: requestPaint()
    Component.onCompleted: requestPaint()
    onPaint: {
        var ctx=getContext("2d"); ctx.reset();
        var s=Math.min(width,height)/24.0; ctx.scale(s,s);
        ctx.strokeStyle=tint; ctx.fillStyle=tint;
        ctx.lineWidth=1.7; ctx.lineCap="round"; ctx.lineJoin="round";
        var P=function(){ ctx.beginPath(); };
        if (name==="i-inbox"){ P(); ctx.moveTo(3,13);ctx.lineTo(6,5);ctx.lineTo(18,5);ctx.lineTo(21,13);ctx.lineTo(21,19);ctx.lineTo(3,19);ctx.closePath();ctx.stroke();
            P(); ctx.moveTo(3,13);ctx.lineTo(8,13);ctx.lineTo(10,16);ctx.lineTo(14,16);ctx.lineTo(16,13);ctx.lineTo(21,13);ctx.stroke(); }
        else if (name==="i-star"){ P(); ctx.moveTo(12,3);ctx.lineTo(14.7,8.7);ctx.lineTo(21,9.5);ctx.lineTo(16.4,13.8);ctx.lineTo(17.6,20);ctx.lineTo(12,17.1);ctx.lineTo(6.4,20);ctx.lineTo(7.6,13.8);ctx.lineTo(3,9.5);ctx.lineTo(9.3,8.7);ctx.closePath(); ctx.fill(); }
        else if (name==="i-sent"){ P(); ctx.moveTo(21,4);ctx.lineTo(3,11);ctx.lineTo(9,13);ctx.lineTo(11,19);ctx.lineTo(14,14);ctx.lineTo(18,18);ctx.lineTo(21,4);ctx.closePath(); ctx.stroke(); }
        else if (name==="i-draft"){ P(); ctx.moveTo(5,19);ctx.lineTo(6,15);ctx.lineTo(17,4);ctx.lineTo(20,7);ctx.lineTo(9,18);ctx.closePath(); ctx.stroke(); P(); ctx.moveTo(14,7);ctx.lineTo(17,10);ctx.stroke(); }
        else if (name==="i-archive"){ P(); ctx.rect(3,7,18,3); ctx.stroke(); P(); ctx.moveTo(5,10);ctx.lineTo(5,19);ctx.lineTo(19,19);ctx.lineTo(19,10);ctx.stroke(); P(); ctx.moveTo(10,14);ctx.lineTo(14,14);ctx.stroke(); }
        else if (name==="i-spam"){ P(); ctx.moveTo(12,3);ctx.lineTo(21,8);ctx.lineTo(21,14);ctx.bezierCurveTo(21,18,17,20,12,21);ctx.bezierCurveTo(7,20,3,18,3,14);ctx.lineTo(3,8);ctx.closePath();ctx.stroke(); P(); ctx.moveTo(12,8);ctx.lineTo(12,13);ctx.stroke(); P(); ctx.arc(12,16,0.6,0,2*Math.PI); ctx.fill(); }
        else if (name==="i-trash"){ P(); ctx.moveTo(4,7);ctx.lineTo(20,7);ctx.stroke(); P(); ctx.moveTo(9,7);ctx.lineTo(9,5);ctx.lineTo(15,5);ctx.lineTo(15,7);ctx.stroke(); P(); ctx.moveTo(6,7);ctx.lineTo(7,20);ctx.lineTo(17,20);ctx.lineTo(18,7);ctx.stroke(); }
        else if (name==="i-contacts"){ P(); ctx.rect(4,5,16,14); ctx.stroke(); P(); ctx.arc(12,10,2.6,0,2*Math.PI); ctx.stroke(); P(); ctx.moveTo(8,17);ctx.bezierCurveTo(8,14,10,13,12,13);ctx.bezierCurveTo(14,13,16,14,16,17);ctx.stroke(); }
        else if (name==="i-reply"){ P(); ctx.moveTo(9,7);ctx.lineTo(4,12);ctx.lineTo(9,17);ctx.stroke(); P(); ctx.moveTo(4,12);ctx.lineTo(13,12);ctx.bezierCurveTo(17,12,20,14,20,18);ctx.stroke(); }
        else if (name==="i-reply-all"){ P(); ctx.moveTo(8,7);ctx.lineTo(3,12);ctx.lineTo(8,17);ctx.stroke(); P(); ctx.moveTo(13,7);ctx.lineTo(10,12);ctx.lineTo(13,17);ctx.stroke(); P(); ctx.moveTo(10,12);ctx.lineTo(16,12);ctx.bezierCurveTo(19,12,21,14,21,17);ctx.stroke(); }
        else if (name==="i-forward"){ P(); ctx.moveTo(15,7);ctx.lineTo(20,12);ctx.lineTo(15,17);ctx.stroke(); P(); ctx.moveTo(20,12);ctx.lineTo(11,12);ctx.bezierCurveTo(7,12,4,14,4,18);ctx.stroke(); }
        else if (name==="i-search"){ P(); ctx.arc(11,11,7,0,2*Math.PI); ctx.stroke(); P(); ctx.moveTo(16,16);ctx.lineTo(21,21);ctx.stroke(); }
        else if (name==="i-clip"){ P(); ctx.moveTo(20,11);ctx.lineTo(12,19);ctx.bezierCurveTo(9,22,4,17,7,14);ctx.lineTo(15,6);ctx.bezierCurveTo(17,4,20,7,18,9);ctx.lineTo(10,17);ctx.stroke(); }
        else if (name==="i-thread"){ P(); ctx.moveTo(4,6);ctx.lineTo(17,6);ctx.stroke(); P(); ctx.moveTo(4,10);ctx.lineTo(17,10);ctx.stroke(); P(); ctx.moveTo(7,14);ctx.lineTo(17,14);ctx.stroke(); }
        else if (name==="i-feather"){ P(); ctx.moveTo(20,4);ctx.bezierCurveTo(10,4,5,9,5,16);ctx.lineTo(4,20);ctx.lineTo(9,18);ctx.bezierCurveTo(16,18,20,12,20,4);ctx.closePath(); ctx.fill(); }
        else if (name==="i-book"){ P(); ctx.moveTo(4,5);ctx.lineTo(11,5);ctx.bezierCurveTo(12,5,12,6,12,6);ctx.lineTo(12,19);ctx.bezierCurveTo(12,18,11,18,11,18);ctx.lineTo(4,18);ctx.closePath(); ctx.stroke(); P(); ctx.moveTo(20,5);ctx.lineTo(13,5);ctx.bezierCurveTo(12,5,12,6,12,6);ctx.lineTo(12,19);ctx.bezierCurveTo(12,18,13,18,13,18);ctx.lineTo(20,18);ctx.closePath(); ctx.stroke(); }
        else if (name==="i-refresh"){ P(); ctx.arc(12,12,7,0.6,2*Math.PI); ctx.stroke(); P(); ctx.moveTo(17,5);ctx.lineTo(19,8);ctx.lineTo(15.5,8.5);ctx.stroke(); }
    }
}
