#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16 // Define block size (e.g., 128-bit block)

// XOR-based "cipher" for simplicity
void xor_block(uint8_t* block1, uint8_t* block2, uint8_t* result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

// CBC MAC function for one-block message X
void cbc_mac(uint8_t* key, uint8_t* message, uint8_t* mac) {
    // Assume the key is not used in this simplified XOR cipher
    // Initialize the IV to 0
    uint8_t iv[BLOCK_SIZE] = {0};
    
    // Perform CBC MAC: T = C(IV || X)
    xor_block(iv, message, mac); // XOR the IV with the message block to create T
}

// Function to generate X ? T
void xor_message_with_mac(uint8_t* message, uint8_t* mac, uint8_t* result) {
    xor_block(message, mac, result);
}

int main() {
    // Example message X (16 bytes/128 bits)
    uint8_t message[BLOCK_SIZE] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10
    };
    
    uint8_t key[BLOCK_SIZE] = {0};  // In this simplified version, key is not used
    uint8_t mac[BLOCK_SIZE] = {0};  // CBC MAC output
    uint8_t message_with_mac[BLOCK_SIZE] = {0}; // X || (X ? T)

    // Step 1: Generate CBC MAC for the original message X
    cbc_mac(key, message, mac);
    
    printf("CBC MAC (T) of message X: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    // Step 2: Generate X ? T and append it to X to form X || (X ? T)
    xor_message_with_mac(message, mac, message_with_mac);
    
    printf("X ? T: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", message_with_mac[i]);
    }
    printf("\n");

    // Step 3: Now the adversary can compute the CBC MAC for X || (X ? T)
    uint8_t mac2[BLOCK_SIZE] = {0};
    cbc_mac(key, message_with_mac, mac2);

    printf("CBC MAC of X || (X ? T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac2[i]);
    }
    printf("\n");

    return 0;
}

