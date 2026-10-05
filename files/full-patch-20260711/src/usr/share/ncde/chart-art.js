// chart-art.js — painterly renderer for NCDEGeoChart.
// Drawn entirely with the Canvas 2D context, no image assets.
// Call:  Art.paint(ctx, W, H, P)  where P = { continents, palette }
// Deterministic: a seeded RNG means every repaint is identical (no flicker).
.pragma library

function mulberry32(a){ return function(){ a|=0; a=a+0x6D2B79F5|0; var t=Math.imul(a^a>>>15,1|a);
    t=t+Math.imul(t^t>>>7,61|t)^t; return ((t^t>>>14)>>>0)/4294967296; }; }

function px(lon,W){ return (lon+180)/360*W; }
function py(lat,H){ return (90-lat)/180*H; }

// ── vellum ground: warm radial + soft uneven blotches + fibre flecks ──
function paintVellum(ctx,W,H,C,rng){
    var g=ctx.createRadialGradient(W*0.42,H*0.36,12,W*0.5,H*0.5,Math.max(W,H)*0.78);
    g.addColorStop(0,C.vellum0); g.addColorStop(0.5,C.vellum1);
    g.addColorStop(0.82,C.vellum2); g.addColorStop(1,C.vellum3);
    ctx.fillStyle=g; ctx.fillRect(0,0,W,H);

    // large soft age-blotches
    ctx.globalCompositeOperation="multiply";
    for (var i=0;i<14;i++){
        var cx=rng()*W, cy=rng()*H, r=20+rng()*90, a=0.04+rng()*0.10;
        var b=ctx.createRadialGradient(cx,cy,0,cx,cy,r);
        b.addColorStop(0,"rgba(110,72,28,"+a+")"); b.addColorStop(1,"rgba(110,72,28,0)");
        ctx.fillStyle=b; ctx.beginPath(); ctx.arc(cx,cy,r,0,2*Math.PI); ctx.fill();
    }
    // pale bloom highlights
    for (var j=0;j<6;j++){
        var hx=rng()*W, hy=rng()*H, hr=30+rng()*70;
        var hb=ctx.createRadialGradient(hx,hy,0,hx,hy,hr);
        hb.addColorStop(0,"rgba(255,250,232,0.10)"); hb.addColorStop(1,"rgba(255,250,232,0)");
        ctx.fillStyle=hb; ctx.beginPath(); ctx.arc(hx,hy,hr,0,2*Math.PI); ctx.fill();
    }
    ctx.globalCompositeOperation="source-over";

    // faint fibre flecks
    ctx.globalAlpha=0.5;
    for (var f=0;f<140;f++){
        var x=rng()*W, y=rng()*H, len=1+rng()*3, ang=rng()*Math.PI;
        ctx.strokeStyle = rng()>0.5 ? "rgba(120,86,40,0.10)" : "rgba(255,248,228,0.12)";
        ctx.lineWidth=0.5; ctx.beginPath();
        ctx.moveTo(x,y); ctx.lineTo(x+Math.cos(ang)*len,y+Math.sin(ang)*len); ctx.stroke();
    }
    ctx.globalAlpha=1;
}

// ── graticule with degree ticks ──
function paintGraticule(ctx,W,H,C){
    ctx.strokeStyle=C.sepia; ctx.lineWidth=0.6;
    for (var r=1;r<=3;r++){ var y=H*r/4; ctx.globalAlpha=0.32; ctx.beginPath(); ctx.moveTo(0,y);
        for (var x=0;x<=W;x+=36) ctx.lineTo(x,y+Math.sin(x/55+r)*2); ctx.stroke(); }
    for (var c=1;c<=5;c++){ var xx=W*c/6; ctx.globalAlpha=0.32; ctx.beginPath(); ctx.moveTo(xx,0);
        for (var yy=0;yy<=H;yy+=36) ctx.lineTo(xx+Math.sin(yy/55+c)*2,yy); ctx.stroke(); }
    // tick ladder down the left meridian
    ctx.globalAlpha=0.4; ctx.lineWidth=0.7;
    for (var t=0;t<=H;t+=H/12){ ctx.beginPath(); ctx.moveTo(6,t); ctx.lineTo(11,t); ctx.stroke(); }
    ctx.globalAlpha=1;
}

