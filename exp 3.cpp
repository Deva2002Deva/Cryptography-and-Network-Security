#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function prototypes
void prepareText(char *input, char *output);
void createMatrix(char *key, char matrix[SIZE][SIZE]);
void encryptPlayfair(char *plaintext, char *ciphertext, char matrix[SIZE][SIZE]);
void findPosition(char letter, char matrix[SIZE][SIZE], int *row, int *col);

int main() {
    char key[100], plaintext[100], preparedText[200], ciphertext[200];
    char matrix[SIZE][SIZE];
    
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    prepareText(plaintext, preparedText);
    createMatrix(key, matrix);
    encryptPlayfair(preparedText, ciphertext, matrix);

    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

void prepareText(char *input, char *output) {
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i]);
        }
    }
    output[j] = '\0';
    
    // Insert X between repeated letters
    for (i = 0; i < j; i += 2) {
        if (output[i] == output[i+1]) {
            memmove(output + i + 2, output + i + 1, j - i);
            output[i+1] = 'X';
            j++;
        }
    }
    
    // If length is odd, add an extra X
    if (j % 2 != 0) {
        output[j++] = 'X';
    }
    output[j] = '\0';
}

void createMatrix(char *key, char matrix[SIZE][SIZE]) {
    int i, j, k, keyLen = strlen(key);
    int used[26] = {0}; // To track used letters
    int x = 0, y = 0;

    // Fill matrix with key letters
    for (i = 0; i < keyLen; i++) {
        char letter = toupper(key[i]);
        if (letter == 'J') {
            letter = 'I';
        }
        if (!isalpha(letter) || used[letter - 'A']) {
            continue;
        }
        matrix[x][y++] = letter;
        used[letter - 'A'] = 1;
        if (y == SIZE) {
            y = 0;
            x++;
        }
    }

    // Fill matrix with remaining letters
    for (i = 0; i < 26; i++) {
        char letter = 'A' + i;
        if (letter == 'J') {
            continue; // Skip J
        }
        if (!used[i]) {
            matrix[x][y++] = letter;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
}

void encryptPlayfair(char *plaintext, char *ciphertext, char matrix[SIZE][SIZE]) {
    int i;
    int row1, col1, row2, col2;

    for (i = 0; plaintext[i] != '\0'; i += 2) {
        findPosition(plaintext[i], matrix, &row1, &col1);
        findPosition(plaintext[i+1], matrix, &row2, &col2);

        if (row1 == row2) {
            // Same row
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i+1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            // Same column
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i+1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            // Rectangle
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i+1] = matrix[row2][col1];
        }
    }
    ciphertext[i] = '\0';
}

void findPosition(char letter, char matrix[SIZE][SIZE], int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
