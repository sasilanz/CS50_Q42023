#include <cs50.h>
#include <stdio.h>

int main(void)

{
    // TODO: Prompt for start size
    int s;
    do
    {
        s = get_int("Actual Population size (must be at least 9): ");
    }
    while (s < 9);

    // TODO: Prompt for end size
    int e;
    do
    {
        e = get_int("Desired end size of population (must be greater than the start size): ");
    }
    while (e < s);

    // TODO: Calculate number of years until we reach threshold
    int y; // variable counting the years
    do
    {
        for (y = 0; s < e; y++)
        {
            s = s + (s / 3) - (s / 4);
        }
    }
    while (s < e);

    // TODO: Print number of years
    printf("Years: %i\n", y);
}
