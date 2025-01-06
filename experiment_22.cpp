#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function prototypes
uint8_t sdes_encrypt(uint8_t plaintext, uint8_t key);
uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t key);
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output, size_t size);
void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t iv, size_t length);
void cbc_decrypt(uint8_t *ciphertext, uint8_t *decrypted_text, uint8_t *key, uint8_t iv, size_t length);

// Placeholder S-DES encryption/decryption (replace with actual implementation)
uint8_t sdes_encrypt(uint8_t plaintext, uint8_t key) {
    // A dummy implementation: real S-DES logic should go here.
    return plaintext ^ key;  // Replace this with actual S-DES
}

uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t key) {
    // A dummy implementation: real S-DES logic should go here.
    return ciphertext ^ key;  // Replace this with actual S-DES
}

// XOR function for blocks
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output, size_t size) {
    for (size_t i = 0; i < size; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

// CBC Encryption
void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t iv, size_t length) {
    uint8_t previous_block = iv;

    for (size_t i = 0; i < length; i++) {
        uint8_t xored_block = plaintext[i] ^ previous_block;
        ciphertext[i] = sdes_encrypt(xored_block, key[i]);
        previous_block = ciphertext[i];
    }
}

// CBC Decryption
void cbc_decrypt(uint8_t *ciphertext, uint8_t *decrypted_text, uint8_t *key, uint8_t iv, size_t length) {
    uint8_t previous_block = iv;

    for (size_t i = 0; i < length; i++) {
        uint8_t decrypted_block = sdes_decrypt(ciphertext[i], key[i]);
        decrypted_text[i] = decrypted_block ^ previous_block;
        previous_block = ciphertext[i];
    }
}

// Helper function to print binary data
void print_binary(uint8_t *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (data[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    // Parameters
    uint8_t iv = 0xAA; // Initialization vector: 10101010
    uint8_t key[] = {0x7D}; // Key: 0111111101
    uint8_t plaintext[] = {0x01, 0x23}; // Plaintext: 00000001 00100011
    size_t length = sizeof(plaintext);

    uint8_t ciphertext[length];
    uint8_t decrypted_text[length];

    // Encryption
    printf("Plaintext: ");
    print_binary(plaintext, length);
    cbc_encrypt(plaintext, ciphertext, key, iv, length);
    printf("Ciphertext: ");
    print_binary(ciphertext, length);

    // Decryption
    cbc_decrypt(ciphertext, decrypted_text, key, iv, length);
    printf("Decrypted text: ");
    print_binary(decrypted_text, length);

    return 0;
}

