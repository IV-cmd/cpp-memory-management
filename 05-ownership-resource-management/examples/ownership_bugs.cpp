#include <cstddef>
#include <iostream>
#include <string_view>

int ChecksumService(const int* buffer) {
    int checksum = 0;
    for (std::size_t i = 0; i < 1000; ++i) {
        checksum += buffer[i];
    }
    std::cout << "ChecksumService read checksum " << checksum << '\n';
    return checksum;
}

void StorageWriter(int* buffer, bool deleteBuffer) {
    std::cout << "StorageWriter received the buffer\n";
    if (deleteBuffer) {
        delete[] buffer;
        std::cout << "StorageWriter deleted the buffer\n";
    }
}

void RequestHandler(std::string_view mistake) {
    int* buffer = new int[1000];
    int* checksumBuffer = buffer;
    int* writerBuffer = buffer;

    for (std::size_t i = 0; i < 1000; ++i) {
        buffer[i] = static_cast<int>(i);
    }

    if (mistake == "nobody") {
        ChecksumService(checksumBuffer);
        StorageWriter(writerBuffer, false);
    } else if (mistake == "everyone") {
        ChecksumService(checksumBuffer);
        delete[] buffer;
        StorageWriter(writerBuffer, true);
    } else if (mistake == "early") {
        StorageWriter(writerBuffer, true);
        ChecksumService(checksumBuffer);
    }
}

int main(int argc, char* argv[]) {
    const std::string_view mistake = argc > 1 ? argv[1] : "nobody";
    RequestHandler(mistake);
}
