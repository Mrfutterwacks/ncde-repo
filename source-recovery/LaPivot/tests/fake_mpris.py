#!/usr/bin/env python3
"""fake_mpris.py <suffix> [<suffix> ...] — silent fake MPRIS players on the session bus for media_live_test.

Each player owns org.mpris.MediaPlayer2.<suffix> on its OWN bus connection (like real players), serves
/org/mpris/MediaPlayer2 (org.mpris.MediaPlayer2.Player + Properties), and a control interface
org.ncde.FakePlayer the test drives: SetStatus(s), SetTrack(s trackid, s title, x length), SetProp(s, v),
EmitSeeked(x), Stats() -> {GetAll, GetPosition, SetPosition(last), PlayPause}. No audio anywhere."""
import sys
import dbus, dbus.service, dbus.mainloop.glib
from gi.repository import GLib

PLAYER = "org.mpris.MediaPlayer2.Player"
PROPS = "org.freedesktop.DBus.Properties"


class Fake(dbus.service.Object):
    def __init__(self, suffix):
        self.bus = dbus.SessionBus(private=True)
        self.name = dbus.service.BusName("org.mpris.MediaPlayer2." + suffix, self.bus)
        super().__init__(self.bus, "/org/mpris/MediaPlayer2")
        self.p = {"PlaybackStatus": "Stopped", "Rate": dbus.Double(1.0), "Volume": dbus.Double(1.0),
                  "Position": dbus.Int64(0), "Metadata": dbus.Dictionary({}, signature="sv")}
        self.stats = {"GetAll": 0, "GetPosition": 0, "PlayPause": 0, "SetPosition": ""}

    def changed(self, props):
        self.PropertiesChanged(PLAYER, dbus.Dictionary(props, signature="sv"), dbus.Array([], signature="s"))

    # --- MPRIS ---
    def count(self, key, sender):
        self.stats[key] += 1
        self.stats[key + ":" + sender] = self.stats.get(key + ":" + sender, 0) + 1   # who is asking

    @dbus.service.method(PROPS, in_signature="s", out_signature="a{sv}", sender_keyword="sender")
    def GetAll(self, iface, sender=None):
        self.count("GetAll", sender)
        return dbus.Dictionary(self.p, signature="sv")

    @dbus.service.method(PROPS, in_signature="ss", out_signature="v", sender_keyword="sender")
    def Get(self, iface, name, sender=None):
        if name == "Position":
            self.count("GetPosition", sender)
        return self.p[name]

    @dbus.service.signal(PROPS, signature="sa{sv}as")
    def PropertiesChanged(self, iface, changed, invalidated):
        pass

    @dbus.service.signal(PLAYER, signature="x")
    def Seeked(self, position):
        pass

    @dbus.service.method(PLAYER)
    def PlayPause(self):
        self.stats["PlayPause"] += 1

    @dbus.service.method(PLAYER, in_signature="ox")
    def SetPosition(self, track, position):
        self.stats["SetPosition"] = f"{track} {position}"

    # --- test control ---
    @dbus.service.method("org.ncde.FakePlayer", in_signature="sx")
    def SetStatus(self, status, position):
        self.p["PlaybackStatus"] = status
        self.p["Position"] = dbus.Int64(position)
        self.changed({"PlaybackStatus": status})           # like real players: Position not included

    @dbus.service.method("org.ncde.FakePlayer", in_signature="ssx")
    def SetTrack(self, trackid, title, length):
        md = dbus.Dictionary({"mpris:trackid": dbus.ObjectPath(trackid), "xesam:title": title,
                              "xesam:artist": dbus.Array(["Test Artist"], signature="s"),
                              "mpris:length": dbus.Int64(length)}, signature="sv")
        self.p["Metadata"] = md
        self.p["Position"] = dbus.Int64(0)                  # a new track starts at 0 (not announced, as real players do)
        self.changed({"Metadata": md})

    @dbus.service.method("org.ncde.FakePlayer", in_signature="sv")
    def SetProp(self, name, value):
        self.p[name] = value
        self.changed({name: value})

    @dbus.service.method("org.ncde.FakePlayer", in_signature="x")
    def EmitSeeked(self, position):
        self.p["Position"] = dbus.Int64(position)
        self.Seeked(dbus.Int64(position))

    @dbus.service.method("org.ncde.FakePlayer", out_signature="a{sv}")
    def Stats(self):
        return dbus.Dictionary({k: v for k, v in self.stats.items()}, signature="sv")


dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
players = [Fake(s) for s in sys.argv[1:]]
print("READY", " ".join(p.bus.get_unique_name() for p in players), flush=True)
GLib.MainLoop().run()
