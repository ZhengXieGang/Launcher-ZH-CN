// Chinese display text keyed by the existing English UI/API strings. HTTP paths,
// JSON fields, NVS keys and protocol commands remain unchanged.
const UI_TEXT = {
        "Launcher": "启动器", "Menu": "菜单", "Config": "配置", "OTA": "OTA", "Files": "文件",
        "Partitions": "分区", "Firmware list": "固件列表", "NVS Config": "NVS 配置",
        "Save": "保存", "Close": "关闭", "Uploading": "正在上传", "Reboot": "重启", "SD Pins": "SD 引脚",
        "WiFi": "WiFi", "User/Pass": "用户名/密码", "Logout": "注销",
        "OTA Update": "OTA 更新", "Preparing...": "正在准备...", "Updating...": "正在更新...",
        "Start Update": "开始更新", "No installable partitions found in this file.": "文件中没有可安装的分区。",
        "Data partition": "数据分区", "Files": "文件", "Folder": "文件夹", "+ New Folder": "+ 新建文件夹",
        "Partition Manager": "分区管理", "Apply Changes": "应用更改", "Discard Changes": "放弃更改",
        "Unsaved changes — nothing is written to flash until you Apply.": "有未保存的更改，应用前不会写入闪存。",
        "Free Space": "可用空间", "App": "应用", "Data": "数据", "Free": "空闲", "System": "系统",
        "Details": "详情", "Resize": "调整大小", "Backup": "备份", "Restore": "恢复", "Format": "格式化",
        "Remove": "删除", "protected": "受保护", "running": "运行中", "Firmware": "固件",
        "No data partition": "没有数据分区", "Loading...": "正在加载...", "Failed to load partitions.": "加载分区失败。",
        "Upload Complete": "上传完成", "Upload Failed": "上传失败", "Upload Aborted": "上传已取消",
        "File saved!": "文件已保存！", "NVS saved!": "NVS 已保存！", "Confirm Restart?!": "确认重启？",
        "Invalid credentials.": "用户名或密码无效。", "Error loading file": "加载文件失败", "Invalid pins": "引脚无效",
        "Please, select a file.": "请选择文件。", "File is not a .bin": "文件不是 .bin 格式",
        "Start Update": "开始更新", "Installation complete, restart your device!": "安装完成，请重启设备！",
        "Invalid pins": "引脚无效", "Invalid Name": "名称无效", "Invalid Folder Name": "文件夹名称无效",
        "Invalid size": "大小无效", "Invalid choice": "选择无效", "Failed": "失败", "Failed to list backups": "列出备份失败",
        "Backup saved: ": "备份已保存：", "No backups found for \"": "找不到分区备份：\"",
        "Partition table written. The device is rebooting...": "分区表已写入，设备正在重启...",
        "Canceled": "已取消", "Used": "已用", "Total": "总计", "Name": "名称", "Size": "大小", "Folder": "文件夹",
        "+ New Folder": "+ 新建文件夹", "Enter the new name: ": "输入新名称：", "Invalid Name": "名称无效",
        "Do you really want to DELETE the file: ": "确定要删除文件：", "This action can't be undone!": "此操作无法撤销！",
        "Folder Name": "文件夹名称", "Invalid Folder Name": "文件夹名称无效"
        ,"Uploaded": "已上传", "of": "/", "files.": "个文件。", "Upload failed": "上传失败"
        ,"OTA App": "OTA 应用", "FAT": "FAT", "Partition": "分区", "Offset": "偏移量",
        "Range: ": "范围：", "Size in KB:": "大小（KB）：", "Partition label:": "分区标签：",
        "Used": "已用", "Total": "总计", "Functionality exclusive for Headless environment": "仅无屏设备支持此功能",
        "Functionality exclusive for Headless environment (devices with no screen)": "仅无屏设备（无屏幕设备）支持此功能",
        "MISO pin": "MISO 引脚", "MOSI pin": "MOSI 引脚", "SCK pin": "SCK 引脚", "CS pin": "CS 引脚",
        "Username of access Launcher": "启动器访问用户名", "Password": "密码", "SSID of your network": "网络 SSID",
        "Password of your network": "网络密码", "System (bootloader, nvs, otadata...)": "系统（引导程序、NVS、OTA 数据...）",
        "Write the new partition table and reboot the device now?": "立即写入新的分区表并重启设备？",
        "Discard all pending changes?": "放弃所有待处理的更改？",
        "Remove partition": "删除分区", "This is staged until you Apply Changes.": "应用更改前只暂存此操作。",
        "Erase all data on": "立即擦除分区", "This happens immediately and can't be undone.": "此操作立即执行且无法撤销。",
        "Choose a backup to restore:\n": "选择要恢复的备份：\n",
        "Restore": "恢复", "This overwrites the current data on the partition.": "这会覆盖分区中的当前数据。",
        "Restored": "已恢复", "from": "来源",
        "No backups found for": "找不到分区备份",
        "Label: ": "标签：", "Type: ": "类型：", "Offset: ": "偏移量：", "Size: ": "大小：", "Flags: ": "标志：", "Firmware: ": "固件：", "Data partition: ": "数据分区："
        ,"Created new folder: ": "已创建文件夹：", "Deleted : ": "已删除：", "FAIL deleting: ": "删除失败：",
        "FAIL creating folder: ": "创建文件夹失败：", "Fail renaming file.": "重命名文件失败。",
        "renamed to": "已重命名为", "Starting Update": "正在开始更新", "Fail starting SD Card.": "启动 SD 卡失败。",
        "Pins configured.": "引脚配置完成。", "Pins not configured.": "引脚未配置。", "User: ": "用户：",
        "configured with password: ": "已配置密码：", "Flash file system for ESP32. Some apps like": "ESP32 的闪存文件系统，某些应用（例如",
        " require it.": "）需要它。"
};
function t(key, fallback) {
    return Object.prototype.hasOwnProperty.call(UI_TEXT, key) ? UI_TEXT[key] : (fallback === undefined ? key : fallback);
}
function translateStatus(value) {
    if (!value) return value;
    if (Object.prototype.hasOwnProperty.call(UI_TEXT, value)) return UI_TEXT[value];
    const keys = Object.keys(UI_TEXT).sort((a, b) => b.length - a.length);
    for (const key of keys) {
        if (!value.startsWith(key)) continue;
        const next = value.charAt(key.length);
        if (next && /[0-9A-Za-z_]/.test(next)) continue;
        return UI_TEXT[key] + value.substring(key.length);
    }
    return value;
}
function applyLanguage() {
    document.documentElement.lang = 'zh-CN';
    document.querySelectorAll('[data-i18n]').forEach((node) => {
        const key = node.getAttribute('data-i18n');
        if (!node.dataset.i18nDefault) node.dataset.i18nDefault = node.textContent;
        node.textContent = t(key, node.dataset.i18nDefault);
    });
    const title = document.querySelector('title[data-i18n]');
    if (title) document.title = t(title.getAttribute('data-i18n'), title.textContent);
    document.querySelectorAll('[data-i18n-title]').forEach((node) => {
        node.title = t(node.getAttribute('data-i18n-title'), node.title);
    });
}
function translateRenderedText(root) {
    if (!root) return;
    const walker = document.createTreeWalker(root, NodeFilter.SHOW_TEXT);
    const nodes = [];
    while (walker.nextNode()) nodes.push(walker.currentNode);
    nodes.forEach((node) => { node.nodeValue = translateRenderedValue(node.nodeValue); });
    root.querySelectorAll('[title]').forEach((node) => { node.title = translateRenderedValue(node.title); });
}
function translateRenderedValue(value) {
    let result = value;
    const pairs = Object.entries(UI_TEXT);
    pairs.sort((a, b) => b[0].length - a[0].length);
    pairs.forEach(([source, translated]) => {
        if (source && source !== translated && result.includes(source)) result = result.split(source).join(translated);
    });
    return result;
}
function _(e) { return document.getElementById(e); }
function toggleMenu(){_('menu').classList.toggle('open')}
function toggleConfigOverlay(){_('configOverlay').classList.toggle('open')}
function closeConfigOverlay(event){if(event.target.id==='configOverlay')_('configOverlay').classList.remove('open')}
function closePmanResizeOverlay(event){if(event.target.id==='pmanResizeOverlay')_('pmanResizeOverlay').classList.remove('open')}
function toggleRow(b){const r=b.closest('tr').nextElementSibling;r.style.display=r.style.display==='none'?'table-row':'none'}
function refreshLocalizedSection() {
    const section = _currentSection;
    if (section === 'files') {
        listFilesButton(_('actualFolder').value || '/');
    } else if (section === 'partitions') {
        loadPartitions();
    } else if (section === 'ota') {
        _('detailsheader').innerHTML = '<h3>' + t('OTA Update') + '</h3>';
        if (_otaFile && _otaManifest) renderOtaActions(_otaFile, _otaManifest);
        else {
            translateRenderedText(_('analysisOutput'));
            translateRenderedText(_('spiffsInfo'));
        }
        translateRenderedText(_('status'));
        translateRenderedText(_('updetails'));
    }
}
const editableExts = new Set(['txt','ini','conf','c','cpp','h','hpp','js','css','htm','html','ts']);
function isEditable(name) { return editableExts.has(name.split('.').pop().toLowerCase()); }
let editingFile = '';
function editFile(path) {
    editingFile = path;
    _('editor-title').textContent = path;
    _('editor-content').value = t('Loading...');
    _('editor').style.display = 'block';
    const xhr = new XMLHttpRequest();
    xhr.open('GET', '/editfile?name=' + encodeURIComponent(path));
    xhr.onload = () => { _('editor-content').value = xhr.responseText; };
    xhr.onerror = () => { _('editor-content').value = t('Error loading file'); };
    xhr.send();
}
function saveFile() {
    const xhr = new XMLHttpRequest();
    xhr.open('POST', '/editfile?name=' + encodeURIComponent(editingFile));
    xhr.setRequestHeader('Content-Type', 'text/plain');
    xhr.onload = () => { _('status').innerHTML = xhr.responseText === 'OK' ? t('File saved!') : translateStatus(xhr.responseText); };
    xhr.send(_('editor-content').value);
}

