.pragma library
// Mucha palette — pale gold, sage, dusty rose, ivory, deep night
// Used by all three canvases. Drop these as `var` consts inside each
// onPaint or define them at the QML root and reference from onPaint.
var MUCHA = {
  // Golds — leaf, pale, deep, ink
  goldLeaf:   "rgba(212,185,106,1.00)",
  goldPale:   "rgba(232,212,148,1.00)",
  goldDeep:   "rgba(166,128,42,1.00)",
  goldInk:    "rgba(110, 78, 20,1.00)",
  goldHi:     "rgba(248,232,178,1.00)",

  // Sage greens — botanical accents
  sage:       "rgba(148,167,138,1.00)",
  sageDeep:   "rgba(107,126,98 ,1.00)",
  sageDark:   "rgba( 68, 82, 64,1.00)",

  // Dusty rose — floral / lips / poppy
  rose:       "rgba(200,144,144,1.00)",
  roseDeep:   "rgba(160,104,104,1.00)",
  roseDark:   "rgba(112, 64, 64,1.00)",

  // Ivory — face / moon body / parchment
  ivory:      "rgba(240,232,216,1.00)",
  ivoryWarm:  "rgba(232,218,184,1.00)",
  ivoryCool:  "rgba(220,224,224,1.00)",

  // Sky — deep midnight with violet undertone
  skyTop:     "rgba( 22, 18, 44,1.00)",
  skyMid:     "rgba( 16, 12, 36,1.00)",
  skyDeep:    "rgba(  8,  6, 22,1.00)",

  // Moon palette — cool pearl / lavender shadow
  moonHi:     "rgba(244,238,228,1.00)",
  moonMid:    "rgba(208,202,210,1.00)",
  moonShade:  "rgba(138,140,168,1.00)",
  moonDark:   "rgba( 38, 42, 72,1.00)"
};

// rgba helper — alpha override on any of the above
function ma(c, a) {
  return c.replace(/,[^,]+\)$/, "," + a + ")");
}
