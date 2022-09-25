#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    // GET, VERIFY AND PROCESS ENCRYPTION KEY
    // Get key
    string key = argv[1];
    string cipher = 0;

    // Check if only 1 key has been input. Else reject. Check if key is 26 char. Else reject
    if (argc != 2 || strlen(key) != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check key for invalid characters
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("Key must only contain alphabetical characters\n");
            return 1;
        }
    }

    // Convert all characters to uppercase
    for (int i = 0; i < 26; i++)
    {
        key[i] = toupper(key[i]);
    }

    // Check for multible dublicate characters
    for (int i = 0, j = 0; j < 26; i++)
    {
        if (key[i] == key[j] && i != j)
        {
            printf("Key must not contain duplicate characters\n");
            return 1;
        }

        if (i == 25)
        {
            i = 0;
            j++;
        }
    }

    // Get and process plaintext
    string plain = get_string("plaintext: ");

    // Count characters
    int length = strlen(plain);

    // Create ciphertext:
    cipher = plain;

    for (int i = 0; i < length; i++)
    {
        // Check if each letter is upper or lower case
        // If lower, replace with ascii value -97
        if (islower(plain[i]))
        {
            cipher[i] = tolower(key[(plain[i] - 97)]);
        }
        // If upper, replace with ascii value -65
        else if (isupper(plain[i]))
        {
            cipher[i] = key[(plain[i] - 65)];
        }
        // Else, move to next character
    }

    printf("ciphertext: %s\n", cipher);

}
