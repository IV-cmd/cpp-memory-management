#include <iostream>
#include <memory>

struct Tracked {
    Tracked() {
        std::cout << "+ Tracked\n";
    }

    ~Tracked() {
        std::cout << "- Tracked\n";
    }
};

void inspectOwner(std::shared_ptr<Tracked> owner) {
    std::cout << "inside function: use_count = " << owner.use_count() << '\n';
}

int main() {
    auto first = std::make_shared<Tracked>();
    std::cout << "after make_shared: " << first.use_count() << '\n';

    auto second = first;
    std::cout << "after second = first: " << second.use_count() << '\n';

    auto third = second;
    std::cout << "after third = second: " << third.use_count() << '\n';

    inspectOwner(first);
    std::cout << "after function returns: " << first.use_count() << '\n';

    first.reset();
    std::cout << "after first.reset: " << second.use_count() << '\n';

    second.reset();
    std::cout << "after second.reset: " << third.use_count() << '\n';

    third.reset();
    std::cout << "after third.reset: " << third.use_count() << '\n';
}
