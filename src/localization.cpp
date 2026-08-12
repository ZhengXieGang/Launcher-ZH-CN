#include "localization.h"
#include "localization_font.h"

#if !defined(LOCALIZATION_HOST_TEST)
#include "display.h"
#endif

#include <cstring>

namespace {

struct UiTranslation {
    UiTextKey key;
    const char *english;
    const char *simplifiedChinese;
};

// Compatibility aliases cover legacy menu/error literals while call sites are
// gradually migrated to UiTextKey.
struct UiLegacyTranslation {
    const char *english;
    const char *simplifiedChinese;
};

// English strings are lookup keys used by existing business code. Firmware UI
// output is always Simplified Chinese.
constexpr UiTranslation kTranslations[] = {
    {UiTextKey::Launcher, "Launcher", "启动器"},
    {UiTextKey::NoOptions, "No options available", "没有可用选项"},
    {UiTextKey::SdShort, "SD", "SD"},
    {UiTextKey::LaunchFromSd, "Launch from SDCard", "从 SD 卡启动"},
    {UiTextKey::LaunchFromOrManageSd, "Launch from or mng SDCard", "从 SD 卡启动或管理"},
    {UiTextKey::OtaShort, "OTA", "OTA"},
    {UiTextKey::OnlineInstaller, "Online Installer", "在线安装"},
    {UiTextKey::WuiShort, "WUI", "WUI"},
    {UiTextKey::StartWebUi, "Start WebUI", "启动 WebUI"},
    {UiTextKey::StartWebUserInterface, "Start Web User Interface", "启动 Web 用户界面"},
    {UiTextKey::UsbShort, "USB", "USB"},
    {UiTextKey::SdUsb, "SD->USB", "SD->USB"},
    {UiTextKey::SdUsbInterface, "SD->USB Interface", "SD->USB 接口"},
    {UiTextKey::PartitionManager, "Partition Manager", "分区管理"},
    {UiTextKey::ChangeSettings, "Change Settings.", "更改设置"},
    {UiTextKey::ChangeLauncherSettings, "Change Launcher Settings.", "更改启动器设置"},
    {UiTextKey::TurnOffDevice, "Turn off Device", "关闭设备"},
    {UiTextKey::InsertSdCard, "Insert SD Card", "请插入 SD 卡"},
    {UiTextKey::MainMenu, "Main Menu", "主菜单"},
    {UiTextKey::Back, "Back", "返回"},
    {UiTextKey::Cancel, "Cancel", "取消"},
    {UiTextKey::ChargeMode, "Charge Mode", "充电模式"},
    {UiTextKey::Brightness, "Brightness", "亮度"},
    {UiTextKey::DimTime, "Dim time", "息屏时间"},
    {UiTextKey::UiColor, "UI Color", "界面颜色"},
    {UiTextKey::Orientation, "Orientation", "屏幕方向"},
    {UiTextKey::SeeAllFiles, "See All Files", "查看全部文件"},
    {UiTextKey::ShowDotfiles, "Show Dotfiles", "显示隐藏文件"},
    {UiTextKey::AutoBackup, "Auto Backup", "自动备份"},
    {UiTextKey::BootToLauncher, "Boot to Launcher", "启动到主界面"},
    {UiTextKey::AskToCopySpiffs, "Ask to copy SPIFFS", "询问是否复制 SPIFFS"},
    {UiTextKey::ManageShortcuts, "Manage shortcuts", "管理快捷键"},
    {UiTextKey::BootAnimation, "Boot Animation", "启动动画"},
    {UiTextKey::DeactivateDev, "Deactivate Dev", "停用开发模式"},
    {UiTextKey::CalibrateTouch, "Calibrate Touch", "校准触摸"},
    {UiTextKey::StartCardKb, "Start CardKb", "启动 CardKb"},
    {UiTextKey::RetryWifiModule, "Retry WiFi Module", "重试 WiFi 模块"},
    {UiTextKey::ResetConfigsWifi, "Reset Configs/Wifi", "重置配置和 WiFi"},
    {UiTextKey::Restart, "Restart", "重启"},
    {UiTextKey::TurnOff, "Turn-off", "关机"},
    {UiTextKey::Saving, "Saving...", "正在保存..."},
    {UiTextKey::Default, "Default", "默认"},
    {UiTextKey::Red, "Red", "红色"},
    {UiTextKey::Blue, "Blue", "蓝色"},
    {UiTextKey::Yellow, "Yellow", "黄色"},
    {UiTextKey::Purple, "Purple", "紫色"},
    {UiTextKey::White, "White", "白色"},
    {UiTextKey::Black, "Black", "黑色"},
    {UiTextKey::Disable, "Disable", "禁用"},
    {UiTextKey::InstallingFirmware, "Installing FW", "正在安装固件"},
    {UiTextKey::CopyingData, "Copying Data", "正在复制数据"},
    {UiTextKey::Downloading, "Downloading", "正在下载"},
    {UiTextKey::RestartYourDevice, "Restart your device", "请重启设备"},
    {UiTextKey::UploadFailed, "Upload Failed", "上传失败"},
    {UiTextKey::UploadAborted, "Upload Aborted", "上传已取消"},
    {UiTextKey::FileNotFound, "File not found", "找不到文件"},
    {UiTextKey::InvalidAction, "ERROR: invalid action param supplied", "错误：操作参数无效"},
    {UiTextKey::NoOtaSlot, "No OTA slot", "没有可用 OTA 分区"},
    {UiTextKey::ProtectedPartition, "Protected partition", "分区受保护"},
    {UiTextKey::PartitionNotFound, "Partition not found", "找不到分区"},
    {UiTextKey::InvalidSize, "Invalid size", "大小无效"},
    {UiTextKey::ApplyOrDiscardPending, "Apply or discard pending changes first", "请先应用或放弃待处理的更改"},
    {UiTextKey::CannotFormat, "Cannot format", "无法格式化"},
    {UiTextKey::BackupDataFor, "Backup data for {0}?", "备份应用数据：{0}？"},
    {UiTextKey::BackupFailed, "Backup failed", "备份失败"},
    {UiTextKey::RestoreFailed, "Restore failed", "恢复失败"},
    {UiTextKey::WebUiMyNetwork, "my Network", "我的网络"},
    {UiTextKey::WebUiApMode, "AP mode", "AP 模式"},
    {UiTextKey::PressSelectToStop, "press Sel to stop", "按选择键停止"},
    {UiTextKey::Options, "Options", "选项"},
    {UiTextKey::OtaInstall, "OTA Install", "OTA 安装"},
    {UiTextKey::DownloadToSd, "Download->SD", "下载到 SD 卡"},
    {UiTextKey::AddToFavorite, "Add to Favorite", "添加到收藏"},
    {UiTextKey::BackToList, "Back to List", "返回列表"},
    {UiTextKey::PreviousPage, "[Previous Page]", "[上一页]"},
    {UiTextKey::NextPage, "[Next Page]", "[下一页]"},
    {UiTextKey::RefineSearch, "[Refine Search]", "[筛选搜索]"},
    {UiTextKey::UpdateAll, "[Update all]", "[全部更新]"},
    {UiTextKey::OrderByDownloads, "Order by downloads", "按下载量排序"},
    {UiTextKey::OrderByName, "Order by name", "按名称排序"},
    {UiTextKey::OrderByLatest, "Order by latest", "按最新排序"},
    {UiTextKey::StarredOnly, "Starred Only", "仅显示收藏"},
    {UiTextKey::TextSearch, "Text Search", "文本搜索"},
    {UiTextKey::BackToMenu, "Back to Menu", "返回菜单"},
    {UiTextKey::PageUp, "-- Page Up --", "-- 上一页 --"},
    {UiTextKey::PageDown, "-- Page Down --", "-- 下一页 --"},
    {UiTextKey::UsbMsc, "-= USB MSC =-", "-= USB 存储 =-"},
    {UiTextKey::Loading, "Loading...", "正在加载..."},
    {UiTextKey::Preparing, "Preparing...", "正在准备..."},
    {UiTextKey::Updating, "Updating...", "正在更新..."},
    {UiTextKey::UploadComplete, "Upload Complete", "上传完成"},
    {UiTextKey::FileSaved, "File saved!", "文件已保存！"},
    {UiTextKey::NvsSaved, "NVS saved!", "NVS 已保存！"},
    {UiTextKey::Unknown, "Unknown", "未知"},
};

constexpr UiLegacyTranslation kLegacyTranslations[] = {
    {"Canceled", "已取消"},
    {"-= Launcher WebUI =-", "-= 启动器 WebUI =-"},
    {"Usr: ", "用户名："},
    {"Pwd: ", "密码："},
    // Application and backup management
    {"App Name:", "应用名称："},
    {"App not found", "应用不存在"},
    {"App renamed", "应用已重命名"},
    {"Backed up", "已备份"},
    {"No backup", "无备份"},
    {"Backing up ", "正在备份 "},
    {"Backup Data partition", "备份数据分区"},
    {"Backup Data", "备份数据"},
    {"Backup data for ", "备份应用数据："},
    {"Backup failed", "备份失败"},
    {"Backup failed: ", "备份失败："},
    {"Backup failed: no RAM", "备份失败：内存不足"},
    {"Backup saved!", "备份已保存！"},
    {"Backup saved", "备份已保存"},
    {"Boot clear failed", "清除启动项失败"},
    {"Boot set failed", "设置启动项失败"},
    {"Clearing boot", "正在清除启动项"},
    {"Compact failed", "压缩失败"},
    {"Data restored", "数据已恢复"},
    {"Delete ", "删除 "},
    {"Erase failed", "擦除失败"},
    {"Invalid table", "分区表无效"},
    {"Launch ", "启动 "},
    {"Move failed", "移动失败"},
    {"No apps found", "未找到应用"},
    {"Optimizing flash", "正在优化闪存"},
    {"Overwrite current data?", "覆盖当前数据？"},
    {"Partition read failed", "读取分区失败"},
    {"Remove Without Backup", "不备份并移除"},
    {"Removing firmware", "正在移除固件"},
    {"Rename App", "重命名应用"},
    {"Rename failed", "重命名失败"},
    {"Restart needed", "需要重启"},
    {"Restore Last Data", "恢复上次数据"},
    {"Restore failed", "恢复失败"},
    {"Restore failed: ", "恢复失败："},
    {"Restore failed: no RAM", "恢复失败：内存不足"},
    {"Restore", "恢复"},
    {"Write failed", "写入失败"},
    {"Writing table", "正在写入分区表"},
    {"Restoring ", "正在恢复 "},
    {"Installed", "已安装"},
    {" [Backed up]", " [已备份]"},
    {" [No backup]", " [无备份]"},

    // SD card and installer menus
    {"Cannot copy Folder", "无法复制文件夹"},
    {"Couldn't create folder", "无法创建文件夹"},
    {"SD not found or not formatted in FAT32", "未找到 SD 卡，或未使用 FAT32 格式化"},
    {"Fail open root", "无法打开根目录"},
    {"Press a key to bind...", "请按键进行绑定..."},
    {"Key reserved for navigation", "该按键已用于导航"},
    {" bound", " 已绑定"},
    {"Open Folder", "打开文件夹"},
    {"New Folder", "新建文件夹"},
    {"Rename", "重命名"},
    {"Delete", "删除"},
    {"Main Menu", "主菜单"},
    {"Back Folder", "返回上级文件夹"},
    {"Paste", "粘贴"},
    {"Install", "安装"},
    {"Copy", "复制"},
    {"Bind to key", "绑定按键"},
    {"Restore Data", "恢复数据"},
    {"Fresh Install", "全新安装"},
    {"Previous backup found. Restore?", "找到以前的备份。是否恢复？"},
    {"SPIFFS No", "SPIFFS 否"},
    {"SPIFFS Yes", "SPIFFS 是"},
    {"Complete", "完成"},
    {"Update Error.", "更新错误。"},
    {"Updating partition", "正在更新分区"},
    {"Setting boot", "正在设置启动项"},
    {"Table failed", "分区表操作失败"},
    {"Boot failed", "设置启动失败"},
    {"No install space", "没有足够的安装空间"},
    {"Invalid app image", "应用镜像无效"},
    {"Invalid link", "链接无效"},
    {"Fail creating file.", "创建文件失败。"},
    {"Fail creating file", "创建文件失败"},
    {"SDCard Not Found", "未找到 SD 卡"},
    {"Can't create: ", "无法创建："},
    {"Can't open file", "无法打开文件"},

    // Partition manager
    {"Confirm", "确认"},
    {"Details", "详情"},
    {"Associate to Bin", "关联到 Bin"},
    {"Backup", "备份"},
    {"Restore data", "恢复数据"},
    {"Edit Size", "调整大小"},
    {"Remove", "移除"},
    {"Format", "格式化"},
    {"Add OTA", "添加 OTA"},
    {"Add FAT", "添加 FAT"},
    {"Add SPIFFS", "添加 SPIFFS"},
    {"* Partition Scheme", "* 分区方案"},
    {"* = protected", "* = 受保护"},
    {"Apply Changes", "应用更改"},
    {"Discard Changes", "放弃更改"},
    {"Wipe Flash memory", "擦除闪存"},
    {"Attach to a file", "关联到文件"},
    {"No usable range", "没有可用范围"},
    {"Invalid partition", "分区无效"},
    {"Protected partition", "分区受保护"},
    {"Apply changes first", "请先应用更改"},
    {"Cannot format", "无法格式化"},
    {"Formatting...", "正在格式化..."},
    {"No space in range", "范围内空间不足"},
    {"No free range", "没有空闲范围"},
    {"No OTA slot", "没有可用 OTA 分区"},
    {"Create failed", "创建失败"},
    {"Read failed", "读取失败"},
    {"Clearing App registry", "正在清除应用注册表"},
    {"Registry clear failed", "清除注册表失败"},
    {"Writing table", "正在写入分区表"},
    {"Reload failed", "重新加载失败"},
    {"Backup failed", "备份失败"},
    {"Backup saved!", "备份已保存！"},
    {"Backing up", "正在备份"},
    {"Complete!", "完成！"},
    {"Restored!", "已恢复！"},
    {"Updating...", "正在更新..."},
    {"Launcher Update", "启动器更新"},
    {"Use M5Burner!", "请使用 M5Burner！"},
    {"Updating table", "正在更新分区表"},
    {"Partition fix failed", "修复分区失败"},
    {"Can't open target", "无法打开目标"},
    {"Can't create target", "无法创建目标"},
    {"No memory", "内存不足"},
    {"Can't reopen target", "无法重新打开目标"},
    {"Can't open source", "无法打开源文件"},
    {"Linked to ", "已关联到 "},

    // Online installer and network states
    {"Wrong Password", "密码错误"},
    {"Retry", "重试"},
    {"Scanning...", "正在扫描..."},
    {"WiFi scan failed", "WiFi 扫描失败"},
    {"ESP-Hosted unavailable: no WiFi", "ESP-Hosted 不可用：没有 WiFi"},
    {"OTA List", "OTA 列表"},
    {"Favorite List", "收藏列表"},
    {"Check for Updates", "检查更新"},
    {"View firmware", "查看固件"},
    {"Remove Favorite", "移除收藏"},
    {"Firmware list fetch Failed", "获取固件列表失败"},
    {"Version fetch Failed", "获取版本失败"},
    {"Install info failed", "获取安装信息失败"},
    {"Bad install info", "安装信息无效"},
    {"Size failed", "获取大小失败"},
    {"Bad app offset", "应用偏移无效"},
    {"Invalid app size", "应用大小无效"},
    {"JSON Parse Failed: ", "JSON 解析失败："},
    {"Writing table", "正在写入分区表"},
    {"Restarting", "正在重启"},
    {"WiFi not connected", "WiFi 未连接"},
    {"GET failed (", "GET 失败 ("},
    {"WiFi lost during fetch", "获取过程中 WiFi 断开"},
    {"Server unreachable", "无法连接服务器"},
    {"No downloads found", "未找到下载"},
    {"Checking updates...", "正在检查更新..."},
    {"Update check failed", "检查更新失败"},
    {"Bad server response", "服务器响应无效"},
    {"No updates found", "没有可用更新"},
    {"Download FAILED", "下载失败"},
    {" Downloaded ", " 已下载 "},
    {"Padding..", "正在填充..."},
    {"Firmware..", "固件..."},
    {"Data..", "数据..."},
    {"Bootloader..", "引导程序..."},
    {"Partitions..", "分区表..."},
    {"Preparing..", "正在准备..."},
    {"Getting file info", "正在获取文件信息"},
    {"Connecting FW", "正在连接固件"},
    {"Connecting FAT", "正在连接 FAT"},
    {"Installing FAT", "正在安装 FAT"},
    {"Partition not found", "找不到分区"},
    {"WebUI Update Fail: ", "WebUI 更新失败："},
    {"WebUI unavailable with ESP-AT WiFi", "ESP-AT WiFi 不支持 WebUI"},
    {"Restart your Device", "请重启设备"},
    {"Mounting...", "正在挂载..."},
    {"SD card not found.", "未找到 SD 卡。"},
    {"by: ", "作者："},
    {"v: ", "版本："},
    {"from: ", "来源："},
    {"Launcher Touch Calibration", "启动器触摸校准"},
    {"Touch the screen corners", "触摸屏幕四角"},
    {"indicated by the arrows", "按箭头指示操作"},
    {"Confirm/Exit", "确认/退出"},
    {"[Prev/Next move]", "[上一项/下一项移动]"},
    {"[Sel ok]", "[选择确认]"},
    {"[Esc cancel]", "[返回取消]"},
    {"Getting info from", "正在获取信息："},
    {"Search Firmware", "搜索固件"},
    {"> Back", "> 返回"},
    {"[Main Menu]", "[主菜单]"},
    {"[ ] Starred Only", "[ ] 仅显示收藏"},
    {"[x] Starred Only", "[x] 仅显示收藏"},
    {"Back to list", "返回列表"},
    {"Hidden SSID", "隐藏 SSID"},
    {"Your SSID", "您的 SSID"},
    {"Network Password:", "网络密码："},
    {"Connecting to: ", "正在连接："},
    {"Aborted", "已中止"},
    {"Bad Argument", "参数错误"},
    {"Bad Size Given", "提供的大小错误"},
    {"Could Not Activate The Firmware", "无法激活固件"},
    {"Flash Erase Failed", "擦除闪存失败"},
    {"Flash Read Failed", "读取闪存失败"},
    {"Flash Write Failed", "写入闪存失败"},
    {"No Error", "无错误"},
    {"Not Enough Space", "空间不足"},
    {"Partition Could Not be Found", "找不到分区"},
    {"Stream Read Timeout", "流读取超时"},
    {"UNKNOWN", "未知错误"},
    {"Wrong Magic Byte", "Magic Byte 错误"},
    {"HTTP transport error ", "HTTP 传输错误 "},
    {"HTTP status ", "HTTP 状态 "},
    {"Download incomplete (", "下载不完整 ("},
    {"Unknown failure", "未知失败"},

    // Headless serial console responses.  Command names, status prefixes and
    // machine-readable fields remain English; only the human-readable body is
    // translated by the serial-console adapter.
    {"Press the button to enter the Launcher!", "按键进入启动器！"},
    {"Type 'help' for Serial commands.", "输入“help”查看串口命令。"},
    {"Scanning networks...", "正在扫描网络..."},
    {"Target: ", "目标："},
    {" Network: ", " 网络："},
    {"Connecting to ", "正在连接 "},
    {"Network matches the SSID, starting connection", "网络匹配 SSID，开始连接"},
    {"Couldn't find SD Card and SSID Saved,", "未找到 SD 卡和已保存的 SSID，"},
    {"you can configure it on the WEB Ui,", "你可以在 Web 界面中配置，"},
    {"Starting the Launcher in Access point mode", "正在以接入点模式启动启动器"},
    {"Connect into the following network", "请连接到以下网络"},
    {"with no other network (mobile data off and unplug wired connections)",
     "请断开其他网络（关闭移动数据并拔掉有线连接）"},
    {"Welcome to Launcher, an ESP32 firmware where you can have", "欢迎使用启动器，这是一个让你更好控制 ESP32 固件的启动器。"},
    {"a better control on what you are running on it.", "更好地控制设备上运行的内容。"},
    {"Now it will Start a web interface, where you can flash a new", "现在将启动 Web 界面，你可以在其中刷入新的"},
    {"firmware on a dedicated partition, and swap it whenever you", "固件到专用分区，并随时切换"},
    {"want using this Launcher.", "使用此启动器。"},
    {"Usage: ", "用法："},
    {"usage: ", "用法："},
    {"  <offset>/<size>: decimal or 0x-prefixed hex", "  <offset>/<size>：十进制或 0x 前缀十六进制"},
    {"  <type>:    app | data", "  <type>：    app | data"},
    {"  <subtype>: ota                       (type=app)", "  <subtype>：ota                       (type=app)"},
    {"             fat | spiffs | littlefs   (type=data)", "             fat | spiffs | littlefs   (type=data)"},
    {"  <size>: decimal or 0x-prefixed hex", "  <size>：十进制或 0x 前缀十六进制"},
    {"unknown nav target", "未知导航目标"},
    {"rebooting", "正在重启"},
    {"== Partition table ==", "== 分区表 =="},
    {"cannot delete the Launcher partition", "不能删除启动器分区"},
    {"partition deleted", "分区已删除"},
    {"all OTA/data partitions deleted", "所有 OTA/数据分区已删除"},
    {"partition edited", "分区已修改"},
    {"unknown partition type", "未知分区类型"},
    {"unknown partition subtype", "未知分区子类型"},
    {"partition created at offset=", "分区已创建，偏移量="},
    {"unknown partition subcommand", "未知分区子命令"},
    {"flash failed: ", "闪存写入失败："},
    {"flashed, rebooting", "刷写完成，正在重启"},
    {"== WiFi networks ==", "== WiFi 网络 =="},
    {"scan failed", "扫描失败"},
    {"no known network found", "未找到已知网络"},
    {"unknown SSID, password required", "未知 SSID，需要密码"},
    {"wrong password", "密码错误"},
    {"connect failed", "连接失败"},
    {"connected to ", "已连接到 "},
    {"disconnect failed", "断开连接失败"},
    {"disconnected", "已断开连接"},
    {"failed to save network", "保存网络失败"},
    {"saved ", "已保存 "},
    {"SSID not found", "未找到 SSID"},
    {"removed ", "已移除 "},
    {"failed to clear networks", "清除网络失败"},
    {"hosted guard cleared, reboot to probe again", "Hosted 守护已清除，请重启后重新探测"},
    {"unknown wifi subcommand", "未知 WiFi 子命令"},
    {"no calibration saved", "未保存校准数据"},
    {"invalid calibration values", "校准值无效"},
    {"calibration saved", "校准已保存"},
    {"axis must be X or Y", "轴必须是 X 或 Y"},
    {"failed to save calibration", "保存校准失败"},
    {"Starting calibration..", "正在开始校准..."},
    {"unknown calibrate subcommand", "未知校准子命令"},
    {"Commands:", "命令："},
    {"unknown command, type 'help' for command list", "未知命令，请输入“help”查看命令列表"},
};

#if defined(LOCALIZATION_HOST_TEST)
String hostLastDrawText;
int hostLastDrawX = 0;
#endif

const UiTranslation *findTranslation(UiTextKey key) {
    for (const UiTranslation &entry : kTranslations) {
        if (entry.key == key) return &entry;
    }
    return nullptr;
}

const UiTranslation *findTranslation(const String &source) {
    for (const UiTranslation &entry : kTranslations) {
        if (source == entry.english) return &entry;
    }
    return nullptr;
}

String replaceToken(String value, const char *token, const String &replacement) {
    const int tokenLength = strlen(token);
    int at = value.indexOf(token);
    while (at >= 0) {
        value = value.substring(0, at) + replacement + value.substring(at + tokenLength);
        at = value.indexOf(token, at + replacement.length());
    }
    return value;
}

int glyphWidth(uint32_t codepoint, uint8_t textSize) {
    if (codepoint == '\t') return 4 * kUiAsciiGlyphWidth * textSize;
    if (codepoint < 0x80) return kUiAsciiGlyphWidth * textSize;
    return kUiWideGlyphWidth * textSize;
}

bool isPrefixBoundary(const String &source, size_t prefixLength) {
    if (prefixLength >= static_cast<size_t>(source.length())) return true;
    const uint8_t last = static_cast<uint8_t>(source.c_str()[prefixLength - 1]);
    const bool prefixEndsInWord =
        (last >= '0' && last <= '9') || (last >= 'A' && last <= 'Z') ||
        (last >= 'a' && last <= 'z') || last == '_';
    if (!prefixEndsInWord) return true;
    const uint8_t next = static_cast<uint8_t>(source.c_str()[prefixLength]);
    return !((next >= '0' && next <= '9') || (next >= 'A' && next <= 'Z') ||
             (next >= 'a' && next <= 'z') || next == '_');
}

#if !defined(LOCALIZATION_HOST_TEST)
const UiBitmapGlyph *findBitmapGlyph(uint32_t codepoint) {
    if (codepoint > 0xFFFFU) return nullptr;
    size_t first = 0;
    size_t last = kUiBitmapGlyphCount;
    while (first < last) {
        const size_t middle = first + (last - first) / 2U;
        const uint32_t candidate = kUiBitmapGlyphs[middle].codepoint;
        if (candidate == codepoint) return &kUiBitmapGlyphs[middle];
        if (candidate < codepoint) first = middle + 1U;
        else last = middle;
    }
    return nullptr;
}

void drawMissingGlyph(uint32_t codepoint, int x, int y, uint8_t textSize) {
    // Keep unsupported text visibly distinct from a missing draw call.  The
    // shipped UI strings are all in the real bitmap table above.
    (void)codepoint;
    const int cell = textSize ? textSize : 1;
    const int width = kUiWideGlyphWidth * cell;
    const uint16_t color = tft->getTextcolor();
    for (int row = 0; row < kUiFontCellHeight; ++row) {
        int runStart = -1;
        for (int col = 0; col <= kUiWideGlyphWidth; ++col) {
            const bool edge =
                row == 0 || row == kUiFontCellHeight - 1 || col == 0 || col == kUiWideGlyphWidth - 1;
            const bool diagonal = row == col || row + col == kUiWideGlyphWidth - 1;
            const bool on = col < kUiWideGlyphWidth && (edge || (diagonal && row > 2 && row < 9));
            if (on && runStart < 0) runStart = col;
            if ((!on || col == kUiWideGlyphWidth) && runStart >= 0) {
                tft->fillRect(
                    x + runStart * cell,
                    y + row * cell,
                    (col - runStart) * cell,
                    cell,
                    color
                );
                runStart = -1;
            }
        }
    }
    tft->setCursor(x + width, y);
}

void drawPackedGlyph(
    const uint8_t *bitmap, int glyphWidth, int glyphHeight, int x, int y, uint8_t textSize
) {
    const int cell = textSize ? textSize : 1;
    const uint16_t color = tft->getTextcolor();
    for (int row = 0; row < glyphHeight; ++row) {
        int runStart = -1;
        for (int col = 0; col <= glyphWidth; ++col) {
            const int bit = row * glyphWidth + col;
            const bool on = col < glyphWidth && (bitmap[bit / 8] & (1U << (7 - (bit % 8)))) != 0;
            if (on && runStart < 0) runStart = col;
            if ((!on || col == glyphWidth) && runStart >= 0) {
                tft->fillRect(
                    x + runStart * cell,
                    y + row * cell,
                    (col - runStart) * cell,
                    cell,
                    color
                );
                runStart = -1;
            }
        }
    }
    tft->setCursor(x + glyphWidth * cell, y);
}

void drawBitmapGlyph(const UiBitmapGlyph &glyph, int x, int y, uint8_t textSize) {
    drawPackedGlyph(
        glyph.bitmap, kUiWideGlyphWidth, kUiFontCellHeight, x, y, textSize
    );
}
#endif

} // namespace

