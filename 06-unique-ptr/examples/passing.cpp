#include <cstddef>
#include <iostream>
#include <memory>
#include <span>
#include <utility>

using Buffer = std::unique_ptr<char[]>;

void storageWorker(Buffer buffer) {
    std::cout << "storageWorker owns buffer: " << (buffer != nullptr ? "yes" : "no") << '\n';
}

void logOwner(const std::unique_ptr<char[]>& buffer) {
    std::cout << "logOwner sees buffer: " << (buffer != nullptr ? "not empty" : "empty") << '\n';
}

int calculateChecksum(std::span<const char> buffer) {
    int checksum = 0;
    for (char value : buffer) {
        checksum += value;
    }
    return checksum;
}

int main() {
    auto transferred = std::make_unique<char[]>(4096);
    storageWorker(std::move(transferred));
    std::cout << "after storageWorker, handler is "
              << (transferred == nullptr ? "empty" : "not empty") << '\n';

    auto handlerBuffer = std::make_unique<char[]>(4096);
    handlerBuffer[0] = 'A';
    logOwner(handlerBuffer);
    std::cout << "after logOwner, handler still owns buffer: "
              << (handlerBuffer != nullptr ? "yes" : "no") << '\n';

    std::span<const char> view(handlerBuffer.get(), 4096);
    std::cout << "checksum: " << calculateChecksum(view) << '\n';
    std::cout << "after checksum, handler still owns buffer: "
              << (handlerBuffer != nullptr ? "yes" : "no") << '\n';

    auto buffer = std::make_unique<int[]>(1000);
    buffer[0] = 42;
    int* checksumBuffer = buffer.get();
    int* writerBuffer = buffer.get();
    std::cout << "checksum view: " << checksumBuffer[0] << '\n';
    std::cout << "writer view: " << writerBuffer[0] << '\n';
#ifdef SHOW_BUG
    delete[] checksumBuffer;
#endif
}
