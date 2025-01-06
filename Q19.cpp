#include <stdio.h>
#include <openssl/des.h>
#include <string.h>

void encryptDecryptDES(const unsigned char *input, unsigned char *output, const unsigned char *key, int encryptMode) {
    DES_cblock desKey1, desKey2, desKey3;
    DES_key_schedule keySchedule1, keySchedule2, keySchedule3;

    memcpy(desKey1, key, 8);
    memcpy(desKey2, key + 8, 8);
    memcpy(desKey3, key + 16, 8);

    DES_set_odd_parity(&desKey1);
    DES_set_odd_parity(&desKey2);
    DES_set_odd_parity(&desKey3);

    DES_set_key_checked(&desKey1, &keySchedule1);
    DES_set_key_checked(&desKey2, &keySchedule2);
    DES_set_key_checked(&desKey3, &keySchedule3);

    DES_cblock iv;
    memset(iv, 0, sizeof(iv)); 

    DES_ede3_cbc_encrypt(input, output, strlen((char *)input), &keySchedule1, &keySchedule2, &keySchedule3, &iv, encryptMode);
}

int main() {
    const unsigned char plaintext[] = "Hello, this is a message to be encrypted using 3DES CBC mode.";
    const unsigned char key[] = "123456789012345678901234"; 

    unsigned char encryptedData[1024];
    unsigned char decryptedData[1024];

   
    encryptDecryptDES(plaintext, encryptedData, key, DES_ENCRYPT);

    printf("Encrypted Data: %s\n", encryptedData);

    encryptDecryptDES(encryptedData, decryptedData, key, DES_DECRYPT);

    printf("Decrypted Data: %s\n", decryptedData);

    return 0;
}

