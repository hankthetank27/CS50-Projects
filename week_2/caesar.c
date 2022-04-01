#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


//run program and collect key value
int main(int argc, string argv[])
{
    
    //check if key is valid (one numeric string)
    string g = argv[1];
    
    if (argc > 2 || argc <= 1)
    {
        printf("usage: ./caeser key \n");
        return 1;
    }
    else
    {
        for (int z = 0, r = strlen(g); z < r; z++)
        {
            if (g[z] < '0' || g[z] > '9')
            {
                printf("usage: ./caeser key \n");
                return 1;
            }
        }
    }

    //collect plaintext to be scrambled from user 
    int key = 0;
    key = atoi(g);
    string startword = get_string("plaintext: ");
    
    //cipher text
    int n = strlen(startword);
    char ciphertext[n - 1];
    if (key < 0)
    {
        printf("usage: ./caeser key \n");
        return 1;
    }
    else
    {
        for (int x = 0; x < n; x++)
        { 
            if (isalpha(startword[x]))
            {
                if (isupper(startword[x]))
                {   
                    ciphertext[x] = ((((startword[x] + key) - 'A') % 26) + 'A');
                }
        
                if (islower(startword[x]))
                {
                    ciphertext[x] = ((((startword[x] + key) - 'a') % 26) + 'a');
                }
            }
            else
            {
                ciphertext [x] = (startword[x]);
            }
        }
    }
    
    //return ciphered text to user    
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}