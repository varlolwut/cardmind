#include "provider_profiles.h"

#include "text_utils.h"

#include <algorithm>
#include <array>
#include <limits>
#include <utility>

#ifdef ARDUINO
#include <esp_err.h>
#include <esp_system.h>
#include <nvs.h>
#endif

namespace cardputer {
namespace {

constexpr std::uint8_t kApiProfileMetadataVersion = 1;
constexpr std::uint8_t kApiProfileSecretVersion = 1;
constexpr std::uint8_t kModelPresetVersion = 1;
constexpr std::size_t kApiProfileMetadataHeaderBytes = 25;
constexpr std::size_t kApiProfileSecretHeaderBytes = 7;
constexpr std::size_t kModelPresetHeaderBytes = 23;

ProviderStoreResult providerError(ProviderStoreError error,
                                  const std::string& message)
{
    return {error, false, false, message};
}

#ifdef ARDUINO
ProviderStoreResult providerCommittedCleanupError(const std::string& message)
{
    return {ProviderStoreError::CleanupFailed, true, false, message};
}

ProviderStoreResult providerCommittedCleanupError(
    const ProviderStoreResult& cause)
{
    return {ProviderStoreError::CleanupFailed, true, cause.outcomeUnknown,
            cause.message};
}

ProviderStoreResult providerOutcomeUnknown(ProviderStoreError error,
                                           const std::string& message)
{
    return {error, false, true, message};
}
#endif

bool containsCarriageReturnOrLineFeed(const std::string& value)
{
    return value.find('\r') != std::string::npos ||
           value.find('\n') != std::string::npos;
}

bool hasValidApiBaseUrl(const std::string& value)
{
    return value.size() >= kMinimumApiBaseUrlBytes &&
           value.size() <= kMaximumApiBaseUrlBytes &&
           value.rfind("https://", 0) == 0 &&
           value.find(' ') == std::string::npos &&
           value.find('?') == std::string::npos &&
           value.find('#') == std::string::npos &&
           !containsCarriageReturnOrLineFeed(value);
}

void appendUint16(std::vector<std::uint8_t>& bytes, std::uint16_t value)
{
    bytes.push_back(static_cast<std::uint8_t>(value & 0xFFU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 8U) & 0xFFU));
}

void appendUint32(std::vector<std::uint8_t>& bytes, std::uint32_t value)
{
    bytes.push_back(static_cast<std::uint8_t>(value & 0xFFU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 8U) & 0xFFU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 16U) & 0xFFU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 24U) & 0xFFU));
}

std::uint16_t readUint16(const std::vector<std::uint8_t>& bytes,
                         std::size_t offset)
{
    return static_cast<std::uint16_t>(bytes[offset]) |
           (static_cast<std::uint16_t>(bytes[offset + 1]) << 8U);
}

std::uint32_t readUint32(const std::vector<std::uint8_t>& bytes,
                         std::size_t offset)
{
    return static_cast<std::uint32_t>(bytes[offset]) |
           (static_cast<std::uint32_t>(bytes[offset + 1]) << 8U) |
           (static_cast<std::uint32_t>(bytes[offset + 2]) << 16U) |
           (static_cast<std::uint32_t>(bytes[offset + 3]) << 24U);
}

void appendString(std::vector<std::uint8_t>& bytes, const std::string& value)
{
    bytes.insert(bytes.end(), value.begin(), value.end());
}

std::string readString(const std::vector<std::uint8_t>& bytes,
                       std::size_t offset,
                       std::size_t length)
{
    return std::string(bytes.begin() + static_cast<std::ptrdiff_t>(offset),
                       bytes.begin() + static_cast<std::ptrdiff_t>(offset + length));
}

ProviderStoreResult validateProfileMetadataRecord(
    const ApiProfileMetadataRecord& record)
{
    if (!isValidProviderStableId(record.id)) {
        return providerError(ProviderStoreError::InvalidInput,
                             "API profile id must contain exactly 16 lowercase hex characters");
    }
    const ProviderStoreResult metadata =
        validateApiProfileMetadataInput(record.name, record.baseUrl);
    if (!providerStoreResultSucceeded(metadata)) {
        return metadata;
    }
    if (record.authorityRevision == 0) {
        return providerError(ProviderStoreError::InvalidInput,
                             "API profile authority revision must be nonzero");
    }
    if (record.secretLength < kMinimumApiKeyBytes ||
        record.secretLength > kMaximumApiKeyBytes) {
        return providerError(ProviderStoreError::InvalidInput,
                             "API profile secret length is outside the supported range");
    }
    return validProviderStoreResult();
}

ProviderStoreResult validateSecretRecord(const ApiProfileSecretRecord& record)
{
    if (record.authorityRevision == 0) {
        return providerError(ProviderStoreError::InvalidInput,
                             "API profile secret revision must be nonzero");
    }
    return validateApiKeyInput(record.apiKey);
}

ProviderStoreResult validatePresetRecord(const ModelPresetRecord& record)
{
    if (!isValidProviderStableId(record.id)) {
        return providerError(ProviderStoreError::InvalidInput,
                             "Model preset id must contain exactly 16 lowercase hex characters");
    }
    return validateModelPresetInput(
        {record.name, record.model, record.maximumOutputTokens});
}

template <std::size_t Size>
bool providerIdentitySetHasDuplicate(
    const std::array<const std::string*, Size>& ids)
{
    for (std::size_t left = 0; left < ids.size(); ++left) {
        if (ids[left] == nullptr) continue;
        for (std::size_t right = left + 1; right < ids.size(); ++right) {
            if (ids[right] != nullptr && *ids[left] == *ids[right]) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace

ProviderStoreResult validProviderStoreResult()
{
    return {ProviderStoreError::None, false, false, ""};
}

bool providerStoreResultSucceeded(const ProviderStoreResult& result)
{
    return result.error == ProviderStoreError::None;
}

const char* providerStoreStateName(ProviderStoreState state)
{
    switch (state) {
        case ProviderStoreState::Uninitialized:
            return "uninitialized";
        case ProviderStoreState::Unconfigured:
            return "unconfigured";
        case ProviderStoreState::LegacyRetained:
            return "legacy_retained";
        case ProviderStoreState::Ready:
            return "ready";
        case ProviderStoreState::AuthorityUncertain:
            return "authority_uncertain";
        case ProviderStoreState::Corrupt:
            return "corrupt";
    }
    return "invalid";
}

const char* providerStoreErrorName(ProviderStoreError error)
{
    switch (error) {
        case ProviderStoreError::None:
            return "none";
        case ProviderStoreError::InvalidInput:
            return "invalid_input";
        case ProviderStoreError::NotFound:
            return "not_found";
        case ProviderStoreError::Conflict:
            return "conflict";
        case ProviderStoreError::Capacity:
            return "capacity";
        case ProviderStoreError::Corrupt:
            return "corrupt";
        case ProviderStoreError::Storage:
            return "storage";
        case ProviderStoreError::LegacyRetained:
            return "legacy_retained";
        case ProviderStoreError::AuthorityUncertain:
            return "authority_uncertain";
        case ProviderStoreError::CleanupFailed:
            return "cleanup_failed";
    }
    return "invalid";
}

bool providerAuthorityIdentitiesEqual(const ProviderAuthorityIdentity& left,
                                      const ProviderAuthorityIdentity& right)
{
    return left.kind == right.kind && left.profileId == right.profileId &&
           left.revision == right.revision;
}

bool isValidProviderStableId(const std::string& value)
{
    if (value.size() != kProviderStableIdBytes) {
        return false;
    }
    return std::all_of(value.begin(), value.end(), [](char character) {
        return (character >= '0' && character <= '9') ||
               (character >= 'a' && character <= 'f');
    });
}

ProviderStoreResult validateApiProfileIdentitySet(
    const ApiProfileIdReferences& ids)
{
    return providerIdentitySetHasDuplicate(ids)
        ? providerError(ProviderStoreError::Corrupt,
                        "Stored API profile ids are duplicated")
        : validProviderStoreResult();
}

ProviderStoreResult validateModelPresetIdentitySet(
    const ModelPresetIdReferences& ids)
{
    return providerIdentitySetHasDuplicate(ids)
        ? providerError(ProviderStoreError::Corrupt,
                        "Stored model preset ids are duplicated")
        : validProviderStoreResult();
}

ProviderStoreResult validateDefaultApiProfileReference(
    const ApiProfileIdReferences& ids,
    const std::string& defaultProfileId)
{
    const bool found = std::any_of(
        ids.begin(), ids.end(), [&defaultProfileId](const std::string* id) {
            return id != nullptr && *id == defaultProfileId;
        });
    return found
        ? validProviderStoreResult()
        : providerError(
              ProviderStoreError::Corrupt,
              "Default API profile id does not identify a stored profile");
}

ProviderStoreResult validateApiProfileMetadataInput(const std::string& name,
                                                    const std::string& baseUrl)
{
    if (name.empty() || name.size() > kMaximumApiProfileNameBytes ||
        containsCarriageReturnOrLineFeed(name) || !isValidUtf8(name)) {
        return providerError(
            ProviderStoreError::InvalidInput,
            "API profile name must be valid UTF-8, contain 1-48 bytes, and contain no line breaks");
    }
    if (!hasValidApiBaseUrl(baseUrl)) {
        return providerError(
            ProviderStoreError::InvalidInput,
            "API base URL must be an https:// URL of 12-180 bytes without spaces, query, fragment, or line breaks");
    }
    return validProviderStoreResult();
}

ProviderStoreResult validateApiKeyInput(const std::string& apiKey)
{
    if (apiKey.size() < kMinimumApiKeyBytes ||
        apiKey.size() > kMaximumApiKeyBytes ||
        containsCarriageReturnOrLineFeed(apiKey)) {
        return providerError(
            ProviderStoreError::InvalidInput,
            "API key must contain 8-512 bytes and contain no line breaks");
    }
    return validProviderStoreResult();
}

ProviderStoreResult validateModelPresetInput(const ModelPresetInput& input)
{
    if (input.name.empty() || input.name.size() > kMaximumModelPresetNameBytes ||
        containsCarriageReturnOrLineFeed(input.name) || !isValidUtf8(input.name)) {
        return providerError(
            ProviderStoreError::InvalidInput,
            "Model preset name must be valid UTF-8, contain 1-48 bytes, and contain no line breaks");
    }
    if (input.model.empty() || input.model.size() > kMaximumModelPresetModelBytes ||
        containsCarriageReturnOrLineFeed(input.model) || !isValidUtf8(input.model)) {
        return providerError(
            ProviderStoreError::InvalidInput,
            "Model preset model must be valid UTF-8, contain 1-120 bytes, and contain no line breaks");
    }
    if (input.maximumOutputTokens < kMinimumModelPresetOutputTokens ||
        input.maximumOutputTokens > kMaximumModelPresetOutputTokens) {
        return providerError(
            ProviderStoreError::InvalidInput,
            "Model preset output tokens must be between 128 and 8192");
    }
    return validProviderStoreResult();
}

EncodedProviderRecordResult encodeApiProfileMetadataRecord(
    const ApiProfileMetadataRecord& record)
{
    const ProviderStoreResult validation = validateProfileMetadataRecord(record);
    if (!providerStoreResultSucceeded(validation)) {
        return {validation, {}};
    }
    std::vector<std::uint8_t> bytes;
    bytes.reserve(kApiProfileMetadataHeaderBytes + record.name.size() +
                  record.baseUrl.size());
    bytes.push_back(kApiProfileMetadataVersion);
    appendUint32(bytes, record.authorityRevision);
    appendUint16(bytes, record.secretLength);
    appendString(bytes, record.id);
    bytes.push_back(static_cast<std::uint8_t>(record.name.size()));
    bytes.push_back(static_cast<std::uint8_t>(record.baseUrl.size()));
    appendString(bytes, record.name);
    appendString(bytes, record.baseUrl);
    return {validProviderStoreResult(), std::move(bytes)};
}

ApiProfileMetadataDecodeResult decodeApiProfileMetadataRecord(
    const std::vector<std::uint8_t>& bytes)
{
    const ApiProfileMetadataRecord empty = {"", "", "", 0, 0};
    if (bytes.size() < kApiProfileMetadataHeaderBytes ||
        bytes[0] != kApiProfileMetadataVersion) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored API profile metadata has an invalid version or length"),
                empty};
    }
    const std::size_t nameLength = bytes[23];
    const std::size_t baseUrlLength = bytes[24];
    if (bytes.size() != kApiProfileMetadataHeaderBytes + nameLength + baseUrlLength) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored API profile metadata length fields do not match its record"),
                empty};
    }
    ApiProfileMetadataRecord record = {
        readString(bytes, 7, kProviderStableIdBytes),
        readString(bytes, kApiProfileMetadataHeaderBytes, nameLength),
        readString(bytes, kApiProfileMetadataHeaderBytes + nameLength,
                   baseUrlLength),
        readUint32(bytes, 1),
        readUint16(bytes, 5),
    };
    const ProviderStoreResult validation = validateProfileMetadataRecord(record);
    if (!providerStoreResultSucceeded(validation)) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored API profile metadata is invalid: " +
                                  validation.message),
                empty};
    }
    return {validProviderStoreResult(), std::move(record)};
}

