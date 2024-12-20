#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate modular inverse of 'a' under modulo 'm'
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Encryption function: C = (a * p + b) % 26
void encryptAffineCipher(char plaintext[], int a, int b, char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((a * (plaintext[i] - offset) + b) % 26) + offset;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Decryption function: p = a_inv * (C - b) % 26
void decryptAffineCipher(char ciphertext[], int a, int b, char plaintext[]) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Error: 'a' has no modular inverse under modulo 26. Decryption is not possible.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((a_inv * ((ciphertext[i] - offset) - b + 26)) % 26) + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Check if 'a' is coprime with 26
int isCoprime(int a, int m) {
    int t;
    while (m != 0) {
        t = a % m;
        a = m;
        m = t;
    }
    return (a == 1);
}

int main() {
    char plaintext[100], ciphertext[100], decryptedText[100];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);

    if (!isCoprime(a, 26)) {
        printf("Error: 'a' must be coprime with 26 for the cipher to work correctly.\n");
        return 1;
    }

    encryptAffineCipher(plaintext, a, b, ciphertext);
    printf("\nEncrypted text: %s\n", ciphertext);

    decryptAffineCipher(ciphertext, a, b, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

