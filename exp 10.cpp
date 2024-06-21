#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void prepareText(char *text);
void encryptPlayfair(const char *plaintext, char *ciphertext, char matrix[5][5]);
void findPosition(char matrix[5][5], char ch, int *row, int *col);

int main() {
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[100];
    char playfairMatrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    // Prepare the plaintext
    prepareText(plaintext);

    // Encrypt the plaintext using Playfair cipher
    encryptPlayfair(plaintext, ciphertext, playfairMatrix);

    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

// Function to prepare the text by removing non-alphabetic characters and handling 'I'/'J'
void prepareText(char *text) {
    int i, j = 0;
    char temp[100];

    // Convert to uppercase and remove non-alphabetic characters
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            temp[j++] = toupper(text[i]);
        }
    }
    temp[j] = '\0';

    // Handle repeated letters and make pairs
    j = 0;
    for (i = 0; temp[i] != '\0'; i++) {
        text[j++] = temp[i];
        if (temp[i] == temp[i + 1]) {
            text[j++] = 'X'; // Insert 'X' between repeated letters
        }
    }
    text[j] = '\0';

    // Make sure text length is even by adding 'X' if necessary
    if (strlen(text) % 2 != 0) {
        text[j++] = 'X';
    }
    text[j] = '\0';
}

// Function to encrypt the plaintext using Playfair cipher rules
void encryptPlayfair(const char *plaintext, char *ciphertext, char matrix[5][5]) {
    int i, r1, c1, r2, c2;
    for (i = 0; i < strlen(plaintext); i += 2) {
        char first = plaintext[i];
        char second = plaintext[i + 1];

        if (first == 'J') first = 'I';
        if (second == 'J') second = 'I';

        findPosition(matrix, first, &r1, &c1);
        findPosition(matrix, second, &r2, &c2);

        if (r1 == r2) { // Same row
            *ciphertext++ = matrix[r1][(c1 + 1) % 5];
            *ciphertext++ = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) { // Same column
            *ciphertext++ = matrix[(r1 + 1) % 5][c1];
            *ciphertext++ = matrix[(r2 + 1) % 5][c2];
        } else { // Rectangle case
            *ciphertext++ = matrix[r1][c2];
            *ciphertext++ = matrix[r2][c1];
        }
    }
    *ciphertext = '\0';
}

// Function to find the position of a character in the Playfair matrix
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
