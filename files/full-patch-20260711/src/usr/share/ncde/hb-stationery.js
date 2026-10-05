// hb-stationery.js — Hummingbird Courier stationery, Outlook-Express style.
//
// Classic OE stationery format: a decorative vertical BORDER BAND down the left
// margin, a soft tiled WATERMARK behind the text, and the message flowing to the
// right of the band. Shared by HBStationery.qml (picker) and HBCompose.qml (the
// letterhead the user types on). All ornament is Canvas-2D so it runs the same
// in a QML Canvas and the HTML preview.
//
// A set: { key,name,desc,group,role,sal,signoff,dark,nameC,roleC,bodyL(0..1
// text-left fraction), paint(ctx,w,h) }. SETS is ordered; setByKey(k) looks up.
.pragma library

var INK="#3a2c18", FAINT="#7a6238", GOLD="#b8862c", GOLD_BR="#e2c772", GOLD_DK="#6e4f17";

// ── helpers ──────────────────────────────────────────────────────────────────
function lerp(a,b,t){return a+(b-a)*t;}
function paper(ctx,w,h,top,bot){var g=ctx.createLinearGradient(0,0,0,h);g.addColorStop(0,top);g.addColorStop(1,bot||top);ctx.fillStyle=g;ctx.fillRect(0,0,w,h);}

// soft repeating watermark motif behind the whole sheet
function watermark(ctx,w,h,draw,alpha){ctx.save();ctx.globalAlpha=alpha||0.05;
  var cw=w/5, ch=cw; for(var r=-1;r*ch<h+ch;r++)for(var c=2;c*cw<w+cw;c++){ // start past the band
    draw(ctx, c*cw+(r%2?cw/2:0), r*ch, cw*0.34);} ctx.restore();}

// the defining OE element: a vertical border band down the left margin
function leftBand(ctx,w,h,bandW,fill,edge){ctx.save();
  if(typeof fill==="function"){fill(ctx,bandW,h);}else{ctx.fillStyle=fill;ctx.fillRect(0,0,bandW,h);}
  if(edge){ctx.strokeStyle=edge;ctx.lineWidth=2;ctx.beginPath();ctx.moveTo(bandW,0);ctx.lineTo(bandW,h);ctx.stroke();}
  ctx.restore();}
function bandGrad(ctx,bandW,h,a,b){var g=ctx.createLinearGradient(0,0,bandW,0);g.addColorStop(0,a);g.addColorStop(1,b);ctx.fillStyle=g;ctx.fillRect(0,0,bandW,h);}

// ── motif vocabulary (used in bands + watermarks) ────────────────────────────
function ivyLeaf(ctx,x,y,r,col){ctx.save();ctx.translate(x,y);ctx.fillStyle=col;
  var lobe=[0,0.42,0.95,1.6,2.2,Math.PI-0.3,Math.PI,Math.PI+0.3,2*Math.PI-2.2,2*Math.PI-1.6,2*Math.PI-0.95,2*Math.PI-0.42];
  var rad=[r,r*0.55,r*0.9,r*0.5,r*0.8,r*0.4,r*0.5,r*0.4,r*0.8,r*0.5,r*0.9,r*0.55];
  ctx.beginPath();for(var i=0;i<lobe.length;i++){var a=lobe[i]-Math.PI/2,rr=rad[i];var px=Math.cos(a)*rr,py=Math.sin(a)*rr;i?ctx.lineTo(px,py):ctx.moveTo(px,py);}ctx.closePath();ctx.fill();
  ctx.strokeStyle="rgba(255,255,255,.28)";ctx.lineWidth=0.8;
  ctx.beginPath();ctx.moveTo(0,r*0.6);ctx.lineTo(0,-r*0.75);ctx.moveTo(0,-r*0.1);ctx.lineTo(-r*0.55,-r*0.45);ctx.moveTo(0,-r*0.1);ctx.lineTo(r*0.55,-r*0.45);ctx.stroke();ctx.restore();}
