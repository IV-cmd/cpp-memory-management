#include <iostream>
#include <memory>

struct MonitoringService;

struct StorageNode {
    std::shared_ptr<MonitoringService> monitoring;

    ~StorageNode() {
        std::cout << "- StorageNode\n";
    }
};

struct MonitoringService {
#ifdef WEAK
    std::weak_ptr<StorageNode> node;
#else
    std::shared_ptr<StorageNode> node;
#endif

    ~MonitoringService() {
        std::cout << "- MonitoringService\n";
    }
};

int main() {
    {
        auto node = std::make_shared<StorageNode>();
        auto monitoring = std::make_shared<MonitoringService>();
        node->monitoring = monitoring;
        monitoring->node = node;
        std::cout << "node use_count: " << node.use_count() << '\n';
        std::cout << "monitor use_count: " << monitoring.use_count() << '\n';
    }
    std::cout << "block ended\n";
}
