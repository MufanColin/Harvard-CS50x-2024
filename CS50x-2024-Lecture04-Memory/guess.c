#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *x; // x stores the address of an integer
    int *y; // y stores the address of an integer

    x = malloc(sizeof(int)); // allocate memory for an int
    *x = 42; // go to the memory and put 42 in that address

    // *y = 13;
    y = x;
    *y = 13;
    printf("%i\n", *x);
    printf("%i\n", *y);
}
