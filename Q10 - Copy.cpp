#include <stdio.h>
#include <string.h>

#define SIZE 5


void createPlayfairMatrix(char key[], char matrix[SIZE][SIZE]) {
    int keyLength = strlen(key);
    int i, j, k;
    int used[26] = {0};

    k = 0;
    for (i = 0; i < keyLength; ++i) {
        if (key[i] == 'J')
            key[i] = 'I'; 

        if (!used[key[i] - 'A']) {
            matrix[k / SIZE][k % SIZE] = key[i];
            used[key[i] - 'A'] = 1;
            ++k;
        }
    }

    for (i = 0; i < 26; ++i) {
        if (i != ('J' - 'A') && !used[i]) {
            matrix[k / SIZE][k % SIZE] = i + 'A';
            ++k;
        }
    }
}


void displayMatrix(char matrix[SIZE][SIZE]) {
    printf("Playfair Matrix:\n");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char key[] = "MFHIJKUNOPQZVWXYELARGDSTBC"; 
    char playfairMatrix[SIZE][SIZE];

    createPlayfairMatrix(key, playfairMatrix);
    displayMatrix(playfairMatrix);

    return 0;
}

