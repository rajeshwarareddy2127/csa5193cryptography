#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    int j = 0; 

    for (int i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            char keyOffset = isupper(key[j % keyLen]) ? 'A' : 'a';

            ciphertext[i] = ((plaintext[i] - offset + (key[j % keyLen] - keyOffset)) % 26) + offset;
            j++; 
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[textLen] = '\0';
}

void decrypt(char ciphertext[], char key[], char plaintext[]) {
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);
    int j = 0; 

    for (int i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyOffset = isupper(key[j % keyLen]) ? 'A' : 'a';

            plaintext[i] = ((ciphertext[i] - offset - (key[j % keyLen] - keyOffset) + 26) % 26) + offset;
            j++;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[textLen] = '\0';
}

int main() {
    char plaintext[100], key[100], ciphertext[100], decryptedText[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    encrypt(plaintext, key, ciphertext);
    printf("\nEncrypted text: %s\n", ciphertext);

    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
