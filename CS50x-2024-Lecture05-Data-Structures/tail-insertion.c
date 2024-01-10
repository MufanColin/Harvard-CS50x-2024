#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[]) {
    node *head = NULL;
    node *tail = NULL;

    for (int i = 1; i < argc; i++) {
        int number = atoi(argv[i]);
        node *n = malloc(sizeof(node));
        n->number = number;
        n->next = NULL;
        if (head == NULL) {
            head = n;
            tail = head;
        } else {
            tail->next = n;
            tail = tail->next;
        }
    }

    node *tmp = head;
    while (tmp != NULL) {
        printf("%i\n", tmp->number);
        tmp = tmp->next;
    }

    return 0;
}

// 1 --> 2 --> 3