let _nvsData = null;
const _nvsInts = new Set(['u8','i8','u16','i16','u32','i32','u64','i64']);
function _nvsIsCheckbox(f) { return f.t === 'u8' && (f.v === 0 || f.v === 1); }
function _nvsId(ns, k) { return 'nvs__' + ns + '__' + k; }
function loadNvs() {
    _('nvs').style.display = 'block';
    _('nvs-body').innerHTML = t('Loading...');
    const x = new XMLHttpRequest();
    x.open('GET', '/nvs');
    x.onload = () => {
        _nvsData = JSON.parse(x.responseText);
        const inp = 'style="width:100px;background:#303134;color:#0d0;border:1px solid #0d0;padding:2px"';
        const inps = 'style="width:220px;background:#303134;color:#0d0;border:1px solid #0d0;padding:2px"';
        let h = '';
        for (const ns in _nvsData) {
            h += '<h3 style="margin:8px 0 4px;color:#0d0">' + ns + '</h3>';
            _nvsData[ns].forEach(f => {
                const id = _nvsId(ns, f.k);
                h += '<div style="margin:4px 0"><label style="display:inline-block;width:150px;font-size:0.9em">' + f.k + ':</label>';
                if (_nvsIsCheckbox(f))
                    h += '<input type="checkbox" id="' + id + '"' + (f.v ? ' checked' : '') + '>';
                else if (_nvsInts.has(f.t))
                    h += '<input type="number" id="' + id + '" value="' + f.v + '" ' + inp + '>';
                else
                    h += '<input type="text" id="' + id + '" value="' + f.v + '" ' + inps + '>';
                h += ' <small style="color:#888">' + f.t + '</small></div>';
            });
        }
        _('nvs-body').innerHTML = h;
    };
    x.send();
}
function saveNvs() {
    const out = {};
    for (const ns in _nvsData) {
        out[ns] = _nvsData[ns].map(f => {
            const el = document.getElementById(_nvsId(ns, f.k));
            if (!el) return f;
            let v = _nvsIsCheckbox(f) ? (el.checked ? 1 : 0) : _nvsInts.has(f.t) ? parseInt(el.value) : el.value;
            return {k: f.k, t: f.t, v};
        });
    }
    const x = new XMLHttpRequest();
    x.open('POST', '/nvs');
    x.setRequestHeader('Content-Type', 'application/json');
    x.onload = () => { _('status').innerHTML = x.responseText === 'OK' ? t('NVS saved!') : translateStatus(x.responseText); _('nvs').style.display = 'none'; };
    x.send(JSON.stringify(out));
}

