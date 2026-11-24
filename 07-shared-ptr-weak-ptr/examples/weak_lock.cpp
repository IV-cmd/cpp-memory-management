#include <iostream>
#include <memory>

int main() {
    auto owner = std::make_shared<int>(100);
    std::cout << "use_count before weak_ptr: " << owner.use_count() << '\n';
    std::weak_ptr<int> observer = owner;
    std::cout << "use_count after weak_ptr: " << owner.use_count() << '\n';

    if (auto strong = observer.lock()) {
        std::cout << "resource is alive; use_count: " << strong.use_count() << '\n';
    }
    std::cout << "use_count after lock scope: " << owner.use_count() << '\n';

    owner.reset();
    std::cout << "expired: " << (observer.expired() ? "yes" : "no") << '\n';
    if (auto strong = observer.lock()) {
        std::cout << "resource is alive; use_count: " << strong.use_count() << '\n';
    } else {
        std::cout << "already destroyed\n";
    }
}
