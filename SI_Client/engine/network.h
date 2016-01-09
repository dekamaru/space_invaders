#ifndef SI_CLIENT_NETWORK_H
#define SI_CLIENT_NETWORK_H

#include <stdint.h>

typedef struct Packet {
    uint32_t packet_id;
    uint32_t data_length;
    char data[0];
} Packet;

int net_socket;
int net_client_connect(char* addr, uint16_t port);
Packet* net_receive_packet();
char* net_create_packet(uint32_t packet_id, uint32_t data_length, char* data);
void net_send_packet(char* packet, uint32_t length);


#endif //SI_CLIENT_NETWORK_H
