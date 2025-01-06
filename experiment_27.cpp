#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute power of a number modulo m
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // exp = exp / 2
        base = (base * base) % mod;
    }
    
    return result;
}

// Function to encrypt a single character
int encryptChar(char c, long long e, long long n) {
    int num = (c - 'A');  // Convert character to an integer between 0-25
    return modExp(num, e, n);
}

// Function to decrypt a single number (ciphertext)
char decryptChar(int cipher, long long d, long long n) {
    int num = modExp(cipher, d, n);  // Decrypt the number
    return (char)(num + 'A');  // Convert the number back to a character
}

int main() {
    // Example RSA values
    long long p = 61;  // Prime p
    long long q = 53;  // Prime q
    long long n = p * q;  // Modulus n
    long long phi = (p - 1) * (q - 1);  // Euler's totient function
    
    long long e = 17;  // Public exponent
    long long d = 2753;  // Private exponent (precomputed, for simplicity)

    printf("Public key: (e = %lld, n = %lld)\n", e, n);
    printf("Private key: (d = %lld, n = %lld)\n", d, n);

    // Encrypting a message
    char message[] = "HELLO";
    printf("\nOriginal message: %s\n", message);
    int ciphertext[sizeof(message)/sizeof(message[0])];

    // Encrypt each character in the message
    for (int i = 0; message[i] != '\0'; i++) {
        ciphertext[i] = encryptChar(message[i], e, n);
        printf("Encrypted %c: %d\n", message[i], ciphertext[i]);
    }

    // Decrypting the ciphertext
    printf("\nDecrypted message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        printf("%c", decryptChar(ciphertext[i], d, n));
    }

    printf("\n");

    return 0;
}

