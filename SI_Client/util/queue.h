#ifndef UTIL_QUEUE_H
#define UTIL_QUEUE_H

typedef struct Node {
    struct Packet* data;
    struct Node *next;
} Node;

typedef struct Queue {
    int size;
    struct Node *first;
    struct Node *last;
} Queue;

Queue* queue_create();
void queue_push(Queue* q, struct Packet* value);
struct Packet* queue_pop(Queue* q);
int queue_empty(Queue* q);
int queue_size(Queue* q);

#endif // UTIL_QUEUE_H
