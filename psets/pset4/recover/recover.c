#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        FILE *input = fopen(argv[1], "r");

        if (input == NULL)
        {
            printf("Could not open file.\n");
            return 2;
        }

        FILE *output = NULL;
        
        BYTE buffer[512];
        char file[8];
        int i = 0;

        while ((fread(&buffer, 512, 1, input)) == 1)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[0] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                if (i != 0)
                {
                    fclose(output);
                }
                sprintf(file, "%03i.jpg", i);
                output = fopen(file, "w");
                i++;
            }
            if (i != 0)
            {
                fwrite(&buffer, 512, 1, output);
            }
        }

        fclose(output);
        fclose(input);

        return 0;
    }
}