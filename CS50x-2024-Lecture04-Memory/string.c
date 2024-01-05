#include <stdio.h>

int main(void) {
    char *s = "Hello!"; // char * = string
    printf("%s\n", s);
    char *t = "Bear!";
    while (*t != '\0') {
        printf("%c", *t); // fetch the value(which is a char) from a certain address
        t++; // increment the address, pointer arithmetic
    }
    printf("\n");
    return 0;
}
