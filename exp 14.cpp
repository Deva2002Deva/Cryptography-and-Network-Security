#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to encrypt plaintext with a given key stream
void encrypt(const char *plaintext, const int *keyStream, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int letterShift = keyStream[i % ALPHABET_SIZE];
            ciphertext[i] = ((plaintext[i] - 'a' + letterShift) % ALPHABET_SIZE) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt ciphertext with a given key stream
void decrypt(const char *ciphertext, const int *keyStream, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int letterShift = keyStream[i % ALPHABET_SIZE];
            plaintext[i] = ((ciphertext[i] - 'a' - letterShift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

// Function to find the key stream that decrypts a ciphertext to a given plaintext
void findKey(const char *ciphertext, const char *plaintext, int *keyStream) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i]) && isalpha(plaintext[i])) {
            keyStream[i % ALPHABET_SIZE] = ((ciphertext[i] - plaintext[i] + ALPHABET_SIZE) % ALPHABET_SIZE);
        }
    }
}

void printKeyStream(const int *keyStream, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", keyStream[i]);
    }
    printf("\n");
}

int main() {
    const char *plaintext = "send more money";
    const int keyStream[13] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};  // Provided key stream
    char ciphertext[100];
    char decryptedText[100];
    int newKeyStream[13];

    // Encrypt the plaintext
    encrypt(plaintext, keyStream, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext to find the new key stream for "cash not needed"
    const char *newPlaintext = "cash not needed";
    findKey(ciphertext, newPlaintext, newKeyStream);
    
    printf("Key stream to decrypt ciphertext to 'cash not needed': ");
    printKeyStream(newKeyStream, 13);

    // Decrypt using the new key stream
    decrypt(ciphertext, newKeyStream, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
