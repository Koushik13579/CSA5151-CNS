#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void removeDuplicates(char* str) {
    int len = strlen(str);
    int index = 0;

    for (int i = 0; i < len; i++) {
        int j;
        for (j = 0; j < i; j++) {
            if (str[i] == str[j]) {
                break;
            }
        }
        if (j == i) {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}

void generateCipherAlphabet(char* keyword, char* cipherAlphabet) {
    char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int index = 0;
    for (int i = 0; keyword[i]; i++) {
        keyword[i] = toupper(keyword[i]);
    }
    removeDuplicates(keyword);

    for (int i = 0; keyword[i]; i++) {
        cipherAlphabet[index++] = keyword[i];
    }

    for (int i = 0; i < 26; i++) {
        if (!strchr(keyword, alphabet[i])) {
            cipherAlphabet[index++] = alphabet[i];
        }
    }
    cipherAlphabet[index] = '\0';
}

void encrypt(char* plaintext, char* cipherAlphabet, char* ciphertext) {
    char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; plaintext[i]; i++) {
        if (isalpha(plaintext[i])) {
            int isLower = islower(plaintext[i]);
            char upperChar = toupper(plaintext[i]);
            int pos = strchr(alphabet, upperChar) - alphabet;
            ciphertext[i] = isLower ? tolower(cipherAlphabet[pos]) : cipherAlphabet[pos];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(char* ciphertext, char* cipherAlphabet, char* decryptedtext) {
    char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            int isLower = islower(ciphertext[i]);
            char upperChar = toupper(ciphertext[i]);
            int pos = strchr(cipherAlphabet, upperChar) - cipherAlphabet;
            decryptedtext[i] = isLower ? tolower(alphabet[pos]) : alphabet[pos];
        } else {
            decryptedtext[i] = ciphertext[i];
        }
    }
    decryptedtext[strlen(ciphertext)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipherAlphabet[27];
    char plaintext[256];
    char ciphertext[256];
    char decryptedtext[256];

    generateCipherAlphabet(keyword, cipherAlphabet);

    printf("Cipher alphabet: %s\n", cipherAlphabet);

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    encrypt(plaintext, cipherAlphabet, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, cipherAlphabet, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

