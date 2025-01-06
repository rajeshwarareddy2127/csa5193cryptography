#include <stdio.h>
#include <stdint.h>


unsigned long long factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
   
    unsigned long long totalPossibleKeys = factorial(25); 

    printf("Total possible keys without considering symmetrical equivalence: %llu\n", totalPossibleKeys);



    printf("Estimated effectively unique keys considering symmetrical properties: %llu\n", effectivelyUniqueKeys);

    return 0;
}

