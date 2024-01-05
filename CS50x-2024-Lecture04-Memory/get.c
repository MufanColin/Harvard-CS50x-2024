#include <stdio.h>

int main(void) {
    int n;
    printf("n: ");
    scanf("%i", &n); // pass by reference, so that scanf can change the value of n
    printf("%i\n", n);
    return 0;
}