EncodedProviderRecordResult encodeApiProfileSecretRecord(
    const ApiProfileSecretRecord& record)
{
    const ProviderStoreResult validation = validateSecretRecord(record);
    if (!providerStoreResultSucceeded(validation)) {
        return {validation, {}};
    }
    std::vector<std::uint8_t> bytes;
    bytes.reserve(kApiProfileSecretHeaderBytes + record.apiKey.size());
    bytes.push_back(kApiProfileSecretVersion);
    appendUint32(bytes, record.authorityRevision);
    appendUint16(bytes, static_cast<std::uint16_t>(record.apiKey.size()));
    appendString(bytes, record.apiKey);
    return {validProviderStoreResult(), std::move(bytes)};
}

ApiProfileSecretDecodeResult decodeApiProfileSecretRecord(
    const std::vector<std::uint8_t>& bytes)
{
    const ApiProfileSecretRecord empty = {0, ""};
    if (bytes.size() < kApiProfileSecretHeaderBytes ||
        bytes[0] != kApiProfileSecretVersion) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored API profile secret has an invalid version or length"),
                empty};
    }
    const std::size_t secretLength = readUint16(bytes, 5);
    if (bytes.size() != kApiProfileSecretHeaderBytes + secretLength) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored API profile secret length does not match its record"),
                empty};
    }
    ApiProfileSecretRecord record = {
        readUint32(bytes, 1),
        readString(bytes, kApiProfileSecretHeaderBytes, secretLength),
    };
    const ProviderStoreResult validation = validateSecretRecord(record);
    if (!providerStoreResultSucceeded(validation)) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored API profile secret is invalid"),
                empty};
    }
    return {validProviderStoreResult(), std::move(record)};
}

EncodedProviderRecordResult encodeModelPresetRecord(const ModelPresetRecord& record)
{
    const ProviderStoreResult validation = validatePresetRecord(record);
    if (!providerStoreResultSucceeded(validation)) {
        return {validation, {}};
    }
    std::vector<std::uint8_t> bytes;
    bytes.reserve(kModelPresetHeaderBytes + record.name.size() + record.model.size());
    bytes.push_back(kModelPresetVersion);
    appendString(bytes, record.id);
    bytes.push_back(static_cast<std::uint8_t>(record.name.size()));
    bytes.push_back(static_cast<std::uint8_t>(record.model.size()));
    appendUint32(bytes, record.maximumOutputTokens);
    appendString(bytes, record.name);
    appendString(bytes, record.model);
    return {validProviderStoreResult(), std::move(bytes)};
}

ModelPresetDecodeResult decodeModelPresetRecord(
    const std::vector<std::uint8_t>& bytes)
{
    const ModelPresetRecord empty = {"", "", "", 0};
    if (bytes.size() < kModelPresetHeaderBytes || bytes[0] != kModelPresetVersion) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored model preset has an invalid version or length"),
                empty};
    }
    const std::size_t nameLength = bytes[17];
    const std::size_t modelLength = bytes[18];
    if (bytes.size() != kModelPresetHeaderBytes + nameLength + modelLength) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored model preset length fields do not match its record"),
                empty};
    }
    ModelPresetRecord record = {
        readString(bytes, 1, kProviderStableIdBytes),
        readString(bytes, kModelPresetHeaderBytes, nameLength),
        readString(bytes, kModelPresetHeaderBytes + nameLength, modelLength),
        readUint32(bytes, 19),
    };
    const ProviderStoreResult validation = validatePresetRecord(record);
    if (!providerStoreResultSucceeded(validation)) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored model preset is invalid: " + validation.message),
                empty};
    }
    return {validProviderStoreResult(), std::move(record)};
}

ProviderWriteDisposition classifyProviderCandidateSetResult(
    std::int32_t errorCode)
{
    if (errorCode == 0) {
        return ProviderWriteDisposition::Stored;
    }
    if (errorCode == kProviderNvsNotEnoughSpaceCode) {
        return ProviderWriteDisposition::Capacity;
    }
    if (errorCode == kProviderNvsRemoveFailedCode) {
        return ProviderWriteDisposition::CandidateUncertain;
    }
    return ProviderWriteDisposition::DefiniteFailure;
}

ProviderWriteDisposition classifyProviderAuthoritySetResult(
    std::int32_t errorCode)
{
    if (errorCode == 0) {
        return ProviderWriteDisposition::Stored;
    }
    if (errorCode == kProviderNvsNotEnoughSpaceCode) {
        return ProviderWriteDisposition::Capacity;
    }
    if (errorCode == kProviderNvsRemoveFailedCode) {
        return ProviderWriteDisposition::AuthorityUncertain;
    }
    return ProviderWriteDisposition::DefiniteFailure;
}

ProviderWriteDisposition classifyProviderAuthorityCommitResult(
    std::int32_t errorCode)
{
    return errorCode == 0 ? ProviderWriteDisposition::Stored
                          : ProviderWriteDisposition::AuthorityUncertain;
}

#ifdef ARDUINO

namespace {

constexpr const char* kProviderNamespace = "cardmind_api";
constexpr const char* kLegacyNamespace = "assistant";
constexpr const char* kLegacyApiKey = "api_key";
constexpr const char* kLegacyBaseUrlKey = "base_url";
constexpr const char* kSchemaKey = "schema";
constexpr const char* kDefaultProfileKey = "default";
constexpr std::uint8_t kProviderSchemaVersion = 1;
constexpr std::size_t kMaximumMetadataRecordBytes =
    kApiProfileMetadataHeaderBytes + kMaximumApiProfileNameBytes +
    kMaximumApiBaseUrlBytes;
constexpr std::size_t kMaximumSecretRecordBytes =
    kApiProfileSecretHeaderBytes + kMaximumApiKeyBytes;
constexpr std::size_t kMaximumPresetRecordBytes =
    kModelPresetHeaderBytes + kMaximumModelPresetNameBytes +
    kMaximumModelPresetModelBytes;

struct BlobReadResult {
    ProviderStoreResult result;
    bool found;
    std::vector<std::uint8_t> bytes;
};

struct StringReadResult {
    ProviderStoreResult result;
    bool found;
    std::string value;
};

struct SelectorReadResult {
    ProviderStoreResult result;
    bool found;
    std::uint8_t generation;
};

struct SelectedMetadataResult {
    ProviderStoreResult result;
    bool found;
    std::size_t slot;
    std::uint8_t generation;
    ApiProfileMetadataRecord metadata;
};

struct SelectedProfileResult {
    ProviderStoreResult result;
    bool found;
    std::size_t slot;
    std::uint8_t generation;
    ApiProfileMetadataRecord metadata;
    ApiProfileSecretRecord secret;
};

struct ProfileCollectionResult {
    ProviderStoreResult result;
    std::vector<SelectedMetadataResult> profiles;
};

std::string nvsErrorMessage(const std::string& operation, esp_err_t error)
{
    return operation + " failed with " + esp_err_to_name(error) +
           " (" + std::to_string(static_cast<std::int32_t>(error)) + ")";
}

std::string profileSelectorKey(std::size_t slot)
{
    return "p" + std::to_string(slot) + "s";
}

std::string profileMetadataKey(std::size_t slot, std::uint8_t generation)
{
    return "p" + std::to_string(slot) + (generation == 0 ? "a" : "b") + "m";
}

std::string profileSecretKey(std::size_t slot, std::uint8_t generation)
{
    return "p" + std::to_string(slot) + (generation == 0 ? "a" : "b") + "k";
}

std::string presetKey(std::size_t slot)
{
    return "m" + std::to_string(slot);
}

std::size_t blobEntryCount(std::size_t bytes)
{
    return 2 + ((bytes + 31) / 32);
}

std::size_t stringEntryCount(std::size_t bytesWithoutTerminator)
{
    return 1 + ((bytesWithoutTerminator + 1 + 31) / 32);
}

ProviderStoreResult checkAvailableEntries(std::size_t requiredEntries)
{
    nvs_stats_t stats = {};
    const esp_err_t error = nvs_get_stats(nullptr, &stats);
    if (error != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Reading aggregate NVS capacity", error));
    }
    if (stats.available_entries < requiredEntries) {
        return providerError(
            ProviderStoreError::Capacity,
            "Provider settings require " + std::to_string(requiredEntries) +
                " available NVS entries, but only " +
                std::to_string(stats.available_entries) + " are available");
    }
    return validProviderStoreResult();
}

BlobReadResult readBlob(nvs_handle_t handle,
                        const std::string& key,
                        std::size_t maximumBytes,
                        const std::string& label)
{
    std::size_t length = 0;
    esp_err_t error = nvs_get_blob(handle, key.c_str(), nullptr, &length);
    if (error == ESP_ERR_NVS_NOT_FOUND) {
        return {validProviderStoreResult(), false, {}};
    }
    if (error == ESP_ERR_NVS_TYPE_MISMATCH) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored " + label + " has the wrong NVS type"),
                false, {}};
    }
    if (error != ESP_OK) {
        return {providerError(ProviderStoreError::Storage,
                              nvsErrorMessage("Reading " + label, error)),
                false, {}};
    }
    if (length == 0 || length > maximumBytes) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored " + label + " has an invalid bounded length"),
                false, {}};
    }
    std::vector<std::uint8_t> bytes(length);
    error = nvs_get_blob(handle, key.c_str(), bytes.data(), &length);
    if (error != ESP_OK) {
        return {providerError(ProviderStoreError::Storage,
                              nvsErrorMessage("Loading " + label, error)),
                false, {}};
    }
    bytes.resize(length);
    return {validProviderStoreResult(), true, std::move(bytes)};
}

StringReadResult readBoundedString(nvs_handle_t handle,
                                   const std::string& key,
                                   std::size_t maximumBytes,
                                   const std::string& label)
{
    std::size_t length = 0;
    esp_err_t error = nvs_get_str(handle, key.c_str(), nullptr, &length);
    if (error == ESP_ERR_NVS_NOT_FOUND) {
        return {validProviderStoreResult(), false, ""};
    }
    if (error == ESP_ERR_NVS_TYPE_MISMATCH) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored " + label + " has the wrong NVS type"),
                false, ""};
    }
    if (error != ESP_OK) {
        return {providerError(ProviderStoreError::Storage,
                              nvsErrorMessage("Reading " + label, error)),
                false, ""};
    }
    if (length == 0 || length > maximumBytes + 1) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored " + label + " has an invalid bounded length"),
                false, ""};
    }
    std::vector<char> buffer(length, '\0');
    error = nvs_get_str(handle, key.c_str(), buffer.data(), &length);
    if (error != ESP_OK) {
        return {providerError(ProviderStoreError::Storage,
                              nvsErrorMessage("Loading " + label, error)),
                false, ""};
    }
    return {validProviderStoreResult(), true, std::string(buffer.data())};
}

