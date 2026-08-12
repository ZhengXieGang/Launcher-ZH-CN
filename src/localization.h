#ifndef LAUNCHER_LOCALIZATION_H
#define LAUNCHER_LOCALIZATION_H

#include <Arduino.h>
#include <cstdint>
#include <vector>

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

// Display-independent text drawing entry points. ASCII keeps the display
// driver's original 5x7 glyphs in 6x8 cells; Simplified Chinese uses seven
// visible rows in a compact 8x8 full-width cell with the same top edge and line
// height. Unknown code points render as a stable replacement glyph rather than
// corrupting UTF-8 output.
void uiDrawText(const String &text, int x, int y, uint8_t textSize = 1);
void uiDrawCentreText(const String &text, int x, int y, uint8_t textSize = 1);
void uiDrawRightText(const String &text, int x, int y, uint8_t textSize = 1);

#if defined(LOCALIZATION_HOST_TEST)
// Host-only hooks let the standalone regression test exercise alignment without
// an ESP32 or a display driver.
int uiTestLastDrawX();
String uiTestLastDrawText();
#endif

#endif
