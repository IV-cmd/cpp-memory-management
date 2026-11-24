#!/usr/bin/env bash
# Builds and runs the special-member examples.
ulimit -c 0

for example in rule_of_zero special_members file_handle; do
    echo "=== $example"
    g++ -std=c++20 -Wall -Wextra "$example.cpp" -o "$example" && "./$example"
    rm -f "$example"
done

echo "=== rule_of_zero with -DSHOW_ERRORS"
g++ -std=c++20 -DSHOW_ERRORS -fsyntax-only rule_of_zero.cpp 2>&1 |
    grep -E 'error:' | sed -E 's#^[^ ]*/##' | head -1

echo "=== file_handle with -DSHOW_ERRORS"
g++ -std=c++20 -DSHOW_ERRORS -fsyntax-only file_handle.cpp 2>&1 |
    grep -E 'use of deleted function' | sed -E 's#^[^ ]*/##' | head -1

echo "=== rule_of_zero with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address rule_of_zero.cpp -o rule_of_zero
output=$(./rule_of_zero 2>&1)
status=$?
printf '%s\n' "$output"
if [ "$status" -eq 0 ] && ! printf '%s\n' "$output" | grep -Eq 'ERROR: AddressSanitizer|LeakSanitizer'; then
    echo "AddressSanitizer: no errors"
fi
rm -f rule_of_zero
