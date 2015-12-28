#include "packet.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void packet_create(char* buffer, uint32_t packet_id, uint32_t data_length, char* data) {
    Packet *p = (Packet*) buffer;
    p->packet_id = packet_id;
    p->data_length = data_length;
    strcpy(p->data, data);
}

char* packet_create_handshake(int player_id) {
    char* data = malloc(1);
    sprintf(data, "%i", player_id);
    char* buffer = malloc(sizeof(Packet));
    packet_create(buffer, 1, 1, data);
    return buffer;
}
