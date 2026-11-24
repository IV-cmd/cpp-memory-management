#!/usr/bin/env bash
# Builds and runs the copy-semantics examples.
ulimit -c 0

for example in copy_basics deep_copy; do
    echo "=== $example"
    g++ -std=c++20 -Wall -Wextra "$example.cpp" -o "$example" && "./$example"
    rm -f "$example"
done

echo "=== shallow_copy"
g++ -std=c++20 -Wall -Wextra shallow_copy.cpp -o shallow_copy
output=$(./shallow_copy 2>&1)
status=$?
printf '%s\n' "$output"
echo "exit status: $status"
rm -f shallow_copy

echo "=== copy_basics with -DSHOW_ERRORS"
g++ -std=c++20 -DSHOW_ERRORS -fsyntax-only copy_basics.cpp 2>&1 |
    grep -E 'invalid constructor' | sed -E 's#^[^ ]*/##' | head -1

echo "=== shallow_copy with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address shallow_copy.cpp -o shallow_copy
./shallow_copy 2>&1 |
    grep -E 'ERROR: AddressSanitizer: attempting double-free|#[0-9]+ .*(FileBuffer|main|operator delete)|freed by thread|previously allocated by|SUMMARY: AddressSanitizer' |
    sed -E 's/0x[0-9a-f]+ in //g; s/0x[0-9a-f]+/<address>/g; s# at [^ ]+##g; s#/[^ ]*/##g'
rm -f shallow_copy

echo "=== deep_copy with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address deep_copy.cpp -o deep_copy
output=$(./deep_copy 2>&1)
status=$?
printf '%s\n' "$output" | sed -E 's/0x[0-9a-f]+/<address>/g'
if [ "$status" -eq 0 ] && ! printf '%s\n' "$output" | grep -Eq 'ERROR: AddressSanitizer|LeakSanitizer'; then
    echo "AddressSanitizer: no errors"
fi
rm -f deep_copy
