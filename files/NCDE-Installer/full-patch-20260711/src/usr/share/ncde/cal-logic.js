.pragma library
.import "ncde-color.js" as Col
// cal-logic.js — shared pure logic for Leap Frog Ledger (QML build).
// Date utils, recurrence expansion, astronomy, holidays, categories.
// NO storage here: appointment/todo data + persistence live in the C++
// `calBackend`. Recurrence functions take the appointments array as input.
// (Mirrors the browser prototype's cal-core.js logic exactly.)

var CATEGORIES = {
  azure:    { label: "Affairs",  color: "#3a6ea5", gem: "#5b9bd5" },
  verdant:  { label: "Personal", color: "#4a7a45", gem: "#6ab04c" },
  garnet:   { label: "Urgent",   color: "#8a2230", gem: "#c0392b" },
  amethyst: { label: "Social",   color: "#6a3a8a", gem: "#9b59b6" },
  amber:    { label: "Travel",   color: "#b87a18", gem: "#f1c40f" },
  teal:     { label: "Health",   color: "#1d6b58", gem: "#1abc9c" }
};
// The hexes above are only each category's hue identity (Affairs is blue,
// Urgent is red…). What the Ledger paints comes from cat(): the same hue,
// pulled 15% toward the palette accent and re-made at the palette's weight,
// so the categories belong to whichever Iris palette is active (operator,
// 2026-09-24: the palette is universal). k = the caller's NCDEKit.
//   gem   — dots, bars, swatches: jewel tone, at least 3:1 on the page
//   color — text (appointment times): kept readable (4.5:1) on the page
function cat(key, k) {
  var base = CATEGORIES[key] || CATEGORIES.azure;
  if (!k) return base;
  var ground = k.surfaceAlt, dark = k.dark;
  return { label: base.label,
           gem:   Col.readable(Col.harmonize(base.gem, k.accent, dark ? 66 : 54, 44, 0.15), ground, 3.0),
           color: Col.readable(Col.harmonize(base.color, k.accent, dark ? 76 : 38, 40, 0.15), ground, 4.5) };
}
var MONTHS = ["January","February","March","April","May","June","July","August","September","October","November","December"];
var DOW = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];
var DOW_FULL = ["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"];
var ZODIAC_NAME = ["Aries","Taurus","Gemini","Cancer","Leo","Virgo","Libra","Scorpio","Sagittarius","Capricorn","Aquarius","Pisces"];

function pad(n){ return (""+n).length<2 ? "0"+n : ""+n; }
function iso(d){ return d.getFullYear()+"-"+pad(d.getMonth()+1)+"-"+pad(d.getDate()); }
function fromIso(s){ var p=s.split("-"); return new Date(+p[0], +p[1]-1, +p[2]); }
function addDays(d,n){ var x=new Date(d); x.setDate(x.getDate()+n); return x; }
function sameDay(a,b){ return iso(a)===iso(b); }
function startOfWeek(d){ return addDays(d, -d.getDay()); }

function weekNumber(d){
  var date=new Date(Date.UTC(d.getFullYear(),d.getMonth(),d.getDate()));
  var dayNum=(date.getUTCDay()+6)%7; date.setUTCDate(date.getUTCDate()-dayNum+3);
  var ft=new Date(Date.UTC(date.getUTCFullYear(),0,4));
  return 1+Math.round((date-ft)/604800000);
}
function moonPhase(d){ var jd=d.getTime()/86400000+2440587.5; var dsn=(jd-2451549.5)%29.53058867; if(dsn<0)dsn+=29.53058867; return dsn/29.53058867; }
function moonBucket(d){ return Math.round(moonPhase(d)*8)%8; }
function zodiacOfMonth(m){ return [9,10,11,0,1,2,3,4,5,6,7,8][m]; }
function season(m){ if(m<=1||m===11)return"winter"; if(m<=4)return"spring"; if(m<=7)return"summer"; return"autumn"; }

