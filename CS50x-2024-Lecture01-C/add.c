#include <cs50.h>
#include <stdio.h>

int add(const int a, const int b);

int main(void) {
    int x = get_int("What's x? ");
    int y = get_int("What's y? ");
    printf("%d + %d = %d\n", x, y, add(x, y));
    return 0;
}

int add(const int a, const int b) {
    return a + b;
}
