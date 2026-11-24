#include <iostream>

int* createBuffer() {
    int* buffer = new int(100);   // the pointer is local, the int is dynamic
    std::cout << "  inside createBuffer: &buffer = " << &buffer << ", buffer = " << buffer << '\n';
    return buffer;
}

void processRequest() {
    int requestId = 10;
    if (requestId > 0) {
        int retryCount = 3;
        std::cout << "  retryCount = " << retryCount << '\n';
    }
#ifdef SHOW_ERRORS
    std::cout << retryCount;      // error: retryCount isn't in scope here
#endif
}

int main() {
    std::cout << "1. scope\n";
    processRequest();

    std::cout << "2. the pointer dies, the object doesn't\n";
    int* p = createBuffer();
    std::cout << "  back in main:        p = " << p << ", *p = " << *p << '\n';
    delete p;
    p = nullptr;
}
