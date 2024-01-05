#include "helpers.h"
#include <cs50.h>
#include <math.h> // for round function

int my_min(int a, int b);
bool inBounds(int x, int y, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

int my_min(int a, int b)
{
    return (a < b) ? a : b;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Some inconsistency of variable type here, but this works!
            BYTE sepiaRed =
                my_min(255, (int) (round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue)));
            BYTE sepiaGreen =
                my_min(255, (int) (round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue)));
            BYTE sepiaBlue =
                my_min(255, (int) (round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue)));
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int numPixels = 9;
    // Create a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int candidates[][2] = {
                {i - 1, j - 1}, {i - 1, j},     {i - 1, j + 1}, {i, j - 1},    {i, j},
                {i, j + 1},     {i + 1, j - 1}, {i + 1, j},     {i + 1, j + 1}}; // we must specify the second dimension of the 2d
                                                                                 // array in C
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            for (int k = 0; k < numPixels; k++)
            {
                if (inBounds(candidates[k][0], candidates[k][1], height, width))
                {
                    count++;
                    totalRed += copy[candidates[k][0]][candidates[k][1]].rgbtRed;
                    totalBlue += copy[candidates[k][0]][candidates[k][1]].rgbtBlue;
                    totalGreen += copy[candidates[k][0]][candidates[k][1]].rgbtGreen;
                }
            }
            image[i][j].rgbtRed = (int) (round(1.0 * totalRed / count));
            image[i][j].rgbtBlue = (int) (round(1.0 * totalBlue / count));
            image[i][j].rgbtGreen = (int) (round(1.0 * totalGreen / count));
        }
    }
    return;
}

bool inBounds(int x, int y, int height, int width)
{
    if (0 <= x && x < height && 0 <= y && y < width)
    {
        return true;
    }
    return false;
}
