#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>

int col(int n);

int main()
{
    int num = get_int("number: ");
    int col_val = col(num);
    printf("%i\n", col_val);
}

int col(int n)
{
    if (n == 1)
        return 0;
    else if ((n % 2) == 0)
        return 1 + col(n/2);
    else
        return 1 + col(3*n + 1);
}