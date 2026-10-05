#!/bin/bash
# NCDE launcher-hide reapply (dock-only policy, 2026-07-21).
for f in chromium.desktop rofi.desktop rofi-theme-selector.desktop blueman-manager.desktop blueman-adapters.desktop org.pulseaudio.pavucontrol.desktop qt5ct.desktop qt6ct.desktop kvantummanager.desktop cups.desktop avahi-discover.desktop bssh.desktop bvnc.desktop lstopo.desktop qv4l2.desktop qvidcap.desktop yad-icon-browser.desktop yad-settings.desktop stoken-gui.desktop stoken-gui-small.desktop htop.desktop vim.desktop xarchiver.desktop libreoffice-base.desktop libreoffice-calc.desktop libreoffice-draw.desktop libreoffice-impress.desktop libreoffice-math.desktop libreoffice-writer.desktop xfce4-about.desktop xfce4-accessibility-settings.desktop xfce4-color-settings.desktop xfce4-mime-settings.desktop xfce4-notifyd-config.desktop xfce4-power-manager-settings.desktop xfce4-settings-editor.desktop xfce-display-settings.desktop xfce-keyboard-settings.desktop xfce-mouse-settings.desktop xfce-settings-manager.desktop xfce-ui-settings.desktop xfce4-file-manager.desktop xfce4-mail-reader.desktop xfce4-web-browser.desktop xfce4-terminal-emulator.desktop; do
  p="/usr/share/applications/$f"; [ -f "$p" ] || continue
  grep -q "^NoDisplay=true" "$p" && continue
  if grep -q "^NoDisplay=" "$p"; then sed -i "s/^NoDisplay=.*/NoDisplay=true/" "$p"
  else sed -i "0,/^\[Desktop Entry\]/s//[Desktop Entry]\nNoDisplay=true/" "$p"; fi
done