function httpRequest(method, url, { async = true, body, headers = {}, onload, onerror } = {}) {
    const xhr = new XMLHttpRequest();
    if (typeof onload === "function") {
        xhr.onload = () => onload(xhr);
    }
    xhr.onerror = () => {
        if (typeof onerror === "function") {
            onerror(xhr);
        } else {
            console.error("Network error or request failure.");
        }
    };
    xhr.open(method, url, async);
    Object.keys(headers).forEach((header) => xhr.setRequestHeader(header, headers[header]));
    if (body !== undefined && body !== null) {
        xhr.send(body);
    } else {
        xhr.send();
    }
    return xhr;
}

function isNullOrEmpty(value) {
    return value === null || value === "";
}

function WifiConfig(target) {
    let wifiSsid;
    let wifiPwd;
    if (target === "usr") {
        wifiSsid = prompt(t("Username of access Launcher"), "admin");
        wifiPwd = prompt(t("Password"), "launcher");
    } else if (target === "ssid") {
        wifiSsid = prompt(t("SSID of your network"), "");
        wifiPwd = prompt(t("Password of your network"), "");
    }
    if (isNullOrEmpty(wifiSsid) || wifiPwd === null) {
        window.alert(t("Invalid credentials.", "Invalid " + target + " or password"));
    } else {
        const xhr = httpRequest("GET", "/wifi?" + target + "=" + wifiSsid + "&pwd=" + wifiPwd, { async: false });
        _("status").innerHTML = translateStatus(xhr.responseText);
    }
}

