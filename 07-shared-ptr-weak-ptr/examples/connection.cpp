#include <iostream>
#include <memory>

struct Connection {
    ~Connection() {
        std::cout << "- Connection\n";
    }
};

int main() {
    auto requestHandler = std::make_shared<Connection>();
    auto monitoring = requestHandler;
    auto healthChecker = monitoring;
    std::cout << "connection created (owners: " << requestHandler.use_count() << ")\n";

    requestHandler.reset();
    std::cout << "connection still alive (owners: " << monitoring.use_count() << ")\n";

    monitoring.reset();
    std::cout << "connection still alive (owners: " << healthChecker.use_count() << ")\n";

    healthChecker.reset();
}
