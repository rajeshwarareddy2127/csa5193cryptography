#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Block size (in bits) for AES (can be adjusted)
#define BLOCK_SIZE 8 // 64 bits (8 bytes)

// Example key (56-bit key for DES, can be expanded for AES)
uint64_t key = 0x133457799BBCDFF1;

// Simple XOR function to mimic DES-like encryption (for illustration)
uint64_t xor_encrypt(uint64_t data, uint64_t key) {
    return data ^ key;
}

// Padding function: Adds padding to make plaintext a multiple of the block size
void pad_plaintext(uint8_t* plaintext, int* length) {
    int padding_size = BLOCK_SIZE - (*length % BLOCK_SIZE);
    if (padding_size == BLOCK_SIZE) {
        padding_size = 0;
    }
    for (int i = *length; i < *length + padding_size; i++) {
        plaintext[i] = 0x00; // Adding zero bytes for padding
    }
    *length += padding_size;
}

// ECB Mode: Each block is encrypted independently
void ecb_encrypt(uint8_t* plaintext, uint8_t* ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        uint64_t block = *(uint64_t*)&plaintext[i];
        uint64_t encrypted_block = xor_encrypt(block, key);
        *(uint64_t*)&ciphertext[i] = encrypted_block;
    }
}

// CBC Mode: XOR each block with the previous ciphertext block before encryption
void cbc_encrypt(uint8_t* plaintext, uint8_t* ciphertext, int length, uint64_t iv) {
    uint64_t prev_ciphertext = iv;
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        uint64_t block = *(uint64_t*)&plaintext[i];
        block ^= prev_ciphertext; // XOR with previous ciphertext or IV for the first block
        uint64_t encrypted_block = xor_encrypt(block, key);
        *(uint64_t*)&ciphertext[i] = encrypted_block;
        prev_ciphertext = encrypted_block; // Update previous ciphertext
    }
}

// CFB Mode: Feedback of previous ciphertext block to the encryption process
void cfb_encrypt(uint8_t* plaintext, uint8_t* ciphertext, int length, uint64_t iv) {
    uint64_t feedback = iv;
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        uint64_t encrypted_feedback = xor_encrypt(feedback, key);
        uint64_t block = *(uint64_t*)&plaintext[i];
        uint64_t encrypted_block = encrypted_feedback ^ block; // XOR with the plaintext
        *(uint64_t*)&ciphertext[i] = encrypted_block;
        feedback = encrypted_block; // Update feedback with ciphertext block
    }
}

// Function to print hexadecimal representation of data
void print_hex(uint8_t* data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    // Example plaintext (should be a multiple of the block size)
    uint8_t plaintext[] = "This is a secret message!";
    int length = strlen((char*)plaintext);

    // Pad the plaintext to a multiple of BLOCK_SIZE
    pad_plaintext(plaintext, &length);

    // Ciphertext buffer
    uint8_t ciphertext[length];

    // Initialization Vector (for CBC and CFB)
    uint64_t iv = 0x123456789abcdef0;

    printf("Original plaintext: ");
    print_hex(plaintext, length);

    // ECB Encryption
    ecb_encrypt(plaintext, ciphertext, length);
    printf("Encrypted (ECB): ");
    print_hex(ciphertext, length);

    // CBC Encryption
    cbc_encrypt(plaintext, ciphertext, length, iv);
    printf("Encrypted (CBC): ");
    print_hex(ciphertext, length);

    // CFB Encryption
    cfb_encrypt(plaintext, ciphertext, length, iv);
    printf("Encrypted (CFB): ");
    print_hex(ciphertext, length);

    return 0;
}

