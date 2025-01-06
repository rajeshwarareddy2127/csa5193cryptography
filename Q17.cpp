#include <stdio.h>
#include <stdint.h>


void reverseSubkeys(uint64_t keys[]) {
    uint64_t temp;
    for (int i = 0; i < 8; ++i) {
        temp = keys[i];
        keys[i] = keys[15 - i];
        keys[15 - i] = temp;
    }
}


void desDecrypt(uint64_t plaintext, uint64_t keys[]) {

}

int main() {
   
    uint64_t plaintext = 0x0123456789ABCDEF; 
    uint64_t subkeys[16] = {
        0xFFFFFFFFFFFFFFFF, 
        // ...
        0x0123456789ABCDEF
    };

    
    reverseSubkeys(subkeys);

    
    desDecrypt(plaintext, subkeys);

    return 0;
}

