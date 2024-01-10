#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
} node;

int main(void) {
    // Task 1: Create a linked list that looks like below:
    // (3 is the head of the linked list)3 --> 2 --> 1

    // This is also what we called a tail insertion

    node *head = NULL; // initialization

    node *first = malloc(sizeof(node));
    first->number = 1;
    first->next = NULL;

    head = first;

    node *second = malloc(sizeof(node));
    second->number = 2;
    second->next = first;

    head = second;

    node *third = malloc(sizeof(node));
    third->number = 3;
    third->next = second;

    head = third;

    node *tmp = head;
    while (tmp != NULL) {
        printf("%i\n", tmp->number);
        tmp = tmp->next;
    }

    return 0;
}
