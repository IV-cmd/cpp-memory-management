#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

class StorageBuffer {
    std::vector<char> data;

public:
    explicit StorageBuffer(std::size_t size) : data(size) {}

    void write(std::size_t index, char value) {
        data.at(index) = value;
    }

    char read(std::size_t index) const {
        return data.at(index);
    }

    std::size_t size() const {
        return data.size();
    }

    const char* address() const {
        return data.data();
    }
};

int main() {
    StorageBuffer first(1'000'000);
    first.write(0, 'A');
    StorageBuffer second = first;
    std::cout << "first  buffer at " << static_cast<const void*>(first.address()) << '\n';
    std::cout << "second buffer at " << static_cast<const void*>(second.address()) << '\n';
    std::cout << "independent copy: " << (first.address() != second.address() ? "yes" : "no") << '\n';

    second.write(0, 'B');
    std::cout << "first.read(0) = " << first.read(0) << '\n';
    std::cout << "second.read(0) = " << second.read(0) << '\n';

    const char* before = second.address();
    StorageBuffer third = std::move(second);
    std::cout << "third took second's buffer: " << (third.address() == before ? "yes" : "no") << '\n';

    try {
        first.read(1'000'000);
    } catch (const std::out_of_range& error) {
        std::cout << "out_of_range: " << error.what() << '\n';
    }

#ifdef SHOW_ERRORS
    StorageBuffer implicit = 4096;
#endif
}