// ── Fixed holidays / feast days with a short almanac note (lore) ──
var HOLIDAYS = {
  "01-01": { name: "New Year's Day", lore: "The Gregorian year turns. Romans dedicated the day to Janus, the two-faced god of doorways — one face to the year past, one to the year ahead." },
  "02-02": { name: "Groundhog Day", lore: "A Pennsylvania-Dutch folk custom rooted in Candlemas: if the creature sees its shadow, six more weeks of winter." },
  "02-14": { name: "St. Valentine's Day", lore: "Named for a 3rd-century martyr, but its romance is medieval — Chaucer first tied the feast to birds choosing their mates in February." },
  "03-17": { name: "St. Patrick's Day", lore: "Marks the death of Ireland's patron saint (c. 461). The shamrock, legend says, he used to teach the Trinity — three leaves, one stem." },
  "04-22": { name: "Earth Day", lore: "First held in 1970, when 20 million Americans rallied for the environment. It helped spur the EPA and the Clean Air and Water Acts." },
  "05-01": { name: "May Day", lore: "An ancient spring festival — Beltane fires, maypole dances, flower crowns — later doubled as International Workers' Day after the 1886 Haymarket affair." },
  "06-14": { name: "Flag Day", lore: "Commemorates 1777, when the Continental Congress adopted the Stars and Stripes. Made official by President Wilson in 1916." },
  "06-19": { name: "Juneteenth", lore: "June 19, 1865 — Union troops reached Galveston, Texas and enforced emancipation, two and a half years after the Proclamation. Now a U.S. federal holiday." },
  "06-21": { name: "Summer Solstice", lore: "The sun reaches its northernmost point; the longest day. Marked from Stonehenge to Scandinavia with fire and vigil." },
  "07-04": { name: "Independence Day", lore: "In 1776 the Continental Congress adopted the Declaration of Independence. John Adams imagined it celebrated with 'illuminations' — fireworks — forever after." },
  "10-31": { name: "All Hallows' Eve", lore: "The night before All Saints' Day, blended with the Celtic Samhain — when the veil between worlds was thought thinnest. Source of our Halloween." },
  "11-01": { name: "All Saints' Day", lore: "A Christian feast honoring all saints, known and unknown. Its eve became Hallowe'en; the following day, All Souls', remembers the departed." },
  "11-11": { name: "Veterans Day", lore: "Once Armistice Day — the guns of the First World War fell silent at the 11th hour of the 11th day of the 11th month, 1918." },
  "12-21": { name: "Winter Solstice", lore: "The longest night; the sun stands still and turns back toward spring. Yule fires and evergreens promised the light's return." },
  "12-24": { name: "Christmas Eve", lore: "The vigil before the Nativity. Many of its customs — candles, carols, the tree — are Northern European midwinter traditions grafted onto the feast." },
  "12-25": { name: "Christmas", lore: "The Nativity feast, fixed at December 25th by the 4th century — near the old Roman Sol Invictus and the solstice, the sun's rebirth." },
  "12-31": { name: "New Year's Eve", lore: "The old year's last night. 'Auld Lang Syne,' Robert Burns's 1788 verse, became its anthem — 'for old times' sake.'" }
};
function hkey(d){ return pad(d.getMonth()+1)+"-"+pad(d.getDate()); }

