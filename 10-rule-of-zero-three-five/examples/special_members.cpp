#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

struct RawOwner {
    int* data = nullptr;

    ~RawOwner() {
        delete[] data;
    }
};

struct ZeroVector {
    std::vector<int> data;
};

struct ZeroUnique {
    std::unique_ptr<int[]> data;
};

struct DtorOnly {
    std::vector<int> data;

    ~DtorOnly() {}
};

template <typename T>
void printTraits(const char* name) {
    std::cout << name << ": "
              << (std::is_copy_constructible_v<T> ? "yes" : "no") << " / "
              << (std::is_move_constructible_v<T> ? "yes" : "no") << " / "
              << (std::is_nothrow_move_constructible_v<T> ? "yes" : "no") << '\n';
}

int main() {
    std::cout << "type: copy-constructible / move-constructible / nothrow-move-constructible\n";
    printTraits<RawOwner>("RawOwner");
    printTraits<ZeroVector>("ZeroVector");
    printTraits<ZeroUnique>("ZeroUnique");
    printTraits<DtorOnly>("DtorOnly");

    {
        ZeroVector a{std::vector<int>(1000)};
        const int* vectorAddress = a.data.data();
        ZeroVector b = std::move(a);
        std::cout << "ZeroVector: moved (same buffer: "
                  << (b.data.data() == vectorAddress ? "yes" : "no")
                  << ", a.data.size() = " << a.data.size() << ")\n";
    }

    {
        DtorOnly a{std::vector<int>(1000)};
        const int* vectorAddress = a.data.data();
        DtorOnly b = std::move(a);
        std::cout << "DtorOnly: copied (same buffer: "
                  << (b.data.data() == vectorAddress ? "yes" : "no")
                  << ", a.data.size() = " << a.data.size() << ")\n";
    }
}
