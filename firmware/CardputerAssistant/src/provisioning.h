#pragma once

#include "app_types.h"
#include "provider_profiles.h"

namespace cardputer {

[[noreturn]] void runProvisioningPortal(const Settings& existingSettings,
                                        ProviderProfileStore& providerStore);

}  // namespace cardputer
