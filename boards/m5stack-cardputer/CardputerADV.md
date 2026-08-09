# M5Stack Cardputer ADV 支持

本文说明 Launcher 固件对 M5Stack Cardputer ADV 的支持。Cardputer ADV 使用与原版
Cardputer 不同的键盘控制器，因此需要专用的硬件适配。

## 硬件差异

### 原版 Cardputer 与 Cardputer ADV

| 组件 | 原版 Cardputer | Cardputer ADV |
|-----------|-------------------|---------------|
| 键盘控制器 | 直接 GPIO 矩阵 | TCA8418 I2C 控制器 |
| I2C 地址 | 不适用 | 0x34 |
| SDA 引脚 | GPIO13 | GPIO8 |
| SCL 引脚 | GPIO15 | GPIO9 |
| 中断引脚 | 不适用 | GPIO11 |

### TCA8418 配置

- **I2C 地址**：0x34
- **矩阵大小**：7 行 × 8 列
- **通信方式**：仅轮询 I2C
- **按键检测**：轮询间隔 100ms

## 按键映射

### 导航按键

| 功能 | 按键 | 矩阵位置 | 键码 | 说明 |
|----------|-----|----------------|---------|-------|
| 上一项 | ↑ 或 ← | Row=3, Col=9 或 Row=3, Col=6 | 0x39 或 0x36 | 两个方向键均可 |
| 下一项 | ↓ 或 → | Row=3, Col=10 或 Row=4, Col=0 | 0x3A 或 0x40 | 两个方向键均可 |
| 确认/选择 | Enter | Row=4, Col=3 | 0x43 | 主选择键 |
| 返回/取消 | Esc | Row=0, Col=1 | 0x01 | 返回或取消 |

### Cardputer ADV 导航

| 功能 | 按键 |
|----------|-------------------|
| **上一项** | `,`（←）或 `;`（↑） |
| **下一项** | `/`（→）或 `.`（↓） |
| **选择** | Enter 或 GPIO0 |
| **返回** | `` ` `` 或 Backspace |

### 检测到的其他 I2C 设备

- **0x18**：可能是加速度计/IMU
- **0x34**：TCA8418 键盘控制器
- **0x69**：可能是其他传感器

## 实现细节

### 修改的文件

```
boards/m5stack-cardputer-adv/
├── platformio.ini          # ADV 专用构建配置
└── interface.cpp           # TCA8418 键盘实现
```

### 构建配置

**platformio.ini** 新增：
```ini
-DCARDPUTER_ADV=1
-DTCA8418_INT_PIN=11
-DTCA8418_I2C_ADDR=0x34
-DTCA8418_SDA_PIN=8
-DTCA8418_SCL_PIN=9
```

**依赖：**
```ini
adafruit/Adafruit TCA8418 @ ^1.0.1
```

### 主要实现函数

1. **_setup_gpio()**：为 SD 卡兼容性将 GPIO5 置为 HIGH。
2. **_post_setup_gpio()**：初始化 TCA8418 的 I2C 通信。

## 故障排查

### 原始问题

- **现象**：显示“Using config.conf setup file”后设备不断重启。
- **原因**：原版 GPIO 键盘初始化方式与 ADV 硬件不兼容。
- **解决**：条件编译 ADV 版本的 TCA8418 初始化逻辑。

### SD 卡挂载问题

- **现象**：由于额外的 I2C 设备冲突，SD 卡无法挂载。
- **原因**：GPIO5（SPI CS）受到 TCA8418 和其他传感器干扰。
- **解决**：GPIO 初始化时将 GPIO5 设为 HIGH，确保 SD 卡片选保持空闲。

### I2C 通信

- **总线扫描**：自动检测可用 I2C 设备。
- **多地址回退**：尝试常见的 TCA8418 地址。
- **引脚检测**：尝试多组 I2C 引脚组合。

## 构建说明

### 前置条件

- 已安装 PlatformIO
- M5Stack Cardputer ADV 硬件
- 用于编程的 USB 线

### 编译

- 在 `platformio.ini` 中启用 `m5stack-cardputer-adv`。
- 注释掉不使用的其他板卡。

```bash
cd Launcher
pio run -e m5stack-cardputer-adv
```

### 上传

1. 某些设备需要进入引导模式（按住 GPIO0 并按复位）。
2. 上传固件：

```bash
pio run -e m5stack-cardputer-adv -t upload --upload-port /dev/ttyACM0
```

### 串口监控

```bash
pio device monitor --port /dev/ttyACM0 --baud 115200
```

## 调试输出

### 初始化成功

```text
DEBUG: Cardputer ADV - Initializing TCA8418 keyboard
DEBUG: Initializing I2C with SDA=8, SCL=9
DEBUG: Scanning I2C bus...
DEBUG: Found I2C device at address 0x18
DEBUG: Found I2C device at address 0x34
DEBUG: Found I2C device at address 0x69
DEBUG: Found 3 I2C devices
DEBUG: Attempting to initialize TCA8418 at address 0x34
DEBUG: TCA8418 found and initialized successfully!
```

### 按键事件

```text
DEBUG: Polling found key event (interrupt not working)
TCA8418 Key Event (polled): Row=3, Col=10, PRESSED (keycode=0x3A)
MAPPED: Down/Next pressed
```

以上调试输出属于有屏设备的历史串口调试日志，保持英文。无屏构建通过串口控制台交互时，
说明文字默认使用简体中文；命令关键字、协议状态前缀和字段仍保持英文。

## 性能特征

- **按键响应时间**：约 100ms（轮询间隔）
- **内存使用**：RAM 25.3%，Flash 27.5%
- **I2C 通信**：标准速率（100kHz）下稳定
- **功耗**：与原版 Cardputer 相近

## 后续改进

1. 支持按字母跳转。

### 已知限制

1. **仅轮询**：轮询间隔为 100ms（硬件未连接中断引脚）。
2. **按键映射有限**：当前只映射导航按键。
3. **不支持组合键**：尚未实现修饰键。

## 验证测试

### 已通过的功能测试

- ✅ 设备启动后不会进入重启循环
- ✅ TCA8418 检测和初始化
- ✅ I2C 通信稳定
- ✅ 按键检测正常
- ✅ 导航键映射正常
- ✅ Launcher 菜单导航正常
- ✅ SD 卡挂载和文件系统访问
- ✅ 键盘导航期间不会误进入省电
- ✅ Launcher 功能均可访问

### 硬件兼容性

- ✅ M5Stack Cardputer ADV
- ✅ ESP32-S3 处理器
- ✅ 8MB Flash 使用
- ✅ 与其他传感器共享 I2C 总线

## 支持信息

### 调试命令

```bash
# 仅构建
pio run -e m5stack-cardputer-adv

# 引导模式上传
pio run -e m5stack-cardputer-adv -t upload --upload-port /dev/ttyACM0

# 串口监控
pio device monitor --port /dev/ttyACM0 --baud 115200

# 清理构建
pio run -e m5stack-cardputer-adv -t clean
```

### 配置文件

- **主配置**：`platformio.ini`（默认环境已禁用）
- **ADV 配置**：`boards/m5stack-cardputer-adv/platformio.ini`
- **硬件接口**：`boards/m5stack-cardputer-adv/interface.cpp`

---

**作者**：n0xa
**日期**：2025-09-09
**状态**：已完成并可用
**测试硬件**：M5Stack Cardputer ADV 和 M5Stack Cardputer
