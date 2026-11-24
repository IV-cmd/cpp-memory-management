#!/usr/bin/env bash
# Builds and runs the shared_ptr and weak_ptr examples.
ulimit -c 0

for example in use_count connection cycle weak_lock sizes_allocs; do
    echo "=== $example"
    g++ -std=c++20 -Wall -Wextra "$example.cpp" -o "$example" && "./$example"
    rm -f "$example"
done

echo "=== cycle with AddressSanitizer"
g++ -std=c++20 -g -fsanitize=address cycle.cpp -o cycle
./cycle 2>&1 |
    grep -E 'node use_count|monitor use_count|block ended|Direct leak|Indirect leak|SUMMARY: AddressSanitizer' |
    sed -E 's/0x[0-9a-f]+ in //g; s/0x[0-9a-f]+/<address>/g; s# at [^ ]+##g; s#/[^ ]*/##g'
rm -f cycle

echo "=== cycle with -DWEAK"
g++ -std=c++20 -Wall -Wextra -DWEAK cycle.cpp -o cycle && ./cycle
rm -f cycle
