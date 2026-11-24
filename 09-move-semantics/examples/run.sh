#!/usr/bin/env bash
# Builds and runs the move-semantics examples.
ulimit -c 0

for example in rvalue_refs move_buffer noexcept_vector; do
    echo "=== $example"
    g++ -std=c++20 -Wall -Wextra "$example.cpp" -o "$example" && "./$example"
    rm -f "$example"
done

echo "=== copy_vs_move"
g++ -std=c++20 -O2 -Wall -Wextra copy_vs_move.cpp -o copy_vs_move && ./copy_vs_move
rm -f copy_vs_move

echo "=== rvalue_refs with -DSHOW_ERRORS"
g++ -std=c++20 -DSHOW_ERRORS -fsyntax-only rvalue_refs.cpp 2>&1 |
    grep -E 'error:' | sed -E 's#^[^ ]*/##'

echo "=== move_buffer with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address move_buffer.cpp -o move_buffer
output=$(./move_buffer 2>&1)
status=$?
printf '%s\n' "$output"
if [ "$status" -eq 0 ] && ! printf '%s\n' "$output" | grep -Eq 'ERROR: AddressSanitizer|LeakSanitizer'; then
    echo "AddressSanitizer: no errors"
fi
rm -f move_buffer
