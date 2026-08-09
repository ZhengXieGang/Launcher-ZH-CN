# Launcher WebUI 开发服务器

这是一个 Node.js 开发后端，用于在没有 ESP32 硬件时测试 WebUI。设备与开发服务器
共享 `launcher/language` 语言设置，默认值为 `zh-CN`，也支持 `en`。

## 要求

- Node.js 16 或更高版本
- 不需要额外依赖

## 使用

```bash
node server.js <SD 卡根目录>
```

`<SD 卡根目录>` 会被当作设备 SD 卡。文件列表、下载、上传和删除操作都限制在此目录内。

示例：

```bash
node server.js C:\Users\bmorc\Downloads
node server.js D:\testes\sdcard
```

也可以从 `backend/` 目录通过 npm 启动：

```bash
npm start -- C:\Users\bmorc\Downloads
```

可通过环境变量设置端口和凭据：

```bash
PORT=3000 WUI_USR=admin WUI_PWD=minhasenha node server.js C:\pasta
```

启动后打开 `http://localhost:8080`。默认登录名为 `admin`，默认密码为 `admin`。

## 已实现的端点

| 端点 | 方法 | 行为 |
|---|---|---|
| `/language` | GET/POST | 读取或更新 `zh-CN`/`en` 语言设置（POST 需要登录） |
| `/ping` | GET | 返回 `launcher-pong` |
| `/login` | POST | 验证凭据并创建会话 Cookie |
| `/logout` | GET | 结束会话并重定向 |
| `/systeminfo` | GET | 返回模拟版本和 SD 卡统计 |
| `/listfiles?folder=` | GET | 列出真实目录 |
| `/file?name=&action=` | GET | 下载、删除或创建文件夹 |
| `/editfile?name=` | GET / POST | 读取或保存文本文件 |
| `/` | POST | 上传文件（multipart） |
| `/rename` | POST | 重命名文件或文件夹 |
| `/nvs` | GET / POST | 读取或保存 `nvs_mock.json` 中的 NVS 数据 |
| `/partitions` | GET | 返回当前分区表（包含待应用编辑） |
| `/partitions?list=backups&label=` | GET | 列出指定分区的模拟备份 |
| `/partitions` | POST | `action=resize\|create\|delete\|format\|apply\|discard\|backup\|restore` |
| `/wifi` | GET | 模拟 WiFi 配置 |
| `/sdpins` | GET | 模拟 SD 引脚配置 |
| `/reboot` | GET | 模拟重启 |
| `/OTA?update=1` | GET | 进入模拟更新模式并清除 OTA 上下文 |
| `/OTA` | POST | 校验 `command`、`size` 和 `manifest`，准备分段安装 |
| `/OTAFILE` | POST | 接收完整二进制并模拟按 manifest 顺序写入 |
| `/UPDATE` | POST | 模拟 SD 卡更新 |

## OTA 模拟流程

后端复现固件端的 OTA 流程：

1. `GET /OTA?update=1`
2. `POST /OTA`，提交 `command=0`、`size` 和 `manifest`
3. `POST /OTAFILE`，提交完整二进制文件

提交 `manifest` 时，服务器会：

- 校验每个分段的范围；
- 要求恰好存在一个 `kind=app` 分段；
- 按 `sourceOffset` 排序；
- 模拟将上传文件中的对应范围写入设备。

没有 `manifest` 时，保留旧版兼容流程。

## NVS

语言值保存在 `launcher/language`。缺失或非法值会回退到 `zh-CN`；`launcher/token`
不会暴露，也不允许编辑，与固件行为一致。其余示例数据保存在同目录的
`nvs_mock.json`，会跨服务器重启保留。

## 模拟分区管理（PMan）

该实现参考 `src/partition_table_model.cpp` 和 `src/partitioner.cpp`，用于驱动完整的
WebUI 测试流程：

- 已写入的分区表保存在 `partitions_mock.json`，首次运行会创建包含 `factory`、`app1`、
  `app2` 及其数据分区的示例表；
- `resize`、`create`、`delete` 只修改内存中的待处理表，`action=apply` 才写回文件，
  `action=discard` 放弃更改；
- 有待处理更改时不能 `format`；备份和恢复只生成并记录模拟路径，不复制真实数据；
- 正在运行的 `factory`/`test`、系统分区（如 `nvs`、`otadata`）按固件规则受保护。

## 安全边界

所有文件操作都限制在启动参数指定的根目录内，路径穿越请求会被拒绝。

HTTP 路径、JSON 字段、NVS 键和表单操作名保持英文，以便同一套浏览器测试流程同时
验证 mock 后端和真实设备。
