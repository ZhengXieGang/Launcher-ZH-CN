#include "launcher_platform.h"

#include "localization.h"
#include <HardwareSerial.h>
#include <cstdarg>
#include <cstdio>
#include <vector>

void launcherConsolePrintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
#if defined(HEADLESS)
    va_list probe;
    va_copy(probe, args);
    const int required = vsnprintf(nullptr, 0, fmt, probe);
    va_end(probe);
    if (required >= 0) {
        std::vector<char> buffer(static_cast<size_t>(required) + 1U);
        vsnprintf(buffer.data(), buffer.size(), fmt, args);
        const String translated = uiTranslateSerialLine(String(buffer.data()));
        Serial.print(translated.c_str());
    }
#else
    Serial.vprintf(fmt, args);
#endif
    va_end(args);
}

void launcherConsolePrint(const char *text) {
#if defined(HEADLESS)
    const String translated = uiTranslateSerialLine(text ? String(text) : String());
    Serial.print(translated.c_str());
#else
    Serial.print(text);
#endif
}

void launcherConsolePrintln(const char *text) {
#if defined(HEADLESS)
    const String translated = uiTranslateSerialLine(text ? String(text) : String());
    Serial.println(translated.c_str());
#else
    Serial.println(text);
#endif
}

void launcherConsoleBegin(unsigned long baud) { Serial.begin(baud); }

void launcherConsoleFlush() { Serial.flush(); }

void launcherConsoleEnd() { Serial.end(); }