SelectorReadResult readSelector(nvs_handle_t handle, std::size_t slot)
{
    std::uint8_t generation = 0;
    const std::string key = profileSelectorKey(slot);
    const esp_err_t error = nvs_get_u8(handle, key.c_str(), &generation);
    if (error == ESP_ERR_NVS_NOT_FOUND) {
        return {validProviderStoreResult(), false, 0};
    }
    if (error == ESP_ERR_NVS_TYPE_MISMATCH) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored API profile selector has the wrong NVS type"),
                false, 0};
    }
    if (error != ESP_OK) {
        return {providerError(ProviderStoreError::Storage,
                              nvsErrorMessage("Reading API profile selector", error)),
                false, 0};
    }
    if (generation > 1) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Stored API profile selector has an invalid generation"),
                false, 0};
    }
    return {validProviderStoreResult(), true, generation};
}

ProviderStoreResult writeCandidateBlob(nvs_handle_t handle,
                                       const std::string& key,
                                       const std::vector<std::uint8_t>& bytes,
                                       const std::string& label)
{
    const esp_err_t setError = nvs_set_blob(handle, key.c_str(), bytes.data(), bytes.size());
    const ProviderWriteDisposition disposition =
        classifyProviderCandidateSetResult(static_cast<std::int32_t>(setError));
    if (disposition == ProviderWriteDisposition::Capacity) {
        return providerError(ProviderStoreError::Capacity,
                             "NVS capacity changed before " + label + " could be staged");
    }
    if (disposition == ProviderWriteDisposition::CandidateUncertain) {
        return providerOutcomeUnknown(
            ProviderStoreError::Storage,
            label + " staging outcome is unknown until the next normal boot");
    }
    if (disposition != ProviderWriteDisposition::Stored) {
        return providerError(ProviderStoreError::Storage,
                             nvsErrorMessage("Staging " + label, setError));
    }
    const esp_err_t commitError = nvs_commit(handle);
    if (commitError != ESP_OK) {
        return providerOutcomeUnknown(
            ProviderStoreError::Storage,
            nvsErrorMessage("Committing staged " + label, commitError));
    }
    const BlobReadResult stored = readBlob(handle, key, bytes.size(), label);
    if (!providerStoreResultSucceeded(stored.result) || !stored.found ||
        stored.bytes != bytes) {
        return providerOutcomeUnknown(
            ProviderStoreError::Storage,
            "Staged " + label + " could not be verified after commit");
    }
    return validProviderStoreResult();
}

ProviderStoreResult authoritySetFailure(const std::string& label,
                                        esp_err_t error)
{
    const ProviderWriteDisposition disposition =
        classifyProviderAuthoritySetResult(static_cast<std::int32_t>(error));
    if (disposition == ProviderWriteDisposition::Capacity) {
        return providerError(ProviderStoreError::Capacity,
                             "NVS capacity changed before " + label + " could be updated");
    }
    if (disposition == ProviderWriteDisposition::AuthorityUncertain) {
        return providerOutcomeUnknown(
            ProviderStoreError::AuthorityUncertain,
            label + " authority is unknown until the next normal boot");
    }
    return providerError(ProviderStoreError::Storage,
                         nvsErrorMessage("Updating " + label, error));
}

ProviderStoreResult authorityCommitFailure(const std::string& label,
                                           esp_err_t error)
{
    return providerOutcomeUnknown(
        ProviderStoreError::AuthorityUncertain,
        nvsErrorMessage("Committing " + label, error) +
            "; actual authority must be read after the next normal boot");
}

ProviderStoreResult writeAuthorityByte(nvs_handle_t handle,
                                       const std::string& key,
                                       std::uint8_t value,
                                       const std::string& label)
{
    const esp_err_t setError = nvs_set_u8(handle, key.c_str(), value);
    if (setError != ESP_OK) {
        return authoritySetFailure(label, setError);
    }
    const esp_err_t commitError = nvs_commit(handle);
    if (commitError != ESP_OK) {
        return authorityCommitFailure(label, commitError);
    }
    std::uint8_t stored = 0;
    const esp_err_t readError = nvs_get_u8(handle, key.c_str(), &stored);
    if (readError != ESP_OK || stored != value) {
        return providerOutcomeUnknown(
            ProviderStoreError::AuthorityUncertain,
            label + " could not be verified after commit");
    }
    ProviderStoreResult result = validProviderStoreResult();
    result.committed = true;
    return result;
}

ProviderStoreResult writeAuthorityString(nvs_handle_t handle,
                                         const std::string& key,
                                         const std::string& value,
                                         const std::string& label)
{
    const esp_err_t setError = nvs_set_str(handle, key.c_str(), value.c_str());
    if (setError != ESP_OK) {
        return authoritySetFailure(label, setError);
    }
    const esp_err_t commitError = nvs_commit(handle);
    if (commitError != ESP_OK) {
        return authorityCommitFailure(label, commitError);
    }
    const StringReadResult stored = readBoundedString(handle, key, value.size(), label);
    if (!providerStoreResultSucceeded(stored.result) || !stored.found ||
        stored.value != value) {
        return providerOutcomeUnknown(
            ProviderStoreError::AuthorityUncertain,
            label + " could not be verified after commit");
    }
    ProviderStoreResult result = validProviderStoreResult();
    result.committed = true;
    return result;
}

ProviderStoreResult writeAuthorityBlob(nvs_handle_t handle,
                                       const std::string& key,
                                       const std::vector<std::uint8_t>& bytes,
                                       const std::string& label)
{
    const esp_err_t setError = nvs_set_blob(handle, key.c_str(), bytes.data(), bytes.size());
    if (setError != ESP_OK) {
        return authoritySetFailure(label, setError);
    }
    const esp_err_t commitError = nvs_commit(handle);
    if (commitError != ESP_OK) {
        return authorityCommitFailure(label, commitError);
    }
    const BlobReadResult stored = readBlob(handle, key, bytes.size(), label);
    if (!providerStoreResultSucceeded(stored.result) || !stored.found ||
        stored.bytes != bytes) {
        return providerOutcomeUnknown(
            ProviderStoreError::AuthorityUncertain,
            label + " could not be verified after commit");
    }
    ProviderStoreResult result = validProviderStoreResult();
    result.committed = true;
    return result;
}

ProviderStoreResult eraseAuthorityKey(nvs_handle_t handle,
                                      const std::string& key,
                                      const std::string& label)
{
    const esp_err_t eraseError = nvs_erase_key(handle, key.c_str());
    if (eraseError != ESP_OK) {
        return authoritySetFailure(label, eraseError);
    }
    const esp_err_t commitError = nvs_commit(handle);
    if (commitError != ESP_OK) {
        return authorityCommitFailure(label, commitError);
    }
    nvs_type_t type = NVS_TYPE_ANY;
    const esp_err_t findError = nvs_find_key(handle, key.c_str(), &type);
    if (findError != ESP_ERR_NVS_NOT_FOUND) {
        return providerOutcomeUnknown(
            ProviderStoreError::AuthorityUncertain,
            label + " removal could not be verified after commit");
    }
    ProviderStoreResult result = validProviderStoreResult();
    result.committed = true;
    return result;
}

ProviderStoreResult removePreparationKey(nvs_handle_t handle,
                                         const std::string& key,
                                         const std::string& label)
{
    nvs_type_t type = NVS_TYPE_ANY;
    const esp_err_t findError = nvs_find_key(handle, key.c_str(), &type);
    if (findError == ESP_ERR_NVS_NOT_FOUND) {
        return validProviderStoreResult();
    }
    if (findError != ESP_OK) {
        return providerOutcomeUnknown(
            ProviderStoreError::Storage,
            nvsErrorMessage("Inspecting " + label + " for cleanup", findError));
    }
    const ProviderStoreResult capacity = checkAvailableEntries(1);
    if (!providerStoreResultSucceeded(capacity)) {
        return capacity;
    }
    const esp_err_t eraseError = nvs_erase_key(handle, key.c_str());
    const ProviderWriteDisposition disposition =
        classifyProviderCandidateSetResult(static_cast<std::int32_t>(eraseError));
    if (disposition == ProviderWriteDisposition::Capacity) {
        return providerError(ProviderStoreError::Capacity,
                             "NVS capacity changed before " + label +
                                 " could be removed");
    }
    if (disposition == ProviderWriteDisposition::CandidateUncertain) {
        return providerOutcomeUnknown(
            ProviderStoreError::Storage,
            label + " removal outcome is unknown until the next normal boot");
    }
    if (disposition != ProviderWriteDisposition::Stored) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Removing " + label + " during preparation",
                            eraseError));
    }
    const esp_err_t commitError = nvs_commit(handle);
    if (commitError != ESP_OK) {
        return providerOutcomeUnknown(
            ProviderStoreError::Storage,
            nvsErrorMessage("Committing " + label + " removal", commitError));
    }
    type = NVS_TYPE_ANY;
    const esp_err_t verifyError = nvs_find_key(handle, key.c_str(), &type);
    if (verifyError != ESP_ERR_NVS_NOT_FOUND) {
        return providerOutcomeUnknown(
            ProviderStoreError::Storage,
            verifyError == ESP_OK
                ? "Could not verify " + label + " removal"
                : nvsErrorMessage("Verifying " + label + " removal",
                                  verifyError));
    }
    return validProviderStoreResult();
}

ProviderStoreResult cleanupCommittedKey(nvs_handle_t handle,
                                        const std::string& key,
                                        const std::string& label)
{
    const ProviderStoreResult result =
        removePreparationKey(handle, key, label);
    return providerStoreResultSucceeded(result)
        ? result : providerCommittedCleanupError(result);
}

SelectedMetadataResult readSelectedMetadata(nvs_handle_t handle,
                                            std::size_t slot)
{
    const ApiProfileMetadataRecord empty = {"", "", "", 0, 0};
    const SelectorReadResult selector = readSelector(handle, slot);
    if (!providerStoreResultSucceeded(selector.result)) {
        return {selector.result, false, slot, 0, empty};
    }
    if (!selector.found) {
        return {validProviderStoreResult(), false, slot, 0, empty};
    }
    const BlobReadResult blob = readBlob(
        handle, profileMetadataKey(slot, selector.generation),
        kMaximumMetadataRecordBytes, "API profile metadata");
    if (!providerStoreResultSucceeded(blob.result)) {
        return {blob.result, false, slot, selector.generation, empty};
    }
    if (!blob.found) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Selected API profile metadata is missing"),
                false, slot, selector.generation, empty};
    }
    ApiProfileMetadataDecodeResult decoded =
        decodeApiProfileMetadataRecord(blob.bytes);
    if (!providerStoreResultSucceeded(decoded.result)) {
        return {decoded.result, false, slot, selector.generation, empty};
    }
    return {validProviderStoreResult(), true, slot, selector.generation,
            std::move(decoded.record)};
}

