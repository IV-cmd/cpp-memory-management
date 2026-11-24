#include <iostream>
#include <memory>
#include <utility>

struct Buffer {
    int id;

    explicit Buffer(int value) : id(value) {
        std::cout << "+ Buffer " << id << '\n';
    }

    ~Buffer() {
        std::cout << "- Buffer " << id << '\n';
    }
};

void writeToDisk(std::unique_ptr<Buffer> buffer) {
    std::cout << "writeToDisk owns Buffer " << buffer->id << '\n';
}

int main() {
    auto first = std::make_unique<int>(100);
    std::cout << "value: " << *first << '\n';
    int* originalAddress = first.get();
    auto second = std::move(first);
    std::cout << "first is nullptr: " << (first == nullptr ? "yes" : "no") << '\n';
    std::cout << "same object: " << (second.get() == originalAddress ? "yes" : "no") << '\n';

#ifdef SHOW_ERRORS
    auto copy = second;
#endif

    auto buffer = std::make_unique<Buffer>(1);
    writeToDisk(std::move(buffer));
    std::cout << "back in main, buffer is empty: " << (buffer == nullptr ? "yes" : "no") << '\n';
}
