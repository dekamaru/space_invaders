#include "packet.h"
#include <string.h>
#include <stdio.h>

char* packet_create(uint32_t packet_id, uint32_t data_length, char* data) {
    char* buffer = malloc(1024);
    Packet *p = (Packet*) buffer;
    p->packet_id = packet_id;
    p->data_length = data_length;
    strcpy(p->data, data);
    return buffer;
}

