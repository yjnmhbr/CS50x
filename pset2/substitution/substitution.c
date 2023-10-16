#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int i, string s[])
{
    if (i == 2)
    {
        string key = s[1];
        
        int check = 0;
        int dup = 0;
        
        for (int j = 0; j < 26; j++)
        {
            if (!((key[j] <= 90 && key[j] >= 65) || (key[j] <= 122 && key[j] >= 97)))
            {
                check++;
            }
            
            for (int k = j + 1; k < 26; k++) 
            {
                if (key[j] == key[k])
                {
                    dup++;
                }
            }
        }
        
        if (dup == 0)
        {
            if (check == 0)
            {
                if (strlen(key) == 26)
                {
                    string plain = get_string("plaintext: ");
                    string alphaL = "abcdefghijklmnopqrstuvwxyz";
                    string alphaU = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    
                    printf("ciphertext: ");
                    
                    for (int j = 0; j < strlen(plain); j++)
                    {
                        if (plain[j] <= 122 && plain[j] >= 97)
                        {
                            for (int k = 0; k < 26; k++)
                            {
                                if (plain[j] == alphaL[k])
                                {
                                    if (key[k] <= 122 && key[k] >= 97)
                                    {
                                        printf("%c", key[k]);
                                    }
                                    else if (key[k] <= 90 && key[k] >= 65)
                                    {
                                        printf("%c", key[k] + 32);
                                    }
                                    else
                                    {
                                        printf("%c", plain[j]);
                                    }
                                }
                            }
                        }
                        else if (plain[j] <= 90 && plain[j] >= 65)
                        {
                            for (int k = 0; k < 26; k++)
                            {
                                if (plain[j] == alphaU[k])
                                {
                                    if (key[k] <= 122 && key[k] >= 97)
                                    {
                                        printf("%c", key[k] - 32);
                                    }
                                    else if (key[k] <= 90 && key[k] >= 65)
                                    {
                                        printf("%c", key[k]);
                                    }
                                    else
                                    {
                                        printf("%c", plain[j]);
                                    }
                                }
                            }
                        }
                        else
                        {
                            printf("%c", plain[j]);
                        }
                    }
                    printf("\n");
                }
                else
                {
                    printf("Key must contain 26 characters.\n");
                }
            }
            else
            {
                printf("Usage: %s key\n", s[0]);
                exit(1);
            }
        }
        else
        {
            printf("Usage: %s key\n", s[0]);
            exit(1);
        }
    }
    else
    {
        printf("Usage: %s key\n", s[0]);
        exit(1);
    }
}