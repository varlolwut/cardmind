namespace {

void clearDeviceModelDiscovery()
{
    availableModels.clear();
    availableModelsAuthority = {
        cardputer::ProviderAuthorityKind::None, "", 0};
}

cardputer::ProviderStoreResult reloadDeviceDefaultProvider()
{
    return providerProfileStore.loadDefaultInto(settings);
}

void showDeviceProviderResult(const String& title, const String& message)
{
    modalSelection(title, {message, "Back"}, 1,
                   "UP/DOWN  ENTER close");
}

struct DeviceApiProfileInputResult {
    bool accepted;
    cardputer::ApiProfileInput input;
};

DeviceApiProfileInputResult collectNewApiProfile()
{
    std::string name;
    std::string baseUrl;
    std::string apiKey;
    if (!modalTextInput("NEW API PROFILE", "Profile name", "", 48,
                        false, name) ||
        !modalTextInput("API BASE URL", "https://api.example.com", "", 180,
                        false, baseUrl) ||
        !modalTextInput("API KEY", "Required; never displayed", "", 512,
                        true, apiKey)) {
        return {false, {"", "", ""}};
    }
    return {true, {std::move(name), std::move(baseUrl), std::move(apiKey)}};
}

DeviceApiProfileInputResult collectApiProfileEdit(
    const cardputer::ApiProfileSummary& current)
{
    std::string name;
    std::string baseUrl;
    std::string apiKey;
    if (!modalTextInput("EDIT API PROFILE", "Profile name", current.name, 48,
                        false, name) ||
        !modalTextInput("API BASE URL", "https://api.example.com",
                        current.baseUrl, 180, false, baseUrl) ||
        !modalTextInput("API KEY", "Blank keeps saved key", "", 512,
                        true, apiKey)) {
        return {false, {"", "", ""}};
    }
    return {true, {std::move(name), std::move(baseUrl), std::move(apiKey)}};
}

String refreshDeviceHotProviderAfterMutation(
    const cardputer::ProviderStoreResult& mutation,
    bool affectsDefault)
{
    if (!mutation.committed) return "";
    clearDeviceModelDiscovery();
    if (!affectsDefault) return "";
    const cardputer::ProviderStoreResult loaded = reloadDeviceDefaultProvider();
    return cardputer::providerStoreResultSucceeded(loaded)
        ? String()
        : String("Provider saved, but active settings reload failed: ") +
              String(loaded.message.c_str());
}

void createDeviceApiProfile()
{
    DeviceApiProfileInputResult entered = collectNewApiProfile();
    if (!entered.accepted) return;
    const cardputer::ApiProfileMutationResult created =
        providerProfileStore.createProfile(entered.input);
    const String reloadError =
        refreshDeviceHotProviderAfterMutation(created.result, false);
    showDeviceProviderResult(
        cardputer::providerStoreResultSucceeded(created.result)
            ? String("API PROFILE SAVED") : String("API PROFILE ERROR"),
        cardputer::providerStoreResultSucceeded(created.result)
            ? (reloadError.isEmpty() ? String(created.profile.name.c_str())
                                     : reloadError)
            : String(created.result.message.c_str()));
}

void editDeviceApiProfile(const cardputer::ApiProfileSummary& current)
{
    DeviceApiProfileInputResult entered = collectApiProfileEdit(current);
    if (!entered.accepted) return;
    const cardputer::ApiProfileMutationResult updated =
        providerProfileStore.updateProfile(current.id, entered.input);
    const String reloadError = refreshDeviceHotProviderAfterMutation(
        updated.result, current.isDefault);
    const bool succeeded =
        cardputer::providerStoreResultSucceeded(updated.result);
    String message;
    if (succeeded) {
        message = reloadError.isEmpty() ? String(updated.profile.name.c_str())
                                        : reloadError;
    } else if (updated.result.committed) {
        message = String(updated.profile.name.c_str()) +
                  "\nSaved, but cleanup did not finish: " +
                  String(updated.result.message.c_str());
        if (!reloadError.isEmpty()) message += "\n" + reloadError;
    } else {
        message = String(updated.result.message.c_str());
    }
    showDeviceProviderResult(
        succeeded ? String("API PROFILE SAVED")
                  : (updated.result.committed
                         ? String("SAVED WITH WARNING")
                         : String("API PROFILE ERROR")),
        message);
}

void makeDeviceApiProfileDefault(
    const cardputer::ApiProfileSummary& current)
{
    const cardputer::ProviderStoreResult updated =
        providerProfileStore.setDefaultProfile(current.id);
    const String reloadError =
        refreshDeviceHotProviderAfterMutation(updated, true);
    showDeviceProviderResult(
        cardputer::providerStoreResultSucceeded(updated)
            ? String("DEFAULT PROFILE") : String("API PROFILE ERROR"),
        cardputer::providerStoreResultSucceeded(updated)
            ? (reloadError.isEmpty() ? String(current.name.c_str())
                                     : reloadError)
            : String(updated.message.c_str()));
}

void deleteDeviceApiProfile(const cardputer::ApiProfileSummary& current)
{
    if (modalSelection("DELETE API PROFILE",
                       {"Delete " + String(current.name.c_str()), "Cancel"},
                       1, "ENTER confirm  ESC cancel") != 0) {
        return;
    }
    const cardputer::ProviderStoreResult deleted =
        providerProfileStore.deleteProfile(current.id);
    static_cast<void>(refreshDeviceHotProviderAfterMutation(deleted, false));
    const bool succeeded = cardputer::providerStoreResultSucceeded(deleted);
    showDeviceProviderResult(
        succeeded ? String("API PROFILE DELETED")
                  : (deleted.committed
                         ? String("DELETED WITH WARNING")
                         : String("API PROFILE ERROR")),
        succeeded ? String(current.name.c_str())
                  : (deleted.committed
                         ? String(current.name.c_str()) +
                               "\nDeleted, but cleanup did not finish: " +
                               String(deleted.message.c_str())
                         : String(deleted.message.c_str())));
}

void manageDeviceApiProfile(const cardputer::ApiProfileSummary& current)
{
    while (true) {
        const int action = modalSelection(
            String(current.name.c_str()),
            {"Edit", current.isDefault ? "Already default" : "Use as default",
             "Delete", "Back"},
            0, "UP/DOWN  ENTER  ESC back");
        if (action < 0 || action == 3) return;
        if (action == 0) {
            editDeviceApiProfile(current);
            return;
        }
        if (action == 1) {
            if (!current.isDefault) makeDeviceApiProfileDefault(current);
            return;
        }
        if (action == 2) {
            deleteDeviceApiProfile(current);
            return;
        }
    }
}

void retryDeviceLegacyProviderMigration()
{
    const cardputer::ProviderStoreResult migrated =
        providerProfileStore.retryLegacyMigration(settings);
    const String reloadError =
        refreshDeviceHotProviderAfterMutation(migrated, true);
    showDeviceProviderResult(
        cardputer::providerStoreResultSucceeded(migrated)
            ? String("API PROFILES READY") : String("MIGRATION ERROR"),
        cardputer::providerStoreResultSucceeded(migrated)
            ? (reloadError.isEmpty() ? String("Legacy settings migrated")
                                     : reloadError)
            : String(migrated.message.c_str()));
}

void manageDeviceApiProfiles()
{
    while (true) {
        if (providerProfileStore.state() !=
            cardputer::ProviderStoreState::Ready) {
            std::vector<String> actions;
            if (providerProfileStore.state() ==
                cardputer::ProviderStoreState::LegacyRetained) {
                actions = {"Retry migration", "Back"};
            } else {
                actions = {String(providerProfileStore.stateMessage().c_str()),
                           "Back"};
            }
            const int action = modalSelection(
                "API PROFILES", actions, actions.size() - 1,
                "ENTER  ESC back");
            if (action == 0 && providerProfileStore.state() ==
                    cardputer::ProviderStoreState::LegacyRetained) {
                retryDeviceLegacyProviderMigration();
                continue;
            }
            return;
        }
        const cardputer::ApiProfilesResult profiles =
            providerProfileStore.listProfiles();
        if (!cardputer::providerStoreResultSucceeded(profiles.result)) {
            showDeviceProviderResult("API PROFILE ERROR",
                                     String(profiles.result.message.c_str()));
            return;
        }
        std::vector<String> items = {"New API profile"};
        for (const cardputer::ApiProfileSummary& profile : profiles.profiles) {
            items.push_back(String(profile.name.c_str()) +
                            (profile.isDefault ? " · default" : ""));
        }
        items.push_back("Back");
        const int selected = modalSelection(
            "API PROFILES", items, 0, "UP/DOWN  ENTER  ESC back");
        if (selected < 0 || selected == static_cast<int>(items.size() - 1)) {
            return;
        }
        if (selected == 0) {
            createDeviceApiProfile();
        } else {
            manageDeviceApiProfile(
                profiles.profiles[static_cast<std::size_t>(selected - 1)]);
        }
    }
}

struct DevicePresetInputResult {
    bool accepted;
    cardputer::ModelPresetInput input;
};

DevicePresetInputResult collectDevicePresetInput(
    const cardputer::ModelPresetInput& initial)
{
    std::string name;
    std::string model;
    std::string output;
    if (!modalTextInput("MODEL PRESET", "Preset name", initial.name, 48,
                        false, name) ||
        !modalTextInput("MODEL ID", "Editable model id", initial.model, 120,
                        false, model) ||
        !modalTextInput("OUTPUT TOKENS", "128-8192",
                        std::to_string(initial.maximumOutputTokens), 4,
                        false, output)) {
        return {false, {"", "", 0}};
    }
    std::uint32_t outputTokens = 0;
    for (const char character : output) {
        if (character < '0' || character > '9') {
            return {true, {std::move(name), std::move(model), 0}};
        }
        outputTokens = outputTokens * 10U +
            static_cast<std::uint32_t>(character - '0');
    }
    return {true, {std::move(name), std::move(model), outputTokens}};
}

void createDeviceModelPreset()
{
    const DevicePresetInputResult entered = collectDevicePresetInput(
        {"", settings.model.c_str(), 1024U});
    if (!entered.accepted) return;
    const cardputer::ModelPresetMutationResult created =
        providerProfileStore.createModelPreset(entered.input);
    showDeviceProviderResult(
        cardputer::providerStoreResultSucceeded(created.result)
            ? String("MODEL PRESET SAVED") : String("MODEL PRESET ERROR"),
        cardputer::providerStoreResultSucceeded(created.result)
            ? String(created.preset.name.c_str())
            : String(created.result.message.c_str()));
}

void editDeviceModelPreset(const cardputer::ModelPresetRecord& current)
{
    const DevicePresetInputResult entered = collectDevicePresetInput(
        {current.name, current.model, current.maximumOutputTokens});
    if (!entered.accepted) return;
    const cardputer::ModelPresetMutationResult updated =
        providerProfileStore.updateModelPreset(current.id, entered.input);
    showDeviceProviderResult(
        cardputer::providerStoreResultSucceeded(updated.result)
            ? String("MODEL PRESET SAVED") : String("MODEL PRESET ERROR"),
        cardputer::providerStoreResultSucceeded(updated.result)
            ? String(updated.preset.name.c_str())
            : String(updated.result.message.c_str()));
}

void discoverDeviceModelForPreset(
    const cardputer::ModelPresetRecord& current)
{
    const cardputer::ProjectDocumentResult project =
        cardputer::loadProject(activeProjectId);
    if (!project.success) {
        showDeviceProviderResult("MODEL DISCOVERY", project.error);
        return;
    }
    refreshModels(project.project.apiProfile);
    if (availableModels.empty()) {
        showDeviceProviderResult("MODEL DISCOVERY", statusMessage);
        return;
    }
    const auto existing = std::find(
        availableModels.begin(), availableModels.end(),
        String(current.model.c_str()));
    const std::size_t initial = existing == availableModels.end()
        ? 0 : static_cast<std::size_t>(
            std::distance(availableModels.begin(), existing));
    const int selected = modalSelection(
        "DISCOVERED MODELS", availableModels, initial,
        "UP/DOWN  ENTER choose  ESC cancel");
    if (selected < 0) return;
    const cardputer::ModelPresetMutationResult updated =
        providerProfileStore.updateModelPreset(
            current.id,
            {current.name,
             std::string(availableModels[static_cast<std::size_t>(selected)].c_str()),
             current.maximumOutputTokens});
    showDeviceProviderResult(
        cardputer::providerStoreResultSucceeded(updated.result)
            ? String("MODEL PRESET SAVED") : String("MODEL PRESET ERROR"),
        cardputer::providerStoreResultSucceeded(updated.result)
            ? availableModels[static_cast<std::size_t>(selected)]
            : String(updated.result.message.c_str()));
}

void applyDeviceModelPreset(const cardputer::ModelPresetRecord& current)
{
    cardputer::ProjectDocumentResult project =
        cardputer::loadProject(activeProjectId);
    if (!project.success) {
        showDeviceProviderResult("PRESET APPLY ERROR", project.error);
        return;
    }
    project.project.model = String(current.model.c_str());
    project.project.maximumOutputTokens = current.maximumOutputTokens;
    const cardputer::OperationResult saved =
        cardputer::saveProject(project.project);
    if (!saved.success) {
        showDeviceProviderResult("PRESET APPLY ERROR", saved.error);
        return;
    }
    activeProjectDocument.model = project.project.model;
    activeProjectDocument.maximumOutputTokens =
        project.project.maximumOutputTokens;
    const cardputer::ProjectDocumentResult canonical =
        cardputer::loadProject(activeProjectId);
    if (!canonical.success) {
        showDeviceProviderResult(
            "PRESET APPLIED",
            "Project saved, but active project reload failed: " +
                canonical.error);
        return;
    }
    activeProjectDocument = canonical.project;
    showDeviceProviderResult("PRESET APPLIED", String(current.name.c_str()));
}

void deleteDeviceModelPreset(const cardputer::ModelPresetRecord& current)
{
    if (modalSelection("DELETE MODEL PRESET",
                       {"Delete " + String(current.name.c_str()), "Cancel"},
                       1, "ENTER confirm  ESC cancel") != 0) {
        return;
    }
    const cardputer::ProviderStoreResult deleted =
        providerProfileStore.deleteModelPreset(current.id);
    showDeviceProviderResult(
        cardputer::providerStoreResultSucceeded(deleted)
            ? String("MODEL PRESET DELETED") : String("MODEL PRESET ERROR"),
        cardputer::providerStoreResultSucceeded(deleted)
            ? String(current.name.c_str()) : String(deleted.message.c_str()));
}

void manageDeviceModelPreset(const cardputer::ModelPresetRecord& current)
{
    const int action = modalSelection(
        String(current.name.c_str()),
        {"Edit", "Discover model", "Apply to active project", "Delete", "Back"},
        0, "UP/DOWN  ENTER  ESC back");
    if (action == 0) editDeviceModelPreset(current);
    else if (action == 1) discoverDeviceModelForPreset(current);
    else if (action == 2) applyDeviceModelPreset(current);
    else if (action == 3) deleteDeviceModelPreset(current);
}

void manageDeviceModelPresets()
{
    while (true) {
        const cardputer::ModelPresetsResult presets =
            providerProfileStore.listModelPresets();
        if (!cardputer::providerStoreResultSucceeded(presets.result)) {
            showDeviceProviderResult("MODEL PRESET ERROR",
                                     String(presets.result.message.c_str()));
            return;
        }
        std::vector<String> items = {"New model preset"};
        for (const cardputer::ModelPresetRecord& preset : presets.presets) {
            items.push_back(String(preset.name.c_str()) + " · " +
                            String(preset.model.c_str()));
        }
        items.push_back("Back");
        const int selected = modalSelection(
            "MODEL PRESETS", items, 0, "UP/DOWN  ENTER  ESC back");
        if (selected < 0 || selected == static_cast<int>(items.size() - 1)) {
            return;
        }
        if (selected == 0) {
            createDeviceModelPreset();
        } else {
            manageDeviceModelPreset(
                presets.presets[static_cast<std::size_t>(selected - 1)]);
        }
    }
}

void runProviderProfiles()
{
    while (true) {
        const int selected = modalSelection(
            "AI PROVIDERS", {"API profiles", "Model presets", "Back"},
            0, "UP/DOWN  ENTER  ESC back");
        if (selected < 0 || selected == 2) return;
        if (selected == 0) manageDeviceApiProfiles();
        else manageDeviceModelPresets();
    }
}

String deviceProjectApiProfileLabel(
    const cardputer::ProjectDocument& project)
{
    if (project.apiProfile.isEmpty()) {
        return "API profile: Global default";
    }
    const cardputer::ApiProfilesResult profiles =
        providerProfileStore.listProfiles();
    if (!cardputer::providerStoreResultSucceeded(profiles.result)) {
        return "API profile: Unavailable";
    }
    const auto selected = std::find_if(
        profiles.profiles.begin(), profiles.profiles.end(),
        [&project](const cardputer::ApiProfileSummary& profile) {
            return profile.id == project.apiProfile.c_str();
        });
    return selected == profiles.profiles.end()
        ? String("API profile: Unavailable")
        : String("API profile: ") + String(selected->name.c_str());
}

String assignDeviceProjectApiProfile(const String& projectId)
{
    const cardputer::ProjectDocumentResult original =
        cardputer::loadProject(projectId);
    if (!original.success) return original.error;
    const cardputer::ApiProfilesResult profiles =
        providerProfileStore.listProfiles();
    if (!cardputer::providerStoreResultSucceeded(profiles.result)) {
        return String(profiles.result.message.c_str());
    }
    std::vector<String> items = {"Use global default"};
    std::size_t initial = 0;
    for (std::size_t index = 0; index < profiles.profiles.size(); ++index) {
        const cardputer::ApiProfileSummary& profile = profiles.profiles[index];
        items.push_back(String(profile.name.c_str()) +
                        (profile.isDefault ? " · default" : ""));
        if (profile.id == original.project.apiProfile.c_str()) {
            initial = index + 1;
        }
    }
    if (!original.project.apiProfile.isEmpty() && initial == 0) {
        items.push_back("Unavailable current profile");
        initial = items.size() - 1;
    }
    items.push_back("Cancel");
    const int selected = modalSelection(
        "PROJECT API PROFILE", items, initial,
        "UP/DOWN  ENTER  ESC cancel");
    if (selected < 0 || selected == static_cast<int>(items.size() - 1) ||
        static_cast<std::size_t>(selected) > profiles.profiles.size()) {
        return "Project API profile unchanged";
    }
    const String selectedId = selected == 0
        ? String() : String(profiles.profiles[
              static_cast<std::size_t>(selected - 1)].id.c_str());
    if (selectedId == original.project.apiProfile) {
        return "Project API profile unchanged";
    }
    cardputer::ProjectDocumentResult current = cardputer::loadProject(projectId);
    if (!current.success) return current.error;
    current.project.apiProfile = selectedId;
    const cardputer::OperationResult saved =
        cardputer::saveProject(current.project);
    if (!saved.success) return saved.error;
    clearDeviceModelDiscovery();
    if (projectId == activeProjectId) {
        const cardputer::ProjectDocumentResult canonical =
            cardputer::loadProject(projectId);
        if (!canonical.success) {
            return "Project API profile saved, but active project reload failed: " +
                canonical.error;
        }
        activeProjectDocument = canonical.project;
    }
    return selectedId.isEmpty()
        ? String("Project uses global API profile")
        : String("Project API profile saved");
}

}  // namespace