function rosebud(ctx,x,y,r,col,leaf){ctx.save();ctx.translate(x,y);
  function lf(ang,len){ctx.save();ctx.rotate(ang);ctx.fillStyle=leaf;ctx.beginPath();ctx.moveTo(0,0);
    ctx.quadraticCurveTo(len*0.32,len*0.3,0,len);ctx.quadraticCurveTo(-len*0.32,len*0.3,0,0);ctx.closePath();ctx.fill();
    ctx.strokeStyle="rgba(255,255,255,.22)";ctx.lineWidth=0.7;ctx.beginPath();ctx.moveTo(0,len*0.12);ctx.lineTo(0,len*0.85);ctx.stroke();ctx.restore();}
  lf(-2.5,r*1.5);lf(2.5,r*1.5);lf(Math.PI,r*1.45);
  function sh(hex,f){var n=parseInt(hex.slice(1),16),R=(n>>16)&255,G=(n>>8)&255,B=n&255;
    return "rgb("+Math.round(Math.min(255,R*f))+","+Math.round(Math.min(255,G*f))+","+Math.round(Math.min(255,B*f))+")";}
  ctx.fillStyle=sh(col,0.82);
  for(var i=0;i<5;i++){ctx.save();ctx.rotate(i/5*Math.PI*2);
    ctx.beginPath();ctx.moveTo(0,-r*0.2);
    ctx.bezierCurveTo(-r*0.78,-r*0.55,-r*0.5,-r*1.05,0,-r*0.95);
    ctx.bezierCurveTo(r*0.5,-r*1.05,r*0.78,-r*0.55,0,-r*0.2);ctx.closePath();ctx.fill();ctx.restore();}
  ctx.fillStyle=col;
  for(var j=0;j<5;j++){ctx.save();ctx.rotate(j/5*Math.PI*2+Math.PI/5);
    ctx.beginPath();ctx.moveTo(0,-r*0.1);
    ctx.bezierCurveTo(-r*0.5,-r*0.35,-r*0.34,-r*0.72,0,-r*0.66);
    ctx.bezierCurveTo(r*0.34,-r*0.72,r*0.5,-r*0.35,0,-r*0.1);ctx.closePath();ctx.fill();ctx.restore();}
  ctx.fillStyle=sh(col,0.7);ctx.beginPath();ctx.arc(0,0,r*0.3,0,7);ctx.fill();
  ctx.strokeStyle=sh(col,1.15);ctx.lineWidth=Math.max(0.8,r*0.06);ctx.lineCap="round";
  ctx.beginPath();for(var a=0;a<Math.PI*3;a+=0.25){var rr=r*0.07+a*r*0.045;ctx.lineTo(Math.cos(a)*rr,Math.sin(a)*rr);}ctx.stroke();
  ctx.fillStyle="rgba(255,255,255,.25)";ctx.beginPath();ctx.arc(-r*0.32,-r*0.5,r*0.18,0,7);ctx.fill();
  ctx.restore();}
function fernSprig(ctx,x,y,r,col){ctx.save();ctx.translate(x,y);ctx.strokeStyle=col;ctx.lineWidth=1.4;ctx.lineCap="round";
  ctx.beginPath();ctx.moveTo(0,r*1.4);ctx.quadraticCurveTo(-r*0.3,0,0,-r*1.4);ctx.stroke();
  for(var i=-1;i<=1;i+=2)for(var k=1;k<=4;k++){var yy=-r*1.0+k*r*0.55;ctx.beginPath();ctx.moveTo(0,yy);ctx.lineTo(i*r*0.7*(1-k*0.12),yy+r*0.3);ctx.stroke();}ctx.restore();}
function starlet(ctx,x,y,r,col){ctx.save();ctx.translate(x,y);ctx.fillStyle=col;ctx.beginPath();
  for(var i=0;i<8;i++){var a=i/8*Math.PI*2,rr=i%2?r:r*0.4;ctx.lineTo(Math.cos(a)*rr,Math.sin(a)*rr);}ctx.closePath();ctx.fill();ctx.restore();}
function shell(ctx,x,y,r,col){ctx.save();ctx.translate(x,y);
  ctx.fillStyle=col;ctx.globalAlpha=0.9;ctx.beginPath();ctx.moveTo(0,r*0.55);
  ctx.arc(0,r*0.55,r,Math.PI*1.15,Math.PI*1.85);ctx.closePath();ctx.fill();ctx.globalAlpha=1;
  ctx.strokeStyle="rgba(255,255,255,.4)";ctx.lineWidth=0.8;
  for(var i=-3;i<=3;i++){var a=Math.PI*1.5+i*0.16;ctx.beginPath();ctx.moveTo(0,r*0.55);ctx.lineTo(Math.cos(a)*r*0.95,r*0.55+Math.sin(a)*r*0.95);ctx.stroke();}
  ctx.fillStyle=col;ctx.beginPath();ctx.arc(0,r*0.55,r*0.14,0,7);ctx.fill();ctx.restore();}
