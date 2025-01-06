#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long mod_pow(long long base, long long exponent, long long modulus) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

long long rsa_encrypt(long long plaintext, long long public_key, long long modulus) {
    return mod_pow(plaintext, public_key, modulus);
}

int main() {
    long long n = 3233; // Replace with your modulus (n)
    long long e = 17;   // Replace with your public exponent (e)

    
    long long plaintext = 12;
    long long ciphertext = rsa_encrypt(plaintext, e, n);

    printf("Plaintext: %lld\n", plaintext);
    printf("Ciphertext: %lld\n", ciphertext);

    return 0;
}

