#include <stdio.h>
#include <string.h>


void encrypt(char plaintext[], char ciphertext[], char key[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
         
            ciphertext[i] = key[plaintext[i] - 'a'];
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            
            ciphertext[i] = key[plaintext[i] - 'A'] - 'a' + 'A';
        } else {
            
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}


void decrypt(char ciphertext[], char plaintext[], char key[]) {
    char reverseKey[26];

    
    for (int i = 0; i < 26; i++) {
        reverseKey[key[i] - 'a'] = 'a' + i;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            
            plaintext[i] = reverseKey[ciphertext[i] - 'a'];
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            
            plaintext[i] = reverseKey[ciphertext[i] - 'A'] - 'a' + 'A';
        } else {
           
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

int main() {
    char key[27] = "qwertyuiopasdfghjklzxcvbnm"; 
    char plaintext[100], ciphertext[100], decryptedText[100];

   
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    
    encrypt(plaintext, ciphertext, key);
    printf("Encrypted text: %s\n", ciphertext);

    
    decrypt(ciphertext, decryptedText, key);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