SelectedProfileResult readSelectedProfile(nvs_handle_t handle,
                                          std::size_t slot)
{
    const ApiProfileMetadataRecord emptyMetadata = {"", "", "", 0, 0};
    const ApiProfileSecretRecord emptySecret = {0, ""};
    SelectedMetadataResult metadata = readSelectedMetadata(handle, slot);
    if (!providerStoreResultSucceeded(metadata.result) || !metadata.found) {
        return {metadata.result, metadata.found, slot, metadata.generation,
                emptyMetadata, emptySecret};
    }
    const BlobReadResult blob = readBlob(
        handle, profileSecretKey(slot, metadata.generation),
        kMaximumSecretRecordBytes, "API profile secret");
    if (!providerStoreResultSucceeded(blob.result)) {
        return {blob.result, false, slot, metadata.generation,
                emptyMetadata, emptySecret};
    }
    if (!blob.found) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Selected API profile secret is missing"),
                false, slot, metadata.generation, emptyMetadata, emptySecret};
    }
    ApiProfileSecretDecodeResult decoded = decodeApiProfileSecretRecord(blob.bytes);
    if (!providerStoreResultSucceeded(decoded.result)) {
        return {decoded.result, false, slot, metadata.generation,
                emptyMetadata, emptySecret};
    }
    if (decoded.record.authorityRevision != metadata.metadata.authorityRevision ||
        decoded.record.apiKey.size() != metadata.metadata.secretLength) {
        return {providerError(ProviderStoreError::Corrupt,
                              "Selected API profile metadata and secret do not match"),
                false, slot, metadata.generation, emptyMetadata, emptySecret};
    }
    return {validProviderStoreResult(), true, slot, metadata.generation,
            std::move(metadata.metadata), std::move(decoded.record)};
}

ProfileCollectionResult readProfileCollection(nvs_handle_t handle)
{
    std::vector<SelectedMetadataResult> profiles;
    profiles.reserve(kMaximumApiProfiles);
    for (std::size_t slot = 0; slot < kMaximumApiProfiles; ++slot) {
        SelectedMetadataResult profile = readSelectedMetadata(handle, slot);
        if (!providerStoreResultSucceeded(profile.result)) {
            return {profile.result, {}};
        }
        if (!profile.found) {
            continue;
        }
        profiles.push_back(std::move(profile));
    }
    ApiProfileIdReferences ids = {};
    for (std::size_t index = 0; index < profiles.size(); ++index) {
        ids[index] = &profiles[index].metadata.id;
    }
    const ProviderStoreResult identities = validateApiProfileIdentitySet(ids);
    if (!providerStoreResultSucceeded(identities)) {
        return {identities, {}};
    }
    return {validProviderStoreResult(), std::move(profiles)};
}

SelectedMetadataResult findProfileMetadata(nvs_handle_t handle,
                                           const std::string& id)
{
    const ApiProfileMetadataRecord empty = {"", "", "", 0, 0};
    const ProfileCollectionResult collection = readProfileCollection(handle);
    if (!providerStoreResultSucceeded(collection.result)) {
        return {collection.result, false, 0, 0, empty};
    }
    const auto found = std::find_if(
        collection.profiles.begin(), collection.profiles.end(),
        [&id](const auto& profile) { return profile.metadata.id == id; });
    if (found == collection.profiles.end()) {
        return {providerError(ProviderStoreError::NotFound,
                              "API profile is unavailable"),
                false, 0, 0, empty};
    }
    return *found;
}

SelectedProfileResult findProfile(nvs_handle_t handle, const std::string& id)
{
    const ApiProfileMetadataRecord emptyMetadata = {"", "", "", 0, 0};
    const ApiProfileSecretRecord emptySecret = {0, ""};
    const SelectedMetadataResult metadata = findProfileMetadata(handle, id);
    if (!providerStoreResultSucceeded(metadata.result) || !metadata.found) {
        return {metadata.result, false, metadata.slot, metadata.generation,
                emptyMetadata, emptySecret};
    }
    return readSelectedProfile(handle, metadata.slot);
}

StringReadResult readDefaultProfileId(nvs_handle_t handle)
{
    StringReadResult result = readBoundedString(
        handle, kDefaultProfileKey, kProviderStableIdBytes,
        "default API profile id");
    if (!providerStoreResultSucceeded(result.result) || !result.found) {
        if (providerStoreResultSucceeded(result.result)) {
            result.result = providerError(ProviderStoreError::Corrupt,
                                          "Default API profile id is missing");
        }
        return result;
    }
    if (!isValidProviderStableId(result.value)) {
        result.result = providerError(ProviderStoreError::Corrupt,
                                      "Default API profile id is invalid");
    }
    return result;
}

ProviderStoreResult prepareProfileGeneration(nvs_handle_t handle,
                                             std::size_t slot,
                                             std::uint8_t generation)
{
    ProviderStoreResult result = removePreparationKey(
        handle, profileMetadataKey(slot, generation),
        "inactive API profile metadata");
    if (providerStoreResultSucceeded(result)) {
        result = removePreparationKey(
            handle, profileSecretKey(slot, generation),
            "inactive API profile secret");
    }
    return result;
}

ProviderStoreResult prepareProfileSlot(nvs_handle_t handle, std::size_t slot)
{
    ProviderStoreResult result = prepareProfileGeneration(handle, slot, 0);
    if (providerStoreResultSucceeded(result)) {
        result = prepareProfileGeneration(handle, slot, 1);
    }
    return result;
}

ProviderStoreResult cleanupProfileGeneration(nvs_handle_t handle,
                                             std::size_t slot,
                                             std::uint8_t generation)
{
    ProviderStoreResult result = cleanupCommittedKey(
        handle, profileMetadataKey(slot, generation),
        "inactive API profile metadata");
    if (providerStoreResultSucceeded(result)) {
        result = cleanupCommittedKey(
            handle, profileSecretKey(slot, generation),
            "inactive API profile secret");
    }
    return result;
}

ProviderStoreResult cleanupProfileSlot(nvs_handle_t handle, std::size_t slot)
{
    ProviderStoreResult result = cleanupProfileGeneration(handle, slot, 0);
    if (providerStoreResultSucceeded(result)) {
        result = cleanupProfileGeneration(handle, slot, 1);
    }
    return result;
}

std::string generateStableId()
{
    std::array<std::uint8_t, 8> randomBytes = {};
    esp_fill_random(randomBytes.data(), randomBytes.size());
    constexpr char alphabet[] = "0123456789abcdef";
    std::string id;
    id.reserve(kProviderStableIdBytes);
    for (const std::uint8_t byte : randomBytes) {
        id.push_back(alphabet[(byte >> 4U) & 0x0FU]);
        id.push_back(alphabet[byte & 0x0FU]);
    }
    return id;
}

std::string uniqueProfileId(const ProfileCollectionResult& collection)
{
    for (std::size_t attempt = 0; attempt < 8; ++attempt) {
        const std::string id = generateStableId();
        const bool collision = std::any_of(
            collection.profiles.begin(), collection.profiles.end(),
            [&id](const auto& profile) { return profile.metadata.id == id; });
        if (!collision) {
            return id;
        }
    }
    return "";
}

ProviderStoreResult cleanupLegacyCredentials()
{
    nvs_handle_t probeHandle = 0;
    const esp_err_t probeError =
        nvs_open(kLegacyNamespace, NVS_READONLY, &probeHandle);
    if (probeError == ESP_ERR_NVS_NOT_FOUND) {
        return validProviderStoreResult();
    }
    if (probeError != ESP_OK) {
        return providerCommittedCleanupError(
            nvsErrorMessage("Inspecting legacy settings for cleanup", probeError));
    }
    nvs_close(probeHandle);

    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kLegacyNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return providerCommittedCleanupError(
            nvsErrorMessage("Opening legacy settings for cleanup", openError));
    }
    ProviderStoreResult result = cleanupCommittedKey(
        handle, kLegacyApiKey, "legacy API key");
    if (providerStoreResultSucceeded(result)) {
        result = cleanupCommittedKey(
            handle, kLegacyBaseUrlKey, "legacy API base URL");
    }
    nvs_close(handle);
    return result;
}

struct StoredPreset {
    std::size_t slot;
    ModelPresetRecord record;
};

struct PresetCollectionResult {
    ProviderStoreResult result;
    std::vector<StoredPreset> presets;
};

PresetCollectionResult readPresetCollection(nvs_handle_t handle)
{
    std::vector<StoredPreset> presets;
    presets.reserve(kMaximumModelPresets);
    for (std::size_t slot = 0; slot < kMaximumModelPresets; ++slot) {
        const BlobReadResult blob = readBlob(
            handle, presetKey(slot), kMaximumPresetRecordBytes,
            "model preset");
        if (!providerStoreResultSucceeded(blob.result)) {
            return {blob.result, {}};
        }
        if (!blob.found) {
            continue;
        }
        ModelPresetDecodeResult decoded = decodeModelPresetRecord(blob.bytes);
        if (!providerStoreResultSucceeded(decoded.result)) {
            return {decoded.result, {}};
        }
        presets.push_back({slot, std::move(decoded.record)});
    }
    ModelPresetIdReferences ids = {};
    for (std::size_t index = 0; index < presets.size(); ++index) {
        ids[index] = &presets[index].record.id;
    }
    const ProviderStoreResult identities = validateModelPresetIdentitySet(ids);
    if (!providerStoreResultSucceeded(identities)) {
        return {identities, {}};
    }
    return {validProviderStoreResult(), std::move(presets)};
}

std::string uniquePresetId(const PresetCollectionResult& collection)
{
    for (std::size_t attempt = 0; attempt < 8; ++attempt) {
        const std::string id = generateStableId();
        const bool collision = std::any_of(
            collection.presets.begin(), collection.presets.end(),
            [&id](const auto& preset) { return preset.record.id == id; });
        if (!collision) {
            return id;
        }
    }
    return "";
}

ProviderStoreResult cleanupMigrationKeys(nvs_handle_t handle)
{
    for (std::size_t slot = 0; slot < kMaximumApiProfiles; ++slot) {
        ProviderStoreResult result = removePreparationKey(
            handle, profileSelectorKey(slot),
            "pre-authority API profile selector");
        if (providerStoreResultSucceeded(result)) {
            result = prepareProfileSlot(handle, slot);
        }
        if (!providerStoreResultSucceeded(result)) {
            return result;
        }
    }
    for (std::size_t slot = 0; slot < kMaximumModelPresets; ++slot) {
        const ProviderStoreResult result = removePreparationKey(
            handle, presetKey(slot), "pre-authority model preset");
        if (!providerStoreResultSucceeded(result)) {
            return result;
        }
    }
    return removePreparationKey(handle, kDefaultProfileKey,
                                "pre-authority default API profile id");
}

ProviderStoreResult writeProfileGeneration(
    nvs_handle_t handle,
    std::size_t slot,
    std::uint8_t generation,
    const EncodedProviderRecordResult& metadata,
    const EncodedProviderRecordResult& secret)
{
    ProviderStoreResult result = writeCandidateBlob(
        handle, profileMetadataKey(slot, generation), metadata.bytes,
        "API profile metadata");
    if (providerStoreResultSucceeded(result)) {
        result = writeCandidateBlob(
            handle, profileSecretKey(slot, generation), secret.bytes,
            "API profile secret");
    }
    return result;
}

std::size_t profileWriteEntryCount(
    const EncodedProviderRecordResult& metadata,
    const EncodedProviderRecordResult& secret)
{
    return blobEntryCount(metadata.bytes.size()) +
           blobEntryCount(secret.bytes.size()) + 1;
}

ApiProfileSummary profileSummary(const ApiProfileMetadataRecord& metadata,
                                 const std::string& defaultId)
{
    return {metadata.id, metadata.name, metadata.baseUrl,
            metadata.authorityRevision, metadata.id == defaultId};
}

ProviderStoreResult storeStateError(ProviderStoreState state,
                                    const std::string& message)
{
    if (state == ProviderStoreState::LegacyRetained) {
        return providerError(ProviderStoreError::LegacyRetained, message);
    }
    if (state == ProviderStoreState::AuthorityUncertain) {
        return providerOutcomeUnknown(ProviderStoreError::AuthorityUncertain,
                                      message);
    }
    if (state == ProviderStoreState::Corrupt) {
        return providerError(ProviderStoreError::Corrupt, message);
    }
    if (state == ProviderStoreState::Unconfigured ||
        state == ProviderStoreState::Uninitialized) {
        return providerError(ProviderStoreError::Conflict, message);
    }
    return validProviderStoreResult();
}

}  // namespace

