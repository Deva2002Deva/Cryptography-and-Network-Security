#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000
#define ALPHABET_SIZE 26

// Frequency of letters in the English language (approximate)
double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

// Function to calculate the frequency of letters in a text
void calculateFrequencies(const char *text, double *frequencies) {
    int count[ALPHABET_SIZE] = {0};
    int total = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            count[tolower(text[i]) - 'a']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = (double)count[i] / total * 100;
    }
}

// Function to score a text based on letter frequency comparison
double scoreText(const char *text) {
    double frequencies[ALPHABET_SIZE];
    calculateFrequencies(text, frequencies);

    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += frequencies[i] * englishFrequencies[i];
    }
    return score;
}

// Function to decrypt text with a given key
void decrypt(const char *ciphertext, int key, char *plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            plaintext[i] = ((tolower(ciphertext[i]) - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

// Function to perform a frequency attack and find the top N possible plaintexts
void frequencyAttack(const char *ciphertext, int topN) {
    double scores[ALPHABET_SIZE];
    char possiblePlaintexts[ALPHABET_SIZE][MAX_TEXT_LENGTH];

    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, key, possiblePlaintexts[key]);
        scores[key] = scoreText(possiblePlaintexts[key]);
    }

    // Sort the possible plaintexts by score in descending order
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[j] > scores[i]) {
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                char tempText[MAX_TEXT_LENGTH];
                strcpy(tempText, possiblePlaintexts[i]);
                strcpy(possiblePlaintexts[i], possiblePlaintexts[j]);
                strcpy(possiblePlaintexts[j], tempText);
            }
        }
    }

    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        printf("%2d: %s\n", i + 1, possiblePlaintexts[i]);
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    printf("Enter the number of top possible plaintexts you want to see: ");
    scanf("%d", &topN);

    frequencyAttack(ciphertext, topN);

    return 0;
}
