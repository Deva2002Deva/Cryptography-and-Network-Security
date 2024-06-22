#include <stdio.h>
#include <stdlib.h>

#define MOD 26  // Modulus for the Hill cipher (26 letters in the alphabet)

void encrypt(int plaintext[], int ciphertext[], int key[2][2]) {
    for (int i = 0; i < 2; i++) {
        ciphertext[i] = 0;
        for (int j = 0; j < 2; j++) {
            ciphertext[i] += key[i][j] * plaintext[j];
        }
        ciphertext[i] %= MOD;
    }
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void inverseKeyMatrix(int key[2][2], int inverseKey[2][2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    if (det < 0) det += MOD;

    int detInv = modInverse(det, MOD);
    if (detInv == -1) {
        printf("No inverse exists for this matrix.\n");
        exit(1);
    }

    inverseKey[0][0] = (key[1][1] * detInv) % MOD;
    inverseKey[1][1] = (key[0][0] * detInv) % MOD;
    inverseKey[0][1] = (-key[0][1] * detInv) % MOD;
    inverseKey[1][0] = (-key[1][0] * detInv) % MOD;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inverseKey[i][j] < 0) inverseKey[i][j] += MOD;
        }
    }
}

void decrypt(int ciphertext[], int plaintext[], int key[2][2]) {
    int inverseKey[2][2];
    inverseKeyMatrix(key, inverseKey);

    for (int i = 0; i < 2; i++) {
        plaintext[i] = 0;
        for (int j = 0; j < 2; j++) {
            plaintext[i] += inverseKey[i][j] * ciphertext[j];
        }
        plaintext[i] %= MOD;
    }
}

void printVector(int vec[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c ", vec[i] + 'A');
    }
    printf("\n");
}

int main() {
    int key[2][2] = { {3, 3}, {2, 5} };  // Example key matrix
    int plaintext[2] = { 7, 4 };  // Plaintext "HE" -> H=7, E=4
    int ciphertext[2];

    printf("Plaintext: ");
    printVector(plaintext, 2);

    encrypt(plaintext, ciphertext, key);
    printf("Ciphertext: ");
    printVector(ciphertext, 2);

    int decryptedText[2];
    decrypt(ciphertext, decryptedText, key);
    printf("Decrypted text: ");
    printVector(decryptedText, 2);

    return 0;
}
