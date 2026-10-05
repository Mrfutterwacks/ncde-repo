# NCDE beautification: next ideas (written 2026-09-24)

## First: this batch is staged, not live
- Install: `sudo bash ~/Projects/ncde-beautify-20260924/install.sh`, then relog. Undo: `revert.sh`.
- Check after relog:
  - The clock reads the time, not 88:88.
  - Weather says GERMANTOWN HILLS (can take up to a minute).
  - Stats rows sit clear of the frame.
  - Salon idle shows the resting rose.
  - Dock shows the kith emblems.
  - Window frames look metal.
  - Filigree → Iris Chroma → "From your wallpaper" → tap ✦ Woven, relog, and check it stuck.

## Ideas for the next round (seen on the live desktop, not yet started)
1. **Kith emblems for the rest of the dock.** Chromium, Terminal, Steam, GIMP, LibreOffice, Spotify and Verve still use their generic Mucha motifs. One kith each would make the whole dock one set: Nocker for Terminal, Satyr for Spotify, Troll for Steam, Sluagh for GIMP?
2. **House apps follow the Woven palette (and the wallpaper ink).** Hummingbird, Magpie and the others look up colours by preset name, so they show the template's colours, not the woven ones. Point them at `~/.config/ncde/wallpaper-palette.json`.
3. **Metal everywhere, to match the new window frames.** The same specular band, bevel and brushed grain on:
   - the desktop widget frames (`NCDEGlass2`'s ornamental frame);
   - the bottom panel's 1–4 workspace buttons (flat brown now);
   - the frame's title-bar button bezels.
4. **Stray white shine blob** at the top of the left dock, above the first icon.
5. **Stats gauges:** the CPU/RAM/DISK percentages overlap the arch bars.
6. **Athelian Engine Earth:** the continents render as soft green blotches. Real coastlines or leaded-glass land shapes would suit the rest.
7. **Top panel is sparse:** only the N button on the left. Room for the Glia global menu, or a date/moon-phase cartouche.
8. **Clock greeting:** "stephen" renders in lowercase. Capitalise the name. *(13:11 screenshot already reads "GOOD AFTERNOON STEPHEN" — confirm after relog, likely done.)*
9. **Your call:** Salon's idle title is magenta because of the La'Ombre fill override (`#E158FF`) set in Filigree → Widgets. Keep it or reset it.

## Round 3 ideas (added 2026-09-24 afternoon, after the Expose + wallpaper-ink batches)
Installed 13:30, awaiting relog: `~/Projects/ncde-expose-apps-20260924`, `~/Projects/ncde-wallpaper-ink-20260924`.

**Wallpaper ink, finishing touches**
10. **Ink everywhere else.** Settings apps (Filigree, Fonts, Wallpaper, Accents, Icon Manager), Hummingbird, Orchidée, the calendar apps and main.qml's small dialog still use the old text colours. Wrapping them in `WallInk.inked()` (NOT `theme.inked()` — `theme` is C++) is the same mechanical change as the ink-fix batch.
11. **Ink hue control.** At text brightness, the wallpaper's LCh 320° reads orchid-pink (`#f0c2fb`). A small Filigree slider (or a "violet ↔ orchid" nudge) and an ink-strength (chroma) setting would let you tune it.
12. **Ink the gold, as an option.** A second switch that also re-hues the gilt trim (the "B" option in the mockup). Needs its own token path, because `gilt4` is shared by text and trim.
13. **Follow wallpaper changes.** When the wallpaper changes (or the slideshow advances), re-sample the colours and update the ink and Woven palette automatically, instead of only when a card is tapped.

**Apps and launchers**
14. **Real icons for AppImages.** `ncde-appimage-gen` only guesses an icon name. Extract each AppImage's `.DirIcon`, or give it a kith medallion like the house apps.
15. **Expose polish.** Category shelves (or kith groupings), a staggered fade-in as it opens, keyboard arrows to move between icons, and the dock's hover wobble on its tiles.
16. **Launchpad and AppMenu use the same bezel + dome icon stack** as the dock and Expose, so every app grid matches.

**Everything else the palette doesn't reach yet**
17. **GTK/Qt apps from the wallpaper palette.** Generate a GTK3/4 colour sheet and a Kvantum/qt6ct scheme from the active (woven) tokens, so Thunar, GIMP and LibreOffice pick up the purple and gold. The `gtk-theme-designer-kit.zip` on the USB is a starting point. (Terminal excluded: never touch ncde-terminal.)
18. **Notification popups and OSD** (volume/brightness) in the same leaded-glass + ink style as the widgets.
19. **Lock screen, SDDM greeter and Plymouth boot splash** themed to match: wallpaper, gilt frame, ink text. Needs sudo installs, so stage them the same way.
20. **Cursor theme.** A gilt/brass cursor set to match the frames.
21. **Metal WM frames tinted by the palette.** Let the specular band pick up a hint of the wallpaper hue, like brass reflecting violet glass.

**Widgets**
22. **Top-panel clock in the widget style.** Small seven-segment or Cinzel digits with the same glow as the desktop clock.
23. **Moon-phase cartouche** in the empty top panel (ties in with #7 and the Athelian Engine).
24. ~~Salon album-art tint~~ — Salon has no album art. Instead (operator: "gives the whimsy NCDE needs"): **idle Salon breathes** — rose swells/brightens on a ~8 s breath, captions glow softly in sync. STAGED `~/Projects/ncde-salon-breath-20260924` (2026-09-24).

## Testing tools from this session
- `maim` screenshots work on :0.
- Qt logs go to journald unless `QT_FORCE_STDERR_LOGGING=1` is set.
- `QT_QPA_PLATFORM=offscreen` uses the SOFTWARE scenegraph: MultiEffect/shaders silently draw nothing. For effects render under `QT_QPA_PLATFORM=xcb xvfb-run -a` (GL).
- The offscreen PySide6 harness needs rebuilding each session: `python -m venv` + `pip install PySide6-Essentials`, then mock ncde/theme/widget_data/settings/windowMgr as context properties.

## Round 4: physical materials (added 2026-09-24 evening)
Goal: make the metal, glass and lead we already have act like real materials. Every idea extends a part that is already on screen. None is started yet.

**One light for the whole shell**
25. **A shared light source.** Right now each highlight picks its own "upper-left": MotifFrame's specular band, NCDEIconBezel's glint, NCDEGlassCap's crescent and catch-light, and NCDEGlassSurface's shine. Put one light angle in a qmldir singleton (`ShellLight`, built like WallInk) and have every one of them read it.
26. **The light follows the sun.** WeatherPanel already knows sunrise and sunset. The light angle moves across the day. Speculars soften at dusk. After sunset the frame's amber lamp-glow (`ncde.lamp`) takes over as the main light.
27. **Shadows from that light.** The dock, the widgets and the windows cast soft shadows away from the light. Shadow length depends on height: a window sits higher than a widget, and a widget higher than the dock.

**Glass that is not perfect**
28. **Cathedral-glass texture.** The title-bar panes are flat colour blocks. Give each pane a gentle gradient, faint streaks and one or two seed bubbles. Use mucha-grain's Mulberry32 PRNG with a fixed seed per pane so the pattern never shimmers.
29. **Stained glass casts coloured light.** A 4–6 px wash of the pane colours falls from the title band onto the top of the window. The dock domes cast a faint tinted caustic onto the wallpaper under them.
30. **Domes act as lenses.** On hover, NCDEGlassCap magnifies the medallion under it by a few percent, and the catch-light slides toward the cursor.

**Lead, brass and bronze**
31. **Lead came has a profile.** Real came is H-shaped. Add a 1 px centre highlight to the came lines (the MotifFrame band and the mucha-glass.js leading), plus small bright solder joints where two lines meet.
32. **Verdigris in the crevices.** Bronze patina collects in corners and recesses: MotifFrame's corners, the roots of mucha-glass's corner curls, the socket shadow of each bezel. Use the palette's `verd` token, which the frame painter already receives.
33. **Worn brass.** Dock bezels of the apps you use most are polished bright, and rarely used ones are duller. Needs a launch counter first: Dock.qml doesn't track usage today.
34. **Uneven mosaic tiles.** The bottom-rail mosaic tiles are all the same brightness. Tilt each tile a little (a seeded brightness and sheen jitter) so the band glitters as light moves (#26).

**Weight and touch**
35. **STAGED `~/Projects/ncde-weight-touch-20260924`**. **Buttons press in.** A pressed cabochon, dock icon or workspace button sinks 1 px into its bezel. The socket shadow grows, the specular drops and it springs back on release. Reuses NCDEIconBezel's socket and glint layers.
36. ~~**Jewel chains swing.**~~ Declined: the operator said no animation changes. MotifFrame already knows when a window is being dragged (`lampPulse.isDragging`). The side-rail jewel chains lag behind the drag and settle with a damped swing. Honour animPolicy.
37. ~~**Glass fogs when idle.**~~ Declined: the operator said no idle fog. When `animPolicy.screenIdle` is set, the widget glass slowly frosts over (more blur, less specular). It clears on the first mouse movement.

Suggested first batch: #25 + #31 + #34 + #35. They are cheap, static or nearly so, and they make every later light effect read as one system.

## 2026-09-25 — refinement pass + one light + wet glass (STAGED `~/Projects/ncde-refine-light-20260925`)
Install: `sudo bash ~/Projects/ncde-refine-light-20260925/install.sh`, relog. Undo: `revert.sh`. USB copy: `files/ncde-batches-20260925/`.
Fold into the master as step 7am right after the user installs it.
- Done in it: #4 (dock shine blob), #5-ish stats rows, #25 ShellLight, #31 came profile + solder, #34 mosaic tilt jitter,
  greeting band above the clock (operator), dimmer unlit segments, weather ZIP dropped, NCDE logo button hued from Iris,
  task-title contrast, 1–4 buttons = launcher-icon size (operator), even top-panel clock/readouts, wet glass (operator:
  "a wet shine to all glass … more of a liquid shine"), right window rail lit from the same side as the left.
- Operator rule for glass: "make sure everything is the right shape, we don't want harsh lines again" — every new
  layer stays inside its surface's rounded outline and fades out instead of ending square.
- Still open from this round: date + moon-phase cartouche in the top panel (#7/#23); frame title panes still use
  fixed sapphire/amethyst (amber/emerald/ruby already follow gilt2/verd/wine4); #26 light follows the sun.
Check after relog: greeting band; no "88:88" ghost; weather caption town only; stats bottom row whole; no white
blob at the dock top; logo button violet; 1–4 match the launcher icons; wet shine on dock domes (curved lip +
faint arc at lower right); no hard lines at any glass corner.

## 2026-09-25 (afternoon) — refine-light INSTALLED + folded (7am); sunlight batch STAGED
Operator after installing refine-light: "the light shine works! everything works!" — then "yes let's do it" to #7 + #26 + #29 + #23.
STAGED `~/Projects/ncde-sunlight-20260925` (USB `files/ncde-batches-20260925/`). Install: `sudo bash …/install.sh`, relog. Fold as 7ao after install.
- #26 light follows the sun: ShellLight azimuth -145° (sunrise) → -35° (sunset) from widget_data.weatherSunrise/Sunset, 5-min re-read, 5° steps, no tween; strength softer near horizon; warmth toward ncde.lamp at golden hour + night (night = lamp at -120°). Canvases repaint on ShellLight.signature. Operator: Night Light (2700K) is on "so the desktop is more gaslit" → warmth ×0.35 while Night Light is active.
- Frame jewels all from the palette (sapphire/amethyst harmonized 30% toward accent, deep/shine by Lab L; honey from gilt3; cream from gilt4).
- #29 cast light: 5px wash of each title pane's colour below it; end-pane wash down the top 40px of each rail; each NCDEGlassCap throws a faint tint pool onto the bed (cut away under the socket).
- #7/#23 date + moon cartouche right of the top-panel clock (Space.paintMoon, hover = phase name, tap = Ledger pop-out).
- Limits: the cast light can't fall on the app's own content (the client X window sits over the frame).
Also STAGED `~/Projects/ncde-appnap-fix-20260925`: App-Nap is a wanted feature (operator); Sentinel put app scopes in system.slice beside Xorg at CPUWeight 10000 → unclickable desktop. Now user-<uid>-ncdeapps.slice, 100/50/10.
Next candidates: #27 shadows from the light, #28 cathedral-glass texture, #32 verdigris, #13 follow wallpaper changes, #17 GTK/Qt from palette, #18 notifications/OSD, #19 lock/SDDM/Plymouth.
