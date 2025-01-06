#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1; 
}
void generate_keys(int p, int q, int *n, int *e, int *d) {
    *n = p * q;
    int phi = (p - 1) * (q - 1);
    for (*e = 2; *e < phi; (*e)++) {
        if (gcd(*e, phi) == 1)
            break;
    }
    *d = mod_inverse(*e, phi);
}
int encrypt(int plaintext, int e, int n) {
    return (int)pow(plaintext, e) % n;
}
int decrypt(int ciphertext, int d, int n) {
    return (int)pow(ciphertext, d) % n;
}

int main() {
    int p = 61; 
    int q = 53; 
    int n, e, d;

    generate_keys(p, q, &n, &e, &d);

    int plaintext = 42; 

    int ciphertext = encrypt(plaintext, e, n);
    int decrypted_text = decrypt(ciphertext, d, n);

    printf("Original Message: %d\n", plaintext);
    printf("Encrypted Message: %d\n", ciphertext);
    printf("Decrypted Message: %d\n", decrypted_text);

    return 0;
}

