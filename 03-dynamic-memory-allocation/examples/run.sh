#!/usr/bin/env bash
# Builds and runs every example. leak, use_after_free and double_delete are broken
# on purpose and are run both plainly and under AddressSanitizer.
asan() { grep -E 'ERROR|READ of|freed by|previously allocated|Direct leak|#[01] .*(main|operator|processFile)|SUMMARY' | sed -E 's/ at pc.*//; s/0x[0-9a-f]+ in //; s#/[^ ]*/##'; }

echo "=== new_delete"
g++ -std=c++20 -Wall -Wextra new_delete.cpp -o new_delete && ./new_delete
echo "=== new_delete -DMISMATCH with AddressSanitizer"
g++ -std=c++20 -g -DMISMATCH -fsanitize=address new_delete.cpp -o new_delete 2>&1 | grep -E 'warning' | sed -E 's#^[^ ]*/##'
./new_delete 2>&1 | grep -E 'ERROR|SUMMARY' | sed -E 's/ at pc.*//; s#/[^ ]*/##'
rm -f new_delete

echo "=== leak"
g++ -std=c++20 -Wall -Wextra leak.cpp -o leak && ./leak
echo "=== leak with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address leak.cpp -o leak && ./leak 2>&1 | grep -E 'Direct leak|SUMMARY'
rm -f leak

echo "=== use_after_free"
g++ -std=c++20 -Wall -Wextra use_after_free.cpp -o use_after_free && ./use_after_free
echo "=== use_after_free with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address use_after_free.cpp -o use_after_free && ./use_after_free 2>&1 | asan
rm -f use_after_free

echo "=== double_delete"
g++ -std=c++20 -Wall -Wextra double_delete.cpp -o double_delete && ./double_delete
echo "exit status: $?"
echo "=== double_delete with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address double_delete.cpp -o double_delete && ./double_delete 2>&1 | asan
rm -f double_delete
echo "=== leak at -O1 with AddressSanitizer (the optimiser removes the allocation)"
g++ -std=c++20 -g -O1 -fsanitize=address leak.cpp -o leak && ./leak 2>&1
rm -f leak