// ── Computed holy days (2026-09-24, operator: "we have Jews using it as well") ──
// Jewish holidays follow the Hebrew calendar and Easter follows the moon, so
// neither can live in the fixed table above: both are COMPUTED per year (no
// hand-typed dates to go stale). Verified against Hebcal: 112/112 Jewish dates
// 2020–2035, and Easter 2020–2030. Jewish days begin at sundown, so each major
// festival also gets an "Erev …" entry on the civil evening before. Diaspora
// observance (two-day festivals, Simchat Torah on 23 Tishrei).
// ── Hebrew calendar (Dershowitz & Reingold, "Calendrical Calculations") ──
// Fixed day numbers (RD): RD 1 = Monday, January 1, year 1 (proleptic Gregorian).
var HEB_EPOCH = -1373427;                       // RD of 1 Tishrei, AM 1
function hebLeap(y){ return ((7*y + 1) % 19) < 7; }
function hebElapsed(y){                          // days from epoch to molad-based new year
  var months = Math.floor((235*y - 234) / 19);
  var parts  = 12084 + 13753*months;
  var day    = 29*months + Math.floor(parts / 25920);
  return ((3*(day + 1)) % 7) < 3 ? day + 1 : day;  // lo ADU Rosh
}
function hebNewYearDelay(y){
  var ny0 = hebElapsed(y-1), ny1 = hebElapsed(y), ny2 = hebElapsed(y+1);
  if (ny2 - ny1 === 356) return 2;
  if (ny1 - ny0 === 382) return 1;
  return 0;
}
function roshHashanahRD(y){ return HEB_EPOCH + hebElapsed(y) + hebNewYearDelay(y); }
function rdToDate(rd){                           // RD -> local Date at midnight
  var u = new Date(Date.UTC(1970, 0, 1) + (rd - 719163) * 86400000);
  return new Date(u.getUTCFullYear(), u.getUTCMonth(), u.getUTCDate());
}
// Day-of-Hebrew-year (0 = 1 Tishrei) of (month, day). month: 7 Tishrei, 8 Cheshvan,
// 9 Kislev, 10 Tevet, 11 Shevat, 12 Adar (Adar I in a leap year), 13 Adar II, 1 Nisan … 6 Elul.
function hebMonthLengths(y){
  var len = roshHashanahRD(y+1) - roshHashanahRD(y);    // 353/354/355 or 383/384/385
  var ches = (len % 10 === 5) ? 30 : 29;                // complete year: long Cheshvan
  var kis  = (len % 10 === 3) ? 29 : 30;                // deficient year: short Kislev
  var leap = hebLeap(y);
  // civil order from Tishrei
  var order = leap ? [7,8,9,10,11,12,13,1,2,3,4,5,6] : [7,8,9,10,11,12,1,2,3,4,5,6];
  var lens  = { 7:30, 8:ches, 9:kis, 10:29, 11:30, 12:(leap?30:29), 13:29, 1:30, 2:29, 3:30, 4:29, 5:30, 6:29 };
  return { order: order, lens: lens, leap: leap };
}
function hebToRD(y, month, day){
  var ml = hebMonthLengths(y), rd = roshHashanahRD(y);
  for (var i = 0; i < ml.order.length && ml.order[i] !== month; i++) rd += ml.lens[ml.order[i]];
  return rd + day - 1;
}
function hebDate(y, month, day){ return rdToDate(hebToRD(y, month, day)); }
function purimMonth(y){ return hebLeap(y) ? 13 : 12; }   // Purim is in Adar II in a leap year

// ── Western Easter (Gregorian computus, "Anonymous Gregorian" algorithm) ──
function easter(Y){
  var a=Y%19, b=Math.floor(Y/100), c=Y%100, d=Math.floor(b/4), e=b%4,
      f=Math.floor((b+8)/25), g=Math.floor((b-f+1)/3), h=(19*a+b-d-g+15)%30,
      i=Math.floor(c/4), k=c%4, l=(32+2*e+2*i-h-k)%7, m=Math.floor((a+11*h+22*l)/451),
      mo=Math.floor((h+l-7*m+114)/31), da=((h+l-7*m+114)%31)+1;
  return new Date(Y, mo-1, da);
}

var LILITH = { name: "Lilith's Cave", lore: "On this night, dear children, Lilith makes her home in every mirror. Jewish legend makes her Adam's first wife, who fled Eden for the shores of the Red Sea and became queen of the night-demons; Howard Schwartz gathered the old tales of her in Lilith's Cave (1988)." };

