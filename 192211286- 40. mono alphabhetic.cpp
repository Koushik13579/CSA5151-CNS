#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1024

// Typical letter frequencies in English
double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

// Function to calculate letter frequencies in ciphertext
void calculateFrequencies(const char *text, int textLength, double *frequencies) {
    int count[ALPHABET_SIZE] = {0};
    for (int i = 0; i < textLength; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            count[text[i] - 'A']++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            count[text[i] - 'a']++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = ((double)count[i] / textLength) * 100;
    }
}

// Function to score a possible plaintext by comparing its frequencies with English frequencies
double scoreText(const double *frequencies) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += frequencies[i] * englishFrequencies[i];
    }
    return score;
}

// Function to decrypt a text using a given key
void decryptText(const char *ciphertext, char *plaintext, const char *key) {
    int textLength = strlen(ciphertext);
    for (int i = 0; i < textLength; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = key[ciphertext[i] - 'A'] + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = key[ciphertext[i] - 'a'] + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[textLength] = '\0';
}

// Function to generate possible keys (simple substitution based on frequency analysis)
void generateKeys(const double *cipherFrequencies, char keys[ALPHABET_SIZE][ALPHABET_SIZE]) {
    // Create an array of indices sorted by frequency
    int sortedIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i;
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (cipherFrequencies[sortedIndices[i]] < cipherFrequencies[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }
    
    // Generate possible keys by matching sorted cipher frequencies to English frequencies
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            keys[i][sortedIndices[j]] = (char)(j + 'A');
        }
    }
}

// Function to perform a letter frequency attack and produce possible plaintexts
void frequencyAttack(const char *ciphertext, int topN) {
    int textLength = strlen(ciphertext);
    double cipherFrequencies[ALPHABET_SIZE] = {0};
    calculateFrequencies(ciphertext, textLength, cipherFrequencies);

    char keys[ALPHABET_SIZE][ALPHABET_SIZE];
    generateKeys(cipherFrequencies, keys);

    char plaintext[MAX_TEXT_SIZE];
    double scores[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        decryptText(ciphertext, plaintext, keys[i]);
        double frequencies[ALPHABET_SIZE] = {0};
        calculateFrequencies(plaintext, textLength, frequencies);
        scores[i] = scoreText(frequencies);
    }

    // Print top N possible plaintexts
    for (int i = 0; i < topN; i++) {
        decryptText(ciphertext, plaintext, keys[i]);
        printf("Possible plaintext #%d: %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    frequencyAttack(ciphertext, topN);

    return 0;
}

