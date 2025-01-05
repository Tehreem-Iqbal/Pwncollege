#include <stdio.h>
#include <string.h>

unsigned int seed = 0;
int bruetforce_seed() {
    unsigned int found_seed = 0;

    for (seed = 0; seed <= 0xFFFFFFFF; ++seed) {
        if (seed == 0x3f656e0f) {
            printf("Seed found: 0x%08X\n", seed);
            return 0;
        }
        if (seed % 1000000 == 0) {
            printf("Checked up to seed: 0x%08X\n", seed);
        }
    }
        printf("No matching seed found.\n");
    return 0;
}

int main() {
    //bruetforce_seed();
    unsigned int seed = 0;
    unsigned int buf[17] = {0};
    memcpy(buf, "pwn.college{o0r5nD7xuflvytS1FNcjODc4osD.QX3gjMsQDM5QzW}", 128);
    // seed value 0x000000003f656e0f for practice flag

    for (int i = 0; i < 32; i++) {
        seed ^= buf[i];
    }

    printf("Seed: 0x%x (%u)\n", seed, seed);

    unsigned char V[8] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};

   srand(seed); 
   int i;
   unsigned char temp = 0x0;
//    for (i = 0; i < 65534; i++) {
//       int v1 = rand() % 8;
//       int v2 = rand() % 8;
//       printf("%d %d\n", v1, v2);
//         temp = V[v1];
//         V[v1] = V[v2];
//         V[v2] = temp;
//    }
   for (i = 0; i < 8; i++) {
      printf("%d ", V[i]);
   }
   return 0;
}