var JEWISH_LORE = {
  rh:     "The Jewish New Year, 1 Tishrei, remembered as the birthday of the world. The shofar is sounded, and apples dipped in honey wish everyone a sweet year.",
  yk:     "The Day of Atonement, holiest day of the Jewish year: a 25-hour fast of prayer and repentance that closes at nightfall with Ne'ilah and one long blast of the shofar.",
  sukkot: "The Festival of Booths. For seven days families eat, and some sleep, in a sukkah, a leaf-roofed hut recalling the Israelites' years in the wilderness, and wave the lulav and etrog.",
  hr:     "The seventh day of Sukkot, when willow branches are beaten on the ground. Folklore holds that the year's verdicts, written on Rosh Hashanah, are finally sealed tonight.",
  sa:     "'The Eighth Day of Assembly' closes the autumn festivals; the prayer for rain is recited for the first time since spring.",
  st:     "'Rejoicing in the Torah': the year's cycle of readings ends and at once begins again at Genesis, and the scrolls are carried round the synagogue in joyful dancing.",
  chan:   "The Festival of Lights recalls the Maccabees rededicating the Temple in 164 BCE, and the one day's oil that burned for eight. Each night one more candle is lit on the menorah.",
  tubsh:  "The New Year of the Trees. Almonds blossom in the Land of Israel; the day is kept with fruits of the land and, in modern times, by planting trees.",
  purim:  "Esther and Mordecai foil Haman's plot in Persia. The Megillah is read aloud, with noisemakers drowning out Haman's name; costumes are worn and gifts of food exchanged.",
  pesach: "Passover recalls the Exodus from Egypt. The seder tells the story over matzah, bitter herbs and four cups of wine, and for eight days nothing leavened is eaten.",
  shoah:  "Holocaust Remembrance Day. In Israel a siren sounds and the whole country stands still for two minutes, in memory of the six million.",
  lag:    "The 33rd day of the Omer, a break in weeks of mourning: bonfires, picnics and first haircuts, in honor of the sage Rabbi Shimon bar Yochai.",
  shav:   "The Feast of Weeks, seven weeks after Passover, celebrates the giving of the Torah at Sinai. Homes are decked in greenery; dairy foods and the Book of Ruth are traditional.",
  av:     "The saddest day of the Jewish year: a fast mourning the destruction of both Temples in Jerusalem, when Lamentations is chanted by low light.",
  erev:   "Jewish days run from evening to evening (\"there was evening and there was morning\"), so the festival begins at sundown tonight."
};
var CHRISTIAN_LORE = {
  shrove: "The last feast before Lent: pancakes in England, parades in New Orleans. Mardi Gras is simply French for 'Fat Tuesday'.",
  ash:    "Lent begins. Ashes are traced on the forehead in a cross: 'remember that you are dust, and to dust you shall return.'",
  palm:   "Recalls Jesus entering Jerusalem to crowds waving palm branches. Holy Week begins.",
  maundy: "The Last Supper. 'Maundy' comes from the Latin mandatum, the new commandment to love one another.",
  good:   "Commemorates the Crucifixion, the most solemn day of the Christian year; in many churches the altar is stripped bare.",
  easter: "The Resurrection, oldest and greatest of Christian feasts. It follows the moon: the first Sunday after the first full moon on or after the spring equinox.",
  pent:   "Fifty days after Easter the Holy Spirit descends on the apostles as tongues of fire. Once called Whitsunday, for the white robes of the newly baptized.",
  advent: "The church year begins: four Sundays of waiting for Christmas, one more candle lit on the Advent wreath each week."
};

