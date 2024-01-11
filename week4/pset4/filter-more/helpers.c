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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the original image (as suggested in the instruction for blur)
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // initialize the Sobel arrays (as per the picture from the instruction)
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // looping through the image rows and columns i and j
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize values for the gx/y array
            int GxRed = 0, GxGreen = 0, GxBlue = 0;
            int GyRed = 0, GyGreen = 0, GyBlue = 0;

            // detect above and below from i (height)
            for (int x = -1; x < 2; x++)
            {
                // detect left and right from j ( width)
                for (int y = -1; y < 2; y++)
                {
                    if (i + x < 0 || i + x > height - 1)
                    {
                        continue;
                    }
                    if (j + y < 0 || j + y > width - 1)
                    {
                        continue;
                    }
                    GxRed += image[i + x][j + y].rgbtRed * Gx[x + 1][y + 1];
                    GyRed += image[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];

                    GxGreen += image[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];
                    GyGreen += image[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];

                    GxBlue += image[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1];
                    GyBlue += image[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                }
            }
            int new_red = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int new_green = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int new_blue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));

            copy[i][j].rgbtRed = (new_red > 255) ? 255 : new_red;
            copy[i][j].rgbtGreen = (new_green > 255) ? 255 : new_green;
            copy[i][j].rgbtBlue = (new_blue > 255) ? 255 : new_blue;
        }
    }
    // write the new date to the image file
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}
