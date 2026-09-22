#include "ui.h"

#include "text_utils.h"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

namespace cardputer {
namespace {

constexpr std::size_t kTranscriptCells = 38;
constexpr std::size_t kIdleTranscriptLines = 7;
constexpr std::size_t kCompactTranscriptLines = 6;
constexpr std::size_t kDetailedTranscriptLines = 5;
constexpr std::uint16_t kCanvas = 0x2104;
constexpr std::uint16_t kBand = 0x2985;
constexpr std::uint16_t kRaised = 0x3185;
constexpr std::uint16_t kText = 0xF77C;
constexpr std::uint16_t kMuted = 0xCE16;
constexpr std::uint16_t kSignal = 0xC3E4;
constexpr std::uint16_t kOxideAccent = 0xAAE2;
constexpr std::uint16_t kCoolSecondary = 0x32EA;
constexpr std::uint16_t kSuccess = 0x7DAF;
constexpr std::uint16_t kWarning = 0xFE8F;
constexpr std::uint16_t kDanger = 0xFBAD;
constexpr int kCarouselCardX = 6;
constexpr int kCarouselCardY = 22;
constexpr int kCarouselCardWidth = 228;
constexpr int kCarouselCardHeight = 75;
constexpr int kCarouselTravel = 240;
constexpr int kCarouselAnimationFrames = 6;
constexpr int kCarouselWidth = 240;
constexpr int kCarouselHeight = 135;
constexpr std::size_t kCarouselBufferBytes = 64800;
std::unique_ptr<LGFX_Sprite> canvas;

const std::uint8_t kWifiIcon[] PROGMEM = {
    0x00, 0x3C, 0x42, 0x99, 0x24, 0x18, 0x00, 0x18,
};
const std::uint8_t kTrashIcon[] PROGMEM = {
    0x18, 0x7E, 0x42, 0x5A, 0x5A, 0x42, 0x3C, 0x00,
};
const std::uint8_t kChatsIcon[] PROGMEM = {
    0x00, 0x78, 0x84, 0xFE, 0x82, 0x82, 0x7C, 0x00,
};
const std::uint8_t kModelIcon[] PROGMEM = {
    0x3C, 0x42, 0x99, 0xA5, 0xA5, 0x99, 0x42, 0x3C,
};
const std::uint8_t kLanguageIcon[] PROGMEM = {
    0x3C, 0x5A, 0xA5, 0xFF, 0xA5, 0x5A, 0x3C, 0x00,
};
const std::uint8_t kSettingsIcon[] PROGMEM = {
    0x18, 0x5A, 0x3C, 0xE7, 0xE7, 0x3C, 0x5A, 0x18,
};
const std::uint8_t kMicIcon[] PROGMEM = {
    0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x5A, 0x3C, 0x18,
};
const std::uint8_t kUpIcon[] PROGMEM = {
    0x18, 0x3C, 0x7E, 0xDB, 0x18, 0x18, 0x18, 0x00,
};
const std::uint8_t kDownIcon[] PROGMEM = {
    0x18, 0x18, 0x18, 0xDB, 0x7E, 0x3C, 0x18, 0x00,
};

struct TranscriptLine {
    std::string text;
    std::uint16_t color;
};

struct TranscriptLineCounts {
    std::size_t totalLines;
    std::size_t lastMessageLines;
};

TranscriptLineCounts transcriptLineCounts(const std::vector<Message>& history,
                                          const std::string& activeResponse)
{
    TranscriptLineCounts counts{0, 0};
    for (const auto& message : history) {
        counts.lastMessageLines = countWrappedUtf8Lines(
            message.role == "user" ? "You: " : "AI: ",
            message.content,
            kTranscriptCells);
        counts.totalLines += counts.lastMessageLines;
    }
    if (!activeResponse.empty()) {
        counts.lastMessageLines = countWrappedUtf8Lines(
            "AI: ", activeResponse, kTranscriptCells);
        counts.totalLines += counts.lastMessageLines;
    }
    return counts;
}

std::vector<TranscriptLine> transcriptLineWindow(
    const std::vector<Message>& history,
    const std::string& activeResponse,
    std::size_t scrollOffset,
    std::size_t maximumLines,
    std::size_t lastMessageLines)
{
    std::vector<TranscriptLine> lines;
    lines.reserve(maximumLines);
    std::size_t remainingSkip = scrollOffset;
    const auto appendReversedWindow = [&](const std::string& body,
                                          const char* prefix,
                                          std::uint16_t color,
                                          std::size_t lineCount) {
        if (remainingSkip >= lineCount) {
            remainingSkip -= lineCount;
            return;
        }
        const std::size_t endLine = lineCount - remainingSkip;
        remainingSkip = 0;
        const std::size_t selectedLines =
            std::min(endLine, maximumLines - lines.size());
        const std::size_t firstLine = endLine - selectedLines;
        WrappedTextWindow window = wrapUtf8TextWindow(
            prefix, body, kTranscriptCells, firstLine, selectedLines);
        for (auto line = window.lines.rbegin();
             line != window.lines.rend();
             ++line) {
            lines.push_back({std::move(*line), color});
        }
    };
    if (!activeResponse.empty() && lines.size() < maximumLines) {
        appendReversedWindow(
            activeResponse, "AI: ", kSuccess, lastMessageLines);
    }
    bool useLastMessageLines = activeResponse.empty();
    for (auto message = history.rbegin(); message != history.rend(); ++message) {
        if (lines.size() >= maximumLines) {
            break;
        }
        const std::size_t lineCount = useLastMessageLines
            ? lastMessageLines
            : countWrappedUtf8Lines(
                  message->role == "user" ? "You: " : "AI: ",
                  message->content,
                  kTranscriptCells);
        useLastMessageLines = false;
        appendReversedWindow(
            message->content,
            message->role == "user" ? "You: " : "AI: ",
            message->role == "user" ? kSignal : kMuted,
            lineCount);
    }
    std::reverse(lines.begin(), lines.end());
    return lines;
}

String clippedLine(const String& value, std::size_t maximumLength)
{
    return String(ellipsizeUtf8(value.c_str(), maximumLength).c_str());
}

bool isErrorStatus(const String& status)
{
    return status.indexOf("Failed") >= 0 || status.indexOf("failed") >= 0 ||
           status.indexOf("HTTP") >= 0 || status.indexOf("timed out") >= 0 ||
           status.indexOf("not in") >= 0 || status.indexOf("invalid") >= 0 ||
           status.indexOf("Error") >= 0 || status.indexOf("error") >= 0;
}

std::uint16_t chatCapabilityColor(ChatCapabilityState state)
{
    switch (state) {
        case ChatCapabilityState::Off:
            return kMuted;
        case ChatCapabilityState::Inherit:
            return kCoolSecondary;
        case ChatCapabilityState::Ask:
            return kWarning;
        case ChatCapabilityState::Allow:
            return kSuccess;
        case ChatCapabilityState::Required:
            return kOxideAccent;
    }
    return kDanger;
}

std::size_t visibleTranscriptLineCount(const String& status)
{
    if (status.isEmpty() || status == "Ready") {
        return kIdleTranscriptLines;
    }
    const String visibleStatus = status.isEmpty() ? String("Ready") : status;
    const auto statusLines = wrapUtf8Text(visibleStatus.c_str(), kTranscriptCells);
    return isErrorStatus(status) && statusLines.size() > 1
        ? kDetailedTranscriptLines
        : kCompactTranscriptLines;
}

std::string prepareChatInputLine(const std::string& input)
{
    const auto inputLines = wrapUtf8Text("> " + input + "_", kTranscriptCells);
    return inputLines.back();
}

template <typename Display>
void drawChatInputLine(Display& display, const std::string& preparedInputLine)
{
    display.fillRect(0, 104, 240, 17, kCanvas);
    display.drawFastHLine(0, 104, 240, kBand);
    display.setFont(&fonts::efontCN_12);
    display.setTextColor(kSignal, kCanvas);
    display.setCursor(3, 106);
    display.print(preparedInputLine.c_str());
}

void drawToolbarItem(int x, const std::uint8_t* icon, const char* label)
{
    canvas->drawBitmap(x + 2, 125, icon, 8, 8, kText);
    canvas->setCursor(x + 11, 124);
    canvas->print(label);
}

void drawBatteryStatus(int x, int y, int batteryLevel, bool batteryCharging)
{
    const std::uint16_t color = batteryLevel >= 0 && batteryLevel <= 15
        ? kDanger
        : (batteryCharging ? kSuccess : kText);
    canvas->drawRoundRect(x, y, 17, 9, 2, color);
    canvas->fillRect(x + 17, y + 3, 2, 3, color);
    if (batteryLevel >= 0) {
        const int fillWidth = std::max(1, std::min(13, batteryLevel * 13 / 100));
        canvas->fillRect(x + 2, y + 2, fillWidth, 5, color);
    }
    if (batteryCharging) {
        canvas->setFont(&fonts::efontCN_10);
        canvas->setTextColor(kCanvas, color);
        canvas->setCursor(x + 6, y - 1);
        canvas->print("+");
    }
}

void drawCarouselIcon(CarouselIcon icon, int x, int y, std::uint16_t color)
{
    switch (icon) {
        case CarouselIcon::Chats:
            canvas->drawRoundRect(x, y, 31, 22, 5, color);
            canvas->drawLine(x + 7, y + 22, x + 3, y + 28, color);
            canvas->drawFastHLine(x + 7, y + 7, 18, color);
            canvas->drawFastHLine(x + 7, y + 13, 14, color);
            break;
        case CarouselIcon::Ai:
            canvas->drawRoundRect(x, y + 5, 25, 19, 4, color);
            canvas->drawLine(x + 7, y + 24, x + 3, y + 29, color);
            canvas->drawFastHLine(x + 6, y + 12, 11, color);
            canvas->drawFastHLine(x + 6, y + 17, 8, color);
            canvas->drawFastVLine(x + 26, y, 9, color);
            canvas->drawFastHLine(x + 22, y + 4, 9, color);
            canvas->drawLine(x + 23, y + 1, x + 29, y + 7, color);
            canvas->drawLine(x + 29, y + 1, x + 23, y + 7, color);
            break;
        case CarouselIcon::Voice:
            canvas->drawRoundRect(x + 9, y, 13, 20, 6, color);
            canvas->drawRoundRect(x + 4, y + 8, 23, 19, 10, color);
            canvas->drawFastVLine(x + 15, y + 27, 4, color);
            canvas->drawFastHLine(x + 9, y + 30, 13, color);
            break;
        case CarouselIcon::Network:
            canvas->drawCircle(x + 15, y + 25, 2, color);
            canvas->drawArc(x + 15, y + 25, 9, 8, 215, 325, color);
            canvas->drawArc(x + 15, y + 25, 16, 15, 215, 325, color);
            break;
        case CarouselIcon::Web:
            canvas->drawRoundRect(x, y + 3, 31, 24, 3, color);
            canvas->drawFastHLine(x, y + 10, 31, color);
            canvas->fillCircle(x + 5, y + 7, 1, color);
            canvas->fillCircle(x + 9, y + 7, 1, color);
            canvas->drawFastHLine(x + 6, y + 16, 19, color);
            canvas->drawFastHLine(x + 6, y + 21, 13, color);
            break;
        case CarouselIcon::Files:
            canvas->drawRoundRect(x, y + 5, 31, 23, 3, color);
            canvas->drawRect(x + 3, y + 1, 12, 7, color);
            canvas->drawFastHLine(x + 6, y + 14, 19, color);
            canvas->drawFastHLine(x + 6, y + 20, 15, color);
            break;
        case CarouselIcon::Device:
            canvas->drawRoundRect(x + 2, y + 3, 27, 25, 4, color);
            canvas->drawCircle(x + 15, y + 15, 6, color);
            canvas->fillCircle(x + 15, y + 15, 2, color);
            break;
        case CarouselIcon::Tools:
            canvas->drawCircle(x + 15, y + 15, 10, color);
            canvas->drawFastVLine(x + 15, y, 6, color);
            canvas->drawFastVLine(x + 15, y + 25, 6, color);
            canvas->drawFastHLine(x, y + 15, 6, color);
            canvas->drawFastHLine(x + 25, y + 15, 6, color);
            canvas->fillCircle(x + 15, y + 15, 3, color);
            break;
        case CarouselIcon::Help:
            canvas->drawCircle(x + 15, y + 15, 14, color);
            canvas->setFont(&fonts::efontCN_14);
            canvas->setTextColor(color);
            canvas->setCursor(x + 11, y + 4);
            canvas->print("?");
            break;
    }
}

void drawCarouselHeader(bool wifiConnected,
                        bool sdReady,
                        int batteryLevel,
                        bool batteryCharging)
{
    canvas->fillRect(0, 0, 240, 17, kBand);
    canvas->setFont(&fonts::efontCN_12);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(5, 2);
    canvas->print("CARDMIND");
    canvas->drawBitmap(126, 4, kWifiIcon, 8, 8,
                       wifiConnected ? kSuccess : kMuted);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(sdReady ? kSuccess : kMuted, kBand);
    canvas->setCursor(143, 3);
    canvas->print("SD");
    drawBatteryStatus(171, 4, batteryLevel, batteryCharging);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(194, 3);
    canvas->print(batteryLevel >= 0 ? String(batteryLevel) + "%" : String("--%"));
}

void drawCarouselCard(const CarouselCard& card, int x)
{
    const int clipLeft = std::max(0, x);
    const int clipRight = std::min(kCarouselWidth, x + kCarouselCardWidth);
    if (clipLeft >= clipRight) {
        return;
    }
    canvas->setClipRect(clipLeft, kCarouselCardY,
                        clipRight - clipLeft, kCarouselCardHeight);
    canvas->fillRect(x, kCarouselCardY, kCarouselCardWidth,
                     kCarouselCardHeight, kRaised);
    canvas->drawRect(x, kCarouselCardY, kCarouselCardWidth,
                     kCarouselCardHeight, kSignal);
    drawCarouselIcon(card.icon, x + 14, kCarouselCardY + 21,
                     card.accentColor);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kMuted, kRaised);
    canvas->setCursor(x + 60, kCarouselCardY + 7);
    canvas->print(clippedLine(card.kicker, 26));
    canvas->setFont(&fonts::efontCN_14);
    canvas->setTextColor(kText, kRaised);
    canvas->setCursor(x + 60, kCarouselCardY + 20);
    canvas->print(card.title);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kMuted, kRaised);
    const auto lines = wrapUtf8Text(card.subtitle.c_str(), 26);
    for (std::size_t index = 0;
         index < std::min<std::size_t>(lines.size(), 2);
         ++index) {
        canvas->setCursor(x + 60,
                          kCarouselCardY + 38 + static_cast<int>(index * 11));
        canvas->print(lines[index].c_str());
    }
    canvas->clearClipRect();
}

