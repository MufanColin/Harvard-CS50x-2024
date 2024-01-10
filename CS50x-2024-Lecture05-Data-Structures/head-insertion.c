#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[]) {
    node *head = NULL; // initialization

    for (int i = 1; i < argc; i++) {
        int number = atoi(argv[i]); // ascii to integer, very useful in practice;
        //printf("%s\n", argv[i]);
        node *n = malloc(sizeof(node));

        if (n == NULL) {
            // Free memory so far
            return 1;
        }

        n->number = number;
        n->next = head; // head insertion
        head = n; // head insertion
        // Time complexity for insertion is O(1)
    }
    node *tmp = head;
    while (tmp != NULL) { // Searching takes O(n) time
        printf("%i\n", tmp->number);
        tmp = tmp->next;
    }
    return 0;
}
