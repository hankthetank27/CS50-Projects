#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Prompt user for money
    
    float dollars;
    do
    {
        dollars = get_float("Amount of money: ");
    }
    while (dollars < 0);
    
    
    // Convert to cents
    int cents = round(dollars * 100);
    
    // Define coins
    int coins = 0;
    
    
    // Quarters
    if (cents >= 25)
    {
          cents = cents - 25;
          coins++;
    }
    while (cents >= 25);
   
    // Print coin total
    printf("%i\n", coins);
    
}