void drawCarouselNavigation(const std::vector<CarouselCard>& cards,
                            std::size_t selectedIndex,
                            const String& status)
{
    const std::size_t leftIndex = selectedIndex == 0
        ? cards.size() - 1 : selectedIndex - 1;
    const std::size_t rightIndex = (selectedIndex + 1) % cards.size();
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(5, 101);
    canvas->print("< " + cards[leftIndex].title);
    canvas->setTextColor(kSignal, kCanvas);
    canvas->drawCenterString(String(selectedIndex + 1) + "/" +
                             String(cards.size()), 120, 101);
    canvas->setTextColor(kMuted, kCanvas);
    canvas->drawRightString(cards[rightIndex].title + " >", 235, 101);
    canvas->fillRect(0, 115, 240, 20, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(5, 119);
    canvas->print(status.isEmpty() ? "LEFT/RIGHT      ENTER open"
                                   : clippedLine(status, 43));
}

void drawCarouselFrame(const std::vector<CarouselCard>& cards,
                       std::size_t selectedIndex,
                       bool wifiConnected,
                       bool sdReady,
                       int batteryLevel,
                       bool batteryCharging,
                       const String& status)
{
    canvas->fillScreen(kCanvas);
    drawCarouselHeader(wifiConnected, sdReady, batteryLevel, batteryCharging);
    drawCarouselCard(cards[selectedIndex], kCarouselCardX);
    drawCarouselNavigation(cards, selectedIndex, status);
    canvas->pushSprite(0, 0);
}

void drawCarouselAnimationFrame(const std::vector<CarouselCard>& cards,
                                std::size_t previousIndex,
                                std::size_t selectedIndex,
                                int previousX,
                                int selectedX,
                                bool wifiConnected,
                                bool sdReady,
                                int batteryLevel,
                                bool batteryCharging,
                                const String& status)
{
    canvas->fillScreen(kCanvas);
    drawCarouselHeader(wifiConnected, sdReady, batteryLevel, batteryCharging);
    drawCarouselCard(cards[previousIndex], previousX);
    drawCarouselCard(cards[selectedIndex], selectedX);
    drawCarouselNavigation(cards, selectedIndex, status);
    canvas->pushSprite(0, 0);
}

OperationResult writeCarouselDiagnosticFrame(std::size_t index)
{
    if (canvas->width() != kCarouselWidth || canvas->height() != kCarouselHeight) {
        return {false, String("Canvas dimensions are ") + String(canvas->width()) +
                       "x" + String(canvas->height()) + ", expected 240x135"};
    }
    if (canvas->getColorDepth() != lgfx::color_depth_t::rgb565_2Byte) {
        return {false, "Canvas color depth is not RGB565"};
    }
    if (canvas->bufferLength() != kCarouselBufferBytes) {
        return {false, String("Canvas buffer is ") +
                       String(canvas->bufferLength()) +
                       " bytes, expected 64800"};
    }
    const auto* pixels = static_cast<const std::uint8_t*>(canvas->getBuffer());
    if (pixels == nullptr) {
        return {false, "Canvas buffer is unavailable"};
    }
    const String header = String("CAROUSEL_FRAME index=") + String(index) +
        " width=240 height=135 bytes=64800 format=rgb565be\n";
    const std::size_t headerBytes = Serial.write(
        reinterpret_cast<const std::uint8_t*>(header.c_str()), header.length());
    if (headerBytes != header.length()) {
        return {false, String("Frame header short write: ") +
                       String(headerBytes) + "/" + String(header.length())};
    }
    const std::size_t pixelBytes = Serial.write(pixels, kCarouselBufferBytes);
    const std::size_t delimiterBytes = Serial.write('\n');
    Serial.flush();
    if (pixelBytes != kCarouselBufferBytes) {
        return {false, String("Frame data short write: ") +
                       String(pixelBytes) + "/64800"};
    }
    if (delimiterBytes != 1) {
        return {false, "Frame delimiter short write"};
    }
    return {true, ""};
}

}  // namespace

