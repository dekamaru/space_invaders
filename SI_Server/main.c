#include <stdio.h>
#include <string.h>
#include "network/packet.h"
#include "network/net.h"

int main(int *argc, char **argv)
{
    net_server_start(27015);
    return 0;
}
