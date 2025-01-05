#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
// 0x2e516f18
// 0xfe95f7db
int main() {
unsigned int seed = 0;
    unsigned int i;
    int fd;
    unsigned int buf[32] = {0}; // Buffer as an array of 4-byte integers

    // Read the stack canary for security

    // Open the "/flag" file
    fd = open("/flag", O_RDONLY);
    assert(fd >= 0);  // Ensure the file descriptor is valid

    // Read up to 128 bytes into `buf` (32 * 4 bytes)
    assert(read(fd, buf, sizeof(buf)) > 0);  // Ensure the read operation succeeded

    // XOR the contents of the buffer into `seed`
    for (i = 0; i < 32; ++i) { // Process all 32 elements (128 bytes / 4 bytes)
        seed ^= buf[i];
    }
    printf("Seed: 0x%x (%u)\n", seed, seed);

    srand(seed);

    // Zero out the buffer for security
    memset(buf, 0, sizeof(buf));

    // Return the XOR of the initial stack canary and the current stack canary
    return __readfsqword(0x28u) ^ v5;
}
