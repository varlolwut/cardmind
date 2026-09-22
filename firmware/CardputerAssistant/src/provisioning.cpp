#include "provisioning.h"

#include "python_mode.h"
#include "storage.h"
#include "ui.h"
#include "wifi_networks.h"

#include <WebServer.h>
#include <WiFi.h>
#include <esp_system.h>

#include <algorithm>
#include <vector>

namespace cardputer {
namespace {

constexpr const char* kDefaultModel = "claude-sonnet-4-6";
constexpr const char* kDefaultApiBaseUrl = "";
constexpr const char* kDefaultSttBaseUrl = "https://api.groq.com/openai/v1";
constexpr const char* kDefaultSttModel = "whisper-large-v3-turbo";
constexpr const char* kDefaultWebSearchBaseUrl = "https://api.exa.ai";
constexpr const char* kDefaultTtsBaseUrl = "https://api.elevenlabs.io";
constexpr const char* kDefaultTtsModel = "eleven_multilingual_v2";
constexpr const char* kDefaultTtsVoice = "JBFqnCBsd6RMkjVDRZzb";
constexpr std::uint32_t kRestartDelayMs = 5000;
constexpr const char* kSetupPageStyle =
    ":root{color-scheme:light;--canvas:#aaa49a;--paper:#ded8ce;--ink:#242622;"
    "--muted:#59564f;--line:#746f66;--accent:#a85f12;--signal:#c77d24;"
    "--select:#e6c89c;--warning:#f5dfaa;--danger:#f0d2ca;--graphite:#242724;"
    "--raised:#30332f;--instrument:#f3eee4;--instrument-muted:#c9c1b4}"
    "*{box-sizing:border-box}html{background:var(--canvas)}"
    "body{margin:0;min-width:280px;background:var(--canvas);color:var(--ink);"
    "font:15px/1.5 system-ui,-apple-system,BlinkMacSystemFont,'Segoe UI',sans-serif}"
    ".instrument{background:var(--graphite);color:var(--instrument);"
    "border-bottom:4px solid var(--signal)}"
    ".instrument-inner,.shell{max-width:680px;margin:0 auto}"
    ".instrument-inner{padding:22px 18px 20px}.shell{padding:20px 18px 36px}"
    ".eyebrow{margin:0 0 4px;color:var(--signal);font-size:14px;font-weight:800;"
    "letter-spacing:.08em;text-transform:uppercase}"
    "h1,.instrument-title{margin:0;font-size:20px;line-height:1.25;font-weight:800}"
    ".instrument-note{margin:7px 0 0;color:var(--instrument-muted);font-size:14px}"
    ".setup-card,.result-card{background:var(--paper);border:1px solid var(--line);"
    "border-radius:2px;padding:20px}"
    ".section{padding:0 0 20px}.section+.section{border-top:1px solid var(--line);"
    "padding-top:20px}.section:last-of-type{padding-bottom:0}"
    ".section h2{margin:0 0 12px;font-size:18px;line-height:1.3}"
    ".section-kicker{margin:0 0 3px;color:var(--accent);font-size:14px;"
    "font-weight:800;text-transform:uppercase}"
    "label{display:block;margin:13px 0 5px;font-size:14px;font-weight:700}"
    "input,select,button{font:inherit}input,select{display:block;width:100%;"
    "min-height:44px;padding:10px 11px;border:1px solid var(--line);border-radius:2px;"
    "background:var(--instrument);color:var(--ink)}select{background:var(--select)}"
    "input::placeholder{color:#69645c;opacity:1}"
    "input:focus-visible,select:focus-visible,button:focus-visible{outline:3px solid var(--signal);"
    "outline-offset:2px;border-color:var(--ink)}"
    ".note{margin:7px 0 0;color:var(--muted);font-size:14px}"
    ".check-row{display:flex;align-items:center;gap:10px;min-height:44px;margin-top:13px}"
    ".check-row input{flex:0 0 auto;min-height:18px;height:18px;margin:0;accent-color:var(--accent)}"
    ".actions{border-top:1px solid var(--line);margin-top:20px;padding-top:20px}"
    "button{width:100%;min-height:44px;padding:10px 18px;border:1px solid #6f3d09;"
    "border-radius:2px;background:var(--signal);color:#1f211f;font-weight:800;cursor:pointer}"
    ".notice{margin:0 0 16px;padding:12px 14px;border:1px solid;border-left-width:4px;"
    "border-radius:2px}.notice p{margin:7px 0 0}.notice h1{margin:0}"
    ".notice.error{background:var(--danger);border-color:#922f27;color:#5f211c}"
    ".notice.warning{background:var(--warning);border-color:#765014;color:#59400f}"
    ".notice.success{background:var(--select);border-color:var(--accent);color:var(--ink)}"
    ".result-card{margin-top:4px}.result-copy{margin:16px 0 0;color:var(--muted)}"
    "@media(max-width:480px){.instrument-inner{padding:20px 16px 18px}"
    ".shell{padding:16px 12px 28px}.setup-card,.result-card{padding:16px 14px}}";
WebServer webServer(80);
Settings currentSettings;
WifiScanResult nearbyNetworkScan = {true, {}, ""};
bool restartPending = false;
bool routesConfigured = false;
bool exitRequested = false;
bool saveBlocksExit = false;
std::uint32_t restartAt = 0;
String serialCommand;
ProviderProfileStore* currentProviderStore = nullptr;

String htmlEscape(const String& value)
{
    String result;
    result.reserve(value.length() + 16);
    for (std::size_t index = 0; index < value.length(); ++index) {
        const char character = value[index];
        switch (character) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default: result += character; break;
        }
    }
    return result;
}

bool containsNetwork(const std::vector<WifiNetwork>& networks, const String& ssid)
{
    for (const auto& network : networks) {
        if (network.ssid == ssid) {
            return true;
        }
    }
    return false;
}

String networkOptions(const std::vector<WifiNetwork>& networks, const String& selectedSsid)
{
    String options;
    for (const auto& network : networks) {
        options += "<option value='" + htmlEscape(network.ssid) + "'";
        if (network.ssid == selectedSsid) {
            options += " selected";
        }
        options += ">" + htmlEscape(network.ssid) + " (" + String(network.rssi) + " dBm" +
                   (network.secured ? ", locked)</option>" : ", open)</option>");
    }
    const bool manualSelected = selectedSsid.isEmpty() || !containsNetwork(networks, selectedSsid);
    options += String("<option value='' ") + (manualSelected ? "selected" : "") +
               ">Hidden network / manual entry</option>";
    return options;
}

String setupPage(const String& error)
{
    const String model = currentSettings.model.isEmpty() ? String(kDefaultModel) : currentSettings.model;
    const String apiBaseUrl = currentSettings.apiBaseUrl.isEmpty()
        ? String(kDefaultApiBaseUrl) : currentSettings.apiBaseUrl;
    const String sttBaseUrl = currentSettings.sttBaseUrl.isEmpty()
        ? String(kDefaultSttBaseUrl) : currentSettings.sttBaseUrl;
    const String sttModel = currentSettings.sttModel.isEmpty()
        ? String(kDefaultSttModel) : currentSettings.sttModel;
    const bool obsoleteTavilyDefault = currentSettings.webSearchApiKey.isEmpty() &&
        currentSettings.webSearchBaseUrl == "https://api.tavily.com";
    const String webSearchBaseUrl = currentSettings.webSearchBaseUrl.isEmpty() || obsoleteTavilyDefault
        ? String(kDefaultWebSearchBaseUrl) : currentSettings.webSearchBaseUrl;
    const String ttsBaseUrl = currentSettings.ttsBaseUrl.isEmpty()
        ? String(kDefaultTtsBaseUrl) : currentSettings.ttsBaseUrl;
    const String ttsModel = currentSettings.ttsModel.isEmpty()
        ? String(kDefaultTtsModel) : currentSettings.ttsModel;
    const String ttsVoice = currentSettings.ttsVoice.isEmpty()
        ? String(kDefaultTtsVoice) : currentSettings.ttsVoice;
    String page =
        "<!doctype html><html><head><meta charset='utf-8'>"
        "<meta name='viewport' content='width=device-width,initial-scale=1'>"
        "<title>Cardputer Assistant Setup</title><style>";
    page += kSetupPageStyle;
    page +=
        "</style></head><body><header class='instrument'><div class='instrument-inner'>"
        "<p class='eyebrow'>CardMind / setup</p><h1>Cardputer Assistant</h1>"
        "<p class='instrument-note'>Open 192.168.4.1 in a browser on the connected device.</p>"
        "</div></header><main class='shell'>";
    if (!error.isEmpty()) {
        page += "<div class='notice error' role='alert'>" + htmlEscape(error) + "</div>";
    }
    if (!nearbyNetworkScan.success) {
        page += "<div class='notice error' role='alert'>" +
                htmlEscape(nearbyNetworkScan.error) + "</div>";
    }
    const bool manualSsid = currentSettings.wifiSsid.isEmpty() ||
        !containsNetwork(nearbyNetworkScan.networks, currentSettings.wifiSsid);
    page += "<form class='setup-card' method='post' action='/save'>"
            "<section class='section' aria-labelledby='network-model-heading'>"
            "<p class='section-kicker'>Core</p>"
            "<h2 id='network-model-heading'>Network &amp; model</h2>"
            "<label for='ssid'>Wi-Fi network (2.4 GHz)</label><select id='ssid' name='ssid'>" +
            networkOptions(nearbyNetworkScan.networks, currentSettings.wifiSsid) +
            "</select><div id='ssid-manual-field'><label for='ssid_manual'>Hidden network name (SSID)</label>"
            "<input id='ssid_manual' name='ssid_manual' maxlength='32' placeholder='Hidden SSID' value='" +
            (manualSsid ? htmlEscape(currentSettings.wifiSsid) : String("")) +
            "'></div><label for='wifi_password'>Wi-Fi password</label>"
            "<input id='wifi_password' name='wifi_password' type='password' maxlength='63' autocomplete='new-password'>"
            "<p class='note'>Leave blank to keep the saved password. Open networks may use an empty password.</p>"
            "<label for='api_key'>API key</label>"
            "<input id='api_key' name='api_key' type='password' minlength='8' autocomplete='new-password' data-1p-ignore data-lpignore='true' placeholder='Never displayed or logged'>"
            "<p class='note'>Leave blank to keep the saved key. The key is stored only in device NVS.</p>"
            "<label for='api_base_url'>API base URL</label>"
            "<input id='api_base_url' name='api_base_url' type='url' required maxlength='180' placeholder='https://api.example.com' value='" +
            htmlEscape(apiBaseUrl) + "'>"
            "<label for='model'>Model id</label><input id='model' name='model' required maxlength='80' value='" +
            htmlEscape(model) + "'></section>"
            "<section class='section' aria-labelledby='voice-input-heading'>"
            "<p class='section-kicker'>Audio</p>"
            "<h2 id='voice-input-heading'>Voice input (optional)</h2>"
            "<p class='note'>Use a separate Groq API key. It is stored only in device NVS and is never displayed or logged.</p>"
            "<label for='stt_api_key'>STT API key</label>"
            "<input id='stt_api_key' name='stt_api_key' type='password' minlength='8' autocomplete='new-password' data-1p-ignore data-lpignore='true' placeholder='Leave blank to keep saved STT key'>"
            "<label for='stt_base_url'>STT base URL</label>"
            "<input id='stt_base_url' name='stt_base_url' type='url' maxlength='180' value='" +
            htmlEscape(sttBaseUrl) + "'>"
            "<label for='stt_model'>STT model</label>"
            "<input id='stt_model' name='stt_model' maxlength='80' value='" +
            htmlEscape(sttModel) + "'></section>"
            "<section class='section' aria-labelledby='web-search-heading'>"
            "<p class='section-kicker'>Tools</p>"
            "<h2 id='web-search-heading'>Web search (optional)</h2>"
            "<p class='note'>Exa is the default provider and offers a starter tier without a payment method. Its key is stored only in device NVS and is never displayed or logged.</p>"
            "<label for='search_api_key'>Web search API key</label>"
            "<input id='search_api_key' name='search_api_key' type='password' minlength='8' autocomplete='new-password' data-1p-ignore data-lpignore='true' placeholder='Leave blank to keep saved search key'>"
            "<label for='search_base_url'>Web search base URL</label>"
            "<input id='search_base_url' name='search_base_url' type='url' maxlength='180' value='" +
            htmlEscape(webSearchBaseUrl) + "'></section>"
            "<section class='section' aria-labelledby='speech-output-heading'>"
            "<p class='section-kicker'>Audio</p>"
            "<h2 id='speech-output-heading'>Speech output (optional)</h2>"
            "<p class='note'>ElevenLabs multilingual TTS. The separate key is stored only in device NVS.</p>"
            "<label for='tts_api_key'>TTS API key</label>"
            "<input id='tts_api_key' name='tts_api_key' type='password' minlength='8' autocomplete='new-password' data-1p-ignore data-lpignore='true' placeholder='Leave blank to keep saved TTS key'>"
            "<label for='tts_base_url'>TTS base URL</label>"
            "<input id='tts_base_url' name='tts_base_url' type='url' maxlength='180' value='" +
            htmlEscape(ttsBaseUrl) + "'>"
            "<label for='tts_model'>TTS model</label>"
            "<input id='tts_model' name='tts_model' maxlength='80' value='" + htmlEscape(ttsModel) + "'>"
            "<label for='tts_voice'>TTS voice id</label>"
            "<input id='tts_voice' name='tts_voice' maxlength='80' value='" + htmlEscape(ttsVoice) + "'>"
            "<label class='check-row'><input name='tts_auto' type='checkbox' style='width:auto' " +
            (currentSettings.ttsAutoPlay ? String("checked") : String("")) +
            "><span>Automatically speak new assistant replies</span></label></section>"
            "<div class='actions'><button type='submit'>Save and restart</button></div></form>"
            "<script>const s=document.getElementById('ssid'),m=document.getElementById('ssid_manual'),"
            "g=document.getElementById('ssid-manual-field');"
            "function u(){g.hidden=!!s.value;m.required=!s.value}"
            "s.addEventListener('change',u);u()</script></main></body></html>";
    return page;
}

void sendSetupPage()
{
    webServer.send(200, "text/html; charset=utf-8", setupPage(""));
}

void saveSubmittedSettings()
{
    Settings submitted = currentSettings;
    submitted.wifiSsid = webServer.arg("ssid");
    if (submitted.wifiSsid.isEmpty()) {
        submitted.wifiSsid = webServer.arg("ssid_manual");
    }
    submitted.apiBaseUrl = webServer.arg("api_base_url");
    submitted.apiBaseUrl.trim();
    while (submitted.apiBaseUrl.endsWith("/")) {
        submitted.apiBaseUrl.remove(submitted.apiBaseUrl.length() - 1);
    }
    submitted.model = webServer.arg("model");
    submitted.sttBaseUrl = webServer.arg("stt_base_url");
    submitted.sttBaseUrl.trim();
    while (submitted.sttBaseUrl.endsWith("/")) {
        submitted.sttBaseUrl.remove(submitted.sttBaseUrl.length() - 1);
    }
    submitted.sttModel = webServer.arg("stt_model");
    submitted.webSearchBaseUrl = webServer.arg("search_base_url");
    submitted.webSearchBaseUrl.trim();
    while (submitted.webSearchBaseUrl.endsWith("/")) {
        submitted.webSearchBaseUrl.remove(submitted.webSearchBaseUrl.length() - 1);
    }
    submitted.ttsBaseUrl = webServer.arg("tts_base_url");
    submitted.ttsBaseUrl.trim();
    while (submitted.ttsBaseUrl.endsWith("/")) {
        submitted.ttsBaseUrl.remove(submitted.ttsBaseUrl.length() - 1);
    }
    submitted.ttsModel = webServer.arg("tts_model");
    submitted.ttsVoice = webServer.arg("tts_voice");
    submitted.ttsAutoPlay = webServer.hasArg("tts_auto");
    const String wifiPassword = webServer.arg("wifi_password");
    String apiKey = webServer.arg("api_key");
    String sttApiKey = webServer.arg("stt_api_key");
    String webSearchApiKey = webServer.arg("search_api_key");
    String ttsApiKey = webServer.arg("tts_api_key");
    sttApiKey.trim();
    webSearchApiKey.trim();
    ttsApiKey.trim();
    if (!wifiPassword.isEmpty() || currentSettings.wifiSsid.isEmpty()) {
        submitted.wifiPassword = wifiPassword;
    }
    if (!apiKey.isEmpty()) {
        submitted.apiKey = apiKey;
    }
    if (!sttApiKey.isEmpty()) {
        submitted.sttApiKey = sttApiKey;
    }
    if (!webSearchApiKey.isEmpty()) {
        submitted.webSearchApiKey = webSearchApiKey;
    }
    if (!ttsApiKey.isEmpty()) {
        submitted.ttsApiKey = ttsApiKey;
    }
    if (currentProviderStore == nullptr) {
        webServer.send(500, "text/html; charset=utf-8",
                       setupPage("Provider profile storage is unavailable"));
        return;
    }
    const ProviderStoreResult result =
        saveProvisionedSettings(submitted, *currentProviderStore);
    saveBlocksExit = saveBlocksExit || result.committed || result.outcomeUnknown;
    const bool savedWithCleanupWarning =
        !providerStoreResultSucceeded(result) && result.committed &&
        result.error == ProviderStoreError::CleanupFailed;
    if (!providerStoreResultSucceeded(result) && !savedWithCleanupWarning) {
        webServer.send(
            400, "text/html; charset=utf-8",
            setupPage(String(result.message.c_str())));
        return;
    }
    currentSettings = submitted;
    String response =
        "<!doctype html><html><head><meta charset='utf-8'>"
        "<meta name='viewport' content='width=device-width,initial-scale=1'>"
        "<title>Cardputer Assistant Setup</title><style>";
    response += kSetupPageStyle;
    response +=
        "</style></head><body><header class='instrument'><div class='instrument-inner'>"
        "<p class='eyebrow'>CardMind / setup</p>"
        "<p class='instrument-title'>Cardputer Assistant</p>"
        "</div></header><main class='shell'><article class='result-card'>";
    response += savedWithCleanupWarning
        ? "<div class='notice warning' role='status'><h1>Saved with a cleanup warning</h1>"
          "<p>The provider settings are authoritative. "
        : "<div class='notice success' role='status'><h1>Saved and verified</h1></div>";
    if (savedWithCleanupWarning) {
        response += htmlEscape(String(result.message.c_str())) + "</p></div>";
    }
    response += "<p class='result-copy'>The Cardputer will restart in five seconds. "
                "You may close this page after it disconnects.</p></article></main></body></html>";
    webServer.send(200, "text/html; charset=utf-8", response);
    Serial.printf("PROVISIONING settings_saved=yes nvs_verified=yes restart_delay_ms=%u\n",
                  static_cast<unsigned int>(kRestartDelayMs));
    restartPending = true;
    restartAt = millis() + kRestartDelayMs;
}

String macSuffix()
{
    const std::uint64_t mac = ESP.getEfuseMac();
    char suffix[5];
    snprintf(suffix, sizeof(suffix), "%04X", static_cast<unsigned int>(mac & 0xFFFF));
    return String(suffix);
}

String randomPassword()
{
    char password[13];
    snprintf(password, sizeof(password), "CP-%08lX", static_cast<unsigned long>(esp_random()));
    return String(password);
}

bool provisioningEscapePressed()
{
    const Keyboard_Class::KeysState& keys = M5Cardputer.Keyboard.keysState();
    return keys.esc ||
        std::find(keys.word.begin(), keys.word.end(), '`') != keys.word.end();
}

void updateProvisioningSerial()
{
    while (Serial.available() > 0) {
        const char character = static_cast<char>(Serial.read());
        if (character == '\n') {
            serialCommand.trim();
            if (serialCommand == "PING") {
                Serial.println("PONG");
            } else if (serialCommand == "EXIT") {
                if (!settingsAreComplete(currentSettings)) {
                    Serial.println("PROVISIONING exit=blocked reason=configuration_required");
                } else if (restartPending || saveBlocksExit) {
                    Serial.println("PROVISIONING exit=blocked reason=restart_required");
                } else {
                    exitRequested = true;
                    Serial.println("PROVISIONING exit=requested");
                }
            } else if (serialCommand == "STATUS") {
                Serial.printf("STATUS board_adv=%s configured=%s search_configured=%s tts_configured=%s wifi=ap portal=ready heap=%u\n",
                              M5.getBoard() == m5::board_t::board_M5CardputerADV ? "yes" : "no",
                              settingsAreComplete(currentSettings) ? "yes" : "no",
                              webSearchSettingsAreComplete(currentSettings) ? "yes" : "no",
                              ttsSettingsAreComplete(currentSettings) ? "yes" : "no",
                              static_cast<unsigned int>(ESP.getFreeHeap()));
            } else if (serialCommand == "APITEST") {
                Serial.println("APITEST result=blocked reason=setup_portal_active");
            } else if (serialCommand == "PYTHONCHECK" ||
                       serialCommand == "PYTHONBOOTTEST") {
                const PythonModeStatus status = inspectPythonMode();
                Serial.printf("PYTHONCHECK result=%s layout=%s image=%s cardmind_bytes=%u python_bytes=%u runtime_error=%s error=%s\n",
                              status.partitionLayoutReady && status.pythonImageReady
                                  ? "pass" : "failed",
                              status.partitionLayoutReady ? "yes" : "no",
                              status.pythonImageReady ? "yes" : "no",
                              static_cast<unsigned int>(status.cardMindPartitionBytes),
                              static_cast<unsigned int>(status.pythonPartitionBytes),
                              status.lastRuntimeError.isEmpty()
                                  ? "none" : status.lastRuntimeError.c_str(),
                              status.error.isEmpty() ? "none" : status.error.c_str());
                if (serialCommand == "PYTHONBOOTTEST" &&
                    status.partitionLayoutReady && status.pythonImageReady) {
                    const OperationResult activated = activatePythonMode();
                    Serial.printf("PYTHONBOOTTEST result=%s error=%s\n",
                                  activated.success ? "restarting" : "failed",
                                  activated.success ? "none" : activated.error.c_str());
                    Serial.flush();
                    if (activated.success) {
                        delay(200);
                        ESP.restart();
                    }
                }
            } else if (!serialCommand.isEmpty()) {
                Serial.println("ERROR event=serial_command reason=unsupported_command");
            }
            Serial.flush();
            serialCommand = "";
        } else if (character != '\r' && serialCommand.length() < 32) {
            serialCommand += character;
        }
    }
}

}  // namespace

