#include <stdio.h>

int main(void) {
    // char *s; // if we don't do the initialization, then we don't know what addresses s contains
    char s[4];
    scanf("%s", s);
    printf("%s\n", s);
    return 0;
}