// ── rhumb network from a compass origin ──
function paintRhumb(ctx,W,H,C,ox,oy){
    ctx.strokeStyle=C.wine4; ctx.globalAlpha=0.22; ctx.lineWidth=0.4;
    for (var a=0;a<32;a++){ var ang=a/32*2*Math.PI;
        ctx.beginPath(); ctx.moveTo(ox,oy);
        ctx.lineTo(ox+Math.cos(ang)*Math.max(W,H),oy+Math.sin(ang)*Math.max(W,H)); ctx.stroke(); }
    ctx.globalAlpha=1;
}

// ── one continent: depth contour, gradient fill, double ink, hatch, coast stipple ──
function paintLand(ctx,W,H,C,poly,rng){
    function trace(){ ctx.beginPath(); ctx.moveTo(px(poly[0][0],W),py(poly[0][1],H));
        for (var i=1;i<poly.length;i++) ctx.lineTo(px(poly[i][0],W),py(poly[i][1],H)); ctx.closePath(); }

    // bounding box for gradient
    var minx=1e9,miny=1e9,maxx=-1e9,maxy=-1e9;
    for (var i=0;i<poly.length;i++){ var X=px(poly[i][0],W),Y=py(poly[i][1],H);
        if(X<minx)minx=X; if(X>maxx)maxx=X; if(Y<miny)miny=Y; if(Y>maxy)maxy=Y; }

    // soft sea depth contour (halo just outside the coast)
    ctx.save(); trace(); ctx.lineWidth=5; ctx.strokeStyle="rgba(120,86,40,0.16)"; ctx.stroke();
    ctx.lineWidth=9; ctx.strokeStyle="rgba(120,86,40,0.08)"; ctx.stroke(); ctx.restore();

    // land gradient fill
    var g=ctx.createLinearGradient(0,miny,0,maxy);
    g.addColorStop(0,C.land0); g.addColorStop(1,C.land1);
    trace(); ctx.fillStyle=g; ctx.globalAlpha=0.94; ctx.fill(); ctx.globalAlpha=1;

    ctx.save(); trace(); ctx.clip();

    // soft inland colour wash — regions bleed from coast (paler) to heart (deeper)
    var cxm=(minx+maxx)/2, cym=(miny+maxy)/2, rad=Math.max(maxx-minx,maxy-miny)*0.6;
    var wash=ctx.createRadialGradient(cxm,cym,rad*0.1,cxm,cym,rad);
    wash.addColorStop(0,"rgba(150,112,58,0.30)");      // heartland
    wash.addColorStop(0.6,"rgba(120,86,40,0.10)");
    wash.addColorStop(1,"rgba(206,165,105,0.0)");      // coast
    ctx.fillStyle=wash; ctx.fillRect(minx,miny,maxx-minx,maxy-miny);

    // faint vellum hatch for tooth
    ctx.strokeStyle=C.sepia; ctx.globalAlpha=0.10; ctx.lineWidth=0.5;
    for (var hx=-H; hx<W; hx+=8){ ctx.beginPath(); ctx.moveTo(hx,0); ctx.lineTo(hx+H,H); ctx.stroke(); }
    ctx.globalAlpha=1;

    // ── illustrated mountain RANGES — drawn as overlapping ridgelines ──
    var ranges=1+Math.floor(rng()*2);
    for (var rg=0; rg<ranges; rg++){
        var rxs=minx+(0.2+rng()*0.5)*(maxx-minx), rys=miny+(0.2+rng()*0.5)*(maxy-miny);
        var dir=(rng()*2-1), peaks=4+Math.floor(rng()*5), step=3+rng()*2;
        var prevX=rxs, prevY=rys;
        for (var pk=0; pk<peaks; pk++){
            var s=2.4+rng()*2.6;                       // peak size, tapers along the chain
            var bx=prevX+step*(0.7+rng()*0.7), by=prevY+dir*step*(rng()*0.6-0.3);
            // back (shadow) face
            ctx.fillStyle="rgba(62,42,19,0.34)"; ctx.beginPath();
            ctx.moveTo(bx,by-s*1.7); ctx.lineTo(bx+s*0.9,by); ctx.lineTo(bx,by); ctx.closePath(); ctx.fill();
            // sunlit face
            ctx.fillStyle="rgba(150,112,58,0.55)"; ctx.beginPath();
            ctx.moveTo(bx,by-s*1.7); ctx.lineTo(bx-s*0.9,by); ctx.lineTo(bx,by); ctx.closePath(); ctx.fill();
            // snow/light cap fleck
            ctx.fillStyle="rgba(246,227,176,0.5)"; ctx.beginPath();
            ctx.moveTo(bx,by-s*1.7); ctx.lineTo(bx-s*0.28,by-s*1.1); ctx.lineTo(bx+s*0.2,by-s*1.1); ctx.closePath(); ctx.fill();
            // ink ridge
            ctx.strokeStyle="rgba(46,30,12,0.6)"; ctx.lineWidth=0.6; ctx.lineJoin="round";
            ctx.beginPath(); ctx.moveTo(bx-s*0.9,by); ctx.lineTo(bx,by-s*1.7); ctx.lineTo(bx+s*0.9,by); ctx.stroke();
            prevX=bx; prevY=by;
        }
    }

    // ── forest groves — clustered stipple "trees" ──
    var groves=2+Math.floor(rng()*3);
    for (var gv2=0; gv2<groves; gv2++){
        var fx=minx+rng()*(maxx-minx), fy=miny+rng()*(maxy-miny), fn=6+Math.floor(rng()*10);
        for (var tr=0; tr<fn; tr++){
            var tx=fx+(rng()*2-1)*7, ty=fy+(rng()*2-1)*5;
            ctx.fillStyle="rgba(44,72,40,0.42)";       // muted forest green
            ctx.beginPath(); ctx.arc(tx,ty,1.5,0,2*Math.PI); ctx.fill();
            ctx.strokeStyle="rgba(36,58,32,0.5)"; ctx.lineWidth=0.4;
            ctx.beginPath(); ctx.moveTo(tx,ty+0.5); ctx.lineTo(tx,ty-2.2); ctx.stroke();
        }
    }

    // marsh/heath dot-stipple in a couple of lowland patches
    ctx.globalAlpha=0.22; ctx.fillStyle=C.sepiaDeep;
    var patches=2+Math.floor(rng()*2);
    for (var pa=0; pa<patches; pa++){
        var px0=minx+rng()*(maxx-minx), py0=miny+rng()*(maxy-miny);
        for (var st=0; st<16; st++){
            ctx.beginPath(); ctx.arc(px0+(rng()*2-1)*9, py0+(rng()*2-1)*6, 0.55, 0, 2*Math.PI); ctx.fill();
        }
    }
    ctx.restore(); ctx.globalAlpha=1;

    // double-inked coastline: soft outer, crisp inner
    trace(); ctx.lineWidth=2.4; ctx.strokeStyle="rgba(62,42,19,0.4)"; ctx.stroke();
    trace(); ctx.lineWidth=1.2; ctx.strokeStyle=C.sepiaDeep; ctx.stroke();

    // tiny coastal vertices as ink dots
    ctx.fillStyle=C.sepiaDeep; ctx.globalAlpha=0.5;
    for (var v=0;v<poly.length;v+=2){ ctx.beginPath(); ctx.arc(px(poly[v][0],W),py(poly[v][1],H),0.8,0,2*Math.PI); ctx.fill(); }
    ctx.globalAlpha=1;
}

