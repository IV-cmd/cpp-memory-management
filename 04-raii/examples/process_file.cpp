#include <iostream>
#include <memory>
#include <vector>

void handleRequest() {                              // leaks on purpose
    int requestId = 10;
    int* buffer = new int[1000];
    std::cout << "Processing request " << requestId << " (raw new[])\n";
    buffer[0] = requestId;
}

void processFile() {                                // the same shape, nothing to leak
    int fileSize = 4096;
    auto buffer = std::make_unique<char[]>(fileSize);
    std::vector<int> metadata(100);
    std::cout << "Processing file (unique_ptr + vector)\n";
    buffer[0] = 'x';
    metadata[0] = fileSize;
}

int main() {
    handleRequest();
    processFile();
}