var _yearCache = {};
// Every holiday of Gregorian year G as a map "YYYY-MM-DD" -> [{ name, lore }].
function holidaysOfYear(G){
  if (_yearCache[G]) return _yearCache[G];
  var m = {};
  // cont = a festival's continuation day: marked on the month grid, left out of the year's list
  function put(d, name, lore, cont){ if (d.getFullYear() !== G) return; var k = iso(d); (m[k] = m[k] || []).push({ name: name, lore: lore, cont: !!cont }); }
  // Halloween's Lilith first (operator's line leads the day), then the fixed table (unchanged)
  put(new Date(G, 9, 31), LILITH.name, LILITH.lore);
  for (var key in HOLIDAYS) put(new Date(G, parseInt(key.slice(0,2),10)-1, parseInt(key.slice(3),10)), HOLIDAYS[key].name, HOLIDAYS[key].lore);
  // Christian movable feasts
  var e = easter(G), J = JEWISH_LORE, C = CHRISTIAN_LORE;
  put(addDays(e,-47), "Shrove Tuesday", C.shrove); put(addDays(e,-46), "Ash Wednesday", C.ash);
  put(addDays(e,-7), "Palm Sunday", C.palm);        put(addDays(e,-3), "Maundy Thursday", C.maundy);
  put(addDays(e,-2), "Good Friday", C.good);        put(e, "Easter", C.easter);
  put(addDays(e,49), "Pentecost", C.pent);
  var xmas = new Date(G, 11, 25), back = xmas.getDay() === 0 ? 7 : xmas.getDay();
  put(addDays(xmas, -back - 21), "First Sunday of Advent", C.advent);
  // Jewish holidays: spring ones from Hebrew year G+3760, autumn ones from G+3761;
  // Hanukkah from both (it can straddle New Year's Day).
  function erev(d, name){ put(addDays(d,-1), "Erev " + name, J.erev); }
  for (var hy = G + 3760; hy <= G + 3761; hy++) {
    var rh = hebDate(hy,7,1);   erev(rh, "Rosh Hashanah");
    put(rh, "Rosh Hashanah " + hy, J.rh); put(addDays(rh,1), "Rosh Hashanah (day 2)", J.rh, true);
    var yk = hebDate(hy,7,10);  erev(yk, "Yom Kippur"); put(yk, "Yom Kippur", J.yk);
    var sk = hebDate(hy,7,15);  erev(sk, "Sukkot");
    for (var i = 0; i < 6; i++) put(addDays(sk,i), i ? "Sukkot (day " + (i+1) + ")" : "Sukkot", J.sukkot, i > 0);
    put(hebDate(hy,7,21), "Hoshana Rabbah", J.hr);
    put(hebDate(hy,7,22), "Shemini Atzeret", J.sa); put(hebDate(hy,7,23), "Simchat Torah", J.st);
    var ch = hebDate(hy,9,25);  put(addDays(ch,-1), "Erev Hanukkah", "Hanukkah begins at sundown: tonight the first candle is lit. " + J.chan);
    for (i = 0; i < 8; i++) put(addDays(ch,i), "Hanukkah day " + (i+1), J.chan, i > 0);   // short: month cells are narrow
    put(hebDate(hy,11,15), "Tu BiShvat", J.tubsh);
    put(hebDate(hy,purimMonth(hy),14), "Purim", J.purim);
    var ps = hebDate(hy,1,15);  put(addDays(ps,-1), "Erev Passover", "The first seder is tonight. " + J.pesach);
    put(ps, "Passover", J.pesach); put(addDays(ps,1), "Passover (day 2)", J.pesach, true); put(addDays(ps,7), "Passover (last day)", J.pesach);
    var sh = hebDate(hy,1,27), dw = sh.getDay();          // moved off Fri/Sun so it never touches Shabbat
    put(dw === 5 ? addDays(sh,-1) : dw === 0 ? addDays(sh,1) : sh, "Yom HaShoah", J.shoah);
    put(hebDate(hy,2,18), "Lag BaOmer", J.lag);
    var sv = hebDate(hy,3,6);   erev(sv, "Shavuot"); put(sv, "Shavuot", J.shav); put(addDays(sv,1), "Shavuot (day 2)", J.shav, true);
    var tb = hebDate(hy,5,9);   put(tb.getDay() === 6 ? addDays(tb,1) : tb, "Tisha B'Av", J.av);   // never on Shabbat
  }
  _yearCache[G] = m;
  return m;
}
function holidaysOn(d){ return holidaysOfYear(d.getFullYear())[iso(d)] || []; }
// Month-cell label: every holiday that day, joined.
function holiday(d){ var l = holidaysOn(d); return l.length ? l.map(function(h){ return h.name; }).join(" · ") : null; }
// { name, lore } for the Day card + lore dialog; shared days carry every entry's lore in turn.
function holidayLore(d){
  var l = holidaysOn(d);
  if (!l.length) return null;
  return { name: l.map(function(h){ return h.name; }).join(" · "),
           lore: l.map(function(h){ return l.length > 1 ? h.name + ": " + h.lore : h.lore; }).join("\n\n") };
}
// The year's list for "Feasts & Holy Days": [{ d, name }] sorted by date.
function holidaysInYear(G){
  var m = holidaysOfYear(G), rows = [];
  for (var k in m) for (var i = 0; i < m[k].length; i++) if (!m[k][i].cont) rows.push({ d: fromIso(k), name: m[k][i].name });
  rows.sort(function(a,b){ return a.d - b.d; });
  return rows;
}