OperationResult beginUi()
{
    canvas = std::make_unique<LGFX_Sprite>(&M5Cardputer.Display);
    if (canvas->createSprite(M5Cardputer.Display.width(), M5Cardputer.Display.height()) == nullptr) {
        return {false, "Failed to allocate 240x135 display canvas"};
    }
    canvas->setFont(&fonts::efontCN_12);
    canvas->setTextSize(1);
    canvas->setTextWrap(false);
    canvas->setBaseColor(kCanvas);
    return {true, ""};
}

void showFatalError(const String& error)
{
    M5Cardputer.Display.fillScreen(kCanvas);
    M5Cardputer.Display.setFont(&fonts::efontCN_12);
    M5Cardputer.Display.setTextColor(kDanger, kCanvas);
    M5Cardputer.Display.setCursor(4, 4);
    M5Cardputer.Display.fillTriangle(224, 3, 237, 25, 211, 25, kDanger);
    M5Cardputer.Display.setTextColor(kCanvas, kDanger);
    M5Cardputer.Display.drawCenterString("!", 224, 10);
    M5Cardputer.Display.setTextColor(kDanger, kCanvas);
    M5Cardputer.Display.println("FATAL ERROR");
    M5Cardputer.Display.setTextColor(kText, kCanvas);
    M5Cardputer.Display.println(error);
}

void showProvisioning(const String& accessPointName, const String& accessPointPassword,
                      const String& footer)
{
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_14);
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(5, 5);
    canvas->print("LOCAL SETUP");
    canvas->drawBitmap(222, 5, kWifiIcon, 8, 8, kSignal);
    canvas->setTextColor(kText, kCanvas);
    canvas->setCursor(5, 23);
    canvas->print("Wi-Fi:");
    canvas->setTextColor(kWarning, kCanvas);
    canvas->setCursor(5, 41);
    canvas->print(accessPointName);
    canvas->setTextColor(kText, kCanvas);
    canvas->setCursor(5, 59);
    canvas->print("Password:");
    canvas->setTextColor(kWarning, kCanvas);
    canvas->setCursor(5, 77);
    canvas->print(accessPointPassword);
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(5, 97);
    canvas->print("Open in browser:");
    canvas->setTextColor(kText, kCanvas);
    canvas->setCursor(5, 115);
    canvas->print("192.168.4.1");
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(235 - canvas->textWidth(footer), 115);
    canvas->print(footer);
    canvas->pushSprite(0, 0);
}

