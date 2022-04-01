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
    while (cents >= 25)
    {
        cents = cents - 25;
        coins++;
    }
    
    // Dimes
    while (cents >= 10)
    {
        cents = cents - 10;
        coins++;
    }

    // Nickles
    while (cents >= 5)
    {
        cents = cents - 5;
        coins++;
    }
   
    // Pennies
    while (cents >= 1)
    {
        cents = cents - 1;
        coins++;
    }
    
    // Print coin total
    printf("%i\n", coins);
    
}

