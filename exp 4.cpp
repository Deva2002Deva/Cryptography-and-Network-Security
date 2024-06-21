#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void vigenereCipher(char *plaintext, char *ciphertext, char *key);

int main() {
    char plaintext[1000], ciphertext[1000], key[100];
    
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    vigenereCipher(plaintext, ciphertext, key);

    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

void vigenereCipher(char *plaintext, char *ciphertext, char *key) {
    int i, j = 0, keyLen = strlen(key);
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            char keyChar = toupper(key[j % keyLen]) - 'A';
            ciphertext[i] = ((plaintext[i] - offset + keyChar) % 26) + offset;
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}
