#!/usr/bin/env bash
# Builds and runs every example. unique_ptr is also rebuilt with -DSHOW_ERRORS
# to show the copy error, and process_file runs under AddressSanitizer.
for f in raii_file fd_leak lock_guard unique_ptr; do
    echo "=== $f"
    g++ -std=c++20 -Wall -Wextra $f.cpp -o $f && ./$f
    rm -f $f
done
echo "=== unique_ptr with -DSHOW_ERRORS"
g++ -std=c++20 -DSHOW_ERRORS -fsyntax-only unique_ptr.cpp 2>&1 | grep -E 'error' | sed -E 's#^[^ ]*/##' | head -2
echo "=== caveats"
g++ -std=c++20 -Wall -Wextra caveats.cpp -o caveats
for how in return exit abort; do
    ./caveats $how
    echo "  exit status: $?"
done 2>/dev/null
rm -f caveats
echo "=== process_file with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address process_file.cpp -o process_file && ./process_file 2>&1 | grep -E 'Processing|Direct leak|#[01] .*(handleRequest|operator)|SUMMARY' | sed -E 's/0x[0-9a-f]+ in //; s#/[^ ]*/##'
rm -f process_file
