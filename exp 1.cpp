#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to encrypt text using Caesar Cipher
void caesarCipher(char *text, int shift) {
    char ch;
    int i = 0;

    while (text[i] != '\0') {
        ch = text[i];

        if (isalpha(ch)) { // Check if the character is an alphabet
            char offset = isupper(ch) ? 'A' : 'a';
            ch = ((ch - offset + shift) % 26) + offset; // Shift character and wrap around if necessary
        }
        
        text[i] = ch;
        i++;
    }
}

int main() {
    char text[100];
    int shift;

    // Get input from user
    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);

    // Check if shift value is within valid range
    if (shift < 1 || shift > 25) {
        printf("Invalid shift value. Please enter a number between 1 and 25.\n");
        return 1;
    }

    // Encrypt the text
    caesarCipher(text, shift);

    // Print the encrypted text
    printf("Encrypted text: %s\n", text);

    return 0;
}


output:
Enter a string to encrypt: hi
Enter shift value (1-25): 5
Encrypted text: mn