function gear(ctx,x,y,r,col){ctx.save();ctx.translate(x,y);ctx.strokeStyle=col;ctx.lineWidth=1.4;ctx.beginPath();ctx.arc(0,0,r*0.6,0,7);ctx.stroke();
  for(var i=0;i<8;i++){var a=i/8*Math.PI*2;ctx.beginPath();ctx.moveTo(Math.cos(a)*r*0.6,Math.sin(a)*r*0.6);ctx.lineTo(Math.cos(a)*r,Math.sin(a)*r);ctx.stroke();}ctx.restore();}
function diamondNode(ctx,cx,cy,r,col){ctx.save();ctx.fillStyle=col;ctx.beginPath();ctx.moveTo(cx,cy-r);ctx.lineTo(cx+r,cy);ctx.lineTo(cx,cy+r);ctx.lineTo(cx-r,cy);ctx.closePath();ctx.fill();ctx.restore();}

// a column of a motif running down the band centre
function bandColumn(ctx,bandW,h,motif,col,step){var x=bandW*0.5,s=bandW*0.26;step=step||s*2.6;
  for(var y=step*0.7;y<h;y+=step) motif(ctx,x,y,s,col);}

// gold double rule just inside the band edge (engraved look)
function bandRules(ctx,bandW,h,col){ctx.strokeStyle=col;ctx.lineWidth=1.5;ctx.beginPath();ctx.moveTo(bandW-3,0);ctx.lineTo(bandW-3,h);ctx.stroke();
  ctx.lineWidth=0.8;ctx.beginPath();ctx.moveTo(bandW-7,0);ctx.lineTo(bandW-7,h);ctx.stroke();}

// the small hummingbird crest mark, centred in a (w×h) canvas
function crestMark(ctx,w,h,color){ctx.clearRect(0,0,w,h);ctx.save();ctx.translate(w/2,h*0.46);
  var s=Math.min(w,h)*0.18;ctx.fillStyle=color;ctx.strokeStyle=color;ctx.globalAlpha=.95;
  ctx.beginPath();ctx.ellipse(-2,2,s*0.5,s*0.3,-0.25,0,7);ctx.fill();
  ctx.beginPath();ctx.moveTo(-s*0.5,4);ctx.lineTo(-s*1.1,11);ctx.lineTo(-s*1.0,3);ctx.closePath();ctx.fill();
  ctx.beginPath();ctx.arc(s*0.42,-2,s*0.2,0,7);ctx.fill();
  ctx.lineWidth=1.4;ctx.beginPath();ctx.moveTo(s*0.6,-1);ctx.lineTo(s*1.25,1);ctx.stroke();
  ctx.globalAlpha=.6;ctx.beginPath();ctx.moveTo(-2,-1);ctx.quadraticCurveTo(2,-s*0.9,s*0.5,-s*0.5);ctx.quadraticCurveTo(s*0.1,-2,-2,-1);ctx.fill();
  ctx.globalAlpha=1;ctx.lineWidth=1;ctx.beginPath();ctx.moveTo(-w*0.28,17);ctx.quadraticCurveTo(0,23,w*0.28,17);ctx.stroke();
  ctx.beginPath();ctx.arc(w*0.28,17,1.6,0,7);ctx.fill();ctx.beginPath();ctx.arc(-w*0.28,17,1.6,0,7);ctx.fill();ctx.restore();}

// ── OE composer: paper → watermark → left band → band rule ───────────────────
function oe(ctx,w,h,opt){
  paper(ctx,w,h,opt.paperTop,opt.paperBot);
  if(opt.water) watermark(ctx,w,h,opt.water,opt.waterA);
  var bw=w*(opt.bandW||0.16);
  if(opt.bandFill) leftBand(ctx,w,h,bw,opt.bandFill);
  if(opt.bandCol) bandColumn(ctx,bw,h,opt.bandMotif,opt.bandMotifCol,opt.bandStep);
  if(opt.bandRule) bandRules(ctx,bw,h,opt.bandRule);
  if(opt.topRule){ctx.strokeStyle=opt.topRule;ctx.lineWidth=2;ctx.beginPath();ctx.moveTo(bw,h*0.06);ctx.lineTo(w*0.93,h*0.06);ctx.stroke();}
}
var ML = 0.235;  // default text-left fraction (just past a 0.16 band)