function fmtTime(min, h12){
  if (h12 === undefined) h12 = true;
  var h=Math.floor(min/60), m=min%60;
  if(h12){ var ap=h<12?"AM":"PM"; var hh=h%12; if(hh===0)hh=12; return hh+":"+pad(m)+" "+ap; }
  return pad(h)+":"+pad(m);
}

// ── Recurrence: expand `appts` (array of plain objects) into occurrences in [from,to] ──
// Each occurrence is computed from the BASE date (never from the previous one), so a
// monthly-on-the-31st or a Feb-29 yearly doesn't drift (the old setMonth(+1) walk turned
// Jan 31 into Mar 3, Apr 3, …). A month/year without that day is skipped — RFC 5545
// behaviour, and the same rule cal-reminders uses. Ranges start at local midnight of
// `from` (the old one-day slack leaked yesterday into Agenda).
function daysBetween(a, b){ return Math.round((b.getTime()-a.getTime())/86400000); }
function nthOccurrence(rep, base, n){
  if (rep==="daily")  return addDays(base, n);
  if (rep==="weekly") return addDays(base, 7*n);
  if (rep==="monthly"){ var m=new Date(base.getFullYear(), base.getMonth()+n, base.getDate()); return m.getDate()===base.getDate() ? m : null; }
  if (rep==="yearly"){ var y=new Date(base.getFullYear()+n, base.getMonth(), base.getDate()); return y.getMonth()===base.getMonth() ? y : null; }
  return null;
}
function periodStart(rep, base, n){   // earliest date the nth period could land on
  if (rep==="monthly") return new Date(base.getFullYear(), base.getMonth()+n, 1);
  if (rep==="yearly")  return new Date(base.getFullYear()+n, 0, 1);
  return nthOccurrence(rep, base, n);
}
function occurrencesInRange(appts, from, to){
  var out=[], f=new Date(from); f.setHours(0,0,0,0);
  var fromT=f.getTime(), toT=to.getTime();
  for (var i=0;i<appts.length;i++){
    var a=appts[i], base=fromIso(a.date), rep=a.repeat||"none";
    if (base.getTime()>toT) continue;
    if (rep==="none"){
      if (base.getTime()>=fromT) out.push(inst(a,base));
      continue;
    }
    // jump straight to the first period that can reach the range (no walking from 2019)
    var d0=Math.max(0, daysBetween(base, f)), n=0;
    if (rep==="daily") n=d0;
    else if (rep==="weekly") n=Math.floor(d0/7);
    else if (rep==="monthly") n=Math.max(0, (f.getFullYear()-base.getFullYear())*12 + f.getMonth()-base.getMonth() - 1);
    else if (rep==="yearly") n=Math.max(0, f.getFullYear()-base.getFullYear() - 1);
    else continue;
    for (var guard=0; guard<1200; guard++, n++){
      if (periodStart(rep, base, n).getTime()>toT) break;
      var d=nthOccurrence(rep, base, n);
      if (d && d.getTime()>=fromT && d.getTime()<=toT) out.push(inst(a,d));
    }
  }
  return out;
}
function inst(a,dateObj){ var c={}; for(var k in a) c[k]=a[k]; c.date=iso(dateObj); c._baseId=a.id; return c; }

function apptsOn(appts, d){
  var day=new Date(d); day.setHours(0,0,0,0);
  var end=new Date(d); end.setHours(23,59,59,999);
  return occurrencesInRange(appts, day, end)
    .filter(function(a){ return sameDay(fromIso(a.date), d); })
    .sort(function(x,y){ return (x.allDay?-1:0)-(y.allDay?-1:0) || x.start-y.start; });
}

