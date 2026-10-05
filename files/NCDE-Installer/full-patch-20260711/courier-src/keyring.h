// keyring.h — refresh-token storage in the Secret Service (gnome-keyring /
// KWallet) via libsecret. Kept in its own translation unit because glib's
// headers and Qt's `signals` keyword do not mix.
#pragma once
#include <string>

namespace courier_keyring {
// All three return false/empty on any keyring error; `err` gets the reason.
bool store(const std::string &account, const std::string &secret, std::string *err);
std::string lookup(const std::string &account, std::string *err);
bool clear(const std::string &account, std::string *err);
}
