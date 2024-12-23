#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 500

// Function to count character frequencies
void countFrequencies(const char *text, int freq[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isprint(text[i])) {
            freq[(unsigned char)text[i]]++;
        }
    }
}

// Function to print frequency analysis
void printFrequencies(int freq[]) {
    printf("Character Frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i, freq[i]);
        }
    }
}

// Function to substitute characters based on mapping
void substituteText(const char *ciphertext, const char mapping[], char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            plaintext[i] = mapping[(unsigned char)ciphertext[i]];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    const char ciphertext[] = "53\u2020\u2020305))6*;4826)4\u2020.)4\u2020);806*;48\u20208\u00b660))85;;]8*;:\u2020*8\u202083 (88)5*\u2020;46(;88*96*?;8)*\u2020(;485);5*\u20202:*\u2020(;4956*2(5*\u20144)8\u00b68*;4069285);)6\u20208)4\u2020\u2020;1(\u20209;48081;8:8\u20201;48\u202085;4)485\u2020528806*81 (\u20209;48;(88;4(\u20203;48)4\u2020;161;:188;\u2020;";
    int freq[256] = {0};
    char plaintext[MAX_LENGTH];

    // Step 1: Frequency analysis
    countFrequencies(ciphertext, freq);
    printFrequencies(freq);

    // Step 2: Create a substitution mapping
    // Mapping example: modify based on observation from frequency analysis
    char mapping[256];
    for (int i = 0; i < 256; i++) {
        mapping[i] = i; // Default: no substitution
    }

    // Manually update mappings based on frequency and guesses
    mapping['‡'] = 'e';
    mapping[';'] = 't';
    mapping['*'] = 'h';
    mapping['8'] = 'o';
    mapping['4'] = 'a';
    mapping['6'] = 'n';
    mapping['5'] = 's';
    mapping['2'] = 'r';
    mapping['3'] = 'l';
    mapping['9'] = 'd';
    mapping[':'] = 'i';
    mapping[')'] = ' '; // Assuming parentheses are spaces

    // Step 3: Apply substitution
    substituteText(ciphertext, mapping, plaintext);

    // Step 4: Print decrypted text
    printf("\nDecrypted Text:\n%s\n", plaintext);

    return 0;
}