function SDConfig() {
    const miso = prompt(t("MISO pin"), "");
    const mosi = prompt(t("MOSI pin"), "");
    const sck = prompt(t("SCK pin"), "");
    const cs = prompt(t("CS pin"), "");
    if ([miso, mosi, sck, cs].some(isNullOrEmpty)) {
        window.alert(t("Invalid pins"));
    } else {
        const xhr = httpRequest("GET", "/sdpins?miso=" + miso + "&mosi=" + mosi + "&sck=" + sck + "&cs=" + cs, { async: false });
        _("status").innerHTML = translateStatus(xhr.responseText);
    }
}
function startUpdate(fileName) {
    const formdata4 = new FormData();
    formdata4.append("fileName", fileName);
    httpRequest("POST", "/UPDATE", { async: false, body: formdata4 });
}
function callOTA() {
    _currentSection = 'ota';
    _otaFile = null;
    _otaManifest = null;
    const formdata = new FormData();
    formdata.append("update", 1);
    httpRequest("POST", "/OTA", { async: false, body: formdata });
    _("detailsheader").innerHTML = "<h3>" + t("OTA Update") + "</h3>";
    _("status").innerHTML = "";
    _("details").innerHTML = "";
    _("updetailsheader").innerHTML = "";
    _("updetails").innerHTML = "";
    _("OTAdetails").style.display = 'block';
    _("drop-area").style.display = 'none';
    _("fileInput").click();
}
function readLe32(bytes, offset) {
    return ((bytes[offset]) |
        (bytes[offset + 1] << 8) |
        (bytes[offset + 2] << 16) |
        (bytes[offset + 3] << 24)) >>> 0;
}
function readPartitionLabel(bytes, offset) {
    let label = '';
    for (let i = 0; i < 16; i++) {
        const value = bytes[offset + i];
        if (!value) break;
        label += String.fromCharCode(value);
    }
    return label;
}
function alignUp(value, alignment) {
    return Math.ceil(value / alignment) * alignment;
}
function isSourceDataEmpty(data, offset, len = 16) {
    const end = Math.min(offset + len, data.length);
    if (end <= offset) return true;
    let allFF = true, allZero = true;
    for (let i = offset; i < end; i++) {
        if (data[i] !== 0xFF) allFF = false;
        if (data[i] !== 0x00) allZero = false;
    }
    return allFF || allZero;
}
function measureEspImageSize(data, imageOffset) {
    if (imageOffset + 24 > data.length) return 0;
    const magic = data[imageOffset];
    const segmentCount = data[imageOffset + 1];
    const hashAppended = data[imageOffset + 23];
    if (magic !== 0xE9 || segmentCount === 0 || segmentCount > 16) return 0;

    let cursor = imageOffset + 24;
    for (let i = 0; i < segmentCount; i++) {
        if (cursor + 8 > data.length) return 0;
        const segmentSize = readLe32(data, cursor + 4);
        cursor += 8;
        if (segmentSize > data.length || cursor > data.length - segmentSize) return 0;
        cursor += segmentSize;
    }

    let end = alignUp(cursor, 16) + 1;
    if (hashAppended) end += 32;
    end = alignUp(end, 16);
    if (end <= imageOffset || end > data.length) return 0;
    return end - imageOffset;
}
function buildOtaManifest(file, partitions) {
    return {
        sourceName: file.name,
        parts: partitions.map(partition => ({
            kind: partition.kind,
            label: partition.label || '',
            subtype: partition.subtype,
            sourceOffset: partition.offset,
            copySize: partition.size,
            declaredSize: partition.declaredSize || partition.size
        }))
    };
}
let _otaFile = null;
let _otaManifest = null;
function renderOtaActions(file, manifest) {
    _otaFile = file;
    _otaManifest = manifest;
    const outputDiv = _('analysisOutput');
    const spiffsInfo = _('spiffsInfo');
    outputDiv.innerHTML = '';
    outputDiv.style.display = 'block';
    spiffsInfo.style.display = 'none';

    manifest.parts.forEach((partition) => {
        const meta = document.createElement('div');
        meta.style.fontSize = '0.85em';
        meta.style.opacity = '0.8';
        meta.textContent =
            `${partition.kind.toUpperCase()} offset 0x${partition.sourceOffset.toString(16)} size 0x${partition.copySize.toString(16)}` +
            (partition.label ? ` label ${partition.label}` : '');
        outputDiv.appendChild(meta);
    });

    if (manifest.parts.length === 0) {
        outputDiv.textContent = t('No installable partitions found in this file.');
        return;
    }

    const button = document.createElement('button');
    button.textContent = t('Start Update');
    button.onclick = () => uploadPackage(file, manifest);
    outputDiv.appendChild(button);

    if (manifest.parts.some(partition => partition.kind === 'data')) {
        spiffsInfo.style.display = 'block';
        spiffsInfo.innerHTML =
            '<p><b>' + t('Data partition') + '</b>: this can be SPIFFS, LittleFS, or FAT depending on the firmware package.</p>';
    }
}
function analyzeFile() {
    const fileInput = _('fileInput');
    const outputDiv = _('analysisOutput');
    outputDiv.style.display = 'none';
    let pass = true;
    if (fileInput.files.length === 0) {
        window.alert(t('Please, select a file.'));
        return;
    }
    if (fileInput.files[0].name.split('.').pop() !== "bin") {
        window.alert(t('File is not a .bin'));
        return;
    }
    const file = fileInput.files[0];
    const reader = new FileReader();
    reader.onload = function (e) {
        const data = new Uint8Array(reader.result);
        let appOffset = 0;
        let appSize = 0;
        const partitions = [];
        const first_slice = data.slice(0x8000, 0x8000 + 32);
        const byte0 = first_slice[0];
        const byte1 = first_slice[1];
        const byte2 = first_slice[2];
        if (byte0 === 0xaa && byte1 === 0x50 && byte2 === 0x01 && pass === true) {
            pass = false;
            for (let i = 0; i < 0x1000; i += 0x20) {
                const pos = 0x8000 + i;
                if (pos + 32 > data.length) break;
                const slice = data.slice(pos, pos + 32);
                if ((slice[0] === 0xEB && slice[1] === 0xEB) || (slice[0] === 0xFF && slice[1] === 0xFF)) break;
                const type = slice[2];
                const subtype = slice[3];
                const offset = readLe32(slice, 4);
                const declaredSize = readLe32(slice, 8);
                const label = readPartitionLabel(slice, 12);
                if (type === 0x00 && [0x00, 0x10, 0x20].includes(subtype)) {
                    appOffset = offset || 0x10000;
                    const measuredAppSize = measureEspImageSize(data, appOffset);
                    appSize = declaredSize;
                    if (data.length < (appOffset + appSize)) appSize = data.length - appOffset;
                    if (measuredAppSize > 0 && (appSize === 0 || measuredAppSize < appSize)) {
                        appSize = measuredAppSize;
                    }
                }
                if (type === 0x01 && [0x81, 0x82, 0x83].includes(subtype) && offset < data.length) {
                    let size = declaredSize;
                    if (data.length < (offset + size)) size = data.length - offset;
                    const isSpiffsLike = subtype === 0x82 || subtype === 0x83;
                    // an empty (formatted, no payload) SPIFFS/LittleFS partition still needs to be
                    // reported so the device can create it at minimum size, just with nothing to copy
                    if (isSpiffsLike && isSourceDataEmpty(data, offset)) size = 0;
                    if (size > 0 || (isSpiffsLike && declaredSize > 0)) {
                        partitions.push({
                            kind: 'data',
                            subtype,
                            label,
                            offset,
                            size,
                            declaredSize
                        });
                    }
                }
            }
        }
        else if (pass === true) {
            pass = false;
            appOffset = 0x0;
            appSize = measureEspImageSize(data, 0) || data.length;
        }
        if (appSize > 0) {
            partitions.unshift({
                kind: 'app',
                subtype: 0,
                label: 'app',
                offset: appOffset,
                size: appSize,
                declaredSize: appSize
            });
        }
        renderOtaActions(file, buildOtaManifest(file, partitions));
    };
    reader.readAsArrayBuffer(file);
}
function uploadPackage(file, manifest) {
    _("updetails").innerHTML = t("Preparing...");
    totalFiles = 1;
    completedFiles = 0;
    const ajax = new XMLHttpRequest();
    ajax.onload = function () {
        if (ajax.status === 200 && ajax.responseText === "OK") {
            const fileProgressDiv = document.createElement("div");
            fileProgressDiv.innerHTML = `<p>${t("Updating...")}</p><p><progress id="otaprb" value="0" max="100" style="width:100%;"></progress></p>`;
            _("updetails").appendChild(fileProgressDiv);
            const formdata2 = new FormData();
            formdata2.append("file1", file, file.name);
            const ajax2 = new XMLHttpRequest();
            ajax2.open("POST", "/OTAFILE");
            ajax2.upload.addEventListener("progress", function (event) {
                const p = (event.loaded / event.total) * 100;
                _("otaprb").value = Math.round(p);
            }, false);
            ajax2.addEventListener("load", function () { _("status").innerHTML = t("Installation complete, restart your device!"); }, false);
            ajax2.addEventListener("error", function () { _("status").innerHTML = t("Upload Failed"); }, false);
            ajax2.addEventListener("abort", function () { _("status").innerHTML = t("Upload Aborted"); }, false);
            ajax2.send(formdata2);
        }
    };
    ajax.onerror = function () {
        console.error("Initial OTA request failed.");
    };
    const formdata = new FormData();
    formdata.append("command", 0);
    formdata.append("size", file.size);
    formdata.append("manifest", JSON.stringify(manifest));
    ajax.open("POST", "/OTA", true);
    ajax.send(formdata);
}
function logoutButton() {
    httpRequest("GET", "/logout");
    setTimeout(function () { window.open("/logged-out", "_self"); }, 500);
}
function rebootButton() {
    if (confirm(t("Confirm Restart?!"))) {
        httpRequest("GET", "/reboot");
    }
}
let _sdInfo = null;
let _currentSection = '';
function systemInfo() {
    httpRequest("GET", "/systeminfo", {
        onload: (xhr) => {
            if (xhr.status === 200) {
                try {
                    const data = JSON.parse(xhr.responseText);
                    _("firmwareVersion").innerHTML = data.VERSION;
                    _sdInfo = data.SD;
                    if (_currentSection === 'files') _("detailsheader").innerHTML = "<h3>" + t("Files") + "</h3>" + sdUsageBar();
                } catch (error) {
                    console.error("JSON Parsing Error: ", error);
                }
            } else {
                console.error("Request Error: " + xhr.status);
            }
        }
    });
}
// Same visual language as the partition usage bar (pman-bar/pman-seg/pman-legend), reused
// here so the SD Card stats read as one system: Used maps to pman-data, Free to pman-free.
function sdUsageBar() {
    if (!_sdInfo || !_sdInfo.totalBytes) return '';
    const usedPct = (_sdInfo.usedBytes / _sdInfo.totalBytes) * 100;
    const freePct = 100 - usedPct;
    return `<div class="pman-bar"><div class="pman-seg pman-data" style="width:${usedPct}%" title="${t('Used')} (${_sdInfo.used})"></div><div class="pman-seg pman-free" style="width:${freePct}%" title="${t('Free')} (${_sdInfo.free})"></div></div>` +
        `<div class="row pman-legend">` +
        `<span><i class="pman-dot pman-data"></i>${t('Used')} <b style="color:var(--fg)">${_sdInfo.used}</b></span>` +
        `<span><i class="pman-dot pman-free"></i>${t('Free')} <b style="color:var(--fg)">${_sdInfo.free}</b></span>` +
        `<span>${t('Total')} <b style="color:var(--fg)">${_sdInfo.total}</b></span></div>`;
}
function listFilesButton(folders) {
    _currentSection = 'files';
    _("drop-area").style.display = 'block';
    _("actualFolder").value = folders;
    let previousFolder = folders.substring(0, folders.lastIndexOf('/'));
    if (previousFolder === "") { previousFolder = "/"; }
    httpRequest("GET", "/listfiles?folder=" + folders, {
        onload: (xhr) => {
            if (xhr.status === 200) {
                const responseText = xhr.responseText;
                const lines = responseText.split('\n');
                let tableContent = "<table><tr><th>" + t("Name") + "</th><th class='sz'>" + t("Size") + "</th><th class='ac'></th><th class='mb'></th></tr>\n";
                tableContent += "<tr><td colspan='4'><a onclick=\"listFilesButton('" + previousFolder + "')\" href='javascript:void(0);'>&#8592; ..</a></td></tr>\n";
                let folder = "";
                const foldersArray = [];
                const filesArray = [];
                lines.forEach((line) => {
                    if (line) {
                        const type = line.substring(0, 2);
                        const path = line.substring(3, line.lastIndexOf(':'));
                        const filename = line.substring(3, line.lastIndexOf(':'));
                        const size = line.substring(line.lastIndexOf(':') + 1);
                        if (type === "pa") {
                            if (path !== "" && folder !== "/") folder = path + (path.endsWith("/") ? "" : "/");
                        } else if (type === "Fo") {
                            foldersArray.push({ path: folder + path, name: filename });
                        } else if (type === "Fi") {
                            filesArray.push({ path: folder + path, name: filename, size });
                        }
                    }
                });
                foldersArray.sort((a, b) => a.name.localeCompare(b.name));
                filesArray.sort((a, b) => a.name.localeCompare(b.name));
                foldersArray.forEach((item) => {
                    const ac = "<span style='cursor:pointer;color:#e0d204' onclick=\"listFilesButton('" + item.path + "')\">&#128193;</span>&nbsp" +
                               "<span style='cursor:pointer' onclick=\"renameFile('" + item.path + "', '" + item.name + "')\">&#9999;</span>&nbsp" +
                               "<span style='cursor:pointer' onclick=\"downloadDeleteButton('" + item.path + "', 'delete')\">&#128465;</span>";
                    tableContent += "<tr><td><a onclick=\"listFilesButton('" + item.path + "')\" href='javascript:void(0);'>" + item.name + "</a></td>" +
                                    "<td class='sz'></td><td class='ac'>" + ac + "</td>" +
                                    "<td class='mb'><button onclick='toggleRow(this)'>&#8942;</button></td></tr>\n" +
                                    "<tr class='mrow' style='display:none'><td colspan='4'>" + ac + "</td></tr>\n";
                });
                filesArray.forEach((item) => {
                    const isBin = item.name.split('.').pop().toLowerCase() === "bin";
                    const fname = item.name + (isBin ? "&nbsp<span style='cursor:pointer' onclick=\"startUpdate('" + item.path + "')\">&#128640;</span>" : "");
                    const ac = (isEditable(item.name) ? "<span style='cursor:pointer' onclick=\"editFile('" + item.path + "')\">&#9998;</span>&nbsp" : "") +
                               "<span style='cursor:pointer' onclick=\"downloadDeleteButton('" + item.path + "', 'download')\">&#11015;</span>&nbsp" +
                               "<span style='cursor:pointer' onclick=\"renameFile('" + item.path + "', '" + item.name + "')\">&#9999;</span>&nbsp" +
                               "<span style='cursor:pointer' onclick=\"downloadDeleteButton('" + item.path + "', 'delete')\">&#128465;</span>";
                    tableContent += "<tr><td>" + fname + "</td>" +
                                    "<td class='sz'>" + item.size + "</td><td class='ac'>" + ac + "</td>" +
                                    "<td class='mb'><button onclick='toggleRow(this)'>&#8942;</button></td></tr>\n" +
                                    "<tr class='mrow' style='display:none'><td colspan='4'><span style='color:var(--dim);font-size:.75rem'>" + item.size + "</span>&nbsp;&nbsp;" + ac + "</td></tr>\n";
                });
                tableContent += "</table>";
                _("details").innerHTML = tableContent;
                translateRenderedText(_("details"));
            } else {
                console.error("Request Error: " + xhr.status);
            }
        },
        onerror: () => {
            console.error("Network error while fetching file list.");
        }
    });
    _("detailsheader").innerHTML = "<h3>" + t("Files") + "</h3>" + sdUsageBar();
    _("updetailsheader").innerHTML =
        "<input type='file' id='fa' multiple style='display:none'>" +
        "<input type='file' id='fol' webkitdirectory directory multiple style='display:none'>" +
        "<div class='row' style='margin:6px 0'><button onclick=\"_('fa').click()\">&#8679; " + t("Files") + "</button>" +
        "<button onclick=\"_('fol').click()\">&#128193; " + t("Folder") + "</button>" +
        "<button onclick=\"CreateFolder('" + folders + "')\">" + t("+ New Folder") + "</button></div>";
    _("fa").onchange = e => handleFileForm(e.target.files, folders);
    _("fol").onchange = e => handleFileForm(e.target.files, folders);
    _("updetails").innerHTML = "";
    _("OTAdetails").style.display = 'none';
    _("analysisOutput").style.display = 'none';
    _("spiffsInfo").style.display = 'none';
}
function renameFile(filePath, oldName) {
    const actualFolder = _("actualFolder").value;
    const fileName = prompt(t("Enter the new name: "), oldName);
    if (isNullOrEmpty(fileName)) {
        window.alert(t("Invalid Name"));
    } else {
        const formdata5 = new FormData();
        formdata5.append("filePath", filePath);
        formdata5.append("fileName", fileName);
        const xhr = httpRequest("POST", "/rename", { async: false, body: formdata5 });
        _("status").innerHTML = xhr.responseText;
        listFilesButton(actualFolder);
    }
}
function downloadDeleteButton(filename, action) {
    const urltocall = "/file?name=" + filename + "&action=" + action;
    const actualFolder = _("actualFolder").value;
    const isDelete = action === "delete";
    if (isDelete || action === "create") {
        if (!isDelete || confirm(t("Do you really want to DELETE the file: ") + filename + " ?\n\n" + t("This action can't be undone!"))) {
            const xhr = httpRequest("GET", urltocall, { async: false });
            _("status").innerHTML = xhr.responseText;
            listFilesButton(actualFolder);
        }
        return;
    }
    if (action === "download") {
        _("status").innerHTML = "";
        window.open(urltocall, "_blank");
    }
}
function CreateFolder(folders) {
    const folderName = prompt(t("Folder Name"), "");
    if (isNullOrEmpty(folderName)) {
        window.alert(t("Invalid Folder Name"));
    } else {
        downloadDeleteButton(_("actualFolder").value + "/" + folderName, 'create');
    }
}
const addHighlight = (event) => {
    event.preventDefault();
    event.currentTarget.classList.add("highlight");
};
const removeHighlight = (event) => {
    event.preventDefault();
    event.currentTarget.classList.remove("highlight");
};
window.addEventListener("load", () => {
    const dropArea = _("drop-area");
    dropArea.addEventListener("dragenter", addHighlight, false);
    dropArea.addEventListener("dragover", addHighlight, false);
    dropArea.addEventListener("dragleave", removeHighlight, false);
    dropArea.addEventListener("drop", drop, false);
});
let totalFiles = 0;
let completedFiles = 0;
let uploadIdx = 0;
function writeSendForm() {
    _('uplist').innerHTML = '';
    _('upmodal').classList.add('open');
}
async function drop(event) {
    event.preventDefault();
    _("drop-area").classList.remove("highlight");
    const items = event.dataTransfer.items;
    const filesQ = [];
    const promises = [];
    for (let i = 0; i < items.length; i++) {
        const entry = items[i].webkitGetAsEntry();
        if (entry) {
            promises.push(FileTree(entry, "", filesQ));
        }
    }
    await Promise.all(promises);
    handleFileForm(filesQ, _("actualFolder").value);
}
function FileTree(item, path = "", filesQ) {
    return new Promise((resolve) => {
        if (item.isFile) {
            item.file(function (file) {
                const fileWithPath = new File([file], path + file.name, { type: file.type });
                filesQ.push(fileWithPath);
                resolve();
            });
        } else if (item.isDirectory) {
            const dirReader = item.createReader();
            dirReader.readEntries((entries) => {
                const entryPromises = [];
                for (let i = 0; i < entries.length; i++) {
                    entryPromises.push(FileTree(entries[i], path + item.name + "/", filesQ));
                } Promise.all(entryPromises).then(resolve);
            });
        } else {
            resolve();
        }
    });
}
window.addEventListener("load", () => {
    applyLanguage();
    listFilesButton("/");
    systemInfo();
});
let fileQueue = [];
let activeUploads = 0;
const maxConcurrentUploads = 2;
function handleFileForm(files, folder) {
    uploadIdx = 0;
    writeSendForm();
    fileQueue = Array.from(files);
    totalFiles = fileQueue.length;
    completedFiles = 0;
    activeUploads = 0;
    for (let i = 0; i < maxConcurrentUploads; i++) {
        processNextUpload(folder);
    }
}
function processNextUpload(folder) {
    if (fileQueue.length === 0) {
        if (activeUploads === 0) {
            _('upmodal').classList.remove('open');
            _("status").innerHTML = t("Upload Complete");
            const actualFolder = _("actualFolder").value;
            listFilesButton(actualFolder);
        }
        return;
    }
    if (activeUploads >= maxConcurrentUploads) return;
    const file = fileQueue.shift();
    activeUploads++;
    uploadFile(folder, file)
        .then(() => {
            activeUploads--;
            completedFiles++;
            _("status").innerHTML = `${t("Uploaded")} ${completedFiles} ${t("of")} ${totalFiles} ${t("files.")}`;
            processNextUpload(folder);
        })
        .catch((error) => {
            activeUploads--;
            _("status").innerHTML = translateStatus(error) || t("Upload Failed");
            processNextUpload(folder);
        });
}
function uploadFile(folder, file) {
    return new Promise((resolve, reject) => {
        const id = 'upfill' + (uploadIdx++);
        const row = document.createElement('div');
        row.className = 'upl';
        row.innerHTML = `<div class="upl-fill" id="${id}"></div><div class="upl-lbl">${file.webkitRelativePath || file.name}</div>`;
        _('uplist').appendChild(row);
        const formdata = new FormData();
        formdata.append("folder", folder);
        formdata.append("file", file, file.webkitRelativePath || file.name);
        const ajax = new XMLHttpRequest();
        ajax.upload.addEventListener("progress", (event) => {
            if (event.lengthComputable)
                _(id).style.width = Math.round(event.loaded / event.total * 100) + '%';
        }, false);
        ajax.addEventListener("load", () => {
            if (ajax.status === 200 && ajax.responseText === "OK") {
                resolve();
            } else {
                reject(ajax.responseText || t("Upload failed"));
            }
        }, false);
        ajax.addEventListener("error", () => reject(), false);
        ajax.addEventListener("abort", () => reject(), false);
        ajax.open("POST", "/");
        ajax.send(formdata);
    });
}

