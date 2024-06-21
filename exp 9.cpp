#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void createPlayfairMatrix(const char *keyword, char matrix[5][5]);
void findPosition(char matrix[5][5], char ch, int *row, int *col);
void decryptPlayfair(const char *ciphertext, char *plaintext, char matrix[5][5]);

int main() {
    char keyword[] = "MONARCHY";
    char matrix[5][5];
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY "
                        "CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE "
                        "BAAHY USEDQ";
    char plaintext[500];

    // Remove spaces from the ciphertext
    char sanitizedCiphertext[500];
    int k = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (!isspace(ciphertext[i])) {
            sanitizedCiphertext[k++] = ciphertext[i];
        }
    }
    sanitizedCiphertext[k] = '\0';

    // Create Playfair matrix
    createPlayfairMatrix(keyword, matrix);

    // Decrypt the ciphertext
    decryptPlayfair(sanitizedCiphertext, plaintext, matrix);

    // Output the decrypted message
    printf("Decrypted message: %s\n", plaintext);

    return 0;
}

// Function to create the Playfair matrix from the keyword
void createPlayfairMatrix(const char *keyword, char matrix[5][5]) {
    int used[26] = {0}; // Keep track of which letters have been used
    int k = 0, i, j;

    // Fill matrix with keyword letters
    for (i = 0; i < strlen(keyword); i++) {
        char ch = toupper(keyword[i]);
        if (ch == 'J') {
            ch = 'I'; // Treat J as I
        }
        if (!used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    // Fill matrix with remaining letters
    for (i = 0; i < 26; i++) {
        if (i + 'A' == 'J') {
            continue; // Skip J, already combined with I
        }
        if (!used[i]) {
            matrix[k / 5][k % 5] = 'A' + i;
            used[i] = 1;
            k++;
        }
    }
}

// Function to find the position of a character in the Playfair matrix
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    int i, j;
    if (ch == 'J') {
        ch = 'I'; // Treat J as I
    }
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

// Function to decrypt the ciphertext using Playfair cipher rules
void decryptPlayfair(const char *ciphertext, char *plaintext, char matrix[5][5]) {
    int i, r1, c1, r2, c2;
    for (i = 0; i < strlen(ciphertext); i += 2) {
        char first = toupper(ciphertext[i]);
        char second = toupper(ciphertext[i + 1]);
        findPosition(matrix, first, &r1, &c1);
        findPosition(matrix, second, &r2, &c2);

        if (r1 == r2) { // Same row
            *plaintext++ = matrix[r1][(c1 + 4) % 5];
            *plaintext++ = matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) { // Same column
            *plaintext++ = matrix[(r1 + 4) % 5][c1];
            *plaintext++ = matrix[(r2 + 4) % 5][c2];
        } else { // Rectangle case
            *plaintext++ = matrix[r1][c2];
            *plaintext++ = matrix[r2][c1];
        }
    }
    *plaintext = '\0';
}
