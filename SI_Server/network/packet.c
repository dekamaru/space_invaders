#include "endian.h"
#include "packet.h"
#include <string.h>
#include <stdio.h>

#define INT_SIZE 4

void packet_serialize(unsigned char* buffer, Packet *p) {
    buffer = endian_pack_int(buffer, p->packet_id);
    buffer = endian_pack_int(buffer, p->data_length);
    buffer = endian_pack_string(buffer, p->data, p->data_length);
}

int packet_size(Packet *p) {
    return INT_SIZE + INT_SIZE + p->data_length;
}

int packet_buffer_size(int data_length) {
    return INT_SIZE + INT_SIZE + data_length; // kostyl
}

Packet* packet_deserialize(unsigned char* buffer) {
    Packet* p = malloc(sizeof(Packet));
    p->packet_id = endian_unpack_int(buffer);
    buffer += INT_SIZE;
    p->data_length = endian_unpack_int(buffer);
    buffer += INT_SIZE;
    p->data = malloc(sizeof(char) * p->data_length);
    endian_unpack_string(buffer, p->data, p->data_length);
    buffer += p->data_length;
    return p;
}

unsigned char* packet_create(int packet_id, int data_length, char* data) {
    Packet *p = malloc(sizeof(Packet));
    p->packet_id = packet_id;
    p->data_length = data_length;
    p->data = data;
    unsigned char* buffer = malloc(packet_size(p));
    packet_serialize(buffer, p);
    free(p);
    return buffer;
}
