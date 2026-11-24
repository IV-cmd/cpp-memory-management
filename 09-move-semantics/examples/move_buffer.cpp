#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>

class FileBuffer {
public:
    int* data;
    std::size_t size;

    explicit FileBuffer(std::size_t count) : data(new int[count]{}), size(count) {
        std::cout << "allocated " << size << " ints\n";
    }

    FileBuffer(const FileBuffer& other) : data(new int[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
        std::cout << "copy constructor (allocated " << size << " ints)\n";
    }

    FileBuffer& operator=(const FileBuffer& other) {
        if (this != &other) {
            int* newData = new int[other.size];
            std::copy(other.data, other.data + other.size, newData);
            delete[] data;
            data = newData;
            size = other.size;
        }
        std::cout << "copy assignment\n";
        return *this;
    }

    FileBuffer(FileBuffer&& other) noexcept
        : data(std::exchange(other.data, nullptr)), size(std::exchange(other.size, 0)) {
        std::cout << "move constructor\n";
    }

    FileBuffer& operator=(FileBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = std::exchange(other.data, nullptr);
            size = std::exchange(other.size, 0);
        }
        std::cout << "move assignment\n";
        return *this;
    }

    ~FileBuffer() {
        if (data != nullptr) {
            std::cout << "~FileBuffer releasing " << size << " ints\n";
            delete[] data;
        } else {
            std::cout << "~FileBuffer (empty)\n";
        }
    }
};

int main() {
    FileBuffer first(1000);
    int* original = first.data;
    FileBuffer second = std::move(first);
    std::cout << "second.data == original: " << (second.data == original ? "yes" : "no") << '\n';
    std::cout << "first.data: " << (first.data == nullptr ? "nullptr" : "not null") << '\n';
    std::cout << "first.size: " << first.size << '\n';

    FileBuffer third(10);
    third = std::move(second);
    std::cout << "third.data == original: " << (third.data == original ? "yes" : "no") << '\n';
    std::cout << "second.data: " << (second.data == nullptr ? "nullptr" : "not null") << '\n';
    std::cout << "second.size: " << second.size << '\n';

    FileBuffer copy = third;
    std::cout << "copy.size: " << copy.size << '\n';
}
