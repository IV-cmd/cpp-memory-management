#include <cstdio>
#include <iostream>
#include <memory>

struct StructDeleter {
    void operator()(FILE* file) const {
        if (file != nullptr) {
            std::fclose(file);
            std::cout << "fclose called\n";
        }
    }
};

int closeFile(FILE* file) {
    const int result = std::fclose(file);
    std::cout << "fclose called\n";
    return result;
}

int main() {
    std::cout << "sizeof(int*) = " << sizeof(int*) << '\n'
              << "sizeof(unique_ptr<int>) = " << sizeof(std::unique_ptr<int>) << '\n'
              << "sizeof(unique_ptr<FILE, StructDeleter>) = "
              << sizeof(std::unique_ptr<FILE, StructDeleter>) << '\n'
              << "sizeof(unique_ptr<FILE, int(*)(FILE*)>) = "
              << sizeof(std::unique_ptr<FILE, int (*)(FILE*)>) << '\n';

    std::unique_ptr<FILE, StructDeleter> structured(std::tmpfile());
    std::unique_ptr<FILE, int (*)(FILE*)> functionPointer(
        std::tmpfile(), &closeFile);

    std::unique_ptr<FILE, StructDeleter> releasedOwner(std::tmpfile());
    FILE* released = releasedOwner.release();
    std::cout << "release: caller owns FILE*\n";
    if (released != nullptr) {
        std::fclose(released);
        std::cout << "fclose called\n";
    }

    std::unique_ptr<FILE, StructDeleter> resetOwner(std::tmpfile());
    resetOwner.reset();
    std::cout << "reset: closed now\n";
}