// ── Side-by-side lanes for overlapping timed blocks (Week/Day) — adds _lane/_lanes ──
// Blocks that overlap share their cluster's width instead of hiding one another.
function layoutLanes(list){
  var xs=list.slice().sort(function(x,y){ return x.start-y.start || (y.end-y.start)-(x.end-x.start); });
  var cluster=[], laneEnds=[], clusterEnd=-1;
  function close(){ for (var j=0;j<cluster.length;j++) cluster[j]._lanes=laneEnds.length; cluster=[]; laneEnds=[]; }
  for (var i=0;i<xs.length;i++){
    var a=xs[i], end=Math.max(a.end, a.start+20);   // a 0-min block still takes 20 min of room
    if (a.start>=clusterEnd) close();
    var lane=0; while (lane<laneEnds.length && laneEnds[lane]>a.start) lane++;
    laneEnds[lane]=end; a._lane=lane; cluster.push(a);
    clusterEnd=Math.max(clusterEnd, end);
  }
  close();
  return xs;
}

// ── Pending reminders, soonest first — same rules as /usr/local/bin/cal-reminders:
// lead = the appointment's own reminder, else the default; all-day ones at 9:00 AM. ──
var ALLDAY_REMIND_MIN = 9*60;
function upcomingReminders(appts, now, days, defaultLead){
  var from=new Date(now); from.setHours(0,0,0,0);
  var occ=occurrencesInRange(appts, from, addDays(from, days+1)), out=[];
  for (var i=0;i<occ.length;i++){
    var a=occ[i], startMin=a.allDay ? ALLDAY_REMIND_MIN : a.start;
    var lead=(a.reminder==null) ? defaultLead : a.reminder;
    var startAt=fromIso(a.date); startAt.setMinutes(startMin);
    var fireAt=new Date(startAt.getTime()-lead*60000);
    if (startAt.getTime()<=now.getTime()) continue;           // already begun
    out.push({ appt:a, lead:lead, fireAt:fireAt, startAt:startAt, due: fireAt.getTime()<=now.getTime() });
  }
  return out.sort(function(x,y){ return x.fireAt-y.fireAt; });
}
function fmtLead(min){
  if (!min) return "at the time";
  if (min>=1440 && min%1440===0) return (min/1440===1 ? "1 day" : (min/1440)+" days")+" before";
  if (min>=60 && min%60===0) return (min/60===1 ? "1 hr" : (min/60)+" hrs")+" before";
  return min+" min before";
}

// "HH:MM" → minutes, or null for anything that isn't a real clock time (25:99 etc.)
function parseHM(s){
  var m=/^\s*(\d{1,2}):(\d{2})\s*$/.exec(s||"");
  if (!m || +m[1]>23 || +m[2]>59) return null;
  return (+m[1])*60+(+m[2]);
}

// ── Search across an appts + todos array (pure) ──
function searchAll(appts, todos, q){
  q = (q||"").trim().toLowerCase();
  if (!q) return { appts: [], todos: [] };
  var am = appts.filter(function(a){
    return (a.title||"").toLowerCase().indexOf(q)>=0
        || (a.location||"").toLowerCase().indexOf(q)>=0
        || (a.notes||"").toLowerCase().indexOf(q)>=0;
  }).sort(function(x,y){ return x.date<y.date?-1:x.date>y.date?1:x.start-y.start; });
  var tm = (todos||[]).filter(function(t){ return (t.text||"").toLowerCase().indexOf(q)>=0; });
  return { appts: am, todos: tm };
}

// ── Jump-to-date parser: "today" | "+7" | "2026-07-15" | "7/4" | "Jul 4" ──
function parseJump(s){
  s = (s||"").trim().toLowerCase(); if (!s) return null;
  if (s==="today") return new Date();
  if (s==="tomorrow") return addDays(new Date(),1);
  if (s==="yesterday") return addDays(new Date(),-1);
  var m = /^([+-]\d+)$/.exec(s); if (m) return addDays(new Date(), +m[1]);
  m = /^(\d{4})-(\d{1,2})-(\d{1,2})$/.exec(s); if (m) return new Date(+m[1], +m[2]-1, +m[3]);
  m = /^(\d{1,2})\/(\d{1,2})(?:\/(\d{2,4}))?$/.exec(s);
  if (m){ var y = m[3] ? (+m[3]<100?2000+ +m[3]:+m[3]) : new Date().getFullYear(); return new Date(y, +m[1]-1, +m[2]); }
  m = /^([a-z]+)\s+(\d{1,2})$/.exec(s);
  if (m){ for (var i=0;i<MONTHS.length;i++){ if (MONTHS[i].toLowerCase().indexOf(m[1])===0) return new Date(new Date().getFullYear(), i, +m[2]); } }
  return null;
}

