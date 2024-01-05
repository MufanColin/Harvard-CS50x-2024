#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[]) { // remember char * is equivalent to string
    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");

    BYTE b;

    while (fread(&b, sizeof(b), 1, src) != 0) { // b stands as a buffer or a transfer station here
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(dst);
    fclose(src);
    return 0;
}