ProviderProfileStore::ProviderProfileStore()
    : state_(ProviderStoreState::Uninitialized),
      stateMessage_("Provider profile storage has not been initialized"),
      migrationRetryAllowed_(false),
      legacyAuthorityGeneration_(0),
      profileMutationBlocked_(false)
{
}

ProviderStoreState ProviderProfileStore::state() const
{
    return state_;
}

const std::string& ProviderProfileStore::stateMessage() const
{
    return stateMessage_;
}

void ProviderProfileStore::setState(ProviderStoreState state,
                                    const std::string& message)
{
    state_ = state;
    stateMessage_ = message;
}

ProviderStoreResult ProviderProfileStore::requireReady() const
{
    if (state_ == ProviderStoreState::Ready) {
        return validProviderStoreResult();
    }
    return storeStateError(
        state_, stateMessage_.empty()
                    ? std::string("Provider profile storage is not ready")
                    : stateMessage_);
}

ProviderStoreResult ProviderProfileStore::requireProfileMutationAllowed() const
{
    if (!profileMutationBlocked_) {
        return validProviderStoreResult();
    }
    return providerError(
        ProviderStoreError::Conflict,
        "API profile mutations are blocked until the next normal boot resolves staged profile storage");
}

ProviderStoreResult ProviderProfileStore::initialize(
    const Settings& legacySettings)
{
    if (legacyAuthorityGeneration_ == 0) {
        esp_fill_random(&legacyAuthorityGeneration_,
                        sizeof(legacyAuthorityGeneration_));
        if (legacyAuthorityGeneration_ == 0) {
            legacyAuthorityGeneration_ = 1;
        }
    }
    if (state_ != ProviderStoreState::Uninitialized) {
        if (state_ == ProviderStoreState::Ready ||
            state_ == ProviderStoreState::Unconfigured) {
            return validProviderStoreResult();
        }
        return requireReady();
    }

    bool schemaPresent = false;
    std::uint8_t schema = 0;
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READONLY, &handle);
    if (openError != ESP_ERR_NVS_NOT_FOUND && openError != ESP_OK) {
        setState(ProviderStoreState::AuthorityUncertain,
                 nvsErrorMessage("Opening provider profile storage", openError));
        return requireReady();
    }
    if (openError == ESP_OK) {
        const esp_err_t schemaError = nvs_get_u8(handle, kSchemaKey, &schema);
        nvs_close(handle);
        if (schemaError == ESP_OK) {
            schemaPresent = true;
        } else if (schemaError == ESP_ERR_NVS_TYPE_MISMATCH) {
            setState(ProviderStoreState::Corrupt,
                     "Provider profile schema marker has the wrong NVS type");
            return requireReady();
        } else if (schemaError != ESP_ERR_NVS_NOT_FOUND) {
            setState(ProviderStoreState::AuthorityUncertain,
                     nvsErrorMessage("Reading provider profile schema", schemaError));
            return requireReady();
        }
    }

    if (schemaPresent) {
        if (schema != kProviderSchemaVersion) {
            setState(ProviderStoreState::Corrupt,
                     "Provider profile schema version is unsupported");
            return requireReady();
        }
        return inspectReadyStore();
    }

    const std::string legacyKey(legacySettings.apiKey.c_str());
    const std::string legacyBaseUrl(legacySettings.apiBaseUrl.c_str());
    if (legacyKey.empty() && legacyBaseUrl.empty()) {
        setState(ProviderStoreState::Unconfigured,
                 "API provider has not been configured");
        migrationRetryAllowed_ = true;
        return validProviderStoreResult();
    }

    setState(ProviderStoreState::LegacyRetained,
             "Legacy API settings are authoritative until migration commits");
    migrationRetryAllowed_ = true;
    return migrateToReady(legacySettings);
}

ProviderStoreResult ProviderProfileStore::inspectReadyStore()
{
    const ProviderStoreResult mutationAllowed =
        requireProfileMutationAllowed();
    if (!providerStoreResultSucceeded(mutationAllowed)) {
        return mutationAllowed;
    }
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        setState(ProviderStoreState::AuthorityUncertain,
                 nvsErrorMessage("Opening authoritative provider storage", openError));
        return requireReady();
    }

    const StringReadResult defaultId = readDefaultProfileId(handle);
    if (!providerStoreResultSucceeded(defaultId.result)) {
        nvs_close(handle);
        setState(defaultId.result.error == ProviderStoreError::Corrupt
                     ? ProviderStoreState::Corrupt
                     : ProviderStoreState::AuthorityUncertain,
                 defaultId.result.message);
        return requireReady();
    }
    const ProfileCollectionResult collection = readProfileCollection(handle);
    if (!providerStoreResultSucceeded(collection.result) ||
        collection.profiles.empty()) {
        nvs_close(handle);
        const std::string message = providerStoreResultSucceeded(collection.result)
            ? std::string("Authoritative provider storage has no API profiles")
            : collection.result.message;
        setState(providerStoreResultSucceeded(collection.result) ||
                         collection.result.error == ProviderStoreError::Corrupt
                     ? ProviderStoreState::Corrupt
                     : ProviderStoreState::AuthorityUncertain,
                 message);
        return requireReady();
    }

    ApiProfileIdReferences profileIds = {};
    for (std::size_t index = 0; index < collection.profiles.size(); ++index) {
        const SelectedMetadataResult& metadata = collection.profiles[index];
        profileIds[index] = &metadata.metadata.id;
        const SelectedProfileResult profile = readSelectedProfile(handle, metadata.slot);
        if (!providerStoreResultSucceeded(profile.result) || !profile.found) {
            nvs_close(handle);
            setState(providerStoreResultSucceeded(profile.result) ||
                             profile.result.error == ProviderStoreError::Corrupt
                         ? ProviderStoreState::Corrupt
                         : ProviderStoreState::AuthorityUncertain,
                     providerStoreResultSucceeded(profile.result)
                         ? std::string("Authoritative API profile is incomplete")
                         : profile.result.message);
            return requireReady();
        }
    }
    const ProviderStoreResult defaultReference =
        validateDefaultApiProfileReference(profileIds, defaultId.value);
    if (!providerStoreResultSucceeded(defaultReference)) {
        nvs_close(handle);
        setState(ProviderStoreState::Corrupt, defaultReference.message);
        return requireReady();
    }

    const PresetCollectionResult presets = readPresetCollection(handle);
    if (!providerStoreResultSucceeded(presets.result)) {
        nvs_close(handle);
        setState(presets.result.error == ProviderStoreError::Corrupt
                     ? ProviderStoreState::Corrupt
                     : ProviderStoreState::AuthorityUncertain,
                 presets.result.message);
        return requireReady();
    }

    ProviderStoreResult cleanup = validProviderStoreResult();
    for (std::size_t slot = 0; slot < kMaximumApiProfiles; ++slot) {
        const SelectorReadResult selector = readSelector(handle, slot);
        if (!providerStoreResultSucceeded(selector.result)) {
            cleanup = providerCommittedCleanupError(selector.result.message);
            break;
        }
        cleanup = selector.found
            ? cleanupProfileGeneration(
                  handle, slot, static_cast<std::uint8_t>(1 - selector.generation))
            : cleanupProfileSlot(handle, slot);
        if (!providerStoreResultSucceeded(cleanup)) {
            break;
        }
    }
    nvs_close(handle);

    setState(ProviderStoreState::Ready,
             providerStoreResultSucceeded(cleanup) ? "" : cleanup.message);
    migrationRetryAllowed_ = false;
    if (!providerStoreResultSucceeded(cleanup)) {
        profileMutationBlocked_ = true;
        return cleanup;
    }
    const ProviderStoreResult legacyCleanup = cleanupLegacyCredentials();
    if (!providerStoreResultSucceeded(legacyCleanup)) {
        setState(ProviderStoreState::Ready, legacyCleanup.message);
        return legacyCleanup;
    }
    return validProviderStoreResult();
}

ProviderStoreResult ProviderProfileStore::bootstrapToReady(
    const Settings& sourceSettings)
{
    const ProviderStoreResult result = writeInitialStore(sourceSettings);
    if (providerStoreResultSucceeded(result) ||
        state_ == ProviderStoreState::Ready ||
        state_ == ProviderStoreState::Corrupt ||
        state_ == ProviderStoreState::AuthorityUncertain) {
        return result;
    }
    setState(ProviderStoreState::Unconfigured,
             "API provider configuration was not saved: " + result.message);
    migrationRetryAllowed_ = false;
    return result;
}

ProviderStoreResult ProviderProfileStore::migrateToReady(
    const Settings& sourceSettings)
{
    const ProviderStoreResult result = writeInitialStore(sourceSettings);
    if (providerStoreResultSucceeded(result) ||
        state_ == ProviderStoreState::Ready ||
        state_ == ProviderStoreState::Corrupt ||
        state_ == ProviderStoreState::AuthorityUncertain) {
        return result;
    }
    if (result.error == ProviderStoreError::AuthorityUncertain) {
        setState(ProviderStoreState::AuthorityUncertain, result.message);
        migrationRetryAllowed_ = false;
        return result;
    }
    setState(ProviderStoreState::LegacyRetained,
             "Legacy API settings could not be migrated: " + result.message);
    migrationRetryAllowed_ = !result.outcomeUnknown;
    return {ProviderStoreError::LegacyRetained, false, result.outcomeUnknown,
            stateMessage_};
}

