#include <stdio.h>
#include <string.h>


void decryptCiphertext(char *ciphertext) {
    int freq[256] = {0}; 


    for (int i = 0; ciphertext[i] != '\0'; i++) {
        freq[(int)ciphertext[i]]++;
    }

    int mostFrequentChar = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > freq[mostFrequentChar]) {
            mostFrequentChar = i;
        }
    }


    int key = mostFrequentChar - 'e';

    
    printf("Decrypted message: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] == ' ') {
            printf(" ");
        } else if (ciphertext[i] >= '0' && ciphertext[i] <= '9') {
            printf("%c", ciphertext[i]);
        } else {
            char decryptedChar = ciphertext[i] - key;
            if (decryptedChar < 'A') {
                decryptedChar += 26;
            }
            printf("%c", decryptedChar);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                        ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
                        " (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    decryptCiphertext(ciphertext);

    return 0;
}

