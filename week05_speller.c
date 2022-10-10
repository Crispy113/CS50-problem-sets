/* NOTE: This is only part of a larger program for spellchecking 
* .txt-files. See https://cs50.harvard.edu/x/2022/psets/5/speller/ for
* the full program.
*/

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Global variables
int dict_words = 0;

// Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Define ptr and set initial table value
    node *ptr = table[hash(word)];

    while (ptr != NULL)
    {
        if (!strcasecmp(word, ptr->word))
        {
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    long hash_nb = 0;
    int i = 0;

    while (word[i] != 0)
    {
        hash_nb = hash_nb + toupper(word[i]);
        i++;
    }
    return hash_nb % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Load file
    FILE *dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        return false;
    }

    char temp[LENGTH + 1];

    while (fscanf(dict_ptr, "%s", temp) != EOF)
    {
        // Create new node at copy word into it
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, temp);

        // Get hashnumber
        int hash_nb = hash(new_node->word);

        // Add node to hash table
        new_node->next = table[hash_nb];
        table[hash_nb] = new_node;

        // Count word
        dict_words++;
    }

    fclose(dict_ptr);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i];
            table[i] = table[i]->next;
            free(tmp);
        }
        if (table[i] == NULL && i == N - 1)
        {
            return true;
        }
    }

    return false;
}
