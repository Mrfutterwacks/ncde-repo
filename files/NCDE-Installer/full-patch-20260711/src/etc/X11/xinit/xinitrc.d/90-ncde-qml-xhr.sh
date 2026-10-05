#!/bin/sh
# 90-ncde-qml-xhr.sh — NCDE fix 2026-07-13: allow QML XMLHttpRequest file:// I/O.
# Why: Qt 6 blocks XHR file:// reads/writes unless these are set. LaPivot's QML
# uses the file:// XHR idiom for local config (WeatherLive.qml location brain
# reading /etc/geolocation + ~/.config/ncde/location-memory.json and LEARNING new
# places via PUT; main.qml config read). Without these the reads silently never
# complete (proven live 2026-07-13: qml6 offscreen test — no var: callback never
# fires; with var: completes), so weather never showed the real town/ZIP.
export QML_XHR_ALLOW_FILE_READ=1
export QML_XHR_ALLOW_FILE_WRITE=1
