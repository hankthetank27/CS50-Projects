// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int TABLESIZE = 5381;

int dict_size = 0;

// Hash table
node *table[TABLESIZE];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char wordlower[LENGTH + 1];
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        if (isupper(word[i]))
        {
            wordlower[i] = tolower(word[i]);
        }
        else
        {
            wordlower[i] = word[i];
        }
    }
    wordlower[length] = '\0';
        
    // TODO
    int hashnum = hash(wordlower);
    node *cursor = table[hashnum];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, wordlower) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}
    
// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        sum += word[i];
    }
    
    int bucket = sum % TABLESIZE;
    return bucket;
}
    
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < TABLESIZE; i++)
    {
        table[i] = NULL;
    }
    
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open file\n");
        return false;
    }
    
    char tmpword[LENGTH + 1];
    while (fscanf(dict, "%s", tmpword) > 0)
    {
        struct node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("could not allocate memory\n");
            return false;
        }
        
        strcpy(n->word, tmpword);
        n->next = NULL;

        int tablenum = hash(n->word);
        if (table[tablenum] == NULL)
        {
            table[tablenum] = n;
        }
        else
        {
            n->next = table[tablenum];
            table[tablenum] = n;
        }
    
        dict_size++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < TABLESIZE; i++)
    {
        node *ptr = table[i];
        while (ptr)
        {
            node *tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return true;
}