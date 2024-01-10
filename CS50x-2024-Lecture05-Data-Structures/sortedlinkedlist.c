#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[]) {
    node *head = NULL;
    node *tail = NULL;

    // We want to build a linked list in ascending order

    for (int i = 1; i < argc; i++) {
        int number = atoi(argv[i]);
        node *n = malloc(sizeof(struct node));
        n->number = number;
        n->next = NULL;

        if (head == NULL) {
            head = n;
            tail = head;
        } else if (head != NULL && number <= head->number) {
            // do a head insertion
            n->next = head;
            head = n;
        } else if (tail != NULL && number >= tail->number) {
            // do a tail insertion
            tail->next = n;
            tail = tail->next;
        } else {
            // the number should be inserted somewhere in the middle
            node *tmp = head;
            while (tmp != NULL && tmp->next != NULL) {
                if (tmp->number <= number && number <= tmp->next->number) {
                    // insert the new node between tmp and tmp->next
                    n->next = tmp->next;
                    tmp->next = n;
                    break;
                } else {
                    tmp = tmp->next;
                }
            }
        }
    }

    node *tmp = head;
    while (tmp != NULL) {
        printf("%i\n", tmp->number);
        tmp = tmp->next;
    }

    return 0;
}