String uiText(UiTextKey key) {
    const UiTranslation *entry = findTranslation(key);
    if (!entry) return "";
    return entry->simplifiedChinese;
}

String uiTranslate(const String &source) {
    const UiTranslation *entry = findTranslation(source);
    if (entry) return entry->simplifiedChinese;

    for (const UiLegacyTranslation &legacy : kLegacyTranslations) {
        if (source == legacy.english) return legacy.simplifiedChinese;
    }

    // Keep parameterized legacy messages localizable without forcing every
    // caller to assemble a temporary format key.  Prefer the longest prefix so
    // entries such as "Back to List" win over the shorter "Back" entry.
    const UiTranslation *prefix = nullptr;
    size_t prefixLength = 0;
    for (const UiTranslation &candidate : kTranslations) {
        const size_t length = strlen(candidate.english);
        if (length > prefixLength && length < static_cast<size_t>(source.length()) &&
            source.startsWith(candidate.english) && isPrefixBoundary(source, length)) {
            prefix = &candidate;
            prefixLength = length;
        }
    }
    const UiLegacyTranslation *legacyPrefix = nullptr;
    for (const UiLegacyTranslation &candidate : kLegacyTranslations) {
        const size_t length = strlen(candidate.english);
        if (length > prefixLength && length < static_cast<size_t>(source.length()) &&
            source.startsWith(candidate.english) && isPrefixBoundary(source, length)) {
            legacyPrefix = &candidate;
            prefix = nullptr;
            prefixLength = length;
        }
    }
    if (!prefix && !legacyPrefix) return source;
    const char *translated = prefix ? prefix->simplifiedChinese : legacyPrefix->simplifiedChinese;
    return String(translated) + source.substring(prefixLength);
}

