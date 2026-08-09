#!/usr/bin/env python3
"""Generate the firmware's compact UTF-8 bitmap glyph table.

The launcher only needs the non-ASCII characters present in firmware source
strings.  Rendering a 12x12 subset keeps flash usage small while retaining a
real glyph for every shipped Simplified Chinese translation and its punctuation.
"""

from __future__ import annotations

import argparse
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont


CELL_SIZE = 12
INNER_SIZE = 11
BITMAP_BYTES = (CELL_SIZE * CELL_SIZE + 7) // 8
SOURCE_SUFFIXES = {".c", ".cpp", ".h", ".hpp", ".ino"}


def source_codepoints(root: Path) -> list[int]:
    codepoints: set[int] = set()
    for source_root in (root / "src", root / "boards"):
        for path in source_root.rglob("*"):
            if not path.is_file() or path.suffix not in SOURCE_SUFFIXES:
                continue
            try:
                text = path.read_text(encoding="utf-8")
            except UnicodeDecodeError:
                continue
            codepoints.update(ord(char) for char in text if 0x80 <= ord(char) <= 0xFFFF)
    return sorted(codepoints)


def rasterize(font: ImageFont.FreeTypeFont, codepoint: int) -> bytes:
    char = chr(codepoint)
    canvas = Image.new("L", (96, 96), 0)
    ImageDraw.Draw(canvas).text((8, 0), char, font=font, fill=255)
    bounds = canvas.getbbox()
    if bounds is None:
        return bytes(BITMAP_BYTES)

    glyph = canvas.crop(bounds)
    scale = min(INNER_SIZE / glyph.width, INNER_SIZE / glyph.height)
    size = (max(1, round(glyph.width * scale)), max(1, round(glyph.height * scale)))
    glyph = glyph.resize(size, Image.Resampling.LANCZOS)

    cell = Image.new("L", (CELL_SIZE, CELL_SIZE), 0)
    cell.paste(glyph, ((CELL_SIZE - size[0]) // 2, (CELL_SIZE - size[1]) // 2))

    bitmap = bytearray(BITMAP_BYTES)
    for row in range(CELL_SIZE):
        for column in range(CELL_SIZE):
            if cell.getpixel((column, row)) < 110:
                continue
            bit = row * CELL_SIZE + column
            bitmap[bit // 8] |= 1 << (7 - (bit % 8))
    return bytes(bitmap)


def write_header(path: Path, codepoints: list[int], glyphs: list[bytes], font_path: Path) -> None:
    lines = [
        "#ifndef LAUNCHER_LOCALIZATION_FONT_H",
        "#define LAUNCHER_LOCALIZATION_FONT_H",
        "",
        "#include <cstddef>",
        "#include <cstdint>",
        "",
        "// Generated from Noto Sans CJK SC Regular.",
        "// Noto fonts are copyright Google and licensed under SIL OFL 1.1.",
        "// Only the non-ASCII codepoints used by firmware source strings are included.",
        "struct UiBitmapGlyph {",
        "    uint16_t codepoint;",
        f"    uint8_t bitmap[{BITMAP_BYTES}]; // {CELL_SIZE}x{CELL_SIZE}, MSB first",
        "};",
        "",
        f"static constexpr UiBitmapGlyph kUiBitmapGlyphs[{len(codepoints)}] = {{",
    ]
    for codepoint, bitmap in zip(codepoints, glyphs):
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
    print(f"generated {len(codepoints)} glyphs ({path.stat().st_size} bytes) from {font_path}")


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
    glyphs = [rasterize(font, codepoint) for codepoint in codepoints]
    write_header(output, codepoints, glyphs, args.font)


if __name__ == "__main__":
    main()
