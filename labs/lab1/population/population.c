#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // TODO: Prompt for start size
    int start_n;

    do
    {
        start_n = get_int("Start size: ");
    }
    while (start_n < 9);

    // TODO: Prompt for end size
    int end_n;

    do
    {
        end_n = get_int("End size:");
    }
    while (end_n < start_n);

    // TODO: Calculate number of years until we reach threshold

    int n = 0;
    int new_n = start_n;

    while (new_n < end_n)
    {
        new_n = new_n + (new_n / 3) - (new_n / 4);
        n++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", n);
    
    
    
}