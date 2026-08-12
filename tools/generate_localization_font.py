#!/usr/bin/env python3
"""Generate the firmware's compact Simplified Chinese bitmap glyph table.

The launcher embeds only the non-ASCII characters used by its localization
catalog. Glyphs come directly from Fusion Pixel Font's native 8px zh_hans BDF,
so no antialiasing or resampling can blur the one-pixel strokes.
"""

from __future__ import annotations

import argparse
import hashlib
import io
from pathlib import Path
import urllib.request
import zipfile


CELL_HEIGHT = 8
WIDE_CELL_WIDTH = 8
ASCII_CELL_WIDTH = 6
WIDE_BITMAP_BYTES = (WIDE_CELL_WIDTH * CELL_HEIGHT + 7) // 8

FUSION_PIXEL_VERSION = "2026.08.11"
FUSION_PIXEL_ARCHIVE = f"fusion-pixel-font-8px-monospaced-bdf-v{FUSION_PIXEL_VERSION}.zip"
FUSION_PIXEL_URL = (
    "https://github.com/TakWolf/fusion-pixel-font/releases/download/"
    f"{FUSION_PIXEL_VERSION}/{FUSION_PIXEL_ARCHIVE}"
)
FUSION_PIXEL_SHA256 = "8e2147c08c76f99d1e670bf6ad30b35787a1fb6a8e69626a73c8f4705249a69e"
FUSION_PIXEL_BDF = "fusion-pixel-8px-monospaced-zh_hans.bdf"


def source_codepoints(root: Path) -> list[int]:
    # The localization catalog is the only firmware source of non-ASCII text
    # that is intentionally drawn. Scanning comments and board notes would add
    # unrelated glyphs to every board's binary.
    path = root / "src" / "localization.cpp"
    try:
        text = path.read_text(encoding="utf-8")
    except (OSError, UnicodeDecodeError):
        return []
    return sorted({ord(char) for char in text if 0x80 <= ord(char) <= 0xFFFF})


def load_font_archive(path: Path | None) -> bytes:
    if path is not None:
        archive = path.read_bytes()
    else:
        print(f"downloading {FUSION_PIXEL_URL}")
        with urllib.request.urlopen(FUSION_PIXEL_URL, timeout=60) as response:
            archive = response.read()

    digest = hashlib.sha256(archive).hexdigest()
    if digest != FUSION_PIXEL_SHA256:
        raise ValueError(
            f"Fusion Pixel Font archive SHA-256 mismatch: expected {FUSION_PIXEL_SHA256}, got {digest}"
        )
    return archive


def load_bdf(archive: bytes) -> str:
    with zipfile.ZipFile(io.BytesIO(archive)) as package:
        try:
            return package.read(FUSION_PIXEL_BDF).decode("ascii")
        except KeyError as error:
            raise ValueError(f"{FUSION_PIXEL_BDF} is missing from the font archive") from error


def parse_bdf_glyphs(bdf: str, required_codepoints: set[int]) -> dict[int, bytes]:
    glyphs: dict[int, bytes] = {}
    encoding: int | None = None
    dwidth: tuple[int, int] | None = None
    bounds: tuple[int, int, int, int] | None = None
    bitmap: list[int] = []
    reading_bitmap = False

    for raw_line in bdf.splitlines():
        fields = raw_line.split()
        if not fields:
            continue
        keyword = fields[0]
        if keyword == "STARTCHAR":
            encoding = None
            dwidth = None
            bounds = None
            bitmap = []
            reading_bitmap = False
        elif keyword == "ENCODING":
            encoding = int(fields[1])
        elif keyword == "DWIDTH":
            dwidth = (int(fields[1]), int(fields[2]))
        elif keyword == "BBX":
            bounds = tuple(map(int, fields[1:5]))
        elif keyword == "BITMAP":
            reading_bitmap = True
        elif keyword == "ENDCHAR":
            if encoding is not None and encoding in required_codepoints:
                if dwidth != (WIDE_CELL_WIDTH, 0) or bounds != (WIDE_CELL_WIDTH, CELL_HEIGHT, 0, -1):
                    raise ValueError(
                        f"U+{encoding:04X} has incompatible Fusion Pixel Font metrics: "
                        f"DWIDTH={dwidth}, BBX={bounds}"
                    )
                if len(bitmap) != CELL_HEIGHT:
                    raise ValueError(f"U+{encoding:04X} has {len(bitmap)} rows, expected {CELL_HEIGHT}")
                # Fusion's 8px BDF reserves its first row and draws through the
                # eighth. Shift up one row to match the native ASCII top edge and
                # preserve the launcher's existing seven-visible-row contract.
                glyphs[encoding] = bytes(bitmap[1:] + [0])
            reading_bitmap = False
        elif reading_bitmap:
            bitmap.append(int(raw_line, 16))

    return glyphs


def write_header(path: Path, codepoints: list[int], glyphs: dict[int, bytes]) -> None:
    missing = [codepoint for codepoint in codepoints if codepoint not in glyphs]
    if missing:
        values = ", ".join(f"U+{codepoint:04X}" for codepoint in missing)
        raise ValueError(f"Fusion Pixel Font is missing required glyphs: {values}")

    lines = [
        "#ifndef LAUNCHER_LOCALIZATION_FONT_H",
        "#define LAUNCHER_LOCALIZATION_FONT_H",
        "",
        "#include <cstddef>",
        "#include <cstdint>",
        "",
        f"// Generated from Fusion Pixel Font {FUSION_PIXEL_VERSION}, 8px monospaced zh_hans.",
        "// Copyright (c) 2022 TakWolf. Licensed under SIL OFL 1.1.",
        "// ASCII uses the display driver's native 5x7 glyphs in 6x8 cells.",
        "// Chinese uses seven visible rows in 8x8 cells to keep the same height and top edge.",
        f"static constexpr uint8_t kUiFontCellHeight = {CELL_HEIGHT};",
        f"static constexpr uint8_t kUiAsciiGlyphWidth = {ASCII_CELL_WIDTH};",
        f"static constexpr uint8_t kUiWideGlyphWidth = {WIDE_CELL_WIDTH};",
        "",
        "struct UiBitmapGlyph {",
        "    uint16_t codepoint;",
        f"    uint8_t bitmap[{WIDE_BITMAP_BYTES}]; // {WIDE_CELL_WIDTH}x{CELL_HEIGHT}, MSB first",
        "};",
        "",
        f"static constexpr UiBitmapGlyph kUiBitmapGlyphs[{len(codepoints)}] = {{",
    ]
    for codepoint in codepoints:
        bytes_text = ", ".join(f"0x{value:02X}" for value in glyphs[codepoint])
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
        f"generated {len(codepoints)} Fusion Pixel Font 8x8 glyphs "
        f"({path.stat().st_size} bytes)"
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument(
        "--font-archive",
        type=Path,
        default=None,
        help="local Fusion Pixel Font release archive; otherwise download the pinned release",
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
    archive = load_font_archive(args.font_archive)
    glyphs = parse_bdf_glyphs(load_bdf(archive), set(codepoints))
    write_header(output, codepoints, glyphs)


if __name__ == "__main__":
    main()
