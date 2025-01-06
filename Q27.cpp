#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1)
            return x;
    return 0;
}
int power(int base, unsigned int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
int encrypt(int msg, int e, int n) {
    return power(msg, e, n);
}
int decrypt(int cipher, int d, int n) {
    return power(cipher, d, n);
}

int main() {
    int p = 61;
    int q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 17;
    int d = modInverse(e, phi);
    int msg = 7;
    int cipher = encrypt(msg, e, n);
    int decrypted_msg = decrypt(cipher, d, n);
    printf("Original message: %d\n", msg);
    printf("Encrypted message: %d\n", cipher);
    printf("Decrypted message: %d\n", decrypted_msg);

    return 0;
}