// ── sea: drifting stipple + a few wave glyphs ──
function paintSea(ctx,W,H,C,rng){
    ctx.fillStyle=C.sepia; ctx.globalAlpha=0.28;
    for (var i=0;i<70;i++){ ctx.beginPath(); ctx.arc(rng()*W,rng()*H,0.8,0,2*Math.PI); ctx.fill(); }
    ctx.globalAlpha=0.3; ctx.strokeStyle=C.sepia; ctx.lineWidth=0.6;
    for (var w=0;w<10;w++){ var x=rng()*W, y=rng()*H;
        ctx.beginPath(); ctx.moveTo(x,y);
        ctx.quadraticCurveTo(x+4,y-3,x+8,y); ctx.quadraticCurveTo(x+12,y+3,x+16,y); ctx.stroke(); }
    ctx.globalAlpha=1;
}

// ── stained-glass compass rose (leaded glass, gold star) ──
function paintCompass(ctx,cx,cy,R,C){
    ctx.save(); ctx.translate(cx,cy);
    var lead="#101418";                       // black leading

    // outer lead ring
    ctx.beginPath(); ctx.arc(0,0,R,0,2*Math.PI);
    ctx.fillStyle=lead; ctx.fill();

    // segmented blue/white glass border ring
    var segs=16, rOut=R*0.97, rIn=R*0.74;
    for (var s=0;s<segs;s++){
        var a0=s/segs*2*Math.PI - Math.PI/segs, a1=(s+1)/segs*2*Math.PI - Math.PI/segs;
        var gap=0.05;
        ctx.beginPath();
        ctx.arc(0,0,rOut,a0+gap,a1-gap);
        ctx.arc(0,0,rIn,a1-gap,a0+gap,true);
        ctx.closePath();
        ctx.fillStyle = (s%2===0) ? "#5fa8d8" : "#eef4f7";   // cobalt / milk glass
        ctx.fill();
        ctx.lineWidth=R*0.02; ctx.strokeStyle=lead; ctx.stroke();
    }

    // inner concentric glass: cobalt → indigo → violet
    function disc(rr,col){ ctx.beginPath(); ctx.arc(0,0,rr,0,2*Math.PI); ctx.fillStyle=col; ctx.fill();
        ctx.lineWidth=R*0.022; ctx.strokeStyle=lead; ctx.stroke(); }
    disc(R*0.70,"#2f6fb0");
    disc(R*0.60,"#3a4f9e");
    disc(R*0.50,"#4a3d82");
    disc(R*0.42,"#3a2f63");

    // 8-point gold star — diagonals short, cardinals long
    function point(rot,len,wid,fill,hi){ ctx.save(); ctx.rotate(rot);
        ctx.beginPath(); ctx.moveTo(0,-len); ctx.lineTo(wid,-wid*0.7); ctx.lineTo(0,0); ctx.lineTo(-wid,-wid*0.7); ctx.closePath();
        ctx.fillStyle=fill; ctx.fill();
        // inner highlight sliver
        ctx.beginPath(); ctx.moveTo(0,-len); ctx.lineTo(wid*0.32,-wid*0.7); ctx.lineTo(0,0); ctx.closePath();
        ctx.fillStyle=hi; ctx.fill();
        ctx.lineWidth=R*0.02; ctx.strokeStyle=lead; ctx.lineJoin="round";
        ctx.beginPath(); ctx.moveTo(0,-len); ctx.lineTo(wid,-wid*0.7); ctx.lineTo(0,0); ctx.lineTo(-wid,-wid*0.7); ctx.closePath(); ctx.stroke();
        ctx.restore(); }
    // diagonals (short, deeper gold)
    for (var k=0;k<4;k++) point(Math.PI/4 + k*Math.PI/2, R*0.40, R*0.085, "#d99a3a", "#f6e3b0");
    // cardinals E/S/W (long, bright gold)
    point(Math.PI/2, R*0.66, R*0.10, "#f1c54a", "#fff6d8");
    point(Math.PI,   R*0.66, R*0.10, "#f1c54a", "#fff6d8");
    point(-Math.PI/2,R*0.66, R*0.10, "#f1c54a", "#fff6d8");
    // North — long with an ornate fleur tip
    point(0, R*0.70, R*0.11, "#f1c54a", "#fff6d8");
    // fleur curl at the north tip
    ctx.save();
    ctx.strokeStyle=lead; ctx.lineWidth=R*0.03; ctx.lineCap="round"; ctx.fillStyle="#f1c54a";
    ctx.beginPath(); ctx.arc(-R*0.06,-R*0.74,R*0.05,0.2*Math.PI,1.9*Math.PI); ctx.stroke();
    ctx.beginPath(); ctx.arc( R*0.06,-R*0.74,R*0.05,-0.9*Math.PI,0.8*Math.PI); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(0,-R*0.66); ctx.lineTo(0,-R*0.86); ctx.stroke();
    ctx.restore();

    // central boss
    ctx.beginPath(); ctx.arc(0,0,R*0.085,0,2*Math.PI); ctx.fillStyle="#d99a3a"; ctx.fill();
    ctx.lineWidth=R*0.02; ctx.strokeStyle=lead; ctx.stroke();
    ctx.beginPath(); ctx.arc(-R*0.025,-R*0.025,R*0.035,0,2*Math.PI); ctx.fillStyle="#fff6d8"; ctx.fill();

    // crisp outer rim
    ctx.beginPath(); ctx.arc(0,0,R,0,2*Math.PI); ctx.lineWidth=R*0.04; ctx.strokeStyle=lead; ctx.stroke();
    ctx.restore();
}