String uiTranslateSerialLine(const String &source) {
    if (source.isEmpty()) return source;

    auto translateRecord = [](const String &record) {
        size_t indentLength = 0;
        while (indentLength < static_cast<size_t>(record.length()) &&
               (record.c_str()[indentLength] == ' ' || record.c_str()[indentLength] == '\t')) {
            indentLength++;
        }
        const String indent = record.substring(0, indentLength);
        String body = record.substring(indentLength);
        String marker;
        const char *markers[] = {"ERR ", "WARN ", "OK ", "READY ", "ACK "};
        for (const char *candidate : markers) {
            if (body.startsWith(candidate)) {
                marker = candidate;
                body = body.substring(strlen(candidate));
                break;
            }
        }
        // These records are consumed by raw flashing clients. Keep their
        // complete payload byte-for-byte stable, including numeric fields.
        if (marker == "READY " || marker == "ACK ") return record;
        if (marker.isEmpty()) {
            const String directTranslation = uiTranslate(record);
            if (directTranslation != record) return directTranslation;
        }
        String translated = indent + marker;
        translated += uiTranslate(body);
        return translated;
    };

    String result;
    size_t start = 0;
    const size_t length = static_cast<size_t>(source.length());
    while (start < length) {
        const int newline = source.indexOf("\n", start);
        if (newline < 0) {
            result += translateRecord(source.substring(start));
            break;
        }
        result += translateRecord(source.substring(start, static_cast<size_t>(newline)));
        result += "\n";
        start = static_cast<size_t>(newline) + 1U;
    }
    return result;
}