void showFilesPortal(const String& accessPointName, const String& accessPointPassword)
{
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_14);
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(5, 5);
    canvas->print("FILES DOWNLOAD");
    canvas->drawBitmap(222, 5, kChatsIcon, 8, 8, kSignal);
    canvas->setTextColor(kText, kCanvas);
    canvas->setCursor(5, 24);
    canvas->print("Wi-Fi:");
    canvas->setTextColor(kWarning, kCanvas);
    canvas->setCursor(5, 42);
    canvas->print(clippedLine(accessPointName, 28));
    canvas->setTextColor(kText, kCanvas);
    canvas->setCursor(5, 60);
    canvas->print("Password:");
    canvas->setTextColor(kWarning, kCanvas);
    canvas->setCursor(5, 78);
    canvas->print(accessPointPassword);
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(5, 98);
    canvas->print("Open 192.168.4.1");
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(5, 120);
    canvas->print("Use Restart button to return");
    canvas->pushSprite(0, 0);
}

void showWebConsoleAccess(const String& address,
                          const String& accessPassword,
                          bool authenticationActive,
                          WebConsoleBrowserState browserState,
                          bool passwordVisible)
{
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_14);
    canvas->fillRect(0, 0, 240, 18, kBand);
    canvas->drawBitmap(5, 5, kWifiIcon, 8, 8, kSignal);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(18, 1);
    canvas->print("WEB CONSOLE");
    canvas->setTextColor(authenticationActive ? kSuccess : kWarning, kCanvas);
    canvas->setCursor(6, 27);
    canvas->print(authenticationActive ? "Authentication: active"
                                       : "Authentication: waiting");
    const bool browserConnected =
        browserState == WebConsoleBrowserState::Connected;
    canvas->setTextColor(
        browserConnected ? kSuccess :
        browserState == WebConsoleBrowserState::Busy ? kSignal : kWarning,
        kCanvas);
    canvas->setCursor(6, 44);
    canvas->print(
        browserConnected ? "Browser: connected" :
        browserState == WebConsoleBrowserState::Busy ? "Browser: busy"
                                                     : "Browser: waiting");
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(6, 61);
    canvas->print(clippedLine(address, 29));
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(6, 78);
    canvas->print(passwordVisible ? "Installation password:" : "Password hidden");
    canvas->setTextColor(kWarning, kCanvas);
    canvas->setCursor(6, 95);
    canvas->print(passwordVisible ? clippedLine(accessPassword, 29)
                                  : String("Press ENTER to reveal"));
    canvas->fillRect(0, 117, 240, 18, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 120);
    canvas->print("ENTER reveal 30s    ESC close");
    canvas->pushSprite(0, 0);
}

void showPythonWorkspaceAccess(const String& address, const String& accessPassword)
{
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_14);
    canvas->fillRect(0, 0, 240, 18, kBand);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(6, 1);
    canvas->print("PYTHON WORKSPACE");
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(6, 27);
    canvas->print("Address after restart:");
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(6, 45);
    canvas->print(clippedLine(address, 29));
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(6, 68);
    canvas->print("Installation password:");
    canvas->setTextColor(kWarning, kCanvas);
    canvas->setCursor(6, 86);
    canvas->print(clippedLine(accessPassword, 29));
    canvas->fillRect(0, 117, 240, 18, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 120);
    canvas->print("ENTER start   ESC cancel");
    canvas->pushSprite(0, 0);
}

void showPythonWorkspaceRunning(const String& address, const String& accessPassword)
{
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_14);
    canvas->fillRect(0, 0, 240, 18, kBand);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(6, 1);
    canvas->print("PYTHON WORKSPACE");
    canvas->setTextColor(kSuccess, kCanvas);
    canvas->setCursor(6, 27);
    canvas->print("Runtime starting");
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(6, 45);
    canvas->print(clippedLine(address, 29));
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(6, 68);
    canvas->print("Installation password:");
    canvas->setTextColor(kWarning, kCanvas);
    canvas->setCursor(6, 86);
    canvas->print(clippedLine(accessPassword, 29));
    canvas->fillRect(0, 117, 240, 18, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 120);
    canvas->print("Use browser to run or return");
    canvas->pushSprite(0, 0);
}

std::size_t showChat(const std::vector<Message>& history,
                     const std::string& activeResponse,
                     const std::string& input,
                     KeyboardLayout layout,
                     const String& chatTitle,
                     const String& status,
                     std::size_t scrollOffset,
                     const ChatCapabilityStates& capabilities,
                     bool wifiConnected,
                     int batteryLevel,
                     bool batteryCharging)
{
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_12);
    canvas->fillRect(0, 0, 240, 14, kBand);
    canvas->drawBitmap(3, 3, kChatsIcon, 8, 8, kSignal);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(14, 2);
    canvas->print(clippedLine(chatTitle, 14));
    constexpr char capabilityLabels[] = {'W', 'F', 'S', 'P'};
    for (std::size_t index = 0; index < capabilities.size(); ++index) {
        canvas->setTextColor(chatCapabilityColor(capabilities[index]), kBand);
        canvas->setCursor(106 + static_cast<int>(index * 8U), 2);
        canvas->print(capabilityLabels[index]);
    }
    drawBatteryStatus(143, 3, batteryLevel, batteryCharging);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(164, 2);
    canvas->print(batteryLevel >= 0 ? String(batteryLevel) + "%" : String("--%"));
    canvas->drawBitmap(190, 3, kWifiIcon, 8, 8,
                       wifiConnected ? kSuccess : kMuted);
    canvas->setFont(&fonts::efontCN_12);
    const std::uint16_t layoutColor = layout == KeyboardLayout::English
        ? kCoolSecondary : kOxideAccent;
    canvas->fillRoundRect(203, 1, 34, 12, 3, layoutColor);
    canvas->setTextColor(kText, layoutColor);
    canvas->setCursor(206, 2);
    canvas->print(layout == KeyboardLayout::English ? "EN" : "RU");

    const std::size_t visibleTranscriptLines = visibleTranscriptLineCount(status);
    const TranscriptLineCounts transcript =
        transcriptLineCounts(history, activeResponse);
    const std::size_t availableStart = transcript.totalLines > visibleTranscriptLines
        ? transcript.totalLines - visibleTranscriptLines
        : 0;
    const std::size_t effectiveScrollOffset = std::min(scrollOffset, availableStart);
    const auto lines = transcriptLineWindow(
        history, activeResponse, effectiveScrollOffset,
        visibleTranscriptLines, transcript.lastMessageLines);
    int y = 17;
    for (const auto& line : lines) {
        canvas->setTextColor(line.color, kCanvas);
        canvas->setCursor(3, y);
        canvas->print(line.text.c_str());
        y += 12;
    }
    if (availableStart > 0) {
        canvas->drawBitmap(230, 18, kUpIcon, 8, 8,
                           effectiveScrollOffset < availableStart ? kSignal : kMuted);
        const int downIconY = 18 + static_cast<int>((visibleTranscriptLines - 1) * 12);
        canvas->drawBitmap(230, downIconY, kDownIcon, 8, 8,
                           effectiveScrollOffset > 0 ? kSignal : kMuted);
    }

    if (visibleTranscriptLines != kIdleTranscriptLines) {
        const std::uint16_t statusColor = isErrorStatus(status) ? kDanger : kBand;
        const auto statusLines = wrapUtf8Text(status.c_str(), kTranscriptCells);
        const bool detailedStatus = visibleTranscriptLines == kDetailedTranscriptLines;
        const int statusY = detailedStatus ? 78 : 90;
        const int statusHeight = detailedStatus ? 26 : 14;
        canvas->fillRect(0, statusY, 240, statusHeight, statusColor);
        canvas->setTextColor(isErrorStatus(status) ? kCanvas : kText,
                             statusColor);
        const std::size_t maximumStatusLines = detailedStatus ? 2U : 1U;
        const std::size_t visibleStatusLines = std::min(statusLines.size(), maximumStatusLines);
        for (std::size_t index = 0; index < visibleStatusLines; ++index) {
            canvas->setCursor(3, statusY + static_cast<int>(index * 12));
            canvas->print(statusLines[index].c_str());
        }
    }

    const std::string preparedInputLine = prepareChatInputLine(input);
    drawChatInputLine(*canvas, preparedInputLine);

    canvas->fillRect(0, 121, 240, 14, kBand);
    canvas->drawFastVLine(47, 121, 14, kCanvas);
    canvas->drawFastVLine(95, 121, 14, kCanvas);
    canvas->drawFastVLine(143, 121, 14, kCanvas);
    canvas->drawFastVLine(191, 121, 14, kCanvas);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    drawToolbarItem(0, kMicIcon, "G0 MIC");
    drawToolbarItem(48, kChatsIcon, "F1 CHAT");
    drawToolbarItem(96, kModelIcon, "F2 CAP");
    drawToolbarItem(144, kLanguageIcon,
                    layout == KeyboardLayout::English ? "F3 RU" : "F3 EN");
    drawToolbarItem(192, kSettingsIcon, "F4 MENU");
    canvas->pushSprite(0, 0);
    return effectiveScrollOffset;
}

