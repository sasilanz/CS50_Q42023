#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterating through the image rows
    for (int i = 0; i < height; i++)
    {
        // iterating through the columns of each row
        for (int j = 0; j < width; j++)
        {
            // get the RGBTRIPLE values for each pixel, calculate the average and round it
            // set the colours to the average value
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = image[i][j].rgbtBlue;
            int average = round((Red + Green + Blue) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //
    for (int i = 0; i < height; i++)
    {
        // iterating through the columns of each row
        for (int j = 0; j < width; j++)
        {
            // get the RGBTRIPLE values for each pixel
            int Red = image[i][j].rgbtRed;
            int Green = image[i][j].rgbtGreen;
            int Blue = image[i][j].rgbtBlue;
            // calculate the new sepia colour

            int sepiaRed = round((.393 * Red) + (.769 * Green) + (.189 * Blue));
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            int sepiaGreen = round((.349 * Red) + (.686 * Green) + (.168 * Blue));
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            int sepiaBlue = round((.272 * Red) + (.534 * Green) + (.131 * Blue));
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // iterating through half the columns of each row
        for (int j = 0; j < (width / 2); j++)
        {
            // set temp varialbe for the pixels in the first half of the row
            RGBTRIPLE temp = image[i][j];
            // switch current pixels to the new location
            image[i][j] = image[i][width - (j + 1)];
            // set switched pixels to temp
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the original image (as suggested in the instruction)
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // loop through each pixel, declare var to store the sums of each of the colours
    // count number of the surrounding pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize the values
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            int count_pixels = 0;

            // check if the surrounding pixels exist, loop one pixel up/down and left/right
            // if i+k or j+l is outside the range of 0 to the height/width, skip pixel

            // for each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // for each row: check if pixel exists means, if it is outside the row
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // for each column: check if pixel exists - is outside column
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // add existing pixel values to each sum of colour
                    sum_red += copy[i + k][j + l].rgbtRed;
                    sum_green += copy[i + k][j + l].rgbtGreen;
                    sum_blue += copy[i + k][j + l].rgbtBlue;
                    // increase counter for each pixel found - required for the average
                    count_pixels++;
                }
            }
            // get the average and write the new values to the image

            image[i][j].rgbtRed = round(sum_red / count_pixels);
            image[i][j].rgbtGreen = round(sum_green / count_pixels);
            image[i][j].rgbtBlue = round(sum_blue / count_pixels);
        }
    }
    return;
}
