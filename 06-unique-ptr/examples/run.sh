#!/usr/bin/env bash
# Builds and runs the unique_ptr ownership examples.
ulimit -c 0

for example in raw_vs_unique move_ownership passing custom_deleter; do
    echo "=== $example"
    g++ -std=c++20 -Wall -Wextra "$example.cpp" -o "$example" && "./$example"
    rm -f "$example"
done

echo "=== raw_vs_unique with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address raw_vs_unique.cpp -o raw_vs_unique
./raw_vs_unique 2>&1 |
    grep -E 'raw version|unique_ptr version|Direct leak|#[0-9]+ .*(processFileRaw|operator new)|SUMMARY: AddressSanitizer' |
    sed -E 's/0x[0-9a-f]+ in //g; s/0x[0-9a-f]+/<address>/g; s# at [^ ]+##g; s#/[^ ]*/##g'
rm -f raw_vs_unique

echo "=== move_ownership with -DSHOW_ERRORS"
g++ -std=c++20 -DSHOW_ERRORS -fsyntax-only move_ownership.cpp 2>&1 |
    grep -E 'use of deleted function' |
    sed -E 's#^[^ ]*/##' | head -1

echo "=== passing with -DSHOW_BUG and AddressSanitizer"
g++ -std=c++20 -g -DSHOW_BUG -fsanitize=address passing.cpp -o passing
./passing 2>&1 |
    grep -E 'ERROR: AddressSanitizer|freed by|previously allocated|#[0-9]+ .*( main |operator new|operator delete)|SUMMARY: AddressSanitizer' |
    sed -E 's/0x[0-9a-f]+ in //g; s/0x[0-9a-f]+/<address>/g; s# at [^ ]+##g; s#/[^ ]*/##g'
rm -f passing
