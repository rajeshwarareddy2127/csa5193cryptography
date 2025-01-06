#include <stdio.h>
#include <stdlib.h>

// Function to compute GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular inverse
int modInverse(int e, int phi) {
    for (int x = 1; x < phi; x++) {
        if ((e * x) % phi == 1) {
            return x;
        }
    }
    return -1;
}

// Main function
int main() {
    int p = 61;  // Example prime
    int q = 53;  // Example prime
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 17;  // Public key (e must be coprime with phi)
    int d = modInverse(e, phi);  // Private key

    if (d == -1) {
        printf("Error: Could not compute modular inverse.\n");
        return 1;
    }

    printf("Original RSA Key Pair:\n");
    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n\n", d, n);

    // Simulating key leak
    printf("Private key leaked! Generating new keys with the same modulus...\n");

    // Generating new keys
    int new_e = 7;  // New public key
    int new_d = modInverse(new_e, phi);

    if (new_d == -1) {
        printf("Error: Could not compute modular inverse for new key.\n");
        return 1;
    }

    printf("New RSA Key Pair:\n");
    printf("Public Key: (e = %d, n = %d)\n", new_e, n);
    printf("Private Key: (d = %d, n = %d)\n\n", new_d, n);

    // Warning about security
    printf("WARNING: Reusing the same modulus (n) is NOT safe. An attacker can factor n if they know the leaked private key.\n");
    printf("The correct solution is to generate a new modulus (n) with new primes (p and q).\n");

    return 0;
}

