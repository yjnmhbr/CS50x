#include "helpers.h"
for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int colour = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed = colour;
            image[i][j].rgbtGreen = colour;
            image[i][j].rgbtBlue = colour;
        }
    }
    return;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int colour = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed = colour;
            image[i][j].rgbtGreen = colour;
            image[i][j].rgbtBlue = colour;
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
        for (int j = 0; j < width/2; j++)
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
