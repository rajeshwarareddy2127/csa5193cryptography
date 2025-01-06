#include <stdio.h>
#include <string.h>
#include <ctype.h>


void generateCipherSequence(char *keyword, char *cipherSequence) {
    int len = strlen(keyword);
    int index = 0;
    int used[26] = {0}; 

    
    strcpy(cipherSequence, keyword);
    index = len;

    
    for (int i = 0; i < len; i++) {
        used[toupper(keyword[i]) - 'A'] = 1;
    }

    
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch != 'J' && used[ch - 'A'] != 1) {
            cipherSequence[index++] = ch;
        }
    }
    cipherSequence[index] = '\0';
}


void monoalphabeticCipher(char *plaintext, char *cipherSequence) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int index = toupper(plaintext[i]) - 'A';
            plaintext[i] = isupper(plaintext[i]) ? toupper(cipherSequence[index]) : tolower(cipherSequence[index]);
        }
    }
    printf("Encrypted text: %s\n", plaintext);
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "Hello, World! This is a monoalphabetic cipher example.";

    char cipherSequence[27];
    generateCipherSequence(keyword, cipherSequence);

    printf("Generated Cipher Sequence: %s\n", cipherSequence);

    monoalphabeticCipher(plaintext, cipherSequence);

    return 0;
}

