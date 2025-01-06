#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void vigenereOneTimePadEncrypt(char plaintext[], int key[], int keyLength) {
    int plaintextLength = 0;
    while (plaintext[plaintextLength] != '\0') {
        plaintextLength++;
    }

    for (int i = 0; i < plaintextLength; i++) {
        if (!isalpha(plaintext[i])) {
            continue; 
        }

        int shift = key[i % keyLength]; 

        if (islower(plaintext[i])) {
            plaintext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
        } else if (isupper(plaintext[i])) {
            plaintext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
        }
    }

    printf("Encrypted Text: %s\n", plaintext);
}

int main() {
    char plaintext[] = "HelloWorld"; 
    int key[] = {3, 19, 5}; 

    int keyLength = sizeof(key) / sizeof(key[0]);

    printf("Plaintext: %s\n", plaintext);
    vigenereOneTimePadEncrypt(plaintext, key, keyLength);

    return 0;
}

