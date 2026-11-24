#include <cstddef>
#include <iostream>
#include <vector>

std::size_t safeCopies = 0;
std::size_t safeGrowthMoves = 0;
std::size_t safePushMoves = 0;
std::size_t riskyCopies = 0;
std::size_t riskyGrowthMoves = 0;
std::size_t riskyPushMoves = 0;

struct Safe {
    bool temporary = true;

    Safe() = default;

    Safe(const Safe&) : temporary(false) {
        ++safeCopies;
    }

    Safe(Safe&& other) noexcept : temporary(false) {
        if (other.temporary) {
            ++safePushMoves;
        } else {
            ++safeGrowthMoves;
        }
    }
};

struct Risky {
    bool temporary = true;

    Risky() = default;

    Risky(const Risky&) : temporary(false) {
        ++riskyCopies;
    }

    Risky(Risky&& other) : temporary(false) {
        if (other.temporary) {
            ++riskyPushMoves;
        } else {
            ++riskyGrowthMoves;
        }
    }
};

int main() {
    {
        std::vector<Safe> buffers;
        for (int i = 0; i < 17; ++i) {
            buffers.push_back(Safe{});
        }
    }
    std::cout << "Safe: " << safeCopies << " copies, " << safeGrowthMoves
              << " moves during growth, " << safePushMoves << " push_back moves\n";

    {
        std::vector<Risky> buffers;
        for (int i = 0; i < 17; ++i) {
            buffers.push_back(Risky{});
        }
    }
    std::cout << "Risky: " << riskyCopies << " copies, " << riskyGrowthMoves
              << " moves during growth, " << riskyPushMoves << " push_back moves\n";
}
