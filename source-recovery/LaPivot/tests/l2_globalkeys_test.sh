#!/bin/bash
# Action for l2_sandbox_shot.sh (W15): with an app focused, Super tap toggles Expose, a Super chord
# does not, Alt+F4 closes the focused app. Expose state = is the "LaPivot-L2" override window viewable.
exposeUp() {   # the desktop and Expose are both viewable override-redirect full-screen LaPivot windows
  local n=0
  for w in $(xwininfo -root -children | awk '/"LaPivot/ && /1920x1200/ {print $1}'); do
    i=$(xwininfo -id $w); echo "$i" | grep -q 'IsViewable' && echo "$i" | grep -q 'Override Redirect State: yes' && n=$((n+1))
  done; [ $n -ge 2 ] && echo up || echo "down"; }
kitty >/dev/null 2>&1 & sleep 4
K=$(xdotool search --class kitty | tail -1); xdotool windowfocus $K 2>/dev/null; sleep 0.5
echo "focus is kitty: $([ "$(xdotool getwindowfocus)" = "$K" ] && echo yes || echo no)"
echo "start: expose $(exposeUp)"
xdotool key super; sleep 1.5;          echo "Super tap: expose $(exposeUp)"
xdotool key super; sleep 1.5;          echo "Super tap again: expose $(exposeUp)"
xdotool key super+a; sleep 1.5;        echo "Super+a chord: expose $(exposeUp)"
xdotool windowfocus $K 2>/dev/null; sleep 0.5
xdotool key alt+F4; sleep 2;           echo "Alt+F4: kitty $(xdotool search --class kitty >/dev/null && echo still-open || echo closed)"
