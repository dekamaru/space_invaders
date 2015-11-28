#include <stdint.h>

typedef struct Packet {
    uint32_t packet_id;
    uint32_t data_length;
    char data[0];
} Packet;

char* packet_create(uint32_t packet_id, uint32_t data_length, char* data);
