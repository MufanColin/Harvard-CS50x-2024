#include <cs50.h>
#include <stdio.h>

void swap(int *a, int *b);

int main(void) {
    int a = get_int("Integer a is: ");
    int b = get_int("Integer b is: ");

    printf("a before is: %i\n", a);
    printf("b before is: %i\n", b);
    printf("------------------\n");
    swap(&a, &b);
    printf("a after is: %i\n", a);
    printf("b after is: %i\n", b);
    return 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
