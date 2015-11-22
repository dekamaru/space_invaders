#define P_GAME_WAITING 0
#define P_GAME_STARTED 1
#define P_GAME_ENDED 2
#define P_GAME_FIELD 3

#define P_DATA_SIZE 500

#include "endian.h"

typedef struct Packet {
    int data_length;
    int packet_id;
    char data[P_DATA_SIZE];
} Packet;

unsigned char* serialize_packet(unsigned char* buffer, Packet* p) {
    buffer = endian_pack_int(buffer, p->data_length);
    buffer = endian_pack_int(buffer, p->packet_id);
    buffer = endian_pack_string(buffer, P_DATA_SIZE, p->data);
    return buffer;
}
