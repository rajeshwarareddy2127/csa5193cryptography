#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    used['J' - 'A'] = 1; // 'I' and 'J' are treated as the same letter
    int keyLen = strlen(key), k = 0;

    for (int i = 0; i < keyLen; i++) {
        char c = toupper(key[i]);
        if (!used[c - 'A'] && isalpha(c)) {
            used[c - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            matrix[k / SIZE][k % SIZE] = (char)(i + 'A');
            k++;
        }
    }
}

void findPosition(char matrix[SIZE][SIZE], char c, int *row, int *col) {
    if (c == 'J') c = 'I'; // Treat 'J' as 'I'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char a, char b, char matrix[SIZE][SIZE], char *result) {
    int r1, c1, r2, c2;

    findPosition(matrix, a, &r1, &c1);
    findPosition(matrix, b, &r2, &c2);

    if (r1 == r2) { // Same row
        result[0] = matrix[r1][(c1 + 1) % SIZE];
        result[1] = matrix[r2][(c2 + 1) % SIZE];
    } else if (c1 == c2) { // Same column
        result[0] = matrix[(r1 + 1) % SIZE][c1];
        result[1] = matrix[(r2 + 1) % SIZE][c2];
    } else { // Rectangle
        result[0] = matrix[r1][c2];
        result[1] = matrix[r2][c1];
    }
}

void prepareText(char text[], char prepared[]) {
    int len = strlen(text), k = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            prepared[k++] = toupper(text[i]);
        }
    }
    prepared[k] = '\0';

    // Add 'X' if needed to make pairs
    len = k;
    k = 0;
    char result[100];
    for (int i = 0; i < len; i++) {
        result[k++] = prepared[i];
        if (i + 1 < len && prepared[i] == prepared[i + 1]) {
            result[k++] = 'X';
        }
    }
    if (k % 2 != 0) result[k++] = 'X';
    result[k] = '\0';
    strcpy(prepared, result);
}

void encryptText(char plaintext[], char matrix[SIZE][SIZE], char ciphertext[]) {
    char prepared[100];
    prepareText(plaintext, prepared);

    int len = strlen(prepared);
    for (int i = 0; i < len; i += 2) {
        encryptPair(prepared[i], prepared[i + 1], matrix, &ciphertext[i]);
    }
    ciphertext[len] = '\0';
}

int main() {
    char key[100], plaintext[100], matrix[SIZE][SIZE], ciphertext[100];

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    createMatrix(key, matrix);
    printf("\n5x5 Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    encryptText(plaintext, matrix, ciphertext);
    printf("\nEncrypted text: %s\n", ciphertext);

    return 0;
}

