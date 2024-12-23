#include <stdio.h>
#include <string.h>

void railFenceEncrypt(char message[], int key, char encrypted[]) {
    int len = strlen(message);
    int index = 0;

    for (int row = 0; row < key; row++) {
        int step1 = (key - row - 1) * 2;
        int step2 = row * 2;
        int pos = row;

        while (pos < len) {
            encrypted[index++] = message[pos];
            if (step1 > 0 && pos + step1 < len) pos += step1;
            else pos += step2;
        }
    }
  
}

void railFenceDecrypt(char encrypted[], int key, char decrypted[]) {
    int len = strlen(encrypted);
    int index = 0;
    char grid[key][len];

    memset(grid, 0, sizeof(grid));

    for (int row = 0; row < key; row++) {
        int step1 = (key - row - 1) * 2;
        int step2 = row * 2;
        int pos = row;

        while (pos < len) {
            grid[row][pos] = 1;
            if (step1 > 0 && pos + step1 < len) pos += step1;
            else pos += step2;
        }
    }

    for (int row = 0; row < key; row++) {
        for (int col = 0; col < len; col++) {
            if (grid[row][col] == 1) grid[row][col] = encrypted[index++];
        }
    }

    index = 0;
    for (int col = 0; col < len; col++) {
        for (int row = 0; row < key; row++) {
            if (grid[row][col] > 0) decrypted[index++] = grid[row][col];
        }
    }
    
}

int main() {
    char message[100], encrypted[100], decrypted[100];
    int key;

    printf("Enter the message: ");
    scanf("%s", message);
    printf("Enter the key (number of rows): ");
    scanf("%d", &key);

    railFenceEncrypt(message, key, encrypted);
    printf("Encrypted Text: %s\n", encrypted);

    railFenceDecrypt(encrypted, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
