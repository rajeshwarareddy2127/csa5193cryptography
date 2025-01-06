#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Simplified S-Box values for demonstration purposes
uint8_t S1[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 10, 7, 9, 3, 5, 11, 2, 14, 1, 12, 4, 13, 8, 6},
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 5, 10, 0},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5}
};

uint8_t S2[4][16] = {
    {15, 12, 8, 14, 4, 7, 9, 5, 1, 11, 10, 3, 6, 13, 0, 2},
    {5, 10, 15, 13, 9, 3, 0, 14, 7, 6, 4, 8, 12, 11, 1, 2},
    {14, 1, 4, 10, 15, 11, 7, 5, 3, 8, 0, 9, 12, 6, 13, 2},
    {9, 0, 8, 14, 12, 4, 7, 3, 15, 1, 10, 5, 13, 6, 11, 2}
};

// Permutation function (initial and final)
uint64_t permute(uint64_t input, const int* table, int size) {
    uint64_t output = 0;
    for (int i = 0; i < size; i++) {
        output |= ((input >> (64 - table[i])) & 1) << (size - 1 - i);
    }
    return output;
}

// Example key schedule (simplified version)
void key_schedule(uint64_t key, uint64_t* subkeys) {
    // For simplicity, we're not implementing the full key schedule here.
    // Normally, the key would be divided into left and right parts, shifted, and permuted.
    subkeys[0] = key;
}

// DES encryption function
uint64_t des_encrypt(uint64_t data, uint64_t key) {
    int initial_permutation[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };

    uint64_t permuted_data = permute(data, initial_permutation, 64);
    uint64_t subkeys[16];
    key_schedule(key, subkeys);

    // Here we just demonstrate using the S-boxes to simplify. Normally, rounds would be applied.
    for (int i = 0; i < 16; i++) {
        // Simplified round operation using S-box (a full DES round involves more steps)
        permuted_data ^= S1[0][i];  // Example substitution step using S-box
    }

    return permuted_data;
}

// DES decryption function (inverse of encryption)
uint64_t des_decrypt(uint64_t data, uint64_t key) {
    // Decryption process is very similar to encryption but using subkeys in reverse order
    int initial_permutation[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };

    uint64_t permuted_data = permute(data, initial_permutation, 64);
    uint64_t subkeys[16];
    key_schedule(key, subkeys);

    // For simplicity, we just reverse the encryption process
    for (int i = 15; i >= 0; i--) {
        // Reverse round operation using S-boxes (a full DES round involves more steps)
        permuted_data ^= S1[0][i];  // Example reverse substitution
    }

    return permuted_data;
}

int main() {
    uint64_t plaintext = 0x0123456789abcdef; // Sample 64-bit plaintext
    uint64_t key = 0x133457799BBCDFF1; // Example 56-bit key

    printf("Plaintext: %llx\n", plaintext);
    printf("Key: %llx\n", key);

    uint64_t ciphertext = des_encrypt(plaintext, key);
    printf("Ciphertext: %llx\n", ciphertext);

    uint64_t decrypted_text = des_decrypt(ciphertext, key);
    printf("Decrypted Text: %llx\n", decrypted_text);

    return 0;
}

