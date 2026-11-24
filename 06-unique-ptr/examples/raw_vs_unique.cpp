#include <iostream>
#include <memory>
#include <stdexcept>

void processFileRaw() {
    int* buffer = new int[1000];
    buffer[0] = 42;
    throw std::runtime_error("Disk error");
    delete[] buffer;
}

void processFileUnique() {
    auto buffer = std::make_unique<int[]>(1000);
    buffer[0] = 42;
    throw std::runtime_error("Disk error");
}

int main() {
    try {
        processFileRaw();
    } catch (const std::runtime_error& error) {
        std::cout << "raw version: " << error.what() << '\n';
    }

    try {
        processFileUnique();
    } catch (const std::runtime_error& error) {
        std::cout << "unique_ptr version: " << error.what() << '\n';
    }
}