OperationResult runProvisioningPortal(const Settings& existingSettings,
                                     ProviderProfileStore& providerStore)
{
    const bool exitAllowed = settingsAreComplete(existingSettings);
    const bool stationWasEnabled = (WiFi.getMode() & WIFI_MODE_STA) != 0;
    restartPending = false;
    exitRequested = false;
    saveBlocksExit = false;
    serialCommand = "";
    currentSettings = existingSettings;
    currentProviderStore = &providerStore;
    const String accessPointName = "Cardputer-" + macSuffix();
    String accessPointPassword;
    const OperationResult passwordLoadResult = loadSetupAccessPointPassword(accessPointPassword);
    if (!passwordLoadResult.success) {
        showFatalError(passwordLoadResult.error);
        Serial.println("FATAL event=setup_password_load result=failed");
        while (true) {
            delay(1000);
        }
    }
    if (accessPointPassword.isEmpty()) {
        accessPointPassword = randomPassword();
        const OperationResult passwordSaveResult = saveSetupAccessPointPassword(accessPointPassword);
        if (!passwordSaveResult.success) {
            showFatalError(passwordSaveResult.error);
            Serial.println("FATAL event=setup_password_save result=failed");
            while (true) {
                delay(1000);
            }
        }
    }
    WiFi.disconnect(true, false);
    WiFi.mode(WIFI_AP_STA);
    if (!WiFi.softAP(accessPointName.c_str(), accessPointPassword.c_str())) {
        showFatalError("Failed to start protected setup access point");
        while (true) {
            delay(1000);
        }
    }
    nearbyNetworkScan = scanWifiNetworks();
    if (nearbyNetworkScan.success) {
        Serial.printf("INFO event=wifi_scan result=ok count=%u\n",
                      static_cast<unsigned int>(nearbyNetworkScan.networks.size()));
    } else {
        Serial.println("WARN event=wifi_scan result=failed");
    }
    if (!routesConfigured) {
        webServer.on("/", HTTP_GET, sendSetupPage);
        webServer.on("/save", HTTP_POST, saveSubmittedSettings);
        webServer.onNotFound(sendSetupPage);
        routesConfigured = true;
    }
    webServer.begin();
    Serial.println("PROVISIONING result=started security=wpa2 ip=192.168.4.1");
    showProvisioning(accessPointName, accessPointPassword,
                     exitAllowed ? "ESC back" : "Save in browser");
    bool exitHintVisible = exitAllowed;
    M5Cardputer.update();
    bool escapeHeld = provisioningEscapePressed();
    while (true) {
        webServer.handleClient();
        updateProvisioningSerial();
        M5Cardputer.update();
        const bool escapePressed = provisioningEscapePressed();
        if (exitAllowed && !restartPending && !saveBlocksExit &&
            escapePressed && !escapeHeld) {
            exitRequested = true;
        }
        escapeHeld = escapePressed;
        if (exitHintVisible && (saveBlocksExit || restartPending)) {
            showProvisioning(accessPointName, accessPointPassword,
                             restartPending ? "Restarting..." : "Restart required");
            exitHintVisible = false;
        }
        if (restartPending && static_cast<std::int32_t>(millis() - restartAt) >= 0) {
            ESP.restart();
        }
        if (exitRequested && exitAllowed && !restartPending && !saveBlocksExit) {
            break;
        }
        delay(2);
    }
    webServer.stop();
    const bool accessPointStopped = WiFi.softAPdisconnect(true);
    const bool stationRestored = stationWasEnabled
        ? WiFi.reconnect() : WiFi.mode(WIFI_OFF);
    currentSettings = Settings{};
    nearbyNetworkScan = {true, {}, ""};
    currentProviderStore = nullptr;
    serialCommand = "";
    while (!M5Cardputer.Keyboard.keyList().empty()) {
        M5Cardputer.update();
        delay(5);
    }
    String error;
    if (!accessPointStopped) {
        error = "Failed to stop Local setup access point";
    }
    if (!stationRestored) {
        if (!error.isEmpty()) {
            error += "; ";
        }
        error += "Failed to restore Wi-Fi after Local setup";
    }
    Serial.printf("PROVISIONING result=%s error=%s\n",
                  error.isEmpty() ? "stopped" : "failed",
                  error.isEmpty() ? "none" : error.c_str());
    return {error.isEmpty(), error};
}

}  // namespace cardputer
