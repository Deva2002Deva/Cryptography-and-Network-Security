#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
int modInverse(int a, int m);
void affineDecrypt(char *ciphertext, char *plaintext, int a, int b);

int main() {
    char ciphertext[1000], plaintext[1000];
    int a = 3, b = 15;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    affineDecrypt(ciphertext, plaintext, a, b);

    printf("Decrypted text: %s\n", plaintext);
    return 0;
}

// Function to find the modular inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // If no modular inverse exists
}

// Function to decrypt ciphertext using the affine cipher
void affineDecrypt(char *ciphertext, char *plaintext, int a, int b) {
    int i;
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("No modular inverse exists for a = %d under modulo 26.\n", a);
        return;
    }
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (a_inv * ((ciphertext[i] - offset - b + 26) % 26)) % 26 + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}
