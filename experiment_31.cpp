#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Block size constants
#define BLOCK_SIZE_128 16   // 128 bits
#define BLOCK_SIZE_64 8     // 64 bits

// Constants for CMAC generation based on block size
#define CONSTANT_128 0x87   // Constant for 128-bit block size
#define CONSTANT_64 0x1F    // Constant for 64-bit block size

// Function to perform the block cipher (e.g., AES, for simplicity we simulate it)
void block_cipher(uint8_t *input, uint8_t *output) {
    // Simulate block cipher (this is where you'd apply a real block cipher like AES)
    // Here, we simulate it by copying input to output (replace with real block cipher)
    memcpy(output, input, BLOCK_SIZE_128);
}

// Function to left shift a block by 1 bit
void left_shift(uint8_t *block, uint8_t *result, int block_size) {
    int i;
    uint8_t carry = 0;
    for (i = block_size - 1; i >= 0; i--) {
        uint8_t temp = block[i];
        block[i] = (block[i] << 1) | carry;
        carry = (temp >> 7) & 1;
    }

    memcpy(result, block, block_size);
}

// Function to XOR two blocks
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *result, int block_size) {
    for (int i = 0; i < block_size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

// Function to generate CMAC subkeys
void generate_cmac_subkeys(uint8_t *key, uint8_t *K1, uint8_t *K2, int block_size) {
    uint8_t block[BLOCK_SIZE_128] = {0}; // All-zero block
    uint8_t temp[BLOCK_SIZE_128] = {0};  // Temporary storage for blocks
    
    // Step 1: Apply block cipher to all-zero block to get the initial block
    block_cipher(block, temp);
    
    // Step 2: Left shift the block to get K1
    left_shift(temp, K1, block_size);
    
    // Check if XOR is needed for K1
    if (K1[0] & 0x80) { // If the leftmost bit is 1
        K1[block_size - 1] ^= CONSTANT_128;
    }

    // Step 3: Left shift K1 to get K2
    left_shift(K1, K2, block_size);
    
    // Check if XOR is needed for K2
    if (K2[0] & 0x80) { // If the leftmost bit is 1
        K2[block_size - 1] ^= CONSTANT_128;
    }
}

void print_block(uint8_t *block, int block_size) {
    for (int i = 0; i < block_size; i++) {
        printf("%02X ", block[i]);
    }
    printf("\n");
}

int main() {
    uint8_t key[BLOCK_SIZE_128] = {0};  // All-zero key for simplicity
    uint8_t K1[BLOCK_SIZE_128] = {0};  // First subkey
    uint8_t K2[BLOCK_SIZE_128] = {0};  // Second subkey
    
    // Generate subkeys for 128-bit block size
    generate_cmac_subkeys(key, K1, K2, BLOCK_SIZE_128);
    
    printf("Subkey K1 for 128-bit block: ");
    print_block(K1, BLOCK_SIZE_128);
    
    printf("Subkey K2 for 128-bit block: ");
    print_block(K2, BLOCK_SIZE_128);

    // Repeat for 64-bit block size
    uint8_t K1_64[BLOCK_SIZE_64] = {0};
    uint8_t K2_64[BLOCK_SIZE_64] = {0};
    
    // Generate subkeys for 64-bit block size
    generate_cmac_subkeys(key, K1_64, K2_64, BLOCK_SIZE_64);
    
    printf("Subkey K1 for 64-bit block: ");
    print_block(K1_64, BLOCK_SIZE_64);
    
    printf("Subkey K2 for 64-bit block: ");
    print_block(K2_64, BLOCK_SIZE_64);

    return 0;
}

