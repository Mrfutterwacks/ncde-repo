import QtQuick 2.15
import QtQuick.Effects 6.5

Rectangle {
    id: desktopMenu; visible: false; width:190; z:800
    property Item settingsPanelTarget: null
    readonly property bool canShuffle: typeof tilingManager !== "undefined" && tilingManager !== null && tilingManager.tileOrder.length >= 2
    color:ncde.popupBg;border.color:ncde.border;border.width:1;radius:8;height:desktopMenuCol.height+12

    Column {
        id: desktopMenuCol
        anchors { left: parent.left; right: parent.right; top: parent.top; margins: 6 }
        spacing: 2
        Repeater { model:[{label:"Terminal",action:"terminal"},{label:"Orchidée",action:"files"},{label:"Shuffle the Spread",action:"shuffle"},{label:"─────────────",action:"sep"},{label:"Settings",action:"settings"},{label:"─────────────",action:"sep"},{label:"Reload Applications",action:"refresh"}]
            // "Shuffle the Spread" (tarot, 2026-09-26): only while two or more windows are stacked
            Rectangle{width:parent.width;visible:modelData.action!=="shuffle"||desktopMenu.canShuffle;height:!visible?0:modelData.action==="sep"?12:28;radius:3;color:"transparent"
                Text {
                    anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter
                    text: modelData.label
                    color: WallInk.inked(modelData.action === "sep" ? ncde.accentMuted : ctxH.hovered ? ncde.accent : theme.textColor)
                    font.pixelSize: theme.fontSmall
                    font.family: modelData.action === "sep" ? "TerminalVector" : theme.fontFamily
                    style: modelData.action === "sep" ? Text.Normal : theme.textStyle
                    styleColor: theme.textStyleColor
                    layer.enabled: modelData.action !== "sep" && theme.textShadowEnabled
                    layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                        shadowBlur: theme.textShadowRadius / 32.0
                        shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
                    Behavior on color { ColorAnimation { duration: 80 } }
                }
                HoverHandler{id:ctxH}
                TapHandler{enabled:modelData.action!=="sep";onTapped:{desktopMenu.visible=false;var a=modelData.action;if(a==="terminal")launcher.launchExec("ncde-terminal");else if(a==="files")launcher.launchExec("/usr/local/bin/orchidee");else if(a==="settings"){if(settingsPanelTarget)settingsPanelTarget.visible=!settingsPanelTarget.visible;}else if(a==="refresh")appMenuModel.reload();else if(a==="shuffle")tilingManager.shuffleSpread()}} } } }
}
