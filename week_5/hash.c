#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int TABLESIZE = 2000;

unsigned int hash(const char *word);

int main()
{
    char word [30];
    word[0] = 0;
    
    do
    {
        printf("Enter word: ");
        scanf("%[^\n]", word);
    }
    while (word[0] == 0);
    
    int n = hash(word);
    printf("n = %i\n", n);
}

unsigned int hash(const char *word)
{
    int sum = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        if (isupper(word[i]) > 0)
        {
            sum += (word[i] + 32);
            printf("%i\n", (word[i] + 32));
        }
        else
        {
            sum += word[i];
            printf("%i\n", word[i]);
        }    
    }
    int bucket = sum % TABLESIZE;
    return bucket;
}
