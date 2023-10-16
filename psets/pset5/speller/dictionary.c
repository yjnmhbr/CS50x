// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

//No. of words
unsigned int wordnum = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *n = table[hash(word)];

    if (n == NULL)
    {
        return false;
    }
    else
    {
        while (n != NULL)
        {
            if (strcasecmp(n -> word, word) == 0)
            {
                return true;
            }
            n = n -> next;
        }
    }
    return false;
}

// Hashes word to a number
//Solution from http://www.cse.yorku.ca/~oz/hash.html (their solution is much more sophisticated than mine)
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fhold = fopen(dictionary, "r");

    char indiv_word[LENGTH + 1];

    if (fhold == NULL)
    {
        return false;
    }
    else
    {
        while (fscanf(fhold, "%s", indiv_word) != EOF)
        {
            node *n = malloc(sizeof(node));

            if (n != NULL)
            {
                strcpy(n->word, indiv_word);
                n->next = table[hash(indiv_word)];
                table[hash(indiv_word)] = n;
                wordnum ++;
            }

        }
        fclose(fhold);
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordnum;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *h = table[i];
        node *c = h;
        node *hold = h;
        while (c != NULL)
        {
            c = c -> next;
            free(hold);
            hold = c;
        }
    }
    return true;
}
