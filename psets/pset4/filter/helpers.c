#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int colour = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed     = colour;
            image[i][j].rgbtGreen   = colour;
            image[i][j].rgbtBlue    = colour;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int sepRed      = round(0.393 * (float)image[i][j].rgbtRed  + 0.769 * (float)image[i][j].rgbtGreen  + 0.189 *
                                             (float)image[i][j].rgbtBlue);
            unsigned int sepGreen    = round(0.349 * (float)image[i][j].rgbtRed  + 0.686 * (float)image[i][j].rgbtGreen  + 0.168 *
                                             (float)image[i][j].rgbtBlue);
            unsigned int sepBlue     = round(0.272 * (float)image[i][j].rgbtRed  + 0.534 * (float)image[i][j].rgbtGreen  + 0.131 *
                                             (float)image[i][j].rgbtBlue);

            if (sepRed > 255)
            {
                sepRed = 255;
            }

            if (sepGreen > 255)
            {
                sepGreen = 255;
            }

            if (sepBlue > 255)
            {
                sepBlue = 255;
            }

            image[i][j].rgbtRed     = sepRed;
            image[i][j].rgbtGreen   = sepGreen;
            image[i][j].rgbtBlue    = sepBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE hold[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            hold[i][j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = hold[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE holdimg[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            holdimg[i][j] = image[i][j];
        }
    }

    unsigned int red = 0;
    unsigned int green = 0;
    unsigned int blue = 0;
    float x = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = green = blue = x = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int a = i + k;
                    int b = j + l;
                    if ((b < width) && (a < height) && (b >= 0) && (a >= 0))
                    {
                        red += holdimg[a][b].rgbtRed;
                        green += holdimg[a][b].rgbtGreen;
                        blue += holdimg[a][b].rgbtBlue;
                        x++;
                    }
                }
            }
            image[i][j].rgbtRed = round(red / (double) x);
            image[i][j].rgbtGreen = round(green / (double) x);
            image[i][j].rgbtBlue = round(blue / (double) x);
        }
    }
    return;
}
