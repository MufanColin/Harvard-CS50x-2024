#include <cs50.h>
#include <stdio.h>

int main(void) {
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
    return 0;
}

// clang -o name name.c -lcs50
