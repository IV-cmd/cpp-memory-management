#include <cstddef>
#include <iostream>
#include <span>

int calculateChecksum(const int* buffer, std::size_t size) {
    int checksum = 0;
    for (std::size_t i = 0; i < size; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

void writeToDisk(std::span<const int> buffer) {
    std::cout << "wrote " << buffer.size_bytes() << " bytes\n";
}

void processFile() {
    constexpr std::size_t size = 1000;
    int* buffer = new int[size];
    for (std::size_t i = 0; i < size; ++i) {
        buffer[i] = static_cast<int>(i);
    }

    std::cout << "checksum: " << calculateChecksum(buffer, size) << '\n';
    writeToDisk(std::span<const int>(buffer, size));
    delete[] buffer;
}

int main() {
    processFile();
}
