#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

char encrypt(char p, int a, int b) {
    if (isalpha(p)) {
        p = toupper(p);
        return (char)(((a * (p - 'A') + b) % 26) + 'A');
    }
    return p;
}

char decrypt(char c, int a, int b) {
    if (isalpha(c)) {
        c = toupper(c);
        int a_inv = modInverse(a, 26);
        if (a_inv == -1) {
            fprintf(stderr, "Error: 'a' has no modular inverse. Decryption impossible.\n");
            exit(1);
        }
        return (char)((a_inv * (c - 'A' - b + 26) % 26) + 'A');
    }
    return c;
}

int main() {
    int a, b;
    char plaintext[] = "HELLO";
    char ciphertext[sizeof(plaintext)];

    printf("Enter values for a and b (a should be coprime with 26): ");
    scanf("%d %d", &a, &b);

    if (modInverse(a, 26) == -1) {
        fprintf(stderr, "Error: 'a' must be coprime with 26.\n");
        return 1;
    }

    for (size_t i = 0; i < sizeof(plaintext) - 1; i++) {
        ciphertext[i] = encrypt(plaintext[i], a, b);
    }
    ciphertext[sizeof(plaintext) - 1] = '\0';

    printf("Encrypted text: %s\n", ciphertext);

    char decrypted_text[sizeof(ciphertext)];
    for (size_t i = 0; i < sizeof(ciphertext) - 1; i++) {
        decrypted_text[i] = decrypt(ciphertext[i], a, b);
    }
    decrypted_text[sizeof(ciphertext) - 1] = '\0';

    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}

