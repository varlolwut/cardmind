#pragma once

#include "app_types.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace cardputer {

constexpr std::size_t kMaximumApiProfiles = 3;
constexpr std::size_t kMaximumModelPresets = 6;
constexpr std::size_t kProviderStableIdBytes = 16;
constexpr std::size_t kMaximumApiProfileNameBytes = 48;
constexpr std::size_t kMinimumApiBaseUrlBytes = 12;
constexpr std::size_t kMaximumApiBaseUrlBytes = 180;
constexpr std::size_t kMinimumApiKeyBytes = 8;
constexpr std::size_t kMaximumApiKeyBytes = 512;
constexpr std::size_t kMaximumModelPresetNameBytes = 48;
constexpr std::size_t kMaximumModelPresetModelBytes = 120;
constexpr std::uint32_t kMinimumModelPresetOutputTokens = 128;
constexpr std::uint32_t kMaximumModelPresetOutputTokens = 8192;
constexpr std::int32_t kProviderNvsNotEnoughSpaceCode = 0x1105;
constexpr std::int32_t kProviderNvsRemoveFailedCode = 0x1108;

enum class ProviderStoreState : std::uint8_t {
    Uninitialized,
    Unconfigured,
    LegacyRetained,
    Ready,
    AuthorityUncertain,
    Corrupt,
};

enum class ProviderStoreError : std::uint8_t {
    None,
    InvalidInput,
    NotFound,
    Conflict,
    Capacity,
    Corrupt,
    Storage,
    LegacyRetained,
    AuthorityUncertain,
    CleanupFailed,
};

enum class ProviderAuthorityKind : std::uint8_t {
    None,
    LegacySingleton,
    Profile,
};

enum class ProviderWriteDisposition : std::uint8_t {
    Stored,
    Capacity,
    DefiniteFailure,
    CandidateUncertain,
    AuthorityUncertain,
};

struct ProviderStoreResult {
    ProviderStoreError error;
    bool committed;
    bool outcomeUnknown;
    std::string message;
};

struct ProviderAuthorityIdentity {
    ProviderAuthorityKind kind;
    std::string profileId;
    std::uint32_t revision;
};

struct ApiProfileMetadataRecord {
    std::string id;
    std::string name;
    std::string baseUrl;
    std::uint32_t authorityRevision;
    std::uint16_t secretLength;
};

struct ApiProfileSecretRecord {
    std::uint32_t authorityRevision;
    std::string apiKey;
};

struct ApiProfileInput {
    std::string name;
    std::string baseUrl;
    std::string apiKey;
};

struct ApiProfileSummary {
    std::string id;
    std::string name;
    std::string baseUrl;
    std::uint32_t authorityRevision;
    bool isDefault;
};

struct ModelPresetRecord {
    std::string id;
    std::string name;
    std::string model;
    std::uint32_t maximumOutputTokens;
};

struct ModelPresetInput {
    std::string name;
    std::string model;
    std::uint32_t maximumOutputTokens;
};

struct EncodedProviderRecordResult {
    ProviderStoreResult result;
    std::vector<std::uint8_t> bytes;
};

struct ApiProfileMetadataDecodeResult {
    ProviderStoreResult result;
    ApiProfileMetadataRecord record;
};

struct ApiProfileSecretDecodeResult {
    ProviderStoreResult result;
    ApiProfileSecretRecord record;
};

struct ModelPresetDecodeResult {
    ProviderStoreResult result;
    ModelPresetRecord record;
};

struct ApiProfilesResult {
    ProviderStoreResult result;
    std::vector<ApiProfileSummary> profiles;
    std::string defaultProfileId;
};

struct ModelPresetsResult {
    ProviderStoreResult result;
    std::vector<ModelPresetRecord> presets;
};

struct ApiProfileMutationResult {
    ProviderStoreResult result;
    ApiProfileSummary profile;
};

struct ModelPresetMutationResult {
    ProviderStoreResult result;
    ModelPresetRecord preset;
};

struct ProviderSettingsResult {
    ProviderStoreResult result;
    Settings settings;
    ProviderAuthorityIdentity authority;
};

struct ProviderStorageStats {
    std::size_t totalEntries;
    std::size_t usedEntries;
    std::size_t availableEntries;
    std::size_t namespaceEntries;
};

struct ProviderStorageStatsResult {
    ProviderStoreResult result;
    ProviderStorageStats stats;
};

