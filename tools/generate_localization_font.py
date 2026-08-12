#!/usr/bin/env python3
"""Generate the firmware's compact UTF-8 bitmap glyph tables.

The launcher only needs the non-ASCII characters present in firmware source
strings.  Rendering a 12x12 subset keeps flash usage small while retaining a
real glyph for every shipped Simplified Chinese translation and its punctuation.
Printable ASCII also gets a narrow 6x12 companion font so mixed Chinese/English
text can share one visual size and baseline on every display driver.
"""

from __future__ import annotations

import argparse
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont


CELL_HEIGHT = 12
WIDE_CELL_WIDTH = 12
WIDE_INNER_SIZE = 11
ASCII_CELL_WIDTH = 6
ASCII_GLYPH_WIDTH = 5
ASCII_BASELINE = 10
WIDE_BITMAP_BYTES = (WIDE_CELL_WIDTH * CELL_HEIGHT + 7) // 8
ASCII_BITMAP_BYTES = (ASCII_CELL_WIDTH * CELL_HEIGHT + 7) // 8


def source_codepoints(root: Path) -> list[int]:
    # The localization catalog is the only firmware source of non-ASCII text
    # that is intentionally drawn.  Scanning every comment and board note would
    # silently add Japanese/Portuguese punctuation to every board's binary.
    codepoints: set[int] = set()
    path = root / "src" / "localization.cpp"
    try:
        text = path.read_text(encoding="utf-8")
    except (OSError, UnicodeDecodeError):
        return []
    codepoints.update(ord(char) for char in text if 0x80 <= ord(char) <= 0xFFFF)
    return sorted(codepoints)


