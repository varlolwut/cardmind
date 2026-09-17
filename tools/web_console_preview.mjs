import { createServer } from "node:http";
import { readFileSync } from "node:fs";

const pagePath = new URL(
    "../firmware/CardputerAssistant/assets/web_console.html",
    import.meta.url,
);
const source = readFileSync(pagePath, "utf8");

const previewState = {
    ip: "192.168.1.129",
    battery: 87,
    wifi_rssi: -53,
    free_heap: 124608,
    minimum_heap: 98240,
    largest_heap: 63488,
    stack_free: 4288,
    cpu_mhz: 240,
    uptime_ms: 4368000,
    reset_reason: 1,
    sd_used_bytes: 3145728,
    sd_total_bytes: 31914983424,
    active_project_id: "1111111111111111",
    project_id: "1111111111111111",
    project_title: "CardMind development",
    project_archived: false,
    project_instructions: "Keep project decisions consistent across chats.",
    project_model: "",
    context_byte_budget: 32768,
    maximum_output_tokens: 1024,
    automatic_compaction: true,
    active_chat_id: "aaaaaaaaaaaaaaaa",
    active_chat_title: "CardMind UX review",
    total_messages: 18,
    active_context_messages: 18,
    active_context_bytes: 12480,
    maximum_context_messages: 64,
    maximum_context_bytes: 32768,
    archived_messages: 6,
    instructions: "Answer clearly and keep code examples compact.",
    history_before_messages: 6,
    ssh_tools_enabled: false,
    status: "",
    firmware_version: "1.12.0-preview",
    wifi_ssid: "Studio 2.4 GHz",
    wifi_connected_ssid: "Studio 2.4 GHz",
    web_session_lifetime: "1h",
    global_instructions: "Keep device guidance concise and explicit.",
    project_chat_history_quota_bytes: 268435456,
    master_tool_policy: "v1;ws=a;wf=a;fr=a;fw=q;sr=q;sm=q;sf=q;py=o",
    new_chat_tool_policy: "v1;ws=i;wf=i;fr=i;fw=i;sr=i;sm=i;sf=i;py=i",
    project_tool_policy: "v1;ws=i;wf=i;fr=i;fw=i;sr=i;sm=i;sf=i;py=i",
    chat_tool_policy: "v1;ws=i;wf=i;fr=i;fw=i;sr=i;sm=i;sf=i;py=i",
    provider_state: "ready",
    provider_message: "",
    api_profile_limit: 3,
    model_preset_limit: 6,
    default_api_profile_id: "3333333333333333",
    api_profiles: [
        {id: "3333333333333333", name: "Primary provider", api_base_url: "https://api.example.com", authority_revision: 1, is_default: true, api_key_configured: true},
    ],
    model_presets: [
        {id: "5555555555555555", name: "Field notes", model: "claude-sonnet-4-6", maximum_output_tokens: 1024},
    ],
    project_api_profile_id: "",
    effective_api_profile_id: "3333333333333333",
    api_profile_error: "",
    api_profile_available: true,
    project_ssh_profile: "",
    project_ssh_profile_matches: true,
    chat_ssh_profile: "",
    chat_ssh_profile_matches: true,
    model: "claude-sonnet-4-6",
    api_base_url: "https://api.example.com",
    api_key_configured: true,
    stt_base_url: "https://speech.example.com",
    stt_model: "whisper-1",
    stt_key_configured: true,
    search_base_url: "https://search.example.com",
    search_key_configured: true,
    tts_base_url: "https://speech.example.com",
    tts_model: "tts-1",
    tts_voice: "alloy",
    tts_key_configured: true,
    tts_auto_play: false,
    tts_volume: 190,
    display_brightness: 180,
    screen_sleep_minutes: 5,
    keyboard_repeat_ms: 125,
    power_profile: 1,
    projects_revision: 1,
    chats_revision: 1,
    chat_revision: 1,
    files_revision: 1,
    settings_revision: 1,
    projects: [
        {id: "1111111111111111", title: "CardMind development", archived: false, chat_count: 3},
        {id: "2222222222222222", title: "Language practice", archived: false, chat_count: 2},
    ],
    next_offset: 0,
    eof: true,
    python_layout_ready: true,
    python_image_ready: true,
    python_error: "",
    python_runtime_error: "",
    chats: [
        {id: "aaaaaaaaaaaaaaaa", title: "CardMind UX review", pinned: true, archived: false, total_messages: 18},
        {id: "bbbbbbbbbbbbbbbb", title: "Travel notes", pinned: false, archived: false, total_messages: 9},
        {id: "cccccccccccccccc", title: "SSH troubleshooting", pinned: false, archived: false, total_messages: 14},
    ],
    messages: [
        {role: "user", content: "Can you summarize the last device regression?"},
        {role: "assistant", content: "All storage, network, streaming, voice, search, and SSH checks passed. Peak free heap remained stable after the Web console cycle."},
        {role: "user", content: "Show me the remaining UX work."},
        {role: "assistant", content: "The next pass focuses on navigation clarity, mobile ergonomics, and reducing heap allocations while the browser console is open."},
    ],
    capabilities: [
        {id: "ws", raw_project: "inherit", raw_chat: "inherit", effective: "ask", source: "global"},
        {id: "wf", raw_project: "inherit", raw_chat: "inherit", effective: "ask", source: "global"},
        {id: "fr", raw_project: "inherit", raw_chat: "inherit", effective: "allow", source: "global"},
        {id: "fw", raw_project: "inherit", raw_chat: "inherit", effective: "ask", source: "global"},
        {id: "sr", raw_project: "inherit", raw_chat: "inherit", effective: "ask", source: "global"},
        {id: "sm", raw_project: "inherit", raw_chat: "inherit", effective: "ask", source: "global"},
        {id: "sf", raw_project: "inherit", raw_chat: "inherit", effective: "ask", source: "global"},
        {id: "py", raw_project: "inherit", raw_chat: "inherit", effective: "deny", source: "global"},
    ],
    ssh_profiles: [
        {id: "4444444444444444", name: "Home server", username: "cardmind", host: "192.168.1.40", port: 22, auth_mode: "key"},
    ],
    ssh_selected: 0,
    ssh_name: "Home server",
    ssh_host: "192.168.1.40",
    ssh_port: 22,
    ssh_username: "cardmind",
    ssh_auth_mode: "key",
    ssh_terminal_open: false,
    ssh_stage: "idle",
    ssh_error: "",
    ssh_key_installed: true,
    ssh_configured: true,
    files: [
        {name: "notes.md", size: 18422, editable: true},
        {name: "report.txt", size: 92480, editable: true},
        {name: "capture.bin", size: 1482, editable: false},
    ],
    diagnostic_metrics_enabled: false,
    activities: [],
};

