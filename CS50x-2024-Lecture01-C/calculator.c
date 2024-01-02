#include <cs50.h>
#include <stdio.h>

int main(void) {
    int x = 1;
    int y = 3;
    printf("%.20f\n", x * 1.0 / y);
    printf("%.20f\n", (float)x / (float)y);
    printf("%.20f\n", (double)x / (double)y);
    return 0;
}