def pack_bitmap(image: Image.Image) -> bytes:
    width, height = image.size
    bitmap = bytearray((width * height + 7) // 8)
    for row in range(height):
        for column in range(width):
            if image.getpixel((column, row)) < 110:
                continue
            bit = row * width + column
            bitmap[bit // 8] |= 1 << (7 - (bit % 8))
    return bytes(bitmap)


def rasterize_wide(font: ImageFont.FreeTypeFont, codepoint: int) -> bytes:
    char = chr(codepoint)
    canvas = Image.new("L", (96, 96), 0)
    ImageDraw.Draw(canvas).text((8, 0), char, font=font, fill=255)
    bounds = canvas.getbbox()
    if bounds is None:
        return bytes(WIDE_BITMAP_BYTES)

    glyph = canvas.crop(bounds)
    scale = min(WIDE_INNER_SIZE / glyph.width, WIDE_INNER_SIZE / glyph.height)
    size = (max(1, round(glyph.width * scale)), max(1, round(glyph.height * scale)))
    glyph = glyph.resize(size, Image.Resampling.LANCZOS)

    cell = Image.new("L", (WIDE_CELL_WIDTH, CELL_HEIGHT), 0)
    cell.paste(glyph, ((WIDE_CELL_WIDTH - size[0]) // 2, (CELL_HEIGHT - size[1]) // 2))
    return pack_bitmap(cell)


def rasterize_ascii(font: ImageFont.FreeTypeFont, codepoint: int) -> bytes:
    if codepoint == 0x20:
        return bytes(ASCII_BITMAP_BYTES)

    char = chr(codepoint)
    bounds = font.getbbox(char, anchor="ls")
    if bounds is None:
        return bytes(ASCII_BITMAP_BYTES)

    left, top, right, bottom = bounds
    source_width = max(1, right - left)
    source_height = max(1, bottom - top)
    source = Image.new("L", (source_width, source_height), 0)
    ImageDraw.Draw(source).text((-left, -top), char, font=font, fill=255, anchor="ls")

    # Preserve vertical proportions and the font baseline, compressing only the
    # width into a five-pixel half-width cell. Capitals occupy nine rows while
    # descenders use the final three, matching the 12x12 CJK cell without making
    # punctuation such as '-' or ':' unnaturally tall.
    target_top = ASCII_BASELINE + top
    target_height = min(source_height, CELL_HEIGHT - target_top)
    glyph = source.resize((ASCII_GLYPH_WIDTH, target_height), Image.Resampling.LANCZOS)

    cell = Image.new("L", (ASCII_CELL_WIDTH, CELL_HEIGHT), 0)
    cell.paste(glyph, (0, target_top))
    return pack_bitmap(cell)


def write_header(
    path: Path,
    codepoints: list[int],
    wide_glyphs: list[bytes],
    ascii_glyphs: list[bytes],
    font_path: Path,
    ascii_font_path: Path,
) -> None:
    lines = [
        "#ifndef LAUNCHER_LOCALIZATION_FONT_H",
        "#define LAUNCHER_LOCALIZATION_FONT_H",
        "",
        "#include <cstddef>",
        "#include <cstdint>",
        "",
        "// Generated from Noto Sans CJK SC Regular and Noto Sans Mono Regular.",
        "// Noto fonts are copyright Google and licensed under SIL OFL 1.1.",
        "// Printable ASCII is 6x12; only non-ASCII codepoints used by firmware strings are included.",
        f"static constexpr uint8_t kUiFontCellHeight = {CELL_HEIGHT};",
        f"static constexpr uint8_t kUiAsciiGlyphWidth = {ASCII_CELL_WIDTH};",
        f"static constexpr uint8_t kUiWideGlyphWidth = {WIDE_CELL_WIDTH};",
        f"static constexpr uint8_t kUiFontBaseline = {ASCII_BASELINE};",
        "",
        "struct UiAsciiGlyph {",
        f"    uint8_t bitmap[{ASCII_BITMAP_BYTES}]; // {ASCII_CELL_WIDTH}x{CELL_HEIGHT}, MSB first",
        "};",
        "",
        f"static constexpr UiAsciiGlyph kUiAsciiGlyphs[{len(ascii_glyphs)}] = {{",
    ]
    for bitmap in ascii_glyphs:
        bytes_text = ", ".join(f"0x{value:02X}" for value in bitmap)
        lines.append(f"    {{{{{bytes_text}}}}},")
    lines.extend(
        [
            "};",
            "",
            f"static constexpr size_t kUiAsciiGlyphCount = {len(ascii_glyphs)};",
            "",
            "struct UiBitmapGlyph {",
            "    uint16_t codepoint;",
            f"    uint8_t bitmap[{WIDE_BITMAP_BYTES}]; // {WIDE_CELL_WIDTH}x{CELL_HEIGHT}, MSB first",
            "};",
            "",
            f"static constexpr UiBitmapGlyph kUiBitmapGlyphs[{len(codepoints)}] = {{",
        ]
    )
    for codepoint, bitmap in zip(codepoints, wide_glyphs):
        bytes_text = ", ".join(f"0x{value:02X}" for value in bitmap)
        lines.append(f"    {{0x{codepoint:04X}, {{{bytes_text}}}}},")
    lines.extend(
        [
            "};",
            "",
            f"static constexpr size_t kUiBitmapGlyphCount = {len(codepoints)};",
            "",
            "#endif",
            "",
        ]
    )
    path.write_text("\n".join(lines), encoding="utf-8")
    print(
        f"generated {len(ascii_glyphs)} ASCII and {len(codepoints)} wide glyphs "
        f"({path.stat().st_size} bytes) from {ascii_font_path} and {font_path}"
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument(
        "--font",
        type=Path,
        default=Path("/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc"),
    )
    parser.add_argument("--font-index", type=int, default=2, help="Noto Sans CJK SC face index")
    parser.add_argument(
        "--ascii-font",
        type=Path,
        default=Path("/usr/share/fonts/noto/NotoSansMono-Regular.ttf"),
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=None,
        help="output header (defaults to src/localization_font.h)",
    )
    args = parser.parse_args()
    root = args.root.resolve()
    output = args.output or root / "src" / "localization_font.h"
    codepoints = source_codepoints(root)
    font = ImageFont.truetype(str(args.font), 64, index=args.font_index)
    ascii_font = ImageFont.truetype(str(args.ascii_font), 12)
    wide_glyphs = [rasterize_wide(font, codepoint) for codepoint in codepoints]
    ascii_glyphs = [rasterize_ascii(ascii_font, codepoint) for codepoint in range(0x20, 0x7F)]
    write_header(output, codepoints, wide_glyphs, ascii_glyphs, args.font, args.ascii_font)


if __name__ == "__main__":
    main()