// ── ICS (iCalendar) export / import (pure; the C++ backend does file I/O) ──
function icsEsc(s){ return String(s||"").replace(/([\\;,])/g, "\\$1").replace(/\n/g, "\\n"); }
function exportICS(appts){
  var hm = function(min){ return pad(Math.floor(min/60))+pad(min%60)+"00"; };
  var L = ["BEGIN:VCALENDAR","VERSION:2.0","PRODID:-//NCDE//Leap Frog Ledger//EN","CALSCALE:GREGORIAN"];
  for (var i=0;i<appts.length;i++){
    var a=appts[i], d=a.date.replace(/-/g,"");
    L.push("BEGIN:VEVENT","UID:"+a.id+"@ncde-leapfrog");
    if (a.allDay) L.push("DTSTART;VALUE=DATE:"+d);
    else { L.push("DTSTART:"+d+"T"+hm(a.start)); L.push("DTEND:"+d+"T"+hm(a.end)); }
    L.push("SUMMARY:"+icsEsc(a.title));
    if (a.location) L.push("LOCATION:"+icsEsc(a.location));
    if (a.notes) L.push("DESCRIPTION:"+icsEsc(a.notes));
    if (a.repeat && a.repeat!=="none") L.push("RRULE:FREQ="+a.repeat.toUpperCase());
    if (a.category) L.push("CATEGORIES:"+a.category);
    L.push("END:VEVENT");
  }
  L.push("END:VCALENDAR");
  return L.join("\r\n");
}
// returns an array of appt records parsed from ICS text (caller assigns ids + persists)
function importICS(text, uidFn){
  var unfold = String(text).replace(/\r\n[ \t]/g,"").split(/\r?\n/);
  var out=[], cur=null;
  var parseDT = function(v){ var m=/(\d{4})(\d{2})(\d{2})(?:T(\d{2})(\d{2}))?/.exec(v);
    return m ? { date:m[1]+"-"+m[2]+"-"+m[3], min: m[4]!=null ? (+m[4])*60+(+m[5]) : null } : null; };
  for (var i=0;i<unfold.length;i++){
    var line=unfold[i];
    if (line==="BEGIN:VEVENT") cur={ category:"azure", repeat:"none", reminder:15, notes:"", location:"" };
    else if (line==="END:VEVENT"){
      if (cur && cur.date){
        cur.id = uidFn ? uidFn() : (""+Date.now()+Math.random());
        cur.allDay = cur.start==null; if (cur.allDay){ cur.start=0; cur.end=0; } if (cur.end==null) cur.end=cur.start+60;
        out.push({ id:cur.id, date:cur.date, title:cur.title||"Untitled", start:cur.start, end:cur.end,
          allDay:cur.allDay, location:cur.location, notes:cur.notes, repeat:cur.repeat, reminder:15, category:cur.category });
      }
      cur=null;
    } else if (cur){
      var ci=line.indexOf(":"); if (ci<0) continue;
      var key=line.slice(0,ci).split(";")[0], val=line.slice(ci+1);
      var un = function(s){ return s.replace(/\\n/g,"\n").replace(/\\([\\;,])/g,"$1"); };
      if (key==="SUMMARY") cur.title=un(val);
      else if (key==="LOCATION") cur.location=un(val);
      else if (key==="DESCRIPTION") cur.notes=un(val);
      else if (key==="DTSTART"){ var p=parseDT(val); if(p){ cur.date=p.date; cur.start=p.min; } }
      else if (key==="DTEND"){ var q=parseDT(val); if(q) cur.end=q.min; }
      else if (key==="RRULE"){ var fm=/FREQ=(\w+)/.exec(val); if(fm) cur.repeat=fm[1].toLowerCase(); }
      else if (key==="CATEGORIES" && CATEGORIES[val]) cur.category=val;
    }
  }
  return out;
}
