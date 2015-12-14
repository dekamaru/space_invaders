#ifndef NETWORK_PACKET_H
#define NETWORK_PACKET_H

#include <stdint.h>

typedef struct Packet {
    uint32_t packet_id;
    uint32_t data_length;
    char data[0];
} Packet;

char* packet_create(uint32_t packet_id, uint32_t data_length, char* data);
void packet_write_int(char* buffer, int value);
int packet_read_int(char** buffer);

#endif // NETWORK_PACKET_H
