#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element *data;
    int front, rear, capacity;
}DequeueType;

void init_dequeue (DequeueType *d) {
    d->front = d->rear = 0;
    d->capacity = 2;
    d->data = (element*)malloc(d->capacity * sizeof(element));
}

int is_full(DequeueType *d) {
    return ((d->rear + 1) % d->capacity == d->front);
}

int is_empty(DequeueType *d) {
    return (d->rear == d->front);
}

void push_front(DequeueType *d) {
    int item;
    if(is_full(d)){
        d->capacity *= 2;
        d->data = (element*)realloc(d->data, d->capacity * sizeof(element));
    }
    scanf("%d", &item);
    d->data[d->front] = item;
    d->front = (d->front - 1 + d->capacity) % d->capacity;
}

void push_back(DequeueType *d) {
    int item;
    if(is_full(d)){
        d->capacity *= 2;
        d->data = (element*)realloc(d->data, d->capacity * sizeof(element));
    }
    scanf("%d", &item);
    d->rear = (d->rear + 1) % d->capacity;
    d->data[d->rear] = item;
}

void pop_front(DequeueType *d) {
    if(is_empty(d)) printf("-1\n");
    else {
        d->front = (d->front + 1) % d->capacity;
        printf("%d\n", d->data[d->front]);
    }
}

void pop_back(DequeueType *d) {
    if(is_empty(d)) printf("-1\n");
    else {
        printf("%d\n", d->data[d->rear]);
        d->rear = (d->rear - 1 + d->capacity) % d->capacity;
    }
}

void size(DequeueType *d) {
    int size = 0;
    size = (d->capacity + d->rear - d->front) % d->capacity;
    printf("%d\n", size);
}

void print_empty(DequeueType *d) {
    printf("%d\n", is_empty(d));
}

void print_front (DequeueType *d) {
    if(is_empty(d)) printf("-1\n");
    else printf("%d\n", d->data[(d->front + 1) % d->capacity]);
}

void print_back (DequeueType *d) {
    if(is_empty(d)) printf("-1\n");
    else printf("%d\n", d->data[(d->rear)]);
}

int main(void) {
    int count = 0;
    char order[15];
    DequeueType d;
    
    init_dequeue(&d);
    scanf("%d", &count);
    for(int i = 0; i < count; i++) {
        scanf("%s", order);
        
        if(strcmp(order, "push_front") == 0) push_front(&d);
        else if(strcmp(order, "push_back") == 0) push_back(&d);
        else if(strcmp(order, "pop_front") == 0) pop_front(&d);
        else if(strcmp(order, "pop_back") == 0) pop_back(&d);
        else if(strcmp(order, "size") == 0) size(&d);
        else if(strcmp(order, "empty") == 0) print_empty(&d);
        else if(strcmp(order, "front") == 0) print_front(&d);
        else if(strcmp(order, "back") == 0) print_back(&d);
    }
    free(d.data);
    return 0;
}
