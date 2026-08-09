#!/usr/bin/env sh
set -eu

test_dir=$(mktemp -d "${TMPDIR:-/tmp}/m5launcher-localization.XXXXXX")
trap 'rm -rf "$test_dir"' EXIT

c++ -std=c++17 -Wall -Wextra -DLOCALIZATION_HOST_TEST \
    -Itests/stubs -Isrc \
    tests/localization_test.cpp src/localization.cpp \
    -o "$test_dir/localization_test"
"$test_dir/localization_test"
