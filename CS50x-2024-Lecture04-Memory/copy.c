#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void) {
    char *s = get_string("String: ");
    char *t = s;
    printf("%s\n", s);
    printf("%s\n", t);
    if (s == t) {
        printf("Same addresses.\n");
    } else {
        printf("Different addresses.\n");
    }
    if (t[0] != '\0' && isalpha(t[0])) {
        t[0] = toupper(t[0]);
    }
    printf("%s\n", s);
    printf("%s\n", t);
    return 0;
}
