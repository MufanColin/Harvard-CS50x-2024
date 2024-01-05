#include <cs50.h>
#include <stdio.h>

bool mystrcmp(char *s, char *t);

int main(void) {
    char *s = get_string("String: ");
    char *t = get_string("String: ");
    if (mystrcmp(s, t)) {
        printf("Same.\n");
    } else {
        printf("Different.\n");
    }
}

bool mystrcmp(char *s, char *t) {
    while (*s != '\0' && *t != '\0') {
        if (*s != *t) {
            return false;
        }
        s++;
        t++;
    }
    if (*s != '\0') { // one string is longer than the other
        return false;
    } else if (*t != '\0') { // one string is longer than the other
        return false;
    }
    return true;
}
