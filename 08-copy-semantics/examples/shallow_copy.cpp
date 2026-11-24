#include <iostream>

class FileBuffer {
public:
    int* data;

    explicit FileBuffer(int size) : data(new int[size]) {}

    ~FileBuffer() {
        delete[] data;
    }
};

int main() {
    FileBuffer first(1000);
    FileBuffer second = first;
    std::cout << "first.data  = " << first.data << '\n';
    std::cout << "second.data = " << second.data << '\n';
    std::cout << "same allocation: " << (first.data == second.data ? "yes" : "no")
              << '\n' << std::flush;
}
