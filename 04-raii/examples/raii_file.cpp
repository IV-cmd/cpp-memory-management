#include <iostream>
#include <stdexcept>

int openFile() { return 3; }                       // stand-ins so the order is easy to see
void closeFile(int) {}

class File {
public:
    File() : fd(openFile()) { std::cout << "File opened\n"; }
    ~File() {
        closeFile(fd);
        std::cout << "File closed\n";
    }

    File(const File&) = delete;
    File& operator=(const File&) = delete;

private:
    int fd;
};

void writeFile() {
    File file;
    std::cout << "Writing data\n";
    throw std::runtime_error("Write failed");
}

int main() {
    try {
        writeFile();
    } catch (const std::exception& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
}
