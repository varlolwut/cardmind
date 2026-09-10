#pragma once

#include "app_types.h"
#include "provider_profiles.h"

namespace cardputer {

constexpr std::uint32_t kMinimumProjectChatHistoryQuotaBytes = 2U * 1024U * 1024U;

bool isValidProjectChatHistoryQuota(std::uint32_t quotaBytes);

OperationResult loadSettings(Settings& settings, ProviderProfileStore& providerStore);
OperationResult saveSettings(const Settings& settings);
ProviderStoreResult saveProvisionedSettings(
    const Settings& settings,
    ProviderProfileStore& providerStore);
OperationResult saveModel(const String& model);
OperationResult loadSetupAccessPointPassword(String& password);
OperationResult saveSetupAccessPointPassword(const String& password);
OperationResult loadActiveChatId(String& id);
OperationResult saveActiveChatId(const String& id);
OperationResult loadSdVolumeIdentity(String& identity);
OperationResult saveSdVolumeIdentity(const String& identity);
bool settingsAreComplete(const Settings& settings);
bool voiceSettingsAreComplete(const Settings& settings);
bool webSearchSettingsAreComplete(const Settings& settings);
bool ttsSettingsAreComplete(const Settings& settings);

}  // namespace cardputer
