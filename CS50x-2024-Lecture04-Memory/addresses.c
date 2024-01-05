#include <stdio.h>

int main(void) {
    int n = 50;
    printf("%i\n", n);
    printf("%p\n", &n); // we use %p to print out addresses in C
    int *p = &n; // declare a pointer, 8 bytes
    printf("----------------\n");
    printf("%p\n", p);
    printf("----------------\n");
    printf("%i\n", *p); // go to a particular location in the computer
    printf("----------------\n");
    printf("%p\n", &p);
    return 0;
}
