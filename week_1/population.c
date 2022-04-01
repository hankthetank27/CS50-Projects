#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // User input start population
    int start;
    do
    {
        start = get_int("Start size (min. 9): ");
    }
    while (start < 9);
    
    // User input end population 
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // Years passed update
    int year = 0;
    
    
    // Calculate amout of years till threshold passed
    while (start < end)
    {
        start = start + (start/3) - (start/4);
        year++;
    }
    
    // Print years passed to user
    printf("Years: %i\n", year);
}