using ApiProfileIdReferences =
    std::array<const std::string*, kMaximumApiProfiles>;
using ModelPresetIdReferences =
    std::array<const std::string*, kMaximumModelPresets>;

ProviderStoreResult validProviderStoreResult();
bool providerStoreResultSucceeded(const ProviderStoreResult& result);
const char* providerStoreStateName(ProviderStoreState state);
const char* providerStoreErrorName(ProviderStoreError error);
bool providerAuthorityIdentitiesEqual(const ProviderAuthorityIdentity& left,
                                      const ProviderAuthorityIdentity& right);
bool isValidProviderStableId(const std::string& value);
ProviderStoreResult validateApiProfileIdentitySet(
    const ApiProfileIdReferences& ids);
ProviderStoreResult validateModelPresetIdentitySet(
    const ModelPresetIdReferences& ids);
ProviderStoreResult validateDefaultApiProfileReference(
    const ApiProfileIdReferences& ids,
    const std::string& defaultProfileId);
ProviderStoreResult validateApiProfileMetadataInput(const std::string& name,
                                                    const std::string& baseUrl);
ProviderStoreResult validateApiKeyInput(const std::string& apiKey);
ProviderStoreResult validateModelPresetInput(const ModelPresetInput& input);
EncodedProviderRecordResult encodeApiProfileMetadataRecord(
    const ApiProfileMetadataRecord& record);
ApiProfileMetadataDecodeResult decodeApiProfileMetadataRecord(
    const std::vector<std::uint8_t>& bytes);
EncodedProviderRecordResult encodeApiProfileSecretRecord(
    const ApiProfileSecretRecord& record);
ApiProfileSecretDecodeResult decodeApiProfileSecretRecord(
    const std::vector<std::uint8_t>& bytes);
EncodedProviderRecordResult encodeModelPresetRecord(const ModelPresetRecord& record);
ModelPresetDecodeResult decodeModelPresetRecord(const std::vector<std::uint8_t>& bytes);
ProviderWriteDisposition classifyProviderCandidateSetResult(std::int32_t errorCode);
ProviderWriteDisposition classifyProviderAuthoritySetResult(std::int32_t errorCode);
ProviderWriteDisposition classifyProviderAuthorityCommitResult(std::int32_t errorCode);

class ProviderProfileStore;

#ifdef ARDUINO

class ProviderProfileStore {
public:
    ProviderProfileStore();

    ProviderStoreResult initialize(const Settings& legacySettings);
    ProviderStoreState state() const;
    const std::string& stateMessage() const;
    ProviderStoreResult retryLegacyMigration(const Settings& legacySettings);
    ProviderStoreResult saveProvisionedDefault(const Settings& provisionedSettings);
    ProviderSettingsResult resolveSettings(const Settings& baseSettings,
                                           const std::string& projectProfileId);
    ProviderStoreResult loadDefaultInto(Settings& settings);
    ApiProfilesResult listProfiles();
    ApiProfileMutationResult createProfile(const ApiProfileInput& input);
    ApiProfileMutationResult updateProfile(const std::string& id,
                                           const ApiProfileInput& input);
    ProviderStoreResult setDefaultProfile(const std::string& id);
    ProviderStoreResult deleteProfile(const std::string& id);
    ProviderStoreResult updateDefaultBaseUrl(const std::string& baseUrl);
    ModelPresetsResult listModelPresets();
    ModelPresetMutationResult createModelPreset(const ModelPresetInput& input);
    ModelPresetMutationResult updateModelPreset(const std::string& id,
                                                const ModelPresetInput& input);
    ProviderStoreResult deleteModelPreset(const std::string& id);
    ProviderStorageStatsResult storageStats();

private:
    ProviderStoreResult bootstrapToReady(const Settings& sourceSettings);
    ProviderStoreResult migrateToReady(const Settings& sourceSettings);
    ProviderStoreResult writeInitialStore(const Settings& sourceSettings);
    ProviderStoreResult inspectReadyStore();
    ProviderStoreResult requireReady() const;
    ProviderStoreResult requireProfileMutationAllowed() const;
    void setState(ProviderStoreState state, const std::string& message);

    ProviderStoreState state_;
    std::string stateMessage_;
    bool migrationRetryAllowed_;
    std::uint32_t legacyAuthorityGeneration_;
    bool profileMutationBlocked_;
};

#endif

}  // namespace cardputer
