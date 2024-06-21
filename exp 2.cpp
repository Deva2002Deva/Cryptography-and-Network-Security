#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform monoalphabetic substitution
void monoalphabeticCipher(char *plaintext, char *ciphertext, char *keyMap) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                ciphertext[i] = toupper(keyMap[plaintext[i] - 'A']);
            } else {
                ciphertext[i] = keyMap[plaintext[i] - 'a'];
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    // Define the plaintext and ciphertext
    char plaintext[1000], ciphertext[1000];
    
    // Define the substitution key
    // For example, here is a key that maps each letter to another letter
    char keyMap[26] = {
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 
        'X', 'C', 'V', 'B', 'N', 'M'
    };
    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    // Remove newline character from the input if present
    size_t len = strlen(plaintext);
    if (len > 0 && plaintext[len-1] == '\n') {
        plaintext[len-1] = '\0';
    }
    
    // Perform monoalphabetic substitution
    monoalphabeticCipher(plaintext, ciphertext, keyMap);
    
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}
