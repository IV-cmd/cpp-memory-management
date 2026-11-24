#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int totalFiles = 100;   // initialised global: data segment
int totalErrors;        // zero-initialised global: bss segment

void writeFile() {}     // code: text segment

int main() {
    int fileSize = 4096;              // local: stack
    int* buffer = new int[1024];      // dynamic: heap

    std::printf("text  &writeFile   = %p\n", reinterpret_cast<void*>(&writeFile));
    std::printf("data  &totalFiles  = %p\n", static_cast<void*>(&totalFiles));
    std::printf("bss   &totalErrors = %p\n", static_cast<void*>(&totalErrors));
    std::printf("heap  buffer       = %p\n", static_cast<void*>(buffer));
    std::printf("stack &fileSize    = %p\n", static_cast<void*>(&fileSize));

    // The kernel's own view of this process's address space.
    std::cout << "\n/proc/self/maps (trimmed):\n";
    const std::string self = std::filesystem::read_symlink("/proc/self/exe");
    std::ifstream maps("/proc/self/maps");
    std::string line;
    while (std::getline(maps, line)) {
        if (line.find(self) != std::string::npos || line.find("[heap]") != std::string::npos ||
            line.find("[stack]") != std::string::npos || line.find("libc.so") != std::string::npos) {
            std::cout << line.substr(0, 34) << ' ' << line.substr(line.find_last_of("/ ") + 1) << '\n';
        }
    }

    delete[] buffer;
}
