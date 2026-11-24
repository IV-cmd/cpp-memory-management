#include <cstdio>

void writeFile() {
    int bufferSize = 4096;
    std::printf("  writeFile():      &bufferSize = %p\n", static_cast<void*>(&bufferSize));
}

void processRequest() {
    int requestId = 10;
    std::printf("  processRequest(): &requestId  = %p\n", static_cast<void*>(&requestId));
    writeFile();
}

int main() {
    int mainLocal = 0;
    std::printf("  main():           &mainLocal  = %p\n", static_cast<void*>(&mainLocal));
    processRequest();
}
