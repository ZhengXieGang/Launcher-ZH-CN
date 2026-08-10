# Launcher
适用于 M5Stack、Lilygo、CYD、Marauder 及其他 ESP32 设备的应用启动器。

首版界面支持简体中文（默认）和 English。设备与 WebUI 共用 NVS 中的
`launcher/language` 设置；首次启动、缺少设置或设置无效时自动使用 `zh-CN`。
无屏设备通过串口交互时，控制台返回的说明文字默认使用简体中文；可输入
`language en` 切换英文。命令关键字、`OK`/`ERR`/`READY`/`ACK` 状态前缀及协议字段保持英文，
以保证脚本和旧版命令兼容。有屏设备的历史调试日志仍保持英文。
有屏设备内置覆盖固件界面文案的 12x12 简体中文位图字库；未收录的外部动态字符会显示替代符号。


<p align="center" width="100%">
    <img src="https://github.com/bmorcelli/Launcher/blob/main/M5Launcher.png?raw=true"> <img src="https://github.com/bmorcelli/Launcher/blob/main/New Launcher.jpg?raw=true" width="240" height="135"> <img src="https://github.com/bmorcelli/Launcher/blob/main/Launcher_anim.webp?raw=true" width="auto" height="135">
</p>

Join our [Discord community](https://discord.gg/BE9by2a2FF)

## 安装
* 使用 [Launcher Flasher](https://bmorcelli.github.io/Launcher/)。
* 使用 M5Burner。
* 从 Releases 下载对应设备的 `.bin`，使用 https://web.esphome.io/ 或 esptool.py
  将 `Launcher-{YourDevice}.bin` 写入设备。

## 使用方法
* 打开设备。
* 在启动画面按 M5/Sel（Enter）进入 Launcher。
* 选择 OTA，从在线服务（M5Burner 或 GitHub 链接）安装新的二进制文件。
* 安装完成后再次开机，如果不按键，设备会自动启动已安装的程序。

## SD 卡无法使用
* 确认 SD 卡是 SDHC（不是 SDXC）。
* 容量建议不超过 32GB（8GB 或 16GB 通常更稳定）。
* 使用 FAT32 格式，可用 [Rufus](https://rufus.ie/) 格式化。
* 分区方案应为 MBR，而不是 GPT。

## Launcher 提供的功能
<details>
  <summary><h3>OTA - OTA 更新</h3></summary>

 - 从在线仓库（M5Burner 或 GitHub 链接）安装二进制文件，无需 USB 线。
 - 在 WUI 中启动 WebUI，使用电脑或手机上的二进制文件安装。
 - 从 SD 卡安装二进制文件。

</details>
<details>
  <summary><h3>SD - SD 卡管理</h3></summary>
* 新建文件夹。
* 删除文件和文件夹。
* 重命名文件。
* 复制和粘贴文件。
* 安装二进制文件。

</details>
<details>
  <summary><h3>WUI - Web 用户界面</h3></summary>
* 管理 SD 卡文件。
* 使用 OTA Update 选项无线安装二进制文件。
* 编辑文本文件。
* 编辑 NVS 信息（UiFlow2 数据、Launcher 设置等）。
* 从文件列表部署安装。

</details>
<details>
  <summary><h3>CFG - 配置（自定义）</h3></summary>
* 充电模式。
* 调整亮度和息屏时间。
* 更改界面颜色和屏幕方向。
* 避免/询问 SPIFFS（控制是否询问安装 SPIFFS；该功能主要供 Orca One 使用）。
* 查看全部文件或仅查看 `.bin`（默认）。
* 更改分区方案，以便安装大型应用或 UiFlow2。
* 查看分区列表、清空 FAT 分区、备份和恢复 SPIFFS。
</details>

<details>
  <summary><h3>PMan - 分区管理</h3></summary>
* 查看当前分区方案。
* 创建、删除和格式化分区。
* 备份和恢复数据分区（SPIFFS 或 FAT）。
* 调整分区大小。
</details>

<details>
  <summary><h3>提示</h3></summary>
* SD 卡不是必需品，但能带来更完整的体验。[M5StickCs SD Card Hat](https://www.thingiverse.com/thing:6459069)
* 项目原理请参阅 [Launcher Wiki](https://github.com/bmorcelli/Launcher/wiki/Explaining-the-project)。
* 不知道从哪里获取可启动二进制文件？请看[获取可启动二进制文件](https://github.com/bmorcelli/Launcher/wiki/Obtaining-binaries-to-launch)。
* 也可以从[这里](https://bmorcelli.github.io/Launcher/catalog.html)下载二进制文件。
</details>

## 已知问题
* UiFlow 1 与 Launcher 不兼容。它使用旧版 MicroPython 和旧版 ESP-IDF，依赖的内部配置目前无法可靠解析。

## 待办事项
后续版本计划：

* [ ] LVGL UI (?)
* [ ] 迁移到 ESP-IDF Platform
* [ ] 优化设置功能以节省 Flash
* [ ] 优化存储功能以节省 Flash

## 最新更新日志
* 2.8.1:
     * [x] 移除 `phy_init` 分区，并将 NVS 增大到 0x5000

     * [x] Port to [T-Display P4](https://lilygo.cc/products/t-display-p4?bg_ref=sDI8Bh4HmO)
     * [x] Port to [T-Display C5](https://lilygo.cc/products/t-display-c5?bg_ref=sDI8Bh4HmO)
* 2.8.0:
     * [x] 移植到 Xueersi-XiaoMiao。
     * [x] Lilygo T-Watch-Ultra 支持 OTA 安装。
     * [x] **键盘设备快捷键系统**：可将二进制文件绑定到按键，从主菜单一键安装。
     * [x] **键盘和触摸设备快速启动**：启动画面按键或触摸即可快速进入已安装固件。
     * [x] **新增串口接口**：在串口输入 "help" 查看命令；可配置 Wifi、校准触摸屏、镜像 X/Y 轴或交换 XY 轴。例如："wifi add MyNetworkSSID MyN37w0rkPWD"。
     * [x] **无屏串口中文交互**：输入 `language` 查看当前语言，输入 `language zh-CN` 或 `language en` 可立即切换并保存到 NVS；命令关键字和协议状态前缀保持英文。
     * [x] **已下载固件更新列表**：Launcher 会读取 `{dwn_path}/downloaded.json`，检查下载固件的新版本，并可通过 `[Update All]` 将新文件下载到 SDCard。
     * [x] **多段二进制下载**：LauncherHub 上的 `bootloader.bin`、`partitions.bin`、`firmware.bin` 和 `data.bin` 会在运行时合并为一个可从 SDCard 刷写的文件。
     * [x] **新的数据分区备份系统**：在 `/bkp/backupData.json` 保存备份与二进制文件的关系，重新安装时自动恢复；应用图标和 PMan 会显示备份状态。此功能需要 SD Card。
     * [x] **WebUI** 显示分区信息并支持分区管理。
     * [x] **支持 M5 CardKB2、CardKB 1.1 和 Tab5 键盘**，并为使用 Grove I2C Port A 的 StickC、StickCPlus 1.1、StickCPlus2、StickS3、Tab5、CoreS3、Core2 和 Core 增加支持，感谢 @cddigi。
     * [x] 修复 TSL 1.3 网络上的未释放流量并完善错误处理，感谢 @anton-vinogradov。
     * [x] 数据分区使用分区表中的标签创建，并兼容需要更多 SPIFFS 空间的 xiaozhi-esp32，感谢 @QQSHI13。
     * [x] 固件包含有效数据分区时按原样复制；空分区至少创建为 0x70000 (448kb)，超过阈值时填满剩余 Flash。
     * [x] 完整复制标签为 "sys"/"system" 的 FAT 分区，并正确复制、调整其他 FAT 或 LittleFS 分区，避免重新格式化，兼容 UiFlow、Tactility 等固件。
     * [x] 启动器关机时，电子纸显示屏显示 "Powered Off"。
     * [x] 优化 RAM，减少 Heap 碎片。
     * [x] 修复 M5Stack PaperS3 触摸屏，见 https://github.com/bmorcelli/Launcher/issues/338。
     * [x] 修复 WebUI OTA 安装。
     * [x] 在重置配置和 WiFi 凭据时增加 "dev" 选项。

* 2.7.2:
     * [x] 调整启动逻辑，恢复原有行为。
     * [x] 修复共享 TFT 和 Touch SPI 总线的设备（如 NM-CYD-C5）无法从 SD Card 安装固件的问题。
     * [x] 修复共享 TFT 与 SD Card 的设备无法通过 OTA 下载固件的问题。

* 2.7.1:
     * [x] 修复 Launcher 自动更新流程。

* 2.7.0:
     * [x] 改进五键设备和键盘设备的导航，可在主菜单上下移动。
     * [x] 改进小屏幕（T-Dongle、StickC）的主菜单。
     * [x] 自定义分区管理器 "PMan"，Cardputer 不再使用硬编码分区。
     * [x] 增加自动分区、固件检查和 Flash 优化。
     * [x] 支持一次安装多个固件。
     * [x] 加密 `config.conf` 和 NVS 中的 WiFi 密码。
     * [x] 重做 WebUI，支持编辑文本文件和内存中的 NVS 字段。
     * [x] 调整 CFG 项目名称，降低理解成本。
     * [x] 优化 WiFi/WebUI 功能以节省 Flash。
     * [x] 为 CYD-3248S035C 和 CYD-3248S035R 启用 OTA。
     * [x] 移植到 [M5-DinMeter](https://shop.m5stack.com/products/m5stack-din-meter-w-m5stamps3?ref=Pirata)。
     * [x] 移植到 [Arduino Nesso N1](https://docs.arduino.cc/hardware/nesso-n1)。
     * [x] 移植到 [Reaper Board](https://www.elecrow.com/bruce-pcb-rf-reaper.html)。

<details>
  <summary><h2>历史更新日志</h2></summary>

* 2.6.10:
     * [x] 修复三键设备按 Next 或 Prev 时误触发 EscPress 的导航问题。

* 2.6.9:
     * [X] 移植到 [NM-CYD-C5](https://www.nmminer.com/product/nm-cyd-c5/)。
     * [x] 移植到 [3248W535C](https://www.displaysmodule.com/sale-51335661-jc3248w535c-i-y-lcd-display-module-with-320-480-pixel-resolution-and-effective-display-area-73-4-49-.html)。
     * [x] 移植到 [Waveshare-ESP32-S3-LCD-1.47](https://www.waveshare.com/wiki/ESP32-S3-LCD-1.47)。
     * [x] 移植到 [T-Dongle-C5 (tft)](https://lilygo.cc/products/t-dongle-c5?bg_ref=sDI8Bh4HmO)。
     * [x] 移植到 [T-Display S3 AMOLED Plus](https://lilygo.cc/products/t-display-s3-amoled-plus)。
     * [x] 修复亮度无法保存。
     * [x] 修复未使用自定义 "downloads" 文件夹。
     * [x] 修复固件名称含禁用字符导致下载失败。
     * [x] 修复 T-Watch Ultra 无法挂载 SD 卡，并调整主菜单和文件列表的圆角界面。
     * [x] 为 Lilygo T-LoraPager、T-Deck、T-Deck Plus 和 T-Deck Pro 启用 WASD 导航。
     * [x] 为 XPT2046 设备（CYD、Marauder、Phantom、T-HMI 等电阻触摸屏）增加触摸校准；首次启动没有校准数据时会提示，也可从 `CFG > Calibrate Touch` 或串口发送 "calibrate" 启动。
     * [x] 主界面增加 "OFF" 选项；没有 PMIC 时使用 DeepSleep 关机。
     * [x] 使用 git submodule 集中管理主库，避免在 `.pio/libdeps/**/` 中下载重复库。
     * [x] 使用 GitHub 缓存加快框架和库的构建。

* 2.6.8:
     * [x] 增大 Game Station 分区，见 https://github.com/bmorcelli/Launcher/issues/299。
     * [x] 增加擦除应用分区的选项。
     * [x] 增加始终启动 Launcher 的选项，见 https://github.com/bmorcelli/Launcher/issues/292。
     * [x] 主界面增加 "APP" 项，可重启到最近安装的固件。
     * [x] 增强 UiFlow2 的 NVS 分区和分区方案。
     * [x] 修复 M5Stack Tab5 WiFi 扫描及 AP 模式 WebUI。
     * [x] 新设备：[Lilygo T-Watch-S3](https://lilygo.cc/products/t-watch-s3?bg_ref=sDI8Bh4HmO)。
     * [x] 新设备：[Lilygo T-Watch-Ultra](https://lilygo.cc/products/t-watch-ultra?bg_ref=sDI8Bh4HmO)。
     * [x] 新设备：[Lilygo E-Paper S3 Pro H752-x](https://lilygo.cc/products/t5-e-paper-s3-pro?bg_ref=sDI8Bh4HmO)。


* 2.6.7:
     * [x] 为兼容 WiFi，将 Tab5 SD 卡恢复到 SPI，并重构重启流程，通过断电重置 SD 卡通信总线。
     * [x] Tab5 现在支持 Mass Storage 接口。
     * [x] 修复 M5Stack Paper S3 USB Mass Storage 问题，见 https://github.com/bmorcelli/Launcher/issues/287；OTA 只显示 S3 固件。
     * [x] 增加应用偏移参数，允许更新 Tab5 上的 Launcher，也支持位于不同 factory/app0 地址的固件。
     * [x] StickC 和 CPlus 设备的 OTA 只显示 ESP32 固件，排除 ESP32-S3（StickS3）固件。
     * [x] 为未合并固件补充分区表，使其可以附加 SPIFFS 分区。该文件仅适用于 Launcher，因没有有效 bootloader 和分区表，不能单独刷写，见 https://github.com/bmorcelli/Launcher/issues/289。

* 2.6.6:
     * [x] 移植到 [M5-StickS3](https://shop.m5stack.com/products/m5sticks3-esp32s3-mini-iot-dev-kit?ref=Pirata)。
     * [ ] （Beta）移植到 [M5-DinMeter](https://shop.m5stack.com/products/m5stack-din-meter-w-m5stamps3?ref=Pirata)。
     * [x] 移植到 [Arduino Nesso N1](https://docs.arduino.cc/hardware/nesso-n1)。

* 2.6.5:
     * [x] M5-Tab5 使用 SDMMC 驱动，兼容其他固件。
     * [x] 增加按 "Latest update" 排序。
     * [x] 移植到 OpenSourceSRDLabs [WaveSentry 和 WaveSentry Pro](https://opensourcesdrlab.com/products/aifw-wavesentry-esp32?VariantsId=10331)。
     * [x] 修复 Cardputer、Tdeck、StickCPlus2、T-Display S3、T-HMI 的电池 ADC 测量。

* 2.6.4:
     * [x] 修复 CYD 3243S035R 触摸屏旋转。
     * [x] 修复 Marauder V7 屏幕问题。
     * [x] 增强 M5-PaperS3 显示，使用 Sprites 提高绘制分辨率。
     * [x] 修复 M5Stack Cardputer ADV 键盘无法输入 `*` 和 `(`。
     * [x] 为 [Cardputer Game Station](https://github.com/geo-tp/Cardputer-Game-Station-Emulators/) 增加分区方案，支持 4.5MB 游戏 ROM。
     * [ ] 移植到 [M5-Paper](https://shop.m5stack.com/products/m5paper-esp32-development-kit-v1-1-960x540-4-7-eink-display-235-ppi?ref=Pirata)。
     * [ ] 移植到 [Arduino Nesso N1](https://docs.arduino.cc/hardware/nesso-n1)，目前尚未构建。

* 2.6.3:
     * [x] 修复 Marauder 键盘。
     * [x] 从 EEPROM 改为 NVS 保存配置和 WiFi 凭据，见 [Issue 232](https://github.com/bmorcelli/Launcher/issues/232)。
     * [x] 移植到 [M5-PaperS3](https://shop.m5stack.com/products/m5papers3-esp32s3-development-kit?ref=Pirata)。
     * [x] 修复 SelPress 泄漏到主菜单。
     * [x] 增强全部 T-Embed 和 T-LoraPager 编码器。
     * [x] 改进并修复 WebUI 会话。


* 2.6.2:
     * [x] 修复 T-Embed CC1101 OTA 链接。
     * [x] 加速 SD 文件列表，见 [PR 230](https://github.com/bmorcelli/Launcher/pull/230) 和 [Issue 229](https://github.com/bmorcelli/Launcher/issues/229)，感谢 @geo-tp 和 @emericklaw。

* 2.6.1:
     * [x] 修复 T-Deck Plus 触摸屏（增加新环境）。
     * [x] 修复 M5Stack CoreS3 无法挂载 SD 卡。
     * [x] 增加从收藏中删除的选项。

* 2.6.0:
     * [x] 使用新的 API，从 M5Burner API 获取设备列表并统计下载量。
     * [x] OTA 分页（每页 100 个固件，默认按下载量排序）。
     * [x] 新设备：[M5Stack Tab5](https://shop.m5stack.com/products/m5stack-tab5-iot-development-kit-esp32-p4?ref=Pirata)。
     * [x] 新设备：[Lilygo T-HMI](https://www.lilygo.cc/products/t-hmi?bg_ref=sDI8Bh4HmO)。
     * [x] 新功能：备份 SPIFFS/FAT 时可将数据合并到指定二进制；安装时选择 `SPIFFS Yes` 即可同时安装固件和数据，备份文件使用递增名称。
     * [x] 新功能：固件列表支持筛选和排序。
     * [x] 新功能：增加 *Starred* 固件列表（由维护者管理，欢迎支持项目并提交固件）。
     * [x] 新功能：增加 "Favorite"（需要 SD 卡），可收藏 OTA 列表固件或手动添加本地服务器/其他位置的二进制链接。
     * [x] `config.conf` 变化：
```
...
    "favorite": [
      { // Example of firmware added into Favorites through OTA function
        "name": "Evil-Cardputer-7h30th3r0n3",
        "fid": "2128851a0c98a4c1d15ac1a327b49812",
        "link": ""
      },
      { // Example of my custom link file added by manually editing this file
        "name": "Launcher Beta link",
        "fid": "", // leave it blank
        "link": "https://github.com/bmorcelli/Launcher/releases/download/beta/Launcher-m5stack-cardputer.bin"
      },
      {
        "name": "Bruce Beta link",
        "fid": "",
        "link": "https://github.com/pr3y/Bruce/releases/download/betaRelease/Bruce-m5stack-cardputer.bin"
      },
    ],
    "c0:4e:30:13:8d:f4": 1, // Rotation is now bound to hardware MAC
...

```

* 2.5.3:
     * [x] 恢复 T-Deck OTA。
     * [x] 改进 T-Deck 触摸输入。

* 2.5.2:
     * [x] 修复 Marauder V6 和 CYD 触摸屏无响应及息屏问题，见 [issue](https://github.com/bmorcelli/Launcher/issues/210)。
     * [x] 修复 Marauder Mini 和 V7 屏幕调光。
     * [x] 修复 Smoochiee 板卡输入和 SD 卡，见 [issue](https://github.com/bmorcelli/Launcher/issues/209)。
     * [x] 修复 Cardputer ADV 长按。
     * [x] 修复子文件夹创建。

* 2.5.1:
     * [x] 修复 Cardputer ADV 键盘兼容性。
     * [x] 修复 OTA 固件列表未完整下载。

* 2.5.0:
     * [x] 迁移到基于 pioarduino 3.3 的框架（ESP-IDF 5.5）。
          * [x] 为 SD_MMC 设备启用 USB Mass Storage（T-Display-S3 touch 和 T-Dongle S3 tft）。
          * [x] 调整分区。
          * [x] 更新固件流程。
          * [x] 更新 OTA 列表和安装。
     * [x] 为 T-Deck Pro 增加键盘支持，见 https://github.com/bmorcelli/Launcher/issues/180。
     * [x] 修复 UIFlow 2.3.x 兼容性，见 https://github.com/bmorcelli/Launcher/issues/192。
     * [x] 增加 CSS、JS、HTML 在线压缩器。
     * [x] 迁移到 ESP32Async/ESPAsyncWebServer 官方仓库。
     * [x] 移植到 [Cardputer ADV](https://shop.m5stack.com/products/m5stack-cardputer-adv-version-esp32-s3?ref=Pirata)，感谢 [@n0xa](https://github.com/n0xa)。
     * [x] 移植到 [Lilygo Lora Pager](https://lilygo.cc/products/t-lora-pager)，作者 @emericklaw。
     * [x] 移植到 [CYD-4827S043R](https://github.com/bmorcelli/Launcher/issues/186)，状态 WIP。
     * [x] 修复 [filelist](https://github.com/bmorcelli/Launcher/issues/166) 第一行。

* 2.4.10:
     * [x] 修复 T-Embed 屏幕。
     * [x] 修复 StickC（及 Plus）键盘导航。
     * [x] 修复 Phantom 触摸映射。

* 2.4.9:
     * [x] 修复 T-Display-S3 PRO。
     * [x] 为 Marauder Mini 启用 OTA。

* 2.4.8:
     * [x] 为 CYD 2432S028R、2-USB、S024R、W328C/R、Marauder、Awok、Phantom、Lilygo T-Embed CC1101 和 T-Deck（普通版及 Plus）启用 OTA。
     * [x] 移植到 [AWOK Mini v2](https://awokdynamics.com/products/dual-mini-v2) 和 [AWOK Touch v2](https://awokdynamics.com/products/dual-touch-v2)。
     * [x] 移植到 [RabbitLabs Phantom](https://rabbit-labs.com/product/the-phantom-by-rabbit-labs/?v=dc634e207282)。
     * [x] 移植到 [8048S043C、8048W550C](https://github.com/bmorcelli/Launcher/issues/108)。
     * [x] 移植到 Lilygo T-Deck Pro（电子纸显示）。
     * [x] 改进触摸设备的文件列表和菜单响应。
     * [x] 新主菜单，所有项目均可触摸。
     * [x] 修复 [Marauder v4、v6、v7、mini](https://github.com/bmorcelli/Launcher/issues/146) 移植。
     * [x] 修复 [2432s032C 触摸屏错位](https://github.com/bmorcelli/Launcher/issues/149)。

* 2.4.7:
     * [x] WebUI 支持通过拖放或文件/文件夹选择器批量上传，并支持文件夹上传和排序。
     * [x] 修复 StickC 黑屏。
     * [x] 移植到 [T-Dongle-S3 (tft)](https://lilygo.cc/products/t-dongle-s3?srsltid=AfmBOopwCcPQTTC4wTNi3rNZHn8W6g8Yo_ShcrfDiAfECS6tGq59vWo7)。
     * [x] 移植到 [T-Display-S3](https://lilygo.cc/products/t-display-s3?variant=42284559827125)。
* 2.4.6:
     * [x] 支持 UiFlow2 v2.2.3，并恢复 StickCPlus2 兼容性。
     * [x] 拆分 WebUI 文件。
     * [x] ESP32S3 设备支持 USB Interface 管理 SD 文件（ESP32 不支持）。
     * [x] 使用 gzip 压缩 WebUI。
     * [x] 移植到 CYD-3248S035C 和 CYD-3248S035R，见 https://github.com/bmorcelli/Launcher/issues/125。
     * [x] 修复接口多次点击跳过项目，见 https://github.com/bmorcelli/Launcher/issues/127、https://github.com/bmorcelli/Launcher/issues/126 和 [comment](https://github.com/bmorcelli/Launcher/issues/125#issuecomment-2705628306)。
     * [x] 修复 StickCPlus 键盘颜色。
     * [x] 修复 OTA 返回列表（多列表时会继续增强）。
     * [x] （回滚）OTA 使用 http 下载/更新以减少 Flash 占用。
* 2.4.5:
     * [x] 移植到 CYD-2432S024R（https://github.com/bmorcelli/Launcher/issues/99）、CYD-2432W328R、CYD-2432S022C（https://github.com/bmorcelli/Launcher/issues/112）、CYD-2432S032C 和 CYD-2432S032R。
     * [x] 修复 Marauder V4-OG。
     * [x] 电池不可用或为 0% 时不再显示电量。
     * [x] 修复 Headless 16Mb 环境，见 https://github.com/bmorcelli/Launcher/issues/121 和 https://github.com/bmorcelli/Launcher/issues/120。
     * [x] 使用 ArduinoGFX 作为主图形库，同时支持 TFT_eSPI 和 LovyanGFX。
* 2.4.4:
     * [x] 为非 M5Stack 设备关闭 OTA 菜单（主要为 CYD 和 Marauder 节省 Flash），并创建新的分区方案。
     * [x] 修复 T-Embed CC1101 电池数值。

* 2.4.3:
     * [x] 修复 Core 设备按键。
     * [x] 修复屏幕调光时随机重启。
     * [x] 移植到 Lilygo E-Paper S3 Pro（目前仅 Pro）。
     * [x] 修复 T-Embed 从 deepSleep 返回。

* 2.4.2:
     * [x] Cardputer 兼容 UiFlow2 v2.2.0，见 https://github.com/bmorcelli/Launcher/issues/92；StickCPlus2 因存储空间不足暂不支持。
     * [x] 修复 https://github.com/bmorcelli/Launcher/issues/93、https://github.com/bmorcelli/Launcher/issues/97 和 https://github.com/bmorcelli/Launcher/issues/95。
     * [x] 支持输入 SSID 和 Pwd 连接隐藏网络，见 https://github.com/bmorcelli/Launcher/issues/89。
     * [x] 改为后台任务读取输入（与 Bruce 相同）。
     * [x] 增强键盘。
     * [x] 为大于 200x200px 的屏幕（如 CYD、Core）增加竖屏旋转。

* 2.4.1:
     * [x] 修复 T-Deck SD 卡（关闭 LoRa 芯片并将 CS 置 HIGH 以避免冲突），见 https://github.com/bmorcelli/Launcher/issues/86。
     * [x] 移植 Lilygo T-Display-S3-Pro，见 https://github.com/bmorcelli/Launcher/issues/73。

* 2.4.0:
     * [x] 移植 CYD-2432W328C，见 https://github.com/bmorcelli/Launcher/issues/80。
     * [x] 支持滚动显示过长 SSID 和文件名。
     * [x] 输错 WiFi 密码或进入其他菜单后增加返回路径（键盘本身暂不支持退出），见 https://github.com/bmorcelli/Launcher/issues/82 和 https://github.com/bmorcelli/Launcher/issues/81。
     * [x] 修复方向设置未保存到 SD 卡，见 https://github.com/bmorcelli/Launcher/issues/84。
     * [x] 息屏功能现在会关闭屏幕。
     * [x] 项目更名为 "Launcher"，并在启动动画加入作者昵称。
     * [x] 调整接口代码，为后续移植做准备，见 https://github.com/bmorcelli/Launcher/issues/83。
* 2.3.2:
     * [x] 修复 T-Embed CC1101 电源芯片管理。
* 2.3.1:
     * [x] 修复 https://github.com/bmorcelli/Launcher/issues/77。
     * [x] 修复 T-Deck 设备屏幕方向。
     * [x] 修复 Json 处理和 config.conf 随机失败。
* 2.3.0:
     * [x] 移植到 Lilygo T-Embed CC1101。
     * [x] 移植到 Lilygo T-Embed。
     * [x] 移植到 Lilygo T-Deck。
     * [x] 增加 ESP32 和 ESP32-S3 无屏版本。
     * [x] StickC 的 Power Btn 和 Prev Btn 在菜单中作为向上操作，长按退出菜单。
* 2.2.5:
     * [x] 调整框架以移除所有 Watchdog Timer，并修复 SD 相关问题，见 https://github.com/bmorcelli/Launcher/issues/61 和 https://github.com/bmorcelli/Launcher/issues/63。
     * [x] StickC 和 Cardputer 的 Grove 引脚置 LOW，避免连接 RF433T 时受到 433Mhz 干扰。
* 2.2.4:
     * [x] 完成 CoreS3 和 CoreS3-SE 移植。
     * [x] WebUI 增加 watchdog 重置，并在加载文件时检查可用内存以避免崩溃。
* 2.2.3:
     * [x] StickC、Plus 和 Plus2 启动时不再将 Power Btn 用于跳过逻辑。
     * [x] 调整 EEPROM 地址，避免与新版 Bruce 和其他固件冲突。
* 2.2.2:
     * [x] 移植到 [CYD-2432S028R](https://www.amazon.com/dp/B0BVFXR313) 和 [CYD-2-Usb](https://www.amazon.com/dp/B0CLR7MQ91)。
     * [x] 下载结束后检查并删除失败的文件。
* 2.2.1:
     * [x] 移植到 [Lilygo T-Display S3 Touch](https://www.lilygo.cc/products/t-display-s3?variant=42351558590645)。
     * [x] 修复 JSON 读写。
* 2.2.0:
     * [x] M5Launcher 2.2+ 支持 OTA 或 SD 卡更新。
     * [x] 增加 UI 颜色设置（可在 `/config.conf` 中自定义）。
     * [x] 减少 SD 文件导航闪烁。
     * [x] 修复固件名称包含 "/" 时无法下载。
     * [x] 下载文件名附加固件版本。
     * [x] 增加 Dim time，空闲时降低亮度和 CPU 频率。
     * [x] 设置中增加 "Charge Mode"，将 CPU 降至 80MHz、亮度降至 5%，见 https://github.com/bmorcelli/Launcher/issues/40。
     * [x] 修复下载进度条，见 https://github.com/bmorcelli/Launcher/issues/41。
     * [x] 修改下载默认文件夹（在 `/config.conf` 中手动设置），见 https://github.com/bmorcelli/Launcher/issues/15。
     * [x] 保存更多 SSID 和密码，并自动连接已知网络（config.conf），见 https://github.com/bmorcelli/Launcher/issues/30。
     * [x] 使用定制框架略微提高 WiFi 下载/OTA 速度。
* 2.1.2:
     * [x] 修复 OTA 错误提示。
     * [x] 增大 Options Menu 宽度并减少闪烁。
* 2.1.1:
     * [x] 修复 UIFlow 兼容性。
     * [x] 修复 SD 卡问题。
     * [x] 小幅修复，见 https://github.com/bmorcelli/Launcher/issues/37。
* 2.1.0:
     * [x] 支持 Core Fire（所有 16Mb Core 设备）和 Core2。
     * [x] SPIFFS 更新可选（默认关闭，配置在 config.conf）。
     * [x] Core 设备取消 Sprites（无 PSRAM，无法处理大 Sprites），见 https://github.com/bmorcelli/Launcher/issues/34。
     * [x] 让 Core 设备键盘可与触摸捕获协同工作。
     * [x] 主界面增加专用 WebUI 按键，见 https://github.com/bmorcelli/Launcher/issues/22。
     * [x] WebUI 支持多文件上传，见 https://github.com/bmorcelli/Launcher/issues/28。
     * [x] 更新 FAT VFS 分区以兼容 UIFlow2，见 https://github.com/bmorcelli/Launcher/issues/29。
     * [x] 增加分区切换器，使 Cardputer 和 StickC 可运行 DOOM 与 UIFlow。
     * [x] 修复文件数量限制，见 https://github.com/bmorcelli/Launcher/issues/33。
     * [x] 支持备份和恢复 FAT/SPIFFS 文件系统；使用 UIFlow 时可保存草图，并在重装 UIFlow、MicroHydra 或 CircuitPython 后恢复。
* 2.0.1:
     * 修复 UIFlow 安装，见 https://github.com/bmorcelli/Launcher/issues/20。
     * 修复 WebUI 创建文件夹，见 https://github.com/bmorcelli/Launcher/issues/18。
     * 修复部分情况下 WebUI 无法打开，见 https://github.com/bmorcelli/Launcher/issues/16。
     * M5Launcher 现在会格式化 FAT VFS 分区；使用 MicroPython、UIFlow 或 MicroHydra 前请先将数据保存到 SD 卡，见 https://github.com/bmorcelli/Launcher/issues/19。
* 2.0.0:
     * SD：支持创建文件夹、删除和重命名文件/文件夹，以及复制和粘贴文件。
     * OTA（Over-The-Air update）：列出 M5Burner 中的程序并从网络安装。
     * WebUI：支持管理 SD 卡并无线安装二进制文件。
     * 其他小幅功能改进。
     *
* 1.3.0:
     * 支持基于 MicroPython 的二进制文件（MicroHydra）；Cardputer 和 StickCPlus2 使用 1MB FAT 分区，StickC 和 Plus1.1 使用 64KB。
* 1.2.1:
     * 重启前降低 LCD 功率并将屏幕填黑，避免运行不使用屏幕的应用时烧屏。
     * 修复 M5StickC 的显示内容和位置。
* 1.2.0:
     * 移除不需要的 ota_data.bin。
     * 移除 StartApp 应用。
     * 从 .csv 文件移除不需要的 OTA_1 分区。
     * 将空闲空间重新分配到 "SPIFFS" 分区，为改进和 OrcaOne 等应用留出空间。
     * 增加带电池监视的 Bootscreen。
     * Launcher 增加 Restart 选项和电池监视。
     * 为 M5StickC 增加自动方向。
     * Launcher 不再创建 .bak 文件！
     * 改进 .bin 文件处理，提示文件过大、无效等错误。

* 1.1.3:
     * 修复菜单偶尔隐藏文件和文件夹。
* 1.1.2:
     * 调整 Magic number，兼容部分应用（Volos Watch）。
* 1.1.1:
     * 将 Cardputer 和 M5StickCPlus2 的 OTA_0 分区从 3MB 增大到 6MB。
     * ~~增加识别 MicroPython 二进制并避免裁切损坏的校验（这些应用仍不能工作，需要继续处理……）~~
* 1.1.0:
     * 修复 M5Launcher 无法在 Cardputer 启动应用的问题。
* 1.0.1:
     * 修复 Cardputer 黑屏和键盘捕获。
</details>
