// Implements a dictionary's functionality
#include <cs50.h>
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
const unsigned int N = 999331;

// Hash table
node *table[N];

int totalWordsInDict = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Case insensitive!!!

    // 1. Hash word to obtain a hash value
    // 2. Access linked list at that index in the hash table
    // 3. Traverse linked list, looking for the word (strcasecmp)
    int index = hash(word);
    node *dest = table[index];
    node *tmp = dest;
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // Larger N means more buckets
    // If your function ends upwith a value greater than N, you can take the value % N to get a value in the appropriate range.

    // Examples of hash functions:
    // First letter
    // First two letters
    // Math using all letters

    // I borrowed the hash function from the following website and made some changes to the original version.
    // https://cp-algorithms.com/string/string-hashing.html

    const int p = 53;
    long long hash_value = 0;
    long long p_pow = 1;
    char *tmp = (char *) word;
    while (*tmp != '\0')
    {
        if (isalpha(*tmp))
        {
            hash_value = (hash_value + (toupper(*tmp) - 'A' + 1) * p_pow) % N;
            p_pow = (p_pow * p) % N;
        }
        tmp++;
    }
    return (unsigned int) hash_value;

    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1];
    int index;
    // Hash table is just an array of **linked lists** !!!

    // Step1: Open dictionary file
    // 1. Use fopen
    // 2. Remember to check if return value is NULL

    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    { // we can't open the file correctly
        return false;
    }

    // Step2: Read strings from file
    // 1. fscanf(file, "%s", word); file is the pointer returned by fopen
    // 2. fscanf will return EOF once it reaches end of file

    // Step3: Create a new node
    // 1. Use malloc
    // 2. Remember to check if return value is NULL
    // 3. Copy word into node using strcpy (which is a function inside ctype.h)

    // Step4: Use the hash function
    // 1. Use the hash function
    // 2. Function takes a string and returns an index

    // Step5: Insert node into hash table
    // 1. Recall that hash table is an array of linked lists
    // 2. Be sure to set pointers in the correct order

    while (fscanf(file, "%s", word) != EOF)
    {
        totalWordsInDict++;
        node *n = malloc(sizeof(struct node));
        if (n == NULL)
        {
            return false;
        }
        else
        {
            strcpy(n->word, word);
            n->next = NULL;
            index = hash(word);
            if (table[index] == NULL)
            {
                table[index] = n;
            }
            else
            {
                // v1: head insertion
                n->next = table[index];
                table[index] = n;
                // v2: tail insertion
            }
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return totalWordsInDict; // totalWordsInDict is a global variable that keeps track of the number of words in the dictionary
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // Freeing the linked list by using two pointers (tmp and cursor)
    // We free the tmp pointer, and use cursor pointer to keep track of the linked list that we are processing

    for (int i = 0; i < N; i++)
    {
        node *head = table[i]; // the head of the particular linked list that we are interested in
        node *tmp = head;
        node *cursor = tmp;
        if (head != NULL)
        {
            while (cursor->next != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            }
            free(tmp);
        }
    }
    return true;
}
