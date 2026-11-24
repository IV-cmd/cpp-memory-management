#include <iostream>

// Broken on purpose: reads an int after deleting it.
int main() {
    int* buffer = new int(100);
    delete buffer;
    int* other = new int(7);          // the allocator is free to hand the same spot out again
    std::cout << "buffer = " << buffer << ", other = " << other << '\n';
    std::cout << "*buffer = " << *buffer << '\n';
    delete other;
}
