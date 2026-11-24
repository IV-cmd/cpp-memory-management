#include <cstdio>

// Broken on purpose: a 100 MB local array doesn't fit in an 8 MB stack.
void processFile() {
    char buffer[100 * 1024 * 1024];
    buffer[0] = 'x';                       // touch it so it isn't optimised away
    std::printf("buffer[0] = %c\n", buffer[0]);
}

int main() {
    std::printf("calling processFile()\n");
    std::fflush(stdout);
    processFile();
    std::printf("never printed\n");
}
