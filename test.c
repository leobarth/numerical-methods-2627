#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
    struct Element* ptrNext;
    int data;
} Element;

Element* appendAtFront(Element* start, int data) {
    Element* newElement = malloc(sizeof(Element));
    newElement->ptrNext = start;
    newElement->data = data;
    return newElement;
}

int main() {
    Element* end = malloc(sizeof(Element));
    end->ptrNext = NULL;
    end->data = 50;

    // create linked list with entries 50, 40, 30, 20, 10, 0
    int temp = end->data;
    while (temp > 0) {
        temp -= 10;
        end = appendAtFront(end, temp);
    }

    while (end != NULL) {
        printf("%d ", end->data);
        end = end->ptrNext;
    }
    printf("\n");

    return 0;
}