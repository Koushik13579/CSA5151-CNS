#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

void encrypt(const char* plaintext, const int* keystream, char* ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            ciphertext[i] = ((plaintext[i] - base + keystream[i]) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

void decrypt(const char* ciphertext, const int* keystream, char* plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = ((ciphertext[i] - base - keystream[i] + 26) % 26) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    const char* plaintext = "send more money";
    const int keystream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[MAX_LEN];

    encrypt(plaintext, keystream, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    const char* target_plaintext = "cash not needed";
    int new_keystream[MAX_LEN];
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            int cipher_val = ciphertext[i] - base;
            int plain_val = target_plaintext[i] - base;
            new_keystream[i] = (cipher_val - plain_val + 26) % 26;
        } else {
            new_keystream[i] = 0; 
        }
    }

    printf("New keystream for decryption to 'cash not needed': ");
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            printf("%d ", new_keystream[i]);
        }
    }
    printf("\n");

    return 0;
}

