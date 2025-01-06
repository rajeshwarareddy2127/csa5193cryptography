#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the modular exponentiation (a^b mod m)
int mod_pow(int base, int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

// Function to find the multiplicative inverse of 'a' modulo 'm' using the extended Euclidean algorithm
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int p = /* your value of p */;
    int q = /* your value of q */;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 31; // given public key
    int d = mod_inverse(e, phi); // private key

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d): %d\n", d);

    // Now, you can use e, n for encryption and d for decryption

    return 0;
}

