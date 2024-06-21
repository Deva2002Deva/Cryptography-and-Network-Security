#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
int gcd(int a, int b);
int modInverse(int a, int m);
void affineEncrypt(char *plaintext, char *ciphertext, int a, int b);
void affineDecrypt(char *ciphertext, char *plaintext, int a, int b);

int main() {
    char plaintext[1000], ciphertext[1000];
    int a, b;

    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    getchar(); // To consume the newline character after entering b

    if (gcd(a, 26) != 1) {
        printf("Invalid value of a. It must be coprime with 26.\n");
        return 1;
    }

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    affineEncrypt(plaintext, ciphertext, a, b);
    printf("Ciphertext: %s\n", ciphertext);

    affineDecrypt(ciphertext, plaintext, a, b);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

// Function to calculate the greatest common divisor
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
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

// Function to encrypt plaintext using the affine cipher
void affineEncrypt(char *plaintext, char *ciphertext, int a, int b) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((a * (plaintext[i] - offset) + b) % 26) + offset;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
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