const apiStates = {
    "/api/status": previewState,
    "/api/projects": previewState,
    "/api/chats": previewState,
    "/api/chat": previewState,
    "/api/files": previewState,
    "/api/ssh/state": previewState,
    "/api/settings": previewState,
    "/api/activity": {activities: []},
    "/api/pending": {present: false},
    "/api/session": {
        ok: true,
        csrf: "preview",
        authenticated: true,
        session_lifetime: "1h",
        browser_presence: "connected",
    },
    "/api/search/sources": {
        ok: true,
        source_kind: "latest_device_cache",
        query: "Cardputer interface design",
        sources: [
            {title: "M5Stack Cardputer documentation", url: "https://docs.m5stack.com/", snippet: "Official hardware reference retained by the latest device search."},
            {title: "Local field note", url: "device-cache:field-note", snippet: "Non-HTTP references remain plain text."},
        ],
    },
    "/api/models": {
        ok: true,
        profile_id: "3333333333333333",
        authority_revision: 1,
        models: ["claude-sonnet-4-6", "gpt-5-mini"],
    },
    "/api/project/links": {links: ["notes.md"], next_offset: 0, eof: true},
    "/api/file": {
        name: "notes.md",
        content: "# CardMind notes\n\nThis preview uses the same windowed editor as the device.",
        offset: 0,
        next_offset: 73,
        total_bytes: 73,
        eof: true,
    },
};

const stateScript = `const previewState=${JSON.stringify(previewState)};\n`;
const page = source
    .replace("let csrf=''", "let csrf='preview'")
    .replace("initializeWebConsole().catch(showError);", "")
    .replace(
        "</script>",
        `${stateScript}setReconnectIdentity(previewState.active_project_id,previewState.active_chat_id);showPanel(location.hash.slice(1)||'chat').catch(showError);</script>`,
    );
const server = createServer((request, response) => {
    const url = new URL(request.url, "http://127.0.0.1:8765");
    if (url.pathname.startsWith("/api/") && request.method === "GET") {
        const payload = apiStates[url.pathname];
        if (payload === undefined) {
            response.writeHead(404, {"Content-Type": "application/json"});
            response.end(JSON.stringify({error: `Preview route ${url.pathname} is not implemented`}));
            return;
        }
        response.writeHead(200, {"Content-Type": "application/json; charset=utf-8"});
        response.end(JSON.stringify(payload));
        return;
    }
    if (url.pathname.startsWith("/api/") && request.method === "POST") {
        request.resume();
        request.on("end", () => {
            response.writeHead(200, {"Content-Type": "application/json; charset=utf-8"});
            const payload = url.pathname === "/api/wifi/scan"
                ? {ok: true, networks: [
                    {ssid: "Studio 2.4 GHz", rssi: -53, secured: true},
                    {ssid: "Workshop", rssi: -67, secured: true},
                    {ssid: "Guest", rssi: -72, secured: false},
                ]}
                : {ok: true};
            response.end(JSON.stringify(payload));
        });
        return;
    }
    if (url.pathname !== "/" && url.pathname !== "/index.html") {
        response.writeHead(404, {"Content-Type": "text/plain; charset=utf-8"});
        response.end("Not found");
        return;
    }
    response.writeHead(200, {
        "Cache-Control": "no-store",
        "Content-Type": "text/html; charset=utf-8",
    });
    response.end(page);
});

server.listen(8765, "127.0.0.1", () => {
    console.log("WEB_CONSOLE_PREVIEW address=http://127.0.0.1:8765/");
});