// ── flourishes: sea serpent, whale, galleon ──
function paintFlourishes(ctx,W,H,C){
    ctx.strokeStyle=C.sepiaDeep; ctx.fillStyle=C.sepiaDeep;
    // serpent (lower-left)
    var mx=W*0.05, my=H*0.86; ctx.globalAlpha=0.55; ctx.lineWidth=1.5;
    ctx.beginPath(); ctx.moveTo(mx,my);
    ctx.bezierCurveTo(mx+14,my-12,mx+24,my+2,mx+36,my-8);
    ctx.bezierCurveTo(mx+48,my-16,mx+58,my,mx+70,my-10); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(mx+64,my-12);
    ctx.bezierCurveTo(mx+70,my-17,mx+75,my-12,mx+70,my-6);
    ctx.bezierCurveTo(mx+66,my-2,mx+61,my-7,mx+64,my-12); ctx.closePath(); ctx.fill();
    // spouting whale (upper-left sea)
    var wx=W*0.16, wy=H*0.2; ctx.globalAlpha=0.4; ctx.lineWidth=1.2;
    ctx.beginPath(); ctx.moveTo(wx,wy); ctx.bezierCurveTo(wx+10,wy-6,wx+26,wy-6,wx+34,wy);
    ctx.bezierCurveTo(wx+26,wy+6,wx+10,wy+6,wx,wy); ctx.closePath(); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(wx+34,wy); ctx.lineTo(wx+42,wy-5); ctx.lineTo(wx+40,wy+2); ctx.closePath(); ctx.fill();
    ctx.beginPath(); ctx.moveTo(wx+6,wy-4); ctx.quadraticCurveTo(wx+2,wy-12,wx+8,wy-14); ctx.stroke();
    // galleon (right sea)
    var gx=W*0.8, gy=H*0.78; ctx.globalAlpha=0.55;
    ctx.beginPath(); ctx.moveTo(gx,gy); ctx.lineTo(gx+40,gy); ctx.lineTo(gx+34,gy+8); ctx.lineTo(gx+6,gy+8); ctx.closePath(); ctx.fill();
    ctx.lineWidth=1.1; ctx.beginPath(); ctx.moveTo(gx+20,gy-20); ctx.lineTo(gx+20,gy); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(gx+20,gy-18); ctx.bezierCurveTo(gx+32,gy-14,gx+32,gy-4,gx+20,gy-2); ctx.closePath();
    ctx.globalAlpha=0.4; ctx.fill();
    ctx.globalAlpha=1;
}

