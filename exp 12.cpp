#include <stdio.h>
#include <string.h>

// Function to compute the modular inverse of a number modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Function to compute the determinant modulo 26
int modDeterminant(int matrix[2][2], int mod) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % mod;
}

// Function to find the inverse of a 2x2 matrix modulo 26
void modInverseMatrix(int matrix[2][2], int invMatrix[2][2], int mod) {
    int det = modDeterminant(matrix, mod);
    int detInv = modInverse(det, mod);

    invMatrix[0][0] =  matrix[1][1] * detInv % mod;
    invMatrix[0][1] = -matrix[0][1] * detInv % mod;
    invMatrix[1][0] = -matrix[1][0] * detInv % mod;
    invMatrix[1][1] =  matrix[0][0] * detInv % mod;

    // Adjust to positive modulo 26
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            invMatrix[i][j] = (invMatrix[i][j] + mod) % mod;
        }
    }
}

// Function to encrypt using Hill cipher
void hillEncrypt(char *plaintext, char *ciphertext, int key[2][2], int mod) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        int x1 = plaintext[i] - 'a';
        int x2 = plaintext[i + 1] - 'a';
        ciphertext[i] = ((key[0][0] * x1 + key[0][1] * x2) % mod) + 'a';
        ciphertext[i + 1] = ((key[1][0] * x1 + key[1][1] * x2) % mod) + 'a';
    }
    ciphertext[len] = '\0';
}

// Function to decrypt using Hill cipher
void hillDecrypt(char *ciphertext, char *plaintext, int key[2][2], int mod) {
    int len = strlen(ciphertext);
    int invKey[2][2];
    modInverseMatrix(key, invKey, mod);
    for (int i = 0; i < len; i += 2) {
        int y1 = ciphertext[i] - 'a';
        int y2 = ciphertext[i + 1] - 'a';
        plaintext[i] = ((invKey[0][0] * y1 + invKey[0][1] * y2) % mod) + 'a';
        plaintext[i + 1] = ((invKey[1][0] * y1 + invKey[1][1] * y2) % mod) + 'a';
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[100];
    char decryptedtext[100];
    
    // Key matrix for encryption
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    int mod = 26;

    // Ensure plaintext length is even by appending 'x' if necessary
    int len = strlen(plaintext);
    if (len % 2 != 0) {
        plaintext[len] = 'x';
        plaintext[len + 1] = '\0';
    }

    // Encrypt the plaintext
    hillEncrypt(plaintext, ciphertext, key, mod);
    printf("Encrypted text: %s\n", ciphertext);

    // Decrypt the ciphertext
    hillDecrypt(ciphertext, decryptedtext, key, mod);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
