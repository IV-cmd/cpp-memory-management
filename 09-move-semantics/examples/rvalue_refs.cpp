#include <iostream>
#include <string>
#include <utility>

void take(const std::string&) {
    std::cout << "lvalue overload\n";
}

void take(std::string&&) {
    std::cout << "rvalue overload\n";
}

int main() {
    int x = 10;
    int& ref = x;
    int&& rref = 10;
    std::cout << "ref = " << ref << ", rref = " << rref << '\n';

    std::string name = "disk-07";
    take(name);
    take(std::string("temp"));
    take(std::move(name));
    std::cout << "name after std::move without a move: \"" << name << "\"\n";

    int a = 10;
    int b = std::move(a);
    std::cout << "a = " << a << ", b = " << b << '\n';

#ifdef SHOW_ERRORS
    int& bad = 10;
    int&& alsoBad = x;
    (void)bad;
    (void)alsoBad;
#endif
}
