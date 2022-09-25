#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int c_letters(string text);
int c_words(string text);
int c_sentn(string text);


int main(void)
{

    // Get text to test
    string text = get_string("Text: ");

    // Count string length
    int length = strlen(text);

    // Count letters
    float letters = c_letters(text);
    // printf("Letters: %f\n", letters);

    // Count words
    float words = c_words(text);
    // printf("Words: %f\n", words);

    // Count sentences
    float sentn = c_sentn(text);
    // printf("Sentences: %f\n", sentn);

    // Calculate index = 0.0588 * L - 0.296 * S - 15.8
    // Where L is the average number of letters per 100 words in the text,
    // and S is the average number of sentences per 100 words in the text.
    float L = (letters / words) * 100;
    float S = (sentn / words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;


    // Your program should print as output "Grade X" where X is the grade level computed by
    // the Coleman-Liau formula, rounded to the nearest integer. If the resulting index
    // number is 16 or higher (equivalent to or greater than a senior undergraduate reading
    // level), your program should output "Grade 16+" instead of giving the exact index
    // number. If the index number is less than 1, your program should output "Before Grade 1".
    if (round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round(index) > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %0.0f\n", round(index));
    }
}

// CUSTOM FUNCTIONS

// Count letters
int c_letters(string text)
{
    int n = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            n = n + 1;
        }
    }

    return n;
}

// Count words
int c_words(string text)
{
    int n = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            n++;
            i++;
        }

        while (islower(text[i]) || isupper(text[i]) || text[i] == 39 || text[i] == 45)
        {
            i++;
        }
    }

    return n;
}

// Count sentences
int c_sentn(string text)
{
    int n = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            n++;

            while (text[i] != '.' && text[i] != '?' && text[i] != '!')
            {
                i++;
            }
        }
    }

    return n;
}
