#include <stdlib.h>
#include <string.h>
#include "queue.h"

Queue* queue_create() {
    Queue* q = malloc(sizeof(Queue));
    q->first = q->last = NULL;
    q->size = 0;
    return q;
}

void queue_push(Queue* q, struct Packet* value) {
    Node* t = malloc(sizeof(Node));
    t->data = value;
    t->next = NULL;
    if (q->first == NULL && q->last == NULL) {
        q->first = q->last = t;
    } else {
        q->last->next = t;
        q->last = t;
    }
    q->size++;
}

struct Packet* queue_pop(Queue* q) {
    if (q->first == NULL && q->last == NULL) {
        return 0;
    }
    struct Packet* result = q->first->data;
    Node* h = NULL;
    Node* p = NULL;
    h = q->first;
    p = h->next;
    free(h);
    q->first = p;
    if (q->first == NULL) {
        q->last = q->first;
    }
    q->size--;
    return result;
}

int queue_empty(Queue* q) {
    if(q->size == 0) return 1;
    return 0;
}

int queue_size(Queue* q) {
    return q->size;
}
