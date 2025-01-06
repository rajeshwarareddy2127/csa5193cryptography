#include <stdio.h>
#include <string.h>

#define SIZE 5


void findPosition(char keyTable[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') 
        ch = 'I';

    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (keyTable[*row][*col] == ch)
                return;
}


void decryptPlayfair(char cipher[], char key[]) {
    char keyTable[SIZE][SIZE];
    int i, j, row1, row2, col1, col2;

    
    int len = strlen(key);
    int k = 0;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
            if (k < len) {
                int found = 0;
                for (int l = 0; l < i * SIZE + j; l++) {
                    if (key[l] == key[i * SIZE + j]) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    keyTable[i][j] = key[k];
                    k++;
                } else {
                    j--;
                }
            } else {
                for (char ch = 'A'; ch <= 'Z'; ch++) {
                    int found = 0;
                    for (int l = 0; l < i * SIZE + j; l++) {
                        if (key[l] == ch || ch == 'J') {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        keyTable[i][j] = ch;
                        break;
                    }
                }
            }
        }

    
    len = strlen(cipher);
    i = 0;
    while (i < len) {
        findPosition(keyTable, cipher[i], &row1, &col1);
        findPosition(keyTable, cipher[i + 1], &row2, &col2);

        if (col1 == col2) {
            printf("%c%c", keyTable[(row1 + 4) % 5][col1], keyTable[(row2 + 4) % 5][col2]);
        } else if (row1 == row2) {
            printf("%c%c", keyTable[row1][(col1 + 4) % 5], keyTable[row2][(col2 + 4) % 5]);
        } else {
            printf("%c%c", keyTable[row1][col2], keyTable[row2][col1]);
        }
        i += 2;
    }
}

int main() {
    char cipher[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char key[] = "PT109"; 

    printf("Decrypted message:\n");
    decryptPlayfair(cipher, key);

    return 0;
}

