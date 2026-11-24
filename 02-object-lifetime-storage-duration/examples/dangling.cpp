#include <iostream>

// Broken on purpose: reading through p after delete.
int main() {
    int* p = new int(50);
    int* copy = p;            // a second pointer to the same int
    delete p;
    p = nullptr;              // clears p...
    std::cout << *copy << '\n';   // ...but not copy
}
