#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function prototypes
uint8_t sdes_encrypt(uint8_t input, uint8_t key);
void ctr_encrypt_decrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t key, uint8_t counter, size_t length);

// Placeholder S-DES encryption function (replace with actual S-DES logic)
uint8_t sdes_encrypt(uint8_t input, uint8_t key) {
    // Dummy implementation for demonstration: Replace with actual S-DES logic.
    return input ^ key;  // Simple XOR for demonstration
}

// Counter (CTR) Mode Encryption/Decryption
void ctr_encrypt_decrypt(uint8_t *plaintext, uint8_t *output, uint8_t key, uint8_t counter, size_t length) {
    for (size_t i = 0; i < length; i++) {
        uint8_t keystream = sdes_encrypt(counter, key); // Encrypt the counter using S-DES
        output[i] = plaintext[i] ^ keystream;           // XOR plaintext with keystream
        counter++;                                      // Increment the counter
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
    uint8_t key = 0x7D; // Key: 0111111101
    uint8_t counter = 0x00; // Counter starts at 00000000
    uint8_t plaintext[] = {0x01, 0x02, 0x04}; // Plaintext: 00000001 00000010 00000100
    size_t length = sizeof(plaintext);

    uint8_t ciphertext[length];
    uint8_t decrypted_text[length];

    // Encryption
    printf("Plaintext: ");
    print_binary(plaintext, length);
    ctr_encrypt_decrypt(plaintext, ciphertext, key, counter, length);
    printf("Ciphertext: ");
    print_binary(ciphertext, length);

    // Decryption (CTR mode decryption is the same as encryption)
    ctr_encrypt_decrypt(ciphertext, decrypted_text, key, counter, length);
    printf("Decrypted text: ");
    print_binary(decrypted_text, length);

    return 0;
}

