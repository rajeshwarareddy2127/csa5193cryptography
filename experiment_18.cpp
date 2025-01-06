#include <stdio.h>
#include <stdint.h>

// Permuted Choice 1 Table (splits 56-bit key into two 28-bit halves)
int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Permuted Choice 2 Table (creates 48-bit subkeys from the 56-bit key)
int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Shift Schedule for each round
int SHIFTS[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Function to permute a given input based on a table
uint64_t permute(uint64_t input, int *table, int table_size, int input_size) {
    uint64_t output = 0;
    for (int i = 0; i < table_size; i++) {
        output |= ((input >> (input_size - table[i])) & 1) << (table_size - i - 1);
    }
    return output;
}

// Function to generate subkeys
void generate_subkeys(uint64_t key, uint64_t subkeys[16]) {
    // Apply PC1 to get the 56-bit key
    uint64_t permuted_key = permute(key, PC1, 56, 64);

    // Split into two 28-bit halves
    uint32_t C = (permuted_key >> 28) & 0xFFFFFFF;
    uint32_t D = permuted_key & 0xFFFFFFF;

    // Generate 16 subkeys
    for (int i = 0; i < 16; i++) {
        // Perform left circular shifts
        C = ((C << SHIFTS[i]) | (C >> (28 - SHIFTS[i]))) & 0xFFFFFFF;
        D = ((D << SHIFTS[i]) | (D >> (28 - SHIFTS[i]))) & 0xFFFFFFF;

        // Combine halves and apply PC2 to generate the subkey
        uint64_t combined = ((uint64_t)C << 28) | D;
        subkeys[i] = permute(combined, PC2, 48, 56);
    }
}

// Function to display the subkeys
void display_subkeys(uint64_t subkeys[16]) {
    for (int i = 0; i < 16; i++) {
        printf("Subkey %2d: ", i + 1);
        for (int j = 47; j >= 0; j--) {
            printf("%d", (subkeys[i] >> j) & 1);
        }
        printf("\n");
    }
}

int main() {
    // Example 64-bit key (8 bytes)
    uint64_t key = 0x133457799BBCDFF1;

    // Array to store the 16 subkeys
    uint64_t subkeys[16];

    // Generate the subkeys
    generate_subkeys(key, subkeys);

    // Display the subkeys
    printf("Generated Subkeys:\n");
    display_subkeys(subkeys);

    return 0;
}

