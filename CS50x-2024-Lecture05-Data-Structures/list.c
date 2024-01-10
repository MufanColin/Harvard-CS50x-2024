#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *list = malloc(3 * sizeof(int));

    if (list == NULL) {
        return 1;
    }

    list[0] = 1000; // *list = 1000;
    list[1] = 2000; // *(list+1) = 2000;
    list[2] = 3000; // *(list+2) = 3000;

    for (int i = 0; i < 3; i++) {
        printf("%i\n", list[i]);
    }

    printf("----------------------------\n");


    int *copy = malloc(4 * sizeof(int));

    if (copy == NULL) {
        free(list);
        return 1;
    }

    copy[0] = list[0];
    copy[1] = list[1];
    copy[2] = list[2];

    free(list);
    list = copy;

    list[3] = 4000;

    for (int i = 0; i < 4; i++) {
        printf("%i\n", list[i]);
    }

    free(copy);
    return 0;
}
