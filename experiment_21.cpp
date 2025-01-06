#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8 // Block size in bytes

// XOR function for blocks
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output, size_t size) {
    for (size_t i = 0; i < size; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

// Placeholder encryption function (reverse bytes for simplicity)
void encrypt_block(uint8_t *input, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[BLOCK_SIZE - 1 - i];
    }
}

// ECB encryption
void ecb_encrypt(uint8_t *plaintext, size_t length, uint8_t *ciphertext) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        encrypt_block(&plaintext[i], &ciphertext[i]);
    }
}

// CBC encryption
void cbc_encrypt(uint8_t *plaintext, size_t length, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t current_block[BLOCK_SIZE];
    uint8_t previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE); // Initialize with IV

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        xor_blocks(&plaintext[i], previous_block, current_block, BLOCK_SIZE);
        encrypt_block(current_block, &ciphertext[i]);
        memcpy(previous_block, &ciphertext[i], BLOCK_SIZE);
    }
}

// CFB encryption
void cfb_encrypt(uint8_t *plaintext, size_t length, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE); // Initialize feedback with IV

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t encrypted_feedback[BLOCK_SIZE];
        encrypt_block(feedback, encrypted_feedback); // Encrypt the feedback
        xor_blocks(&plaintext[i], encrypted_feedback, &ciphertext[i], BLOCK_SIZE);
        memcpy(feedback, &ciphertext[i], BLOCK_SIZE); // Update feedback with ciphertext
    }
}

// Padding function
size_t pad(uint8_t *data, size_t length) {
    size_t padded_length = (length / BLOCK_SIZE + 1) * BLOCK_SIZE;
    size_t padding_size = padded_length - length;

    data[length] = 0x80; // Add a 1 bit followed by zeros
    for (size_t i = length + 1; i < padded_length; i++) {
        data[i] = 0x00;
    }
    return padded_length;
}

// Helper function to print data in hexadecimal format
void print_hex(uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t plaintext[] = "This is a test message for encryption.";
    size_t plaintext_len = strlen((char *)plaintext);

    // Allocate memory for padded plaintext
    uint8_t padded_plaintext[BLOCK_SIZE * ((plaintext_len / BLOCK_SIZE) + 2)];
    memcpy(padded_plaintext, plaintext, plaintext_len);

    // Pad plaintext
    size_t padded_len = pad(padded_plaintext, plaintext_len);

    // Initialize IV
    uint8_t iv[BLOCK_SIZE] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11};

    // Ciphertext buffers
    uint8_t ecb_ciphertext[padded_len];
    uint8_t cbc_ciphertext[padded_len];
    uint8_t cfb_ciphertext[padded_len];

    // Encrypt using ECB, CBC, and CFB modes
    ecb_encrypt(padded_plaintext, padded_len, ecb_ciphertext);
    cbc_encrypt(padded_plaintext, padded_len, NULL, iv, cbc_ciphertext);
    cfb_encrypt(padded_plaintext, padded_len, NULL, iv, cfb_ciphertext);

    // Print results
    printf("Plaintext (padded): ");
    print_hex(padded_plaintext, padded_len);

    printf("ECB Ciphertext:     ");
    print_hex(ecb_ciphertext, padded_len);

    printf("CBC Ciphertext:     ");
    print_hex(cbc_ciphertext, padded_len);

    printf("CFB Ciphertext:     ");
    print_hex(cfb_ciphertext, padded_len);

    return 0;
}

