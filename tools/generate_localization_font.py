#!/usr/bin/env python3
"""Generate the firmware's compact Simplified Chinese bitmap glyph table.

The launcher only needs the non-ASCII characters present in firmware source
strings. Rendering each glyph into the same seven visible rows as the native
5x7 ASCII font keeps mixed text aligned inside the existing 8-pixel line height.
"""

from __future__ import annotations

import argparse
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont


CELL_HEIGHT = 8
WIDE_CELL_WIDTH = 8
WIDE_INNER_WIDTH = 8
WIDE_INNER_HEIGHT = 7
ASCII_CELL_WIDTH = 6
WIDE_BITMAP_BYTES = (WIDE_CELL_WIDTH * CELL_HEIGHT + 7) // 8


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
    scale = min(WIDE_INNER_WIDTH / glyph.width, WIDE_INNER_HEIGHT / glyph.height)
    size = (max(1, round(glyph.width * scale)), max(1, round(glyph.height * scale)))
    glyph = glyph.resize(size, Image.Resampling.LANCZOS)

    cell = Image.new("L", (WIDE_CELL_WIDTH, CELL_HEIGHT), 0)
    # Native 5x7 ASCII starts at the cursor's top edge and leaves the eighth
    # scanline empty. Use the same top edge and visible height for Chinese.
    cell.paste(glyph, ((WIDE_CELL_WIDTH - size[0]) // 2, 0))
    return pack_bitmap(cell)


def write_header(
    path: Path,
    codepoints: list[int],
    wide_glyphs: list[bytes],
    font_path: Path,
) -> None:
    lines = [
        "#ifndef LAUNCHER_LOCALIZATION_FONT_H",
        "#define LAUNCHER_LOCALIZATION_FONT_H",
        "",
        "#include <cstddef>",
        "#include <cstdint>",
        "",
        "// Generated from Noto Sans CJK SC Regular.",
        "// Noto fonts are copyright Google and licensed under SIL OFL 1.1.",
        "// ASCII uses the display driver's native 5x7 glyphs in 6x8 cells.",
        "// Chinese uses seven visible rows in 8x8 cells to keep the same height and top edge.",
        f"static constexpr uint8_t kUiFontCellHeight = {CELL_HEIGHT};",
        f"static constexpr uint8_t kUiAsciiGlyphWidth = {ASCII_CELL_WIDTH};",
        f"static constexpr uint8_t kUiWideGlyphWidth = {WIDE_CELL_WIDTH};",
    ]
    lines.extend(
        [
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
    print(f"generated {len(codepoints)} 8x8 glyphs ({path.stat().st_size} bytes) from {font_path}")


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
    wide_glyphs = [rasterize_wide(font, codepoint) for codepoint in codepoints]
    write_header(output, codepoints, wide_glyphs, args.font)


if __name__ == "__main__":
    main()