// ── gold-leaf ornamental border with corner knots ──
function paintBorder(ctx,W,H,C){
    // outer gold-leaf band with diagonal sheen
    ctx.save();
    ctx.beginPath(); ctx.rect(2,2,W-4,H-4); ctx.rect(13,13,W-26,H-26); ctx.clip("evenodd");
    var g=ctx.createLinearGradient(0,0,W,H);
    g.addColorStop(0,C.gilt2); g.addColorStop(0.25,C.gilt5); g.addColorStop(0.5,C.gilt3);
    g.addColorStop(0.75,C.gilt5); g.addColorStop(1,C.gilt2);
    ctx.fillStyle=g; ctx.fillRect(0,0,W,H);
    // sheen hatching
    ctx.strokeStyle="rgba(255,250,232,0.35)"; ctx.lineWidth=0.5;
    for (var x=-H;x<W;x+=5){ ctx.beginPath(); ctx.moveTo(x,0); ctx.lineTo(x+H,H); ctx.stroke(); }
    ctx.restore();
    // crisp rules either side of the band
    ctx.strokeStyle=C.sepiaDeep; ctx.lineWidth=1; ctx.globalAlpha=0.8;
    ctx.strokeRect(2,2,W-4,H-4); ctx.strokeRect(13,13,W-26,H-26);
    ctx.globalAlpha=1;
    // corner florets
    var pts=[[13,13,1,1],[W-13,13,-1,1],[13,H-13,1,-1],[W-13,H-13,-1,-1]];
    for (var p=0;p<pts.length;p++){ var q=pts[p];
        ctx.save(); ctx.translate(q[0],q[1]); ctx.scale(q[2],q[3]);
        ctx.strokeStyle=C.sepiaDeep; ctx.lineWidth=1; ctx.globalAlpha=0.7;
        ctx.beginPath(); ctx.moveTo(2,16); ctx.bezierCurveTo(2,7,7,2,16,2); ctx.stroke();
        ctx.beginPath(); ctx.moveTo(2,22); ctx.bezierCurveTo(2,10,10,2,22,2); ctx.stroke();
        ctx.fillStyle=C.wine3; ctx.beginPath(); ctx.arc(8,8,2.4,0,2*Math.PI); ctx.fill();
        ctx.fillStyle=C.gilt5; ctx.beginPath(); ctx.arc(7,7,1,0,2*Math.PI); ctx.fill();
        ctx.restore(); ctx.globalAlpha=1;
    }
}

