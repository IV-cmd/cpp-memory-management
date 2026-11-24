#include <iostream>

struct PlainBuffer {
    int size;
};

class FileBuffer {
public:
    int size;

    explicit FileBuffer(int value) : size(value) {}

    FileBuffer(const FileBuffer& other) : size(other.size) {
        std::cout << "copy constructor\n";
    }

    FileBuffer& operator=(const FileBuffer& other) {
        std::cout << "copy assignment\n";
        size = other.size;
        return *this;
    }
};

void inspect(FileBuffer buffer) {
    std::cout << "inspect received buffer of size " << buffer.size << '\n';
}

#ifdef SHOW_ERRORS
class BadBuffer {
public:
    BadBuffer(BadBuffer other);
};
#endif

int main() {
    PlainBuffer first{1000};
    PlainBuffer second = first;
    second.size = 2000;
    std::cout << "first.size = " << first.size << '\n';
    std::cout << "second.size = " << second.size << '\n';

    std::cout << "--- FileBuffer a(1000);\n";
    FileBuffer a(1000);
    std::cout << "--- FileBuffer b = a;\n";
    FileBuffer b = a;
    (void)b.size;
    std::cout << "--- FileBuffer c(a);\n";
    FileBuffer c(a);
    std::cout << "--- FileBuffer d(500); d = a;\n";
    FileBuffer d(500);
    d = a;
    std::cout << "--- inspect(a);\n";
    inspect(a);
}