ProviderStoreResult ProviderProfileStore::writeInitialStore(
    const Settings& sourceSettings)
{
    const ProviderStoreResult mutationAllowed = requireProfileMutationAllowed();
    if (!providerStoreResultSucceeded(mutationAllowed)) {
        return mutationAllowed;
    }

    const std::string apiKey(sourceSettings.apiKey.c_str());
    const std::string baseUrl(sourceSettings.apiBaseUrl.c_str());
    const ProviderStoreResult metadataValidation =
        validateApiProfileMetadataInput("Default", baseUrl);
    const ProviderStoreResult secretValidation = validateApiKeyInput(apiKey);
    if (!providerStoreResultSucceeded(metadataValidation) ||
        !providerStoreResultSucceeded(secretValidation)) {
        return providerStoreResultSucceeded(metadataValidation)
            ? secretValidation : metadataValidation;
    }

    bool namespaceExists = true;
    nvs_handle_t readHandle = 0;
    const esp_err_t readOpenError =
        nvs_open(kProviderNamespace, NVS_READONLY, &readHandle);
    if (readOpenError == ESP_ERR_NVS_NOT_FOUND) {
        namespaceExists = false;
    } else if (readOpenError != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Inspecting pre-authority provider storage",
                            readOpenError));
    } else {
        std::uint8_t schema = 0;
        const esp_err_t schemaError = nvs_get_u8(readHandle, kSchemaKey, &schema);
        nvs_close(readHandle);
        if (schemaError == ESP_OK) {
            if (schema != kProviderSchemaVersion) {
                setState(ProviderStoreState::Corrupt,
                         "Provider profile schema version is unsupported");
                return requireReady();
            }
            return inspectReadyStore();
        }
        if (schemaError == ESP_ERR_NVS_TYPE_MISMATCH) {
            setState(ProviderStoreState::Corrupt,
                     "Provider profile schema marker has the wrong NVS type");
            return requireReady();
        }
        if (schemaError != ESP_ERR_NVS_NOT_FOUND) {
            return providerError(
                ProviderStoreError::Storage,
                nvsErrorMessage("Inspecting pre-authority provider schema",
                                schemaError));
        }
    }

    const std::string id = generateStableId();
    const ApiProfileMetadataRecord metadataRecord = {
        id, "Default", baseUrl, 1,
        static_cast<std::uint16_t>(apiKey.size()),
    };
    const ApiProfileSecretRecord secretRecord = {1, apiKey};
    const EncodedProviderRecordResult metadata =
        encodeApiProfileMetadataRecord(metadataRecord);
    const EncodedProviderRecordResult secret =
        encodeApiProfileSecretRecord(secretRecord);
    if (!providerStoreResultSucceeded(metadata.result) ||
        !providerStoreResultSucceeded(secret.result)) {
        return providerStoreResultSucceeded(metadata.result)
            ? secret.result : metadata.result;
    }

    const std::size_t namespaceEntries = namespaceExists ? 0 : 1;
    const std::size_t requiredEntries =
        profileWriteEntryCount(metadata, secret) +
        stringEntryCount(id.size()) + 1 + namespaceEntries;
    ProviderStoreResult result = checkAvailableEntries(requiredEntries);
    if (!providerStoreResultSucceeded(result)) {
        return result;
    }

    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Opening provider storage for initialization",
                            openError));
    }
    result = cleanupMigrationKeys(handle);
    if (!providerStoreResultSucceeded(result)) {
        nvs_close(handle);
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
        }
        return result;
    }
    result = checkAvailableEntries(requiredEntries - namespaceEntries);
    if (providerStoreResultSucceeded(result)) {
        result = writeProfileGeneration(handle, 0, 0, metadata, secret);
    }
    if (!providerStoreResultSucceeded(result)) {
        nvs_close(handle);
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
        }
        return result;
    }
    result = writeAuthorityByte(handle, profileSelectorKey(0), 0,
                                "initial API profile selector");
    if (!providerStoreResultSucceeded(result)) {
        nvs_close(handle);
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
        }
        return result;
    }
    result = writeAuthorityString(handle, kDefaultProfileKey, id,
                                  "initial default API profile id");
    if (!providerStoreResultSucceeded(result)) {
        nvs_close(handle);
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
        }
        return result;
    }
    result = writeAuthorityByte(handle, kSchemaKey, kProviderSchemaVersion,
                                "provider profile schema");
    nvs_close(handle);
    if (!providerStoreResultSucceeded(result)) {
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
            setState(ProviderStoreState::AuthorityUncertain, result.message);
            migrationRetryAllowed_ = false;
        }
        return result;
    }
    ProviderStoreResult inspected = inspectReadyStore();
    inspected.committed = result.committed;
    return inspected;
}

ProviderStoreResult ProviderProfileStore::retryLegacyMigration(
    const Settings& legacySettings)
{
    if (state_ != ProviderStoreState::LegacyRetained) {
        return providerError(
            ProviderStoreError::Conflict,
            "Provider migration retry is available only while legacy settings are authoritative");
    }
    if (!migrationRetryAllowed_) {
        return providerError(
            ProviderStoreError::Conflict,
            "Provider migration cannot be retried until the next normal boot resolves staged NVS state");
    }
    return migrateToReady(legacySettings);
}

ProviderStoreResult ProviderProfileStore::saveProvisionedDefault(
    const Settings& provisionedSettings)
{
    if (state_ == ProviderStoreState::Unconfigured) {
        return bootstrapToReady(provisionedSettings);
    }
    if (state_ == ProviderStoreState::LegacyRetained) {
        if (!migrationRetryAllowed_) {
            return providerError(
                ProviderStoreError::Conflict,
                "Provisioning cannot update provider authority until the next normal boot");
        }
        return migrateToReady(provisionedSettings);
    }
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return ready;
    }
    ApiProfilesResult profiles = listProfiles();
    if (!providerStoreResultSucceeded(profiles.result)) {
        return profiles.result;
    }
    const auto current = std::find_if(
        profiles.profiles.begin(), profiles.profiles.end(),
        [&profiles](const auto& profile) {
            return profile.id == profiles.defaultProfileId;
        });
    if (current == profiles.profiles.end()) {
        setState(ProviderStoreState::Corrupt,
                 "Default API profile is missing during provisioning");
        return requireReady();
    }
    const ApiProfileMutationResult updated = updateProfile(
        current->id,
        {current->name,
         std::string(provisionedSettings.apiBaseUrl.c_str()),
         std::string(provisionedSettings.apiKey.c_str())});
    return updated.result;
}

ProviderSettingsResult ProviderProfileStore::resolveSettings(
    const Settings& baseSettings,
    const std::string& projectProfileId)
{
    const ProviderAuthorityIdentity noAuthority = {
        ProviderAuthorityKind::None, "", 0};
    if (state_ == ProviderStoreState::LegacyRetained) {
        if (!projectProfileId.empty()) {
            return {providerError(
                        ProviderStoreError::NotFound,
                        "Explicit API profile is unavailable while legacy settings remain authoritative"),
                    baseSettings, noAuthority};
        }
        const std::string legacyKey(baseSettings.apiKey.c_str());
        const std::string legacyBaseUrl(baseSettings.apiBaseUrl.c_str());
        if (legacyKey.size() < kMinimumApiKeyBytes ||
            legacyBaseUrl.rfind("https://", 0) != 0) {
            return {providerError(
                        ProviderStoreError::Conflict,
                        "Legacy API provider settings are incomplete"),
                    baseSettings, noAuthority};
        }
        return {validProviderStoreResult(), baseSettings,
                {ProviderAuthorityKind::LegacySingleton, "",
                 legacyAuthorityGeneration_}};
    }
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return {ready, baseSettings, noAuthority};
    }
    if (!projectProfileId.empty() &&
        !isValidProviderStableId(projectProfileId)) {
        return {providerError(ProviderStoreError::InvalidInput,
                              "Explicit API profile id is malformed"),
                baseSettings, noAuthority};
    }

    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READONLY, &handle);
    if (openError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for request resolution",
                                    openError)),
                baseSettings, noAuthority};
    }
    std::string effectiveId = projectProfileId;
    if (effectiveId.empty()) {
        const StringReadResult defaultId = readDefaultProfileId(handle);
        if (!providerStoreResultSucceeded(defaultId.result)) {
            nvs_close(handle);
            if (defaultId.result.error == ProviderStoreError::Corrupt) {
                setState(ProviderStoreState::Corrupt,
                         defaultId.result.message);
                return {requireReady(), baseSettings, noAuthority};
            }
            if (defaultId.result.error ==
                    ProviderStoreError::AuthorityUncertain ||
                defaultId.result.outcomeUnknown) {
                setState(ProviderStoreState::AuthorityUncertain,
                         defaultId.result.message);
            }
            return {defaultId.result, baseSettings, noAuthority};
        }
        effectiveId = defaultId.value;
    }
    SelectedProfileResult profile = findProfile(handle, effectiveId);
    nvs_close(handle);
    if (!providerStoreResultSucceeded(profile.result) || !profile.found) {
        if (projectProfileId.empty()) {
            if (providerStoreResultSucceeded(profile.result) ||
                profile.result.error == ProviderStoreError::NotFound ||
                profile.result.error == ProviderStoreError::Corrupt) {
                setState(
                    ProviderStoreState::Corrupt,
                    providerStoreResultSucceeded(profile.result)
                        ? std::string("Default API profile is unavailable")
                        : profile.result.message);
                return {requireReady(), baseSettings, noAuthority};
            }
            if (profile.result.error ==
                    ProviderStoreError::AuthorityUncertain ||
                profile.result.outcomeUnknown) {
                setState(ProviderStoreState::AuthorityUncertain,
                         profile.result.message);
            }
            return {profile.result, baseSettings, noAuthority};
        }
        return {providerStoreResultSucceeded(profile.result)
                    ? providerError(ProviderStoreError::NotFound,
                                    "Explicit API profile is unavailable")
                    : profile.result,
                baseSettings, noAuthority};
    }

    Settings resolved = baseSettings;
    resolved.apiKey = String(profile.secret.apiKey.c_str());
    resolved.apiBaseUrl = String(profile.metadata.baseUrl.c_str());
    return {validProviderStoreResult(), std::move(resolved),
            {ProviderAuthorityKind::Profile, profile.metadata.id,
             profile.metadata.authorityRevision}};
}

ProviderStoreResult ProviderProfileStore::loadDefaultInto(Settings& settings)
{
    ProviderSettingsResult resolved = resolveSettings(settings, "");
    if (!providerStoreResultSucceeded(resolved.result)) {
        return resolved.result;
    }
    settings = std::move(resolved.settings);
    return validProviderStoreResult();
}

ApiProfilesResult ProviderProfileStore::listProfiles()
{
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return {ready, {}, ""};
    }
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READONLY, &handle);
    if (openError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for profile listing",
                                    openError)),
                {}, ""};
    }
    const StringReadResult defaultId = readDefaultProfileId(handle);
    const ProfileCollectionResult collection = providerStoreResultSucceeded(defaultId.result)
        ? readProfileCollection(handle)
        : ProfileCollectionResult{defaultId.result, {}};
    nvs_close(handle);
    if (!providerStoreResultSucceeded(collection.result)) {
        return {collection.result, {}, ""};
    }
    std::vector<ApiProfileSummary> profiles;
    profiles.reserve(collection.profiles.size());
    for (const SelectedMetadataResult& profile : collection.profiles) {
        profiles.push_back(profileSummary(profile.metadata, defaultId.value));
    }
    return {validProviderStoreResult(), std::move(profiles), defaultId.value};
}

ApiProfileMutationResult ProviderProfileStore::createProfile(
    const ApiProfileInput& input)
{
    const ApiProfileSummary empty = {"", "", "", 0, false};
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return {ready, empty};
    }
    const ProviderStoreResult mutationAllowed =
        requireProfileMutationAllowed();
    if (!providerStoreResultSucceeded(mutationAllowed)) {
        return {mutationAllowed, empty};
    }
    const ProviderStoreResult metadataValidation =
        validateApiProfileMetadataInput(input.name, input.baseUrl);
    const ProviderStoreResult secretValidation = validateApiKeyInput(input.apiKey);
    if (!providerStoreResultSucceeded(metadataValidation) ||
        !providerStoreResultSucceeded(secretValidation)) {
        return {providerStoreResultSucceeded(metadataValidation)
                    ? secretValidation : metadataValidation,
                empty};
    }

    nvs_handle_t readHandle = 0;
    const esp_err_t readOpenError =
        nvs_open(kProviderNamespace, NVS_READONLY, &readHandle);
    if (readOpenError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for profile creation",
                                    readOpenError)),
                empty};
    }
    const ProfileCollectionResult collection = readProfileCollection(readHandle);
    const StringReadResult defaultId = providerStoreResultSucceeded(collection.result)
        ? readDefaultProfileId(readHandle)
        : StringReadResult{collection.result, false, ""};
    std::size_t slot = kMaximumApiProfiles;
    if (providerStoreResultSucceeded(defaultId.result)) {
        for (std::size_t candidate = 0; candidate < kMaximumApiProfiles; ++candidate) {
            const bool occupied = std::any_of(
                collection.profiles.begin(), collection.profiles.end(),
                [candidate](const auto& profile) { return profile.slot == candidate; });
            if (!occupied) {
                slot = candidate;
                break;
            }
        }
    }
    nvs_close(readHandle);
    if (!providerStoreResultSucceeded(collection.result)) {
        return {collection.result, empty};
    }
    if (!providerStoreResultSucceeded(defaultId.result)) {
        return {defaultId.result, empty};
    }
    if (slot == kMaximumApiProfiles) {
        return {providerError(ProviderStoreError::Conflict,
                              "The maximum of three API profiles is already stored"),
                empty};
    }
    const std::string id = uniqueProfileId(collection);
    if (id.empty()) {
        return {providerError(ProviderStoreError::Storage,
                              "Could not generate a unique API profile id"),
                empty};
    }
    const ApiProfileMetadataRecord metadataRecord = {
        id, input.name, input.baseUrl, 1,
        static_cast<std::uint16_t>(input.apiKey.size()),
    };
    const ApiProfileSecretRecord secretRecord = {1, input.apiKey};
    const EncodedProviderRecordResult metadata =
        encodeApiProfileMetadataRecord(metadataRecord);
    const EncodedProviderRecordResult secret =
        encodeApiProfileSecretRecord(secretRecord);
    const std::size_t requiredEntries = profileWriteEntryCount(metadata, secret);
    ProviderStoreResult result = checkAvailableEntries(requiredEntries);
    if (!providerStoreResultSucceeded(result)) {
        return {result, empty};
    }

    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for profile creation",
                                    openError)),
                empty};
    }
    const SelectorReadResult selector = readSelector(handle, slot);
    if (!providerStoreResultSucceeded(selector.result) || selector.found) {
        nvs_close(handle);
        return {providerStoreResultSucceeded(selector.result)
                    ? providerError(ProviderStoreError::Conflict,
                                    "API profile slot changed before creation")
                    : selector.result,
                empty};
    }
    result = prepareProfileSlot(handle, slot);
    if (!providerStoreResultSucceeded(result)) {
        nvs_close(handle);
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
        }
        result.message = "Cannot prepare API profile slot: " + result.message;
        return {result, empty};
    }
    result = checkAvailableEntries(requiredEntries);
    if (providerStoreResultSucceeded(result)) {
        result = writeProfileGeneration(handle, slot, 0, metadata, secret);
    }
    if (providerStoreResultSucceeded(result)) {
        result = writeAuthorityByte(handle, profileSelectorKey(slot), 0,
                                    "API profile selector");
    }
    nvs_close(handle);
    if (!providerStoreResultSucceeded(result)) {
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
        }
        if (result.error == ProviderStoreError::AuthorityUncertain) {
            setState(ProviderStoreState::AuthorityUncertain, result.message);
        }
        return {result, empty};
    }
    result.committed = true;
    return {result, profileSummary(metadataRecord, defaultId.value)};
}

