#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16

void print_hex(const char* label, const void* data, size_t size) {
    printf("%s: ", label);
    for (size_t i = 0; i < size; ++i) {
        printf("%02X ", ((const unsigned char*)data)[i]);
    }
    printf("\n");
}

void encrypt_decrypt_ecb(const char* input, const AES_KEY* key, int mode) {
    size_t input_length = strlen(input);
    size_t padded_length = (input_length + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE;
    unsigned char* padded_input = malloc(padded_length);
    memcpy(padded_input, input, input_length);
    memset(padded_input + input_length, 0, padded_length - input_length);

    unsigned char* output = malloc(padded_length);

    if (mode == AES_ENCRYPT) {
        AES_encrypt(padded_input, output, key);
        print_hex("Encrypted (ECB)", output, padded_length);
    } else if (mode == AES_DECRYPT) {
        AES_decrypt(output, padded_input, key);
        print_hex("Decrypted (ECB)", padded_input, padded_length);
    }

    free(padded_input);
    free(output);
}

void encrypt_decrypt_cbc(const char* input, const AES_KEY* key, const unsigned char* iv, int mode) {
    size_t input_length = strlen(input);
    size_t padded_length = (input_length + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE;
    unsigned char* padded_input = malloc(padded_length);
    memcpy(padded_input, input, input_length);
    memset(padded_input + input_length, 0, padded_length - input_length);

    unsigned char* output = malloc(padded_length);

    if (mode == AES_ENCRYPT) {
        AES_cbc_encrypt(padded_input, output, padded_length, key, iv, AES_ENCRYPT);
        print_hex("Encrypted (CBC)", output, padded_length);
    } else if (mode == AES_DECRYPT) {
        AES_cbc_encrypt(output, padded_input, padded_length, key, iv, AES_DECRYPT);
        print_hex("Decrypted (CBC)", padded_input, padded_length);
    }

    free(padded_input);
    free(output);
}

void encrypt_decrypt_cfb(const char* input, const AES_KEY* key, const unsigned char* iv, int mode) {
    size_t input_length = strlen(input);
    size_t padded_length = (input_length + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE;
    unsigned char* padded_input = malloc(padded_length);
    memcpy(padded_input, input, input_length);
    memset(padded_input + input_length, 0, padded_length - input_length);

    unsigned char* output = malloc(padded_length);

    if (mode == AES_ENCRYPT) {
        AES_cfb_encrypt(padded_input, output, padded_length, key, iv, NULL, AES_ENCRYPT);
        print_hex("Encrypted (CFB)", output, padded_length);
    } else if (mode == AES_DECRYPT) {
        AES_cfb_encrypt(output, padded_input, padded_length, key, iv, NULL, AES_DECRYPT);
        print_hex("Decrypted (CFB)", padded_input, padded_length);
    }

    free(padded_input);
    free(output);
}

int main() {
    // Set your key and IV (Initialization Vector)
    const char* key_data = "0123456789abcdef";
    const char* iv_data = "1234567890abcdef";

    AES_KEY key;
    if (AES_set_encrypt_key((const unsigned char*)key_data, 128, &key) != 0) {
        fprintf(stderr, "AES key setup failed\n");
        return 1;
    }

    unsigned char iv[AES_BLOCK_SIZE];
    memcpy(iv, iv_data, AES_BLOCK_SIZE);

    const char* plaintext = "Hello, AES encryption!";
    
    // Encrypt and decrypt using ECB mode
    encrypt_decrypt_ecb(plaintext, &key, AES_ENCRYPT);
    encrypt_decrypt_ecb(plaintext, &key, AES_DECRYPT);

    // Encrypt and decrypt using CBC mode
    encrypt_decrypt_cbc(plaintext, &key, iv, AES_ENCRYPT);
    encrypt_decrypt_cbc(plaintext, &key, iv, AES_DECRYPT);

    // Encrypt and decrypt using CFB mode
    encrypt_decrypt_cfb(plaintext, &key, iv, AES_ENCRYPT);
    encrypt_decrypt_cfb(plaintext, &key, iv, AES_DECRYPT);

    return 0;
}