void updateChatInput(const std::string& input)
{
    const std::string preparedInputLine = prepareChatInputLine(input);
    drawChatInputLine(*canvas, preparedInputLine);
    drawChatInputLine(M5Cardputer.Display, preparedInputLine);
}

void showCarousel(const std::vector<CarouselCard>& cards,
                  std::size_t selectedIndex,
                  bool wifiConnected,
                  bool sdReady,
                  int batteryLevel,
                  bool batteryCharging,
                  const String& status)
{
    if (cards.empty() || selectedIndex >= cards.size()) {
        showFatalError("Carousel has no valid selected card");
        return;
    }
    drawCarouselFrame(cards, selectedIndex, wifiConnected, sdReady,
                      batteryLevel, batteryCharging, status);
}

void animateCarousel(const std::vector<CarouselCard>& cards,
                     std::size_t previousIndex,
                     std::size_t selectedIndex,
                     CarouselDirection direction,
                     bool wifiConnected,
                     bool sdReady,
                     int batteryLevel,
                     bool batteryCharging,
                     const String& status)
{
    if (cards.empty() || previousIndex >= cards.size() ||
        selectedIndex >= cards.size()) {
        showFatalError("Carousel animation has invalid card indexes");
        return;
    }
    const int directionSign = direction == CarouselDirection::Next ? 1 : -1;
    for (int frame = 1; frame <= kCarouselAnimationFrames; ++frame) {
        const int distance = kCarouselTravel * frame / kCarouselAnimationFrames;
        const int previousX = kCarouselCardX - directionSign * distance;
        const int selectedX = kCarouselCardX +
            directionSign * (kCarouselTravel - distance);
        drawCarouselAnimationFrame(cards, previousIndex, selectedIndex,
                                   previousX, selectedX, wifiConnected, sdReady,
                                   batteryLevel, batteryCharging, status);
        delay(1);
    }
}

CarouselDiagnosticResult runCarouselDiagnostic(
    const std::vector<CarouselCard>& cards)
{
    if (cards.size() != 9) {
        return {{false, String("Carousel diagnostic requires 9 cards, received ") +
                        String(cards.size())}, 0, 0};
    }
    for (std::size_t index = 0; index < cards.size(); ++index) {
        showCarousel(cards, index, true, true, 75, false, "");
        const OperationResult write = writeCarouselDiagnosticFrame(index);
        if (!write.success) {
            return {write, 0, 0};
        }
    }
    const std::uint32_t nextStartedAt = micros();
    animateCarousel(cards, cards.size() - 1, 0, CarouselDirection::Next,
                    true, true, 75, false, "");
    const std::uint32_t nextDurationUs = micros() - nextStartedAt;
    const std::uint32_t previousStartedAt = micros();
    animateCarousel(cards, 0, cards.size() - 1, CarouselDirection::Previous,
                    true, true, 75, false, "");
    const std::uint32_t previousDurationUs = micros() - previousStartedAt;

    showSelectionList(
        "PROJECT ACTIONS",
        {"Open chats", "Model: Global default", "Project instructions: OFF",
         "Context: 32 KiB", "Output: 1024 tokens", "Auto compact: ON",
         "Rename project", "Duplicate project", "Archive project",
         "Export project bundle", "API profile: Global default",
         "Capability policies", "Delete project", "Back"},
        12, "UP/DOWN  ENTER  ESC projects");
    OperationResult write = writeCarouselDiagnosticFrame(9);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    showSelectionList(
        "P6-06 CHAT",
        {"Open chat", "Chat instructions", "Chat model: Project default",
         "View full history (12)", "Retry unavailable", "Latest search sources",
         "Pin chat", "Archive chat", "Duplicate chat", "Export Markdown",
         "Export project bundle", "Regenerate context summary",
         "Next output: project default", "Next instructions: OFF",
         "Capability policies", "Capability status", "Next capabilities: Auto",
         "Rename chat", "Clear messages", "Delete chat", "Back"},
        17, "UP/DOWN  ENTER  ESC back");
    write = writeCarouselDiagnosticFrame(10);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    showTextEditor(
        "RENAME CHAT", std::string(256, 'x'), KeyboardLayout::English, 256,
        "Chat name limit: 256 bytes", "Stored title uses up to 28 cells",
        "ENTER save  CTRL+BACKSPACE clear  ESC back");
    write = writeCarouselDiagnosticFrame(11);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    showConfirmation("DELETE PROJECT", "P6-06 Device fixture",
                     "ENTER delete  ESC cancel");
    write = writeCarouselDiagnosticFrame(12);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    showSelectionList("PROJECTS", std::vector<String>{}, 0,
                      "SD unavailable: card removed");
    write = writeCarouselDiagnosticFrame(13);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    showReadOnlyTextViewer(
        "REFERENCE.md",
        {"04  This fixed line checks native width.",
         "05  Read-only content remains visible.",
         "06  Long viewers keep the footer clear.",
         "07  Scrolling starts away from the top.",
         "08  Neutral data replaces user content.",
         "09  Text stays inside the 240px canvas.",
         "10  The final rows remain readable.",
         "11  Footer position is unchanged."},
        2, "3-8/8");
    write = writeCarouselDiagnosticFrame(14);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    {
        const std::string fileInput =
            "alpha beta gamma delta epsilon zeta eta theta iota kappa lambda "
            "mu nu xi omicron pi rho sigma tau upsilon phi chi psi omega";
        showFileEditor("notes.md", fileInput, 78, KeyboardLayout::English, 4096,
                       "Ln 4 Col 12", "Save failed: SD storage is full");
    }
    write = writeCarouselDiagnosticFrame(15);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    showChat(
        {{"user", "Check a representative Device response."},
         {"assistant", "The retained draft and history remain visible."}},
        "", "draft retained", KeyboardLayout::English, "P6-06 CHAT",
        "Error: provider unavailable; request not sent",
        0,
        {ChatCapabilityState::Off, ChatCapabilityState::Inherit,
         ChatCapabilityState::Ask, ChatCapabilityState::Allow},
        false, 75, false);
    write = writeCarouselDiagnosticFrame(16);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    showSecretEntry("API KEY", "Representative provider key", 32,
                    "Error: credential rejected",
                    "ENTER save  ESC cancel");
    write = writeCarouselDiagnosticFrame(17);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    showDeviceDiagnostics(
        {"6.0.0-test", "75%", "Connected", "READY", "96 KiB",
         "48 KiB", "7 KiB", "160 MHz", "00:10:00", "3",
         "Power on", "Idle", true, true, true, true},
        0);
    write = writeCarouselDiagnosticFrame(18);
    if (!write.success) {
        return {write, nextDurationUs, previousDurationUs};
    }

    return {{true, ""}, nextDurationUs, previousDurationUs};
}

