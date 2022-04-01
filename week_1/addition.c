#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long x = get_long("pick your first number ");
    
    long y = get_long("and now your second... ");
    
    printf("and your result is.... %li\n", x + y);
}