String uiFormat(UiTextKey key, const String &arg0, const String &arg1) {
    String value = uiText(key);
    value = replaceToken(value, "{0}", arg0);
    value = replaceToken(value, "{1}", arg1);
    return value;
}

bool uiDecodeUtf8(const char *text, size_t length, size_t &offset, uint32_t &codepoint) {
    if (!text || offset >= length) return false;
    const uint8_t first = static_cast<uint8_t>(text[offset++]);
    if (first < 0x80) {
        codepoint = first;
        return true;
    }
    int continuation = 0;
    uint32_t value = 0;
    if ((first & 0xE0) == 0xC0) {
        continuation = 1;
        value = first & 0x1F;
        if (value == 0) continuation = -1; // overlong
    } else if ((first & 0xF0) == 0xE0) {
        continuation = 2;
        value = first & 0x0F;
    } else if ((first & 0xF8) == 0xF0) {
        continuation = 3;
        value = first & 0x07;
    } else {
        codepoint = 0xFFFD;
        return true;
    }
    if (continuation < 0 || offset + static_cast<size_t>(continuation) > length) {
        codepoint = 0xFFFD;
        return true;
    }
    for (int i = 0; i < continuation; ++i) {
        const uint8_t next = static_cast<uint8_t>(text[offset]);
        if ((next & 0xC0) != 0x80) {
            codepoint = 0xFFFD;
            return true;
        }
        value = (value << 6) | (next & 0x3F);
        offset++;
    }
    if (value > 0x10FFFF || (value >= 0xD800 && value <= 0xDFFF) ||
        (value < 0x80 && continuation > 0) || (value < 0x800 && continuation > 1) ||
        (value < 0x10000 && continuation > 2)) {
        codepoint = 0xFFFD;
        return true;
    }
    codepoint = value;
    return true;
}

