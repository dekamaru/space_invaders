#include "packet.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Packet* packet_create(uint32_t packet_id, uint32_t data_length, char* data) {
    Packet *p = malloc(sizeof(Packet));
    p->packet_id = packet_id;
    p->data_length = data_length;
    strcpy(p->data, data);
    return p;
}

char* packet_create_handshake(int player_id) {
    char* data = malloc(1);
    sprintf(data, "%i", player_id);
    Packet *handshake = packet_create(1, 1, data);
    return (char*) handshake;
}