ApiProfileMutationResult ProviderProfileStore::updateProfile(
    const std::string& id,
    const ApiProfileInput& input)
{
    const ApiProfileSummary empty = {"", "", "", 0, false};
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return {ready, empty};
    }
    const ProviderStoreResult mutationAllowed =
        requireProfileMutationAllowed();
    if (!providerStoreResultSucceeded(mutationAllowed)) {
        return {mutationAllowed, empty};
    }
    if (!isValidProviderStableId(id)) {
        return {providerError(ProviderStoreError::InvalidInput,
                              "API profile id is malformed"),
                empty};
    }
    const ProviderStoreResult metadataValidation =
        validateApiProfileMetadataInput(input.name, input.baseUrl);
    if (!providerStoreResultSucceeded(metadataValidation)) {
        return {metadataValidation, empty};
    }
    if (!input.apiKey.empty()) {
        const ProviderStoreResult secretValidation = validateApiKeyInput(input.apiKey);
        if (!providerStoreResultSucceeded(secretValidation)) {
            return {secretValidation, empty};
        }
    }

    nvs_handle_t readHandle = 0;
    const esp_err_t readOpenError =
        nvs_open(kProviderNamespace, NVS_READONLY, &readHandle);
    if (readOpenError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for profile update",
                                    readOpenError)),
                empty};
    }
    SelectedProfileResult current = findProfile(readHandle, id);
    const StringReadResult defaultId = providerStoreResultSucceeded(current.result)
        ? readDefaultProfileId(readHandle)
        : StringReadResult{current.result, false, ""};
    nvs_close(readHandle);
    if (!providerStoreResultSucceeded(current.result) || !current.found) {
        return {current.result, empty};
    }
    if (!providerStoreResultSucceeded(defaultId.result)) {
        return {defaultId.result, empty};
    }

    const std::string apiKey = input.apiKey.empty()
        ? current.secret.apiKey : input.apiKey;
    const bool authorityChanged = input.baseUrl != current.metadata.baseUrl ||
                                  apiKey != current.secret.apiKey;
    if (authorityChanged &&
        current.metadata.authorityRevision ==
            std::numeric_limits<std::uint32_t>::max()) {
        return {providerError(ProviderStoreError::Conflict,
                              "API profile authority revision is exhausted"),
                empty};
    }
    const std::uint32_t revision = authorityChanged
        ? current.metadata.authorityRevision + 1
        : current.metadata.authorityRevision;
    const ApiProfileMetadataRecord metadataRecord = {
        id, input.name, input.baseUrl, revision,
        static_cast<std::uint16_t>(apiKey.size()),
    };
    const ApiProfileSecretRecord secretRecord = {revision, apiKey};
    const EncodedProviderRecordResult metadata =
        encodeApiProfileMetadataRecord(metadataRecord);
    const EncodedProviderRecordResult secret =
        encodeApiProfileSecretRecord(secretRecord);
    const std::size_t requiredEntries = profileWriteEntryCount(metadata, secret);
    ProviderStoreResult result = checkAvailableEntries(requiredEntries);
    if (!providerStoreResultSucceeded(result)) {
        return {result, empty};
    }

    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for profile update",
                                    openError)),
                empty};
    }
    const SelectedProfileResult revalidated = readSelectedProfile(handle, current.slot);
    if (!providerStoreResultSucceeded(revalidated.result) || !revalidated.found ||
        revalidated.metadata.id != id ||
        revalidated.metadata.authorityRevision != current.metadata.authorityRevision ||
        revalidated.generation != current.generation) {
        nvs_close(handle);
        return {providerError(ProviderStoreError::Conflict,
                              "API profile changed before the bound update"),
                empty};
    }
    const std::uint8_t nextGeneration =
        static_cast<std::uint8_t>(1 - current.generation);
    result = prepareProfileGeneration(handle, current.slot, nextGeneration);
    if (!providerStoreResultSucceeded(result)) {
        nvs_close(handle);
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
        }
        result.message =
            "Cannot prepare inactive API profile generation: " + result.message;
        return {result, empty};
    }
    result = checkAvailableEntries(requiredEntries);
    if (providerStoreResultSucceeded(result)) {
        result = writeProfileGeneration(
            handle, current.slot, nextGeneration, metadata, secret);
    }
    if (providerStoreResultSucceeded(result)) {
        result = writeAuthorityByte(
            handle, profileSelectorKey(current.slot), nextGeneration,
            "API profile selector");
    }
    if (!providerStoreResultSucceeded(result)) {
        nvs_close(handle);
        if (result.outcomeUnknown) {
            profileMutationBlocked_ = true;
        }
        if (result.error == ProviderStoreError::AuthorityUncertain) {
            setState(ProviderStoreState::AuthorityUncertain, result.message);
        }
        return {result, empty};
    }
    const ProviderStoreResult cleanup = cleanupProfileGeneration(
        handle, current.slot, current.generation);
    nvs_close(handle);
    const ApiProfileSummary summary = profileSummary(metadataRecord, defaultId.value);
    if (!providerStoreResultSucceeded(cleanup)) {
        profileMutationBlocked_ = true;
        setState(ProviderStoreState::Ready, cleanup.message);
        return {cleanup, summary};
    }
    result.committed = true;
    return {result, summary};
}

ProviderStoreResult ProviderProfileStore::setDefaultProfile(
    const std::string& id)
{
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return ready;
    }
    if (!isValidProviderStableId(id)) {
        return providerError(ProviderStoreError::InvalidInput,
                             "API profile id is malformed");
    }
    nvs_handle_t readHandle = 0;
    const esp_err_t readOpenError =
        nvs_open(kProviderNamespace, NVS_READONLY, &readHandle);
    if (readOpenError != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Opening provider storage for default update",
                            readOpenError));
    }
    const SelectedProfileResult profile = findProfile(readHandle, id);
    const StringReadResult current = providerStoreResultSucceeded(profile.result)
        ? readDefaultProfileId(readHandle)
        : StringReadResult{profile.result, false, ""};
    nvs_close(readHandle);
    if (!providerStoreResultSucceeded(profile.result) || !profile.found) {
        return profile.result;
    }
    if (!providerStoreResultSucceeded(current.result)) {
        return current.result;
    }
    if (current.value == id) {
        return validProviderStoreResult();
    }
    ProviderStoreResult result = checkAvailableEntries(stringEntryCount(id.size()));
    if (!providerStoreResultSucceeded(result)) {
        return result;
    }
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Opening provider storage for default update",
                            openError));
    }
    const SelectedProfileResult revalidated = findProfile(handle, id);
    const StringReadResult revalidatedDefault =
        providerStoreResultSucceeded(revalidated.result)
            ? readDefaultProfileId(handle)
            : StringReadResult{revalidated.result, false, ""};
    if (!providerStoreResultSucceeded(revalidated.result) ||
        !revalidated.found) {
        nvs_close(handle);
        return revalidated.result;
    }
    if (!providerStoreResultSucceeded(revalidatedDefault.result)) {
        nvs_close(handle);
        return revalidatedDefault.result;
    }
    if (revalidatedDefault.value != current.value ||
        revalidated.generation != profile.generation ||
        revalidated.metadata.authorityRevision !=
            profile.metadata.authorityRevision) {
        nvs_close(handle);
        return providerError(ProviderStoreError::Conflict,
                             "Default API profile changed before the bound update");
    }
    result = writeAuthorityString(handle, kDefaultProfileKey, id,
                                  "default API profile id");
    nvs_close(handle);
    if (result.error == ProviderStoreError::AuthorityUncertain) {
        setState(ProviderStoreState::AuthorityUncertain, result.message);
    }
    return result;
}

ProviderStoreResult ProviderProfileStore::deleteProfile(const std::string& id)
{
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return ready;
    }
    const ProviderStoreResult mutationAllowed =
        requireProfileMutationAllowed();
    if (!providerStoreResultSucceeded(mutationAllowed)) {
        return mutationAllowed;
    }
    if (!isValidProviderStableId(id)) {
        return providerError(ProviderStoreError::InvalidInput,
                             "API profile id is malformed");
    }
    nvs_handle_t readHandle = 0;
    const esp_err_t readOpenError =
        nvs_open(kProviderNamespace, NVS_READONLY, &readHandle);
    if (readOpenError != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Opening provider storage for profile deletion",
                            readOpenError));
    }
    const SelectedMetadataResult profile = findProfileMetadata(readHandle, id);
    const StringReadResult defaultId = providerStoreResultSucceeded(profile.result)
        ? readDefaultProfileId(readHandle)
        : StringReadResult{profile.result, false, ""};
    nvs_close(readHandle);
    if (!providerStoreResultSucceeded(profile.result) || !profile.found) {
        return profile.result;
    }
    if (!providerStoreResultSucceeded(defaultId.result)) {
        return defaultId.result;
    }
    if (defaultId.value == id) {
        return providerError(
            ProviderStoreError::Conflict,
            "The default API profile cannot be deleted; choose another default first");
    }
    ProviderStoreResult result = checkAvailableEntries(1);
    if (!providerStoreResultSucceeded(result)) {
        return result;
    }
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Opening provider storage for profile deletion",
                            openError));
    }
    const SelectedMetadataResult revalidated = findProfileMetadata(handle, id);
    const StringReadResult revalidatedDefault =
        providerStoreResultSucceeded(revalidated.result)
            ? readDefaultProfileId(handle)
            : StringReadResult{revalidated.result, false, ""};
    if (!providerStoreResultSucceeded(revalidated.result) ||
        !revalidated.found ||
        !providerStoreResultSucceeded(revalidatedDefault.result) ||
        revalidatedDefault.value == id ||
        revalidated.generation != profile.generation) {
        nvs_close(handle);
        return providerError(ProviderStoreError::Conflict,
                             "API profile changed before the bound deletion");
    }
    result = eraseAuthorityKey(handle, profileSelectorKey(profile.slot),
                               "API profile selector");
    if (!providerStoreResultSucceeded(result)) {
        nvs_close(handle);
        if (result.error == ProviderStoreError::AuthorityUncertain) {
            setState(ProviderStoreState::AuthorityUncertain, result.message);
        }
        return result;
    }
    const ProviderStoreResult cleanup = cleanupProfileSlot(handle, profile.slot);
    nvs_close(handle);
    if (!providerStoreResultSucceeded(cleanup)) {
        profileMutationBlocked_ = true;
        setState(ProviderStoreState::Ready, cleanup.message);
        return cleanup;
    }
    result.committed = true;
    return result;
}

