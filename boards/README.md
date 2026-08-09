# 板卡配置

下面说明如何为新的 ESP32/M5Stack 板卡添加 Launcher 支持。目录名、文件名、
编译命令和宏名保持英文，便于直接复制使用。

```
.
├── platformio.ini
├── boards
    ├── _JsonFiles
    │   └── [board].json
    ├── [board]
    │   ├── interface.cpp
    |   └── [board].ini
    ├── pinouts
    │   ├── pins_arduino.h
    │   └── [board].h
    └── Readme.md
    
...
```

# 文件
（将 `[board]` 替换为实际板卡名称。）

## boards/pinouts/pins_arduino.h
在此添加用于包含板卡引脚定义头文件的宏。

## boards/pinouts/\[board].h
在此放置板卡宏和引脚定义，可参考其他板卡的写法。
官方示例及本项目采用的格式如下：
https://github.com/espressif/arduino-esp32/blob/master/variants/esp32s3/pins_arduino.h

## boards/\[board]/interface.cpp
在此放置板卡专属的初始化代码。

## boards/_JsonFiles/\[board].json
这是板卡配置文件，可参考其他板卡的写法。
官方示例及本项目使用的格式如下：
https://github.com/platformio/platform-espressif32/blob/master/boards/esp32-s3-devkitc-1.json

## boards/\[board]/\[board].ini
这是设备的 PlatformIO 配置文件，可参考其他板卡的写法。
