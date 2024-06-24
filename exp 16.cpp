#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1000
#define ALPHABET_SIZE 26

// English letter frequency in decreasing order of likelihood
const char ENGLISH_FREQ[ALPHABET_SIZE + 1] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function prototypes
void countFrequencies(const char *text, int *freq);
void sortFrequencies(int *freq, char *sortedFreq);
void decrypt(const char *ciphertext, const char *key, char *plaintext);
void generateKey(const char *cipherSorted, const char *keySorted, char *key);

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    char sortedCipherFreq[ALPHABET_SIZE];
    char key[ALPHABET_SIZE];
    char plaintext[MAX_TEXT_LENGTH];
    int cipherFreq[ALPHABET_SIZE] = {0};
    int numResults;

    // Input ciphertext
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    // Input number of results
    printf("Enter the number of top possible plaintexts you want: ");
    scanf("%d", &numResults);

    // Count frequencies of each letter in the ciphertext
    countFrequencies(ciphertext, cipherFreq);

    // Sort the ciphertext frequencies in descending order
    sortFrequencies(cipherFreq, sortedCipherFreq);

    // Generate possible keys and decrypt
    for (int i = 0; i < numResults; i++) {
        generateKey(sortedCipherFreq, ENGLISH_FREQ + i, key);
        decrypt(ciphertext, key, plaintext);
        printf("Possible plaintext %d: %s\n", i + 1, plaintext);
    }

    return 0;
}

// Function to count frequencies of letters in a text
void countFrequencies(const char *text, int *freq) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            freq[text[i] - 'A']++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            freq[text[i] - 'a']++;
        }
    }
}

// Function to sort letters by frequency
void sortFrequencies(int *freq, char *sortedFreq) {
    int sortedIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i;
    }

    // Sort indices based on frequencies
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[sortedIndices[i]] < freq[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedFreq[i] = 'A' + sortedIndices[i];
    }
    sortedFreq[ALPHABET_SIZE] = '\0'; // Null-terminate the string
}

// Function to generate a key based on sorted frequencies
void generateKey(const char *cipherSorted, const char *keySorted, char *key) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[cipherSorted[i] - 'A'] = keySorted[i];
    }
    key[ALPHABET_SIZE] = '\0'; // Null-terminate the key string
}

// Function to decrypt the text using a given key
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = key[ciphertext[i] - 'A'];
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = key[ciphertext[i] - 'a'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
