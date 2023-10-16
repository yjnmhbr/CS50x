#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Input height as a positive integer from 1 to 8
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height >= 9);

    for (int i = 0; i < height; i++)
    {
        for (int j = 1; j < (height - i); j++)
        {
            printf(" ");
        }

        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        printf("  ");
        
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}