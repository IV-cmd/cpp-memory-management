#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::vector<int> first(10'000'000, 1);
    std::array<long long, 5> copyTimes{};
    std::array<long long, 5> moveTimes{};
    int copiedValue = 0;
    bool sameStorage = false;
    std::size_t movedFromSize = 0;

    for (std::size_t trial = 0; trial < copyTimes.size(); ++trial) {
        const auto copyStart = std::chrono::steady_clock::now();
        std::vector<int> copy = first;
        const auto copyEnd = std::chrono::steady_clock::now();
        copyTimes[trial] =
            std::chrono::duration_cast<std::chrono::microseconds>(copyEnd - copyStart).count();
        copiedValue = copy[123] + copy.back();

        const int* before = first.data();
        const auto moveStart = std::chrono::steady_clock::now();
        std::vector<int> moved = std::move(first);
        const auto moveEnd = std::chrono::steady_clock::now();
        moveTimes[trial] =
            std::chrono::duration_cast<std::chrono::microseconds>(moveEnd - moveStart).count();
        sameStorage = moved.data() == before;
        movedFromSize = first.size();
        first = std::move(moved);
    }

    std::sort(copyTimes.begin(), copyTimes.end());
    std::sort(moveTimes.begin(), moveTimes.end());
    std::cout << "copy: " << copyTimes[2] << " us\n";
    std::cout << "move: " << moveTimes[2] << " us\n";
    std::cout << "moved.data() == before: " << (sameStorage ? "yes" : "no") << '\n';
    std::cout << "first.size() after move: " << movedFromSize << '\n';
    std::cout << "copy check: " << copiedValue << '\n';

    int value = 10;
    int destination = std::move(value);
    std::cout << "int move: source = " << value << ", destination = " << destination << '\n';
}
