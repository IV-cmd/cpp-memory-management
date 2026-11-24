#include <algorithm>
#include <iostream>

class FileBuffer {
public:
    int* data;
    int size;

    explicit FileBuffer(int count) : data(new int[count]{}), size(count) {}

    FileBuffer(const FileBuffer& other) : data(new int[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
    }

    FileBuffer& operator=(const FileBuffer& other) {
        if (this != &other) {
            int* newData = new int[other.size];
            std::copy(other.data, other.data + other.size, newData);
            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;
    }

    ~FileBuffer() {
        delete[] data;
    }
};

int main() {
    FileBuffer first(1000);
    first.data[0] = 42;

    FileBuffer second = first;
    std::cout << "first.data  = " << first.data << '\n';
    std::cout << "second.data = " << second.data << '\n';
    std::cout << "same allocation: " << (first.data == second.data ? "yes" : "no") << '\n';

    second.data[0] = 7;
    std::cout << "first.data[0] = " << first.data[0] << '\n';
    std::cout << "second.data[0] = " << second.data[0] << '\n';

    FileBuffer third(10);
    third = first;
    std::cout << "third.size = " << third.size << '\n';
    std::cout << "third.data[0] = " << third.data[0] << '\n';
    FileBuffer& alias = third;
    third = alias;
}
