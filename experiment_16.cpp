#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 64
#define SUBKEY_SIZE 48
#define NUM_ROUNDS 16

// Initial Permutation Table
int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table
int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Permuted Choice 1 Table
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

// Permuted Choice 2 Table
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

// Expansion Table
int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// S-Boxes
int S_BOX[8][4][16] = {
    // S1
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    // S2
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    // (other S-Boxes omitted for brevity)...
};

// Permutation Table
int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// Shift Schedule
int SHIFTS[NUM_ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Perform Permutation
uint64_t permute(uint64_t input, int *table, int table_size) {
    uint64_t output = 0;
    for (int i = 0; i < table_size; i++) {
        output |= ((input >> (64 - table[i])) & 1) << (table_size - i - 1);
    }
    return output;
}

// Generate Subkeys
void generate_subkeys(uint64_t key, uint64_t *subkeys) {
    uint64_t permuted_key = permute(key, PC1, 56);
    uint32_t C = (permuted_key >> 28) & 0xFFFFFFF;
    uint32_t D = permuted_key & 0xFFFFFFF;

    for (int i = 0; i < NUM_ROUNDS; i++) {
        C = ((C << SHIFTS[i]) | (C >> (28 - SHIFTS[i]))) & 0xFFFFFFF;
        D = ((D << SHIFTS[i]) | (D >> (28 - SHIFTS[i]))) & 0xFFFFFFF;

        uint64_t combined = ((uint64_t)C << 28) | D;
        subkeys[i] = permute(combined, PC2, 48);
    }
}

// DES Decryption
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    uint64_t subkeys[NUM_ROUNDS];
    generate_subkeys(key, subkeys);

    uint64_t permuted_text = permute(ciphertext, IP, 64);

    // (left, right halves processing and decryption logic omitted for brevity)...

    return permute(permuted_text, FP, 64);
}

int main() {
    uint64_t ciphertext = 0x85E813540F0AB405;
    uint64_t key = 0x133457799BBCDFF1;

    uint64_t plaintext = des_decrypt(ciphertext, key);
    printf("Decrypted plaintext: %016llX\n", plaintext);

    return 0;
}

