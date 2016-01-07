//
// Created by dekamaru on 07.01.16.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

Queue *queue_create() {
    Queue* q = malloc(sizeof(Queue));
    q->front = 0;
    q->count = 0;
    return q;
}

void queue_push(Queue *q, Packet *value) {
    if (q->count >= MAX_QUEUE_SIZE) {
        fprintf(stderr, "Queue is full.\n");
        exit(666);  /* Exit program, returning error code. */
    }
    int newElementIndex = (q->front + q->count) % MAX_QUEUE_SIZE;
    q->queue_array[newElementIndex] = value;
    q->count++;
}


Packet* queue_pop(Queue *q) {
    if (q->count <= 0) {
        fprintf(stderr, "Delete attempt on empty queue!.\n");
        exit(666);
    }
    Packet *to_return = q->queue_array[q->front];
    q->front++;
    q->front %= MAX_QUEUE_SIZE;
    q->count--;
    return to_return;
}

int queue_empty(Queue *q) {
    return (q->count == 0);
}