// ── Partition Manager (PMan) ────────────────────────────────────────────────────
let _pmanData = null;
function pmanSize(bytes) {
    if (bytes >= 1048576) return (bytes % 1048576 ? (bytes / 1048576).toFixed(2) : bytes / 1048576) + ' MB';
    if (bytes >= 1024) return (bytes % 1024 ? (bytes / 1024).toFixed(2) : bytes / 1024) + ' KB';
    return bytes + ' B';
}
function pmanHex(n) { return '0x' + n.toString(16).toUpperCase(); }
function partitionsPost(params, onDone) {
    const fd = new FormData();
    Object.keys(params).forEach((k) => fd.append(k, params[k]));
    httpRequest("POST", "/partitions", {
        body: fd,
        onload: (xhr) => {
            if (xhr.status === 200) {
                if (typeof onDone === 'function') onDone(xhr);
            } else {
                _("status").innerHTML = translateStatus(xhr.responseText || t('Failed'));
            }
        }
    });
}
function loadPartitions() {
    _currentSection = 'partitions';
    _("detailsheader").innerHTML = "<h3>" + t("Partition Manager") + "</h3>";
    _("status").innerHTML = "";
    _("OTAdetails").style.display = 'none';
    _("analysisOutput").style.display = 'none';
    _("spiffsInfo").style.display = 'none';
    _("updetailsheader").innerHTML = "";
    _("updetails").innerHTML = "";
    _("drop-area").style.display = 'block';
    _("details").innerHTML = t("Loading...");
    httpRequest("GET", "/partitions", {
        onload: (xhr) => {
            if (xhr.status !== 200) { _("details").innerHTML = t("Failed to load partitions."); return; }
            _pmanData = JSON.parse(xhr.responseText);
            pmanRender(_pmanData);
        }
    });
}
function pmanUsageBar(data) {
    const items = [...data.entries].sort((a, b) => a.offset - b.offset);
    let segs = '';
    const addSeg = (size, cls, title) => {
        if (size <= 0) return;
        segs += `<div class="pman-seg ${cls}" style="width:${(size / data.flashSize) * 100}%" title="${title}"></div>`;
    };
    if (items.length && items[0].offset > 0) addSeg(items[0].offset, 'pman-sys', t('System (bootloader, nvs, otadata...)'));
    items.forEach((e, i) => {
        addSeg(e.size, e.type === 0 ? 'pman-app' : 'pman-data', `${e.label} (${pmanSize(e.size)})`);
        const next = items[i + 1];
        const gapEnd = next ? next.offset : data.flashSize;
        const gapStart = e.offset + e.size;
        addSeg(gapEnd - gapStart, 'pman-free', `${t('Free')} (${pmanSize(gapEnd - gapStart)})`);
    });
    return `<div class="pman-bar">${segs}</div>` +
        `<div class="row pman-legend">` +
        `<span><i class="pman-dot pman-app"></i>${t('App')}</span>` +
        `<span><i class="pman-dot pman-data"></i>${t('Data')}</span>` +
        `<span><i class="pman-dot pman-free"></i>${t('Free')}</span>` +
        `<span><i class="pman-dot pman-sys"></i>${t('System')}</span></div>`;
}
function pmanRowActions(e) {
    let a = `<span style="cursor:pointer" onclick="pmanDetails(${e.offset})" title="${t('Details')}">&#8505;</span>`;
    if (e.protected) return a;
    a += `&nbsp;<span style="cursor:pointer" onclick="pmanResize(${e.offset})" title="${t('Resize')}">&#8596;</span>`;
    if (e.type === 1) {
        a += `&nbsp;<span style="cursor:pointer" onclick="pmanBackup('${e.label}')" title="${t('Backup')}">&#128190;</span>` +
             `&nbsp;<span style="cursor:pointer" onclick="pmanRestore('${e.label}')" title="${t('Restore')}">&#8635;</span>` +
             `&nbsp;<span style="cursor:pointer" onclick="pmanFormat(${e.offset},'${e.label}')" title="${t('Format')}">&#9099;</span>`;
    }
    a += `&nbsp;<span style="cursor:pointer" onclick="pmanDelete(${e.offset},'${e.label}')" title="${t('Remove')}">&#128465;</span>`;
    return a;
}
function pmanRender(data) {
    let toolbar = '<div class="row" style="margin:8px 0">' +
        '<button onclick="pmanCreate(0,16,\'app\',1024)">+ ' + t('OTA App') + '</button>' +
        '<button onclick="pmanCreate(1,129,\'vfs\',512)">+ ' + t('FAT') + '</button>' +
        '<button onclick="pmanCreate(1,130,\'spiffs\',256)">+ SPIFFS</button>';
    if (data.dirty) {
        toolbar += '<button onclick="pmanApply()" style="color:var(--ac);border-color:var(--ac)">&#10003; ' + t('Apply Changes') + '</button>' +
            '<button onclick="pmanDiscard()">&#8634; ' + t('Discard Changes') + '</button>';
    }
    toolbar += '</div>';
    if (data.dirty) toolbar += '<p style="color:var(--yw)">' + t('Unsaved changes — nothing is written to flash until you Apply.') + '</p>';

    let table = '<table><tr><th>' + t('Partition') + '</th><th class="sz">' + t('Size') + '</th><th class="ac"></th><th class="mb"></th></tr>\n';
    data.entries.forEach((e) => {
        const badges = (e.protected ? ' <span class="tag" style="opacity:.65">' + t('protected') + '</span>' : '') +
            (e.running ? ' <span class="tag" style="color:var(--ac)">' + t('running') + '</span>' : '');
        const appInfo = e.appName ? `<br><span style="color:var(--dim);font-size:.75rem">${t('Firmware: ')}${e.appName}</span>` : '';
        const dataInfo = (e.dataLabels && e.dataLabels.length) ?
            `<br><span style="color:var(--dim);font-size:.75rem">${t('Data partition: ')}${e.dataLabels.join(', ')}</span>` :
            (e.type === 0 ? `<br><span style="color:var(--dim);font-size:.75rem">${t('No data partition')}</span>` : '');
        const label = `<b>${e.label}</b> <span style="color:var(--dim);font-size:.75rem">${e.typeName}/${e.subtypeName}</span>${badges}${appInfo}${dataInfo}`;
        const actions = pmanRowActions(e);
        table += `<tr><td>${label}</td><td class="sz">${pmanSize(e.size)}</td><td class="ac">${actions}</td>` +
            `<td class="mb"><button onclick="toggleRow(this)">&#8942;</button></td></tr>\n` +
            `<tr class="mrow" style="display:none"><td colspan="4"><span style="color:var(--dim);font-size:.75rem">${pmanSize(e.size)}</span>&nbsp;&nbsp;${actions}</td></tr>\n`;
    });
    table += '</table>';

    let freeHtml = '';
    if (data.freeRanges && data.freeRanges.length) {
        freeHtml = '<h3 style="margin-top:14px">' + t('Free Space') + '</h3><table>' +
            '<tr><th>' + t('Offset') + '</th><th class="sz">' + t('Size') + '</th></tr>' +
            data.freeRanges.map((r) => `<tr><td>${pmanHex(r.offset)}</td><td class="sz">${pmanSize(r.size)}</td></tr>`).join('') +
            '</table>';
    }

    _("details").innerHTML = pmanUsageBar(data) + toolbar + table + freeHtml;
    translateRenderedText(_("details"));
}
function pmanDetails(offset) {
    const e = _pmanData.entries.find((x) => x.offset === offset);
    if (!e) return;
    window.alert(
        t('Label: ') + e.label +
        '\n' + t('Type: ') + e.typeName + '/' + e.subtypeName +
        '\n' + t('Offset: ') + pmanHex(e.offset) +
        '\n' + t('Size: ') + pmanHex(e.size) + ' (' + pmanSize(e.size) + ')' +
        '\n' + t('Flags: ') + pmanHex(e.flags) +
        (e.appName ? '\n' + t('Firmware: ') + e.appName : '') +
        (e.dataLabels && e.dataLabels.length ? '\n' + t('Data partition: ') + e.dataLabels.join(', ') : '')
    );
}
let _pmanResizeEntry = null;
function pmanResize(offset) {
    const e = _pmanData.entries.find((x) => x.offset === offset);
    if (!e) return;
    _pmanResizeEntry = e;
    const alignment = e.alignment || 4096;
    const minSize = alignment;
    const maxSize = e.maxOffset - e.offset;
    const value = Math.min(Math.max(e.size, minSize), maxSize);

    _('pmanResizeTitle').textContent = t('Resize') + ' ' + e.label;
    _('pmanResizeBody').innerHTML =
        `<p class="pman-resize-range">${t('Range: ')}${pmanHex(minSize)} - ${pmanHex(maxSize)} (step ${pmanHex(alignment)})</p>` +
        `<input type="range" id="pmanResizeSlider" min="${minSize}" max="${maxSize}" step="${alignment}" value="${value}" oninput="pmanResizeUpdate()">` +
        `<div class="pman-resize-vals"><b id="pmanResizeHex"></b><span id="pmanResizeHuman" style="color:var(--dim)"></span></div>`;
    pmanResizeUpdate();
    _('pmanResizeOverlay').classList.add('open');
}
function pmanResizeUpdate() {
    const v = parseInt(_('pmanResizeSlider').value);
    _('pmanResizeHex').textContent = pmanHex(v);
    _('pmanResizeHuman').textContent = pmanSize(v);
}
function pmanResizeConfirm() {
    if (!_pmanResizeEntry) return;
    const size = parseInt(_('pmanResizeSlider').value);
    _('pmanResizeOverlay').classList.remove('open');
    partitionsPost({ action: 'resize', offset: _pmanResizeEntry.offset, size }, () => loadPartitions());
}
function pmanCreate(type, subtype, defaultLabel, defaultSizeKb) {
    const label = prompt(t('Partition label:'), defaultLabel);
    if (isNullOrEmpty(label)) return;
    const sizeKb = prompt(t('Size in KB:'), defaultSizeKb);
    if (isNullOrEmpty(sizeKb)) return;
    const size = parseInt(sizeKb) * 1024;
    if (!size || size <= 0) { window.alert(t('Invalid size')); return; }
    partitionsPost({ action: 'create', type, subtype, label, size }, () => loadPartitions());
}
function pmanDelete(offset, label) {
    if (!confirm(t('Remove partition') + ` "${label}"?\n\n` + t('This is staged until you Apply Changes.'))) return;
    partitionsPost({ action: 'delete', offset }, () => loadPartitions());
}
function pmanFormat(offset, label) {
    if (!confirm(t('Erase all data on') + ` "${label}" now?\n\n` + t("This happens immediately and can't be undone."))) return;
    partitionsPost({ action: 'format', offset }, () => loadPartitions());
}
function pmanApply() {
    if (!confirm(t('Write the new partition table and reboot the device now?'))) return;
    partitionsPost({ action: 'apply' }, () => {
        _("details").innerHTML = '<p>' + t('Partition table written. The device is rebooting...') + '</p>';
        _("status").innerHTML = '';
    });
}
function pmanDiscard() {
    if (!confirm(t('Discard all pending changes?'))) return;
    partitionsPost({ action: 'discard' }, () => loadPartitions());
}
function pmanBackup(label) {
    partitionsPost({ action: 'backup', label }, (xhr) => {
        const res = JSON.parse(xhr.responseText);
        _("status").innerHTML = t('Backup saved: ') + res.path;
    });
}
function pmanRestore(label) {
    httpRequest("GET", "/partitions?list=backups&label=" + encodeURIComponent(label), {
        onload: (xhr) => {
            if (xhr.status !== 200) { _("status").innerHTML = t('Failed to list backups'); return; }
            const list = (JSON.parse(xhr.responseText).backups) || [];
            if (!list.length) { window.alert(t('No backups found for') + ` "${label}"`); return; }
            let path = list[list.length - 1].path;
            if (list.length > 1) {
                const options = list.map((b, i) => `${i + 1}: ${b.path}`).join('\n');
                const choice = prompt(t('Choose a backup to restore:\n') + options, String(list.length));
                if (isNullOrEmpty(choice)) return;
                const picked = list[parseInt(choice) - 1];
                if (!picked) { window.alert(t('Invalid choice')); return; }
                path = picked.path;
            }
            if (!confirm(t('Restore') + ` "${label}" ${t('from')}:\n${path}\n\n` + t('This overwrites the current data on the partition.'))) return;
            partitionsPost({ action: 'restore', label, path }, () => {
                _("status").innerHTML = t('Restored') + ` ${label} ` + t('from') + ` ${path}`;
            });
        }
    });
}