int uiTextWidth(const String &text, uint8_t textSize) {
    if (textSize == 0) textSize = 1;
    int width = 0;
    size_t offset = 0;
    uint32_t codepoint = 0;
    while (uiDecodeUtf8(text.c_str(), text.length(), offset, codepoint)) {
        if (codepoint == '\n') continue;
        width += glyphWidth(codepoint, textSize);
    }
    return width;
}

int uiTextLineHeight(const String &text, uint8_t textSize) {
    (void)text;
    if (textSize == 0) textSize = 1;
    return kUiFontCellHeight * textSize;
}

String uiClipText(const String &text, int maxWidth, uint8_t textSize) {
    if (maxWidth <= 0) return "";
    String result;
    size_t offset = 0;
    uint32_t codepoint = 0;
    int width = 0;
    while (offset < static_cast<size_t>(text.length())) {
        const size_t start = offset;
        if (!uiDecodeUtf8(text.c_str(), text.length(), offset, codepoint)) break;
        const int nextWidth = glyphWidth(codepoint, textSize);
        if (codepoint != '\n' && width + nextWidth > maxWidth) break;
        result += text.substring(start, offset);
        width += codepoint == '\n' ? 0 : nextWidth;
    }
    return result;
}

std::vector<String> uiWrapText(const String &text, int maxWidth, uint8_t textSize) {
    std::vector<String> lines;
    if (maxWidth <= 0) {
        lines.push_back("");
        return lines;
    }
    String line;
    int lineWidth = 0;
    size_t offset = 0;
    while (offset < static_cast<size_t>(text.length())) {
        const size_t start = offset;
        uint32_t codepoint = 0;
        if (!uiDecodeUtf8(text.c_str(), text.length(), offset, codepoint)) break;
        if (codepoint == '\n') {
            lines.push_back(line);
            line = "";
            lineWidth = 0;
            continue;
        }
        const int width = glyphWidth(codepoint, textSize);
        if (lineWidth > 0 && lineWidth + width > maxWidth) {
            lines.push_back(line);
            line = "";
            lineWidth = 0;
        }
        line += text.substring(start, offset);
        lineWidth += width;
    }
    if (!line.isEmpty() || lines.empty()) lines.push_back(line);
    return lines;
}

