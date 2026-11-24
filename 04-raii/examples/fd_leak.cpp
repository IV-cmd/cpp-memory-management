#include <fcntl.h>
#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <stdexcept>

int openFile() { return ::open("/dev/null", O_RDONLY); }
void closeFile(int fd) { ::close(fd); }

long openFds() {
    long n = 0;
    for ([[maybe_unused]] auto& e : std::filesystem::directory_iterator("/proc/self/fd")) {
        ++n;
    }
    return n;
}

// Manual cleanup: closeFile is skipped on the early return and on the throw.
void writeFileManual(bool someError, bool throws) {
    int fd = openFile();
    if (someError) {
        return;
    }
    if (throws) {
        throw std::runtime_error("write failed");
    }
    closeFile(fd);
}

// RAII: the destructor closes the fd on every way out of the function.
class File {
public:
    File() : fd(openFile()) {
        if (fd < 0) {
            throw std::runtime_error("open failed");
        }
    }
    ~File() { closeFile(fd); }

    File(const File&) = delete;
    File& operator=(const File&) = delete;

    int get() const { return fd; }

private:
    int fd;
};

void writeFileRaii(bool someError, bool throws) {
    File file;
    if (someError) {
        return;
    }
    if (throws) {
        throw std::runtime_error("write failed");
    }
}

template <typename F>
void run(const char* label, F writeFile) {
    long before = openFds();
    for (int i = 0; i < 10; ++i) {
        writeFile(false, false);                    // normal path
        writeFile(true, false);                     // early return
        try {
            writeFile(false, true);                 // exception
        } catch (const std::runtime_error&) {
        }
    }
    std::cout << label << ": open fds before = " << before << ", after 30 calls = " << openFds() << '\n';
}

int main() {
    run("manual", writeFileManual);
    run("RAII  ", writeFileRaii);
}
