#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1000


void generateCipherSequence(const char *keyword, char cipher[]) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;


    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

   
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }

    cipher[index] = '\0';
}

void encrypt(const char *plaintext, const char *cipher, char *encrypted) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            encrypted[i] = cipher[ch - 'A'];
            if (islower(plaintext[i])) {
                encrypted[i] = tolower(encrypted[i]);
            }
        } else {
            encrypted[i] = plaintext[i]; 
        }
    }
    encrypted[strlen(plaintext)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipher[ALPHABET_SIZE + 1];
    char plaintext[MAX_TEXT_SIZE];
    char encrypted[MAX_TEXT_SIZE];


    generateCipherSequence(keyword, cipher);

    printf("Generated Cipher Sequence:\n");
    printf("Plain:  abcdefghijklmnopqrstuvwxyz\n");
    printf("Cipher: %s\n", cipher);

    
    printf("\nEnter plaintext to encrypt: ");
    fgets(plaintext, MAX_TEXT_SIZE, stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

  
    encrypt(plaintext, cipher, encrypted);


    printf("\nEncrypted Text:\n%s\n", encrypted);

    return 0;
}