#if defined(LOCALIZATION_HOST_TEST)
int uiTestLastDrawX() { return hostLastDrawX; }

String uiTestLastDrawText() { return hostLastDrawText; }

void uiDrawText(const String &text, int x, int y, uint8_t textSize) {
    (void)y;
    (void)textSize;
    hostLastDrawText = text;
    hostLastDrawX = x;
}
#else
void uiDrawText(const String &text, int x, int y, uint8_t textSize) {
    if (textSize == 0) textSize = 1;
    tft->setTextSize(textSize);
    tft->setCursor(x, y);
    String ascii;
    size_t offset = 0;
    while (offset < static_cast<size_t>(text.length())) {
        const size_t start = offset;
        uint32_t codepoint = 0;
        if (!uiDecodeUtf8(text.c_str(), text.length(), offset, codepoint)) break;
        if (codepoint < 0x80) {
            ascii += text.substring(start, offset);
            continue;
        }
        if (!ascii.isEmpty()) {
            tft->print(ascii);
            ascii = "";
        }
        const UiBitmapGlyph *glyph = findBitmapGlyph(codepoint);
        if (glyph) drawBitmapGlyph(*glyph, tft->getCursorX(), tft->getCursorY(), textSize);
        else drawMissingGlyph(codepoint, tft->getCursorX(), tft->getCursorY(), textSize);
    }
    if (!ascii.isEmpty()) tft->print(ascii);
}
#endif

void uiDrawCentreText(const String &text, int x, int y, uint8_t textSize) {
    const int width = uiTextWidth(text, textSize);
    uiDrawText(text, x - width / 2, y, textSize);
}

void uiDrawRightText(const String &text, int x, int y, uint8_t textSize) {
    uiDrawText(text, x - uiTextWidth(text, textSize), y, textSize);
}
