#include <cs50.h>
#include <stdio.h>

void printColumns(int height);

int main(void) {
    int h = get_int("Height: ");
    printColumns(h);
    return 0;
}

void printColumns(int height) {
    for (int i = 0; i < height; i++) {
        printf("#\n");
    }
}