void showSelectionList(const String& title,
                       const std::vector<String>& items,
                       std::size_t selectedIndex,
                       const String& footer)
{
    constexpr std::size_t maximumVisibleItems = 5;
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_14);
    canvas->fillRect(0, 0, 240, 17, kBand);
    canvas->drawBitmap(4, 4, kSettingsIcon, 8, 8, kSignal);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(16, 1);
    canvas->print(clippedLine(title, 26));

    if (items.empty()) {
        canvas->setTextColor(kMuted, kCanvas);
        canvas->setCursor(8, 47);
        canvas->print("No items available");
    } else {
        const std::size_t boundedSelection = std::min(selectedIndex, items.size() - 1);
        std::size_t start = boundedSelection >= maximumVisibleItems
            ? boundedSelection - maximumVisibleItems + 1
            : 0;
        if (items.size() - start < maximumVisibleItems && items.size() > maximumVisibleItems) {
            start = items.size() - maximumVisibleItems;
        }
        canvas->setFont(&fonts::efontCN_12);
        for (std::size_t row = 0; row < maximumVisibleItems && start + row < items.size(); ++row) {
            const std::size_t index = start + row;
            const int y = 20 + static_cast<int>(row * 19);
            const bool selected = index == boundedSelection;
            const std::uint16_t background = selected ? kSignal : kCanvas;
            canvas->fillRect(3, y, 234, 17, background);
            if (selected) {
                canvas->drawRect(3, y, 234, 17, kText);
            }
            canvas->setTextColor(selected ? kCanvas : kText, background);
            canvas->setCursor(7, y + 1);
            canvas->print(selected ? "> " : "  ");
            canvas->print(clippedLine(items[index], 31));
        }
    }

    canvas->fillRect(0, 117, 240, 18, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 120);
    canvas->print(clippedLine(footer, 44));
    canvas->pushSprite(0, 0);
}

void showDeviceDiagnostics(const DeviceDiagnosticsView& diagnostics, std::size_t pageIndex)
{
    constexpr std::size_t pageCount = 2;
    const std::size_t page = std::min(pageIndex, pageCount - 1);
    canvas->fillScreen(kCanvas);
    canvas->fillRect(0, 0, 240, 18, kBand);
    canvas->drawBitmap(4, 4, kSettingsIcon, 8, 8, kSignal);
    canvas->setFont(&fonts::efontCN_12);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(16, 2);
    canvas->print(page == 0 ? "DEVICE STATUS" : "SYSTEM DETAILS");
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kSignal, kBand);
    canvas->setCursor(207, 3);
    canvas->print(String(page + 1) + "/" + String(pageCount));

    const auto metric = [](int x, int y, const char* label, const String& value,
                           std::uint16_t accent) {
        canvas->fillRoundRect(x, y, 112, 38, 5, kRaised);
        canvas->drawFastVLine(x, y + 5, 28, accent);
        canvas->setFont(&fonts::efontCN_10);
        canvas->setTextColor(kMuted, kRaised);
        canvas->setCursor(x + 8, y + 4);
        canvas->print(label);
        canvas->setFont(&fonts::efontCN_12);
        canvas->setTextColor(kText, kRaised);
        canvas->setCursor(x + 8, y + 18);
        canvas->print(clippedLine(value, 16));
    };
    const auto detail = [](int y, const char* label, const String& value,
                           std::uint16_t valueColor) {
        canvas->setFont(&fonts::efontCN_10);
        canvas->setTextColor(kMuted, kCanvas);
        canvas->setCursor(7, y);
        canvas->print(label);
        canvas->setTextColor(valueColor, kCanvas);
        canvas->setCursor(79, y);
        canvas->print(clippedLine(value, 27));
    };

    if (page == 0) {
        metric(5, 23, "BATTERY", diagnostics.battery,
               diagnostics.battery.startsWith("LOW") ? kDanger : kSuccess);
        metric(123, 23, "WI-FI", diagnostics.wifi,
               diagnostics.wifiConnected ? kSuccess : kWarning);
        metric(5, 66, "MICROSD", diagnostics.storage,
               diagnostics.storageReady ? kCoolSecondary : kDanger);
        metric(123, 66, "FREE MEMORY", diagnostics.heap, kOxideAccent);
        canvas->setFont(&fonts::efontCN_10);
        canvas->setTextColor(kMuted, kCanvas);
        canvas->setCursor(7, 108);
        canvas->print(clippedLine("v" + diagnostics.firmware + "  " + diagnostics.uptime,
                                  38));
    } else {
        detail(25, "CPU", diagnostics.cpu, kText);
        detail(39, "MEM BLOCK", diagnostics.largestHeap, kText);
        detail(53, "STACK", diagnostics.stack, kText);
        detail(67, "CHATS", diagnostics.chats, kText);
        detail(81, "LAST TASK", diagnostics.previousOperation, kSignal);
        detail(95, "RESET", diagnostics.resetReason, kWarning);
        const String services = String("JOURNAL ") +
            (diagnostics.crashJournalReady ? "OK" : "--") + "   SSH " +
            (diagnostics.sshStorageReady ? "OK" : "--");
        detail(109, "SERVICES", services,
               diagnostics.crashJournalReady && diagnostics.sshStorageReady
                   ? kSuccess
                   : kWarning);
    }

    canvas->fillRect(0, 119, 240, 16, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(5, 120);
    canvas->print("LEFT/RIGHT pages   ESC back");
    canvas->pushSprite(0, 0);
}

