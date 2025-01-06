#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26


void calculateFrequencies(const char *input, int frequencies[]) {
    int i;
    for (i = 0; i < strlen(input); i++) {
        char ch = tolower(input[i]);
        if (isalpha(ch)) {
            frequencies[ch - 'a']++;
        }
    }
}


void frequencyAttack(const char *ciphertext, int topPlaintexts) {
    int ciphertextLength = strlen(ciphertext);

    int frequencies[ALPHABET_SIZE] = {0};
    calculateFrequencies(ciphertext, frequencies);

    
    int maxFrequency = 0;
    char mostCommonLetter;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequencies[i] > maxFrequency) {
            maxFrequency = frequencies[i];
            mostCommonLetter = 'a' + i;
        }
    }

  
    int shift = mostCommonLetter - 'e';
    if (shift < 0) {
        shift += ALPHABET_SIZE;
    }

    
    printf("Top %d possible plaintexts:\n", topPlaintexts);
    for (int i = 0; i < topPlaintexts; i++) {
        printf("%d. ", i + 1);
        for (int j = 0; j < ciphertextLength; j++) {
            char ch = ciphertext[j];
            if (isalpha(ch)) {
                char decrypted = 'a' + ((tolower(ch) - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE);
                if (isupper(ch)) {
                    decrypted = toupper(decrypted);
                }
                printf("%c", decrypted);
            } else {
                printf("%c", ch);
            }
        }
        printf("\n");
        shift = (shift + 1) % ALPHABET_SIZE;
    }
}

int main() {
    char ciphertext[] = "Vtfeqi"; 

    int topPlaintexts;
    printf("Enter the number of top possible plaintexts to generate: ");
    scanf("%d", &topPlaintexts);

    frequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

