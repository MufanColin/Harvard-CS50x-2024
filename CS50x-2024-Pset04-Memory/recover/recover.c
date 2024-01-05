#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
const int FILENAME_SIZE = 8; // \0 at the end!!!

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    bool hasOpenFile = false;
    int count = 0;
    char filename[FILENAME_SIZE]; // a string to store the filename

    // It's a smart choice to initialize img with NULL outside of the while loop.
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, sizeof(buffer[0]), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // we found a new jpeg signature
        {
            if (hasOpenFile)
            {
                fclose(img); // close the previous image
                hasOpenFile = false;
                count++; // increment the count for a new filename
            }
            sprintf(filename, "%03i.jpg", count); // format the output and store it in the string
            img = fopen(filename, "w");
            hasOpenFile = true;
            fwrite(buffer, sizeof(buffer[0]), BLOCK_SIZE, img);
        }
        else // no new jpeg signature
        {
            if (hasOpenFile)
            {
                fwrite(buffer, sizeof(buffer[0]), BLOCK_SIZE, img); // continue writing to the current image file
            }
        }
    }
    fclose(img);  // to ensure that there is no memory leak
    fclose(card); // to ensure that there is no memory leak
    return 0;
}
