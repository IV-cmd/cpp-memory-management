#!/usr/bin/env bash
# Builds each ownership example and captures the intentional memory errors.
ulimit -c 0

echo "=== normal builds"
g++ -std=c++20 -Wall -Wextra ownership_bugs.cpp -o ownership_bugs
g++ -std=c++20 -Wall -Wextra borrow.cpp -o borrow && ./borrow
rm -f ownership_bugs borrow

echo "=== ownership_bugs with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address ownership_bugs.cpp -o ownership_bugs
for mistake in nobody everyone early; do
    echo "--- $mistake"
    ./ownership_bugs "$mistake" 2>&1 |
        grep -E 'ERROR: AddressSanitizer|Direct leak|freed by|previously allocated|allocated by|#[0-9]+ .*(RequestHandler|ChecksumService|StorageWriter|operator new|operator delete)|SUMMARY: AddressSanitizer' |
        sed -E 's/0x[0-9a-f]+ in //g; s/0x[0-9a-f]+/<address>/g; s# at [^ ]+##g; s#/[^ ]*/##g'
done
rm -f ownership_bugs

echo "=== borrow with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address borrow.cpp -o borrow
output=$(./borrow 2>&1)
status=$?
printf '%s\n' "$output"
if [ "$status" -eq 0 ] && ! printf '%s\n' "$output" | grep -Eq 'ERROR: AddressSanitizer|LeakSanitizer'; then
    echo "AddressSanitizer: no errors"
fi
rm -f borrow
