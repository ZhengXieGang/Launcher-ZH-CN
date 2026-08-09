#ifndef LAUNCHER_LOCALIZATION_H
#define LAUNCHER_LOCALIZATION_H

#include <Arduino.h>
#include <cstdint>
#include <vector>

// The language code is deliberately kept independent from the display driver and
// the WebUI.  A language package can therefore be added without changing the
// launcher state machine or any protocol/API names.
enum class UiLanguage : uint8_t {
    ChineseSimplified = 0,
    English = 1,
};

enum class UiTextKey : uint16_t {
    Launcher = 0,
    NoOptions,
    SdShort,
    LaunchFromSd,
    LaunchFromOrManageSd,
    OtaShort,
    OnlineInstaller,
    WuiShort,
    StartWebUi,
    StartWebUserInterface,
    UsbShort,
    SdUsb,
    SdUsbInterface,
    PartitionManager,
    ChangeSettings,
    ChangeLauncherSettings,
    TurnOffDevice,
    InsertSdCard,
    MainMenu,
    Back,
    Cancel,
    ChargeMode,
    Brightness,
    DimTime,
    UiColor,
    Orientation,
    SeeAllFiles,
    ShowDotfiles,
    AutoBackup,
    BootToLauncher,
    AskToCopySpiffs,
    ManageShortcuts,
    BootAnimation,
    DeactivateDev,
    CalibrateTouch,
    StartCardKb,
    RetryWifiModule,
    ResetConfigsWifi,
    Restart,
    TurnOff,
    Language,
    SimplifiedChinese,
    EnglishLanguage,
    Saving,
    Default,
    Red,
    Blue,
    Yellow,
    Purple,
    White,
    Black,
    Disable,
    InstallingFirmware,
    CopyingData,
    Downloading,
    RestartYourDevice,
    UploadFailed,
    UploadAborted,
    FileNotFound,
    InvalidAction,
    NoOtaSlot,
    ProtectedPartition,
    PartitionNotFound,
    InvalidSize,
    ApplyOrDiscardPending,
    CannotFormat,
    BackupDataFor,
    BackupFailed,
    RestoreFailed,
    WebUiMyNetwork,
    WebUiApMode,
    PressSelectToStop,
    Options,
    OtaInstall,
    DownloadToSd,
    AddToFavorite,
    BackToList,
    PreviousPage,
    NextPage,
    RefineSearch,
    UpdateAll,
    OrderByDownloads,
    OrderByName,
    OrderByLatest,
    StarredOnly,
    TextSearch,
    BackToMenu,
    PageUp,
    PageDown,
    UsbMsc,
    Loading,
    Preparing,
    Updating,
    UploadComplete,
    FileSaved,
    NvsSaved,
    Unknown,
    Count,
};

UiLanguage uiLanguage();
const char *uiLanguageCode();
const char *uiLanguageName(UiLanguage language);
bool uiIsSupportedLanguage(const String &code);
UiLanguage uiLanguageFromCode(const String &code);
bool uiSetLanguage(UiLanguage language, bool persist = true);
bool uiSetLanguageCode(const String &code, bool persist = true);
bool uiLoadLanguageFromNVS();
bool uiSaveLanguageToNVS();

String uiText(UiTextKey key);
String uiTranslate(const String &source);
// Translate human-readable console lines while keeping command/protocol
// markers stable. Newline-separated records are translated independently so
// callers may pass multi-line banners or status blocks.
String uiTranslateSerialLine(const String &source);
String uiFormat(UiTextKey key, const String &arg0 = "", const String &arg1 = "");

// UTF-8 helpers are intentionally small and allocation-free at the decode layer.
// Invalid sequences always consume at least one byte and become U+FFFD, keeping
// rendering, width calculations, and wrapping deterministic for damaged input.
bool uiDecodeUtf8(const char *text, size_t length, size_t &offset, uint32_t &codepoint);
int uiTextWidth(const String &text, uint8_t textSize = 1);
int uiTextLineHeight(const String &text, uint8_t textSize = 1);
String uiClipText(const String &text, int maxWidth, uint8_t textSize = 1);
std::vector<String> uiWrapText(const String &text, int maxWidth, uint8_t textSize = 1);

// Display-independent text drawing entry points. ASCII uses the active native
// font; the shipped Simplified Chinese strings use a compact 12x12 bitmap subset
// that works consistently with every display driver. Unknown code points render
// as a stable replacement glyph rather than corrupting UTF-8 output.
void uiDrawText(const String &text, int x, int y, uint8_t textSize = 1);
void uiDrawCentreText(const String &text, int x, int y, uint8_t textSize = 1);
void uiDrawRightText(const String &text, int x, int y, uint8_t textSize = 1);

#if defined(LOCALIZATION_HOST_TEST)
// Host-only hooks let the standalone regression test exercise NVS fallback and
// alignment without an ESP32 or a display driver.
void uiTestSetNvsLanguage(const String &code);
void uiTestClearNvsLanguage();
int uiTestLastDrawX();
String uiTestLastDrawText();
#endif

#endif