// ── the sets ─────────────────────────────────────────────────────────────────
var SETS = [
 // ── Victorian / decorative (OE-format) ──
 { key:"ivy", name:"Ivy League", desc:"trailing ivy border · green", group:"Garden", bodyL:ML,
   role:"", sal:"My dear friend,", signoff:"Ever yours,", nameC:"#2c5e3a", roleC:"#6a7c52", bodyC:"#3a2c18",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#f4f7ec",paperBot:"#eaf0db",
     water:function(ctx,x,y,r){ivyLeaf(ctx,x,y,r,"#3c6e44");},waterA:0.05,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#2c5e3a","#4a7c52");},
     bandMotif:ivyLeaf,bandMotifCol:"#bcd6a8",bandCol:true,bandRule:"#b8862c"}); } },

 { key:"roses", name:"Climbing Roses", desc:"rosebud border · rose & sage", group:"Garden", bodyL:ML,
   role:"", sal:"Dearest heart,", signoff:"With all that I have,", nameC:"#a8455f", roleC:"#9a6512", bodyC:"#3a2c18",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#fdf4f4",paperBot:"#f8e8ea",
     water:function(ctx,x,y,r){rosebud(ctx,x,y,r*0.7,"#e3a3b6","#9aae7a");},waterA:0.06,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#8c2f44","#b65066");},
     bandMotif:function(ctx,x,y,r,col){rosebud(ctx,x,y,r,"#f1c0cd","#9aae7a");},bandCol:true,bandRule:"#e2c772"}); } },

 { key:"fern", name:"The Fernery", desc:"conservatory fern band · sage", group:"Garden", bodyL:ML,
   role:"", sal:"Friend of the garden,", signoff:"Among the ferns,", nameC:"#3c5a3a", roleC:"#6a7c52", bodyC:"#3a2c18",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#eef2e6",paperBot:"#e3ead7",
     water:function(ctx,x,y,r){fernSprig(ctx,x,y,r*0.8,"#5a7048");},waterA:0.06,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#46603e","#6a8456");},
     bandMotif:fernSprig,bandMotifCol:"#cfe0b6",bandCol:true,bandRule:"#b8862c"}); } },

 { key:"lily", name:"Lily & Lake", desc:"shell border · tiffany teal", group:"Garden", bodyL:ML,
   role:"", sal:"From the lakeside,", signoff:"By still water,", nameC:"#137a63", roleC:"#9a6512", bodyC:"#3a2c18",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#e9f3f0",paperBot:"#d8ebe6",
     water:function(ctx,x,y,r){shell(ctx,x,y,r,"#3a9a86");},waterA:0.05,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#0f6b58","#179a7e");},
     bandMotif:function(ctx,x,y,r,col){shell(ctx,x,y,r,"#c6e8de");},bandCol:true,bandRule:"#e2c772"}); } },

 { key:"damask", name:"Damask Salon", desc:"gilt damask band · burgundy", group:"Formal", bodyL:ML,
   role:"", sal:"My dear friend,", signoff:"Ever yours,", nameC:"#7a2230", roleC:"#6e4f17", bodyC:"#3a2c18",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#f7f0db",paperBot:"#efe4c6",
     water:function(ctx,x,y,r){starlet(ctx,x,y,r*0.5,"#7a2230");},waterA:0.045,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#6a1c2a","#8c2f3e");},
     bandMotif:function(ctx,x,y,r,col){starlet(ctx,x,y,r*0.7,"#e2c772");},bandCol:true,bandRule:"#e2c772",bandStep:34}); } },

 { key:"noir", name:"Gilded Damask Noir", desc:"gold on charcoal band", group:"Formal", bodyL:ML, dark:true,
   role:"", sal:"Esteemed friend,", signoff:"With regard,", nameC:"#e2c772", roleC:"#c9b48a", bodyC:"#e8ddc8",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#23202a",paperBot:"#1c1a22",
     water:function(ctx,x,y,r){starlet(ctx,x,y,r*0.5,"#b8862c");},waterA:0.10,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#2a2620","#3a3326");},
     bandMotif:function(ctx,x,y,r,col){starlet(ctx,x,y,r*0.7,"#e2c772");},bandCol:true,bandRule:"#e2c772",bandStep:34}); } },

 { key:"nightsky", name:"Celestial", desc:"star border · indigo night", group:"Formal", bodyL:ML, dark:true,
   role:"", sal:"Under a waning moon,", signoff:"By starlight,", nameC:"#dfe3ff", roleC:"#aab0e0", bodyC:"#dfe3ff",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#202450",paperBot:"#171a3c",
     water:function(ctx,x,y,r){starlet(ctx,x,y,r*0.4,"#9aa0e0");},waterA:0.12,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#161838","#2a2e66");},
     bandMotif:function(ctx,x,y,r,col){starlet(ctx,x,y,r*0.7,"#e2c772");},bandCol:true,bandRule:"#c8a24a",bandStep:30}); } },

 // ── Professional / corporate (OE-format, restrained) ──
 { key:"meridian", name:"Meridian", desc:"navy band · gold keyline", group:"Professional", bodyL:0.2,
   role:"", sal:"Dear Ms. Vance,", signoff:"Kind regards,", nameC:"#1f3a5c", roleC:"#8a96a4", bodyC:"#1a2030",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#ffffff",paperBot:"#fbfcfe",bandW:0.075,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#1f3a5c","#2c4e74");},
     bandRule:"#c8a24a",topRule:"#1f3a5c"}); c.fillStyle="#c8a24a"; c.fillRect(w*0.075-0.5,0,1,h); } },

 { key:"slate", name:"Slate & Rule", desc:"teal hairline band · minimal", group:"Professional", bodyL:0.17,
   role:"", sal:"Dear colleague,", signoff:"Best regards,", nameC:"#2c7a6b", roleC:"#8a8d86", bodyC:"#2a2a2a",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#fbfbf9",paperBot:"#f6f6f2",bandW:0.05,
     bandFill:function(ctx,bw,hh){ctx.fillStyle="#2c7a6b";ctx.fillRect(bw*0.55,0,Math.max(3,bw*0.18),hh);}}); } },

 { key:"verdant", name:"Verdant & Co.", desc:"forest green band · survey", group:"Professional", bodyL:0.2,
   role:"", sal:"To whom it may concern,", signoff:"Yours faithfully,", nameC:"#1f5135", roleC:"#6a8a6e", bodyC:"#1a2a1a",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#ffffff",paperBot:"#fafcfa",bandW:0.075,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#1f5135","#2f6a48");},bandRule:"#1f5135",topRule:"#1f5135"}); } },

 { key:"ironside", name:"Ironside Executive", desc:"charcoal band · silver rule", group:"Professional", bodyL:0.2, dark:true,
   role:"", sal:"Dear Sir or Madam,", signoff:"Sincerely,", nameC:"#e6e8ea", roleC:"#9aa0a8", bodyC:"#e6e8ea",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#23262b",paperBot:"#1e2125",bandW:0.075,
     bandFill:function(ctx,bw,hh){bandGrad(ctx,bw,hh,"#2d3138","#383d45");},bandRule:"#9aa0a8",topRule:"#9aa0a8"}); } },

 { key:"courier", name:"Courier Plain", desc:"one gold keyline · everyday", group:"Professional", bodyL:0.13,
   role:"", sal:"Hello,", signoff:"Best,", nameC:"#3a2c18", roleC:"#7a6238", bodyC:"#3a2c18",
   paint:function(c,w,h){ oe(c,w,h,{paperTop:"#f8f4e9",paperBot:"#f4efe0",bandW:0.04,
     bandFill:function(ctx,bw,hh){ctx.fillStyle="#b8862c";ctx.fillRect(bw*0.6,0,2,hh);}}); } },

 // ── Plain — operator-requested "just a regular email" option, no letterhead.
 // sal/signoff are intentionally "" (blank): callers that fall back with
 // `Sta.setByKey(k).sal || "..."` must check `win.composeStationery==="plain"`
 // explicitly rather than relying on the `||`, since "" is falsy in QML/JS.
 { key:"plain", name:"Plain", desc:"no letterhead — just your letter", group:"Plain", bodyL:0.06,
   role:"", sal:"", signoff:"", nameC:"#1a1a1a", roleC:"#5a5a5a", bodyC:"#1a1a1a",
   paint:function(c,w,h){ paper(c,w,h,"#ffffff","#ffffff"); } },
];

function setByKey(k){ for(var i=0;i<SETS.length;i++) if(SETS[i].key===k) return SETS[i]; return SETS[0]; }
function groups(){ var g=[]; for(var i=0;i<SETS.length;i++) if(g.indexOf(SETS[i].group)<0) g.push(SETS[i].group); return g; }
