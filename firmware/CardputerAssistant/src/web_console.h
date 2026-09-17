#pragma once

#include "app_types.h"
#include "provider_profiles.h"

namespace cardputer {

constexpr std::uint32_t kWebBrowserHeartbeatIntervalMs = 8000U;
constexpr std::uint32_t kWebBrowserPresenceTimeoutMs = 24000U;

struct WebSessionLifetimePolicy {
    bool valid;
    bool expires;
    std::uint32_t idleMilliseconds;
    std::uint32_t cookieMaxAgeSeconds;
    const char* value;
    const char* label;
};

constexpr WebSessionLifetimePolicy webSessionLifetimePolicy(
    WebSessionLifetime lifetime)
{
    switch (lifetime) {
        case WebSessionLifetime::Minutes15:
            return {true, true, 15U * 60U * 1000U, 15U * 60U,
                    "15m", "15 minutes"};
        case WebSessionLifetime::Hour1:
            return {true, true, 60U * 60U * 1000U, 60U * 60U,
                    "1h", "1 hour"};
        case WebSessionLifetime::Hours8:
            return {true, true, 8U * 60U * 60U * 1000U, 8U * 60U * 60U,
                    "8h", "8 hours"};
        case WebSessionLifetime::UntilReboot:
            return {true, false, 0, 0, "until_reboot", "Until reboot"};
    }
    return {false, true, 0, 0, "", "Invalid"};
}

constexpr bool webSessionAuthenticationExpired(
    WebSessionLifetime lifetime,
    std::uint32_t lastActivityAt,
    std::uint32_t now)
{
    const WebSessionLifetimePolicy policy =
        webSessionLifetimePolicy(lifetime);
    return !policy.valid ||
           (policy.expires &&
            static_cast<std::uint32_t>(now - lastActivityAt) >=
                policy.idleMilliseconds);
}

constexpr bool webBrowserPresenceConnected(
    bool initialized,
    std::uint32_t lastHeartbeatAt,
    std::uint32_t now)
{
    return initialized &&
           static_cast<std::uint32_t>(now - lastHeartbeatAt) <
               kWebBrowserPresenceTimeoutMs;
}

struct WebConsoleResult {
    bool success;
    String activeChatId;
    String error;
};

void configureWebConsole();

WebConsoleResult runWebConsole(const Settings& settings,
                               ProviderProfileStore& providerStore,
                               const String& initialChatId,
                               const String& version);

}  // namespace cardputer
