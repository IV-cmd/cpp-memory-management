#!/usr/bin/env bash
# Builds and runs every example, runs the dangling pointer under AddressSanitizer,
# then rebuilds scope_lifetime with -DSHOW_ERRORS to show the scope error.
for f in scope_lifetime storage_durations; do
    echo "=== $f"
    g++ -std=c++20 -Wall -Wextra -pthread $f.cpp -o $f && ./$f
    rm -f $f
done
echo "=== dangling with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address dangling.cpp -o dangling && ./dangling 2>&1 | grep -E 'ERROR|READ of|freed by|previously allocated|#[01] .*(main|operator)|SUMMARY' | sed -E 's/ at pc.*//; s/0x[0-9a-f]+ in //; s#/[^ ]*/##'
rm -f dangling
echo "=== scope_lifetime with -DSHOW_ERRORS"
g++ -std=c++20 -DSHOW_ERRORS -fsyntax-only scope_lifetime.cpp 2>&1 | grep error