// ── scorched edge + a couple of burn holes ──
function paintScorch(ctx,W,H,rng){
    var steps=28;
    for (var s=0;s<steps;s++){ var a=(1-s/steps)*0.5; ctx.strokeStyle="rgba(62,42,19,"+a+")";
        ctx.lineWidth=1; ctx.strokeRect(s,s,W-2*s,H-2*s); }
    // burn holes on two edges
    function burn(cx,cy,r){ var g=ctx.createRadialGradient(cx,cy,0,cx,cy,r);
        g.addColorStop(0,"rgba(20,10,4,0.6)"); g.addColorStop(0.6,"rgba(62,42,19,0.4)"); g.addColorStop(1,"rgba(62,42,19,0)");
        ctx.fillStyle=g; ctx.beginPath(); ctx.arc(cx,cy,r,0,2*Math.PI); ctx.fill(); }
    burn(W*0.03, H*0.5, 16); burn(W*0.7, H*0.02, 13);
}

// ── calligraphic spaced label (manual letter-tracking for the period look) ──
function spacedText(ctx, str, cx, cy, track, align){
    var widths=[], total=0;
    for (var i=0;i<str.length;i++){ var w=ctx.measureText(str[i]).width; widths.push(w); total+=w+track; }
    total-=track;
    var x = align==="center" ? cx-total/2 : cx;
    for (var j=0;j<str.length;j++){ ctx.fillText(str[j], x, cy); x+=widths[j]+track; }
}
function paintLabels(ctx,W,H,C,labels){
    function px(lon){ return (lon+180)/360*W; }
    function py(lat){ return (90-lat)/180*H; }
    for (var i=0;i<labels.length;i++){
        var L=labels[i];
        var size=L.size||13, italic=L.italic?"italic ":"";
        ctx.font = italic+size+"px '"+(L.font||"Cinzel")+"', serif";
        ctx.textBaseline="middle";
        ctx.fillStyle = L.sea ? "rgba(47,90,110,0.7)" : "rgba(62,42,19,0.78)";
        ctx.save(); ctx.translate(px(L.lon),py(L.lat)); if (L.rot) ctx.rotate(L.rot*Math.PI/180);
        // faint raised highlight then ink
        ctx.fillStyle="rgba(255,247,222,0.5)"; spacedText(ctx,L.text,0.6,1.2,(L.track==null?2:L.track),"center");
        ctx.fillStyle = L.sea ? "rgba(40,80,100,0.72)" : "rgba(62,42,19,0.8)";
        spacedText(ctx,L.text,0,0,(L.track==null?2:L.track),"center");
        ctx.restore();
    }
    ctx.textBaseline="alphabetic";
}

