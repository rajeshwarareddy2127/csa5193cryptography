#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 2


int determinant(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}


int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}


void matrixInverse(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(key);
    int detInv = modInverse(det, 26);

    inverse[0][0] = key[1][1] * detInv % 26;
    inverse[0][1] = (-key[0][1] + 26) * detInv % 26;
    inverse[1][0] = (-key[1][0] + 26) * detInv % 26;
    inverse[1][1] = key[0][0] * detInv % 26;

    // Adjust negative values
    if (inverse[0][1] < 0)
        inverse[0][1] += 26;
    if (inverse[1][0] < 0)
        inverse[1][0] += 26;
}


void hillCipherDecrypt(int ciphertext[], int key[MATRIX_SIZE][MATRIX_SIZE], int length) {
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    matrixInverse(key, inverse);

    for (int i = 0; i < length; i += 2) {
        int c1 = ciphertext[i];
        int c2 = ciphertext[i + 1];

        int decrypted1 = (inverse[0][0] * c1 + inverse[0][1] * c2) % 26;
        int decrypted2 = (inverse[1][0] * c1 + inverse[1][1] * c2) % 26;

        printf("%c%c", (char)(decrypted1 + 'A'), (char)(decrypted2 + 'A'));
    }
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{9, 4}, {5, 7}};
    int ciphertext[] = {15, 0, 25, 17, 15, 21}; 
    int length = sizeof(ciphertext) / sizeof(ciphertext[0]);

    printf("Recovered plaintext from ciphertext:\n");
    hillCipherDecrypt(ciphertext, key, length);

    return 0;
}

