#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int getSum(int n)
{
    int i = n;
    int sum = 0;
    int rem;

    while (i != 0)
    {
        rem = i % 10;
        sum = sum + rem;
        i = i / 10;
    }

    return sum;
}

int main(void)
{
    string n;
    int len = 0;
    int check;;
    
    do
    {
        check = 0;
        n = get_string("Number: ");
        len = strlen(n);
        for (int i = 0; i < len; i++)
        {
            if (n[i] < 48 || n[i] > 57)
            {
                check += 1;
            }
        }
    }
    while (check != 0);
    
    string comp = n;
    
    int sum = 0;
    int sum1 = 0;
    int hold = 0;
    int d1 = 0;
    int d2 = 0;
    
    if (len % 2 == 0)
    {
        for (int i = 0; i < len; i++)
        {
            hold = (n[i] - 48) * 2;;
            if (i == 0)
            {
                if (hold < 10)
                {
                    sum += (n[i] - 48) * 2;
                }
                else
                {
                    sum += getSum((n[i] - 48) * 2);
                }
            }
            else if (i % 2 == 0)
            {
                if (hold < 10)
                {
                    sum += (n[i] - 48) * 2;
                }
                else
                {
                    sum += getSum((n[i] - 48) * 2);
                }
            }
        }
        
        for (int i = 0; i < len; i++)
        {
            if (i % 2 != 0)
            {
                sum += n[i] - 48;
            }
            
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            hold = (n[i] - 48) * 2;;
            if (i % 2 != 0)
            {
                if (hold < 10)
                {
                    sum += (n[i] - 48) * 2;
                }
                else
                {
                    sum += getSum((n[i] - 48) * 2);
                }
            }
        }
        
        for (int i = 0; i < len; i++)
        {
            if (i % 2 == 0)
            {
                sum += n[i] - 48;
            }
            
        }
    }
    
    if ((n[0] - 48 == 3 && (n[1] - 48 == 4 || n[1] - 48 == 7)) && sum % 10 == 0 && len == 15)
    {
        printf("AMEX\n");
    }
    else if ((n[0] - 48 == 5 && (n[1] - 48 == 1 || n[1] - 48 == 2 || n[1] - 48 == 3 || n[1] - 48 == 4 || n[1] - 48 == 5))
             && (sum % 10 == 0) && (len == 16))
    {
        printf("MASTERCARD\n");
    }
    else if (n[0] - 48 == 4 && sum % 10 == 0 && (len >= 13 && len <= 16))
    {
        printf("VISA\n");
        
    }
    else
    {
        printf("INVALID\n");
    }
}