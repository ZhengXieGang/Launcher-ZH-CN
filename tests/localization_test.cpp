#include "localization.h"
#include "localization_font.h"

#include <cassert>
#include <cstring>
#include <iostream>

namespace {

void expect(bool condition, const char *message) {
    if (condition) return;
    std::cerr << "localization test failed: " << message << '\n';
    std::abort();
}

void testTranslationContractAndFormatting() {
    for (uint16_t key = 0; key < static_cast<uint16_t>(UiTextKey::Count); ++key) {
        const UiTextKey textKey = static_cast<UiTextKey>(key);
        expect(!uiText(textKey).isEmpty(), "Chinese translation key is missing");
    }

    expect(uiFormat(UiTextKey::BackupDataFor, "Demo") == u8"备份应用数据：Demo？", "Chinese format tokens must expand");
    expect(uiTranslate("Backup failed: Demo") == u8"备份失败：Demo", "longest legacy prefix must translate");
    expect(uiTranslate("Canceled") == u8"已取消", "Canceled must not become a translated Cancel prefix plus 'ed'");
}

void testSerialTranslationContract() {
    expect(uiTranslateSerialLine("ERR unknown nav target\n") == "ERR 未知导航目标\n",
           "serial error body must be translated while ERR stays stable");
    expect(uiTranslateSerialLine("  <offset>/<size>: decimal or 0x-prefixed hex") ==
               u8"  <offset>/<size>：十进制或 0x 前缀十六进制",
           "indented serial help must be translated");
    expect(uiTranslateSerialLine("OK partition deleted\n") == "OK 分区已删除\n",
           "serial success body must be translated while OK stays stable");
    expect(uiTranslateSerialLine("READY 1234\n") == "READY 1234\n",
           "READY payload must remain machine-readable");
    expect(uiTranslateSerialLine("ACK 512/1234\n") == "ACK 512/1234\n",
           "ACK payload must remain machine-readable");
    expect(uiTranslateSerialLine("\nRestart your Device") == "\n请重启设备",
           "multi-line serial messages must preserve line boundaries");
}

void testUtf8MetricsClippingWrappingAndAlignment() {
    const char *mixed = u8"A中B";
    size_t offset = 0;
    uint32_t codepoint = 0;
    expect(uiDecodeUtf8(mixed, std::strlen(mixed), offset, codepoint) && codepoint == 'A', "ASCII UTF-8 decode failed");
    expect(uiDecodeUtf8(mixed, std::strlen(mixed), offset, codepoint) && codepoint == 0x4E2D, "Chinese UTF-8 decode failed");
    expect(uiDecodeUtf8(mixed, std::strlen(mixed), offset, codepoint) && codepoint == 'B', "trailing ASCII UTF-8 decode failed");

    const char invalid[] = {'A', static_cast<char>(0xC0), static_cast<char>(0xAF)};
    offset = 1;
    expect(uiDecodeUtf8(invalid, sizeof(invalid), offset, codepoint) && codepoint == 0xFFFD, "invalid UTF-8 must use replacement glyph");

    const String text(mixed);
    expect(uiTextWidth(text) == 20, "mixed ASCII/Chinese width must be deterministic");
    expect(uiClipText(text, 14) == u8"A中", "clip must not split a UTF-8 glyph");

    const std::vector<String> lines = uiWrapText(text, 14);
    expect(lines.size() == 2 && lines[0] == u8"A中" && lines[1] == "B", "wrap must preserve mixed glyph boundaries");

    uiDrawCentreText(text, 50, 0, 1);
    expect(uiTestLastDrawX() == 40 && uiTestLastDrawText() == text, "center alignment must use mixed-text width");
    uiDrawRightText(text, 50, 0, 1);
    expect(uiTestLastDrawX() == 30, "right alignment must use mixed-text width");
}

void testBitmapFontContract() {
    expect(kUiFontCellHeight == 8, "Chinese must keep the native ASCII line height");
    expect(kUiAsciiGlyphWidth == 6, "ASCII must keep the existing half-width advance");
    expect(kUiWideGlyphWidth == 8, "CJK must use a compact full-width 8-pixel cell");
    expect(kUiBitmapGlyphCount >= 300, "firmware bitmap font must cover the shipped UI subset");
    for (size_t i = 0; i < kUiBitmapGlyphCount; ++i) {
        expect(kUiBitmapGlyphs[i].bitmap[7] == 0, "CJK glyphs must leave the native font's eighth scanline empty");
    }
    auto hasGlyph = [](uint16_t codepoint) {
        for (size_t i = 0; i < kUiBitmapGlyphCount; ++i) {
            if (kUiBitmapGlyphs[i].codepoint == codepoint) {
                for (uint8_t byte : kUiBitmapGlyphs[i].bitmap) {
                    if (byte != 0) return true;
                }
                return false;
            }
        }
        return false;
    };
    expect(hasGlyph(0x4E2D), "Chinese glyph for U+4E2D must be present");
    expect(hasGlyph(0x542F), "Chinese glyph for U+542F must be present");
    expect(hasGlyph(0x7F6E), "Chinese glyph for U+7F6E must be present");
    expect(hasGlyph(0xFF1A), "full-width Chinese punctuation must be present");
    expect(uiTextLineHeight(u8"中文", 1) == 8, "Chinese lines must match native ASCII height");
    expect(uiTextLineHeight("English", 1) == 8, "ASCII lines must keep native height");
    expect(uiTextLineHeight(u8"English中文", 2) == 16, "mixed text must keep native scaled line height");
}

} // namespace

int main() {
    testTranslationContractAndFormatting();
    testSerialTranslationContract();
    testUtf8MetricsClippingWrappingAndAlignment();
    testBitmapFontContract();
    std::cout << "localization tests passed\n";
    return 0;
}
