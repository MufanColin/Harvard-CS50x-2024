#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int *x = malloc(3 * sizeof(int));
    x[0] = 0;
    x[1] = 1;
    x[2] = 2;
    // x[3] = 3;
    printf("%i\n", x[0]);
    printf("%i\n", x[1]);
    printf("%i\n", x[2]);
    // printf("%i\n", x[3]);
    free(x);
    return 0;
}
