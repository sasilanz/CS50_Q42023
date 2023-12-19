// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// counting the words in the  dictionary
unsigned int dict_wordcount = 0;

unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hash_value = hash(word);
    node *tmp = table[hash_value];
    while (tmp != 0)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
// academic honesty: I took the % N idea from devin finley (www.youtube.com/@RealisticResponse)
// the other code i did myself
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // define var to store the added chars of the word
    unsigned long sum = 0;
    // iterate through the word and add the values of each char
    for (int i = 0; i < strlen(word); i++)
    {
        sum += toupper(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODOS - as per instructions from the video
    // Section 1: Open dictionary file
    FILE *dictfile = fopen(dictionary, "r");
    if (dictfile == NULL)
    {
        fclose(dictfile);
        return false;
    }
    // Section 2 read strings from the dictfile
    // buffer variable to store the word in a node
    char buffer[LENGTH + 1];

    // read each word from buffer until EOF
    while (fscanf(dictfile, "%s", buffer) != EOF)
    {
        // for each word, create a new node in the hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dictfile);
            return false;
        }
        // copy word into the node using strcpy
        strcpy(n->word, buffer);
        // set the pointer of the address to the next node to NULL
        n->next = NULL;
        // hash word
        int index = hash(buffer);

        // insert node to hash table
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        // increment the words in dictionary
        dict_wordcount++;
    }
    // close dictionary file
    fclose(dictfile);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // take from function load
    if (dict_wordcount > 0)
    {
        return dict_wordcount;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // creating a temporary node pointing to the first node
    // move pointer and then free the temp node
    // node *temp_pointer;

    for (int i = 0; i < N; i++)
    {
        node *temp_pointer = table[i];
        while (table[i] != NULL)
        {
            temp_pointer = table[i]->next;
            free(table[i]);
            table[i] = temp_pointer;
        }
    }
    free(*table);
    return true;
}

// Implements a dictionary's functionality
