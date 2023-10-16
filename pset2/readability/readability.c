#include <cs50.h>
#include <stdio.h>
#include <string.h>//>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    
    int space = 0;
    int end = 0;
    int letters = 0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 32)
        {
            space += 1;
        }
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            end += 1;
        }
        else if ((text[i] <= 90 && text[i] >= 65) || (text[i] <= 122 && text[i] >= 92))
        {
            letters += 1;
        }
    }
    
    int words = space + 1;
    int sentences = end;
    
    float L = letters / (float)words * 100;
    float S = sentences / (float)words * 100;
    
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}