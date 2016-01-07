//
// Created by dekamaru on 07.01.16.
//

#ifndef SI_SERVER_QUEUE_H
#define SI_SERVER_QUEUE_H

#include "../network/packet.h"
#define MAX_QUEUE_SIZE 1000

typedef struct Queue {
    Packet *queue_array[MAX_QUEUE_SIZE];
    int front;
    int count;
} Queue;

Queue* queue_create();
void queue_push(Queue* q, Packet *value);
Packet* queue_pop(Queue* q);
int queue_empty(Queue* q);

#endif //SI_SERVER_QUEUE_H