ProviderStoreResult ProviderProfileStore::updateDefaultBaseUrl(
    const std::string& baseUrl)
{
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return ready;
    }
    ApiProfilesResult profiles = listProfiles();
    if (!providerStoreResultSucceeded(profiles.result)) {
        return profiles.result;
    }
    const auto profile = std::find_if(
        profiles.profiles.begin(), profiles.profiles.end(),
        [&profiles](const auto& candidate) {
            return candidate.id == profiles.defaultProfileId;
        });
    if (profile == profiles.profiles.end()) {
        setState(ProviderStoreState::Corrupt,
                 "Default API profile is missing during base URL update");
        return requireReady();
    }
    return updateProfile(profile->id, {profile->name, baseUrl, ""}).result;
}

ModelPresetsResult ProviderProfileStore::listModelPresets()
{
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return {ready, {}};
    }
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READONLY, &handle);
    if (openError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for preset listing",
                                    openError)),
                {}};
    }
    PresetCollectionResult collection = readPresetCollection(handle);
    nvs_close(handle);
    if (!providerStoreResultSucceeded(collection.result)) {
        return {collection.result, {}};
    }
    std::vector<ModelPresetRecord> presets;
    presets.reserve(collection.presets.size());
    for (StoredPreset& preset : collection.presets) {
        presets.push_back(std::move(preset.record));
    }
    return {validProviderStoreResult(), std::move(presets)};
}

ModelPresetMutationResult ProviderProfileStore::createModelPreset(
    const ModelPresetInput& input)
{
    const ModelPresetRecord empty = {"", "", "", 0};
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return {ready, empty};
    }
    const ProviderStoreResult validation = validateModelPresetInput(input);
    if (!providerStoreResultSucceeded(validation)) {
        return {validation, empty};
    }
    nvs_handle_t readHandle = 0;
    const esp_err_t readOpenError =
        nvs_open(kProviderNamespace, NVS_READONLY, &readHandle);
    if (readOpenError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for preset creation",
                                    readOpenError)),
                empty};
    }
    const PresetCollectionResult collection = readPresetCollection(readHandle);
    std::size_t slot = kMaximumModelPresets;
    if (providerStoreResultSucceeded(collection.result)) {
        for (std::size_t candidate = 0; candidate < kMaximumModelPresets; ++candidate) {
            const bool occupied = std::any_of(
                collection.presets.begin(), collection.presets.end(),
                [candidate](const auto& preset) { return preset.slot == candidate; });
            if (!occupied) {
                slot = candidate;
                break;
            }
        }
    }
    nvs_close(readHandle);
    if (!providerStoreResultSucceeded(collection.result)) {
        return {collection.result, empty};
    }
    if (slot == kMaximumModelPresets) {
        return {providerError(ProviderStoreError::Conflict,
                              "The maximum of six model presets is already stored"),
                empty};
    }
    const std::string id = uniquePresetId(collection);
    if (id.empty()) {
        return {providerError(ProviderStoreError::Storage,
                              "Could not generate a unique model preset id"),
                empty};
    }
    const ModelPresetRecord record = {
        id, input.name, input.model, input.maximumOutputTokens};
    const EncodedProviderRecordResult encoded = encodeModelPresetRecord(record);
    if (!providerStoreResultSucceeded(encoded.result)) {
        return {encoded.result, empty};
    }
    ProviderStoreResult result = checkAvailableEntries(blobEntryCount(encoded.bytes.size()));
    if (!providerStoreResultSucceeded(result)) {
        return {result, empty};
    }
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for preset creation",
                                    openError)),
                empty};
    }
    const BlobReadResult revalidated = readBlob(
        handle, presetKey(slot), kMaximumPresetRecordBytes, "model preset");
    if (!providerStoreResultSucceeded(revalidated.result) || revalidated.found) {
        nvs_close(handle);
        return {providerStoreResultSucceeded(revalidated.result)
                    ? providerError(ProviderStoreError::Conflict,
                                    "Model preset slot changed before creation")
                    : revalidated.result,
                empty};
    }
    result = writeAuthorityBlob(handle, presetKey(slot), encoded.bytes,
                                "model preset");
    nvs_close(handle);
    if (result.error == ProviderStoreError::AuthorityUncertain) {
        setState(ProviderStoreState::AuthorityUncertain, result.message);
    }
    return {result, providerStoreResultSucceeded(result) ? record : empty};
}

ModelPresetMutationResult ProviderProfileStore::updateModelPreset(
    const std::string& id,
    const ModelPresetInput& input)
{
    const ModelPresetRecord empty = {"", "", "", 0};
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return {ready, empty};
    }
    if (!isValidProviderStableId(id)) {
        return {providerError(ProviderStoreError::InvalidInput,
                              "Model preset id is malformed"),
                empty};
    }
    const ProviderStoreResult validation = validateModelPresetInput(input);
    if (!providerStoreResultSucceeded(validation)) {
        return {validation, empty};
    }
    nvs_handle_t readHandle = 0;
    const esp_err_t readOpenError =
        nvs_open(kProviderNamespace, NVS_READONLY, &readHandle);
    if (readOpenError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for preset update",
                                    readOpenError)),
                empty};
    }
    const PresetCollectionResult collection = readPresetCollection(readHandle);
    nvs_close(readHandle);
    if (!providerStoreResultSucceeded(collection.result)) {
        return {collection.result, empty};
    }
    const auto current = std::find_if(
        collection.presets.begin(), collection.presets.end(),
        [&id](const auto& preset) { return preset.record.id == id; });
    if (current == collection.presets.end()) {
        return {providerError(ProviderStoreError::NotFound,
                              "Model preset is unavailable"),
                empty};
    }
    const std::size_t slot = current->slot;
    const ModelPresetRecord record = {
        id, input.name, input.model, input.maximumOutputTokens};
    const EncodedProviderRecordResult encoded = encodeModelPresetRecord(record);
    if (!providerStoreResultSucceeded(encoded.result)) {
        return {encoded.result, empty};
    }
    ProviderStoreResult result = checkAvailableEntries(blobEntryCount(encoded.bytes.size()));
    if (!providerStoreResultSucceeded(result)) {
        return {result, empty};
    }
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider storage for preset update",
                                    openError)),
                empty};
    }
    const PresetCollectionResult revalidated = readPresetCollection(handle);
    const auto currentNow = providerStoreResultSucceeded(revalidated.result)
        ? std::find_if(
              revalidated.presets.begin(), revalidated.presets.end(),
              [&id](const auto& preset) { return preset.record.id == id; })
        : revalidated.presets.end();
    if (!providerStoreResultSucceeded(revalidated.result) ||
        currentNow == revalidated.presets.end() || currentNow->slot != slot ||
        currentNow->record.name != current->record.name ||
        currentNow->record.model != current->record.model ||
        currentNow->record.maximumOutputTokens != current->record.maximumOutputTokens) {
        nvs_close(handle);
        return {providerError(ProviderStoreError::Conflict,
                              "Model preset changed before the bound update"),
                empty};
    }
    result = writeAuthorityBlob(handle, presetKey(slot), encoded.bytes,
                                "model preset");
    nvs_close(handle);
    if (result.error == ProviderStoreError::AuthorityUncertain) {
        setState(ProviderStoreState::AuthorityUncertain, result.message);
    }
    return {result, providerStoreResultSucceeded(result) ? record : empty};
}

ProviderStoreResult ProviderProfileStore::deleteModelPreset(
    const std::string& id)
{
    const ProviderStoreResult ready = requireReady();
    if (!providerStoreResultSucceeded(ready)) {
        return ready;
    }
    if (!isValidProviderStableId(id)) {
        return providerError(ProviderStoreError::InvalidInput,
                             "Model preset id is malformed");
    }
    nvs_handle_t readHandle = 0;
    const esp_err_t readOpenError =
        nvs_open(kProviderNamespace, NVS_READONLY, &readHandle);
    if (readOpenError != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Opening provider storage for preset deletion",
                            readOpenError));
    }
    const PresetCollectionResult collection = readPresetCollection(readHandle);
    nvs_close(readHandle);
    if (!providerStoreResultSucceeded(collection.result)) {
        return collection.result;
    }
    const auto current = std::find_if(
        collection.presets.begin(), collection.presets.end(),
        [&id](const auto& preset) { return preset.record.id == id; });
    if (current == collection.presets.end()) {
        return providerError(ProviderStoreError::NotFound,
                             "Model preset is unavailable");
    }
    ProviderStoreResult result = checkAvailableEntries(1);
    if (!providerStoreResultSucceeded(result)) {
        return result;
    }
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READWRITE, &handle);
    if (openError != ESP_OK) {
        return providerError(
            ProviderStoreError::Storage,
            nvsErrorMessage("Opening provider storage for preset deletion",
                            openError));
    }
    const PresetCollectionResult revalidated = readPresetCollection(handle);
    const auto currentNow = providerStoreResultSucceeded(revalidated.result)
        ? std::find_if(
              revalidated.presets.begin(), revalidated.presets.end(),
              [&id](const auto& preset) { return preset.record.id == id; })
        : revalidated.presets.end();
    if (!providerStoreResultSucceeded(revalidated.result) ||
        currentNow == revalidated.presets.end() ||
        currentNow->slot != current->slot) {
        nvs_close(handle);
        return providerError(ProviderStoreError::Conflict,
                             "Model preset changed before the bound deletion");
    }
    result = eraseAuthorityKey(handle, presetKey(current->slot), "model preset");
    nvs_close(handle);
    if (result.error == ProviderStoreError::AuthorityUncertain) {
        setState(ProviderStoreState::AuthorityUncertain, result.message);
    }
    return result;
}

ProviderStorageStatsResult ProviderProfileStore::storageStats()
{
    nvs_stats_t stats = {};
    const esp_err_t statsError = nvs_get_stats(nullptr, &stats);
    if (statsError != ESP_OK) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Reading aggregate provider storage statistics",
                                    statsError)),
                {0, 0, 0, 0}};
    }
    std::size_t namespaceEntries = 0;
    nvs_handle_t handle = 0;
    const esp_err_t openError = nvs_open(kProviderNamespace, NVS_READONLY, &handle);
    if (openError == ESP_OK) {
        const esp_err_t countError =
            nvs_get_used_entry_count(handle, &namespaceEntries);
        nvs_close(handle);
        if (countError != ESP_OK) {
            return {providerError(
                        ProviderStoreError::Storage,
                        nvsErrorMessage("Reading provider namespace entry count",
                                        countError)),
                    {0, 0, 0, 0}};
        }
        ++namespaceEntries;
    } else if (openError != ESP_ERR_NVS_NOT_FOUND) {
        return {providerError(
                    ProviderStoreError::Storage,
                    nvsErrorMessage("Opening provider namespace for statistics",
                                    openError)),
                {0, 0, 0, 0}};
    }
    return {validProviderStoreResult(),
            {stats.total_entries, stats.used_entries, stats.available_entries,
             namespaceEntries}};
}

#endif

}  // namespace cardputer
