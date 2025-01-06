#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long long power(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}
void diffieHellman(int q, int alpha, int xa, int xb) {
    long long ya = power(alpha, xa, q);
    long long yb = power(alpha, xb, q);
    long long ka = power(yb, xa, q);
    long long kb = power(ya, xb, q);

    printf("Public keys exchanged:\n");
    printf("Alice's public key (ya): %lld\n", ya);
    printf("Bob's public key (yb): %lld\n\n", yb);

    printf("Shared secret keys calculated:\n");
    printf("Key for Alice (ka): %lld\n", ka);
    printf("Key for Bob (kb): %lld\n", kb);
}

int main() {

    int q = 23;
    int alpha = 5;
    int xa = 6;  
    int xb = 15; 

    diffieHellman(q, alpha, xa, xb);

    return 0;
}

