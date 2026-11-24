#!/usr/bin/env bash
# Builds and runs every example. stack_overflow crashes on purpose.
echo "=== regions"
g++ -std=c++20 -Wall -Wextra regions.cpp -o regions && ./regions
echo "=== size regions (bytes in each section of the executable)"
size regions
rm -f regions
echo "=== stack_frames"
g++ -std=c++20 -Wall -Wextra stack_frames.cpp -o stack_frames && ./stack_frames
rm -f stack_frames
echo "=== stack size limit (KiB)"
ulimit -s
echo "=== stack_overflow (crashes on purpose)"
g++ -std=c++20 -Wall -Wextra stack_overflow.cpp -o stack_overflow && ./stack_overflow
echo "exit status: $?"
rm -f stack_overflow
