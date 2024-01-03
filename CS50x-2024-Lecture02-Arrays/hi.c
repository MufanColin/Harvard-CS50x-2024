#include <cs50.h>
#include <stdio.h>

int main(void) {
    string words[2];
    words[0] = "HI!";
    words[1] = "BYE!";
    printf("%s\n", words[0]);
    printf("%s\n", words[1]);
    printf("--------------------\n");
    printf("%c%c%c\n", words[0][0], words[0][1], words[0][2]);
    printf("%c%c%c%c\n", words[1][0], words[1][1], words[1][2], words[1][3]);
    printf("--------------------\n");
    printf("%d %d %d %d\n", words[0][0], words[0][1], words[0][2], words[0][3]);
    printf("%d %d %d %d %d\n", words[1][0], words[1][1], words[1][2], words[1][3], words[1][4]);
    return 0;
}
