#include <stdio.h>

// Function to compute the GCD and Extended Euclidean Algorithm
int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// Function to compute modular inverse
int modular_inverse(int e, int phi) {
    int x, y;
    int gcd = extended_gcd(e, phi, &x, &y);
    if (gcd != 1) {
        printf("Modular inverse does not exist.\n");
        return -1;
    }
    return (x % phi + phi) % phi; // Ensure the result is positive
}

// Main function
int main() {
    int n = 3599, e = 31, p, q, phi, d;

    // Step 1: Factorize n to find p and q
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }
    printf("Factors of n: p = %d, q = %d\n", p, q);

    // Step 2: Compute phi(n)
    phi = (p - 1) * (q - 1);
    printf("Phi(n): %d\n", phi);

    // Step 3: Compute the private key d
    d = modular_inverse(e, phi);
    if (d != -1) {
        printf("Private key (d): %d\n", d);
    }

    return 0;
}

