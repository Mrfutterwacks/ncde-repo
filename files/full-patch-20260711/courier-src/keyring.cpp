// keyring.cpp — see keyring.h.
#include "keyring.h"
#include <libsecret/secret.h>
#include <string>

namespace {
const SecretSchema *schema()
{
    static const SecretSchema s = {
        "com.ncde.Courier.GoogleLink", SECRET_SCHEMA_NONE,
        { { "account", SECRET_SCHEMA_ATTRIBUTE_STRING },
          { nullptr, SECRET_SCHEMA_ATTRIBUTE_STRING } },
        0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
    };
    return &s;
}

void takeError(GError *e, std::string *err)
{
    if (!e) return;
    if (err) *err = e->message ? e->message : "keyring error";
    g_error_free(e);
}
}

namespace courier_keyring {

bool store(const std::string &account, const std::string &secret, std::string *err)
{
    GError *e = nullptr;
    const std::string label = "Hummingbird Courier — Google (" + account + ")";
    gboolean ok = secret_password_store_sync(schema(), SECRET_COLLECTION_DEFAULT,
                                             label.c_str(), secret.c_str(), nullptr, &e,
                                             "account", account.c_str(), nullptr);
    takeError(e, err);
    return ok;
}

std::string lookup(const std::string &account, std::string *err)
{
    GError *e = nullptr;
    gchar *pw = secret_password_lookup_sync(schema(), nullptr, &e,
                                            "account", account.c_str(), nullptr);
    takeError(e, err);
    if (!pw) return {};
    std::string out(pw);
    secret_password_free(pw);
    return out;
}

bool clear(const std::string &account, std::string *err)
{
    GError *e = nullptr;
    gboolean ok = secret_password_clear_sync(schema(), nullptr, &e,
                                             "account", account.c_str(), nullptr);
    takeError(e, err);
    return ok || !e;
}

}