namespace {

void drawTextViewer(const String& title,
                    const std::vector<std::string>& lines,
                    std::size_t firstLine,
                    const String& position,
                    const String& footer)
{
    constexpr std::size_t maximumVisibleLines = 8;
    canvas->fillScreen(kCanvas);
    canvas->fillRect(0, 0, 240, 17, kBand);
    canvas->drawBitmap(4, 4, kChatsIcon, 8, 8, kCoolSecondary);
    canvas->setFont(&fonts::efontCN_12);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(16, 2);
    canvas->print(clippedLine(title, 27));

    const std::size_t boundedFirstLine = lines.empty()
        ? 0
        : std::min(firstLine, lines.size() - 1);
    for (std::size_t row = 0;
         row < maximumVisibleLines && boundedFirstLine + row < lines.size();
         ++row) {
        canvas->setTextColor(kText, kCanvas);
        canvas->setCursor(3, 19 + static_cast<int>(row * 12));
        canvas->print(lines[boundedFirstLine + row].c_str());
    }
    if (lines.empty()) {
        canvas->setTextColor(kMuted, kCanvas);
        canvas->setCursor(7, 53);
        canvas->print("Empty file");
    }

    canvas->fillRect(0, 116, 240, 19, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kSignal, kBand);
    canvas->setCursor(4, 118);
    canvas->print(clippedLine(position, 18));
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(91, 118);
    canvas->print(footer);
    canvas->pushSprite(0, 0);
}

}  // namespace

void showTextViewer(const String& title,
                    const std::vector<std::string>& lines,
                    std::size_t firstLine,
                    const String& position)
{
    drawTextViewer(title, lines, firstLine, position,
                   "UP/DOWN  ENTER edit  ESC");
}

void showReadOnlyTextViewer(const String& title,
                            const std::vector<std::string>& lines,
                            std::size_t firstLine,
                            const String& position)
{
    drawTextViewer(title, lines, firstLine, position, "UP/DOWN  ESC back");
}

void showTextEditor(const String& title,
                    const std::string& input,
                    KeyboardLayout layout,
                    std::size_t maximumBytes,
                    const String& status,
                    const String& emptyHint,
                    const String& footer)
{
    constexpr std::size_t maximumVisibleLines = 6;
    canvas->fillScreen(kCanvas);
    canvas->fillRect(0, 0, 240, 17, kBand);
    canvas->drawBitmap(4, 4, kChatsIcon, 8, 8, kCoolSecondary);
    canvas->setFont(&fonts::efontCN_12);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(16, 2);
    canvas->print(clippedLine(title, 24));
    const std::uint16_t layoutColor = layout == KeyboardLayout::Russian
        ? kOxideAccent : kCoolSecondary;
    canvas->fillRoundRect(207, 1, 31, 15, 3, layoutColor);
    canvas->setTextColor(kText, layoutColor);
    canvas->setCursor(213, 2);
    canvas->print(layout == KeyboardLayout::Russian ? "RU" : "EN");

    const std::string visibleInput = input.empty()
        ? std::string(emptyHint.c_str()) + "_"
        : input + "_";
    const auto wrapped = wrapUtf8Text(visibleInput, 38);
    const std::size_t firstLine = wrapped.size() > maximumVisibleLines
        ? wrapped.size() - maximumVisibleLines
        : 0;
    canvas->setTextColor(input.empty() ? kMuted : kText, kCanvas);
    for (std::size_t row = 0; row < maximumVisibleLines && firstLine + row < wrapped.size(); ++row) {
        canvas->setCursor(3, 19 + static_cast<int>(row * 13));
        canvas->print(wrapped[firstLine + row].c_str());
    }

    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(status.isEmpty() ? kSignal : kWarning, kCanvas);
    canvas->setCursor(4, 105);
    const String detail = status.isEmpty()
        ? String(input.size()) + "/" + String(maximumBytes) + " bytes"
        : status;
    canvas->print(clippedLine(detail, 42));
    canvas->fillRect(0, 117, 240, 18, kBand);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 120);
    canvas->print(clippedLine(footer, 44));
    canvas->pushSprite(0, 0);
}

void showQrCode(const String& title, const String& payload, const String& footer)
{
    canvas->fillScreen(TFT_WHITE);
    canvas->fillRect(0, 0, 240, 18, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(5, 3);
    canvas->print(clippedLine(title, 38));
    canvas->qrcode(payload.c_str(), 68, 21, 92, 1, true);
    canvas->fillRect(0, 116, 240, 19, kBand);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(5, 119);
    canvas->print(clippedLine(footer, 42));
    canvas->pushSprite(0, 0);
}

void showFileEditor(const String& title,
                    const std::string& input,
                    std::size_t cursor,
                    KeyboardLayout layout,
                    std::size_t maximumBytes,
                    const String& position,
                    const String& status)
{
    constexpr std::size_t maximumVisibleLines = 6;
    canvas->fillScreen(kCanvas);
    canvas->fillRect(0, 0, 240, 17, kBand);
    canvas->drawBitmap(4, 4, kChatsIcon, 8, 8, kCoolSecondary);
    canvas->setFont(&fonts::efontCN_12);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(16, 2);
    canvas->print(clippedLine(title, 24));
    const std::uint16_t layoutColor = layout == KeyboardLayout::Russian
        ? kOxideAccent : kCoolSecondary;
    canvas->fillRoundRect(207, 1, 31, 15, 3, layoutColor);
    canvas->setTextColor(kText, layoutColor);
    canvas->setCursor(213, 2);
    canvas->print(layout == KeyboardLayout::Russian ? "RU" : "EN");

    const std::size_t boundedCursor = std::min(cursor, input.size());
    const std::string visibleInput = input.substr(0, boundedCursor) + "|" +
        input.substr(boundedCursor);
    const auto wrapped = wrapUtf8Text(visibleInput, 38);
    const auto cursorWrapped = wrapUtf8Text(input.substr(0, boundedCursor) + "|", 38);
    const std::size_t cursorLine = cursorWrapped.empty() ? 0 : cursorWrapped.size() - 1;
    const std::size_t preferredFirstLine = cursorLine > maximumVisibleLines / 2
        ? cursorLine - maximumVisibleLines / 2
        : 0;
    const std::size_t maximumFirstLine = wrapped.size() > maximumVisibleLines
        ? wrapped.size() - maximumVisibleLines
        : 0;
    const std::size_t firstLine = std::min(preferredFirstLine, maximumFirstLine);
    canvas->setTextColor(kText, kCanvas);
    for (std::size_t row = 0; row < maximumVisibleLines && firstLine + row < wrapped.size(); ++row) {
        canvas->setCursor(3, 19 + static_cast<int>(row * 13));
        canvas->print(wrapped[firstLine + row].c_str());
    }

    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(status.isEmpty() ? kSignal : kWarning, kCanvas);
    canvas->setCursor(4, 99);
    const String detail = status.isEmpty()
        ? position + "  " + String(input.size()) + "/" + String(maximumBytes) + " B"
        : status;
    canvas->print(clippedLine(detail, 42));
    canvas->fillRect(0, 113, 240, 22, kBand);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 113);
    canvas->print("ENTER save  ESC cancel");
    canvas->setCursor(4, 123);
    canvas->print("Opt+< > cursor  Fn+ENTER newline");
    canvas->pushSprite(0, 0);
}

