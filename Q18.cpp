#include <stdio.h>
#include <stdint.h>


void generateSubkeys(uint64_t initialKey, uint64_t subkeys[]) {


    uint32_t leftSubset = (initialKey >> 28) & 0xFFFFFFF;
    uint32_t rightSubset = initialKey & 0xFFFFFFF; 
   

int main() {
    uint64_t initialKey = 0x123456789ABCDEF0; 
    uint64_t subkeys[16]; 

    generateSubkeys(initialKey, subkeys);


    printf("Generated Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("K%d: %llx\n", i + 1, subkeys[i]);
    }

    return 0;
}

