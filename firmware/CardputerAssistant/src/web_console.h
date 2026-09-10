#pragma once

#include "app_types.h"
#include "provider_profiles.h"

namespace cardputer {

struct WebConsoleResult {
    bool success;
    String activeChatId;
    String error;
};

WebConsoleResult runWebConsole(const Settings& settings,
                               ProviderProfileStore& providerStore,
                               const String& initialChatId,
                               const String& version);

}  // namespace cardputer
