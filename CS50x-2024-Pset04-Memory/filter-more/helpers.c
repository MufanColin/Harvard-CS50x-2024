#include "helpers.h"
#include <cs50.h>
#include <math.h> // for round function

int my_min(int a, int b);
bool inBounds(int x, int y, int height, int width);
int conv(int i, int j, int kernel_x[3][3], int kernel_y[3][3], char mode, int height, int width, RGBTRIPLE copy[height][width]);
int conv_x(int i, int j, int kernel_x[3][3], char mode, int height, int width, RGBTRIPLE copy[height][width]);
int conv_y(int i, int j, int kernel_y[3][3], char mode, int height, int width, RGBTRIPLE copy[height][width]);

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

int my_min(int a, int b)
{
    return (a < b) ? a : b;
}

bool inBounds(int x, int y, int height, int width)
{
    if (0 <= x && x < height && 0 <= y && y < width)
    {
        return true;
    }
    return false;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int kernel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

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
            image[i][j].rgbtRed =
                conv(i, j, kernel_x, kernel_y, 'r', height, width, copy); // we need to pass copy into the function, but not image
            image[i][j].rgbtGreen = conv(i, j, kernel_x, kernel_y, 'g', height, width, copy);
            image[i][j].rgbtBlue = conv(i, j, kernel_x, kernel_y, 'b', height, width, copy);
        }
    }
    return;
}

int conv(int i, int j, int kernel_x[3][3], int kernel_y[3][3], char mode, int height, int width, RGBTRIPLE copy[height][width])
{
    return my_min(255, (int) (round(sqrt(pow(conv_x(i, j, kernel_x, mode, height, width, copy), 2) +
                                         pow(conv_y(i, j, kernel_y, mode, height, width, copy), 2)))));
}

int conv_x(int i, int j, int kernel_x[3][3], char mode, int height, int width, RGBTRIPLE copy[height][width])
{
    int corr = 0;
    for (int m = -1; m <= 1; m++)
    {
        for (int n = -1; n <= 1; n++)
        {
            if (inBounds(i + m, j + n, height, width))
            {
                if (mode == 'r')
                {
                    corr += copy[i + m][j + n].rgbtRed *
                            kernel_x[m + 1][n + 1]; // the so called convolution is just correlation under the hood
                }
                else if (mode == 'g')
                {
                    corr += copy[i + m][j + n].rgbtGreen *
                            kernel_x[m + 1][n + 1]; // the so called convolution is just correlation under the hood
                }
                else
                {
                    corr += copy[i + m][j + n].rgbtBlue *
                            kernel_x[m + 1][n + 1]; // the so called convolution is just correlation under the hood
                }
            }
        }
    }
    return corr;
}

// this might not be the best design, but at least it works!

int conv_y(int i, int j, int kernel_y[3][3], char mode, int height, int width, RGBTRIPLE copy[height][width])
{
    int corr = 0;
    for (int m = -1; m <= 1; m++)
    {
        for (int n = -1; n <= 1; n++)
        {
            if (inBounds(i + m, j + n, height, width))
            {
                if (mode == 'r')
                {
                    corr += copy[i + m][j + n].rgbtRed *
                            kernel_y[m + 1][n + 1]; // the so called convolution is just correlation under the hood
                }
                else if (mode == 'g')
                {
                    corr += copy[i + m][j + n].rgbtGreen *
                            kernel_y[m + 1][n + 1]; // the so called convolution is just correlation under the hood
                }
                else
                {
                    corr += copy[i + m][j + n].rgbtBlue *
                            kernel_y[m + 1][n + 1]; // the so called convolution is just correlation under the hood
                }
            }
        }
    }
    return corr;
}
