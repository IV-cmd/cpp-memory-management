#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>

namespace {
std::size_t allocationCount = 0;
bool countAllocations = false;
}

void* operator new(std::size_t size) {
    if (void* memory = std::malloc(size)) {
        if (countAllocations) {
            ++allocationCount;
        }
        return memory;
    }
    throw std::bad_alloc();
}

void operator delete(void* memory) noexcept {
    std::free(memory);
}

void operator delete(void* memory, std::size_t) noexcept {
    std::free(memory);
}

template <typename Function>
std::size_t countAllocationsFor(Function createOwner) {
    allocationCount = 0;
    countAllocations = true;
    createOwner();
    countAllocations = false;
    return allocationCount;
}

int main() {
    std::cout << "sizeof(unique_ptr<int>) = " << sizeof(std::unique_ptr<int>) << '\n'
              << "sizeof(shared_ptr<int>) = " << sizeof(std::shared_ptr<int>) << '\n'
              << "sizeof(weak_ptr<int>) = " << sizeof(std::weak_ptr<int>) << '\n';

    const std::size_t sharedRaw = countAllocationsFor([] {
        std::shared_ptr<int> owner(new int(100));
    });
    const std::size_t sharedMake = countAllocationsFor([] {
        std::shared_ptr<int> owner = std::make_shared<int>(100);
    });
    const std::size_t uniqueMake = countAllocationsFor([] {
        std::unique_ptr<int> owner = std::make_unique<int>(100);
    });

    std::cout << "shared_ptr(new int): " << sharedRaw << " allocation(s)\n"
              << "make_shared<int>: " << sharedMake << " allocation(s)\n"
              << "make_unique<int>: " << uniqueMake << " allocation(s)\n";
}
