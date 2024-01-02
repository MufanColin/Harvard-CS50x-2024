#include <cs50.h>
#include <stdio.h>

int main(void) {
    int x = get_int("What's x? ");
    int y = get_int("What's y? ");
    if (x < y) {
        printf("%d is less than %d\n", x, y);
    } else if (x > y) {
        printf("%d is greater than %d\n", x, y);
    } else {
        printf("%d is equal to %d\n", x, y);
    }
    return 0;
}