// ── title cartouche: a scroll with curled ends ──
function paintCartouche(ctx,W,H,C,title,subtitle){
    var cw=Math.min(260,W*0.42), ch=46, cx=W*0.5-cw/2, cy=H-ch-14;
    // curled rods
    function rod(x){ ctx.save(); ctx.translate(x,cy+ch/2);
        var g=ctx.createLinearGradient(0,-ch/2,0,ch/2); g.addColorStop(0,C.gilt5); g.addColorStop(0.5,C.gilt3); g.addColorStop(1,C.gilt1);
        ctx.fillStyle=g; ctx.beginPath(); ctx.arc(0,0,ch*0.42,0,2*Math.PI); ctx.fill();
        ctx.strokeStyle=C.sepiaDeep; ctx.lineWidth=1; ctx.stroke();
        ctx.beginPath(); ctx.arc(0,0,ch*0.16,0,2*Math.PI); ctx.strokeStyle=C.wine3; ctx.stroke(); ctx.restore(); }
    // parchment body
    var bg=ctx.createLinearGradient(0,cy,0,cy+ch); bg.addColorStop(0,C.vellum0); bg.addColorStop(1,C.vellum2);
    ctx.fillStyle=bg; ctx.strokeStyle=C.sepiaDeep; ctx.lineWidth=1.2;
    ctx.beginPath(); ctx.moveTo(cx,cy); ctx.lineTo(cx+cw,cy);
    ctx.lineTo(cx+cw,cy+ch); ctx.lineTo(cx,cy+ch); ctx.closePath(); ctx.fill(); ctx.stroke();
    // top/bottom fold shadows
    ctx.fillStyle="rgba(62,42,19,0.12)"; ctx.fillRect(cx,cy,cw,4); ctx.fillRect(cx,cy+ch-4,cw,4);
    rod(cx); rod(cx+cw);
    // gilt inner rule
    ctx.strokeStyle=C.gilt3; ctx.globalAlpha=0.7; ctx.lineWidth=0.8; ctx.strokeRect(cx+6,cy+5,cw-12,ch-10); ctx.globalAlpha=1;
    // title
    ctx.fillStyle=C.wine2; ctx.textAlign="center"; ctx.textBaseline="middle";
    ctx.font="700 19px 'Cinzel Decorative', serif";
    spacedText(ctx,title,W*0.5,cy+ (subtitle?17:ch/2),2,"center");
    if (subtitle){ ctx.fillStyle=C.sepia; ctx.font="italic 11px 'IM Fell English', serif";
        ctx.fillText(subtitle, W*0.5, cy+ch-13); }
    ctx.textAlign="start"; ctx.textBaseline="alphabetic";
}
function paint(ctx, W, H, P){
    var C = P.palette;
    var rng = mulberry32(0x9E3779B1 ^ Math.round(W) ^ (Math.round(H)<<8));
    ctx.reset();
    paintVellum(ctx,W,H,C,rng);
    paintGraticule(ctx,W,H,C);
    var ox=W-W*0.10, oy=H*0.19;                 // compass origin (top-right)
    paintRhumb(ctx,W,H,C,ox,oy);
    paintSea(ctx,W,H,C,rng);
    for (var i=0;i<P.continents.length;i++) paintLand(ctx,W,H,C,P.continents[i],rng);
    paintFlourishes(ctx,W,H,C);
    paintCompass(ctx,ox,oy,Math.min(W,H)*0.095,C);
    if (P.labels && P.labels.length) paintLabels(ctx,W,H,C,P.labels);
    paintBorder(ctx,W,H,C);
    if (P.title) paintCartouche(ctx,W,H,C,P.title,P.subtitle||"");
    paintScorch(ctx,W,H,rng);
}
