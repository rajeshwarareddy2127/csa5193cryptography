#include <stdio.h>
#include <stdint.h>

// Key for S-DES
uint8_t key[10] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 1}; // 01111 11101

// Initial counter value
uint8_t counter = 0;

// S-DES S-boxes
uint8_t sBox0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

uint8_t sBox1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

// S-DES functions
void generateRoundKeys(uint8_t* roundKeys, uint8_t* key);
void encrypt(uint8_t* input, uint8_t* output, uint8_t* roundKeys);
void decrypt(uint8_t* input, uint8_t* output, uint8_t* roundKeys);

int main() {
    // Plaintext: 0000 0001 0000 0010 0000 0100
    uint8_t plaintext[8] = {0, 0, 0, 1, 0, 0, 0, 0};

    // Ciphertext: 0011 1000 0100 1111 0011 0010
    uint8_t ciphertext[8] = {0, 0, 1, 1, 1, 0, 0, 0};

    // Initialize round keys
    uint8_t roundKeys[16];
    generateRoundKeys(roundKeys, key);

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, roundKeys);

    // Print the encrypted ciphertext
    printf("Encrypted Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    decrypt(ciphertext, plaintext, roundKeys);

    // Print the decrypted plaintext
    printf("Decrypted Plaintext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", plaintext[i]);
    }
    printf("\n");

    return 0;
}

void generateRoundKeys(uint8_t* roundKeys, uint8_t* key) {
    // Implement key generation logic here
    // For simplicity, this example uses the given key as round keys
    for (int i = 0; i < 16; i++) {
        roundKeys[i] = key[i % 10];
    }
}

void encrypt(uint8_t* input, uint8_t* output, uint8_t* roundKeys) {
    // Implement encryption logic here
    // For simplicity, this example uses a counter mode
    for (int i = 0; i < 8; i++) {
        output[i] = input[i] ^ roundKeys[i + counter];
    }
    counter++;
}

void decrypt(uint8_t* input, uint8_t* output, uint8_t* roundKeys) {
    // Implement decryption logic here
    // For simplicity, this example uses the same logic as encryption
    encrypt(input, output, roundKeys);
}

