#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // Define rows
    for (int row = 0; row < height; row++)
    {
        
        // Print dots
        for (int dot = height - 1; dot > row; dot--)
        {
            printf(" ");
        }
        
        // Print left bricks
        for (int brick = 0; brick <= row; brick++)
        {
            printf("#");
        }
        
        // Print Spaces
        printf("  ");
        
        //Print right bricks
        for (int brick2 = 0; brick2 <= row; brick2++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}