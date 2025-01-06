#include <stdio.h>
#include <math.h>

// Function to compute (base^exp) % mod using modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Public values (chosen values)
    long long a = 5;  // Public base
    long long q = 23; // Public prime modulus

    // Alice's secret number (private key)
    long long x_A = 6;

    // Bob's secret number (private key)
    long long x_B = 15;

    // Alice computes A = a^x_A % q and sends A to Bob
    long long A = modExp(a, x_A, q);
    printf("Alice sends A = %lld\n", A);

    // Bob computes B = a^x_B % q and sends B to Alice
    long long B = modExp(a, x_B, q);
    printf("Bob sends B = %lld\n", B);

    // Alice computes shared secret key K_A = B^x_A % q
    long long K_A = modExp(B, x_A, q);
    printf("Alice computes shared secret key K_A = %lld\n", K_A);

    // Bob computes shared secret key K_B = A^x_B % q
    long long K_B = modExp(A, x_B, q);
    printf("Bob computes shared secret key K_B = %lld\n", K_B);

    if (K_A == K_B) {
        printf("Alice and Bob share the same secret key: %lld\n", K_A);
    } else {
        printf("There was an error, the keys do not match.\n");
    }

    return 0;
}

