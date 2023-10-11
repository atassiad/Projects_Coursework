// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <cs50.h>

#include "dictionary.h"

//words variable
int words = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //establish current pointer
    node *current = table[hash(word)];
    //check if it's in first hash
    if (strcasecmp(word, current->word) == 0)
    {
        return true;
    }
    else if (strcasecmp(word, current->word) != 0)
    {
        do
        {
            if (current->next == NULL)
            {
                return false;
            }
            current = current->next;
        }
        while(strcasecmp(word, current->word) != 0);
        return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open Dictionary
    FILE *dictionary1 = fopen(dictionary, "r");
    if (dictionary1 == NULL)
    {
        printf("Error\n");
        return 1;
    }

    //scan info into hashtable
    char temp[LENGTH + 1];
    while (fscanf(dictionary1, "%s", temp) != EOF)
    {
        words++;
        //malloc new node and place current word in node
        node *new = malloc(sizeof(node));
        //initalize next
        new->next = NULL;
        if (new == NULL)
        {
            printf("Error\n");
            return 1;
        }
        strcpy(new->word, temp);

        if (table[toupper(temp[0]-'a')] == NULL)
        {
            table[toupper(temp[0]-'a')] = new;
        }
        else if (table[toupper(temp[0]-'a')] != NULL)
        {
            node *current = table[toupper(temp[0]-'a')];
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new;
        }
    }

    // Close Dictionary
    fclose(dictionary1);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //iterate over each hash in table
    for (int i = 0; i <= N; i++)
    {
        if (table[i] != NULL)
        {
            node *current = table[i];
            if (current->next == NULL)
            {
                free(current);
            }
            else if (current->next != NULL)
            {
                do
                {
                    node *temp = current->next;
                    free(current);
                    current = temp;
                }
                while (current->next != NULL);
                free(current);
            }
        }
    }
    return true;
}
