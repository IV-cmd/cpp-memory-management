#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

// Broken on purpose: allocates on every request and never frees.
void processFile() {
    int* buffer = new int[10000];                     // 40 KB per call
    std::memset(buffer, 0, 10000 * sizeof(int));      // touch it so the pages are really used
}

long residentKiB() {
    std::ifstream status("/proc/self/status");
    std::string key;
    long value = 0;
    while (status >> key) {
        if (key == "VmRSS:") {
            status >> value;
            break;
        }
    }
    return value;
}

int main() {
    std::cout << "before any request: " << residentKiB() << " KiB resident\n";
    for (int request = 1; request <= 1000; ++request) {
        processFile();
        if (request == 1 || request == 100 || request == 1000) {
            std::cout << "after request " << request << ": " << residentKiB() << " KiB resident\n";
        }
    }
}
