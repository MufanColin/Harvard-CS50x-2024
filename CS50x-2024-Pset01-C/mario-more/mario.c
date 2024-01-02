#include <cs50.h>
#include <stdio.h>

void printSpace(int height, int rowNumber);
void printHash(int rowNumber);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    for (int i = 0; i < height; i++)
    {
        printSpace(height, i);
        printHash(i);
        printf("  ");
        printHash(i);
        printf("\n");
    }
    return 0;
}

void printSpace(int height, int rowNumber)
{
    for (int i = 0; i < height - 1 - rowNumber; i++)
    {
        printf(" ");
    }
}

void printHash(int rowNumber)
{
    for (int i = 0; i < rowNumber + 1; i++)
    {
        printf("#");
    }
}
