#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int l = 0; l < width; l++)
        {
            float red = image[i][l].rgbtRed;
            float green = image[i][l].rgbtGreen;
            float blue = image[i][l].rgbtBlue;
            int grey = round((red + green + blue) / 3.0);
            image[i][l].rgbtRed = grey;
            image[i][l].rgbtGreen = grey;
            image[i][l].rgbtBlue = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int l = 0; l < width; l++)
        {
            float red = image[i][l].rgbtRed;
            float green = image[i][l].rgbtGreen;
            float blue = image[i][l].rgbtBlue;
            int sred = round(0.393 * red + 0.769 * green + 0.189 * blue);
            if (sred >= 255)
            {
                sred = 255;
            }
            int sgreen = round(0.349 * red + 0.686 * green + 0.168 * blue);
            if (sgreen >= 255)
            {
                sgreen = 255;
            }
            int sblue = round(0.272 * red + 0.534 * green + 0.131 * blue);
            if (sblue >= 255)
            {
                sblue = 255;
            }
            image[i][l].rgbtRed = sred;
            image[i][l].rgbtGreen = sgreen;
            image[i][l].rgbtBlue = sblue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //buffer
    RGBTRIPLE buffer;
    //height
    for (int i = 0; i < height; i++)
    {
        //width iteration
        for (int l = 0; l < (int)(0.5 * width); l++)
        {
            buffer = image[i][l];
            image[i][l] = image[i][width - 1 - l];
            image[i][width - 1 - l] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy
    RGBTRIPLE copy[height][width];
    for (int h1 = 0; h1 < height; h1++)
    {
        for (int w1 = 0; w1 < width; w1++)
        {
            copy[h1][w1] = image[h1][w1];
        }
    }

    //iterate through the height
    for (int i = 0; i < height; i++)
    {
        //iterate through the width
        for (int l = 0; l < width; l++)
        {
            //iterate through size of surrounding squares
            //establish variables
            double numdigits = 0;
            double redtotal = 0;
            double greentotal = 0;
            double bluetotal = 0;
            for (int h = -1; h <= 1; h++)
            {
                for (int w = -1; w <= 1; w++)
                {
                    //if statement for real numbers
                    if ((0 <= i + h) && (i + h < height) && (0 <= l + w) && (l + w < width))
                    {
                        redtotal = redtotal + copy[i + h][l + w].rgbtRed;
                        greentotal = greentotal + copy[i + h][l + w].rgbtGreen;
                        bluetotal = bluetotal + copy[i + h][l + w].rgbtBlue;
                        numdigits++;
                    }
                }
            }
            image[i][l].rgbtRed = round(redtotal / numdigits);
            image[i][l].rgbtGreen = round(greentotal / numdigits);
            image[i][l].rgbtBlue = round(bluetotal / numdigits);
        }
    }
    return;
}
