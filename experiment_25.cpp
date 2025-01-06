#include <stdio.h>

// Function to compute the GCD using the Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Main function
int main() {
    int n = 3599;  // Assume n is given
    int e = 31;    // Assume public key e is given
    int plaintext_block = 1777;  // Assume someone tells us a plaintext block
    int p, q;

    // Step 1: Find GCD of plaintext block and n
    int common_factor = gcd(plaintext_block, n);
    if (common_factor > 1 && common_factor < n) {
        printf("A common factor of plaintext and n is found: %d\n", common_factor);
        p = common_factor;
        q = n / p;
        printf("Factors of n: p = %d, q = %d\n", p, q);

        // Step 2: Compute phi(n)
        int phi = (p - 1) * (q - 1);
        printf("Phi(n): %d\n", phi);

        // Step 3: Compute private key d (modular inverse of e mod phi)
        int d = 0;
        for (int i = 1; i < phi; i++) {
            if ((e * i) % phi == 1) {
                d = i;
                break;
            }
        }

        if (d > 0) {
            printf("Private key (d): %d\n", d);
        } else {
            printf("Failed to compute private key.\n");
        }
    } else {
        printf("No common factor found. Unable to break RSA encryption.\n");
    }

    return 0;
}

