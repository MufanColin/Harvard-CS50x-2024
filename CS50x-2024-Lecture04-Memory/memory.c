#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char *s = get_string("String: "); // get_string manages memory for you, we don't need to do the free part

    if (s == NULL) { // error checking
        return 1;
    }

    char *t = malloc(strlen(s) + 1);

    if (t == NULL) { // error checking
        return 1;
    }

    // for (int i = 0, n = strlen(s); i <= n; i++) { // remember to copy the \0 as well
    //     t[i] = s[i];
    // }

    strcpy(t, s); // equivalent to the code above

    printf("Original string is: %s\n", s);
    printf("New string is: %s\n", t);
    if (s == t) {
        printf("Same addresses.\n");
    } else {
        printf("Different addresses.\n");
    }

    if (t[0] != '\0' && isalpha(t[0])) {
        t[0] = toupper(t[0]);
    }

    printf("Original string is: %s\n", s);
    printf("New string is: %s\n", t);
    free(t);
    return 0;
}
