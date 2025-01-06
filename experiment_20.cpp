#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 // 3DES block size is 64 bits (8 bytes)

// XOR function for two byte arrays
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output, size_t size) {
    for (size_t i = 0; i < size; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

// Simulated 3DES encryption (placeholder function)
void triple_des_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    // In a real implementation, apply 3DES encryption here
    // For simplicity, we'll just reverse the plaintext as a placeholder
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[BLOCK_SIZE - 1 - i];
    }
}

// CBC encryption function
void cbc_encrypt(uint8_t *plaintext, size_t plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t current_block[BLOCK_SIZE];
    uint8_t previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE); // Set IV as the initial previous block

    for (size_t i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        // XOR the plaintext block with the previous ciphertext block (or IV for the first block)
        xor_blocks(&plaintext[i], previous_block, current_block, BLOCK_SIZE);

        // Encrypt the current block with 3DES
        triple_des_encrypt(current_block, key, &ciphertext[i]);

        // Update the previous block to the current ciphertext block
        memcpy(previous_block, &ciphertext[i], BLOCK_SIZE);
    }
}

// Helper function to print data in hexadecimal format
void print_hex(uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    // Example plaintext (must be a multiple of 8 bytes for simplicity)
    uint8_t plaintext[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10
    };
    size_t plaintext_len = sizeof(plaintext);

    // Example 3DES key (must be 24 bytes for real 3DES)
    uint8_t key[24] = {
        0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38
    };

    // Example Initialization Vector (IV)
    uint8_t iv[BLOCK_SIZE] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11};

    // Array to hold the ciphertext
    uint8_t ciphertext[plaintext_len];

    // Perform CBC encryption
    cbc_encrypt(plaintext, plaintext_len, key, iv, ciphertext);

    // Output results
    printf("Plaintext:  ");
    print_hex(plaintext, plaintext_len);

    printf("Ciphertext: ");
    print_hex(ciphertext, plaintext_len);

    return 0;
}

