#include <iostream>

int main() {
    int* value = new int(100);        // one int, initialised to 100
    std::cout << "*value = " << *value << '\n';
    delete value;

    int* buffer = new int[5];         // five ints
    for (int i = 0; i < 5; ++i) {
        buffer[i] = (i + 1) * 10;
    }
    std::cout << "buffer = ";
    for (int i = 0; i < 5; ++i) {
        std::cout << buffer[i] << ' ';
    }
    std::cout << '\n';

#ifdef MISMATCH
    delete buffer;                    // wrong form: new[] needs delete[]
#else
    delete[] buffer;
#endif
}
