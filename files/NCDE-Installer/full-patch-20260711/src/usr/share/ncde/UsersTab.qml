// UsersTab.qml — User accounts: avatar, add, remove, admin, password, auto-login.
// Backend (guarded): lelan.users (list {name, displayName, isAdmin, hasPassword, isAutoLogin, avatar}),
//   lelan.addUser(name, displayName, isAdmin), lelan.removeUser(name),
//   lelan.setUserAdmin(name, bool), lelan.changePassword(name, newPwd),
//   lelan.setAutoLogin(name, bool), lelan.setUserAvatar(name, filename).
//   accountsservice already in packages.x86_64.
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: ut; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }

    readonly property var users: gv(lelan,"users",[])
    property int  selectedUser:   users.length > 0 ? 0 : -1
    property bool addUserMode:    false
    property bool showAvatarPicker: false
    property bool showPwdForm:    false

    // Add-user form state
    property string newDisplay:  ""
    property string newName:     ""
    property bool   newIsAdmin:  false
    property string newPassword: ""

    // Password-change state
    property string newPwd1:     ""
    property string newPwd2:     ""

    // All 19 celestial avatars
    readonly property var avatarList: [
        "avatars/01-full-moon.svg",     "avatars/02-star-cluster.svg",
        "avatars/03-crescent-moon.svg", "avatars/04-constellation.svg",
        "avatars/05-north-star.svg",    "avatars/06-galaxy.svg",
        "avatars/07-nebula.svg",        "avatars/08-saturn.svg",
        "avatars/09-zodiac.svg",        "avatars/10-aurora.svg",
        "avatars/11-solar-system.svg",  "avatars/12-comet.svg",
        "avatars/13-eclipse.svg",       "avatars/14-sun.svg",
        "avatars/15-hsien-earth.svg",   "avatars/16-hsien-fire.svg",
        "avatars/17-hsien-metal.svg",   "avatars/18-hsien-water.svg",
        "avatars/19-hsien-wood.svg"
    ]

    function currentUser() {
        return (ut.selectedUser >= 0 && ut.users.length > ut.selectedUser)
               ? ut.users[ut.selectedUser] : null
    }
    function userAvatar(u) {
        return u ? gv(u,"avatar","avatars/01-full-moon.svg") : "avatars/01-full-moon.svg"
    }

    // ── Left user list ────────────────────────────────────────────────
    Rectangle {
        id: listPanel
        anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: 188; radius: 6
        color: Qt.rgba(ut.k.wine1.r, ut.k.wine1.g, ut.k.wine1.b, 0.05)
        border.color: ut.k.gilt1; border.width: 1

        Flickable {
            anchors.left: parent.left; anchors.right: parent.right
            anchors.top: parent.top; anchors.bottom: userBtns.top
            anchors.margins: 6
            contentHeight: userCol.height; interactive: contentHeight > height; clip: true

            Column {
                id: userCol; width: parent.width; spacing: 2

                Repeater {
                    model: ut.users
                    Rectangle {
                        property bool sel: ut.selectedUser === index && !ut.addUserMode
                        width: userCol.width; height: 56; radius: 6
                        color: sel ? ut.k.gilt4 : (uHov.hovered ? Qt.rgba(ut.k.gilt4.r, ut.k.gilt4.g, ut.k.gilt4.b, 0.22) : "transparent")
                        border.color: sel ? ut.k.gilt2 : "transparent"; border.width: 1

                        Row {
                            anchors.fill: parent; anchors.margins: 8; spacing: 8

                            // Avatar circle
                            Rectangle {
                                width: 38; height: 38; radius: 19; anchors.verticalCenter: parent.verticalCenter
                                color: Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.15)
                                border.color: sel ? ut.k.gilt2 : ut.k.gilt1; border.width: sel ? 2 : 1
                                clip: true
                                Image {
                                    anchors.fill: parent
                                    source: ut.userAvatar(modelData)
                                    fillMode: Image.PreserveAspectFit; smooth: true; asynchronous: true
                                }
                            }

                            Column {
                                width: parent.width - 46; anchors.verticalCenter: parent.verticalCenter; spacing: 3
                                Text {
                                    width: parent.width; elide: Text.ElideRight
                                    text: modelData.displayName || modelData.name
                                    color: sel ? ut.k.wine1 : ut.k.ink
                                    font.family: sel ? ut.k.titles : ut.k.serif; font.pixelSize: k.sm; font.bold: sel
                                }
                                Rectangle {
                                    width: badgeTxt.implicitWidth + 8; height: 14; radius: 3
                                    color: modelData.isAdmin ? Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.28) : "transparent"
                                    border.color: modelData.isAdmin ? ut.k.gilt2 : ut.k.inkSoft; border.width: 1
                                    Text { id: badgeTxt; anchors.centerIn: parent
                                           text: modelData.isAdmin ? "Admin" : "Standard"
                                           color: modelData.isAdmin ? ut.k.gilt1 : ut.k.inkSoft
                                           font.family: ut.k.display; font.pixelSize: k.sm; font.bold: true; font.letterSpacing: 1 }
                                }
                            }
                        }

                        HoverHandler { id: uHov }
                        TapHandler { onTapped: { ut.selectedUser = index; ut.addUserMode = false; ut.showPwdForm = false; ut.showAvatarPicker = false } }
                    }
                }

                Text {
                    visible: ut.users.length === 0; width: userCol.width; wrapMode: Text.WordWrap
                    leftPadding: 10; topPadding: 12
                    text: "No users found."; color: ut.k.inkSoft; font.family: ut.k.fell; font.italic: true; font.pixelSize: k.sm
                }
            }
        }

        Row {
            id: userBtns
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            anchors.margins: 6; height: 32; spacing: 6

            Rectangle {
                width: 28; height: 28; radius: 4; anchors.verticalCenter: parent.verticalCenter
                color: Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.12)
                border.color: ut.k.gilt1; border.width: 1
                Text { anchors.centerIn: parent; text: "+"; color: ut.k.gilt1; font.pixelSize: k.lg; font.bold: true }
                TapHandler { onTapped: { ut.addUserMode = true; ut.newDisplay = ""; ut.newName = ""; ut.newIsAdmin = false; ut.newPassword = "" } }
                HoverHandler { cursorShape: Qt.PointingHandCursor }
            }

            Rectangle {
                width: 28; height: 28; radius: 4; anchors.verticalCenter: parent.verticalCenter
                enabled: ut.selectedUser >= 0 && ut.users.length > 0 && !ut.addUserMode
                opacity: enabled ? 1.0 : 0.4
                color: Qt.rgba(ut.k.rose.r, ut.k.rose.g, ut.k.rose.b, 0.12)
                border.color: ut.k.rose; border.width: 1
                Text { anchors.centerIn: parent; text: "−"; color: ut.k.rose; font.pixelSize: k.lg; font.bold: true }
                TapHandler {
                    onTapped: {
                        var u = ut.currentUser()
                        if(u && typeof lelan.removeUser==="function") lelan.removeUser(u.name)
                    }
                }
                HoverHandler { cursorShape: Qt.PointingHandCursor }
            }
        }
    }

    // ── Right panel ───────────────────────────────────────────────────
    Item {
        anchors.left: listPanel.right; anchors.leftMargin: 8
        anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: parent.bottom

        // ── Add User form ─────────────────────────────────────────────
        Flickable {
            anchors.fill: parent; contentHeight: addCol.height; interactive: contentHeight > height
            visible: ut.addUserMode
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: addCol; width: parent.width; spacing: 14

                Text { text: "New Account"; color: ut.k.wine2; font.family: ut.k.display; font.bold: true; font.pixelSize: k.lg }
                Text { text: "Create a new user account."; color: ut.k.inkSoft; font.family: ut.k.fell; font.italic: true; font.pixelSize: k.md }

                Rectangle { width: parent.width; height: 1; color: ut.k.gilt1; opacity: 0.4 }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           width: 130; text: "Full Name"; color: ut.k.ink; font.family: ut.k.titles; font.pixelSize: k.md }
                    Rectangle {
                        anchors.left: parent.left; anchors.leftMargin: 136; anchors.right: parent.right; height: 28; radius: 4
                        color: ut.k.paper0; border.color: ut.k.gilt1; border.width: 1.5
                        TextInput { anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                                    text: ut.newDisplay; onTextChanged: ut.newDisplay = text
                                    color: ut.k.ink; font.family: ut.k.serif; font.pixelSize: k.md }
                    }
                }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           width: 130; text: "Username"; color: ut.k.ink; font.family: ut.k.titles; font.pixelSize: k.md }
                    Rectangle {
                        anchors.left: parent.left; anchors.leftMargin: 136; anchors.right: parent.right; height: 28; radius: 4
                        color: ut.k.paper0; border.color: ut.k.gilt1; border.width: 1.5
                        TextInput { anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                                    text: ut.newName; onTextChanged: ut.newName = text
                                    color: ut.k.ink; font.family: ut.k.serif; font.pixelSize: k.md
                                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText }
                    }
                }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           text: "Account Type"; color: ut.k.ink; font.family: ut.k.titles; font.pixelSize: k.md }
                    SetSegment { anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                                 model: ["Standard", "Administrator"]; currentIndex: ut.newIsAdmin ? 1 : 0
                                 onChose: function(i){ ut.newIsAdmin = (i === 1) } }
                }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           width: 130; text: "Password"; color: ut.k.ink; font.family: ut.k.titles; font.pixelSize: k.md }
                    Rectangle {
                        anchors.left: parent.left; anchors.leftMargin: 136; anchors.right: parent.right; height: 28; radius: 4
                        color: ut.k.paper0; border.color: ut.k.gilt1; border.width: 1.5
                        TextInput { anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                                    echoMode: TextInput.Password; text: ut.newPassword; onTextChanged: ut.newPassword = text
                                    color: ut.k.ink; font.family: ut.k.serif; font.pixelSize: k.md }
                    }
                }

                Row { spacing: 10
                    Rectangle {
                        width: 120; height: 30; radius: 4
                        color: Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.15)
                        border.color: ut.k.gilt1; border.width: 1
                        Text { anchors.centerIn: parent; text: "Create Account"
                               color: ut.k.gilt1; font.family: ut.k.titles; font.pixelSize: k.sm; font.bold: true }
                        TapHandler {
                            onTapped: {
                                if(ut.newName.trim() !== "" && typeof lelan.addUser==="function") {
                                    lelan.addUser(ut.newName.trim(), ut.newDisplay.trim(), ut.newIsAdmin)
                                    // addUser(name, display, isAdmin) takes no password — the typed
                                    // password was silently discarded and the new account had none.
                                    // Set it through the same changePassword backend the PASSWORD
                                    // section below already uses.
                                    if(ut.newPassword !== "" && typeof lelan.changePassword==="function")
                                        lelan.changePassword(ut.newName.trim(), ut.newPassword)
                                }
                                ut.addUserMode = false
                            }
                        }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                    }
                    Rectangle {
                        width: 70; height: 30; radius: 4
                        color: "transparent"; border.color: ut.k.inkSoft; border.width: 1
                        Text { anchors.centerIn: parent; text: "Cancel"
                               color: ut.k.inkSoft; font.family: ut.k.titles; font.pixelSize: k.sm }
                        TapHandler { onTapped: ut.addUserMode = false }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                    }
                }

                Item { width: 1; height: 8 }
            }
        }

        // ── Account detail view ───────────────────────────────────────
        Flickable {
            anchors.fill: parent; contentHeight: detCol.height; interactive: contentHeight > height
            visible: !ut.addUserMode && ut.selectedUser >= 0 && ut.users.length > 0
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: detCol; width: parent.width; spacing: 14

                property var u: ut.currentUser()

                Text { text: "Account"; color: ut.k.wine2; font.family: ut.k.display; font.bold: true; font.pixelSize: k.lg }

                // ── AVATAR section ────────────────────────────────────
                Text { text: "AVATAR"; color: ut.k.gilt1; font.family: ut.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2; topPadding: 4 }

                Row { spacing: 18; width: parent.width
                    // Current avatar (large)
                    Rectangle {
                        width: 72; height: 72; radius: 36; anchors.verticalCenter: parent.verticalCenter
                        color: Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.12)
                        border.color: ut.k.gilt2; border.width: 2; clip: true
                        Image {
                            anchors.fill: parent
                            source: ut.userAvatar(detCol.u)
                            fillMode: Image.PreserveAspectFit; smooth: true; asynchronous: true
                        }
                    }

                    Column { anchors.verticalCenter: parent.verticalCenter; spacing: 8
                        Text { text: (detCol.u ? (detCol.u.displayName || detCol.u.name) : "")
                               color: ut.k.ink; font.family: ut.k.titles; font.bold: true; font.pixelSize: k.lg }

                        Rectangle {
                            width: 130; height: 28; radius: 4
                            color: Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.12)
                            border.color: ut.k.gilt1; border.width: 1
                            Text { anchors.centerIn: parent
                                   text: ut.showAvatarPicker ? "Hide Avatars" : "Choose Avatar"
                                   color: ut.k.gilt1; font.family: ut.k.titles; font.pixelSize: k.sm; font.bold: true }
                            TapHandler { onTapped: ut.showAvatarPicker = !ut.showAvatarPicker }
                            HoverHandler { cursorShape: Qt.PointingHandCursor }
                        }
                    }
                }

                // Avatar picker grid
                Flow {
                    visible: ut.showAvatarPicker
                    width: parent.width; spacing: 8

                    Repeater {
                        model: ut.avatarList
                        Rectangle {
                            property bool isCurrent: detCol.u && ut.userAvatar(detCol.u) === modelData
                            width: 48; height: 48; radius: 24; clip: true
                            color: Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, isCurrent ? 0.3 : 0.1)
                            border.color: isCurrent ? ut.k.gilt2 : Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.4)
                            border.width: isCurrent ? 2 : 1

                            Image {
                                anchors.fill: parent
                                source: modelData
                                fillMode: Image.PreserveAspectFit; smooth: true; asynchronous: true
                            }

                            TapHandler {
                                onTapped: {
                                    if(detCol.u && typeof lelan.setUserAvatar==="function")
                                        lelan.setUserAvatar(detCol.u.name, modelData)
                                }
                            }
                            HoverHandler { cursorShape: Qt.PointingHandCursor }
                        }
                    }
                }

                // ── ACCOUNT section ───────────────────────────────────
                Rectangle { width: parent.width; height: 1; color: ut.k.gilt1; opacity: 0.4 }
                Text { text: "ACCOUNT"; color: ut.k.gilt1; font.family: ut.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

                Item { width: parent.width; height: 26
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           width: 120; text: "Display Name"; color: ut.k.inkSoft; font.family: ut.k.fell; font.italic: true; font.pixelSize: k.sm }
                    Text { anchors.left: parent.left; anchors.leftMargin: 126; anchors.verticalCenter: parent.verticalCenter
                           text: detCol.u ? (detCol.u.displayName || detCol.u.name) : ""
                           color: ut.k.ink; font.family: ut.k.serif; font.pixelSize: k.md }
                }
                Item { width: parent.width; height: 26
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           width: 120; text: "Username"; color: ut.k.inkSoft; font.family: ut.k.fell; font.italic: true; font.pixelSize: k.sm }
                    Text { anchors.left: parent.left; anchors.leftMargin: 126; anchors.verticalCenter: parent.verticalCenter
                           text: detCol.u ? detCol.u.name : ""
                           color: ut.k.ink; font.family: ut.k.serif; font.pixelSize: k.md }
                }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           text: "Account Type"; color: ut.k.ink; font.family: ut.k.titles; font.pixelSize: k.md }
                    SetSegment {
                        anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                        model: ["Standard", "Administrator"]
                        currentIndex: (detCol.u && detCol.u.isAdmin) ? 1 : 0
                        onChose: function(i){ if(detCol.u && typeof lelan.setUserAdmin==="function") lelan.setUserAdmin(detCol.u.name, i === 1) }
                    }
                }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           text: "Auto-login"; color: ut.k.ink; font.family: ut.k.titles; font.pixelSize: k.md }
                    NCDEToggle {
                        anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                        checked: detCol.u ? detCol.u.isAutoLogin : false
                        // Pass v so OFF works too — the old `if(v && …)` guard made the
                        // toggle one-directional (could enable auto-login, never clear it).
                        onToggled: function(v){ if(detCol.u && typeof lelan.setAutoLogin==="function") lelan.setAutoLogin(detCol.u.name, v) }
                    }
                }

                // ── PASSWORD section ──────────────────────────────────
                Rectangle { width: parent.width; height: 1; color: ut.k.gilt1; opacity: 0.4 }
                Text { text: "PASSWORD"; color: ut.k.gilt1; font.family: ut.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

                Rectangle {
                    visible: !ut.showPwdForm; width: 150; height: 30; radius: 4
                    color: Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.12)
                    border.color: ut.k.gilt1; border.width: 1
                    Text { anchors.centerIn: parent; text: "Change Password"
                           color: ut.k.gilt1; font.family: ut.k.titles; font.pixelSize: k.sm; font.bold: true }
                    TapHandler { onTapped: { ut.showPwdForm = true; ut.newPwd1 = ""; ut.newPwd2 = "" } }
                    HoverHandler { cursorShape: Qt.PointingHandCursor }
                }

                Column {
                    visible: ut.showPwdForm; width: parent.width; spacing: 10

                    Item { width: parent.width; height: 30
                        Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                               width: 130; text: "New Password"; color: ut.k.ink; font.family: ut.k.titles; font.pixelSize: k.md }
                        Rectangle {
                            anchors.left: parent.left; anchors.leftMargin: 136; anchors.right: parent.right; height: 28; radius: 4
                            color: ut.k.paper0; border.color: ut.k.gilt1; border.width: 1.5
                            TextInput { anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                                        echoMode: TextInput.Password; text: ut.newPwd1; onTextChanged: ut.newPwd1 = text
                                        color: ut.k.ink; font.family: ut.k.serif; font.pixelSize: k.md }
                        }
                    }

                    Item { width: parent.width; height: 30
                        Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                               width: 130; text: "Confirm"; color: ut.k.ink; font.family: ut.k.titles; font.pixelSize: k.md }
                        Rectangle {
                            anchors.left: parent.left; anchors.leftMargin: 136; anchors.right: parent.right; height: 28; radius: 4
                            color: ut.k.paper0
                            border.color: (ut.newPwd2.length > 0 && ut.newPwd1 !== ut.newPwd2) ? ut.k.rose : ut.k.gilt1
                            border.width: 1.5
                            TextInput { anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                                        echoMode: TextInput.Password; text: ut.newPwd2; onTextChanged: ut.newPwd2 = text
                                        color: ut.k.ink; font.family: ut.k.serif; font.pixelSize: k.md }
                        }
                    }

                    Row { spacing: 10
                        Rectangle {
                            width: 80; height: 30; radius: 4
                            enabled: ut.newPwd1.length > 0 && ut.newPwd1 === ut.newPwd2
                            opacity: enabled ? 1.0 : 0.4
                            color: Qt.rgba(ut.k.gilt1.r, ut.k.gilt1.g, ut.k.gilt1.b, 0.15)
                            border.color: ut.k.gilt1; border.width: 1
                            Text { anchors.centerIn: parent; text: "Apply"
                                   color: ut.k.gilt1; font.family: ut.k.titles; font.pixelSize: k.sm; font.bold: true }
                            TapHandler {
                                onTapped: {
                                    if(detCol.u && ut.newPwd1 === ut.newPwd2 && ut.newPwd1.length > 0)
                                        if(typeof lelan.changePassword==="function") lelan.changePassword(detCol.u.name, ut.newPwd1)
                                    ut.showPwdForm = false
                                }
                            }
                            HoverHandler { cursorShape: Qt.PointingHandCursor }
                        }
                        Rectangle {
                            width: 70; height: 30; radius: 4
                            color: "transparent"; border.color: ut.k.inkSoft; border.width: 1
                            Text { anchors.centerIn: parent; text: "Cancel"
                                   color: ut.k.inkSoft; font.family: ut.k.titles; font.pixelSize: k.sm }
                            TapHandler { onTapped: ut.showPwdForm = false }
                            HoverHandler { cursorShape: Qt.PointingHandCursor }
                        }
                    }
                }

                // ── LOGIN ITEMS section ───────────────────────────────
                Rectangle { width: parent.width; height: 1; color: ut.k.gilt1; opacity: 0.4 }
                Text { text: "LOGIN ITEMS"; color: ut.k.gilt1; font.family: ut.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }
                Text { text: "Manage autostart items in Settings → Session → Autostart."
                       color: ut.k.inkSoft; font.family: ut.k.fell; font.italic: true; font.pixelSize: k.sm; wrapMode: Text.WordWrap; width: parent.width }

                Item { width: 1; height: 8 }
            }
        }

        // Empty state
        Column {
            anchors.centerIn: parent; spacing: 10
            visible: !ut.addUserMode && (ut.selectedUser < 0 || ut.users.length === 0)
            Text { anchors.horizontalCenter: parent.horizontalCenter
                   text: "No users found."; color: ut.k.gilt1; font.family: ut.k.display; font.bold: true; font.pixelSize: k.md }
        }
    }
}
