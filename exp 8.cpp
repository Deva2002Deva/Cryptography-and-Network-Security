#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void createCipherAlphabet(const char *keyword, char *cipherAlphabet);
void encrypt(const char *plaintext, char *ciphertext, const char *cipherAlphabet);
void decrypt(const char *ciphertext, char *plaintext, const char *cipherAlphabet);

int main() {
    char keyword[27], plaintext[1000], ciphertext[1000], decryptedText[1000];
    char cipherAlphabet[27];
    
    // Input the keyword
    printf("Enter the keyword: ");
    scanf("%s", keyword);

    // Generate the cipher alphabet
    createCipherAlphabet(keyword, cipherAlphabet);

    // Display the cipher alphabet
    printf("Cipher alphabet: %s\n", cipherAlphabet);

    // Input the plaintext
    printf("Enter the plaintext: ");
    scanf(" %[^\n]%*c", plaintext); // Use this format to allow spaces in input

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, cipherAlphabet);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedText, cipherAlphabet);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

// Function to create the cipher alphabet from the keyword
void createCipherAlphabet(const char *keyword, char *cipherAlphabet) {
    int alphaUsed[26] = {0};
    int i, j = 0, k;
    char ch;

    // Convert keyword to uppercase and remove duplicates
    for (i = 0; keyword[i] != '\0'; i++) {
        ch = toupper(keyword[i]);
        if (!alphaUsed[ch - 'A']) {
            cipherAlphabet[j++] = ch;
            alphaUsed[ch - 'A'] = 1;
        }
    }

    // Add remaining letters of the alphabet
    for (i = 0; i < 26; i++) {
        if (!alphaUsed[i]) {
            cipherAlphabet[j++] = 'A' + i;
        }
    }
    cipherAlphabet[j] = '\0';
}

// Function to encrypt the plaintext using the cipher alphabet
void encrypt(const char *plaintext, char *ciphertext, const char *cipherAlphabet) {
    int i;
    char ch;

    for (i = 0; plaintext[i] != '\0'; i++) {
        ch = toupper(plaintext[i]);
        if (isalpha(ch)) {
            ciphertext[i] = cipherAlphabet[ch - 'A'];
        } else {
            ciphertext[i] = ch; // Preserve non-alphabet characters
        }
    }
    ciphertext[i] = '\0';
}

// Function to decrypt the ciphertext using the cipher alphabet
void decrypt(const char *ciphertext, char *plaintext, const char *cipherAlphabet) {
    int i, j;
    char ch;

    for (i = 0; ciphertext[i] != '\0'; i++) {
        ch = toupper(ciphertext[i]);
        if (isalpha(ch)) {
            for (j = 0; j < 26; j++) {
                if (cipherAlphabet[j] == ch) {
                    plaintext[i] = 'A' + j;
                    break;
                }
            }
        } else {
            plaintext[i] = ch; // Preserve non-alphabet characters
        }
    }
    plaintext[i] = '\0';
}
