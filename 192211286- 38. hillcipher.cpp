#include <stdio.h>

int charToNum(char c) { return c - 'a'; }
char numToChar(int n) { return n + 'a'; }

void hillCipherEncrypt(char *message, int key[2][2], char *ciphertext) {
    for (int i = 0; i < 2; i++) {
        int x = charToNum(message[i * 2]);
        int y = charToNum(message[i * 2 + 1]);
        ciphertext[i * 2] = numToChar((key[0][0] * x + key[0][1] * y) % 26);
        ciphertext[i * 2 + 1] = numToChar((key[1][0] * x + key[1][1] * y) % 26);
    }
    ciphertext[4] = '\0';
}

int modInverse(int a) {
    for (int x = 1; x < 26; x++) if ((a * x) % 26 == 1) return x;
    return -1;
}

void inverseMatrix(int m[2][2], int inv[2][2]) {
    int det = (m[0][0] * m[1][1] - m[0][1] * m[1][0] + 26) % 26;
    int invDet = modInverse(det);
    inv[0][0] = (m[1][1] * invDet) % 26;
    inv[0][1] = (-m[0][1] * invDet + 26) % 26;
    inv[1][0] = (-m[1][0] * invDet + 26) % 26;
    inv[1][1] = (m[0][0] * invDet) % 26;
}

void multiplyMatrices(int a[2][2], int b[2][2], int res[2][2]) {
    res[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % 26;
    res[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % 26;
    res[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % 26;
    res[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % 26;
}

void determineKeyMatrix(char *plaintext, char *ciphertext, int key[2][2]) {
    int P[2][2] = {{charToNum(plaintext[0]), charToNum(plaintext[1])}, 
                   {charToNum(plaintext[2]), charToNum(plaintext[3])}};
    int C[2][2] = {{charToNum(ciphertext[0]), charToNum(ciphertext[1])}, 
                   {charToNum(ciphertext[2]), charToNum(ciphertext[3])}};
    int P_inv[2][2];
    inverseMatrix(P, P_inv);
    multiplyMatrices(C, P_inv, key);
}

int main() {
    char plaintext[] = "help";
    char ciphertext[5];
    int knownKey[2][2] = {{9, 4}, {5, 7}};
    
    hillCipherEncrypt(plaintext, knownKey, ciphertext);
    printf("Original plaintext: %s\nEncrypted ciphertext: %s\n", plaintext, ciphertext);
    
    int key[2][2];
    determineKeyMatrix(plaintext, ciphertext, key);
    printf("Determined key matrix:\n%d %d\n%d %d\n", key[0][0], key[0][1], key[1][0], key[1][1]);
    
    return 0;
}

