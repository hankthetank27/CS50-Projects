#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user name
    string name = get_string("What's your name? \n");
    
    // Print reply
    printf("Hello, %s\n", name);
}