#include <iostream>

// Broken on purpose: deletes the same allocation twice.
int main() {
    int* buffer = new int(100);
    delete buffer;
    std::cout << "deleted once\n" << std::flush;
    delete buffer;
    std::cout << "deleted twice\n";
}
