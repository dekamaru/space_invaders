#include <stdio.h>
#include "network/net.h"
#include "network/packet.h"

int main(int *argc, char **argv)
{
    Packet *p = packet_create_handshake(3);
    printf("%i %i %s", p->packet_id, p->data_length, p->data);
    //net_server_start(27016);
    return 0;
}
