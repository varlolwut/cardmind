#pragma once

#include "app_types.h"
#include "provider_profiles.h"

namespace cardputer {

OperationResult runProvisioningPortal(const Settings& existingSettings,
                                     ProviderProfileStore& providerStore);

}  // namespace cardputer