void showFilenameEntry(const String& title,
                       const std::string& input,
                       const String& status)
{
    canvas->fillScreen(kCanvas);
    canvas->fillRect(0, 0, 240, 17, kBand);
    canvas->drawBitmap(4, 4, kChatsIcon, 8, 8, kCoolSecondary);
    canvas->setFont(&fonts::efontCN_12);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(16, 2);
    canvas->print(clippedLine(title, 30));
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(5, 27);
    canvas->print("UTF-8 nested path:");
    canvas->drawRoundRect(4, 47, 232, 25, 4, kMuted);
    canvas->setTextColor(kText, kCanvas);
    canvas->setCursor(9, 52);
    canvas->print(clippedLine(String(input.c_str()) + "_", 34));
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(status.isEmpty() ? kSignal : kWarning, kCanvas);
    canvas->setCursor(5, 83);
    canvas->print(clippedLine(status.isEmpty()
                                  ? String("Transfer: any safe ext; text: .txt/.md/...")
                                  : status,
                              42));
    canvas->setCursor(5, 101);
    canvas->setTextColor(kMuted, kCanvas);
    canvas->print(String(input.size()) + "/512 bytes");
    canvas->fillRect(0, 117, 240, 18, kBand);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 120);
    canvas->print("ENTER confirm ESC  Fn+3 lang");
    canvas->pushSprite(0, 0);
}

void showPasswordEntry(const String& ssid, std::size_t passwordLength, const String& status)
{
    showSecretEntry("WI-FI PASSWORD", ssid, passwordLength, status,
                    "ENTER connect   ESC cancel");
}

void showSecretEntry(const String& title, const String& label,
                     std::size_t secretLength, const String& status,
                     const String& footer)
{
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_14);
    canvas->fillRect(0, 0, 240, 17, kBand);
    canvas->drawBitmap(4, 4, kWifiIcon, 8, 8, kSignal);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(16, 1);
    canvas->print(clippedLine(title, 26));
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(5, 25);
    canvas->print(clippedLine(label, 29));
    canvas->drawRoundRect(4, 48, 232, 25, 4, kMuted);
    canvas->setTextColor(kWarning, kCanvas);
    canvas->setCursor(9, 52);
    String mask;
    const std::size_t visibleCharacters = std::min<std::size_t>(secretLength, 25);
    for (std::size_t index = 0; index < visibleCharacters; ++index) {
        mask += '*';
    }
    if (secretLength > visibleCharacters) {
        mask += "...";
    }
    canvas->print(mask + "_");
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(5, 80);
    canvas->print("Length: " + String(secretLength));
    canvas->setTextColor(isErrorStatus(status) ? kDanger : kSignal, kCanvas);
    canvas->setCursor(5, 98);
    canvas->print(clippedLine(status, 34));
    canvas->fillRect(0, 117, 240, 18, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 120);
    canvas->print(clippedLine(footer, 42));
    canvas->pushSprite(0, 0);
}

void showBusyScreen(const String& title, const String& message)
{
    canvas->fillScreen(kCanvas);
    canvas->setFont(&fonts::efontCN_14);
    canvas->setTextColor(kSignal, kCanvas);
    canvas->setCursor(7, 26);
    canvas->print(clippedLine(title, 27));
    canvas->drawBitmap(220, 27, kWifiIcon, 8, 8, kSignal);
    canvas->setTextColor(kText, kCanvas);
    canvas->setCursor(7, 57);
    canvas->print(clippedLine(message, 29));
    canvas->pushSprite(0, 0);
}

void showConfirmation(const String& title, const String& message, const String& footer)
{
    canvas->fillScreen(kCanvas);
    canvas->fillRect(0, 0, 240, 18, kDanger);
    canvas->setFont(&fonts::efontCN_14);
    canvas->drawBitmap(5, 5, kTrashIcon, 8, 8, kCanvas);
    canvas->setTextColor(kCanvas, kDanger);
    canvas->setCursor(18, 1);
    canvas->print(clippedLine(title, 25));
    canvas->setTextColor(kText, kCanvas);
    const auto lines = wrapUtf8Text(message.c_str(), 31);
    for (std::size_t index = 0; index < std::min<std::size_t>(lines.size(), 4); ++index) {
        canvas->setCursor(8, 29 + static_cast<int>(index * 17));
        canvas->print(lines[index].c_str());
    }
    canvas->fillRect(0, 117, 240, 18, kBand);
    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kText, kBand);
    canvas->setCursor(4, 120);
    canvas->print(clippedLine(footer, 44));
    canvas->pushSprite(0, 0);
}

void showVoiceRecording(std::uint32_t elapsedMs,
                        std::uint32_t maximumMs,
                        std::uint16_t level)
{
    canvas->fillScreen(kCanvas);
    canvas->fillRect(0, 0, 240, 18, kDanger);
    canvas->setFont(&fonts::efontCN_14);
    canvas->setTextColor(kCanvas, kDanger);
    canvas->setCursor(6, 1);
    canvas->print("VOICE RECORDING");

    canvas->fillRoundRect(105, 29, 30, 43, 12, kDanger);
    canvas->fillRoundRect(111, 34, 18, 31, 8, kText);
    canvas->drawRoundRect(99, 45, 42, 36, 16, kDanger);
    canvas->fillRect(117, 80, 6, 10, kDanger);
    canvas->fillRoundRect(108, 88, 24, 5, 2, kDanger);

    const std::uint16_t visibleLevel = static_cast<std::uint16_t>(
        std::min<std::uint32_t>(1000U, static_cast<std::uint32_t>(level) * 8U));
    const int meterWidth = static_cast<int>(visibleLevel * 210U / 1000U);
    canvas->drawRoundRect(14, 99, 212, 9, 3, kMuted);
    canvas->fillRoundRect(15, 100, meterWidth, 7, 2, kSuccess);
    const std::uint32_t boundedElapsed = std::min(elapsedMs, maximumMs);
    const int progressWidth = maximumMs == 0
        ? 0
        : static_cast<int>(boundedElapsed * 232U / maximumMs);
    canvas->fillRect(4, 113, progressWidth, 4, kDanger);

    canvas->setFont(&fonts::efontCN_10);
    canvas->setTextColor(kMuted, kCanvas);
    canvas->setCursor(4, 122);
    canvas->print("Release G0: transcribe   max ");
    canvas->print(maximumMs / 1000U);
    canvas->print("s");
    canvas->pushSprite(0, 0);
}

bool fontSupportsCyrillic()
{
    lgfx::FontMetrics metric;
    return fonts::efontCN_12.updateFontMetric(&metric, 0x041F) &&
           fonts::efontCN_12.updateFontMetric(&metric, 0x044F);
}

}  // namespace cardputer
