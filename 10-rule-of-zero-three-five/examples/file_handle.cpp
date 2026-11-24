#include <cerrno>
#include <fcntl.h>
#include <iostream>
#include <system_error>
#include <unistd.h>
#include <utility>

class FileHandle {
    int fd;

public:
    explicit FileHandle(const char* path) : fd(open(path, O_RDONLY)) {
        if (fd == -1) {
            throw std::system_error(errno, std::generic_category(), path);
        }
        std::cout << "open -> fd " << fd << '\n';
    }

    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    FileHandle(FileHandle&& other) noexcept : fd(std::exchange(other.fd, -1)) {}

    FileHandle& operator=(FileHandle&& other) noexcept {
        if (this != &other) {
            if (fd >= 0) {
                close(fd);
                std::cout << "close(fd " << fd << ")\n";
            }
            fd = std::exchange(other.fd, -1);
        }
        return *this;
    }

    ~FileHandle() {
        if (fd >= 0) {
            close(fd);
            std::cout << "close(fd " << fd << ")\n";
        }
    }

    int get() const {
        return fd;
    }
};

int main() {
    FileHandle first("/dev/null");
    FileHandle second(std::move(first));
    std::cout << "first.get() = " << first.get() << '\n';
    std::cout << "second.get() = " << second.get() << '\n';

    FileHandle third("/dev/null");
    second = std::move(third);
    std::cout << "third.get() = " << third.get() << '\n';
    std::cout << "second.get() after move assignment = " << second.get() << '\n';

    try {
        FileHandle missing("/no/such/file");
    } catch (const std::system_error& error) {
        std::cout << error.what() << '\n';
    }

#ifdef SHOW_ERRORS
    FileHandle copy = second;
#endif
}
