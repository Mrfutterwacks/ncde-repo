#!/bin/bash
# Action for l2_sandbox_shot.sh: open a window, send each iconify/restore request a self-decorated app
# (Steam, games, Electron) can send, print the client's map state + WM_STATE after each.
yad --title=Notes --text=hello --width=500 --height=300 --no-buttons >/dev/null 2>&1 & sleep 3
W=$(xdotool search --name '^Notes$' | head -1); echo "client=$W"
st() { echo "$1: $(xwininfo -id $W | grep -o 'Is[A-Za-z]*')  WM_STATE=$(xprop -id $W WM_STATE | sed -n "s/.*window state: //p")  NET=$(xprop -id $W _NET_WM_STATE | sed "s/.*= //")"; }
st before
xdotool windowminimize $W; sleep 1.5;           st "WM_CHANGE_STATE Iconic"
wmctrl -i -a $W; sleep 1.5;                     st "_NET_ACTIVE_WINDOW"
wmctrl -i -r $W -b add,hidden; sleep 1.5;       st "_NET_WM_STATE add HIDDEN"
wmctrl -i -r $W -b remove,hidden; sleep 1.5;    st "_NET_WM_STATE remove HIDDEN"
