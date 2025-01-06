#include <stdio.h>
#include <stdint.h>

// Key for S-DES
uint8_t key[10] = {0, 1, 1, 1, 1, 1, 1, 0, 1, 0};

// Initialization vector for CBC mode
uint8_t iv[8] = {1, 0, 1, 0, 1, 0, 1, 0};

// S-DES S-box
uint8_t sBox[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

// Function to perform S-DES encryption on a single block
void encryptBlock(uint8_t *block, uint8_t *subKey) {
    // Permutation
    uint8_t temp[8];
    temp[0] = block[1];
    temp[1] = block[5];
    temp[2] = block[2];
    temp[3] = block[0];
    temp[4] = block[3];
    temp[5] = block[7];
    temp[6] = block[4];
    temp[7] = block[6];

    // XOR with subkey
    for (int i = 0; i < 8; i++) {
        temp[i] ^= subKey[i];
    }

    // S-box substitution
    uint8_t row = (temp[0] << 1) + temp[3];
    uint8_t col = (temp[1] << 1) + temp[2];
    uint8_t sBoxOutput = sBox[row][col];

    // Convert the result to binary
    for (int i = 0; i < 4; i++) {
        temp[3 - i] = (sBoxOutput >> i) & 1;
    }

    // Permutation P4
    uint8_t permutedOutput[4];
    permutedOutput[0] = temp[2];
    permutedOutput[1] = temp[0];
    permutedOutput[2] = temp[3];
    permutedOutput[3] = temp[1];

    // XOR with the left half of the block
    for (int i = 0; i < 4; i++) {
        block[i] ^= permutedOutput[i];
    }
}

// Function to perform CBC mode encryption
void encryptCBC(uint8_t *plaintext, uint8_t *key, uint8_t *iv, int blockCount) {
    uint8_t block[8];
    uint8_t previousBlock[8];
    int i, j;

    // Set the initial vector
    for (i = 0; i < 8; i++) {
        previousBlock[i] = iv[i];
    }

    // Encrypt each block
    for (i = 0; i < blockCount; i++) {
        // XOR with the previous block
        for (j = 0; j < 8; j++) {
            block[j] = plaintext[i * 8 + j] ^ previousBlock[j];
        }

        // Encrypt the current block
        encryptBlock(block, key);

        // Update the previous block for the next iteration
        for (j = 0; j < 8; j++) {
            previousBlock[j] = block[j];
        }

        // Print the encrypted block
        for (j = 0; j < 8; j++) {
            printf("%d", block[j]);
        }
    }

    printf("\n");
}

int main() {
    // Binary plaintext: 0000 0001 0010 0011
    uint8_t plaintext[] = {0, 0, 0, 0, 0, 0, 0, 1,
                           0, 0, 0, 1, 0, 0, 1, 0,
                           0, 0, 1, 0, 0, 1, 1, 0,
                           0, 0, 1, 1, 0, 0, 1, 1};

    // Binary key: 01111 11101
    uint8_t key[10] = {0, 1, 1, 1, 1, 1, 1, 0, 1, 0};

    // Binary initialization vector: 1010 1010
    uint8_t iv[8] = {1, 0, 1, 0, 1, 0, 1, 0};

    // Number of blocks
    int blockCount = sizeof(plaintext) / 8;

    // Perform CBC encryption
    encryptCBC(plaintext, key, iv, blockCount);

    return 0;
}

