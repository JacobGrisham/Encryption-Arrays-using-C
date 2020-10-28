// Includes
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

// Delcare functions
bool text(char *s);
void cipher(char *plaintext, char *ciphertext, int k);
char *get_string(const char *prompt);

// argv[1] is the secret key (i.e., a non-negative integer)
int main(int argc, char *argv[])
{
    // No user input or multiple inputs error handling
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Text input error handling
    else if (text(argv[1]) == true)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Finally run program
    else
    {
        // Capture secret key
        int k = atoi(argv[1]);

        // Prompt user for text input
        char *plaintext = get_string("plaintext: ");

        // Get number of characters
        int n = strlen(plaintext);

        // Make sure to capture terminating null character
        char ciphertext[n + 1];

        // Call cipher function
        cipher(plaintext, ciphertext, k);

        // Print ciphertext
        printf("ciphertext: %s", ciphertext);

        // Print a newline
        printf("\n");

        // Program exit
        return 0;
    }
}

// Function to determine if user inputted text
bool text(char *s)
{
    // Use a loop to iterate over argv
    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        // If any of the inputted text is non-numerical, return false
        if (isdigit(c))
        {
            return false;
        }
    }
    return true;
}


// Main function: encrpyting the plaintext
void cipher(char *plaintext, char *ciphertext, int k)
{
    // Declare i
    int i = 0;
    // Iterate over each character of the plaintext using for loop:
    for (i = 0; i < strlen(plaintext); i++)
    {
        char ch = plaintext[i];
        // Change characters using formula. Change all to lowercase and then convert back to uppercase
        if (isalpha(ch))
        {
            char lower = tolower(ch);
            int pi = lower - 'a';
            // ci returns number, therefore must anchor the number to letter
            char ci = ((pi + k) % 26) + 'a';
            // Change character using ci value. If lowercase, keep it as is
            if (islower(ch))
            {
                ciphertext[i] = ci;
            }
            // Change character using ci value. If uppercase, change to uppercase
            else
            {
                ciphertext[i] = toupper(ci);
            }
        }
        // Non-alphabetical characters should be outputted unchanged
        else
        {
            ciphertext[i] = ch;
        }
    }
    // Lastly, add terminating null character
    ciphertext[i] = '\0';
}

// get_string function. Source: https://stackoverflow.com/questions/48282630/troubles-creating-a-get-string-function-in-c
char *get_string(const char *prompt)
{
    char temp[26] = "";//24 + newline + '\0'
    int size,count;
    while ( 1)
    {
        printf ( "%s",prompt);
        if ( fgets ( temp, sizeof temp, stdin)) {
            if ( !strchr ( temp, '\n')) {//no newline
                printf("\x1B[31mError\x1B[0m: too long.\n%s",prompt);
                size = strlen ( temp);
                do {
                    fgets ( temp, sizeof temp, stdin);//read more and discard
                    size += strlen ( temp);
                } while (!strchr ( temp, '\n'));//loop until newline found
                printf("size :%i\n",size);
                continue;//re prompt
            }
            break;
        }
        else {
            fprintf ( stderr, "fgets problem\n");
            return NULL;
        }
    }

    temp[strcspn ( temp,"\n")] = '\0';//remove newline
    char *word = malloc(strlen ( temp) + 1);
    strcpy ( word, temp);
    return word;
}