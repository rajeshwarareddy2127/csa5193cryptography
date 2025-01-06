#include <stdio.h>

int main() {
    char mostFrequent = 'B'; 
    char secondFrequent = 'U'; 

    int positionB = mostFrequent - 'A'; 
    int positionU = secondFrequent - 'A'; 

    int a, b; 


    int diffPositions = (positionB - positionU + 26) % 26; 
    int gcd = 1; 

    for (int i = 2; i <= diffPositions; i++) {
        if (diffPositions % i == 0 && 26 % i == 0) {
            gcd = i;
            break;
        }
    }

   
    for (a = 1; a < 26; a++) {
        if ((a * gcd) % 26 == 1) {
            break;
        }
    }

    
    b = ((positionB - (a * positionU)) + 26) % 26;

    printf("Coefficients a: %d, b: %d\n", a, b);

    
    return 0;
}

