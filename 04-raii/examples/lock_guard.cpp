#include <iostream>
#include <mutex>
#include <stdexcept>

std::mutex storageMutex;

void updateManual() {
    storageMutex.lock();
    throw std::runtime_error("metadata update failed");
    storageMutex.unlock();                          // never reached
}

void updateGuarded() {
    std::lock_guard<std::mutex> lock(storageMutex); // unlocks in its destructor
    throw std::runtime_error("metadata update failed");
}

template <typename F>
void attempt(const char* label, F update) {
    try {
        update();
    } catch (const std::exception&) {
    }
    bool free = storageMutex.try_lock();            // can anyone else get the lock now?
    std::cout << label << ": mutex free after the exception? " << (free ? "yes" : "no, still locked") << '\n';
    if (free) {
        storageMutex.unlock();
    }
}

int main() {
    attempt("lock_guard", updateGuarded);
    attempt("manual    ", updateManual);
}
