#include <cs50.h>
#include <stdio.h>
#include <string.h>

int length(string s);

int main(void) {
    string s = get_string("Enter a string please: ");
    printf("%d\n", length(s));
    printf("--------------\n");
    printf("%lu\n", strlen(s));
    // it's more efficient to use another variable to store the length of s
    // rather than call the strlen function multiple times.
    for (int i = 0, n = strlen(s); i < n; i++) {
        printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}

int length(string s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}
