#include <iostream>
#include <memory>
#include <utility>

struct Buffer {
    int id;
    explicit Buffer(int i) : id(i) { std::cout << "  allocate buffer " << id << '\n'; }
    ~Buffer() { std::cout << "  free buffer " << id << '\n'; }
};

void processFile() {
    auto buffer = std::make_unique<Buffer>(1);
    auto block = std::make_unique<int[]>(1000);
    block[0] = 42;
    std::cout << "  using buffer " << buffer->id << ", block[0] = " << block[0] << '\n';
}   // both freed here, in reverse order

int main() {
    std::cout << "processFile()\n";
    processFile();

    std::cout << "moving ownership\n";
    auto first = std::make_unique<Buffer>(2);
#ifdef SHOW_ERRORS
    auto copy = first;                              // error: unique_ptr can't be copied
#endif
    auto second = std::move(first);
    std::cout << "  first is " << (first ? "not empty" : "empty (nullptr)")
              << ", second owns buffer " << second->id << '\n';

    std::cout << "sizeof(int*) = " << sizeof(int*)
              << ", sizeof(std::unique_ptr<int>) = " << sizeof(std::unique_ptr<int>) << '\n';
    std::cout << "end of main\n";
}
