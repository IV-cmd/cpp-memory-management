#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

struct Tracer {
    std::string name;
    explicit Tracer(std::string n) : name(std::move(n)) {}
    ~Tracer() { std::cout << "  destructor: " << name << std::endl; }
};

Tracer global("static object");

// Usage: ./caveats return|exit|abort
int main(int argc, char** argv) {
    const char* how = argc > 1 ? argv[1] : "return";
    Tracer local("local object");
    std::cout << "leaving main with " << how << std::endl;
    if (std::strcmp(how, "exit") == 0) {
        std::exit(0);                 // static objects are destroyed, locals aren't
    }
    if (std::strcmp(how, "abort") == 0) {
        std::abort();                 // nothing is destroyed
    }
    return 0;
}
