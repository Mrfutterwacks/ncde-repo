# NCDE.Courier — Hummingbird's Google link (Gmail contacts, true folder numbers,
# calendar permission for LeapFrog). Build: qmake6 && make → libncdecourier.so;
# install with qmldir into /usr/lib/qt6/qml/NCDE/Courier/
TEMPLATE = lib
TARGET   = ncdecourier
CONFIG  += plugin c++20 link_pkgconfig release
QT      += qml network
PKGCONFIG += libsecret-1
DEFINES += QT_NO_KEYWORDS
SOURCES += plugin.cpp googlelink.cpp mailcounts.cpp keyring.cpp
HEADERS += googlelink.h mailcounts.h keyring.h
OTHER_FILES += qmldir
