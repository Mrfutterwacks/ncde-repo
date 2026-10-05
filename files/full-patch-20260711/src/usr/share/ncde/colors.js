.pragma library

function hslToRgb(h, s, l) {
    h = ((h % 360) + 360) % 360;
    s = Math.max(0, Math.min(1, s));
    l = Math.max(0, Math.min(1, l));
    var a = s * Math.min(l, 1 - l);
    function f(n) {
        var k = (n + h / 30) % 12;
        return l - a * Math.max(-1, Math.min(k - 3, 9 - k, 1));
    }
    return { r: f(0), g: f(8), b: f(4) };
}

function hslToHex(h, s, l) {
    var c = hslToRgb(h, s, l);
    function h2(v) { return Math.round(v * 255).toString(16).padStart(2, "0"); }
    return ("#" + h2(c.r) + h2(c.g) + h2(c.b)).toUpperCase();
}

// Canvas-safe hue→RGB string. Qt Canvas ignores hsl() CSS strings.
// Pass integer degree (0–359), full saturation, 50% lightness.
function hueToRgb(deg) {
    var h = ((deg % 360) + 360) % 360;
    var x = 1 - Math.abs((h / 60) % 2 - 1);
    var r=0, g=0, b=0;
    if      (h < 60)  { r=1; g=x; b=0; }
    else if (h < 120) { r=x; g=1; b=0; }
    else if (h < 180) { r=0; g=1; b=x; }
    else if (h < 240) { r=0; g=x; b=1; }
    else if (h < 300) { r=x; g=0; b=1; }
    else              { r=1; g=0; b=x; }
    return "rgb(" + Math.round(r*255) + "," + Math.round(g*255) + "," + Math.round(b*255) + ")";
}

function derivedPalette(hue, sat) {
    return [
        hslToHex(hue, sat,                       0.18),
        hslToHex(hue, sat,                       0.32),
        hslToHex(hue, sat,                       0.45),
        hslToHex(hue, Math.max(0.30, sat*0.85),  0.62),
        hslToHex(hue, Math.max(0.15, sat*0.50),  0.82),
    ];
}

function hexToRgba(hex) {
    var c = hex.replace("#","");
    return Qt.rgba(
        parseInt(c.substr(0,2), 16) / 255,
        parseInt(c.substr(2,2), 16) / 255,
        parseInt(c.substr(4,2), 16) / 255,
        1.0
    );
}
