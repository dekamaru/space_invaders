#include <stdio.h>
#include <string.h>
#include "util/queue.h"
#include "util/endian.h"
#include "network/net.h"
#include "network/packet.h"

int main(int *argc, char **argv)
{
    net_server_start(27016);
    return 0;
}
