#include <iostream>
#include <string>
#include <thread>
#include <utility>

struct Tracer {
    std::string name;
    explicit Tracer(std::string n) : name(std::move(n)) { std::cout << "  + " << name << '\n'; }
    ~Tracer() { std::cout << "  - " << name << '\n'; }
};

Tracer globalTracer("static: global");             // static storage duration

void process() {
    static int retryCount = 0;                     // static, even though it's a local
    int calls = 0;                                 // automatic: a fresh one every call
    ++retryCount;
    ++calls;
    std::cout << "  process(): retryCount = " << retryCount << ", calls = " << calls << '\n';
}

thread_local int requestCount = 0;                 // thread storage duration

void worker(int requests, int* seen, const void** where) {
    for (int i = 0; i < requests; ++i) {
        ++requestCount;
    }
    *seen = requestCount;
    *where = &requestCount;
}

int main() {
    std::cout << "main starts\n";

    std::cout << "automatic\n";
    {
        Tracer t("automatic: block local");
    }

    std::cout << "static local\n";
    process();
    process();
    process();

    std::cout << "dynamic\n";
    Tracer* d = new Tracer("dynamic: new");
    std::cout << "  ...still alive after the line that created it\n";
    delete d;

    std::cout << "thread_local\n";
    int seenA = 0, seenB = 0;
    const void* whereA = nullptr;
    const void* whereB = nullptr;
    std::thread a(worker, 3, &seenA, &whereA);    // both threads run at the same time
    std::thread b(worker, 5, &seenB, &whereB);
    a.join();
    b.join();
    std::cout << "  thread A: requestCount = " << seenA << " at " << whereA << '\n';
    std::cout << "  thread B: requestCount = " << seenB << " at " << whereB << '\n';
    std::cout << "  main:     requestCount = " << requestCount << " at " << &requestCount << '\n';

    std::cout << "main ends\n";
}
